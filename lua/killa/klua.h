/* ========================================================================== */
/*   Lua to Killa                                                             */
/* -------------------------------------------------------------------------- */
/*   Copyright (c) 2012 Laurens Rodriguez Oscanoa.                            */
/*                                                                            */
/*   This code is licensed under the MIT license:                             */
/*   http://www.opensource.org/licenses/mit-license.php                       */
/* -------------------------------------------------------------------------- */

#ifndef KLUA_H_
#define KLUA_H_

#define KILLA_COMPAT_ALL

#define LUA_VERSION_NUM	    501

#include <killa.h>
#include <killalib.h>
#include <kauxlib.h>


#define LUA_ERRMEM          KILLA_ERRMEM
#define LUA_ERRRUN          KILLA_ERRRUN
#define LUA_ERRSYNTAX       KILLA_ERRSYNTAX
#define LUA_GCCOLLECT       KILLA_GCCOLLECT
#define LUA_MULTRET         KILLA_MULTRET
#define LUA_REFNIL          KILLA_REFNIL
#define LUA_REGISTRYINDEX   KILLA_REGISTRYINDEX
#define LUA_TBOOLEAN        KILLA_TBOOLEAN
#define LUA_TFUNCTION       KILLA_TFUNCTION
#define LUA_TLIGHTUSERDATA  KILLA_TLIGHTUSERDATA
#define LUA_TNONE           KILLA_TNONE
#define LUA_TNUMBER         KILLA_TNUMBER
#define LUA_TSTRING         KILLA_TSTRING
#define LUA_TTABLE          KILLA_TTABLE
#define LUA_TUSERDATA       KILLA_TUSERDATA

#define lua_call            killa_call
#define lua_close           killa_close
#define lua_concat          killa_concat
#define lua_createtable     killa_createtable
#define lua_CFunction       killa_CFunction
#define lua_error           killa_error
#define lua_gc              killa_gc
#define lua_getfenv         killa_getuservalue
#define lua_getfield        killa_getfield
#define lua_getglobal       killa_getglobal
#define lua_getmetatable    killa_getmetatable
#define lua_gettable        killa_gettable
#define lua_gettop          killa_gettop
#define lua_insert          killa_insert
#define lua_Integer         killa_Integer
#define lua_isboolean       killa_isboolean
#define lua_iscfunction     killa_iscfunction
#define lua_isfunction      killa_isfunction
#define lua_islightuserdata killa_islightuserdata
#define lua_islightuserdata killa_islightuserdata
#define lua_isnil           killa_isnull
#define lua_isnumber        killa_isnumber
#define lua_isnoneornil     killa_isnoneornull
#define lua_isstring        killa_isstring
#define lua_istable         killa_istable
#define lua_isuserdata      killa_isuserdata
#define lua_newtable        killa_newtable
#define lua_next            killa_next
#define lua_newuserdata     killa_newuserdata
#define lua_Number          killa_Number
#define lua_objlen          killa_objlen
#define lua_open            killaL_newstate
#define lua_pcall           killa_pcall
#define lua_pop             killa_pop
#define lua_pushboolean     killa_pushboolean
#define lua_pushcclosure    killa_pushcclosure
#define lua_pushcfunction   killa_pushcfunction
#define lua_pushfstring     killa_pushfstring
#define lua_pushinteger     killa_pushinteger
#define lua_pushlightuserdata   killa_pushlightuserdata
#define lua_pushliteral     killa_pushliteral
#define lua_pushlstring     killa_pushlstring
#define lua_pushnil         killa_pushnull
#define lua_pushnumber      killa_pushnumber
#define lua_pushstring      killa_pushstring
#define lua_pushvalue       killa_pushvalue
#define lua_rawequal        killa_rawequal
#define lua_rawget          killa_rawget
#define lua_rawgeti         killa_rawgeti
#define lua_rawset          killa_rawset
#define lua_rawseti         killa_rawseti
#define lua_replace         killa_replace
#define lua_remove          killa_remove
#define lua_setfenv         killa_setuservalue
#define lua_setfield        killa_setfield
#define lua_setglobal       killa_setglobal
#define lua_setmetatable    killa_setmetatable
#define lua_settable        killa_settable
#define lua_settop          killa_settop
#define lua_State           killa_State
#define lua_strlen          killa_strlen
#define lua_toboolean       killa_toboolean
#define lua_tocfunction     killa_tocfunction
#define lua_tointeger       killa_tointeger
#define lua_tolstring       killa_tolstring
#define lua_tonumber        killa_tonumber
#define lua_tostring        killa_tostring
#define lua_touserdata      killa_touserdata
#define lua_type            killa_type
#define lua_typename        killa_typename
#define lua_upvalueindex    killa_upvalueindex

#define luaL_addlstring     killaL_addlstring
#define luaL_addstring      killaL_addstring
#define luaL_argcheck       killaL_argcheck
#define luaL_argerror       killaL_argerror
#define luaL_Buffer         killaL_Buffer
#define luaL_buffinit       killaL_buffinit
#define luaL_checkint       killaL_checkint
#define luaL_checklstring   killaL_checklstring
#define luaL_checkinteger   killaL_checkinteger
#define luaL_checknumber    killaL_checknumber
#define luaL_checkstring    killaL_checkstring
#define luaL_checkudata     killaL_checkudata
#define luaL_dofile         killaL_dofile
#define luaL_dostring       killaL_dostring
#define luaL_error          killaL_error
#define luaL_getmetafield   killaL_getmetafield
#define luaL_getmetatable   killaL_getmetatable
#define luaL_loadbuffer     killaL_loadbuffer
#define luaL_loadstring     killaL_loadstring
#define luaL_newmetatable   killaL_newmetatable
#define luaL_openlib        killaL_openlib
#define luaL_openlibs       killaL_openlibs
#define luaL_optint         killaL_optint
#define luaL_optlstring     killaL_optlstring
#define luaL_optnumber      killaL_optnumber
#define luaL_optstring      killaL_optstring
#define luaL_putchar        killaL_addchar
#define luaL_pushresult     killaL_pushresult
#define luaL_ref            killaL_ref
#define luaL_reg            killaL_Reg
#define luaL_Reg            killaL_Reg
#define luaL_register       killaL_register
#define luaL_typename       killaL_typename
#define luaL_typerror       killaL_typerror
#define luaL_unref          killaL_unref

#endif
