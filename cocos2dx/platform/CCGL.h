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

#ifndef __PLATFOMR_CCGL_H__
#define __PLATFOMR_CCGL_H__

//
// Common layer for OpenGL stuff
//

#include "ccxGL.h"
#include "CCXEGLView.h"

// iOS
#if defined(CCX_PLATFORM_MOBILE)
    #define CC_GLVIEW                   cocos2d::CCXEGLView
    #define ccglOrtho					glOrthof
    #define	ccglClearDepth				glClearDepthf
    #define ccglGenerateMipmap			glGenerateMipmapOES
    #define ccglGenFramebuffers			glGenFramebuffersOES
    #define ccglBindFramebuffer			glBindFramebufferOES
    #define ccglFramebufferTexture2D	glFramebufferTexture2DOES
    #define ccglDeleteFramebuffers		glDeleteFramebuffersOES
    #define ccglCheckFramebufferStatus	glCheckFramebufferStatusOES
    #define ccglTranslate				glTranslatef

    #define CC_GL_FRAMEBUFFER			GL_FRAMEBUFFER_OES
    #define CC_GL_FRAMEBUFFER_BINDING	GL_FRAMEBUFFER_BINDING_OES
    #define CC_GL_COLOR_ATTACHMENT0		GL_COLOR_ATTACHMENT0_OES
    #define CC_GL_FRAMEBUFFER_COMPLETE	GL_FRAMEBUFFER_COMPLETE_OES

// Mac
#elif defined(CCX_PLATFORM_PC)
    #define CC_GLVIEW                   MacGLView
    #define ccglOrtho					glOrtho
    #define	ccglClearDepth				glClearDepth
    #define ccglGenerateMipmap			glGenerateMipmap
    #define ccglGenFramebuffers			glGenFramebuffers
    #define ccglBindFramebuffer			glBindFramebuffer
    #define ccglFramebufferTexture2D	glFramebufferTexture2D
    #define ccglDeleteFramebuffers		glDeleteFramebuffers
    #define ccglCheckFramebufferStatus	glCheckFramebufferStatus
    #define ccglTranslate				glTranslated

    #define CC_GL_FRAMEBUFFER			GL_FRAMEBUFFER
    #define CC_GL_FRAMEBUFFER_BINDING	GL_FRAMEBUFFER_BINDING
    #define CC_GL_COLOR_ATTACHMENT0		GL_COLOR_ATTACHMENT0
    #define CC_GL_FRAMEBUFFER_COMPLETE	GL_FRAMEBUFFER_COMPLETE

#endif

#endif // __PLATFOMR_CCGL_H__
