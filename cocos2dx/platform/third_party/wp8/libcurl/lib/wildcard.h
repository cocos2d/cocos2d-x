#ifndef HEADER_CURL_WILDCARD_H
#define HEADER_CURL_WILDCARD_H
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 2010 - 2013, Daniel Stenberg, <daniel@haxx.se>, et al.
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

#include <curl/curl.h>

/* list of wildcard process states */
typedef enum {
  CURLWC_INIT = 0,
  CURLWC_MATCHING, /* library is trying to get list of addresses for
                      downloading */
  CURLWC_DOWNLOADING,
  CURLWC_CLEAN, /* deallocate resources and reset settings */
  CURLWC_SKIP,  /* skip over concrete file */
  CURLWC_ERROR, /* error cases */
  CURLWC_DONE   /* if is wildcard->state == CURLWC_DONE wildcard loop
                   will end */
} curl_wildcard_states;

typedef void (*curl_wildcard_tmp_dtor)(void *ptr);

/* struct keeping information about wildcard download process */
struct WildcardData {
  curl_wildcard_states state;
  char *path; /* path to the directory, where we trying wildcard-match */
  char *pattern; /* wildcard pattern */
  struct curl_llist *filelist; /* llist with struct Curl_fileinfo */
  void *tmp; /* pointer to protocol specific temporary data */
  curl_wildcard_tmp_dtor tmp_dtor;
  void *customptr;  /* for CURLOPT_CHUNK_DATA pointer */
};

CURLcode Curl_wildcard_init(struct WildcardData *wc);
void Curl_wildcard_dtor(struct WildcardData *wc);

struct SessionHandle;

#endif /* HEADER_CURL_WILDCARD_H */
