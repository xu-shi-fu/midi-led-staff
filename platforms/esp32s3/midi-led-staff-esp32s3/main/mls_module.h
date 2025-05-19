// mls_module.h

#ifndef __mls_module_h__
#define __mls_module_h__

#include "mls_api.h"
#include "mls_common_mls.h"
#include "mls_errors.h"

////////////////////////////////////////////////////////////////////////////////
// fn_ptr

typedef mls_error (*mls_module_life_func)(struct mls_module_t *module);

////////////////////////////////////////////////////////////////////////////////
// enum

typedef enum mls_lifecycle_phase_t
{

    MLS_LIFECYCLE_PHASE_INIT,
    MLS_LIFECYCLE_PHASE_CREATE,
    MLS_LIFECYCLE_PHASE_START,
    MLS_LIFECYCLE_PHASE_RESUME,
    MLS_LIFECYCLE_PHASE_RUN,
    MLS_LIFECYCLE_PHASE_PAUSE,
    MLS_LIFECYCLE_PHASE_STOP,
    MLS_LIFECYCLE_PHASE_DESTROY,

} mls_lifecycle_phase;

////////////////////////////////////////////////////////////////////////////////
// struct

// mls_module 表示应用程序中的一个模块
typedef struct mls_module_t
{

    const char *name;

    struct mls_app_t *app;

    void *inner; // 指向模块的内部结构, 具体类型由各个模块决定

    bool enabled; // 启用|禁用此模块

    mls_module_life_func on_init;
    mls_module_life_func on_create;
    mls_module_life_func on_destroy;
    mls_module_life_func on_start;
    mls_module_life_func on_stop;
    mls_module_life_func on_pause;
    mls_module_life_func on_resume;
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

typedef struct
{
    uint i;
    uint count;
    mls_module_ref *modules; // modules[]

} mls_module_array_iterator;

////////////////////////////////////////////////////////////////////////////////

void mls_module_array_init(mls_module_array *array);
mls_error mls_module_array_create(mls_module_array *array, uint capacity);
void mls_module_array_release(mls_module_array *array);
void mls_module_array_reset(mls_module_array *array);
void mls_module_array_add(mls_module_array *array, mls_module *item);
bool mls_module_array_is_overflow(mls_module_array *array);

// mls_error mls_module_array_invoke_each_init(mls_module_array *array);
// mls_error mls_module_array_invoke_each_create(mls_module_array *array);
// mls_error mls_module_array_invoke_each_start(mls_module_array *array);
// mls_error mls_module_array_invoke_each_run(mls_module_array *array);
mls_error mls_module_array_invoke_lifecycle_fn(mls_module_array *array, mls_lifecycle_phase phase);

void mls_module_array_iterator_init(mls_module_array_iterator *iter, mls_module_array *array);
bool mls_module_array_iterator_has_more(mls_module_array_iterator *iter);
mls_module *mls_module_array_iterator_next(mls_module_array_iterator *iter);

#endif // __mls_module_h__
