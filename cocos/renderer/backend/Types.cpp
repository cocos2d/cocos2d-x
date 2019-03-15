#include "Types.h"


CC_BACKEND_BEGIN


bool UniformLocation::operator==(const UniformLocation &other) const
{
    return shaderStage == other.shaderStage && location == other.location;
}

std::size_t UniformLocation::operator()(const UniformLocation &uniform) const {
    return (((size_t) shaderStage) & 0xFFFFFFF0 )|((size_t)(location << 4));
}

CC_BACKEND_END
