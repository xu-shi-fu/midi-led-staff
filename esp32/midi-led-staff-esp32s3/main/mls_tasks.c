#include "mls_tasks.h"
#include "mls_common_esp.h"

////////////////////////////////////////////////////////////////////////////////
// fn

void mls_sleep(uint32_t ms)
{
    mls_int32 ticks = ms / portTICK_PERIOD_MS;
    if (ticks < 1)
    {
        ticks = 1;
    }
    vTaskDelay(ticks);
}

void mls_tasks_run_idle_loop()
{
    for (;;)
    {
        mls_sleep(1000);
    }
}

void mls_tasks_common_fn(void *p)
{
    struct mls_task_t *task = p;
    if (task)
    {
        // ESP_LOGI(TAG, "run task: %s", task->name);
        mls_task_func fn = task->fn;
        if (fn)
        {
            mls_error err = fn(task);
            mls_errors_log_warn(err);
            task->error = err;
        }
        else
        {
            ESP_LOGW(TAG, "fn|app of task is NULL, task: %s", task->name);
        }
        ESP_LOGI(TAG, "task is done, name: %s", task->name);
    }

    // 执行完成后进入死循环,否则系统会出错
    mls_tasks_run_idle_loop();
}

////////////////////////////////////////////////////////////////////////////////
// task

mls_error mls_task_init(mls_task *t)
{
    if (t)
    {
        memset(t, 0, sizeof(t[0]));
        t->priority = 1;
        t->name = "unnamed_task";
    }
    return NULL;
}

mls_error mls_task_start(mls_task *task)
{
    // todo ...

    ESP_LOGI(TAG, "start task: %s", task->name);

    uint16_t stack_depth = 4 * 1024;
    mls_uint priority = task->priority;
    TaskHandle_t *h = &task->handle;
    const char *const task_name = task->name;
    void *params = task;

    xTaskCreate(mls_tasks_common_fn, task_name, stack_depth, params, priority, h);

    return NULL;
}

mls_error mls_task_run(mls_task *t)
{
    ESP_LOGI(TAG, "run task: %s", t->name);

    mls_task_func fn = t->fn;

    if (fn)
    {
        return fn(t);
    }
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// mutex

void mls_mutex_init(mls_mutex *m)
{

    // todo ...
}

void mls_mutex_lock(mls_mutex *m)
{
    // todo ...
}

void mls_mutex_unlock(mls_mutex *m)
{
    // todo ...
}

////////////////////////////////////////////////////////////////////////////////
// EOF
