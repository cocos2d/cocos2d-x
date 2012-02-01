#ifndef __LUASOCKETSCRIPTS__
#define __LUASOCKETSCRIPTS__

#include "lua.h"

#ifndef socket 
#define socket 
#endif

socket int luaopen_socket(lua_State *L);
socket int luaopen_socket_url(lua_State *L);
socket int luaopen_socket_tp(lua_State *L);
socket int luaopen_socket_smtp(lua_State *L);
socket int luaopen_socket_mime(lua_State *L);
socket int luaopen_socket_ltn12(lua_State *L);
socket int luaopen_socket_http(lua_State *L);
socket int luaopen_socket_ftp(lua_State *L);

#endif /* __LUASOCKETSCRIPTS__ */
