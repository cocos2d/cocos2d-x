#include "C3DFrameBuffer.h"
#include "C3DRenderTarget.h"
#include "C3DDepthStencilTarget.h"
#include "C3DTexture.h"
#include "ccMacros.h"
#include "C3DRenderSystem.h"


namespace cocos3d
{

static std::vector<C3DFrameBuffer*> __frameBuffers;

C3DFrameBuffer::C3DFrameBuffer(const char* id) :
    _id(id ? id : ""), _handle(0), _renderTarget(NULL), _depthStencilTarget(NULL), _width(1), _height(1),
    _isBind(false), _oldFBO(0), _oldViewport(0, 0, 1, 1)
{
}

C3DFrameBuffer::~C3DFrameBuffer()
{
	SAFE_RELEASE(_renderTarget);
    SAFE_RELEASE(_depthStencilTarget);
    // Release GL resource.
    if (_handle)
    {
        GL_ASSERT( glDeleteFramebuffers(1, &_handle) );
    }

    // Remove self from vector.
    std::vector<C3DFrameBuffer*>::iterator it = std::find(__frameBuffers.begin(), __frameBuffers.end(), this);
    if (it != __frameBuffers.end())
    {
        __frameBuffers.erase(it);
    }
}


C3DFrameBuffer* C3DFrameBuffer::create(const char* id, unsigned int width, unsigned int height, unsigned int fmtColor, unsigned int fmtDepth)
{
    // Create C3DRenderTarget with same ID
    C3DRenderTarget* renderTarget = NULL;
    
    if (fmtColor)
    {
        renderTarget = C3DRenderTarget::create(id, width, height, fmtColor);
        if (renderTarget == NULL)
        {
            LOG_ERROR("Failed to create render target");
        }
    }

    C3DDepthStencilTarget* depthTarget = NULL;
    
    if (fmtDepth)
    {
        depthTarget = C3DDepthStencilTarget::create(id, (C3DDepthStencilTarget::Format) fmtDepth, width, height);
        if (depthTarget == NULL)
        {
            LOG_ERROR("Failed to create depth & stencil target");
        }
    }

    // Create the frame buffer
    GLuint handle = 0;
    GL_ASSERT( glGenFramebuffers(1, &handle) );

    // Create the new frame buffer
    C3DFrameBuffer* frameBuffer = new C3DFrameBuffer(id ? id : "");
	if (frameBuffer == NULL)
    {
        LOG_ERROR("Failed to create frame buffer object");
        return NULL;
    }
    
    frameBuffer->_handle = handle;

    // Add the render target as the first color attachment
    if (renderTarget)
        frameBuffer->setRenderTarget(renderTarget);

    if (depthTarget)
        frameBuffer->setDepthStencilTarget(depthTarget);
    
    // Add to the global list of managed frame buffers
    __frameBuffers.push_back(frameBuffer);
    frameBuffer->_width = width;
    frameBuffer->_height = height;
    frameBuffer->autorelease();
    return frameBuffer;
}

C3DFrameBuffer* C3DFrameBuffer::getFrameBuffer(const char* id)
{
    // Search the vector for a matching ID.
    std::vector<C3DFrameBuffer*>::const_iterator it;
    for (it = __frameBuffers.begin(); it < __frameBuffers.end(); it++)
    {
        C3DFrameBuffer* fb = *it;
        if (strcmp(id, fb->getID()) == 0)
        {
            return fb;
        }
    }

    return NULL;
}

const char* C3DFrameBuffer::getID() const
{
    return _id.c_str();
}


void C3DFrameBuffer::setRenderTarget(C3DRenderTarget* target)
{
    if (_renderTarget == target)
    {
        return;
    }

    SAFE_RELEASE(_renderTarget);

    _renderTarget = target;

    if (target)
    {
        target->retain();

        // Store the current FBO binding so we can restore it
        GLint currentFbo;
        GL_ASSERT( glGetIntegerv(GL_FRAMEBUFFER_BINDING, &currentFbo) );

        // Now set this target as the color attachment.
        GL_ASSERT( glBindFramebuffer(GL_FRAMEBUFFER, _handle) );
        GL_ASSERT( glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _renderTarget->getTexture()->getHandle(), 0) );
		GLenum fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
        {
            //LOG_ERROR("Framebuffer status incomplete: 0x%x", fboStatus);
        }

        // Restore the FBO binding
        GL_ASSERT( glBindFramebuffer(GL_FRAMEBUFFER, currentFbo) );
    }
}

C3DRenderTarget* C3DFrameBuffer::getRenderTarget() const
{
	return _renderTarget;
}

void C3DFrameBuffer::setDepthStencilTarget(C3DDepthStencilTarget* target)
{
    if (_depthStencilTarget == target)
    {
        return; 
    }

    // Release our existing depth stencil target
    SAFE_RELEASE(_depthStencilTarget);

    _depthStencilTarget = target;

    if (target)
    {
        // The C3DFrameBuffer now owns this C3DDepthStencilTarget
        target->retain();

        // Store the current FBO binding so we can restore it
        GLint currentFbo;
        GL_ASSERT( glGetIntegerv(GL_FRAMEBUFFER_BINDING, &currentFbo) );

        // Now set this target as the color attachment.
        GL_ASSERT( glBindFramebuffer(GL_FRAMEBUFFER, _handle) );

        // Bind the depth texture
        GL_ASSERT( glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthStencilTarget->getTexture()->getHandle(), 0) );

        // If the taget has a stencil buffer, bind that as well
        if (target->getFormat() == C3DDepthStencilTarget::DEPTH24_STENCIL8)
        {
            GL_ASSERT( glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _depthStencilTarget->_stencilBuffer) );
        }

		 // Check the framebuffer is good to go.
        GLenum fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
        {
            //LOG_ERROR("Framebuffer status incomplete: 0x%x", fboStatus);
        }

        // Restore the FBO binding
        GL_ASSERT( glBindFramebuffer(GL_FRAMEBUFFER, currentFbo) );
    }
}

C3DDepthStencilTarget* C3DFrameBuffer::getDepthStencilTarget() const
{
    return _depthStencilTarget;
}

void C3DFrameBuffer::bind()
{
    CCAssert(!_isBind, "Already bind framebuffer");

    
    GL_ASSERT( glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_oldFBO));

    // Bind this C3DFrameBuffer for rendering.
    GL_ASSERT( glBindFramebuffer(GL_FRAMEBUFFER, _handle) );

    _oldViewport = *C3DRenderSystem::getInstance()->getViewport();
    C3DRenderSystem::getInstance()->setViewport(0, 0, _width, _height);
    
    _isBind = true;
}

void C3DFrameBuffer::bindDefault()
{
    GL_ASSERT( glBindFramebuffer(GL_FRAMEBUFFER, 0) );
    cocos2d::CCDirector::sharedDirector()->setViewport();

    std::vector<C3DFrameBuffer*>::const_iterator it;
    for (it = __frameBuffers.begin(); it < __frameBuffers.end(); it++)
    {
        C3DFrameBuffer* fb = *it;
        fb->_isBind = false;
        fb->_oldFBO = 0;
    }

}

void C3DFrameBuffer::unbind()
{
    CCAssert(_isBind, "frame buffer is not bind");
    GL_ASSERT( glBindFramebuffer(GL_FRAMEBUFFER, _oldFBO) );
    C3DRenderSystem::getInstance()->setViewport(&_oldViewport);
    _isBind = false;
}

}
