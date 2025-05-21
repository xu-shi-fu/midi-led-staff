#include "mls_cp_mock_adapter.h"

#include "mls_app.h"

////////////////////////////////////////////////////////////////////////////////
// struct

typedef struct mls_cp_mock_adapter_t
{

    mls_cp_implementation implementation; // 适配器实现, 必须放在开头!

    mls_cp_server *server;

    mls_cp_context context;
    mls_cp_request request;
    mls_cp_response response;

    mls_buffer rx_buffer;
    mls_buffer tx_buffer;
    mls_cp_block_array rx_blocks;
    mls_cp_block_array tx_blocks;

} mls_cp_mock_adapter;

////////////////////////////////////////////////////////////////////////////////
// function

mls_cp_mock_adapter *mls_cp_mock_module_get_adapter(mls_module *m);

mls_error mls_cp_mock_module_on_init(mls_module *m);
mls_error mls_cp_mock_module_on_create(mls_module *m);
mls_error mls_cp_mock_module_on_start(mls_module *m);
mls_error mls_cp_mock_module_on_run_loop(mls_module *m);

mls_error mls_cp_mock_adapter_init(mls_cp_mock_adapter *adapter);
mls_error mls_cp_mock_adapter_create(mls_cp_mock_adapter *adapter);
mls_error mls_cp_mock_adapter_start(mls_cp_mock_adapter *adapter);
mls_error mls_cp_mock_adapter_run(mls_cp_mock_adapter *adapter);

////////////////////////////////////////////////////////////////////////////////
// implementation

mls_module *mls_cp_mock_module_init(mls_cp_mock_module *m1)
{
    mls_module *m2 = &m1->module;

    m2->name = "mls_cp_mock_module";
    m2->inner = NULL;

    m2->on_init = mls_cp_mock_module_on_init;
    m2->on_create = mls_cp_mock_module_on_create;
    m2->on_start = mls_cp_mock_module_on_start;
    m2->on_run = mls_cp_mock_module_on_run_loop;

    return m2;
}

mls_cp_mock_adapter *mls_cp_mock_module_get_adapter(mls_module *m)
{
    if (m == NULL)
    {
        return NULL;
    }

    mls_cp_mock_adapter *adapter = m->inner; // inner is adapter

    if (adapter == NULL)
    {
        size_t size = sizeof(adapter[0]);
        adapter = malloc(size);
        memset(adapter, 0, size);
        mls_cp_mock_adapter_init(adapter);
        m->inner = adapter;
    }

    return adapter;
}

mls_error mls_cp_mock_module_on_init(mls_module *m)
{
    mls_cp_mock_adapter *adapter = mls_cp_mock_module_get_adapter(m);
    if (adapter == NULL)
    {
        return mls_errors_make(500, "mls_cp_mock_module_on_init: failed to get adapter");
    }
    adapter->server = &m->app->server.server;
    return mls_cp_mock_adapter_init(adapter);
}

mls_error mls_cp_mock_module_on_create(mls_module *m)
{
    mls_cp_mock_adapter *adapter = mls_cp_mock_module_get_adapter(m);
    return mls_cp_mock_adapter_create(adapter);
}

mls_error mls_cp_mock_module_on_start(mls_module *m)
{
    mls_cp_mock_adapter *adapter = mls_cp_mock_module_get_adapter(m);
    return mls_cp_mock_adapter_start(adapter);
}

mls_error mls_cp_mock_module_on_run_loop(mls_module *m)
{
    mls_cp_mock_adapter *adapter = mls_cp_mock_module_get_adapter(m);
    return mls_cp_mock_adapter_run(adapter);
}

mls_error mls_cp_mock_adapter_init(mls_cp_mock_adapter *adapter)
{
    return NULL;
}

mls_error mls_cp_mock_adapter_create(mls_cp_mock_adapter *adapter)
{
    return NULL;
}

mls_error mls_cp_mock_adapter_start(mls_cp_mock_adapter *adapter)
{
    return NULL;
}

mls_error mls_cp_mock_adapter_run(mls_cp_mock_adapter *adapter)
{
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
