#include "AnimationState.h"
#include "TimelineState.h"
#include "../armature/Armature.h"
#include "../armature/Bone.h"
#include "../armature/Slot.h"
#include "../animation/Animation.h"

DRAGONBONES_NAMESPACE_BEGIN

bool AnimationState::stateActionEnabled = true;

AnimationState::AnimationState() :
    _timeline(nullptr)
{
    _onClear();
}
AnimationState::~AnimationState() 
{
    _onClear();
}

void AnimationState::_onClear()
{
    for (const auto boneTimelineState : _boneTimelines)
    {
        boneTimelineState->returnToPool();
    }

    for (const auto slotTimelineState : _slotTimelines)
    {
        slotTimelineState->returnToPool();
    }

    for (const auto ffdTimelineState : _ffdTimelines)
    {
        ffdTimelineState->returnToPool();
    }

    displayControl = true;
    additiveBlending = false;
    actionEnabled = false;
    playTimes = 1;
    timeScale = 1.f;
    weight = 1.f;
    autoFadeOutTime = -1.f;
    fadeTotalTime = 0.f;

    _isFadeOutComplete = false;
    _layer = 0;
    _position = 0.f;
    _duration = 0.f;
    _weightResult = 0.f;
    _fadeProgress = 0.f;
    _group.clear();

    if (_timeline)
    {
        _timeline->returnToPool();
        _timeline = nullptr;
    }
    
    _isPlaying = true;
    _isPausePlayhead = false;
    _isFadeOut = false;
    _fadeTime = 0.f;
    _time = 0.f;
    _name.clear();
    _armature = nullptr;
    _animationData = nullptr;
    _boneMask.clear();
    _boneTimelines.clear();
    _slotTimelines.clear();
    _ffdTimelines.clear();
}

void AnimationState::_advanceFadeTime(float passedTime)
{
    if (passedTime < 0.f)
    {
        passedTime = -passedTime;
    }

    _fadeTime += passedTime;

    auto fadeProgress = 0.f;
    if (_fadeTime >= fadeTotalTime)
    {
        fadeProgress = _isFadeOut? 0.f : 1.f;
    }
    else if (_fadeTime > 0.f)
    {
        fadeProgress = _isFadeOut ? (1.f - _fadeTime / fadeTotalTime) : (_fadeTime / fadeTotalTime);
    }
    else
    {
        fadeProgress = _isFadeOut ? 1.f : 0.f;
    }

    if (_fadeProgress != fadeProgress)
    {
        _fadeProgress = fadeProgress;

        const auto eventDispatcher = _armature->_display;

        if (_fadeTime <= passedTime)
        {
            if (_isFadeOut)
            {
                if (eventDispatcher->hasEvent(EventObject::FADE_OUT))
                {
                    auto event = BaseObject::borrowObject<EventObject>();
                    event->animationState = this;
                    _armature->_bufferEvent(event, EventObject::FADE_OUT);
                }
            }
            else
            {
                if (eventDispatcher->hasEvent(EventObject::FADE_IN))
                {
                    auto event = BaseObject::borrowObject<EventObject>();
                    event->animationState = this;
                    _armature->_bufferEvent(event, EventObject::FADE_IN);
                }
            }
        }

        if (_fadeTime >= fadeTotalTime)
        {
            if (_isFadeOut)
            {
                _isFadeOutComplete = true;

                if (eventDispatcher->hasEvent(EventObject::FADE_OUT_COMPLETE))
                {
                    auto event = BaseObject::borrowObject<EventObject>();
                    event->animationState = this;
                    _armature->_bufferEvent(event, EventObject::FADE_OUT_COMPLETE);
                }
            }
            else
            {
                _isPausePlayhead = false;

                if (eventDispatcher->hasEvent(EventObject::FADE_IN_COMPLETE))
                {
                    auto event = BaseObject::borrowObject<EventObject>();
                    event->animationState = this;
                    _armature->_bufferEvent(event, EventObject::FADE_IN_COMPLETE);
                }
            }
        }
    }
}

bool AnimationState::_isDisabled(const Slot& slot) const
{
    if (
        displayControl &&
        (
            slot.displayController.empty() ||
            slot.displayController == _name ||
            slot.displayController == _group
        )
    )
    {
        return false;
    }

    return true;
}

void AnimationState::_fadeIn(
    Armature* armature, AnimationData* clip, const std::string& animationName, 
    unsigned playTimes, float position, float duration, float time, float timeScale, float fadeInTime,
    bool pausePlayhead
)
{
    _armature = armature;
    _animationData = clip;
    _name = animationName;

    actionEnabled = AnimationState::stateActionEnabled;
    this->playTimes = playTimes;
    this->timeScale = timeScale;
    fadeTotalTime = fadeInTime;

    _position = position;
    _duration = duration;
    _time = time;
    _isPausePlayhead = pausePlayhead;
    if (fadeTotalTime <= 0.f)
    {
        _fadeProgress = 0.999999f;
    }

    _timeline = BaseObject::borrowObject<AnimationTimelineState>();
    _timeline->fadeIn(_armature, this, _animationData, _time);

    _updateTimelineStates();
}

void AnimationState::_updateTimelineStates()
{
    auto time = _time;
    if (!_animationData->hasAsynchronyTimeline)
    {
        time = _timeline->_currentTime;
    }

    std::map<std::string, BoneTimelineState*> boneTimelineStates;
    std::map<std::string, SlotTimelineState*> slotTimelineStates;

    //
    for (const auto boneTimelineState : _boneTimelines)
    {
        boneTimelineStates[boneTimelineState->bone->name] = boneTimelineState;
    }

    const auto& bones = _armature->getBones();
    for (const auto bone : bones)
    {
        const auto& boneTimelineName = bone->name;
        const auto boneTimelineData = _animationData->getBoneTimeline(boneTimelineName);

        if (boneTimelineData && containsBoneMask(boneTimelineName))
        {
            const auto iterator = boneTimelineStates.find(boneTimelineName);
            if (iterator != boneTimelineStates.end())
            {
                boneTimelineStates.erase(iterator);
            }
            else
            {
                const auto boneTimelineState = BaseObject::borrowObject<BoneTimelineState>();
                boneTimelineState->bone = bone;
                boneTimelineState->fadeIn(_armature, this, boneTimelineData, time);
                _boneTimelines.push_back(boneTimelineState);
            }
        }
    }

    for (const auto& pair : boneTimelineStates)
    {
        const auto boneTimelineState = pair.second;
        boneTimelineState->bone->invalidUpdate();
        _boneTimelines.erase(std::find(_boneTimelines.begin(), _boneTimelines.end(), boneTimelineState));
        boneTimelineState->returnToPool();
    }

    //
    for (const auto slotTimelineState : _slotTimelines)
    {
        slotTimelineStates[slotTimelineState->slot->name] = slotTimelineState;
    }

    for (const auto slot : _armature->getSlots())
    {
        const auto& timelineName = slot->name;
        const auto& parentTimelineName = slot->getParent()->name;
        const auto slotTimelineData = _animationData->getSlotTimeline(timelineName);

        if (slotTimelineData && containsBoneMask(parentTimelineName) && !_isFadeOut)
        {
            const auto iterator = slotTimelineStates.find(timelineName);
            if (iterator != slotTimelineStates.end())
            {
                slotTimelineStates.erase(iterator);
            }
            else
            {
                const auto slotTimelineState = BaseObject::borrowObject<SlotTimelineState>();
                slotTimelineState->slot = slot;
                slotTimelineState->fadeIn(_armature, this, slotTimelineData, time);
                _slotTimelines.push_back(slotTimelineState);
            }
        }
    }

    for (const auto& pair : slotTimelineStates)
    {
        const auto timelineState = pair.second;
        _slotTimelines.erase(std::find(_slotTimelines.begin(), _slotTimelines.end(), timelineState));
        timelineState->returnToPool();
    }

    _updateFFDTimelineStates();
}

void AnimationState::_updateFFDTimelineStates()
{
    auto time = _time;
    if (!_animationData->hasAsynchronyTimeline)
    {
        time = _timeline->_currentTime;
    }

    std::map<std::string, FFDTimelineState*> ffdTimelineStates;

    for (const auto ffdTimelineState : _ffdTimelines)
    {
        ffdTimelineStates[ffdTimelineState->slot->name] = ffdTimelineState;
    }

    for (const auto slot : _armature->getSlots())
    {
        const auto& timelineName = slot->name;
        const auto& parentTimelineName = slot->getParent()->name;

        if (slot->_meshData)
        {
            const auto displayIndex = slot->getDisplayIndex();
            const auto rawMeshData = displayIndex < slot->_displayDataSet->displays.size() ? slot->_displayDataSet->displays[displayIndex]->mesh : nullptr;

            if (slot->_meshData == rawMeshData) 
            {
                const auto ffdTimelineData = _animationData->getFFDTimeline(_armature->_skinData->name, timelineName, displayIndex);
                if (ffdTimelineData && containsBoneMask(parentTimelineName)) //  && !_isFadeOut
                {
                    const auto iterator = ffdTimelineStates.find(timelineName);
                    if (iterator != ffdTimelineStates.end())
                    {
                        ffdTimelineStates.erase(iterator);
                    }
                    else
                    {
                        const auto timelineState = BaseObject::borrowObject<FFDTimelineState>();
                        timelineState->slot = slot;
                        timelineState->fadeIn(_armature, this, ffdTimelineData, time);
                        _ffdTimelines.push_back(timelineState);
                    }
                }
                else
                {
                    const auto totalCount = slot->_ffdVertices.size();
                    slot->_ffdVertices.clear();
                    slot->_ffdVertices.resize(totalCount, 0.f);
                    slot->_ffdDirty = true;
                }
            }
        }
    }

    for (const auto& pair : ffdTimelineStates)
    {
        const auto ffdTimelineState = pair.second;
        //ffdTimelineState->slot->_ffdDirty = true;
        _ffdTimelines.erase(std::find(_ffdTimelines.begin(), _ffdTimelines.end(), ffdTimelineState));
        ffdTimelineState->returnToPool();
    }
}

void AnimationState::_advanceTime(float passedTime, float weightLeft, int index)
{
    _advanceFadeTime(passedTime);

    passedTime *= timeScale;

    if (passedTime != 0.f && _isPlaying && !_isPausePlayhead)
    {
        _time += passedTime;
    }

    _weightResult = weight * _fadeProgress * weightLeft;

    if (_weightResult != 0.f)
    {
        const auto isCacheEnabled = _fadeProgress >= 1.f && index == 0 && _armature->getCacheFrameRate() > 0;
        const auto cacheTimeToFrameScale = _animationData->cacheTimeToFrameScale;
        auto isUpdatesTimeline = true;
        auto isUpdatesBoneTimeline = true;
        auto time = cacheTimeToFrameScale * 2;
        time = isCacheEnabled ? ((unsigned)(_time * time) / time) : _time;
        _timeline->update(time);
        if (!_animationData->hasAsynchronyTimeline)
        {
            time = _timeline->_currentTime;
        }

        if (isCacheEnabled)
        {
            const auto cacheFrameIndex = (unsigned)(_timeline->_currentTime * cacheTimeToFrameScale);
            if (_armature->_cacheFrameIndex == cacheFrameIndex) 
            {
                isUpdatesTimeline = false;
                isUpdatesBoneTimeline = false;
            }
            else 
            {
                _armature->_cacheFrameIndex = cacheFrameIndex;

                if (_armature->_animation->_animationStateDirty)
                {
                    _armature->_animation->_animationStateDirty = false;

                    for (const auto boneTimelineState : _boneTimelines)
                    {
                        boneTimelineState->bone->_cacheFrames = &(boneTimelineState->_timeline->cachedFrames);
                    }

                    for (const auto slotTimelineState : _slotTimelines)
                    {
                        slotTimelineState->slot->_cacheFrames = &(slotTimelineState->_timeline->cachedFrames);
                    }
                }

                if (_animationData->cachedFrames[cacheFrameIndex]) 
                {
                    isUpdatesBoneTimeline = false;
                }
                else 
                {
                    _animationData->cachedFrames[cacheFrameIndex] = true;
                }
            }
        }
        else 
        {
            _armature->_cacheFrameIndex = -1;
        }

        if (isUpdatesTimeline)
        {
            if (isUpdatesBoneTimeline)
            {
                for (const auto boneTimelineState : _boneTimelines)
                {
                    boneTimelineState->update(time);
                }
            }

            for (const auto slotTimelineState : _slotTimelines)
            {
                slotTimelineState->update(time);
            }

            for (const auto ffdTimelineState : _ffdTimelines)
            {
                ffdTimelineState->update(time);
            }
        }
    }

    if (autoFadeOutTime >= 0.f && _fadeProgress >= 1.f && _timeline->_isCompleted)
    {
        fadeOut(autoFadeOutTime);
    }
}

void AnimationState::play()
{
    _isPlaying = true;
}

void AnimationState::stop()
{
    _isPlaying = false;
}

void AnimationState::fadeOut(float fadeOutTime, bool pausePlayhead)
{
    if (fadeOutTime < 0.f || fadeOutTime != fadeOutTime)
    {
        fadeOutTime = 0.f;
    }

    _isPausePlayhead = pausePlayhead;

    if (_isFadeOut)
    {
        if (fadeOutTime > fadeOutTime - _fadeTime)
        {
            return;
        }
    }
    else
    {
        _isFadeOut = true;

        if (fadeOutTime <= 0.f || _fadeProgress <= 0.f)
        {
            _fadeProgress = 0.000001f;
        }

        for (const auto boneTimelineState : _boneTimelines)
        {
            boneTimelineState->fadeOut();
        }

        for (const auto slotTimelineState : _slotTimelines)
        {
            slotTimelineState->fadeOut();
        }
    }

    displayControl = false;
    fadeTotalTime = _fadeProgress > 0.000001f ? fadeOutTime / _fadeProgress : 0.f;
    _fadeTime = fadeTotalTime * (1.f - _fadeProgress);
}

void AnimationState::addBoneMask(const std::string& name, bool recursive)
{
    const auto currentBone = _armature->getBone(name);
    if (!currentBone)
    {
        return;
    }

    if (
        std::find(_boneMask.cbegin(), _boneMask.cend(), name) == _boneMask.cend() &&
        _animationData->getBoneTimeline(name)
        )
    {
        _boneMask.push_back(name);
    }

    if (recursive)
    {
        for (const auto bone : _armature->getBones())
        {
            const auto& boneName = bone->name;
            if (
                std::find(_boneMask.cbegin(), _boneMask.cend(), boneName) == _boneMask.cend() &&
                _animationData->getBoneTimeline(boneName) &&
                currentBone->contains(bone)
                )
            {
                _boneMask.push_back(boneName);
            }
        }
    }

    _updateTimelineStates();
}

void AnimationState::removeBoneMask(const std::string& name, bool recursive)
{
    auto iterator = std::find(_boneMask.begin(), _boneMask.end(), name);
    if (iterator != _boneMask.cend())
    {
        _boneMask.erase(iterator);
    }

    if (recursive)
    {
        const auto currentBone = _armature->getBone(name);
        if (currentBone)
        {
            for (const auto bone : _armature->getBones())
            {
                const auto boneName = bone->name;
                auto iterator = std::find(_boneMask.begin(), _boneMask.end(), boneName);
                if (
                    iterator != _boneMask.cend() &&
                    currentBone->contains(bone)
                    )
                {
                    _boneMask.erase(iterator);
                }
            }
        }
    }

    _updateTimelineStates();
}

void AnimationState::removeAllBoneMask()
{
    _boneMask.clear();
    _updateTimelineStates();
}

bool AnimationState::isCompleted() const
{
    return _timeline->_isCompleted;
}

float AnimationState::getCurrentTime() const
{
    return _timeline->_currentTime;
}

void AnimationState::setCurrentTime(float value)
{
    if (value < 0 || value != value)
    {
        value = 0;
    }

    const auto currentPlayTimes = _timeline->_currentPlayTimes - (_timeline->_isCompleted ? 1 : 0);
    value = std::fmod(value, _duration) + currentPlayTimes * _duration;
    if (_time == value) {
        return;
    }

    _time = value;
    _timeline->setCurrentTime(_time);

    for (const auto boneTimelineState : _boneTimelines)
    {
        boneTimelineState->_isCompleted = false;
    }

    for (const auto slotTimelineState : _slotTimelines)
    {
        slotTimelineState->_isCompleted = false;
    }

    for (const auto ffdTimelineState : _ffdTimelines)
    {
        ffdTimelineState->_isCompleted = false;
    }
}

unsigned AnimationState::getCurrentPlayTimes() const
{
    return _timeline->_currentPlayTimes;
}

DRAGONBONES_NAMESPACE_END
