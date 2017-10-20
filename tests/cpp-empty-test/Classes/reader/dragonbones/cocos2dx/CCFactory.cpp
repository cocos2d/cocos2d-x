#include "CCFactory.h"
#include "CCTextureData.h"
#include "CCArmatureDisplay.h"
#include "CCSlot.h"

DRAGONBONES_NAMESPACE_BEGIN

CCFactory* CCFactory::s_factory = nullptr;

CCFactory* CCFactory::getInstance()
{
    if (!s_factory)
        s_factory = new (std::nothrow) CCFactory();

    return s_factory;
}

void CCFactory::destroyInstance()
{
    delete s_factory;
    s_factory = nullptr;
}

CCFactory::CCFactory() 
{
    if (!EventObject::_soundEventManager) 
    {
        const auto display = CCArmatureDisplay::create();
        display->retain();

        EventObject::_soundEventManager = display;
    }
}
CCFactory::~CCFactory() 
{
    clear();
}

TextureAtlasData * CCFactory::_generateTextureAtlasData(TextureAtlasData* textureAtlasData, void* textureAtlas) const
{
    if (textureAtlasData)
    {
        static_cast<CCTextureAtlasData*>(textureAtlasData)->texture = (cocos2d::Texture2D*)textureAtlas;
    }
    else
    {
        textureAtlasData = BaseObject::borrowObject<CCTextureAtlasData>();
    }

    return textureAtlasData;
}

Armature * CCFactory::_generateArmature(const BuildArmaturePackage & dataPackage) const
{
    const auto armature = BaseObject::borrowObject<Armature>();
    const auto armatureDisplay = CCArmatureDisplay::create();

    armature->_armatureData = dataPackage.armature;
    armature->_skinData = dataPackage.skin;
    armature->_animation = BaseObject::borrowObject<Animation>();
    armature->_display = armatureDisplay;

    armatureDisplay->retain();
    armatureDisplay->setCascadeOpacityEnabled(true);
    armatureDisplay->setCascadeColorEnabled(true);
    armatureDisplay->_armature = armature;
    armature->_animation->_armature = armature;

    armature->getAnimation().setAnimations(dataPackage.armature->animations);

    return armature;
}

Slot * CCFactory::_generateSlot(const BuildArmaturePackage& dataPackage, const SlotDisplayDataSet& slotDisplayDataSet) const
{
    const auto slot = BaseObject::borrowObject<CCSlot>();
    const auto slotData = slotDisplayDataSet.slot;
    std::vector<std::pair<void*, DisplayType>> displayList;
    const auto rawDisplay = DBCCSprite::create();

    slot->name = slotData->name;
    slot->_rawDisplay = rawDisplay;
    slot->_meshDisplay = slot->_rawDisplay;

    displayList.reserve(slotDisplayDataSet.displays.size());
    rawDisplay->retain();
    rawDisplay->setCascadeOpacityEnabled(true);
    rawDisplay->setCascadeColorEnabled(true);
    rawDisplay->setAnchorPoint(cocos2d::Vec2::ZERO);

    for (const auto displayData : slotDisplayDataSet.displays)
    {
        switch (displayData->type)
        {
            case DisplayType::Image:
                if (!displayData->texture)
                {
                    displayData->texture = this->_getTextureData(dataPackage.dataName, displayData->name);
                }

                displayList.push_back(std::make_pair(slot->_rawDisplay, DisplayType::Image));
                break;

            case DisplayType::Mesh:
                if (!displayData->texture)
                {
                    displayData->texture = this->_getTextureData(dataPackage.dataName, displayData->name);
                }

                displayList.push_back(std::make_pair(slot->_meshDisplay, DisplayType::Mesh));
                break;

            case DisplayType::Armature:
            {
                const auto childArmature = buildArmature(displayData->name, dataPackage.dataName);
                if (childArmature)
                {
                    childArmature->getAnimation().play();
                }

                displayList.push_back(std::make_pair(childArmature, DisplayType::Armature));
                break;
            }

            default:
                displayList.push_back(std::make_pair(nullptr, DisplayType::Image));
                break;
        }
    }

    slot->_setDisplayList(displayList);

    rawDisplay->setLocalZOrder(slotData->zOrder);

    return slot;
}

DragonBonesData* CCFactory::loadDragonBonesData(const std::string& filePath, const std::string& dragonBonesName)
{
    if (!dragonBonesName.empty())
    {
        const auto existedData = this->getDragonBonesData(dragonBonesName);
        if (existedData)
        {
            return existedData;
        }
    }

    const auto fullpath = cocos2d::FileUtils::getInstance()->fullPathForFilename(filePath);
    const auto data = cocos2d::FileUtils::getInstance()->getStringFromFile(fullpath);
    if (data.empty())
    {
        return nullptr;
    }

    const auto scale = cocos2d::Director::getInstance()->getContentScaleFactor();
    return this->parseDragonBonesData(data.c_str(), dragonBonesName, 1.f / scale);
}

TextureAtlasData* CCFactory::loadTextureAtlasData(const std::string& filePath, const std::string& dragonBonesName, float scale)
{
    const auto fullpath = cocos2d::FileUtils::getInstance()->fullPathForFilename(filePath);
    const auto data = cocos2d::FileUtils::getInstance()->getStringFromFile(fullpath);
    if (data.empty())
    {
        return nullptr;
    }

    const auto textureAtlasData = static_cast<CCTextureAtlasData*>(BaseFactory::parseTextureAtlasData(data.c_str(), nullptr, dragonBonesName, scale));

    const auto pos = filePath.find_last_of("/");
    if (std::string::npos != pos)
    {
        const auto basePath = filePath.substr(0, pos + 1);
        textureAtlasData->imagePath = basePath + textureAtlasData->imagePath;
    }
    
    _initTextureAtlasData(textureAtlasData);

    return textureAtlasData;
}

TextureAtlasData* CCFactory::parseTextureAtlasData(const std::string& atlasData, const std::string& texturePath, const std::string& dragonBonesName, float scale)
{
    const auto textureAtlasData = static_cast<CCTextureAtlasData*>(BaseFactory::parseTextureAtlasData(atlasData.c_str(), nullptr, dragonBonesName, scale));
    textureAtlasData->imagePath = texturePath;
    _initTextureAtlasData(textureAtlasData);
    
    return textureAtlasData;

}

void CCFactory::_initTextureAtlasData(TextureAtlasData* atlasData)
{
    const auto textureCache = cocos2d::Director::getInstance()->getTextureCache();
    auto texture = textureCache->getTextureForKey(atlasData->imagePath);
    if (!texture)
    {
        const auto defaultPixelFormat = cocos2d::Texture2D::getDefaultAlphaPixelFormat();
        auto pixelFormat = defaultPixelFormat;
        switch (atlasData->format)
        {
            case TextureFormat::RGBA8888:
                pixelFormat = cocos2d::Texture2D::PixelFormat::RGBA8888;
                break;
                
            case TextureFormat::BGRA8888:
                pixelFormat = cocos2d::Texture2D::PixelFormat::BGRA8888;
                break;
                
            case TextureFormat::RGBA4444:
                pixelFormat = cocos2d::Texture2D::PixelFormat::RGBA4444;
                break;
                
            case TextureFormat::RGB888:
                pixelFormat = cocos2d::Texture2D::PixelFormat::RGB888;
                break;
                
            case TextureFormat::RGB565:
                pixelFormat = cocos2d::Texture2D::PixelFormat::RGB565;
                break;
                
            case TextureFormat::RGBA5551:
                pixelFormat = cocos2d::Texture2D::PixelFormat::RGB5A1;
                break;
                
            case TextureFormat::DEFAULT:
            default:
                break;
        }
        
        cocos2d::Texture2D::setDefaultAlphaPixelFormat(pixelFormat);
        texture = textureCache->addImage(atlasData->imagePath);
        cocos2d::Texture2D::setDefaultAlphaPixelFormat(defaultPixelFormat);
    }
    
    static_cast<CCTextureAtlasData*>(atlasData)->texture = texture;
}

CCArmatureDisplay * CCFactory::buildArmatureDisplay(const std::string& armatureName, const std::string& dragonBonesName, const std::string& skinName) const
{
    const auto armature = this->buildArmature(armatureName, dragonBonesName, skinName);
    const auto armatureDisplay = armature ? dynamic_cast<CCArmatureDisplay*>(armature->_display) : nullptr;
    if (armatureDisplay)
    {
        armatureDisplay->advanceTimeBySelf(true);
    }

    return armatureDisplay;
}

cocos2d::Sprite* CCFactory::getTextureDisplay(const std::string& textureName, const std::string& dragonBonesName) const
{
    const auto textureData = static_cast<CCTextureData*>(this->_getTextureData(dragonBonesName, textureName));
    if (textureData) 
    {
        if (!textureData->texture)
        {
            const auto textureAtlasTexture = static_cast<CCTextureAtlasData*>(textureData->parent)->texture;
            cocos2d::Rect rect(textureData->region.x, textureData->region.y, textureData->region.width, textureData->region.height);
            cocos2d::Vec2 offset(0.f, 0.f);
            cocos2d::Size originSize(textureData->region.width, textureData->region.height);
            textureData->texture = cocos2d::SpriteFrame::createWithTexture(textureAtlasTexture, rect, textureData->rotated, offset, originSize); // TODO multiply textureAtlas
            textureData->texture->retain();
        }

        return cocos2d::Sprite::createWithSpriteFrame(textureData->texture);
    }

    return nullptr;
}

CCArmatureDisplay* CCFactory::getSoundEventManater() const
{
    return dynamic_cast<CCArmatureDisplay*>(static_cast<IArmatureDisplay*>(EventObject::_soundEventManager));
}

DRAGONBONES_NAMESPACE_END
