
#include "mls_module.h"

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

mls_error mls_module_array_invoke_each_init(mls_module_array *array)
{
    return mls_errors_make(500, "no impl");
}

mls_error mls_module_array_invoke_each_create(mls_module_array *array)
{
    return mls_errors_make(500, "no impl");
}

mls_error mls_module_array_invoke_each_start(mls_module_array *array)
{
    return mls_errors_make(500, "no impl");
}

mls_error mls_module_array_invoke_each_run(mls_module_array *array)
{
    return mls_errors_make(500, "no impl");
}
