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

#include "CCEGLView.h"

#define CC_GLVIEW                   cocos2d::CCEGLView
#define ccglOrtho					cocos2d::CCDirector::sharedDirector()->getGLContext()->glOrthof
#define	ccglClearDepth				cocos2d::CCDirector::sharedDirector()->getGLContext()->glClearDepthf
#define ccglGenerateMipmap			cocos2d::CCDirector::sharedDirector()->getGLContext()->glGenerateMipmap
#define ccglGenFramebuffers			cocos2d::CCDirector::sharedDirector()->getGLContext()->glGenFramebuffers
#define ccglBindFramebuffer			cocos2d::CCDirector::sharedDirector()->getGLContext()->glBindFramebuffer
#define ccglFramebufferTexture2D	cocos2d::CCDirector::sharedDirector()->getGLContext()->glFramebufferTexture2D
#define ccglDeleteFramebuffers		cocos2d::CCDirector::sharedDirector()->getGLContext()->glDeleteFramebuffers
#define ccglCheckFramebufferStatus	cocos2d::CCDirector::sharedDirector()->getGLContext()->glCheckFramebufferStatus
#define ccglTranslate				cocos2d::CCDirector::sharedDirector()->getGLContext()->glTranslatef

#define CC_GL_FRAMEBUFFER			GL_FRAMEBUFFER
#define CC_GL_FRAMEBUFFER_BINDING	GL_FRAMEBUFFER_BINDING
#define CC_GL_COLOR_ATTACHMENT0		GL_COLOR_ATTACHMENT0
#define CC_GL_FRAMEBUFFER_COMPLETE	GL_FRAMEBUFFER_COMPLETE

#include "CCCommon.h"

#include "support/gl_support/OpenGLES/OpenGLESContext.h"

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//#include "OpenGLES/ES1/gl.h"
//#include "OpenGLES/ES1/glext.h"
//#endif
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include <GLES/gl.h>
//#include <GLES/glext.h>
//#endif
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)
//#include <GLES/gl.h>
//#include <GLES/glext.h>
//#endif
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//#include <GLES/gl.h>
//#include <GLES/glext.h>
//#endif
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_AIRPLAY)
//#include <IwGL.h>
//#endif

NS_CC_BEGIN;

/*
OpenGL GLU implementation
*/

/** OpenGL gluLookAt implementation */
void CC_DLL gluLookAt(GLfloat fEyeX, GLfloat fEyeY, GLfloat fEyeZ, 
               GLfloat fLookAtX, GLfloat fLookAtY, GLfloat fLookAtZ, 
               GLfloat fUpX, GLfloat fUpY, GLfloat fUpZ);

/** OpenGL gluPerspective implementation */
void CC_DLL gluPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar);

NS_CC_END;

#endif // __PLATFOMR_CCGL_H__
