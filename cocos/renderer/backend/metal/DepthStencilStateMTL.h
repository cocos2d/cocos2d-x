#pragma once

#include "../DepthStencilState.h"
#import <Metal/Metal.h>

CC_BACKEND_BEGIN

class DepthStencilStateMTL : public DepthStencilState
{
public:
    DepthStencilStateMTL(id<MTLDevice> mtlDevice, const DepthStencilDescriptor& descriptor);
    ~DepthStencilStateMTL();
    
    inline id<MTLDepthStencilState> getMTLDepthStencilState() const { return _mtlDepthStencilState; }
    
private:
    id<MTLDepthStencilState> _mtlDepthStencilState = nil;
};

CC_BACKEND_END
