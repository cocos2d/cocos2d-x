/*=========================================================================*\
* UDP object
* LuaSocket toolkit
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
static int global_create6(lua_State *L);
static int meth_send(lua_State *L);
static int meth_sendto(lua_State *L);
static int meth_receive(lua_State *L);
static int meth_receivefrom(lua_State *L);
static int meth_getfamily(lua_State *L);
static int meth_getsockname(lua_State *L);
static int meth_getpeername(lua_State *L);
static int meth_setsockname(lua_State *L);
static int meth_setpeername(lua_State *L);
static int meth_close(lua_State *L);
static int meth_setoption(lua_State *L);
static int meth_getoption(lua_State *L);
static int meth_settimeout(lua_State *L);
static int meth_getfd(lua_State *L);
static int meth_setfd(lua_State *L);
static int meth_dirty(lua_State *L);

/* udp object methods */
static luaL_Reg udp_methods[] = {
    {"__gc",        meth_close},
    {"__tostring",  auxiliar_tostring},
    {"close",       meth_close},
    {"dirty",       meth_dirty},
    {"getfamily",   meth_getfamily},
    {"getfd",       meth_getfd},
    {"getpeername", meth_getpeername},
    {"getsockname", meth_getsockname},
    {"receive",     meth_receive},
    {"receivefrom", meth_receivefrom},
    {"send",        meth_send},
    {"sendto",      meth_sendto},
    {"setfd",       meth_setfd},
    {"setoption",   meth_setoption},
    {"getoption",   meth_getoption},
    {"setpeername", meth_setpeername},
    {"setsockname", meth_setsockname},
    {"settimeout",  meth_settimeout},
    {NULL,          NULL}
};

/* socket options for setoption */
static t_opt optset[] = {
    {"dontroute",          opt_set_dontroute},
    {"broadcast",          opt_set_broadcast},
    {"reuseaddr",          opt_set_reuseaddr},
    {"reuseport",          opt_set_reuseport},
    {"ip-multicast-if",    opt_set_ip_multicast_if},
    {"ip-multicast-ttl",   opt_set_ip_multicast_ttl},
    {"ip-multicast-loop",  opt_set_ip_multicast_loop},
    {"ip-add-membership",  opt_set_ip_add_membership},
    {"ip-drop-membership", opt_set_ip_drop_membersip},
    {"ipv6-v6only",        opt_set_ip6_v6only},
    {NULL,                 NULL}
};

/* socket options for getoption */
static t_opt optget[] = {
    {"ip-multicast-if",    opt_get_ip_multicast_if},
    {"ip-multicast-loop",  opt_get_ip_multicast_loop},
    {NULL,                 NULL}
};

/* functions in library namespace */
static luaL_Reg func[] = {
    {"udp", global_create},
    {"udp6", global_create6},
    {NULL, NULL}
};

/*-------------------------------------------------------------------------*\
* Initializes module
\*-------------------------------------------------------------------------*/
int udp_open(lua_State *L)
{
    /* create classes */
    auxiliar_newclass(L, "udp{connected}", udp_methods);
    auxiliar_newclass(L, "udp{unconnected}", udp_methods);
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
    lua_pushnumber(L, (lua_Number) sent);
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
    int err;
    switch (udp->family) {
	case PF_INET: {
	    struct sockaddr_in addr;
	    memset(&addr, 0, sizeof(addr));
	    if (!my_inet_pton(AF_INET, ip, &addr.sin_addr))
		luaL_argerror(L, 3, "invalid ip address");
	    addr.sin_family = AF_INET;
	    addr.sin_port = htons(port);
	    timeout_markstart(tm);
	    err = socket_sendto(&udp->sock, data, count, &sent,
		    (SA *) &addr, sizeof(addr), tm);
	    break;
	}
	case PF_INET6: {
	    struct sockaddr_in6 addr;
	    memset(&addr, 0, sizeof(addr));
	    if (!my_inet_pton(AF_INET6, ip, &addr.sin6_addr))
		luaL_argerror(L, 3, "invalid ip address");
	    addr.sin6_family = AF_INET6;
	    addr.sin6_port = htons(port);
	    timeout_markstart(tm);
	    err = socket_sendto(&udp->sock, data, count, &sent,
		    (SA *) &addr, sizeof(addr), tm);
	    break;
	}
	default:
            lua_pushnil(L);
            lua_pushfstring(L, "unknown family %d", udp->family);
            return 2;
    }
    if (err != IO_DONE) {
        lua_pushnil(L);
        lua_pushstring(L, udp_strerror(err));
        return 2;
    }
    lua_pushnumber(L, (lua_Number) sent);
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
    /* Unlike TCP, recv() of zero is not closed, but a zero-length packet. */
    if (err == IO_CLOSED)
        err = IO_DONE;
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
    char buffer[UDP_DATAGRAMSIZE];
    size_t got, count = (size_t) luaL_optnumber(L, 2, sizeof(buffer));
    int err;
    p_timeout tm = &udp->tm;
    timeout_markstart(tm);
    count = MIN(count, sizeof(buffer));
    switch (udp->family) {
	case PF_INET: {
	    struct sockaddr_in addr;
	    socklen_t addr_len = sizeof(addr);
	    err = socket_recvfrom(&udp->sock, buffer, count, &got,
		    (SA *) &addr, &addr_len, tm);
	    /* Unlike TCP, recv() of zero is not closed, but a zero-length packet. */
	    if (err == IO_CLOSED)
		err = IO_DONE;
	    if (err == IO_DONE) {
		char addrstr[INET_ADDRSTRLEN];
		lua_pushlstring(L, buffer, got);
		if (!my_inet_ntop(AF_INET, &addr.sin_addr,
			addrstr, sizeof(addrstr))) {
		    lua_pushnil(L);
		    lua_pushstring(L, "invalid source address");
		    return 2;
		}
		lua_pushstring(L, addrstr);
		lua_pushnumber(L, ntohs(addr.sin_port));
		return 3;
	    }
	    break;
	}
	case PF_INET6: {
	    struct sockaddr_in6 addr;
	    socklen_t addr_len = sizeof(addr);
	    err = socket_recvfrom(&udp->sock, buffer, count, &got,
		    (SA *) &addr, &addr_len, tm);
	    /* Unlike TCP, recv() of zero is not closed, but a zero-length packet. */
	    if (err == IO_CLOSED)
		err = IO_DONE;
	    if (err == IO_DONE) {
		char addrstr[INET6_ADDRSTRLEN];
		lua_pushlstring(L, buffer, got);
		if (!my_inet_ntop(AF_INET6, &addr.sin6_addr,
			addrstr, sizeof(addrstr))) {
		    lua_pushnil(L);
		    lua_pushstring(L, "invalid source address");
		    return 2;
		}
		lua_pushstring(L, addrstr);
		lua_pushnumber(L, ntohs(addr.sin6_port));
		return 3;
	    }
	    break;
	}
    default:
        lua_pushnil(L);
        lua_pushfstring(L, "unknown family %d", udp->family);
        return 2;
    }
    lua_pushnil(L);
    lua_pushstring(L, udp_strerror(err));
    return 2;
}

/*-------------------------------------------------------------------------*\
* Returns family as string
\*-------------------------------------------------------------------------*/
static int meth_getfamily(lua_State *L)
{
    p_udp udp = (p_udp) auxiliar_checkgroup(L, "udp{any}", 1);
    if (udp->family == PF_INET6) {
        lua_pushliteral(L, "inet6");
        return 1;
    } else {
        lua_pushliteral(L, "inet4");
        return 1;
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
    return inet_meth_getpeername(L, &udp->sock, udp->family);
}

static int meth_getsockname(lua_State *L) {
    p_udp udp = (p_udp) auxiliar_checkgroup(L, "udp{any}", 1);
    return inet_meth_getsockname(L, &udp->sock, udp->family);
}

/*-------------------------------------------------------------------------*\
* Just call option handler
\*-------------------------------------------------------------------------*/
static int meth_setoption(lua_State *L) {
    p_udp udp = (p_udp) auxiliar_checkgroup(L, "udp{any}", 1);
    return opt_meth_setoption(L, optset, &udp->sock);
}

/*-------------------------------------------------------------------------*\
* Just call option handler
\*-------------------------------------------------------------------------*/
static int meth_getoption(lua_State *L) {
    p_udp udp = (p_udp) auxiliar_checkgroup(L, "udp{any}", 1);
    return opt_meth_getoption(L, optget, &udp->sock);
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
    const char *address = luaL_checkstring(L, 2);
    int connecting = strcmp(address, "*");
    const char *port = connecting? luaL_checkstring(L, 3): "0";
    struct addrinfo connecthints;
    const char *err;
    memset(&connecthints, 0, sizeof(connecthints));
    connecthints.ai_socktype = SOCK_DGRAM;
    /* make sure we try to connect only to the same family */
    connecthints.ai_family = udp->family;
    if (connecting) {
        err = inet_tryconnect(&udp->sock, address, port, tm, &connecthints);
        if (err) {
            lua_pushnil(L);
            lua_pushstring(L, err);
            return 2;
        }
        auxiliar_setclass(L, "udp{connected}", 1);
    } else {
        /* we ignore possible errors because Mac OS X always
         * returns EAFNOSUPPORT */
        inet_trydisconnect(&udp->sock, udp->family, tm);
        auxiliar_setclass(L, "udp{unconnected}", 1);
    }
    /* change class to connected or unconnected depending on address */
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
    const char *port = luaL_checkstring(L, 3);
    const char *err;
	struct addrinfo bindhints;
    memset(&bindhints, 0, sizeof(bindhints));
    bindhints.ai_socktype = SOCK_DGRAM;
    bindhints.ai_family = udp->family;
    bindhints.ai_flags = AI_PASSIVE;
    err = inet_trybind(&udp->sock, address, port, &bindhints);
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
static int udp_create(lua_State *L, int family) {
    t_socket sock;
    const char *err = inet_trycreate(&sock, family, SOCK_DGRAM);
    /* try to allocate a system socket */
    if (!err) {
        /* allocate udp object */
        p_udp udp = (p_udp) lua_newuserdata(L, sizeof(t_udp));
        auxiliar_setclass(L, "udp{unconnected}", -1);
        /* initialize remaining structure fields */
        socket_setnonblocking(&sock);
        if (family == PF_INET6) {
            int yes = 1;
            setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY,
                (void *)&yes, sizeof(yes));
        }
        udp->sock = sock;
        timeout_init(&udp->tm, -1, -1);
        udp->family = family;
        return 1;
    } else {
        lua_pushnil(L);
        lua_pushstring(L, err);
        return 2;
    }
}

static int global_create(lua_State *L) {
	return udp_create(L, AF_INET);
}

static int global_create6(lua_State *L) {
	return udp_create(L, AF_INET6);
}
