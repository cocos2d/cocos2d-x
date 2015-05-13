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
 * RFC1734 POP3 Authentication
 * RFC1939 POP3 protocol
 * RFC2195 CRAM-MD5 authentication
 * RFC2384 POP URL Scheme
 * RFC2449 POP3 Extension Mechanism
 * RFC2595 Using TLS with IMAP, POP3 and ACAP
 * RFC2831 DIGEST-MD5 authentication
 * RFC4422 Simple Authentication and Security Layer (SASL)
 * RFC4616 PLAIN authentication
 * RFC5034 POP3 SASL Authentication Mechanism
 * RFC6749 OAuth 2.0 Authorization Framework
 * Draft   LOGIN SASL Mechanism <draft-murchison-sasl-login-00.txt>
 *
 ***************************************************************************/

#include "curl_setup.h"

#ifndef CURL_DISABLE_POP3

#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif
#ifdef HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif
#ifdef HAVE_UTSNAME_H
#include <sys/utsname.h>
#endif
#ifdef HAVE_NETDB_H
#include <netdb.h>
#endif
#ifdef __VMS
#include <in.h>
#include <inet.h>
#endif

#if (defined(NETWARE) && defined(__NOVELL_LIBC__))
#undef in_addr_t
#define in_addr_t unsigned long
#endif

#include <curl/curl.h>
#include "urldata.h"
#include "sendf.h"
#include "if2ip.h"
#include "hostip.h"
#include "progress.h"
#include "transfer.h"
#include "escape.h"
#include "http.h" /* for HTTP proxy tunnel stuff */
#include "socks.h"
#include "pop3.h"

#include "strtoofft.h"
#include "strequal.h"
#include "sslgen.h"
#include "connect.h"
#include "strerror.h"
#include "select.h"
#include "multiif.h"
#include "url.h"
#include "rawstr.h"
#include "curl_sasl.h"
#include "curl_md5.h"
#include "warnless.h"

#define _MPRINTF_REPLACE /* use our functions only */
#include <curl/mprintf.h>

#include "curl_memory.h"
/* The last #include file should be: */
#include "memdebug.h"

/* Local API functions */
static CURLcode pop3_regular_transfer(struct connectdata *conn, bool *done);
static CURLcode pop3_do(struct connectdata *conn, bool *done);
static CURLcode pop3_done(struct connectdata *conn, CURLcode status,
                          bool premature);
static CURLcode pop3_connect(struct connectdata *conn, bool *done);
static CURLcode pop3_disconnect(struct connectdata *conn, bool dead);
static CURLcode pop3_multi_statemach(struct connectdata *conn, bool *done);
static int pop3_getsock(struct connectdata *conn, curl_socket_t *socks,
                        int numsocks);
static CURLcode pop3_doing(struct connectdata *conn, bool *dophase_done);
static CURLcode pop3_setup_connection(struct connectdata *conn);
static CURLcode pop3_parse_url_options(struct connectdata *conn);
static CURLcode pop3_parse_url_path(struct connectdata *conn);
static CURLcode pop3_parse_custom_request(struct connectdata *conn);

/*
 * POP3 protocol handler.
 */

const struct Curl_handler Curl_handler_pop3 = {
  "POP3",                           /* scheme */
  pop3_setup_connection,            /* setup_connection */
  pop3_do,                          /* do_it */
  pop3_done,                        /* done */
  ZERO_NULL,                        /* do_more */
  pop3_connect,                     /* connect_it */
  pop3_multi_statemach,             /* connecting */
  pop3_doing,                       /* doing */
  pop3_getsock,                     /* proto_getsock */
  pop3_getsock,                     /* doing_getsock */
  ZERO_NULL,                        /* domore_getsock */
  ZERO_NULL,                        /* perform_getsock */
  pop3_disconnect,                  /* disconnect */
  ZERO_NULL,                        /* readwrite */
  PORT_POP3,                        /* defport */
  CURLPROTO_POP3,                   /* protocol */
  PROTOPT_CLOSEACTION | PROTOPT_NOURLQUERY /* flags */
};

#ifdef USE_SSL
/*
 * POP3S protocol handler.
 */

const struct Curl_handler Curl_handler_pop3s = {
  "POP3S",                          /* scheme */
  pop3_setup_connection,            /* setup_connection */
  pop3_do,                          /* do_it */
  pop3_done,                        /* done */
  ZERO_NULL,                        /* do_more */
  pop3_connect,                     /* connect_it */
  pop3_multi_statemach,             /* connecting */
  pop3_doing,                       /* doing */
  pop3_getsock,                     /* proto_getsock */
  pop3_getsock,                     /* doing_getsock */
  ZERO_NULL,                        /* domore_getsock */
  ZERO_NULL,                        /* perform_getsock */
  pop3_disconnect,                  /* disconnect */
  ZERO_NULL,                        /* readwrite */
  PORT_POP3S,                       /* defport */
  CURLPROTO_POP3 | CURLPROTO_POP3S, /* protocol */
  PROTOPT_CLOSEACTION | PROTOPT_SSL
  | PROTOPT_NOURLQUERY              /* flags */
};
#endif

#ifndef CURL_DISABLE_HTTP
/*
 * HTTP-proxyed POP3 protocol handler.
 */

static const struct Curl_handler Curl_handler_pop3_proxy = {
  "POP3",                               /* scheme */
  Curl_http_setup_conn,                 /* setup_connection */
  Curl_http,                            /* do_it */
  Curl_http_done,                       /* done */
  ZERO_NULL,                            /* do_more */
  ZERO_NULL,                            /* connect_it */
  ZERO_NULL,                            /* connecting */
  ZERO_NULL,                            /* doing */
  ZERO_NULL,                            /* proto_getsock */
  ZERO_NULL,                            /* doing_getsock */
  ZERO_NULL,                            /* domore_getsock */
  ZERO_NULL,                            /* perform_getsock */
  ZERO_NULL,                            /* disconnect */
  ZERO_NULL,                            /* readwrite */
  PORT_POP3,                            /* defport */
  CURLPROTO_HTTP,                       /* protocol */
  PROTOPT_NONE                          /* flags */
};

#ifdef USE_SSL
/*
 * HTTP-proxyed POP3S protocol handler.
 */

static const struct Curl_handler Curl_handler_pop3s_proxy = {
  "POP3S",                              /* scheme */
  Curl_http_setup_conn,                 /* setup_connection */
  Curl_http,                            /* do_it */
  Curl_http_done,                       /* done */
  ZERO_NULL,                            /* do_more */
  ZERO_NULL,                            /* connect_it */
  ZERO_NULL,                            /* connecting */
  ZERO_NULL,                            /* doing */
  ZERO_NULL,                            /* proto_getsock */
  ZERO_NULL,                            /* doing_getsock */
  ZERO_NULL,                            /* domore_getsock */
  ZERO_NULL,                            /* perform_getsock */
  ZERO_NULL,                            /* disconnect */
  ZERO_NULL,                            /* readwrite */
  PORT_POP3S,                           /* defport */
  CURLPROTO_HTTP,                       /* protocol */
  PROTOPT_NONE                          /* flags */
};
#endif
#endif

#ifdef USE_SSL
static void pop3_to_pop3s(struct connectdata *conn)
{
  conn->handler = &Curl_handler_pop3s;
}
#else
#define pop3_to_pop3s(x) Curl_nop_stmt
#endif

/***********************************************************************
 *
 * pop3_endofresp()
 *
 * Checks for an ending POP3 status code at the start of the given string, but
 * also detects the APOP timestamp from the server greeting and various
 * capabilities from the CAPA response including the supported authentication
 * types and allowed SASL mechanisms.
 */
static bool pop3_endofresp(struct connectdata *conn, char *line, size_t len,
                           int *resp)
{
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  size_t wordlen;
  size_t i;

  /* Do we have an error response? */
  if(len >= 4 && !memcmp("-ERR", line, 4)) {
    *resp = '-';

    return TRUE;
  }

  /* Are we processing servergreet responses? */
  if(pop3c->state == POP3_SERVERGREET) {
    /* Look for the APOP timestamp */
    if(len >= 3 && line[len - 3] == '>') {
      for(i = 0; i < len - 3; ++i) {
        if(line[i] == '<') {
          /* Calculate the length of the timestamp */
          size_t timestamplen = len - 2 - i;

          /* Allocate some memory for the timestamp */
          pop3c->apoptimestamp = (char *)calloc(1, timestamplen + 1);

          if(!pop3c->apoptimestamp)
            break;

          /* Copy the timestamp */
          memcpy(pop3c->apoptimestamp, line + i, timestamplen);
          pop3c->apoptimestamp[timestamplen] = '\0';
          break;
        }
      }
    }
  }
  /* Are we processing CAPA command responses? */
  else if(pop3c->state == POP3_CAPA) {
    /* Do we have the terminating line? */
    if(len >= 1 && !memcmp(line, ".", 1)) {
      *resp = '+';

      return TRUE;
    }

    /* Does the server support the STLS capability? */
    if(len >= 4 && !memcmp(line, "STLS", 4))
      pop3c->tls_supported = TRUE;

    /* Does the server support clear text authentication? */
    else if(len >= 4 && !memcmp(line, "USER", 4))
      pop3c->authtypes |= POP3_TYPE_CLEARTEXT;

    /* Does the server support APOP authentication? */
    else if(len >= 4 && !memcmp(line, "APOP", 4))
      pop3c->authtypes |= POP3_TYPE_APOP;

    /* Does the server support SASL based authentication? */
    else if(len >= 5 && !memcmp(line, "SASL ", 5)) {
      pop3c->authtypes |= POP3_TYPE_SASL;

      /* Advance past the SASL keyword */
      line += 5;
      len -= 5;

      /* Loop through the data line */
      for(;;) {
        while(len &&
              (*line == ' ' || *line == '\t' ||
               *line == '\r' || *line == '\n')) {

          line++;
          len--;
        }

        if(!len)
          break;

        /* Extract the word */
        for(wordlen = 0; wordlen < len && line[wordlen] != ' ' &&
              line[wordlen] != '\t' && line[wordlen] != '\r' &&
              line[wordlen] != '\n';)
          wordlen++;

        /* Test the word for a matching authentication mechanism */
        if(sasl_mech_equal(line, wordlen, SASL_MECH_STRING_LOGIN))
          pop3c->authmechs |= SASL_MECH_LOGIN;
        else if(sasl_mech_equal(line, wordlen, SASL_MECH_STRING_PLAIN))
          pop3c->authmechs |= SASL_MECH_PLAIN;
        else if(sasl_mech_equal(line, wordlen, SASL_MECH_STRING_CRAM_MD5))
          pop3c->authmechs |= SASL_MECH_CRAM_MD5;
        else if(sasl_mech_equal(line, wordlen, SASL_MECH_STRING_DIGEST_MD5))
          pop3c->authmechs |= SASL_MECH_DIGEST_MD5;
        else if(sasl_mech_equal(line, wordlen, SASL_MECH_STRING_GSSAPI))
          pop3c->authmechs |= SASL_MECH_GSSAPI;
        else if(sasl_mech_equal(line, wordlen, SASL_MECH_STRING_EXTERNAL))
          pop3c->authmechs |= SASL_MECH_EXTERNAL;
        else if(sasl_mech_equal(line, wordlen, SASL_MECH_STRING_NTLM))
          pop3c->authmechs |= SASL_MECH_NTLM;
        else if(sasl_mech_equal(line, wordlen, SASL_MECH_STRING_XOAUTH2))
          pop3c->authmechs |= SASL_MECH_XOAUTH2;

        line += wordlen;
        len -= wordlen;
      }
    }

    return FALSE;
  }

  /* Do we have a command or continuation response? */
  if((len >= 3 && !memcmp("+OK", line, 3)) ||
     (len >= 1 && !memcmp("+", line, 1))) {
    *resp = '+';

    return TRUE;
  }

  return FALSE; /* Nothing for us */
}

/***********************************************************************
 *
 * pop3_get_message()
 *
 * Gets the authentication message from the response buffer.
 */
static void pop3_get_message(char *buffer, char** outptr)
{
  size_t len = 0;
  char* message = NULL;

  /* Find the start of the message */
  for(message = buffer + 2; *message == ' ' || *message == '\t'; message++)
    ;

  /* Find the end of the message */
  for(len = strlen(message); len--;)
    if(message[len] != '\r' && message[len] != '\n' && message[len] != ' ' &&
        message[len] != '\t')
      break;

  /* Terminate the message */
  if(++len) {
    message[len] = '\0';
  }

  *outptr = message;
}

/***********************************************************************
 *
 * state()
 *
 * This is the ONLY way to change POP3 state!
 */
static void state(struct connectdata *conn, pop3state newstate)
{
  struct pop3_conn *pop3c = &conn->proto.pop3c;
#if defined(DEBUGBUILD) && !defined(CURL_DISABLE_VERBOSE_STRINGS)
  /* for debug purposes */
  static const char * const names[] = {
    "STOP",
    "SERVERGREET",
    "CAPA",
    "STARTTLS",
    "UPGRADETLS",
    "AUTH_PLAIN",
    "AUTH_LOGIN",
    "AUTH_LOGIN_PASSWD",
    "AUTH_CRAMMD5",
    "AUTH_DIGESTMD5",
    "AUTH_DIGESTMD5_RESP",
    "AUTH_NTLM",
    "AUTH_NTLM_TYPE2MSG",
    "AUTH_XOAUTH2",
    "AUTH_CANCEL",
    "AUTH_FINAL",
    "APOP",
    "USER",
    "PASS",
    "COMMAND",
    "QUIT",
    /* LAST */
  };

  if(pop3c->state != newstate)
    infof(conn->data, "POP3 %p state change from %s to %s\n",
          (void *)pop3c, names[pop3c->state], names[newstate]);
#endif

  pop3c->state = newstate;
}

/***********************************************************************
 *
 * pop3_perform_capa()
 *
 * Sends the CAPA command in order to obtain a list of server side supported
 * capabilities.
 */
static CURLcode pop3_perform_capa(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct pop3_conn *pop3c = &conn->proto.pop3c;

  pop3c->authmechs = 0;         /* No known authentication mechanisms yet */
  pop3c->authused = 0;          /* Clear the authentication mechanism used */
  pop3c->tls_supported = FALSE; /* Clear the TLS capability */

  /* Send the CAPA command */
  result = Curl_pp_sendf(&pop3c->pp, "%s", "CAPA");

  if(!result)
    state(conn, POP3_CAPA);

  return result;
}

/***********************************************************************
 *
 * pop3_perform_starttls()
 *
 * Sends the STLS command to start the upgrade to TLS.
 */
static CURLcode pop3_perform_starttls(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;

  /* Send the STLS command */
  result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s", "STLS");

  if(!result)
    state(conn, POP3_STARTTLS);

  return result;
}

/***********************************************************************
 *
 * pop3_perform_upgrade_tls()
 *
 * Performs the upgrade to TLS.
 */
static CURLcode pop3_perform_upgrade_tls(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct pop3_conn *pop3c = &conn->proto.pop3c;

  /* Start the SSL connection */
  result = Curl_ssl_connect_nonblocking(conn, FIRSTSOCKET, &pop3c->ssldone);

  if(!result) {
    if(pop3c->state != POP3_UPGRADETLS)
      state(conn, POP3_UPGRADETLS);

    if(pop3c->ssldone) {
      pop3_to_pop3s(conn);
      result = pop3_perform_capa(conn);
    }
  }

  return result;
}

/***********************************************************************
 *
 * pop3_perform_user()
 *
 * Sends a clear text USER command to authenticate with.
 */
static CURLcode pop3_perform_user(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;

  /* Check we have a username and password to authenticate with and end the
     connect phase if we don't */
  if(!conn->bits.user_passwd) {
    state(conn, POP3_STOP);

    return result;
  }

  /* Send the USER command */
  result = Curl_pp_sendf(&conn->proto.pop3c.pp, "USER %s",
                         conn->user ? conn->user : "");
  if(!result)
    state(conn, POP3_USER);

  return result;
}

#ifndef CURL_DISABLE_CRYPTO_AUTH
/***********************************************************************
 *
 * pop3_perform_apop()
 *
 * Sends an APOP command to authenticate with.
 */
static CURLcode pop3_perform_apop(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  size_t i;
  MD5_context *ctxt;
  unsigned char digest[MD5_DIGEST_LEN];
  char secret[2 * MD5_DIGEST_LEN + 1];

  /* Check we have a username and password to authenticate with and end the
     connect phase if we don't */
  if(!conn->bits.user_passwd) {
    state(conn, POP3_STOP);

    return result;
  }

  /* Create the digest */
  ctxt = Curl_MD5_init(Curl_DIGEST_MD5);
  if(!ctxt)
    return CURLE_OUT_OF_MEMORY;

  Curl_MD5_update(ctxt, (const unsigned char *) pop3c->apoptimestamp,
                  curlx_uztoui(strlen(pop3c->apoptimestamp)));

  Curl_MD5_update(ctxt, (const unsigned char *) conn->passwd,
                  curlx_uztoui(strlen(conn->passwd)));

  /* Finalise the digest */
  Curl_MD5_final(ctxt, digest);

  /* Convert the calculated 16 octet digest into a 32 byte hex string */
  for(i = 0; i < MD5_DIGEST_LEN; i++)
    snprintf(&secret[2 * i], 3, "%02x", digest[i]);

  result = Curl_pp_sendf(&pop3c->pp, "APOP %s %s", conn->user, secret);

  if(!result)
    state(conn, POP3_APOP);

  return result;
}
#endif

/***********************************************************************
 *
 * pop3_perform_authenticate()
 *
 * Sends an AUTH command allowing the client to login with the appropriate
 * SASL authentication mechanism.
 *
 * Additionally, the function will perform fallback to APOP and USER commands
 * should a common mechanism not be available between the client and server.
 */
static CURLcode pop3_perform_authenticate(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  const char *mech = NULL;
  char *initresp = NULL;
  size_t len = 0;
  pop3state state1 = POP3_STOP;
  pop3state state2 = POP3_STOP;

  /* Check we have a username and password to authenticate with and end the
     connect phase if we don't */
  if(!conn->bits.user_passwd) {
    state(conn, POP3_STOP);

    return result;
  }

  /* Calculate the supported authentication mechanism, by decreasing order of
     security, as well as the initial response where appropriate */
  if(pop3c->authtypes & POP3_TYPE_SASL) {
#ifndef CURL_DISABLE_CRYPTO_AUTH
    if((pop3c->authmechs & SASL_MECH_DIGEST_MD5) &&
       (pop3c->prefmech & SASL_MECH_DIGEST_MD5)) {
      mech = SASL_MECH_STRING_DIGEST_MD5;
      state1 = POP3_AUTH_DIGESTMD5;
      pop3c->authused = SASL_MECH_DIGEST_MD5;
    }
    else if((pop3c->authmechs & SASL_MECH_CRAM_MD5) &&
            (pop3c->prefmech & SASL_MECH_CRAM_MD5)) {
      mech = SASL_MECH_STRING_CRAM_MD5;
      state1 = POP3_AUTH_CRAMMD5;
      pop3c->authused = SASL_MECH_CRAM_MD5;
    }
    else
#endif
#ifdef USE_NTLM
    if((pop3c->authmechs & SASL_MECH_NTLM) &&
       (pop3c->prefmech & SASL_MECH_NTLM)) {
      mech = SASL_MECH_STRING_NTLM;
      state1 = POP3_AUTH_NTLM;
      state2 = POP3_AUTH_NTLM_TYPE2MSG;
      pop3c->authused = SASL_MECH_NTLM;

      if(data->set.sasl_ir)
        result = Curl_sasl_create_ntlm_type1_message(conn->user, conn->passwd,
                                                     &conn->ntlm,
                                                     &initresp, &len);
    }
    else
#endif
    if(((pop3c->authmechs & SASL_MECH_XOAUTH2) &&
        (pop3c->prefmech & SASL_MECH_XOAUTH2) &&
        (pop3c->prefmech != SASL_AUTH_ANY)) || conn->xoauth2_bearer) {
      mech = SASL_MECH_STRING_XOAUTH2;
      state1 = POP3_AUTH_XOAUTH2;
      state2 = POP3_AUTH_FINAL;
      pop3c->authused = SASL_MECH_XOAUTH2;

      if(data->set.sasl_ir)
        result = Curl_sasl_create_xoauth2_message(conn->data, conn->user,
                                                  conn->xoauth2_bearer,
                                                  &initresp, &len);
    }
    else if((pop3c->authmechs & SASL_MECH_LOGIN) &&
       (pop3c->prefmech & SASL_MECH_LOGIN)) {
      mech = SASL_MECH_STRING_LOGIN;
      state1 = POP3_AUTH_LOGIN;
      state2 = POP3_AUTH_LOGIN_PASSWD;
      pop3c->authused = SASL_MECH_LOGIN;

      if(data->set.sasl_ir)
        result = Curl_sasl_create_login_message(conn->data, conn->user,
                                                &initresp, &len);
    }
    else if((pop3c->authmechs & SASL_MECH_PLAIN) &&
            (pop3c->prefmech & SASL_MECH_PLAIN)) {
      mech = SASL_MECH_STRING_PLAIN;
      state1 = POP3_AUTH_PLAIN;
      state2 = POP3_AUTH_FINAL;
      pop3c->authused = SASL_MECH_PLAIN;

      if(data->set.sasl_ir)
        result = Curl_sasl_create_plain_message(conn->data, conn->user,
                                                conn->passwd, &initresp,
                                                &len);
    }
  }

  if(!result) {
    if(mech && (pop3c->preftype & POP3_TYPE_SASL)) {
      /* Perform SASL based authentication */
      if(initresp &&
         8 + strlen(mech) + len <= 255) { /* AUTH <mech> ...<crlf> */
        result = Curl_pp_sendf(&pop3c->pp, "AUTH %s %s", mech, initresp);

        if(!result)
          state(conn, state2);
      }
      else {
        result = Curl_pp_sendf(&pop3c->pp, "AUTH %s", mech);

        if(!result)
          state(conn, state1);
      }

      Curl_safefree(initresp);
    }
#ifndef CURL_DISABLE_CRYPTO_AUTH
    else if((pop3c->authtypes & POP3_TYPE_APOP) &&
            (pop3c->preftype & POP3_TYPE_APOP))
      /* Perform APOP authentication */
      result = pop3_perform_apop(conn);
#endif
    else if((pop3c->authtypes & POP3_TYPE_CLEARTEXT) &&
            (pop3c->preftype & POP3_TYPE_CLEARTEXT))
      /* Perform clear text authentication */
      result = pop3_perform_user(conn);
    else {
      /* Other mechanisms not supported */
      infof(conn->data, "No known authentication mechanisms supported!\n");
      result = CURLE_LOGIN_DENIED;
    }
  }

  return result;
}

/***********************************************************************
 *
 * pop3_perform_command()
 *
 * Sends a POP3 based command.
 */
static CURLcode pop3_perform_command(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct POP3 *pop3 = data->req.protop;
  const char *command = NULL;

  /* Calculate the default command */
  if(pop3->id[0] == '\0' || conn->data->set.ftp_list_only) {
    command = "LIST";

    if(pop3->id[0] != '\0')
      /* Message specific LIST so skip the BODY transfer */
      pop3->transfer = FTPTRANSFER_INFO;
  }
  else
    command = "RETR";

  /* Send the command */
  if(pop3->id[0] != '\0')
    result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s %s",
                           (pop3->custom && pop3->custom[0] != '\0' ?
                            pop3->custom : command), pop3->id);
  else
    result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s",
                           (pop3->custom && pop3->custom[0] != '\0' ?
                            pop3->custom : command));

  if(!result)
    state(conn, POP3_COMMAND);

  return result;
}

/***********************************************************************
 *
 * pop3_perform_quit()
 *
 * Performs the quit action prior to sclose() be called.
 */
static CURLcode pop3_perform_quit(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;

  /* Send the QUIT command */
  result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s", "QUIT");

  if(!result)
    state(conn, POP3_QUIT);

  return result;
}

/* For the initial server greeting */
static CURLcode pop3_state_servergreet_resp(struct connectdata *conn,
                                            int pop3code,
                                            pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    failf(data, "Got unexpected pop3-server response");
    result = CURLE_FTP_WEIRD_SERVER_REPLY;
  }
  else
    result = pop3_perform_capa(conn);

  return result;
}

/* For CAPA responses */
static CURLcode pop3_state_capa_resp(struct connectdata *conn, int pop3code,
                                     pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct pop3_conn *pop3c = &conn->proto.pop3c;

  (void)instate; /* no use for this yet */

  if(pop3code != '+')
    result = pop3_perform_user(conn);
  else if(data->set.use_ssl && !conn->ssl[FIRSTSOCKET].use) {
    /* We don't have a SSL/TLS connection yet, but SSL is requested */
    if(pop3c->tls_supported)
      /* Switch to TLS connection now */
      result = pop3_perform_starttls(conn);
    else if(data->set.use_ssl == CURLUSESSL_TRY)
      /* Fallback and carry on with authentication */
      result = pop3_perform_authenticate(conn);
    else {
      failf(data, "STLS not supported.");
      result = CURLE_USE_SSL_FAILED;
    }
  }
  else
    result = pop3_perform_authenticate(conn);

  return result;
}

/* For STARTTLS responses */
static CURLcode pop3_state_starttls_resp(struct connectdata *conn,
                                         int pop3code,
                                         pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    if(data->set.use_ssl != CURLUSESSL_TRY) {
      failf(data, "STARTTLS denied. %c", pop3code);
      result = CURLE_USE_SSL_FAILED;
    }
    else
      result = pop3_perform_authenticate(conn);
  }
  else
    result = pop3_perform_upgrade_tls(conn);

  return result;
}

/* For AUTH PLAIN (without initial response) responses */
static CURLcode pop3_state_auth_plain_resp(struct connectdata *conn,
                                           int pop3code,
                                           pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  size_t len = 0;
  char *plainauth = NULL;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    failf(data, "Access denied. %c", pop3code);
    result = CURLE_LOGIN_DENIED;
  }
  else {
    /* Create the authorisation message */
    result = Curl_sasl_create_plain_message(data, conn->user, conn->passwd,
                                            &plainauth, &len);
    if(!result && plainauth) {
      /* Send the message */
      result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s", plainauth);

      if(!result)
        state(conn, POP3_AUTH_FINAL);
    }
  }

  Curl_safefree(plainauth);

  return result;
}

/* For AUTH LOGIN (without initial response) responses */
static CURLcode pop3_state_auth_login_resp(struct connectdata *conn,
                                           int pop3code,
                                           pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  size_t len = 0;
  char *authuser = NULL;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    failf(data, "Access denied: %d", pop3code);
    result = CURLE_LOGIN_DENIED;
  }
  else {
    /* Create the user message */
    result = Curl_sasl_create_login_message(data, conn->user,
                                            &authuser, &len);
    if(!result && authuser) {
      /* Send the user */
      result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s", authuser);

      if(!result)
        state(conn, POP3_AUTH_LOGIN_PASSWD);
    }
  }

  Curl_safefree(authuser);

  return result;
}

/* For AUTH LOGIN user entry responses */
static CURLcode pop3_state_auth_login_password_resp(struct connectdata *conn,
                                                    int pop3code,
                                                    pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  size_t len = 0;
  char *authpasswd = NULL;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    failf(data, "Access denied: %d", pop3code);
    result = CURLE_LOGIN_DENIED;
  }
  else {
    /* Create the password message */
    result = Curl_sasl_create_login_message(data, conn->passwd,
                                            &authpasswd, &len);
    if(!result && authpasswd) {
      /* Send the password */
      result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s", authpasswd);

      if(!result)
        state(conn, POP3_AUTH_FINAL);
    }
  }

  Curl_safefree(authpasswd);

  return result;
}

#ifndef CURL_DISABLE_CRYPTO_AUTH
/* For AUTH CRAM-MD5 responses */
static CURLcode pop3_state_auth_cram_resp(struct connectdata *conn,
                                          int pop3code,
                                          pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  char *chlg = NULL;
  char *chlg64 = NULL;
  char *rplyb64 = NULL;
  size_t len = 0;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    failf(data, "Access denied: %d", pop3code);
    return CURLE_LOGIN_DENIED;
  }

  /* Get the challenge message */
  pop3_get_message(data->state.buffer, &chlg64);

  /* Decode the challenge message */
  result = Curl_sasl_decode_cram_md5_message(chlg64, &chlg, &len);
  if(result) {
    /* Send the cancellation */
    result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s", "*");

    if(!result)
      state(conn, POP3_AUTH_CANCEL);
  }
  else {
    /* Create the response message */
    result = Curl_sasl_create_cram_md5_message(data, chlg, conn->user,
                                               conn->passwd, &rplyb64, &len);
    if(!result && rplyb64) {
      /* Send the response */
      result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s", rplyb64);

      if(!result)
        state(conn, POP3_AUTH_FINAL);
    }
  }

  Curl_safefree(chlg);
  Curl_safefree(rplyb64);

  return result;
}

/* For AUTH DIGEST-MD5 challenge responses */
static CURLcode pop3_state_auth_digest_resp(struct connectdata *conn,
                                            int pop3code,
                                            pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  char *chlg64 = NULL;
  char *rplyb64 = NULL;
  size_t len = 0;

  char nonce[64];
  char realm[128];
  char algorithm[64];

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    failf(data, "Access denied: %d", pop3code);
    return CURLE_LOGIN_DENIED;
  }

  /* Get the challenge message */
  pop3_get_message(data->state.buffer, &chlg64);

  /* Decode the challange message */
  result = Curl_sasl_decode_digest_md5_message(chlg64, nonce, sizeof(nonce),
                                               realm, sizeof(realm),
                                               algorithm, sizeof(algorithm));
  if(result || strcmp(algorithm, "md5-sess") != 0) {
    /* Send the cancellation */
    result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s", "*");

    if(!result)
      state(conn, POP3_AUTH_CANCEL);
  }
  else {
    /* Create the response message */
    result = Curl_sasl_create_digest_md5_message(data, nonce, realm,
                                                 conn->user, conn->passwd,
                                                 "pop", &rplyb64, &len);
    if(!result && rplyb64) {
      /* Send the response */
      result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s", rplyb64);

      if(!result)
        state(conn, POP3_AUTH_DIGESTMD5_RESP);
    }
  }

  Curl_safefree(rplyb64);

  return result;
}

/* For AUTH DIGEST-MD5 challenge-response responses */
static CURLcode pop3_state_auth_digest_resp_resp(struct connectdata *conn,
                                                 int pop3code,
                                                 pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    failf(data, "Authentication failed: %d", pop3code);
    result = CURLE_LOGIN_DENIED;
  }
  else {
    /* Send an empty response */
    result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s", "");

    if(!result)
      state(conn, POP3_AUTH_FINAL);
  }

  return result;
}
#endif

#ifdef USE_NTLM
/* For AUTH NTLM (without initial response) responses */
static CURLcode pop3_state_auth_ntlm_resp(struct connectdata *conn,
                                          int pop3code,
                                          pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  size_t len = 0;
  char *type1msg = NULL;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    failf(data, "Access denied: %d", pop3code);
    result = CURLE_LOGIN_DENIED;
  }
  else {
    /* Create the type-1 message */
    result = Curl_sasl_create_ntlm_type1_message(conn->user, conn->passwd,
                                                 &conn->ntlm,
                                                 &type1msg, &len);
    if(!result && type1msg) {
      /* Send the message */
      result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s", type1msg);

      if(!result)
        state(conn, POP3_AUTH_NTLM_TYPE2MSG);
    }
  }

  Curl_safefree(type1msg);

  return result;
}

/* For NTLM type-2 responses (sent in reponse to our type-1 message) */
static CURLcode pop3_state_auth_ntlm_type2msg_resp(struct connectdata *conn,
                                                   int pop3code,
                                                   pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  char *type2msg = NULL;
  char *type3msg = NULL;
  size_t len = 0;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    failf(data, "Access denied: %d", pop3code);
    result = CURLE_LOGIN_DENIED;
  }
  else {
    /* Get the type-2 message */
    pop3_get_message(data->state.buffer, &type2msg);

    /* Decode the type-2 message */
    result = Curl_sasl_decode_ntlm_type2_message(data, type2msg, &conn->ntlm);
    if(result) {
      /* Send the cancellation */
      result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s", "*");

      if(!result)
        state(conn, POP3_AUTH_CANCEL);
    }
    else {
      /* Create the type-3 message */
      result = Curl_sasl_create_ntlm_type3_message(data, conn->user,
                                                   conn->passwd, &conn->ntlm,
                                                   &type3msg, &len);
      if(!result && type3msg) {
        /* Send the message */
        result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s", type3msg);

        if(!result)
          state(conn, POP3_AUTH_FINAL);
      }
    }
  }

  Curl_safefree(type3msg);

  return result;
}
#endif

/* For AUTH XOAUTH2 (without initial response) responses */
static CURLcode pop3_state_auth_xoauth2_resp(struct connectdata *conn,
                                             int pop3code, pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  size_t len = 0;
  char *xoauth = NULL;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    failf(data, "Access denied: %d", pop3code);
    result = CURLE_LOGIN_DENIED;
  }
  else {
    /* Create the authorisation message */
    result = Curl_sasl_create_xoauth2_message(conn->data, conn->user,
                                              conn->xoauth2_bearer,
                                              &xoauth, &len);
    if(!result && xoauth) {
      /* Send the message */
      result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s", xoauth);

      if(!result)
        state(conn, POP3_AUTH_FINAL);
    }
  }

  Curl_safefree(xoauth);

  return result;
}

/* For AUTH cancellation responses */
static CURLcode pop3_state_auth_cancel_resp(struct connectdata *conn,
                                            int pop3code,
                                            pop3state instate)
{
  struct SessionHandle *data = conn->data;

  (void)pop3code;
  (void)instate; /* no use for this yet */

  failf(data, "Authentication cancelled");

  return CURLE_LOGIN_DENIED;
}

/* For final responses in the AUTH sequence */
static CURLcode pop3_state_auth_final_resp(struct connectdata *conn,
                                           int pop3code,
                                           pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    failf(data, "Authentication failed: %d", pop3code);
    result = CURLE_LOGIN_DENIED;
  }
  else
    /* End of connect phase */
    state(conn, POP3_STOP);

  return result;
}

#ifndef CURL_DISABLE_CRYPTO_AUTH
/* For APOP responses */
static CURLcode pop3_state_apop_resp(struct connectdata *conn, int pop3code,
                                     pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    failf(data, "Authentication failed: %d", pop3code);
    result = CURLE_LOGIN_DENIED;
  }
  else
    /* End of connect phase */
    state(conn, POP3_STOP);

  return result;
}
#endif

/* For USER responses */
static CURLcode pop3_state_user_resp(struct connectdata *conn, int pop3code,
                                     pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    failf(data, "Access denied. %c", pop3code);
    result = CURLE_LOGIN_DENIED;
  }
  else
    /* Send the PASS command */
    result = Curl_pp_sendf(&conn->proto.pop3c.pp, "PASS %s",
                           conn->passwd ? conn->passwd : "");
  if(!result)
    state(conn, POP3_PASS);

  return result;
}

/* For PASS responses */
static CURLcode pop3_state_pass_resp(struct connectdata *conn, int pop3code,
                                     pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    failf(data, "Access denied. %c", pop3code);
    result = CURLE_LOGIN_DENIED;
  }
  else
    /* End of connect phase */
    state(conn, POP3_STOP);

  return result;
}

/* For command responses */
static CURLcode pop3_state_command_resp(struct connectdata *conn,
                                        int pop3code,
                                        pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct POP3 *pop3 = data->req.protop;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  struct pingpong *pp = &pop3c->pp;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    state(conn, POP3_STOP);
    return CURLE_RECV_ERROR;
  }

  /* This 'OK' line ends with a CR LF pair which is the two first bytes of the
     EOB string so count this is two matching bytes. This is necessary to make
     the code detect the EOB if the only data than comes now is %2e CR LF like
     when there is no body to return. */
  pop3c->eob = 2;

  /* But since this initial CR LF pair is not part of the actual body, we set
     the strip counter here so that these bytes won't be delivered. */
  pop3c->strip = 2;

  if(pop3->transfer == FTPTRANSFER_BODY) {
    /* POP3 download */
    Curl_setup_transfer(conn, FIRSTSOCKET, -1, FALSE, NULL, -1, NULL);

    if(pp->cache) {
      /* The header "cache" contains a bunch of data that is actually body
         content so send it as such. Note that there may even be additional
         "headers" after the body */

      if(!data->set.opt_no_body) {
        result = Curl_pop3_write(conn, pp->cache, pp->cache_size);
        if(result)
          return result;
      }

      /* Free the cache */
      Curl_safefree(pp->cache);

      /* Reset the cache size */
      pp->cache_size = 0;
    }
  }

  /* End of DO phase */
  state(conn, POP3_STOP);

  return result;
}

static CURLcode pop3_statemach_act(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  curl_socket_t sock = conn->sock[FIRSTSOCKET];
  int pop3code;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  struct pingpong *pp = &pop3c->pp;
  size_t nread = 0;

  /* Busy upgrading the connection; right now all I/O is SSL/TLS, not POP3 */
  if(pop3c->state == POP3_UPGRADETLS)
    return pop3_perform_upgrade_tls(conn);

  /* Flush any data that needs to be sent */
  if(pp->sendleft)
    return Curl_pp_flushsend(pp);

  /* Read the response from the server */
  result = Curl_pp_readresp(sock, pp, &pop3code, &nread);
  if(result)
    return result;

  if(pop3code) {
    /* We have now received a full POP3 server response */
    switch(pop3c->state) {
    case POP3_SERVERGREET:
      result = pop3_state_servergreet_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_CAPA:
      result = pop3_state_capa_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_STARTTLS:
      result = pop3_state_starttls_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_PLAIN:
      result = pop3_state_auth_plain_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_LOGIN:
      result = pop3_state_auth_login_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_LOGIN_PASSWD:
      result = pop3_state_auth_login_password_resp(conn, pop3code,
                                                   pop3c->state);
      break;

#ifndef CURL_DISABLE_CRYPTO_AUTH
    case POP3_AUTH_CRAMMD5:
      result = pop3_state_auth_cram_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_DIGESTMD5:
      result = pop3_state_auth_digest_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_DIGESTMD5_RESP:
      result = pop3_state_auth_digest_resp_resp(conn, pop3code, pop3c->state);
      break;
#endif

#ifdef USE_NTLM
    case POP3_AUTH_NTLM:
      result = pop3_state_auth_ntlm_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_NTLM_TYPE2MSG:
      result = pop3_state_auth_ntlm_type2msg_resp(conn, pop3code,
                                                  pop3c->state);
      break;
#endif

    case POP3_AUTH_XOAUTH2:
      result = pop3_state_auth_xoauth2_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_CANCEL:
      result = pop3_state_auth_cancel_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_AUTH_FINAL:
      result = pop3_state_auth_final_resp(conn, pop3code, pop3c->state);
      break;

#ifndef CURL_DISABLE_CRYPTO_AUTH
    case POP3_APOP:
      result = pop3_state_apop_resp(conn, pop3code, pop3c->state);
      break;
#endif

    case POP3_USER:
      result = pop3_state_user_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_PASS:
      result = pop3_state_pass_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_COMMAND:
      result = pop3_state_command_resp(conn, pop3code, pop3c->state);
      break;

    case POP3_QUIT:
      /* fallthrough, just stop! */
    default:
      /* internal error */
      state(conn, POP3_STOP);
      break;
    }
  }

  return result;
}

/* Called repeatedly until done from multi.c */
static CURLcode pop3_multi_statemach(struct connectdata *conn, bool *done)
{
  CURLcode result = CURLE_OK;
  struct pop3_conn *pop3c = &conn->proto.pop3c;

  if((conn->handler->flags & PROTOPT_SSL) && !pop3c->ssldone) {
    result = Curl_ssl_connect_nonblocking(conn, FIRSTSOCKET, &pop3c->ssldone);
    if(result || !pop3c->ssldone)
      return result;
  }

  result = Curl_pp_statemach(&pop3c->pp, FALSE);
  *done = (pop3c->state == POP3_STOP) ? TRUE : FALSE;

  return result;
}

static CURLcode pop3_block_statemach(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct pop3_conn *pop3c = &conn->proto.pop3c;

  while(pop3c->state != POP3_STOP && !result)
    result = Curl_pp_statemach(&pop3c->pp, TRUE);

  return result;
}

/* Allocate and initialize the POP3 struct for the current SessionHandle if
   required */
static CURLcode pop3_init(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct POP3 *pop3;

  pop3 = data->req.protop = calloc(sizeof(struct POP3), 1);
  if(!pop3)
    result = CURLE_OUT_OF_MEMORY;

  return result;
}

/* For the POP3 "protocol connect" and "doing" phases only */
static int pop3_getsock(struct connectdata *conn, curl_socket_t *socks,
                        int numsocks)
{
  return Curl_pp_getsock(&conn->proto.pop3c.pp, socks, numsocks);
}

/***********************************************************************
 *
 * pop3_connect()
 *
 * This function should do everything that is to be considered a part of the
 * connection phase.
 *
 * The variable 'done' points to will be TRUE if the protocol-layer connect
 * phase is done when this function returns, or FALSE if not.
 */
static CURLcode pop3_connect(struct connectdata *conn, bool *done)
{
  CURLcode result = CURLE_OK;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  struct pingpong *pp = &pop3c->pp;

  *done = FALSE; /* default to not done yet */

  /* We always support persistent connections in POP3 */
  conn->bits.close = FALSE;

  /* Set the default response time-out */
  pp->response_time = RESP_TIMEOUT;
  pp->statemach_act = pop3_statemach_act;
  pp->endofresp = pop3_endofresp;
  pp->conn = conn;

  /* Set the default preferred authentication type and mechanism */
  pop3c->preftype = POP3_TYPE_ANY;
  pop3c->prefmech = SASL_AUTH_ANY;

  /* Initialise the pingpong layer */
  Curl_pp_init(pp);

  /* Parse the URL options */
  result = pop3_parse_url_options(conn);
  if(result)
    return result;

  /* Start off waiting for the server greeting response */
  state(conn, POP3_SERVERGREET);

  result = pop3_multi_statemach(conn, done);

  return result;
}

/***********************************************************************
 *
 * pop3_done()
 *
 * The DONE function. This does what needs to be done after a single DO has
 * performed.
 *
 * Input argument is already checked for validity.
 */
static CURLcode pop3_done(struct connectdata *conn, CURLcode status,
                          bool premature)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct POP3 *pop3 = data->req.protop;

  (void)premature;

  if(!pop3)
    /* When the easy handle is removed from the multi interface while libcurl
       is still trying to resolve the host name, the POP3 struct is not yet
       initialized. However, the removal action calls Curl_done() which in
       turn calls this function, so we simply return success. */
    return CURLE_OK;

  if(status) {
    conn->bits.close = TRUE; /* marked for closure */
    result = status;         /* use the already set error code */
  }

  /* Cleanup our per-request based variables */
  Curl_safefree(pop3->id);
  Curl_safefree(pop3->custom);

  /* Clear the transfer mode for the next request */
  pop3->transfer = FTPTRANSFER_BODY;

  return result;
}

/***********************************************************************
 *
 * pop3_perform()
 *
 * This is the actual DO function for POP3. Get a message/listing according to
 * the options previously setup.
 */
static CURLcode pop3_perform(struct connectdata *conn, bool *connected,
                             bool *dophase_done)
{
  /* This is POP3 and no proxy */
  CURLcode result = CURLE_OK;
  struct POP3 *pop3 = conn->data->req.protop;

  DEBUGF(infof(conn->data, "DO phase starts\n"));

  if(conn->data->set.opt_no_body) {
    /* Requested no body means no transfer */
    pop3->transfer = FTPTRANSFER_INFO;
  }

  *dophase_done = FALSE; /* not done yet */

  /* Start the first command in the DO phase */
  result = pop3_perform_command(conn);
  if(result)
    return result;

  /* Run the state-machine */
  result = pop3_multi_statemach(conn, dophase_done);

  *connected = conn->bits.tcpconnect[FIRSTSOCKET];

  if(*dophase_done)
    DEBUGF(infof(conn->data, "DO phase is complete\n"));

  return result;
}

/***********************************************************************
 *
 * pop3_do()
 *
 * This function is registered as 'curl_do' function. It decodes the path
 * parts etc as a wrapper to the actual DO function (pop3_perform).
 *
 * The input argument is already checked for validity.
 */
static CURLcode pop3_do(struct connectdata *conn, bool *done)
{
  CURLcode result = CURLE_OK;

  *done = FALSE; /* default to false */

  /* Parse the URL path */
  result = pop3_parse_url_path(conn);
  if(result)
    return result;

  /* Parse the custom request */
  result = pop3_parse_custom_request(conn);
  if(result)
    return result;

  result = pop3_regular_transfer(conn, done);

  return result;
}

/***********************************************************************
 *
 * pop3_disconnect()
 *
 * Disconnect from an POP3 server. Cleanup protocol-specific per-connection
 * resources. BLOCKING.
 */
static CURLcode pop3_disconnect(struct connectdata *conn, bool dead_connection)
{
  struct pop3_conn *pop3c = &conn->proto.pop3c;

  /* We cannot send quit unconditionally. If this connection is stale or
     bad in any way, sending quit and waiting around here will make the
     disconnect wait in vain and cause more problems than we need to. */

  /* The POP3 session may or may not have been allocated/setup at this
     point! */
  if(!dead_connection && pop3c->pp.conn && pop3c->pp.conn->bits.protoconnstart)
    if(!pop3_perform_quit(conn))
      (void)pop3_block_statemach(conn); /* ignore errors on QUIT */

  /* Disconnect from the server */
  Curl_pp_disconnect(&pop3c->pp);

  /* Cleanup the SASL module */
  Curl_sasl_cleanup(conn, pop3c->authused);

  /* Cleanup our connection based variables */
  Curl_safefree(pop3c->apoptimestamp);

  return CURLE_OK;
}

/* Call this when the DO phase has completed */
static CURLcode pop3_dophase_done(struct connectdata *conn, bool connected)
{
  (void)conn;
  (void)connected;

  return CURLE_OK;
}

/* Called from multi.c while DOing */
static CURLcode pop3_doing(struct connectdata *conn, bool *dophase_done)
{
  CURLcode result = pop3_multi_statemach(conn, dophase_done);

  if(result)
    DEBUGF(infof(conn->data, "DO phase failed\n"));
  else if(*dophase_done) {
    result = pop3_dophase_done(conn, FALSE /* not connected */);

    DEBUGF(infof(conn->data, "DO phase is complete\n"));
  }

  return result;
}

/***********************************************************************
 *
 * pop3_regular_transfer()
 *
 * The input argument is already checked for validity.
 *
 * Performs all commands done before a regular transfer between a local and a
 * remote host.
 */
static CURLcode pop3_regular_transfer(struct connectdata *conn,
                                      bool *dophase_done)
{
  CURLcode result = CURLE_OK;
  bool connected = FALSE;
  struct SessionHandle *data = conn->data;

  /* Make sure size is unknown at this point */
  data->req.size = -1;

  /* Set the progress data */
  Curl_pgrsSetUploadCounter(data, 0);
  Curl_pgrsSetDownloadCounter(data, 0);
  Curl_pgrsSetUploadSize(data, 0);
  Curl_pgrsSetDownloadSize(data, 0);

  /* Carry out the perform */
  result = pop3_perform(conn, &connected, dophase_done);

  /* Perform post DO phase operations if necessary */
  if(!result && *dophase_done)
    result = pop3_dophase_done(conn, connected);

  return result;
}

static CURLcode pop3_setup_connection(struct connectdata *conn)
{
  struct SessionHandle *data = conn->data;

  /* Initialise the POP3 layer */
  CURLcode result = pop3_init(conn);
  if(result)
    return result;

  if(conn->bits.httpproxy && !data->set.tunnel_thru_httpproxy) {
    /* Unless we have asked to tunnel POP3 operations through the proxy, we
       switch and use HTTP operations only */
#ifndef CURL_DISABLE_HTTP
    if(conn->handler == &Curl_handler_pop3)
      conn->handler = &Curl_handler_pop3_proxy;
    else {
#ifdef USE_SSL
      conn->handler = &Curl_handler_pop3s_proxy;
#else
      failf(data, "POP3S not supported!");
      return CURLE_UNSUPPORTED_PROTOCOL;
#endif
    }

    /* set it up as an HTTP connection instead */
    return conn->handler->setup_connection(conn);
#else
    failf(data, "POP3 over http proxy requires HTTP support built-in!");
    return CURLE_UNSUPPORTED_PROTOCOL;
#endif
  }

  data->state.path++;   /* don't include the initial slash */

  return CURLE_OK;
}

/***********************************************************************
 *
 * pop3_parse_url_options()
 *
 * Parse the URL login options.
 */
static CURLcode pop3_parse_url_options(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  const char *options = conn->options;
  const char *ptr = options;

  if(options) {
    const char *key = ptr;

    while(*ptr && *ptr != '=')
        ptr++;

    if(strnequal(key, "AUTH", 4)) {
      const char *value = ptr + 1;

      if(strequal(value, "*")) {
        pop3c->preftype = POP3_TYPE_ANY;
        pop3c->prefmech = SASL_AUTH_ANY;
      }
      else if(strequal(value, "+APOP")) {
        pop3c->preftype = POP3_TYPE_APOP;
        pop3c->prefmech = SASL_AUTH_NONE;
      }
      else if(strequal(value, SASL_MECH_STRING_LOGIN)) {
        pop3c->preftype = POP3_TYPE_SASL;
        pop3c->prefmech = SASL_MECH_LOGIN;
      }
      else if(strequal(value, SASL_MECH_STRING_PLAIN)) {
        pop3c->preftype = POP3_TYPE_SASL;
        pop3c->prefmech = SASL_MECH_PLAIN;
      }
      else if(strequal(value, SASL_MECH_STRING_CRAM_MD5)) {
        pop3c->preftype = POP3_TYPE_SASL;
        pop3c->prefmech = SASL_MECH_CRAM_MD5;
      }
      else if(strequal(value, SASL_MECH_STRING_DIGEST_MD5)) {
        pop3c->preftype = POP3_TYPE_SASL;
        pop3c->prefmech = SASL_MECH_DIGEST_MD5;
      }
      else if(strequal(value, SASL_MECH_STRING_GSSAPI)) {
        pop3c->preftype = POP3_TYPE_SASL;
        pop3c->prefmech = SASL_MECH_GSSAPI;
      }
      else if(strequal(value, SASL_MECH_STRING_NTLM)) {
        pop3c->preftype = POP3_TYPE_SASL;
        pop3c->prefmech = SASL_MECH_NTLM;
      }
      else if(strequal(value, SASL_MECH_STRING_XOAUTH2)) {
        pop3c->preftype = POP3_TYPE_SASL;
        pop3c->prefmech = SASL_MECH_XOAUTH2;
      }
      else {
        pop3c->preftype = POP3_TYPE_NONE;
        pop3c->prefmech = SASL_AUTH_NONE;
      }
    }
    else
      result = CURLE_URL_MALFORMAT;
  }

  return result;
}

/***********************************************************************
 *
 * pop3_parse_url_path()
 *
 * Parse the URL path into separate path components.
 */
static CURLcode pop3_parse_url_path(struct connectdata *conn)
{
  /* The POP3 struct is already initialised in pop3_connect() */
  struct SessionHandle *data = conn->data;
  struct POP3 *pop3 = data->req.protop;
  const char *path = data->state.path;

  /* URL decode the path for the message ID */
  return Curl_urldecode(data, path, 0, &pop3->id, NULL, TRUE);
}

/***********************************************************************
 *
 * pop3_parse_custom_request()
 *
 * Parse the custom request.
 */
static CURLcode pop3_parse_custom_request(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct POP3 *pop3 = data->req.protop;
  const char *custom = data->set.str[STRING_CUSTOMREQUEST];

  /* URL decode the custom request */
  if(custom)
    result = Curl_urldecode(data, custom, 0, &pop3->custom, NULL, TRUE);

  return result;
}

/***********************************************************************
 *
 * Curl_pop3_write()
 *
 * This function scans the body after the end-of-body and writes everything
 * until the end is found.
 */
CURLcode Curl_pop3_write(struct connectdata *conn, char *str, size_t nread)
{
  /* This code could be made into a special function in the handler struct */
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct SingleRequest *k = &data->req;

  struct pop3_conn *pop3c = &conn->proto.pop3c;
  bool strip_dot = FALSE;
  size_t last = 0;
  size_t i;

  /* Search through the buffer looking for the end-of-body marker which is
     5 bytes (0d 0a 2e 0d 0a). Note that a line starting with a dot matches
     the eob so the server will have prefixed it with an extra dot which we
     need to strip out. Additionally the marker could of course be spread out
     over 5 different data chunks. */
  for(i = 0; i < nread; i++) {
    size_t prev = pop3c->eob;

    switch(str[i]) {
    case 0x0d:
      if(pop3c->eob == 0) {
        pop3c->eob++;

        if(i) {
          /* Write out the body part that didn't match */
          result = Curl_client_write(conn, CLIENTWRITE_BODY, &str[last],
                                     i - last);

          if(result)
            return result;

          last = i;
        }
      }
      else if(pop3c->eob == 3)
        pop3c->eob++;
      else
        /* If the character match wasn't at position 0 or 3 then restart the
           pattern matching */
        pop3c->eob = 1;
      break;

    case 0x0a:
      if(pop3c->eob == 1 || pop3c->eob == 4)
        pop3c->eob++;
      else
        /* If the character match wasn't at position 1 or 4 then start the
           search again */
        pop3c->eob = 0;
      break;

    case 0x2e:
      if(pop3c->eob == 2)
        pop3c->eob++;
      else if(pop3c->eob == 3) {
        /* We have an extra dot after the CRLF which we need to strip off */
        strip_dot = TRUE;
        pop3c->eob = 0;
      }
      else
        /* If the character match wasn't at position 2 then start the search
           again */
        pop3c->eob = 0;
      break;

    default:
      pop3c->eob = 0;
      break;
    }

    /* Did we have a partial match which has subsequently failed? */
    if(prev && prev >= pop3c->eob) {
      /* Strip can only be non-zero for the very first mismatch after CRLF
         and then both prev and strip are equal and nothing will be output
         below */
      while(prev && pop3c->strip) {
        prev--;
        pop3c->strip--;
      }

      if(prev) {
        /* If the partial match was the CRLF and dot then only write the CRLF
           as the server would have inserted the dot */
        result = Curl_client_write(conn, CLIENTWRITE_BODY, (char*)POP3_EOB,
                                   strip_dot ? prev - 1 : prev);

        if(result)
          return result;

        last = i;
        strip_dot = FALSE;
      }
    }
  }

  if(pop3c->eob == POP3_EOB_LEN) {
    /* We have a full match so the transfer is done, however we must transfer
    the CRLF at the start of the EOB as this is considered to be part of the
    message as per RFC-1939, sect. 3 */
    result = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)POP3_EOB, 2);

    k->keepon &= ~KEEP_RECV;
    pop3c->eob = 0;

    return result;
  }

  if(pop3c->eob)
    /* While EOB is matching nothing should be output */
    return CURLE_OK;

  if(nread - last) {
    result = Curl_client_write(conn, CLIENTWRITE_BODY, &str[last],
                               nread - last);
  }

  return result;
}

#endif /* CURL_DISABLE_POP3 */
