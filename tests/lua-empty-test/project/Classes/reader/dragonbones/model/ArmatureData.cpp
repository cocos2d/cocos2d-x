#include "ArmatureData.h"

DRAGONBONES_NAMESPACE_BEGIN

BoneData::BoneData()
{
    _onClear();
}
BoneData::~BoneData()
{
    _onClear();
}

void BoneData::_onClear()
{
    inheritTranslation = false;
    inheritRotation = false;
    inheritScale = false;
    bendPositive = false;
    chain = 0;
    chainIndex = 0;
    weight = 0.f;
    length = 0.f;
    name.clear();
    parent = nullptr;
    ik = nullptr;
    transform.identity();
}

ColorTransform SlotData::DEFAULT_COLOR;
ColorTransform * SlotData::generateColor()
{
    return new ColorTransform();
}

SlotData::SlotData() :
    color(nullptr)
{
    _onClear();
}
SlotData::~SlotData()
{
    _onClear();
}

void SlotData::_onClear()
{
    for (const auto action : actions) 
    {
        action->returnToPool();
    }

    displayIndex = 0;
    zOrder = 0;
    blendMode = BlendMode::Normal;
    name.clear();
    parent = nullptr;

    if (color)
    {
        if (color != &DEFAULT_COLOR)
        {
            delete color;
        }

        color = nullptr;
    }

    actions.clear();
}

MeshData::MeshData() 
{
    _onClear();
}
MeshData::~MeshData()
{
    _onClear();
}

void MeshData::_onClear()
{
    skinned = false;
    slotPose.identity();
    uvs.clear();
    vertices.clear();
    vertexIndices.clear();
    boneIndices.clear();
    weights.clear();
    boneVertices.clear();
    bones.clear();
    inverseBindPose.clear();
}

DisplayData::DisplayData() :
    mesh(nullptr)
{
    _onClear();
}
DisplayData::~DisplayData() 
{
    _onClear();
}

void DisplayData::_onClear()
{
    isRelativePivot = false;
    type = DisplayType::Image;
    name.clear();
    texture = nullptr;
    armature = nullptr;

    if (mesh)
    {
        mesh->returnToPool();
        mesh = nullptr;
    }

    pivot.clear();
    transform.identity();
}

SlotDisplayDataSet::SlotDisplayDataSet() 
{
    _onClear();
}
SlotDisplayDataSet::~SlotDisplayDataSet() 
{
    _onClear();
}

void SlotDisplayDataSet::_onClear()
{
    slot = nullptr;

    for (const auto displayData : displays)
    {
        displayData->returnToPool();
    }

    displays.clear();
}

SkinData::SkinData() 
{
    _onClear();
}
SkinData::~SkinData() 
{
    _onClear();
}

void SkinData::_onClear()
{
    name.clear();

    for (const auto& pair : slots)
    {
        pair.second->returnToPool();
    }

    slots.clear();
}

void SkinData::addSlot(SlotDisplayDataSet* value)
{
    if (value && value->slot && slots.find(value->slot->name) == slots.end())
    {
        slots[value->slot->name] = value;
    }
    else
    {
        DRAGONBONES_ASSERT(false, "Argument error.");
    }
}

bool ArmatureData::_onSortSlots(const SlotData* a, const SlotData* b)
{
    return a->zOrder < b->zOrder;
}

ArmatureData::ArmatureData()
{
    _onClear();
}
ArmatureData::~ArmatureData()
{
    _onClear();
}

void ArmatureData::_onClear()
{
    for (const auto& pair : bones)
    {
        pair.second->returnToPool();
    }

    for (const auto& pair : slots)
    {
        pair.second->returnToPool();
    }

    for (const auto& pair : skins)
    {
        pair.second->returnToPool();
    }

    for (const auto& pair : animations)
    {
        pair.second->returnToPool();
    }

    for (const auto action : actions)
    {
        action->returnToPool();
    }

    frameRate = 0;
    type = ArmatureType::Armature;
    name.clear();
    parent = nullptr;
    aabb.clear();
    actions.clear();
    bones.clear();
    slots.clear();
    skins.clear();
    animations.clear();

    cacheFrameRate = 0;
    scale = 1.f;

    _boneDirty = false;
    _slotDirty = false;
    _defaultSkin = nullptr;
    _defaultAnimation = nullptr;

    _sortedBones.clear();
    _sortedSlots.clear();
    _bonesChildren.clear();
}

void ArmatureData::_sortBones()
{
    if (_sortedBones.empty())
    {
        return;
    }

    const auto total = _sortedBones.size();
    const auto sortHelper = _sortedBones;
    std::size_t index = 0;
    std::size_t count = 0;

    _sortedBones.clear();

    while (count < total)
    {
        const auto bone = sortHelper[index++];

        if (index >= total)
        {
            index = 0;
        }
        
        if (std::find(_sortedBones.cbegin(), _sortedBones.cend(), bone) != _sortedBones.cend())
        {
            continue;
        }

        if (bone->parent && std::find(_sortedBones.cbegin(), _sortedBones.cend(), bone->parent) == _sortedBones.cend())
        {
            continue;
        }
        
        if (bone->ik && std::find(_sortedBones.cbegin(), _sortedBones.cend(), bone->ik) == _sortedBones.cend())
        {
            continue;
        }

        if (bone->ik && bone->chain > 0 && bone->chainIndex == bone->chain)
        {
            auto parentInerator = std::find(_sortedBones.begin(), _sortedBones.end(), bone->parent);
            _sortedBones.insert(parentInerator + 1, bone);
        }
        else
        {
            _sortedBones.push_back(bone);
        }
        
        count++;
    }
}

void ArmatureData::_sortSlots()
{
    std::sort(_sortedSlots.begin(), _sortedSlots.end(), _onSortSlots);

    auto copy = _sortedSlots;
    copy.swap(_sortedSlots);
}

void ArmatureData::cacheFrames(unsigned value)
{
    if (cacheFrameRate == value)
    {
        return;
    }

    cacheFrameRate = value;

    const auto frameScale = (float)cacheFrameRate / frameRate;
    for (const auto& pair : animations)
    {
        pair.second->cacheFrames(frameScale);
    }
}

void ArmatureData::addBone(BoneData* value, const std::string& parentName)
{
    if (value && !value->name.empty() && bones.find(value->name) == bones.end())
    {
        if (!parentName.empty())
        {
            const auto parent = getBone(parentName);
            if (parent)
            {
                value->parent = parent;
            }
            else
            {
                auto& children = _bonesChildren[parentName];
                children.push_back(value);
            }
        }

        const auto iterator = _bonesChildren.find(value->name);
        if (iterator != _bonesChildren.cend())
        {
            for (const auto child : iterator->second)
            {
                child->parent = value;
            }

            _bonesChildren.erase(iterator);
        }

        bones[value->name] = value;
        _sortedBones.push_back(value);
        _boneDirty = true;
    }
    else
    {
        DRAGONBONES_ASSERT(false, "Argument error.");
    }
}

void ArmatureData::addSlot(SlotData* value)
{
    if (value && !value->name.empty() && slots.find(value->name) == slots.end())
    {
        slots[value->name] = value;
        _slotDirty = true;
        _sortedSlots.push_back(value);
    }
    else
    {
        DRAGONBONES_ASSERT(false, "Argument error.");
    }
}

void ArmatureData::addSkin(SkinData* value)
{
    if (value && !value->name.empty() && skins.find(value->name) == skins.end())
    {
        skins[value->name] = value;
        if (!_defaultSkin)
        {
            _defaultSkin = value;
        }
    }
    else
    {
        DRAGONBONES_ASSERT(false, "Argument error.");
    }
}

void ArmatureData::addAnimation(AnimationData* value)
{
    if (value && !value->name.empty() && animations.find(value->name) == animations.end())
    {
        animations[value->name] = value;
        if (!_defaultAnimation)
        {
            _defaultAnimation = value;
        }
    }
    else
    {
        DRAGONBONES_ASSERT(false, "Argument error.");
    }
}

DRAGONBONES_NAMESPACE_END