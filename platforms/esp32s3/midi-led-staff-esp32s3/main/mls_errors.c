// mls_errors.c

#include "mls_errors.h"
#include "mls_common.h"

////////////////////////////////////////////////////////////////////////////////
// buffer

typedef struct
{

    mls_error_t head;

    char message[99];
    char end;

} mls_error_info;

static mls_error_info the_error_buffer;

////////////////////////////////////////////////////////////////////////////////
// error functions

mls_error mls_errors_make(int code, char *const msg)
{
    mls_error_info *buffer = &the_error_buffer;
    if (msg)
    {
        size_t l1 = strlen(msg);
        size_t l2 = sizeof(buffer->message);
        size_t len = (l1 < l2) ? l1 : l2;
        memcpy(buffer->message, msg, len + 1);
    }
    else
    {
        buffer->message[0] = 0;
    }
    buffer->head.code = code;
    buffer->head.message = buffer->message;
    buffer->end = 0;
    return &buffer->head;
}

void mls_errors_log(mls_error err)
{
    if (err)
    {
        int code = err->code;
        const char *msg = err->message;
        if (msg == NULL)
        {
            msg = "[no_message]";
        }
        ESP_LOGE(TAG, "[error code:%d msg:%s]", code, msg);
    }
}

void mls_errors_log_warn(mls_error err)
{
    if (err)
    {
        int code = err->code;
        const char *msg = err->message;
        if (msg == NULL)
        {
            msg = "[no_message]";
        }
        ESP_LOGW(TAG, "[error code:%d msg:%s]", code, msg);
    }
}
