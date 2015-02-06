#include "private-libwebsockets.h"

#include "extension-deflate-frame.h"
#include "extension-deflate-stream.h"

struct libwebsocket_extension libwebsocket_internal_extensions[] = {
#ifdef LWS_EXT_DEFLATE_STREAM
	{
		"deflate-stream",
		lws_extension_callback_deflate_stream,
		sizeof(struct lws_ext_deflate_stream_conn)
	},
#else
	{
		"x-webkit-deflate-frame",
		lws_extension_callback_deflate_frame,
		sizeof(struct lws_ext_deflate_frame_conn)
	},
	{
		"deflate-frame",
		lws_extension_callback_deflate_frame,
		sizeof(struct lws_ext_deflate_frame_conn)
	},
#endif
	{ /* terminator */
		NULL, NULL, 0
	}
};

LWS_VISIBLE struct libwebsocket_extension *libwebsocket_get_internal_extensions()
{
	return libwebsocket_internal_extensions;
}
