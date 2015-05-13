/*
 * Copyright (c) 2003-2004, Artem B. Bityuckiy, SoftMine Corporation.
 * Rights transferred to Franklin Electronic Publishers.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#ifndef _ICONV_H_
#define _ICONV_H_

#include <_ansi.h>
#include <reent.h>
#include <sys/types.h>
#include <sys/_types.h>

/* iconv_t: charset conversion descriptor type */
typedef _iconv_t iconv_t;

_BEGIN_STD_C

#ifndef _REENT_ONLY
iconv_t
_EXFUN(iconv_open, (_CONST char *, _CONST char *));

size_t
_EXFUN(iconv, (iconv_t, char **, size_t *, char **, size_t *));

int
_EXFUN(iconv_close, (iconv_t));
#endif

iconv_t
_EXFUN(_iconv_open_r, (struct _reent *, _CONST char *, _CONST char *));

size_t
_EXFUN(_iconv_r, (struct _reent *, iconv_t, _CONST char **,
                  size_t *, char **, size_t *));

int
_EXFUN(_iconv_close_r, (struct _reent *, iconv_t));

_END_STD_C

#endif /* #ifndef _ICONV_H_ */
