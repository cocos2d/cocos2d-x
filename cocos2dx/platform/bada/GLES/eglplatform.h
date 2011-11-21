/* $Change: 608281 $ */

/*! \file eglplatform.h
    \brief eglplatform header file.
    
    eglplatform header file.
*/
#ifndef __eglplatform_h_
#define __eglplatform_h_

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

/* Platform-specific types and definitions for egl.h
 * $Revision: #3 $ on $Date: 2010/08/05 $
 *
 * Adopters may modify khrplatform.h and this file to suit their platform.
 * You are encouraged to submit all modifications to the Khronos group so that
 * they can be included in future versions of this file.  Please submit changes
 * by sending them to the public Khronos Bugzilla (http://khronos.org/bugzilla)
 * by filing a bug against product "EGL" component "Registry".
 */

//}}}
//
//namespace Osp { namespace Ui { class Control; }; };
//namespace Osp { namespace Graphics { class Bitmap; }; };
//
//namespace Osp { namespace Graphics { namespace Opengl {


#include "khrplatform.h"


/* Macros used in EGL function prototype declarations.
 *
 * EGL functions should be prototyped as:
 *
 * EGLAPI return-type EGLAPIENTRY eglFunction(arguments);
 * typedef return-type (EXPAPIENTRYP PFNEGLFUNCTIONPROC) (arguments);
 *
 * KHRONOS_APICALL and KHRONOS_APIENTRY are defined in KHR/khrplatform.h
 */

/**
 * @addtogroup opengles
 * 
 * @{
 */

#ifndef _WIN32
#define EGLAPI
#define EGLAPIENTRY
#else
#ifndef EGLAPIENTRY
#define EGLAPIENTRY __stdcall
#endif
#ifndef EGLAPI
#define EGLAPI
#endif
#endif

/*
** Types and resources
*/

/*! \var typedef int EGLint
    \brief A type definition for EGLConfig.
*/
typedef int EGLint;

#ifdef _WIN32_bada
typedef void *EGLNativeDisplayType;
class Osp::Ui::Control;
typedef Osp::Ui::Control *EGLNativeWindowType;
class Osp::Graphics::Bitmap;
typedef Bitmap *EGLNativePixmapType;

#elif FEATURE_SYSLSI_S5PC110
typedef int  EGLNativeDisplayType;
typedef void *EGLNativeWindowType;
typedef struct
{
	void	*pBuffer;
	long	lWidth;
	long	lHeight;
	enum
	{
		NUEGL_PIXELFORMAT_565 = 0,
		NUEGL_PIXELFORMAT_4444 = 1,
		NUEGL_PIXELFORMAT_8888 = 2,
		NUEGL_PIXELFORMAT_1555 = 3,
		NUEGL_PIXELFORMAT_force_to_32_bits = 0x12345678
	} ePixelFormat;
	enum
	{
		NUEGL_ROTATE_0 = 0,
		NUEGL_ROTATE_90 = 1,
		NUEGL_ROTATE_180 = 2,
		NUEGL_ROTATE_270 = 3,
		NUEGL_ROTATE_force_to_32_bits = 0x12345678
	} eRotation;
} sEGLNativePixmapType;
typedef sEGLNativePixmapType *EGLNativePixmapType;
#else

/*! \var typedef void *EGLNativeDisplayType
    \brief A type definition for EGLNativeDisplayType.
*/
typedef void *EGLNativeDisplayType;

/*! \var typedef void *EGLNativeWindowType
    \brief A type definition for EGLNativeWindowType.
*/
typedef void *EGLNativeWindowType;

/*! \var typedef void *EGLNativePixmapType
    \brief A type definition for EGLNativePixmapType.
*/
typedef void *EGLNativePixmapType;
#endif

/*! \var typedef EGLNativeDisplayType NativeDisplayType
    \brief A type definition for NativeDisplayType.
*/
typedef EGLNativeDisplayType NativeDisplayType;

/*! \var typedef EGLNativePixmapType  NativePixmapType
    \brief A type definition for NativePixmapType.
*/
typedef EGLNativePixmapType  NativePixmapType;

/*! \var typedef EGLNativeWindowType  NativeWindowType
    \brief A type definition for NativeWindowType.
*/
typedef EGLNativeWindowType  NativeWindowType;

#include "egl_macro.h"

/**
 * @}
 */

#endif /* __eglplatform_h_ */
