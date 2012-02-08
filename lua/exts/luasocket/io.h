#ifndef IO_H
#define IO_H
/*=========================================================================*\
* Input/Output abstraction
* LuaSocket toolkit
*
* This module defines the interface that LuaSocket expects from the
* transport layer for streamed input/output. The idea is that if any
* transport implements this interface, then the buffer.c functions
* automatically work on it.
*
* The module socket.h implements this interface, and thus the module tcp.h
* is very simple.
*
* RCS ID: $Id: io.h,v 1.11 2005/10/07 04:40:59 diego Exp $
\*=========================================================================*/
#include <stdio.h>
#include "lua.h"

#include "timeout.h"

/* IO error codes */
enum {
    IO_DONE = 0,        /* operation completed successfully */
    IO_TIMEOUT = -1,    /* operation timed out */
    IO_CLOSED = -2,     /* the connection has been closed */
	IO_UNKNOWN = -3
};

/* interface to error message function */
typedef const char *(*p_error) (
    void *ctx,          /* context needed by send */
    int err             /* error code */
);

/* interface to send function */
typedef int (*p_send) (
    void *ctx,          /* context needed by send */
    const char *data,   /* pointer to buffer with data to send */
    size_t count,       /* number of bytes to send from buffer */
    size_t *sent,       /* number of bytes sent uppon return */
    p_timeout tm        /* timeout control */
);

/* interface to recv function */
typedef int (*p_recv) (
    void *ctx,          /* context needed by recv */
    char *data,         /* pointer to buffer where data will be writen */
    size_t count,       /* number of bytes to receive into buffer */
    size_t *got,        /* number of bytes received uppon return */
    p_timeout tm        /* timeout control */
);

/* IO driver definition */
typedef struct t_io_ {
    void *ctx;          /* context needed by send/recv */
    p_send send;        /* send function pointer */
    p_recv recv;        /* receive function pointer */
    p_error error;      /* strerror function */
} t_io;
typedef t_io *p_io;

void io_init(p_io io, p_send send, p_recv recv, p_error error, void *ctx);
const char *io_strerror(int err);

#endif /* IO_H */

