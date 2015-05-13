#ifndef HEADER_CURL_MULTIHANDLE_H
#define HEADER_CURL_MULTIHANDLE_H
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

struct Curl_message {
  /* the 'CURLMsg' is the part that is visible to the external user */
  struct CURLMsg extmsg;
};

/* NOTE: if you add a state here, add the name to the statename[] array as
   well!
*/
typedef enum {
  CURLM_STATE_INIT,         /* 0 - start in this state */
  CURLM_STATE_CONNECT_PEND, /* 1 - no connections, waiting for one */
  CURLM_STATE_CONNECT,      /* 2 - resolve/connect has been sent off */
  CURLM_STATE_WAITRESOLVE,  /* 3 - awaiting the resolve to finalize */
  CURLM_STATE_WAITCONNECT,  /* 4 - awaiting the connect to finalize */
  CURLM_STATE_WAITPROXYCONNECT, /* 5 - awaiting proxy CONNECT to finalize */
  CURLM_STATE_PROTOCONNECT, /* 6 - completing the protocol-specific connect
                                   phase */
  CURLM_STATE_WAITDO,       /* 7 - wait for our turn to send the request */
  CURLM_STATE_DO,           /* 8 - start send off the request (part 1) */
  CURLM_STATE_DOING,        /* 9 - sending off the request (part 1) */
  CURLM_STATE_DO_MORE,      /* 10 - send off the request (part 2) */
  CURLM_STATE_DO_DONE,      /* 11 - done sending off request */
  CURLM_STATE_WAITPERFORM,  /* 12 - wait for our turn to read the response */
  CURLM_STATE_PERFORM,      /* 13 - transfer data */
  CURLM_STATE_TOOFAST,      /* 14 - wait because limit-rate exceeded */
  CURLM_STATE_DONE,         /* 15 - post data transfer operation */
  CURLM_STATE_COMPLETED,    /* 16 - operation complete */
  CURLM_STATE_MSGSENT,      /* 17 - the operation complete message is sent */
  CURLM_STATE_LAST          /* 18 - not a true state, never use this */
} CURLMstate;

/* we support N sockets per easy handle. Set the corresponding bit to what
   action we should wait for */
#define MAX_SOCKSPEREASYHANDLE 5
#define GETSOCK_READABLE (0x00ff)
#define GETSOCK_WRITABLE (0xff00)

/* This is the struct known as CURLM on the outside */
struct Curl_multi {
  /* First a simple identifier to easier detect if a user mix up
     this multi handle with an easy handle. Set this to CURL_MULTI_HANDLE. */
  long type;

  /* We have a doubly-linked circular list with easy handles */
  struct SessionHandle *easyp;
  struct SessionHandle *easylp; /* last node */

  int num_easy; /* amount of entries in the linked list above. */
  int num_alive; /* amount of easy handles that are added but have not yet
                    reached COMPLETE state */

  struct curl_llist *msglist; /* a list of messages from completed transfers */

  /* callback function and user data pointer for the *socket() API */
  curl_socket_callback socket_cb;
  void *socket_userp;

  /* Hostname cache */
  struct curl_hash *hostcache;

  /* timetree points to the splay-tree of time nodes to figure out expire
     times of all currently set timers */
  struct Curl_tree *timetree;

  /* 'sockhash' is the lookup hash for socket descriptor => easy handles (note
     the pluralis form, there can be more than one easy handle waiting on the
     same actual socket) */
  struct curl_hash *sockhash;

  /* Whether pipelining is enabled for this multi handle */
  bool pipelining_enabled;

  /* Shared connection cache (bundles)*/
  struct conncache *conn_cache;

  /* This handle will be used for closing the cached connections in
     curl_multi_cleanup() */
  struct SessionHandle *closure_handle;

  long maxconnects; /* if >0, a fixed limit of the maximum number of entries
                       we're allowed to grow the connection cache to */

  long max_host_connections; /* if >0, a fixed limit of the maximum number
                                of connections per host */

  long max_total_connections; /* if >0, a fixed limit of the maximum number
                                 of connections in total */

  long max_pipeline_length; /* if >0, maximum number of requests in a
                               pipeline */

  long content_length_penalty_size; /* a connection with a
                                       content-length bigger than
                                       this is not considered
                                       for pipelining */

  long chunk_length_penalty_size; /* a connection with a chunk length
                                     bigger than this is not
                                     considered for pipelining */

  struct curl_llist *pipelining_site_bl; /* List of sites that are blacklisted
                                            from pipelining */

  struct curl_llist *pipelining_server_bl; /* List of server types that are
                                              blacklisted from pipelining */

  /* timer callback and user data pointer for the *socket() API */
  curl_multi_timer_callback timer_cb;
  void *timer_userp;
  struct timeval timer_lastcall; /* the fixed time for the timeout for the
                                    previous callback */
};

#endif /* HEADER_CURL_MULTIHANDLE_H */

