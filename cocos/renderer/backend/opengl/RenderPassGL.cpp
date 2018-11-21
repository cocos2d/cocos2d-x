#include "RenderPassGL.h"
#include "TextureGL.h"
#include "ccMacros.h"

CC_BACKEND_BEGIN

RenderPassGL::RenderPassGL(const RenderPassDescriptor& descriptor)
: RenderPass(descriptor)
, _hasStencil(descriptor.hasStencil())
{
    if (_depthStencilAttachmentSet || _colorAttachmentsSet)
        glGenFramebuffers(1, &_frameBuffer);
}

void RenderPassGL::apply(GLuint defaultFrameBuffer) const
{
    if (_frameBuffer)
    {
        // depth and stencil attachment
        glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
        if (_depthStencilAttachmentSet && _depthStencilAttachment.texture)
        {
            auto textureGL = static_cast<TextureGL*>(_depthStencilAttachment.texture);
            glFramebufferTexture2D(GL_FRAMEBUFFER,
                                   GL_DEPTH_ATTACHMENT,
                                   GL_TEXTURE_2D,
                                   textureGL->getHandler(),
                                   0);
            CHECK_GL_ERROR_DEBUG();
            
            if (_hasStencil)
            {
                glFramebufferTexture2D(GL_FRAMEBUFFER,
                                       GL_STENCIL_ATTACHMENT,
                                       GL_TEXTURE_2D,
                                       textureGL->getHandler(),
                                       0);
                CHECK_GL_ERROR_DEBUG();
            }
        }
        
        // color attachments
        if (_colorAttachmentsSet)
        {
            int i = 0;
            for (const auto& texture : _colorAttachments.textures)
            {
                if (texture)
                {
                    // TODO: support texture cube
                    auto textureGL = static_cast<TextureGL*>(texture);
                    glFramebufferTexture2D(GL_FRAMEBUFFER,
                                           GL_COLOR_ATTACHMENT0 + i,
                                           GL_TEXTURE_2D,
                                           textureGL->getHandler(),
                                           0);
                }
                ++i;
            }
        }
        else
        {
            // If not draw buffer is needed, should invoke this line explicitly, or it will cause
            // GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER and GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER error.
            // https://stackoverflow.com/questions/28313782/porting-opengl-es-framebuffer-to-opengl
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
            glDrawBuffer(GL_NONE);
            glReadBuffer(GL_NONE);
#endif
        }
    }
    else
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFrameBuffer);
    
    CHECK_GL_ERROR_DEBUG();
        
    // set clear color, depth and stencil
    GLbitfield mask = 0;
    if (_colorAttachments.needClearColor)
    {
        mask |= GL_COLOR_BUFFER_BIT;
        const auto& clearColor = _colorAttachments.clearColor;
        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
    }
    
    CHECK_GL_ERROR_DEBUG();
    
    GLboolean oldDepthWrite = GL_FALSE;
    GLboolean oldDepthTest = GL_FALSE;
    GLfloat oldDepthClearValue = 0.f;
    GLint oldDepthFunc = GL_LESS;
    if (_depthStencilAttachment.needClearDepth)
    {
        glGetBooleanv(GL_DEPTH_WRITEMASK, &oldDepthWrite);
        glGetBooleanv(GL_DEPTH_TEST, &oldDepthTest);
        glGetFloatv(GL_DEPTH_CLEAR_VALUE, &oldDepthClearValue);
        glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFunc);
        
        mask |= GL_DEPTH_BUFFER_BIT;
        glClearDepth(_depthStencilAttachment.clearDepth);
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_ALWAYS);
    }
    
    CHECK_GL_ERROR_DEBUG();
    
    if (_depthStencilAttachment.needClearStencil)
    {
        mask |= GL_STENCIL_BUFFER_BIT;
        glClearStencil(_depthStencilAttachment.clearStencil);
    }
    glClear(mask);
    
    CHECK_GL_ERROR_DEBUG();
    
    // restore depth test
    if (_depthStencilAttachment.needClearDepth)
    {
        if (!oldDepthTest)
            glDisable(GL_DEPTH_TEST);
        
        glDepthMask(oldDepthWrite);
        glDepthFunc(oldDepthFunc);
        glClearDepth(oldDepthClearValue);
    }
    
    CHECK_GL_ERROR_DEBUG();
}

CC_BACKEND_END
