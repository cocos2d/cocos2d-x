#include "DragonBonesData.h"

DRAGONBONES_NAMESPACE_BEGIN

DragonBonesData::DragonBonesData()
{
    _onClear();
}
DragonBonesData::~DragonBonesData()
{
    _onClear();
}

void DragonBonesData::_onClear()
{
    autoSearch = false;
    frameRate = 0;
    name.clear();

    for (const auto& pair : armatures)
    {
        pair.second->returnToPool();
    }

    armatures.clear();

    _armatureNames.clear();
}

void DragonBonesData::addArmature(ArmatureData * value)
{
    if (value && !value->name.empty() && armatures.find(value->name) == armatures.end())
    {
        armatures[value->name] = value;
        _armatureNames.push_back(value->name);
        value->parent = this;
    }
    else
    {
        DRAGONBONES_ASSERT(false, "Argument error.");
    }
}

DRAGONBONES_NAMESPACE_END
