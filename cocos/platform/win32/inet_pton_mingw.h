#ifndef HEADER_CURL_INET_PTON_MINGW_H
#define HEADER_CURL_INET_PTON_MINGW_H
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2005, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at http://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 * Portions Copyright (c) Microsoft Open Technologies, Inc.
 *
 ***************************************************************************/

#if defined(__MINGW32__)
int inet_pton(int af, const char *src, void *dst);
#endif

#endif /* HEADER_CURL_INET_PTON_MINGW_H */

