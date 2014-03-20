/*=========================================================================*\
* LuaSocket toolkit
* Networking support for the Lua language
* Diego Nehab
* 26/11/1999
*
* This library is part of an  effort to progressively increase the network
* connectivity  of  the Lua  language.  The  Lua interface  to  networking
* functions follows the Sockets API  closely, trying to simplify all tasks
* involved in setting up both  client and server connections. The provided
* IO routines, however, follow the Lua  style, being very similar  to the
* standard Lua read and write functions.
\*=========================================================================*/

/*=========================================================================*\
* Standard include files
\*=========================================================================*/
#include "lua.h"
#include "lauxlib.h"


/*=========================================================================*\
* LuaSocket includes
\*=========================================================================*/
#include "luasocket.h"
#include "auxiliar.h"
#include "except.h"
#include "timeout.h"
#include "buffer.h"
#include "inet.h"
#include "tcp.h"
#include "udp.h"
#include "select.h"

/*-------------------------------------------------------------------------*\
* Internal function prototypes
\*-------------------------------------------------------------------------*/
static int global_skip(lua_State *L);
static int global_unload(lua_State *L);
static int base_open(lua_State *L);

/*-------------------------------------------------------------------------*\
* Modules and functions
\*-------------------------------------------------------------------------*/
static const luaL_Reg mod[] = {
    {"auxiliar", auxiliar_open},
    {"except", except_open},
    {"timeout", timeout_open},
    {"buffer", buffer_open},
    {"inet", inet_open},
    {"tcp", tcp_open},
    {"udp", udp_open},
    {"select", select_open},
    {NULL, NULL}
};

static luaL_Reg func[] = {
    {"skip",      global_skip},
    {"__unload",  global_unload},
    {NULL,        NULL}
};

/*-------------------------------------------------------------------------*\
* Skip a few arguments
\*-------------------------------------------------------------------------*/
static int global_skip(lua_State *L) {
    int amount = luaL_checkint(L, 1);
    int ret = lua_gettop(L) - amount - 1;
    return ret >= 0 ? ret : 0;
}

/*-------------------------------------------------------------------------*\
* Unloads the library
\*-------------------------------------------------------------------------*/
static int global_unload(lua_State *L) {
    (void) L;
    socket_close();
    return 0;
}

#if LUA_VERSION_NUM > 501
int luaL_typerror (lua_State *L, int narg, const char *tname) {
  const char *msg = lua_pushfstring(L, "%s expected, got %s",
                                    tname, luaL_typename(L, narg));
  return luaL_argerror(L, narg, msg);
}
#endif

/*-------------------------------------------------------------------------*\
* Setup basic stuff.
\*-------------------------------------------------------------------------*/
static int base_open(lua_State *L) {
    if (socket_open()) {
        /* export functions (and leave namespace table on top of stack) */
#if LUA_VERSION_NUM > 501 && !defined(LUA_COMPAT_MODULE)
        lua_newtable(L);
        luaL_setfuncs(L, func, 0);
#else
        luaL_openlib(L, "socket", func, 0);
#endif
#ifdef LUASOCKET_DEBUG
        lua_pushstring(L, "_DEBUG");
        lua_pushboolean(L, 1);
        lua_rawset(L, -3);
#endif
        /* make version string available to scripts */
        lua_pushstring(L, "_VERSION");
        lua_pushstring(L, LUASOCKET_VERSION);
        lua_rawset(L, -3);
        return 1;
    } else {
        lua_pushstring(L, "unable to initialize library");
        lua_error(L);
        return 0;
    }
}

/*-------------------------------------------------------------------------*\
* Initializes all library modules.
\*-------------------------------------------------------------------------*/
LUASOCKET_API int luaopen_socket_core(lua_State *L) {
    int i;
    base_open(L);
    for (i = 0; mod[i].name; i++) mod[i].func(L);
    return 1;
}
