/*=========================================================================*\
* Simple exception support
* LuaSocket toolkit
\*=========================================================================*/
#include <stdio.h>

#include "lua.h"
#include "lauxlib.h"

#include "except.h"

/*=========================================================================*\
* Internal function prototypes.
\*=========================================================================*/
static int global_protect(lua_State *L);
static int global_newtry(lua_State *L);
static int protected_(lua_State *L);
static int finalize(lua_State *L);
static int do_nothing(lua_State *L);

/* except functions */
static luaL_Reg func[] = {
    {"newtry",    global_newtry},
    {"protect",   global_protect},
    {NULL,        NULL}
};

/*-------------------------------------------------------------------------*\
* Try factory
\*-------------------------------------------------------------------------*/
static void wrap(lua_State *L) {
    lua_newtable(L);
    lua_pushnumber(L, 1);
    lua_pushvalue(L, -3);
    lua_settable(L, -3);
    lua_insert(L, -2);
    lua_pop(L, 1);
}

static int finalize(lua_State *L) {
    if (!lua_toboolean(L, 1)) {
        lua_pushvalue(L, lua_upvalueindex(1));
        lua_pcall(L, 0, 0, 0);
        lua_settop(L, 2);
        wrap(L);
        lua_error(L);
        return 0;
    } else return lua_gettop(L);
}

static int do_nothing(lua_State *L) { 
    (void) L;
    return 0; 
}

static int global_newtry(lua_State *L) {
    lua_settop(L, 1);
    if (lua_isnil(L, 1)) lua_pushcfunction(L, do_nothing);
    lua_pushcclosure(L, finalize, 1);
    return 1;
}

/*-------------------------------------------------------------------------*\
* Protect factory
\*-------------------------------------------------------------------------*/
static int unwrap(lua_State *L) {
    if (lua_istable(L, -1)) {
        lua_pushnumber(L, 1);
        lua_gettable(L, -2);
        lua_pushnil(L);
        lua_insert(L, -2);
        return 1;
    } else return 0;
}

static int protected_(lua_State *L) {
    lua_pushvalue(L, lua_upvalueindex(1));
    lua_insert(L, 1);
    if (lua_pcall(L, lua_gettop(L) - 1, LUA_MULTRET, 0) != 0) {
        if (unwrap(L)) return 2;
        else lua_error(L);
        return 0;
    } else return lua_gettop(L);
}

static int global_protect(lua_State *L) {
    lua_pushcclosure(L, protected_, 1);
    return 1;
}

/*-------------------------------------------------------------------------*\
* Init module
\*-------------------------------------------------------------------------*/
int except_open(lua_State *L) {
#if LUA_VERSION_NUM > 501 && !defined(LUA_COMPAT_MODULE)
    luaL_setfuncs(L, func, 0);
#else
    luaL_openlib(L, NULL, func, 0);
#endif
    return 0;
}
