//
//  lualoadexts.c
//  Mystic-Fish-Puzzle
//
//  Created by  on 11-10-3.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "lualoadexts.h"

// luasocket
#include "luasocket.h"
#include "mime.h"
#include "luasocketscripts.h"

static luaL_Reg luax_preload_list[] = {
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
    {NULL, NULL}
};

void luax_initpreload(lua_State *L)
{
    luaL_Reg* lib = luax_preload_list;
    luaL_findtable(L, LUA_GLOBALSINDEX, "package.preload", sizeof(luax_preload_list)/sizeof(luax_preload_list[0])-1);
    for (; lib->func; lib++) {
        lua_pushstring(L, lib->name);
        lua_pushcfunction(L, lib->func);
        lua_rawset(L, -3);
    }
    lua_pop(L, 1);
}
