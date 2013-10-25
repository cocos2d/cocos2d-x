#include "C3DDepthStencilTarget.h"
#include "C3DTexture.h"

namespace cocos3d
{

static std::vector<C3DDepthStencilTarget*> __depthStencilTargets;

C3DDepthStencilTarget::C3DDepthStencilTarget(const char* id, Format format)
    : _id(id), _format(format), _depthTexture(NULL), _stencilBuffer(0)
{
}

C3DDepthStencilTarget::~C3DDepthStencilTarget()
{
    SAFE_RELEASE(_depthTexture);

    // Destroy GL resources.
    if (_stencilBuffer)
    {
        GL_ASSERT( glDeleteTextures(1, &_stencilBuffer) );
    }

    // Remove from vector.
    std::vector<C3DDepthStencilTarget*>::iterator it = std::find(__depthStencilTargets.begin(), __depthStencilTargets.end(), this);
    if (it != __depthStencilTargets.end())
    {
        __depthStencilTargets.erase(it);
    }
}

C3DDepthStencilTarget* C3DDepthStencilTarget::create(const char* id, Format format, unsigned int width, unsigned int height)
{
    // Create a backing texture buffer.
    C3DTexture* depthTexture = C3DTexture::create(width, height, C3DTexture::DEPTH, false);
    if (depthTexture == NULL)
    {
        return NULL;
    }

    // Create stencil renderbuffer if format is DEPTH24_STENCIL8
    RenderBufferHandle stencilBuffer = 0;
    if (format == DEPTH24_STENCIL8)
    {
        // Backup the existing render buffer
        GLint currentRbo = 0;
        GL_ASSERT( glGetIntegerv(GL_RENDERBUFFER_BINDING, &currentRbo) );

        // Create the new render buffer
        GL_ASSERT( glGenRenderbuffers(1, &stencilBuffer) );
        GL_ASSERT( glBindRenderbuffer(GL_RENDERBUFFER, stencilBuffer) );
        GL_ASSERT( glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8, width, height) );

        // Restore the old render buffer
        GL_ASSERT( glBindRenderbuffer(GL_RENDERBUFFER, currentRbo) );
    }

    // Create the depth stencil target
    C3DDepthStencilTarget* depthStencilTarget = new C3DDepthStencilTarget(id, format);
    depthStencilTarget->_depthTexture = depthTexture;
    depthStencilTarget->_stencilBuffer = stencilBuffer;
	depthTexture->retain();

    // Add it to the cache
    __depthStencilTargets.push_back(depthStencilTarget);

    depthStencilTarget->autorelease();
    return depthStencilTarget;
}

C3DDepthStencilTarget* C3DDepthStencilTarget::getDepthStencilTarget(const char* id)
{
    // Search the vector for a matching ID.
    std::vector<C3DDepthStencilTarget*>::const_iterator it;
    for (it = __depthStencilTargets.begin(); it < __depthStencilTargets.end(); it++)
    {
        C3DDepthStencilTarget* dst = *it;
        if (strcmp(id, dst->getID()) == 0)
        {
            return dst;
        }
    }

    return NULL;
}

const char* C3DDepthStencilTarget::getID() const
{
    return _id.c_str();
}

C3DDepthStencilTarget::Format C3DDepthStencilTarget::getFormat() const
{
    return _format;
}

C3DTexture* C3DDepthStencilTarget::getTexture() const
{
    return _depthTexture;
}

}
