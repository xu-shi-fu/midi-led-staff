
#include "mls_module.h"
#include "mls_common_esp.h"

////////////////////////////////////////////////////////////////////////////////
// internal functions

mls_error mls_module_invoke_lifecycle_fn(mls_module *module, mls_lifecycle_phase phase);

mls_error mls_module_invoke_lifecycle_fn(mls_module *module, mls_lifecycle_phase phase)
{
    mls_module_life_func fn;
    const char *module_name;
    const char *phase_name;

    if (module == NULL)
    {
        return NULL;
    }
    if (!module->enabled)
    {
        return NULL;
    }

    switch (phase)
    {
    case MLS_LIFECYCLE_PHASE_INIT:
        fn = module->on_init;
        phase_name = "init";
        break;
    case MLS_LIFECYCLE_PHASE_CREATE:
        fn = module->on_create;
        phase_name = "create";
        break;
    case MLS_LIFECYCLE_PHASE_START:
        fn = module->on_start;
        phase_name = "start";
        break;
    case MLS_LIFECYCLE_PHASE_RESUME:
        fn = module->on_resume;
        phase_name = "resume";
        break;
    case MLS_LIFECYCLE_PHASE_RUN:
        fn = module->on_run;
        phase_name = "run";
        break;
    case MLS_LIFECYCLE_PHASE_PAUSE:
        fn = module->on_pause;
        phase_name = "pause";
        break;
    case MLS_LIFECYCLE_PHASE_STOP:
        fn = module->on_stop;
        phase_name = "stop";
        break;
    case MLS_LIFECYCLE_PHASE_DESTROY:
        fn = module->on_destroy;
        phase_name = "destroy";
        break;
    default:
        fn = NULL;
        break;
    }

    if (fn)
    {
        module_name = module->name;
        ESP_LOGI(TAG, "mls-module: on_%s@%s", phase_name, module_name);
        return fn(module);
    }
    return NULL;
}

mls_error mls_module_array_invoke_lifecycle_fn(mls_module_array *array, mls_lifecycle_phase phase)
{

    mls_error err;
    mls_module *item;
    mls_module_array_iterator iter;
    mls_module_array_iterator_init(&iter, array);

    for (;;)
    {
        if (!mls_module_array_iterator_has_more(&iter))
        {
            break;
        }
        item = mls_module_array_iterator_next(&iter);
        err = mls_module_invoke_lifecycle_fn(item, phase);
        if (err)
        {
            return err;
        }
    }

    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// mls_module_array::

void mls_module_array_init(mls_module_array *array)
{
    if (array)
    {
        memset(array, 0, sizeof(array[0]));
    }
}

mls_error mls_module_array_create(mls_module_array *array, uint capacity)
{
    if (array == NULL)
    {
        return mls_errors_make(500, "mls_module_array is nil");
    }

    if (array->modules)
    {
        return NULL;
    }

    if (capacity < 1)
    {
        capacity = array->capacity;
    }

    size_t len = capacity * sizeof(mls_module_ref);
    void *p = malloc(len);
    if (p == NULL)
    {
        return mls_errors_make(500, "mls_module_array_create: malloc return nil");
    }

    array->modules = p;
    array->capacity = capacity;
    array->count = 0;
    return NULL;
}

void mls_module_array_release(mls_module_array *array)
{
    if (array)
    {
        if (array->modules)
        {
            free(array->modules);
            array->modules = NULL;
            array->count = 0;
        }
    }
}

bool mls_module_array_is_overflow(mls_module_array *array)
{
    if (array == NULL)
    {
        return false;
    }
    return array->overflow;
}

void mls_module_array_reset(mls_module_array *array)
{
    if (array)
    {
        array->count = 0;
        array->overflow = false;
    }
}

void mls_module_array_add(mls_module_array *array, mls_module *item)
{
    if (array && item)
    {
        uint max = array->capacity;
        uint i = array->count;
        if (i < max)
        {
            array->modules[i].module = item;
            array->count = i + 1;
        }
        else
        {
            array->overflow = true;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// mls_module_array_iterator::

void mls_module_array_iterator_init(mls_module_array_iterator *iter, mls_module_array *array)
{
    if (iter == NULL || array == NULL)
    {
        return;
    }
    iter->modules = array->modules;
    iter->i = 0;
    iter->count = array->count;
}

bool mls_module_array_iterator_has_more(mls_module_array_iterator *iter)
{
    if (iter)
    {
        return (iter->i < iter->count);
    }
    return false;
}

mls_module *mls_module_array_iterator_next(mls_module_array_iterator *iter)
{
    if (iter)
    {
        uint i = iter->i;
        iter->i++;
        return iter->modules[i].module;
    }
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
