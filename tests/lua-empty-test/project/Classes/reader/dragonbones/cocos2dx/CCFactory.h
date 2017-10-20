#ifndef DRAGONBONES_CC_FACTORY_H
#define DRAGONBONES_CC_FACTORY_H

#include "dragonbones/DragonBonesHeaders.h"
#include "cocos2d.h"
#include "CCArmatureDisplay.h"

DRAGONBONES_NAMESPACE_BEGIN

class CCFactory : public BaseFactory
{
public:
    static CCFactory* getInstance();
    static void destroyInstance();

private:
    static CCFactory *s_factory;

public:
    CCFactory();
    ~CCFactory();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(CCFactory);

protected:
    virtual TextureAtlasData* _generateTextureAtlasData(TextureAtlasData* textureAtlasData, void* textureAtlas) const override;
    virtual Armature* _generateArmature(const BuildArmaturePackage& dataPackage) const override;
    virtual Slot* _generateSlot(const BuildArmaturePackage& dataPackage, const SlotDisplayDataSet& slotDisplayDataSet) const override;

public:
    virtual DragonBonesData* loadDragonBonesData(const std::string& filePath, const std::string& dragonBonesName = "");
    virtual TextureAtlasData* loadTextureAtlasData(const std::string& filePath, const std::string& dragonBonesName = "", float scale = 0.f);
    virtual TextureAtlasData* parseTextureAtlasData(const std::string& atlasData, const std::string& texturePath, const std::string& dragonBonesName = "", float scale = 0.f);
    virtual CCArmatureDisplay* buildArmatureDisplay(const std::string& armatureName, const std::string& dragonBonesName = "", const std::string& skinName = "") const;
    virtual cocos2d::Sprite* getTextureDisplay(const std::string& textureName, const std::string& dragonBonesName = "") const;
    virtual CCArmatureDisplay* getSoundEventManater() const;

private:
    void _initTextureAtlasData(TextureAtlasData* atlasData);
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_CC_FACTORY_H
