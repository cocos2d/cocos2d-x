#include "RenderPassDescriptor.h"

CC_BACKEND_BEGIN

RenderPassDescriptor& RenderPassDescriptor::operator=(const RenderPassDescriptor& descriptor)
{
    clearDepthValue = descriptor.clearDepthValue;
    clearStencilValue = descriptor.clearStencilValue;
    clearColorValue = descriptor.clearColorValue;
    needColorAttachment = descriptor.needColorAttachment;
    depthTestEnabled = descriptor.depthTestEnabled;
    stencilTestEnabled = descriptor.stencilTestEnabled;
    needClearColor = descriptor.needClearColor;
    needClearDepth = descriptor.needClearDepth;
    needClearStencil = descriptor.needClearStencil;
    depthAttachmentTexture = descriptor.depthAttachmentTexture;
    stencilAttachmentTexture = descriptor.stencilAttachmentTexture;
    colorAttachmentsTexture[0] = descriptor.colorAttachmentsTexture[0];
    
    return *this;
}

bool RenderPassDescriptor::operator==(const RenderPassDescriptor& descriptor)
{
    if( clearDepthValue == descriptor.clearDepthValue &&
        clearStencilValue == descriptor.clearStencilValue &&
        clearColorValue == descriptor.clearColorValue &&
        needColorAttachment == descriptor.needColorAttachment &&
        depthTestEnabled == descriptor.depthTestEnabled &&
        stencilTestEnabled == descriptor.stencilTestEnabled &&
        needClearColor == descriptor.needClearColor &&
        needClearDepth == descriptor.needClearDepth &&
        needClearStencil == descriptor.needClearStencil &&
        depthAttachmentTexture == descriptor.depthAttachmentTexture &&
        stencilAttachmentTexture == descriptor.stencilAttachmentTexture &&
        colorAttachmentsTexture[0] == descriptor.colorAttachmentsTexture[0])
    {
        return true;
    }
    else
    {
        return false;
    }
}

CC_BACKEND_END
