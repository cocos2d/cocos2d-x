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

#ifndef __CCGL_H__
#define __CCGL_H__

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_EMSCRIPTEN
#define GLFW_INCLUDE_ES2 1

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

//#include <GLFW/glfw3.h>
//#include <GLES2/gl2.h>
//#include <GLES2/gl2ext.h>


//#include "GL/glew.h"
//#include <EGL/egl.h>

// normal process
//#include <GLES2/gl2.h>
//#include <GLES2/gl2ext.h>
//#include <GLES2/gl2platform.h>

//#define	glClearDepth				glClearDepthf
//#define GL_WRITE_ONLY				GL_WRITE_ONLY_OES
//#define GL_BGRA						GL_BGRA_EXT
//#define GL_DEPTH24_STENCIL8			GL_DEPTH24_STENCIL8_OES
//#define CC_GL_DEPTH24_STENCIL8		GL_DEPTH24_STENCIL8

//extern PFNGLGENVERTEXARRAYSOESPROC glGenVertexArrays;
//extern PFNGLBINDVERTEXARRAYOESPROC glBindVertexArray;
//extern PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArrays;
//extern PFNGLMAPBUFFEROESPROC glMapBuffer;
//extern PFNGLUNMAPBUFFEROESPROC glUnmapBuffer;
//extern PFNGLGETBUFFERPOINTERVOESPROC glGetBufferPointerv;

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_LINUX

#endif // __CCGL_H__
