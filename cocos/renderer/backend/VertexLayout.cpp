#include "VertexLayout.h"

CC_BACKEND_BEGIN

void VertexLayout::setAtrribute(const std::string &name, uint32_t index, VertexFormat format, uint32_t offset)
{
    _attributes.push_back({name, index, format, offset});
}

void VertexLayout::setLayout(uint32_t stride, VertexStepMode stepMode)
{
    _stride = stride;
    _stepMode = stepMode;
}

CC_BACKEND_END
