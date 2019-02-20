#include "VertexLayout.h"
#include <cassert>

CC_BACKEND_BEGIN

void VertexLayout::setAtrribute(const std::string &name, unsigned int index, VertexFormat format, unsigned int offset, bool needToBeNormallized)
{
    if (_attributes.find(name) != _attributes.end())
    {
        CCASSERT(false, "VertexAttribute already setup!");
    }
    _attributes[name] = { name, index, format, offset, needToBeNormallized };
}

void VertexLayout::setLayout(unsigned int stride, VertexStepMode stepMode)
{
    _stride = stride;
    _stepMode = stepMode;
}

void VertexLayout::reset()
{
    _attributes.clear();
    _stride = 0;
    _stepMode = VertexStepMode::VERTEX;
}

CC_BACKEND_END
