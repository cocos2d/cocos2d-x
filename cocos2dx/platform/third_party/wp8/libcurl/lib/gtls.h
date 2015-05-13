#ifndef HEADER_CURL_GTLS_H
#define HEADER_CURL_GTLS_H
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2013, Daniel Stenberg, <daniel@haxx.se>, et al.
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

#ifdef USE_GNUTLS

#include "urldata.h"

int Curl_gtls_init(void);
int Curl_gtls_cleanup(void);
CURLcode Curl_gtls_connect(struct connectdata *conn, int sockindex);
CURLcode Curl_gtls_connect_nonblocking(struct connectdata *conn,
                                       int sockindex,
                                       bool *done);

/* tell GnuTLS to close down all open information regarding connections (and
   thus session ID caching etc) */
void Curl_gtls_close_all(struct SessionHandle *data);

 /* close a SSL connection */
void Curl_gtls_close(struct connectdata *conn, int sockindex);

void Curl_gtls_session_free(void *ptr);
size_t Curl_gtls_version(char *buffer, size_t size);
int Curl_gtls_shutdown(struct connectdata *conn, int sockindex);
int Curl_gtls_seed(struct SessionHandle *data);

void Curl_gtls_random(struct SessionHandle *data,
                      unsigned char *entropy,
                      size_t length);
void Curl_gtls_md5sum(unsigned char *tmp, /* input */
                      size_t tmplen,
                      unsigned char *md5sum, /* output */
                      size_t md5len);

/* this backend provides these functions: */
#define have_curlssl_random 1
#define have_curlssl_md5sum 1

/* API setup for GnuTLS */
#define curlssl_init Curl_gtls_init
#define curlssl_cleanup Curl_gtls_cleanup
#define curlssl_connect Curl_gtls_connect
#define curlssl_connect_nonblocking Curl_gtls_connect_nonblocking
#define curlssl_session_free(x)  Curl_gtls_session_free(x)
#define curlssl_close_all Curl_gtls_close_all
#define curlssl_close Curl_gtls_close
#define curlssl_shutdown(x,y) Curl_gtls_shutdown(x,y)
#define curlssl_set_engine(x,y) (x=x, y=y, CURLE_NOT_BUILT_IN)
#define curlssl_set_engine_default(x) (x=x, CURLE_NOT_BUILT_IN)
#define curlssl_engines_list(x) (x=x, (struct curl_slist *)NULL)
#define curlssl_version Curl_gtls_version
#define curlssl_check_cxn(x) (x=x, -1)
#define curlssl_data_pending(x,y) (x=x, y=y, 0)
#define curlssl_random(x,y,z) Curl_gtls_random(x,y,z)
#define curlssl_md5sum(a,b,c,d) Curl_gtls_md5sum(a,b,c,d)

#endif /* USE_GNUTLS */
#endif /* HEADER_CURL_GTLS_H */
