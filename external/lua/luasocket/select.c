/*=========================================================================*\
* Select implementation
* LuaSocket toolkit
\*=========================================================================*/
#include <string.h>

#include "lua.h"
#include "lauxlib.h"

#include "socket.h"
#include "timeout.h"
#include "select.h"

/*=========================================================================*\
* Internal function prototypes.
\*=========================================================================*/
static t_socket getfd(lua_State *L);
static int dirty(lua_State *L);
static void collect_fd(lua_State *L, int tab, int itab, 
        fd_set *set, t_socket *max_fd);
static int check_dirty(lua_State *L, int tab, int dtab, fd_set *set);
static void return_fd(lua_State *L, fd_set *set, t_socket max_fd, 
        int itab, int tab, int start);
static void make_assoc(lua_State *L, int tab);
static int global_select(lua_State *L);

/* functions in library namespace */
static luaL_Reg func[] = {
    {"select", global_select},
    {NULL,     NULL}
};

/*=========================================================================*\
* Exported functions
\*=========================================================================*/
/*-------------------------------------------------------------------------*\
* Initializes module
\*-------------------------------------------------------------------------*/
int select_open(lua_State *L) {
    lua_pushstring(L, "_SETSIZE");
    lua_pushnumber(L, FD_SETSIZE);
    lua_rawset(L, -3);
#if LUA_VERSION_NUM > 501 && !defined(LUA_COMPAT_MODULE)
    luaL_setfuncs(L, func, 0);
#else
    luaL_openlib(L, NULL, func, 0);
#endif
    return 0;
}

/*=========================================================================*\
* Global Lua functions
\*=========================================================================*/
/*-------------------------------------------------------------------------*\
* Waits for a set of sockets until a condition is met or timeout.
\*-------------------------------------------------------------------------*/
static int global_select(lua_State *L) {
    int rtab, wtab, itab, ret, ndirty;
    t_socket max_fd = SOCKET_INVALID;
    fd_set rset, wset;
    t_timeout tm;
    double t = luaL_optnumber(L, 3, -1);
    FD_ZERO(&rset); FD_ZERO(&wset);
    lua_settop(L, 3);
    lua_newtable(L); itab = lua_gettop(L);
    lua_newtable(L); rtab = lua_gettop(L);
    lua_newtable(L); wtab = lua_gettop(L);
    collect_fd(L, 1, itab, &rset, &max_fd);
    collect_fd(L, 2, itab, &wset, &max_fd);
    ndirty = check_dirty(L, 1, rtab, &rset);
    t = ndirty > 0? 0.0: t;
    timeout_init(&tm, t, -1);
    timeout_markstart(&tm);
    ret = socket_select(max_fd+1, &rset, &wset, NULL, &tm);
    if (ret > 0 || ndirty > 0) {
        return_fd(L, &rset, max_fd+1, itab, rtab, ndirty);
        return_fd(L, &wset, max_fd+1, itab, wtab, 0);
        make_assoc(L, rtab);
        make_assoc(L, wtab);
        return 2;
    } else if (ret == 0) {
        lua_pushstring(L, "timeout");
        return 3;
    } else {
        luaL_error(L, "select failed");
        return 3;
    }
}

/*=========================================================================*\
* Internal functions
\*=========================================================================*/
static t_socket getfd(lua_State *L) {
    t_socket fd = SOCKET_INVALID;
    lua_pushstring(L, "getfd");
    lua_gettable(L, -2);
    if (!lua_isnil(L, -1)) {
        lua_pushvalue(L, -2);
        lua_call(L, 1, 1);
        if (lua_isnumber(L, -1)) {
            double numfd = lua_tonumber(L, -1); 
            fd = (numfd >= 0.0)? (t_socket) numfd: SOCKET_INVALID;
        }
    } 
    lua_pop(L, 1);
    return fd;
}

static int dirty(lua_State *L) {
    int is = 0;
    lua_pushstring(L, "dirty");
    lua_gettable(L, -2);
    if (!lua_isnil(L, -1)) {
        lua_pushvalue(L, -2);
        lua_call(L, 1, 1);
        is = lua_toboolean(L, -1);
    } 
    lua_pop(L, 1);
    return is;
}

static void collect_fd(lua_State *L, int tab, int itab, 
        fd_set *set, t_socket *max_fd) {
    int i = 1, n = 0;
    /* nil is the same as an empty table */
    if (lua_isnil(L, tab)) return;
    /* otherwise we need it to be a table */
    luaL_checktype(L, tab, LUA_TTABLE);
    for ( ;; ) {
        t_socket fd;
        lua_pushnumber(L, i);
        lua_gettable(L, tab);
        if (lua_isnil(L, -1)) {
            lua_pop(L, 1);
            break;
        }
        /* getfd figures out if this is a socket */
        fd = getfd(L);
        if (fd != SOCKET_INVALID) {
            /* make sure we don't overflow the fd_set */
#ifdef _WIN32
            if (n >= FD_SETSIZE) 
                luaL_argerror(L, tab, "too many sockets");
#else
            if (fd >= FD_SETSIZE) 
                luaL_argerror(L, tab, "descriptor too large for set size");
#endif
            FD_SET(fd, set);
            n++;
            /* keep track of the largest descriptor so far */
            if (*max_fd == SOCKET_INVALID || *max_fd < fd) 
                *max_fd = fd;
            /* make sure we can map back from descriptor to the object */
            lua_pushnumber(L, (lua_Number) fd);
            lua_pushvalue(L, -2);
            lua_settable(L, itab);
        }
        lua_pop(L, 1);
        i = i + 1;
    }
}

static int check_dirty(lua_State *L, int tab, int dtab, fd_set *set) {
    int ndirty = 0, i = 1;
    if (lua_isnil(L, tab)) 
        return 0;
    for ( ;; ) { 
        t_socket fd;
        lua_pushnumber(L, i);
        lua_gettable(L, tab);
        if (lua_isnil(L, -1)) {
            lua_pop(L, 1);
            break;
        }
        fd = getfd(L);
        if (fd != SOCKET_INVALID && dirty(L)) {
            lua_pushnumber(L, ++ndirty);
            lua_pushvalue(L, -2);
            lua_settable(L, dtab);
            FD_CLR(fd, set);
        }
        lua_pop(L, 1);
        i = i + 1;
    }
    return ndirty;
}

static void return_fd(lua_State *L, fd_set *set, t_socket max_fd, 
        int itab, int tab, int start) {
    t_socket fd;
    for (fd = 0; fd < max_fd; fd++) {
        if (FD_ISSET(fd, set)) {
            lua_pushnumber(L, ++start);
            lua_pushnumber(L, (lua_Number) fd);
            lua_gettable(L, itab);
            lua_settable(L, tab);
        }
    }
}

static void make_assoc(lua_State *L, int tab) {
    int i = 1, atab;
    lua_newtable(L); atab = lua_gettop(L);
    for ( ;; ) {
        lua_pushnumber(L, i);
        lua_gettable(L, tab);
        if (!lua_isnil(L, -1)) {
            lua_pushnumber(L, i);
            lua_pushvalue(L, -2);
            lua_settable(L, atab);
            lua_pushnumber(L, i);
            lua_settable(L, atab);
        } else {
            lua_pop(L, 1);
            break;
        }
        i = i+1;
    }
}

