// mls_tasks.h

#ifndef __mls_tasks_h__
#define __mls_tasks_h__

#include "mls_common.h"
#include "mls_errors.h"
#include "mls_app.h"

// static TaskHandle_t task_handle_led = NULL;
// static TaskHandle_t task_handle_ble = NULL;
// static TaskHandle_t task_handle_midi = NULL;
// static TaskHandle_t task_handle_engine = NULL;
// static TaskHandle_t task_handle_wifi = NULL;
// static TaskHandle_t task_handle_udp = NULL;

/***
 * 函数指针
 */

typedef mls_error (*mls_task_func)(mls_app *);

typedef struct
{
    mls_error error;
    mls_app *app;
    mls_task_func fn;
    uint priority;
    const char *name;
    TaskHandle_t handle;

} mls_task;

mls_error mls_tasks_init(mls_task *task);
mls_error mls_tasks_start(mls_task *task);
mls_error mls_tasks_run(mls_task *task);
void mls_tasks_sleep(uint32_t ms);

#endif // __mls_tasks_h__
