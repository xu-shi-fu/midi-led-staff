// mls_udp.c

#include "mls_cp_udp_adapter.h"

#include "mls_control_protocol.h"
#include "mls_buffer.h"
#include "mls_common_esp.h"
#include "mls_app.h"

////////////////////////////////////////////////////////////////////////////////
// internal structures

typedef struct mls_cp_udp_adapter_t
{
    mls_cp_implementation impl; // 注意: 这个字段必须放在结构的开头, 以便使其地址与 owner 相同

    mls_cp_server *server;
    mls_cp_udp_module *module_outer;
    mls_settings *settings;

    int port;
    int socket_fd;
    struct sockaddr_in address;

    mls_cp_context context;
    mls_cp_request request;
    mls_cp_response response;
    mls_buffer rx_buffer;
    mls_buffer tx_buffer;
    mls_cp_block_array rx_blocks;
    mls_cp_block_array tx_blocks;
    mls_cp_dispatcher dispatcher; // 适配器的 dispatcher, 用于处理请求

    mls_task task;

} mls_cp_udp_adapter;

////////////////////////////////////////////////////////////////////////////////
// 内部函数(定义)

void convert_address_from_sock_to_cp(struct sockaddr_in *src, mls_cp_address *dst);
void convert_address_from_cp_to_sock(mls_cp_address *src, struct sockaddr_in *dst);

mls_error mls_cp_udp_module_on_init(mls_module *m);
mls_error mls_cp_udp_module_on_create(mls_module *m);
mls_error mls_cp_udp_module_on_start(mls_module *m);

// 从模块中获取适配器
mls_cp_udp_adapter *mls_cp_udp_module_get_adapter(mls_module *m);

mls_error mls_cp_udp_adapter_init(mls_cp_udp_adapter *adapter);
mls_error mls_cp_udp_adapter_create(mls_cp_udp_adapter *adapter);
mls_error mls_cp_udp_adapter_wire(mls_cp_udp_adapter *adapter);
mls_error mls_cp_udp_adapter_start(mls_cp_udp_adapter *adapter);

// mls_error mls_cp_udp_adapter_listen(mls_cp_udp_adapter *adapter);

mls_error mls_cp_udp_adapter_sock_create(mls_cp_udp_adapter *adapter);
mls_error mls_cp_udp_adapter_sock_bind(mls_cp_udp_adapter *adapter);
mls_error mls_cp_udp_adapter_sock_receive(mls_cp_udp_adapter *adapter);
mls_error mls_cp_udp_adapter_sock_handle(mls_cp_udp_adapter *adapter);
mls_error mls_cp_udp_adapter_sock_destroy(mls_cp_udp_adapter *adapter);

mls_error mls_cp_udp_adapter_run_task(mls_cp_udp_adapter *adapter, bool infinity);
mls_error mls_cp_udp_adapter_task_fn(mls_task *task);
mls_error mls_cp_udp_adapter_dispatcher_fn(struct mls_cp_context_t *context, struct mls_cp_response_t *resp);

////////////////////////////////////////////////////////////////////////////////
// 内部函数(实现)

mls_error mls_cp_udp_module_on_init(mls_module *m)
{
    mls_cp_udp_adapter *adapter = mls_cp_udp_module_get_adapter(m);
    mls_app *app = m->app;

    adapter->server = &app->server.server;
    adapter->settings = &app->settings.settings;

    return mls_cp_udp_adapter_init(adapter);
}

mls_error mls_cp_udp_module_on_create(mls_module *m)
{
    mls_cp_udp_adapter *adapter = mls_cp_udp_module_get_adapter(m);
    mls_settings *settings = adapter->settings;

    adapter->port = settings->udp.port;

    mls_error err = mls_cp_udp_adapter_create(adapter);
    if (err)
    {
        return err;
    }

    return mls_cp_udp_adapter_wire(adapter);
}

mls_error mls_cp_udp_module_on_start(mls_module *m)
{
    mls_cp_udp_adapter *adapter = mls_cp_udp_module_get_adapter(m);
    return mls_cp_udp_adapter_start(adapter);
}

mls_cp_udp_adapter *mls_cp_udp_module_get_adapter(mls_module *m)
{
    if (m == NULL)
    {
        return NULL;
    }

    mls_cp_udp_adapter *adapter = m->inner; // inner==adapter

    if (adapter == NULL)
    {
        size_t size = sizeof(mls_cp_udp_adapter);
        adapter = malloc(size);
        if (adapter)
        {
            memset(adapter, 0, size);
            adapter->context.implementation = &adapter->impl;
            adapter->impl.name = m->name;
            adapter->impl.outer = adapter;
        }
        m->inner = adapter;
    }

    return adapter;
}

mls_error mls_cp_udp_adapter_init(mls_cp_udp_adapter *adapter)
{
    mls_buffer *rx_buffer = &adapter->rx_buffer;
    mls_buffer *tx_buffer = &adapter->tx_buffer;
    mls_cp_block_array *rx_blocks = &adapter->rx_blocks;
    mls_cp_block_array *tx_blocks = &adapter->tx_blocks;
    mls_task *task = &adapter->task;

    mls_buffer_init(rx_buffer);
    mls_buffer_init(tx_buffer);
    mls_cp_block_array_init(rx_blocks);
    mls_cp_block_array_init(tx_blocks);
    mls_task_init(task);

    return NULL;
}

mls_error mls_cp_udp_adapter_wire(mls_cp_udp_adapter *adapter)
{
    mls_cp_context *context = &adapter->context;
    mls_cp_request *request = &adapter->request;
    mls_cp_response *response = &adapter->response;
    mls_cp_block_array *rx_blocks = &adapter->rx_blocks;
    mls_cp_block_array *tx_blocks = &adapter->tx_blocks;
    mls_cp_dispatcher *dispatcher = &adapter->dispatcher;
    mls_buffer *rx_buffer = &adapter->rx_buffer;
    mls_buffer *tx_buffer = &adapter->tx_buffer;
    mls_task *task = &adapter->task;

    context->request = request;
    context->response = response;
    context->server = adapter->server;
    context->implementation = &adapter->impl;
    context->dispatcher = dispatcher;
    context->handler = NULL;

    request->context = context;
    request->blocks = rx_blocks;
    request->buffer = rx_buffer;

    response->context = context;
    response->blocks = tx_blocks;
    response->buffer = tx_buffer;

    task->name = "mls_cp_udp_adapter_task";
    task->fn = mls_cp_udp_adapter_task_fn;
    task->data = adapter; // 传递 adapter 作为任务数据

    dispatcher->provider = adapter; // 适配器作为 dispatcher 的提供者
    dispatcher->fn = mls_cp_udp_adapter_dispatcher_fn;

    return NULL;
}

mls_error mls_cp_udp_adapter_create(mls_cp_udp_adapter *adapter)
{
    mls_error err;
    mls_error_holder eh;
    mls_error_holder_init(&eh);

    mls_buffer *rx_buffer = &adapter->rx_buffer;
    mls_buffer *tx_buffer = &adapter->tx_buffer;
    mls_cp_block_array *rx_blocks = &adapter->rx_blocks;
    mls_cp_block_array *tx_blocks = &adapter->tx_blocks;

    rx_buffer->capacity = CP_RX_BUFFER_SIZE;
    tx_buffer->capacity = CP_TX_BUFFER_SIZE;

    err = mls_buffer_create(rx_buffer);
    mls_error_holder_push(&eh, err);

    err = mls_buffer_create(tx_buffer);
    mls_error_holder_push(&eh, err);

    err = mls_cp_block_array_create(rx_blocks, CP_RX_BLOCK_ARRAY_CAPACITY);
    mls_error_holder_push(&eh, err);

    err = mls_cp_block_array_create(tx_blocks, CP_TX_BLOCK_ARRAY_CAPACITY);
    mls_error_holder_push(&eh, err);

    return mls_error_holder_get_error(&eh);
}

mls_error mls_cp_udp_adapter_start(mls_cp_udp_adapter *adapter)
{
    mls_task *task = &adapter->task;
    return mls_task_start(task);
}

// deprecated
// mls_error mls_cp_udp_adapter_listen(mls_cp_udp_adapter *adapter)
// {
//     mls_cp_udp_adapter *ctx = adapter;

//     const mls_string host = "0.0.0.0";
//     int port = ctx->port;

//     // create socket
//     int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
//     if (sock_fd < 0)
//     {
//         ESP_LOGE(TAG, "error: udp socket create failed");
//         return mls_errors_make(500, "udp socket create error");
//     }

//     // address
//     struct sockaddr_in addr;
//     addr.sin_family = AF_INET;
//     addr.sin_addr.s_addr = inet_addr(host);
//     addr.sin_port = htons(port);

//     // bind
//     int ret = bind(sock_fd, (struct sockaddr *)&addr, sizeof(addr));
//     if (ret < 0)
//     {
//         ESP_LOGE(TAG, "error: udp bind return: %d", ret);
//         return mls_errors_make(0, "udp bind error");
//     }

//     ESP_LOGI(TAG, "udp://listen@%s:%d", host, port);

//     ctx->address = addr;
//     ctx->socket_fd = sock_fd;

//     return NULL;
// }

void mls_cp_udp_adapter_nop(void *p)
{
}

mls_error mls_cp_udp_adapter_task_fn(mls_task *task)
{
    mls_cp_udp_adapter *adapter = task->data;
    mls_cp_context *ctx = &adapter->context;
    mls_cp_request *request = &adapter->request;
    mls_cp_response *response = &adapter->response;

    bool infinity = true;

    mls_cp_udp_adapter_nop(ctx);
    mls_cp_udp_adapter_nop(request);
    mls_cp_udp_adapter_nop(response);

    // return NULL;

    return mls_cp_udp_adapter_run_task(adapter, infinity);
}

mls_error mls_cp_udp_adapter_run_task(mls_cp_udp_adapter *adapter, bool infinity)
{
    if (adapter == NULL)
    {
        ESP_LOGE(TAG, "mls_cp_udp_adapter_run_loop: adapter is NULL");
        return mls_errors_make(500, "adapter is NULL");
    }

    // create
    mls_error err = mls_cp_udp_adapter_sock_create(adapter);
    if (err)
    {
        return err;
    }

    // bind
    err = mls_cp_udp_adapter_sock_bind(adapter);
    if (err)
    {
        mls_cp_udp_adapter_sock_destroy(adapter);
        return err;
    }

    // receive loop
    do
    {
        if (err)
        {
            mls_errors_log(err);
            err = NULL;
            mls_sleep(50);
        }

        err = mls_cp_udp_adapter_sock_receive(adapter);
        if (err)
        {
            continue;
        }

        err = mls_cp_udp_adapter_sock_handle(adapter);
        if (err)
        {
            continue;
        }

    } while (infinity);

    return mls_cp_udp_adapter_sock_destroy(adapter);
}

mls_error mls_cp_udp_adapter_sock_create(mls_cp_udp_adapter *adapter)
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        ESP_LOGE(TAG, "error: udp socket create failed");
        return mls_errors_make(500, "udp socket create error");
    }
    adapter->socket_fd = fd;
    return NULL;
}

mls_error mls_cp_udp_adapter_sock_bind(mls_cp_udp_adapter *adapter)
{
    const char *host = "0.0.0.0";
    int port = adapter->port;

    // address
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(host);
    addr.sin_port = htons(port);

    int fd = adapter->socket_fd;
    int ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0)
    {
        ESP_LOGE(TAG, "error: udp bind return: %d", ret);
        return mls_errors_make(0, "udp bind error");
    }

    ESP_LOGI(TAG, "mls_cp_udp_adapter_sock_bind: listen UDP at %s:%d", host, port);
    return NULL;
}

mls_error mls_cp_udp_adapter_sock_receive(mls_cp_udp_adapter *adapter)
{
    int fd = adapter->socket_fd;
    mls_cp_request *request = &adapter->request;
    mls_buffer *rx_buffer = request->buffer;
    mls_cp_block_array *rx_blocks = request->blocks;
    mls_byte *buffer_ptr = rx_buffer->data;
    size_t buffer_size = rx_buffer->capacity;

    struct sockaddr_in addr1;
    mls_cp_address addr2;
    socklen_t addr1_len = sizeof(addr1);
    memset(&addr1, 0, sizeof(addr1));
    memset(&addr2, 0, sizeof(addr2));

    ssize_t data_len = recvfrom(fd, buffer_ptr, buffer_size, 0, (struct sockaddr *)&addr1, &addr1_len);
    if (data_len < 1)
    {
        ESP_LOGE(TAG, "error: udp recvfrom failed, data_len: %zd", data_len);
        return mls_errors_make(500, "udp recvfrom error");
    }

    convert_address_from_sock_to_cp(&addr1, &addr2);
    mls_cp_block_array_reset(rx_blocks);

    mls_cp_address_log(&addr2);

    rx_buffer->size = data_len;
    request->remote = addr2;
    return NULL;
}

mls_error mls_cp_udp_adapter_sock_destroy(mls_cp_udp_adapter *adapter)
{
    int fd = adapter->socket_fd;
    adapter->socket_fd = 0;
    if (fd > 0)
    {
        close(fd);
        ESP_LOGI(TAG, "udp socket closed");
    }
    else
    {
        ESP_LOGW(TAG, "udp socket already closed");
    }
    return NULL;
}

mls_error mls_cp_udp_adapter_sock_handle(mls_cp_udp_adapter *adapter)
{
    mls_cp_context *ctx = &adapter->context;
    return mls_cp_server_handle(ctx);
}

mls_error mls_cp_udp_adapter_send(mls_cp_udp_adapter *adapter)
{
    mls_buffer *buffer = adapter->response.buffer;
    int fd = adapter->socket_fd;
    mls_byte *data_ptr = buffer->data;
    size_t data_len = buffer->size;
    int flags = 0;
    struct mls_cp_address_t addr1;
    struct sockaddr_in addr2;
    ssize_t addr2_len = sizeof(addr2);

    addr1 = adapter->response.remote;
    memset(&addr2, 0, addr2_len);
    convert_address_from_cp_to_sock(&addr1, &addr2);

    int err_code = 0;
    const char *err_msg = NULL;
    int res = sendto(fd, data_ptr, data_len, flags, (struct sockaddr *)&addr2, addr2_len);
    if (res < 0)
    {
        err_code = errno;
        err_msg = esp_err_to_name(err_code);
        ESP_LOGW(TAG, "      res=%d", res);
        ESP_LOGW(TAG, "    errno=%d (%s)", err_code, err_msg);
    }

    ESP_LOGW(TAG, "mls_cp_udp_adapter_send:");
    ESP_LOGW(TAG, "           fd=%d", fd);
    ESP_LOGW(TAG, "         data=%d", (int)data_ptr);
    ESP_LOGW(TAG, "     data_len=%d", (int)data_len);
    ESP_LOGW(TAG, "        flags=%d", flags);
    ESP_LOGW(TAG, "    addr2_len=%d", (int)addr2_len);

    mls_cp_address_log(&addr1);

    if (res < 0)
    {
        return mls_errors_make(res, "mls_cp_udp_adapter_send: sendto() return err");
    }

    return NULL;
}

mls_error mls_cp_udp_adapter_dispatcher_fn(struct mls_cp_context_t *context, struct mls_cp_response_t *resp)
{
    mls_cp_dispatcher *disp = context->dispatcher;
    mls_cp_udp_adapter *adapter = disp->provider;
    return mls_cp_udp_adapter_send(adapter);
}

void convert_address_from_sock_to_cp(struct sockaddr_in *src, mls_cp_address *dst)
{
    int size1 = sizeof(src[0]);
    int size2 = sizeof(dst[0]);
    int size12 = MLS_MIN(size1, size2);
    memset(dst, 0, size2);
    memcpy(dst, src, size12);
}

void convert_address_from_cp_to_sock(mls_cp_address *src, struct sockaddr_in *dst)
{
    int size1 = sizeof(src[0]);
    int size2 = sizeof(dst[0]);
    int size12 = MLS_MIN(size1, size2);
    memset(dst, 0, size2);
    memcpy(dst, src, size12);
}

void mls_cp_address_log(mls_cp_address *addr)
{
#define ITEM_COUNT 16
    int n[ITEM_COUNT];
    for (int i = 0; i < ITEM_COUNT; ++i)
    {
        n[i] = addr->addr[i];
    }

    ESP_LOGI(TAG, "mls_cp_address( 0~3 ): %d-%d-%d-%d", n[0], n[1], n[2], n[3]);
    ESP_LOGI(TAG, "mls_cp_address( 4~7 ): %d-%d-%d-%d", n[4], n[5], n[6], n[7]);
    ESP_LOGI(TAG, "mls_cp_address( 8~11): %d-%d-%d-%d", n[8], n[9], n[10], n[11]);
    ESP_LOGI(TAG, "mls_cp_address(12~15): %d-%d-%d-%d", n[12], n[13], n[14], n[15]);
}

////////////////////////////////////////////////////////////////////////////////
// public functions

mls_module *mls_cp_udp_module_init(mls_cp_udp_module *m1)
{
    mls_module *m2 = &m1->module;
    m2->name = "mls_cp_udp_adapter_module";
    m2->on_init = mls_cp_udp_module_on_init;
    m2->on_create = mls_cp_udp_module_on_create;
    m2->on_start = mls_cp_udp_module_on_start;
    return m2;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
