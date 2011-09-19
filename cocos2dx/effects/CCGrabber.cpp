/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2009      On-Core
 
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
#include "platform/platform.h"

namespace cocos2d
{
	CCGrabber::CCGrabber(void)
		: m_fbo(0)
		, m_oldFBO(0)
	{
		m_eGlesVersion = CCConfiguration::sharedConfiguration()->getGlesVersion();

		// If the gles version is lower than GLES_VER_1_0, 
		// all the functions in CCGrabber return directly.
		if (m_eGlesVersion <= GLES_VER_1_0)
		{
			return ;
		}

		// generate FBO
		ccglGenFramebuffers(1, &m_fbo);
	}

	void CCGrabber::grab(CCTexture2D *pTexture)
	{
		// If the gles version is lower than GLES_VER_1_0, 
		// all the functions in CCGrabber return directly.
		if (m_eGlesVersion <= GLES_VER_1_0)
		{
			return ;
		}

		glGetIntegerv(CC_GL_FRAMEBUFFER_BINDING, &m_oldFBO);

		// bind
		ccglBindFramebuffer(CC_GL_FRAMEBUFFER, m_fbo);

		// associate texture with FBO
		ccglFramebufferTexture2D(CC_GL_FRAMEBUFFER, CC_GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
			pTexture->getName(), 0);

		// check if it worked (probably worth doing :) )
		GLuint status = ccglCheckFramebufferStatus(CC_GL_FRAMEBUFFER);
		if (status != CC_GL_FRAMEBUFFER_COMPLETE)
		{
			CCLOG("Frame Grabber: could not attach texture to frmaebuffer");
		}

		ccglBindFramebuffer(CC_GL_FRAMEBUFFER, m_oldFBO);
	}
	
	void CCGrabber::beforeRender(CCTexture2D *pTexture)
	{
        CC_UNUSED_PARAM(pTexture);
		// If the gles version is lower than GLES_VER_1_0, 
		// all the functions in CCGrabber return directly.
		if (m_eGlesVersion <= GLES_VER_1_0)
		{
			return ;
		}

		glGetIntegerv(CC_GL_FRAMEBUFFER_BINDING, &m_oldFBO);
		ccglBindFramebuffer(CC_GL_FRAMEBUFFER, m_fbo);

		// BUG XXX: doesn't work with RGB565.

		/*glClearColor(0, 0, 0, 0);*/

		// BUG #631: To fix #631, uncomment the lines with #631
		// Warning: But it CCGrabber won't work with 2 effects at the same time
		glClearColor(0.0f,0.0f,0.0f,1.0f);	// #631

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glColorMask(true, true, true, false);	// #631
	}

	void CCGrabber::afterRender(cocos2d::CCTexture2D *pTexture)
	{
        CC_UNUSED_PARAM(pTexture);
		// If the gles version is lower than GLES_VER_1_0, 
		// all the functions in CCGrabber return directly.
		if (m_eGlesVersion <= GLES_VER_1_0)
		{
			return ;
		}

		ccglBindFramebuffer(CC_GL_FRAMEBUFFER, m_oldFBO);
		glColorMask(true, true, true, true);	// #631
	}

	CCGrabber::~CCGrabber()
	{
		// If the gles version is lower than GLES_VER_1_0, 
		// all the functions in CCGrabber return directly.
		if (m_eGlesVersion <= GLES_VER_1_0)
		{
			return ;
		}

		CCLOGINFO("cocos2d: deallocing %p", this);
		ccglDeleteFramebuffers(1, &m_fbo);
	}
} // end of namespace cocos2d
