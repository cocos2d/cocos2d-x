#include "Slot.h"
#include "Armature.h"
#include "../model/TimelineData.h"
#include "../animation/Animation.h"

DRAGONBONES_NAMESPACE_BEGIN

Slot::Slot() :
    _rawDisplay(nullptr),
    _meshDisplay(nullptr)
{}
Slot::~Slot() {}

void Slot::_onClear()
{
    TransformObject::_onClear();

    std::vector<std::pair<void*, DisplayType>> disposeDisplayList;
    for (const auto& pair : this->_displayList)
    {
        if (
            pair.first != _rawDisplay && pair.first != _meshDisplay &&
            std::find(disposeDisplayList.cbegin(), disposeDisplayList.cend(), pair) == disposeDisplayList.cend()
        )
        {
            disposeDisplayList.push_back(pair);
        }
    }

    for (const auto& pair : disposeDisplayList)
    {
        if (pair.second == DisplayType::Armature)
        {
            static_cast<Armature*>(pair.first)->returnToPool();
        }
        else
        {
            _disposeDisplay(pair.first);
        }
    }

    if (_meshDisplay && _meshDisplay != _rawDisplay) 
    {
        _disposeDisplay(_meshDisplay);
    }

    if (_rawDisplay) {
        _disposeDisplay(_rawDisplay);
    }

    inheritAnimation = true;
    displayController.clear();

    _colorDirty = false;
    _ffdDirty = false;
    _blendIndex = 0;
    _zOrder = 0;
    _blendMode = BlendMode::Normal;
    _pivotX = 0.f;
    _pivotY = 0.f;
    _displayDataSet = nullptr;
    _meshData = nullptr;
    _cacheFrames = nullptr;
    _rawDisplay = nullptr;
    _meshDisplay = nullptr;
    _colorTransform.identity();
    _ffdVertices.clear();
    _replacedDisplayDataSet.clear();

    _displayDirty = false;
    _blendModeDirty = false;
    _originDirty = false;
    _transformDirty = false;
    _displayIndex = 0;
    _display = nullptr;
    _childArmature = nullptr;
    _localMatrix.identity();
    _displayList.clear();
    _meshBones.clear();
}

void Slot::_updateDisplay()
{
    const auto prevDisplay = _display ? _display : _rawDisplay;
    const auto prevChildArmature = _childArmature;

    if (_displayIndex >= 0 && (std::size_t)_displayIndex < _displayList.size())
    {
        const auto& displayPair = _displayList[_displayIndex];
        if (displayPair.second == DisplayType::Armature)
        {
            _childArmature = static_cast<Armature*>(displayPair.first);
            _display = _childArmature->_display;
        }
        else
        {
            _display = displayPair.first;
            _childArmature = nullptr;
        }
    }
    else
    {
        _display = nullptr;
        _childArmature = nullptr;
    }

    const auto currentDisplay = _display ? _display : _rawDisplay;

    if (currentDisplay != prevDisplay)
    {
        _onUpdateDisplay();

        if (prevDisplay)
        {
            _replaceDisplay(prevDisplay, prevChildArmature != nullptr);
        }
        else
        {
            _addDisplay();
        }

        _blendModeDirty = true;
        _colorDirty = true;
    }

    if (_displayDataSet && _displayIndex >= 0 && (std::size_t)_displayIndex < _displayDataSet->displays.size())
    {
        this->origin = _displayDataSet->displays[_displayIndex]->transform; // copy
        _originDirty = true;
    }

    _updateMeshData(false);

    if (currentDisplay == _rawDisplay || currentDisplay == _meshDisplay)
    {
        _updateFrame();
    }

    if (_childArmature != prevChildArmature)
    {
        if (prevChildArmature)
        {
            prevChildArmature->_parent = nullptr;
            if (inheritAnimation)
            {
                prevChildArmature->getAnimation().reset();
            }
        }

        if (_childArmature)
        {
            _childArmature->_parent = this;
            if (inheritAnimation)
            {
                if (_childArmature->getCacheFrameRate() == 0)
                {
                    const auto chacheFrameRate = this->_armature->getCacheFrameRate();
                    if (chacheFrameRate != 0)
                    {
                        _childArmature->setCacheFrameRate(chacheFrameRate);
                    }
                }
                
                const auto slotData = this->_armature->getArmatureData().getSlot(this->name);
                const auto& actions = !slotData->actions.empty() ? slotData->actions : _childArmature->getArmatureData().actions;
                if (!actions.empty())
                {
                    for (const auto action : actions) 
                    {
                        _childArmature->_bufferAction(action);
                    }
                }
                else 
                {
                    _childArmature->getAnimation().play();
                }
            }
        }
    }
}

void Slot::_setArmature(Armature* value)
{
    if (this->_armature == value)
    {
        return;
    }

    if (this->_armature)
    {
        this->_armature->_removeSlotFromSlotList(this);
    }

    this->_armature = value;

    _onUpdateDisplay();

    if (this->_armature)
    {
        this->_armature->_addSlotToSlotList(this);
        _addDisplay();
    }
    else
    {
        _removeDisplay();
    }
}

void Slot::_updateMeshData(bool isTimelineUpdate)
{
    const auto prevMeshData = _meshData;
    auto rawMeshData = (MeshData*)nullptr;
    if (_display && _display == _meshDisplay && _displayIndex >= 0)
    {
        rawMeshData = (_displayDataSet && _displayIndex < _displayDataSet->displays.size()) ? _displayDataSet->displays[_displayIndex]->mesh : nullptr;
        const auto replaceDisplayData = (_displayIndex < _replacedDisplayDataSet.size()) ? _replacedDisplayDataSet[_displayIndex] : nullptr;
        const auto replaceMeshData = replaceDisplayData ? replaceDisplayData->mesh : nullptr;
        _meshData = replaceMeshData? replaceMeshData: rawMeshData;
    }
    else
    {
        _meshData = nullptr;
    }

    if (_meshData != prevMeshData)
    {
        if (_meshData && _meshData == rawMeshData)
        {
            if (_meshData->skinned)
            {
                _meshBones.resize(_meshData->bones.size(), nullptr);

                for (std::size_t i = 0, l = _meshBones.size(); i < l; ++i)
                {
                    _meshBones[i] = this->_armature->getBone(_meshData->bones[i]->name);
                }

                std::size_t ffdVerticesCount = 0;
                for (std::size_t i = 0, l = _meshData->boneIndices.size(); i < l; ++i)
                {
                    ffdVerticesCount += _meshData->boneIndices[i].size();
                }

                _ffdVertices.resize(ffdVerticesCount * 2.f, 0.f);
            }
            else
            {
                _meshBones.clear();
                _ffdVertices.resize(_meshData->vertices.size(), 0.f);
            }

            _ffdDirty = true;
        }
        else
        {
            _meshBones.clear();
            _ffdVertices.clear();
        }

        if (isTimelineUpdate)
        {
            _armature->getAnimation()._updateFFDTimelineStates();
        }
    }
}

void Slot::_update(int cacheFrameIndex)
{
    _blendIndex = 0;

    if (_displayDirty)
    {
        _displayDirty = false;
        _updateDisplay();
    }

    if (!_display)
    {
        return;
    }

    if (_blendModeDirty)
    {
        _blendModeDirty = false;
        _updateBlendMode();
    }

    if (_colorDirty)
    {
        _colorDirty = false;
        _updateColor();
    }

    if (_meshData)
    {
        if (_ffdDirty || (_meshData->skinned && _isMeshBonesUpdate()))
        {
            _ffdDirty = false;
            _updateMesh();
        }

        if (_meshData->skinned)
        {
            return;
        }
    }

    if (_originDirty)
    {
        _originDirty = false;
        _transformDirty = true;
        _updateLocalTransformMatrix();
    }

    if (cacheFrameIndex >= 0)
    {
        const auto cacheFrame = (*_cacheFrames)[cacheFrameIndex];
        if (this->globalTransformMatrix == cacheFrame)
        {
            _transformDirty = false;
        }
        else if (cacheFrame)
        {
            _transformDirty = true;
            this->globalTransformMatrix = cacheFrame;
        }
        else if (_transformDirty || this->_parent->_transformDirty != Bone::BoneTransformDirty::None)
        {
            _transformDirty = true;
            this->globalTransformMatrix = &this->_globalTransformMatrix;
        }
        else if (this->globalTransformMatrix != &this->_globalTransformMatrix)
        {
            _transformDirty = false;
            (*_cacheFrames)[cacheFrameIndex] = this->globalTransformMatrix;
        }
        else
        {
            _transformDirty = true;
            this->globalTransformMatrix = &this->_globalTransformMatrix;
        }
    }
    else if (_transformDirty || this->_parent->_transformDirty != Bone::BoneTransformDirty::None)
    {
        _transformDirty = true;
        this->globalTransformMatrix = &this->_globalTransformMatrix;
    }

    if (_transformDirty)
    {
        _transformDirty = false;

        if (this->globalTransformMatrix == &this->_globalTransformMatrix)
        {
            _updateGlobalTransformMatrix();

            if (cacheFrameIndex >= 0 && !(*_cacheFrames)[cacheFrameIndex])
            {
                this->globalTransformMatrix = SlotTimelineData::cacheFrame(*_cacheFrames, cacheFrameIndex, this->_globalTransformMatrix);
            }
        }

        _updateTransform();
    }
}

bool Slot::_setDisplayList(const std::vector<std::pair<void*, DisplayType>>& value)
{
    if (!value.empty())
    {
        if (_displayList.size() != value.size())
        {
            _displayList.resize(value.size());
        }

        for (std::size_t i = 0, l = value.size(); i < l; ++i)
        {
            const auto& eachPair = value[i];
            if (
                eachPair.first && eachPair.first != _rawDisplay && eachPair.first != _meshDisplay &&
                eachPair.second != DisplayType::Armature && std::find(_displayList.cbegin(), _displayList.cend(), eachPair) == _displayList.cend()
            )
            {
                _initDisplay(eachPair.first);
            }

            _displayList[i].first = eachPair.first;
            _displayList[i].second = eachPair.second;
        }
    }
    else if (!_displayList.empty())
    {
        _displayList.clear();
    }

    if (_displayIndex >= 0 && (std::size_t)_displayIndex < _displayList.size())
    {
        _displayDirty = _display != _displayList[_displayIndex].first;
    }
    else
    {
        _displayDirty = _display != nullptr;
    }

    return _displayDirty;
}

bool Slot::_setDisplayIndex(int value)
{
    if (_displayIndex == value)
    {
        return false;
    }

    _displayIndex = value;
    _displayDirty = true;

    return _displayDirty;
}

bool Slot::_setBlendMode(BlendMode value)
{
    if (_blendMode == value)
    {
        return false;
    }

    _blendMode = value;
    _blendModeDirty = true;

    return true;
}

bool Slot::_setColor(const ColorTransform& value)
{
    _colorTransform = value; // copy
    _colorDirty = true;

    return true;
}

void Slot::setDisplayIndex(int value)
{
    if (_setDisplayIndex(value))
    {
        _update(-1);
    }
}

void Slot::setDisplayList(const std::vector<std::pair<void*, DisplayType>>& value)
{
    const auto backupDisplayList = _displayList; // copy
    auto disposeDisplayList = backupDisplayList; // copy
    disposeDisplayList.clear();

    if (_setDisplayList(value))
    {
        _update(-1);
    }

    for (const auto& pair : backupDisplayList)
    {
        if (
            pair.first && pair.first != _rawDisplay && pair.first != _meshDisplay &&
            std::find(_displayList.cbegin(), _displayList.cend(), pair) == _displayList.cend() &&
            std::find(disposeDisplayList.cbegin(), disposeDisplayList.cend(), pair) == disposeDisplayList.cend()
        )
        {
            disposeDisplayList.push_back(pair);
        }
    }

    for (const auto& pair : disposeDisplayList)
    {
        if (pair.second == DisplayType::Armature)
        {
            static_cast<Armature*>(pair.first)->returnToPool();
        }
        else
        {
            _disposeDisplay(pair.first);
        }
    }
}

void Slot::setDisplay(void* value, DisplayType displayType)
{
    if (_display == value)
    {
        return;
    }

    const auto displayListLength = _displayList.size();
    if (_displayIndex < 0 && displayListLength == 0)  // Emprty
    {
        _displayIndex = 0;
    }

    if (_displayIndex < 0)
    {
        return;
    }
    else
    {
        auto relpaceDisplayList = _displayList; // copy
        if (displayListLength <= (std::size_t)_displayIndex)
        {
            relpaceDisplayList.resize(_displayIndex + 1);
        }

        relpaceDisplayList[_displayIndex].first = value;
        relpaceDisplayList[_displayIndex].second = displayType;

        setDisplayList(relpaceDisplayList);
    }
}

void Slot::setChildArmature(Armature* value)
{
    if (_childArmature == value)
    {
        return;
    }

    if (value)
    {
        (value->getDisplay())->advanceTimeBySelf(false);
    }

    setDisplay(value, DisplayType::Armature);
}

DRAGONBONES_NAMESPACE_END