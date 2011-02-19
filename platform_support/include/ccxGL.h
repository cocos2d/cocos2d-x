/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CCX_GL_H__
#define __CCX_GL_H__

#include "ccxCommon.h"

#if (CCX_TARGET_PLATFORM == CCX_PLATFORM_IOS)
#error
#endif

#if (CCX_TARGET_PLATFORM == CCX_PLATFORM_MAC)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#if (CCX_TARGET_PLATFORM == CCX_PLATFORM_ANDROID)
#error
#endif

#if (CCX_TARGET_PLATFORM == CCX_PLATFORM_UPHONE)
#include <GLES/gl.h>
#include <GLES/glext.h>
#endif

#if (CCX_TARGET_PLATFORM == CCX_PLATFORM_WIN32)
#include <GLES/gl.h>
#include <GLES/glext.h>
#endif

#if defined(CCX_PLATFORM_MOBILE)

NS_CC_BEGIN;

/*
OpenGL GLU implementation
*/

/** OpenGL gluLookAt implementation */
void CCX_DLL_PS gluLookAt(GLfloat fEyeX, GLfloat fEyeY, GLfloat fEyeZ, 
               GLfloat fLookAtX, GLfloat fLookAtY, GLfloat fLookAtZ, 
               GLfloat fUpX, GLfloat fUpY, GLfloat fUpZ);

/** OpenGL gluPerspective implementation */
void CCX_DLL_PS gluPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar);

NS_CC_END;

#endif

#endif	// __CCX_GL_H__
