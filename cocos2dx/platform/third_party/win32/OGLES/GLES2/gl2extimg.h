#ifndef __gl2extimg_h_
#define __gl2extimg_h_

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------*
 * IMG extension tokens
 *------------------------------------------------------------------------*/

/* GL_IMG_binary_shader */
#ifndef GL_IMG_binary_shader
#define GL_SGX_BINARY_IMG	0x8C0A
#endif

/* GL_IMG_texture_compression_pvrtc */
#ifndef GL_IMG_texture_compression_pvrtc
#define GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG			0x8C00
#define GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG			0x8C01
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG			0x8C02
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG			0x8C03
#endif


/* GL_IMG_texture_format_BGRA8888 */
#define GL_BGRA							0x80E1

/*------------------------------------------------------------------------*
 * IMG extension functions
 *------------------------------------------------------------------------*/

/* GL_IMG_binary_shader */
#ifndef GL_IMG_binary_shader
#define GL_IMG_binary_shader 1
#endif

/* GL_IMG_texture_compression_pvrtc */
#ifndef GL_IMG_texture_compression_pvrtc
#define GL_IMG_texture_compression_pvrtc 1
#endif

#ifdef __cplusplus
}
#endif

#endif /* __gl2extimg_h_ */
