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
#include "CCGrabber.h"
#include "ccMacros.h"
#include "CCTexture2D.h"
#include "support/opengl_support/OpenGL_Internal.h"
#include "platform/platform.h"
#include <GLES/glext.h>

namespace cocos2d
{
	CCGrabber::CCGrabber(void)
	{
		m_fbo = 0;
		m_oldFBO = 0;

		// generate FBO
		glGenFramebuffersOES(1, &m_fbo);
	}

	void CCGrabber::grab(cocos2d::CCTexture2D *pTexture)
	{
		glGetIntegerv(GL_FRAMEBUFFER_BINDING_OES, &m_oldFBO);

		// bind
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, m_fbo);

		// associate texture with FBO
		glFramebufferTexture2DOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_TEXTURE_2D,
			pTexture->getName(), 0);

		// check if it worked (probably worth doing :) )
		GLuint status = glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES);
		if (status != GL_FRAMEBUFFER_COMPLETE_OES)
		{
			CCLOG("Frame Grabber: could not attach texture to frmaebuffer");
		}

		glBindFramebufferOES(GL_FRAMEBUFFER_OES, m_oldFBO);
	}
	
	void CCGrabber::beforeRender(cocos2d::CCTexture2D *pTexture)
	{
		glGetIntegerv(GL_FRAMEBUFFER_BINDING_OES, &m_oldFBO);
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, m_fbo);

		// BUG XXX: doesn't work with RGB565.

		glClearColor(0, 0, 0, 0);

		// BUG #631: To fix #631, uncomment the lines with #631
		// Warning: But it CCGrabber won't work with 2 effects at the same time
		//	glClearColor(0.0f,0.0f,0.0f,1.0f);	// #631

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//	glColorMask(TRUE, TRUE, TRUE, FALSE);	// #631
	}

	void CCGrabber::afterRender(cocos2d::CCTexture2D *pTexture)
	{
		CCLOGINFO("cocos2d: deallocing %p", this);
		glDeleteFramebuffersOES(1, &m_fbo);
	}
} // end of namespace cocos2d
