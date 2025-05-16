// mls_module.h

#ifndef __mls_module_h__
#define __mls_module_h__

#include "mls_api.h"
#include "mls_common.h"
#include "mls_errors.h"

typedef mls_error (*mls_module_life_func)(struct mls_module_t *module);

// mls_module 表示应用程序中的一个模块
typedef struct mls_module_t
{

    char *name;

    struct mls_app_t *app;

    mls_module_life_func on_init;
    mls_module_life_func on_create;
    mls_module_life_func on_start;
    mls_module_life_func on_stop;
    mls_module_life_func on_destroy;

    mls_module_life_func on_run;

} mls_module;

typedef struct mls_module_ref_t
{

    mls_module *module;

} mls_module_ref;

typedef struct mls_module_array_t
{

    uint capacity;
    uint count;
    bool overflow;
    mls_module_ref *modules; // modules[]

} mls_module_array;

////////////////////////////////////////////////////////////////////////////////

void mls_module_array_init(mls_module_array *array);
mls_error mls_module_array_create(mls_module_array *array, uint capacity);
void mls_module_array_release(mls_module_array *array);
void mls_module_array_reset(mls_module_array *array);
void mls_module_array_add(mls_module_array *array, mls_module *item);
bool mls_module_array_is_overflow(mls_module_array *array);

mls_error mls_module_array_invoke_each_init(mls_module_array *array);
mls_error mls_module_array_invoke_each_create(mls_module_array *array);
mls_error mls_module_array_invoke_each_start(mls_module_array *array);
mls_error mls_module_array_invoke_each_run(mls_module_array *array);

#endif // __mls_module_h__
