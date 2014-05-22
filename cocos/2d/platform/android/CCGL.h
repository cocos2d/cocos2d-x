/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#ifndef __CCGL_H__
#define __CCGL_H__

#include "base/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#define	glClearDepth				glClearDepthf
#define glDeleteVertexArrays		glDeleteVertexArraysOES
#define glGenVertexArrays			glGenVertexArraysOES
#define glBindVertexArray			glBindVertexArrayOES
#define glMapBuffer					glMapBufferOES
#define glUnmapBuffer				glUnmapBufferOES

#define GL_DEPTH24_STENCIL8			GL_DEPTH24_STENCIL8_OES
#define GL_WRITE_ONLY				GL_WRITE_ONLY_OES

// 在android ndk r7中，头文件glplatform.h中没有定义GL_GLEXT_PROTOTYPES
// 我们要在这里手动定义它
#include <GLES2/gl2platform.h>
#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif

// 标准过程
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
//  Android平台上，在gl2.h中没有定义GLchar
typedef char GLchar;
// 在android中定义 GL_BGRA_EXT而不定义GL_BRGA
#ifndef GL_BGRA
#define GL_BGRA  0x80E1
#endif

//在这里声明并在EGLView_android.cpp中定义
extern PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOESEXT;
extern PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOESEXT;
extern PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOESEXT;

#define glGenVertexArraysOES glGenVertexArraysOESEXT
#define glBindVertexArrayOES glBindVertexArrayOESEXT
#define glDeleteVertexArraysOES glDeleteVertexArraysOESEXT


#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#endif // __CCGL_H__
