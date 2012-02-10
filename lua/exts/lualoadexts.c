
#include "lualoadexts.h"
 
// luasocket
#include "luasocket.h"
#include "mime.h"
#include "luasocketscripts.h"

// cjson
#include "lua_cjson.h"

static luaL_Reg luax_exts[] = {
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

void luax_loadexts(lua_State *L)
{
    luaL_Reg* lib = luax_exts;
    luaL_findtable(L, LUA_GLOBALSINDEX, "package.preload", sizeof(luax_exts)/sizeof(luax_exts[0])-1);
    for (; lib->func; lib++) {
        lua_pushstring(L, lib->name);
        lua_pushcfunction(L, lib->func);
        lua_rawset(L, -3);
    }
    lua_pop(L, 1);
}
