/*
 * libwebsockets - small server side websockets and web server implementation
 *
 * Copyright (C) 2010-2013 Andy Green <andy@warmcat.com>
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


#include "private-libwebsockets.h"

#ifdef WIN32
#include <tchar.h>
#include <io.h>
#else
#ifdef LWS_BUILTIN_GETIFADDRS
#include <getifaddrs.h>
#else
#include <ifaddrs.h>
#endif
#include <sys/un.h>
#include <sys/socket.h>
#include <netdb.h>
#endif

#ifdef LWS_OPENSSL_SUPPORT

static void
libwebsockets_decode_ssl_error(void)
{
	char buf[256];
	u_long err;

	while ((err = ERR_get_error()) != 0) {
		ERR_error_string_n(err, buf, sizeof(buf));
		lwsl_err("*** %lu %s\n", err, buf);
	}
}
#endif

int
interface_to_sa(const char *ifname, struct sockaddr_in *addr, size_t addrlen)
{
	int rc = -1;
#ifdef WIN32
	/* TODO */
#else
	struct ifaddrs *ifr;
	struct ifaddrs *ifc;
	struct sockaddr_in *sin;

	getifaddrs(&ifr);
	for (ifc = ifr; ifc != NULL; ifc = ifc->ifa_next) {
		if (strcmp(ifc->ifa_name, ifname))
			continue;
		if (ifc->ifa_addr == NULL)
			continue;
		sin = (struct sockaddr_in *)ifc->ifa_addr;
		if (sin->sin_family != AF_INET)
			continue;
		memcpy(addr, sin, addrlen);
		rc = 0;
	}

	freeifaddrs(ifr);
#endif
	return rc;
}

struct libwebsocket *
libwebsocket_create_new_server_wsi(struct libwebsocket_context *context)
{
	struct libwebsocket *new_wsi;

	new_wsi = (struct libwebsocket *)malloc(sizeof(struct libwebsocket));
	if (new_wsi == NULL) {
		lwsl_err("Out of memory for new connection\n");
		return NULL;
	}

	memset(new_wsi, 0, sizeof(struct libwebsocket));
#ifndef LWS_NO_EXTENSIONS
	new_wsi->count_active_extensions = 0;
#endif
	new_wsi->pending_timeout = NO_PENDING_TIMEOUT;

	/* intialize the instance struct */

	new_wsi->state = WSI_STATE_HTTP;
	new_wsi->mode = LWS_CONNMODE_HTTP_SERVING;
	new_wsi->hdr_parsing_completed = 0;

	if (lws_allocate_header_table(new_wsi)) {
		free(new_wsi);
		return NULL;
	}

	/*
	 * these can only be set once the protocol is known
	 * we set an unestablished connection's protocol pointer
	 * to the start of the supported list, so it can look
	 * for matching ones during the handshake
	 */
	new_wsi->protocol = context->protocols;
	new_wsi->user_space = NULL;
	new_wsi->ietf_spec_revision = 0;

	return new_wsi;
}

int lws_server_socket_service(struct libwebsocket_context *context,
			struct libwebsocket *wsi, struct pollfd *pollfd)
{
	struct libwebsocket *new_wsi;
	int accept_fd;
	socklen_t clilen;
	struct sockaddr_in cli_addr;
	int n;
	ssize_t len;
#ifdef LWS_OPENSSL_SUPPORT
	int m;
#ifndef USE_CYASSL
	BIO *bio;
#endif
#endif

	switch (wsi->mode) {

	case LWS_CONNMODE_HTTP_SERVING:
	case LWS_CONNMODE_HTTP_SERVING_ACCEPTED:

		/* handle http headers coming in */

		/* any incoming data ready? */

		if (pollfd->revents & POLLIN) {

	#ifdef LWS_OPENSSL_SUPPORT
			if (wsi->ssl)
				len = SSL_read(wsi->ssl,
					context->service_buffer,
					       sizeof(context->service_buffer));
			else
	#endif
				len = recv(pollfd->fd,
					context->service_buffer,
					sizeof(context->service_buffer), 0);

			if (len < 0) {
				lwsl_debug("Socket read returned %d\n", len);
				if (errno != EINTR && errno != EAGAIN)
					libwebsocket_close_and_free_session(
						context, wsi,
						LWS_CLOSE_STATUS_NOSTATUS);
				return 0;
			}
			if (!len) {
				lwsl_info("lws_server_skt_srv: read 0 len\n");
				/* lwsl_info("   state=%d\n", wsi->state); */
				if (!wsi->hdr_parsing_completed)
					free(wsi->u.hdr.ah);
				libwebsocket_close_and_free_session(
				       context, wsi, LWS_CLOSE_STATUS_NOSTATUS);
				return 0;
			}

			n = libwebsocket_read(context, wsi,
						context->service_buffer, len);
			if (n < 0)
				/* we closed wsi */
				return 0;
		}

		/* this handles POLLOUT for http serving fragments */

		if (!(pollfd->revents & POLLOUT))
			break;

		/* one shot */
		pollfd->events &= ~POLLOUT;

		if (wsi->state != WSI_STATE_HTTP_ISSUING_FILE) {
			n = user_callback_handle_rxflow(
					wsi->protocol->callback,
					wsi->protocol->owning_server,
					wsi, LWS_CALLBACK_HTTP_WRITEABLE,
					wsi->user_space,
					NULL,
					0);
			if (n < 0)
				libwebsocket_close_and_free_session(
				       context, wsi, LWS_CLOSE_STATUS_NOSTATUS);
			break;
		}

		/* nonzero for completion or error */
		if (libwebsockets_serve_http_file_fragment(context, wsi))
			libwebsocket_close_and_free_session(context, wsi,
					       LWS_CLOSE_STATUS_NOSTATUS);
		break;

	case LWS_CONNMODE_SERVER_LISTENER:

		/* pollin means a client has connected to us then */

		if (!(pollfd->revents & POLLIN))
			break;

		/* listen socket got an unencrypted connection... */

		clilen = sizeof(cli_addr);
		lws_latency_pre(context, wsi);
		accept_fd  = accept(pollfd->fd, (struct sockaddr *)&cli_addr,
								       &clilen);
		lws_latency(context, wsi,
			"unencrypted accept LWS_CONNMODE_SERVER_LISTENER",
						     accept_fd, accept_fd >= 0);
		if (accept_fd < 0) {
			if (errno == EAGAIN || errno == EWOULDBLOCK) {
				lwsl_debug("accept asks to try again\n");
				break;
			}
			lwsl_warn("ERROR on accept: %s\n", strerror(errno));
			break;
		}

		lws_set_socket_options(context, accept_fd);

		/*
		 * look at who we connected to and give user code a chance
		 * to reject based on client IP.  There's no protocol selected
		 * yet so we issue this to protocols[0]
		 */

		if ((context->protocols[0].callback)(context, wsi,
				LWS_CALLBACK_FILTER_NETWORK_CONNECTION,
					   NULL, (void *)(long)accept_fd, 0)) {
			lwsl_debug("Callback denied network connection\n");
			compatible_close(accept_fd);
			break;
		}

		new_wsi = libwebsocket_create_new_server_wsi(context);
		if (new_wsi == NULL) {
			compatible_close(accept_fd);
			break;
		}

		new_wsi->sock = accept_fd;

#ifdef LWS_OPENSSL_SUPPORT
		new_wsi->ssl = NULL;
		if (!context->use_ssl) {
#endif

			lwsl_debug("accepted new conn  port %u on fd=%d\n",
					  ntohs(cli_addr.sin_port), accept_fd);

			insert_wsi_socket_into_fds(context, new_wsi);
			break;
#ifdef LWS_OPENSSL_SUPPORT
		}

		new_wsi->ssl = SSL_new(context->ssl_ctx);
		if (new_wsi->ssl == NULL) {
			lwsl_err("SSL_new failed: %s\n",
			    ERR_error_string(SSL_get_error(
			    new_wsi->ssl, 0), NULL));
			    libwebsockets_decode_ssl_error();
			free(new_wsi);
			compatible_close(accept_fd);
			break;
		}

		SSL_set_ex_data(new_wsi->ssl,
			openssl_websocket_private_data_index, context);

		SSL_set_fd(new_wsi->ssl, accept_fd);

		#ifdef USE_CYASSL
		CyaSSL_set_using_nonblock(new_wsi->ssl, 1);
		#else
		bio = SSL_get_rbio(new_wsi->ssl);
		if (bio)
			BIO_set_nbio(bio, 1); /* nonblocking */
		else
			lwsl_notice("NULL rbio\n");
		bio = SSL_get_wbio(new_wsi->ssl);
		if (bio)
			BIO_set_nbio(bio, 1); /* nonblocking */
		else
			lwsl_notice("NULL rbio\n");
		#endif

		/*
		 * we are not accepted yet, but we need to enter ourselves
		 * as a live connection.  That way we can retry when more
		 * pieces come if we're not sorted yet
		 */

		wsi = new_wsi;
		wsi->mode = LWS_CONNMODE_SSL_ACK_PENDING;
		insert_wsi_socket_into_fds(context, wsi);

		libwebsocket_set_timeout(wsi, PENDING_TIMEOUT_SSL_ACCEPT,
							AWAITING_TIMEOUT);

		lwsl_info("inserted SSL accept into fds, trying SSL_accept\n");

		/* fallthru */

	case LWS_CONNMODE_SSL_ACK_PENDING:

		pollfd->events &= ~POLLOUT;

		/* external POLL support via protocol 0 */
		context->protocols[0].callback(context, wsi,
			LWS_CALLBACK_CLEAR_MODE_POLL_FD,
			wsi->user_space, (void *)(long)wsi->sock, POLLOUT);

		lws_latency_pre(context, wsi);
		n = SSL_accept(wsi->ssl);
		lws_latency(context, wsi,
			"SSL_accept LWS_CONNMODE_SSL_ACK_PENDING\n", n, n == 1);

		if (n != 1) {
			m = SSL_get_error(wsi->ssl, n);
			lwsl_debug("SSL_accept failed %d / %s\n",
						  m, ERR_error_string(m, NULL));

			if (m == SSL_ERROR_WANT_READ) {
				context->fds[
				   wsi->position_in_fds_table].events |= POLLIN;

				/* external POLL support via protocol 0 */
				context->protocols[0].callback(context, wsi,
					LWS_CALLBACK_SET_MODE_POLL_FD,
					wsi->user_space,
					(void *)(long)wsi->sock, POLLIN);
				lwsl_info("SSL_ERROR_WANT_READ\n");
				break;
			}
			if (m == SSL_ERROR_WANT_WRITE) {
				context->fds[
				  wsi->position_in_fds_table].events |= POLLOUT;

				/* external POLL support via protocol 0 */
				context->protocols[0].callback(context, wsi,
					LWS_CALLBACK_SET_MODE_POLL_FD,
					wsi->user_space,
					(void *)(long)wsi->sock, POLLOUT);
				break;
			}
			lwsl_debug("SSL_accept failed skt %u: %s\n",
			      pollfd->fd,
			      ERR_error_string(m, NULL));
			libwebsocket_close_and_free_session(context, wsi,
						     LWS_CLOSE_STATUS_NOSTATUS);
			break;
		}

		/* OK, we are accepted */

		libwebsocket_set_timeout(wsi, NO_PENDING_TIMEOUT, 0);

		wsi->mode = LWS_CONNMODE_HTTP_SERVING;

		lwsl_debug("accepted new SSL conn\n");
		break;
#endif

	default:
		break;
	}
	return 0;
}

