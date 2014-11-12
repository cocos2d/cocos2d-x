#ifndef BUF_H
#define BUF_H 
/*=========================================================================*\
* Input/Output interface for Lua programs
* LuaSocket toolkit
*
* Line patterns require buffering. Reading one character at a time involves
* too many system calls and is very slow. This module implements the
* LuaSocket interface for input/output on connected objects, as seen by 
* Lua programs. 
*
* Input is buffered. Output is *not* buffered because there was no simple
* way of making sure the buffered output data would ever be sent.
*
* The module is built on top of the I/O abstraction defined in io.h and the
* timeout management is done with the timeout.h interface.
\*=========================================================================*/
#include "lua.h"

#include "io.h"
#include "timeout.h"

/* buffer size in bytes */
#define BUF_SIZE 8192

/* buffer control structure */
typedef struct t_buffer_ {
    double birthday;        /* throttle support info: creation time, */
    size_t sent, received;  /* bytes sent, and bytes received */
    p_io io;                /* IO driver used for this buffer */
    p_timeout tm;           /* timeout management for this buffer */
    size_t first, last;     /* index of first and last bytes of stored data */
    char data[BUF_SIZE];    /* storage space for buffer data */
} t_buffer;
typedef t_buffer *p_buffer;

int buffer_open(lua_State *L);
void buffer_init(p_buffer buf, p_io io, p_timeout tm);
int buffer_meth_send(lua_State *L, p_buffer buf);
int buffer_meth_receive(lua_State *L, p_buffer buf);
int buffer_meth_getstats(lua_State *L, p_buffer buf);
int buffer_meth_setstats(lua_State *L, p_buffer buf);
int buffer_isempty(p_buffer buf);

#endif /* BUF_H */
