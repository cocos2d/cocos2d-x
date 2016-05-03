/*
 * libwebsockets - small server side websockets and web server implementation
 *
 * Copyright (C) 2010-2016 Andy Green <andy@warmcat.com>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation:
 *  version 2.1 of the License.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA  02110-1301  USA
 */

#ifndef LIBWEBSOCKET_H_3060898B846849FF9F88F5DB59B5950C
#define LIBWEBSOCKET_H_3060898B846849FF9F88F5DB59B5950C

#ifdef __cplusplus
#include <cstddef>
#include <cstdarg>
#ifdef MBED_OPERATORS
#include "mbed-drivers/mbed.h"
#include "sal-iface-eth/EthernetInterface.h"
#include "sockets/TCPListener.h"
#include "sal-stack-lwip/lwipv4_init.h"

namespace {
}
using namespace mbed::Sockets::v0;

struct lws;
struct lws_context;

class lws_conn {
	public:
	lws_conn():
		ts(NULL),
		wsi(NULL),
		writeable(1),
		awaiting_on_writeable(0)
	{
	}

public:
	void set_wsi(struct lws *_wsi) { wsi = _wsi; }
	int actual_onRX(Socket *s);
	void onRX(Socket *s);
	void onError(Socket *s, socket_error_t err);
	void onDisconnect(TCPStream *s);
	void onSent(Socket *s, uint16_t len);
	void serialized_writeable(struct lws *wsi);

public:
	TCPStream *ts;

public:
	struct lws *wsi;
	char writeable;
	char awaiting_on_writeable;
};

class lws_conn_listener : lws_conn {
public:
	lws_conn_listener():
		srv(SOCKET_STACK_LWIP_IPV4)
	{
		srv.setOnError(TCPStream::ErrorHandler_t(this,
				&lws_conn_listener::onError));
	}

	void start(const uint16_t port);

protected:
	void onRX(Socket *s);
	void onError(Socket *s, socket_error_t err);
	void onIncoming(TCPListener *s, void *impl);
	void onDisconnect(TCPStream *s);

public:
	TCPListener srv;
};

#endif

extern "C" {
#else
#include <stdarg.h>
#endif

#if _MSC_VER >= 1900
#pragma comment(lib,"legacy_stdio_definitions.lib")

FILE * __cdecl __iob_func(void)
{
	FILE __libwebsocket_std_redef_arr[] = { stdin, stdout, stderr };
	return &(__libwebsocket_std_redef_arr[0]);
}
#endif

#ifdef MBED_OPERATORS
#define LWS_POSIX 0
#else
#define LWS_POSIX 1
#endif

#include "lws_config.h"

#if defined(WIN32) || defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stddef.h>
#include <stdint.h>
#include <basetsd.h>
#include <fcntl.h>

#define strcasecmp stricmp
#define getdtablesize() 30000

#define LWS_INLINE __inline
#define LWS_VISIBLE

#ifdef LWS_DLL
#ifdef LWS_INTERNAL
#define LWS_EXTERN extern __declspec(dllexport)
#else
#define LWS_EXTERN extern __declspec(dllimport)
#endif
#else
#define LWS_EXTERN
#endif

#define LWS_INVALID_FILE INVALID_HANDLE_VALUE
#define LWS_O_RDONLY _O_RDONLY

#else /* NOT WIN32 */
#include <unistd.h>

#define LWS_INLINE inline
#define LWS_O_RDONLY O_RDONLY

#ifndef MBED_OPERATORS
#include <poll.h>
#include <netdb.h>
#define LWS_INVALID_FILE -1
#else
#define getdtablesize() (20)
#define LWS_INVALID_FILE NULL
#endif

#if defined(__GNUC__)
#define LWS_VISIBLE __attribute__((visibility("default")))
#else
#define LWS_VISIBLE
#endif

#if defined(__ANDROID__)
#define getdtablesize() 1024
#endif

#endif

#ifdef LWS_USE_LIBEV
#include <ev.h>
#endif /* LWS_USE_LIBEV */

#ifndef LWS_EXTERN
#define LWS_EXTERN extern
#endif

#ifdef _WIN32
#define random rand
#else
#include <sys/time.h>
#include <unistd.h>
#endif

#ifdef LWS_OPENSSL_SUPPORT
#ifdef USE_WOLFSSL
#ifdef USE_OLD_CYASSL
#include <cyassl/openssl/ssl.h>
#else
#include <wolfssl/openssl/ssl.h>
#endif /* not USE_OLD_CYASSL */
#else
#include <openssl/ssl.h>
#endif /* not USE_WOLFSSL */
#endif

#define CONTEXT_PORT_NO_LISTEN -1

enum lws_log_levels {
	LLL_ERR = 1 << 0,
	LLL_WARN = 1 << 1,
	LLL_NOTICE = 1 << 2,
	LLL_INFO = 1 << 3,
	LLL_DEBUG = 1 << 4,
	LLL_PARSER = 1 << 5,
	LLL_HEADER = 1 << 6,
	LLL_EXT = 1 << 7,
	LLL_CLIENT = 1 << 8,
	LLL_LATENCY = 1 << 9,

	LLL_COUNT = 10 /* set to count of valid flags */
};

LWS_VISIBLE LWS_EXTERN void _lws_log(int filter, const char *format, ...);
LWS_VISIBLE LWS_EXTERN void _lws_logv(int filter, const char *format, va_list vl);

/* notice, warn and log are always compiled in */
#define lwsl_notice(...) _lws_log(LLL_NOTICE, __VA_ARGS__)
#define lwsl_warn(...) _lws_log(LLL_WARN, __VA_ARGS__)
#define lwsl_err(...) _lws_log(LLL_ERR, __VA_ARGS__)
/*
 *  weaker logging can be deselected at configure time using --disable-debug
 *  that gets rid of the overhead of checking while keeping _warn and _err
 *  active
 */
#ifdef _DEBUG

#define lwsl_info(...) _lws_log(LLL_INFO, __VA_ARGS__)
#define lwsl_debug(...) _lws_log(LLL_DEBUG, __VA_ARGS__)
#define lwsl_parser(...) _lws_log(LLL_PARSER, __VA_ARGS__)
#define lwsl_header(...)  _lws_log(LLL_HEADER, __VA_ARGS__)
#define lwsl_ext(...)  _lws_log(LLL_EXT, __VA_ARGS__)
#define lwsl_client(...) _lws_log(LLL_CLIENT, __VA_ARGS__)
#define lwsl_latency(...) _lws_log(LLL_LATENCY, __VA_ARGS__)
LWS_VISIBLE LWS_EXTERN void lwsl_hexdump(void *buf, size_t len);

#else /* no debug */

#define lwsl_info(...) {}
#define lwsl_debug(...) {}
#define lwsl_parser(...) {}
#define lwsl_header(...) {}
#define lwsl_ext(...) {}
#define lwsl_client(...) {}
#define lwsl_latency(...) {}
#define lwsl_hexdump(a, b)

#endif
struct lws;
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

/* api change list for user code to test against */

#define LWS_FEATURE_SERVE_HTTP_FILE_HAS_OTHER_HEADERS_ARG

/* the struct lws_protocols has the id field present */
#define LWS_FEATURE_PROTOCOLS_HAS_ID_FIELD

/* you can call lws_get_peer_write_allowance */
#define LWS_FEATURE_PROTOCOLS_HAS_PEER_WRITE_ALLOWANCE

/* extra parameter introduced in 917f43ab821 */
#define LWS_FEATURE_SERVE_HTTP_FILE_HAS_OTHER_HEADERS_LEN

/* File operations stuff exists */
#define LWS_FEATURE_FOPS

/*
 * NOTE: These public enums are part of the abi.  If you want to add one,
 * add it at where specified so existing users are unaffected.
 */
enum lws_context_options {
	LWS_SERVER_OPTION_REQUIRE_VALID_OPENSSL_CLIENT_CERT	= (1 << 1),
	LWS_SERVER_OPTION_SKIP_SERVER_CANONICAL_NAME		= (1 << 2),
	LWS_SERVER_OPTION_ALLOW_NON_SSL_ON_SSL_PORT		= (1 << 3),
	LWS_SERVER_OPTION_LIBEV					= (1 << 4),
	LWS_SERVER_OPTION_DISABLE_IPV6				= (1 << 5),
	LWS_SERVER_OPTION_DISABLE_OS_CA_CERTS			= (1 << 6),
	LWS_SERVER_OPTION_PEER_CERT_NOT_REQUIRED		= (1 << 7),
	LWS_SERVER_OPTION_VALIDATE_UTF8				= (1 << 8),
	LWS_SERVER_OPTION_SSL_ECDH				= (1 << 9),

	/****** add new things just above ---^ ******/
};

/*
 * NOTE: These public enums are part of the abi.  If you want to add one,
 * add it at where specified so existing users are unaffected.
 */
enum lws_callback_reasons {
	LWS_CALLBACK_ESTABLISHED				=  0,
	LWS_CALLBACK_CLIENT_CONNECTION_ERROR			=  1,
	LWS_CALLBACK_CLIENT_FILTER_PRE_ESTABLISH		=  2,
	LWS_CALLBACK_CLIENT_ESTABLISHED				=  3,
	LWS_CALLBACK_CLOSED					=  4,
	LWS_CALLBACK_CLOSED_HTTP				=  5,
	LWS_CALLBACK_RECEIVE					=  6,
	LWS_CALLBACK_RECEIVE_PONG				=  7,
	LWS_CALLBACK_CLIENT_RECEIVE				=  8,
	LWS_CALLBACK_CLIENT_RECEIVE_PONG			=  9,
	LWS_CALLBACK_CLIENT_WRITEABLE				= 10,
	LWS_CALLBACK_SERVER_WRITEABLE				= 11,
	LWS_CALLBACK_HTTP					= 12,
	LWS_CALLBACK_HTTP_BODY					= 13,
	LWS_CALLBACK_HTTP_BODY_COMPLETION			= 14,
	LWS_CALLBACK_HTTP_FILE_COMPLETION			= 15,
	LWS_CALLBACK_HTTP_WRITEABLE				= 16,
	LWS_CALLBACK_FILTER_NETWORK_CONNECTION			= 17,
	LWS_CALLBACK_FILTER_HTTP_CONNECTION			= 18,
	LWS_CALLBACK_SERVER_NEW_CLIENT_INSTANTIATED		= 19,
	LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION			= 20,
	LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS	= 21,
	LWS_CALLBACK_OPENSSL_LOAD_EXTRA_SERVER_VERIFY_CERTS	= 22,
	LWS_CALLBACK_OPENSSL_PERFORM_CLIENT_CERT_VERIFICATION	= 23,
	LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER		= 24,
	LWS_CALLBACK_CONFIRM_EXTENSION_OKAY			= 25,
	LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED		= 26,
	LWS_CALLBACK_PROTOCOL_INIT				= 27,
	LWS_CALLBACK_PROTOCOL_DESTROY				= 28,
	LWS_CALLBACK_WSI_CREATE /* always protocol[0] */	= 29,
	LWS_CALLBACK_WSI_DESTROY /* always protocol[0] */	= 30,
	LWS_CALLBACK_GET_THREAD_ID				= 31,

	/* external poll() management support */
	LWS_CALLBACK_ADD_POLL_FD				= 32,
	LWS_CALLBACK_DEL_POLL_FD				= 33,
	LWS_CALLBACK_CHANGE_MODE_POLL_FD			= 34,
	LWS_CALLBACK_LOCK_POLL					= 35,
	LWS_CALLBACK_UNLOCK_POLL				= 36,

	LWS_CALLBACK_OPENSSL_CONTEXT_REQUIRES_PRIVATE_KEY	= 37,
	LWS_CALLBACK_WS_PEER_INITIATED_CLOSE			= 38,

	LWS_CALLBACK_WS_EXT_DEFAULTS				= 39,

	/****** add new things just above ---^ ******/

	LWS_CALLBACK_USER = 1000, /* user code can use any including / above */
};


#if defined(_WIN32)
typedef SOCKET lws_sockfd_type;
typedef HANDLE lws_filefd_type;
#define lws_sockfd_valid(sfd) (!!sfd)
struct lws_pollfd {
	lws_sockfd_type fd;
	SHORT events;
	SHORT revents;
};
#else

#if defined(MBED_OPERATORS)
/* it's a class lws_conn * */
typedef void * lws_sockfd_type;
typedef void * lws_filefd_type;
#define lws_sockfd_valid(sfd) (!!sfd)
struct pollfd {
	lws_sockfd_type fd;
	short events;
	short revents;
};
#define POLLIN		0x0001
#define POLLPRI		0x0002
#define POLLOUT		0x0004
#define POLLERR		0x0008
#define POLLHUP		0x0010
#define POLLNVAL	0x0020

struct lws;

void * mbed3_create_tcp_stream_socket(void);
void mbed3_delete_tcp_stream_socket(void *sockfd);
void mbed3_tcp_stream_bind(void *sock, int port, struct lws *);
void mbed3_tcp_stream_accept(void *sock, struct lws *);
#else
typedef int lws_sockfd_type;
typedef int lws_filefd_type;
#define lws_sockfd_valid(sfd) (sfd >= 0)
#endif

#define lws_pollfd pollfd
#endif

/* argument structure for all external poll related calls
 * passed in via 'in'
 */
struct lws_pollargs {
	lws_sockfd_type fd;		/* applicable socket descriptor */
	int events;			/* the new event mask */
	int prev_events;		/* the previous event mask */
};

/**
 * struct lws_plat_file_ops - Platform-specific file operations
 *
 * These provide platform-agnostic ways to deal with filesystem access in the
 * library and in the user code.
 *
 * @open:		Open file (always binary access if plat supports it)
 *			 filelen is filled on exit to be the length of the file
 *			 flags should be set to O_RDONLY or O_RDWR
 * @close:		Close file
 * @seek_cur:		Seek from current position
 * @read:		Read fron file *amount is set on exit to amount read
 * @write:		Write to file *amount is set on exit as amount written
 */
struct lws_plat_file_ops {
	lws_filefd_type (*open)(struct lws *wsi, const char *filename,
				unsigned long *filelen, int flags);
	int (*close)(struct lws *wsi, lws_filefd_type fd);
	unsigned long (*seek_cur)(struct lws *wsi, lws_filefd_type fd,
				  long offset_from_cur_pos);
	int (*read)(struct lws *wsi, lws_filefd_type fd, unsigned long *amount,
		    unsigned char *buf, unsigned long len);
	int (*write)(struct lws *wsi, lws_filefd_type fd, unsigned long *amount,
		     unsigned char *buf, unsigned long len);

	/* Add new things just above here ---^
	 * This is part of the ABI, don't needlessly break compatibilty */
};

/*
 * NOTE: These public enums are part of the abi.  If you want to add one,
 * add it at where specified so existing users are unaffected.
 */
enum lws_extension_callback_reasons {
	LWS_EXT_CB_SERVER_CONTEXT_CONSTRUCT		=  0,
	LWS_EXT_CB_CLIENT_CONTEXT_CONSTRUCT		=  1,
	LWS_EXT_CB_SERVER_CONTEXT_DESTRUCT		=  2,
	LWS_EXT_CB_CLIENT_CONTEXT_DESTRUCT		=  3,
	LWS_EXT_CB_CONSTRUCT				=  4,
	LWS_EXT_CB_CLIENT_CONSTRUCT			=  5,
	LWS_EXT_CB_CHECK_OK_TO_REALLY_CLOSE		=  6,
	LWS_EXT_CB_CHECK_OK_TO_PROPOSE_EXTENSION		=  7,
	LWS_EXT_CB_DESTROY				=  8,
	LWS_EXT_CB_DESTROY_ANY_WSI_CLOSING		=  9,
	LWS_EXT_CB_ANY_WSI_ESTABLISHED			= 10,
	LWS_EXT_CB_PACKET_RX_PREPARSE			= 11,
	LWS_EXT_CB_PACKET_TX_PRESEND			= 12,
	LWS_EXT_CB_PACKET_TX_DO_SEND			= 13,
	LWS_EXT_CB_HANDSHAKE_REPLY_TX			= 14,
	LWS_EXT_CB_FLUSH_PENDING_TX			= 15,
	LWS_EXT_CB_EXTENDED_PAYLOAD_RX			= 16,
	LWS_EXT_CB_CAN_PROXY_CLIENT_CONNECTION		= 17,
	LWS_EXT_CB_1HZ					= 18,
	LWS_EXT_CB_REQUEST_ON_WRITEABLE			= 19,
	LWS_EXT_CB_IS_WRITEABLE				= 20,
	LWS_EXT_CB_PAYLOAD_TX				= 21,
	LWS_EXT_CB_PAYLOAD_RX				= 22,
	LWS_EXT_CB_OPTION_DEFAULT			= 23,
	LWS_EXT_CB_OPTION_SET				= 24,
	LWS_EXT_CB_OPTION_CONFIRM			= 25,

	/****** add new things just above ---^ ******/
};

/*
 * NOTE: These public enums are part of the abi.  If you want to add one,
 * add it at where specified so existing users are unaffected.
 */
enum lws_write_protocol {
	LWS_WRITE_TEXT						= 0,
	LWS_WRITE_BINARY					= 1,
	LWS_WRITE_CONTINUATION					= 2,
	LWS_WRITE_HTTP						= 3,

	/* special 04+ opcodes */

	/* LWS_WRITE_CLOSE is handled by lws_close_reason() */
	LWS_WRITE_PING						= 5,
	LWS_WRITE_PONG						= 6,

	/* Same as write_http but we know this write ends the transaction */
	LWS_WRITE_HTTP_FINAL					= 7,

	/* HTTP2 */

	LWS_WRITE_HTTP_HEADERS					= 8,

	/****** add new things just above ---^ ******/

	/* flags */

	LWS_WRITE_NO_FIN = 0x40,
	/*
	 * client packet payload goes out on wire unmunged
	 * only useful for security tests since normal servers cannot
	 * decode the content if used
	 */
	LWS_WRITE_CLIENT_IGNORE_XOR_MASK = 0x80
};

/*
 * you need these to look at headers that have been parsed if using the
 * LWS_CALLBACK_FILTER_CONNECTION callback.  If a header from the enum
 * list below is absent, .token = NULL and token_len = 0.  Otherwise .token
 * points to .token_len chars containing that header content.
 */

struct lws_tokens {
	char *token;
	int token_len;
};

/*
 * don't forget to update test server header dump accordingly
 *
 * these have to be kept in sync with lextable.h / minilex.c
 *
 * NOTE: These public enums are part of the abi.  If you want to add one,
 * add it at where specified so existing users are unaffected.
 */
enum lws_token_indexes {
	WSI_TOKEN_GET_URI					=  0,
	WSI_TOKEN_POST_URI					=  1,
	WSI_TOKEN_OPTIONS_URI					=  2,
	WSI_TOKEN_HOST						=  3,
	WSI_TOKEN_CONNECTION					=  4,
	WSI_TOKEN_UPGRADE					=  5,
	WSI_TOKEN_ORIGIN					=  6,
	WSI_TOKEN_DRAFT						=  7,
	WSI_TOKEN_CHALLENGE					=  8,
	WSI_TOKEN_EXTENSIONS					=  9,
	WSI_TOKEN_KEY1						= 10,
	WSI_TOKEN_KEY2						= 11,
	WSI_TOKEN_PROTOCOL					= 12,
	WSI_TOKEN_ACCEPT					= 13,
	WSI_TOKEN_NONCE						= 14,
	WSI_TOKEN_HTTP						= 15,
	WSI_TOKEN_HTTP2_SETTINGS				= 16,
	WSI_TOKEN_HTTP_ACCEPT					= 17,
	WSI_TOKEN_HTTP_AC_REQUEST_HEADERS			= 18,
	WSI_TOKEN_HTTP_IF_MODIFIED_SINCE			= 19,
	WSI_TOKEN_HTTP_IF_NONE_MATCH				= 20,
	WSI_TOKEN_HTTP_ACCEPT_ENCODING				= 21,
	WSI_TOKEN_HTTP_ACCEPT_LANGUAGE				= 22,
	WSI_TOKEN_HTTP_PRAGMA					= 23,
	WSI_TOKEN_HTTP_CACHE_CONTROL				= 24,
	WSI_TOKEN_HTTP_AUTHORIZATION				= 25,
	WSI_TOKEN_HTTP_COOKIE					= 26,
	WSI_TOKEN_HTTP_CONTENT_LENGTH				= 27,
	WSI_TOKEN_HTTP_CONTENT_TYPE				= 28,
	WSI_TOKEN_HTTP_DATE					= 29,
	WSI_TOKEN_HTTP_RANGE					= 30,
	WSI_TOKEN_HTTP_REFERER					= 31,
	WSI_TOKEN_KEY						= 32,
	WSI_TOKEN_VERSION					= 33,
	WSI_TOKEN_SWORIGIN					= 34,

	WSI_TOKEN_HTTP_COLON_AUTHORITY				= 35,
	WSI_TOKEN_HTTP_COLON_METHOD				= 36,
	WSI_TOKEN_HTTP_COLON_PATH				= 37,
	WSI_TOKEN_HTTP_COLON_SCHEME				= 38,
	WSI_TOKEN_HTTP_COLON_STATUS				= 39,

	WSI_TOKEN_HTTP_ACCEPT_CHARSET				= 40,
	WSI_TOKEN_HTTP_ACCEPT_RANGES				= 41,
	WSI_TOKEN_HTTP_ACCESS_CONTROL_ALLOW_ORIGIN		= 42,
	WSI_TOKEN_HTTP_AGE					= 43,
	WSI_TOKEN_HTTP_ALLOW					= 44,
	WSI_TOKEN_HTTP_CONTENT_DISPOSITION			= 45,
	WSI_TOKEN_HTTP_CONTENT_ENCODING				= 46,
	WSI_TOKEN_HTTP_CONTENT_LANGUAGE				= 47,
	WSI_TOKEN_HTTP_CONTENT_LOCATION				= 48,
	WSI_TOKEN_HTTP_CONTENT_RANGE				= 49,
	WSI_TOKEN_HTTP_ETAG					= 50,
	WSI_TOKEN_HTTP_EXPECT					= 51,
	WSI_TOKEN_HTTP_EXPIRES					= 52,
	WSI_TOKEN_HTTP_FROM					= 53,
	WSI_TOKEN_HTTP_IF_MATCH					= 54,
	WSI_TOKEN_HTTP_IF_RANGE					= 55,
	WSI_TOKEN_HTTP_IF_UNMODIFIED_SINCE			= 56,
	WSI_TOKEN_HTTP_LAST_MODIFIED				= 57,
	WSI_TOKEN_HTTP_LINK					= 58,
	WSI_TOKEN_HTTP_LOCATION					= 59,
	WSI_TOKEN_HTTP_MAX_FORWARDS				= 60,
	WSI_TOKEN_HTTP_PROXY_AUTHENTICATE			= 61,
	WSI_TOKEN_HTTP_PROXY_AUTHORIZATION			= 62,
	WSI_TOKEN_HTTP_REFRESH					= 63,
	WSI_TOKEN_HTTP_RETRY_AFTER				= 64,
	WSI_TOKEN_HTTP_SERVER					= 65,
	WSI_TOKEN_HTTP_SET_COOKIE				= 66,
	WSI_TOKEN_HTTP_STRICT_TRANSPORT_SECURITY		= 67,
	WSI_TOKEN_HTTP_TRANSFER_ENCODING			= 68,
	WSI_TOKEN_HTTP_USER_AGENT				= 69,
	WSI_TOKEN_HTTP_VARY					= 70,
	WSI_TOKEN_HTTP_VIA					= 71,
	WSI_TOKEN_HTTP_WWW_AUTHENTICATE				= 72,
	WSI_TOKEN_PROXY,

	WSI_TOKEN_PATCH_URI					= 73,
	WSI_TOKEN_PUT_URI					= 74,
	WSI_TOKEN_DELETE_URI					= 75,

	WSI_TOKEN_HTTP_URI_ARGS					= 76,

	/* use token storage to stash these */

	_WSI_TOKEN_CLIENT_SENT_PROTOCOLS			= 77,
	_WSI_TOKEN_CLIENT_PEER_ADDRESS				= 78,
	_WSI_TOKEN_CLIENT_URI					= 79,
	_WSI_TOKEN_CLIENT_HOST					= 80,
	_WSI_TOKEN_CLIENT_ORIGIN				= 81,

	/****** add new things just above ---^ ******/

	/* always last real token index*/
	WSI_TOKEN_COUNT,

	/* parser state additions */
	WSI_TOKEN_NAME_PART,
	WSI_TOKEN_SKIPPING,
	WSI_TOKEN_SKIPPING_SAW_CR,
	WSI_PARSING_COMPLETE,
	WSI_INIT_TOKEN_MUXURL,
};

struct lws_token_limits {
	unsigned short token_limit[WSI_TOKEN_COUNT];
};

/*
 * From RFC 6455
   1000

      1000 indicates a normal closure, meaning that the purpose for
      which the connection was established has been fulfilled.

   1001

      1001 indicates that an endpoint is "going away", such as a server
      going down or a browser having navigated away from a page.

   1002

      1002 indicates that an endpoint is terminating the connection due
      to a protocol error.

   1003

      1003 indicates that an endpoint is terminating the connection
      because it has received a type of data it cannot accept (e.g., an
      endpoint that understands only text data MAY send this if it
      receives a binary message).

   1004

      Reserved.  The specific meaning might be defined in the future.

   1005

      1005 is a reserved value and MUST NOT be set as a status code in a
      Close control frame by an endpoint.  It is designated for use in
      applications expecting a status code to indicate that no status
      code was actually present.

   1006

      1006 is a reserved value and MUST NOT be set as a status code in a
      Close control frame by an endpoint.  It is designated for use in
      applications expecting a status code to indicate that the
      connection was closed abnormally, e.g., without sending or
      receiving a Close control frame.

   1007

      1007 indicates that an endpoint is terminating the connection
      because it has received data within a message that was not
      consistent with the type of the message (e.g., non-UTF-8 [RFC3629]
      data within a text message).

   1008

      1008 indicates that an endpoint is terminating the connection
      because it has received a message that violates its policy.  This
      is a generic status code that can be returned when there is no
      other more suitable status code (e.g., 1003 or 1009) or if there
      is a need to hide specific details about the policy.

   1009

      1009 indicates that an endpoint is terminating the connection
      because it has received a message that is too big for it to
      process.

   1010

      1010 indicates that an endpoint (client) is terminating the
      connection because it has expected the server to negotiate one or
      more extension, but the server didn't return them in the response
      message of the WebSocket handshake.  The list of extensions that
      are needed SHOULD appear in the /reason/ part of the Close frame.
      Note that this status code is not used by the server, because it
      can fail the WebSocket handshake instead.

   1011

      1011 indicates that a server is terminating the connection because
      it encountered an unexpected condition that prevented it from
      fulfilling the request.

   1015

      1015 is a reserved value and MUST NOT be set as a status code in a
      Close control frame by an endpoint.  It is designated for use in
      applications expecting a status code to indicate that the
      connection was closed due to a failure to perform a TLS handshake
      (e.g., the server certificate can't be verified).
*/

/*
 * NOTE: These public enums are part of the abi.  If you want to add one,
 * add it at where specified so existing users are unaffected.
 */
enum lws_close_status {
	LWS_CLOSE_STATUS_NOSTATUS				=    0,
	LWS_CLOSE_STATUS_NORMAL					= 1000,
	LWS_CLOSE_STATUS_GOINGAWAY				= 1001,
	LWS_CLOSE_STATUS_PROTOCOL_ERR				= 1002,
	LWS_CLOSE_STATUS_UNACCEPTABLE_OPCODE			= 1003,
	LWS_CLOSE_STATUS_RESERVED				= 1004,
	LWS_CLOSE_STATUS_NO_STATUS				= 1005,
	LWS_CLOSE_STATUS_ABNORMAL_CLOSE				= 1006,
	LWS_CLOSE_STATUS_INVALID_PAYLOAD			= 1007,
	LWS_CLOSE_STATUS_POLICY_VIOLATION			= 1008,
	LWS_CLOSE_STATUS_MESSAGE_TOO_LARGE			= 1009,
	LWS_CLOSE_STATUS_EXTENSION_REQUIRED			= 1010,
	LWS_CLOSE_STATUS_UNEXPECTED_CONDITION			= 1011,
	LWS_CLOSE_STATUS_TLS_FAILURE				= 1015,

	/****** add new things just above ---^ ******/

	LWS_CLOSE_STATUS_NOSTATUS_CONTEXT_DESTROY		= 9999,
};

enum http_status {
	HTTP_STATUS_OK						= 200,
	HTTP_STATUS_NO_CONTENT					= 204,

	HTTP_STATUS_BAD_REQUEST					= 400,
	HTTP_STATUS_UNAUTHORIZED,
	HTTP_STATUS_PAYMENT_REQUIRED,
	HTTP_STATUS_FORBIDDEN,
	HTTP_STATUS_NOT_FOUND,
	HTTP_STATUS_METHOD_NOT_ALLOWED,
	HTTP_STATUS_NOT_ACCEPTABLE,
	HTTP_STATUS_PROXY_AUTH_REQUIRED,
	HTTP_STATUS_REQUEST_TIMEOUT,
	HTTP_STATUS_CONFLICT,
	HTTP_STATUS_GONE,
	HTTP_STATUS_LENGTH_REQUIRED,
	HTTP_STATUS_PRECONDITION_FAILED,
	HTTP_STATUS_REQ_ENTITY_TOO_LARGE,
	HTTP_STATUS_REQ_URI_TOO_LONG,
	HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE,
	HTTP_STATUS_REQ_RANGE_NOT_SATISFIABLE,
	HTTP_STATUS_EXPECTATION_FAILED,

	HTTP_STATUS_INTERNAL_SERVER_ERROR			= 500,
	HTTP_STATUS_NOT_IMPLEMENTED,
	HTTP_STATUS_BAD_GATEWAY,
	HTTP_STATUS_SERVICE_UNAVAILABLE,
	HTTP_STATUS_GATEWAY_TIMEOUT,
	HTTP_STATUS_HTTP_VERSION_NOT_SUPPORTED,
};

struct lws;
struct lws_context;
/* needed even with extensions disabled for create context */
struct lws_extension;

/**
 * typedef lws_callback_function() - User server actions
 * @wsi:	Opaque websocket instance pointer
 * @reason:	The reason for the call
 * @user:	Pointer to per-session user data allocated by library
 * @in:		Pointer used for some callback reasons
 * @len:	Length set for some callback reasons
 *
 *	This callback is the way the user controls what is served.  All the
 *	protocol detail is hidden and handled by the library.
 *
 *	For each connection / session there is user data allocated that is
 *	pointed to by "user".  You set the size of this user data area when
 *	the library is initialized with lws_create_server.
 *
 *	You get an opportunity to initialize user data when called back with
 *	LWS_CALLBACK_ESTABLISHED reason.
 *
 *  LWS_CALLBACK_ESTABLISHED:  after the server completes a handshake with
 *				an incoming client.  If you built the library
 *				with ssl support, @in is a pointer to the
 *				ssl struct associated with the connection or
 *				NULL.
 *
 *  LWS_CALLBACK_CLIENT_CONNECTION_ERROR: the request client connection has
 *        been unable to complete a handshake with the remote server.  If
 *	  in is non-NULL, you can find an error string of length len where
 *	  it points to.
 *
 *  LWS_CALLBACK_CLIENT_FILTER_PRE_ESTABLISH: this is the last chance for the
 *				client user code to examine the http headers
 *				and decide to reject the connection.  If the
 *				content in the headers is interesting to the
 *				client (url, etc) it needs to copy it out at
 *				this point since it will be destroyed before
 *				the CLIENT_ESTABLISHED call
 *
 *  LWS_CALLBACK_CLIENT_ESTABLISHED: after your client connection completed
 *				a handshake with the remote server
 *
 *	LWS_CALLBACK_CLOSED: when the websocket session ends
 *
 *	LWS_CALLBACK_CLOSED_HTTP: when a HTTP (non-websocket) session ends
 *
 *	LWS_CALLBACK_RECEIVE: data has appeared for this server endpoint from a
 *				remote client, it can be found at *in and is
 *				len bytes long
 *
 *	LWS_CALLBACK_CLIENT_RECEIVE_PONG: if you elected to see PONG packets,
 *				they appear with this callback reason.  PONG
 *				packets only exist in 04+ protocol
 *
 *	LWS_CALLBACK_CLIENT_RECEIVE: data has appeared from the server for the
 *				client connection, it can be found at *in and
 *				is len bytes long
 *
 *	LWS_CALLBACK_HTTP: an http request has come from a client that is not
 *				asking to upgrade the connection to a websocket
 *				one.  This is a chance to serve http content,
 *				for example, to send a script to the client
 *				which will then open the websockets connection.
 *				@in points to the URI path requested and
 *				lws_serve_http_file() makes it very
 *				simple to send back a file to the client.
 *				Normally after sending the file you are done
 *				with the http connection, since the rest of the
 *				activity will come by websockets from the script
 *				that was delivered by http, so you will want to
 *				return 1; to close and free up the connection.
 *				That's important because it uses a slot in the
 *				total number of client connections allowed set
 *				by MAX_CLIENTS.
 *
 *	LWS_CALLBACK_HTTP_BODY: the next @len bytes data from the http
 *		request body HTTP connection is now available in @in.
 *
 *	LWS_CALLBACK_HTTP_BODY_COMPLETION: the expected amount of http request
 *		body has been delivered
 *
 *	LWS_CALLBACK_HTTP_WRITEABLE: you can write more down the http protocol
 *		link now.
 *
 *	LWS_CALLBACK_HTTP_FILE_COMPLETION: a file requested to be send down
 *				http link has completed.
 *
 *	LWS_CALLBACK_CLIENT_WRITEABLE:
 *      LWS_CALLBACK_SERVER_WRITEABLE:   If you call
 *		lws_callback_on_writable() on a connection, you will
 *		get one of these callbacks coming when the connection socket
 *		is able to accept another write packet without blocking.
 *		If it already was able to take another packet without blocking,
 *		you'll get this callback at the next call to the service loop
 *		function.  Notice that CLIENTs get LWS_CALLBACK_CLIENT_WRITEABLE
 *		and servers get LWS_CALLBACK_SERVER_WRITEABLE.
 *
 *	LWS_CALLBACK_FILTER_NETWORK_CONNECTION: called when a client connects to
 *		the server at network level; the connection is accepted but then
 *		passed to this callback to decide whether to hang up immediately
 *		or not, based on the client IP.  @in contains the connection
 *		socket's descriptor. Since the client connection information is
 *		not available yet, @wsi still pointing to the main server socket.
 *		Return non-zero to terminate the connection before sending or
 *		receiving anything. Because this happens immediately after the
 *		network connection from the client, there's no websocket protocol
 *		selected yet so this callback is issued only to protocol 0.
 *
 *	LWS_CALLBACK_SERVER_NEW_CLIENT_INSTANTIATED: A new client just had
 *		been connected, accepted, and instantiated into the pool. This
 *		callback allows setting any relevant property to it. Because this
 *		happens immediately after the instantiation of a new client,
 *		there's no websocket protocol selected yet so this callback is
 *		issued only to protocol 0. Only @wsi is defined, pointing to the
 *		new client, and the return value is ignored.
 *
 *	LWS_CALLBACK_FILTER_HTTP_CONNECTION: called when the request has
 *		been received and parsed from the client, but the response is
 *		not sent yet.  Return non-zero to disallow the connection.
 *		@user is a pointer to the connection user space allocation,
 *		@in is the URI, eg, "/"
 *		In your handler you can use the public APIs
 *		lws_hdr_total_length() / lws_hdr_copy() to access all of the
 *		headers using the header enums lws_token_indexes from
 *		libwebsockets.h to check for and read the supported header
 *		presence and content before deciding to allow the http
 *		connection to proceed or to kill the connection.
 *
 *	LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION: called when the handshake has
 *		been received and parsed from the client, but the response is
 *		not sent yet.  Return non-zero to disallow the connection.
 *		@user is a pointer to the connection user space allocation,
 *		@in is the requested protocol name
 *		In your handler you can use the public APIs
 *		lws_hdr_total_length() / lws_hdr_copy() to access all of the
 *		headers using the header enums lws_token_indexes from
 *		libwebsockets.h to check for and read the supported header
 *		presence and content before deciding to allow the handshake
 *		to proceed or to kill the connection.
 *
 *	LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS: if configured for
 *		including OpenSSL support, this callback allows your user code
 *		to perform extra SSL_CTX_load_verify_locations() or similar
 *		calls to direct OpenSSL where to find certificates the client
 *		can use to confirm the remote server identity.  @user is the
 *		OpenSSL SSL_CTX*
 *
 *	LWS_CALLBACK_OPENSSL_LOAD_EXTRA_SERVER_VERIFY_CERTS: if configured for
 *		including OpenSSL support, this callback allows your user code
 *		to load extra certifcates into the server which allow it to
 *		verify the validity of certificates returned by clients.  @user
 *		is the server's OpenSSL SSL_CTX*
 *
 *	LWS_CALLBACK_OPENSSL_CONTEXT_REQUIRES_PRIVATE_KEY: if configured for
 *		including OpenSSL support but no private key file has been
 *		specified (ssl_private_key_filepath is NULL), this is called to
 *		allow the user to set the private key directly via libopenssl
 *		and perform further operations if required; this might be useful
 *		in situations where the private key is not directly accessible
 *		by the OS, for example if it is stored on a smartcard
 *		@user is the server's OpenSSL SSL_CTX*
 *
 *	LWS_CALLBACK_OPENSSL_PERFORM_CLIENT_CERT_VERIFICATION: if the
 *		libwebsockets context was created with the option
 *		LWS_SERVER_OPTION_REQUIRE_VALID_OPENSSL_CLIENT_CERT, then this
 *		callback is generated during OpenSSL verification of the cert
 *		sent from the client.  It is sent to protocol[0] callback as
 *		no protocol has been negotiated on the connection yet.
 *		Notice that the libwebsockets context and wsi are both NULL
 *		during this callback.  See
 *		 http://www.openssl.org/docs/ssl/SSL_CTX_set_verify.html
 *		to understand more detail about the OpenSSL callback that
 *		generates this libwebsockets callback and the meanings of the
 *		arguments passed.  In this callback, @user is the x509_ctx,
 *		@in is the ssl pointer and @len is preverify_ok
 *		Notice that this callback maintains libwebsocket return
 *		conventions, return 0 to mean the cert is OK or 1 to fail it.
 *		This also means that if you don't handle this callback then
 *		the default callback action of returning 0 allows the client
 *		certificates.
 *
 *	LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER: this callback happens
 *		when a client handshake is being compiled.  @user is NULL,
 *		@in is a char **, it's pointing to a char * which holds the
 *		next location in the header buffer where you can add
 *		headers, and @len is the remaining space in the header buffer,
 *		which is typically some hundreds of bytes.  So, to add a canned
 *		cookie, your handler code might look similar to:
 *
 *		char **p = (char **)in;
 *
 *		if (len < 100)
 *			return 1;
 *
 *		*p += sprintf(*p, "Cookie: a=b\x0d\x0a");
 *
 *		return 0;
 *
 *		Notice if you add anything, you just have to take care about
 *		the CRLF on the line you added.  Obviously this callback is
 *		optional, if you don't handle it everything is fine.
 *
 *		Notice the callback is coming to protocols[0] all the time,
 *		because there is no specific protocol handshook yet.
 *
 *	LWS_CALLBACK_CONFIRM_EXTENSION_OKAY: When the server handshake code
 *		sees that it does support a requested extension, before
 *		accepting the extension by additing to the list sent back to
 *		the client it gives this callback just to check that it's okay
 *		to use that extension.  It calls back to the requested protocol
 *		and with @in being the extension name, @len is 0 and @user is
 *		valid.  Note though at this time the ESTABLISHED callback hasn't
 *		happened yet so if you initialize @user content there, @user
 *		content during this callback might not be useful for anything.
 *		Notice this callback comes to protocols[0].
 *
 *	LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED:	When a client
 *		connection is being prepared to start a handshake to a server,
 *		each supported extension is checked with protocols[0] callback
 *		with this reason, giving the user code a chance to suppress the
 *		claim to support that extension by returning non-zero.  If
 *		unhandled, by default 0 will be returned and the extension
 *		support included in the header to the server.  Notice this
 *		callback comes to protocols[0].
 *
 *	LWS_CALLBACK_PROTOCOL_INIT:	One-time call per protocol so it can
 *		do initial setup / allocations etc
 *
 *	LWS_CALLBACK_PROTOCOL_DESTROY:	One-time call per protocol indicating
 *		this protocol won't get used at all after this callback, the
 *		context is getting destroyed.  Take the opportunity to
 *		deallocate everything that was allocated by the protocol.
 *
 *	LWS_CALLBACK_WSI_CREATE: outermost (earliest) wsi create notification
 *
 *	LWS_CALLBACK_WSI_DESTROY: outermost (latest) wsi destroy notification
 *
 *	The next five reasons are optional and only need taking care of if you
 *	will be integrating libwebsockets sockets into an external polling
 *	array.
 *
 *	For these calls, @in points to a struct lws_pollargs that
 *	contains @fd, @events and @prev_events members
 *
 *	LWS_CALLBACK_ADD_POLL_FD: libwebsocket deals with its poll() loop
 *		internally, but in the case you are integrating with another
 *		server you will need to have libwebsocket sockets share a
 *		polling array with the other server.  This and the other
 *		POLL_FD related callbacks let you put your specialized
 *		poll array interface code in the callback for protocol 0, the
 *		first protocol you support, usually the HTTP protocol in the
 *		serving case.
 *		This callback happens when a socket needs to be
 *		added to the polling loop: @in points to a struct
 *		lws_pollargs; the @fd member of the struct is the file
 *		descriptor, and @events contains the active events.
 *
 *		If you are using the internal polling loop (the "service"
 *		callback), you can just ignore these callbacks.
 *
 *	LWS_CALLBACK_DEL_POLL_FD: This callback happens when a socket descriptor
 *		needs to be removed from an external polling array.  @in is
 *		again the struct lws_pollargs containing the @fd member
 *		to be removed.  If you are using the internal polling
 *		loop, you can just ignore it.
 *
 *	LWS_CALLBACK_CHANGE_MODE_POLL_FD: This callback happens when
 *		libwebsockets wants to modify the events for a connectiion.
 *		@in is the struct lws_pollargs with the @fd to change.
 *		The new event mask is in @events member and the old mask is in
 *		the @prev_events member.
 *		If you are using the internal polling loop, you can just ignore
 *		it.
 *
 *	LWS_CALLBACK_LOCK_POLL:
 *	LWS_CALLBACK_UNLOCK_POLL: These allow the external poll changes driven
 *		by libwebsockets to participate in an external thread locking
 *		scheme around the changes, so the whole thing is threadsafe.
 *		These are called around three activities in the library,
 *			- inserting a new wsi in the wsi / fd table (len=1)
 *			- deleting a wsi from the wsi / fd table (len=1)
 *			- changing a wsi's POLLIN/OUT state (len=0)
 *		Locking and unlocking external synchronization objects when
 *		len == 1 allows external threads to be synchronized against
 *		wsi lifecycle changes if it acquires the same lock for the
 *		duration of wsi dereference from the other thread context.
 *
 *	LWS_CALLBACK_WS_PEER_INITIATED_CLOSE:
 *		The peer has sent an unsolicited Close WS packet.  @in and
 *		@len are the optional close code (first 2 bytes, network
 *		order) and the optional additional information which is not
 *		defined in the standard, and may be a string or non-human-
 *		readble data.
 *		If you return 0 lws will echo the close and then close the
 *		connection.  If you return nonzero lws will just close the
 *		connection.
 */
typedef int
lws_callback_function(struct lws *wsi, enum lws_callback_reasons reason,
		    void *user, void *in, size_t len);

/**
 * typedef lws_extension_callback_function() - Hooks to allow extensions to operate
 * @context:	Websockets context
 * @ext:	This extension
 * @wsi:	Opaque websocket instance pointer
 * @reason:	The reason for the call
 * @user:	Pointer to ptr to per-session user data allocated by library
 * @in:		Pointer used for some callback reasons
 * @len:	Length set for some callback reasons
 *
 *	Each extension that is active on a particular connection receives
 *	callbacks during the connection lifetime to allow the extension to
 *	operate on websocket data and manage itself.
 *
 *	Libwebsockets takes care of allocating and freeing "user" memory for
 *	each active extension on each connection.  That is what is pointed to
 *	by the @user parameter.
 *
 *	LWS_EXT_CB_CONSTRUCT:  called when the server has decided to
 *		select this extension from the list provided by the client,
 *		just before the server will send back the handshake accepting
 *		the connection with this extension active.  This gives the
 *		extension a chance to initialize its connection context found
 *		in @user.
 *
 *	LWS_EXT_CB_CLIENT_CONSTRUCT: same as LWS_EXT_CB_CONSTRUCT
 *		but called when client is instantiating this extension.  Some
 *		extensions will work the same on client and server side and then
 *		you can just merge handlers for both CONSTRUCTS.
 *
 *	LWS_EXT_CB_DESTROY:  called when the connection the extension was
 *		being used on is about to be closed and deallocated.  It's the
 *		last chance for the extension to deallocate anything it has
 *		allocated in the user data (pointed to by @user) before the
 *		user data is deleted.  This same callback is used whether you
 *		are in client or server instantiation context.
 *
 *	LWS_EXT_CB_PACKET_RX_PREPARSE: when this extension was active on
 *		a connection, and a packet of data arrived at the connection,
 *		it is passed to this callback to give the extension a chance to
 *		change the data, eg, decompress it.  @user is pointing to the
 *		extension's private connection context data, @in is pointing
 *		to an lws_tokens struct, it consists of a char * pointer called
 *		token, and an int called token_len.  At entry, these are
 *		set to point to the received buffer and set to the content
 *		length.  If the extension will grow the content, it should use
 *		a new buffer allocated in its private user context data and
 *		set the pointed-to lws_tokens members to point to its buffer.
 *
 *	LWS_EXT_CB_PACKET_TX_PRESEND: this works the same way as
 *		LWS_EXT_CB_PACKET_RX_PREPARSE above, except it gives the
 *		extension a chance to change websocket data just before it will
 *		be sent out.  Using the same lws_token pointer scheme in @in,
 *		the extension can change the buffer and the length to be
 *		transmitted how it likes.  Again if it wants to grow the
 *		buffer safely, it should copy the data into its own buffer and
 *		set the lws_tokens token pointer to it.
 *
 *	LWS_EXT_CB_ARGS_VALIDATE:
 */
typedef int
lws_extension_callback_function(struct lws_context *context,
			      const struct lws_extension *ext, struct lws *wsi,
			      enum lws_extension_callback_reasons reason,
			      void *user, void *in, size_t len);

/**
 * struct lws_protocols -	List of protocols and handlers server
 *					supports.
 * @name:	Protocol name that must match the one given in the client
 *		Javascript new WebSocket(url, 'protocol') name.
 * @callback:	The service callback used for this protocol.  It allows the
 *		service action for an entire protocol to be encapsulated in
 *		the protocol-specific callback
 * @per_session_data_size:	Each new connection using this protocol gets
 *		this much memory allocated on connection establishment and
 *		freed on connection takedown.  A pointer to this per-connection
 *		allocation is passed into the callback in the 'user' parameter
 * @rx_buffer_size: if you want atomic frames delivered to the callback, you
 *		should set this to the size of the biggest legal frame that
 *		you support.  If the frame size is exceeded, there is no
 *		error, but the buffer will spill to the user callback when
 *		full, which you can detect by using
 *		lws_remaining_packet_payload().  Notice that you
 *		just talk about frame size here, the LWS_PRE
 *		and post-padding are automatically also allocated on top.
 * @id:		ignored by lws, but useful to contain user information bound
 *		to the selected protocol.  For example if this protocol was
 *		called "myprotocol-v2", you might set id to 2, and the user
 *		code that acts differently according to the version can do so by
 *		switch (wsi->protocol->id), user code might use some bits as
 *		capability flags based on selected protocol version, etc.
 * @user:	User provided context data at the protocol level.
 *		Accessible via lws_get_protocol(wsi)->user
 *		This should not be confused with wsi->user, it is not the same.
 *		The library completely ignores any value in here.
 *
 *	This structure represents one protocol supported by the server.  An
 *	array of these structures is passed to lws_create_server()
 *	allows as many protocols as you like to be handled by one server.
 *
 *	The first protocol given has its callback used for user callbacks when
 *	there is no agreed protocol name, that's true during HTTP part of the
 *	connection and true if the client did not send a Protocol: header.
 */

struct lws_protocols {
	const char *name;
	lws_callback_function *callback;
	size_t per_session_data_size;
	size_t rx_buffer_size;
	unsigned int id;
	void *user;

	/* Add new things just above here ---^
	 * This is part of the ABI, don't needlessly break compatibilty */
};

enum lws_ext_options_types {
	EXTARG_NONE,
	EXTARG_DEC,
	EXTARG_OPT_DEC

	/* Add new things just above here ---^
	 * This is part of the ABI, don't needlessly break compatibilty */
};

/**
 * struct lws_ext_options -	Option arguments to the extension.  These are
 *				used in the negotiation at ws upgrade time.
 *				The helper function lws_ext_parse_options()
 *				uses these to generate callbacks
 *
 * @name:			Option name, eg, "server_no_context_takeover"
 * @type:			What kind of args the option can take
 */
struct lws_ext_options {
	const char *name;
	enum lws_ext_options_types type;

	/* Add new things just above here ---^
	 * This is part of the ABI, don't needlessly break compatibilty */
};

struct lws_ext_option_arg {
	int option_index;
	const char *start;
	int len;
};

/**
 * struct lws_extension -	An extension we know how to cope with
 *
 * @name:			Formal extension name, eg, "permessage-deflate"
 * @callback:			Service callback
 * @client_offer:		String containing exts and options client offers
 */

struct lws_extension {
	const char *name;
	lws_extension_callback_function *callback;
	const char *client_offer;

	/* Add new things just above here ---^
	 * This is part of the ABI, don't needlessly break compatibilty */
};

/*
 * The internal exts are part of the public abi
 * If we add more extensions, publish the callback here
 */

extern int lws_extension_callback_pm_deflate(
	struct lws_context *context, const struct lws_extension *ext,
	struct lws *wsi, enum lws_extension_callback_reasons reason,
	void *user, void *in, size_t len);


/**
 * struct lws_context_creation_info - parameters to create context with
 *
 * @port:	Port to listen on... you can use CONTEXT_PORT_NO_LISTEN to
 *		suppress listening on any port, that's what you want if you are
 *		not running a websocket server at all but just using it as a
 *		client
 * @iface:	NULL to bind the listen socket to all interfaces, or the
 *		interface name, eg, "eth2"
 * @protocols:	Array of structures listing supported protocols and a protocol-
 *		specific callback for each one.  The list is ended with an
 *		entry that has a NULL callback pointer.
 *		It's not const because we write the owning_server member
 * @extensions: NULL or array of lws_extension structs listing the
 *		extensions this context supports.  If you configured with
 *		--without-extensions, you should give NULL here.
 * @token_limits: NULL or struct lws_token_limits pointer which is initialized
 *		with a token length limit for each possible WSI_TOKEN_***
 * @ssl_cert_filepath:	If libwebsockets was compiled to use ssl, and you want
 *			to listen using SSL, set to the filepath to fetch the
 *			server cert from, otherwise NULL for unencrypted
 * @ssl_private_key_filepath: filepath to private key if wanting SSL mode;
 *			if this is set to NULL but sll_cert_filepath is set, the
 *			OPENSSL_CONTEXT_REQUIRES_PRIVATE_KEY callback is called
 *			to allow setting of the private key directly via openSSL
 *			library calls
 * @ssl_ca_filepath: CA certificate filepath or NULL
 * @ssl_cipher_list:	List of valid ciphers to use (eg,
 * 			"RC4-MD5:RC4-SHA:AES128-SHA:AES256-SHA:HIGH:!DSS:!aNULL"
 * 			or you can leave it as NULL to get "DEFAULT"
 * @http_proxy_address: If non-NULL, attempts to proxy via the given address.
 *			If proxy auth is required, use format
 *			"username:password@server:port"
 * @http_proxy_port:	If http_proxy_address was non-NULL, uses this port at
 * 			the address
 * @gid:	group id to change to after setting listen socket, or -1.
 * @uid:	user id to change to after setting listen socket, or -1.
 * @options:	0, or LWS_SERVER_OPTION_... bitfields
 * @user:	optional user pointer that can be recovered via the context
 *		pointer using lws_context_user
 * @ka_time:	0 for no keepalive, otherwise apply this keepalive timeout to
 *		all libwebsocket sockets, client or server
 * @ka_probes:	if ka_time was nonzero, after the timeout expires how many
 *		times to try to get a response from the peer before giving up
 *		and killing the connection
 * @ka_interval: if ka_time was nonzero, how long to wait before each ka_probes
 *		attempt
 * @provided_client_ssl_ctx: If non-null, swap out libwebsockets ssl
 *		implementation for the one provided by provided_ssl_ctx.
 *		Libwebsockets no longer is responsible for freeing the context
 *		if this option is selected.
 * @max_http_header_data: The max amount of header payload that can be handled
 *		in an http request (unrecognized header payload is dropped)
 * @max_http_header_pool: The max number of connections with http headers that
 *		can be processed simultaneously (the corresponding memory is
 *		allocated for the lifetime of the context).  If the pool is
 *		busy new incoming connections must wait for accept until one
 *		becomes free.
 */

struct lws_context_creation_info {
	int port;
	const char *iface;
	const struct lws_protocols *protocols;
	const struct lws_extension *extensions;
	const struct lws_token_limits *token_limits;
	const char *ssl_private_key_password;
	const char *ssl_cert_filepath;
	const char *ssl_private_key_filepath;
	const char *ssl_ca_filepath;
	const char *ssl_cipher_list;
	const char *http_proxy_address;
	unsigned int http_proxy_port;
	int gid;
	int uid;
	unsigned int options;
	void *user;
	int ka_time;
	int ka_probes;
	int ka_interval;
#ifdef LWS_OPENSSL_SUPPORT
	SSL_CTX *provided_client_ssl_ctx;
#else /* maintain structure layout either way */
	void *provided_client_ssl_ctx;
#endif

	short max_http_header_data;
	short max_http_header_pool;

	/* Add new things just above here ---^
	 * This is part of the ABI, don't needlessly break compatibility
	 *
	 * The below is to ensure later library versions with new
	 * members added above will see 0 (default) even if the app
	 * was not built against the newer headers.
	 */

	void *_unused[8];
};

/**
 * struct lws_client_connect_info - parameters to connect with when using
 *				    lws_client_connect_via_info()
 *
 * @context:	lws context to create connection in
 * @address:	remote address to connect to
 * @port:	remote port to connect to
 * @ssl_connection: nonzero for ssl
 * @path:	uri path
 * @host:	content of host header
 * @origin:	content of origin header
 * @protocol:	list of ws protocols
 * @ietf_version_or_minus_one: currently leave at 0 or -1
 * @userdata:	if non-NULL, use this as wsi user_data instead of malloc it
 * @client_exts: array of extensions that may be used on connection
 */

struct lws_client_connect_info {
	struct lws_context *context;
	const char *address;
	int port;
	int ssl_connection;
	const char *path;
	const char *host;
	const char *origin;
	const char *protocol;
	int ietf_version_or_minus_one;
	void *userdata;
	const struct lws_extension *client_exts;

	/* Add new things just above here ---^
	 * This is part of the ABI, don't needlessly break compatibility
	 *
	 * The below is to ensure later library versions with new
	 * members added above will see 0 (default) even if the app
	 * was not built against the newer headers.
	 */

	void *_unused[4];
};

LWS_VISIBLE LWS_EXTERN void
lws_set_log_level(int level,
		  void (*log_emit_function)(int level, const char *line));

LWS_VISIBLE LWS_EXTERN void
lwsl_emit_syslog(int level, const char *line);

LWS_VISIBLE LWS_EXTERN struct lws_context *
lws_create_context(struct lws_context_creation_info *info);

LWS_VISIBLE LWS_EXTERN int
lws_set_proxy(struct lws_context *context, const char *proxy);

LWS_VISIBLE LWS_EXTERN void
lws_context_destroy(struct lws_context *context);

LWS_VISIBLE LWS_EXTERN int
lws_service(struct lws_context *context, int timeout_ms);

LWS_VISIBLE LWS_EXTERN void
lws_cancel_service(struct lws_context *context);

LWS_VISIBLE LWS_EXTERN int
lws_interface_to_sa(int ipv6, const char *ifname, struct sockaddr_in *addr, size_t addrlen);

LWS_VISIBLE LWS_EXTERN const unsigned char *
lws_token_to_string(enum lws_token_indexes token);

LWS_VISIBLE LWS_EXTERN int
lws_add_http_header_by_name(struct lws *wsi, const unsigned char *name,
			    const unsigned char *value, int length,
			    unsigned char **p, unsigned char *end);
LWS_VISIBLE LWS_EXTERN int
lws_finalize_http_header(struct lws *wsi, unsigned char **p,
			 unsigned char *end);
LWS_VISIBLE LWS_EXTERN int
lws_add_http_header_by_token(struct lws *wsi, enum lws_token_indexes token,
			     const unsigned char *value, int length,
			     unsigned char **p, unsigned char *end);
LWS_VISIBLE LWS_EXTERN int
lws_add_http_header_content_length(struct lws *wsi,
				   unsigned long content_length,
				   unsigned char **p, unsigned char *end);
LWS_VISIBLE LWS_EXTERN int
lws_add_http_header_status(struct lws *wsi,
			   unsigned int code, unsigned char **p,
			   unsigned char *end);

LWS_EXTERN int
lws_http_transaction_completed(struct lws *wsi);

#ifdef LWS_USE_LIBEV
typedef void (lws_ev_signal_cb)(EV_P_ struct ev_signal *w, int revents);

LWS_VISIBLE LWS_EXTERN int
lws_sigint_cfg(struct lws_context *context, int use_ev_sigint,
	       lws_ev_signal_cb *cb);

LWS_VISIBLE LWS_EXTERN int
lws_initloop(struct lws_context *context, struct ev_loop *loop);

LWS_VISIBLE void
lws_sigint_cb(struct ev_loop *loop, struct ev_signal *watcher, int revents);
#endif /* LWS_USE_LIBEV */

LWS_VISIBLE LWS_EXTERN int
lws_service_fd(struct lws_context *context, struct lws_pollfd *pollfd);

LWS_VISIBLE LWS_EXTERN void *
lws_context_user(struct lws_context *context);

LWS_VISIBLE LWS_EXTERN void *
lws_wsi_user(struct lws *wsi);

/*
 * NOTE: These public enums are part of the abi.  If you want to add one,
 * add it at where specified so existing users are unaffected.
 */
enum pending_timeout {
	NO_PENDING_TIMEOUT					=  0,
	PENDING_TIMEOUT_AWAITING_PROXY_RESPONSE			=  1,
	PENDING_TIMEOUT_AWAITING_CONNECT_RESPONSE		=  2,
	PENDING_TIMEOUT_ESTABLISH_WITH_SERVER			=  3,
	PENDING_TIMEOUT_AWAITING_SERVER_RESPONSE		=  4,
	PENDING_TIMEOUT_AWAITING_PING				=  5,
	PENDING_TIMEOUT_CLOSE_ACK				=  6,
	PENDING_TIMEOUT_AWAITING_EXTENSION_CONNECT_RESPONSE	=  7,
	PENDING_TIMEOUT_SENT_CLIENT_HANDSHAKE			=  8,
	PENDING_TIMEOUT_SSL_ACCEPT				=  9,
	PENDING_TIMEOUT_HTTP_CONTENT				= 10,
	PENDING_TIMEOUT_AWAITING_CLIENT_HS_SEND			= 11,
	PENDING_FLUSH_STORED_SEND_BEFORE_CLOSE			= 12,

	/****** add new things just above ---^ ******/
};

LWS_VISIBLE LWS_EXTERN void
lws_set_timeout(struct lws *wsi, enum pending_timeout reason, int secs);

/*
 * IMPORTANT NOTICE!
 *
 * When sending with websocket protocol
 *
 * LWS_WRITE_TEXT,
 * LWS_WRITE_BINARY,
 * LWS_WRITE_CONTINUATION,
 * LWS_WRITE_PING,
 * LWS_WRITE_PONG
 *
 * the send buffer has to have LWS_PRE bytes valid BEFORE
 * the buffer pointer you pass to lws_write().
 *
 * This allows us to add protocol info before and after the data, and send as
 * one packet on the network without payload copying, for maximum efficiency.
 *
 * So for example you need this kind of code to use lws_write with a
 * 128-byte payload
 *
 *   char buf[LWS_PRE + 128];
 *
 *   // fill your part of the buffer... for example here it's all zeros
 *   memset(&buf[LWS_PRE], 0, 128);
 *
 *   lws_write(wsi, &buf[LWS_PRE], 128, LWS_WRITE_TEXT);
 *
 * When sending HTTP, with
 *
 * LWS_WRITE_HTTP,
 * LWS_WRITE_HTTP_HEADERS
 * LWS_WRITE_HTTP_FINAL
 *
 * there is no protocol data prepended, and don't need to take care about the
 * LWS_PRE bytes valid before the buffer pointer.
 *
 * LWS_PRE is at least the frame nonce + 2 header + 8 length
 * LWS_SEND_BUFFER_POST_PADDING is deprecated, it's now 0 and can be left off.
 * The example apps no longer use it.
 *
 * Pad LWS_PRE to the CPU word size, so that word references
 * to the address immediately after the padding won't cause an unaligned access
 * error. Sometimes for performance reasons the recommended padding is even
 * larger than sizeof(void *).
 */

#if !defined(LWS_SIZEOFPTR)
#define LWS_SIZEOFPTR (sizeof (void *))
#endif
#if !defined(u_int64_t)
#define u_int64_t unsigned long long
#endif

#if __x86_64__
#define _LWS_PAD_SIZE 16	/* Intel recommended for best performance */
#else
#define _LWS_PAD_SIZE LWS_SIZEOFPTR   /* Size of a pointer on the target arch */
#endif
#define _LWS_PAD(n) (((n) % _LWS_PAD_SIZE) ? \
		((n) + (_LWS_PAD_SIZE - ((n) % _LWS_PAD_SIZE))) : (n))
#define LWS_PRE _LWS_PAD(4 + 10)
/* used prior to 1.7 and retained for backward compatibility */
#define LWS_SEND_BUFFER_PRE_PADDING LWS_PRE
#define LWS_SEND_BUFFER_POST_PADDING 0

LWS_VISIBLE LWS_EXTERN int
lws_write(struct lws *wsi, unsigned char *buf, size_t len,
	  enum lws_write_protocol protocol);

/**
 * lws_close_reason - Set reason and aux data to send with Close packet
 *		If you are going to return nonzero from the callback
 *		requesting the connection to close, you can optionally
 *		call this to set the reason the peer will be told if
 *		possible.
 *
 * @wsi:	The websocket connection to set the close reason on
 * @status:	A valid close status from websocket standard
 * @buf:	NULL or buffer containing up to 124 bytes of auxiliary data
 * @len:	Length of data in @buf to send
 */
LWS_VISIBLE LWS_EXTERN void
lws_close_reason(struct lws *wsi, enum lws_close_status status,
		 unsigned char *buf, size_t len);

/* helper for case where buffer may be const */
#define lws_write_http(wsi, buf, len) \
	lws_write(wsi, (unsigned char *)(buf), len, LWS_WRITE_HTTP)

LWS_VISIBLE LWS_EXTERN int
lws_serve_http_file(struct lws *wsi, const char *file, const char *content_type,
		    const char *other_headers, int other_headers_len);
LWS_VISIBLE LWS_EXTERN int
lws_serve_http_file_fragment(struct lws *wsi);

LWS_VISIBLE LWS_EXTERN int
lws_return_http_status(struct lws *wsi, unsigned int code,
		       const char *html_body);

LWS_VISIBLE LWS_EXTERN const struct lws_protocols *
lws_get_protocol(struct lws *wsi);

LWS_VISIBLE LWS_EXTERN int
lws_callback_on_writable(struct lws *wsi);

LWS_VISIBLE LWS_EXTERN int
lws_callback_on_writable_all_protocol(const struct lws_context *context,
				      const struct lws_protocols *protocol);

LWS_VISIBLE LWS_EXTERN int
lws_callback_all_protocol(struct lws_context *context,
			  const struct lws_protocols *protocol, int reason);

LWS_VISIBLE LWS_EXTERN int
lws_get_socket_fd(struct lws *wsi);

LWS_VISIBLE LWS_EXTERN int
lws_is_final_fragment(struct lws *wsi);

LWS_VISIBLE LWS_EXTERN unsigned char
lws_get_reserved_bits(struct lws *wsi);

LWS_VISIBLE LWS_EXTERN int
lws_rx_flow_control(struct lws *wsi, int enable);

LWS_VISIBLE LWS_EXTERN void
lws_rx_flow_allow_all_protocol(const struct lws_context *context,
			       const struct lws_protocols *protocol);

LWS_VISIBLE LWS_EXTERN size_t
lws_remaining_packet_payload(struct lws *wsi);

/*
 * if the protocol does not have any guidance, returns -1.  Currently only
 * http2 connections get send window information from this API.  But your code
 * should use it so it can work properly with any protocol.
 *
 * If nonzero return is the amount of payload data the peer or intermediary has
 * reported it has buffer space for.  That has NO relationship with the amount
 * of buffer space your OS can accept on this connection for a write action.
 *
 * This number represents the maximum you could send to the peer or intermediary
 * on this connection right now without it complaining.
 *
 * lws manages accounting for send window updates and payload writes
 * automatically, so this number reflects the situation at the peer or
 * intermediary dynamically.
 */
LWS_VISIBLE LWS_EXTERN size_t
lws_get_peer_write_allowance(struct lws *wsi);

/* deprecated, use lws_client_connect_via_info() */
LWS_VISIBLE LWS_EXTERN struct lws *
lws_client_connect(struct lws_context *clients, const char *address,
		   int port, int ssl_connection, const char *path,
		   const char *host, const char *origin, const char *protocol,
		   int ietf_version_or_minus_one);
/* deprecated, use lws_client_connect_via_info() */
LWS_VISIBLE LWS_EXTERN struct lws *
lws_client_connect_extended(struct lws_context *clients, const char *address,
			    int port, int ssl_connection, const char *path,
			    const char *host, const char *origin,
			    const char *protocol, int ietf_version_or_minus_one,
			    void *userdata);

LWS_VISIBLE LWS_EXTERN struct lws *
lws_client_connect_via_info(struct lws_client_connect_info * ccinfo);

LWS_VISIBLE LWS_EXTERN const char *
lws_canonical_hostname(struct lws_context *context);


LWS_VISIBLE LWS_EXTERN void
lws_get_peer_addresses(struct lws *wsi, lws_sockfd_type fd, char *name,
		       int name_len, char *rip, int rip_len);

LWS_VISIBLE LWS_EXTERN int
lws_get_random(struct lws_context *context, void *buf, int len);

LWS_VISIBLE LWS_EXTERN int
lws_daemonize(const char *_lock_path);

LWS_VISIBLE LWS_EXTERN int
lws_send_pipe_choked(struct lws *wsi);

LWS_VISIBLE LWS_EXTERN int
lws_partial_buffered(struct lws *wsi);

LWS_VISIBLE LWS_EXTERN int
lws_frame_is_binary(struct lws *wsi);

LWS_VISIBLE LWS_EXTERN int
lws_is_ssl(struct lws *wsi);
#ifdef LWS_SHA1_USE_OPENSSL_NAME
#define lws_SHA1 SHA1
#else
LWS_VISIBLE LWS_EXTERN unsigned char *
lws_SHA1(const unsigned char *d, size_t n, unsigned char *md);
#endif

LWS_VISIBLE LWS_EXTERN int
lws_b64_encode_string(const char *in, int in_len, char *out, int out_size);

LWS_VISIBLE LWS_EXTERN int
lws_b64_decode_string(const char *in, char *out, int out_size);

LWS_VISIBLE LWS_EXTERN const char *
lws_get_library_version(void);

LWS_VISIBLE LWS_EXTERN int
lws_parse_uri(char *p, const char **prot, const char **ads, int *port,
	      const char **path);

/*
 *  Access to http headers
 *
 *  In lws the client http headers are temporarily malloc'd only for the
 *  duration of the http part of the handshake.  It's because in most cases,
 *  the header content is ignored for the whole rest of the connection lifetime
 *  and would then just be taking up space needlessly.
 *
 *  During LWS_CALLBACK_HTTP when the URI path is delivered is the last time
 *  the http headers are still allocated, you can use these apis then to
 *  look at and copy out interesting header content (cookies, etc)
 *
 *  Notice that the header total length reported does not include a terminating
 *  '\0', however you must allocate for it when using the _copy apis.  So the
 *  length reported for a header containing "123" is 3, but you must provide
 *  a buffer of length 4 so that "123\0" may be copied into it, or the copy
 *  will fail with a nonzero return code.
 */

LWS_VISIBLE LWS_EXTERN int
lws_hdr_total_length(struct lws *wsi, enum lws_token_indexes h);

LWS_VISIBLE LWS_EXTERN int
lws_hdr_fragment_length(struct lws *wsi, enum lws_token_indexes h, int frag_idx);

/*
 * copies the whole, aggregated header, even if it was delivered in
 * several actual headers piece by piece
 */
LWS_VISIBLE LWS_EXTERN int
lws_hdr_copy(struct lws *wsi, char *dest, int len, enum lws_token_indexes h);

/*
 * copies only fragment frag_idx of a header.  Normally this is only useful
 * to parse URI arguments like ?x=1&y=2, oken index WSI_TOKEN_HTTP_URI_ARGS
 * fragment 0 will contain "x=1" and fragment 1 "y=2"
 */
LWS_VISIBLE LWS_EXTERN int
lws_hdr_copy_fragment(struct lws *wsi, char *dest, int len,
		      enum lws_token_indexes h, int frag_idx);


/* get the active file operations struct */
LWS_VISIBLE LWS_EXTERN struct lws_plat_file_ops *
lws_get_fops(struct lws_context *context);

LWS_VISIBLE LWS_EXTERN struct lws_context *
lws_get_context(const struct lws *wsi);

/*
 * Wsi-associated File Operations access helpers
 *
 * Use these helper functions if you want to access a file from the perspective
 * of a specific wsi, which is usually the case.  If you just want contextless
 * file access, use the fops callbacks directly with NULL wsi instead of these
 * helpers.
 *
 * If so, then it calls the platform handler or user overrides where present
 * (as defined in info->fops)
 *
 * The advantage from all this is user code can be portable for file operations
 * without having to deal with differences between platforms.
 */

static LWS_INLINE lws_filefd_type
lws_plat_file_open(struct lws *wsi, const char *filename,
		   unsigned long *filelen, int flags)
{
	return lws_get_fops(lws_get_context(wsi))->open(wsi, filename,
						    filelen, flags);
}

static LWS_INLINE int
lws_plat_file_close(struct lws *wsi, lws_filefd_type fd)
{
	return lws_get_fops(lws_get_context(wsi))->close(wsi, fd);
}

static LWS_INLINE unsigned long
lws_plat_file_seek_cur(struct lws *wsi, lws_filefd_type fd, long offset)
{
	return lws_get_fops(lws_get_context(wsi))->seek_cur(wsi, fd, offset);
}

static LWS_INLINE int
lws_plat_file_read(struct lws *wsi, lws_filefd_type fd, unsigned long *amount,
		   unsigned char *buf, unsigned long len)
{
	return lws_get_fops(lws_get_context(wsi))->read(wsi, fd, amount, buf,
							len);
}

static LWS_INLINE int
lws_plat_file_write(struct lws *wsi, lws_filefd_type fd, unsigned long *amount,
		    unsigned char *buf, unsigned long len)
{
	return lws_get_fops(lws_get_context(wsi))->write(wsi, fd, amount, buf,
							 len);
}

/*
 * Note: this is not normally needed as a user api.  It's provided in case it is
 * useful when integrating with other app poll loop service code.
 */
LWS_VISIBLE LWS_EXTERN int
lws_read(struct lws *wsi, unsigned char *buf, size_t len);

#ifndef LWS_NO_EXTENSIONS
/* deprecated */
#define lws_get_internal_extensions() NULL
LWS_VISIBLE LWS_EXTERN int
lws_ext_parse_options(const struct lws_extension *ext, struct lws *wsi,
		       void *ext_user, const struct lws_ext_options *opts, const char *o, int len);
#endif

/*
 * custom allocator support
 */
LWS_VISIBLE LWS_EXTERN void
lws_set_allocator(void *(*realloc)(void *ptr, size_t size));

#ifdef __cplusplus
}
#endif

#endif
