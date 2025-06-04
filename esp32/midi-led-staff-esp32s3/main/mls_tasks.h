// mls_tasks.h

#ifndef __mls_tasks_h__
#define __mls_tasks_h__

#include "mls_common_mls.h"
#include "mls_errors.h"

// #include "mls_app.h"

struct mls_app_t;
struct mls_task_t;

/***
 * 函数指针
 */

typedef mls_error (*mls_task_func)(struct mls_task_t *task);

// struct

typedef struct mls_task_t
{
    mls_error error;
    struct mls_app_t *app;
    mls_task_func fn;
    mls_uint priority;
    const char *name;
    TaskHandle_t handle;
    void *data; // 调用端自定义数据

} mls_task;

typedef struct
{
} mls_mutex;

// functions

mls_error mls_task_init(mls_task *task);
mls_error mls_task_start(mls_task *task);
mls_error mls_task_run(mls_task *task);

void mls_sleep(uint32_t ms);

void mls_mutex_init(mls_mutex *m);
void mls_mutex_lock(mls_mutex *m);
void mls_mutex_unlock(mls_mutex *m);

#endif // __mls_tasks_h__
