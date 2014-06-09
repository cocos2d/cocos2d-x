#ifndef OPTIONS_H
#define OPTIONS_H
/*=========================================================================*\
* Common option interface 
* LuaSocket toolkit
*
* This module provides a common interface to socket options, used mainly by
* modules UDP and TCP. 
\*=========================================================================*/

#include "lua.h"
#include "socket.h"

/* option registry */
typedef struct t_opt {
  const char *name;
  int (*func)(lua_State *L, p_socket ps);
} t_opt;
typedef t_opt *p_opt;

/* supported options for setoption */
int opt_set_dontroute(lua_State *L, p_socket ps);
int opt_set_broadcast(lua_State *L, p_socket ps);
int opt_set_reuseaddr(lua_State *L, p_socket ps);
int opt_set_tcp_nodelay(lua_State *L, p_socket ps);
int opt_set_keepalive(lua_State *L, p_socket ps);
int opt_set_linger(lua_State *L, p_socket ps);
int opt_set_reuseaddr(lua_State *L, p_socket ps);
int opt_set_reuseport(lua_State *L, p_socket ps);
int opt_set_ip_multicast_if(lua_State *L, p_socket ps);
int opt_set_ip_multicast_ttl(lua_State *L, p_socket ps);
int opt_set_ip_multicast_loop(lua_State *L, p_socket ps);
int opt_set_ip_add_membership(lua_State *L, p_socket ps);
int opt_set_ip_drop_membersip(lua_State *L, p_socket ps);
int opt_set_ip6_v6only(lua_State *L, p_socket ps);

/* supported options for getoption */
int opt_get_reuseaddr(lua_State *L, p_socket ps);
int opt_get_tcp_nodelay(lua_State *L, p_socket ps);
int opt_get_keepalive(lua_State *L, p_socket ps);
int opt_get_linger(lua_State *L, p_socket ps);
int opt_get_reuseaddr(lua_State *L, p_socket ps);
int opt_get_ip_multicast_loop(lua_State *L, p_socket ps);
int opt_get_ip_multicast_if(lua_State *L, p_socket ps);

/* invokes the appropriate option handler */
int opt_meth_setoption(lua_State *L, p_opt opt, p_socket ps);
int opt_meth_getoption(lua_State *L, p_opt opt, p_socket ps);

#endif
