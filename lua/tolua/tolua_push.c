/* tolua: functions to push C values.
** Support code for Lua bindings.
** Written by Waldemar Celes
** TeCGraf/PUC-Rio
** Apr 2003
** $Id: $
*/

/* This code is free software; you can redistribute it and/or modify it.
** The software provided hereunder is on an "as is" basis, and
** the author has no obligation to provide maintenance, support, updates,
** enhancements, or modifications.
*/

#include "tolua++.h"
#include "lauxlib.h"

#include <stdlib.h>

TOLUA_API void tolua_pushvalue (lua_State* L, int lo)
{
    lua_pushvalue(L,lo);
}

TOLUA_API void tolua_pushboolean (lua_State* L, int value)
{
    lua_pushboolean(L,value);
}

TOLUA_API void tolua_pushnumber (lua_State* L, lua_Number value)
{
    lua_pushnumber(L,value);
}

TOLUA_API void tolua_pushstring (lua_State* L, const char* value)
{
    if (value == NULL)
        lua_pushnil(L);
    else
        lua_pushstring(L,value);
}

TOLUA_API void tolua_pushuserdata (lua_State* L, void* value)
{
    if (value == NULL)
        lua_pushnil(L);
    else
        lua_pushlightuserdata(L,value);
}

TOLUA_API void tolua_pushusertype (lua_State* L, void* value, const char* type)
{
    if (value == NULL)
        lua_pushnil(L);
    else
    {        
        luaL_getmetatable(L, type);                                 /* stack: mt */
        if (lua_isnil(L, -1)) { /* NOT FOUND metatable */
            lua_pop(L, 1);
            return;
        }
        lua_pushstring(L,"tolua_ubox");
        lua_rawget(L,-2);                                           /* stack: mt ubox */
        if (lua_isnil(L, -1)) {
            lua_pop(L, 1);
            lua_pushstring(L, "tolua_ubox");
            lua_rawget(L, LUA_REGISTRYINDEX);
        };
        
        lua_pushlightuserdata(L,value);                             /* stack: mt ubox key<value> */
        lua_rawget(L,-2);                                           /* stack: mt ubox ubox[value] */
        
        if (lua_isnil(L,-1))
        {
            lua_pop(L,1);                                           /* stack: mt ubox */
            lua_pushlightuserdata(L,value);
            *(void**)lua_newuserdata(L,sizeof(void *)) = value;     /* stack: mt ubox value newud */
            lua_pushvalue(L,-1);                                    /* stack: mt ubox value newud newud */
            lua_insert(L,-4);                                       /* stack: mt newud ubox value newud */
            lua_rawset(L,-3);                  /* ubox[value] = newud, stack: mt newud ubox */
            lua_pop(L,1);                                           /* stack: mt newud */
            /*luaL_getmetatable(L,type);*/
            lua_pushvalue(L, -2);                                   /* stack: mt newud mt */
            lua_setmetatable(L,-2);                      /* update mt, stack: mt newud */

#ifdef LUA_VERSION_NUM
            lua_pushvalue(L, TOLUA_NOPEER);
            lua_setfenv(L, -2);
#endif
        }
        else
        {
            /* check the need of updating the metatable to a more specialized class */
            lua_insert(L,-2);                                       /* stack: mt ubox[u] ubox */
            lua_pop(L,1);                                           /* stack: mt ubox[u] */
            lua_pushstring(L,"tolua_super");
            lua_rawget(L,LUA_REGISTRYINDEX);                        /* stack: mt ubox[u] super */
            lua_getmetatable(L,-2);                                 /* stack: mt ubox[u] super mt */
            lua_rawget(L,-2);                                       /* stack: mt ubox[u] super super[mt] */
            if (lua_istable(L,-1))
            {
                lua_pushstring(L,type);                             /* stack: mt ubox[u] super super[mt] type */
                lua_rawget(L,-2);                                   /* stack: mt ubox[u] super super[mt] flag */
                if (lua_toboolean(L,-1) == 1)                       /* if true */
                {
                    lua_pop(L,3);                                   /* mt ubox[u]*/
                    lua_remove(L, -2);
                    return;
                }
            }
            /* type represents a more specilized type */
            /*luaL_getmetatable(L,type);             // stack: mt ubox[u] super super[mt] flag mt */
            lua_pushvalue(L, -5);					/* stack: mt ubox[u] super super[mt] flag mt */
            lua_setmetatable(L,-5);                /* stack: mt ubox[u] super super[mt] flag */
            lua_pop(L,3);                          /* stack: mt ubox[u] */
        }
        lua_remove(L, -2);	/* stack: ubox[u]*/
    }
}

TOLUA_API void tolua_pushusertype_and_takeownership (lua_State* L, void* value, const char* type)
{
    tolua_pushusertype(L,value,type);
    tolua_register_gc(L,lua_gettop(L));
}

TOLUA_API void tolua_pushfieldvalue (lua_State* L, int lo, int index, int v)
{
    lua_pushnumber(L,index);
    lua_pushvalue(L,v);
    lua_settable(L,lo);
}

TOLUA_API void tolua_pushfieldboolean (lua_State* L, int lo, int index, int v)
{
    lua_pushnumber(L,index);
    lua_pushboolean(L,v);
    lua_settable(L,lo);
}


TOLUA_API void tolua_pushfieldnumber (lua_State* L, int lo, int index, lua_Number v)
{
    lua_pushnumber(L,index);
    tolua_pushnumber(L,v);
    lua_settable(L,lo);
}

TOLUA_API void tolua_pushfieldstring (lua_State* L, int lo, int index, const char* v)
{
    lua_pushnumber(L,index);
    tolua_pushstring(L,v);
    lua_settable(L,lo);
}

TOLUA_API void tolua_pushfielduserdata (lua_State* L, int lo, int index, void* v)
{
    lua_pushnumber(L,index);
    tolua_pushuserdata(L,v);
    lua_settable(L,lo);
}

TOLUA_API void tolua_pushfieldusertype (lua_State* L, int lo, int index, void* v, const char* type)
{
    lua_pushnumber(L,index);
    tolua_pushusertype(L,v,type);
    lua_settable(L,lo);
}

TOLUA_API void tolua_pushfieldusertype_and_takeownership (lua_State* L, int lo, int index, void* v, const char* type)
{
    lua_pushnumber(L,index);
    tolua_pushusertype(L,v,type);
    tolua_register_gc(L,lua_gettop(L));
    lua_settable(L,lo);
}

