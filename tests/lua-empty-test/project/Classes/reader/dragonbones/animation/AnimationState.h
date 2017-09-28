#ifndef DRAGONBONES_ANIMATION_STATE_H
#define DRAGONBONES_ANIMATION_STATE_H

#include "../core/BaseObject.h"
#include "../model/AnimationData.h"

DRAGONBONES_NAMESPACE_BEGIN

class Armature;
class Bone;
class Slot;
class AnimationTimelineState;
class BoneTimelineState;
class SlotTimelineState;
class FFDTimelineState;

class AnimationState final : public BaseObject
{
    BIND_CLASS_TYPE(AnimationState);

public:
    static bool stateActionEnabled;

public:
    bool displayControl;
    bool additiveBlending;
    bool actionEnabled;
    unsigned playTimes;
    float timeScale;
    float weight;
    float autoFadeOutTime;
    float fadeTotalTime;

public:
    /** @private */
    bool _isFadeOutComplete;
    /** @private */
    int _layer;
    /** @private */
    float _position;
    /** @private */
    float _duration;
    /** @private */
    float _weightResult;
    /** @private */
    float _fadeProgress;
    /** @private */
    std::string _group;
    /** @private */
    AnimationTimelineState* _timeline;

private:
    bool _isPlaying;
    bool _isPausePlayhead;
    bool _isFadeOut;
    float _fadeTime;
    float _time;
    std::string _name;
    Armature* _armature;
    AnimationData* _animationData;
    std::vector<std::string> _boneMask;
    std::vector<BoneTimelineState*> _boneTimelines;
    std::vector<SlotTimelineState*> _slotTimelines;
    std::vector<FFDTimelineState*> _ffdTimelines;

public:
    AnimationState();
    ~AnimationState();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(AnimationState);

    void _advanceFadeTime(float passedTime);

protected:
    void _onClear() override;

public:
    /** @private */
    bool _isDisabled(const Slot& slot) const;
    /** @private */
    void _fadeIn(Armature* armature, AnimationData* clip, const std::string& animationName,
        unsigned playTimes, float position, float duration, float time, float timeScale, float fadeInTime,
        bool pausePlayhead
    );
    /** @private */
    void _updateTimelineStates();
    /** @private */
    void _updateFFDTimelineStates();
    /** @private */
    void _advanceTime(float passedTime, float weightLeft, int index);

public:
    void play();
    void stop();
    void fadeOut(float fadeOutTime, bool pausePlayhead = true);
    void addBoneMask(const std::string& name, bool recursive = true);
    void removeBoneMask(const std::string& name, bool recursive = true);
    void removeAllBoneMask();

    bool isCompleted() const;
    float getCurrentTime() const;
    void setCurrentTime(float value);
    unsigned getCurrentPlayTimes() const;

    bool containsBoneMask(const std::string& name)
    {
        return _boneMask.empty() || std::find(_boneMask.cbegin(), _boneMask.cend(), name) != _boneMask.cend();
    }

    inline int getLayer() const 
    {
        return _layer;
    }

    inline const std::string& getName() const
    {
        return _name;
    }

    inline const std::string& getGroup() const
    {
        return _group;
    }

    inline const AnimationData& getAnimationData() const
    {
        return *_animationData;
    }

    inline bool isPlaying() const
    {
        return (_isPlaying && !isCompleted());
    }

    inline float getTotalTime() const
    {
        return _duration;
    }
};

DRAGONBONES_NAMESPACE_END
#endif  // DRAGONBONES_ANIMATION_STATE_H