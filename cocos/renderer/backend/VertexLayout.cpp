#include "VertexLayout.h"
#include <cassert>

CC_BACKEND_BEGIN

void VertexLayout::setAtrribute(const std::string &name, unsigned int index, VertexFormat format, unsigned int offset, bool needToBeNormallized)
{
    _attributes[name] = {name, index, format, offset, needToBeNormallized};
}

void VertexLayout::setLayout(unsigned int stride, VertexStepMode stepMode)
{
    _stride = stride;
    _stepMode = stepMode;
}

CC_BACKEND_END
