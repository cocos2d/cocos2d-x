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
#include "support/ccUtils.h"
#include "CCTextureCache.h"
#include "CCFileUtils.h"
#include "CCGL.h"

namespace cocos2d { 

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
    removeAllChildrenWithCleanup(true);
    ccglDeleteFramebuffers(1, &m_uFBO);

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
	CC_SAFE_DELETE(pRet)
	return NULL;
}

bool CCRenderTexture::initWithWidthAndHeight(int w, int h, CCTexture2DPixelFormat eFormat)
{
	// If the gles version is lower than GLES_VER_1_0, 
	// some extended gles functions can't be implemented, so return false directly.
	if (CCConfiguration::sharedConfiguration()->getGlesVersion() <= GLES_VER_1_0)
	{
		return false;
	}

    bool bRet = false;
    do 
    {
        w *= (int)CC_CONTENT_SCALE_FACTOR();
        h *= (int)CC_CONTENT_SCALE_FACTOR();

        glGetIntegerv(CC_GL_FRAMEBUFFER_BINDING, &m_nOldFBO);

        // textures must be power of two squared
        unsigned int powW = ccNextPOT(w);
        unsigned int powH = ccNextPOT(h);

        void *data = malloc((int)(powW * powH * 4));
        CC_BREAK_IF(! data);

        memset(data, 0, (int)(powW * powH * 4));
        m_ePixelFormat = eFormat;

        m_pTexture = new CCTexture2D();
        CC_BREAK_IF(! m_pTexture);

        m_pTexture->initWithData(data, (CCTexture2DPixelFormat)m_ePixelFormat, powW, powH, CCSizeMake((float)w, (float)h));
        free( data );

        // generate FBO
        ccglGenFramebuffers(1, &m_uFBO);
        ccglBindFramebuffer(CC_GL_FRAMEBUFFER, m_uFBO);

        // associate texture with FBO
        ccglFramebufferTexture2D(CC_GL_FRAMEBUFFER, CC_GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_pTexture->getName(), 0);

        // check if it worked (probably worth doing :) )
        GLuint status = ccglCheckFramebufferStatus(CC_GL_FRAMEBUFFER);
        if (status != CC_GL_FRAMEBUFFER_COMPLETE)
        {
            CCAssert(0, "Render Texture : Could not attach texture to framebuffer");
            CC_SAFE_DELETE(m_pTexture);
            break;
        }

        m_pTexture->setAliasTexParameters();

        m_pSprite = CCSprite::spriteWithTexture(m_pTexture);

        m_pTexture->release();
        m_pSprite->setScaleY(-1);
        this->addChild(m_pSprite);

        ccBlendFunc tBlendFunc = {GL_ONE, GL_ONE_MINUS_SRC_ALPHA };
        m_pSprite->setBlendFunc(tBlendFunc);

        ccglBindFramebuffer(CC_GL_FRAMEBUFFER, m_nOldFBO);
        bRet = true;
    } while (0);
    return bRet;
    
}

void CCRenderTexture::begin()
{
	// Save the current matrix
	glPushMatrix();

	const CCSize& texSize = m_pTexture->getContentSizeInPixels();

	// Calculate the adjustment ratios based on the old and new projections
	CCSize size = CCDirector::sharedDirector()->getDisplaySizeInPixels();
	float widthRatio = size.width / texSize.width;
	float heightRatio = size.height / texSize.height;

	// Adjust the orthographic propjection and viewport
	ccglOrtho((float)-1.0 / widthRatio,  (float)1.0 / widthRatio, (float)-1.0 / heightRatio, (float)1.0 / heightRatio, -1,1);
    glViewport(0, 0, (GLsizei)texSize.width, (GLsizei)texSize.height);
//     CCDirector::sharedDirector()->getOpenGLView()->setViewPortInPoints(0, 0, texSize.width, texSize.height);

	glGetIntegerv(CC_GL_FRAMEBUFFER_BINDING, &m_nOldFBO);
	ccglBindFramebuffer(CC_GL_FRAMEBUFFER, m_uFBO);//Will direct drawing to the frame buffer created above

	// Issue #1145
	// There is no need to enable the default GL states here
	// but since CCRenderTexture is mostly used outside the "render" loop
	// these states needs to be enabled.
	// Since this bug was discovered in API-freeze (very close of 1.0 release)
	// This bug won't be fixed to prevent incompatibilities with code.
	// 
	// If you understand the above mentioned message, then you can comment the following line
	// and enable the gl states manually, in case you need them.

	CC_ENABLE_DEFAULT_GL_STATES();	
}

void CCRenderTexture::beginWithClear(float r, float g, float b, float a)
{
    this->begin();

	// save clear color
	GLfloat	clearColor[4];
	glGetFloatv(GL_COLOR_CLEAR_VALUE,clearColor); 

	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// restore clear color
	glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);     
}

void CCRenderTexture::end(bool bIsTOCacheTexture)
{
	ccglBindFramebuffer(CC_GL_FRAMEBUFFER, m_nOldFBO);
	// Restore the original matrix and viewport
	glPopMatrix();
	CCSize size = CCDirector::sharedDirector()->getDisplaySizeInPixels();
	//	glViewport(0, 0, (GLsizei)size.width, (GLsizei)size.height);
	CCDirector::sharedDirector()->getOpenGLView()->setViewPortInPoints(0, 0, size.width, size.height);

#if CC_ENABLE_CACHE_TEXTTURE_DATA
	if (bIsTOCacheTexture)
	{
		CC_SAFE_DELETE(m_pUITextureImage);

		// to get the rendered texture data
		const CCSize& s = m_pTexture->getContentSizeInPixels();
		int tx = (int)s.width;
		int ty = (int)s.height;
		m_pUITextureImage = new CCImage;
		if (true == getUIImageFromBuffer(m_pUITextureImage, 0, 0, tx, ty))
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

bool CCRenderTexture::saveBuffer(const char *szFilePath, int x, int y, int nWidth, int nHeight)
{
	bool bRet = false;

	CCImage *pImage = new CCImage();
	if (pImage != NULL && getUIImageFromBuffer(pImage, x, y, nWidth, nHeight))
	{
		bRet = pImage->saveToFile(szFilePath);
	}

	CC_SAFE_DELETE(pImage);
	return bRet;
}
bool CCRenderTexture::saveBuffer(int format, const char *fileName, int x, int y, int nWidth, int nHeight)
{
	bool bRet = false;
	CCAssert(format == kCCImageFormatJPG || format == kCCImageFormatPNG,
			 "the image can only be saved as JPG or PNG format");

	CCImage *pImage = new CCImage();
	if (pImage != NULL && getUIImageFromBuffer(pImage, x, y, nWidth, nHeight))
	{
		std::string fullpath = CCFileUtils::getWriteablePath() + fileName;
		
		bRet = pImage->saveToFile(fullpath.c_str());
	}

	CC_SAFE_DELETE(pImage);

	return bRet;
}

/* get buffer as UIImage */
bool CCRenderTexture::getUIImageFromBuffer(CCImage *pImage, int x, int y, int nWidth, int nHeight)
{
	if (NULL == pImage || NULL == m_pTexture)
	{
		return false;
	}

	const CCSize& s = m_pTexture->getContentSizeInPixels();
	int tx = (int)s.width;
	int ty = (int)s.height;

	if (x < 0 || x >= tx || y < 0 || y >= ty)
	{
		return false;
	}

	if (nWidth < 0 
		|| nHeight < 0
		|| (0 == nWidth && 0 != nHeight)
		|| (0 == nHeight && 0 != nWidth))
	{
		return false;
	}
	
	// to get the image size to save
	//		if the saving image domain exeeds the buffer texture domain,
	//		it should be cut
	int nSavedBufferWidth = nWidth;
	int nSavedBufferHeight = nHeight;
	if (0 == nWidth)
	{
		nSavedBufferWidth = tx;
	}
	if (0 == nHeight)
	{
		nSavedBufferHeight = ty;
	}
	nSavedBufferWidth = x + nSavedBufferWidth > tx ? (tx - x): nSavedBufferWidth;
	nSavedBufferHeight = y + nSavedBufferHeight > ty ? (ty - y): nSavedBufferHeight;

	GLubyte *pBuffer = NULL;
	GLubyte *pTempData = NULL;
	bool bRet = false;

	do
	{
		CCAssert(m_ePixelFormat == kCCTexture2DPixelFormat_RGBA8888, "only RGBA8888 can be saved as image");

		CC_BREAK_IF(! (pBuffer = new GLubyte[nSavedBufferWidth * nSavedBufferHeight * 4]));

		// On some machines, like Samsung i9000, Motorola Defy,
		// the dimension need to be a power of 2
		int nReadBufferWidth = 0;
		int nReadBufferHeight = 0;
		int nMaxTextureSize = 0;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &nMaxTextureSize);

		nReadBufferWidth = ccNextPOT(tx);
		nReadBufferHeight = ccNextPOT(ty);

		CC_BREAK_IF(0 == nReadBufferWidth || 0 == nReadBufferHeight);
		CC_BREAK_IF(nReadBufferWidth > nMaxTextureSize || nReadBufferHeight > nMaxTextureSize);

		CC_BREAK_IF(! (pTempData = new GLubyte[nReadBufferWidth * nReadBufferHeight * 4]));

		this->begin();
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glReadPixels(0,0,nReadBufferWidth,nReadBufferHeight,GL_RGBA,GL_UNSIGNED_BYTE, pTempData);
		this->end(false);

		// to get the actual texture data 
		// #640 the image read from rendertexture is upseted
		for (int i = 0; i < nSavedBufferHeight; ++i)
		{
			memcpy(&pBuffer[i * nSavedBufferWidth * 4], 
				&pTempData[(y + nSavedBufferHeight - i - 1) * nReadBufferWidth * 4 + x * 4], 
				nSavedBufferWidth * 4);
		}

		bRet = pImage->initWithImageData(pBuffer, nSavedBufferWidth * nSavedBufferHeight * 4, CCImage::kFmtRawData, nSavedBufferWidth, nSavedBufferHeight, 8);
	} while (0);

	CC_SAFE_DELETE_ARRAY(pBuffer);
	CC_SAFE_DELETE_ARRAY(pTempData);

	return bRet;
}


CCData * CCRenderTexture::getUIImageAsDataFromBuffer(int format)
{
    CC_UNUSED_PARAM(format);
    CCData *  pData     = NULL;
//@ todo CCRenderTexture::getUIImageAsDataFromBuffer

// #include "Availability.h"
// #include "UIKit.h"

//     GLubyte * pBuffer   = NULL;
//     GLubyte * pPixels   = NULL;
//     do 
//     {
//         CC_BREAK_IF(! m_pTexture);
// 
//         CCAssert(m_ePixelFormat == kCCTexture2DPixelFormat_RGBA8888, "only RGBA8888 can be saved as image");
// 
//         const CCSize& s = m_pTexture->getContentSizeInPixels();
//         int tx = s.width;
//         int ty = s.height;
// 
//         int bitsPerComponent = 8;
//         int bitsPerPixel = 32;
// 
//         int bytesPerRow = (bitsPerPixel / 8) * tx;
//         int myDataLength = bytesPerRow * ty;
// 
//         CC_BREAK_IF(! (pBuffer = new GLubyte[tx * ty * 4]));
//         CC_BREAK_IF(! (pPixels = new GLubyte[tx * ty * 4]));
// 
//         this->begin();
//         glReadPixels(0,0,tx,ty,GL_RGBA,GL_UNSIGNED_BYTE, pBuffer);
//         this->end();
// 
//         int x,y;
// 
//         for(y = 0; y <ty; y++) {
//             for(x = 0; x <tx * 4; x++) {
//                 pPixels[((ty - 1 - y) * tx * 4 + x)] = pBuffer[(y * 4 * tx + x)];
//             }
//         }
// 
//         if (format == kCCImageFormatRawData)
//         {
//             pData = CCData::dataWithBytesNoCopy(pPixels, myDataLength);
//             break;
//         }

        //@ todo impliment save to jpg or png
        /*
        CGImageCreate(size_t width, size_t height,
        size_t bitsPerComponent, size_t bitsPerPixel, size_t bytesPerRow,
        CGColorSpaceRef space, CGBitmapInfo bitmapInfo, CGDataProviderRef provider,
        const CGFloat decode[], bool shouldInterpolate,
        CGColorRenderingIntent intent)
        */
        // make data provider with data.
//         CGBitmapInfo bitmapInfo = kCGImageAlphaPremultipliedLast | kCGBitmapByteOrderDefault;
//         CGDataProviderRef provider		= CGDataProviderCreateWithData(NULL, pixels, myDataLength, NULL);
//         CGColorSpaceRef colorSpaceRef	= CGColorSpaceCreateDeviceRGB();
//         CGImageRef iref					= CGImageCreate(tx, ty,
//             bitsPerComponent, bitsPerPixel, bytesPerRow,
//             colorSpaceRef, bitmapInfo, provider,
//             NULL, false,
//             kCGRenderingIntentDefault);
// 
//         UIImage* image					= [[UIImage alloc] initWithCGImage:iref];
// 
//         CGImageRelease(iref);	
//         CGColorSpaceRelease(colorSpaceRef);
//         CGDataProviderRelease(provider);
// 
// 
// 
//         if (format == kCCImageFormatPNG)
//             data = UIImagePNGRepresentation(image);
//         else
//             data = UIImageJPEGRepresentation(image, 1.0f);
// 
//         [image release];
//     } while (0);
//     
//     CC_SAFE_DELETE_ARRAY(pBuffer);
//     CC_SAFE_DELETE_ARRAY(pPixels);
	return pData;
}

} // namespace cocos2d
