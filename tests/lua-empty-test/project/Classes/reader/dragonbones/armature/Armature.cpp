#include "Armature.h"
#include "Bone.h"
#include "Slot.h"
#include "../animation/Animation.h"
#include "../events/EventObject.h"

DRAGONBONES_NAMESPACE_BEGIN

Armature::Armature() :
    _animation(nullptr),
    _display(nullptr)
{
    _onClear();
}
Armature::~Armature()
{
    _onClear();
}

void Armature::_onClear()
{
    for (const auto bone : _bones)
    {
        bone->returnToPool();
    }

    for (const auto slot : _slots)
    {
        slot->returnToPool();
    }

    for (const auto event : _events)
    {
        event->returnToPool();
    }

    userData = nullptr;

    _bonesDirty = false;
    _cacheFrameIndex = -1;
    _delayAdvanceTime = -1.f;
    _armatureData = nullptr;
    _skinData = nullptr;

    if (_animation)
    {
        _animation->returnToPool();
        _animation = nullptr;
    }

    if (_display)
    {
        _display->_onClear();
        _display = nullptr;
    }

    _replacedTexture = nullptr;
    _parent = nullptr;

    _delayDispose = false;
    _lockDispose = false;
    _lockActionAndEvent = false;
    _slotsDirty = false;
    _bones.clear();
    _slots.clear();
    _actions.clear();
    _events.clear();
}

void Armature::_sortBones()
{
    if (_bones.empty())
    {
        return;
    }

    const auto total = _bones.size();
    const auto sortHelper = _bones;
    std::size_t index = 0;
    std::size_t count = 0;

    _bones.clear();

    while (count < total)
    {
        const auto bone = sortHelper[index++];

        if (index >= total)
        {
            index = 0;
        }

        if (std::find(_bones.cbegin(), _bones.cend(), bone) != _bones.cend())
        {
            continue;
        }

        if (bone->getParent() && std::find(_bones.cbegin(), _bones.cend(), bone->getParent()) == _bones.cend())
        {
            continue;
        }

        if (bone->getIK() && std::find(_bones.cbegin(), _bones.cend(), bone->getIK()) == _bones.cend())
        {
            continue;
        }

        if (bone->getIK() && bone->getIKChain() > 0 && bone->getIKChainIndex() == bone->getIKChain())
        {
            auto parentInerator = std::find(_bones.begin(), _bones.end(), bone->getParent());
            _bones.insert(parentInerator + 1, bone);
        }
        else
        {
            _bones.push_back(bone);
        }

        count++;
    }
}

void Armature::_sortSlots()
{
}

void Armature::_doAction(const ActionData& value)
{
    const auto& ints = std::get<0>(value.data);
    const auto& floats = std::get<1>(value.data);
    const auto& strings = std::get<2>(value.data);

    switch (value.type) 
    {
        case ActionType::Play:
            _animation->play(strings[0], ints[0]);
            break;

        case ActionType::Stop:
            _animation->stop(strings[0]);
            break;

        case ActionType::GotoAndPlay:
            _animation->gotoAndPlayByTime(strings[0], floats[0], ints[0]);
            break;

        case ActionType::GotoAndStop:
            _animation->gotoAndStopByTime(strings[0], floats[0]);
            break;

        case ActionType::FadeIn:
            _animation->fadeIn(strings[0], floats[0], ints[0]);
            break;

        case ActionType::FadeOut:
            // TODO fade out
            break;

        default:
            break;
    }
}

void Armature::_addBoneToBoneList(Bone* value)
{
    if (std::find(_bones.begin(), _bones.end(), value) == _bones.end())
    {
        _bonesDirty = true;
        _bones.push_back(value);
        _animation->_timelineStateDirty = true;
    }
}

void Armature::_removeBoneFromBoneList(Bone* value)
{
    const auto iterator = std::find(_bones.begin(), _bones.end(), value);
    if (iterator != _bones.end())
    {
        _bones.erase(iterator);
        _animation->_timelineStateDirty = true;
    }
}

void Armature::_addSlotToSlotList(Slot* value)
{
    if (std::find(_slots.begin(), _slots.end(), value) == _slots.end())
    {
        _slotsDirty = true;
        _slots.push_back(value);
        _animation->_timelineStateDirty = true;
    }
}

void Armature::_removeSlotFromSlotList(Slot* value)
{
    const auto iterator = std::find(_slots.begin(), _slots.end(), value);
    if (iterator != _slots.end())
    {
        _slots.erase(iterator);
        _animation->_timelineStateDirty = true;
    }
}

void Armature::_bufferAction(ActionData* value)
{
    _actions.push_back(value);
}

void Armature::_bufferEvent(EventObject* value, const std::string& type)
{
    value->type = type;
    value->armature = this;
    _events.push_back(value);
}

void Armature::dispose()
{
    _delayDispose = true;

    if (!_lockDispose && _animation)
    {
        this->returnToPool();
    }
}

void Armature::advanceTime(float passedTime)
{
    if (!_animation) 
    {
        DRAGONBONES_ASSERT(false, "The armature has been disposed.");
    }

    const auto scaledPassedTime = passedTime * _animation->timeScale;

    //
    _animation->_advanceTime(scaledPassedTime);

    //
    if (_bonesDirty)
    {
        _bonesDirty = false;
        _sortBones();
    }

    if (_slotsDirty)
    {
        _slotsDirty = false;
        _sortSlots();
    }

    //
    for (const auto bone : _bones)
    {
        bone->_update(_cacheFrameIndex);
    }

    for (const auto slot : _slots)
    {
        slot->_update(_cacheFrameIndex);

        const auto childArmature = slot->getChildArmature();
        if (childArmature)
        {
            if (slot->inheritAnimation)
            {
                childArmature->advanceTime(scaledPassedTime);
            }
            else
            {
                childArmature->advanceTime(passedTime);
            }
        }
    }

    //

    if (!_lockDispose)
    {
        _lockDispose = true;

        if (!_events.empty())
        {
            for (const auto event : _events)
            {
                if (EventObject::_soundEventManager && event->type == EventObject::SOUND_EVENT)
                {
                    EventObject::_soundEventManager->_dispatchEvent(event);
                }
                else
                {
                    _display->_dispatchEvent(event);
                }

                event->returnToPool();
            }

            _events.clear();
        }

        if (!_actions.empty())
        {
            for (const auto action : _actions)
            {
                if (action->slot) 
                {
                    const auto slot = getSlot(action->slot->name);
                    if (slot) 
                    {
                        const auto childArmature = slot->getChildArmature();
                        if (childArmature) 
                        {
                            childArmature->_doAction(*action);
                        }
                    }
                }
                else if (action->bone) 
                {
                    for (const auto slot : _slots) 
                    {
                        const auto childArmature = slot->getChildArmature();
                        if (childArmature) 
                        {
                            childArmature->_doAction(*action);
                        }
                    }
                }
                else 
                {
                    _doAction(*action);
                }
            }

            _actions.clear();
        }

        _lockDispose = false;
    }

    if (_delayDispose)
    {
        this->returnToPool();
    }
}

void Armature::invalidUpdate(const std::string& boneName, bool updateSlotDisplay)
{
    if (!boneName.empty())
    {
        const auto bone = getBone(boneName);
        if (bone)
        {
            bone->invalidUpdate();

            if (updateSlotDisplay)
            {
                for (const auto slot : _slots)
                {
                    if (slot->getParent() == bone)
                    {
                        slot->invalidUpdate();
                    }
                }
            }
        }
    }
    else
    {
        for (const auto bone : _bones)
        {
            bone->invalidUpdate();
        }

        if (updateSlotDisplay)
        {
            for (const auto slot : _slots)
            {
                slot->invalidUpdate();
            }
        }
    }
}

Slot* Armature::getSlot(const std::string& name) const
{
    for (const auto slot : _slots)
    {
        if (slot->name == name)
        {
            return slot;
        }
    }

    return nullptr;
}

Slot* Armature::getSlotByDisplay(void* display) const
{
    if (display)
    {
        for (const auto slot : _slots)
        {
            if (slot->getDisplay() == display)
            {
                return slot;
            }
        }
    }

    return nullptr;
}

void Armature::addSlot(Slot* value, const std::string& boneName)
{
    const auto bone = getBone(boneName);
    if (bone)
    {
        value->_setArmature(this);
        value->_setParent(bone);
    }
    else
    {
        DRAGONBONES_ASSERT(false, "Argument error.");
    }
}

void Armature::removeSlot(Slot* value)
{
    if (value && value->getArmature() == this)
    {
        value->_setParent(nullptr);
        value->_setArmature(nullptr);
    }
    else
    {
        DRAGONBONES_ASSERT(false, "Argument error.");
    }
}

Bone* Armature::getBone(const std::string& name) const
{
    for (const auto bone : _bones)
    {
        if (bone->name == name)
        {
            return bone;
        }
    }

    return nullptr;
}

Bone* Armature::getBoneByDisplay(void* display) const
{
    const auto slot = getSlotByDisplay(display);

    return slot ? slot->getParent() : nullptr;
}

void Armature::addBone(Bone* value, const std::string& parentName)
{
    if (value)
    {
        value->_setArmature(this);
        value->_setParent(parentName.empty() ? nullptr : getBone(parentName));
    }
    else
    {
        DRAGONBONES_ASSERT(false, "Argument error.");
    }
}

void Armature::removeBone(Bone* value)
{
    if (value && value->getArmature() == this)
    {
        value->_setParent(nullptr);
        value->_setArmature(nullptr);
    }
    else
    {
        DRAGONBONES_ASSERT(false, "Argument error.");
    }
}

void Armature::replaceTexture(void* texture)
{
    _replacedTexture = texture;
    for (auto const slot : _slots) 
    {
        slot->invalidUpdate();
    }
}

void Armature::setCacheFrameRate(unsigned value)
{
    if (_armatureData->cacheFrameRate != value)
    {
        _armatureData->cacheFrames(value);

        for (const auto slot : _slots) 
        {
            const auto childArmature = slot->getChildArmature();
            if (childArmature && childArmature->getCacheFrameRate() == 0) 
            {
                childArmature->setCacheFrameRate(value);
            }
        }
    }
}

DRAGONBONES_NAMESPACE_END
