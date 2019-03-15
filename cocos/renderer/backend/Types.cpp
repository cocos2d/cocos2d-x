#include "Types.h"


CC_BACKEND_BEGIN


bool UniformLocation::operator==(const UniformLocation &other) const
{
    return shaderStage == other.shaderStage && location == other.location;
}

std::size_t UniformLocation::operator()(const UniformLocation &uniform) const {
    return (size_t)(shaderStage) || (size_t)(location & 0xFFFFFFF0);
}

CC_BACKEND_END
