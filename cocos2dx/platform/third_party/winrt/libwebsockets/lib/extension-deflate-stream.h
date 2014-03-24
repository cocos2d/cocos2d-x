
#include <zlib.h>

#define DEFLATE_STREAM_CHUNK 128
#define DEFLATE_STREAM_COMPRESSION_LEVEL 1

struct lws_ext_deflate_stream_conn {
	z_stream zs_in;
	z_stream zs_out;
	int remaining_in;
	unsigned char buf_in[LWS_MAX_SOCKET_IO_BUF];
	unsigned char buf_out[LWS_MAX_SOCKET_IO_BUF];
};

extern int lws_extension_callback_deflate_stream(
		struct libwebsocket_context *context,
		struct libwebsocket_extension *ext,
		struct libwebsocket *wsi,
		enum libwebsocket_extension_callback_reasons reason,
					      void *user, void *in, size_t len);
