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

/*
 * -04 of the protocol (actually the 80th version) has a radically different
 * handshake.  The 04 spec gives the following idea
 *
 *    The handshake from the client looks as follows:
 *
 *      GET /chat HTTP/1.1
 *      Host: server.example.com
 *      Upgrade: websocket
 *      Connection: Upgrade
 *      Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==
 *      Sec-WebSocket-Origin: http://example.com
 *      Sec-WebSocket-Protocol: chat, superchat
 *	Sec-WebSocket-Version: 4
 *
 *  The handshake from the server looks as follows:
 *
 *       HTTP/1.1 101 Switching Protocols
 *       Upgrade: websocket
 *       Connection: Upgrade
 *       Sec-WebSocket-Accept: me89jWimTRKTWwrS3aRrL53YZSo=
 *       Sec-WebSocket-Nonce: AQIDBAUGBwgJCgsMDQ4PEC==
 *       Sec-WebSocket-Protocol: chat
 */

/*
 * We have to take care about parsing because the headers may be split
 * into multiple fragments.  They may contain unknown headers with arbitrary
 * argument lengths.  So, we parse using a single-character at a time state
 * machine that is completely independent of packet size.
 */

LWS_VISIBLE int
libwebsocket_read(struct libwebsocket_context *context,
		     struct libwebsocket *wsi, unsigned char *buf, size_t len)
{
	size_t n;
	struct allocated_headers *ah;
	char *uri_ptr;
	int uri_len;

	switch (wsi->state) {
	case WSI_STATE_HTTP_ISSUING_FILE:
	case WSI_STATE_HTTP:
		wsi->state = WSI_STATE_HTTP_HEADERS;
		wsi->u.hdr.parser_state = WSI_TOKEN_NAME_PART;
		wsi->u.hdr.lextable_pos = 0;
		/* fallthru */
	case WSI_STATE_HTTP_HEADERS:

		lwsl_parser("issuing %d bytes to parser\n", (int)len);

#ifndef LWS_NO_CLIENT
		switch (wsi->mode) {
		case LWS_CONNMODE_WS_CLIENT_WAITING_PROXY_REPLY:
		case LWS_CONNMODE_WS_CLIENT_ISSUE_HANDSHAKE:
		case LWS_CONNMODE_WS_CLIENT_WAITING_SERVER_REPLY:
		case LWS_CONNMODE_WS_CLIENT_WAITING_EXTENSION_CONNECT:
		case LWS_CONNMODE_WS_CLIENT:
			for (n = 0; n < len; n++)
				if (libwebsocket_client_rx_sm(wsi, *buf++)) {
					lwsl_info("client_rx_sm failed\n");
					goto bail;
				}
			return 0;
		default:
			break;
		}
#endif
#ifndef LWS_NO_SERVER
		/* LWS_CONNMODE_WS_SERVING */

		for (n = 0; n < len; n++)
			if (libwebsocket_parse(wsi, *buf++)) {
				lwsl_info("libwebsocket_parse failed\n");
				goto bail_nuke_ah;
			}

		if (wsi->u.hdr.parser_state != WSI_PARSING_COMPLETE)
			break;

		lwsl_parser("libwebsocket_parse sees parsing complete\n");

		wsi->mode = LWS_CONNMODE_PRE_WS_SERVING_ACCEPT;

		/* is this websocket protocol or normal http 1.0? */

		if (!lws_hdr_total_length(wsi, WSI_TOKEN_UPGRADE) ||
			     !lws_hdr_total_length(wsi, WSI_TOKEN_CONNECTION)) {

			/* it's not websocket.... shall we accept it as http? */

			if (!lws_hdr_total_length(wsi, WSI_TOKEN_GET_URI)) {
				lwsl_warn("Missing URI in HTTP request\n");
				goto bail_nuke_ah;
			}

			lwsl_info("HTTP request for '%s'\n",
				lws_hdr_simple_ptr(wsi, WSI_TOKEN_GET_URI));

			if (libwebsocket_ensure_user_space(wsi))
				goto bail_nuke_ah;

			/*
			 * Hm we still need the headers so the
			 * callback can look at leaders like the URI, but we
			 * need to transition to http union state.... hold a
			 * copy of u.hdr.ah and deallocate afterwards
			 */

			ah = wsi->u.hdr.ah;
			uri_ptr = lws_hdr_simple_ptr(wsi, WSI_TOKEN_GET_URI);
			uri_len = lws_hdr_total_length(wsi, WSI_TOKEN_GET_URI);

			/* union transition */
			memset(&wsi->u, 0, sizeof(wsi->u));

			wsi->mode = LWS_CONNMODE_HTTP_SERVING_ACCEPTED;
			wsi->state = WSI_STATE_HTTP;
			n = 0;
			if (wsi->protocol->callback)
				n = wsi->protocol->callback(context, wsi,
				    LWS_CALLBACK_HTTP,
				    wsi->user_space, uri_ptr, uri_len);

			/* now drop the header info we kept a pointer to */
			if (ah)
				free(ah);

			if (n) {
				lwsl_info("LWS_CALLBACK_HTTP closing\n");
				goto bail; /* struct ah ptr already nuked */
			}

			return 0;
		}

		if (!wsi->protocol)
			lwsl_err("NULL protocol at libwebsocket_read\n");

		/*
		 * It's websocket
		 *
		 * Make sure user side is happy about protocol
		 */

		while (wsi->protocol->callback) {

			if (!lws_hdr_total_length(wsi, WSI_TOKEN_PROTOCOL)) {
				if (wsi->protocol->name == NULL)
					break;
			} else
				if (wsi->protocol->name && strcmp(
					lws_hdr_simple_ptr(wsi,
						WSI_TOKEN_PROTOCOL),
						      wsi->protocol->name) == 0)
					break;

			wsi->protocol++;
		}

		/* we didn't find a protocol he wanted? */

		if (wsi->protocol->callback == NULL) {
			if (lws_hdr_simple_ptr(wsi, WSI_TOKEN_PROTOCOL) ==
									 NULL) {
				lwsl_info("no protocol -> prot 0 handler\n");
				wsi->protocol = &context->protocols[0];
			} else {
				lwsl_err("Req protocol %s not supported\n",
				   lws_hdr_simple_ptr(wsi, WSI_TOKEN_PROTOCOL));
				goto bail_nuke_ah;
			}
		}

		/* allocate wsi->user storage */
		if (libwebsocket_ensure_user_space(wsi))
				goto bail_nuke_ah;

		/*
		 * Give the user code a chance to study the request and
		 * have the opportunity to deny it
		 */

		if ((wsi->protocol->callback)(wsi->protocol->owning_server, wsi,
				LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION,
				wsi->user_space,
			      lws_hdr_simple_ptr(wsi, WSI_TOKEN_PROTOCOL), 0)) {
			lwsl_warn("User code denied connection\n");
			goto bail_nuke_ah;
		}


		/*
		 * Perform the handshake according to the protocol version the
		 * client announced
		 */

		switch (wsi->ietf_spec_revision) {
		case 13:
			lwsl_parser("lws_parse calling handshake_04\n");
			if (handshake_0405(context, wsi)) {
				lwsl_info("hs0405 has failed the connection\n");
				goto bail_nuke_ah;
			}
			break;

		default:
			lwsl_warn("Unknown client spec version %d\n",
						       wsi->ietf_spec_revision);
			goto bail_nuke_ah;
		}

		/* drop the header info -- no bail_nuke_ah after this */

		if (wsi->u.hdr.ah)
			free(wsi->u.hdr.ah);

		wsi->mode = LWS_CONNMODE_WS_SERVING;

		/* union transition */
		memset(&wsi->u, 0, sizeof(wsi->u));
		wsi->u.ws.rxflow_change_to = LWS_RXFLOW_ALLOW;

		/*
		 * create the frame buffer for this connection according to the
		 * size mentioned in the protocol definition.  If 0 there, use
		 * a big default for compatibility
		 */

		n = wsi->protocol->rx_buffer_size;
		if (!n)
			n = LWS_MAX_SOCKET_IO_BUF;
		n += LWS_SEND_BUFFER_PRE_PADDING + LWS_SEND_BUFFER_POST_PADDING;
		wsi->u.ws.rx_user_buffer = malloc(n);
		if (!wsi->u.ws.rx_user_buffer) {
			lwsl_err("Out of Mem allocating rx buffer %d\n", n);
			goto bail;
		}
		lwsl_info("Allocating RX buffer %d\n", n);

		if (setsockopt(wsi->sock, SOL_SOCKET, SO_SNDBUF,  &n, sizeof n)) {
			lwsl_warn("Failed to set SNDBUF to %d", n);
			goto bail;
		}

		lwsl_parser("accepted v%02d connection\n",
						       wsi->ietf_spec_revision);
#endif
		break;

	case WSI_STATE_AWAITING_CLOSE_ACK:
	case WSI_STATE_ESTABLISHED:
#ifndef LWS_NO_CLIENT
		switch (wsi->mode) {
		case LWS_CONNMODE_WS_CLIENT:
			for (n = 0; n < len; n++)
				if (libwebsocket_client_rx_sm(
							     wsi, *buf++) < 0) {
					lwsl_info("client rx has bailed\n");
					goto bail;
				}

			return 0;
		default:
			break;
		}
#endif
#ifndef LWS_NO_SERVER
		/* LWS_CONNMODE_WS_SERVING */

		if (libwebsocket_interpret_incoming_packet(wsi, buf, len) < 0) {
			lwsl_info("interpret_incoming_packet has bailed\n");
			goto bail;
		}
#endif
		break;
	default:
		lwsl_err("libwebsocket_read: Unhandled state\n");
		break;
	}

	return 0;

bail_nuke_ah:
	/* drop the header info */
	if (wsi->u.hdr.ah)
		free(wsi->u.hdr.ah);

bail:
	lwsl_info("closing connection at libwebsocket_read bail:\n");

	libwebsocket_close_and_free_session(context, wsi,
						     LWS_CLOSE_STATUS_NOSTATUS);

	return -1;
}
