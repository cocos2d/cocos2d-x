/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2009      Jason Booth

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

#include "CCConfiguration.h"
#include "CCRenderTexture.h"
#include "CCDirector.h"
#include "platform/platform.h"
#include "CCImage.h"
#include "CCGLProgram.h"
#include "ccGLStateCache.h"
#include "CCConfiguration.h"
#include "support/ccUtils.h"
#include "CCTextureCache.h"
#include "CCFileUtils.h"
#include "CCGL.h"
// extern
#include "kazmath/GL/matrix.h"

NS_CC_BEGIN

// implementation CCRenderTexture
CCRenderTexture::CCRenderTexture()
: m_pSprite(NULL)
, m_uFBO(0)
, m_nOldFBO(0)
, m_pTexture(0)
, m_pUITextureImage(NULL)
, m_ePixelFormat(kCCTexture2DPixelFormat_RGBA8888)
{
}

CCRenderTexture::~CCRenderTexture()
{
//TODO: 2.0 remove this line.    removeAllChildrenWithCleanup(true);
    glDeleteFramebuffers(1, &m_uFBO);

    CC_SAFE_DELETE(m_pUITextureImage);
}

CCSprite * CCRenderTexture::getSprite()
{
    return m_pSprite;
}
void CCRenderTexture::setSprite(CCSprite* var)
{
    m_pSprite = var;
}

CCRenderTexture * CCRenderTexture::renderTextureWithWidthAndHeight(int w, int h, CCTexture2DPixelFormat eFormat)
{
    CCRenderTexture *pRet = new CCRenderTexture();

    if(pRet && pRet->initWithWidthAndHeight(w, h, eFormat))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCRenderTexture * CCRenderTexture::renderTextureWithWidthAndHeight(int w, int h)
{
    CCRenderTexture *pRet = new CCRenderTexture();

    if(pRet && pRet->initWithWidthAndHeight(w, h, kCCTexture2DPixelFormat_RGBA8888))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCRenderTexture::initWithWidthAndHeight(int w, int h, CCTexture2DPixelFormat eFormat)
{
    CCAssert(m_ePixelFormat != kCCTexture2DPixelFormat_A8, "only RGB and RGBA formats are valid for a render texture");

    bool bRet = false;
    do 
    {
        w *= (int)CC_CONTENT_SCALE_FACTOR();
        h *= (int)CC_CONTENT_SCALE_FACTOR();

        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_nOldFBO);

        // textures must be power of two squared
        unsigned int powW = 0;
        unsigned int powH = 0;

        if( CCConfiguration::sharedConfiguration()->isSupportsNPOT() ) {
            powW = w;
            powH = h;
        } else {
            powW = ccNextPOT(w);
            powH = ccNextPOT(h);
        }

        void *data = malloc((int)(powW * powH * 4));
        CC_BREAK_IF(! data);

        memset(data, 0, (int)(powW * powH * 4));
        m_ePixelFormat = eFormat;

        m_pTexture = new CCTexture2D();
        CC_BREAK_IF(! m_pTexture);

        m_pTexture->initWithData(data, (CCTexture2DPixelFormat)m_ePixelFormat, powW, powH, CCSizeMake((float)w, (float)h));
        free( data );

        // generate FBO
        glGenFramebuffers(1, &m_uFBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_uFBO);

        // associate texture with FBO
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_pTexture->getName(), 0);

        // check if it worked (probably worth doing :) )
        CCAssert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Could not attach texture to framebuffer");

        m_pTexture->setAliasTexParameters();

        m_pSprite = CCSprite::spriteWithTexture(m_pTexture);

        m_pTexture->release();
        m_pSprite->setScaleY(-1);
        this->addChild(m_pSprite);

        ccBlendFunc tBlendFunc = {GL_ONE, GL_ONE_MINUS_SRC_ALPHA };
        m_pSprite->setBlendFunc(tBlendFunc);

        glBindFramebuffer(GL_FRAMEBUFFER, m_nOldFBO);
        bRet = true;
    } while (0);
    return bRet;
    
}

void CCRenderTexture::begin()
{
    // Save the current matrix
    kmGLPushMatrix();

    const CCSize& texSize = m_pTexture->getContentSizeInPixels();

    // Calculate the adjustment ratios based on the old and new projections
    CCDirector *director = CCDirector::sharedDirector();
    CCSize size = director->getWinSizeInPixels();
    float widthRatio = size.width / texSize.width;
    float heightRatio = size.height / texSize.height;

    // Adjust the orthographic projection and viewport
    glViewport(0, 0, (GLsizei)(texSize.width * CC_CONTENT_SCALE_FACTOR()), (GLsizei)(texSize.height * CC_CONTENT_SCALE_FACTOR()));

    // special viewport for 3d projection + retina display
    if ( director->getProjection() == kCCDirectorProjection3D && CC_CONTENT_SCALE_FACTOR() != 1 )
    {
        glViewport((GLsizei)(-texSize.width/2), (GLsizei)(-texSize.height/2), (GLsizei)(texSize.width * CC_CONTENT_SCALE_FACTOR()), (GLsizei)(texSize.height * CC_CONTENT_SCALE_FACTOR()));
    }

    kmMat4 orthoMatrix;
    kmMat4OrthographicProjection(&orthoMatrix, (float)-1.0 / widthRatio,  (float)1.0 / widthRatio,
        (float)-1.0 / heightRatio, (float)1.0 / heightRatio, -1,1 );
    kmGLMultMatrix(&orthoMatrix);

    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_nOldFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_uFBO);
}

void CCRenderTexture::beginWithClear(float r, float g, float b, float a)
{
    this->begin();

    // save clear color
    GLfloat    clearColor[4];
    glGetFloatv(GL_COLOR_CLEAR_VALUE,clearColor); 

    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // restore clear color
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);     
}

void CCRenderTexture::end(bool bIsTOCacheTexture)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_nOldFBO);
    kmGLPopMatrix();

    CCDirector *director = CCDirector::sharedDirector();

    CCSize size = director->getWinSizeInPixels();

    // restore viewport
    glViewport(0, 0, GLsizei(size.width * CC_CONTENT_SCALE_FACTOR()), GLsizei(size.height * CC_CONTENT_SCALE_FACTOR()));

    // special viewport for 3d projection + retina display
    if ( director->getProjection() == kCCDirectorProjection3D && CC_CONTENT_SCALE_FACTOR() != 1 )
    {
        glViewport((GLsizei)(-size.width/2), (GLsizei)(-size.height/2), (GLsizei)(size.width * CC_CONTENT_SCALE_FACTOR()), (GLsizei)(size.height * CC_CONTENT_SCALE_FACTOR()));
    }

//TODO: Does this line take effect?    director->setProjection(director->getProjection());

#if CC_ENABLE_CACHE_TEXTTURE_DATA
    if (bIsTOCacheTexture)
    {
        CC_SAFE_DELETE(m_pUITextureImage);

		// to get the rendered texture data
		const CCSize& s = m_pTexture->getContentSizeInPixels();
        m_pUITextureImage = newCCImage();

		if (m_pUITextureImage)
		{
			VolatileTexture::addDataTexture(m_pTexture, m_pUITextureImage->getData(), kTexture2DPixelFormat_RGBA8888, s);
		} 
		else
		{
			CCLOG("Cache rendertexture failed!");
		}
	}
#endif
}

void CCRenderTexture::clear(float r, float g, float b, float a)
{
    this->beginWithClear(r, g, b, a);
    this->end();
}

bool CCRenderTexture::saveToFile(const char *szFilePath)
{
    bool bRet = false;

    CCImage *pImage = newCCImage();
    if (pImage)
    {
        bRet = pImage->saveToFile(szFilePath, kCCImageFormatJPEG);
    }

    CC_SAFE_DELETE(pImage);
    return bRet;
}
bool CCRenderTexture::saveToFile(const char *fileName, tCCImageFormat format)
{
    bool bRet = false;
    CCAssert(format == kCCImageFormatJPEG || format == kCCImageFormatPNG,
             "the image can only be saved as JPG or PNG format");

    CCImage *pImage = newCCImage();
    if (pImage)
    {
        std::string fullpath = CCFileUtils::getWriteablePath() + fileName;
        
        bRet = pImage->saveToFile(fullpath.c_str(), true);
    }

    CC_SAFE_DELETE(pImage);

    return bRet;
}

/* get buffer as CCImage */
CCImage* CCRenderTexture::newCCImage()
{
    CCAssert(m_ePixelFormat == kCCTexture2DPixelFormat_RGBA8888, "only RGBA8888 can be saved as image");

    if (NULL == m_pTexture)
    {
        return NULL;
    }

    const CCSize& s = m_pTexture->getContentSizeInPixels();

    // to get the image size to save
    //        if the saving image domain exeeds the buffer texture domain,
    //        it should be cut
    int nSavedBufferWidth = (int)s.width;
    int nSavedBufferHeight = (int)s.height;

    GLubyte *pBuffer = NULL;
    GLubyte *pTempData = NULL;
    CCImage *pImage = new CCImage();

    do
    {
        CC_BREAK_IF(! (pBuffer = new GLubyte[nSavedBufferWidth * nSavedBufferHeight * 4]));


        if(! (pTempData = new GLubyte[nSavedBufferWidth * nSavedBufferHeight * 4]))
        {
            delete[] pBuffer;
            pBuffer = NULL;
            break;
        }

        this->begin();
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glReadPixels(0,0,nSavedBufferWidth, nSavedBufferHeight,GL_RGBA,GL_UNSIGNED_BYTE, pTempData);
        this->end(false);

        // to get the actual texture data 
        // #640 the image read from rendertexture is upseted
        for (int i = 0; i < nSavedBufferHeight; ++i)
        {
            memcpy(&pBuffer[i * nSavedBufferWidth * 4], 
                &pTempData[(nSavedBufferHeight - i - 1) * nSavedBufferWidth * 4], 
                nSavedBufferWidth * 4);
        }

        pImage->initWithImageData(pBuffer, nSavedBufferWidth * nSavedBufferHeight * 4, CCImage::kFmtRawData, nSavedBufferWidth, nSavedBufferHeight, 8);
    } while (0);

    CC_SAFE_DELETE_ARRAY(pBuffer);
    CC_SAFE_DELETE_ARRAY(pTempData);

    return pImage;
}

NS_CC_END
