/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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
#include "misc_nodes/CCRenderTexture.h"
#include "CCDirector.h"
#include "platform/platform.h"
#include "platform/CCImage.h"
#include "shaders/CCGLProgram.h"
#include "shaders/ccGLStateCache.h"
#include "CCConfiguration.h"
#include "support/ccUtils.h"
#include "textures/CCTextureCache.h"
#include "platform/CCFileUtils.h"
#include "CCGL.h"
#include "support/CCNotificationCenter.h"
#include "CCEventType.h"
#include "effects/CCGrid.h"
// extern
#include "kazmath/GL/matrix.h"

NS_CC_BEGIN

// implementation CCRenderTexture
CCRenderTexture::CCRenderTexture()
: m_pSprite(NULL)
, m_uFBO(0)
, m_uDepthRenderBufffer(0)
, m_nOldFBO(0)
, m_pTexture(0)
, m_pTextureCopy(0)
, m_pUITextureImage(NULL)
, m_ePixelFormat(kCCTexture2DPixelFormat_RGBA8888)
, m_uClearFlags(0)
, m_sClearColor(ccc4f(0,0,0,0))
, m_fDlearDepth(0.0f)
, m_nClearStencil(0)
, m_bAutoDraw(false)
{
    // Listen this event to save render texture before come to background.
    // Then it can be restored after coming to foreground on Android.
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                                                             callfuncO_selector(CCRenderTexture::listenToBackground),
                                                                             EVENT_COME_TO_BACKGROUND,
                                                                             NULL);
}

CCRenderTexture::~CCRenderTexture()
{
    CC_SAFE_RELEASE(m_pSprite);
    CC_SAFE_RELEASE(m_pTextureCopy);
    
    glDeleteFramebuffers(1, &m_uFBO);
    if (m_uDepthRenderBufffer)
    {
        glDeleteRenderbuffers(1, &m_uDepthRenderBufffer);
    }
    CC_SAFE_DELETE(m_pUITextureImage);
    
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVENT_COME_TO_BACKGROUND);
}

void CCRenderTexture::listenToBackground(cocos2d::CCObject *obj)
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    
    CC_SAFE_DELETE(m_pUITextureImage);
    
    // to get the rendered texture data
    m_pUITextureImage = newCCImage();


    if (m_pUITextureImage)
    {
        const CCSize& s = m_pTexture->getContentSizeInPixels();
        VolatileTexture::addDataTexture(m_pTexture, m_pUITextureImage->getData(), kTexture2DPixelFormat_RGBA8888, s);
    } 
    else
    {
        CCLOG("Cache rendertexture failed!");
    }
#endif
}

CCSprite * CCRenderTexture::getSprite()
{
    return m_pSprite;
}

void CCRenderTexture::setSprite(CCSprite* var)
{
    CC_SAFE_RELEASE(m_pSprite);
    m_pSprite = var;
    CC_SAFE_RETAIN(m_pSprite);
}

unsigned int CCRenderTexture::getClearFlags() const
{
    return m_uClearFlags;
}

void CCRenderTexture::setClearFlags(unsigned int uClearFlags)
{
    m_uClearFlags = uClearFlags;
}

const ccColor4F& CCRenderTexture::getClearColor() const
{
    return m_sClearColor;
}

void CCRenderTexture::setClearColor(const ccColor4F &clearColor)
{
    m_sClearColor = clearColor;
}

float CCRenderTexture::getClearDepth() const
{
    return m_fDlearDepth;
}

void CCRenderTexture::setClearDepth(float fClearDepth)
{
    m_fDlearDepth = fClearDepth;
}

int CCRenderTexture::getClearStencil() const
{
    return m_nClearStencil;
}

void CCRenderTexture::setClearStencil(float fClearStencil)
{
    m_nClearStencil = fClearStencil;
}

bool CCRenderTexture::isAutoDraw() const
{
    return m_bAutoDraw;
}

void CCRenderTexture::setAutoDraw(bool bAutoDraw)
{
    m_bAutoDraw = bAutoDraw;
}

CCRenderTexture * CCRenderTexture::renderTextureWithWidthAndHeight(int w, int h, CCTexture2DPixelFormat eFormat)
{
    return CCRenderTexture::create(w, h, eFormat);
}

CCRenderTexture * CCRenderTexture::create(int w, int h, CCTexture2DPixelFormat eFormat)
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

CCRenderTexture * CCRenderTexture::renderTextureWithWidthAndHeight(int w ,int h, CCTexture2DPixelFormat eFormat, GLuint uDepthStencilFormat)
{
    return CCRenderTexture::create(w, h, eFormat, uDepthStencilFormat);
}

CCRenderTexture * CCRenderTexture::create(int w ,int h, CCTexture2DPixelFormat eFormat, GLuint uDepthStencilFormat)
{
    CCRenderTexture *pRet = new CCRenderTexture();

    if(pRet && pRet->initWithWidthAndHeight(w, h, eFormat, uDepthStencilFormat))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCRenderTexture * CCRenderTexture::renderTextureWithWidthAndHeight(int w, int h)
{
    return CCRenderTexture::create(w, h);
}

CCRenderTexture * CCRenderTexture::create(int w, int h)
{
    CCRenderTexture *pRet = new CCRenderTexture();

    if(pRet && pRet->initWithWidthAndHeight(w, h, kCCTexture2DPixelFormat_RGBA8888, 0))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCRenderTexture::initWithWidthAndHeight(int w, int h, CCTexture2DPixelFormat eFormat)
{
    return initWithWidthAndHeight(w, h, eFormat, 0);
}

bool CCRenderTexture::initWithWidthAndHeight(int w, int h, CCTexture2DPixelFormat eFormat, GLuint uDepthStencilFormat)
{
    CCAssert(m_ePixelFormat != kCCTexture2DPixelFormat_A8, "only RGB and RGBA formats are valid for a render texture");

    bool bRet = false;
    void *data = NULL;
    do 
    {
        w = (int)(w * CC_CONTENT_SCALE_FACTOR());
        h = (int)(h * CC_CONTENT_SCALE_FACTOR());

        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_nOldFBO);

        // textures must be power of two squared
        unsigned int powW = 0;
        unsigned int powH = 0;

        if (CCConfiguration::sharedConfiguration()->supportsNPOT())
        {
            powW = w;
            powH = h;
        }
        else
        {
            powW = ccNextPOT(w);
            powH = ccNextPOT(h);
        }

        data = malloc((int)(powW * powH * 4));
        CC_BREAK_IF(! data);

        memset(data, 0, (int)(powW * powH * 4));
        m_ePixelFormat = eFormat;

        m_pTexture = new CCTexture2D();
        if (m_pTexture)
        {
            m_pTexture->initWithData(data, (CCTexture2DPixelFormat)m_ePixelFormat, powW, powH, CCSizeMake((float)w, (float)h));
        }
        else
        {
            break;
        }
        GLint oldRBO;
        glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldRBO);
        
        if (CCConfiguration::sharedConfiguration()->checkForGLExtension("GL_QCOM"))
        {
            m_pTextureCopy = new CCTexture2D();
            if (m_pTextureCopy)
            {
                m_pTextureCopy->initWithData(data, (CCTexture2DPixelFormat)m_ePixelFormat, powW, powH, CCSizeMake((float)w, (float)h));
            }
            else
            {
                break;
            }
        }

        // generate FBO
        glGenFramebuffers(1, &m_uFBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_uFBO);

        // associate texture with FBO
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_pTexture->getName(), 0);

        if (m_uDepthRenderBufffer != 0) 
        {
            //create and attach depth buffer
            glGenRenderbuffers(1, &m_uDepthRenderBufffer);
            glBindRenderbuffer(GL_RENDERBUFFER, m_uDepthRenderBufffer);
            glRenderbufferStorage(GL_RENDERBUFFER, uDepthStencilFormat, (GLsizei)powW, (GLsizei)powH);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_uDepthRenderBufffer);

            // if depth format is the one with stencil part, bind same render buffer as stencil attachment
            if (uDepthStencilFormat == GL_DEPTH24_STENCIL8)
            {
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_uDepthRenderBufffer);
            }
        }

        // check if it worked (probably worth doing :) )
        CCAssert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Could not attach texture to framebuffer");

        m_pTexture->setAliasTexParameters();

        // retained
        setSprite(CCSprite::createWithTexture(m_pTexture));

        m_pTexture->release();
        m_pSprite->setScaleY(-1);

        ccBlendFunc tBlendFunc = {GL_ONE, GL_ONE_MINUS_SRC_ALPHA };
        m_pSprite->setBlendFunc(tBlendFunc);

        glBindRenderbuffer(GL_RENDERBUFFER, oldRBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_nOldFBO);
        
        // Diabled by default.
        m_bAutoDraw = false;
        
        // add sprite for backward compatibility
        addChild(m_pSprite);
        
        bRet = true;
    } while (0);
    
    CC_SAFE_FREE(data);
    
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
    glViewport(0, 0, (GLsizei)texSize.width, (GLsizei)texSize.height);


    kmMat4 orthoMatrix;
    kmMat4OrthographicProjection(&orthoMatrix, (float)-1.0 / widthRatio,  (float)1.0 / widthRatio,
        (float)-1.0 / heightRatio, (float)1.0 / heightRatio, -1,1 );
    kmGLMultMatrix(&orthoMatrix);

    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_nOldFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_uFBO);
    
    /*  Certain Qualcomm Andreno gpu's will retain data in memory after a frame buffer switch which corrupts the render to the texture. The solution is to clear the frame buffer before rendering to the texture. However, calling glClear has the unintended result of clearing the current texture. Create a temporary texture to overcome this. At the end of CCRenderTexture::begin(), switch the attached texture to the second one, call glClear, and then switch back to the original texture. This solution is unnecessary for other devices as they don't have the same issue with switching frame buffers.
     */
    if (CCConfiguration::sharedConfiguration()->checkForGLExtension("GL_QCOM"))
    {
        // -- bind a temporary texture so we can clear the render buffer without losing our texture
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_pTextureCopy->getName(), 0);
        CHECK_GL_ERROR_DEBUG();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_pTexture->getName(), 0);
    }
}

void CCRenderTexture::beginWithClear(float r, float g, float b, float a)
{
    beginWithClear(r, g, b, a, 0, 0, GL_COLOR_BUFFER_BIT);
}

void CCRenderTexture::beginWithClear(float r, float g, float b, float a, float depthValue)
{
    beginWithClear(r, g, b, a, depthValue, 0, GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void CCRenderTexture::beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue)
{
    beginWithClear(r, g, b, a, depthValue, stencilValue, GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
}

void CCRenderTexture::beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue, GLbitfield flags)
{
    this->begin();

    // save clear color
    GLfloat	clearColor[4] = {0.0f};
    GLfloat depthClearValue = 0.0f;
    int stencilClearValue = 0;
    
    if (flags & GL_COLOR_BUFFER_BIT)
    {
        glGetFloatv(GL_COLOR_CLEAR_VALUE,clearColor);
        glClearColor(r, g, b, a);
    }
    
    if (flags & GL_DEPTH_BUFFER_BIT)
    {
        glGetFloatv(GL_DEPTH_CLEAR_VALUE, &depthClearValue);
        glClearDepth(depthValue);
    }

    if (flags & GL_STENCIL_BUFFER_BIT)
    {
        glGetIntegerv(GL_STENCIL_CLEAR_VALUE, &stencilClearValue);
        glClearStencil(stencilValue);
    }
    
    glClear(flags);

    // restore
    if (flags & GL_COLOR_BUFFER_BIT)
    {
        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
    }
    if (flags & GL_DEPTH_BUFFER_BIT)
    {
        glClearDepth(depthClearValue);
    }
    if (flags & GL_STENCIL_BUFFER_BIT)
    {
        glClearStencil(stencilClearValue);
    }
}

void CCRenderTexture::end()
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

    director->setProjection(director->getProjection());
}

void CCRenderTexture::clear(float r, float g, float b, float a)
{
    this->beginWithClear(r, g, b, a);
    this->end();
}

void CCRenderTexture::clearDepth(float depthValue)
{
    this->begin();
    //! save old depth value
    GLfloat depthClearValue;
    glGetFloatv(GL_DEPTH_CLEAR_VALUE, &depthClearValue);

    glClearDepth(depthValue);
    glClear(GL_DEPTH_BUFFER_BIT);

    // restore clear color
    glClearDepth(depthClearValue);
    this->end();
}

void CCRenderTexture::clearStencil(int stencilValue)
{
    // save old stencil value
    int stencilClearValue;
    glGetIntegerv(GL_STENCIL_CLEAR_VALUE, &stencilClearValue);

    glClearStencil(stencilValue);
    glClear(GL_STENCIL_BUFFER_BIT);

    // restore clear color
    glClearStencil(stencilClearValue);
}

void CCRenderTexture::visit()
{
    // override visit.
	// Don't call visit on its children
    if (!m_bVisible)
    {
        return;
    }
	
	kmGLPushMatrix();
	
    if (m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->beforeDraw();
        transformAncestors();
    }
    
    transform();
    m_pSprite->visit();
    draw();
	
    if (m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->afterDraw(this);
    }
	
	kmGLPopMatrix();

    m_uOrderOfArrival = 0;
}

void CCRenderTexture::draw()
{
    if( m_bAutoDraw)
    {
        begin();
		
        if (m_uClearFlags)
        {
            GLfloat oldClearColor[4] = {0.0f};
			GLfloat oldDepthClearValue = 0.0f;
			GLint oldStencilClearValue = 0;
			
			// backup and set
			if (m_uClearFlags & GL_COLOR_BUFFER_BIT)
            {
				glGetFloatv(GL_COLOR_CLEAR_VALUE, oldClearColor);
				glClearColor(m_sClearColor.r, m_sClearColor.g, m_sClearColor.b, m_sClearColor.a);
			}
			
			if (m_uClearFlags & GL_DEPTH_BUFFER_BIT)
            {
				glGetFloatv(GL_DEPTH_CLEAR_VALUE, &oldDepthClearValue);
				glClearDepth(m_fDlearDepth);
			}
			
			if (m_uClearFlags & GL_STENCIL_BUFFER_BIT)
            {
				glGetIntegerv(GL_STENCIL_CLEAR_VALUE, &oldStencilClearValue);
				glClearStencil(m_nClearStencil);
			}
			
			// clear
			glClear(m_uClearFlags);
			
			// restore
			if (m_uClearFlags & GL_COLOR_BUFFER_BIT)
            {
				glClearColor(oldClearColor[0], oldClearColor[1], oldClearColor[2], oldClearColor[3]);
            }
			if (m_uClearFlags & GL_DEPTH_BUFFER_BIT)
            {
				glClearDepth(oldDepthClearValue);
            }
			if (m_uClearFlags & GL_STENCIL_BUFFER_BIT)
            {
				glClearStencil(oldStencilClearValue);
            }
		}
		
		//! make sure all children are drawn
        sortAllChildren();
		
		CCObject *pElement;
		CCARRAY_FOREACH(m_pChildren, pElement)
        {
            CCNode *pChild = (CCNode*)pElement;

            if (pChild != m_pSprite)
            {
                pChild->visit();
            }
		}
        
        end();
	}
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
        std::string fullpath = CCFileUtils::sharedFileUtils()->getWriteablePath() + fileName;
        
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
    //        if the saving image domain exceeds the buffer texture domain,
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
        this->end();

        // to get the actual texture data 
        // #640 the image read from rendertexture is dirty
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
