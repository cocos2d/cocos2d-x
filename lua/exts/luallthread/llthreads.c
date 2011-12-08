
#include "llthreads.h"

// luasocket
#include "luasocket.h"
#include "mime.h"
#include "luasocketscripts.h"

// cjson
#include "lua_cjson.h"


static luaL_Reg luax_exts[] =
{
    {"socket.core", luaopen_socket_core},
    {"mime.core", luaopen_mime_core},
    {"socket", luaopen_socket},
    {"socket.smtp", luaopen_socket_smtp},
    {"socket.http", luaopen_socket_http},
    {"socket.ftp", luaopen_socket_ftp},
    {"socket.tp", luaopen_socket_tp},
    {"socket.url", luaopen_socket_url},
    {"mime", luaopen_socket_mime},
    {"ltn12", luaopen_socket_ltn12},
    {"cjson", luaopen_cjson},
    {NULL, NULL}
};

/* use static pointer as key to weak userdata table. */
static char *obj_udata_weak_ref_key = "obj_udata_weak_ref_key";

#define obj_type_id_Lua_LLThread 0
#define obj_type_Lua_LLThread (obj_types[obj_type_id_Lua_LLThread])

static obj_type obj_types[] =
{
    {NULL, 0, OBJ_TYPE_FLAG_WEAK_REF, "Lua_LLThread"},
    {NULL, -1, 0, NULL},
};


static lua_State* parent_L = 0;


FUNC_UNUSED obj_udata *obj_udata_toobj(lua_State *L, int _index)
{
    obj_udata *ud;
    size_t len;

    /* make sure it's a userdata value. */
    ud = (obj_udata *)lua_touserdata(L, _index);
    if(ud == NULL)
    {
        luaL_typerror(L, _index, "userdata"); /* is not a userdata value. */
    }
    /* verify userdata size. */
    len = lua_objlen(L, _index);
    if(len != sizeof(obj_udata))
    {
        /* This shouldn't be possible */
        luaL_error(L, "invalid userdata size: size=%d, expected=%d", len, sizeof(obj_udata));
    }
    return ud;
}

FUNC_UNUSED int obj_udata_is_compatible(lua_State *L, obj_udata *ud, void **obj, base_caster_t *caster, obj_type *type)
{
    obj_base *base;
    obj_type *ud_type;
    lua_pushlightuserdata(L, type);
    lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
    if(lua_rawequal(L, -1, -2))
    {
        *obj = ud->obj;
        /* same type no casting needed. */
        return 1;
    }
    else
    {
        /* Different types see if we can cast to the required type. */
        lua_rawgeti(L, -2, type->id);
        base = lua_touserdata(L, -1);
        lua_pop(L, 1); /* pop obj_base or nil */
        if(base != NULL)
        {
            *caster = base->bcaster;
            /* get the obj_type for this userdata. */
            lua_pushliteral(L, ".type");
            lua_rawget(L, -3); /* type's metatable. */
            ud_type = lua_touserdata(L, -1);
            lua_pop(L, 1); /* pop obj_type or nil */
            if(base == NULL)
            {
                luaL_error(L, "bad userdata, missing type info.");
                return 0;
            }
            /* check if userdata is a simple object. */
            if(ud_type->flags & OBJ_TYPE_SIMPLE)
            {
                *obj = ud;
            }
            else
            {
                *obj = ud->obj;
            }
            return 1;
        }
    }
    return 0;
}

FUNC_UNUSED obj_udata *obj_udata_luacheck_internal(lua_State *L, int _index, void **obj, obj_type *type, int not_delete)
{
    obj_udata *ud;
    base_caster_t caster = NULL;
    /* make sure it's a userdata value. */
    ud = (obj_udata *)lua_touserdata(L, _index);
    if(ud != NULL)
    {
        /* check object type by comparing metatables. */
        if(lua_getmetatable(L, _index))
        {
            if(obj_udata_is_compatible(L, ud, obj, &(caster), type))
            {
                lua_pop(L, 2); /* pop both metatables. */
                /* apply caster function if needed. */
                if(caster != NULL && *obj != NULL)
                {
                    caster(obj);
                }
                /* check object pointer. */
                if(*obj == NULL)
                {
                    if(not_delete)
                    {
                        luaL_error(L, "null %s", type->name); /* object was garbage collected? */
                    }
                    return NULL;
                }
                return ud;
            }
        }
    }
    if(not_delete)
    {
        luaL_typerror(L, _index, type->name); /* is not a userdata value. */
    }
    return NULL;
}

FUNC_UNUSED void *obj_udata_luacheck(lua_State *L, int _index, obj_type *type)
{
    void *obj = NULL;
    obj_udata_luacheck_internal(L, _index, &(obj), type, 1);
    return obj;
}

FUNC_UNUSED void *obj_udata_luadelete(lua_State *L, int _index, obj_type *type, int *flags)
{
    void *obj;
    obj_udata *ud = obj_udata_luacheck_internal(L, _index, &(obj), type, 0);
    if(ud == NULL) return NULL;
    *flags = ud->flags;
    /* null userdata. */
    ud->obj = NULL;
    ud->flags = 0;
    return obj;
}

FUNC_UNUSED void obj_udata_luapush(lua_State *L, void *obj, obj_type *type, int flags)
{
    obj_udata *ud;
    /* convert NULL's into Lua nil's. */
    if(obj == NULL)
    {
        lua_pushnil(L);
        return;
    }
    /* check for type caster. */
    if(type->dcaster)
    {
        (type->dcaster)(&obj, &type);
    }
    /* create new userdata. */
    ud = (obj_udata *)lua_newuserdata(L, sizeof(obj_udata));
    ud->obj = obj;
    ud->flags = flags;
    /* get obj_type metatable. */
    lua_pushlightuserdata(L, type);
    lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
    lua_setmetatable(L, -2);
}

FUNC_UNUSED void *obj_udata_luadelete_weak(lua_State *L, int _index, obj_type *type, int *flags)
{
    void *obj;
    obj_udata *ud = obj_udata_luacheck_internal(L, _index, &(obj), type, 0);
    if(ud == NULL) return NULL;
    *flags = ud->flags;
    /* null userdata. */
    ud->obj = NULL;
    ud->flags = 0;
    /* get objects weak table. */
    lua_pushlightuserdata(L, obj_udata_weak_ref_key);
    lua_rawget(L, LUA_REGISTRYINDEX); /* weak ref table. */
    /* remove object from weak table. */
    lua_pushlightuserdata(L, obj);
    lua_pushnil(L);
    lua_rawset(L, -3);
    return obj;
}

FUNC_UNUSED void obj_udata_luapush_weak(lua_State *L, void *obj, obj_type *type, int flags)
{
    obj_udata *ud;

    /* convert NULL's into Lua nil's. */
    if(obj == NULL)
    {
        lua_pushnil(L);
        return;
    }
    /* check for type caster. */
    if(type->dcaster)
    {
        (type->dcaster)(&obj, &type);
    }
    /* get objects weak table. */
    lua_pushlightuserdata(L, obj_udata_weak_ref_key);
    lua_rawget(L, LUA_REGISTRYINDEX); /* weak ref table. */
    /* lookup userdata instance from pointer. */
    lua_pushlightuserdata(L, obj);
    lua_rawget(L, -2);
    if(!lua_isnil(L, -1))
    {
        lua_remove(L, -2);     /* remove objects table. */
        return;
    }
    lua_pop(L, 1);  /* pop nil. */

    /* create new userdata. */
    ud = (obj_udata *)lua_newuserdata(L, sizeof(obj_udata));

    /* init. obj_udata. */
    ud->obj = obj;
    ud->flags = flags;
    /* get obj_type metatable. */
    lua_pushlightuserdata(L, type);
    lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
    lua_setmetatable(L, -2);

    /* add weak reference to object. */
    lua_pushlightuserdata(L, obj); /* push object pointer as the 'key' */
    lua_pushvalue(L, -2);          /* push object's udata */
    lua_rawset(L, -4);             /* add weak reference to object. */
    lua_remove(L, -2);     /* remove objects table. */
}

/* default object equal method. */
FUNC_UNUSED int obj_udata_default_equal(lua_State *L)
{
    obj_udata *ud1 = obj_udata_toobj(L, 1);
    obj_udata *ud2 = obj_udata_toobj(L, 2);

    lua_pushboolean(L, (ud1->obj == ud2->obj));
    return 1;
}

/* default object tostring method. */
FUNC_UNUSED int obj_udata_default_tostring(lua_State *L)
{
    obj_udata *ud = obj_udata_toobj(L, 1);

    /* get object's metatable. */
    lua_getmetatable(L, 1);
    lua_remove(L, 1); /* remove userdata. */
    /* get the object's name from the metatable */
    lua_getfield(L, 1, ".name");
    lua_remove(L, 1); /* remove metatable */
    /* push object's pointer */
    lua_pushfstring(L, ": %p, flags=%d", ud->obj, ud->flags);
    lua_concat(L, 2);

    return 1;
}

/*
 * Simple userdata objects.
 */
FUNC_UNUSED void *obj_simple_udata_toobj(lua_State *L, int _index)
{
    void *ud;

    /* make sure it's a userdata value. */
    ud = lua_touserdata(L, _index);
    if(ud == NULL)
    {
        luaL_typerror(L, _index, "userdata"); /* is not a userdata value. */
    }
    return ud;
}

FUNC_UNUSED void * obj_simple_udata_luacheck(lua_State *L, int _index, obj_type *type)
{
    void *ud;
    /* make sure it's a userdata value. */
    ud = lua_touserdata(L, _index);
    if(ud != NULL)
    {
        /* check object type by comparing metatables. */
        if(lua_getmetatable(L, _index))
        {
            lua_pushlightuserdata(L, type);
            lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
            if(lua_rawequal(L, -1, -2))
            {
                lua_pop(L, 2); /* pop both metatables. */
                return ud;
            }
        }
    }
    luaL_typerror(L, _index, type->name); /* is not a userdata value. */
    return NULL;
}

FUNC_UNUSED void * obj_simple_udata_luadelete(lua_State *L, int _index, obj_type *type, int *flags)
{
    void *obj;
    obj = obj_simple_udata_luacheck(L, _index, type);
    *flags = OBJ_UDATA_FLAG_OWN;
    /* clear the metatable to invalidate userdata. */
    lua_pushnil(L);
    lua_setmetatable(L, _index);
    return obj;
}

FUNC_UNUSED void *obj_simple_udata_luapush(lua_State *L, void *obj, int size, obj_type *type)
{
    /* create new userdata. */
    void *ud = lua_newuserdata(L, size);
    memcpy(ud, obj, size);
    /* get obj_type metatable. */
    lua_pushlightuserdata(L, type);
    lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
    lua_setmetatable(L, -2);

    return ud;
}

/* default simple object equal method. */
FUNC_UNUSED int obj_simple_udata_default_equal(lua_State *L)
{
    void *ud1 = obj_simple_udata_toobj(L, 1);
    size_t len1 = lua_objlen(L, 1);
    void *ud2 = obj_simple_udata_toobj(L, 2);
    size_t len2 = lua_objlen(L, 2);

    if(len1 == len2)
    {
        lua_pushboolean(L, (memcmp(ud1, ud2, len1) == 0));
    }
    else
    {
        lua_pushboolean(L, 0);
    }
    return 1;
}

/* default simple object tostring method. */
FUNC_UNUSED int obj_simple_udata_default_tostring(lua_State *L)
{
    void *ud = obj_simple_udata_toobj(L, 1);

    /* get object's metatable. */
    lua_getmetatable(L, 1);
    lua_remove(L, 1); /* remove userdata. */
    /* get the object's name from the metatable */
    lua_getfield(L, 1, ".name");
    lua_remove(L, 1); /* remove metatable */
    /* push object's pointer */
    lua_pushfstring(L, ": %p", ud);
    lua_concat(L, 2);

    return 1;
}

int obj_constructor_call_wrapper(lua_State *L)
{
    /* replace '__call' table with constructor function. */
    lua_pushvalue(L, lua_upvalueindex(1));
    lua_replace(L, 1);

    /* call constructor function with all parameters after the '__call' table. */
    lua_call(L, lua_gettop(L) - 1, LUA_MULTRET);
    /* return all results from constructor. */
    return lua_gettop(L);
}

void obj_type_register_constants(lua_State *L, const obj_const *constants, int tab_idx)
{
    /* register constants. */
    while(constants->name != NULL)
    {
        lua_pushstring(L, constants->name);
        switch(constants->type)
        {
        case CONST_BOOLEAN:
            lua_pushboolean(L, constants->num != 0.0);
            break;
        case CONST_NUMBER:
            lua_pushnumber(L, constants->num);
            break;
        case CONST_STRING:
            lua_pushstring(L, constants->str);
            break;
        default:
            lua_pushnil(L);
            break;
        }
        lua_rawset(L, tab_idx - 2);
        constants++;
    }
}

void obj_type_register_package(lua_State *L, const reg_sub_module *type_reg)
{
    const luaL_reg *reg_list = type_reg->pub_funcs;

    /* create public functions table. */
    if(reg_list != NULL && reg_list[0].name != NULL)
    {
        /* register functions */
        luaL_register(L, NULL, reg_list);
    }

    obj_type_register_constants(L, type_reg->constants, -1);

    lua_pop(L, 1);  /* drop package table */
}

void obj_type_register(lua_State *L, const reg_sub_module *type_reg, int priv_table)
{
    const luaL_reg *reg_list;
    obj_type *type = type_reg->type;
    const obj_base *base = type_reg->bases;

    if(type_reg->is_package == 1)
    {
        obj_type_register_package(L, type_reg);
        return;
    }

    /* create public functions table. */
    reg_list = type_reg->pub_funcs;
    if(reg_list != NULL && reg_list[0].name != NULL)
    {
        /* register "constructors" as to object's public API */
        luaL_register(L, NULL, reg_list); /* fill public API table. */

        /* make public API table callable as the default constructor. */
        lua_newtable(L); /* create metatable */
        lua_pushliteral(L, "__call");
        lua_pushcfunction(L, reg_list[0].func); /* push first constructor function. */
        lua_pushcclosure(L, obj_constructor_call_wrapper, 1); /* make __call wrapper. */
        lua_rawset(L, -3);         /* metatable.__call = <default constructor> */

#if OBJ_DATA_HIDDEN_METATABLE
        lua_pushliteral(L, "__metatable");
        lua_pushboolean(L, 0);
        lua_rawset(L, -3);         /* metatable.__metatable = false */
#endif

        /* setmetatable on public API table. */
        lua_setmetatable(L, -2);

        lua_pop(L, 1); /* pop public API table, don't need it any more. */
        /* create methods table. */
        lua_newtable(L);
    }
    else
    {
        /* register all methods as public functions. */
#if OBJ_DATA_HIDDEN_METATABLE
        lua_pop(L, 1); /* pop public API table, don't need it any more. */
        /* create methods table. */
        lua_newtable(L);
#endif
    }

    luaL_register(L, NULL, type_reg->methods); /* fill methods table. */

    luaL_newmetatable(L, type->name); /* create metatable */
    lua_pushliteral(L, ".name");
    lua_pushstring(L, type->name);
    lua_rawset(L, -3);    /* metatable['.name'] = "<object_name>" */
    lua_pushliteral(L, ".type");
    lua_pushlightuserdata(L, type);
    lua_rawset(L, -3);    /* metatable['.type'] = lightuserdata -> obj_type */
    lua_pushlightuserdata(L, type);
    lua_pushvalue(L, -2); /* dup metatable. */
    lua_rawset(L, LUA_REGISTRYINDEX);    /* REGISTRY[type] = metatable */

#if LUAJIT_FFI
    /* add metatable to 'priv_table' */
    lua_pushstring(L, type->name);
    lua_pushvalue(L, -2); /* dup metatable. */
    lua_rawset(L, priv_table);    /* priv_table["<object_name>"] = metatable */
#else
    (void)priv_table;
#endif

    luaL_register(L, NULL, type_reg->metas); /* fill metatable */

    /* add obj_bases to metatable. */
    while(base->id >= 0)
    {
        lua_pushlightuserdata(L, (void *)base);
        lua_rawseti(L, -2, base->id);
        base++;
    }

    obj_type_register_constants(L, type_reg->constants, -2);

    lua_pushliteral(L, "__index");
    lua_pushvalue(L, -3);               /* dup methods table */
    lua_rawset(L, -3);                  /* metatable.__index = methods */
#if OBJ_DATA_HIDDEN_METATABLE
    lua_pushliteral(L, "__metatable");
    lua_pushboolean(L, 0);
    lua_rawset(L, -3);                  /* hide metatable:
                                         metatable.__metatable = false */
#endif
    lua_pop(L, 2);                      /* drop metatable & methods */
}

FUNC_UNUSED int lua_checktype_ref(lua_State *L, int _index, int _type)
{
    luaL_checktype(L,_index,_type);
    lua_pushvalue(L,_index);
    return luaL_ref(L, LUA_REGISTRYINDEX);
}

#if LUAJIT_FFI
int nobj_udata_new_ffi(lua_State *L)
{
    size_t size = luaL_checkinteger(L, 1);
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_settop(L, 2);
    /* create userdata. */
    lua_newuserdata(L, size);
    lua_replace(L, 1);
    /* set userdata's metatable. */
    lua_setmetatable(L, 1);
    return 1;
}

int nobj_try_loading_ffi(lua_State *L, const char *ffi_mod_name,
                         const char *ffi_init_code, const ffi_export_symbol *ffi_exports, int priv_table)
{
    int err;

    /* export symbols to priv_table. */
    while(ffi_exports->name != NULL)
    {
        lua_pushstring(L, ffi_exports->name);
        lua_pushlightuserdata(L, ffi_exports->sym);
        lua_settable(L, priv_table);
        ffi_exports++;
    }
    err = luaL_loadbuffer(L, ffi_init_code, strlen(ffi_init_code), ffi_mod_name);
    if(0 == err)
    {
        lua_pushvalue(L, -2); /* dup C module's table. */
        lua_pushvalue(L, priv_table); /* move priv_table to top of stack. */
        lua_remove(L, priv_table);
        lua_pushcfunction(L, nobj_udata_new_ffi);
        err = lua_pcall(L, 3, 0, 0);
    }
    if(err)
    {
        const char *msg = "<err not a string>";
        if(lua_isstring(L, -1))
        {
            msg = lua_tostring(L, -1);
        }
        printf("Failed to install FFI-based bindings: %s\n", msg);
        lua_pop(L, 1); /* pop error message. */
    }
    return err;
}
#endif


#define obj_type_Lua_LLThread_check(L, _index) \
obj_udata_luacheck(L, _index, &(obj_type_Lua_LLThread))
#define obj_type_Lua_LLThread_delete(L, _index, flags) \
obj_udata_luadelete_weak(L, _index, &(obj_type_Lua_LLThread), flags)
#define obj_type_Lua_LLThread_push(L, obj, flags) \
obj_udata_luapush_weak(L, (void *)obj, &(obj_type_Lua_LLThread), flags)

/* maximum recursive depth of table copies. */
#define MAX_COPY_DEPTH 30

#define ERROR_LEN 1024

/******************************************************************************
 * traceback() function from Lua 5.1.x source.
 * Copyright (C) 1994-2008 Lua.org, PUC-Rio.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 ******************************************************************************/
int traceback (lua_State *L)
{
    if (!lua_isstring(L, 1))  /* 'message' not a string? */
        return 1;  /* keep it intact */
    lua_getfield(L, LUA_GLOBALSINDEX, "debug");
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 1);
        return 1;
    }
    lua_getfield(L, -1, "traceback");
    if (!lua_isfunction(L, -1))
    {
        lua_pop(L, 2);
        return 1;
    }
    lua_pushvalue(L, 1);  /* pass error message */
    lua_pushinteger(L, 2);  /* skip this function and traceback */
    lua_call(L, 2, 1);  /* call debug.traceback */
    return 1;
}


Lua_LLThread_child *llthread_child_new()
{
    Lua_LLThread_child *this;

    this = (Lua_LLThread_child *)calloc(1, sizeof(Lua_LLThread_child));
    /* create new lua_State for the thread. */
    this->L = luaL_newstate();
    /* open standard libraries. */
    luaL_openlibs(this->L);

    /* load modules */
    luaL_Reg* lib = luax_exts;
    luaL_findtable(this->L, LUA_GLOBALSINDEX, "package.preload", sizeof(luax_exts)/sizeof(luax_exts[0])-1);
    for (; lib->func; lib++)
    {
        lua_pushstring(this->L, lib->name);
        lua_pushcfunction(this->L, lib->func);
        lua_rawset(this->L, -3);
    }
    lua_pop(this->L, 1);

    /* push traceback function as first value on stack. */
    lua_pushcfunction(this->L, traceback);

    return this;
}

void llthread_child_destroy(Lua_LLThread_child *this)
{
    lua_close(this->L);
    free(this);
}

Lua_LLThread *llthread_new()
{
    Lua_LLThread *this;

    this = (Lua_LLThread *)calloc(1, sizeof(Lua_LLThread));
    this->state = TSTATE_NONE;
    this->child = llthread_child_new();

    return this;
}

void llthread_destroy(Lua_LLThread *this)
{
    /* We still own the child thread object iff the thread was not started or
     * we have joined the thread.
     */
    if((this->state & TSTATE_JOINED) == TSTATE_JOINED || this->state == TSTATE_NONE)
    {
        if(this->child) llthread_child_destroy(this->child);
        this->child = NULL;
    }
    free(this);
}

RUN_CHILD_THREAD run_child_thread(void *arg)
{
    Lua_LLThread_child *this = (Lua_LLThread_child *)arg;
    lua_State *L = this->L;
    int nargs = lua_gettop(L) - 2;

    this->status = lua_pcall(L, nargs, LUA_MULTRET, 1);
    
    /* alwasy print errors here, helps with debugging bad code. */
    if(this->status != 0)
    {
        const char *err_msg = lua_tostring(L, -1);
        fprintf(stderr, "Error from thread: %s\n", err_msg);
        fflush(stderr);
    }
    
    if (this->callback)
    {
        lua_pushstring(parent_L, LLTHREAD_REFID_FUNC_MAPPING);
        lua_rawget(parent_L, LUA_REGISTRYINDEX);                        /* stack: refid_func */
        lua_pushinteger(parent_L, this->callback);                      /* stack: refid_func refid */
        lua_rawget(parent_L, -2);                                       /* stack: refid_func func */
        
//        printf("---- parent_L stackDump ----\n");
//        tolua_stack_dump(parent_L);
//        printf("---- child->L stackDump ----\n");
//        tolua_stack_dump(this->L);
//        
        if (!lua_isfunction(parent_L, -1))
        {
            printf("[LLTHREAD ERROR] callback refid '%d' does not reference a Lua function", this->callback);
            lua_pop(parent_L, 2);
        }
        else
        {
            int top = lua_gettop(this->L);
            nargs = llthread_push_results(parent_L, this, 2, top);      /* stack: refid_func func ... */
            lua_pcall(parent_L, nargs, 0, 0);                           /* stack: refid_func */
            
            lua_pushinteger(parent_L, this->callback);                  /* stack: refid_func refid */
            lua_pushnil(parent_L);                                      /* stack: refid_func refid nil */
            lua_rawget(parent_L, -2);         /* delete refid_func[refid], stack: refid_func */
            lua_pop(parent_L, 1);                                       /* stack: - */
        }
    }

    /* if thread is detached, then destroy the child state. */
    if(this->is_detached != 0)
    {
        /* thread is detached, so it must clean-up the child state. */
        llthread_child_destroy(this);
        this = NULL;
    }
#ifdef __WINDOWS__
    if(this)
    {
        /* attached thread, don't close thread handle. */
        _endthreadex(0);
    }
    else
    {
        /* detached thread, close thread handle. */
        _endthread();
    }
#else
    return this;
#endif
}

int llthread_start(Lua_LLThread *this, int start_detached)
{
    Lua_LLThread_child *child;
    int rc = 0;

    child = this->child;
    child->is_detached = start_detached;
#ifdef __WINDOWS__
    this->thread = (HANDLE)_beginthread(run_child_thread, 0, child);
    if(this->thread != (HANDLE)-1L)
    {
        this->state = TSTATE_STARTED;
        if(start_detached)
        {
            this->state |= TSTATE_DETACHED;
        }
    }
#else
    rc = pthread_create(&(this->thread), NULL, run_child_thread, child);
    if(rc == 0)
    {
        this->state = TSTATE_STARTED;
        if(start_detached)
        {
            this->state |= TSTATE_DETACHED;
            rc = pthread_detach(this->thread);
        }
    }
#endif
    return rc;
}

int llthread_join(Lua_LLThread *this)
{
#ifdef __WINDOWS__
    WaitForSingleObject( this->thread, INFINITE );
    /* Destroy the thread object. */
    CloseHandle( this->thread );

    return 0;
#else
    Lua_LLThread_child *child;
    int rc;

    /* then join the thread. */
    rc = pthread_join(this->thread, (void **)&(child));
    if(rc == 0)
    {
        this->state |= TSTATE_JOINED;
        /* if the child thread returns NULL, then it freed the child object. */
        this->child = child;
    }
    return rc;
#endif
}

int llthread_copy_table_from_cache(llthread_copy_state *state, int idx)
{
    void *ptr;

    /* convert table to pointer for lookup in cache. */
    ptr = (void *)lua_topointer(state->from_L, idx);
    if(ptr == NULL) return 0; /* can't convert to pointer. */

    /* check if we need to create the cache. */
    if(!state->has_cache)
    {
        lua_newtable(state->to_L);
        lua_replace(state->to_L, state->cache_idx);
        state->has_cache = 1;
    }

    lua_pushlightuserdata(state->to_L, ptr);
    lua_rawget(state->to_L, state->cache_idx);
    if(lua_isnil(state->to_L, -1))
    {
        /* not in cache. */
        lua_pop(state->to_L, 1);
        /* create new table and add to cache. */
        lua_newtable(state->to_L);
        lua_pushlightuserdata(state->to_L, ptr);
        lua_pushvalue(state->to_L, -2);
        lua_rawset(state->to_L, state->cache_idx);
        return 0;
    }
    /* found table in cache. */
    return 1;
}

int llthread_copy_value(llthread_copy_state *state, int depth, int idx)
{
    const char *str;
    size_t str_len;
    int kv_pos;

    /* Maximum recursive depth */
    if(++depth > MAX_COPY_DEPTH)
    {
        return luaL_error(state->from_L, "Hit maximum copy depth (%d > %d).", depth, MAX_COPY_DEPTH);
    }

    /* only support string/number/boolean/nil/table/lightuserdata. */
    switch(lua_type(state->from_L, idx))
    {
    case LUA_TNIL:
        lua_pushnil(state->to_L);
        break;
    case LUA_TNUMBER:
        lua_pushnumber(state->to_L, lua_tonumber(state->from_L, idx));
        break;
    case LUA_TBOOLEAN:
        lua_pushboolean(state->to_L, lua_toboolean(state->from_L, idx));
        break;
    case LUA_TSTRING:
        str = lua_tolstring(state->from_L, idx, &(str_len));
        lua_pushlstring(state->to_L, str, str_len);
        break;
    case LUA_TLIGHTUSERDATA:
        lua_pushlightuserdata(state->to_L, lua_touserdata(state->from_L, idx));
        break;
    case LUA_TTABLE:
        /* make sure there is room on the new state for 3 values (table,key,value) */
        if(!lua_checkstack(state->to_L, 3))
        {
            return luaL_error(state->from_L, "To stack overflow!");
        }
        /* make room on from stack for key/value pairs. */
        luaL_checkstack(state->from_L, 2, "From stack overflow!");

        /* check cache for table. */
        if(llthread_copy_table_from_cache(state, idx))
        {
            /* found in cache don't need to copy table. */
            break;
        }
        lua_pushnil(state->from_L);
        while (lua_next(state->from_L, idx) != 0)
        {
            /* key is at (top - 1), value at (top), but we need to normalize these
             * to positive indices */
            kv_pos = lua_gettop(state->from_L);
            /* copy key */
            llthread_copy_value(state, depth, kv_pos - 1);
            /* copy value */
            llthread_copy_value(state, depth, kv_pos);
            /* Copied key and value are now at -2 and -1 in state->to_L. */
            lua_settable(state->to_L, -3);
            /* Pop value for next iteration */
            lua_pop(state->from_L, 1);
        }
        break;
    case LUA_TFUNCTION:
    case LUA_TUSERDATA:
    case LUA_TTHREAD:
    default:
        if (state->is_arg)
        {
            return luaL_argerror(state->from_L, idx, "function/userdata/thread types un-supported.");
        }
        else
        {
            /* convert un-supported types to an error string. */
            lua_pushfstring(state->to_L, "Un-supported value: %s: %p",
                            lua_typename(state->from_L, lua_type(state->from_L, idx)), lua_topointer(state->from_L, idx));
        }
    }

    return 1;
}

int llthread_copy_values(lua_State *from_L, lua_State *to_L, int idx, int top, int is_arg)
{
    llthread_copy_state state;
    int nvalues = 0;
    int n;

    nvalues = (top - idx) + 1;
    /* make sure there is room on the new state for the values. */
    if(!lua_checkstack(to_L, nvalues + 1))
    {
        return luaL_error(from_L, "To stack overflow!");
    }

    /* setup copy state. */
    state.from_L = from_L;
    state.to_L = to_L;
    state.is_arg = is_arg;
    state.has_cache = 0; /* don't create cache table unless it is needed. */
    lua_pushnil(to_L);
    state.cache_idx = lua_gettop(to_L);

    nvalues = 0;
    for(n = idx; n <= top; n++)
    {
        llthread_copy_value(&state, 0, n);
        ++nvalues;
    }

    /* remove cache table. */
    lua_remove(to_L, state.cache_idx);

    return nvalues;
}

int llthread_push_args(lua_State *L, Lua_LLThread_child *child, int idx, int top)
{
    return llthread_copy_values(L, child->L, idx, top, 1 /* is_arg */);
}

int llthread_push_results(lua_State *L, Lua_LLThread_child *child, int idx, int top)
{
    return llthread_copy_values(child->L, L, idx, top, 0 /* is_arg */);
}

Lua_LLThread *llthread_create(lua_State *L, const char *code, size_t code_len, int callbackFunctionRefID)
{
    Lua_LLThread *this;
    Lua_LLThread_child *child;
    const char *str;
    size_t str_len;
    int rc;
    int top;

    this = llthread_new();
    child = this->child;
    child->callback = callbackFunctionRefID;
    /* load Lua code into child state. */
    rc = luaL_loadbuffer(child->L, code, code_len, code);
    if(rc != 0)
    {
        /* copy error message to parent state. */
        str = lua_tolstring(child->L, -1, &(str_len));
        if(str != NULL)
        {
            lua_pushlstring(L, str, str_len);
        }
        else
        {
            /* non-string error message. */
            lua_pushfstring(L, "luaL_loadbuffer() failed to load Lua code: rc=%d", rc);
        }
        llthread_destroy(this);
        lua_error(L);
        return NULL;
    }
    /* copy extra args from main state to child state. */
    top = lua_gettop(L);
    /* Push all args after the Lua code. */
    llthread_push_args(L, child, 2, top);

    return this;
}

/* method: delete */
int Lua_LLThread__delete__meth(lua_State *L)
{
    int this_flags_idx1 = 0;
    Lua_LLThread * this_idx1 = obj_type_Lua_LLThread_delete(L,1,&(this_flags_idx1));
    Lua_LLThread_child *child;

    if(!(this_flags_idx1 & OBJ_UDATA_FLAG_OWN))
    {
        return 0;
    }
    /* if the thread has been started and has not been detached/joined. */
    if((this_idx1->state & TSTATE_STARTED) == TSTATE_STARTED &&
            (this_idx1->state & (TSTATE_DETACHED|TSTATE_JOINED)) == 0)
    {
        /* then join the thread. */
        llthread_join(this_idx1);
        child = this_idx1->child;
        if(child && child->status != 0)
        {
            const char *err_msg = lua_tostring(child->L, -1);
            fprintf(stderr, "Error from non-joined thread: %s\n", err_msg);
            fflush(stderr);
        }
    }
    llthread_destroy(this_idx1);

    return 0;
}

/* method: start */
int Lua_LLThread__start__meth(lua_State *L)
{
    Lua_LLThread * this_idx1 = obj_type_Lua_LLThread_check(L,1);
    bool start_detached_idx2 = lua_toboolean(L,2);
    bool res_idx1 = 0;
    char buf[ERROR_LEN];
    int rc;

    if(this_idx1->state != TSTATE_NONE)
    {
        lua_pushboolean(L, 0); /* false */
        lua_pushliteral(L, "Thread already started.");
        return 2;
    }
    if((rc = llthread_start(this_idx1, start_detached_idx2)) != 0)
    {
        lua_pushboolean(L, 0); /* false */
        strerror_r(errno, buf, ERROR_LEN);
        lua_pushstring(L, buf);
        return 2;
    }
    res_idx1 = true;

    lua_pushboolean(L, res_idx1);
    return 1;
}

/* method: join */
int Lua_LLThread__join__meth(lua_State *L)
{
    Lua_LLThread * this_idx1 = obj_type_Lua_LLThread_check(L,1);
    bool res_idx1 = 0;
    const char * err_msg_idx2 = NULL;
    Lua_LLThread_child *child;
    char buf[ERROR_LEN];
    int top;
    int rc;

    if((this_idx1->state & TSTATE_STARTED) == 0)
    {
        lua_pushboolean(L, 0); /* false */
        lua_pushliteral(L, "Can't join a thread that hasn't be started.");
        return 2;
    }
    if((this_idx1->state & TSTATE_DETACHED) == TSTATE_DETACHED)
    {
        lua_pushboolean(L, 0); /* false */
        lua_pushliteral(L, "Can't join a thread that has been detached.");
        return 2;
    }
    if((this_idx1->state & TSTATE_JOINED) == TSTATE_JOINED)
    {
        lua_pushboolean(L, 0); /* false */
        lua_pushliteral(L, "Can't join a thread that has already been joined.");
        return 2;
    }
    /* join the thread. */
    rc = llthread_join(this_idx1);
    child = this_idx1->child;

    /* Push all results after the Lua code. */
    if(rc == 0 && child)
    {
        if(child->status != 0)
        {
            const char *err_msg = lua_tostring(child->L, -1);
            lua_pushboolean(L, 0);
            lua_pushfstring(L, "Error from child thread: %s", err_msg);
            return 2;
        }
        else
        {
            lua_pushboolean(L, 1);
        }
        top = lua_gettop(child->L);
        /* return results to parent thread. */
        llthread_push_results(L, child, 2, top);
        return top;
    }
    else
    {
        res_idx1 = false;
        err_msg_idx2 = buf;
        strerror_r(errno, buf, ERROR_LEN);
    }

    lua_pushboolean(L, res_idx1);
    lua_pushstring(L, err_msg_idx2);
    return 2;
}

/* method: new */
int llthreads__new__func(lua_State *L)
{
    static int functionRefIDCount = 0;
    ++functionRefIDCount;

    size_t lua_code_len_idx1;
    const char * lua_code_idx1 = luaL_checklstring(L,1,&(lua_code_len_idx1));
    
    int callback = 0;
    if (lua_isfunction(L, 2))
    {
        /* reference to callback function */
        lua_pushstring(L, LLTHREAD_REFID_FUNC_MAPPING);
        lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: code callback ... refid_func */
        lua_pushinteger(L, functionRefIDCount);                     /* stack: code callback ... refid_func refid */
        lua_pushvalue(L, 2);                                        /* stack: code callback ... refid_func refid callback */
        lua_rawset(L, -3);                /* refid_func[refid] = func, stack: code callback ... refid_func */
        lua_pop(L, 1);                                              /* stack: code callback ... */
        lua_remove(L, 2);                                           /* stack: code ... */
        callback = functionRefIDCount;
    }
    
    int this_flags_idx1 = OBJ_UDATA_FLAG_OWN;
    Lua_LLThread * this_idx1;
    this_idx1 = llthread_create(L, lua_code_idx1, lua_code_len_idx1, callback);

    obj_type_Lua_LLThread_push(L, this_idx1, this_flags_idx1);
    return 1;
}

static const luaL_reg obj_Lua_LLThread_pub_funcs[] =
{
    {NULL, NULL}
};

static const luaL_reg obj_Lua_LLThread_methods[] =
{
    {"start", Lua_LLThread__start__meth},
    {"join", Lua_LLThread__join__meth},
    {NULL, NULL}
};

static const luaL_reg obj_Lua_LLThread_metas[] =
{
    {"__gc", Lua_LLThread__delete__meth},
    {"__tostring", obj_udata_default_tostring},
    {"__eq", obj_udata_default_equal},
    {NULL, NULL}
};

static const obj_base obj_Lua_LLThread_bases[] =
{
    {-1, NULL}
};

static const obj_field obj_Lua_LLThread_fields[] =
{
    {NULL, 0, 0, 0}
};

static const obj_const obj_Lua_LLThread_constants[] =
{
    {NULL, NULL, 0.0 , 0}
};

static const luaL_reg llthreads_function[] =
{
    {"new", llthreads__new__func},
    {NULL, NULL}
};

static const obj_const llthreads_constants[] =
{
    {NULL, NULL, 0.0 , 0}
};


static const reg_sub_module reg_sub_modules[] =
{
    { &(obj_type_Lua_LLThread), 0, obj_Lua_LLThread_pub_funcs, obj_Lua_LLThread_methods, obj_Lua_LLThread_metas, obj_Lua_LLThread_bases, obj_Lua_LLThread_fields, obj_Lua_LLThread_constants},
    {NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL}
};

static const luaL_Reg submodule_libs[] =
{
    {NULL, NULL}
};



static void create_object_instance_cache(lua_State *L)
{
    lua_pushlightuserdata(L, obj_udata_weak_ref_key); /* key for weak table. */
    lua_rawget(L, LUA_REGISTRYINDEX);  /* check if weak table exists already. */
    if(!lua_isnil(L, -1))
    {
        lua_pop(L, 1); /* pop weak table. */
        return;
    }
    lua_pop(L, 1); /* pop nil. */
    /* create weak table for object instance references. */
    lua_pushlightuserdata(L, obj_udata_weak_ref_key); /* key for weak table. */
    lua_newtable(L);               /* weak table. */
    lua_newtable(L);               /* metatable for weak table. */
    lua_pushliteral(L, "__mode");
    lua_pushliteral(L, "v");
    lua_rawset(L, -3);             /* metatable.__mode = 'v'  weak values. */
    lua_setmetatable(L, -2);       /* add metatable to weak table. */
    lua_rawset(L, LUA_REGISTRYINDEX);  /* create reference to weak table. */
}

int luaopen_llthreads(lua_State *L)
{
    parent_L = L;
    const reg_sub_module *reg = reg_sub_modules;
    const luaL_Reg *submodules = submodule_libs;
    int priv_table = -1;
    
    /* reference to callback function */
    lua_pushstring(L, LLTHREAD_REFID_FUNC_MAPPING);
    lua_newtable(L);
    lua_rawset(L, LUA_REGISTRYINDEX);

#if LUAJIT_FFI
    /* private table to hold reference to object metatables. */
    lua_newtable(L);
    priv_table = lua_gettop(L);
#endif

    /* create object cache. */
    create_object_instance_cache(L);

    /* module table. */
    luaL_register(L, "llthreads", llthreads_function);

    /* register module constants. */
    obj_type_register_constants(L, llthreads_constants, -1);

    for(; submodules->func != NULL ; submodules++)
    {
        lua_pushcfunction(L, submodules->func);
        lua_pushstring(L, submodules->name);
        lua_call(L, 1, 0);
    }

    /* register objects */
    for(; reg->type != NULL ; reg++)
    {
        lua_newtable(L); /* create public API table for object. */
        lua_pushvalue(L, -1); /* dup. object's public API table. */
        lua_setfield(L, -3, reg->type->name); /* module["<object_name>"] = <object public API> */
#if REG_OBJECTS_AS_GLOBALS
        lua_pushvalue(L, -1);                 /* dup value. */
        lua_setglobal(L, reg->type->name);    /* global: <object_name> = <object public API> */
#endif
        obj_type_register(L, reg, priv_table);
    }

#if LUAJIT_FFI
    nobj_try_loading_ffi(L, "llthreads", llthreads_ffi_lua_code,
                         llthreads_ffi_export, priv_table);
#endif
    return 1;
}
