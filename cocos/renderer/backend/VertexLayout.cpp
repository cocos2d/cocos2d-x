#include "VertexLayout.h"

CC_BACKEND_BEGIN

void VertexLayout::setAtrribute(const std::string &name, unsigned int index, VertexFormat format, unsigned int offset, bool needToBeNormallized)
{
    _attributes.push_back({name, index, format, offset, needToBeNormallized});
}

void VertexLayout::setLayout(unsigned int stride, VertexStepMode stepMode)
{
    _stride = stride;
    _stepMode = stepMode;
}

CC_BACKEND_END
