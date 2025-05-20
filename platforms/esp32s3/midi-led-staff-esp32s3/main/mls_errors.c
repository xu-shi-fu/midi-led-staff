// mls_errors.c

#include "mls_errors.h"
#include "mls_common.h"
#include "mls_tasks.h"

////////////////////////////////////////////////////////////////////////////////
// buffer

typedef struct
{

    mls_error_meta head;

    char message[99];
    char end;

} mls_error_info;

static mls_error_info the_error_buffer;

////////////////////////////////////////////////////////////////////////////////
// error holder

void mls_error_holder_init(mls_error_holder *holder)
{
    if (holder)
    {
        memset(holder, 0, sizeof(holder[0]));
    }
}

void mls_error_holder_reset(mls_error_holder *holder)
{
    if (holder)
    {
        holder->err = NULL;
    }
}

void mls_error_holder_push(mls_error_holder *holder, mls_error err)
{
    if (holder && err)
    {
        holder->err = err;
    }
}

mls_bool mls_error_holder_has_error(mls_error_holder *holder)
{
    if (holder)
    {
        return holder->err ? YES : NO;
    }
    return NO;
}

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

void mls_errors_check_message(mls_error err)
{
    if (err)
    {
        if (err->message == NULL)
        {
            err->message = "[no_message]";
        }
    }
}

void mls_errors_log(mls_error err)
{
    if (err)
    {
        mls_errors_check_message(err);
        int code = err->code;
        const char *msg = err->message;
        ESP_LOGE(TAG, "[error code:%d msg:%s]", code, msg);
    }
}

void mls_errors_log_warn(mls_error err)
{
    if (err)
    {
        mls_errors_check_message(err);
        int code = err->code;
        const char *msg = err->message;
        ESP_LOGW(TAG, "[error code:%d msg:%s]", code, msg);
    }
}

void mls_panic(mls_error err)
{
    if (err)
    {
        mls_errors_check_message(err);
        int code = err->code;
        const char *msg = err->message;
        ESP_LOGE(TAG, "[panic code:%d msg:%s]", code, msg);

        for (;;)
        {
            mls_sleep(500);
        }
    }
}
