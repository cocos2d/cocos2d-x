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

int lws_client_socket_service(struct libwebsocket_context *context,
				struct libwebsocket *wsi, struct pollfd *pollfd)
{
	int n;
	char *p = (char *)&context->service_buffer[0];
	int len;
	char c;

	switch (wsi->mode) {

	case LWS_CONNMODE_WS_CLIENT_WAITING_CONNECT:

		/*
		 * we are under PENDING_TIMEOUT_SENT_CLIENT_HANDSHAKE
		 * timeout protection set in client-handshake.c
		 */

               if (libwebsocket_client_connect_2(context, wsi) == NULL) {
			/* closed */
			lwsl_client("closed\n");
			return -1;
		}

		/* either still pending connection, or changed mode */
		return 0;

	case LWS_CONNMODE_WS_CLIENT_WAITING_PROXY_REPLY:

		/* handle proxy hung up on us */

		if (pollfd->revents & (POLLERR | POLLHUP)) {

			lwsl_warn("Proxy connection %p (fd=%d) dead\n",
				(void *)wsi, pollfd->fd);

			libwebsocket_close_and_free_session(context, wsi,
						     LWS_CLOSE_STATUS_NOSTATUS);
			return 0;
		}

		n = recv(wsi->sock, context->service_buffer,
					sizeof(context->service_buffer), 0);
		if (n < 0) {
			
			if (errno == EAGAIN) {
				lwsl_debug(
						   "Proxy read returned EAGAIN... retrying\n");
				return 0;
			}
			
			libwebsocket_close_and_free_session(context, wsi,
						     LWS_CLOSE_STATUS_NOSTATUS);
			lwsl_err("ERROR reading from proxy socket\n");
			return 0;
		}

		context->service_buffer[13] = '\0';
		if (strcmp((char *)context->service_buffer, "HTTP/1.0 200 ")) {
			libwebsocket_close_and_free_session(context, wsi,
						     LWS_CLOSE_STATUS_NOSTATUS);
			lwsl_err("ERROR proxy: %s\n", context->service_buffer);
			return 0;
		}

		/* clear his proxy connection timeout */

		libwebsocket_set_timeout(wsi, NO_PENDING_TIMEOUT, 0);

		/* fallthru */

	case LWS_CONNMODE_WS_CLIENT_ISSUE_HANDSHAKE:

		/*
		 * we are under PENDING_TIMEOUT_SENT_CLIENT_HANDSHAKE
		 * timeout protection set in client-handshake.c
		 */

	#ifdef LWS_OPENSSL_SUPPORT

		/*
		 * take care of our libwebsocket_callback_on_writable
		 * happening at a time when there's no real connection yet
		 */

		pollfd->events &= ~POLLOUT;

		/* external POLL support via protocol 0 */
		context->protocols[0].callback(context, wsi,
			LWS_CALLBACK_CLEAR_MODE_POLL_FD,
			wsi->user_space, (void *)(long)wsi->sock, POLLOUT);

		/* we can retry this... just cook the SSL BIO the first time */

		if (wsi->use_ssl && !wsi->ssl) {

			wsi->ssl = SSL_new(context->ssl_client_ctx);

#ifdef USE_CYASSL
			/*
			 * CyaSSL does certificate verification differently
			 * from OpenSSL.
			 * If we should ignore the certificate, we need to set
			 * this before SSL_new and SSL_connect is called.
			 * Otherwise the connect will simply fail with error
			 * code -155
			 */
			if (wsi->use_ssl == 2)
				CyaSSL_set_verify(wsi->ssl,
							SSL_VERIFY_NONE, NULL);
#endif /* USE_CYASSL */

			wsi->client_bio =
				BIO_new_socket(wsi->sock, BIO_NOCLOSE);
			SSL_set_bio(wsi->ssl, wsi->client_bio, wsi->client_bio);

#ifdef USE_CYASSL
			CyaSSL_set_using_nonblock(wsi->ssl, 1);
#else
			BIO_set_nbio(wsi->client_bio, 1); /* nonblocking */
#endif

			SSL_set_ex_data(wsi->ssl,
					openssl_websocket_private_data_index,
								       context);
		}

		if (wsi->use_ssl) {
			lws_latency_pre(context, wsi);
			n = SSL_connect(wsi->ssl);
			lws_latency(context, wsi,
			  "SSL_connect LWS_CONNMODE_WS_CLIENT_ISSUE_HANDSHAKE",
								      n, n > 0);

			if (n < 0) {
				n = SSL_get_error(wsi->ssl, n);

				if (n == SSL_ERROR_WANT_READ ||
					n == SSL_ERROR_WANT_WRITE) {
					/*
					 * wants us to retry connect due to
					 * state of the underlying ssl layer...
					 * but since it may be stalled on
					 * blocked write, no incoming data may
					 * arrive to trigger the retry.
					 * Force (possibly many times if the SSL
					 * state persists in returning the
					 * condition code, but other sockets
					 * are getting serviced inbetweentimes)
					 * us to get called back when writable.
					 */

					lwsl_info(
					     "SSL_connect WANT_... retrying\n");
					libwebsocket_callback_on_writable(
								  context, wsi);
					
					wsi->mode = LWS_CONNMODE_WS_CLIENT_WAITING_SSL;
					
					return 0; /* no error */
				}
				n = -1;
			}

			if (n <= 0) {
				/*
				 * retry if new data comes until we
				 * run into the connection timeout or win
				 */
				
				n = ERR_get_error();
				if (n != SSL_ERROR_NONE) {
					lwsl_err("SSL connect error %lu: %s\n",
						ERR_get_error(),
						ERR_error_string(ERR_get_error(),
							  (char *)context->service_buffer));
					return 0;
				}
			}
		} else
			wsi->ssl = NULL;

		/* fallthru */
			
	case LWS_CONNMODE_WS_CLIENT_WAITING_SSL:
			
		if (wsi->use_ssl) {
				
			if (wsi->mode == LWS_CONNMODE_WS_CLIENT_WAITING_SSL) {
				lws_latency_pre(context, wsi);
				n = SSL_connect(wsi->ssl);
				lws_latency(context, wsi,
							"SSL_connect LWS_CONNMODE_WS_CLIENT_WAITING_SSL",
							n, n > 0);
				
				if (n < 0) {
					n = SSL_get_error(wsi->ssl, n);
					
					if (n == SSL_ERROR_WANT_READ ||
						n == SSL_ERROR_WANT_WRITE) {
						/*
						 * wants us to retry connect due to
						 * state of the underlying ssl layer...
						 * but since it may be stalled on
						 * blocked write, no incoming data may
						 * arrive to trigger the retry.
						 * Force (possibly many times if the SSL
						 * state persists in returning the
						 * condition code, but other sockets
						 * are getting serviced inbetweentimes)
						 * us to get called back when writable.
						 */
						
						lwsl_info(
								  "SSL_connect WANT_... retrying\n");
						libwebsocket_callback_on_writable(
														  context, wsi);
						
						wsi->mode = LWS_CONNMODE_WS_CLIENT_WAITING_SSL;
						
						return 0; /* no error */
					}
					n = -1;
				}
				
				if (n <= 0) {
					/*
					 * retry if new data comes until we
					 * run into the connection timeout or win
					 */
					n = ERR_get_error();
					if (n != SSL_ERROR_NONE) {
						lwsl_err("SSL connect error %lu: %s\n",
								 ERR_get_error(),
								 ERR_error_string(ERR_get_error(),
												  (char *)context->service_buffer));
						return 0;
					}
				}
			}
			
			#ifndef USE_CYASSL
			/*
			 * See comment above about CyaSSL certificate
			 * verification
			 */
			lws_latency_pre(context, wsi);
			n = SSL_get_verify_result(wsi->ssl);
			lws_latency(context, wsi,
				"SSL_get_verify_result LWS_CONNMODE..HANDSHAKE",
								      n, n > 0);
			if ((n != X509_V_OK) && (
				n != X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT ||
							   wsi->use_ssl != 2)) {

				lwsl_err(
				      "server's cert didn't look good %d\n", n);
				libwebsocket_close_and_free_session(context,
						wsi, LWS_CLOSE_STATUS_NOSTATUS);
				return 0;
			}
#endif /* USE_CYASSL */
		} else
			wsi->ssl = NULL;
#endif

		p = libwebsockets_generate_client_handshake(context, wsi, p);
		if (p == NULL) {
			lwsl_err("Failed to generate handshake for client\n");
			libwebsocket_close_and_free_session(context, wsi,
						     LWS_CLOSE_STATUS_NOSTATUS);
			return 0;
		}

		/* send our request to the server */

		lws_latency_pre(context, wsi);
#ifdef LWS_OPENSSL_SUPPORT
		if (wsi->use_ssl)
			n = SSL_write(wsi->ssl, context->service_buffer,
					   p - (char *)context->service_buffer);
		else
#endif
			n = send(wsi->sock, context->service_buffer,
					p - (char *)context->service_buffer, MSG_NOSIGNAL);
		lws_latency(context, wsi,
			"send or SSL_write LWS_CONNMODE...HANDSHAKE",
								     n, n >= 0);

		if (n < 0) {
			lwsl_debug("ERROR writing to client socket\n");
			libwebsocket_close_and_free_session(context, wsi,
						     LWS_CLOSE_STATUS_NOSTATUS);
			return 0;
		}

		wsi->u.hdr.parser_state = WSI_TOKEN_NAME_PART;
		wsi->u.hdr.lextable_pos = 0;
		wsi->mode = LWS_CONNMODE_WS_CLIENT_WAITING_SERVER_REPLY;
		libwebsocket_set_timeout(wsi,
				PENDING_TIMEOUT_AWAITING_SERVER_RESPONSE,
							      AWAITING_TIMEOUT);
		break;

	case LWS_CONNMODE_WS_CLIENT_WAITING_SERVER_REPLY:

		/* handle server hung up on us */

		if (pollfd->revents & (POLLERR | POLLHUP)) {

			lwsl_debug("Server connection %p (fd=%d) dead\n",
				(void *)wsi, pollfd->fd);

			goto bail3;
		}

		if (!(pollfd->revents & POLLIN))
			break;

		/* interpret the server response */

		/*
		 *  HTTP/1.1 101 Switching Protocols
		 *  Upgrade: websocket
		 *  Connection: Upgrade
		 *  Sec-WebSocket-Accept: me89jWimTRKTWwrS3aRrL53YZSo=
		 *  Sec-WebSocket-Nonce: AQIDBAUGBwgJCgsMDQ4PEC==
		 *  Sec-WebSocket-Protocol: chat
		 */

		/*
		 * we have to take some care here to only take from the
		 * socket bytewise.  The browser may (and has been seen to
		 * in the case that onopen() performs websocket traffic)
		 * coalesce both handshake response and websocket traffic
		 * in one packet, since at that point the connection is
		 * definitively ready from browser pov.
		 */

		len = 1;
		while (wsi->u.hdr.parser_state != WSI_PARSING_COMPLETE &&
								      len > 0) {
#ifdef LWS_OPENSSL_SUPPORT
			if (wsi->use_ssl) {
				len = SSL_read(wsi->ssl, &c, 1);
				if (len < 0) {
					n = SSL_get_error(wsi->ssl, len);
					if (n ==  SSL_ERROR_WANT_READ ||
						     n ==  SSL_ERROR_WANT_WRITE)
						return 0;
				}
			} else
#endif
				len = recv(wsi->sock, &c, 1, 0);

			if (len < 0) {
				lwsl_warn("error on parsing recv\n");
				goto bail3;
			}

			if (libwebsocket_parse(wsi, c)) {
				lwsl_warn("problems parsing header\n");
				goto bail3;
			}
		}

		/*
		 * hs may also be coming in multiple packets, there is a 5-sec
		 * libwebsocket timeout still active here too, so if parsing did
		 * not complete just wait for next packet coming in this state
		 */

		if (wsi->u.hdr.parser_state != WSI_PARSING_COMPLETE)
			break;

		/*
		 * otherwise deal with the handshake.  If there's any
		 * packet traffic already arrived we'll trigger poll() again
		 * right away and deal with it that way
		 */

		return lws_client_interpret_server_handshake(context, wsi);

bail3:
		lwsl_info(
			"closing connection at LWS_CONNMODE...SERVER_REPLY\n");
		libwebsocket_close_and_free_session(context, wsi,
						    LWS_CLOSE_STATUS_NOSTATUS);
		return -1;

	case LWS_CONNMODE_WS_CLIENT_WAITING_EXTENSION_CONNECT:
		lwsl_ext("LWS_CONNMODE_WS_CLIENT_WAITING_EXTENSION_CONNECT\n");
		break;

	case LWS_CONNMODE_WS_CLIENT_PENDING_CANDIDATE_CHILD:
		lwsl_ext("LWS_CONNMODE_WS_CLIENT_PENDING_CANDIDATE_CHILD\n");
		break;
	default:
		break;
	}

	return 0;
}


/*
 * In-place str to lower case
 */

static void
strtolower(char *s)
{
	while (*s) {
		*s = tolower((int)*s);
		s++;
	}
}

int
lws_client_interpret_server_handshake(struct libwebsocket_context *context,
		struct libwebsocket *wsi)
{
	const char *pc;
	int okay = 0;
	char *p;
	int len;
#ifndef LWS_NO_EXTENSIONS
	char ext_name[128];
	struct libwebsocket_extension *ext;
	void *v;
	int more = 1;
	const char *c;
#endif
	int n;
	int close_reason = LWS_CLOSE_STATUS_PROTOCOL_ERR;

	/*
	 * well, what the server sent looked reasonable for syntax.
	 * Now let's confirm it sent all the necessary headers
	 */

	if (lws_hdr_total_length(wsi, WSI_TOKEN_ACCEPT) == 0) {
		lwsl_info("no ACCEPT\n");
		goto bail3;
	}

	p = lws_hdr_simple_ptr(wsi, WSI_TOKEN_HTTP);
	if (!p) {
		lwsl_info("no URI\n");
		goto bail3;
	}
	if (p && strncmp(p, "101", 3)) {
		lwsl_warn(
		       "lws_client_handshake: got bad HTTP response '%s'\n", p);
		goto bail3;
	}

	p = lws_hdr_simple_ptr(wsi, WSI_TOKEN_UPGRADE);
	if (!p) {
		lwsl_info("no UPGRADE\n");
		goto bail3;
	}
	strtolower(p);
	if (strcmp(p, "websocket")) {
		lwsl_warn(
		      "lws_client_handshake: got bad Upgrade header '%s'\n", p);
		goto bail3;
	}

	p = lws_hdr_simple_ptr(wsi, WSI_TOKEN_CONNECTION);
	if (!p) {
		lwsl_info("no Connection hdr\n");
		goto bail3;
	}
	strtolower(p);
	if (strcmp(p, "upgrade")) {
		lwsl_warn("lws_client_int_s_hs: bad header %s\n", p);
		goto bail3;
	}

	pc = lws_hdr_simple_ptr(wsi, _WSI_TOKEN_CLIENT_SENT_PROTOCOLS);
	if (pc == NULL)
		lwsl_parser("lws_client_int_s_hs: no protocol list\n");
	else
		lwsl_parser("lws_client_int_s_hs: protocol list '%s'\n", pc);

	/*
	 * confirm the protocol the server wants to talk was in the list
	 * of protocols we offered
	 */

	len = lws_hdr_total_length(wsi, WSI_TOKEN_PROTOCOL);
	if (!len) {

		lwsl_info("lws_client_int_s_hs: WSI_TOKEN_PROTOCOL is null\n");
		/*
		 * no protocol name to work from,
		 * default to first protocol
		 */
		wsi->protocol = &context->protocols[0];
		goto check_extensions;
	}

	p = lws_hdr_simple_ptr(wsi, WSI_TOKEN_PROTOCOL);
	len = strlen(p);

	while (*pc && !okay) {
		if (!strncmp(pc, p, len) &&
					  (pc[len] == ',' || pc[len] == '\0')) {
			okay = 1;
			continue;
		}
		while (*pc && *pc != ',')
			pc++;
		while (*pc && *pc != ' ')
			pc++;
	}

	if (!okay) {
		lwsl_err("lws_client_int_s_hs: got bad protocol %s\n", p);
		goto bail2;
	}

	/*
	 * identify the selected protocol struct and set it
	 */
	n = 0;
	wsi->protocol = NULL;
	while (context->protocols[n].callback && !wsi->protocol) {
		if (strcmp(p, context->protocols[n].name) == 0) {
			wsi->protocol = &context->protocols[n];
			break;
		}
		n++;
	}

	if (wsi->protocol == NULL) {
		lwsl_err("lws_client_int_s_hs: fail protocol %s\n", p);
		goto bail2;
	}


check_extensions:
#ifndef LWS_NO_EXTENSIONS
	/* instantiate the accepted extensions */

	if (!lws_hdr_total_length(wsi, WSI_TOKEN_EXTENSIONS)) {
		lwsl_ext("no client extenstions allowed by server\n");
		goto check_accept;
	}

	/*
	 * break down the list of server accepted extensions
	 * and go through matching them or identifying bogons
	 */

	if (lws_hdr_copy(wsi, (char *)context->service_buffer,
		   sizeof(context->service_buffer), WSI_TOKEN_EXTENSIONS) < 0) {
		lwsl_warn("ext list from server failed to copy\n");
		goto bail2;
	}

	c = (char *)context->service_buffer;
	n = 0;
	while (more) {

		if (*c && (*c != ',' && *c != ' ' && *c != '\t')) {
			ext_name[n] = *c++;
			if (n < sizeof(ext_name) - 1)
				n++;
			continue;
		}
		ext_name[n] = '\0';
		if (!*c)
			more = 0;
		else {
			c++;
			if (!n)
				continue;
		}

		/* check we actually support it */

		lwsl_ext("checking client ext %s\n", ext_name);

		n = 0;
		ext = wsi->protocol->owning_server->extensions;
		while (ext && ext->callback) {

			if (strcmp(ext_name, ext->name)) {
				ext++;
				continue;
			}

			n = 1;

			lwsl_ext("instantiating client ext %s\n", ext_name);

			/* instantiate the extension on this conn */

			wsi->active_extensions_user[
				wsi->count_active_extensions] =
					 malloc(ext->per_session_data_size);
			if (wsi->active_extensions_user[
				wsi->count_active_extensions] == NULL) {
				lwsl_err("Out of mem\n");
				goto bail2;
			}
			memset(wsi->active_extensions_user[
				wsi->count_active_extensions], 0,
						    ext->per_session_data_size);
			wsi->active_extensions[
				  wsi->count_active_extensions] = ext;

			/* allow him to construct his context */

			ext->callback(wsi->protocol->owning_server,
				ext, wsi,
				   LWS_EXT_CALLBACK_CLIENT_CONSTRUCT,
					wsi->active_extensions_user[
					 wsi->count_active_extensions],
								   NULL, 0);

			wsi->count_active_extensions++;

			ext++;
		}

		if (n == 0) {
			lwsl_warn("Unknown ext '%s'!\n", ext_name);
			goto bail2;
		}

		n = 0;
	}

check_accept:
#endif

	/*
	 * Confirm his accept token is the one we precomputed
	 */

	p = lws_hdr_simple_ptr(wsi, WSI_TOKEN_ACCEPT);
	if (strcmp(p, wsi->u.hdr.ah->initial_handshake_hash_base64)) {
		lwsl_warn("lws_client_int_s_hs: accept %s wrong vs %s\n", p,
				  wsi->u.hdr.ah->initial_handshake_hash_base64);
		goto bail2;
	}

	/* allocate the per-connection user memory (if any) */
	if (libwebsocket_ensure_user_space(wsi)) {
		lwsl_err("Problem allocating wsi user mem\n");
		goto bail2;
	}

	/*
	 * we seem to be good to go, give client last chance to check
	 * headers and OK it
	 */

	wsi->protocol->callback(context, wsi,
				LWS_CALLBACK_CLIENT_FILTER_PRE_ESTABLISH,
						     wsi->user_space, NULL, 0);

	/* clear his proxy connection timeout */

	libwebsocket_set_timeout(wsi, NO_PENDING_TIMEOUT, 0);

	/* free up his parsing allocations */
	if (wsi->u.hdr.ah)
		free(wsi->u.hdr.ah);

	/* mark him as being alive */

	wsi->state = WSI_STATE_ESTABLISHED;
	wsi->mode = LWS_CONNMODE_WS_CLIENT;

	/* union transition */

	memset(&wsi->u, 0, sizeof(wsi->u));

	wsi->u.ws.rxflow_change_to = LWS_RXFLOW_ALLOW;

	/*
	 * create the frame buffer for this connection according to the
	 * size mentioned in the protocol definition.  If 0 there, then
	 * use a big default for compatibility
	 */

	n = wsi->protocol->rx_buffer_size;
	if (!n)
		n = LWS_MAX_SOCKET_IO_BUF;
	n += LWS_SEND_BUFFER_PRE_PADDING + LWS_SEND_BUFFER_POST_PADDING;
	wsi->u.ws.rx_user_buffer = malloc(n);
	if (!wsi->u.ws.rx_user_buffer) {
		lwsl_err("Out of Mem allocating rx buffer %d\n", n);
		goto bail2;
	}
	lwsl_info("Allocating client RX buffer %d\n", n);

	if (setsockopt(wsi->sock, SOL_SOCKET, SO_SNDBUF,  &n, sizeof n)) {
		lwsl_warn("Failed to set SNDBUF to %d", n);
		goto bail3;
	}

	lwsl_debug("handshake OK for protocol %s\n", wsi->protocol->name);

	/* call him back to inform him he is up */

	wsi->protocol->callback(context, wsi,
				LWS_CALLBACK_CLIENT_ESTABLISHED,
						     wsi->user_space, NULL, 0);
#ifndef LWS_NO_EXTENSIONS
	/*
	 * inform all extensions, not just active ones since they
	 * already know
	 */

	ext = context->extensions;

	while (ext && ext->callback) {
		v = NULL;
		for (n = 0; n < wsi->count_active_extensions; n++)
			if (wsi->active_extensions[n] == ext)
				v = wsi->active_extensions_user[n];

		ext->callback(context, ext, wsi,
			  LWS_EXT_CALLBACK_ANY_WSI_ESTABLISHED, v, NULL, 0);
		ext++;
	}
#endif

	return 0;

bail3:
	free(wsi->u.ws.rx_user_buffer);
	wsi->u.ws.rx_user_buffer = NULL;
	close_reason = LWS_CLOSE_STATUS_NOSTATUS;

bail2:
	if (wsi->protocol)
		wsi->protocol->callback(context, wsi,
			LWS_CALLBACK_CLIENT_CONNECTION_ERROR,
						      wsi->user_space, NULL, 0);

	lwsl_info("closing connection due to bail2 connection error\n");

	/* free up his parsing allocations */

	if (wsi->u.hdr.ah)
		free(wsi->u.hdr.ah);

	libwebsocket_close_and_free_session(context, wsi, close_reason);

	return 1;
}


char *
libwebsockets_generate_client_handshake(struct libwebsocket_context *context,
		struct libwebsocket *wsi, char *pkt)
{
	char buf[128];
	char hash[20];
	char key_b64[40];
	char *p = pkt;
	int n;
#ifndef LWS_NO_EXTENSIONS
	struct libwebsocket_extension *ext;
	struct libwebsocket_extension *ext1;
	int ext_count = 0;
#endif

	/*
	 * create the random key
	 */

	n = libwebsockets_get_random(context, hash, 16);
	if (n != 16) {
		lwsl_err("Unable to read from random dev %s\n",
						SYSTEM_RANDOM_FILEPATH);
		libwebsocket_close_and_free_session(context, wsi,
					     LWS_CLOSE_STATUS_NOSTATUS);
		return NULL;
	}

	lws_b64_encode_string(hash, 16, key_b64, sizeof(key_b64));

	/*
	 * 00 example client handshake
	 *
	 * GET /socket.io/websocket HTTP/1.1
	 * Upgrade: WebSocket
	 * Connection: Upgrade
	 * Host: 127.0.0.1:9999
	 * Origin: http://127.0.0.1
	 * Sec-WebSocket-Key1: 1 0 2#0W 9 89 7  92 ^
	 * Sec-WebSocket-Key2: 7 7Y 4328 B2v[8(z1
	 * Cookie: socketio=websocket
	 *
	 * (Á®Ä0¶†≥
	 *
	 * 04 example client handshake
	 *
	 * GET /chat HTTP/1.1
	 * Host: server.example.com
	 * Upgrade: websocket
	 * Connection: Upgrade
	 * Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==
	 * Sec-WebSocket-Origin: http://example.com
	 * Sec-WebSocket-Protocol: chat, superchat
	 * Sec-WebSocket-Version: 4
	 */

	p += sprintf(p, "GET %s HTTP/1.1\x0d\x0a",
				lws_hdr_simple_ptr(wsi, _WSI_TOKEN_CLIENT_URI));

	p += sprintf(p,
		"Pragma: no-cache\x0d\x0a""Cache-Control: no-cache\x0d\x0a");

	p += sprintf(p, "Host: %s\x0d\x0a",
			       lws_hdr_simple_ptr(wsi, _WSI_TOKEN_CLIENT_HOST));
	p += sprintf(p,
"Upgrade: websocket\x0d\x0a""Connection: Upgrade\x0d\x0a""Sec-WebSocket-Key: ");
	strcpy(p, key_b64);
	p += strlen(key_b64);
	p += sprintf(p, "\x0d\x0a");
	if (lws_hdr_simple_ptr(wsi, _WSI_TOKEN_CLIENT_ORIGIN))
		p += sprintf(p, "Origin: http://%s\x0d\x0a",
			     lws_hdr_simple_ptr(wsi, _WSI_TOKEN_CLIENT_ORIGIN));

	if (lws_hdr_simple_ptr(wsi, _WSI_TOKEN_CLIENT_SENT_PROTOCOLS))
		p += sprintf(p, "Sec-WebSocket-Protocol: %s\x0d\x0a",
		     lws_hdr_simple_ptr(wsi, _WSI_TOKEN_CLIENT_SENT_PROTOCOLS));

	/* tell the server what extensions we could support */

	p += sprintf(p, "Sec-WebSocket-Extensions: ");
#ifndef LWS_NO_EXTENSIONS
	ext = context->extensions;
	while (ext && ext->callback) {

		n = 0;
		ext1 = context->extensions;

		while (ext1 && ext1->callback) {
			n |= ext1->callback(context, ext1, wsi,
				LWS_EXT_CALLBACK_CHECK_OK_TO_PROPOSE_EXTENSION,
					NULL, (char *)ext->name, 0);

			ext1++;
		}

		if (n) { /* an extension vetos us */
			lwsl_ext("ext %s vetoed\n", (char *)ext->name);
			ext++;
			continue;
		}

		n = context->protocols[0].callback(context, wsi,
			LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED,
				wsi->user_space, (char *)ext->name, 0);

		/*
		 * zero return from callback means
		 * go ahead and allow the extension,
		 * it's what we get if the callback is
		 * unhandled
		 */

		if (n) {
			ext++;
			continue;
		}

		/* apply it */

		if (ext_count)
			*p++ = ',';
		p += sprintf(p, "%s", ext->name);
		ext_count++;

		ext++;
	}
#endif
	p += sprintf(p, "\x0d\x0a");

	if (wsi->ietf_spec_revision)
		p += sprintf(p, "Sec-WebSocket-Version: %d\x0d\x0a",
					       wsi->ietf_spec_revision);

	/* give userland a chance to append, eg, cookies */

	context->protocols[0].callback(context, wsi,
		LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER,
		NULL, &p, (pkt + sizeof(context->service_buffer)) - p - 12);

	p += sprintf(p, "\x0d\x0a");

	/* prepare the expected server accept response */

	key_b64[39] = '\0'; /* enforce composed length below buf sizeof */
	n = sprintf(buf, "%s258EAFA5-E914-47DA-95CA-C5AB0DC85B11", key_b64);

	SHA1((unsigned char *)buf, n, (unsigned char *)hash);

	lws_b64_encode_string(hash, 20,
			wsi->u.hdr.ah->initial_handshake_hash_base64,
			  sizeof(wsi->u.hdr.ah->initial_handshake_hash_base64));

	return p;
}

