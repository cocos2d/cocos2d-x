/*
 * libwebsockets - small server side websockets and web server implementation
 *
 * Copyright (C) 2010 - 2013 Andy Green <andy@warmcat.com>
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

/* System introspection configs */
#ifdef CMAKE_BUILD
#include "lws_config.h"
#else
#ifdef WIN32
#define inline __inline
#else
#include "config.h"
#endif
#endif

#if _MSC_VER > 1000 || defined(_WIN32)
#else
#include <unistd.h>
#include <strings.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#ifdef __MINGW64__
#else
#ifdef __MINGW32__
#elif _MSC_VER > 1000 || defined(_WIN32)
#else
#include <netdb.h>
#endif
#endif
#include <stdarg.h>

#include <sys/stat.h>

#ifdef WIN32
#define LWS_NO_DAEMONIZE
#ifndef EWOULDBLOCK
#define EWOULDBLOCK EAGAIN
#endif

#define compatible_close(fd) closesocket(fd);
#ifdef __MINGW64__
#else
#ifdef __MINGW32__
#else
#include <time.h >
#endif
#endif
#include <winsock2.h>
#include <ws2ipdef.h>
#include <windows.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#ifndef LWS_NO_FORK
#ifdef HAVE_SYS_PRCTL_H
#include <sys/prctl.h>
#endif
#endif
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#include <poll.h>
#include <sys/mman.h>
#include <sys/time.h>

#define compatible_close(fd) close(fd);
#endif

#ifdef LWS_OPENSSL_SUPPORT
#ifdef USE_CYASSL
#include <cyassl/openssl/ssl.h>
#include <cyassl/error.h>
unsigned char *
SHA1(const unsigned char *d, size_t n, unsigned char *md);
#else
#include <openssl/ssl.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#endif /* not USE_CYASSL */
#endif

#include "libwebsockets.h"

/*
 * Mac OSX as well as iOS do not define the MSG_NOSIGNAL flag,
 * but happily have something equivalent in the SO_NOSIGPIPE flag.
 */
#ifdef __APPLE__
#define MSG_NOSIGNAL SO_NOSIGPIPE
#endif

#ifndef LWS_MAX_HEADER_LEN
#define LWS_MAX_HEADER_LEN 1024
#endif
#ifndef LWS_MAX_PROTOCOLS
#define LWS_MAX_PROTOCOLS 5
#endif
#ifndef LWS_MAX_EXTENSIONS_ACTIVE
#define LWS_MAX_EXTENSIONS_ACTIVE 3
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
#define LWS_LISTEN_SERVICE_MODULO 10

enum lws_websocket_opcodes_07 {
	LWS_WS_OPCODE_07__CONTINUATION = 0,
	LWS_WS_OPCODE_07__TEXT_FRAME = 1,
	LWS_WS_OPCODE_07__BINARY_FRAME = 2,

	LWS_WS_OPCODE_07__NOSPEC__MUX = 7,

	/* control extensions 8+ */

	LWS_WS_OPCODE_07__CLOSE = 8,
	LWS_WS_OPCODE_07__PING = 9,
	LWS_WS_OPCODE_07__PONG = 0xa,
};


enum lws_connection_states {
	WSI_STATE_HTTP,
	WSI_STATE_HTTP_ISSUING_FILE,
	WSI_STATE_HTTP_HEADERS,
	WSI_STATE_DEAD_SOCKET,
	WSI_STATE_ESTABLISHED,
	WSI_STATE_CLIENT_UNCONNECTED,
	WSI_STATE_RETURNED_CLOSE_ALREADY,
	WSI_STATE_AWAITING_CLOSE_ACK,
};

enum lws_rx_parse_state {
	LWS_RXPS_NEW,

	LWS_RXPS_04_MASK_NONCE_1,
	LWS_RXPS_04_MASK_NONCE_2,
	LWS_RXPS_04_MASK_NONCE_3,

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
	LWS_CONNMODE_HTTP_SERVING,
	LWS_CONNMODE_HTTP_SERVING_ACCEPTED, /* actual HTTP service going on */
	LWS_CONNMODE_PRE_WS_SERVING_ACCEPT,

	LWS_CONNMODE_WS_SERVING,
	LWS_CONNMODE_WS_CLIENT,

	/* transient, ssl delay hiding */
	LWS_CONNMODE_SSL_ACK_PENDING,

	/* transient modes */
	LWS_CONNMODE_WS_CLIENT_WAITING_CONNECT,
	LWS_CONNMODE_WS_CLIENT_WAITING_PROXY_REPLY,
	LWS_CONNMODE_WS_CLIENT_ISSUE_HANDSHAKE,
	LWS_CONNMODE_WS_CLIENT_WAITING_SSL,
	LWS_CONNMODE_WS_CLIENT_WAITING_SERVER_REPLY,
	LWS_CONNMODE_WS_CLIENT_WAITING_EXTENSION_CONNECT,
	LWS_CONNMODE_WS_CLIENT_PENDING_CANDIDATE_CHILD,

	/* special internal types */
	LWS_CONNMODE_SERVER_LISTENER,
};

enum {
	LWS_RXFLOW_ALLOW = (1 << 0),
	LWS_RXFLOW_PENDING_CHANGE = (1 << 1),
};

struct libwebsocket_protocols;
struct libwebsocket;

struct libwebsocket_context {
	struct pollfd *fds;
	struct libwebsocket **lws_lookup; /* fd to wsi */
	int fds_count;
	int max_fds;
	int listen_port;
	char http_proxy_address[128];
	char canonical_hostname[128];
	unsigned int http_proxy_port;
	unsigned int options;
	unsigned long last_timeout_check_s;

	/*
	 * usable by anything in the service code, but only if the scope
	 * does not last longer than the service action (since next service
	 * of any socket can likewise use it and overwrite)
	 */
	unsigned char service_buffer[LWS_MAX_SOCKET_IO_BUF];

	int started_with_parent;

	int fd_random;
	int listen_service_modulo;
	int listen_service_count;
	int listen_service_fd;
	int listen_service_extraseen;

	int ka_time;
	int ka_probes;
	int ka_interval;

#ifdef LWS_LATENCY
	unsigned long worst_latency;
	char worst_latency_info[256];
#endif

#ifdef LWS_OPENSSL_SUPPORT
	int use_ssl;
	SSL_CTX *ssl_ctx;
	SSL_CTX *ssl_client_ctx;
#endif
	struct libwebsocket_protocols *protocols;
	int count_protocols;
#ifndef LWS_NO_EXTENSIONS
	struct libwebsocket_extension *extensions;
#endif
	void *user_space;
};


/*
 * This is totally opaque to code using the library.  It's exported as a
 * forward-reference pointer-only declaration; the user can use the pointer with
 * other APIs to get information out of it.
 */

struct _lws_http_mode_related {
	int fd;
	unsigned long filepos;
	unsigned long filelen;
};

struct lws_fragments {
	unsigned short offset;
	unsigned short len;
	unsigned char next_frag_index;
};

struct allocated_headers {
	unsigned short next_frag_index;
	unsigned short pos;
	unsigned char frag_index[WSI_TOKEN_COUNT];
	struct lws_fragments frags[WSI_TOKEN_COUNT * 2];
	char data[LWS_MAX_HEADER_LEN];
#ifndef LWS_NO_CLIENT
	char initial_handshake_hash_base64[30];
	unsigned short c_port;
#endif
};

struct _lws_header_related {
	struct allocated_headers *ah;
	short lextable_pos;
	unsigned char parser_state; /* enum lws_token_indexes */
};

struct _lws_websocket_related {
	char *rx_user_buffer;
	int rx_user_buffer_head;
	unsigned char frame_masking_nonce_04[4];
	unsigned char frame_mask_index;
	size_t rx_packet_length;
	unsigned char opcode;
	unsigned int final:1;
	unsigned char rsv;
	unsigned int frame_is_binary:1;
	unsigned int all_zero_nonce:1;
	short close_reason; /* enum lws_close_status */
	unsigned char *rxflow_buffer;
	int rxflow_len;
	int rxflow_pos;
	unsigned int rxflow_change_to:2;
	unsigned int this_frame_masked:1;
	unsigned int inside_frame:1; /* next write will be more of frame */
	unsigned int clean_buffer:1; /* buffer not rewritten by extension */
	/* truncated send handling */
	unsigned char *truncated_send_malloc; /* non-NULL means buffering in progress */
	unsigned int truncated_send_offset; /* where we are in terms of spilling */
	unsigned int truncated_send_len; /* how much is buffered */
};

struct libwebsocket {

	/* lifetime members */

	const struct libwebsocket_protocols *protocol;
#ifndef LWS_NO_EXTENSIONS
	struct libwebsocket_extension *
				   active_extensions[LWS_MAX_EXTENSIONS_ACTIVE];
	void *active_extensions_user[LWS_MAX_EXTENSIONS_ACTIVE];
	unsigned char count_active_extensions;
	unsigned int extension_data_pending:1;
#endif
	unsigned char ietf_spec_revision;

	char mode; /* enum connection_mode */
	char state; /* enum lws_connection_states */
	char lws_rx_parse_state; /* enum lws_rx_parse_state */
	char rx_frame_type; /* enum libwebsocket_write_protocol */

	unsigned int hdr_parsing_completed:1;

	char pending_timeout; /* enum pending_timeout */
	unsigned long pending_timeout_limit;

	int sock;
	int position_in_fds_table;
#ifdef LWS_LATENCY
	unsigned long action_start;
	unsigned long latency_start;
#endif

	void *user_space;

	/* members with mutually exclusive lifetimes are unionized */

	union u {
		struct _lws_http_mode_related http;
		struct _lws_header_related hdr;
		struct _lws_websocket_related ws;
	} u;

#ifdef LWS_OPENSSL_SUPPORT
	SSL *ssl;
	BIO *client_bio;
	unsigned int use_ssl:2;
#endif
};

LWS_EXTERN void
libwebsocket_close_and_free_session(struct libwebsocket_context *context,
			       struct libwebsocket *wsi, enum lws_close_status);

#ifndef LWS_LATENCY
static inline void lws_latency(struct libwebsocket_context *context,
		struct libwebsocket *wsi, const char *action,
					 int ret, int completion) { while (0); }
static inline void lws_latency_pre(struct libwebsocket_context *context,
					struct libwebsocket *wsi) { while (0); }
#else
#define lws_latency_pre(_context, _wsi) lws_latency(_context, _wsi, NULL, 0, 0)
extern void
lws_latency(struct libwebsocket_context *context,
			struct libwebsocket *wsi, const char *action,
						       int ret, int completion);
#endif

LWS_EXTERN int
libwebsocket_client_rx_sm(struct libwebsocket *wsi, unsigned char c);

LWS_EXTERN int
libwebsocket_parse(struct libwebsocket *wsi, unsigned char c);

LWS_EXTERN int
libwebsocket_interpret_incoming_packet(struct libwebsocket *wsi,
						unsigned char *buf, size_t len);

LWS_EXTERN int
lws_b64_selftest(void);

LWS_EXTERN struct libwebsocket *
wsi_from_fd(struct libwebsocket_context *context, int fd);

LWS_EXTERN int
insert_wsi_socket_into_fds(struct libwebsocket_context *context,
						      struct libwebsocket *wsi);

LWS_EXTERN int
lws_issue_raw(struct libwebsocket *wsi, unsigned char *buf, size_t len);


LWS_EXTERN int
libwebsocket_service_timeout_check(struct libwebsocket_context *context,
				    struct libwebsocket *wsi, unsigned int sec);

LWS_EXTERN struct libwebsocket *
libwebsocket_client_connect_2(struct libwebsocket_context *context,
	struct libwebsocket *wsi);

LWS_EXTERN struct libwebsocket *
libwebsocket_create_new_server_wsi(struct libwebsocket_context *context);

LWS_EXTERN char *
libwebsockets_generate_client_handshake(struct libwebsocket_context *context,
		struct libwebsocket *wsi, char *pkt);

LWS_EXTERN int
lws_handle_POLLOUT_event(struct libwebsocket_context *context,
			      struct libwebsocket *wsi, struct pollfd *pollfd);
#ifndef LWS_NO_EXTENSIONS
LWS_EXTERN int
lws_any_extension_handled(struct libwebsocket_context *context,
			  struct libwebsocket *wsi,
			  enum libwebsocket_extension_callback_reasons r,
			  void *v, size_t len);

LWS_EXTERN void *
lws_get_extension_user_matching_ext(struct libwebsocket *wsi,
			  struct libwebsocket_extension *ext);
#endif

LWS_EXTERN int
lws_client_interpret_server_handshake(struct libwebsocket_context *context,
		struct libwebsocket *wsi);

LWS_EXTERN int
libwebsocket_rx_sm(struct libwebsocket *wsi, unsigned char c);

LWS_EXTERN int
lws_issue_raw_ext_access(struct libwebsocket *wsi,
						unsigned char *buf, size_t len);

LWS_EXTERN int
_libwebsocket_rx_flow_control(struct libwebsocket *wsi);

LWS_EXTERN int
user_callback_handle_rxflow(callback_function,
		struct libwebsocket_context *context,
			struct libwebsocket *wsi,
			 enum libwebsocket_callback_reasons reason, void *user,
							  void *in, size_t len);

LWS_EXTERN int
lws_set_socket_options(struct libwebsocket_context *context, int fd);

LWS_EXTERN int
lws_allocate_header_table(struct libwebsocket *wsi);

LWS_EXTERN char *
lws_hdr_simple_ptr(struct libwebsocket *wsi, enum lws_token_indexes h);

LWS_EXTERN int
lws_hdr_simple_create(struct libwebsocket *wsi,
				enum lws_token_indexes h, const char *s);

LWS_EXTERN int
libwebsocket_ensure_user_space(struct libwebsocket *wsi);

#ifndef LWS_NO_SERVER
LWS_EXTERN int handshake_0405(struct libwebsocket_context *context,
						      struct libwebsocket *wsi);
#endif

#ifndef LWS_NO_DAEMONIZE
LWS_EXTERN int get_daemonize_pid();
#endif

extern int interface_to_sa(const char *ifname,
		      struct sockaddr_in *addr, size_t addrlen);

#ifndef LWS_OPENSSL_SUPPORT

unsigned char *
SHA1(const unsigned char *d, size_t n, unsigned char *md);

#else

LWS_EXTERN int openssl_websocket_private_data_index;

#endif
