/* $Change: 608281 $ */
/* -*- mode: c; tab-width: 8; -*- */
/* vi: set sw=4 ts=8: */
/* Reference version of egl.h for EGL 1.4.
 * $Revision: #3 $ on $Date: 2010/08/05 $
 */

/*
** Copyright (c) 2007-2009 The Khronos Group Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and/or associated documentation files (the
** "Materials"), to deal in the Materials without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Materials, and to
** permit persons to whom the Materials are furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Materials.
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/

/*! \file egl.h
    \brief egl header file.
    
    egl header file.
*/

#ifndef __egl_h_
#define __egl_h_

/* All platform-dependent types and macro boilerplate (such as EGLAPI
 * and EGLAPIENTRY) should go in eglplatform.h.
 */
#include "eglplatform.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup opengles
 * 
 * @{
 */

/* EGL Types */
/* EGLint is defined in eglplatform.h */

/*! \var typedef unsigned int EGLBoolean
    \brief A type definition for EGLBoolean.
*/
typedef unsigned int EGLBoolean;

/*! \var typedef unsigned int EGLenum
    \brief A type definition for EGLenum.
*/
typedef unsigned int EGLenum;

/*! \var typedef void *EGLConfig
    \brief A type definition for EGLConfig.
*/
typedef void *EGLConfig;

/*! \var typedef void *EGLContext
    \brief A type definition for EGLContext.
*/
typedef void *EGLContext;

/*! \var typedef void *EGLDisplay
    \brief A type definition for EGLDisplay.
*/
typedef void *EGLDisplay;

/*! \var typedef void *EGLSurface
    \brief A type definition for EGLSurface.
*/
typedef void *EGLSurface;

/*! \var typedef void *EGLClientBuffer
    \brief A type definition for EGLClientBuffer.
*/
typedef void *EGLClientBuffer;

/* EGL Versioning */
#define EGL_VERSION_1_0			1
#define EGL_VERSION_1_1			1
#define EGL_VERSION_1_2			1
#define EGL_VERSION_1_3			1
#define EGL_VERSION_1_4			1

/* EGL Enumerants. Bitmasks and other exceptional cases aside, most
 * enums are assigned unique values starting at 0x3000.
 */

/* EGL aliases */
#define EGL_FALSE			0
#define EGL_TRUE			1

/* Out-of-band handle values */
#define EGL_DEFAULT_DISPLAY		((EGLNativeDisplayType)0)
#define EGL_NO_CONTEXT			((EGLContext)0)
#define EGL_NO_DISPLAY			((EGLDisplay)0)
#define EGL_NO_SURFACE			((EGLSurface)0)

/* Out-of-band attribute value */
#define EGL_DONT_CARE			((EGLint)-1)

/* Errors / GetError return values */
#define EGL_SUCCESS			0x3000
#define EGL_NOT_INITIALIZED		0x3001
#define EGL_BAD_ACCESS			0x3002
#define EGL_BAD_ALLOC			0x3003
#define EGL_BAD_ATTRIBUTE		0x3004
#define EGL_BAD_CONFIG			0x3005
#define EGL_BAD_CONTEXT			0x3006
#define EGL_BAD_CURRENT_SURFACE		0x3007
#define EGL_BAD_DISPLAY			0x3008
#define EGL_BAD_MATCH			0x3009
#define EGL_BAD_NATIVE_PIXMAP		0x300A
#define EGL_BAD_NATIVE_WINDOW		0x300B
#define EGL_BAD_PARAMETER		0x300C
#define EGL_BAD_SURFACE			0x300D
#define EGL_CONTEXT_LOST		0x300E	/* EGL 1.1 - IMG_power_management */

/* Reserved 0x300F-0x301F for additional errors */

/* Config attributes */
#define EGL_BUFFER_SIZE			0x3020
#define EGL_ALPHA_SIZE			0x3021
#define EGL_BLUE_SIZE			0x3022
#define EGL_GREEN_SIZE			0x3023
#define EGL_RED_SIZE			0x3024
#define EGL_DEPTH_SIZE			0x3025
#define EGL_STENCIL_SIZE		0x3026
#define EGL_CONFIG_CAVEAT		0x3027
#define EGL_CONFIG_ID			0x3028
#define EGL_LEVEL			0x3029
#define EGL_MAX_PBUFFER_HEIGHT		0x302A
#define EGL_MAX_PBUFFER_PIXELS		0x302B
#define EGL_MAX_PBUFFER_WIDTH		0x302C
#define EGL_NATIVE_RENDERABLE		0x302D
#define EGL_NATIVE_VISUAL_ID		0x302E
#define EGL_NATIVE_VISUAL_TYPE		0x302F
#define EGL_PRESERVED_RESOURCES		0x3030
#define EGL_SAMPLES			0x3031
#define EGL_SAMPLE_BUFFERS		0x3032
#define EGL_SURFACE_TYPE		0x3033
#define EGL_TRANSPARENT_TYPE		0x3034
#define EGL_TRANSPARENT_BLUE_VALUE	0x3035
#define EGL_TRANSPARENT_GREEN_VALUE	0x3036
#define EGL_TRANSPARENT_RED_VALUE	0x3037
#define EGL_NONE			0x3038	/* Attrib list terminator */
#define EGL_BIND_TO_TEXTURE_RGB		0x3039
#define EGL_BIND_TO_TEXTURE_RGBA	0x303A
#define EGL_MIN_SWAP_INTERVAL		0x303B
#define EGL_MAX_SWAP_INTERVAL		0x303C
#define EGL_LUMINANCE_SIZE		0x303D
#define EGL_ALPHA_MASK_SIZE		0x303E
#define EGL_COLOR_BUFFER_TYPE		0x303F
#define EGL_RENDERABLE_TYPE		0x3040
#define EGL_MATCH_NATIVE_PIXMAP		0x3041	/* Pseudo-attribute (not queryable) */
#define EGL_CONFORMANT			0x3042

/* Reserved 0x3041-0x304F for additional config attributes */

/* Config attribute values */
#define EGL_SLOW_CONFIG			0x3050	/* EGL_CONFIG_CAVEAT value */
#define EGL_NON_CONFORMANT_CONFIG	0x3051	/* EGL_CONFIG_CAVEAT value */
#define EGL_TRANSPARENT_RGB		0x3052	/* EGL_TRANSPARENT_TYPE value */
#define EGL_RGB_BUFFER			0x308E	/* EGL_COLOR_BUFFER_TYPE value */
#define EGL_LUMINANCE_BUFFER		0x308F	/* EGL_COLOR_BUFFER_TYPE value */

/* More config attribute values, for EGL_TEXTURE_FORMAT */
#define EGL_NO_TEXTURE			0x305C
#define EGL_TEXTURE_RGB			0x305D
#define EGL_TEXTURE_RGBA		0x305E
#define EGL_TEXTURE_2D			0x305F

/* Config attribute mask bits */
#define EGL_PBUFFER_BIT			0x0001	/* EGL_SURFACE_TYPE mask bits */
#define EGL_PIXMAP_BIT			0x0002	/* EGL_SURFACE_TYPE mask bits */
#define EGL_WINDOW_BIT			0x0004	/* EGL_SURFACE_TYPE mask bits */
#define EGL_VG_COLORSPACE_LINEAR_BIT	0x0020	/* EGL_SURFACE_TYPE mask bits */
#define EGL_VG_ALPHA_FORMAT_PRE_BIT	0x0040	/* EGL_SURFACE_TYPE mask bits */
#define EGL_MULTISAMPLE_RESOLVE_BOX_BIT 0x0200	/* EGL_SURFACE_TYPE mask bits */
#define EGL_SWAP_BEHAVIOR_PRESERVED_BIT 0x0400	/* EGL_SURFACE_TYPE mask bits */

#define EGL_OPENGL_ES_BIT		0x0001	/* EGL_RENDERABLE_TYPE mask bits */
#define EGL_OPENVG_BIT			0x0002	/* EGL_RENDERABLE_TYPE mask bits */
#define EGL_OPENGL_ES2_BIT		0x0004	/* EGL_RENDERABLE_TYPE mask bits */
#define EGL_OPENGL_BIT			0x0008	/* EGL_RENDERABLE_TYPE mask bits */

/* QueryString targets */
#define EGL_VENDOR			0x3053
#define EGL_VERSION			0x3054
#define EGL_EXTENSIONS			0x3055
#define EGL_CLIENT_APIS			0x308D

/* QuerySurface / SurfaceAttrib / CreatePbufferSurface targets */
#define EGL_HEIGHT			0x3056
#define EGL_WIDTH			0x3057
#define EGL_LARGEST_PBUFFER		0x3058
#define EGL_TEXTURE_FORMAT		0x3080
#define EGL_TEXTURE_TARGET		0x3081
#define EGL_MIPMAP_TEXTURE		0x3082
#define EGL_MIPMAP_LEVEL		0x3083
#define EGL_RENDER_BUFFER		0x3086
#define EGL_VG_COLORSPACE		0x3087
#define EGL_VG_ALPHA_FORMAT		0x3088
#define EGL_HORIZONTAL_RESOLUTION	0x3090
#define EGL_VERTICAL_RESOLUTION		0x3091
#define EGL_PIXEL_ASPECT_RATIO		0x3092
#define EGL_SWAP_BEHAVIOR		0x3093
#define EGL_MULTISAMPLE_RESOLVE		0x3099

/* EGL_RENDER_BUFFER values / BindTexImage / ReleaseTexImage buffer targets */
#define EGL_BACK_BUFFER			0x3084
#define EGL_SINGLE_BUFFER		0x3085

/* OpenVG color spaces */
#define EGL_VG_COLORSPACE_sRGB		0x3089	/* EGL_VG_COLORSPACE value */
#define EGL_VG_COLORSPACE_LINEAR	0x308A	/* EGL_VG_COLORSPACE value */

/* OpenVG alpha formats */
#define EGL_VG_ALPHA_FORMAT_NONPRE	0x308B	/* EGL_ALPHA_FORMAT value */
#define EGL_VG_ALPHA_FORMAT_PRE		0x308C	/* EGL_ALPHA_FORMAT value */

/* Constant scale factor by which fractional display resolutions &
 * aspect ratio are scaled when queried as integer values.
 */
#define EGL_DISPLAY_SCALING		10000

/* Unknown display resolution/aspect ratio */
#define EGL_UNKNOWN			((EGLint)-1)

/* Back buffer swap behaviors */
#define EGL_BUFFER_PRESERVED		0x3094	/* EGL_SWAP_BEHAVIOR value */
#define EGL_BUFFER_DESTROYED		0x3095	/* EGL_SWAP_BEHAVIOR value */

/* CreatePbufferFromClientBuffer buffer types */
#define EGL_OPENVG_IMAGE		0x3096

/* QueryContext targets */
#define EGL_CONTEXT_CLIENT_TYPE		0x3097

/* CreateContext attributes */
#define EGL_CONTEXT_CLIENT_VERSION	0x3098

/* Multisample resolution behaviors */
#define EGL_MULTISAMPLE_RESOLVE_DEFAULT 0x309A	/* EGL_MULTISAMPLE_RESOLVE value */
#define EGL_MULTISAMPLE_RESOLVE_BOX	0x309B	/* EGL_MULTISAMPLE_RESOLVE value */

/* BindAPI/QueryAPI targets */
#define EGL_OPENGL_ES_API		0x30A0
#define EGL_OPENVG_API			0x30A1
#define EGL_OPENGL_API			0x30A2

/* GetCurrentSurface targets */
#define EGL_DRAW			0x3059
#define EGL_READ			0x305A

/* WaitNative engines */
#define EGL_CORE_NATIVE_ENGINE		0x305B

/* EGL 1.2 tokens renamed for consistency in EGL 1.3 */
#define EGL_COLORSPACE			EGL_VG_COLORSPACE
#define EGL_ALPHA_FORMAT		EGL_VG_ALPHA_FORMAT
#define EGL_COLORSPACE_sRGB		EGL_VG_COLORSPACE_sRGB
#define EGL_COLORSPACE_LINEAR		EGL_VG_COLORSPACE_LINEAR
#define EGL_ALPHA_FORMAT_NONPRE		EGL_VG_ALPHA_FORMAT_NONPRE
#define EGL_ALPHA_FORMAT_PRE		EGL_VG_ALPHA_FORMAT_PRE

/* EGL extensions must request enum blocks from the Khronos
 * API Registrar, who maintains the enumerant registry. Submit
 * a bug in Khronos Bugzilla against task "Registry".
 */

/*
** FIXME: The EGL_SEQUENCE_ITEM_SYMB token is temporary until an
** offical name and value are assigned.
*/
#define EGL_SEQUENCE_ITEM_SYMB		0x6000

/* EGL Functions */

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLint 		eglGetError(void);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLDisplay  eglGetDisplay(EGLNativeDisplayType display_id);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLBoolean  eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLBoolean  eglTerminate(EGLDisplay dpy);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
const char *  eglQueryString(EGLDisplay dpy, EGLint name);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLBoolean  eglGetConfigs(EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLBoolean  eglChooseConfig(EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLBoolean  eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLSurface  eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLSurface  eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLSurface  eglCreatePixmapSurface(EGLDisplay dpy, EGLConfig config,EGLNativePixmapType pixmap,const EGLint *attrib_list);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLBoolean  eglDestroySurface(EGLDisplay dpy, EGLSurface surface);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLBoolean  eglQuerySurface(EGLDisplay dpy, EGLSurface surface,EGLint attribute, EGLint *value);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLBoolean  eglBindAPI(EGLenum api);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLenum  	eglQueryAPI(void);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLBoolean  eglWaitClient(void);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLBoolean  eglReleaseThread(void);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLSurface  eglCreatePbufferFromClientBuffer(EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLBoolean  eglSurfaceAttrib(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value);

/*
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLBoolean  eglBindTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer); 

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLBoolean  eglReleaseTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLBoolean eglSwapInterval(EGLDisplay dpy,EGLint interval);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLContext eglCreateContext(EGLDisplay dpy,EGLConfig config, EGLContext share_context, const EGLint *attrib_list);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLBoolean eglDestroyContext(EGLDisplay dpy,EGLContext ctx);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLBoolean eglMakeCurrent(EGLDisplay dpy,EGLSurface draw, EGLSurface read,EGLContext ctx);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLContext eglGetCurrentContext(void);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLSurface eglGetCurrentSurface(EGLint readdraw);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLDisplay eglGetCurrentDisplay(void);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLBoolean eglQueryContext(EGLDisplay dpy,EGLContext ctx, EGLint attribute,EGLint *value);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLBoolean eglWaitGL(void);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLBoolean eglWaitNative(EGLint engine);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLBoolean eglSwapBuffers(EGLDisplay dpy,EGLSurface surface);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLBoolean eglCopyBuffers(EGLDisplay dpy,EGLSurface surface, EGLNativePixmapType target);

/* This is a generic function pointer type, whose name indicates it must
 * be cast to the proper type *and calling convention* before use.
 */ 
/*! \var typedef void (*__eglMustCastToProperFunctionPointerType)(void)
    \brief A type definition for __eglMustCastToProperFunctionPointerType.
*/
typedef void (*__eglMustCastToProperFunctionPointerType)(void);

/* Now, define eglGetProcAddress using the generic function ptr. type */
/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLAPI __eglMustCastToProperFunctionPointerType EGLAPIENTRY eglGetProcAddress(const char *procname);

/**
 * You can find more details at the Khronos Group site: http://www.khronos.org/registry/egl
 */
EGLBoolean eglUpdateBufferOSP(EGLDisplay dpy,EGLSurface surface);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __egl_h_ */
