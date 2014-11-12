/************************************************************************
* lsqlite3                                                              *
* Copyright (C) 2002-2013 Tiago Dionizio, Doug Currie                   *
* All rights reserved.                                                  *
* Author    : Tiago Dionizio <tiago.dionizio@ist.utl.pt>                *
* Author    : Doug Currie <doug.currie@alum.mit.edu>                    *
* Library   : lsqlite3 - a SQLite 3 database binding for Lua 5          *
*                                                                       *
* Permission is hereby granted, free of charge, to any person obtaining *
* a copy of this software and associated documentation files (the       *
* "Software"), to deal in the Software without restriction, including   *
* without limitation the rights to use, copy, modify, merge, publish,   *
* distribute, sublicense, and/or sell copies of the Software, and to    *
* permit persons to whom the Software is furnished to do so, subject to *
* the following conditions:                                             *
*                                                                       *
* The above copyright notice and this permission notice shall be        *
* included in all copies or substantial portions of the Software.       *
*                                                                       *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       *
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    *
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  *
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  *
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     *
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                *
************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define LUA_LIB
#include "lua.h"
#include "lauxlib.h"

#if LUA_VERSION_NUM > 501
//
// Lua 5.2
//
#define lua_strlen lua_rawlen
// luaL_typerror always used with arg at ndx == NULL
#define luaL_typerror(L,ndx,str) luaL_error(L,"bad argument %d (%s expected, got nil)",ndx,str)
// luaL_register used once, so below expansion is OK for this case
#define luaL_register(L,name,reg) lua_newtable(L);luaL_setfuncs(L,reg,0)
// luaL_openlib always used with name == NULL
#define luaL_openlib(L,name,reg,nup) luaL_setfuncs(L,reg,nup)
#endif

#include "sqlite3.h"

/* compile time features */
#if !defined(SQLITE_OMIT_PROGRESS_CALLBACK)
    #define SQLITE_OMIT_PROGRESS_CALLBACK 0
#endif
#if !defined(LSQLITE_OMIT_UPDATE_HOOK)
    #define LSQLITE_OMIT_UPDATE_HOOK 0
#endif

typedef struct sdb sdb;
typedef struct sdb_vm sdb_vm;
typedef struct sdb_func sdb_func;

/* to use as C user data so i know what function sqlite is calling */
struct sdb_func {
    /* references to associated lua values */
    int fn_step;
    int fn_finalize;
    int udata;

    sdb *db;
    char aggregate;

    sdb_func *next;
};

/* information about database */
struct sdb {
    /* associated lua state */
    lua_State *L;
    /* sqlite database handle */
    sqlite3 *db;

    /* sql functions stack usage */
    sdb_func *func;         /* top SQL function being called */

    /* references */
    int busy_cb;        /* busy callback */
    int busy_udata;

    int progress_cb;    /* progress handler */
    int progress_udata;

    int trace_cb;       /* trace callback */
    int trace_udata;

#if !defined(LSQLITE_OMIT_UPDATE_HOOK) || !LSQLITE_OMIT_UPDATE_HOOK

    int update_hook_cb; /* update_hook callback */
    int update_hook_udata;

    int commit_hook_cb; /* commit_hook callback */
    int commit_hook_udata;

    int rollback_hook_cb; /* rollback_hook callback */
    int rollback_hook_udata;

#endif
};

static const char *sqlite_meta      = ":sqlite3";
static const char *sqlite_vm_meta   = ":sqlite3:vm";
static const char *sqlite_ctx_meta  = ":sqlite3:ctx";
static int sqlite_ctx_meta_ref;

/*
** =======================================================
** Database Virtual Machine Operations
** =======================================================
*/

static void vm_push_column(lua_State *L, sqlite3_stmt *vm, int idx) {
    switch (sqlite3_column_type(vm, idx)) {
        case SQLITE_INTEGER:
            {
                sqlite_int64 i64 = sqlite3_column_int64(vm, idx);
                lua_Number n = (lua_Number)i64;
                if (n == i64)
                    lua_pushnumber(L, n);
                else
                    lua_pushlstring(L, (const char*)sqlite3_column_text(vm, idx), sqlite3_column_bytes(vm, idx));
            }
            break;
        case SQLITE_FLOAT:
            lua_pushnumber(L, sqlite3_column_double(vm, idx));
            break;
        case SQLITE_TEXT:
            lua_pushlstring(L, (const char*)sqlite3_column_text(vm, idx), sqlite3_column_bytes(vm, idx));
            break;
        case SQLITE_BLOB:
            lua_pushlstring(L, sqlite3_column_blob(vm, idx), sqlite3_column_bytes(vm, idx));
            break;
        case SQLITE_NULL:
            lua_pushnil(L);
            break;
        default:
            lua_pushnil(L);
            break;
    }
}

/* virtual machine information */
struct sdb_vm {
    sdb *db;                /* associated database handle */
    sqlite3_stmt *vm;       /* virtual machine */

    /* sqlite3_step info */
    int columns;            /* number of columns in result */
    char has_values;        /* true when step succeeds */

    char temp;              /* temporary vm used in db:rows */
};

/* called with sql text on the lua stack */
static sdb_vm *newvm(lua_State *L, sdb *db) {
    sdb_vm *svm = (sdb_vm*)lua_newuserdata(L, sizeof(sdb_vm));

    luaL_getmetatable(L, sqlite_vm_meta);
    lua_setmetatable(L, -2);        /* set metatable */

    svm->db = db;
    svm->columns = 0;
    svm->has_values = 0;
    svm->vm = NULL;
    svm->temp = 0;

    /* add an entry on the database table: svm -> sql text */
    lua_pushlightuserdata(L, db);
    lua_rawget(L, LUA_REGISTRYINDEX);
    lua_pushlightuserdata(L, svm);
    lua_pushvalue(L, -4); /* the sql text */
    lua_rawset(L, -3);
    lua_pop(L, 1);

    return svm;
}

static int cleanupvm(lua_State *L, sdb_vm *svm) {
    /* remove entry in database table - no harm if not present in the table */
    lua_pushlightuserdata(L, svm->db);
    lua_rawget(L, LUA_REGISTRYINDEX);
    lua_pushlightuserdata(L, svm);
    lua_pushnil(L);
    lua_rawset(L, -3);
    lua_pop(L, 1);

    svm->columns = 0;
    svm->has_values = 0;

    if (!svm->vm) return 0;

    lua_pushnumber(L, sqlite3_finalize(svm->vm));
    svm->vm = NULL;
    return 1;
}

static int stepvm(lua_State *L, sdb_vm *svm) {
    int result;
    int loop_limit = 3;
    while ( loop_limit-- ) {
        result = sqlite3_step(svm->vm);
        if ( result==SQLITE_ERROR ) {
          result = sqlite3_reset (svm->vm);
        }
        if ( result==SQLITE_SCHEMA ) {
            sqlite3_stmt *vn;
            const char *sql;
            /* recover sql text */
            lua_pushlightuserdata(L, svm->db);
            lua_rawget(L, LUA_REGISTRYINDEX);
            lua_pushlightuserdata(L, svm);
            lua_rawget(L, -2); /* sql text */
            sql = luaL_checkstring(L, -1);
            /* re-prepare */
            result = sqlite3_prepare(svm->db->db, sql, -1, &vn, NULL);
            if (result != SQLITE_OK) break;
            sqlite3_transfer_bindings(svm->vm, vn);
            sqlite3_finalize(svm->vm);
            svm->vm = vn;
            lua_pop(L,2);
        } else {
          break;
        }
    }
    return result;
}

static sdb_vm *lsqlite_getvm(lua_State *L, int index) {
    sdb_vm *svm = (sdb_vm*)luaL_checkudata(L, index, sqlite_vm_meta);
    if (svm == NULL) luaL_argerror(L, index, "bad sqlite virtual machine");
    return svm;
}

static sdb_vm *lsqlite_checkvm(lua_State *L, int index) {
    sdb_vm *svm = lsqlite_getvm(L, index);
    if (svm->vm == NULL) luaL_argerror(L, index, "attempt to use closed sqlite virtual machine");
    return svm;
}

static int dbvm_isopen(lua_State *L) {
    sdb_vm *svm = lsqlite_getvm(L, 1);
    lua_pushboolean(L, svm->vm != NULL ? 1 : 0);
    return 1;
}

static int dbvm_tostring(lua_State *L) {
    char buff[39];
    sdb_vm *svm = lsqlite_getvm(L, 1);
    if (svm->vm == NULL)
        strcpy(buff, "closed");
    else
        sprintf(buff, "%p", svm);
    lua_pushfstring(L, "sqlite virtual machine (%s)", buff);
    return 1;
}

static int dbvm_gc(lua_State *L) {
    sdb_vm *svm = lsqlite_getvm(L, 1);
    if (svm->vm != NULL)  /* ignore closed vms */
        cleanupvm(L, svm);
    return 0;
}

static int dbvm_step(lua_State *L) {
    int result;
    sdb_vm *svm = lsqlite_checkvm(L, 1);

    result = stepvm(L, svm);
    svm->has_values = result == SQLITE_ROW ? 1 : 0;
    svm->columns = sqlite3_data_count(svm->vm);

    lua_pushnumber(L, result);
    return 1;
}

static int dbvm_finalize(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    return cleanupvm(L, svm);
}

static int dbvm_reset(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_reset(svm->vm);
    lua_pushnumber(L, sqlite3_errcode(svm->db->db));
    return 1;
}

static void dbvm_check_contents(lua_State *L, sdb_vm *svm) {
    if (!svm->has_values) {
        luaL_error(L, "misuse of function");
    }
}

static void dbvm_check_index(lua_State *L, sdb_vm *svm, int index) {
    if (index < 0 || index >= svm->columns) {
        luaL_error(L, "index out of range [0..%d]", svm->columns - 1);
    }
}

static void dbvm_check_bind_index(lua_State *L, sdb_vm *svm, int index) {
    if (index < 1 || index > sqlite3_bind_parameter_count(svm->vm)) {
        luaL_error(L, "bind index out of range [1..%d]", sqlite3_bind_parameter_count(svm->vm));
    }
}

/*
** =======================================================
** Virtual Machine - generic info
** =======================================================
*/
static int dbvm_columns(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    lua_pushnumber(L, sqlite3_column_count(svm->vm));
    return 1;
}

/*
** =======================================================
** Virtual Machine - getters
** =======================================================
*/

static int dbvm_get_value(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    int index = luaL_checkint(L, 2);
    dbvm_check_contents(L, svm);
    dbvm_check_index(L, svm, index);
    vm_push_column(L, svm->vm, index);
    return 1;
}

static int dbvm_get_name(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    int index = luaL_checknumber(L, 2);
    dbvm_check_index(L, svm, index);
    lua_pushstring(L, sqlite3_column_name(svm->vm, index));
    return 1;
}

static int dbvm_get_type(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    int index = luaL_checknumber(L, 2);
    dbvm_check_index(L, svm, index);
    lua_pushstring(L, sqlite3_column_decltype(svm->vm, index));
    return 1;
}

static int dbvm_get_values(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int columns = svm->columns;
    int n;
    dbvm_check_contents(L, svm);

    lua_newtable(L);
    for (n = 0; n < columns;) {
        vm_push_column(L, vm, n++);
        lua_rawseti(L, -2, n);
    }
    return 1;
}

static int dbvm_get_names(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int columns = sqlite3_column_count(vm); /* valid as soon as statement prepared */
    int n;

    lua_newtable(L);
    for (n = 0; n < columns;) {
        lua_pushstring(L, sqlite3_column_name(vm, n++));
        lua_rawseti(L, -2, n);
    }
    return 1;
}

static int dbvm_get_types(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int columns = sqlite3_column_count(vm); /* valid as soon as statement prepared */
    int n;

    lua_newtable(L);
    for (n = 0; n < columns;) {
        lua_pushstring(L, sqlite3_column_decltype(vm, n++));
        lua_rawseti(L, -2, n);
    }
    return 1;
}

static int dbvm_get_uvalues(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int columns = svm->columns;
    int n;
    dbvm_check_contents(L, svm);

    lua_checkstack(L, columns);
    for (n = 0; n < columns; ++n)
        vm_push_column(L, vm, n);
    return columns;
}

static int dbvm_get_unames(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int columns = sqlite3_column_count(vm); /* valid as soon as statement prepared */
    int n;

    lua_checkstack(L, columns);
    for (n = 0; n < columns; ++n)
        lua_pushstring(L, sqlite3_column_name(vm, n));
    return columns;
}

static int dbvm_get_utypes(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int columns = sqlite3_column_count(vm); /* valid as soon as statement prepared */
    int n;

    lua_checkstack(L, columns);
    for (n = 0; n < columns; ++n)
        lua_pushstring(L, sqlite3_column_decltype(vm, n));
    return columns;
}

static int dbvm_get_named_values(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int columns = svm->columns;
    int n;
    dbvm_check_contents(L, svm);

    lua_newtable(L);
    for (n = 0; n < columns; ++n) {
        lua_pushstring(L, sqlite3_column_name(vm, n));
        vm_push_column(L, vm, n);
        lua_rawset(L, -3);
    }
    return 1;
}

static int dbvm_get_named_types(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int columns = sqlite3_column_count(vm);
    int n;

    lua_newtable(L);
    for (n = 0; n < columns; ++n) {
        lua_pushstring(L, sqlite3_column_name(vm, n));
        lua_pushstring(L, sqlite3_column_decltype(vm, n));
        lua_rawset(L, -3);
    }
    return 1;
}

/*
** =======================================================
** Virtual Machine - Bind
** =======================================================
*/

static int dbvm_bind_index(lua_State *L, sqlite3_stmt *vm, int index, int lindex) {
    switch (lua_type(L, lindex)) {
        case LUA_TSTRING:
            return sqlite3_bind_text(vm, index, lua_tostring(L, lindex), (int)lua_strlen(L, lindex), SQLITE_TRANSIENT);
        case LUA_TNUMBER:
            return sqlite3_bind_double(vm, index, lua_tonumber(L, lindex));
        case LUA_TBOOLEAN:
            return sqlite3_bind_int(vm, index, lua_toboolean(L, lindex) ? 1 : 0);
        case LUA_TNONE:
        case LUA_TNIL:
            return sqlite3_bind_null(vm, index);
        default:
            luaL_error(L, "index (%d) - invalid data type for bind (%s)", index, lua_typename(L, lua_type(L, lindex)));
            return SQLITE_MISUSE; /*!*/
    }
}


static int dbvm_bind_parameter_count(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    lua_pushnumber(L, sqlite3_bind_parameter_count(svm->vm));
    return 1;
}

static int dbvm_bind_parameter_name(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    int index = luaL_checknumber(L, 2);
    dbvm_check_bind_index(L, svm, index);
    lua_pushstring(L, sqlite3_bind_parameter_name(svm->vm, index));
    return 1;
}

static int dbvm_bind(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int index = luaL_checkint(L, 2);
    int result;

    dbvm_check_bind_index(L, svm, index);
    result = dbvm_bind_index(L, vm, index, 3);

    lua_pushnumber(L, result);
    return 1;
}

static int dbvm_bind_blob(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    int index = luaL_checkint(L, 2);
    const char *value = luaL_checkstring(L, 3);
    int len = (int)lua_strlen(L, 3);

    lua_pushnumber(L, sqlite3_bind_blob(svm->vm, index, value, len, SQLITE_TRANSIENT));
    return 1;
}

static int dbvm_bind_values(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int top = lua_gettop(L);
    int result, n;

    if (top - 1 != sqlite3_bind_parameter_count(vm))
        luaL_error(L,
            "incorrect number of parameters to bind (%d given, %d to bind)",
            top - 1,
            sqlite3_bind_parameter_count(vm)
        );

    for (n = 2; n <= top; ++n) {
        if ((result = dbvm_bind_index(L, vm, n - 1, n)) != SQLITE_OK) {
            lua_pushnumber(L, result);
            return 1;
        }
    }

    lua_pushnumber(L, SQLITE_OK);
    return 1;
}

static int dbvm_bind_names(lua_State *L) {
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm = svm->vm;
    int count = sqlite3_bind_parameter_count(vm);
    const char *name;
    int result, n;
    luaL_checktype(L, 2, LUA_TTABLE);

    for (n = 1; n <= count; ++n) {
        name = sqlite3_bind_parameter_name(vm, n);
        if (name && (name[0] == ':' || name[0] == '$')) {
            lua_pushstring(L, ++name);
            lua_gettable(L, 2);
            result = dbvm_bind_index(L, vm, n, -1);
            lua_pop(L, 1);
        }
        else {
            lua_pushnumber(L, n);
            lua_gettable(L, 2);
            result = dbvm_bind_index(L, vm, n, -1);
            lua_pop(L, 1);
        }

        if (result != SQLITE_OK) {
            lua_pushnumber(L, result);
            return 1;
        }
    }

    lua_pushnumber(L, SQLITE_OK);
    return 1;
}

/*
** =======================================================
** Database (internal management)
** =======================================================
*/

/*
** When creating database handles, always creates a `closed' database handle
** before opening the actual database; so, if there is a memory error, the
** database is not left opened.
**
** Creates a new 'table' and leaves it in the stack
*/
static sdb *newdb (lua_State *L) {
    sdb *db = (sdb*)lua_newuserdata(L, sizeof(sdb));
    db->L = L;
    db->db = NULL;  /* database handle is currently `closed' */
    db->func = NULL;

    db->busy_cb =
    db->busy_udata =
    db->progress_cb =
    db->progress_udata =
    db->trace_cb =
    db->trace_udata = 
#if !defined(LSQLITE_OMIT_UPDATE_HOOK) || !LSQLITE_OMIT_UPDATE_HOOK
    db->update_hook_cb =
    db->update_hook_udata =
    db->commit_hook_cb =
    db->commit_hook_udata =
    db->rollback_hook_cb =
    db->rollback_hook_udata =
#endif
     LUA_NOREF;

    luaL_getmetatable(L, sqlite_meta);
    lua_setmetatable(L, -2);        /* set metatable */

    /* to keep track of 'open' virtual machines */
    lua_pushlightuserdata(L, db);
    lua_newtable(L);
    lua_rawset(L, LUA_REGISTRYINDEX);

    return db;
}

static int cleanupdb(lua_State *L, sdb *db) {
    sdb_func *func;
    sdb_func *func_next;
    int top;
    int result;

    /* free associated virtual machines */
    lua_pushlightuserdata(L, db);
    lua_rawget(L, LUA_REGISTRYINDEX);

    /* close all used handles */
    top = lua_gettop(L);
    lua_pushnil(L);
    while (lua_next(L, -2)) {
        sdb_vm *svm = lua_touserdata(L, -2); /* key: vm; val: sql text */
        cleanupvm(L, svm);

        lua_settop(L, top);
        lua_pushnil(L);
    }

    lua_pop(L, 1); /* pop vm table */

    /* remove entry in lua registry table */
    lua_pushlightuserdata(L, db);
    lua_pushnil(L);
    lua_rawset(L, LUA_REGISTRYINDEX);

    /* 'free' all references */
    luaL_unref(L, LUA_REGISTRYINDEX, db->busy_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->busy_udata);
    luaL_unref(L, LUA_REGISTRYINDEX, db->progress_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->progress_udata);
    luaL_unref(L, LUA_REGISTRYINDEX, db->trace_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->trace_udata);
#if !defined(LSQLITE_OMIT_UPDATE_HOOK) || !LSQLITE_OMIT_UPDATE_HOOK
    luaL_unref(L, LUA_REGISTRYINDEX, db->update_hook_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->update_hook_udata);
    luaL_unref(L, LUA_REGISTRYINDEX, db->commit_hook_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->commit_hook_udata);
    luaL_unref(L, LUA_REGISTRYINDEX, db->rollback_hook_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->rollback_hook_udata);
#endif

    /* close database */
    result = sqlite3_close(db->db);
    db->db = NULL;

    /* free associated memory with created functions */
    func = db->func;
    while (func) {
        func_next = func->next;
        luaL_unref(L, LUA_REGISTRYINDEX, func->fn_step);
        luaL_unref(L, LUA_REGISTRYINDEX, func->fn_finalize);
        luaL_unref(L, LUA_REGISTRYINDEX, func->udata);
        free(func);
        func = func_next;
    }
    db->func = NULL;
    return result;
}

static sdb *lsqlite_getdb(lua_State *L, int index) {
    sdb *db = (sdb*)luaL_checkudata(L, index, sqlite_meta);
    if (db == NULL) luaL_typerror(L, index, "sqlite database");
    return db;
}

static sdb *lsqlite_checkdb(lua_State *L, int index) {
    sdb *db = lsqlite_getdb(L, index);
    if (db->db == NULL) luaL_argerror(L, index, "attempt to use closed sqlite database");
    return db;
}


/*
** =======================================================
** User Defined Functions - Context Methods
** =======================================================
*/
typedef struct {
    sqlite3_context *ctx;
    int ud;
} lcontext;

static lcontext *lsqlite_make_context(lua_State *L) {
    lcontext *ctx = (lcontext*)lua_newuserdata(L, sizeof(lcontext));
    lua_rawgeti(L, LUA_REGISTRYINDEX, sqlite_ctx_meta_ref);
    lua_setmetatable(L, -2);
    ctx->ctx = NULL;
    ctx->ud = LUA_NOREF;
    return ctx;
}

static lcontext *lsqlite_getcontext(lua_State *L, int index) {
    lcontext *ctx = (lcontext*)luaL_checkudata(L, index, sqlite_ctx_meta);
    if (ctx == NULL) luaL_typerror(L, index, "sqlite context");
    return ctx;
}

static lcontext *lsqlite_checkcontext(lua_State *L, int index) {
    lcontext *ctx = lsqlite_getcontext(L, index);
    if (ctx->ctx == NULL) luaL_argerror(L, index, "invalid sqlite context");
    return ctx;
}

static int lcontext_tostring(lua_State *L) {
    char buff[39];
    lcontext *ctx = lsqlite_getcontext(L, 1);
    if (ctx->ctx == NULL)
        strcpy(buff, "closed");
    else
        sprintf(buff, "%p", ctx->ctx);
    lua_pushfstring(L, "sqlite function context (%s)", buff);
    return 1;
}

static void lcontext_check_aggregate(lua_State *L, lcontext *ctx) {
    sdb_func *func = (sdb_func*)sqlite3_user_data(ctx->ctx);
    if (!func->aggregate) {
        luaL_error(L, "attempt to call aggregate method from scalar function");
    }
}

static int lcontext_user_data(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    sdb_func *func = (sdb_func*)sqlite3_user_data(ctx->ctx);
    lua_rawgeti(L, LUA_REGISTRYINDEX, func->udata);
    return 1;
}

static int lcontext_get_aggregate_context(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    lcontext_check_aggregate(L, ctx);
    lua_rawgeti(L, LUA_REGISTRYINDEX, ctx->ud);
    return 1;
}

static int lcontext_set_aggregate_context(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    lcontext_check_aggregate(L, ctx);
    lua_settop(L, 2);
    luaL_unref(L, LUA_REGISTRYINDEX, ctx->ud);
    ctx->ud = luaL_ref(L, LUA_REGISTRYINDEX);
    return 0;
}

static int lcontext_aggregate_count(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    lcontext_check_aggregate(L, ctx);
    lua_pushnumber(L, sqlite3_aggregate_count(ctx->ctx));
    return 1;
}

#if 0
void *sqlite3_get_auxdata(sqlite3_context*, int);
void sqlite3_set_auxdata(sqlite3_context*, int, void*, void (*)(void*));
#endif

static int lcontext_result(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    switch (lua_type(L, 2)) {
        case LUA_TNUMBER:
            sqlite3_result_double(ctx->ctx, luaL_checknumber(L, 2));
            break;
        case LUA_TSTRING:
            sqlite3_result_text(ctx->ctx, luaL_checkstring(L, 2), (int)lua_strlen(L, 2), SQLITE_TRANSIENT);
            break;
        case LUA_TNIL:
        case LUA_TNONE:
            sqlite3_result_null(ctx->ctx);
            break;
        default:
            luaL_error(L, "invalid result type %s", lua_typename(L, 2));
            break;
    }

    return 0;
}

static int lcontext_result_blob(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    const char *blob = luaL_checkstring(L, 2);
    int size = (int)lua_strlen(L, 2);
    sqlite3_result_blob(ctx->ctx, (const void*)blob, size, SQLITE_TRANSIENT);
    return 0;
}

static int lcontext_result_double(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    double d = luaL_checknumber(L, 2);
    sqlite3_result_double(ctx->ctx, d);
    return 0;
}

static int lcontext_result_error(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    const char *err = luaL_checkstring(L, 2);
    int size = (int)lua_strlen(L, 2);
    sqlite3_result_error(ctx->ctx, err, size);
    return 0;
}

static int lcontext_result_int(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    int i = luaL_checkint(L, 2);
    sqlite3_result_int(ctx->ctx, i);
    return 0;
}

static int lcontext_result_null(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    sqlite3_result_null(ctx->ctx);
    return 0;
}

static int lcontext_result_text(lua_State *L) {
    lcontext *ctx = lsqlite_checkcontext(L, 1);
    const char *text = luaL_checkstring(L, 2);
    int size = (int)lua_strlen(L, 2);
    sqlite3_result_text(ctx->ctx, text, size, SQLITE_TRANSIENT);
    return 0;
}

/*
** =======================================================
** Database Methods
** =======================================================
*/

static int db_isopen(lua_State *L) {
    sdb *db = lsqlite_getdb(L, 1);
    lua_pushboolean(L, db->db != NULL ? 1 : 0);
    return 1;
}

static int db_last_insert_rowid(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    /* conversion warning: int64 -> luaNumber */
    sqlite_int64 rowid = sqlite3_last_insert_rowid(db->db);
    lua_Number n = (lua_Number)rowid;
    if (n == rowid)
        lua_pushnumber(L, n);
    else
        lua_pushfstring(L, "%ll", rowid);
    return 1;
}

static int db_changes(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    lua_pushnumber(L, sqlite3_changes(db->db));
    return 1;
}

static int db_total_changes(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    lua_pushnumber(L, sqlite3_total_changes(db->db));
    return 1;
}

static int db_errcode(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    lua_pushnumber(L, sqlite3_errcode(db->db));
    return 1;
}

static int db_errmsg(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    lua_pushstring(L, sqlite3_errmsg(db->db));
    return 1;
}

static int db_interrupt(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    sqlite3_interrupt(db->db);
    return 0;
}

/*
** Registering SQL functions:
*/

static void db_push_value(lua_State *L, sqlite3_value *value) {
    switch (sqlite3_value_type(value)) {
        case SQLITE_TEXT:
            lua_pushlstring(L, (const char*)sqlite3_value_text(value), sqlite3_value_bytes(value));
            break;

        case SQLITE_INTEGER:
            {
                sqlite_int64 i64 = sqlite3_value_int64(value);
                lua_Number n = (lua_Number)i64;
                if (n == i64)
                    lua_pushnumber(L, n);
                else
                    lua_pushlstring(L, (const char*)sqlite3_value_text(value), sqlite3_value_bytes(value));
            }
            break;

        case SQLITE_FLOAT:
            lua_pushnumber(L, sqlite3_value_double(value));
            break;

        case SQLITE_BLOB:
            lua_pushlstring(L, sqlite3_value_blob(value), sqlite3_value_bytes(value));
            break;

        case SQLITE_NULL:
            lua_pushnil(L);
            break;

        default:
            /* things done properly (SQLite + Lua SQLite)
            ** this should never happen */
            lua_pushnil(L);
            break;
    }
}

/*
** callback functions used when calling registered sql functions
*/

/* scalar function to be called
** callback params: context, values... */
static void db_sql_normal_function(sqlite3_context *context, int argc, sqlite3_value **argv) {
    sdb_func *func = (sdb_func*)sqlite3_user_data(context);
    lua_State *L = func->db->L;
    int n;
    lcontext *ctx;

    int top = lua_gettop(L);

    /* ensure there is enough space in the stack */
    lua_checkstack(L, argc + 3);

    lua_rawgeti(L, LUA_REGISTRYINDEX, func->fn_step);   /* function to call */

    if (!func->aggregate) {
        ctx = lsqlite_make_context(L); /* push context - used to set results */
    }
    else {
        /* reuse context userdata value */
        void *p = sqlite3_aggregate_context(context, 1);
        /* i think it is OK to use assume that using a light user data
        ** as an entry on LUA REGISTRY table will be unique */
        lua_pushlightuserdata(L, p);
        lua_rawget(L, LUA_REGISTRYINDEX);       /* context table */

        if (lua_isnil(L, -1)) { /* not yet created? */
            lua_pop(L, 1);
            ctx = lsqlite_make_context(L);
            lua_pushlightuserdata(L, p);
            lua_pushvalue(L, -2);
            lua_rawset(L, LUA_REGISTRYINDEX);
        }
        else
            ctx = lsqlite_getcontext(L, -1);
    }

    /* push params */
    for (n = 0; n < argc; ++n) {
        db_push_value(L, argv[n]);
    }

    /* set context */
    ctx->ctx = context;

    if (lua_pcall(L, argc + 1, 0, 0)) {
        const char *errmsg = lua_tostring(L, -1);
        int size = (int)lua_strlen(L, -1);
        sqlite3_result_error(context, errmsg, size);
    }

    /* invalidate context */
    ctx->ctx = NULL;

    if (!func->aggregate) {
        luaL_unref(L, LUA_REGISTRYINDEX, ctx->ud);
    }

    lua_settop(L, top);
}

static void db_sql_finalize_function(sqlite3_context *context) {
    sdb_func *func = (sdb_func*)sqlite3_user_data(context);
    lua_State *L = func->db->L;
    void *p = sqlite3_aggregate_context(context, 1); /* minimal mem usage */
    lcontext *ctx;
    int top = lua_gettop(L);

    lua_rawgeti(L, LUA_REGISTRYINDEX, func->fn_finalize);   /* function to call */

    /* i think it is OK to use assume that using a light user data
    ** as an entry on LUA REGISTRY table will be unique */
    lua_pushlightuserdata(L, p);
    lua_rawget(L, LUA_REGISTRYINDEX);       /* context table */

    if (lua_isnil(L, -1)) { /* not yet created? - shouldn't happen in finalize function */
        lua_pop(L, 1);
        ctx = lsqlite_make_context(L);
        lua_pushlightuserdata(L, p);
        lua_pushvalue(L, -2);
        lua_rawset(L, LUA_REGISTRYINDEX);
    }
    else
        ctx = lsqlite_getcontext(L, -1);

    /* set context */
    ctx->ctx = context;

    if (lua_pcall(L, 1, 0, 0)) {
        sqlite3_result_error(context, lua_tostring(L, -1), -1);
    }

    /* invalidate context */
    ctx->ctx = NULL;

    /* cleanup context */
    luaL_unref(L, LUA_REGISTRYINDEX, ctx->ud);
    /* remove it from registry */
    lua_pushlightuserdata(L, p);
    lua_pushnil(L);
    lua_rawset(L, LUA_REGISTRYINDEX);

    lua_settop(L, top);
}

/*
** Register a normal function
** Params: db, function name, number arguments, [ callback | step, finalize], user data
** Returns: true on sucess
**
** Normal function:
** Params: context, params
**
** Aggregate function:
** Params of step: context, params
** Params of finalize: context
*/
static int db_register_function(lua_State *L, int aggregate) {
    sdb *db = lsqlite_checkdb(L, 1);
    const char *name;
    int args;
    int result;
    sdb_func *func;

    /* safety measure */
    if (aggregate) aggregate = 1;

    name = luaL_checkstring(L, 2);
    args = luaL_checkint(L, 3);
    luaL_checktype(L, 4, LUA_TFUNCTION);
    if (aggregate) luaL_checktype(L, 5, LUA_TFUNCTION);

    /* maybe an alternative way to allocate memory should be used/avoided */
    func = (sdb_func*)malloc(sizeof(sdb_func));
    if (func == NULL) {
        luaL_error(L, "out of memory");
    }

    result = sqlite3_create_function(
        db->db, name, args, SQLITE_UTF8, func,
        aggregate ? NULL : db_sql_normal_function,
        aggregate ? db_sql_normal_function : NULL,
        aggregate ? db_sql_finalize_function : NULL
    );

    if (result == SQLITE_OK) {
        /* safety measures for userdata field to be present in the stack */
        lua_settop(L, 5 + aggregate);

        /* save registered function in db function list */
        func->db = db;
        func->aggregate = aggregate;
        func->next = db->func;
        db->func = func;

        /* save the setp/normal function callback */
        lua_pushvalue(L, 4);
        func->fn_step = luaL_ref(L, LUA_REGISTRYINDEX);
        /* save user data */
        lua_pushvalue(L, 5+aggregate);
        func->udata = luaL_ref(L, LUA_REGISTRYINDEX);

        if (aggregate) {
            lua_pushvalue(L, 5);
            func->fn_finalize = luaL_ref(L, LUA_REGISTRYINDEX);
        }
        else
            func->fn_finalize = LUA_NOREF;
    }
    else {
        /* free allocated memory */
        free(func);
    }

    lua_pushboolean(L, result == SQLITE_OK ? 1 : 0);
    return 1;
}

static int db_create_function(lua_State *L) {
    return db_register_function(L, 0);
}

static int db_create_aggregate(lua_State *L) {
    return db_register_function(L, 1);
}

/* create_collation; contributed by Thomas Lauer
*/

typedef struct {
    lua_State *L;
    int ref;
} scc;

static int collwrapper(scc *co,int l1,const void *p1,
                        int l2,const void *p2) {
    int res=0;
    lua_State *L=co->L;
    lua_rawgeti(L,LUA_REGISTRYINDEX,co->ref);
    lua_pushlstring(L,p1,l1);
    lua_pushlstring(L,p2,l2);
    if (lua_pcall(L,2,1,0)==0) res=(int)lua_tonumber(L,-1);
    lua_pop(L,1);
    return res;
}

static void collfree(scc *co) {
    if (co) {
        luaL_unref(co->L,LUA_REGISTRYINDEX,co->ref);
        free(co);
    }
}

static int db_create_collation(lua_State *L) {
    sdb *db=lsqlite_checkdb(L,1);
    const char *collname=luaL_checkstring(L,2);
    scc *co=NULL;
    int (*collfunc)(scc *,int,const void *,int,const void *)=NULL;
    lua_settop(L,3); /* default args to nil, and exclude extras */
    if (lua_isfunction(L,3)) collfunc=collwrapper;
    else if (!lua_isnil(L,3))
        luaL_error(L,"create_collation: function or nil expected");
    if (collfunc != NULL) {
        co=(scc *)malloc(sizeof(scc)); /* userdata is a no-no as it
                                          will be garbage-collected */
        if (co) {
            co->L=L;
            /* lua_settop(L,3) above means we don't need: lua_pushvalue(L,3); */
            co->ref=luaL_ref(L,LUA_REGISTRYINDEX);
        }
        else luaL_error(L,"create_collation: could not allocate callback");
    }
    sqlite3_create_collation_v2(db->db, collname, SQLITE_UTF8,
        (void *)co,
        (int(*)(void*,int,const void*,int,const void*))collfunc,
        (void(*)(void*))collfree);
    return 0;
}

/*
** trace callback:
** Params: database, callback function, userdata
**
** callback function:
** Params: userdata, sql
*/
static void db_trace_callback(void *user, const char *sql) {
    sdb *db = (sdb*)user;
    lua_State *L = db->L;
    int top = lua_gettop(L);

    /* setup lua callback call */
    lua_rawgeti(L, LUA_REGISTRYINDEX, db->trace_cb);    /* get callback */
    lua_rawgeti(L, LUA_REGISTRYINDEX, db->trace_udata); /* get callback user data */
    lua_pushstring(L, sql); /* traced sql statement */

    /* call lua function */
    lua_pcall(L, 2, 0, 0);
    /* ignore any error generated by this function */

    lua_settop(L, top);
}

static int db_trace(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);

    if (lua_gettop(L) < 2 || lua_isnil(L, 2)) {
        luaL_unref(L, LUA_REGISTRYINDEX, db->trace_cb);
        luaL_unref(L, LUA_REGISTRYINDEX, db->trace_udata);

        db->trace_cb =
        db->trace_udata = LUA_NOREF;

        /* clear trace handler */
        sqlite3_trace(db->db, NULL, NULL);
    }
    else {
        luaL_checktype(L, 2, LUA_TFUNCTION);

        /* make sure we have an userdata field (even if nil) */
        lua_settop(L, 3);

        luaL_unref(L, LUA_REGISTRYINDEX, db->trace_cb);
        luaL_unref(L, LUA_REGISTRYINDEX, db->trace_udata);

        db->trace_udata = luaL_ref(L, LUA_REGISTRYINDEX);
        db->trace_cb = luaL_ref(L, LUA_REGISTRYINDEX);

        /* set trace handler */
        sqlite3_trace(db->db, db_trace_callback, db);
    }

    return 0;
}

#if !defined(LSQLITE_OMIT_UPDATE_HOOK) || !LSQLITE_OMIT_UPDATE_HOOK

/*
** update_hook callback:
** Params: database, callback function, userdata
**
** callback function:
** Params: userdata, {one of SQLITE_INSERT, SQLITE_DELETE, or SQLITE_UPDATE}, 
**          database name, table name (containing the affected row), rowid of the row
*/
static void db_update_hook_callback(void *user, int op, char const *dbname, char const *tblname, sqlite3_int64 rowid) {
	lua_Number n = 0;
    sdb *db = (sdb*)user;
    lua_State *L = db->L;
    int top = lua_gettop(L);

    /* setup lua callback call */
    lua_rawgeti(L, LUA_REGISTRYINDEX, db->update_hook_cb);    /* get callback */
    lua_rawgeti(L, LUA_REGISTRYINDEX, db->update_hook_udata); /* get callback user data */
    lua_pushnumber(L, (lua_Number )op);
    lua_pushstring(L, dbname); /* update_hook database name */
    lua_pushstring(L, tblname); /* update_hook database name */
    n = (lua_Number)rowid;
    if (n == rowid)
        lua_pushnumber(L, n);
    else
        lua_pushfstring(L, "%ll", rowid);

    /* call lua function */
    lua_pcall(L, 5, 0, 0);
    /* ignore any error generated by this function */

    lua_settop(L, top);
}

static int db_update_hook(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);

    if (lua_gettop(L) < 2 || lua_isnil(L, 2)) {
        luaL_unref(L, LUA_REGISTRYINDEX, db->update_hook_cb);
        luaL_unref(L, LUA_REGISTRYINDEX, db->update_hook_udata);

        db->update_hook_cb =
        db->update_hook_udata = LUA_NOREF;

        /* clear update_hook handler */
        sqlite3_update_hook(db->db, NULL, NULL);
    }
    else {
        luaL_checktype(L, 2, LUA_TFUNCTION);

        /* make sure we have an userdata field (even if nil) */
        lua_settop(L, 3);

        luaL_unref(L, LUA_REGISTRYINDEX, db->update_hook_cb);
        luaL_unref(L, LUA_REGISTRYINDEX, db->update_hook_udata);

        db->update_hook_udata = luaL_ref(L, LUA_REGISTRYINDEX);
        db->update_hook_cb = luaL_ref(L, LUA_REGISTRYINDEX);

        /* set update_hook handler */
        sqlite3_update_hook(db->db, db_update_hook_callback, db);
    }

    return 0;
}

/*
** commit_hook callback:
** Params: database, callback function, userdata
**
** callback function:
** Params: userdata
** Returned value: Return false or nil to continue the COMMIT operation normally.
**  return true (non false, non nil), then the COMMIT is converted into a ROLLBACK. 
*/
static int db_commit_hook_callback(void *user) {
    sdb *db = (sdb*)user;
    lua_State *L = db->L;
    int top = lua_gettop(L);
    int rollback = 0;

    /* setup lua callback call */
    lua_rawgeti(L, LUA_REGISTRYINDEX, db->commit_hook_cb);    /* get callback */
    lua_rawgeti(L, LUA_REGISTRYINDEX, db->commit_hook_udata); /* get callback user data */

    /* call lua function */
    if (!lua_pcall(L, 1, 1, 0))
        rollback = lua_toboolean(L, -1); /* use result if there was no error */

    lua_settop(L, top);
    return rollback;
}

static int db_commit_hook(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);

    if (lua_gettop(L) < 2 || lua_isnil(L, 2)) {
        luaL_unref(L, LUA_REGISTRYINDEX, db->commit_hook_cb);
        luaL_unref(L, LUA_REGISTRYINDEX, db->commit_hook_udata);

        db->commit_hook_cb =
        db->commit_hook_udata = LUA_NOREF;

        /* clear commit_hook handler */
        sqlite3_commit_hook(db->db, NULL, NULL);
    }
    else {
        luaL_checktype(L, 2, LUA_TFUNCTION);

        /* make sure we have an userdata field (even if nil) */
        lua_settop(L, 3);

        luaL_unref(L, LUA_REGISTRYINDEX, db->commit_hook_cb);
        luaL_unref(L, LUA_REGISTRYINDEX, db->commit_hook_udata);

        db->commit_hook_udata = luaL_ref(L, LUA_REGISTRYINDEX);
        db->commit_hook_cb = luaL_ref(L, LUA_REGISTRYINDEX);

        /* set commit_hook handler */
        sqlite3_commit_hook(db->db, db_commit_hook_callback, db);
    }

    return 0;
}

/*
** rollback hook callback:
** Params: database, callback function, userdata
**
** callback function:
** Params: userdata
*/
static void db_rollback_hook_callback(void *user) {
    sdb *db = (sdb*)user;
    lua_State *L = db->L;
    int top = lua_gettop(L);

    /* setup lua callback call */
    lua_rawgeti(L, LUA_REGISTRYINDEX, db->rollback_hook_cb);    /* get callback */
    lua_rawgeti(L, LUA_REGISTRYINDEX, db->rollback_hook_udata); /* get callback user data */

    /* call lua function */
    lua_pcall(L, 1, 0, 0);
    /* ignore any error generated by this function */

    lua_settop(L, top);
}

static int db_rollback_hook(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);

    if (lua_gettop(L) < 2 || lua_isnil(L, 2)) {
        luaL_unref(L, LUA_REGISTRYINDEX, db->rollback_hook_cb);
        luaL_unref(L, LUA_REGISTRYINDEX, db->rollback_hook_udata);

        db->rollback_hook_cb =
        db->rollback_hook_udata = LUA_NOREF;

        /* clear rollback_hook handler */
        sqlite3_rollback_hook(db->db, NULL, NULL);
    }
    else {
        luaL_checktype(L, 2, LUA_TFUNCTION);

        /* make sure we have an userdata field (even if nil) */
        lua_settop(L, 3);

        luaL_unref(L, LUA_REGISTRYINDEX, db->rollback_hook_cb);
        luaL_unref(L, LUA_REGISTRYINDEX, db->rollback_hook_udata);

        db->rollback_hook_udata = luaL_ref(L, LUA_REGISTRYINDEX);
        db->rollback_hook_cb = luaL_ref(L, LUA_REGISTRYINDEX);

        /* set rollback_hook handler */
        sqlite3_rollback_hook(db->db, db_rollback_hook_callback, db);
    }

    return 0;
}

#endif /* #if !defined(LSQLITE_OMIT_UPDATE_HOOK) || !LSQLITE_OMIT_UPDATE_HOOK */

#if !defined(SQLITE_OMIT_PROGRESS_CALLBACK) || !SQLITE_OMIT_PROGRESS_CALLBACK

/*
** progress handler:
** Params: database, number of opcodes, callback function, userdata
**
** callback function:
** Params: userdata
** returns: 0 to return immediatly and return SQLITE_ABORT, non-zero to continue
*/
static int db_progress_callback(void *user) {
    int result = 1; /* abort by default */
    sdb *db = (sdb*)user;
    lua_State *L = db->L;
    int top = lua_gettop(L);

    lua_rawgeti(L, LUA_REGISTRYINDEX, db->progress_cb);
    lua_rawgeti(L, LUA_REGISTRYINDEX, db->progress_udata);

    /* call lua function */
    if (!lua_pcall(L, 1, 1, 0))
        result = lua_toboolean(L, -1);

    lua_settop(L, top);
    return result;
}

static int db_progress_handler(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);

    if (lua_gettop(L) < 2 || lua_isnil(L, 2)) {
        luaL_unref(L, LUA_REGISTRYINDEX, db->progress_cb);
        luaL_unref(L, LUA_REGISTRYINDEX, db->progress_udata);

        db->progress_cb =
        db->progress_udata = LUA_NOREF;

        /* clear busy handler */
        sqlite3_progress_handler(db->db, 0, NULL, NULL);
    }
    else {
        int nop = luaL_checkint(L, 2);  /* number of opcodes */
        luaL_checktype(L, 3, LUA_TFUNCTION);

        /* make sure we have an userdata field (even if nil) */
        lua_settop(L, 4);

        luaL_unref(L, LUA_REGISTRYINDEX, db->progress_cb);
        luaL_unref(L, LUA_REGISTRYINDEX, db->progress_udata);

        db->progress_udata = luaL_ref(L, LUA_REGISTRYINDEX);
        db->progress_cb = luaL_ref(L, LUA_REGISTRYINDEX);

        /* set progress callback */
        sqlite3_progress_handler(db->db, nop, db_progress_callback, db);
    }

    return 0;
}

#else /* #if !defined(SQLITE_OMIT_PROGRESS_CALLBACK) || !SQLITE_OMIT_PROGRESS_CALLBACK */

static int db_progress_handler(lua_State *L) {
    lua_pushliteral(L, "progress callback support disabled at compile time");
    lua_error(L);
    return 0;
}

#endif /* #if !defined(SQLITE_OMIT_PROGRESS_CALLBACK) || !SQLITE_OMIT_PROGRESS_CALLBACK */

/*
** busy handler:
** Params: database, callback function, userdata
**
** callback function:
** Params: userdata, number of tries
** returns: 0 to return immediatly and return SQLITE_BUSY, non-zero to try again
*/
static int db_busy_callback(void *user, int tries) {
    int retry = 0; /* abort by default */
    sdb *db = (sdb*)user;
    lua_State *L = db->L;
    int top = lua_gettop(L);

    lua_rawgeti(L, LUA_REGISTRYINDEX, db->busy_cb);
    lua_rawgeti(L, LUA_REGISTRYINDEX, db->busy_udata);
    lua_pushnumber(L, tries);

    /* call lua function */
    if (!lua_pcall(L, 2, 1, 0))
        retry = lua_toboolean(L, -1);

    lua_settop(L, top);
    return retry;
}

static int db_busy_handler(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);

    if (lua_gettop(L) < 2 || lua_isnil(L, 2)) {
        luaL_unref(L, LUA_REGISTRYINDEX, db->busy_cb);
        luaL_unref(L, LUA_REGISTRYINDEX, db->busy_udata);

        db->busy_cb =
        db->busy_udata = LUA_NOREF;

        /* clear busy handler */
        sqlite3_busy_handler(db->db, NULL, NULL);
    }
    else {
        luaL_checktype(L, 2, LUA_TFUNCTION);
        /* make sure we have an userdata field (even if nil) */
        lua_settop(L, 3);

        luaL_unref(L, LUA_REGISTRYINDEX, db->busy_cb);
        luaL_unref(L, LUA_REGISTRYINDEX, db->busy_udata);

        db->busy_udata = luaL_ref(L, LUA_REGISTRYINDEX);
        db->busy_cb = luaL_ref(L, LUA_REGISTRYINDEX);

        /* set busy handler */
        sqlite3_busy_handler(db->db, db_busy_callback, db);
    }

    return 0;
}

static int db_busy_timeout(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    int timeout = luaL_checkint(L, 2);
    sqlite3_busy_timeout(db->db, timeout);

    /* if there was a timeout callback registered, it is now
    ** invalid/useless. free any references we may have */
    luaL_unref(L, LUA_REGISTRYINDEX, db->busy_cb);
    luaL_unref(L, LUA_REGISTRYINDEX, db->busy_udata);
    db->busy_cb =
    db->busy_udata = LUA_NOREF;

    return 0;
}

/*
** Params: db, sql, callback, user
** returns: code [, errmsg]
**
** Callback:
** Params: user, number of columns, values, names
** Returns: 0 to continue, other value will cause abort
*/
static int db_exec_callback(void* user, int columns, char **data, char **names) {
    int result = SQLITE_ABORT; /* abort by default */
    lua_State *L = (lua_State*)user;
    int n;

    int top = lua_gettop(L);

    lua_pushvalue(L, 3); /* function to call */
    lua_pushvalue(L, 4); /* user data */
    lua_pushnumber(L, columns); /* total number of rows in result */

    /* column values */
    lua_pushvalue(L, 6);
    for (n = 0; n < columns;) {
        lua_pushstring(L, data[n++]);
        lua_rawseti(L, -2, n);
    }

    /* columns names */
    lua_pushvalue(L, 5);
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        lua_newtable(L);
        lua_pushvalue(L, -1);
        lua_replace(L, 5);
        for (n = 0; n < columns;) {
            lua_pushstring(L, names[n++]);
            lua_rawseti(L, -2, n);
        }
    }

    /* call lua function */
    if (!lua_pcall(L, 4, 1, 0)) {
        if (lua_isnumber(L, -1))
            result = lua_tonumber(L, -1);
    }

    lua_settop(L, top);
    return result;
}

static int db_exec(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    const char *sql = luaL_checkstring(L, 2);
    int result;

    if (!lua_isnoneornil(L, 3)) {
        /* stack:
        **  3: callback function
        **  4: userdata
        **  5: column names
        **  6: reusable column values
        */
        luaL_checktype(L, 3, LUA_TFUNCTION);
        lua_settop(L, 4);   /* 'trap' userdata - nil extra parameters */
        lua_pushnil(L);     /* column names not known at this point */
        lua_newtable(L);    /* column values table */

        result = sqlite3_exec(db->db, sql, db_exec_callback, L, NULL);
    }
    else {
        /* no callbacks */
        result = sqlite3_exec(db->db, sql, NULL, NULL, NULL);
    }

    lua_pushnumber(L, result);
    return 1;
}

/*
** Params: db, sql
** returns: code, compiled length or error message
*/
static int db_prepare(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    const char *sql = luaL_checkstring(L, 2);
    int sql_len = (int)lua_strlen(L, 2);
    const char *sqltail;
    sdb_vm *svm;
    lua_settop(L,2); /* sql is on top of stack for call to newvm */
    svm = newvm(L, db);

    if (sqlite3_prepare(db->db, sql, sql_len, &svm->vm, &sqltail) != SQLITE_OK) {
        cleanupvm(L, svm);

        lua_pushnil(L);
        lua_pushnumber(L, sqlite3_errcode(db->db));
        return 2;
    }

    /* vm already in the stack */
    lua_pushstring(L, sqltail);
    return 2;
}

static int db_do_next_row(lua_State *L, int packed) {
    int result;
    sdb_vm *svm = lsqlite_checkvm(L, 1);
    sqlite3_stmt *vm;
    int columns;
    int i;

    result = stepvm(L, svm);
    vm = svm->vm; /* stepvm may change svm->vm if re-prepare is needed */
    svm->has_values = result == SQLITE_ROW ? 1 : 0;
    svm->columns = columns = sqlite3_data_count(vm);

    if (result == SQLITE_ROW) {
        if (packed) {
            lua_newtable(L);
            if (packed == 1) {
                for (i = 0; i < columns;) {
                    vm_push_column(L, vm, i);
                    lua_rawseti(L, -2, ++i);
                }
            }
            else {
                for (i = 0; i < columns; ++i) {
                    lua_pushstring(L, sqlite3_column_name(vm, i));
                    vm_push_column(L, vm, i);
                    lua_rawset(L, -3);
                }
            }
            return 1;
        }
        else {
            lua_checkstack(L, columns);
            for (i = 0; i < columns; ++i)
                vm_push_column(L, vm, i);
            return svm->columns;
        }
    }

    if (svm->temp) {
        /* finalize and check for errors */
        result = sqlite3_finalize(vm);
        svm->vm = NULL;
        cleanupvm(L, svm);
    }
    else if (result == SQLITE_DONE) {
        result = sqlite3_reset(vm);
    }

    if (result != SQLITE_OK) {
        lua_pushstring(L, sqlite3_errmsg(svm->db->db));
        lua_error(L);
    }
    return 0;
}

static int db_next_row(lua_State *L) {
    return db_do_next_row(L, 0);
}

static int db_next_packed_row(lua_State *L) {
    return db_do_next_row(L, 1);
}

static int db_next_named_row(lua_State *L) {
    return db_do_next_row(L, 2);
}

static int dbvm_do_rows(lua_State *L, int(*f)(lua_State *)) {
    /* sdb_vm *svm =  */
    lsqlite_checkvm(L, 1);
    lua_pushvalue(L,1);
    lua_pushcfunction(L, f);
    lua_insert(L, -2);
    return 2;
}

static int dbvm_rows(lua_State *L) {
    return dbvm_do_rows(L, db_next_packed_row);
}

static int dbvm_nrows(lua_State *L) {
    return dbvm_do_rows(L, db_next_named_row);
}

static int dbvm_urows(lua_State *L) {
    return dbvm_do_rows(L, db_next_row);
}

static int db_do_rows(lua_State *L, int(*f)(lua_State *)) {
    sdb *db = lsqlite_checkdb(L, 1);
    const char *sql = luaL_checkstring(L, 2);
    sdb_vm *svm;
    lua_settop(L,2); /* sql is on top of stack for call to newvm */
    svm = newvm(L, db);
    svm->temp = 1;

    if (sqlite3_prepare(db->db, sql, -1, &svm->vm, NULL) != SQLITE_OK) {
        cleanupvm(L, svm);

        lua_pushstring(L, sqlite3_errmsg(svm->db->db));
        lua_error(L);
    }

    lua_pushcfunction(L, f);
    lua_insert(L, -2);
    return 2;
}

static int db_rows(lua_State *L) {
    return db_do_rows(L, db_next_packed_row);
}

static int db_nrows(lua_State *L) {
    return db_do_rows(L, db_next_named_row);
}

/* unpacked version of db:rows */
static int db_urows(lua_State *L) {
    return db_do_rows(L, db_next_row);
}

static int db_tostring(lua_State *L) {
    char buff[32];
    sdb *db = lsqlite_getdb(L, 1);
    if (db->db == NULL)
        strcpy(buff, "closed");
    else
        sprintf(buff, "%p", lua_touserdata(L, 1));
    lua_pushfstring(L, "sqlite database (%s)", buff);
    return 1;
}

static int db_close(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    lua_pushnumber(L, cleanupdb(L, db));
    return 1;
}

static int db_close_vm(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    /* cleanup temporary only tables? */
    int temp = lua_toboolean(L, 2);

    /* free associated virtual machines */
    lua_pushlightuserdata(L, db);
    lua_rawget(L, LUA_REGISTRYINDEX);

    /* close all used handles */
    lua_pushnil(L);
    while (lua_next(L, -2)) {
        sdb_vm *svm = lua_touserdata(L, -2); /* key: vm; val: sql text */

        if ((!temp || svm->temp) && svm->vm)
        {
            sqlite3_finalize(svm->vm);
            svm->vm = NULL;
        }

        /* leave key in the stack */
        lua_pop(L, 1);
    }
    return 0;
}

static int db_gc(lua_State *L) {
    sdb *db = lsqlite_getdb(L, 1);
    if (db->db != NULL)  /* ignore closed databases */
        cleanupdb(L, db);
    return 0;
}

/*
** =======================================================
** General library functions
** =======================================================
*/

static int lsqlite_version(lua_State *L) {
    lua_pushstring(L, sqlite3_libversion());
    return 1;
}

static int lsqlite_complete(lua_State *L) {
    const char *sql = luaL_checkstring(L, 1);
    lua_pushboolean(L, sqlite3_complete(sql));
    return 1;
}

#ifndef WIN32
static int lsqlite_temp_directory(lua_State *L) {
    const char *oldtemp = sqlite3_temp_directory;

    if (!lua_isnone(L, 1)) {
        const char *temp = luaL_optstring(L, 1, NULL);
        if (sqlite3_temp_directory) {
            sqlite3_free((char*)sqlite3_temp_directory);
        }
        if (temp) {
            sqlite3_temp_directory = sqlite3_mprintf("%s", temp);
        }
        else {
            sqlite3_temp_directory = NULL;
        }
    }
    lua_pushstring(L, oldtemp);
    return 1;
}
#endif

static int lsqlite_do_open(lua_State *L, const char *filename) {
    sdb *db = newdb(L); /* create and leave in stack */

    if (sqlite3_open(filename, &db->db) == SQLITE_OK) {
        /* database handle already in the stack - return it */
        return 1;
    }

    /* failed to open database */
    lua_pushnil(L);                             /* push nil */
    lua_pushnumber(L, sqlite3_errcode(db->db));
    lua_pushstring(L, sqlite3_errmsg(db->db));  /* push error message */

    /* clean things up */
    cleanupdb(L, db);

    /* return */
    return 3;
}

static int lsqlite_open(lua_State *L) {
    const char *filename = luaL_checkstring(L, 1);
    return lsqlite_do_open(L, filename);
}

static int lsqlite_open_memory(lua_State *L) {
    return lsqlite_do_open(L, ":memory:");
}

static int lsqlite_newindex(lua_State *L) {
    lua_pushliteral(L, "attempt to change readonly table");
    lua_error(L);
    return 0;
}

/*
** =======================================================
** Register functions
** =======================================================
*/

#define SC(s)   { #s, SQLITE_ ## s },
#define LSC(s)  { #s, LSQLITE_ ## s },

static const struct {
    const char* name;
    int value;
} sqlite_constants[] = {
    /* error codes */
    SC(OK)          SC(ERROR)       SC(INTERNAL)    SC(PERM)
    SC(ABORT)       SC(BUSY)        SC(LOCKED)      SC(NOMEM)
    SC(READONLY)    SC(INTERRUPT)   SC(IOERR)       SC(CORRUPT)
    SC(NOTFOUND)    SC(FULL)        SC(CANTOPEN)    SC(PROTOCOL)
    SC(EMPTY)       SC(SCHEMA)      SC(TOOBIG)      SC(CONSTRAINT)
    SC(MISMATCH)    SC(MISUSE)      SC(NOLFS)
    SC(FORMAT)      SC(NOTADB)

    /* sqlite_step specific return values */
    SC(RANGE)       SC(ROW)         SC(DONE)

    /* column types */
    SC(INTEGER)     SC(FLOAT)       SC(TEXT)        SC(BLOB)
    SC(NULL)

    /* Authorizer Action Codes */
    SC(CREATE_INDEX       )
    SC(CREATE_TABLE       )
    SC(CREATE_TEMP_INDEX  )
    SC(CREATE_TEMP_TABLE  )
    SC(CREATE_TEMP_TRIGGER)
    SC(CREATE_TEMP_VIEW   )
    SC(CREATE_TRIGGER     )
    SC(CREATE_VIEW        )
    SC(DELETE             )
    SC(DROP_INDEX         )
    SC(DROP_TABLE         )
    SC(DROP_TEMP_INDEX    )
    SC(DROP_TEMP_TABLE    )
    SC(DROP_TEMP_TRIGGER  )
    SC(DROP_TEMP_VIEW     )
    SC(DROP_TRIGGER       )
    SC(DROP_VIEW          )
    SC(INSERT             )
    SC(PRAGMA             )
    SC(READ               )
    SC(SELECT             )
    SC(TRANSACTION        )
    SC(UPDATE             )
    SC(ATTACH             )
    SC(DETACH             )
    SC(ALTER_TABLE        )
    SC(REINDEX            )
    SC(ANALYZE            )
    SC(CREATE_VTABLE      )
    SC(DROP_VTABLE        )
    SC(FUNCTION           )
    SC(SAVEPOINT          )

    /* terminator */
    { NULL, 0 }
};

/* ======================================================= */

static const luaL_Reg dblib[] = {
    {"isopen",              db_isopen               },
    {"last_insert_rowid",   db_last_insert_rowid    },
    {"changes",             db_changes              },
    {"total_changes",       db_total_changes        },
    {"errcode",             db_errcode              },
    {"error_code",          db_errcode              },
    {"errmsg",              db_errmsg               },
    {"error_message",       db_errmsg               },
    {"interrupt",           db_interrupt            },

    {"create_function",     db_create_function      },
    {"create_aggregate",    db_create_aggregate     },
    {"create_collation",    db_create_collation     },

    {"trace",               db_trace                },
    {"progress_handler",    db_progress_handler     },
    {"busy_timeout",        db_busy_timeout         },
    {"busy_handler",        db_busy_handler         },
#if !defined(LSQLITE_OMIT_UPDATE_HOOK) || !LSQLITE_OMIT_UPDATE_HOOK
    {"update_hook",         db_update_hook          },
    {"commit_hook",         db_commit_hook          },
    {"rollback_hook",       db_rollback_hook        },
#endif

    {"prepare",             db_prepare              },
    {"rows",                db_rows                 },
    {"urows",               db_urows                },
    {"nrows",               db_nrows                },

    {"exec",                db_exec                 },
    {"execute",             db_exec                 },
    {"close",               db_close                },
    {"close_vm",            db_close_vm             },

    {"__tostring",          db_tostring             },
    {"__gc",                db_gc                   },

    {NULL, NULL}
};

static const luaL_Reg vmlib[] = {
    {"isopen",              dbvm_isopen             },

    {"step",                dbvm_step               },
    {"reset",               dbvm_reset              },
    {"finalize",            dbvm_finalize           },

    {"columns",             dbvm_columns            },

    {"bind",                dbvm_bind               },
    {"bind_values",         dbvm_bind_values        },
    {"bind_names",          dbvm_bind_names         },
    {"bind_blob",           dbvm_bind_blob          },
    {"bind_parameter_count",dbvm_bind_parameter_count},
    {"bind_parameter_name", dbvm_bind_parameter_name},

    {"get_value",           dbvm_get_value          },
    {"get_values",          dbvm_get_values         },
    {"get_name",            dbvm_get_name           },
    {"get_names",           dbvm_get_names          },
    {"get_type",            dbvm_get_type           },
    {"get_types",           dbvm_get_types          },
    {"get_uvalues",         dbvm_get_uvalues        },
    {"get_unames",          dbvm_get_unames         },
    {"get_utypes",          dbvm_get_utypes         },

    {"get_named_values",    dbvm_get_named_values   },
    {"get_named_types",     dbvm_get_named_types    },

    {"rows",                dbvm_rows               },
    {"urows",               dbvm_urows              },
    {"nrows",               dbvm_nrows              },

    /* compatibility names (added by request) */
    {"idata",               dbvm_get_values         },
    {"inames",              dbvm_get_names          },
    {"itypes",              dbvm_get_types          },
    {"data",                dbvm_get_named_values   },
    {"type",                dbvm_get_named_types    },

    {"__tostring",          dbvm_tostring           },
    {"__gc",                dbvm_gc                 },

    { NULL, NULL }
};

static const luaL_Reg ctxlib[] = {
    {"user_data",               lcontext_user_data              },

    {"get_aggregate_data",      lcontext_get_aggregate_context  },
    {"set_aggregate_data",      lcontext_set_aggregate_context  },
    {"aggregate_count",         lcontext_aggregate_count        },

    {"result",                  lcontext_result                 },
    {"result_null",             lcontext_result_null            },
    {"result_number",           lcontext_result_double          },
    {"result_double",           lcontext_result_double          },
    {"result_int",              lcontext_result_int             },
    {"result_text",             lcontext_result_text            },
    {"result_blob",             lcontext_result_blob            },
    {"result_error",            lcontext_result_error           },

    {"__tostring",              lcontext_tostring               },
    {NULL, NULL}
};

static const luaL_Reg sqlitelib[] = {
    {"version",         lsqlite_version         },
    {"complete",        lsqlite_complete        },
#ifndef WIN32
    {"temp_directory",  lsqlite_temp_directory  },
#endif
    {"open",            lsqlite_open            },
    {"open_memory",     lsqlite_open_memory     },

    {"__newindex",      lsqlite_newindex        },
    {NULL, NULL}
};

static void create_meta(lua_State *L, const char *name, const luaL_Reg *lib) {
    luaL_newmetatable(L, name);
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);               /* push metatable */
    lua_rawset(L, -3);                  /* metatable.__index = metatable */

    /* register metatable functions */
    luaL_openlib(L, NULL, lib, 0);

    /* remove metatable from stack */
    lua_pop(L, 1);
}

LUALIB_API int luaopen_lsqlite3(lua_State *L) {
    create_meta(L, sqlite_meta, dblib);
    create_meta(L, sqlite_vm_meta, vmlib);
    create_meta(L, sqlite_ctx_meta, ctxlib);

    luaL_getmetatable(L, sqlite_ctx_meta);
    sqlite_ctx_meta_ref = luaL_ref(L, LUA_REGISTRYINDEX);

    /* register (local) sqlite metatable */
    luaL_register(L, "sqlite3", sqlitelib);

    {
        int i = 0;
        /* add constants to global table */
        while (sqlite_constants[i].name) {
            lua_pushstring(L, sqlite_constants[i].name);
            lua_pushnumber(L, sqlite_constants[i].value);
            lua_rawset(L, -3);
            ++i;
        }
    }

    /* set sqlite's metatable to itself - set as readonly (__newindex) */
    lua_pushvalue(L, -1);
    lua_setmetatable(L, -2);

    return 1;
}
