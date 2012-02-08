#ifndef UDP_H
#define UDP_H
/*=========================================================================*\
* UDP object
* LuaSocket toolkit
*
* The udp.h module provides LuaSocket with support for UDP protocol
* (AF_INET, SOCK_DGRAM).
*
* Two classes are defined: connected and unconnected. UDP objects are
* originally unconnected. They can be "connected" to a given address 
* with a call to the setpeername function. The same function can be used to
* break the connection.
*
* RCS ID: $Id: udp.h,v 1.10 2005/10/07 04:40:59 diego Exp $
\*=========================================================================*/
#include "lua.h"

#include "timeout.h"
#include "socket.h"

/* can't be larger than wsocket.c MAXCHUNK!!! */
#define UDP_DATAGRAMSIZE 8192

typedef struct t_udp_ {
    t_socket sock;
    t_timeout tm;
} t_udp;
typedef t_udp *p_udp;

int udp_open(lua_State *L);

#endif /* UDP_H */
