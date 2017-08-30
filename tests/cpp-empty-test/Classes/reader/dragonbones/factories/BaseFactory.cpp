#include "BaseFactory.h"

DRAGONBONES_NAMESPACE_BEGIN

JSONDataParser BaseFactory::_defaultDataParser;

BaseFactory::BaseFactory() :
    autoSearch(false),

    _dataParser(&_defaultDataParser),
    _dragonBonesDataMap(),
    _textureAtlasDataMap()
{}
BaseFactory::~BaseFactory() {}

TextureData* BaseFactory::_getTextureData(const std::string& dragonBonesName, const std::string& textureName) const
{
    const auto iterator = _textureAtlasDataMap.find(dragonBonesName);
    if (iterator != _textureAtlasDataMap.end())
    {
        for (const auto textureAtlasData : iterator->second)
        {
            const auto textureData = textureAtlasData->getTexture(textureName);
            if (textureData)
            {
                return textureData;
            }
        }
    }

    if (autoSearch)
    {
        for (const auto& pair : _textureAtlasDataMap)
        {
            for (const auto textureAtlasData : pair.second)
            {
                if (textureAtlasData->autoSearch)
                {
                    const auto textureData = textureAtlasData->getTexture(textureName);
                    if (textureData)
                    {
                        return textureData;
                    }
                }
            }
        }
    }

    return nullptr;
}

bool BaseFactory::_fillBuildArmaturePackage(const std::string& dragonBonesName, const std::string& armatureName, const std::string& skinName, BuildArmaturePackage& dataPackage) const
{
    if (!dragonBonesName.empty())
    {
        const auto iterator = _dragonBonesDataMap.find(dragonBonesName);
        if (iterator != _dragonBonesDataMap.end())
        {
            const auto armatureData = iterator->second->getArmature(armatureName);
            if (armatureData)
            {
                dataPackage.dataName = dragonBonesName;
                dataPackage.data = iterator->second;
                dataPackage.armature = armatureData;
                dataPackage.skin = armatureData->getSkin(skinName);
                if (!dataPackage.skin)
                {
                    dataPackage.skin = armatureData->getDefaultSkin();
                }

                return true;
            }
        }
    }

    if (dragonBonesName.empty() || autoSearch)
    {
        for (const auto& pair : _dragonBonesDataMap)
        {
            if (dragonBonesName.empty() || pair.second->autoSearch)
            {
                const auto armatureData = pair.second->getArmature(armatureName);
                if (armatureData)
                {
                    dataPackage.dataName = pair.first;
                    dataPackage.data = pair.second;
                    dataPackage.armature = armatureData;
                    dataPackage.skin = armatureData->getSkin(skinName);
                    if (!dataPackage.skin)
                    {
                        dataPackage.skin = armatureData->getDefaultSkin();
                    }

                    return true;
                }
            }
        }
    }

    return false;
}

void BaseFactory::_buildBones(const BuildArmaturePackage& dataPackage, Armature& armature) const
{
    for (const auto boneData : dataPackage.armature->getSortedBones())
    {
        const auto bone = BaseObject::borrowObject<Bone>();
        bone->name = boneData->name;
        bone->inheritTranslation = boneData->inheritTranslation;
        bone->inheritRotation = boneData->inheritRotation;
        bone->inheritScale = boneData->inheritScale;
        bone->length = boneData->length;
        bone->origin = boneData->transform; // copy

        if (boneData->parent)
        {
            armature.addBone(bone, boneData->parent->name);
        }
        else
        {
            armature.addBone(bone);
        }

        if (boneData->ik)
        {
            bone->ikBendPositive = boneData->bendPositive;
            bone->ikWeight = boneData->weight;
            bone->_setIK(armature.getBone(boneData->ik->name), boneData->chain, boneData->chainIndex);
        }
    }
}

void BaseFactory::_buildSlots(const BuildArmaturePackage& dataPackage, Armature& armature) const
{
    const auto currentSkin = dataPackage.skin;
    const auto defaultSkin = dataPackage.armature->getDefaultSkin();
    auto slotDisplayDataSetMap = defaultSkin->slots; // copy

    if (currentSkin != defaultSkin)
    {
        for (const auto& pair : currentSkin->slots)
        {
            slotDisplayDataSetMap[pair.first] = pair.second;
        }
    }

    for (const auto slotData : dataPackage.armature->getSortedSlots())
    {
        const auto itetator = slotDisplayDataSetMap.find(slotData->name);
        if (itetator == slotDisplayDataSetMap.cend())
        {
            continue;
        }

        const auto slot = _generateSlot(dataPackage, *itetator->second);
        slot->_displayDataSet = itetator->second;
        slot->_setDisplayIndex(slotData->displayIndex);
        slot->_setBlendMode(slotData->blendMode);
        slot->_setColor(*slotData->color);

        armature.addSlot(slot, slotData->parent->name);
    }
}

void BaseFactory::_replaceSlotDisplay(const BuildArmaturePackage& dataPackage, DisplayData& displayData, Slot& slot, int displayIndex) const
{
    if (displayIndex < 0)
    {
        displayIndex = slot.getDisplayIndex();
    }

    if (displayIndex >= 0)
    {
        auto displayList = slot.getDisplayList(); // copy
        if (displayList.size() <= (unsigned)displayIndex)
        {
            displayList.resize(displayIndex + 1, std::make_pair(nullptr, DisplayType::Image));
        }

        if (slot._replacedDisplayDataSet.size() <= (unsigned)displayIndex)
        {
            slot._replacedDisplayDataSet.resize(displayIndex + 1, nullptr);
        }

        slot._replacedDisplayDataSet[displayIndex] = const_cast<DisplayData*>(&displayData);

        if (displayData.type == DisplayType::Armature)
        {
            const auto childArmature = buildArmature(displayData.name, dataPackage.dataName);
            displayList[displayIndex] = std::make_pair(childArmature, DisplayType::Armature);
        }
        else
        {
            if (!displayData.texture)
            {
                displayData.texture = _getTextureData(dataPackage.dataName, displayData.name);
            }

            if (
                displayData.mesh &&
                (displayIndex < slot._displayDataSet->displays.size() && slot._displayDataSet->displays[displayIndex]->mesh)
            )
            {
                displayList[displayIndex] = std::make_pair(slot.getMeshDisplay(), displayData.type);
            }
            else
            {
                displayList[displayIndex] = std::make_pair(slot.getRawDisplay(), displayData.type);
            }
        }

        slot.setDisplayList(displayList);
        slot.invalidUpdate();
    }
}

DragonBonesData* BaseFactory::parseDragonBonesData(const char* rawData, const std::string& dragonBonesName, float scale)
{
    const auto dragonBonesData = _dataParser->parseDragonBonesData(rawData, scale);
    addDragonBonesData(dragonBonesData, dragonBonesName);

    return dragonBonesData;
}

TextureAtlasData* BaseFactory::parseTextureAtlasData(const char* rawData, void* textureAtlas, const std::string& dragonBonesName, float scale)
{
    const auto textureAtlasData = _generateTextureAtlasData(nullptr, nullptr);
    _dataParser->parseTextureAtlasData(rawData, *textureAtlasData, scale);

    _generateTextureAtlasData(textureAtlasData, textureAtlas);
    addTextureAtlasData(textureAtlasData, dragonBonesName);

    return textureAtlasData;
}

void BaseFactory::addDragonBonesData(DragonBonesData* data, const std::string& dragonBonesName)
{
    if (data)
    {
        const auto& mapName = dragonBonesName.empty() ? data->name : dragonBonesName;
        if (!mapName.empty())
        {
            if (_dragonBonesDataMap.find(mapName) == _dragonBonesDataMap.end())
            {
                _dragonBonesDataMap[mapName] = data;
            }
            else
            {
                DRAGONBONES_ASSERT(false, "Same name data.");
            }
        }
        else
        {
            DRAGONBONES_ASSERT(false, "Unnamed data.");
        }
    }
    else
    {
        DRAGONBONES_ASSERT(false, "Argument error.");
    }
}

void BaseFactory::removeDragonBonesData(const std::string& dragonBonesName, bool disposeData)
{
    const auto iterator = _dragonBonesDataMap.find(dragonBonesName);
    if (iterator != _dragonBonesDataMap.end())
    {
        if (disposeData)
        {
            iterator->second->returnToPool();
        }

        _dragonBonesDataMap.erase(iterator);
    }
}

void BaseFactory::addTextureAtlasData(TextureAtlasData* data, const std::string& dragonBonesName)
{
    if (data)
    {
        const auto& mapName = dragonBonesName.empty() ? data->name : dragonBonesName;
        if (!mapName.empty())
        {
            auto& textureAtlasList = _textureAtlasDataMap[mapName];
            if (std::find(textureAtlasList.begin(), textureAtlasList.end(), data) == textureAtlasList.end())
            {
                textureAtlasList.push_back(data);
            }
        }
        else
        {
            DRAGONBONES_ASSERT(false, "Unnamed data.");
        }
    }
    else
    {
        DRAGONBONES_ASSERT(false, "Argument error.");
    }
}

void BaseFactory::removeTextureAtlasData(const std::string& dragonBonesName, bool disposeData)
{
    const auto iterator = _textureAtlasDataMap.find(dragonBonesName);
    if (iterator != _textureAtlasDataMap.end())
    {
        if (disposeData)
        {
            for (const auto textureAtlasData : iterator->second)
            {
                textureAtlasData->returnToPool();
            }
        }

        _textureAtlasDataMap.erase(iterator);
    }
}

void BaseFactory::clear(bool disposeData)
{
    if (disposeData)
    {
        for (const auto& pair : _dragonBonesDataMap)
        {
            pair.second->returnToPool();
        }

        for (const auto& pair : _textureAtlasDataMap)
        {
            for (const auto textureAtlasData : pair.second)
            {
                textureAtlasData->returnToPool();
            }
        }
    }

    _dragonBonesDataMap.clear();
    _textureAtlasDataMap.clear();
}

Armature * BaseFactory::buildArmature(const std::string & armatureName, const std::string & dragonBonesName, const std::string & skinName) const
{
    BuildArmaturePackage dataPackage;
    if (_fillBuildArmaturePackage(dragonBonesName, armatureName, skinName, dataPackage))
    {
        const auto armature = _generateArmature(dataPackage);
        _buildBones(dataPackage, *armature);
        _buildSlots(dataPackage, *armature);

        // Update armature pose
        armature->advanceTime(0.f);
        return armature;
    }

    return nullptr;
}

bool BaseFactory::copyAnimationsToArmature(
    Armature& toArmature, 
    const std::string& fromArmatreName, const std::string& fromSkinName, const std::string& fromDragonBonesDataName, 
    bool ifRemoveOriginalAnimationList
) const
{
    BuildArmaturePackage dataPackage;
    if (_fillBuildArmaturePackage(fromDragonBonesDataName, fromArmatreName, fromSkinName, dataPackage))
    {
        const auto fromArmatureData = dataPackage.armature;
        if (ifRemoveOriginalAnimationList)
        {
            toArmature.getAnimation().setAnimations(fromArmatureData->animations);
        }
        else
        {
            auto animations = toArmature.getAnimation().getAnimations(); // copy

            for (const auto& pair : fromArmatureData->animations)
            {
                animations[pair.first] = pair.second;
            }

            toArmature.getAnimation().setAnimations(animations);
        }

        if (dataPackage.skin)
        {
            for (const auto toSlot : toArmature.getSlots())
            {
                const auto& toSlotDisplayList = toSlot->getDisplayList();
                std::size_t index = 0;
                for (const auto& pair : toSlotDisplayList)
                {
                    if (pair.second == DisplayType::Armature)
                    {
                        const auto displays = dataPackage.skin->getSlot(toSlot->name)->displays;
                        if (index < displays.size())
                        {
                            const auto fromDisplayData = displays[index];
                            if (fromDisplayData->type == DisplayType::Armature)
                            {
                                copyAnimationsToArmature(*(Armature*)pair.first, fromDisplayData->name, fromSkinName, fromDragonBonesDataName, ifRemoveOriginalAnimationList);
                            }
                        }
                    }

                    index++;
                }
            }

            return true;
        }
    }

    return false;
}

void BaseFactory::replaceSlotDisplay(const std::string& dragonBonesName, const std::string& armatureName, const std::string& slotName, const std::string& displayName, Slot& slot, int displayIndex) const
{
    BuildArmaturePackage dataPackage;
    if (_fillBuildArmaturePackage(dragonBonesName, armatureName, "", dataPackage))
    {
        const auto slotDisplayDataSet = dataPackage.skin->getSlot(slotName);
        if (slotDisplayDataSet)
        {
            for (const auto displayData : slotDisplayDataSet->displays)
            {
                if (displayData->name == displayName)
                {
                    _replaceSlotDisplay(dataPackage, *displayData, slot, displayIndex);
                }
            }
        }
    }
}

void BaseFactory::replaceSlotDisplayList(const std::string& dragonBonesName, const std::string& armatureName, const std::string& slotName, Slot& slot) const
{
    BuildArmaturePackage dataPackage;
    if (_fillBuildArmaturePackage(dragonBonesName, armatureName, "", dataPackage))
    {
        const auto slotDisplayDataSet = dataPackage.skin->getSlot(slotName);
        if (slotDisplayDataSet)
        {
            int displayIndex = 0;
            for (const auto displayData : slotDisplayDataSet->displays)
            {
                _replaceSlotDisplay(dataPackage, *displayData, slot, displayIndex++);
            }
        }
    }
}

DRAGONBONES_NAMESPACE_END
