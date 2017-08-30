#ifndef DRAGONBONES_BASE_TIMELINE_STATE_H
#define DRAGONBONES_BASE_TIMELINE_STATE_H

#include "../core/BaseObject.h"
#include "../model/FrameData.h"
#include "../model/TimelineData.h"
#include "../model/AnimationData.h"
#include "../armature/Armature.h"
#include "../armature/Slot.h"
#include "AnimationState.h"

DRAGONBONES_NAMESPACE_BEGIN

/** @private */
template<class T, class M>
class TimelineState : public BaseObject
{
public:
    bool _isCompleted;
    unsigned _currentPlayTimes;
    float _currentTime;
    M* _timeline;

protected:
    bool _isReverse;
    bool _hasAsynchronyTimeline;
    unsigned _frameRate;
    unsigned _keyFrameCount;
    unsigned _frameCount;
    float _position;
    float _duration;
    float _animationiDutation;
    float _timeScale;
    float _timeOffset;
    T* _currentFrame;
    Armature* _armature;
    AnimationState* _animationState;

public:
    TimelineState() {}
    virtual ~TimelineState() {}

protected:
    virtual void _onClear() override
    {
        _isCompleted = false;
        _currentPlayTimes = 0;
        _currentTime = -1.f;
        _timeline = nullptr;

        _isReverse = false;
        _hasAsynchronyTimeline = false;
        _keyFrameCount = 0;
        _frameCount = 0;
        _position = 0.f;
        _duration = 0.f;
        _animationiDutation = 0.f;
        _timeScale = 1.f;
        _timeOffset = 0.f;
        _currentFrame = nullptr;
        _armature = nullptr;
        _animationState = nullptr;
    }

    virtual void _onUpdateFrame(bool isUpdate) {}
    virtual void _onArriveAtFrame(bool isUpdate) {}

    bool _setCurrentTime(float value)
    {
        unsigned currentPlayTimes = 0;

        if (_keyFrameCount == 1 && (void*)this != (void*)_animationState->_timeline)
        {
            _isCompleted = true;
            currentPlayTimes = 1;
        }
        else if (_hasAsynchronyTimeline)
        {
            const auto playTimes = _animationState->playTimes;
            const auto totalTimes = playTimes * _duration;

            value *= _timeScale;
            if (_timeOffset != 0.f)
            {
                value += _timeOffset * _animationiDutation;
            }

            if (playTimes > 0 && (value >= totalTimes || value <= -totalTimes))
            {
                _isCompleted = true;
                currentPlayTimes = playTimes;

                if (value < 0.f)
                {
                    value = 0.f;
                }
                else
                {
                    value = _duration;
                }
            }
            else
            {
                _isCompleted = false;

                if (value < 0.f)
                {
                    currentPlayTimes = (unsigned)(-value / _duration);
                    value = _duration - std::fmod(-value, _duration);
                }
                else
                {
                    currentPlayTimes = (unsigned)(value / _duration);
                    value = std::fmod(value, _duration);
                }

                if (playTimes > 0 && currentPlayTimes > playTimes)
                {
                    currentPlayTimes = playTimes;
                }
            }

            value += _position;
        }
        else
        {
            //_isCompleted = _animationState->_timeline->_isCompleted; // TODO
            //_currentPlayTimes = _animationState->_timeline->_currentPlayTimes;
        }

        if (_currentTime == value)
        {
            return false;
        }

        _isReverse = _currentTime > value && _currentPlayTimes == currentPlayTimes;
        _currentTime = value;
        _currentPlayTimes = currentPlayTimes;

        return true;
    }

public:
    virtual void fadeIn(Armature* armature, AnimationState* animationState, M* timelineData, float time)
    {
        _armature = armature;
        _animationState = animationState;
        _timeline = timelineData;

        const auto isMainTimeline = (void*)this == (void*)_animationState->_timeline;

        _hasAsynchronyTimeline = isMainTimeline || _animationState->getAnimationData().hasAsynchronyTimeline;
        _frameRate = _armature->getArmatureData().frameRate;
        _keyFrameCount = _timeline->frames.size();
        _frameCount = _animationState->getAnimationData().frameCount;
        _position = _animationState->_position;
        _duration = _animationState->_duration;
        _animationiDutation = _animationState->getAnimationData().duration;
        _timeScale = isMainTimeline ? 1.f : (1.f / _timeline->scale);
        _timeOffset = isMainTimeline ? 0.f : _timeline->offset;
    }

    virtual void fadeOut() {}

    virtual void update(float time)
    {
        if (!_isCompleted && _setCurrentTime(time))
        {
            const unsigned currentFrameIndex = _keyFrameCount > 1 ? unsigned(_currentTime * _frameRate) : 0;
            const auto currentFrame = _timeline->frames[currentFrameIndex];

            if (_currentFrame != currentFrame)
            {
                _currentFrame = currentFrame;
                _onArriveAtFrame(true);
            }

            _onUpdateFrame(true);
        }
    }
};

/** @private */
template<class T, class M>
class TweenTimelineState : public TimelineState<T, M>
{
public: // private
    /** @private */
    static float _getEasingValue(float progress, float easing)
    {
        if (progress <= 0.f) {
            return 0.f;
        }
        else if (progress >= 1.f)
        {
            return 1.f;
        }

        auto value = 1.f;
        if (easing > 2.f)
        {
            return progress;
        }
        else if (easing > 1.f) // Ease in out
        {
            value = 0.5f * (1.f - std::cos(progress * PI));
            easing -= 1.f;
        }
        else if (easing > 0.f) // Ease out
        {
            value = 1.f - std::pow(1.f - progress, 2);
        }
        else if (easing >= -1.f) // Ease in
        {
            easing *= -1.f;
            value = std::pow(progress, 2);
        }
        else if (easing >= -2.f) // Ease out in
        {
            easing *= -1.f;
            value = std::acos(1.f - progress * 2.f) / PI;
            easing -= 1.f;
        }
        else
        {
            return progress;
        }

        return (value - progress) * easing + progress;
    }

    /** @private */
    static float _getCurveEasingValue(float progress, const std::vector<float>& sampling)
    {
        if (progress <= 0.f) {
            return 0.f;
        }
        else if (progress >= 1.f) 
        {
            return 1.f;
        }

        auto x = 0.f;
        auto y = 0.f;

        for (std::size_t i = 0, l = sampling.size(); i < l; i += 2)
        {
            x = sampling[i];
            y = sampling[i + 1];
            if (x >= progress)
            {
                if (i == 0)
                {
                    return y * progress / x;
                }
                else
                {
                    const auto xP = sampling[i - 2];
                    const auto yP = sampling[i - 1]; // i - 2 + 1
                    return yP + (y - yP) * (progress - xP) / (x - xP);
                }
            }
        }

        return y + (1.f - y) * (progress - x) / (1.f - x);
    }

protected:
    enum class TweenType
    {
        None = 0,
        Once = 1,
        Always = 2
    };

    float _tweenProgress;
    float _tweenEasing;
    std::vector<float>* _curve;

public:
    TweenTimelineState() {}
    virtual ~TweenTimelineState() {}

protected:
    virtual void _onClear() override
    {
        TimelineState<T, M>::_onClear();

        _tweenProgress = 0.f;
        _tweenEasing = NO_TWEEN;
        _curve = nullptr;
    }

    virtual void _onArriveAtFrame(bool isUpdate) override
    {
        _tweenEasing = this->_currentFrame->tweenEasing;
        _curve = this->_currentFrame->curve.empty() ? nullptr : &this->_currentFrame->curve;

        if (
            this->_keyFrameCount == 1 ||
            (
                this->_currentFrame->next == this->_timeline->frames[0] &&
                (_tweenEasing != NO_TWEEN || _curve) &&
                this->_animationState->playTimes > 0 &&
                this->_animationState->getCurrentPlayTimes() == this->_animationState->playTimes - 1
                )
            )
        {
            _tweenEasing = NO_TWEEN;
            _curve = nullptr;
        }
    }

    virtual void _onUpdateFrame(bool isUpdate) override
    {
        if (_tweenEasing != NO_TWEEN)
        {
            _tweenProgress = (float)(this->_currentTime - this->_currentFrame->position + this->_position) / this->_currentFrame->duration;
            if (_tweenEasing != 0.f)
            {
                _tweenProgress = _getEasingValue(_tweenProgress, _tweenEasing);
            }
        }
        else if (_curve)
        {
            _tweenProgress = (float)(this->_currentTime - this->_currentFrame->position + this->_position) / this->_currentFrame->duration;
            _tweenProgress = _getCurveEasingValue(_tweenProgress, *_curve);
        }
        else
        {
            _tweenProgress = 0.f;
        }
    }

    TweenType _updateExtensionKeyFrame(const ExtensionFrameData& current, const ExtensionFrameData& next, ExtensionFrameData& result)
    {
        auto tweenType = TweenType::None;
        if (current.type == next.type)
        {
            for (std::size_t i = 0, l = current.tweens.size(); i < l; ++i)
            {
                const auto tweenDuration = next.tweens[i] - current.tweens[i];
                result.tweens[i] = tweenDuration;

                if (tweenDuration > 0.f)
                {
                    tweenType = TweenType::Always;
                }
            }
        }

        if (tweenType == TweenType::None)
        {
            if (result.type != current.type)
            {
                tweenType = TweenType::Once;
                result.type = current.type;
            }

            if (result.tweens.size() != current.tweens.size())
            {
                tweenType = TweenType::Once;
                result.tweens.resize(current.tweens.size(), 0.f);
            }

            if (result.keys.size() != current.keys.size())
            {
                tweenType = TweenType::Once;
                result.keys.resize(current.keys.size(), 0.f);
            }

            for (std::size_t i = 0, l = current.keys.size(); i < l; ++i)
            {
                const auto key = current.keys[i];
                if (result.keys[i] != key)
                {
                    tweenType = TweenType::Once;
                    result.keys[i] = key;
                }
            }
        }

        return tweenType;
    }
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_BASE_TIMELINE_STATE_H