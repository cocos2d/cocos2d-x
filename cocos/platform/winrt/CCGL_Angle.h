/****************************************************************************
Copyright (c) 2010 cocos2d-x.org
Copyright (c) Microsoft Open Technologies, Inc.

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

#ifndef __CCGL_ANGLE_H__
#define __CCGL_ANGLE_H__

// disable unimplemented function declarations in Angle
#define GL_OES_mapbuffer 1
#define GL_OES_vertex_array_object 1

#include "EGL/egl.h"
#include "EGL/eglext.h"
#include "EGL/eglplatform.h"
#include "GLES2/gl2.h"
#include "GLES2/gl2ext.h"
#include "winrtangle.h"
#include "esUtil.h"
#include "ccMacros.h"

#define GL_WRITE_ONLY_OES                                       0x88B9
#define GL_BUFFER_ACCESS_OES                                    0x88BB
#define GL_BUFFER_MAPPED_OES                                    0x88BC
#define GL_BUFFER_MAP_POINTER_OES                               0x88BD

#define GL_BGRA						GL_BGRA_EXT

#define	glClearDepth				glClearDepthf


inline void glGenVertexArrays(GLsizei n, GLuint *arrays)
{
    CCASSERT(false, "AngleProject does not implement glGenVertexArraysOES");
}

inline void glBindVertexArray(GLuint array)
{
    CCASSERT(false, "AngleProject does not implement glBindVertexArrayOES");
}

inline void glDeleteVertexArrays(GLsizei n, const GLuint *arrays)
{
    CCASSERT(false, "AngleProject does not implement glDeleteVertexArraysOES");
}

inline void* glMapBuffer(GLenum target, GLenum access)
{
   CCASSERT(false, "AngleProject does not implement glMapBufferOES"); 
   return NULL;
}

inline GLboolean glUnmapBuffer(GLenum targets)
{
   CCASSERT(false, "AngleProject does not implement glUnmapBufferOES"); 
   return false;
}

#define GL_DEPTH24_STENCIL8			GL_DEPTH24_STENCIL8_OES
#define GL_WRITE_ONLY				GL_WRITE_ONLY_OES

#endif // __CCGL_ANGLE_H__
