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

#include "CCRenderTexture.h"
#include "CCDirector.h"
#include "platform/platform.h"
#include "CCXUIImage.h"

#include <GLES/glext.h>

namespace cocos2d { 

	// implementation CCRenderTexture
	CCSprite * CCRenderTexture::getSprite()
	{
		return m_pSprite;
	}
	void CCRenderTexture::setSprite(CCSprite* var)
	{
		m_pSprite = var;
	}

	CCRenderTexture * CCRenderTexture::renderTextureWithWidthAndHeight(int width, int height)
	{
		CCRenderTexture *pRet = new CCRenderTexture();

		if(pRet && pRet->initWithWidthAndHeight(width,height))
		{
			pRet->autorelease();
			return pRet;
		}
		CCX_SAFE_DELETE(pRet)
		return NULL;
	}
	bool CCRenderTexture::initWithWidthAndHeight(int width, int height)
	{
		glGetIntegerv(GL_FRAMEBUFFER_BINDING_OES, &m_nOldFBO);
		CCTexture2DPixelFormat format = kCCTexture2DPixelFormat_RGBA8888;  
		// textures must be power of two squared
		int pow = 8;
		while (pow < width || pow < height)
		{
			pow*=2;
		}
		void *data = malloc((int)(pow * pow * 4));
		memset(data, 0, (int)(pow * pow * 4));
		m_pTexture = new CCTexture2D();
		m_pTexture->initWithData(data, format, pow, pow, CGSizeMake((float)width, (float)height));
		free( data );
		// generate FBO
		glGenFramebuffersOES(1, &m_uFBO);
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, m_uFBO);
		// associate texture with FBO
		glFramebufferTexture2DOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_TEXTURE_2D, m_pTexture->getName(), 0);

		// check if it worked (probably worth doing :) )
		GLuint status = glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES);
		if (status != GL_FRAMEBUFFER_COMPLETE_OES)
		{
			NSAssert(0, "Render Texture : Could not attach texture to framebuffer")
			CCX_SAFE_DELETE(m_pTexture);
			return false;
		}
		m_pSprite = CCSprite::spriteWithTexture(m_pTexture);
		m_pTexture->release();
		m_pSprite->setScaleY(-1);
		this->addChild(m_pSprite);
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, m_nOldFBO);
		return true;
	}
	CCRenderTexture::~CCRenderTexture()
	{
		glDeleteFramebuffersOES(1, &m_uFBO);
	}
	void CCRenderTexture::begin()
	{
		CC_DISABLE_DEFAULT_GL_STATES();
		// Save the current matrix
		glPushMatrix();

		CGSize textureSize = m_pTexture->getContentSize();

		// Calculate the adjustment ratios based on the old and new projections
		CGSize size = CCDirector::sharedDirector()->getDisplaySize();
		float widthRatio = size.width / textureSize.width;
		float heightRatio = size.height / textureSize.height;

		// Adjust the orthographic propjection and viewport
		glOrthof((float)-1.0 / widthRatio,  (float)1.0 / widthRatio, (float)-1.0 / heightRatio, (float)1.0 / heightRatio, -1,1);
		glViewport(0, 0, (GLsizei)textureSize.width, (GLsizei)textureSize.height);

		glGetIntegerv(GL_FRAMEBUFFER_BINDING_OES, &m_nOldFBO);
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, m_uFBO);//Will direct drawing to the frame buffer created above

		CC_ENABLE_DEFAULT_GL_STATES();	
	}
	void CCRenderTexture::end()
	{
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, m_nOldFBO);
		// Restore the original matrix and viewport
		glPopMatrix();
		CGSize size = CCDirector::sharedDirector()->getDisplaySize();
		glViewport(0, 0, (GLsizei)size.width, (GLsizei)size.height);

		glColorMask(true, true, true, true);
	}
	void CCRenderTexture::clear(float r, float g, float b, float a)
	{
		this->begin();
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColorMask(true, true, true, false);
		this->end();
	}
	bool CCRenderTexture::saveBuffer(const char *name)
	{
		return this->saveBuffer(name, kImageFormatJPG);
	}
	bool CCRenderTexture::saveBuffer(const char *name, int format)
	{
		bool bRet = false;
		UIImage *myImage = this->getUIImageFromBuffer();
		if (myImage)
		{
			bRet = myImage->save(name, format);
			delete myImage;
		}
		return bRet;
	}

	/* get buffer as UIImage */
	UIImage * CCRenderTexture::getUIImageFromBuffer()
	{
 		int tx = (int)m_pTexture->getContentSize().width;
 		int ty = (int)m_pTexture->getContentSize().height;
 
 		char * pBuffer = new char[tx * ty * 4];
 
 		this->begin();
 		glReadPixels(0,0,tx,ty,GL_RGBA,GL_UNSIGNED_BYTE, pBuffer);
 		this->end();
 
 		UIImage *pRet = new UIImage();
 		pRet->initWithBuffer(tx, ty, (unsigned char*)pBuffer);
		delete[] pBuffer;
 		return pRet;
	}

} // namespace cocos2d
