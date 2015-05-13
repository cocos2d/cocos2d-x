#ifndef HEADER_CURL_SMTP_H
#define HEADER_CURL_SMTP_H
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 2009 - 2013, Daniel Stenberg, <daniel@haxx.se>, et al.
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

#include "pingpong.h"

/****************************************************************************
 * SMTP unique setup
 ***************************************************************************/
typedef enum {
  SMTP_STOP,        /* do nothing state, stops the state machine */
  SMTP_SERVERGREET, /* waiting for the initial greeting immediately after
                       a connect */
  SMTP_EHLO,
  SMTP_HELO,
  SMTP_STARTTLS,
  SMTP_UPGRADETLS,  /* asynchronously upgrade the connection to SSL/TLS
                       (multi mode only) */
  SMTP_AUTH_PLAIN,
  SMTP_AUTH_LOGIN,
  SMTP_AUTH_LOGIN_PASSWD,
  SMTP_AUTH_CRAMMD5,
  SMTP_AUTH_DIGESTMD5,
  SMTP_AUTH_DIGESTMD5_RESP,
  SMTP_AUTH_NTLM,
  SMTP_AUTH_NTLM_TYPE2MSG,
  SMTP_AUTH_XOAUTH2,
  SMTP_AUTH_CANCEL,
  SMTP_AUTH_FINAL,
  SMTP_COMMAND,     /* VRFY, EXPN, NOOP, RSET and HELP */
  SMTP_MAIL,        /* MAIL FROM */
  SMTP_RCPT,        /* RCPT TO */
  SMTP_DATA,
  SMTP_POSTDATA,
  SMTP_QUIT,
  SMTP_LAST         /* never used */
} smtpstate;

/* This SMTP struct is used in the SessionHandle. All SMTP data that is
   connection-oriented must be in smtp_conn to properly deal with the fact that
   perhaps the SessionHandle is changed between the times the connection is
   used. */
struct SMTP {
  curl_pp_transfer transfer;
  char *custom;            /* Custom Request */
  struct curl_slist *rcpt; /* Recipient list */
  size_t eob;              /* Number of bytes of the EOB (End Of Body) that
                              have been received so far */
  bool trailing_crlf;      /* Specifies if the tailing CRLF is present */
};

/* smtp_conn is used for struct connection-oriented data in the connectdata
   struct */
struct smtp_conn {
  struct pingpong pp;
  smtpstate state;         /* Always use smtp.c:state() to change state! */
  bool ssldone;            /* Is connect() over SSL done? */
  char *domain;            /* Client address/name to send in the EHLO */
  unsigned int authmechs;  /* Accepted authentication mechanisms */
  unsigned int prefmech;   /* Preferred authentication mechanism */
  unsigned int authused;   /* Auth mechanism used for the connection */
  bool tls_supported;      /* StartTLS capability supported by server */
  bool size_supported;     /* If server supports SIZE extension according to
                              RFC 1870 */
};

extern const struct Curl_handler Curl_handler_smtp;
extern const struct Curl_handler Curl_handler_smtps;

/* this is the 5-bytes End-Of-Body marker for SMTP */
#define SMTP_EOB "\x0d\x0a\x2e\x0d\x0a"
#define SMTP_EOB_LEN 5
#define SMTP_EOB_FIND_LEN 3

/* if found in data, replace it with this string instead */
#define SMTP_EOB_REPL "\x0d\x0a\x2e\x2e"
#define SMTP_EOB_REPL_LEN 4

CURLcode Curl_smtp_escape_eob(struct connectdata *conn, ssize_t nread);

#endif /* HEADER_CURL_SMTP_H */
