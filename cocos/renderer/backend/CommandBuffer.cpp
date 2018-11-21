#include "CommandBuffer.h"

CC_BACKEND_BEGIN

void CommandBuffer::setStencilReferenceValue(uint32_t value)
{
    _stencilReferenceValueBack = _stencilReferenceValueFront = value;
}

void CommandBuffer::setStencilReferenceValue(uint32_t frontRef, uint32_t backRef)
{
    _stencilReferenceValueFront = frontRef;
    _stencilReferenceValueBack = backRef;
}

CC_BACKEND_END
