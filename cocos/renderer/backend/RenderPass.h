#pragma once

#include "Types.h"
#include "RenderPassDescriptor.h"
#include "base/CCRef.h"

CC_BACKEND_BEGIN

class RenderPass : public cocos2d::Ref
{
public:
    inline bool hasDepthStencilAttachment() const { return _depthStencilAttachmentSet; }
    inline bool hasColorAttachments() const { return _colorAttachmentsSet; }
    
    inline const RenderPassDepthStencilAttachment& getDepthStencilAttachment() const { return _depthStencilAttachment; }
    inline const RenderPassColorAttachments& getColorAttachments() const { return _colorAttachments; }
    bool find(const RenderPassDescriptor& descriptor) const;
    
protected:
    RenderPass(const RenderPassDescriptor& descriptor);
    virtual ~RenderPass();
    
    bool _depthStencilAttachmentSet = false;
    RenderPassDepthStencilAttachment _depthStencilAttachment;
    
    bool _colorAttachmentsSet = false;
    RenderPassColorAttachments _colorAttachments;
};

CC_BACKEND_END
