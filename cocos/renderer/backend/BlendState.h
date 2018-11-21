#pragma once

#include "Macros.h"
#include "Types.h"
#include "base/CCRef.h"

CC_BACKEND_BEGIN

struct BlendDescriptor
{
    ColorWriteMask writeMask = ColorWriteMask::ALL;
    
    bool blendEnabled = false;
    
    BlendOperation rgbBlendOperation = BlendOperation::ADD;
    BlendOperation alphaBlendOperation = BlendOperation::ADD;
    
    BlendFactor sourceRGBBlendFactor = BlendFactor::ONE;
    BlendFactor destinationRGBBlendFactor = BlendFactor::ZERO;
    BlendFactor sourceAlphaBlendFactor = BlendFactor::ONE;
    BlendFactor destinationAlphaBlendFactor = BlendFactor::ZERO;
};

class BlendState : public cocos2d::Ref
{
protected:
    virtual ~BlendState() = default;
    BlendState(const BlendDescriptor& descriptor);
    
    BlendDescriptor _blendDescriptor;
};

CC_BACKEND_END
