#include "RenderPass.h"

CC_BACKEND_BEGIN

RenderPass::RenderPass(const RenderPassDescriptor& descriptor)
: _depthStencilAttachmentSet(descriptor._depthStencilAttachmentSet)
, _depthStencilAttachment(descriptor._depthStencilAttachment)
, _colorAttachmentsSet(descriptor._colorAttachmentsSet)
, _colorAttachments(descriptor._colorAttachments)
{
}

RenderPass::~RenderPass()
{}

bool RenderPass::find(const RenderPassDescriptor& descriptor) const
{
    if(_colorAttachmentsSet != descriptor.getColorAttachmentSet() ||
       _depthStencilAttachmentSet != descriptor.getDepthStencilAttachmentSet())
        return false;
   
    const RenderPassColorAttachments colorAttachment = descriptor.getColorAttachments();
    const RenderPassDepthStencilAttachment depthStencilAttachment = descriptor.getDepthStencilAttachment();

    if(_colorAttachments == colorAttachment &&
       _depthStencilAttachment == depthStencilAttachment)
        return true;
    
    return  false;
}

CC_BACKEND_END
