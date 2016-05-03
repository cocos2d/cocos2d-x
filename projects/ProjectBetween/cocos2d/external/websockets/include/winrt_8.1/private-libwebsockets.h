/*
 * libwebsockets - small server side websockets and web server implementation
 *
 * Copyright (C) 2010 - 2015 Andy Green <andy@warmcat.com>
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

#include "lws_config.h"
#include "lws_config_private.h"

#ifdef LWS_HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <assert.h>

#ifdef LWS_HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif

#if defined(WIN32) || defined(_WIN32)

#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY != WINAPI_FAMILY_DESKTOP_APP)
    #ifndef WINVER
        #define WINVER 0x0602
        #define _WIN32_WINNT WINVER
    #endif

    #define getenv(x) NULL
    #define _WINSOCK_DEPRECATED_NO_WARNINGS
#else

#if (WINVER < 0x0501)
    #undef WINVER
    #undef _WIN32_WINNT
    #define WINVER 0x0501
    #define _WIN32_WINNT WINVER
    #endif
#endif

#define LWS_NO_DAEMONIZE
#define LWS_ERRNO WSAGetLastError()
#define LWS_EAGAIN WSAEWOULDBLOCK
#define LWS_EALREADY WSAEALREADY
#define LWS_EINPROGRESS WSAEINPROGRESS
#define LWS_EINTR WSAEINTR
#define LWS_EISCONN WSAEISCONN
#define LWS_EWOULDBLOCK WSAEWOULDBLOCK
#define LWS_POLLHUP (FD_CLOSE)
#define LWS_POLLIN (FD_READ | FD_ACCEPT)
#define LWS_POLLOUT (FD_WRITE)
#define MSG_NOSIGNAL 0
#define SHUT_RDWR SD_BOTH
#define SOL_TCP IPPROTO_TCP

#define compatible_close(fd) closesocket(fd)
#define lws_set_blocking_send(wsi) wsi->sock_send_blocking = 1
#define lws_socket_is_valid(x) (!!x)
#define LWS_SOCK_INVALID 0
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <tchar.h>
#ifdef LWS_HAVE_IN6ADDR_H
#include <in6addr.h>
#endif

#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
struct tcp_keepalive {
    ULONG onoff;
    ULONG keepalivetime;
    ULONG keepaliveinterval;
};
#define SIO_KEEPALIVE_VALS  _WSAIOW(IOC_VENDOR,4)
#else
#include <mstcpip.h>
#endif

#ifndef __func__
#define __func__ __FUNCTION__
#endif

#ifdef _WIN32_WCE
#define vsnprintf _vsnprintf
#endif

#else /* not windows --> */

#include <fcntl.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#ifndef MBED_OPERATORS
#ifndef __cplusplus
#include <errno.h>
#endif
#include <netdb.h>
#include <signal.h>
#include <sys/socket.h>
#ifdef LWS_BUILTIN_GETIFADDRS
 #include <getifaddrs.h>
#else
 #include <ifaddrs.h>
#endif
#if defined (__ANDROID__)
#include <syslog.h>
#else
#include <sys/syslog.h>
#endif
#include <sys/un.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <poll.h>
#ifdef LWS_USE_LIBEV
#include <ev.h>
#endif /* LWS_USE_LIBEV */
#include <sys/mman.h>

#endif /* MBED */

#ifndef LWS_NO_FORK
#ifdef LWS_HAVE_SYS_PRCTL_H
#include <sys/prctl.h>
#endif
#endif

#include <sys/time.h>

#define LWS_ERRNO errno
#define LWS_EAGAIN EAGAIN
#define LWS_EALREADY EALREADY
#define LWS_EINPROGRESS EINPROGRESS
#define LWS_EINTR EINTR
#define LWS_EISCONN EISCONN
#define LWS_EWOULDBLOCK EWOULDBLOCK
#define LWS_POLLHUP (POLLHUP|POLLERR)
#define LWS_POLLIN (POLLIN)
#define LWS_POLLOUT (POLLOUT)
#define compatible_close(fd) close(fd)
#define lws_set_blocking_send(wsi)

#ifdef MBED_OPERATORS
#define lws_socket_is_valid(x) ((x) != NULL)
#define LWS_SOCK_INVALID (NULL)
#else
#define lws_socket_is_valid(x) (x >= 0)
#define LWS_SOCK_INVALID (-1)
#endif
#endif

#ifndef LWS_HAVE_BZERO
#ifndef bzero
#define bzero(b, len) (memset((b), '\0', (len)), (void) 0)
#endif
#endif

#ifndef LWS_HAVE_STRERROR
#define strerror(x) ""
#endif

#ifdef LWS_OPENSSL_SUPPORT
#ifdef USE_WOLFSSL
#ifdef USE_OLD_CYASSL
#include <cyassl/openssl/ssl.h>
#include <cyassl/error-ssl.h>
#else
#include <wolfssl/openssl/ssl.h>
#include <wolfssl/error-ssl.h>
#endif /* not USE_OLD_CYASSL */
#else
#include <openssl/ssl.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#endif /* not USE_WOLFSSL */
#endif

#include "libwebsockets.h"

#if defined(MBED_OPERATORS)
#undef compatible_close
#define compatible_close(fd) mbed3_delete_tcp_stream_socket(fd)
#ifndef BIG_ENDIAN
#define BIG_ENDIAN    4321  /* to show byte order (taken from gcc) */
#endif
#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN 1234
#endif
#ifndef BYTE_ORDER
#define BYTE_ORDER LITTLE_ENDIAN
#endif
#endif

#if defined(WIN32) || defined(_WIN32)

#ifndef BIG_ENDIAN
#define BIG_ENDIAN    4321  /* to show byte order (taken from gcc) */
#endif
#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN 1234
#endif
#ifndef BYTE_ORDER
#define BYTE_ORDER LITTLE_ENDIAN
#endif
#ifndef u_int64_t
typedef unsigned __int64 u_int64_t;
#endif

#undef __P
#ifndef __P
#if __STDC__
#define __P(protos) protos
#else
#define __P(protos) ()
#endif
#endif

#else

#include <sys/stat.h>
#include <sys/cdefs.h>
#include <sys/time.h>

#if defined(__APPLE__)
#include <machine/endian.h>
#elif defined(__FreeBSD__)
#include <sys/endian.h>
#elif defined(__linux__)
#include <endian.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
#include <stddef.h>

#ifndef container_of
#define container_of(P,T,M)	((T *)((char *)(P) - offsetof(T, M)))
#endif

#if defined(__QNX__)
	#include <gulliver.h>
	#if defined(__LITTLEENDIAN__)
		#define BYTE_ORDER __LITTLEENDIAN__
		#define LITTLE_ENDIAN __LITTLEENDIAN__
		#define BIG_ENDIAN 4321  /* to show byte order (taken from gcc); for suppres warning that BIG_ENDIAN is not defined. */
	#endif
	#if defined(__BIGENDIAN__)
		#define BYTE_ORDER __BIGENDIAN__
		#define LITTLE_ENDIAN 1234  /* to show byte order (taken from gcc); for suppres warning that LITTLE_ENDIAN is not defined. */
		#define BIG_ENDIAN __BIGENDIAN__
	#endif
#endif

#if !defined(BYTE_ORDER)
# define BYTE_ORDER __BYTE_ORDER
#endif
#if !defined(LITTLE_ENDIAN)
# define LITTLE_ENDIAN __LITTLE_ENDIAN
#endif
#if !defined(BIG_ENDIAN)
# define BIG_ENDIAN __BIG_ENDIAN
#endif

#endif

/*
 * Mac OSX as well as iOS do not define the MSG_NOSIGNAL flag,
 * but happily have something equivalent in the SO_NOSIGPIPE flag.
 */
#ifdef __APPLE__
#define MSG_NOSIGNAL SO_NOSIGPIPE
#endif

#ifdef _WIN32
#ifndef FD_HASHTABLE_MODULUS
#define FD_HASHTABLE_MODULUS 32
#endif
#endif

#ifndef LWS_MAX_HEADER_LEN
#define LWS_MAX_HEADER_LEN 1024
#endif
#ifndef LWS_MAX_HEADER_POOL
#define LWS_MAX_HEADER_POOL 16
#endif
#ifndef LWS_MAX_PROTOCOLS
#define LWS_MAX_PROTOCOLS 5
#endif
#ifndef LWS_MAX_EXTENSIONS_ACTIVE
#define LWS_MAX_EXTENSIONS_ACTIVE 3
#endif
#ifndef LWS_MAX_EXT_OFFERS
#define LWS_MAX_EXT_OFFERS 8
#endif
#ifndef SPEC_LATEST_SUPPORTED
#define SPEC_LATEST_SUPPORTED 13
#endif
#ifndef AWAITING_TIMEOUT
#define AWAITING_TIMEOUT 5
#endif
#ifndef CIPHERS_LIST_STRING
#define CIPHERS_LIST_STRING "DEFAULT"
#endif
#ifndef LWS_SOMAXCONN
#define LWS_SOMAXCONN SOMAXCONN
#endif

#define MAX_WEBSOCKET_04_KEY_LEN 128
#define LWS_MAX_SOCKET_IO_BUF 4096

#ifndef SYSTEM_RANDOM_FILEPATH
#define SYSTEM_RANDOM_FILEPATH "/dev/urandom"
#endif
#ifndef LWS_MAX_ZLIB_CONN_BUFFER
#define LWS_MAX_ZLIB_CONN_BUFFER (64 * 1024)
#endif

/*
 * if not in a connection storm, check for incoming
 * connections this many normal connection services
 */
#define LWS_lserv_mod 10

enum lws_websocket_opcodes_07 {
	LWSWSOPC_CONTINUATION = 0,
	LWSWSOPC_TEXT_FRAME = 1,
	LWSWSOPC_BINARY_FRAME = 2,

	LWSWSOPC_NOSPEC__MUX = 7,

	/* control extensions 8+ */

	LWSWSOPC_CLOSE = 8,
	LWSWSOPC_PING = 9,
	LWSWSOPC_PONG = 0xa,
};


enum lws_connection_states {
	LWSS_HTTP,
	LWSS_HTTP_ISSUING_FILE,
	LWSS_HTTP_HEADERS,
	LWSS_HTTP_BODY,
	LWSS_DEAD_SOCKET,
	LWSS_ESTABLISHED,
	LWSS_CLIENT_UNCONNECTED,
	LWSS_RETURNED_CLOSE_ALREADY,
	LWSS_AWAITING_CLOSE_ACK,
	LWSS_FLUSHING_STORED_SEND_BEFORE_CLOSE,

	LWSS_HTTP2_AWAIT_CLIENT_PREFACE,
	LWSS_HTTP2_ESTABLISHED_PRE_SETTINGS,
	LWSS_HTTP2_ESTABLISHED,
};

enum http_version {
	HTTP_VERSION_1_0,
	HTTP_VERSION_1_1,
};

enum http_connection_type {
	HTTP_CONNECTION_CLOSE,
	HTTP_CONNECTION_KEEP_ALIVE
};

enum lws_pending_protocol_send {
	LWS_PPS_NONE,
	LWS_PPS_HTTP2_MY_SETTINGS,
	LWS_PPS_HTTP2_ACK_SETTINGS,
	LWS_PPS_HTTP2_PONG,
};

enum lws_rx_parse_state {
	LWS_RXPS_NEW,

	LWS_RXPS_04_mask_1,
	LWS_RXPS_04_mask_2,
	LWS_RXPS_04_mask_3,

	LWS_RXPS_04_FRAME_HDR_1,
	LWS_RXPS_04_FRAME_HDR_LEN,
	LWS_RXPS_04_FRAME_HDR_LEN16_2,
	LWS_RXPS_04_FRAME_HDR_LEN16_1,
	LWS_RXPS_04_FRAME_HDR_LEN64_8,
	LWS_RXPS_04_FRAME_HDR_LEN64_7,
	LWS_RXPS_04_FRAME_HDR_LEN64_6,
	LWS_RXPS_04_FRAME_HDR_LEN64_5,
	LWS_RXPS_04_FRAME_HDR_LEN64_4,
	LWS_RXPS_04_FRAME_HDR_LEN64_3,
	LWS_RXPS_04_FRAME_HDR_LEN64_2,
	LWS_RXPS_04_FRAME_HDR_LEN64_1,

	LWS_RXPS_07_COLLECT_FRAME_KEY_1,
	LWS_RXPS_07_COLLECT_FRAME_KEY_2,
	LWS_RXPS_07_COLLECT_FRAME_KEY_3,
	LWS_RXPS_07_COLLECT_FRAME_KEY_4,

	LWS_RXPS_PAYLOAD_UNTIL_LENGTH_EXHAUSTED
};


enum connection_mode {
	LWSCM_HTTP_SERVING,
	LWSCM_HTTP_SERVING_ACCEPTED, /* actual HTTP service going on */
	LWSCM_PRE_WS_SERVING_ACCEPT,

	LWSCM_WS_SERVING,
	LWSCM_WS_CLIENT,

	LWSCM_HTTP2_SERVING,

	/* transient, ssl delay hiding */
	LWSCM_SSL_ACK_PENDING,

	/* transient modes */
	LWSCM_WSCL_WAITING_CONNECT,
	LWSCM_WSCL_WAITING_PROXY_REPLY,
	LWSCM_WSCL_ISSUE_HANDSHAKE,
	LWSCM_WSCL_ISSUE_HANDSHAKE2,
	LWSCM_WSCL_WAITING_SSL,
	LWSCM_WSCL_WAITING_SERVER_REPLY,
	LWSCM_WSCL_WAITING_EXTENSION_CONNECT,
	LWSCM_WSCL_PENDING_CANDIDATE_CHILD,

	/* special internal types */
	LWSCM_SERVER_LISTENER,
};

enum {
	LWS_RXFLOW_ALLOW = (1 << 0),
	LWS_RXFLOW_PENDING_CHANGE = (1 << 1),
};

/* this is not usable directly by user code any more, lws_close_reason() */
#define LWS_WRITE_CLOSE 4

struct lws_protocols;
struct lws;

#ifdef LWS_USE_LIBEV
struct lws_io_watcher {
	struct ev_io watcher;
	struct lws_context* context;
};

struct lws_signal_watcher {
	struct ev_signal watcher;
	struct lws_context* context;
};
#endif /* LWS_USE_LIBEV */

#ifdef _WIN32
#define LWS_FD_HASH(fd) ((fd ^ (fd >> 8) ^ (fd >> 16)) % FD_HASHTABLE_MODULUS)
struct lws_fd_hashtable {
	struct lws **wsi;
	int length;
};
#endif

/*
 * This is totally opaque to code using the library.  It's exported as a
 * forward-reference pointer-only declaration; the user can use the pointer with
 * other APIs to get information out of it.
 */

struct lws_fragments {
	unsigned short offset;
	unsigned short len;
	unsigned char nfrag; /* which ah->frag[] continues this content, or 0 */
};

/*
 * these are assigned from a pool held in the context.
 * Both client and server mode uses them for http header analysis
 */

struct allocated_headers {
	char *data; /* prepared by context init to point to dedicated storage */
	/*
	 * the randomly ordered fragments, indexed by frag_index and
	 * lws_fragments->nfrag for continuation.
	 */
	struct lws_fragments frags[WSI_TOKEN_COUNT * 2];
	/*
	 * for each recognized token, frag_index says which frag[] his data
	 * starts in (0 means the token did not appear)
	 * the actual header data gets dumped as it comes in, into data[]
	 */
	unsigned char frag_index[WSI_TOKEN_COUNT];
#ifndef LWS_NO_CLIENT
	char initial_handshake_hash_base64[30];
	unsigned short c_port;
#endif

	unsigned short pos;
	unsigned char in_use;
	unsigned char nfrag;
};

struct lws_context {
	time_t last_timeout_check_s;
	struct lws_plat_file_ops fops;
#ifdef _WIN32
	WSAEVENT *events;
#endif
	struct lws_pollfd *fds;
#ifdef _WIN32
/* different implementation between unix and windows */
	struct lws_fd_hashtable fd_hashtable[FD_HASHTABLE_MODULUS];
#else
	struct lws **lws_lookup;  /* fd to wsi */
#endif
#ifdef LWS_USE_LIBEV
	struct ev_loop* io_loop;
	struct lws_io_watcher w_accept;
	struct lws_signal_watcher w_sigint;
	lws_ev_signal_cb* lws_ev_sigint_cb;
#endif /* LWS_USE_LIBEV */
	const char *iface;
	const struct lws_token_limits *token_limits;
	void *user_space;
#ifndef LWS_NO_SERVER
	struct lws *wsi_listening;
#endif
	const struct lws_protocols *protocols;
	void *http_header_data;
	struct allocated_headers *ah_pool;
	struct lws *rx_draining_ext_list;
	struct lws *tx_draining_ext_list;
#ifdef LWS_OPENSSL_SUPPORT
	SSL_CTX *ssl_ctx;
	SSL_CTX *ssl_client_ctx;
	struct lws *pending_read_list; /* linked list */
#endif
#ifndef LWS_NO_EXTENSIONS
	const struct lws_extension *extensions;
#endif

	/*
	 * usable by anything in the service code, but only if the scope
	 * does not last longer than the service action (since next service
	 * of any socket can likewise use it and overwrite)
	 */
	unsigned char serv_buf[LWS_MAX_SOCKET_IO_BUF];
	char http_proxy_address[128];
	char proxy_basic_auth_token[128];
	char canonical_hostname[128];
#ifdef LWS_LATENCY
	unsigned long worst_latency;
	char worst_latency_info[256];
#endif

	lws_sockfd_type lserv_fd;

	int fds_count;
	int max_fds;
	int listen_port;
#ifdef LWS_USE_LIBEV
	int use_ev_sigint;
#endif
	int started_with_parent;

	int fd_random;
	int lserv_mod;
	int lserv_count;
	int lserv_seen;
	unsigned int http_proxy_port;
	unsigned int options;

	/*
	 * set to the Thread ID that's doing the service loop just before entry
	 * to poll indicates service thread likely idling in poll()
	 * volatile because other threads may check it as part of processing
	 * for pollfd event change.
	 */
	volatile int service_tid;
	int service_tid_detected;
#ifndef _WIN32
	int dummy_pipe_fds[2];
#endif

	int count_protocols;
	int ka_time;
	int ka_probes;
	int ka_interval;

#ifdef LWS_OPENSSL_SUPPORT
	int use_ssl;
	int allow_non_ssl_on_ssl_port;
	unsigned int user_supplied_ssl_ctx:1;
#define lws_ssl_anybody_has_buffered_read(ctx) \
		(ctx->use_ssl && ctx->pending_read_list)
#else
#define lws_ssl_anybody_has_buffered_read(ctx) (0)
#endif

	short max_http_header_data;
	short max_http_header_pool;
	short ah_count_in_use;

	unsigned int being_destroyed:1;
};

enum {
	LWS_EV_READ = (1 << 0),
	LWS_EV_WRITE = (1 << 1),
	LWS_EV_START = (1 << 2),
	LWS_EV_STOP = (1 << 3),
};

#ifdef LWS_USE_LIBEV
#define LWS_LIBEV_ENABLED(context) (context->options & LWS_SERVER_OPTION_LIBEV)
LWS_EXTERN void lws_feature_status_libev(struct lws_context_creation_info *info);
LWS_EXTERN void
lws_libev_accept(struct lws *new_wsi, lws_sockfd_type accept_fd);
LWS_EXTERN void
lws_libev_io(struct lws *wsi, int flags);
LWS_EXTERN int
lws_libev_init_fd_table(struct lws_context *context);
LWS_EXTERN void
lws_libev_run(const struct lws_context *context);
#else
#define LWS_LIBEV_ENABLED(context) (0)
#ifdef LWS_POSIX
#define lws_feature_status_libev(_a) \
			lwsl_notice("libev support not compiled in\n")
#else
#define lws_feature_status_libev(_a)
#endif
#define lws_libev_accept(_a, _b) ((void) 0)
#define lws_libev_io(_a, _b) ((void) 0)
#define lws_libev_init_fd_table(_a) (0)
#define lws_libev_run(_a) ((void) 0)
#endif

#ifdef LWS_USE_IPV6
#define LWS_IPV6_ENABLED(context) \
	(!(context->options & LWS_SERVER_OPTION_DISABLE_IPV6))
#else
#define LWS_IPV6_ENABLED(context) (0)
#endif

enum uri_path_states {
	URIPS_IDLE,
	URIPS_SEEN_SLASH,
	URIPS_SEEN_SLASH_DOT,
	URIPS_SEEN_SLASH_DOT_DOT,
};

enum uri_esc_states {
	URIES_IDLE,
	URIES_SEEN_PERCENT,
	URIES_SEEN_PERCENT_H1,
};

/* notice that these union members:
 *
 *  hdr
 *  http
 *  http2
 *
 * all have a pointer to allocated_headers struct as their first member.
 *
 * It means for allocated_headers access, the three union paths can all be
 * used interchangeably to access the same data
 */

struct _lws_http_mode_related {
	/* MUST be first in struct */
	struct allocated_headers *ah; /* mirroring  _lws_header_related */
	unsigned long filepos;
	unsigned long filelen;
	lws_filefd_type fd;

	enum http_version request_version;
	enum http_connection_type connection_type;
	unsigned int content_length;
	unsigned int content_remain;
};

#ifdef LWS_USE_HTTP2

enum lws_http2_settings {
	LWS_HTTP2_SETTINGS__HEADER_TABLE_SIZE = 1,
	LWS_HTTP2_SETTINGS__ENABLE_PUSH,
	LWS_HTTP2_SETTINGS__MAX_CONCURRENT_STREAMS,
	LWS_HTTP2_SETTINGS__INITIAL_WINDOW_SIZE,
	LWS_HTTP2_SETTINGS__MAX_FRAME_SIZE,
	LWS_HTTP2_SETTINGS__MAX_HEADER_LIST_SIZE,

	LWS_HTTP2_SETTINGS__COUNT /* always last */
};

enum lws_http2_wellknown_frame_types {
	LWS_HTTP2_FRAME_TYPE_DATA,
	LWS_HTTP2_FRAME_TYPE_HEADERS,
	LWS_HTTP2_FRAME_TYPE_PRIORITY,
	LWS_HTTP2_FRAME_TYPE_RST_STREAM,
	LWS_HTTP2_FRAME_TYPE_SETTINGS,
	LWS_HTTP2_FRAME_TYPE_PUSH_PROMISE,
	LWS_HTTP2_FRAME_TYPE_PING,
	LWS_HTTP2_FRAME_TYPE_GOAWAY,
	LWS_HTTP2_FRAME_TYPE_WINDOW_UPDATE,
	LWS_HTTP2_FRAME_TYPE_CONTINUATION,

	LWS_HTTP2_FRAME_TYPE_COUNT /* always last */
};

enum lws_http2_flags {
	LWS_HTTP2_FLAG_END_STREAM = 1,
	LWS_HTTP2_FLAG_END_HEADERS = 4,
	LWS_HTTP2_FLAG_PADDED = 8,
	LWS_HTTP2_FLAG_PRIORITY = 0x20,

	LWS_HTTP2_FLAG_SETTINGS_ACK = 1,
};

#define LWS_HTTP2_STREAM_ID_MASTER 0
#define LWS_HTTP2_FRAME_HEADER_LENGTH 9
#define LWS_HTTP2_SETTINGS_LENGTH 6

struct http2_settings {
	unsigned int setting[LWS_HTTP2_SETTINGS__COUNT];
};

enum http2_hpack_state {

	/* optional before first header block */
	HPKS_OPT_PADDING,
	HKPS_OPT_E_DEPENDENCY,
	HKPS_OPT_WEIGHT,

	/* header block */
	HPKS_TYPE,

	HPKS_IDX_EXT,

	HPKS_HLEN,
	HPKS_HLEN_EXT,

	HPKS_DATA,

	/* optional after last header block */
	HKPS_OPT_DISCARD_PADDING,
};

enum http2_hpack_type {
	HPKT_INDEXED_HDR_7,
	HPKT_INDEXED_HDR_6_VALUE_INCR,
	HPKT_LITERAL_HDR_VALUE_INCR,
	HPKT_INDEXED_HDR_4_VALUE,
	HPKT_LITERAL_HDR_VALUE,
	HPKT_SIZE_5
};

struct hpack_dt_entry {
	int token; /* additions that don't map to a token are ignored */
	int arg_offset;
	int arg_len;
};

struct hpack_dynamic_table {
	struct hpack_dt_entry *entries;
	char *args;
	int pos;
	int next;
	int num_entries;
	int args_length;
};

struct _lws_http2_related {
	/*
	 * having this first lets us also re-use all HTTP union code
	 * and in turn, http_mode_related has allocated headers in right
	 * place so we can use the header apis on the wsi directly still
	 */
	struct _lws_http_mode_related http; /* MUST BE FIRST IN STRUCT */

	struct http2_settings my_settings;
	struct http2_settings peer_settings;

	struct lws *parent_wsi;
	struct lws *next_child_wsi;

	struct hpack_dynamic_table *hpack_dyn_table;
	struct lws *stream_wsi;
	unsigned char ping_payload[8];
	unsigned char one_setting[LWS_HTTP2_SETTINGS_LENGTH];

	unsigned int count;
	unsigned int length;
	unsigned int stream_id;
	enum http2_hpack_state hpack;
	enum http2_hpack_type hpack_type;
	unsigned int header_index;
	unsigned int hpack_len;
	unsigned int hpack_e_dep;
	int tx_credit;
	unsigned int my_stream_id;
	unsigned int child_count;
	int my_priority;

	unsigned int END_STREAM:1;
	unsigned int END_HEADERS:1;
	unsigned int send_END_STREAM:1;
	unsigned int GOING_AWAY;
	unsigned int requested_POLLOUT:1;
	unsigned int waiting_tx_credit:1;
	unsigned int huff:1;
	unsigned int value:1;

	unsigned short round_robin_POLLOUT;
	unsigned short count_POLLOUT_children;
	unsigned short hpack_pos;

	unsigned char type;
	unsigned char flags;
	unsigned char frame_state;
	unsigned char padding;
	unsigned char hpack_m;
	unsigned char initialized;
};

#define HTTP2_IS_TOPLEVEL_WSI(wsi) (!wsi->u.http2.parent_wsi)

#endif

struct _lws_header_related {
	/* MUST be first in struct */
	struct allocated_headers *ah;
	enum uri_path_states ups;
	enum uri_esc_states ues;
	short lextable_pos;
	unsigned short current_token_limit;
	char esc_stash;
	char post_literal_equal;
	unsigned char parser_state; /* enum lws_token_indexes */
	char redirects;
};

struct _lws_websocket_related {
	char *rx_ubuf;
       unsigned int rx_ubuf_alloc;
	struct lws *rx_draining_ext_list;
	struct lws *tx_draining_ext_list;
	size_t rx_packet_length;
	unsigned int rx_ubuf_head;
	unsigned char mask[4];
	/* Also used for close content... control opcode == < 128 */
	unsigned char ping_payload_buf[128 - 3 + LWS_PRE];

	unsigned char ping_payload_len;
	unsigned char mask_idx;
	unsigned char opcode;
	unsigned char rsv;
	unsigned char rsv_first_msg;
	/* zero if no info, or length including 2-byte close code */
	unsigned char close_in_ping_buffer_len;
	unsigned char utf8;
	unsigned char stashed_write_type;
	unsigned char tx_draining_stashed_wp;

	unsigned int final:1;
	unsigned int frame_is_binary:1;
	unsigned int all_zero_nonce:1;
	unsigned int this_frame_masked:1;
	unsigned int inside_frame:1; /* next write will be more of frame */
	unsigned int clean_buffer:1; /* buffer not rewritten by extension */
	unsigned int payload_is_close:1; /* process as PONG, but it is close */
	unsigned int ping_pending_flag:1;
	unsigned int continuation_possible:1;
	unsigned int owed_a_fin:1;
	unsigned int check_utf8:1;
	unsigned int defeat_check_utf8:1;
	unsigned int pmce_compressed_message:1;
	unsigned int stashed_write_pending:1;
	unsigned int rx_draining_ext:1;
	unsigned int tx_draining_ext:1;
};

struct lws {

	/* structs */
	/* members with mutually exclusive lifetimes are unionized */

	union u {
		struct _lws_http_mode_related http;
#ifdef LWS_USE_HTTP2
		struct _lws_http2_related http2;
#endif
		struct _lws_header_related hdr;
		struct _lws_websocket_related ws;
	} u;

	/* lifetime members */

#ifdef LWS_USE_LIBEV
	struct lws_io_watcher w_read;
	struct lws_io_watcher w_write;
#endif /* LWS_USE_LIBEV */
	time_t pending_timeout_limit;

	/* pointers */

	struct lws_context *context;
	const struct lws_protocols *protocol;
	void *user_space;
	/* rxflow handling */
	unsigned char *rxflow_buffer;
	/* truncated send handling */
	unsigned char *trunc_alloc; /* non-NULL means buffering in progress */
#ifndef LWS_NO_EXTENSIONS
	const struct lws_extension *active_extensions[LWS_MAX_EXTENSIONS_ACTIVE];
	void *act_ext_user[LWS_MAX_EXTENSIONS_ACTIVE];
#endif
#ifdef LWS_OPENSSL_SUPPORT
	SSL *ssl;
	BIO *client_bio;
	struct lws *pending_read_list_prev, *pending_read_list_next;
#endif
#ifdef LWS_LATENCY
	unsigned long action_start;
	unsigned long latency_start;
#endif
	/* pointer / int */
	lws_sockfd_type sock;

	/* ints */
	enum lws_pending_protocol_send pps;
	int position_in_fds_table;
	int rxflow_len;
	int rxflow_pos;
	unsigned int trunc_alloc_len; /* size of malloc */
	unsigned int trunc_offset; /* where we are in terms of spilling */
	unsigned int trunc_len; /* how much is buffered */

	unsigned int hdr_parsing_completed:1;
	unsigned int user_space_externally_allocated:1;
	unsigned int socket_is_permanently_unusable:1;
	unsigned int rxflow_change_to:2;
#ifndef LWS_NO_EXTENSIONS
	unsigned int extension_data_pending:1;
#endif
#ifdef LWS_OPENSSL_SUPPORT
	unsigned int use_ssl:2;
	unsigned int upgraded:1;
#endif
#ifdef _WIN32
	unsigned int sock_send_blocking:1;
#endif

	/* chars */
#ifndef LWS_NO_EXTENSIONS
	unsigned char count_act_ext;
#endif
	unsigned char ietf_spec_revision;
	char mode; /* enum connection_mode */
	char state; /* enum lws_connection_states */
	char lws_rx_parse_state; /* enum lws_rx_parse_state */
	char rx_frame_type; /* enum lws_write_protocol */
	char pending_timeout; /* enum pending_timeout */
};

LWS_EXTERN int log_level;

LWS_EXTERN void
lws_close_free_wsi(struct lws *wsi, enum lws_close_status);

LWS_EXTERN int
remove_wsi_socket_from_fds(struct lws *wsi);
LWS_EXTERN int
lws_rxflow_cache(struct lws *wsi, unsigned char *buf, int n, int len);

#ifndef LWS_LATENCY
static inline void
lws_latency(struct lws_context *context, struct lws *wsi, const char *action,
	    int ret, int completion) {
	do {
		(void)context; (void)wsi; (void)action; (void)ret;
		(void)completion;
	} while (0);
}
static inline void
lws_latency_pre(struct lws_context *context, struct lws *wsi) {
	do { (void)context; (void)wsi; } while (0);
}
#else
#define lws_latency_pre(_context, _wsi) lws_latency(_context, _wsi, NULL, 0, 0)
extern void
lws_latency(struct lws_context *context, struct lws *wsi, const char *action,
	    int ret, int completion);
#endif

LWS_EXTERN void
lws_set_protocol_write_pending(struct lws *wsi,
			       enum lws_pending_protocol_send pend);
LWS_EXTERN int
lws_client_rx_sm(struct lws *wsi, unsigned char c);

LWS_EXTERN int
lws_parse(struct lws *wsi, unsigned char c);

LWS_EXTERN int
lws_http_action(struct lws *wsi);

LWS_EXTERN int
lws_b64_selftest(void);

#if defined(_WIN32) || defined(MBED_OPERATORS)
LWS_EXTERN struct lws *
wsi_from_fd(const struct lws_context *context, lws_sockfd_type fd);

LWS_EXTERN int
insert_wsi(struct lws_context *context, struct lws *wsi);

LWS_EXTERN int
delete_from_fd(struct lws_context *context, lws_sockfd_type fd);
#else
#define wsi_from_fd(A,B)  A->lws_lookup[B]
#define insert_wsi(A,B)   A->lws_lookup[B->sock]=B
#define delete_from_fd(A,B) A->lws_lookup[B]=0
#endif

LWS_EXTERN int
insert_wsi_socket_into_fds(struct lws_context *context, struct lws *wsi);

LWS_EXTERN int
lws_issue_raw(struct lws *wsi, unsigned char *buf, size_t len);


LWS_EXTERN int
lws_service_timeout_check(struct lws *wsi, unsigned int sec);

LWS_EXTERN struct lws *
lws_client_connect_2(struct lws *wsi);

LWS_VISIBLE struct lws *
lws_client_reset(struct lws *wsi, int ssl, const char *address, int port, const char *path, const char *host);


LWS_EXTERN struct lws *
lws_create_new_server_wsi(struct lws_context *context);

LWS_EXTERN char *
lws_generate_client_handshake(struct lws *wsi, char *pkt);

LWS_EXTERN int
lws_handle_POLLOUT_event(struct lws *wsi, struct lws_pollfd *pollfd);

/*
 * EXTENSIONS
 */

#ifndef LWS_NO_EXTENSIONS
LWS_VISIBLE void
lws_context_init_extensions(struct lws_context_creation_info *info,
			    struct lws_context *context);
LWS_EXTERN int
lws_any_extension_handled(struct lws *wsi,
			  enum lws_extension_callback_reasons r,
			  void *v, size_t len);

LWS_EXTERN int
lws_ext_cb_active(struct lws *wsi, int reason,
				 void *buf, int len);
LWS_EXTERN int
lws_ext_cb_all_exts(struct lws_context *context,
					 struct lws *wsi, int reason,
					 void *arg, int len);

#else
#define lws_any_extension_handled(_a, _b, _c, _d) (0)
#define lws_ext_cb_active(_a, _b, _c, _d) (0)
#define lws_ext_cb_all_exts(_a, _b, _c, _d, _e) (0)
#define lws_issue_raw_ext_access lws_issue_raw
#define lws_context_init_extensions(_a, _b)
#endif

LWS_EXTERN int
lws_client_interpret_server_handshake(struct lws *wsi);

LWS_EXTERN int
lws_rx_sm(struct lws *wsi, unsigned char c);

LWS_EXTERN int
lws_issue_raw_ext_access(struct lws *wsi, unsigned char *buf, size_t len);

LWS_EXTERN void
lws_union_transition(struct lws *wsi, enum connection_mode mode);

LWS_EXTERN int
user_callback_handle_rxflow(lws_callback_function, struct lws *wsi,
			    enum lws_callback_reasons reason, void *user,
			    void *in, size_t len);
#ifdef LWS_USE_HTTP2
LWS_EXTERN struct lws *lws_http2_get_network_wsi(struct lws *wsi);
struct lws * lws_http2_get_nth_child(struct lws *wsi, int n);
LWS_EXTERN int
lws_http2_interpret_settings_payload(struct http2_settings *settings,
				     unsigned char *buf, int len);
LWS_EXTERN void lws_http2_init(struct http2_settings *settings);
LWS_EXTERN int
lws_http2_parser(struct lws *wsi, unsigned char c);
LWS_EXTERN int lws_http2_do_pps_send(struct lws_context *context,
				     struct lws *wsi);
LWS_EXTERN int lws_http2_frame_write(struct lws *wsi, int type, int flags,
				     unsigned int sid, unsigned int len,
				     unsigned char *buf);
LWS_EXTERN struct lws *
lws_http2_wsi_from_id(struct lws *wsi, unsigned int sid);
LWS_EXTERN int lws_hpack_interpret(struct lws *wsi,
				   unsigned char c);
LWS_EXTERN int
lws_add_http2_header_by_name(struct lws *wsi,
			     const unsigned char *name,
			     const unsigned char *value, int length,
			     unsigned char **p, unsigned char *end);
LWS_EXTERN int
lws_add_http2_header_by_token(struct lws *wsi,
			    enum lws_token_indexes token,
			    const unsigned char *value, int length,
			    unsigned char **p, unsigned char *end);
LWS_EXTERN int
lws_add_http2_header_status(struct lws *wsi,
			    unsigned int code, unsigned char **p,
			    unsigned char *end);
LWS_EXTERN
void lws_http2_configure_if_upgraded(struct lws *wsi);
#else
#define lws_http2_configure_if_upgraded(x)
#endif

LWS_EXTERN int
lws_plat_set_socket_options(struct lws_context *context, lws_sockfd_type fd);

LWS_EXTERN int
lws_allocate_header_table(struct lws *wsi);

LWS_EXTERN int
lws_free_header_table(struct lws *wsi);

LWS_EXTERN char *
lws_hdr_simple_ptr(struct lws *wsi, enum lws_token_indexes h);

LWS_EXTERN int
lws_hdr_simple_create(struct lws *wsi, enum lws_token_indexes h, const char *s);

LWS_EXTERN int
lws_ensure_user_space(struct lws *wsi);

LWS_EXTERN int
lws_change_pollfd(struct lws *wsi, int _and, int _or);

#ifndef LWS_NO_SERVER
int lws_context_init_server(struct lws_context_creation_info *info,
			    struct lws_context *context);
LWS_EXTERN int
handshake_0405(struct lws_context *context, struct lws *wsi);
LWS_EXTERN int
lws_interpret_incoming_packet(struct lws *wsi, unsigned char **buf, size_t len);
LWS_EXTERN void
lws_server_get_canonical_hostname(struct lws_context *context,
				  struct lws_context_creation_info *info);
#else
#define lws_context_init_server(_a, _b) (0)
#define lws_interpret_incoming_packet(_a, _b, _c) (0)
#define lws_server_get_canonical_hostname(_a, _b)
#endif

#ifndef LWS_NO_DAEMONIZE
LWS_EXTERN int get_daemonize_pid();
#else
#define get_daemonize_pid() (0)
#endif

#if !defined(MBED_OPERATORS)
LWS_EXTERN int
interface_to_sa(struct lws_context *context, const char *ifname,
		struct sockaddr_in *addr, size_t addrlen);
#endif
LWS_EXTERN void lwsl_emit_stderr(int level, const char *line);

enum lws_ssl_capable_status {
	LWS_SSL_CAPABLE_ERROR = -1,
	LWS_SSL_CAPABLE_MORE_SERVICE = -2,
};

#ifndef LWS_OPENSSL_SUPPORT
#define LWS_SSL_ENABLED(context) (0)
#define lws_context_init_server_ssl(_a, _b) (0)
#define lws_ssl_destroy(_a)
#define lws_context_init_http2_ssl(_a)
#define lws_ssl_capable_read lws_ssl_capable_read_no_ssl
#define lws_ssl_capable_write lws_ssl_capable_write_no_ssl
#define lws_ssl_pending lws_ssl_pending_no_ssl
#define lws_server_socket_service_ssl(_a, _b, _c, _d) (0)
#define lws_ssl_close(_a) (0)
#define lws_ssl_context_destroy(_a)
#define lws_ssl_remove_wsi_from_buffered_list(_a)
#else
#define LWS_SSL_ENABLED(context) (context->use_ssl)
LWS_EXTERN int openssl_websocket_private_data_index;
LWS_EXTERN int
lws_ssl_capable_read(struct lws *wsi, unsigned char *buf, int len);
LWS_EXTERN int
lws_ssl_capable_write(struct lws *wsi, unsigned char *buf, int len);
LWS_EXTERN int
lws_ssl_pending(struct lws *wsi);
LWS_EXTERN int
lws_server_socket_service_ssl(struct lws **wsi, struct lws *new_wsi,
			      lws_sockfd_type accept_fd,
			      struct lws_pollfd *pollfd);
LWS_EXTERN int
lws_ssl_close(struct lws *wsi);
LWS_EXTERN void
lws_ssl_context_destroy(struct lws_context *context);
LWS_VISIBLE void
lws_ssl_remove_wsi_from_buffered_list(struct lws *wsi);
#ifndef LWS_NO_SERVER
LWS_EXTERN int
lws_context_init_server_ssl(struct lws_context_creation_info *info,
		 	    struct lws_context *context);
#else
#define lws_context_init_server_ssl(_a, _b) (0)
#endif
LWS_EXTERN void
lws_ssl_destroy(struct lws_context *context);

/* HTTP2-related */

#ifdef LWS_USE_HTTP2
LWS_EXTERN void
lws_context_init_http2_ssl(struct lws_context *context);
#else
#define lws_context_init_http2_ssl(_a)
#endif
#endif

LWS_EXTERN int
lws_ssl_capable_read_no_ssl(struct lws *wsi, unsigned char *buf, int len);

LWS_EXTERN int
lws_ssl_capable_write_no_ssl(struct lws *wsi, unsigned char *buf, int len);

LWS_EXTERN int
lws_ssl_pending_no_ssl(struct lws *wsi);

#ifndef LWS_NO_CLIENT
LWS_EXTERN int lws_client_socket_service(struct lws_context *context,
					 struct lws *wsi,
					 struct lws_pollfd *pollfd);
#ifdef LWS_OPENSSL_SUPPORT
LWS_EXTERN int
lws_context_init_client_ssl(struct lws_context_creation_info *info,
			    struct lws_context *context);
#else
	#define lws_context_init_client_ssl(_a, _b) (0)
#endif
LWS_EXTERN int
lws_handshake_client(struct lws *wsi, unsigned char **buf, size_t len);
LWS_EXTERN void
lws_decode_ssl_error(void);
#else
#define lws_context_init_client_ssl(_a, _b) (0)
#define lws_handshake_client(_a, _b, _c) (0)
#endif

LWS_EXTERN int
_lws_rx_flow_control(struct lws *wsi);

#ifndef LWS_NO_SERVER
LWS_EXTERN int
lws_server_socket_service(struct lws_context *context, struct lws *wsi,
			  struct lws_pollfd *pollfd);
LWS_EXTERN int
lws_handshake_server(struct lws *wsi, unsigned char **buf, size_t len);
LWS_EXTERN int
_lws_server_listen_accept_flow_control(struct lws_context *context, int on);
#else
#define lws_server_socket_service(_a, _b, _c) (0)
#define lws_handshake_server(_a, _b, _c) (0)
#define _lws_server_listen_accept_flow_control(a, b) (0)
#endif

LWS_EXTERN int
lws_get_addresses(struct lws_context *context, void *ads, char *name,
		  int name_len, char *rip, int rip_len);

/*
 * custom allocator
 */
LWS_EXTERN void*
lws_realloc(void *ptr, size_t size);

LWS_EXTERN void*
lws_zalloc(size_t size);

#define lws_malloc(S)	lws_realloc(NULL, S)
#define lws_free(P)	lws_realloc(P, 0)
#define lws_free_set_NULL(P)	do { lws_realloc(P, 0); (P) = NULL; } while(0)

/* lws_plat_ */
LWS_EXTERN void
lws_plat_delete_socket_from_fds(struct lws_context *context,
				struct lws *wsi, int m);
LWS_EXTERN void
lws_plat_insert_socket_into_fds(struct lws_context *context,
				struct lws *wsi);
LWS_EXTERN void
lws_plat_service_periodic(struct lws_context *context);

LWS_EXTERN int
lws_plat_change_pollfd(struct lws_context *context, struct lws *wsi,
		       struct lws_pollfd *pfd);
LWS_EXTERN int
lws_plat_context_early_init(void);
LWS_EXTERN void
lws_plat_context_early_destroy(struct lws_context *context);
LWS_EXTERN void
lws_plat_context_late_destroy(struct lws_context *context);
LWS_EXTERN int
lws_poll_listen_fd(struct lws_pollfd *fd);
LWS_EXTERN int
lws_plat_service(struct lws_context *context, int timeout_ms);
LWS_EXTERN int
lws_plat_init(struct lws_context *context,
	      struct lws_context_creation_info *info);
LWS_EXTERN void
lws_plat_drop_app_privileges(struct lws_context_creation_info *info);
LWS_EXTERN unsigned long long
time_in_microseconds(void);
LWS_EXTERN const char *
lws_plat_inet_ntop(int af, const void *src, char *dst, int cnt);

LWS_EXTERN int
lws_check_utf8(unsigned char *state, unsigned char *buf, size_t len);

#ifdef __cplusplus
};
#endif
