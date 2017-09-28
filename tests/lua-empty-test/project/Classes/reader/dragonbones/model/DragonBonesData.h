#ifndef DRAGONBONES_DRAGONBONES_DATA_H
#define DRAGONBONES_DRAGONBONES_DATA_H

#include "../core/BaseObject.h"
#include "ArmatureData.h"

DRAGONBONES_NAMESPACE_BEGIN

class DragonBonesData : public BaseObject
{
    BIND_CLASS_TYPE(DragonBonesData);

public:
    bool autoSearch;
    unsigned frameRate;
    std::string name;
    std::map<std::string, ArmatureData*> armatures;

private:
    std::vector<std::string> _armatureNames;

public:
    /** @private */
    DragonBonesData();
    /** @private */
    ~DragonBonesData();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(DragonBonesData);

protected:
    void _onClear() override;

public:
    /** @private */
    void addArmature(ArmatureData* value);

    inline ArmatureData* getArmature(const std::string& theName) const
    {
        return mapFind(armatures, theName);
    }

    inline const std::vector<std::string>& getArmatureNames() const 
    {
        return _armatureNames;
    }
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_DRAGONBONES_DATA_H
