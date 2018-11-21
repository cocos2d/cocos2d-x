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
    _isStencilEnabled = _depthStencilInfo.backFaceStencil.stencilCompareFunction != CompareFunction::ALWAYS ||
                        _depthStencilInfo.backFaceStencil.stencilFailureOperation != StencilOperation::KEEP ||
                        _depthStencilInfo.backFaceStencil.depthFailureOperation != StencilOperation::KEEP ||
                        _depthStencilInfo.backFaceStencil.depthStencilPassOperation != StencilOperation::KEEP ||
                        _depthStencilInfo.frontFaceStencil.stencilCompareFunction != CompareFunction::ALWAYS ||
                        _depthStencilInfo.frontFaceStencil.stencilFailureOperation != StencilOperation::KEEP ||
                        _depthStencilInfo.frontFaceStencil.depthFailureOperation != StencilOperation::KEEP ||
                        _depthStencilInfo.frontFaceStencil.depthStencilPassOperation != StencilOperation::KEEP;
    
    _isBackFrontStencilEqual = descriptor.backFaceStencil == descriptor.frontFaceStencil;
}

DepthStencilState::~DepthStencilState()
{}

CC_BACKEND_END
