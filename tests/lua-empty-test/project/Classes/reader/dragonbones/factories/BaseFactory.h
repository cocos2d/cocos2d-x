#ifndef DRAGONBONES_BASE_FACTORY_H
#define DRAGONBONES_BASE_FACTORY_H

#include "../parsers/JSONDataParser.h"
#include "../armature/Armature.h"
#include "../animation/Animation.h"
#include "../armature/Bone.h"
#include "../armature/Slot.h"

DRAGONBONES_NAMESPACE_BEGIN

/**
 * @private
 */
class BuildArmaturePackage final
{
public:
    std::string dataName;
    DragonBonesData* data;
    ArmatureData* armature;
    SkinData* skin;

public:
    BuildArmaturePackage() :
        dataName(),
        data(nullptr),
        armature(nullptr),
        skin(nullptr)
    {
    }
    ~BuildArmaturePackage() {}

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(BuildArmaturePackage);
};

class BaseFactory
{
protected:
    static JSONDataParser _defaultDataParser;

public:
    bool autoSearch;

protected:
    DataParser* _dataParser;
    std::map<std::string, DragonBonesData*> _dragonBonesDataMap;
    std::map<std::string, std::vector<TextureAtlasData*>> _textureAtlasDataMap;

public:
    /** @private */
    BaseFactory();
    /** @private */
    virtual ~BaseFactory() = 0;

protected:
    virtual TextureData* _getTextureData(const std::string& dragonBonesName, const std::string& textureName) const;
    virtual bool _fillBuildArmaturePackage(const std::string& dragonBonesName, const std::string& armatureName, const std::string& skinName, BuildArmaturePackage& dataPackage) const;
    virtual void _buildBones(const BuildArmaturePackage& dataPackage, Armature& armature) const;
    virtual void _buildSlots(const BuildArmaturePackage& dataPackage, Armature& armature) const;
    virtual void _replaceSlotDisplay(const BuildArmaturePackage& dataPackage, DisplayData& displayData, Slot& slot, int displayIndex) const;

    virtual TextureAtlasData* _generateTextureAtlasData(TextureAtlasData* textureAtlasData, void* textureAtlas) const = 0;
    virtual Armature* _generateArmature(const BuildArmaturePackage& dataPackage) const = 0;
    virtual Slot* _generateSlot(const BuildArmaturePackage& dataPackage, const SlotDisplayDataSet& slotDisplayDataSet) const = 0;

public:
    virtual DragonBonesData* parseDragonBonesData(const char* rawData, const std::string& dragonBonesName = "", float scale = 1.f);
    virtual TextureAtlasData* parseTextureAtlasData(const char* rawData, void* textureAtlas, const std::string& dragonBonesName = "", float scale = 0.f);
    virtual void addDragonBonesData(DragonBonesData* data, const std::string& dragonBonesName = "");
    virtual void removeDragonBonesData(const std::string& dragonBonesName, bool disposeData = true);
    virtual void addTextureAtlasData(TextureAtlasData* data, const std::string& dragonBonesName = "");
    virtual void removeTextureAtlasData(const std::string& dragonBonesName, bool disposeData = true);
    virtual void clear(bool disposeData = true);

    virtual Armature* buildArmature(const std::string& armatureName, const std::string& dragonBonesName = "", const std::string& skinName = "") const;
    virtual bool copyAnimationsToArmature(
        Armature& toArmature, 
        const std::string& fromArmatreName, const std::string& fromSkinName = "", const std::string& fromDragonBonesDataName = "", 
        bool ifRemoveOriginalAnimationList = true
    ) const;
    virtual void replaceSlotDisplay(const std::string& dragonBonesName, const std::string& armatureName, const std::string& slotName, const std::string& displayName, Slot& slot, int displayIndex = -1) const;
    virtual void replaceSlotDisplayList(const std::string& dragonBonesName, const std::string& armatureName, const std::string& slotName, Slot& slot) const;

    inline DragonBonesData* getDragonBonesData(const std::string& dragonBonesName) const 
    {
        return mapFind(_dragonBonesDataMap, dragonBonesName);
    }

    inline std::vector<TextureAtlasData*>* getTextureAtlasData(const std::string& dragonBonesName) const
    {
        const auto iterator = _textureAtlasDataMap.find(dragonBonesName);
        return (iterator != _textureAtlasDataMap.end()) ? &const_cast<std::vector<TextureAtlasData*>&>(iterator->second) : nullptr;
    }
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_BASE_FACTORY_H
