#ifndef HEADER_CURL_SSH_H
#define HEADER_CURL_SSH_H
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

#ifdef HAVE_LIBSSH2_H
#include <libssh2.h>
#include <libssh2_sftp.h>
#endif /* HAVE_LIBSSH2_H */

/****************************************************************************
 * SSH unique setup
 ***************************************************************************/
typedef enum {
  SSH_NO_STATE = -1,  /* Used for "nextState" so say there is none */
  SSH_STOP = 0,       /* do nothing state, stops the state machine */

  SSH_INIT,           /* First state in SSH-CONNECT */
  SSH_S_STARTUP,      /* Session startup */
  SSH_HOSTKEY,        /* verify hostkey */
  SSH_AUTHLIST,
  SSH_AUTH_PKEY_INIT,
  SSH_AUTH_PKEY,
  SSH_AUTH_PASS_INIT,
  SSH_AUTH_PASS,
  SSH_AUTH_AGENT_INIT,/* initialize then wait for connection to agent */
  SSH_AUTH_AGENT_LIST,/* ask for list then wait for entire list to come */
  SSH_AUTH_AGENT,     /* attempt one key at a time */
  SSH_AUTH_HOST_INIT,
  SSH_AUTH_HOST,
  SSH_AUTH_KEY_INIT,
  SSH_AUTH_KEY,
  SSH_AUTH_DONE,
  SSH_SFTP_INIT,
  SSH_SFTP_REALPATH,   /* Last state in SSH-CONNECT */

  SSH_SFTP_QUOTE_INIT, /* First state in SFTP-DO */
  SSH_SFTP_POSTQUOTE_INIT, /* (Possibly) First state in SFTP-DONE */
  SSH_SFTP_QUOTE,
  SSH_SFTP_NEXT_QUOTE,
  SSH_SFTP_QUOTE_STAT,
  SSH_SFTP_QUOTE_SETSTAT,
  SSH_SFTP_QUOTE_SYMLINK,
  SSH_SFTP_QUOTE_MKDIR,
  SSH_SFTP_QUOTE_RENAME,
  SSH_SFTP_QUOTE_RMDIR,
  SSH_SFTP_QUOTE_UNLINK,
  SSH_SFTP_TRANS_INIT,
  SSH_SFTP_UPLOAD_INIT,
  SSH_SFTP_CREATE_DIRS_INIT,
  SSH_SFTP_CREATE_DIRS,
  SSH_SFTP_CREATE_DIRS_MKDIR,
  SSH_SFTP_READDIR_INIT,
  SSH_SFTP_READDIR,
  SSH_SFTP_READDIR_LINK,
  SSH_SFTP_READDIR_BOTTOM,
  SSH_SFTP_READDIR_DONE,
  SSH_SFTP_DOWNLOAD_INIT,
  SSH_SFTP_DOWNLOAD_STAT, /* Last state in SFTP-DO */
  SSH_SFTP_CLOSE,    /* Last state in SFTP-DONE */
  SSH_SFTP_SHUTDOWN, /* First state in SFTP-DISCONNECT */
  SSH_SCP_TRANS_INIT, /* First state in SCP-DO */
  SSH_SCP_UPLOAD_INIT,
  SSH_SCP_DOWNLOAD_INIT,
  SSH_SCP_DONE,
  SSH_SCP_SEND_EOF,
  SSH_SCP_WAIT_EOF,
  SSH_SCP_WAIT_CLOSE,
  SSH_SCP_CHANNEL_FREE,   /* Last state in SCP-DONE */
  SSH_SESSION_DISCONNECT, /* First state in SCP-DISCONNECT */
  SSH_SESSION_FREE,       /* Last state in SCP/SFTP-DISCONNECT */
  SSH_QUIT,
  SSH_LAST  /* never used */
} sshstate;

/* this struct is used in the HandleData struct which is part of the
   SessionHandle, which means this is used on a per-easy handle basis.
   Everything that is strictly related to a connection is banned from this
   struct. */
struct SSHPROTO {
  char *path;                  /* the path we operate on */
};

/* ssh_conn is used for struct connection-oriented data in the connectdata
   struct */
struct ssh_conn {
  const char *authlist;       /* List of auth. methods, managed by libssh2 */
#ifdef USE_LIBSSH2
  const char *passphrase;     /* pass-phrase to use */
  char *rsa_pub;              /* path name */
  char *rsa;                  /* path name */
  bool authed;                /* the connection has been authenticated fine */
  sshstate state;             /* always use ssh.c:state() to change state! */
  sshstate nextstate;         /* the state to goto after stopping */
  CURLcode actualcode;        /* the actual error code */
  struct curl_slist *quote_item; /* for the quote option */
  char *quote_path1;          /* two generic pointers for the QUOTE stuff */
  char *quote_path2;
  LIBSSH2_SFTP_ATTRIBUTES quote_attrs; /* used by the SFTP_QUOTE state */
  bool acceptfail;            /* used by the SFTP_QUOTE (continue if
                                 quote command fails) */
  char *homedir;              /* when doing SFTP we figure out home dir in the
                                 connect phase */

  /* Here's a set of struct members used by the SFTP_READDIR state */
  LIBSSH2_SFTP_ATTRIBUTES readdir_attrs;
  char *readdir_filename;
  char *readdir_longentry;
  int readdir_len, readdir_totalLen, readdir_currLen;
  char *readdir_line;
  char *readdir_linkPath;
  /* end of READDIR stuff */

  int secondCreateDirs;         /* counter use by the code to see if the
                                   second attempt has been made to change
                                   to/create a directory */
  char *slash_pos;              /* used by the SFTP_CREATE_DIRS state */
  LIBSSH2_SESSION *ssh_session; /* Secure Shell session */
  LIBSSH2_CHANNEL *ssh_channel; /* Secure Shell channel handle */
  LIBSSH2_SFTP *sftp_session;   /* SFTP handle */
  LIBSSH2_SFTP_HANDLE *sftp_handle;
  int orig_waitfor;             /* default READ/WRITE bits wait for */

#ifdef HAVE_LIBSSH2_AGENT_API
  LIBSSH2_AGENT *ssh_agent;     /* proxy to ssh-agent/pageant */
  struct libssh2_agent_publickey *sshagent_identity,
                                 *sshagent_prev_identity;
#endif

  /* note that HAVE_LIBSSH2_KNOWNHOST_API is a define set in the libssh2.h
     header */
#ifdef HAVE_LIBSSH2_KNOWNHOST_API
  LIBSSH2_KNOWNHOSTS *kh;
#endif
#endif /* USE_LIBSSH2 */
};

#ifdef USE_LIBSSH2

#if !defined(LIBSSH2_VERSION_NUM) || (LIBSSH2_VERSION_NUM < 0x001000)
#  error "SCP/SFTP protocols require libssh2 0.16 or later"
#endif

#if defined(LIBSSH2_VERSION_NUM) && (LIBSSH2_VERSION_NUM >= 0x010000)
#  define HAVE_LIBSSH2_SFTP_SEEK64 1
#else
#  undef HAVE_LIBSSH2_SFTP_SEEK64
#endif

#if defined(LIBSSH2_VERSION_NUM) && (LIBSSH2_VERSION_NUM >= 0x010206)
#  define HAVE_LIBSSH2_SCP_SEND64 1
#else
#  undef HAVE_LIBSSH2_SCP_SEND64
#endif


extern const struct Curl_handler Curl_handler_scp;
extern const struct Curl_handler Curl_handler_sftp;

#endif /* USE_LIBSSH2 */

#endif /* HEADER_CURL_SSH_H */
