#ifndef DRAGONBONES_ANIMATION_DATA_H
#define DRAGONBONES_ANIMATION_DATA_H

#include "TimelineData.h"

DRAGONBONES_NAMESPACE_BEGIN

class AnimationData final : public TimelineData<AnimationFrameData>
{
    BIND_CLASS_TYPE(AnimationData);

public:
    /** @private */
    bool hasAsynchronyTimeline;
    unsigned frameCount;
    unsigned playTimes;
    float position;
    float duration;
    float fadeInTime;
    /** @private */
    float cacheTimeToFrameScale;
    std::string name;
    /** @private */
    AnimationData* animation;
    /** @private */
    std::map<std::string, BoneTimelineData*> boneTimelines;
    /** @private */
    std::map<std::string, SlotTimelineData*> slotTimelines;
    /** @private */
    std::map<std::string, std::map<std::string, std::map<std::string, FFDTimelineData*>>> ffdTimelines; // skin slot displayIndex
    /** @private */
    std::vector<bool> cachedFrames;

    /** @private */
    AnimationData();
    /** @private */
    ~AnimationData();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(AnimationData);

protected:
    void _onClear() override;

public:
    /** @private */
    void cacheFrames(float value);
    /** @private */
    void addBoneTimeline(BoneTimelineData* value);
    /** @private */
    void addSlotTimeline(SlotTimelineData* value);
    /** @private */
    void addFFDTimeline(FFDTimelineData* value);

    /** @private */
    inline BoneTimelineData* getBoneTimeline(const std::string& theName) const
    {
        return mapFind(boneTimelines, theName);
    }

    /** @private */
    inline SlotTimelineData* getSlotTimeline(const std::string& theName) const
    {
        return mapFind(slotTimelines, theName);
    }

    /** @private */
    inline FFDTimelineData* getFFDTimeline(const std::string& skinName, const std::string& slotName, unsigned displayIndex) const
    {
        const auto iteratorSkin = ffdTimelines.find(skinName);
        if (iteratorSkin != ffdTimelines.end())
        {
            const auto& skin = iteratorSkin->second;
            const auto iteratorSlot = skin.find(slotName);
            if (iteratorSlot != skin.end())
            {
                const auto& slot = iteratorSlot->second;
                return mapFind(slot, to_string(displayIndex)); // std::to_string
            }
        }

        return nullptr;
    }
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_ANIMATION_DATA_H
