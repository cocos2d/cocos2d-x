#include "Animation.h"
#include "../armature/Armature.h"
#include "../armature/Slot.h"
#include "AnimationState.h"

DRAGONBONES_NAMESPACE_BEGIN

bool Animation::_sortAnimationState(AnimationState* a, AnimationState* b)
{
    return a->getLayer() > b->getLayer();
}

Animation::Animation() 
{
    _onClear();
}
Animation::~Animation() 
{
    _onClear();
}

void Animation::_onClear()
{
    for (const auto animationState : _animationStates)
    {
        animationState->returnToPool();
    }

    timeScale = 1.f;

    _timelineStateDirty = false;
    _animationStateDirty = false;
    _armature = nullptr;

    _isPlaying = false;
    _time = 0.f;
    _lastAnimationState = nullptr;

    _animations.clear();
    _animationNames.clear();
    _animationStates.clear();
}

void Animation::_fadeOut(float fadeOutTime, int layer, const std::string& group, AnimationFadeOutMode fadeOutMode, bool pauseFadeOut)
{
    switch (fadeOutMode)
    {
        case AnimationFadeOutMode::SameLayer:
            for (const auto animationState : _animationStates)
            {
                if (animationState->getLayer() == layer)
                {
                    animationState->fadeOut(fadeOutTime, pauseFadeOut);
                }
            }
            break;

        case AnimationFadeOutMode::SameGroup:
            for (const auto animationState : _animationStates)
            {
                if (animationState->getGroup() == group)
                {
                    animationState->fadeOut(fadeOutTime, pauseFadeOut);
                }
            }
            break;

        case AnimationFadeOutMode::All:
            for (const auto animationState : _animationStates)
            {
                if (fadeOutTime == 0.f)
                {
                    animationState->returnToPool();
                }
                else
                {
                    animationState->fadeOut(fadeOutTime, pauseFadeOut);
                }
            }

            if (fadeOutTime == 0.f)
            {
                _animationStates.clear();
            }
            break;

        case AnimationFadeOutMode::SameLayerAndGroup:
            for (const auto animationState : _animationStates)
            {
                if (animationState->getLayer() == layer && animationState->getGroup() == group)
                {
                    animationState->fadeOut(fadeOutTime, pauseFadeOut);
                }
            }
            break;

        case AnimationFadeOutMode::None:
        default:
            break;

    }
}

void Animation::_updateFFDTimelineStates()
{
    for (const auto animationState : _animationStates)
    {
        animationState->_updateFFDTimelineStates();
    }
}

void Animation::_advanceTime(float passedTime)
{
    if (!_isPlaying)
    {
        return;
    }

    if (passedTime < 0.f)
    {
        passedTime = -passedTime;
    }

    const auto animationStateCount = _animationStates.size();
    if (animationStateCount == 1)
    {
        const auto animationState = _animationStates[0];
        if (animationState->_isFadeOutComplete)
        {
            animationState->returnToPool();
            _animationStates.clear();
            _animationStateDirty = true;
            _lastAnimationState = nullptr;
        }
        else
        {
            if (_timelineStateDirty)
            {
                animationState->_updateTimelineStates();
            }

            animationState->_advanceTime(passedTime, 1.f, 0);
        }
    }
    else if (animationStateCount > 1)
    {
        auto prevLayer = _animationStates[0]->_layer;
        auto weightLeft = 1.f;
        auto layerTotalWeight = 0.f;
        unsigned animationIndex = 1;

        for (std::size_t i = 0, r = 0; i < animationStateCount; ++i)
        {
            const auto animationState = _animationStates[i];
            if (animationState->_isFadeOutComplete)
            {
                r++;
                animationState->returnToPool();
                _animationStateDirty = true;

                if (_lastAnimationState == animationState)
                {
                    if (i >= r)
                    {
                        _lastAnimationState = _animationStates[i - r];
                    }
                    else
                    {
                        _lastAnimationState = nullptr;
                    }
                }
            }
            else
            {
                if (r > 0)
                {
                    _animationStates[i - r] = animationState;
                }

                if (prevLayer != animationState->_layer)
                {
                    prevLayer = animationState->_layer;

                    if (layerTotalWeight >= weightLeft)
                    {
                        weightLeft = 0.f;
                    }
                    else
                    {
                        weightLeft -= layerTotalWeight;
                    }

                    layerTotalWeight = 0.f;
                }

                if (_timelineStateDirty)
                {
                    animationState->_updateTimelineStates();
                }

                animationState->_advanceTime(passedTime, weightLeft, animationIndex);

                if (animationState->_weightResult != 0.f)
                {
                    layerTotalWeight += animationState->_weightResult;
                    animationIndex++;
                }
            }

            if (i == animationStateCount - 1 && r > 0)
            {
                _animationStates.resize(animationStateCount - r);
            }
        }
    }

    _timelineStateDirty = false;
}

void Animation::reset()
{
    for (const auto animationState : _animationStates)
    {
        animationState->returnToPool();
    }

    _isPlaying = false;
    _lastAnimationState = nullptr;
    _animationStates.clear();
}

void Animation::stop(const std::string& animationName)
{
    if (!animationName.empty())
    {
        const auto animationState = getState(animationName);
        if (animationState)
        {
            animationState->stop();
        }
    }
    else
    {
        _isPlaying = false;
    }
}

AnimationState* Animation::play(const std::string& animationName, int playTimes)
{
    AnimationState* animationState = nullptr;
    if (!animationName.empty())
    {
        animationState = fadeIn(animationName, 0.f, playTimes, 0, "", AnimationFadeOutMode::All);
    }
    else if (!_lastAnimationState)
    {
        const auto defaultAnimation = _armature->getArmatureData().getDefaultAnimation();
        if (defaultAnimation)
        {
            animationState = fadeIn(_armature->getArmatureData().getDefaultAnimation()->name, 0.f, playTimes, 0, "", AnimationFadeOutMode::All);
        }
    }
    else if (!_isPlaying || !_lastAnimationState->isPlaying())
    {
        _isPlaying = true;
        _lastAnimationState->play();
    }
    else
    {
        animationState = fadeIn(_lastAnimationState->getName(), 0.f, playTimes, 0, "", AnimationFadeOutMode::All);
    }

    return animationState;
}

AnimationState* Animation::fadeIn(
    const std::string& animationName, float fadeInTime, int playTimes,
    int layer, const std::string& group, AnimationFadeOutMode fadeOutMode, 
    bool additiveBlending, bool displayControl,
    bool pauseFadeOut, bool pauseFadeIn
)
{
    const auto animationData = mapFind(_animations, animationName);
    if (!animationData)
    {
        _time = 0.f;
        DRAGONBONES_ASSERT(
            false,
            "Non-existent animation." +
            " DragonBones: " + this->_armature->getArmatureData().parent->name +
            " Armature: " + this->_armature->name +
            " Animation: " + animationName
        );
        return nullptr;
    }

    if (_time != _time) 
    {
        _time = 0;
    }

    _isPlaying = true;

    if (fadeInTime != fadeInTime || fadeInTime < 0.f)
    {
        if (_lastAnimationState)
        {
            fadeInTime = animationData->fadeInTime;
        }
        else
        {
            fadeInTime = 0.f;
        }
    }

    if (playTimes < 0)
    {
        playTimes = animationData->playTimes;
    }

    _fadeOut(fadeInTime, layer, group, fadeOutMode, pauseFadeOut);

    _lastAnimationState = BaseObject::borrowObject<AnimationState>();
    _lastAnimationState->_layer = layer;
    _lastAnimationState->_group = group;
    _lastAnimationState->additiveBlending = additiveBlending;
    _lastAnimationState->displayControl = displayControl;
    _lastAnimationState->_fadeIn(
        _armature, animationData->animation ? animationData->animation : animationData, animationName,
        playTimes, animationData->position, animationData->duration, _time, 1.f / animationData->scale, fadeInTime,
        pauseFadeIn
    );
    _animationStates.push_back(_lastAnimationState);
    _animationStateDirty = true;
    _time = 0.f;
    _armature->_cacheFrameIndex = -1;

    if (_animationStates.size() > 1)
    {
        std::sort(_animationStates.begin(), _animationStates.end(), _sortAnimationState);
    }

    for (const auto slot : _armature->getSlots())
    {
        if (slot->inheritAnimation)
        {
            const auto childArmature = slot->getChildArmature();
            if (
                childArmature && 
                childArmature->getAnimation().hasAnimation(animationName) && 
                !childArmature->getAnimation().getState(animationName)
            )
            {
                childArmature->getAnimation().fadeIn(animationName);
            }
        }
    }
    
    if (fadeInTime <= 0.f)
    {
        _armature->advanceTime(0.f);
    }

    return _lastAnimationState;
}

AnimationState* Animation::gotoAndPlayByTime(const std::string& animationName, float time, int playTimes)
{
    _time = time;

    return fadeIn(animationName, 0.f, playTimes, 0, "", AnimationFadeOutMode::All);
}

AnimationState* Animation::gotoAndPlayByFrame(const std::string& animationName, unsigned frame, int playTimes)
{
    const auto clipData = _animations[animationName];
    if (clipData)
    {
        _time = clipData->duration * frame / clipData->frameCount;
    }

    return fadeIn(animationName, 0.f, playTimes, 0, "", AnimationFadeOutMode::All);
}

AnimationState* Animation::gotoAndPlayByProgress(const std::string& animationName, float progress, int playTimes)
{
    const auto clipData = _animations[animationName];
    if (clipData)
    {
        _time = clipData->duration * std::max(progress, 0.f);
    }

    return fadeIn(animationName, 0.f, playTimes, 0, "", AnimationFadeOutMode::All);
}

AnimationState* Animation::gotoAndStopByTime(const std::string& animationName, float time)
{
    const auto animationState = gotoAndPlayByTime(animationName, time, 1);
    if (animationState)
    {
        animationState->stop();
    }

    return animationState;
}

AnimationState* Animation::gotoAndStopByFrame(const std::string& animationName, unsigned frame)
{
    const auto animationState = gotoAndPlayByFrame(animationName, frame, 1);
    if (animationState)
    {
        animationState->stop();
    }

    return animationState;
}

AnimationState* Animation::gotoAndStopByProgress(const std::string& animationName, float progress)
{
    const auto animationState = gotoAndPlayByProgress(animationName, progress, 1);
    if (animationState)
    {
        animationState->stop();
    }

    return animationState;
}

AnimationState* Animation::getState(const std::string& animationName) const
{
    for (std::size_t i = 0, l = _animationStates.size(); i < l; ++i)
    {
        const auto animationState = _animationStates[i];
        if (animationState->getName() == animationName)
        {
            return animationState;
        }
    }

    return nullptr;
}

bool Animation::hasAnimation(const std::string& animationName) const
{
    return _animations.find(animationName) != _animations.end();
}

bool Animation::isPlaying() const
{
    if (_animationStates.size() > 1) 
    {
        return _isPlaying && !isCompleted();
    }
    else if (_lastAnimationState) 
    {
        return _isPlaying && _lastAnimationState->isPlaying();
    }

    return _isPlaying;
}

bool Animation::isCompleted() const
{
    if (_lastAnimationState)
    {
        if (!_lastAnimationState->isCompleted())
        {
            return false;
        }

        for (const auto animationState : _animationStates)
        {
            if (!animationState->isCompleted())
            {
                return false;
            }
        }

        return true;
    }

    return false;
}

const std::string& Animation::getLastAnimationName() const
{
    if (_lastAnimationState)
    {
        return _lastAnimationState->getName();
    }

    static const std::string DEFAULT_NAME = "";
    return DEFAULT_NAME;
}

void Animation::setAnimations(const std::map<std::string, AnimationData*>& value)
{
    if (_animations == value)
    {
        return;
    }

    _animations.clear();
    _animationNames.clear();

    for (const auto& pair : value)
    {
        _animations[pair.first] = pair.second;
        _animationNames.push_back(pair.first);
    }
}

DRAGONBONES_NAMESPACE_END