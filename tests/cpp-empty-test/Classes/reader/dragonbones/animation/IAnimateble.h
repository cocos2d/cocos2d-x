#ifndef DRAGONBONES_ANIMATEBLE_H
#define DRAGONBONES_ANIMATEBLE_H

#include "../core/DragonBones.h"

DRAGONBONES_NAMESPACE_BEGIN

class IAnimateble
{
public:
    IAnimateble() {}
    virtual ~IAnimateble() {}

    virtual void advanceTime(float passedTime) = 0;
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_ANIMATEBLE_H