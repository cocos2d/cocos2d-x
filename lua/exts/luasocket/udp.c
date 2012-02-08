/*=========================================================================*\
* UDP object 
* LuaSocket toolkit
*
* RCS ID: $Id: udp.c,v 1.29 2005/10/07 04:40:59 diego Exp $
\*=========================================================================*/
#include <string.h> 

#include "lua.h"
#include "lauxlib.h"

#include "auxiliar.h"
#include "socket.h"
#include "inet.h"
#include "options.h"
#include "udp.h"

/* min and max macros */
#ifndef MIN
#define MIN(x, y) ((x) < (y) ? x : y)
#endif 
#ifndef MAX
#define MAX(x, y) ((x) > (y) ? x : y)
#endif 

/*=========================================================================*\
* Internal function prototypes
\*=========================================================================*/
static int global_create(lua_State *L);
static int meth_send(lua_State *L);
static int meth_sendto(lua_State *L);
static int meth_receive(lua_State *L);
static int meth_receivefrom(lua_State *L);
static int meth_getsockname(lua_State *L);
static int meth_getpeername(lua_State *L);
static int meth_setsockname(lua_State *L);
static int meth_setpeername(lua_State *L);
static int meth_close(lua_State *L);
static int meth_setoption(lua_State *L);
static int meth_settimeout(lua_State *L);
static int meth_getfd(lua_State *L);
static int meth_setfd(lua_State *L);
static int meth_dirty(lua_State *L);

/* udp object methods */
static luaL_reg udp[] = {
    {"__gc",        meth_close},
    {"__tostring",  auxiliar_tostring},
    {"close",       meth_close},
    {"dirty",       meth_dirty},
    {"getfd",       meth_getfd},
    {"getpeername", meth_getpeername},
    {"getsockname", meth_getsockname},
    {"receive",     meth_receive},
    {"receivefrom", meth_receivefrom},
    {"send",        meth_send},
    {"sendto",      meth_sendto},
    {"setfd",       meth_setfd},
    {"setoption",   meth_setoption},
    {"setpeername", meth_setpeername},
    {"setsockname", meth_setsockname},
    {"settimeout",  meth_settimeout},
    {NULL,          NULL}
};

/* socket options */
static t_opt opt[] = {
    {"dontroute",          opt_dontroute},
    {"broadcast",          opt_broadcast},
    {"reuseaddr",          opt_reuseaddr},
    {"ip-multicast-ttl",   opt_ip_multicast_ttl},
    {"ip-multicast-loop",  opt_ip_multicast_loop},
    {"ip-add-membership",  opt_ip_add_membership},
    {"ip-drop-membership", opt_ip_drop_membersip},
    {NULL,          NULL}
};

/* functions in library namespace */
static luaL_reg func[] = {
    {"udp", global_create},
    {NULL, NULL}
};

/*-------------------------------------------------------------------------*\
* Initializes module
\*-------------------------------------------------------------------------*/
int udp_open(lua_State *L)
{
    /* create classes */
    auxiliar_newclass(L, "udp{connected}", udp);
    auxiliar_newclass(L, "udp{unconnected}", udp);
    /* create class groups */
    auxiliar_add2group(L, "udp{connected}",   "udp{any}");
    auxiliar_add2group(L, "udp{unconnected}", "udp{any}");
    auxiliar_add2group(L, "udp{connected}",   "select{able}");
    auxiliar_add2group(L, "udp{unconnected}", "select{able}");
    /* define library functions */
    luaL_openlib(L, NULL, func, 0); 
    return 0;
}

/*=========================================================================*\
* Lua methods
\*=========================================================================*/
const char *udp_strerror(int err) {
    /* a 'closed' error on an unconnected means the target address was not
     * accepted by the transport layer */
    if (err == IO_CLOSED) return "refused";
    else return socket_strerror(err);
}

/*-------------------------------------------------------------------------*\
* Send data through connected udp socket
\*-------------------------------------------------------------------------*/
static int meth_send(lua_State *L) {
    p_udp udp = (p_udp) auxiliar_checkclass(L, "udp{connected}", 1);
    p_timeout tm = &udp->tm;
    size_t count, sent = 0;
    int err;
    const char *data = luaL_checklstring(L, 2, &count);
    timeout_markstart(tm);
    err = socket_send(&udp->sock, data, count, &sent, tm);
    if (err != IO_DONE) {
        lua_pushnil(L);
        lua_pushstring(L, udp_strerror(err));
        return 2;
    }
    lua_pushnumber(L, sent);
    return 1;
}

/*-------------------------------------------------------------------------*\
* Send data through unconnected udp socket
\*-------------------------------------------------------------------------*/
static int meth_sendto(lua_State *L) {
    p_udp udp = (p_udp) auxiliar_checkclass(L, "udp{unconnected}", 1);
    size_t count, sent = 0;
    const char *data = luaL_checklstring(L, 2, &count);
    const char *ip = luaL_checkstring(L, 3);
    unsigned short port = (unsigned short) luaL_checknumber(L, 4);
    p_timeout tm = &udp->tm;
    struct sockaddr_in addr;
    int err;
    memset(&addr, 0, sizeof(addr));
    if (!inet_aton(ip, &addr.sin_addr)) 
        luaL_argerror(L, 3, "invalid ip address");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    timeout_markstart(tm);
    err = socket_sendto(&udp->sock, data, count, &sent, 
            (SA *) &addr, sizeof(addr), tm);
    if (err != IO_DONE) {
        lua_pushnil(L);
        lua_pushstring(L, udp_strerror(err));
        return 2;
    }
    lua_pushnumber(L, sent);
    return 1;
}

/*-------------------------------------------------------------------------*\
* Receives data from a UDP socket
\*-------------------------------------------------------------------------*/
static int meth_receive(lua_State *L) {
    p_udp udp = (p_udp) auxiliar_checkgroup(L, "udp{any}", 1);
    char buffer[UDP_DATAGRAMSIZE];
    size_t got, count = (size_t) luaL_optnumber(L, 2, sizeof(buffer));
    int err;
    p_timeout tm = &udp->tm;
    count = MIN(count, sizeof(buffer));
    timeout_markstart(tm);
    err = socket_recv(&udp->sock, buffer, count, &got, tm);
    if (err != IO_DONE) {
        lua_pushnil(L);
        lua_pushstring(L, udp_strerror(err));
        return 2;
    }
    lua_pushlstring(L, buffer, got);
    return 1;
}

/*-------------------------------------------------------------------------*\
* Receives data and sender from a UDP socket
\*-------------------------------------------------------------------------*/
static int meth_receivefrom(lua_State *L) {
    p_udp udp = (p_udp) auxiliar_checkclass(L, "udp{unconnected}", 1);
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    char buffer[UDP_DATAGRAMSIZE];
    size_t got, count = (size_t) luaL_optnumber(L, 2, sizeof(buffer));
    int err;
    p_timeout tm = &udp->tm;
    timeout_markstart(tm);
    count = MIN(count, sizeof(buffer));
    err = socket_recvfrom(&udp->sock, buffer, count, &got, 
            (SA *) &addr, &addr_len, tm);
    if (err == IO_DONE) {
        lua_pushlstring(L, buffer, got);
        lua_pushstring(L, inet_ntoa(addr.sin_addr));
        lua_pushnumber(L, ntohs(addr.sin_port));
        return 3;
    } else {
        lua_pushnil(L);
        lua_pushstring(L, udp_strerror(err));
        return 2;
    }
}

/*-------------------------------------------------------------------------*\
* Select support methods
\*-------------------------------------------------------------------------*/
static int meth_getfd(lua_State *L) {
    p_udp udp = (p_udp) auxiliar_checkgroup(L, "udp{any}", 1);
    lua_pushnumber(L, (int) udp->sock);
    return 1;
}

/* this is very dangerous, but can be handy for those that are brave enough */
static int meth_setfd(lua_State *L) {
    p_udp udp = (p_udp) auxiliar_checkgroup(L, "udp{any}", 1);
    udp->sock = (t_socket) luaL_checknumber(L, 2);
    return 0;
}

static int meth_dirty(lua_State *L) {
    p_udp udp = (p_udp) auxiliar_checkgroup(L, "udp{any}", 1);
    (void) udp;
    lua_pushboolean(L, 0);
    return 1;
}

/*-------------------------------------------------------------------------*\
* Just call inet methods
\*-------------------------------------------------------------------------*/
static int meth_getpeername(lua_State *L) {
    p_udp udp = (p_udp) auxiliar_checkclass(L, "udp{connected}", 1);
    return inet_meth_getpeername(L, &udp->sock);
}

static int meth_getsockname(lua_State *L) {
    p_udp udp = (p_udp) auxiliar_checkgroup(L, "udp{any}", 1);
    return inet_meth_getsockname(L, &udp->sock);
}

/*-------------------------------------------------------------------------*\
* Just call option handler
\*-------------------------------------------------------------------------*/
static int meth_setoption(lua_State *L) {
    p_udp udp = (p_udp) auxiliar_checkgroup(L, "udp{any}", 1);
    return opt_meth_setoption(L, opt, &udp->sock);
}

/*-------------------------------------------------------------------------*\
* Just call tm methods
\*-------------------------------------------------------------------------*/
static int meth_settimeout(lua_State *L) {
    p_udp udp = (p_udp) auxiliar_checkgroup(L, "udp{any}", 1);
    return timeout_meth_settimeout(L, &udp->tm);
}

/*-------------------------------------------------------------------------*\
* Turns a master udp object into a client object.
\*-------------------------------------------------------------------------*/
static int meth_setpeername(lua_State *L) {
    p_udp udp = (p_udp) auxiliar_checkgroup(L, "udp{any}", 1);
    p_timeout tm = &udp->tm;
    const char *address =  luaL_checkstring(L, 2);
    int connecting = strcmp(address, "*");
    unsigned short port = connecting ? 
        (unsigned short) luaL_checknumber(L, 3) : 
        (unsigned short) luaL_optnumber(L, 3, 0);
    const char *err = inet_tryconnect(&udp->sock, address, port, tm);
    if (err) {
        lua_pushnil(L);
        lua_pushstring(L, err);
        return 2;
    }
    /* change class to connected or unconnected depending on address */
    if (connecting) auxiliar_setclass(L, "udp{connected}", 1);
    else auxiliar_setclass(L, "udp{unconnected}", 1);
    lua_pushnumber(L, 1);
    return 1;
}

/*-------------------------------------------------------------------------*\
* Closes socket used by object 
\*-------------------------------------------------------------------------*/
static int meth_close(lua_State *L) {
    p_udp udp = (p_udp) auxiliar_checkgroup(L, "udp{any}", 1);
    socket_destroy(&udp->sock);
    lua_pushnumber(L, 1);
    return 1;
}

/*-------------------------------------------------------------------------*\
* Turns a master object into a server object
\*-------------------------------------------------------------------------*/
static int meth_setsockname(lua_State *L) {
    p_udp udp = (p_udp) auxiliar_checkclass(L, "udp{unconnected}", 1);
    const char *address =  luaL_checkstring(L, 2);
    unsigned short port = (unsigned short) luaL_checknumber(L, 3);
    const char *err = inet_trybind(&udp->sock, address, port);
    if (err) {
        lua_pushnil(L);
        lua_pushstring(L, err);
        return 2;
    }
    lua_pushnumber(L, 1);
    return 1;
}

/*=========================================================================*\
* Library functions
\*=========================================================================*/
/*-------------------------------------------------------------------------*\
* Creates a master udp object 
\*-------------------------------------------------------------------------*/
static int global_create(lua_State *L) {
    t_socket sock;
    const char *err = inet_trycreate(&sock, SOCK_DGRAM);
    /* try to allocate a system socket */
    if (!err) { 
        /* allocate tcp object */
        p_udp udp = (p_udp) lua_newuserdata(L, sizeof(t_udp));
        auxiliar_setclass(L, "udp{unconnected}", -1);
        /* initialize remaining structure fields */
        socket_setnonblocking(&sock);
        udp->sock = sock;
        timeout_init(&udp->tm, -1, -1);
        return 1;
    } else {
        lua_pushnil(L);
        lua_pushstring(L, err);
        return 2;
    }
}
