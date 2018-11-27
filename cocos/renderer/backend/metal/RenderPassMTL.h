#pragma once

#include "../RenderPass.h"
#import <Metal/Metal.h>

CC_BACKEND_BEGIN

class RenderPassMTL : public RenderPass
{
public:
    RenderPassMTL(id<MTLDevice> mtlDevice, const RenderPassDescriptor& descriptor);
    ~RenderPassMTL();
    
    MTLRenderPassDescriptor* getMTLRenderPassDescriptor();
    
private:
    void setColorAttachments(const RenderPassDescriptor& descriptor);
    void setDepthStencilAttachment(const RenderPassDescriptor& descriptor);
    
    MTLRenderPassDescriptor* _mtlRenderPassDescritpr = nil;
};

CC_BACKEND_END
