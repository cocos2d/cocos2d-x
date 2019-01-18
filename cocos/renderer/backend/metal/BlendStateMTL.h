#pragma once

#include "../BlendState.h"
#import <Metal/Metal.h>

CC_BACKEND_BEGIN

struct BlendDescriptorMTL
{
    MTLColorWriteMask writeMask = MTLColorWriteMaskAll;
    
    bool blendEnabled = false;
    
    MTLBlendOperation rgbBlendOperation = MTLBlendOperationAdd;
    MTLBlendOperation alphaBlendOperation = MTLBlendOperationAdd;
    
    MTLBlendFactor sourceRGBBlendFactor = MTLBlendFactorOne;
    MTLBlendFactor destinationRGBBlendFactor = MTLBlendFactorZero;
    MTLBlendFactor sourceAlphaBlendFactor = MTLBlendFactorOne;
    MTLBlendFactor destinationAlphaBlendFactor = MTLBlendFactorZero;
};

class BlendStateMTL : public BlendState
{
public:
    BlendStateMTL(const BlendDescriptor& descriptor);
    
    inline const BlendDescriptorMTL& getBlendDescriptorMTL() const { return _blendDescriptorMTL; }
    
private:
    BlendDescriptorMTL _blendDescriptorMTL;
};

CC_BACKEND_END
