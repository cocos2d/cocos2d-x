#pragma once

#include "../DepthStencilState.h"

CC_BACKEND_BEGIN

class DepthStencilStateGL : public DepthStencilState
{
public:
    // Reset to default state.
    static void reset();
    
    DepthStencilStateGL(const DepthStencilDescriptor& descriptor);
    void apply(uint32_t stencilReferenceValueFront, uint32_t stencilReferenceValueBack) const;
};

CC_BACKEND_END
