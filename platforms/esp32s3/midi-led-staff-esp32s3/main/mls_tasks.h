// mls_tasks.h

#ifndef __mls_tasks_h__
#define __mls_tasks_h__

#include "mls_common.h"
#include "mls_errors.h"

// #include "mls_app.h"

struct mls_app_t;

/***
 * 函数指针
 */

typedef mls_error (*mls_task_func)(struct mls_app_t *);

// struct

typedef struct
{
    mls_error error;
    struct mls_app_t *app;
    mls_task_func fn;
    uint priority;
    const char *name;
    TaskHandle_t handle;

} mls_task;

typedef struct
{
} mls_mutex;

// functions

mls_error mls_tasks_init(mls_task *task);
mls_error mls_tasks_start(mls_task *task);
mls_error mls_tasks_run(mls_task *task);
void mls_tasks_sleep(uint32_t ms);

void mls_mutex_init(mls_mutex *m);
void mls_mutex_lock(mls_mutex *m);
void mls_mutex_unlock(mls_mutex *m);

#endif // __mls_tasks_h__
