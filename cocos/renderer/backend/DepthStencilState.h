#pragma once

#include "Macros.h"
#include "Types.h"

#include "base/CCRef.h"

CC_BACKEND_BEGIN

struct StencilDescriptor
{
    bool operator ==(const StencilDescriptor& rhs) const;
    
    StencilOperation stencilFailureOperation = StencilOperation::KEEP;
    StencilOperation depthFailureOperation = StencilOperation::KEEP;
    StencilOperation depthStencilPassOperation = StencilOperation::KEEP;
    CompareFunction stencilCompareFunction = CompareFunction::ALWAYS;
    uint32_t readMask = 0;
    uint32_t writeMask = 0;
};

struct DepthStencilDescriptor
{
    CompareFunction depthCompareFunction = CompareFunction::LESS;
    bool depthWriteEnabled = false;
    bool depthTestEnabled = false;
    
    bool stencilTestEnabled = false;
    StencilDescriptor backFaceStencil;
    StencilDescriptor frontFaceStencil;
};

class DepthStencilState : public cocos2d::Ref
{
protected:
    DepthStencilState(const DepthStencilDescriptor& descriptor);
    virtual ~DepthStencilState();
    
    DepthStencilDescriptor _depthStencilInfo;
    bool _isBackFrontStencilEqual = false;
};

CC_BACKEND_END
