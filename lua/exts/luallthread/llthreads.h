
#ifndef __LLTHREADS_H_
#define __LLTHREADS_H_

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"



#define REG_PACKAGE_IS_CONSTRUCTOR  0
#define REG_OBJECTS_AS_GLOBALS      0
#define OBJ_DATA_HIDDEN_METATABLE   1
#define LUAJIT_FFI                  0
#define USE_FIELD_GET_SET_METHODS   0


#ifdef _MSC_VER
#define __WINDOWS__
#else
#if defined(_WIN32)
#define __WINDOWS__
#endif
#endif

#ifdef __WINDOWS__

/* for MinGW32 compiler need to include <stdint.h> */
#ifdef __GNUC__
#include <stdint.h>
#else

/* define some standard types missing on Windows. */
#ifndef __INT32_MAX__
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
#endif
#ifndef __INT64_MAX__
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif
typedef int bool;
#ifndef true
#define true 1
#endif
#ifndef false
#define false 1
#endif

#endif

/* wrap strerror_s(). */
#ifdef __GNUC__
#ifndef strerror_r
#define strerror_r(errno, buf, buflen) do { \
strncpy((buf), strerror(errno), (buflen)-1); \
(buf)[(buflen)-1] = '\0'; \
} while(0)
#endif
#else
#ifndef strerror_r
#define strerror_r(errno, buf, buflen) strerror_s((buf), (buflen), (errno))
#endif
#endif

#define FUNC_UNUSED

#define LUA_NOBJ_API __declspec(dllexport)

#else

#define LUA_NOBJ_API LUALIB_API

#include <stdint.h>
#include <stdbool.h>

#define FUNC_UNUSED __attribute__((unused))

#endif

#if defined(__GNUC__) && (__GNUC__ >= 4)
#define assert_obj_type(type, obj) \
assert(__builtin_types_compatible_p(typeof(obj), type *))
#else
#define assert_obj_type(type, obj)
#endif

#ifndef obj_type_free
#define obj_type_free(type, obj) do { \
assert_obj_type(type, obj); \
free((obj)); \
} while(0)
#endif

#ifndef obj_type_new
#define obj_type_new(type, obj) do { \
assert_obj_type(type, obj); \
(obj) = malloc(sizeof(type)); \
} while(0)
#endif

typedef struct obj_type obj_type;

typedef void (*base_caster_t)(void **obj);

typedef void (*dyn_caster_t)(void **obj, obj_type **type);

#define OBJ_TYPE_FLAG_WEAK_REF (1<<0)
#define OBJ_TYPE_SIMPLE (1<<1)
struct obj_type
{
    dyn_caster_t    dcaster;  /**< caster to support casting to sub-objects. */
    int32_t         id;       /**< type's id. */
    uint32_t        flags;    /**< type's flags (weak refs) */
    const char      *name;    /**< type's object name. */
};

typedef struct obj_base
{
    int32_t        id;
    base_caster_t  bcaster;
} obj_base;

typedef enum obj_const_type
{
    CONST_UNKOWN    = 0,
    CONST_BOOLEAN   = 1,
    CONST_NUMBER    = 2,
    CONST_STRING    = 3
} obj_const_type;

typedef struct obj_const
{
    const char      *name;    /**< constant's name. */
    const char      *str;
    double          num;
    obj_const_type  type;
} obj_const;

typedef enum obj_field_type
{
    TYPE_UNKOWN    = 0,
    TYPE_UINT8     = 1,
    TYPE_UINT16    = 2,
    TYPE_UINT32    = 3,
    TYPE_UINT64    = 4,
    TYPE_INT8      = 5,
    TYPE_INT16     = 6,
    TYPE_INT32     = 7,
    TYPE_INT64     = 8,
    TYPE_DOUBLE    = 9,
    TYPE_FLOAT     = 10,
    TYPE_STRING    = 11
} obj_field_type;

typedef struct obj_field
{
    const char      *name;  /**< field's name. */
    uint32_t        offset; /**< offset to field's data. */
    obj_field_type  type;   /**< field's data type. */
    uint32_t        flags;  /**< is_writable:1bit */
} obj_field;

typedef struct reg_sub_module
{
    obj_type        *type;
    int             is_package;
    const luaL_reg  *pub_funcs;
    const luaL_reg  *methods;
    const luaL_reg  *metas;
    const obj_base  *bases;
    const obj_field *fields;
    const obj_const *constants;
} reg_sub_module;

#define OBJ_UDATA_FLAG_OWN (1<<0)
#define OBJ_UDATA_FLAG_LOOKUP (1<<1)
#define OBJ_UDATA_LAST_FLAG (OBJ_UDATA_FLAG_LOOKUP)
typedef struct obj_udata
{
    void     *obj;
    uint32_t flags;  /**< lua_own:1bit */
} obj_udata;

#if LUAJIT_FFI
typedef struct ffi_export_symbol
{
    const char *name;
    void       *sym;
} ffi_export_symbol;
#endif

#ifndef REG_PACKAGE_IS_CONSTRUCTOR
#define REG_PACKAGE_IS_CONSTRUCTOR 1
#endif

#ifndef REG_OBJECTS_AS_GLOBALS
#define REG_OBJECTS_AS_GLOBALS 0
#endif

#ifndef OBJ_DATA_HIDDEN_METATABLE
#define OBJ_DATA_HIDDEN_METATABLE 1
#endif


#ifdef __WINDOWS__
#include <windows.h>
#include <stdio.h>
#include <process.h>
#else
#include <pthread.h>
#include <stdio.h>
#endif

typedef enum
{
    TSTATE_NONE     = 0,
    TSTATE_STARTED  = 1<<0,
    TSTATE_DETACHED = 1<<1,
    TSTATE_JOINED   = 1<<2,
} Lua_TState;

typedef struct Lua_LLThread_child
{
    lua_State  *L;
    int        status;
    int        is_detached;
    int        callback;
} Lua_LLThread_child;

typedef struct Lua_LLThread
{
    Lua_LLThread_child *child;
#ifdef __WINDOWS__
    HANDLE     thread;
#else
    pthread_t  thread;
#endif
    Lua_TState state;
} Lua_LLThread;

typedef struct
{
    lua_State *from_L;
    lua_State *to_L;
    int has_cache;
    int cache_idx;
    int is_arg;
} llthread_copy_state;

#define LLTHREAD_REFID_FUNC_MAPPING "llthread_refid_func_mapping"

#ifdef __WINDOWS__
#define RUN_CHILD_THREAD static void
#else
#define RUN_CHILD_THREAD static void*
#endif


int luaopen_llthreads(lua_State *L);
int llthread_push_results(lua_State *L, Lua_LLThread_child *child, int idx, int top);

#endif // __LLTHREADS_H_
