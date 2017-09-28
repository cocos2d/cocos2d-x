#ifndef DRAGONBONES_COLOR_TRANSFORM_H
#define DRAGONBONES_COLOR_TRANSFORM_H

#include "../core/DragonBones.h"

DRAGONBONES_NAMESPACE_BEGIN

/**
 * @private
 */
class ColorTransform final
{
public:
    float alphaMultiplier;
    float redMultiplier;
    float greenMultiplier;
    float blueMultiplier;
    int alphaOffset;
    int redOffset;
    int greenOffset;
    int blueOffset;

    ColorTransform():
        alphaMultiplier(1.f),
        redMultiplier(1.f),
        greenMultiplier(1.f),
        blueMultiplier(1.f),
        alphaOffset(0),
        redOffset(0),
        greenOffset(0),
        blueOffset(0)
    {
    }
    ColorTransform(const ColorTransform &value)
    {
        operator=(value);
    }
    ~ColorTransform() {}

    inline void operator=(const ColorTransform &value)
    {
        alphaMultiplier = value.alphaMultiplier;
        redMultiplier = value.redMultiplier;
        greenMultiplier = value.greenMultiplier;
        blueMultiplier = value.blueMultiplier;
        alphaOffset = value.alphaOffset;
        redOffset = value.redOffset;
        greenOffset = value.greenOffset;
        blueOffset = value.blueOffset;
    }

    inline void identity()
    {
        alphaMultiplier = redMultiplier = greenMultiplier = blueMultiplier = 1.f;
        alphaOffset = redOffset = greenOffset = blueOffset = 0;
    }
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_COLOR_TRANSFORM_H