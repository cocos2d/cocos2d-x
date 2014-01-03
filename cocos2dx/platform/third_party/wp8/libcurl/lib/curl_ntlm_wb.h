#ifndef HEADER_CURL_NTLM_WB_H
#define HEADER_CURL_NTLM_WB_H
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2011, Daniel Stenberg, <daniel@haxx.se>, et al.
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
 ***************************************************************************/

#include "curl_setup.h"

#if defined(USE_NTLM) && defined(NTLM_WB_ENABLED)

/* this is for creating ntlm header output by delegating challenge/response
   to Samba's winbind daemon helper ntlm_auth */
CURLcode Curl_output_ntlm_wb(struct connectdata *conn, bool proxy);

void Curl_ntlm_wb_cleanup(struct connectdata *conn);

#endif /* USE_NTLM && NTLM_WB_ENABLED */

#endif /* HEADER_CURL_NTLM_WB_H */
