
#include <zlib.h>

#define DEFLATE_FRAME_COMPRESSION_LEVEL_SERVER 1
#define DEFLATE_FRAME_COMPRESSION_LEVEL_CLIENT Z_DEFAULT_COMPRESSION

struct lws_ext_deflate_frame_conn {
	z_stream zs_in;
	z_stream zs_out;
	size_t buf_pre_used;
	size_t buf_pre_length;
	size_t buf_in_length;
	size_t buf_out_length;
	int compressed_out;
	unsigned char *buf_pre;
	unsigned char *buf_in;
	unsigned char *buf_out;
};

extern int lws_extension_callback_deflate_frame(
		struct libwebsocket_context *context,
		struct libwebsocket_extension *ext,
		struct libwebsocket *wsi,
		enum libwebsocket_extension_callback_reasons reason,
		void *user, void *in, size_t len);
