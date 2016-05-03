/* lws_config.h  Generated from lws_config.h.in  */

#ifndef NDEBUG
	#ifndef _DEBUG
		#define _DEBUG
	#endif
#endif

/* Define to 1 to use wolfSSL/CyaSSL as a replacement for OpenSSL.
 * LWS_OPENSSL_SUPPORT needs to be set also for this to work. */
/* #undef USE_WOLFSSL */

/* Also define to 1 (in addition to USE_WOLFSSL) when using the
  (older) CyaSSL library */
/* #undef USE_OLD_CYASSL */

/* The Libwebsocket version */
#define LWS_LIBRARY_VERSION "1.6.0"

#define LWS_LIBRARY_VERSION_MAJOR 1
#define LWS_LIBRARY_VERSION_MINOR 6
#define LWS_LIBRARY_VERSION_PATCH 0
/* LWS_LIBRARY_VERSION_NUMBER looks like 1005001 for e.g. version 1.5.1 */
#define LWS_LIBRARY_VERSION_NUMBER (LWS_LIBRARY_VERSION_MAJOR*1000000)+(LWS_LIBRARY_VERSION_MINOR*1000)+LWS_LIBRARY_VERSION_PATCH

/* The current git commit hash that we're building from */
#define LWS_BUILD_HASH "4ea265b"

/* Build with OpenSSL support */
/* #undef LWS_OPENSSL_SUPPORT */

/* The client should load and trust CA root certs it finds in the OS */
#define LWS_SSL_CLIENT_USE_OS_CA_CERTS

/* Sets the path where the client certs should be installed. */
#define LWS_OPENSSL_CLIENT_CERTS "../share"

/* Turn off websocket extensions */
/* #undef LWS_NO_EXTENSIONS */

/* Enable libev io loop */
/* #undef LWS_USE_LIBEV */

/* Build with support for ipv6 */
/* #undef LWS_USE_IPV6 */

/* Build with support for HTTP2 */
/* #undef LWS_USE_HTTP2 */

/* Turn on latency measuring code */
/* #undef LWS_LATENCY */

/* Don't build the daemonizeation api */
#define LWS_NO_DAEMONIZE

/* Build without server support */
#define LWS_NO_SERVER

/* Build without client support */
/* #undef LWS_NO_CLIENT */

/* If we should compile with MinGW support */
/* #undef LWS_MINGW_SUPPORT */

/* Use the BSD getifaddrs that comes with libwebsocket, for uclibc support */
/* #undef LWS_BUILTIN_GETIFADDRS */

/* use SHA1() not internal libwebsockets_SHA1 */
/* #undef LWS_SHA1_USE_OPENSSL_NAME */

/* SSL server using ECDH certificate */
/* #undef LWS_SSL_SERVER_WITH_ECDH_CERT */


