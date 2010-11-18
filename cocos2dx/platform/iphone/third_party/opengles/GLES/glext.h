/*
	Copyright:  (c) 2006-2008 by Apple Computer, Inc., all rights reserved.
*/

#ifndef ES1_GLEXT_H_GUARD
#define ES1_GLEXT_H_GUARD

#include <OpenGLES/ES1/gl.h>
#include <Availability.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
** License Applicability. Except to the extent portions of this file are
** made subject to an alternative license as permitted in the SGI Free
** Software License B, Version 1.0 (the "License"), the contents of this
** file are subject only to the provisions of the License. You may not use
** this file except in compliance with the License. You may obtain a copy
** of the License at Silicon Graphics, Inc., attn: Legal Services, 1600
** Amphitheatre Parkway, Mountain View, CA 94043-1351, or at:
**
** http://oss.sgi.com/projects/FreeB
**
** Note that, as provided in the License, the Software is distributed on an
** "AS IS" basis, with ALL EXPRESS AND IMPLIED WARRANTIES AND CONDITIONS
** DISCLAIMED, INCLUDING, WITHOUT LIMITATION, ANY IMPLIED WARRANTIES AND
** CONDITIONS OF MERCHANTABILITY, SATISFACTORY QUALITY, FITNESS FOR A
** PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
**
** Original Code. The Original Code is: OpenGL Sample Implementation,
** Version 1.2.1, released January 26, 2000, developed by Silicon Graphics,
** Inc. The Original Code is Copyright (c) 1991-2000 Silicon Graphics, Inc.
** Copyright in any portions created by third parties is as indicated
** elsewhere herein. All Rights Reserved.
**
** Additional Notice Provisions: The application programming interfaces
** established by SGI in conjunction with the Original Code are The
** OpenGL(R) Graphics System: A Specification (Version 1.2.1), released
** April 1, 1999; The OpenGL(R) Graphics System Utility Library (Version
** 1.3), released November 4, 1998; and OpenGL(R) Graphics with the X
** Window System(R) (Version 1.3), released October 19, 1998. This software
** was created using the OpenGL(R) version 1.2.1 Sample Implementation
** published by SGI, but has not been independently verified as being
** compliant with the OpenGL(R) version 1.2.1 Specification.
*/

#define GL_APPLE_framebuffer_multisample                        1
#define GL_APPLE_texture_2D_limited_npot                        1
#define GL_APPLE_texture_format_BGRA8888                        1
#define GL_APPLE_texture_max_level                              1
#define GL_EXT_blend_minmax                                     1
#define GL_EXT_discard_framebuffer                              1
#define GL_EXT_read_format_bgra                                 1
#define GL_EXT_texture_filter_anisotropic                       1
#define GL_EXT_texture_lod_bias                                 1
#define GL_IMG_read_format                                      1
#define GL_IMG_texture_compression_pvrtc                        1
#define GL_OES_blend_equation_separate                          1
#define GL_OES_blend_func_separate                              1
#define GL_OES_blend_subtract                                   1
#define GL_OES_depth24                                          1
#define GL_OES_fbo_render_mipmap                                1
#define GL_OES_framebuffer_object                               1
#define GL_OES_mapbuffer                                        1
#define GL_OES_packed_depth_stencil                             1
#define GL_OES_rgb8_rgba8                                       1
#define GL_OES_stencil_wrap                                     1
#define GL_OES_stencil8                                         1
#define GL_OES_texture_mirrored_repeat                          1
#define GL_OES_vertex_array_object                              1


/*------------------------------------------------------------------------*
 * APPLE extension tokens
 *------------------------------------------------------------------------*/
#if GL_APPLE_framebuffer_multisample
#define GL_RENDERBUFFER_SAMPLES_APPLE                           0x8CAB
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE             0x8D56
#define GL_MAX_SAMPLES_APPLE                                    0x8D57
#define GL_READ_FRAMEBUFFER_APPLE                               0x8CA8
#define GL_DRAW_FRAMEBUFFER_APPLE                               0x8CA9
#define GL_DRAW_FRAMEBUFFER_BINDING_APPLE                       0x8CA6
#define GL_READ_FRAMEBUFFER_BINDING_APPLE                       0x8CAA
#endif

#if GL_APPLE_texture_format_BGRA8888
#define GL_BGRA_EXT                                             0x80E1
#endif

#if GL_APPLE_texture_format_BGRA8888 || GL_IMG_read_format
#define GL_BGRA                                                 0x80E1
#endif

#if GL_APPLE_texture_max_level
#define GL_TEXTURE_MAX_LEVEL_APPLE                              0x813D
#endif

/*------------------------------------------------------------------------*
 * EXT extension tokens
 *------------------------------------------------------------------------*/
#if GL_EXT_blend_minmax
#define GL_MIN_EXT                                              0x8007
#define GL_MAX_EXT                                              0x8008
#endif

#if GL_EXT_discard_framebuffer
#define GL_COLOR_EXT                                            0x1800
#define GL_DEPTH_EXT                                            0x1801
#define GL_STENCIL_EXT                                          0x1802
#endif

#if GL_EXT_read_format_bgra
#define GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT                       0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT                       0x8366
#define GL_UNSIGNED_SHORT_1_5_5_5_REV                           GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT
#endif

#if GL_EXT_read_format_bgra || GL_IMG_read_format
#define GL_UNSIGNED_SHORT_4_4_4_4_REV                           0x8365
#endif

#if GL_EXT_texture_filter_anisotropic
#define GL_TEXTURE_MAX_ANISOTROPY_EXT                           0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT                       0x84FF
#endif

#if GL_EXT_texture_lod_bias
#define GL_MAX_TEXTURE_LOD_BIAS_EXT                             0x84FD
#define GL_TEXTURE_FILTER_CONTROL_EXT                           0x8500
#define GL_TEXTURE_LOD_BIAS_EXT                                 0x8501
#endif

/*------------------------------------------------------------------------*
 * IMG extension tokens
 *------------------------------------------------------------------------*/
#if GL_IMG_read_format
#define GL_BGRA_IMG                                             0x80E1
#define GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG                       0x8365
#endif

#if GL_IMG_texture_compression_pvrtc
#define GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG                      0x8C00
#define GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG                      0x8C01
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG                     0x8C02
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG                     0x8C03
#endif

/*------------------------------------------------------------------------*
 * OES extension tokens
 *------------------------------------------------------------------------*/
#if GL_OES_blend_equation_separate
#define GL_BLEND_EQUATION_RGB_OES                               0x8009
#define GL_BLEND_EQUATION_ALPHA_OES                             0x883D
#endif

#if GL_OES_blend_func_separate
#define GL_BLEND_DST_RGB_OES                                    0x80C8
#define GL_BLEND_SRC_RGB_OES                                    0x80C9
#define GL_BLEND_DST_ALPHA_OES                                  0x80CA
#define GL_BLEND_SRC_ALPHA_OES                                  0x80CB
#endif

#if GL_OES_blend_subtract
#define GL_BLEND_EQUATION_OES                                   0x8009
#define GL_FUNC_ADD_OES                                         0x8006
#define GL_FUNC_SUBTRACT_OES                                    0x800A
#define GL_FUNC_REVERSE_SUBTRACT_OES                            0x800B
#endif

#if GL_OES_depth24
#define GL_DEPTH_COMPONENT24_OES                                0x81A6
#endif

#if GL_OES_framebuffer_object
#define GL_FRAMEBUFFER_OES                                      0x8D40
#define GL_RENDERBUFFER_OES                                     0x8D41
#define GL_RGBA4_OES                                            0x8056
#define GL_RGB5_A1_OES                                          0x8057
#define GL_RGB565_OES                                           0x8D62
#define GL_DEPTH_COMPONENT16_OES                                0x81A5
#define GL_RENDERBUFFER_WIDTH_OES                               0x8D42
#define GL_RENDERBUFFER_HEIGHT_OES                              0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT_OES                     0x8D44
#define GL_RENDERBUFFER_RED_SIZE_OES                            0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE_OES                          0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE_OES                           0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE_OES                          0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE_OES                          0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE_OES                        0x8D55
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_OES               0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_OES               0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_OES             0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_OES     0x8CD3
#define GL_COLOR_ATTACHMENT0_OES                                0x8CE0
#define GL_DEPTH_ATTACHMENT_OES                                 0x8D00
#define GL_STENCIL_ATTACHMENT_OES                               0x8D20
#define GL_FRAMEBUFFER_COMPLETE_OES                             0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_OES                0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_OES        0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_OES                0x8CD9
#define GL_FRAMEBUFFER_INCOMPLETE_FORMATS_OES                   0x8CDA
#define GL_FRAMEBUFFER_UNSUPPORTED_OES                          0x8CDD
#define GL_FRAMEBUFFER_BINDING_OES                              0x8CA6
#define GL_RENDERBUFFER_BINDING_OES                             0x8CA7
#define GL_MAX_RENDERBUFFER_SIZE_OES                            0x84E8
#define GL_INVALID_FRAMEBUFFER_OPERATION_OES                    0x0506
#endif

#if GL_OES_mapbuffer
#define GL_WRITE_ONLY_OES                                       0x88B9
#define GL_BUFFER_ACCESS_OES                                    0x88BB
#define GL_BUFFER_MAPPED_OES                                    0x88BC
#define GL_BUFFER_MAP_POINTER_OES                               0x88BD
#endif

#if GL_OES_packed_depth_stencil
#define GL_DEPTH_STENCIL_OES                                    0x84F9
#define GL_UNSIGNED_INT_24_8_OES                                0x84FA
#define GL_DEPTH24_STENCIL8_OES                                 0x88F0
#endif

#if GL_OES_rgb8_rgba8
#define GL_RGB8_OES                                             0x8051
#define GL_RGBA8_OES                                            0x8058
#endif

#if GL_OES_stencil_wrap
#define GL_INCR_WRAP_OES                                        0x8507
#define GL_DECR_WRAP_OES                                        0x8508
#endif

#if GL_OES_stencil8
#define GL_STENCIL_INDEX8_OES                                   0x8D48
#endif

#if GL_OES_texture_mirrored_repeat
#define GL_MIRRORED_REPEAT_OES                                  0x8370
#endif

#if GL_OES_vertex_array_object
#define GL_VERTEX_ARRAY_BINDING_OES                             0x85B5
#endif

/**************************************************************************/

/*------------------------------------------------------------------------*
 * APPLE extension functions
 *------------------------------------------------------------------------*/
#if GL_APPLE_framebuffer_multisample
GL_API GLvoid glRenderbufferStorageMultisampleAPPLE(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
GL_API GLvoid glResolveMultisampleFramebufferAPPLE(void)  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
#endif

/*------------------------------------------------------------------------*
 * EXT extension functions
 *------------------------------------------------------------------------*/
#if GL_EXT_discard_framebuffer
GL_API GLvoid GL_APIENTRY glDiscardFramebufferEXT(GLenum target, GLsizei numAttachments, const GLenum *attachments)  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
#endif

/*------------------------------------------------------------------------*
 * OES extension functions
 *------------------------------------------------------------------------*/
#if GL_OES_blend_equation_separate
GL_API GLvoid GL_APIENTRY glBlendEquationSeparateOES (GLenum modeRGB, GLenum modeAlpha)  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_1);
#endif

#if GL_OES_blend_func_separate
GL_API GLvoid GL_APIENTRY glBlendFuncSeparateOES (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_1);
#endif

#if GL_OES_blend_subtract
GL_API GLvoid GL_APIENTRY glBlendEquationOES (GLenum mode);
#endif

#if GL_OES_framebuffer_object
GL_API GLboolean GL_APIENTRY glIsRenderbufferOES (GLuint renderbuffer);
GL_API GLvoid GL_APIENTRY glBindRenderbufferOES (GLenum target, GLuint renderbuffer);
GL_API GLvoid GL_APIENTRY glDeleteRenderbuffersOES (GLsizei n, const GLuint* renderbuffers);
GL_API GLvoid GL_APIENTRY glGenRenderbuffersOES (GLsizei n, GLuint* renderbuffers);
GL_API GLvoid GL_APIENTRY glRenderbufferStorageOES (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
GL_API GLvoid GL_APIENTRY glGetRenderbufferParameterivOES (GLenum target, GLenum pname, GLint* params);
GL_API GLboolean GL_APIENTRY glIsFramebufferOES (GLuint framebuffer);
GL_API GLvoid GL_APIENTRY glBindFramebufferOES (GLenum target, GLuint framebuffer);
GL_API GLvoid GL_APIENTRY glDeleteFramebuffersOES (GLsizei n, const GLuint* framebuffers);
GL_API GLvoid GL_APIENTRY glGenFramebuffersOES (GLsizei n, GLuint* framebuffers);
GL_API GLenum GL_APIENTRY glCheckFramebufferStatusOES (GLenum target);
GL_API GLvoid GL_APIENTRY glFramebufferRenderbufferOES (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GL_API GLvoid GL_APIENTRY glFramebufferTexture2DOES (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_API GLvoid GL_APIENTRY glGetFramebufferAttachmentParameterivOES (GLenum target, GLenum attachment, GLenum pname, GLint* params);
GL_API GLvoid GL_APIENTRY glGenerateMipmapOES (GLenum target);
#endif

#if GL_OES_mapbuffer
GL_API GLvoid GL_APIENTRY glGetBufferPointervOES (GLenum target, GLenum pname, GLvoid **params);
GL_API GLvoid * GL_APIENTRY glMapBufferOES (GLenum target, GLenum access);
GL_API GLboolean GL_APIENTRY glUnmapBufferOES (GLenum target);
#endif

#if GL_OES_vertex_array_object
GL_API GLvoid glBindVertexArrayOES(GLuint array)  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
GL_API GLvoid glDeleteVertexArraysOES(GLsizei n, const GLuint *arrays)  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
GL_API GLvoid glGenVertexArraysOES(GLsizei n, GLuint *arrays)  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
GL_API GLboolean glIsVertexArrayOES(GLuint array)  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_4_0);
#endif

#ifdef __cplusplus
}
#endif

#endif /* ES1_GLEXT_H_GUARD */
