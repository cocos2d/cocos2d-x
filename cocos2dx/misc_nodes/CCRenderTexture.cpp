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

// implementation RenderTexture
RenderTexture::RenderTexture()
: _FBO(0)
, _depthRenderBufffer(0)
, _oldFBO(0)
, _texture(0)
, _textureCopy(0)
, _UITextureImage(NULL)
, _pixelFormat(Texture2D::PixelFormat::RGBA8888)
, _clearFlags(0)
, _clearColor(Color4F(0,0,0,0))
, _clearDepth(0.0f)
, _clearStencil(0)
, _autoDraw(false)
, _sprite(NULL)
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    // Listen this event to save render texture before come to background.
    // Then it can be restored after coming to foreground on Android.
    NotificationCenter::getInstance()->addObserver(this,
                                                                  callfuncO_selector(RenderTexture::listenToBackground),
                                                                  EVENT_COME_TO_BACKGROUND,
                                                                  NULL);
    
    NotificationCenter::getInstance()->addObserver(this,
                                                                  callfuncO_selector(RenderTexture::listenToForeground),
                                                                  EVNET_COME_TO_FOREGROUND, // this is misspelt
                                                                  NULL);
#endif
}

RenderTexture::~RenderTexture()
{
    CC_SAFE_RELEASE(_sprite);
    CC_SAFE_RELEASE(_textureCopy);
    
    glDeleteFramebuffers(1, &_FBO);
    if (_depthRenderBufffer)
    {
        glDeleteRenderbuffers(1, &_depthRenderBufffer);
    }
    CC_SAFE_DELETE(_UITextureImage);

#if CC_ENABLE_CACHE_TEXTURE_DATA
    NotificationCenter::getInstance()->removeObserver(this, EVENT_COME_TO_BACKGROUND);
    NotificationCenter::getInstance()->removeObserver(this, EVNET_COME_TO_FOREGROUND);
#endif
}

void RenderTexture::listenToBackground(cocos2d::Object *obj)
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    CC_SAFE_DELETE(_UITextureImage);
    
    // to get the rendered texture data
    _UITextureImage = newImage(false);

    if (_UITextureImage)
    {
        const Size& s = _texture->getContentSizeInPixels();
        VolatileTexture::addDataTexture(_texture, _UITextureImage->getData(), Texture2D::PixelFormat::RGBA8888, s);
        
        if ( _textureCopy )
        {
            VolatileTexture::addDataTexture(_textureCopy, _UITextureImage->getData(), Texture2D::PixelFormat::RGBA8888, s);
        }
    }
    else
    {
        CCLOG("Cache rendertexture failed!");
    }
    
    glDeleteFramebuffers(1, &_FBO);
    _FBO = 0;
#endif
}

void RenderTexture::listenToForeground(cocos2d::Object *obj)
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    // -- regenerate frame buffer object and attach the texture
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_oldFBO);
    
    glGenFramebuffers(1, &_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
    
    _texture->setAliasTexParameters();
    
    if ( _textureCopy )
    {
        _textureCopy->setAliasTexParameters();
    }
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture->getName(), 0);
    glBindFramebuffer(GL_FRAMEBUFFER, _oldFBO);
#endif
}

RenderTexture * RenderTexture::create(int w, int h, Texture2D::PixelFormat eFormat)
{
    RenderTexture *pRet = new RenderTexture();

    if(pRet && pRet->initWithWidthAndHeight(w, h, eFormat))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

RenderTexture * RenderTexture::create(int w ,int h, Texture2D::PixelFormat eFormat, GLuint uDepthStencilFormat)
{
    RenderTexture *pRet = new RenderTexture();

    if(pRet && pRet->initWithWidthAndHeight(w, h, eFormat, uDepthStencilFormat))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

RenderTexture * RenderTexture::create(int w, int h)
{
    RenderTexture *pRet = new RenderTexture();

    if(pRet && pRet->initWithWidthAndHeight(w, h, Texture2D::PixelFormat::RGBA8888, 0))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool RenderTexture::initWithWidthAndHeight(int w, int h, Texture2D::PixelFormat eFormat)
{
    return initWithWidthAndHeight(w, h, eFormat, 0);
}

bool RenderTexture::initWithWidthAndHeight(int w, int h, Texture2D::PixelFormat eFormat, GLuint uDepthStencilFormat)
{
    CCASSERT(eFormat != Texture2D::PixelFormat::A8, "only RGB and RGBA formats are valid for a render texture");

    bool bRet = false;
    void *data = NULL;
    do 
    {
        w = (int)(w * CC_CONTENT_SCALE_FACTOR());
        h = (int)(h * CC_CONTENT_SCALE_FACTOR());

        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_oldFBO);

        // textures must be power of two squared
        unsigned int powW = 0;
        unsigned int powH = 0;

        if (Configuration::getInstance()->supportsNPOT())
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
        _pixelFormat = eFormat;

        _texture = new Texture2D();
        if (_texture)
        {
            _texture->initWithData(data, (Texture2D::PixelFormat)_pixelFormat, powW, powH, Size((float)w, (float)h));
        }
        else
        {
            break;
        }
        GLint oldRBO;
        glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldRBO);
        
        if (Configuration::getInstance()->checkForGLExtension("GL_QCOM"))
        {
            _textureCopy = new Texture2D();
            if (_textureCopy)
            {
                _textureCopy->initWithData(data, (Texture2D::PixelFormat)_pixelFormat, powW, powH, Size((float)w, (float)h));
            }
            else
            {
                break;
            }
        }

        // generate FBO
        glGenFramebuffers(1, &_FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, _FBO);

        // associate texture with FBO
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture->getName(), 0);

        if (uDepthStencilFormat != 0)
        {
            //create and attach depth buffer
            glGenRenderbuffers(1, &_depthRenderBufffer);
            glBindRenderbuffer(GL_RENDERBUFFER, _depthRenderBufffer);
            glRenderbufferStorage(GL_RENDERBUFFER, uDepthStencilFormat, (GLsizei)powW, (GLsizei)powH);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRenderBufffer);

            // if depth format is the one with stencil part, bind same render buffer as stencil attachment
            if (uDepthStencilFormat == GL_DEPTH24_STENCIL8)
            {
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _depthRenderBufffer);
            }
        }

        // check if it worked (probably worth doing :) )
        CCASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Could not attach texture to framebuffer");

        _texture->setAliasTexParameters();

        // retained
        setSprite(Sprite::createWithTexture(_texture));

        _texture->release();
        _sprite->setScaleY(-1);

        _sprite->setBlendFunc( BlendFunc::ALPHA_PREMULTIPLIED );

        glBindRenderbuffer(GL_RENDERBUFFER, oldRBO);
        glBindFramebuffer(GL_FRAMEBUFFER, _oldFBO);
        
        // Diabled by default.
        _autoDraw = false;
        
        // add sprite for backward compatibility
        addChild(_sprite);
        
        bRet = true;
    } while (0);
    
    CC_SAFE_FREE(data);
    
    return bRet;
}

void RenderTexture::begin()
{
    kmGLMatrixMode(KM_GL_PROJECTION);
	kmGLPushMatrix();
	kmGLMatrixMode(KM_GL_MODELVIEW);
    kmGLPushMatrix();
    
    Director *director = Director::getInstance();
    director->setProjection(director->getProjection());

    const Size& texSize = _texture->getContentSizeInPixels();

    // Calculate the adjustment ratios based on the old and new projections
    Size size = director->getWinSizeInPixels();
    float widthRatio = size.width / texSize.width;
    float heightRatio = size.height / texSize.height;

    // Adjust the orthographic projection and viewport
    glViewport(0, 0, (GLsizei)texSize.width, (GLsizei)texSize.height);


    kmMat4 orthoMatrix;
    kmMat4OrthographicProjection(&orthoMatrix, (float)-1.0 / widthRatio,  (float)1.0 / widthRatio,
        (float)-1.0 / heightRatio, (float)1.0 / heightRatio, -1,1 );
    kmGLMultMatrix(&orthoMatrix);

    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_oldFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
    
    /*  Certain Qualcomm Andreno gpu's will retain data in memory after a frame buffer switch which corrupts the render to the texture. The solution is to clear the frame buffer before rendering to the texture. However, calling glClear has the unintended result of clearing the current texture. Create a temporary texture to overcome this. At the end of RenderTexture::begin(), switch the attached texture to the second one, call glClear, and then switch back to the original texture. This solution is unnecessary for other devices as they don't have the same issue with switching frame buffers.
     */
    if (Configuration::getInstance()->checkForGLExtension("GL_QCOM"))
    {
        // -- bind a temporary texture so we can clear the render buffer without losing our texture
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureCopy->getName(), 0);
        CHECK_GL_ERROR_DEBUG();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture->getName(), 0);
    }
}

void RenderTexture::beginWithClear(float r, float g, float b, float a)
{
    beginWithClear(r, g, b, a, 0, 0, GL_COLOR_BUFFER_BIT);
}

void RenderTexture::beginWithClear(float r, float g, float b, float a, float depthValue)
{
    beginWithClear(r, g, b, a, depthValue, 0, GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void RenderTexture::beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue)
{
    beginWithClear(r, g, b, a, depthValue, stencilValue, GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
}

void RenderTexture::beginWithClear(float r, float g, float b, float a, float depthValue, int stencilValue, GLbitfield flags)
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

void RenderTexture::end()
{
    Director *director = Director::getInstance();
    
    glBindFramebuffer(GL_FRAMEBUFFER, _oldFBO);

    // restore viewport
    director->setViewport();

    kmGLMatrixMode(KM_GL_PROJECTION);
	kmGLPopMatrix();
	kmGLMatrixMode(KM_GL_MODELVIEW);
	kmGLPopMatrix();
}

void RenderTexture::clear(float r, float g, float b, float a)
{
    this->beginWithClear(r, g, b, a);
    this->end();
}

void RenderTexture::clearDepth(float depthValue)
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

void RenderTexture::clearStencil(int stencilValue)
{
    // save old stencil value
    int stencilClearValue;
    glGetIntegerv(GL_STENCIL_CLEAR_VALUE, &stencilClearValue);

    glClearStencil(stencilValue);
    glClear(GL_STENCIL_BUFFER_BIT);

    // restore clear color
    glClearStencil(stencilClearValue);
}

void RenderTexture::visit()
{
    // override visit.
	// Don't call visit on its children
    if (!_visible)
    {
        return;
    }
	
	kmGLPushMatrix();
	
    if (_grid && _grid->isActive())
    {
        _grid->beforeDraw();
        transformAncestors();
    }
    
    transform();
    _sprite->visit();
    draw();
	
    if (_grid && _grid->isActive())
    {
        _grid->afterDraw(this);
    }
	
	kmGLPopMatrix();

    _orderOfArrival = 0;
}

void RenderTexture::draw()
{
    if( _autoDraw)
    {
        begin();
		
        if (_clearFlags)
        {
            GLfloat oldClearColor[4] = {0.0f};
			GLfloat oldDepthClearValue = 0.0f;
			GLint oldStencilClearValue = 0;
			
			// backup and set
			if (_clearFlags & GL_COLOR_BUFFER_BIT)
            {
				glGetFloatv(GL_COLOR_CLEAR_VALUE, oldClearColor);
				glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
			}
			
			if (_clearFlags & GL_DEPTH_BUFFER_BIT)
            {
				glGetFloatv(GL_DEPTH_CLEAR_VALUE, &oldDepthClearValue);
				glClearDepth(_clearDepth);
			}
			
			if (_clearFlags & GL_STENCIL_BUFFER_BIT)
            {
				glGetIntegerv(GL_STENCIL_CLEAR_VALUE, &oldStencilClearValue);
				glClearStencil(_clearStencil);
			}
			
			// clear
			glClear(_clearFlags);
			
			// restore
			if (_clearFlags & GL_COLOR_BUFFER_BIT)
            {
				glClearColor(oldClearColor[0], oldClearColor[1], oldClearColor[2], oldClearColor[3]);
            }
			if (_clearFlags & GL_DEPTH_BUFFER_BIT)
            {
				glClearDepth(oldDepthClearValue);
            }
			if (_clearFlags & GL_STENCIL_BUFFER_BIT)
            {
				glClearStencil(oldStencilClearValue);
            }
		}
		
		//! make sure all children are drawn
        sortAllChildren();
		
		Object *pElement;
		CCARRAY_FOREACH(_children, pElement)
        {
            Node *child = static_cast<Node*>(pElement);

            if (child != _sprite)
            {
                child->visit();
            }
		}
        
        end();
	}
}

bool RenderTexture::saveToFile(const char *szFilePath)
{
    bool ret = false;

    Image *image = newImage(true);
    if (image)
    {
        ret = image->saveToFile(szFilePath);
    }

    CC_SAFE_DELETE(image);
    return ret;
}
bool RenderTexture::saveToFile(const char *fileName, Image::Format format)
{
    bool bRet = false;
    CCASSERT(format == Image::Format::JPG || format == Image::Format::PNG,
             "the image can only be saved as JPG or PNG format");

    Image *image = newImage(true);
    if (image)
    {
        std::string fullpath = FileUtils::getInstance()->getWritablePath() + fileName;
        
        bRet = image->saveToFile(fullpath.c_str(), true);
    }

    CC_SAFE_DELETE(image);

    return bRet;
}

/* get buffer as Image */
Image* RenderTexture::newImage(bool fliimage)
{
    CCASSERT(_pixelFormat == Texture2D::PixelFormat::RGBA8888, "only RGBA8888 can be saved as image");

    if (NULL == _texture)
    {
        return NULL;
    }

    const Size& s = _texture->getContentSizeInPixels();

    // to get the image size to save
    //        if the saving image domain exceeds the buffer texture domain,
    //        it should be cut
    int nSavedBufferWidth = (int)s.width;
    int nSavedBufferHeight = (int)s.height;

    GLubyte *pBuffer = NULL;
    GLubyte *pTempData = NULL;
    Image *image = new Image();

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

        if ( fliimage ) // -- flip is only required when saving image to file
        {
            // to get the actual texture data
            // #640 the image read from rendertexture is dirty
            for (int i = 0; i < nSavedBufferHeight; ++i)
            {
                memcpy(&pBuffer[i * nSavedBufferWidth * 4], 
                       &pTempData[(nSavedBufferHeight - i - 1) * nSavedBufferWidth * 4], 
                       nSavedBufferWidth * 4);
            }

            image->initWithImageData(pBuffer, nSavedBufferWidth * nSavedBufferHeight * 4, Image::Format::RAW_DATA, nSavedBufferWidth, nSavedBufferHeight, 8);
        }
        else
        {
            image->initWithImageData(pTempData, nSavedBufferWidth * nSavedBufferHeight * 4, Image::Format::RAW_DATA, nSavedBufferWidth, nSavedBufferHeight, 8);
        }
        
    } while (0);

    CC_SAFE_DELETE_ARRAY(pBuffer);
    CC_SAFE_DELETE_ARRAY(pTempData);

    return image;
}

NS_CC_END
