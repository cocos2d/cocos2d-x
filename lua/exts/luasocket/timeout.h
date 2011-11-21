#ifndef TIMEOUT_H
#define TIMEOUT_H
/*=========================================================================*\
* Timeout management functions
* LuaSocket toolkit
*
* RCS ID: $Id: timeout.h,v 1.14 2005/10/07 04:40:59 diego Exp $
\*=========================================================================*/
#include "lua.h"

/* timeout control structure */
typedef struct t_timeout_ {
    double block;          /* maximum time for blocking calls */
    double total;          /* total number of miliseconds for operation */
    double start;          /* time of start of operation */
} t_timeout;
typedef t_timeout *p_timeout;

int timeout_open(lua_State *L);
void timeout_init(p_timeout tm, double block, double total);
double timeout_get(p_timeout tm);
double timeout_getretry(p_timeout tm);
p_timeout timeout_markstart(p_timeout tm);
double timeout_getstart(p_timeout tm);
double timeout_gettime(void);
int timeout_meth_settimeout(lua_State *L, p_timeout tm);

#define timeout_iszero(tm)   ((tm)->block == 0.0)

#endif /* TIMEOUT_H */
