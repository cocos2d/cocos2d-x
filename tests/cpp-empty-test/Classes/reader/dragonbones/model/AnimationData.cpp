#include "AnimationData.h"
#include "ArmatureData.h"

DRAGONBONES_NAMESPACE_BEGIN

AnimationData::AnimationData() 
{
    _onClear();
}
AnimationData::~AnimationData() 
{
    _onClear();
}

void AnimationData::_onClear()
{
    TimelineData::_onClear();

    for (const auto& pair : boneTimelines)
    {
        pair.second->returnToPool();
    }

    for (const auto& pair : slotTimelines)
    {
        pair.second->returnToPool();
    }

    for (const auto& skinPair : ffdTimelines)
    {
        for (const auto& slotPair : skinPair.second)
        {
            for (const auto& pair : slotPair.second)
            {
                pair.second->returnToPool();
            }
        }
    }

    hasAsynchronyTimeline = false;
    frameCount = 0;
    playTimes = 0;
    position = 0.f;
    duration = 0.f;
    fadeInTime = 0.f;
    cacheTimeToFrameScale = 0.f;
    name.clear();
    animation = nullptr;
    boneTimelines.clear();
    slotTimelines.clear();
    ffdTimelines.clear();
    cachedFrames.clear();
}

void AnimationData::cacheFrames(float value)
{
    if (animation)
    {
        return;
    }

    const auto cacheFrameCount = (unsigned)std::max(std::floor((frameCount + 1) * scale * value), 1.f);

    cacheTimeToFrameScale = cacheFrameCount / (duration + 0.0000001f);
    cachedFrames.resize(cacheFrameCount, false);

    for (const auto& pair : boneTimelines)
    {
        pair.second->cacheFrames(cacheFrameCount);
    }

    for (const auto& pair : slotTimelines)
    {
        pair.second->cacheFrames(cacheFrameCount);
    }
}

void AnimationData::addBoneTimeline(BoneTimelineData* value)
{
    if (value && value->bone && boneTimelines.find(value->bone->name) == boneTimelines.end())
    {
        boneTimelines[value->bone->name] = value;
    }
    else
    {
        DRAGONBONES_ASSERT(false, "Argument error.");
    }
}

void AnimationData::addSlotTimeline(SlotTimelineData* value)
{
    if (value && value->slot && slotTimelines.find(value->slot->name) == slotTimelines.end())
    {
        slotTimelines[value->slot->name] = value;
    }
    else
    {
        DRAGONBONES_ASSERT(false, "Argument error.");
    }
}

void AnimationData::addFFDTimeline(FFDTimelineData* value)
{
    if (value && value->skin && value->slot)
    {
        const auto& skinName = value->skin->name;
        const auto& slotName = value->slot->slot->name;
        const auto& displayIndex = to_string(value->displayIndex); // std::to_string

        auto& skin = ffdTimelines[skinName];
        auto& slot = skin[slotName];
        if (slot.find(displayIndex) == slot.end())
        {
            slot[displayIndex] = value;
        }
        else
        {
            DRAGONBONES_ASSERT(false, "Argument error.");
        }
    }
    else
    {
        DRAGONBONES_ASSERT(false, "Argument error.");
    }
}

DRAGONBONES_NAMESPACE_END