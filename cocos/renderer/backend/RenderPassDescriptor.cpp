#include "RenderPassDescriptor.h"
#include "Texture.h"

CC_BACKEND_BEGIN

RenderPassColorAttachments::RenderPassColorAttachments(const RenderPassColorAttachments& rhs)
{
    *this = rhs;
}

RenderPassColorAttachments::~RenderPassColorAttachments()
{
    releaseTextures();
}

RenderPassColorAttachments& RenderPassColorAttachments::operator=(const RenderPassColorAttachments& rhs)
{
    if (this != &rhs)
    {
        clearColor = rhs.clearColor;
        needClearColor = rhs.needClearColor;
        
        rhs.retainTextures();
        releaseTextures();
        textures = rhs.textures;
    }
    return *this;
}

void RenderPassColorAttachments::setTexture(uint32_t attachment, Texture* texture)
{
    if (attachment >= textures.size())
        textures.resize(attachment + 1);
    
    CC_SAFE_RETAIN(texture);
    CC_SAFE_RELEASE(textures[attachment]);
    textures[attachment] = texture;
}

void RenderPassColorAttachments::releaseTextures() const
{
    for (const auto& texture: textures)
        CC_SAFE_RELEASE(texture);
}

void RenderPassColorAttachments::retainTextures() const
{
    for (const auto& texture: textures)
        CC_SAFE_RETAIN(texture);
}

bool RenderPassColorAttachments::operator==(const RenderPassColorAttachments& colorAttachment) const
{
    if(needClearColor != colorAttachment.needClearColor ||
       clearColor != colorAttachment.clearColor)
        return false;
  
    return textures == colorAttachment.textures;
}

RenderPassDepthStencilAttachment::RenderPassDepthStencilAttachment(const RenderPassDepthStencilAttachment& rhs)
{
    *this = rhs;
}

RenderPassDepthStencilAttachment::~RenderPassDepthStencilAttachment()
{
    CC_SAFE_RELEASE(texture);
}

RenderPassDepthStencilAttachment& RenderPassDepthStencilAttachment::operator=(const RenderPassDepthStencilAttachment& rhs)
{
    if (this != &rhs)
    {
        needClearDepth = rhs.needClearDepth;
        needClearStencil = rhs.needClearStencil;
        clearDepth = rhs.clearDepth;
        clearStencil = rhs.clearStencil;
        
        CC_SAFE_RETAIN(rhs.texture);
        CC_SAFE_RELEASE(texture);
        texture = rhs.texture;
    }
    return *this;
}

bool RenderPassDepthStencilAttachment::operator==(const RenderPassDepthStencilAttachment& renderAttachment) const
{
    if(needClearDepth != renderAttachment.needClearDepth ||
       clearDepth != renderAttachment.clearDepth ||
       needClearStencil != renderAttachment.needClearStencil ||
       clearStencil != renderAttachment.clearStencil)
        return  false;
    
    if(texture && renderAttachment.texture)
        return texture->getTextureHashCode()?texture->getTextureHashCode() == renderAttachment.texture->getTextureHashCode():false;
    else if(!texture && !(renderAttachment.texture))
        return  true;
    
    return false;
}

void RenderPassDescriptor::setColorAttachment(uint32_t attachment, Texture* texture)
{
    assert(TextureUsage::RENDER_TARGET == texture->getTextureUsage());
    
    _colorAttachments.setTexture(attachment, texture);
    
    if (texture)
        _colorAttachmentsSet = true;
}

void RenderPassDescriptor::setClearColor(float r, float g, float b, float a)
{
    _colorAttachments.clearColor = {r, g, b, a};
    _colorAttachments.needClearColor = true;
}

void RenderPassDescriptor::setDepthStencilAttachment(Texture* texture)
{
    assert(TextureUsage::RENDER_TARGET == texture->getTextureUsage());
    
    CC_SAFE_RETAIN(texture);
    CC_SAFE_RELEASE(_depthStencilAttachment.texture);
    _depthStencilAttachment.texture = texture;
    
    if (texture)
        _depthStencilAttachmentSet = true;
}

void RenderPassDescriptor::setClearDepth(float clearValue)
{
    _depthStencilAttachment.clearDepth = clearValue;
    _depthStencilAttachment.needClearDepth = true;
}

void RenderPassDescriptor::setClearStencil(uint32_t clearValue)
{
    _depthStencilAttachment.clearStencil = clearValue;
    _depthStencilAttachment.needClearStencil = true;
}

bool RenderPassDescriptor::hasStencil() const
{
    return (_depthStencilAttachmentSet &&
            TextureFormat::D24S8 == _depthStencilAttachment.texture->getTextureFormat());
}

bool RenderPassDescriptor::needGenerateRenderPassState() const
{
    return _colorAttachmentsSet |
           _depthStencilAttachmentSet |
           _colorAttachments.needClearColor |
           _depthStencilAttachment.needClearDepth |
           _depthStencilAttachment.needClearStencil;
}

CC_BACKEND_END
