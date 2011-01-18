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
#include "support/ccUtils.h"

#include <GLES/glext.h>

namespace cocos2d { 

// implementation CCRenderTexture
CCRenderTexture::CCRenderTexture()
: m_pSprite(NULL)
, m_uFBO(0)
, m_nOldFBO(0)
, m_pTexture(0)
, m_ePixelFormat(kCCPixelFormatRGBA8888)
{
    memset(m_aClearColor, 0, sizeof(m_aClearColor));
}

CCRenderTexture::~CCRenderTexture()
{
    removeAllChildrenWithCleanup(true);
    ccglDeleteFramebuffers(1, &m_uFBO);
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
    CCX_SAFE_DELETE(pRet);
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
	CCX_SAFE_DELETE(pRet)
	return NULL;
}
bool CCRenderTexture::initWithWidthAndHeight(int w, int h, CCTexture2DPixelFormat eFormat)
{
    bool bRet = false;
    do 
    {
        w *= (int)CC_CONTENT_SCALE_FACTOR();
        h *= (int)CC_CONTENT_SCALE_FACTOR();

        glGetIntegerv(GL_FRAMEBUFFER_BINDING_OES, &m_nOldFBO);

        // textures must be power of two squared
        unsigned int powW = ccNextPOT(w);
        unsigned int powH = ccNextPOT(h);

        void *data = malloc((int)(powW * powH * 4));
        CCX_BREAK_IF(! data);

        memset(data, 0, (int)(powW * powH * 4));
        m_ePixelFormat = eFormat;

        m_pTexture = new CCTexture2D();
        CCX_BREAK_IF(! m_pTexture);

        m_pTexture->initWithData(data, (CCTexture2DPixelFormat)m_ePixelFormat, powW, powH, CGSizeMake((float)w, (float)h));
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
            NSAssert(0, "Render Texture : Could not attach texture to framebuffer");
            CCX_SAFE_DELETE(m_pTexture);
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
    saveGLstate();

	CC_DISABLE_DEFAULT_GL_STATES();
	// Save the current matrix
	glPushMatrix();

	CGSize texSize = m_pTexture->getContentSizeInPixels();

	// Calculate the adjustment ratios based on the old and new projections
	CGSize size = CCDirector::sharedDirector()->getDisplaySizeInPixels();
	float widthRatio = size.width / texSize.width;
	float heightRatio = size.height / texSize.height;

	// Adjust the orthographic propjection and viewport
	ccglOrtho((float)-1.0 / widthRatio,  (float)1.0 / widthRatio, (float)-1.0 / heightRatio, (float)1.0 / heightRatio, -1,1);
	glViewport(0, 0, (GLsizei)texSize.width, (GLsizei)texSize.height);

	glGetIntegerv(CC_GL_FRAMEBUFFER_BINDING, &m_nOldFBO);
	ccglBindFramebuffer(CC_GL_FRAMEBUFFER, m_uFBO);//Will direct drawing to the frame buffer created above

	CC_ENABLE_DEFAULT_GL_STATES();	
}

void CCRenderTexture::beginWithClear(float r, float g, float b, float a)
{
    this->saveGLstate();

    CC_DISABLE_DEFAULT_GL_STATES();
    // Save the current matrix
    glPushMatrix();

    CGSize texSize = m_pTexture->getContentSizeInPixels();

    // Calculate the adjustment ratios based on the old and new projections
    CGSize size = CCDirector::sharedDirector()->getDisplaySizeInPixels();
    float widthRatio = size.width / texSize.width;
    float heightRatio = size.height / texSize.height;

    // Adjust the orthographic propjection and viewport
    ccglOrtho((float)-1.0 / widthRatio,  (float)1.0 / widthRatio, (float)-1.0 / heightRatio, (float)1.0 / heightRatio, -1,1);
    glViewport(0, 0, (GLsizei)texSize.width, (GLsizei)texSize.height);

    glGetIntegerv(CC_GL_FRAMEBUFFER_BINDING, &m_nOldFBO);
    ccglBindFramebuffer(CC_GL_FRAMEBUFFER, m_uFBO);//Will direct drawing to the frame buffer created above

    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    CC_ENABLE_DEFAULT_GL_STATES();
}

void CCRenderTexture::end()
{
	ccglBindFramebuffer(CC_GL_FRAMEBUFFER, m_nOldFBO);
	// Restore the original matrix and viewport
	glPopMatrix();
	CGSize size = CCDirector::sharedDirector()->getDisplaySizeInPixels();
	glViewport(0, 0, (GLsizei)size.width, (GLsizei)size.height);
    this->restoreGLstate();
}

void CCRenderTexture::clear(float r, float g, float b, float a)
{
	this->begin();
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->end();
}

void CCRenderTexture::saveGLstate()
{
    glGetFloatv(GL_COLOR_CLEAR_VALUE, m_aClearColor);
}

void CCRenderTexture::restoreGLstate()
{
    glClearColor(m_aClearColor[0], m_aClearColor[1], m_aClearColor[2], m_aClearColor[3]);
}


bool CCRenderTexture::saveBuffer(const char *name)
{
	return this->saveBuffer(name, kCCImageFormatJPG);
}
bool CCRenderTexture::saveBuffer(const char *fileName, int format)
{
	bool bRet = false;
//@ todo CCRenderTexture::saveBuffer
// 	UIImage *myImage = this->getUIImageFromBuffer(format);
//     NSArray *paths					= NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
//     NSString *documentsDirectory	= [paths objectAtIndex:0];
//     NSString *fullPath				= [documentsDirectory stringByAppendingPathComponent:fileName];

//     NSData * data = this->getUIImageAsDataFromBuffer(format);
// 	if (data)
// 	{
//         bRet = data->writeToFile(path, true);
// 		delete data;
//         bRet = true;
// 	}
	return bRet;
}

NSData * CCRenderTexture::getUIImageAsDataFromBuffer(int format)
{
    NSData *  pData     = NULL;
//@ todo CCRenderTexture::getUIImageAsDataFromBuffer

// #include "Availability.h"
// #include "UIKit.h"

//     GLubyte * pBuffer   = NULL;
//     GLubyte * pPixels   = NULL;
//     do 
//     {
//         CCX_BREAK_IF(! m_pTexture);
// 
//         NSAssert(m_ePixelFormat == kCCTexture2DPixelFormat_RGBA8888, "only RGBA8888 can be saved as image");
// 
//         CGSize s = m_pTexture->getContentSizeInPixels();
//         int tx = s.width;
//         int ty = s.height;
// 
//         int bitsPerComponent = 8;
//         int bitsPerPixel = 32;
// 
//         int bytesPerRow = (bitsPerPixel / 8) * tx;
//         int myDataLength = bytesPerRow * ty;
// 
//         CCX_BREAK_IF(! (pBuffer = new GLubyte[tx * ty * 4]));
//         CCX_BREAK_IF(! (pPixels = new GLubyte[tx * ty * 4]));
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
//             pData = NSData::dataWithBytesNoCopy(pPixels, myDataLength);
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
//     CCX_SAFE_DELETE_ARRAY(pBuffer);
//     CCX_SAFE_DELETE_ARRAY(pPixels);
	return pData;
}

} // namespace cocos2d
