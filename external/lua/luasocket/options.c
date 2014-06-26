/*=========================================================================*\
* Common option interface 
* LuaSocket toolkit
\*=========================================================================*/
#include <string.h> 

#include "lauxlib.h"

#include "auxiliar.h"
#include "options.h"
#include "inet.h"


/*=========================================================================*\
* Internal functions prototypes
\*=========================================================================*/
static int opt_setmembership(lua_State *L, p_socket ps, int level, int name);
static int opt_ip6_setmembership(lua_State *L, p_socket ps, int level, int name);
static int opt_setboolean(lua_State *L, p_socket ps, int level, int name);
static int opt_getboolean(lua_State *L, p_socket ps, int level, int name);
static int opt_setint(lua_State *L, p_socket ps, int level, int name);
static int opt_getint(lua_State *L, p_socket ps, int level, int name);
static int opt_set(lua_State *L, p_socket ps, int level, int name, 
        void *val, int len);
static int opt_get(lua_State *L, p_socket ps, int level, int name, 
        void *val, int* len);

/*=========================================================================*\
* Exported functions
\*=========================================================================*/
/*-------------------------------------------------------------------------*\
* Calls appropriate option handler
\*-------------------------------------------------------------------------*/
int opt_meth_setoption(lua_State *L, p_opt opt, p_socket ps)
{
    const char *name = luaL_checkstring(L, 2);      /* obj, name, ... */
    while (opt->name && strcmp(name, opt->name))
        opt++;
    if (!opt->func) {
        char msg[45];
        sprintf(msg, "unsupported option `%.35s'", name);
        luaL_argerror(L, 2, msg);
    }
    return opt->func(L, ps);
}

int opt_meth_getoption(lua_State *L, p_opt opt, p_socket ps)
{
    const char *name = luaL_checkstring(L, 2);      /* obj, name, ... */
    while (opt->name && strcmp(name, opt->name))
        opt++;
    if (!opt->func) {
        char msg[45];
        sprintf(msg, "unsupported option `%.35s'", name);
        luaL_argerror(L, 2, msg);
    }
    return opt->func(L, ps);
}

/* enables reuse of local address */
int opt_set_reuseaddr(lua_State *L, p_socket ps)
{
    return opt_setboolean(L, ps, SOL_SOCKET, SO_REUSEADDR); 
}

int opt_get_reuseaddr(lua_State *L, p_socket ps)
{
    return opt_getboolean(L, ps, SOL_SOCKET, SO_REUSEADDR); 
}

/* enables reuse of local port */
int opt_set_reuseport(lua_State *L, p_socket ps)
{
    return opt_setboolean(L, ps, SOL_SOCKET, SO_REUSEPORT); 
}

int opt_get_reuseport(lua_State *L, p_socket ps)
{
    return opt_getboolean(L, ps, SOL_SOCKET, SO_REUSEPORT); 
}

/* disables the Naggle algorithm */
int opt_set_tcp_nodelay(lua_State *L, p_socket ps)
{
    return opt_setboolean(L, ps, IPPROTO_TCP, TCP_NODELAY); 
}

int opt_get_tcp_nodelay(lua_State *L, p_socket ps)
{
    return opt_getboolean(L, ps, IPPROTO_TCP, TCP_NODELAY);
}

int opt_set_keepalive(lua_State *L, p_socket ps)
{
    return opt_setboolean(L, ps, SOL_SOCKET, SO_KEEPALIVE); 
}

int opt_get_keepalive(lua_State *L, p_socket ps)
{
    return opt_getboolean(L, ps, SOL_SOCKET, SO_KEEPALIVE); 
}

int opt_set_dontroute(lua_State *L, p_socket ps)
{
    return opt_setboolean(L, ps, SOL_SOCKET, SO_DONTROUTE);
}

int opt_set_broadcast(lua_State *L, p_socket ps)
{
    return opt_setboolean(L, ps, SOL_SOCKET, SO_BROADCAST);
}

int opt_set_ip6_unicast_hops(lua_State *L, p_socket ps)
{
  return opt_setint(L, ps, IPPROTO_IPV6, IPV6_UNICAST_HOPS);
}

int opt_get_ip6_unicast_hops(lua_State *L, p_socket ps)
{
  return opt_getint(L, ps, IPPROTO_IPV6, IPV6_UNICAST_HOPS);
}

int opt_set_ip6_multicast_hops(lua_State *L, p_socket ps)
{
  return opt_setint(L, ps, IPPROTO_IPV6, IPV6_MULTICAST_HOPS);
}

int opt_get_ip6_multicast_hops(lua_State *L, p_socket ps)
{
  return opt_getint(L, ps, IPPROTO_IPV6, IPV6_MULTICAST_HOPS);
}

int opt_set_ip_multicast_loop(lua_State *L, p_socket ps)
{
    return opt_setboolean(L, ps, IPPROTO_IP, IP_MULTICAST_LOOP);
}

int opt_get_ip_multicast_loop(lua_State *L, p_socket ps)
{
    return opt_getboolean(L, ps, IPPROTO_IP, IP_MULTICAST_LOOP);
}

int opt_set_ip6_multicast_loop(lua_State *L, p_socket ps)
{
    return opt_setboolean(L, ps, IPPROTO_IPV6, IPV6_MULTICAST_LOOP);
}

int opt_get_ip6_multicast_loop(lua_State *L, p_socket ps)
{
    return opt_getboolean(L, ps, IPPROTO_IPV6, IPV6_MULTICAST_LOOP);
}

int opt_set_linger(lua_State *L, p_socket ps)
{
    struct linger li;                      /* obj, name, table */
    if (!lua_istable(L, 3)) auxiliar_typeerror(L,3,lua_typename(L, LUA_TTABLE));
    lua_pushstring(L, "on");
    lua_gettable(L, 3);
    if (!lua_isboolean(L, -1)) 
        luaL_argerror(L, 3, "boolean 'on' field expected");
    li.l_onoff = (u_short) lua_toboolean(L, -1);
    lua_pushstring(L, "timeout");
    lua_gettable(L, 3);
    if (!lua_isnumber(L, -1)) 
        luaL_argerror(L, 3, "number 'timeout' field expected");
    li.l_linger = (u_short) lua_tonumber(L, -1);
    return opt_set(L, ps, SOL_SOCKET, SO_LINGER, (char *) &li, sizeof(li));
}

int opt_get_linger(lua_State *L, p_socket ps)
{
    struct linger li;                      /* obj, name */
    int len = sizeof(li);
    int err = opt_get(L, ps, SOL_SOCKET, SO_LINGER, (char *) &li, &len);
    if (err)
        return err;
    lua_newtable(L);
    lua_pushboolean(L, li.l_onoff);
    lua_setfield(L, -2, "on");
    lua_pushinteger(L, li.l_linger);
    lua_setfield(L, -2, "timeout");
    return 1;
}

int opt_set_ip_multicast_ttl(lua_State *L, p_socket ps)
{
    return opt_setint(L, ps, IPPROTO_IP, IP_MULTICAST_TTL);
}

int opt_set_ip_multicast_if(lua_State *L, p_socket ps)
{
    const char *address = luaL_checkstring(L, 3);    /* obj, name, ip */
    struct in_addr val;
    val.s_addr = htonl(INADDR_ANY);
    if (strcmp(address, "*") && !inet_aton(address, &val))
        luaL_argerror(L, 3, "ip expected");
    return opt_set(L, ps, IPPROTO_IP, IP_MULTICAST_IF, 
        (char *) &val, sizeof(val));
}

int opt_get_ip_multicast_if(lua_State *L, p_socket ps)
{
    struct in_addr val;
    socklen_t len = sizeof(val);
    if (getsockopt(*ps, IPPROTO_IP, IP_MULTICAST_IF, (char *) &val, &len) < 0) {
        lua_pushnil(L);
        lua_pushstring(L, "getsockopt failed");
        return 2;
    }
    lua_pushstring(L, inet_ntoa(val));
    return 1;
}

int opt_set_ip_add_membership(lua_State *L, p_socket ps)
{
    return opt_setmembership(L, ps, IPPROTO_IP, IP_ADD_MEMBERSHIP);
}

int opt_set_ip_drop_membersip(lua_State *L, p_socket ps)
{
    return opt_setmembership(L, ps, IPPROTO_IP, IP_DROP_MEMBERSHIP);
}

int opt_set_ip6_add_membership(lua_State *L, p_socket ps)
{
    return opt_ip6_setmembership(L, ps, IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP);
}

int opt_set_ip6_drop_membersip(lua_State *L, p_socket ps)
{
    return opt_ip6_setmembership(L, ps, IPPROTO_IPV6, IPV6_DROP_MEMBERSHIP);
}

int opt_get_ip6_v6only(lua_State *L, p_socket ps)
{
    return opt_getboolean(L, ps, IPPROTO_IPV6, IPV6_V6ONLY);
}

int opt_set_ip6_v6only(lua_State *L, p_socket ps)
{
    return opt_setboolean(L, ps, IPPROTO_IPV6, IPV6_V6ONLY);
}

/*=========================================================================*\
* Auxiliar functions
\*=========================================================================*/
static int opt_setmembership(lua_State *L, p_socket ps, int level, int name)
{
    struct ip_mreq val;                   /* obj, name, table */
    if (!lua_istable(L, 3)) auxiliar_typeerror(L,3,lua_typename(L, LUA_TTABLE));
    lua_pushstring(L, "multiaddr");
    lua_gettable(L, 3);
    if (!lua_isstring(L, -1)) 
        luaL_argerror(L, 3, "string 'multiaddr' field expected");
    if (!inet_aton(lua_tostring(L, -1), &val.imr_multiaddr)) 
        luaL_argerror(L, 3, "invalid 'multiaddr' ip address");
    lua_pushstring(L, "interface");
    lua_gettable(L, 3);
    if (!lua_isstring(L, -1)) 
        luaL_argerror(L, 3, "string 'interface' field expected");
    val.imr_interface.s_addr = htonl(INADDR_ANY);
    if (strcmp(lua_tostring(L, -1), "*") &&
            !inet_aton(lua_tostring(L, -1), &val.imr_interface)) 
        luaL_argerror(L, 3, "invalid 'interface' ip address");
    return opt_set(L, ps, level, name, (char *) &val, sizeof(val));
}

static int opt_ip6_setmembership(lua_State *L, p_socket ps, int level, int name)
{
    struct ipv6_mreq val;                   /* obj, opt-name, table */
    memset(&val, 0, sizeof(val));
    if (!lua_istable(L, 3)) auxiliar_typeerror(L,3,lua_typename(L, LUA_TTABLE));
    lua_pushstring(L, "multiaddr");
    lua_gettable(L, 3);
    if (!lua_isstring(L, -1)) 
        luaL_argerror(L, 3, "string 'multiaddr' field expected");
    if (!inet_pton(AF_INET6, lua_tostring(L, -1), &val.ipv6mr_multiaddr)) 
        luaL_argerror(L, 3, "invalid 'multiaddr' ip address");
    lua_pushstring(L, "interface");
    lua_gettable(L, 3);
    /* By default we listen to interface on default route
     * (sigh). However, interface= can override it. We should 
     * support either number, or name for it. Waiting for
     * windows port of if_nametoindex */
    if (!lua_isnil(L, -1)) {
        if (lua_isnumber(L, -1)) {
            val.ipv6mr_interface = (unsigned int) lua_tonumber(L, -1);
        } else
          luaL_argerror(L, -1, "number 'interface' field expected");
    }
    return opt_set(L, ps, level, name, (char *) &val, sizeof(val));
}

static 
int opt_get(lua_State *L, p_socket ps, int level, int name, void *val, int* len)
{
    socklen_t socklen = *len;
    if (getsockopt(*ps, level, name, (char *) val, &socklen) < 0) {
        lua_pushnil(L);
        lua_pushstring(L, "getsockopt failed");
        return 2;
    }
    *len = socklen;
    return 0;
}

static 
int opt_set(lua_State *L, p_socket ps, int level, int name, void *val, int len)
{
    if (setsockopt(*ps, level, name, (char *) val, len) < 0) {
        lua_pushnil(L);
        lua_pushstring(L, "setsockopt failed");
        return 2;
    }
    lua_pushnumber(L, 1);
    return 1;
}

static int opt_getboolean(lua_State *L, p_socket ps, int level, int name)
{
    int val = 0;
    int len = sizeof(val);
    int err = opt_get(L, ps, level, name, (char *) &val, &len);
    if (err)
        return err;
    lua_pushboolean(L, val);
    return 1;
}

int opt_get_error(lua_State *L, p_socket ps)
{
    int val = 0;
    socklen_t len = sizeof(val);
    if (getsockopt(*ps, SOL_SOCKET, SO_ERROR, (char *) &val, &len) < 0) {
        lua_pushnil(L);
        lua_pushstring(L, "getsockopt failed");
        return 2;
    }
    lua_pushstring(L, socket_strerror(val));
    return 1;
}

static int opt_setboolean(lua_State *L, p_socket ps, int level, int name)
{
    int val = auxiliar_checkboolean(L, 3);             /* obj, name, bool */
    return opt_set(L, ps, level, name, (char *) &val, sizeof(val));
}

static int opt_getint(lua_State *L, p_socket ps, int level, int name)
{
    int val = 0;
    int len = sizeof(val);
    int err = opt_get(L, ps, level, name, (char *) &val, &len);
    if (err)
        return err;
    lua_pushnumber(L, val);
    return 1;
}

static int opt_setint(lua_State *L, p_socket ps, int level, int name)
{
    int val = (int) lua_tonumber(L, 3);             /* obj, name, int */
    return opt_set(L, ps, level, name, (char *) &val, sizeof(val));
}
