#include "RenderPassMTL.h"
#include "TextureMTL.h"
#include "DeviceMTL.h"
#include "Utils.h"

CC_BACKEND_BEGIN

RenderPassMTL::RenderPassMTL(id<MTLDevice> mtlDevice, const RenderPassDescriptor& descriptor)
: RenderPass(descriptor)
{
    if (_colorAttachmentsSet || _depthStencilAttachmentSet)
        _mtlRenderPassDescritpr = [MTLRenderPassDescriptor renderPassDescriptor];
    else
        _mtlRenderPassDescritpr = Utils::getDefaultRenderPassDescriptor();
    [_mtlRenderPassDescritpr retain];
    
    setColorAttachments(descriptor);
    setDepthStencilAttachment(descriptor);
}

RenderPassMTL::~RenderPassMTL()
{
    if (!_colorAttachmentsSet && !_depthStencilAttachmentSet)
        [_mtlRenderPassDescritpr release];
}

MTLRenderPassDescriptor* RenderPassMTL::getMTLRenderPassDescriptor()
{
    if (!_colorAttachmentsSet && !_depthStencilAttachmentSet)
    {
        const auto& defaultRenderPassDescriptor = Utils::getDefaultRenderPassDescriptor();
        if (!_colorAttachmentsSet)
            _mtlRenderPassDescritpr.colorAttachments[0].texture = defaultRenderPassDescriptor.colorAttachments[0].texture;
        if (!_depthStencilAttachmentSet)
            _mtlRenderPassDescritpr.depthAttachment.texture = defaultRenderPassDescriptor.depthAttachment.texture;
    }
    
    return _mtlRenderPassDescritpr;
}

void RenderPassMTL::setColorAttachments(const RenderPassDescriptor& descriptor)
{
    const auto& renderPassColorAttachments = descriptor.getColorAttachments();
    if (_colorAttachmentsSet)
    {
        int i = 0;
        for (const auto& texture : renderPassColorAttachments.textures)
        {
            if (!texture)
                continue;
            
            if (renderPassColorAttachments.needClearColor)
            {
                _mtlRenderPassDescritpr.colorAttachments[i].loadAction = MTLLoadActionClear;
                _mtlRenderPassDescritpr.colorAttachments[i].clearColor = MTLClearColorMake(renderPassColorAttachments.clearColor[0],
                                                                                           renderPassColorAttachments.clearColor[1],
                                                                                           renderPassColorAttachments.clearColor[2],
                                                                                           renderPassColorAttachments.clearColor[3]);
            }
            else
                _mtlRenderPassDescritpr.colorAttachments[i].loadAction = MTLLoadActionLoad;
            
            _mtlRenderPassDescritpr.colorAttachments[i].texture = static_cast<TextureMTL*>(texture)->getMTLTexture();
            _mtlRenderPassDescritpr.colorAttachments[i].storeAction = MTLStoreActionStore;
            
            ++i;
        }
    }
    else
    {
        _mtlRenderPassDescritpr.colorAttachments[0].texture = Utils::getTempColorAttachmentTexture();
        if (renderPassColorAttachments.needClearColor)
        {
            _mtlRenderPassDescritpr.colorAttachments[0].loadAction = MTLLoadActionClear;
            _mtlRenderPassDescritpr.colorAttachments[0].clearColor = MTLClearColorMake(renderPassColorAttachments.clearColor[0],
                                                                                       renderPassColorAttachments.clearColor[1],
                                                                                       renderPassColorAttachments.clearColor[2],
                                                                                       renderPassColorAttachments.clearColor[3]);
        }
    }
}

void RenderPassMTL::setDepthStencilAttachment(const RenderPassDescriptor &descriptor)
{
    // Set depth/stencil attachment.
    const auto& renderPassDepthStencilAttachment = descriptor.getDepthStencilAttachment();
    if (_depthStencilAttachmentSet)
    {
        const auto& textureMTL = static_cast<TextureMTL*>(renderPassDepthStencilAttachment.texture);
        _mtlRenderPassDescritpr.depthAttachment.texture = textureMTL->getMTLTexture();
        _mtlRenderPassDescritpr.stencilAttachment.texture = textureMTL->getMTLTexture();
    }
    
    // Set depth clear value.
    if (renderPassDepthStencilAttachment.needClearDepth)
    {
        _mtlRenderPassDescritpr.depthAttachment.loadAction = MTLLoadActionClear;
        _mtlRenderPassDescritpr.depthAttachment.clearDepth = renderPassDepthStencilAttachment.clearDepth;
    }
    else
        _mtlRenderPassDescritpr.depthAttachment.loadAction = MTLLoadActionLoad;
    
    // Set stencil clear value.
    if (renderPassDepthStencilAttachment.needClearStencil)
    {
        _mtlRenderPassDescritpr.stencilAttachment.loadAction = MTLLoadActionClear;
        _mtlRenderPassDescritpr.stencilAttachment.clearStencil = renderPassDepthStencilAttachment.clearStencil;
    }
    else
        _mtlRenderPassDescritpr.stencilAttachment.loadAction = MTLLoadActionLoad;
}

CC_BACKEND_END
