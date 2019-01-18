#include "DepthStencilState.h"

CC_BACKEND_BEGIN

bool StencilDescriptor::operator==(const StencilDescriptor &rhs) const
{
    return (stencilFailureOperation == rhs.stencilFailureOperation &&
            depthFailureOperation == rhs.depthFailureOperation &&
            depthStencilPassOperation == rhs.depthStencilPassOperation &&
            stencilCompareFunction == rhs.stencilCompareFunction &&
            readMask == rhs.readMask &&
            writeMask == rhs.writeMask);

}

DepthStencilState::DepthStencilState(const DepthStencilDescriptor& descriptor)
: _depthStencilInfo(descriptor)
{
    _isBackFrontStencilEqual = descriptor.backFaceStencil == descriptor.frontFaceStencil;
}

DepthStencilState::~DepthStencilState()
{}

CC_BACKEND_END
