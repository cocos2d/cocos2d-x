#ifndef __CURL_CURL_H
#define __CURL_CURL_H
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/

/*
 * If you have libcurl problems, all docs and details are found here:
 *   https://curl.haxx.se/libcurl/
 *
 * curl-library mailing list subscription and unsubscription web interface:
 *   https://cool.haxx.se/mailman/listinfo/curl-library/
 */

#include "curlver.h"         /* libcurl version defines   */
#include "curlbuild.h"       /* libcurl build definitions */
#include "curlrules.h"       /* libcurl rules enforcement */

/*
 * Define WIN32 when build target is Win32 API
 */

#if (defined(_WIN32) || defined(__WIN32__)) && \
     !defined(WIN32) && !defined(__SYMBIAN32__)
#define WIN32
#endif

#include <stdio.h>
#include <limits.h>

#if defined(__FreeBSD__) && (__FreeBSD__ >= 2)
/* Needed for __FreeBSD_version symbol definition */
#include <osreldate.h>
#endif

/* The include stuff here below is mainly for time_t! */
#include <sys/types.h>
#include <time.h>

#if defined(WIN32) && !defined(_WIN32_WCE) && !defined(__CYGWIN__)
#if !(defined(_WINSOCKAPI_) || defined(_WINSOCK_H) || \
      defined(__LWIP_OPT_H__) || defined(LWIP_HDR_OPT_H))
/* The check above prevents the winsock2 inclusion if winsock.h already was
   included, since they can't co-exist without problems */
#include <winsock2.h>
#include <ws2tcpip.h>
#endif
#endif

/* HP-UX systems version 9, 10 and 11 lack sys/select.h and so does oldish
   libc5-based Linux systems. Only include it on systems that are known to
   require it! */
#if defined(_AIX) || defined(__NOVELL_LIBC__) || defined(__NetBSD__) || \
    defined(__minix) || defined(__SYMBIAN32__) || defined(__INTEGRITY) || \
    defined(ANDROID) || defined(__ANDROID__) || defined(__OpenBSD__) || \
   (defined(__FreeBSD_version) && (__FreeBSD_version < 800000))
#include <sys/select.h>
#endif

#if !defined(WIN32) && !defined(_WIN32_WCE)
#include <sys/socket.h>
#endif

#if !defined(WIN32) && !defined(__WATCOMC__) && !defined(__VXWORKS__)
#include <sys/time.h>
#endif

#ifdef __BEOS__
#include <support/SupportDefs.h>
#endif

#ifdef  __cplusplus
extern "C" {
#endif

typedef void CURL;

/*
 * libcurl external API function linkage decorations.
 */

#ifdef CURL_STATICLIB
#  define CURL_EXTERN
#elif defined(WIN32) || defined(_WIN32) || defined(__SYMBIAN32__)
#  if defined(BUILDING_LIBCURL)
#    define CURL_EXTERN  __declspec(dllexport)
#  else
#    define CURL_EXTERN  __declspec(dllimport)
#  endif
#elif defined(BUILDING_LIBCURL) && defined(CURL_HIDDEN_SYMBOLS)
#  define CURL_EXTERN CURL_EXTERN_SYMBOL
#else
#  define CURL_EXTERN
#endif

#ifndef curl_socket_typedef
/* socket typedef */
#if defined(WIN32) && !defined(__LWIP_OPT_H__) && !defined(LWIP_HDR_OPT_H)
typedef SOCKET curl_socket_t;
#define CURL_SOCKET_BAD INVALID_SOCKET
#else
typedef int curl_socket_t;
#define CURL_SOCKET_BAD -1
#endif
#define curl_socket_typedef
#endif /* curl_socket_typedef */

struct curl_httppost {
  struct curl_httppost *next;       /* next entry in the list */
  char *name;                       /* pointer to allocated name */
  long namelength;                  /* length of name length */
  char *contents;                   /* pointer to allocated data contents */
  long contentslength;              /* length of contents field, see also
                                       CURL_HTTPPOST_LARGE */
  char *buffer;                     /* pointer to allocated buffer contents */
  long bufferlength;                /* length of buffer field */
  char *contenttype;                /* Content-Type */
  struct curl_slist* contentheader; /* list of extra headers for this form */
  struct curl_httppost *more;       /* if one field name has more than one
                                       file, this link should link to following
                                       files */
  long flags;                       /* as defined below */

/* specified content is a file name */
#define CURL_HTTPPOST_FILENAME (1<<0)
/* specified content is a file name */
#define CURL_HTTPPOST_READFILE (1<<1)
/* name is only stored pointer do not free in formfree */
#define CURL_HTTPPOST_PTRNAME (1<<2)
/* contents is only stored pointer do not free in formfree */
#define CURL_HTTPPOST_PTRCONTENTS (1<<3)
/* upload file from buffer */
#define CURL_HTTPPOST_BUFFER (1<<4)
/* upload file from pointer contents */
#define CURL_HTTPPOST_PTRBUFFER (1<<5)
/* upload file contents by using the regular read callback to get the data and
   pass the given pointer as custom pointer */
#define CURL_HTTPPOST_CALLBACK (1<<6)
/* use size in 'contentlen', added in 7.46.0 */
#define CURL_HTTPPOST_LARGE (1<<7)

  char *showfilename;               /* The file name to show. If not set, the
                                       actual file name will be used (if this
                                       is a file part) */
  void *userp;                      /* custom pointer used for
                                       HTTPPOST_CALLBACK posts */
  curl_off_t contentlen;            /* alternative length of contents
                                       field. Used if CURL_HTTPPOST_LARGE is
                                       set. Added in 7.46.0 */
};

/* This is the CURLOPT_PROGRESSFUNCTION callback proto. It is now considered
   deprecated but was the only choice up until 7.31.0 */
typedef int (*curl_progress_callback)(void *clientp,
                                      double dltotal,
                                      double dlnow,
                                      double ultotal,
                                      double ulnow);

/* This is the CURLOPT_XFERINFOFUNCTION callback proto. It was introduced in
   7.32.0, it avoids floating point and provides more detailed information. */
typedef int (*curl_xferinfo_callback)(void *clientp,
                                      curl_off_t dltotal,
                                      curl_off_t dlnow,
                                      curl_off_t ultotal,
                                      curl_off_t ulnow);

#ifndef CURL_MAX_WRITE_SIZE
  /* Tests have proven that 20K is a very bad buffer size for uploads on
     Windows, while 16K for some odd reason performed a lot better.
     We do the ifndef check to allow this value to easier be changed at build
     time for those who feel adventurous. The practical minimum is about
     400 bytes since libcurl uses a buffer of this size as a scratch area
     (unrelated to network send operations). */
#define CURL_MAX_WRITE_SIZE 16384
#endif

#ifndef CURL_MAX_HTTP_HEADER
/* The only reason to have a max limit for this is to avoid the risk of a bad
   server feeding libcurl with a never-ending header that will cause reallocs
   infinitely */
#define CURL_MAX_HTTP_HEADER (100*1024)
#endif

/* This is a magic return code for the write callback that, when returned,
   will signal libcurl to pause receiving on the current transfer. */
#define CURL_WRITEFUNC_PAUSE 0x10000001

typedef size_t (*curl_write_callback)(char *buffer,
                                      size_t size,
                                      size_t nitems,
                                      void *outstream);



/* enumeration of file types */
typedef enum {
  CURLFILETYPE_FILE = 0,
  CURLFILETYPE_DIRECTORY,
  CURLFILETYPE_SYMLINK,
  CURLFILETYPE_DEVICE_BLOCK,
  CURLFILETYPE_DEVICE_CHAR,
  CURLFILETYPE_NAMEDPIPE,
  CURLFILETYPE_SOCKET,
  CURLFILETYPE_DOOR, /* is possible only on Sun Solaris now */

  CURLFILETYPE_UNKNOWN /* should never occur */
} curlfiletype;

#define CURLFINFOFLAG_KNOWN_FILENAME    (1<<0)
#define CURLFINFOFLAG_KNOWN_FILETYPE    (1<<1)
#define CURLFINFOFLAG_KNOWN_TIME        (1<<2)
#define CURLFINFOFLAG_KNOWN_PERM        (1<<3)
#define CURLFINFOFLAG_KNOWN_UID         (1<<4)
#define CURLFINFOFLAG_KNOWN_GID         (1<<5)
#define CURLFINFOFLAG_KNOWN_SIZE        (1<<6)
#define CURLFINFOFLAG_KNOWN_HLINKCOUNT  (1<<7)

/* Content of this structure depends on information which is known and is
   achievable (e.g. by FTP LIST parsing). Please see the url_easy_setopt(3) man
   page for callbacks returning this structure -- some fields are mandatory,
   some others are optional. The FLAG field has special meaning. */
struct curl_fileinfo {
  char *filename;
  curlfiletype filetype;
  time_t time;
  unsigned int perm;
  int uid;
  int gid;
  curl_off_t size;
  long int hardlinks;

  struct {
    /* If some of these fields is not NULL, it is a pointer to b_data. */
    char *time;
    char *perm;
    char *user;
    char *group;
    char *target; /* pointer to the target filename of a symlink */
  } strings;

  unsigned int flags;

  /* used internally */
  char * b_data;
  size_t b_size;
  size_t b_used;
};

/* return codes for CURLOPT_CHUNK_BGN_FUNCTION */
#define CURL_CHUNK_BGN_FUNC_OK      0
#define CURL_CHUNK_BGN_FUNC_FAIL    1 /* tell the lib to end the task */
#define CURL_CHUNK_BGN_FUNC_SKIP    2 /* skip this chunk over */

/* if splitting of data transfer is enabled, this callback is called before
   download of an individual chunk started. Note that parameter "remains" works
   only for FTP wildcard downloading (for now), otherwise is not used */
typedef long (*curl_chunk_bgn_callback)(const void *transfer_info,
                                        void *ptr,
                                        int remains);

/* return codes for CURLOPT_CHUNK_END_FUNCTION */
#define CURL_CHUNK_END_FUNC_OK      0
#define CURL_CHUNK_END_FUNC_FAIL    1 /* tell the lib to end the task */

/* If splitting of data transfer is enabled this callback is called after
   download of an individual chunk finished.
   Note! After this callback was set then it have to be called FOR ALL chunks.
   Even if downloading of this chunk was skipped in CHUNK_BGN_FUNC.
   This is the reason why we don't need "transfer_info" parameter in this
   callback and we are not interested in "remains" parameter too. */
typedef long (*curl_chunk_end_callback)(void *ptr);

/* return codes for FNMATCHFUNCTION */
#define CURL_FNMATCHFUNC_MATCH    0 /* string corresponds to the pattern */
#define CURL_FNMATCHFUNC_NOMATCH  1 /* pattern doesn't match the string */
#define CURL_FNMATCHFUNC_FAIL     2 /* an error occurred */

/* callback type for wildcard downloading pattern matching. If the
   string matches the pattern, return CURL_FNMATCHFUNC_MATCH value, etc. */
typedef int (*curl_fnmatch_callback)(void *ptr,
                                     const char *pattern,
                                     const char *string);

/* These are the return codes for the seek callbacks */
#define CURL_SEEKFUNC_OK       0
#define CURL_SEEKFUNC_FAIL     1 /* fail the entire transfer */
#define CURL_SEEKFUNC_CANTSEEK 2 /* tell libcurl seeking can't be done, so
                                    libcurl might try other means instead */
typedef int (*curl_seek_callback)(void *instream,
                                  curl_off_t offset,
                                  int origin); /* 'whence' */

/* This is a return code for the read callback that, when returned, will
   signal libcurl to immediately abort the current transfer. */
#define CURL_READFUNC_ABORT 0x10000000
/* This is a return code for the read callback that, when returned, will
   signal libcurl to pause sending data on the current transfer. */
#define CURL_READFUNC_PAUSE 0x10000001

typedef size_t (*curl_read_callback)(char *buffer,
                                      size_t size,
                                      size_t nitems,
                                      void *instream);

typedef enum  {
  CURLSOCKTYPE_IPCXN,  /* socket created for a specific IP connection */
  CURLSOCKTYPE_ACCEPT, /* socket created by accept() call */
  CURLSOCKTYPE_LAST    /* never use */
} curlsocktype;

/* The return code from the sockopt_callback can signal information back
   to libcurl: */
#define CURL_SOCKOPT_OK 0
#define CURL_SOCKOPT_ERROR 1 /* causes libcurl to abort and return
                                CURLE_ABORTED_BY_CALLBACK */
#define CURL_SOCKOPT_ALREADY_CONNECTED 2

typedef int (*curl_sockopt_callback)(void *clientp,
                                     curl_socket_t curlfd,
                                     curlsocktype purpose);

struct curl_sockaddr {
  int family;
  int socktype;
  int protocol;
  unsigned int addrlen; /* addrlen was a socklen_t type before 7.18.0 but it
                           turned really ugly and painful on the systems that
                           lack this type */
  struct sockaddr addr;
};

typedef curl_socket_t
(*curl_opensocket_callback)(void *clientp,
                            curlsocktype purpose,
                            struct curl_sockaddr *address);

typedef int
(*curl_closesocket_callback)(void *clientp, curl_socket_t item);

typedef enum {
  CURLIOE_OK,            /* I/O operation successful */
  CURLIOE_UNKNOWNCMD,    /* command was unknown to callback */
  CURLIOE_FAILRESTART,   /* failed to restart the read */
  CURLIOE_LAST           /* never use */
} curlioerr;

typedef enum  {
  CURLIOCMD_NOP,         /* no operation */
  CURLIOCMD_RESTARTREAD, /* restart the read stream from start */
  CURLIOCMD_LAST         /* never use */
} curliocmd;

typedef curlioerr (*curl_ioctl_callback)(CURL *handle,
                                         int cmd,
                                         void *clientp);

/*
 * The following typedef's are signatures of malloc, free, realloc, strdup and
 * calloc respectively.  Function pointers of these types can be passed to the
 * curl_global_init_mem() function to set user defined memory management
 * callback routines.
 */
typedef void *(*curl_malloc_callback)(size_t size);
typedef void (*curl_free_callback)(void *ptr);
typedef void *(*curl_realloc_callback)(void *ptr, size_t size);
typedef char *(*curl_strdup_callback)(const char *str);
typedef void *(*curl_calloc_callback)(size_t nmemb, size_t size);

/* the kind of data that is passed to information_callback*/
typedef enum {
  CURLINFO_TEXT = 0,
  CURLINFO_HEADER_IN,    /* 1 */
  CURLINFO_HEADER_OUT,   /* 2 */
  CURLINFO_DATA_IN,      /* 3 */
  CURLINFO_DATA_OUT,     /* 4 */
  CURLINFO_SSL_DATA_IN,  /* 5 */
  CURLINFO_SSL_DATA_OUT, /* 6 */
  CURLINFO_END
} curl_infotype;

typedef int (*curl_debug_callback)
       (CURL *handle,      /* the handle/transfer this concerns */
        curl_infotype type, /* what kind of data */
        char *data,        /* points to the data */
        size_t size,       /* size of the data pointed to */
        void *userptr);    /* whatever the user please */

/* All possible error codes from all sorts of curl functions. Future versions
   may return other values, stay prepared.

   Always add new return codes last. Never *EVER* remove any. The return
   codes must remain the same!
 */

typedef enum {
  CURLE_OK = 0,
  CURLE_UNSUPPORTED_PROTOCOL,    /* 1 */
  CURLE_FAILED_INIT,             /* 2 */
  CURLE_URL_MALFORMAT,           /* 3 */
  CURLE_NOT_BUILT_IN,            /* 4 - [was obsoleted in August 2007 for
                                    7.17.0, reused in April 2011 for 7.21.5] */
  CURLE_COULDNT_RESOLVE_PROXY,   /* 5 */
  CURLE_COULDNT_RESOLVE_HOST,    /* 6 */
  CURLE_COULDNT_CONNECT,         /* 7 */
  CURLE_FTP_WEIRD_SERVER_REPLY,  /* 8 */
  CURLE_REMOTE_ACCESS_DENIED,    /* 9 a service was denied by the server
                                    due to lack of access - when login fails
                                    this is not returned. */
  CURLE_FTP_ACCEPT_FAILED,       /* 10 - [was obsoleted in April 2006 for
                                    7.15.4, reused in Dec 2011 for 7.24.0]*/
  CURLE_FTP_WEIRD_PASS_REPLY,    /* 11 */
  CURLE_FTP_ACCEPT_TIMEOUT,      /* 12 - timeout occurred accepting server
                                    [was obsoleted in August 2007 for 7.17.0,
                                    reused in Dec 2011 for 7.24.0]*/
  CURLE_FTP_WEIRD_PASV_REPLY,    /* 13 */
  CURLE_FTP_WEIRD_227_FORMAT,    /* 14 */
  CURLE_FTP_CANT_GET_HOST,       /* 15 */
  CURLE_HTTP2,                   /* 16 - A problem in the http2 framing layer.
                                    [was obsoleted in August 2007 for 7.17.0,
                                    reused in July 2014 for 7.38.0] */
  CURLE_FTP_COULDNT_SET_TYPE,    /* 17 */
  CURLE_PARTIAL_FILE,            /* 18 */
  CURLE_FTP_COULDNT_RETR_FILE,   /* 19 */
  CURLE_OBSOLETE20,              /* 20 - NOT USED */
  CURLE_QUOTE_ERROR,             /* 21 - quote command failure */
  CURLE_HTTP_RETURNED_ERROR,     /* 22 */
  CURLE_WRITE_ERROR,             /* 23 */
  CURLE_OBSOLETE24,              /* 24 - NOT USED */
  CURLE_UPLOAD_FAILED,           /* 25 - failed upload "command" */
  CURLE_READ_ERROR,              /* 26 - couldn't open/read from file */
  CURLE_OUT_OF_MEMORY,           /* 27 */
  /* Note: CURLE_OUT_OF_MEMORY may sometimes indicate a conversion error
           instead of a memory allocation error if CURL_DOES_CONVERSIONS
           is defined
  */
  CURLE_OPERATION_TIMEDOUT,      /* 28 - the timeout time was reached */
  CURLE_OBSOLETE29,              /* 29 - NOT USED */
  CURLE_FTP_PORT_FAILED,         /* 30 - FTP PORT operation failed */
  CURLE_FTP_COULDNT_USE_REST,    /* 31 - the REST command failed */
  CURLE_OBSOLETE32,              /* 32 - NOT USED */
  CURLE_RANGE_ERROR,             /* 33 - RANGE "command" didn't work */
  CURLE_HTTP_POST_ERROR,         /* 34 */
  CURLE_SSL_CONNECT_ERROR,       /* 35 - wrong when connecting with SSL */
  CURLE_BAD_DOWNLOAD_RESUME,     /* 36 - couldn't resume download */
  CURLE_FILE_COULDNT_READ_FILE,  /* 37 */
  CURLE_LDAP_CANNOT_BIND,        /* 38 */
  CURLE_LDAP_SEARCH_FAILED,      /* 39 */
  CURLE_OBSOLETE40,              /* 40 - NOT USED */
  CURLE_FUNCTION_NOT_FOUND,      /* 41 */
  CURLE_ABORTED_BY_CALLBACK,     /* 42 */
  CURLE_BAD_FUNCTION_ARGUMENT,   /* 43 */
  CURLE_OBSOLETE44,              /* 44 - NOT USED */
  CURLE_INTERFACE_FAILED,        /* 45 - CURLOPT_INTERFACE failed */
  CURLE_OBSOLETE46,              /* 46 - NOT USED */
  CURLE_TOO_MANY_REDIRECTS ,     /* 47 - catch endless re-direct loops */
  CURLE_UNKNOWN_OPTION,          /* 48 - User specified an unknown option */
  CURLE_TELNET_OPTION_SYNTAX ,   /* 49 - Malformed telnet option */
  CURLE_OBSOLETE50,              /* 50 - NOT USED */
  CURLE_PEER_FAILED_VERIFICATION, /* 51 - peer's certificate or fingerprint
                                     wasn't verified fine */
  CURLE_GOT_NOTHING,             /* 52 - when this is a specific error */
  CURLE_SSL_ENGINE_NOTFOUND,     /* 53 - SSL crypto engine not found */
  CURLE_SSL_ENGINE_SETFAILED,    /* 54 - can not set SSL crypto engine as
                                    default */
  CURLE_SEND_ERROR,              /* 55 - failed sending network data */
  CURLE_RECV_ERROR,              /* 56 - failure in receiving network data */
  CURLE_OBSOLETE57,              /* 57 - NOT IN USE */
  CURLE_SSL_CERTPROBLEM,         /* 58 - problem with the local certificate */
  CURLE_SSL_CIPHER,              /* 59 - couldn't use specified cipher */
  CURLE_SSL_CACERT,              /* 60 - problem with the CA cert (path?) */
  CURLE_BAD_CONTENT_ENCODING,    /* 61 - Unrecognized/bad encoding */
  CURLE_LDAP_INVALID_URL,        /* 62 - Invalid LDAP URL */
  CURLE_FILESIZE_EXCEEDED,       /* 63 - Maximum file size exceeded */
  CURLE_USE_SSL_FAILED,          /* 64 - Requested FTP SSL level failed */
  CURLE_SEND_FAIL_REWIND,        /* 65 - Sending the data requires a rewind
                                    that failed */
  CURLE_SSL_ENGINE_INITFAILED,   /* 66 - failed to initialise ENGINE */
  CURLE_LOGIN_DENIED,            /* 67 - user, password or similar was not
                                    accepted and we failed to login */
  CURLE_TFTP_NOTFOUND,           /* 68 - file not found on server */
  CURLE_TFTP_PERM,               /* 69 - permission problem on server */
  CURLE_REMOTE_DISK_FULL,        /* 70 - out of disk space on server */
  CURLE_TFTP_ILLEGAL,            /* 71 - Illegal TFTP operation */
  CURLE_TFTP_UNKNOWNID,          /* 72 - Unknown transfer ID */
  CURLE_REMOTE_FILE_EXISTS,      /* 73 - File already exists */
  CURLE_TFTP_NOSUCHUSER,         /* 74 - No such user */
  CURLE_CONV_FAILED,             /* 75 - conversion failed */
  CURLE_CONV_REQD,               /* 76 - caller must register conversion
                                    callbacks using curl_easy_setopt options
                                    CURLOPT_CONV_FROM_NETWORK_FUNCTION,
                                    CURLOPT_CONV_TO_NETWORK_FUNCTION, and
                                    CURLOPT_CONV_FROM_UTF8_FUNCTION */
  CURLE_SSL_CACERT_BADFILE,      /* 77 - could not load CACERT file, missing
                                    or wrong format */
  CURLE_REMOTE_FILE_NOT_FOUND,   /* 78 - remote file not found */
  CURLE_SSH,                     /* 79 - error from the SSH layer, somewhat
                                    generic so the error message will be of
                                    interest when this has happened */

  CURLE_SSL_SHUTDOWN_FAILED,     /* 80 - Failed to shut down the SSL
                                    connection */
  CURLE_AGAIN,                   /* 81 - socket is not ready for send/recv,
                                    wait till it's ready and try again (Added
                                    in 7.18.2) */
  CURLE_SSL_CRL_BADFILE,         /* 82 - could not load CRL file, missing or
                                    wrong format (Added in 7.19.0) */
  CURLE_SSL_ISSUER_ERROR,        /* 83 - Issuer check failed.  (Added in
                                    7.19.0) */
  CURLE_FTP_PRET_FAILED,         /* 84 - a PRET command failed */
  CURLE_RTSP_CSEQ_ERROR,         /* 85 - mismatch of RTSP CSeq numbers */
  CURLE_RTSP_SESSION_ERROR,      /* 86 - mismatch of RTSP Session Ids */
  CURLE_FTP_BAD_FILE_LIST,       /* 87 - unable to parse FTP file list */
  CURLE_CHUNK_FAILED,            /* 88 - chunk callback reported error */
  CURLE_NO_CONNECTION_AVAILABLE, /* 89 - No connection available, the
                                    session will be queued */
  CURLE_SSL_PINNEDPUBKEYNOTMATCH, /* 90 - specified pinned public key did not
                                     match */
  CURLE_SSL_INVALIDCERTSTATUS,   /* 91 - invalid certificate status */
  CURL_LAST /* never use! */
} CURLcode;

#ifndef CURL_NO_OLDIES /* define this to test if your app builds with all
                          the obsolete stuff removed! */

/* Previously obsolete error code re-used in 7.38.0 */
#define CURLE_OBSOLETE16 CURLE_HTTP2

/* Previously obsolete error codes re-used in 7.24.0 */
#define CURLE_OBSOLETE10 CURLE_FTP_ACCEPT_FAILED
#define CURLE_OBSOLETE12 CURLE_FTP_ACCEPT_TIMEOUT

/*  compatibility with older names */
#define CURLOPT_ENCODING CURLOPT_ACCEPT_ENCODING

/* The following were added in 7.21.5, April 2011 */
#define CURLE_UNKNOWN_TELNET_OPTION CURLE_UNKNOWN_OPTION

/* The following were added in 7.17.1 */
/* These are scheduled to disappear by 2009 */
#define CURLE_SSL_PEER_CERTIFICATE CURLE_PEER_FAILED_VERIFICATION

/* The following were added in 7.17.0 */
/* These are scheduled to disappear by 2009 */
#define CURLE_OBSOLETE CURLE_OBSOLETE50 /* no one should be using this! */
#define CURLE_BAD_PASSWORD_ENTERED CURLE_OBSOLETE46
#define CURLE_BAD_CALLING_ORDER CURLE_OBSOLETE44
#define CURLE_FTP_USER_PASSWORD_INCORRECT CURLE_OBSOLETE10
#define CURLE_FTP_CANT_RECONNECT CURLE_OBSOLETE16
#define CURLE_FTP_COULDNT_GET_SIZE CURLE_OBSOLETE32
#define CURLE_FTP_COULDNT_SET_ASCII CURLE_OBSOLETE29
#define CURLE_FTP_WEIRD_USER_REPLY CURLE_OBSOLETE12
#define CURLE_FTP_WRITE_ERROR CURLE_OBSOLETE20
#define CURLE_LIBRARY_NOT_FOUND CURLE_OBSOLETE40
#define CURLE_MALFORMAT_USER CURLE_OBSOLETE24
#define CURLE_SHARE_IN_USE CURLE_OBSOLETE57
#define CURLE_URL_MALFORMAT_USER CURLE_NOT_BUILT_IN

#define CURLE_FTP_ACCESS_DENIED CURLE_REMOTE_ACCESS_DENIED
#define CURLE_FTP_COULDNT_SET_BINARY CURLE_FTP_COULDNT_SET_TYPE
#define CURLE_FTP_QUOTE_ERROR CURLE_QUOTE_ERROR
#define CURLE_TFTP_DISKFULL CURLE_REMOTE_DISK_FULL
#define CURLE_TFTP_EXISTS CURLE_REMOTE_FILE_EXISTS
#define CURLE_HTTP_RANGE_ERROR CURLE_RANGE_ERROR
#define CURLE_FTP_SSL_FAILED CURLE_USE_SSL_FAILED

/* The following were added earlier */

#define CURLE_OPERATION_TIMEOUTED CURLE_OPERATION_TIMEDOUT

#define CURLE_HTTP_NOT_FOUND CURLE_HTTP_RETURNED_ERROR
#define CURLE_HTTP_PORT_FAILED CURLE_INTERFACE_FAILED
#define CURLE_FTP_COULDNT_STOR_FILE CURLE_UPLOAD_FAILED

#define CURLE_FTP_PARTIAL_FILE CURLE_PARTIAL_FILE
#define CURLE_FTP_BAD_DOWNLOAD_RESUME CURLE_BAD_DOWNLOAD_RESUME

/* This was the error code 50 in 7.7.3 and a few earlier versions, this
   is no longer used by libcurl but is instead #defined here only to not
   make programs break */
#define CURLE_ALREADY_COMPLETE 99999

/* Provide defines for really old option names */
#define CURLOPT_FILE CURLOPT_WRITEDATA /* name changed in 7.9.7 */
#define CURLOPT_INFILE CURLOPT_READDATA /* name changed in 7.9.7 */
#define CURLOPT_WRITEHEADER CURLOPT_HEADERDATA

/* Since long deprecated options with no code in the lib that does anything
   with them. */
#define CURLOPT_WRITEINFO CURLOPT_OBSOLETE40
#define CURLOPT_CLOSEPOLICY CURLOPT_OBSOLETE72

#endif /*!CURL_NO_OLDIES*/

/* This prototype applies to all conversion callbacks */
typedef CURLcode (*curl_conv_callback)(char *buffer, size_t length);

typedef CURLcode (*curl_ssl_ctx_callback)(CURL *curl,    /* easy handle */
                                          void *ssl_ctx, /* actually an
                                                            OpenSSL SSL_CTX */
                                          void *userptr);

typedef enum {
  CURLPROXY_HTTP = 0,   /* added in 7.10, new in 7.19.4 default is to use
                           CONNECT HTTP/1.1 */
  CURLPROXY_HTTP_1_0 = 1,   /* added in 7.19.4, force to use CONNECT
                               HTTP/1.0  */
  CURLPROXY_SOCKS4 = 4, /* support added in 7.15.2, enum existed already
                           in 7.10 */
  CURLPROXY_SOCKS5 = 5, /* added in 7.10 */
  CURLPROXY_SOCKS4A = 6, /* added in 7.18.0 */
  CURLPROXY_SOCKS5_HOSTNAME = 7 /* Use the SOCKS5 protocol but pass along the
                                   host name rather than the IP address. added
                                   in 7.18.0 */
} curl_proxytype;  /* this enum was added in 7.10 */

/*
 * Bitmasks for CURLOPT_HTTPAUTH and CURLOPT_PROXYAUTH options:
 *
 * CURLAUTH_NONE         - No HTTP authentication
 * CURLAUTH_BASIC        - HTTP Basic authentication (default)
 * CURLAUTH_DIGEST       - HTTP Digest authentication
 * CURLAUTH_NEGOTIATE    - HTTP Negotiate (SPNEGO) authentication
 * CURLAUTH_GSSNEGOTIATE - Alias for CURLAUTH_NEGOTIATE (deprecated)
 * CURLAUTH_NTLM         - HTTP NTLM authentication
 * CURLAUTH_DIGEST_IE    - HTTP Digest authentication with IE flavour
 * CURLAUTH_NTLM_WB      - HTTP NTLM authentication delegated to winbind helper
 * CURLAUTH_ONLY         - Use together with a single other type to force no
 *                         authentication or just that single type
 * CURLAUTH_ANY          - All fine types set
 * CURLAUTH_ANYSAFE      - All fine types except Basic
 */

#define CURLAUTH_NONE         ((unsigned long)0)
#define CURLAUTH_BASIC        (((unsigned long)1)<<0)
#define CURLAUTH_DIGEST       (((unsigned long)1)<<1)
#define CURLAUTH_NEGOTIATE    (((unsigned long)1)<<2)
/* Deprecated since the advent of CURLAUTH_NEGOTIATE */
#define CURLAUTH_GSSNEGOTIATE CURLAUTH_NEGOTIATE
#define CURLAUTH_NTLM         (((unsigned long)1)<<3)
#define CURLAUTH_DIGEST_IE    (((unsigned long)1)<<4)
#define CURLAUTH_NTLM_WB      (((unsigned long)1)<<5)
#define CURLAUTH_ONLY         (((unsigned long)1)<<31)
#define CURLAUTH_ANY          (~CURLAUTH_DIGEST_IE)
#define CURLAUTH_ANYSAFE      (~(CURLAUTH_BASIC|CURLAUTH_DIGEST_IE))

#define CURLSSH_AUTH_ANY       ~0     /* all types supported by the server */
#define CURLSSH_AUTH_NONE      0      /* none allowed, silly but complete */
#define CURLSSH_AUTH_PUBLICKEY (1<<0) /* public/private key files */
#define CURLSSH_AUTH_PASSWORD  (1<<1) /* password */
#define CURLSSH_AUTH_HOST      (1<<2) /* host key files */
#define CURLSSH_AUTH_KEYBOARD  (1<<3) /* keyboard interactive */
#define CURLSSH_AUTH_AGENT     (1<<4) /* agent (ssh-agent, pageant...) */
#define CURLSSH_AUTH_DEFAULT CURLSSH_AUTH_ANY

#define CURLGSSAPI_DELEGATION_NONE        0      /* no delegation (default) */
#define CURLGSSAPI_DELEGATION_POLICY_FLAG (1<<0) /* if permitted by policy */
#define CURLGSSAPI_DELEGATION_FLAG        (1<<1) /* delegate always */

#define CURL_ERROR_SIZE 256

enum curl_khtype {
  CURLKHTYPE_UNKNOWN,
  CURLKHTYPE_RSA1,
  CURLKHTYPE_RSA,
  CURLKHTYPE_DSS
};

struct curl_khkey {
  const char *key; /* points to a zero-terminated string encoded with base64
                      if len is zero, otherwise to the "raw" data */
  size_t len;
  enum curl_khtype keytype;
};

/* this is the set of return values expected from the curl_sshkeycallback
   callback */
enum curl_khstat {
  CURLKHSTAT_FINE_ADD_TO_FILE,
  CURLKHSTAT_FINE,
  CURLKHSTAT_REJECT, /* reject the connection, return an error */
  CURLKHSTAT_DEFER,  /* do not accept it, but we can't answer right now so
                        this causes a CURLE_DEFER error but otherwise the
                        connection will be left intact etc */
  CURLKHSTAT_LAST    /* not for use, only a marker for last-in-list */
};

/* this is the set of status codes pass in to the callback */
enum curl_khmatch {
  CURLKHMATCH_OK,       /* match */
  CURLKHMATCH_MISMATCH, /* host found, key mismatch! */
  CURLKHMATCH_MISSING,  /* no matching host/key found */
  CURLKHMATCH_LAST      /* not for use, only a marker for last-in-list */
};

typedef int
  (*curl_sshkeycallback) (CURL *easy,     /* easy handle */
                          const struct curl_khkey *knownkey, /* known */
                          const struct curl_khkey *foundkey, /* found */
                          enum curl_khmatch, /* libcurl's view on the keys */
                          void *clientp); /* custom pointer passed from app */

/* parameter for the CURLOPT_USE_SSL option */
typedef enum {
  CURLUSESSL_NONE,    /* do not attempt to use SSL */
  CURLUSESSL_TRY,     /* try using SSL, proceed anyway otherwise */
  CURLUSESSL_CONTROL, /* SSL for the control connection or fail */
  CURLUSESSL_ALL,     /* SSL for all communication or fail */
  CURLUSESSL_LAST     /* not an option, never use */
} curl_usessl;

/* Definition of bits for the CURLOPT_SSL_OPTIONS argument: */

/* - ALLOW_BEAST tells libcurl to allow the BEAST SSL vulnerability in the
   name of improving interoperability with older servers. Some SSL libraries
   have introduced work-arounds for this flaw but those work-arounds sometimes
   make the SSL communication fail. To regain functionality with those broken
   servers, a user can this way allow the vulnerability back. */
#define CURLSSLOPT_ALLOW_BEAST (1<<0)

/* - NO_REVOKE tells libcurl to disable certificate revocation checks for those
   SSL backends where such behavior is present. */
#define CURLSSLOPT_NO_REVOKE (1<<1)

#ifndef CURL_NO_OLDIES /* define this to test if your app builds with all
                          the obsolete stuff removed! */

/* Backwards compatibility with older names */
/* These are scheduled to disappear by 2009 */

#define CURLFTPSSL_NONE CURLUSESSL_NONE
#define CURLFTPSSL_TRY CURLUSESSL_TRY
#define CURLFTPSSL_CONTROL CURLUSESSL_CONTROL
#define CURLFTPSSL_ALL CURLUSESSL_ALL
#define CURLFTPSSL_LAST CURLUSESSL_LAST
#define curl_ftpssl curl_usessl
#endif /*!CURL_NO_OLDIES*/

/* parameter for the CURLOPT_FTP_SSL_CCC option */
typedef enum {
  CURLFTPSSL_CCC_NONE,    /* do not send CCC */
  CURLFTPSSL_CCC_PASSIVE, /* Let the server initiate the shutdown */
  CURLFTPSSL_CCC_ACTIVE,  /* Initiate the shutdown */
  CURLFTPSSL_CCC_LAST     /* not an option, never use */
} curl_ftpccc;

/* parameter for the CURLOPT_FTPSSLAUTH option */
typedef enum {
  CURLFTPAUTH_DEFAULT, /* let libcurl decide */
  CURLFTPAUTH_SSL,     /* use "AUTH SSL" */
  CURLFTPAUTH_TLS,     /* use "AUTH TLS" */
  CURLFTPAUTH_LAST /* not an option, never use */
} curl_ftpauth;

/* parameter for the CURLOPT_FTP_CREATE_MISSING_DIRS option */
typedef enum {
  CURLFTP_CREATE_DIR_NONE,  /* do NOT create missing dirs! */
  CURLFTP_CREATE_DIR,       /* (FTP/SFTP) if CWD fails, try MKD and then CWD
                               again if MKD succeeded, for SFTP this does
                               similar magic */
  CURLFTP_CREATE_DIR_RETRY, /* (FTP only) if CWD fails, try MKD and then CWD
                               again even if MKD failed! */
  CURLFTP_CREATE_DIR_LAST   /* not an option, never use */
} curl_ftpcreatedir;

/* parameter for the CURLOPT_FTP_FILEMETHOD option */
typedef enum {
  CURLFTPMETHOD_DEFAULT,   /* let libcurl pick */
  CURLFTPMETHOD_MULTICWD,  /* single CWD operation for each path part */
  CURLFTPMETHOD_NOCWD,     /* no CWD at all */
  CURLFTPMETHOD_SINGLECWD, /* one CWD to full dir, then work on file */
  CURLFTPMETHOD_LAST       /* not an option, never use */
} curl_ftpmethod;

/* bitmask defines for CURLOPT_HEADEROPT */
#define CURLHEADER_UNIFIED  0
#define CURLHEADER_SEPARATE (1<<0)

/* CURLPROTO_ defines are for the CURLOPT_*PROTOCOLS options */
#define CURLPROTO_HTTP   (1<<0)
#define CURLPROTO_HTTPS  (1<<1)
#define CURLPROTO_FTP    (1<<2)
#define CURLPROTO_FTPS   (1<<3)
#define CURLPROTO_SCP    (1<<4)
#define CURLPROTO_SFTP   (1<<5)
#define CURLPROTO_TELNET (1<<6)
#define CURLPROTO_LDAP   (1<<7)
#define CURLPROTO_LDAPS  (1<<8)
#define CURLPROTO_DICT   (1<<9)
#define CURLPROTO_FILE   (1<<10)
#define CURLPROTO_TFTP   (1<<11)
#define CURLPROTO_IMAP   (1<<12)
#define CURLPROTO_IMAPS  (1<<13)
#define CURLPROTO_POP3   (1<<14)
#define CURLPROTO_POP3S  (1<<15)
#define CURLPROTO_SMTP   (1<<16)
#define CURLPROTO_SMTPS  (1<<17)
#define CURLPROTO_RTSP   (1<<18)
#define CURLPROTO_RTMP   (1<<19)
#define CURLPROTO_RTMPT  (1<<20)
#define CURLPROTO_RTMPE  (1<<21)
#define CURLPROTO_RTMPTE (1<<22)
#define CURLPROTO_RTMPS  (1<<23)
#define CURLPROTO_RTMPTS (1<<24)
#define CURLPROTO_GOPHER (1<<25)
#define CURLPROTO_SMB    (1<<26)
#define CURLPROTO_SMBS   (1<<27)
#define CURLPROTO_ALL    (~0) /* enable everything */

/* long may be 32 or 64 bits, but we should never depend on anything else
   but 32 */
#define CURLOPTTYPE_LONG          0
#define CURLOPTTYPE_OBJECTPOINT   10000
#define CURLOPTTYPE_STRINGPOINT   10000
#define CURLOPTTYPE_FUNCTIONPOINT 20000
#define CURLOPTTYPE_OFF_T         30000

/* *STRINGPOINT is an alias for OBJECTPOINT to allow tools to extract the
   string options from the header file */

/* name is uppercase CURLOPT_<name>,
   type is one of the defined CURLOPTTYPE_<type>
   number is unique identifier */
#ifdef CINIT
#undef CINIT
#endif

#ifdef CURL_ISOCPP
#define CINIT(na,t,nu) CURLOPT_ ## na = CURLOPTTYPE_ ## t + nu
#else
/* The macro "##" is ISO C, we assume pre-ISO C doesn't support it. */
#define LONG          CURLOPTTYPE_LONG
#define OBJECTPOINT   CURLOPTTYPE_OBJECTPOINT
#define STRINGPOINT   CURLOPTTYPE_OBJECTPOINT
#define FUNCTIONPOINT CURLOPTTYPE_FUNCTIONPOINT
#define OFF_T         CURLOPTTYPE_OFF_T
#define CINIT(name,type,number) CURLOPT_/**/name = type + number
#endif

/*
 * This macro-mania below setups the CURLOPT_[what] enum, to be used with
 * curl_easy_setopt(). The first argument in the CINIT() macro is the [what]
 * word.
 */

typedef enum {
  /* This is the FILE * or void * the regular output should be written to. */
  CINIT(WRITEDATA, OBJECTPOINT, 1),

  /* The full URL to get/put */
  CINIT(URL, STRINGPOINT, 2),

  /* Port number to connect to, if other than default. */
  CINIT(PORT, LONG, 3),

  /* Name of proxy to use. */
  CINIT(PROXY, STRINGPOINT, 4),

  /* "user:password;options" to use when fetching. */
  CINIT(USERPWD, STRINGPOINT, 5),

  /* "user:password" to use with proxy. */
  CINIT(PROXYUSERPWD, STRINGPOINT, 6),

  /* Range to get, specified as an ASCII string. */
  CINIT(RANGE, STRINGPOINT, 7),

  /* not used */

  /* Specified file stream to upload from (use as input): */
  CINIT(READDATA, OBJECTPOINT, 9),

  /* Buffer to receive error messages in, must be at least CURL_ERROR_SIZE
   * bytes big. If this is not used, error messages go to stderr instead: */
  CINIT(ERRORBUFFER, OBJECTPOINT, 10),

  /* Function that will be called to store the output (instead of fwrite). The
   * parameters will use fwrite() syntax, make sure to follow them. */
  CINIT(WRITEFUNCTION, FUNCTIONPOINT, 11),

  /* Function that will be called to read the input (instead of fread). The
   * parameters will use fread() syntax, make sure to follow them. */
  CINIT(READFUNCTION, FUNCTIONPOINT, 12),

  /* Time-out the read operation after this amount of seconds */
  CINIT(TIMEOUT, LONG, 13),

  /* If the CURLOPT_INFILE is used, this can be used to inform libcurl about
   * how large the file being sent really is. That allows better error
   * checking and better verifies that the upload was successful. -1 means
   * unknown size.
   *
   * For large file support, there is also a _LARGE version of the key
   * which takes an off_t type, allowing platforms with larger off_t
   * sizes to handle larger files.  See below for INFILESIZE_LARGE.
   */
  CINIT(INFILESIZE, LONG, 14),

  /* POST static input fields. */
  CINIT(POSTFIELDS, OBJECTPOINT, 15),

  /* Set the referrer page (needed by some CGIs) */
  CINIT(REFERER, STRINGPOINT, 16),

  /* Set the FTP PORT string (interface name, named or numerical IP address)
     Use i.e '-' to use default address. */
  CINIT(FTPPORT, STRINGPOINT, 17),

  /* Set the User-Agent string (examined by some CGIs) */
  CINIT(USERAGENT, STRINGPOINT, 18),

  /* If the download receives less than "low speed limit" bytes/second
   * during "low speed time" seconds, the operations is aborted.
   * You could i.e if you have a pretty high speed connection, abort if
   * it is less than 2000 bytes/sec during 20 seconds.
   */

  /* Set the "low speed limit" */
  CINIT(LOW_SPEED_LIMIT, LONG, 19),

  /* Set the "low speed time" */
  CINIT(LOW_SPEED_TIME, LONG, 20),

  /* Set the continuation offset.
   *
   * Note there is also a _LARGE version of this key which uses
   * off_t types, allowing for large file offsets on platforms which
   * use larger-than-32-bit off_t's.  Look below for RESUME_FROM_LARGE.
   */
  CINIT(RESUME_FROM, LONG, 21),

  /* Set cookie in request: */
  CINIT(COOKIE, STRINGPOINT, 22),

  /* This points to a linked list of headers, struct curl_slist kind. This
     list is also used for RTSP (in spite of its name) */
  CINIT(HTTPHEADER, OBJECTPOINT, 23),

  /* This points to a linked list of post entries, struct curl_httppost */
  CINIT(HTTPPOST, OBJECTPOINT, 24),

  /* name of the file keeping your private SSL-certificate */
  CINIT(SSLCERT, STRINGPOINT, 25),

  /* password for the SSL or SSH private key */
  CINIT(KEYPASSWD, STRINGPOINT, 26),

  /* send TYPE parameter? */
  CINIT(CRLF, LONG, 27),

  /* send linked-list of QUOTE commands */
  CINIT(QUOTE, OBJECTPOINT, 28),

  /* send FILE * or void * to store headers to, if you use a callback it
     is simply passed to the callback unmodified */
  CINIT(HEADERDATA, OBJECTPOINT, 29),

  /* point to a file to read the initial cookies from, also enables
     "cookie awareness" */
  CINIT(COOKIEFILE, STRINGPOINT, 31),

  /* What version to specifically try to use.
     See CURL_SSLVERSION defines below. */
  CINIT(SSLVERSION, LONG, 32),

  /* What kind of HTTP time condition to use, see defines */
  CINIT(TIMECONDITION, LONG, 33),

  /* Time to use with the above condition. Specified in number of seconds
     since 1 Jan 1970 */
  CINIT(TIMEVALUE, LONG, 34),

  /* 35 = OBSOLETE */

  /* Custom request, for customizing the get command like
     HTTP: DELETE, TRACE and others
     FTP: to use a different list command
     */
  CINIT(CUSTOMREQUEST, STRINGPOINT, 36),

  /* FILE handle to use instead of stderr */
  CINIT(STDERR, OBJECTPOINT, 37),

  /* 38 is not used */

  /* send linked-list of post-transfer QUOTE commands */
  CINIT(POSTQUOTE, OBJECTPOINT, 39),

  CINIT(OBSOLETE40, OBJECTPOINT, 40), /* OBSOLETE, do not use! */

  CINIT(VERBOSE, LONG, 41),      /* talk a lot */
  CINIT(HEADER, LONG, 42),       /* throw the header out too */
  CINIT(NOPROGRESS, LONG, 43),   /* shut off the progress meter */
  CINIT(NOBODY, LONG, 44),       /* use HEAD to get http document */
  CINIT(FAILONERROR, LONG, 45),  /* no output on http error codes >= 400 */
  CINIT(UPLOAD, LONG, 46),       /* this is an upload */
  CINIT(POST, LONG, 47),         /* HTTP POST method */
  CINIT(DIRLISTONLY, LONG, 48),  /* bare names when listing directories */

  CINIT(APPEND, LONG, 50),       /* Append instead of overwrite on upload! */

  /* Specify whether to read the user+password from the .netrc or the URL.
   * This must be one of the CURL_NETRC_* enums below. */
  CINIT(NETRC, LONG, 51),

  CINIT(FOLLOWLOCATION, LONG, 52),  /* use Location: Luke! */

  CINIT(TRANSFERTEXT, LONG, 53), /* transfer data in text/ASCII format */
  CINIT(PUT, LONG, 54),          /* HTTP PUT */

  /* 55 = OBSOLETE */

  /* DEPRECATED
   * Function that will be called instead of the internal progress display
   * function. This function should be defined as the curl_progress_callback
   * prototype defines. */
  CINIT(PROGRESSFUNCTION, FUNCTIONPOINT, 56),

  /* Data passed to the CURLOPT_PROGRESSFUNCTION and CURLOPT_XFERINFOFUNCTION
     callbacks */
  CINIT(PROGRESSDATA, OBJECTPOINT, 57),
#define CURLOPT_XFERINFODATA CURLOPT_PROGRESSDATA

  /* We want the referrer field set automatically when following locations */
  CINIT(AUTOREFERER, LONG, 58),

  /* Port of the proxy, can be set in the proxy string as well with:
     "[host]:[port]" */
  CINIT(PROXYPORT, LONG, 59),

  /* size of the POST input data, if strlen() is not good to use */
  CINIT(POSTFIELDSIZE, LONG, 60),

  /* tunnel non-http operations through a HTTP proxy */
  CINIT(HTTPPROXYTUNNEL, LONG, 61),

  /* Set the interface string to use as outgoing network interface */
  CINIT(INTERFACE, STRINGPOINT, 62),

  /* Set the krb4/5 security level, this also enables krb4/5 awareness.  This
   * is a string, 'clear', 'safe', 'confidential' or 'private'.  If the string
   * is set but doesn't match one of these, 'private' will be used.  */
  CINIT(KRBLEVEL, STRINGPOINT, 63),

  /* Set if we should verify the peer in ssl handshake, set 1 to verify. */
  CINIT(SSL_VERIFYPEER, LONG, 64),

  /* The CApath or CAfile used to validate the peer certificate
     this option is used only if SSL_VERIFYPEER is true */
  CINIT(CAINFO, STRINGPOINT, 65),

  /* 66 = OBSOLETE */
  /* 67 = OBSOLETE */

  /* Maximum number of http redirects to follow */
  CINIT(MAXREDIRS, LONG, 68),

  /* Pass a long set to 1 to get the date of the requested document (if
     possible)! Pass a zero to shut it off. */
  CINIT(FILETIME, LONG, 69),

  /* This points to a linked list of telnet options */
  CINIT(TELNETOPTIONS, OBJECTPOINT, 70),

  /* Max amount of cached alive connections */
  CINIT(MAXCONNECTS, LONG, 71),

  CINIT(OBSOLETE72, LONG, 72), /* OBSOLETE, do not use! */

  /* 73 = OBSOLETE */

  /* Set to explicitly use a new connection for the upcoming transfer.
     Do not use this unless you're absolutely sure of this, as it makes the
     operation slower and is less friendly for the network. */
  CINIT(FRESH_CONNECT, LONG, 74),

  /* Set to explicitly forbid the upcoming transfer's connection to be re-used
     when done. Do not use this unless you're absolutely sure of this, as it
     makes the operation slower and is less friendly for the network. */
  CINIT(FORBID_REUSE, LONG, 75),

  /* Set to a file name that contains random data for libcurl to use to
     seed the random engine when doing SSL connects. */
  CINIT(RANDOM_FILE, STRINGPOINT, 76),

  /* Set to the Entropy Gathering Daemon socket pathname */
  CINIT(EGDSOCKET, STRINGPOINT, 77),

  /* Time-out connect operations after this amount of seconds, if connects are
     OK within this time, then fine... This only aborts the connect phase. */
  CINIT(CONNECTTIMEOUT, LONG, 78),

  /* Function that will be called to store headers (instead of fwrite). The
   * parameters will use fwrite() syntax, make sure to follow them. */
  CINIT(HEADERFUNCTION, FUNCTIONPOINT, 79),

  /* Set this to force the HTTP request to get back to GET. Only really usable
     if POST, PUT or a custom request have been used first.
   */
  CINIT(HTTPGET, LONG, 80),

  /* Set if we should verify the Common name from the peer certificate in ssl
   * handshake, set 1 to check existence, 2 to ensure that it matches the
   * provided hostname. */
  CINIT(SSL_VERIFYHOST, LONG, 81),

  /* Specify which file name to write all known cookies in after completed
     operation. Set file name to "-" (dash) to make it go to stdout. */
  CINIT(COOKIEJAR, STRINGPOINT, 82),

  /* Specify which SSL ciphers to use */
  CINIT(SSL_CIPHER_LIST, STRINGPOINT, 83),

  /* Specify which HTTP version to use! This must be set to one of the
     CURL_HTTP_VERSION* enums set below. */
  CINIT(HTTP_VERSION, LONG, 84),

  /* Specifically switch on or off the FTP engine's use of the EPSV command. By
     default, that one will always be attempted before the more traditional
     PASV command. */
  CINIT(FTP_USE_EPSV, LONG, 85),

  /* type of the file keeping your SSL-certificate ("DER", "PEM", "ENG") */
  CINIT(SSLCERTTYPE, STRINGPOINT, 86),

  /* name of the file keeping your private SSL-key */
  CINIT(SSLKEY, STRINGPOINT, 87),

  /* type of the file keeping your private SSL-key ("DER", "PEM", "ENG") */
  CINIT(SSLKEYTYPE, STRINGPOINT, 88),

  /* crypto engine for the SSL-sub system */
  CINIT(SSLENGINE, STRINGPOINT, 89),

  /* set the crypto engine for the SSL-sub system as default
     the param has no meaning...
   */
  CINIT(SSLENGINE_DEFAULT, LONG, 90),

  /* Non-zero value means to use the global dns cache */
  CINIT(DNS_USE_GLOBAL_CACHE, LONG, 91), /* DEPRECATED, do not use! */

  /* DNS cache timeout */
  CINIT(DNS_CACHE_TIMEOUT, LONG, 92),

  /* send linked-list of pre-transfer QUOTE commands */
  CINIT(PREQUOTE, OBJECTPOINT, 93),

  /* set the debug function */
  CINIT(DEBUGFUNCTION, FUNCTIONPOINT, 94),

  /* set the data for the debug function */
  CINIT(DEBUGDATA, OBJECTPOINT, 95),

  /* mark this as start of a cookie session */
  CINIT(COOKIESESSION, LONG, 96),

  /* The CApath directory used to validate the peer certificate
     this option is used only if SSL_VERIFYPEER is true */
  CINIT(CAPATH, STRINGPOINT, 97),

  /* Instruct libcurl to use a smaller receive buffer */
  CINIT(BUFFERSIZE, LONG, 98),

  /* Instruct libcurl to not use any signal/alarm handlers, even when using
     timeouts. This option is useful for multi-threaded applications.
     See libcurl-the-guide for more background information. */
  CINIT(NOSIGNAL, LONG, 99),

  /* Provide a CURLShare for mutexing non-ts data */
  CINIT(SHARE, OBJECTPOINT, 100),

  /* indicates type of proxy. accepted values are CURLPROXY_HTTP (default),
     CURLPROXY_SOCKS4, CURLPROXY_SOCKS4A and CURLPROXY_SOCKS5. */
  CINIT(PROXYTYPE, LONG, 101),

  /* Set the Accept-Encoding string. Use this to tell a server you would like
     the response to be compressed. Before 7.21.6, this was known as
     CURLOPT_ENCODING */
  CINIT(ACCEPT_ENCODING, STRINGPOINT, 102),

  /* Set pointer to private data */
  CINIT(PRIVATE, OBJECTPOINT, 103),

  /* Set aliases for HTTP 200 in the HTTP Response header */
  CINIT(HTTP200ALIASES, OBJECTPOINT, 104),

  /* Continue to send authentication (user+password) when following locations,
     even when hostname changed. This can potentially send off the name
     and password to whatever host the server decides. */
  CINIT(UNRESTRICTED_AUTH, LONG, 105),

  /* Specifically switch on or off the FTP engine's use of the EPRT command (
     it also disables the LPRT attempt). By default, those ones will always be
     attempted before the good old traditional PORT command. */
  CINIT(FTP_USE_EPRT, LONG, 106),

  /* Set this to a bitmask value to enable the particular authentications
     methods you like. Use this in combination with CURLOPT_USERPWD.
     Note that setting multiple bits may cause extra network round-trips. */
  CINIT(HTTPAUTH, LONG, 107),

  /* Set the ssl context callback function, currently only for OpenSSL ssl_ctx
     in second argument. The function must be matching the
     curl_ssl_ctx_callback proto. */
  CINIT(SSL_CTX_FUNCTION, FUNCTIONPOINT, 108),

  /* Set the userdata for the ssl context callback function's third
     argument */
  CINIT(SSL_CTX_DATA, OBJECTPOINT, 109),

  /* FTP Option that causes missing dirs to be created on the remote server.
     In 7.19.4 we introduced the convenience enums for this option using the
     CURLFTP_CREATE_DIR prefix.
  */
  CINIT(FTP_CREATE_MISSING_DIRS, LONG, 110),

  /* Set this to a bitmask value to enable the particular authentications
     methods you like. Use this in combination with CURLOPT_PROXYUSERPWD.
     Note that setting multiple bits may cause extra network round-trips. */
  CINIT(PROXYAUTH, LONG, 111),

  /* FTP option that changes the timeout, in seconds, associated with
     getting a response.  This is different from transfer timeout time and
     essentially places a demand on the FTP server to acknowledge commands
     in a timely manner. */
  CINIT(FTP_RESPONSE_TIMEOUT, LONG, 112),
#define CURLOPT_SERVER_RESPONSE_TIMEOUT CURLOPT_FTP_RESPONSE_TIMEOUT

  /* Set this option to one of the CURL_IPRESOLVE_* defines (see below) to
     tell libcurl to resolve names to those IP versions only. This only has
     affect on systems with support for more than one, i.e IPv4 _and_ IPv6. */
  CINIT(IPRESOLVE, LONG, 113),

  /* Set this option to limit the size of a file that will be downloaded from
     an HTTP or FTP server.

     Note there is also _LARGE version which adds large file support for
     platforms which have larger off_t sizes.  See MAXFILESIZE_LARGE below. */
  CINIT(MAXFILESIZE, LONG, 114),

  /* See the comment for INFILESIZE above, but in short, specifies
   * the size of the file being uploaded.  -1 means unknown.
   */
  CINIT(INFILESIZE_LARGE, OFF_T, 115),

  /* Sets the continuation offset.  There is also a LONG version of this;
   * look above for RESUME_FROM.
   */
  CINIT(RESUME_FROM_LARGE, OFF_T, 116),

  /* Sets the maximum size of data that will be downloaded from
   * an HTTP or FTP server.  See MAXFILESIZE above for the LONG version.
   */
  CINIT(MAXFILESIZE_LARGE, OFF_T, 117),

  /* Set this option to the file name of your .netrc file you want libcurl
     to parse (using the CURLOPT_NETRC option). If not set, libcurl will do
     a poor attempt to find the user's home directory and check for a .netrc
     file in there. */
  CINIT(NETRC_FILE, STRINGPOINT, 118),

  /* Enable SSL/TLS for FTP, pick one of:
     CURLUSESSL_TRY     - try using SSL, proceed anyway otherwise
     CURLUSESSL_CONTROL - SSL for the control connection or fail
     CURLUSESSL_ALL     - SSL for all communication or fail
  */
  CINIT(USE_SSL, LONG, 119),

  /* The _LARGE version of the standard POSTFIELDSIZE option */
  CINIT(POSTFIELDSIZE_LARGE, OFF_T, 120),

  /* Enable/disable the TCP Nagle algorithm */
  CINIT(TCP_NODELAY, LONG, 121),

  /* 122 OBSOLETE, used in 7.12.3. Gone in 7.13.0 */
  /* 123 OBSOLETE. Gone in 7.16.0 */
  /* 124 OBSOLETE, used in 7.12.3. Gone in 7.13.0 */
  /* 125 OBSOLETE, used in 7.12.3. Gone in 7.13.0 */
  /* 126 OBSOLETE, used in 7.12.3. Gone in 7.13.0 */
  /* 127 OBSOLETE. Gone in 7.16.0 */
  /* 128 OBSOLETE. Gone in 7.16.0 */

  /* When FTP over SSL/TLS is selected (with CURLOPT_USE_SSL), this option
     can be used to change libcurl's default action which is to first try
     "AUTH SSL" and then "AUTH TLS" in this order, and proceed when a OK
     response has been received.

     Available parameters are:
     CURLFTPAUTH_DEFAULT - let libcurl decide
     CURLFTPAUTH_SSL     - try "AUTH SSL" first, then TLS
     CURLFTPAUTH_TLS     - try "AUTH TLS" first, then SSL
  */
  CINIT(FTPSSLAUTH, LONG, 129),

  CINIT(IOCTLFUNCTION, FUNCTIONPOINT, 130),
  CINIT(IOCTLDATA, OBJECTPOINT, 131),

  /* 132 OBSOLETE. Gone in 7.16.0 */
  /* 133 OBSOLETE. Gone in 7.16.0 */

  /* zero terminated string for pass on to the FTP server when asked for
     "account" info */
  CINIT(FTP_ACCOUNT, STRINGPOINT, 134),

  /* feed cookie into cookie engine */
  CINIT(COOKIELIST, STRINGPOINT, 135),

  /* ignore Content-Length */
  CINIT(IGNORE_CONTENT_LENGTH, LONG, 136),

  /* Set to non-zero to skip the IP address received in a 227 PASV FTP server
     response. Typically used for FTP-SSL purposes but is not restricted to
     that. libcurl will then instead use the same IP address it used for the
     control connection. */
  CINIT(FTP_SKIP_PASV_IP, LONG, 137),

  /* Select "file method" to use when doing FTP, see the curl_ftpmethod
     above. */
  CINIT(FTP_FILEMETHOD, LONG, 138),

  /* Local port number to bind the socket to */
  CINIT(LOCALPORT, LONG, 139),

  /* Number of ports to try, including the first one set with LOCALPORT.
     Thus, setting it to 1 will make no additional attempts but the first.
  */
  CINIT(LOCALPORTRANGE, LONG, 140),

  /* no transfer, set up connection and let application use the socket by
     extracting it with CURLINFO_LASTSOCKET */
  CINIT(CONNECT_ONLY, LONG, 141),

  /* Function that will be called to convert from the
     network encoding (instead of using the iconv calls in libcurl) */
  CINIT(CONV_FROM_NETWORK_FUNCTION, FUNCTIONPOINT, 142),

  /* Function that will be called to convert to the
     network encoding (instead of using the iconv calls in libcurl) */
  CINIT(CONV_TO_NETWORK_FUNCTION, FUNCTIONPOINT, 143),

  /* Function that will be called to convert from UTF8
     (instead of using the iconv calls in libcurl)
     Note that this is used only for SSL certificate processing */
  CINIT(CONV_FROM_UTF8_FUNCTION, FUNCTIONPOINT, 144),

  /* if the connection proceeds too quickly then need to slow it down */
  /* limit-rate: maximum number of bytes per second to send or receive */
  CINIT(MAX_SEND_SPEED_LARGE, OFF_T, 145),
  CINIT(MAX_RECV_SPEED_LARGE, OFF_T, 146),

  /* Pointer to command string to send if USER/PASS fails. */
  CINIT(FTP_ALTERNATIVE_TO_USER, STRINGPOINT, 147),

  /* callback function for setting socket options */
  CINIT(SOCKOPTFUNCTION, FUNCTIONPOINT, 148),
  CINIT(SOCKOPTDATA, OBJECTPOINT, 149),

  /* set to 0 to disable session ID re-use for this transfer, default is
     enabled (== 1) */
  CINIT(SSL_SESSIONID_CACHE, LONG, 150),

  /* allowed SSH authentication methods */
  CINIT(SSH_AUTH_TYPES, LONG, 151),

  /* Used by scp/sftp to do public/private key authentication */
  CINIT(SSH_PUBLIC_KEYFILE, STRINGPOINT, 152),
  CINIT(SSH_PRIVATE_KEYFILE, STRINGPOINT, 153),

  /* Send CCC (Clear Command Channel) after authentication */
  CINIT(FTP_SSL_CCC, LONG, 154),

  /* Same as TIMEOUT and CONNECTTIMEOUT, but with ms resolution */
  CINIT(TIMEOUT_MS, LONG, 155),
  CINIT(CONNECTTIMEOUT_MS, LONG, 156),

  /* set to zero to disable the libcurl's decoding and thus pass the raw body
     data to the application even when it is encoded/compressed */
  CINIT(HTTP_TRANSFER_DECODING, LONG, 157),
  CINIT(HTTP_CONTENT_DECODING, LONG, 158),

  /* Permission used when creating new files and directories on the remote
     server for protocols that support it, SFTP/SCP/FILE */
  CINIT(NEW_FILE_PERMS, LONG, 159),
  CINIT(NEW_DIRECTORY_PERMS, LONG, 160),

  /* Set the behaviour of POST when redirecting. Values must be set to one
     of CURL_REDIR* defines below. This used to be called CURLOPT_POST301 */
  CINIT(POSTREDIR, LONG, 161),

  /* used by scp/sftp to verify the host's public key */
  CINIT(SSH_HOST_PUBLIC_KEY_MD5, STRINGPOINT, 162),

  /* Callback function for opening socket (instead of socket(2)). Optionally,
     callback is able change the address or refuse to connect returning
     CURL_SOCKET_BAD.  The callback should have type
     curl_opensocket_callback */
  CINIT(OPENSOCKETFUNCTION, FUNCTIONPOINT, 163),
  CINIT(OPENSOCKETDATA, OBJECTPOINT, 164),

  /* POST volatile input fields. */
  CINIT(COPYPOSTFIELDS, OBJECTPOINT, 165),

  /* set transfer mode (;type=<a|i>) when doing FTP via an HTTP proxy */
  CINIT(PROXY_TRANSFER_MODE, LONG, 166),

  /* Callback function for seeking in the input stream */
  CINIT(SEEKFUNCTION, FUNCTIONPOINT, 167),
  CINIT(SEEKDATA, OBJECTPOINT, 168),

  /* CRL file */
  CINIT(CRLFILE, STRINGPOINT, 169),

  /* Issuer certificate */
  CINIT(ISSUERCERT, STRINGPOINT, 170),

  /* (IPv6) Address scope */
  CINIT(ADDRESS_SCOPE, LONG, 171),

  /* Collect certificate chain info and allow it to get retrievable with
     CURLINFO_CERTINFO after the transfer is complete. */
  CINIT(CERTINFO, LONG, 172),

  /* "name" and "pwd" to use when fetching. */
  CINIT(USERNAME, STRINGPOINT, 173),
  CINIT(PASSWORD, STRINGPOINT, 174),

    /* "name" and "pwd" to use with Proxy when fetching. */
  CINIT(PROXYUSERNAME, STRINGPOINT, 175),
  CINIT(PROXYPASSWORD, STRINGPOINT, 176),

  /* Comma separated list of hostnames defining no-proxy zones. These should
     match both hostnames directly, and hostnames within a domain. For
     example, local.com will match local.com and www.local.com, but NOT
     notlocal.com or www.notlocal.com. For compatibility with other
     implementations of this, .local.com will be considered to be the same as
     local.com. A single * is the only valid wildcard, and effectively
     disables the use of proxy. */
  CINIT(NOPROXY, STRINGPOINT, 177),

  /* block size for TFTP transfers */
  CINIT(TFTP_BLKSIZE, LONG, 178),

  /* Socks Service */
  CINIT(SOCKS5_GSSAPI_SERVICE, STRINGPOINT, 179),

  /* Socks Service */
  CINIT(SOCKS5_GSSAPI_NEC, LONG, 180),

  /* set the bitmask for the protocols that are allowed to be used for the
     transfer, which thus helps the app which takes URLs from users or other
     external inputs and want to restrict what protocol(s) to deal
     with. Defaults to CURLPROTO_ALL. */
  CINIT(PROTOCOLS, LONG, 181),

  /* set the bitmask for the protocols that libcurl is allowed to follow to,
     as a subset of the CURLOPT_PROTOCOLS ones. That means the protocol needs
     to be set in both bitmasks to be allowed to get redirected to. Defaults
     to all protocols except FILE and SCP. */
  CINIT(REDIR_PROTOCOLS, LONG, 182),

  /* set the SSH knownhost file name to use */
  CINIT(SSH_KNOWNHOSTS, STRINGPOINT, 183),

  /* set the SSH host key callback, must point to a curl_sshkeycallback
     function */
  CINIT(SSH_KEYFUNCTION, FUNCTIONPOINT, 184),

  /* set the SSH host key callback custom pointer */
  CINIT(SSH_KEYDATA, OBJECTPOINT, 185),

  /* set the SMTP mail originator */
  CINIT(MAIL_FROM, STRINGPOINT, 186),

  /* set the list of SMTP mail receiver(s) */
  CINIT(MAIL_RCPT, OBJECTPOINT, 187),

  /* FTP: send PRET before PASV */
  CINIT(FTP_USE_PRET, LONG, 188),

  /* RTSP request method (OPTIONS, SETUP, PLAY, etc...) */
  CINIT(RTSP_REQUEST, LONG, 189),

  /* The RTSP session identifier */
  CINIT(RTSP_SESSION_ID, STRINGPOINT, 190),

  /* The RTSP stream URI */
  CINIT(RTSP_STREAM_URI, STRINGPOINT, 191),

  /* The Transport: header to use in RTSP requests */
  CINIT(RTSP_TRANSPORT, STRINGPOINT, 192),

  /* Manually initialize the client RTSP CSeq for this handle */
  CINIT(RTSP_CLIENT_CSEQ, LONG, 193),

  /* Manually initialize the server RTSP CSeq for this handle */
  CINIT(RTSP_SERVER_CSEQ, LONG, 194),

  /* The stream to pass to INTERLEAVEFUNCTION. */
  CINIT(INTERLEAVEDATA, OBJECTPOINT, 195),

  /* Let the application define a custom write method for RTP data */
  CINIT(INTERLEAVEFUNCTION, FUNCTIONPOINT, 196),

  /* Turn on wildcard matching */
  CINIT(WILDCARDMATCH, LONG, 197),

  /* Directory matching callback called before downloading of an
     individual file (chunk) started */
  CINIT(CHUNK_BGN_FUNCTION, FUNCTIONPOINT, 198),

  /* Directory matching callback called after the file (chunk)
     was downloaded, or skipped */
  CINIT(CHUNK_END_FUNCTION, FUNCTIONPOINT, 199),

  /* Change match (fnmatch-like) callback for wildcard matching */
  CINIT(FNMATCH_FUNCTION, FUNCTIONPOINT, 200),

  /* Let the application define custom chunk data pointer */
  CINIT(CHUNK_DATA, OBJECTPOINT, 201),

  /* FNMATCH_FUNCTION user pointer */
  CINIT(FNMATCH_DATA, OBJECTPOINT, 202),

  /* send linked-list of name:port:address sets */
  CINIT(RESOLVE, OBJECTPOINT, 203),

  /* Set a username for authenticated TLS */
  CINIT(TLSAUTH_USERNAME, STRINGPOINT, 204),

  /* Set a password for authenticated TLS */
  CINIT(TLSAUTH_PASSWORD, STRINGPOINT, 205),

  /* Set authentication type for authenticated TLS */
  CINIT(TLSAUTH_TYPE, STRINGPOINT, 206),

  /* Set to 1 to enable the "TE:" header in HTTP requests to ask for
     compressed transfer-encoded responses. Set to 0 to disable the use of TE:
     in outgoing requests. The current default is 0, but it might change in a
     future libcurl release.

     libcurl will ask for the compressed methods it knows of, and if that
     isn't any, it will not ask for transfer-encoding at all even if this
     option is set to 1.

  */
  CINIT(TRANSFER_ENCODING, LONG, 207),

  /* Callback function for closing socket (instead of close(2)). The callback
     should have type curl_closesocket_callback */
  CINIT(CLOSESOCKETFUNCTION, FUNCTIONPOINT, 208),
  CINIT(CLOSESOCKETDATA, OBJECTPOINT, 209),

  /* allow GSSAPI credential delegation */
  CINIT(GSSAPI_DELEGATION, LONG, 210),

  /* Set the name servers to use for DNS resolution */
  CINIT(DNS_SERVERS, STRINGPOINT, 211),

  /* Time-out accept operations (currently for FTP only) after this amount
     of miliseconds. */
  CINIT(ACCEPTTIMEOUT_MS, LONG, 212),

  /* Set TCP keepalive */
  CINIT(TCP_KEEPALIVE, LONG, 213),

  /* non-universal keepalive knobs (Linux, AIX, HP-UX, more) */
  CINIT(TCP_KEEPIDLE, LONG, 214),
  CINIT(TCP_KEEPINTVL, LONG, 215),

  /* Enable/disable specific SSL features with a bitmask, see CURLSSLOPT_* */
  CINIT(SSL_OPTIONS, LONG, 216),

  /* Set the SMTP auth originator */
  CINIT(MAIL_AUTH, STRINGPOINT, 217),

  /* Enable/disable SASL initial response */
  CINIT(SASL_IR, LONG, 218),

  /* Function that will be called instead of the internal progress display
   * function. This function should be defined as the curl_xferinfo_callback
   * prototype defines. (Deprecates CURLOPT_PROGRESSFUNCTION) */
  CINIT(XFERINFOFUNCTION, FUNCTIONPOINT, 219),

  /* The XOAUTH2 bearer token */
  CINIT(XOAUTH2_BEARER, STRINGPOINT, 220),

  /* Set the interface string to use as outgoing network
   * interface for DNS requests.
   * Only supported by the c-ares DNS backend */
  CINIT(DNS_INTERFACE, STRINGPOINT, 221),

  /* Set the local IPv4 address to use for outgoing DNS requests.
   * Only supported by the c-ares DNS backend */
  CINIT(DNS_LOCAL_IP4, STRINGPOINT, 222),

  /* Set the local IPv4 address to use for outgoing DNS requests.
   * Only supported by the c-ares DNS backend */
  CINIT(DNS_LOCAL_IP6, STRINGPOINT, 223),

  /* Set authentication options directly */
  CINIT(LOGIN_OPTIONS, STRINGPOINT, 224),

  /* Enable/disable TLS NPN extension (http2 over ssl might fail without) */
  CINIT(SSL_ENABLE_NPN, LONG, 225),

  /* Enable/disable TLS ALPN extension (http2 over ssl might fail without) */
  CINIT(SSL_ENABLE_ALPN, LONG, 226),

  /* Time to wait for a response to a HTTP request containing an
   * Expect: 100-continue header before sending the data anyway. */
  CINIT(EXPECT_100_TIMEOUT_MS, LONG, 227),

  /* This points to a linked list of headers used for proxy requests only,
     struct curl_slist kind */
  CINIT(PROXYHEADER, OBJECTPOINT, 228),

  /* Pass in a bitmask of "header options" */
  CINIT(HEADEROPT, LONG, 229),

  /* The public key in DER form used to validate the peer public key
     this option is used only if SSL_VERIFYPEER is true */
  CINIT(PINNEDPUBLICKEY, STRINGPOINT, 230),

  /* Path to Unix domain socket */
  CINIT(UNIX_SOCKET_PATH, STRINGPOINT, 231),

  /* Set if we should verify the certificate status. */
  CINIT(SSL_VERIFYSTATUS, LONG, 232),

  /* Set if we should enable TLS false start. */
  CINIT(SSL_FALSESTART, LONG, 233),

  /* Do not squash dot-dot sequences */
  CINIT(PATH_AS_IS, LONG, 234),

  /* Proxy Service Name */
  CINIT(PROXY_SERVICE_NAME, STRINGPOINT, 235),

  /* Service Name */
  CINIT(SERVICE_NAME, STRINGPOINT, 236),

  /* Wait/don't wait for pipe/mutex to clarify */
  CINIT(PIPEWAIT, LONG, 237),

  /* Set the protocol used when curl is given a URL without a protocol */
  CINIT(DEFAULT_PROTOCOL, STRINGPOINT, 238),

  /* Set stream weight, 1 - 256 (default is 16) */
  CINIT(STREAM_WEIGHT, LONG, 239),

  /* Set stream dependency on another CURL handle */
  CINIT(STREAM_DEPENDS, OBJECTPOINT, 240),

  /* Set E-xclusive stream dependency on another CURL handle */
  CINIT(STREAM_DEPENDS_E, OBJECTPOINT, 241),

  /* Do not send any tftp option requests to the server */
  CINIT(TFTP_NO_OPTIONS, LONG, 242),

  CURLOPT_LASTENTRY /* the last unused */
} CURLoption;

#ifndef CURL_NO_OLDIES /* define this to test if your app builds with all
                          the obsolete stuff removed! */

/* Backwards compatibility with older names */
/* These are scheduled to disappear by 2011 */

/* This was added in version 7.19.1 */
#define CURLOPT_POST301 CURLOPT_POSTREDIR

/* These are scheduled to disappear by 2009 */

/* The following were added in 7.17.0 */
#define CURLOPT_SSLKEYPASSWD CURLOPT_KEYPASSWD
#define CURLOPT_FTPAPPEND CURLOPT_APPEND
#define CURLOPT_FTPLISTONLY CURLOPT_DIRLISTONLY
#define CURLOPT_FTP_SSL CURLOPT_USE_SSL

/* The following were added earlier */

#define CURLOPT_SSLCERTPASSWD CURLOPT_KEYPASSWD
#define CURLOPT_KRB4LEVEL CURLOPT_KRBLEVEL

#else
/* This is set if CURL_NO_OLDIES is defined at compile-time */
#undef CURLOPT_DNS_USE_GLOBAL_CACHE /* soon obsolete */
#endif


  /* Below here follows defines for the CURLOPT_IPRESOLVE option. If a host
     name resolves addresses using more than one IP protocol version, this
     option might be handy to force libcurl to use a specific IP version. */
#define CURL_IPRESOLVE_WHATEVER 0 /* default, resolves addresses to all IP
                                     versions that your system allows */
#define CURL_IPRESOLVE_V4       1 /* resolve to IPv4 addresses */
#define CURL_IPRESOLVE_V6       2 /* resolve to IPv6 addresses */

  /* three convenient "aliases" that follow the name scheme better */
#define CURLOPT_RTSPHEADER CURLOPT_HTTPHEADER

  /* These enums are for use with the CURLOPT_HTTP_VERSION option. */
enum {
  CURL_HTTP_VERSION_NONE, /* setting this means we don't care, and that we'd
                             like the library to choose the best possible
                             for us! */
  CURL_HTTP_VERSION_1_0,  /* please use HTTP 1.0 in the request */
  CURL_HTTP_VERSION_1_1,  /* please use HTTP 1.1 in the request */
  CURL_HTTP_VERSION_2_0,  /* please use HTTP 2 in the request */
  CURL_HTTP_VERSION_2TLS, /* use version 2 for HTTPS, version 1.1 for HTTP */

  CURL_HTTP_VERSION_LAST /* *ILLEGAL* http version */
};

/* Convenience definition simple because the name of the version is HTTP/2 and
   not 2.0. The 2_0 version of the enum name was set while the version was
   still planned to be 2.0 and we stick to it for compatibility. */
#define CURL_HTTP_VERSION_2 CURL_HTTP_VERSION_2_0

/*
 * Public API enums for RTSP requests
 */
enum {
    CURL_RTSPREQ_NONE, /* first in list */
    CURL_RTSPREQ_OPTIONS,
    CURL_RTSPREQ_DESCRIBE,
    CURL_RTSPREQ_ANNOUNCE,
    CURL_RTSPREQ_SETUP,
    CURL_RTSPREQ_PLAY,
    CURL_RTSPREQ_PAUSE,
    CURL_RTSPREQ_TEARDOWN,
    CURL_RTSPREQ_GET_PARAMETER,
    CURL_RTSPREQ_SET_PARAMETER,
    CURL_RTSPREQ_RECORD,
    CURL_RTSPREQ_RECEIVE,
    CURL_RTSPREQ_LAST /* last in list */
};

  /* These enums are for use with the CURLOPT_NETRC option. */
enum CURL_NETRC_OPTION {
  CURL_NETRC_IGNORED,     /* The .netrc will never be read.
                           * This is the default. */
  CURL_NETRC_OPTIONAL,    /* A user:password in the URL will be preferred
                           * to one in the .netrc. */
  CURL_NETRC_REQUIRED,    /* A user:password in the URL will be ignored.
                           * Unless one is set programmatically, the .netrc
                           * will be queried. */
  CURL_NETRC_LAST
};

enum {
  CURL_SSLVERSION_DEFAULT,
  CURL_SSLVERSION_TLSv1, /* TLS 1.x */
  CURL_SSLVERSION_SSLv2,
  CURL_SSLVERSION_SSLv3,
  CURL_SSLVERSION_TLSv1_0,
  CURL_SSLVERSION_TLSv1_1,
  CURL_SSLVERSION_TLSv1_2,

  CURL_SSLVERSION_LAST /* never use, keep last */
};

enum CURL_TLSAUTH {
  CURL_TLSAUTH_NONE,
  CURL_TLSAUTH_SRP,
  CURL_TLSAUTH_LAST /* never use, keep last */
};

/* symbols to use with CURLOPT_POSTREDIR.
   CURL_REDIR_POST_301, CURL_REDIR_POST_302 and CURL_REDIR_POST_303
   can be bitwise ORed so that CURL_REDIR_POST_301 | CURL_REDIR_POST_302
   | CURL_REDIR_POST_303 == CURL_REDIR_POST_ALL */

#define CURL_REDIR_GET_ALL  0
#define CURL_REDIR_POST_301 1
#define CURL_REDIR_POST_302 2
#define CURL_REDIR_POST_303 4
#define CURL_REDIR_POST_ALL \
    (CURL_REDIR_POST_301|CURL_REDIR_POST_302|CURL_REDIR_POST_303)

typedef enum {
  CURL_TIMECOND_NONE,

  CURL_TIMECOND_IFMODSINCE,
  CURL_TIMECOND_IFUNMODSINCE,
  CURL_TIMECOND_LASTMOD,

  CURL_TIMECOND_LAST
} curl_TimeCond;


/* curl_strequal() and curl_strnequal() are subject for removal in a future
   libcurl, see lib/README.curlx for details */
CURL_EXTERN int (curl_strequal)(const char *s1, const char *s2);
CURL_EXTERN int (curl_strnequal)(const char *s1, const char *s2, size_t n);

/* name is uppercase CURLFORM_<name> */
#ifdef CFINIT
#undef CFINIT
#endif

#ifdef CURL_ISOCPP
#define CFINIT(name) CURLFORM_ ## name
#else
/* The macro "##" is ISO C, we assume pre-ISO C doesn't support it. */
#define CFINIT(name) CURLFORM_/**/name
#endif

typedef enum {
  CFINIT(NOTHING),        /********* the first one is unused ************/

  /*  */
  CFINIT(COPYNAME),
  CFINIT(PTRNAME),
  CFINIT(NAMELENGTH),
  CFINIT(COPYCONTENTS),
  CFINIT(PTRCONTENTS),
  CFINIT(CONTENTSLENGTH),
  CFINIT(FILECONTENT),
  CFINIT(ARRAY),
  CFINIT(OBSOLETE),
  CFINIT(FILE),

  CFINIT(BUFFER),
  CFINIT(BUFFERPTR),
  CFINIT(BUFFERLENGTH),

  CFINIT(CONTENTTYPE),
  CFINIT(CONTENTHEADER),
  CFINIT(FILENAME),
  CFINIT(END),
  CFINIT(OBSOLETE2),

  CFINIT(STREAM),
  CFINIT(CONTENTLEN), /* added in 7.46.0, provide a curl_off_t length */

  CURLFORM_LASTENTRY /* the last unused */
} CURLformoption;

#undef CFINIT /* done */

/* structure to be used as parameter for CURLFORM_ARRAY */
struct curl_forms {
  CURLformoption option;
  const char     *value;
};

/* use this for multipart formpost building */
/* Returns code for curl_formadd()
 *
 * Returns:
 * CURL_FORMADD_OK             on success
 * CURL_FORMADD_MEMORY         if the FormInfo allocation fails
 * CURL_FORMADD_OPTION_TWICE   if one option is given twice for one Form
 * CURL_FORMADD_NULL           if a null pointer was given for a char
 * CURL_FORMADD_MEMORY         if the allocation of a FormInfo struct failed
 * CURL_FORMADD_UNKNOWN_OPTION if an unknown option was used
 * CURL_FORMADD_INCOMPLETE     if the some FormInfo is not complete (or error)
 * CURL_FORMADD_MEMORY         if a curl_httppost struct cannot be allocated
 * CURL_FORMADD_MEMORY         if some allocation for string copying failed.
 * CURL_FORMADD_ILLEGAL_ARRAY  if an illegal option is used in an array
 *
 ***************************************************************************/
typedef enum {
  CURL_FORMADD_OK, /* first, no error */

  CURL_FORMADD_MEMORY,
  CURL_FORMADD_OPTION_TWICE,
  CURL_FORMADD_NULL,
  CURL_FORMADD_UNKNOWN_OPTION,
  CURL_FORMADD_INCOMPLETE,
  CURL_FORMADD_ILLEGAL_ARRAY,
  CURL_FORMADD_DISABLED, /* libcurl was built with this disabled */

  CURL_FORMADD_LAST /* last */
} CURLFORMcode;

/*
 * NAME curl_formadd()
 *
 * DESCRIPTION
 *
 * Pretty advanced function for building multi-part formposts. Each invoke
 * adds one part that together construct a full post. Then use
 * CURLOPT_HTTPPOST to send it off to libcurl.
 */
CURL_EXTERN CURLFORMcode curl_formadd(struct curl_httppost **httppost,
                                      struct curl_httppost **last_post,
                                      ...);

/*
 * callback function for curl_formget()
 * The void *arg pointer will be the one passed as second argument to
 *   curl_formget().
 * The character buffer passed to it must not be freed.
 * Should return the buffer length passed to it as the argument "len" on
 *   success.
 */
typedef size_t (*curl_formget_callback)(void *arg, const char *buf,
                                        size_t len);

/*
 * NAME curl_formget()
 *
 * DESCRIPTION
 *
 * Serialize a curl_httppost struct built with curl_formadd().
 * Accepts a void pointer as second argument which will be passed to
 * the curl_formget_callback function.
 * Returns 0 on success.
 */
CURL_EXTERN int curl_formget(struct curl_httppost *form, void *arg,
                             curl_formget_callback append);
/*
 * NAME curl_formfree()
 *
 * DESCRIPTION
 *
 * Free a multipart formpost previously built with curl_formadd().
 */
CURL_EXTERN void curl_formfree(struct curl_httppost *form);

/*
 * NAME curl_getenv()
 *
 * DESCRIPTION
 *
 * Returns a malloc()'ed string that MUST be curl_free()ed after usage is
 * complete. DEPRECATED - see lib/README.curlx
 */
CURL_EXTERN char *curl_getenv(const char *variable);

/*
 * NAME curl_version()
 *
 * DESCRIPTION
 *
 * Returns a static ascii string of the libcurl version.
 */
CURL_EXTERN char *curl_version(void);

/*
 * NAME curl_easy_escape()
 *
 * DESCRIPTION
 *
 * Escapes URL strings (converts all letters consider illegal in URLs to their
 * %XX versions). This function returns a new allocated string or NULL if an
 * error occurred.
 */
CURL_EXTERN char *curl_easy_escape(CURL *handle,
                                   const char *string,
                                   int length);

/* the previous version: */
CURL_EXTERN char *curl_escape(const char *string,
                              int length);


/*
 * NAME curl_easy_unescape()
 *
 * DESCRIPTION
 *
 * Unescapes URL encoding in strings (converts all %XX codes to their 8bit
 * versions). This function returns a new allocated string or NULL if an error
 * occurred.
 * Conversion Note: On non-ASCII platforms the ASCII %XX codes are
 * converted into the host encoding.
 */
CURL_EXTERN char *curl_easy_unescape(CURL *handle,
                                     const char *string,
                                     int length,
                                     int *outlength);

/* the previous version */
CURL_EXTERN char *curl_unescape(const char *string,
                                int length);

/*
 * NAME curl_free()
 *
 * DESCRIPTION
 *
 * Provided for de-allocation in the same translation unit that did the
 * allocation. Added in libcurl 7.10
 */
CURL_EXTERN void curl_free(void *p);

/*
 * NAME curl_global_init()
 *
 * DESCRIPTION
 *
 * curl_global_init() should be invoked exactly once for each application that
 * uses libcurl and before any call of other libcurl functions.
 *
 * This function is not thread-safe!
 */
CURL_EXTERN CURLcode curl_global_init(long flags);

/*
 * NAME curl_global_init_mem()
 *
 * DESCRIPTION
 *
 * curl_global_init() or curl_global_init_mem() should be invoked exactly once
 * for each application that uses libcurl.  This function can be used to
 * initialize libcurl and set user defined memory management callback
 * functions.  Users can implement memory management routines to check for
 * memory leaks, check for mis-use of the curl library etc.  User registered
 * callback routines with be invoked by this library instead of the system
 * memory management routines like malloc, free etc.
 */
CURL_EXTERN CURLcode curl_global_init_mem(long flags,
                                          curl_malloc_callback m,
                                          curl_free_callback f,
                                          curl_realloc_callback r,
                                          curl_strdup_callback s,
                                          curl_calloc_callback c);

/*
 * NAME curl_global_cleanup()
 *
 * DESCRIPTION
 *
 * curl_global_cleanup() should be invoked exactly once for each application
 * that uses libcurl
 */
CURL_EXTERN void curl_global_cleanup(void);

/* linked-list structure for the CURLOPT_QUOTE option (and other) */
struct curl_slist {
  char *data;
  struct curl_slist *next;
};

/*
 * NAME curl_slist_append()
 *
 * DESCRIPTION
 *
 * Appends a string to a linked list. If no list exists, it will be created
 * first. Returns the new list, after appending.
 */
CURL_EXTERN struct curl_slist *curl_slist_append(struct curl_slist *,
                                                 const char *);

/*
 * NAME curl_slist_free_all()
 *
 * DESCRIPTION
 *
 * free a previously built curl_slist.
 */
CURL_EXTERN void curl_slist_free_all(struct curl_slist *);

/*
 * NAME curl_getdate()
 *
 * DESCRIPTION
 *
 * Returns the time, in seconds since 1 Jan 1970 of the time string given in
 * the first argument. The time argument in the second parameter is unused
 * and should be set to NULL.
 */
CURL_EXTERN time_t curl_getdate(const char *p, const time_t *unused);

/* info about the certificate chain, only for OpenSSL builds. Asked
   for with CURLOPT_CERTINFO / CURLINFO_CERTINFO */
struct curl_certinfo {
  int num_of_certs;             /* number of certificates with information */
  struct curl_slist **certinfo; /* for each index in this array, there's a
                                   linked list with textual information in the
                                   format "name: value" */
};

/* enum for the different supported SSL backends */
typedef enum {
  CURLSSLBACKEND_NONE = 0,
  CURLSSLBACKEND_OPENSSL = 1,
  CURLSSLBACKEND_GNUTLS = 2,
  CURLSSLBACKEND_NSS = 3,
  CURLSSLBACKEND_OBSOLETE4 = 4,  /* Was QSOSSL. */
  CURLSSLBACKEND_GSKIT = 5,
  CURLSSLBACKEND_POLARSSL = 6,
  CURLSSLBACKEND_CYASSL = 7,
  CURLSSLBACKEND_SCHANNEL = 8,
  CURLSSLBACKEND_DARWINSSL = 9,
  CURLSSLBACKEND_AXTLS = 10,
  CURLSSLBACKEND_MBEDTLS = 11
} curl_sslbackend;

/* Information about the SSL library used and the respective internal SSL
   handle, which can be used to obtain further information regarding the
   connection. Asked for with CURLINFO_TLS_SSL_PTR or CURLINFO_TLS_SESSION. */
struct curl_tlssessioninfo {
  curl_sslbackend backend;
  void *internals;
};

#define CURLINFO_STRING   0x100000
#define CURLINFO_LONG     0x200000
#define CURLINFO_DOUBLE   0x300000
#define CURLINFO_SLIST    0x400000
#define CURLINFO_SOCKET   0x500000
#define CURLINFO_MASK     0x0fffff
#define CURLINFO_TYPEMASK 0xf00000

typedef enum {
  CURLINFO_NONE, /* first, never use this */
  CURLINFO_EFFECTIVE_URL    = CURLINFO_STRING + 1,
  CURLINFO_RESPONSE_CODE    = CURLINFO_LONG   + 2,
  CURLINFO_TOTAL_TIME       = CURLINFO_DOUBLE + 3,
  CURLINFO_NAMELOOKUP_TIME  = CURLINFO_DOUBLE + 4,
  CURLINFO_CONNECT_TIME     = CURLINFO_DOUBLE + 5,
  CURLINFO_PRETRANSFER_TIME = CURLINFO_DOUBLE + 6,
  CURLINFO_SIZE_UPLOAD      = CURLINFO_DOUBLE + 7,
  CURLINFO_SIZE_DOWNLOAD    = CURLINFO_DOUBLE + 8,
  CURLINFO_SPEED_DOWNLOAD   = CURLINFO_DOUBLE + 9,
  CURLINFO_SPEED_UPLOAD     = CURLINFO_DOUBLE + 10,
  CURLINFO_HEADER_SIZE      = CURLINFO_LONG   + 11,
  CURLINFO_REQUEST_SIZE     = CURLINFO_LONG   + 12,
  CURLINFO_SSL_VERIFYRESULT = CURLINFO_LONG   + 13,
  CURLINFO_FILETIME         = CURLINFO_LONG   + 14,
  CURLINFO_CONTENT_LENGTH_DOWNLOAD   = CURLINFO_DOUBLE + 15,
  CURLINFO_CONTENT_LENGTH_UPLOAD     = CURLINFO_DOUBLE + 16,
  CURLINFO_STARTTRANSFER_TIME = CURLINFO_DOUBLE + 17,
  CURLINFO_CONTENT_TYPE     = CURLINFO_STRING + 18,
  CURLINFO_REDIRECT_TIME    = CURLINFO_DOUBLE + 19,
  CURLINFO_REDIRECT_COUNT   = CURLINFO_LONG   + 20,
  CURLINFO_PRIVATE          = CURLINFO_STRING + 21,
  CURLINFO_HTTP_CONNECTCODE = CURLINFO_LONG   + 22,
  CURLINFO_HTTPAUTH_AVAIL   = CURLINFO_LONG   + 23,
  CURLINFO_PROXYAUTH_AVAIL  = CURLINFO_LONG   + 24,
  CURLINFO_OS_ERRNO         = CURLINFO_LONG   + 25,
  CURLINFO_NUM_CONNECTS     = CURLINFO_LONG   + 26,
  CURLINFO_SSL_ENGINES      = CURLINFO_SLIST  + 27,
  CURLINFO_COOKIELIST       = CURLINFO_SLIST  + 28,
  CURLINFO_LASTSOCKET       = CURLINFO_LONG   + 29,
  CURLINFO_FTP_ENTRY_PATH   = CURLINFO_STRING + 30,
  CURLINFO_REDIRECT_URL     = CURLINFO_STRING + 31,
  CURLINFO_PRIMARY_IP       = CURLINFO_STRING + 32,
  CURLINFO_APPCONNECT_TIME  = CURLINFO_DOUBLE + 33,
  CURLINFO_CERTINFO         = CURLINFO_SLIST  + 34,
  CURLINFO_CONDITION_UNMET  = CURLINFO_LONG   + 35,
  CURLINFO_RTSP_SESSION_ID  = CURLINFO_STRING + 36,
  CURLINFO_RTSP_CLIENT_CSEQ = CURLINFO_LONG   + 37,
  CURLINFO_RTSP_SERVER_CSEQ = CURLINFO_LONG   + 38,
  CURLINFO_RTSP_CSEQ_RECV   = CURLINFO_LONG   + 39,
  CURLINFO_PRIMARY_PORT     = CURLINFO_LONG   + 40,
  CURLINFO_LOCAL_IP         = CURLINFO_STRING + 41,
  CURLINFO_LOCAL_PORT       = CURLINFO_LONG   + 42,
  CURLINFO_TLS_SESSION      = CURLINFO_SLIST  + 43,
  CURLINFO_ACTIVESOCKET     = CURLINFO_SOCKET + 44,
  CURLINFO_TLS_SSL_PTR      = CURLINFO_SLIST  + 45,
  /* Fill in new entries below here! */

  CURLINFO_LASTONE          = 45
} CURLINFO;

/* CURLINFO_RESPONSE_CODE is the new name for the option previously known as
   CURLINFO_HTTP_CODE */
#define CURLINFO_HTTP_CODE CURLINFO_RESPONSE_CODE

typedef enum {
  CURLCLOSEPOLICY_NONE, /* first, never use this */

  CURLCLOSEPOLICY_OLDEST,
  CURLCLOSEPOLICY_LEAST_RECENTLY_USED,
  CURLCLOSEPOLICY_LEAST_TRAFFIC,
  CURLCLOSEPOLICY_SLOWEST,
  CURLCLOSEPOLICY_CALLBACK,

  CURLCLOSEPOLICY_LAST /* last, never use this */
} curl_closepolicy;

#define CURL_GLOBAL_SSL (1<<0)
#define CURL_GLOBAL_WIN32 (1<<1)
#define CURL_GLOBAL_ALL (CURL_GLOBAL_SSL|CURL_GLOBAL_WIN32)
#define CURL_GLOBAL_NOTHING 0
#define CURL_GLOBAL_DEFAULT CURL_GLOBAL_ALL
#define CURL_GLOBAL_ACK_EINTR (1<<2)


/*****************************************************************************
 * Setup defines, protos etc for the sharing stuff.
 */

/* Different data locks for a single share */
typedef enum {
  CURL_LOCK_DATA_NONE = 0,
  /*  CURL_LOCK_DATA_SHARE is used internally to say that
   *  the locking is just made to change the internal state of the share
   *  itself.
   */
  CURL_LOCK_DATA_SHARE,
  CURL_LOCK_DATA_COOKIE,
  CURL_LOCK_DATA_DNS,
  CURL_LOCK_DATA_SSL_SESSION,
  CURL_LOCK_DATA_CONNECT,
  CURL_LOCK_DATA_LAST
} curl_lock_data;

/* Different lock access types */
typedef enum {
  CURL_LOCK_ACCESS_NONE = 0,   /* unspecified action */
  CURL_LOCK_ACCESS_SHARED = 1, /* for read perhaps */
  CURL_LOCK_ACCESS_SINGLE = 2, /* for write perhaps */
  CURL_LOCK_ACCESS_LAST        /* never use */
} curl_lock_access;

typedef void (*curl_lock_function)(CURL *handle,
                                   curl_lock_data data,
                                   curl_lock_access locktype,
                                   void *userptr);
typedef void (*curl_unlock_function)(CURL *handle,
                                     curl_lock_data data,
                                     void *userptr);

typedef void CURLSH;

typedef enum {
  CURLSHE_OK,  /* all is fine */
  CURLSHE_BAD_OPTION, /* 1 */
  CURLSHE_IN_USE,     /* 2 */
  CURLSHE_INVALID,    /* 3 */
  CURLSHE_NOMEM,      /* 4 out of memory */
  CURLSHE_NOT_BUILT_IN, /* 5 feature not present in lib */
  CURLSHE_LAST        /* never use */
} CURLSHcode;

typedef enum {
  CURLSHOPT_NONE,  /* don't use */
  CURLSHOPT_SHARE,   /* specify a data type to share */
  CURLSHOPT_UNSHARE, /* specify which data type to stop sharing */
  CURLSHOPT_LOCKFUNC,   /* pass in a 'curl_lock_function' pointer */
  CURLSHOPT_UNLOCKFUNC, /* pass in a 'curl_unlock_function' pointer */
  CURLSHOPT_USERDATA,   /* pass in a user data pointer used in the lock/unlock
                           callback functions */
  CURLSHOPT_LAST  /* never use */
} CURLSHoption;

CURL_EXTERN CURLSH *curl_share_init(void);
CURL_EXTERN CURLSHcode curl_share_setopt(CURLSH *, CURLSHoption option, ...);
CURL_EXTERN CURLSHcode curl_share_cleanup(CURLSH *);

/****************************************************************************
 * Structures for querying information about the curl library at runtime.
 */

typedef enum {
  CURLVERSION_FIRST,
  CURLVERSION_SECOND,
  CURLVERSION_THIRD,
  CURLVERSION_FOURTH,
  CURLVERSION_LAST /* never actually use this */
} CURLversion;

/* The 'CURLVERSION_NOW' is the symbolic name meant to be used by
   basically all programs ever that want to get version information. It is
   meant to be a built-in version number for what kind of struct the caller
   expects. If the struct ever changes, we redefine the NOW to another enum
   from above. */
#define CURLVERSION_NOW CURLVERSION_FOURTH

typedef struct {
  CURLversion age;          /* age of the returned struct */
  const char *version;      /* LIBCURL_VERSION */
  unsigned int version_num; /* LIBCURL_VERSION_NUM */
  const char *host;         /* OS/host/cpu/machine when configured */
  int features;             /* bitmask, see defines below */
  const char *ssl_version;  /* human readable string */
  long ssl_version_num;     /* not used anymore, always 0 */
  const char *libz_version; /* human readable string */
  /* protocols is terminated by an entry with a NULL protoname */
  const char * const *protocols;

  /* The fields below this were added in CURLVERSION_SECOND */
  const char *ares;
  int ares_num;

  /* This field was added in CURLVERSION_THIRD */
  const char *libidn;

  /* These field were added in CURLVERSION_FOURTH */

  /* Same as '_libiconv_version' if built with HAVE_ICONV */
  int iconv_ver_num;

  const char *libssh_version; /* human readable string */

} curl_version_info_data;

#define CURL_VERSION_IPV6         (1<<0)  /* IPv6-enabled */
#define CURL_VERSION_KERBEROS4    (1<<1)  /* Kerberos V4 auth is supported
                                             (deprecated) */
#define CURL_VERSION_SSL          (1<<2)  /* SSL options are present */
#define CURL_VERSION_LIBZ         (1<<3)  /* libz features are present */
#define CURL_VERSION_NTLM         (1<<4)  /* NTLM auth is supported */
#define CURL_VERSION_GSSNEGOTIATE (1<<5)  /* Negotiate auth is supported
                                             (deprecated) */
#define CURL_VERSION_DEBUG        (1<<6)  /* Built with debug capabilities */
#define CURL_VERSION_ASYNCHDNS    (1<<7)  /* Asynchronous DNS resolves */
#define CURL_VERSION_SPNEGO       (1<<8)  /* SPNEGO auth is supported */
#define CURL_VERSION_LARGEFILE    (1<<9)  /* Supports files larger than 2GB */
#define CURL_VERSION_IDN          (1<<10) /* Internationized Domain Names are
                                             supported */
#define CURL_VERSION_SSPI         (1<<11) /* Built against Windows SSPI */
#define CURL_VERSION_CONV         (1<<12) /* Character conversions supported */
#define CURL_VERSION_CURLDEBUG    (1<<13) /* Debug memory tracking supported */
#define CURL_VERSION_TLSAUTH_SRP  (1<<14) /* TLS-SRP auth is supported */
#define CURL_VERSION_NTLM_WB      (1<<15) /* NTLM delegation to winbind helper
                                             is suported */
#define CURL_VERSION_HTTP2        (1<<16) /* HTTP2 support built-in */
#define CURL_VERSION_GSSAPI       (1<<17) /* Built against a GSS-API library */
#define CURL_VERSION_KERBEROS5    (1<<18) /* Kerberos V5 auth is supported */
#define CURL_VERSION_UNIX_SOCKETS (1<<19) /* Unix domain sockets support */
#define CURL_VERSION_PSL          (1<<20) /* Mozilla's Public Suffix List, used
                                             for cookie domain verification */

 /*
 * NAME curl_version_info()
 *
 * DESCRIPTION
 *
 * This function returns a pointer to a static copy of the version info
 * struct. See above.
 */
CURL_EXTERN curl_version_info_data *curl_version_info(CURLversion);

/*
 * NAME curl_easy_strerror()
 *
 * DESCRIPTION
 *
 * The curl_easy_strerror function may be used to turn a CURLcode value
 * into the equivalent human readable error string.  This is useful
 * for printing meaningful error messages.
 */
CURL_EXTERN const char *curl_easy_strerror(CURLcode);

/*
 * NAME curl_share_strerror()
 *
 * DESCRIPTION
 *
 * The curl_share_strerror function may be used to turn a CURLSHcode value
 * into the equivalent human readable error string.  This is useful
 * for printing meaningful error messages.
 */
CURL_EXTERN const char *curl_share_strerror(CURLSHcode);

/*
 * NAME curl_easy_pause()
 *
 * DESCRIPTION
 *
 * The curl_easy_pause function pauses or unpauses transfers. Select the new
 * state by setting the bitmask, use the convenience defines below.
 *
 */
CURL_EXTERN CURLcode curl_easy_pause(CURL *handle, int bitmask);

#define CURLPAUSE_RECV      (1<<0)
#define CURLPAUSE_RECV_CONT (0)

#define CURLPAUSE_SEND      (1<<2)
#define CURLPAUSE_SEND_CONT (0)

#define CURLPAUSE_ALL       (CURLPAUSE_RECV|CURLPAUSE_SEND)
#define CURLPAUSE_CONT      (CURLPAUSE_RECV_CONT|CURLPAUSE_SEND_CONT)

#ifdef  __cplusplus
}
#endif

/* unfortunately, the easy.h and multi.h include files need options and info
  stuff before they can be included! */
#include "easy.h" /* nothing in curl is fun without the easy stuff */
#include "multi.h"

/* the typechecker doesn't work in C++ (yet) */
#if defined(__GNUC__) && defined(__GNUC_MINOR__) && \
    ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)) && \
    !defined(__cplusplus) && !defined(CURL_DISABLE_TYPECHECK)
#include "typecheck-gcc.h"
#else
#if defined(__STDC__) && (__STDC__ >= 1)
/* This preprocessor magic that replaces a call with the exact same call is
   only done to make sure application authors pass exactly three arguments
   to these functions. */
#define curl_easy_setopt(handle,opt,param) curl_easy_setopt(handle,opt,param)
#define curl_easy_getinfo(handle,info,arg) curl_easy_getinfo(handle,info,arg)
#define curl_share_setopt(share,opt,param) curl_share_setopt(share,opt,param)
#define curl_multi_setopt(handle,opt,param) curl_multi_setopt(handle,opt,param)
#endif /* __STDC__ >= 1 */
#endif /* gcc >= 4.3 && !__cplusplus */

#endif /* __CURL_CURL_H */
