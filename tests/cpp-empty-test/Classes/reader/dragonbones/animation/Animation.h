#ifndef DRAGONBONES_ANIMATION_H
#define DRAGONBONES_ANIMATION_H

#include "../core/BaseObject.h"
#include "../model/AnimationData.h"

DRAGONBONES_NAMESPACE_BEGIN

enum class AnimationFadeOutMode { 
    None = 0, 
    SameLayer = 1, 
    SameGroup = 2, 
    SameLayerAndGroup = 3, 
    All  = 4
};

class Armature;
class AnimationState;

class Animation final : public BaseObject
{
    BIND_CLASS_TYPE(Animation);

private:
    static bool _sortAnimationState(AnimationState* a, AnimationState* b);

public:
    float timeScale;

public:
    /** @private */
    bool _animationStateDirty;
    /** @private */
    bool _timelineStateDirty;
    /** @private */
    Armature* _armature;
    
private:
    bool _isPlaying;
    float _time;
    AnimationState* _lastAnimationState;
    std::map<std::string, AnimationData*> _animations;
    std::vector<std::string> _animationNames;
    std::vector<AnimationState*> _animationStates;

public:
    Animation();
    ~Animation();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(Animation);

protected:
    void _onClear() override;
    void _fadeOut(float fadeOutTime, int layer, const std::string& group, AnimationFadeOutMode fadeOutMode, bool pauseFadeOut);

public:
    /** @private */
    void _updateFFDTimelineStates();
    /** @private */
    void _advanceTime(float passedTime);

public:
    void reset();
    void stop(const std::string& animationName);
    AnimationState* play(const std::string& animationName = "", int playTimes = -1);
    AnimationState* fadeIn(
        const std::string& animationName, float fadeInTime = -1.f, int playTimes = -1,
        int layer = 0, const std::string& group = "", AnimationFadeOutMode fadeOutMode = AnimationFadeOutMode::SameLayerAndGroup,
        bool additiveBlending = false, bool displayControl = true,
        bool pauseFadeOut = true, bool pauseFadeIn = true
    );
    AnimationState* gotoAndPlayByTime(const std::string& animationName, float time = 0.f, int playTimes = -1);
    AnimationState* gotoAndPlayByFrame(const std::string& animationName, unsigned frame = 0, int playTimes = -1);
    AnimationState* gotoAndPlayByProgress(const std::string& animationName, float progress = 0.f, int playTimes = -1);
    AnimationState* gotoAndStopByTime(const std::string& animationName, float time = 0.f);
    AnimationState* gotoAndStopByFrame(const std::string& animationName, unsigned frame = 0);
    AnimationState* gotoAndStopByProgress(const std::string& animationName, float progress = 0.f);
    AnimationState* getState(const std::string& animationName) const;
    bool hasAnimation(const std::string& animationName) const;
    bool isPlaying() const;
    bool isCompleted() const;
    const std::string& getLastAnimationName() const;
    void setAnimations(const std::map<std::string, AnimationData*>& value);

    inline AnimationState* getLastAnimationState() const
    {
        return _lastAnimationState;
    }

    inline const std::map<std::string, AnimationData*>& getAnimations() const
    {
        return _animations;
    }

    inline const std::vector<std::string>& getAnimationNames() const
    {
        return _animationNames;
    }
};

DRAGONBONES_NAMESPACE_END
#endif  // DRAGONBONES_ANIMATION_H