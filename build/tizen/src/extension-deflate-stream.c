#include "private-libwebsockets.h"
#include "extension-deflate-stream.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define LWS_ZLIB_WINDOW_BITS 15
#define LWS_ZLIB_MEMLEVEL 8

int lws_extension_callback_deflate_stream(
		struct libwebsocket_context *context,
		struct libwebsocket_extension *ext,
		struct libwebsocket *wsi,
			enum libwebsocket_extension_callback_reasons reason,
					       void *user, void *in, size_t len)
{
	struct lws_ext_deflate_stream_conn *conn =
				     (struct lws_ext_deflate_stream_conn *)user;
	int n;
	struct lws_tokens *eff_buf = (struct lws_tokens *)in;

	switch (reason) {

	/*
	 * for deflate-stream, both client and server sides act the same
	 */

	case LWS_EXT_CALLBACK_CLIENT_CONSTRUCT:
	case LWS_EXT_CALLBACK_CONSTRUCT:
		conn->zs_in.zalloc = conn->zs_out.zalloc = Z_NULL;
		conn->zs_in.zfree = conn->zs_out.zfree = Z_NULL;
		conn->zs_in.opaque = conn->zs_out.opaque = Z_NULL;
		n = inflateInit2(&conn->zs_in, -LWS_ZLIB_WINDOW_BITS);
		if (n != Z_OK) {
			lwsl_err("deflateInit returned %d\n", n);
			return 1;
		}
		n = deflateInit2(&conn->zs_out,
				 DEFLATE_STREAM_COMPRESSION_LEVEL, Z_DEFLATED,
				 -LWS_ZLIB_WINDOW_BITS, LWS_ZLIB_MEMLEVEL,
							    Z_DEFAULT_STRATEGY);
		if (n != Z_OK) {
			lwsl_err("deflateInit returned %d\n", n);
			return 1;
		}
		lwsl_ext("zlibs constructed\n");
		conn->remaining_in = 0;
		break;

	case LWS_EXT_CALLBACK_DESTROY:
		(void)inflateEnd(&conn->zs_in);
		(void)deflateEnd(&conn->zs_out);
		lwsl_ext("zlibs destructed\n");
		break;

	case LWS_EXT_CALLBACK_PACKET_RX_PREPARSE:

		/*
		 * inflate the incoming compressed data
		 * Notice, length may be 0 and pointer NULL
		 * in the case we are flushing with nothing new coming in
		 */
		if (conn->remaining_in) {
			conn->zs_in.next_in = conn->buf_in;
			conn->zs_in.avail_in = conn->remaining_in;
			conn->remaining_in = 0;
		} else {
			conn->zs_in.next_in = (unsigned char *)eff_buf->token;
			conn->zs_in.avail_in = eff_buf->token_len;
		}

		conn->zs_in.next_out = conn->buf_out;
		conn->zs_in.avail_out = sizeof(conn->buf_out);

		n = inflate(&conn->zs_in, Z_SYNC_FLUSH);
		switch (n) {
		case Z_NEED_DICT:
		case Z_DATA_ERROR:
		case Z_MEM_ERROR:
			/*
			 * screwed.. close the connection... we will get a
			 * destroy callback to take care of closing nicely
			 */
			lwsl_err("zlib error inflate %d\n", n);
			return -1;
		}

		/* rewrite the buffer pointers and length */

		eff_buf->token = (char *)conn->buf_out;
		eff_buf->token_len =
			sizeof(conn->buf_out) - conn->zs_in.avail_out;

		/* copy avail data if not consumed */
		if (conn->zs_in.avail_in > 0) {
			conn->remaining_in = conn->zs_in.avail_in;
			memcpy(conn->buf_in, conn->zs_in.next_in,
							conn->zs_in.avail_in);
			return 1;
		}

		/*
		 * if we filled the output buffer, signal that we likely have
		 * more and need to be called again
		 */

		if (eff_buf->token_len == sizeof(conn->buf_out))
			return 1;

		/* we don't need calling again until new input data comes */

		return 0;

	case LWS_EXT_CALLBACK_FLUSH_PENDING_TX:
	case LWS_EXT_CALLBACK_PACKET_TX_PRESEND:

		/*
		 * deflate the outgoing compressed data
		 */

		conn->zs_out.next_in = (unsigned char *)eff_buf->token;
		conn->zs_out.avail_in = eff_buf->token_len;

		conn->zs_out.next_out = conn->buf_out;
		conn->zs_out.avail_out = sizeof(conn->buf_out);

		n = Z_PARTIAL_FLUSH;
		if (reason == LWS_EXT_CALLBACK_FLUSH_PENDING_TX)
			n = Z_FULL_FLUSH;

		n = deflate(&conn->zs_out, n);
		if (n == Z_STREAM_ERROR) {
			/*
			 * screwed.. close the connection... we will get a
			 * destroy callback to take care of closing nicely
			 */
			lwsl_ext("zlib error deflate\n");

			return -1;
		}

		/* rewrite the buffer pointers and length */

		eff_buf->token = (char *)conn->buf_out;
		eff_buf->token_len =
				sizeof(conn->buf_out) - conn->zs_out.avail_out;

		/*
		 * if we filled the output buffer, signal that we likely have
		 * more and need to be called again... even in deflate case
		 * we might sometimes need to spill more than came in
		 */

		if (eff_buf->token_len == sizeof(conn->buf_out))
			return 1;

		/* we don't need calling again until new input data comes */

		return 0;

	default:
		break;
	}

	return 0;
}
