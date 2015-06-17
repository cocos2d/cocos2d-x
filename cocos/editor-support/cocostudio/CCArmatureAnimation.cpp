/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "cocostudio/CCArmatureAnimation.h"
#include "cocostudio/CCArmature.h"
#include "cocostudio/CCBone.h"
#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CCUtilMath.h"
#include "cocostudio/CCDatas.h"

using namespace cocos2d;


namespace cocostudio {

ArmatureAnimation *ArmatureAnimation::create(Armature *armature)
{
    ArmatureAnimation *pArmatureAnimation = new (std::nothrow) ArmatureAnimation();
    if (pArmatureAnimation && pArmatureAnimation->init(armature))
    {
        pArmatureAnimation->autorelease();
        return pArmatureAnimation;
    }
    CC_SAFE_DELETE(pArmatureAnimation);
    return nullptr;
}


ArmatureAnimation::ArmatureAnimation()
    : _animationData(nullptr)
    , _speedScale(1)
    , _movementData(nullptr)
    , _armature(nullptr)
    , _movementID("")
    , _toIndex(0)
    , _ignoreFrameEvent(false)
    , _onMovementList(false)
    , _movementListLoop(false)
    , _movementListDurationTo(-1)
    , _userObject(nullptr)

    , _movementEventCallFunc(nullptr)
    , _frameEventCallFunc(nullptr)
    , _movementEventTarget(nullptr)
    , _frameEventTarget(nullptr)
    
    , _movementEventListener(nullptr)
    , _frameEventListener(nullptr)
{

}

ArmatureAnimation::~ArmatureAnimation(void)
{
    CC_SAFE_RELEASE_NULL(_animationData);

    CC_SAFE_RELEASE_NULL(_userObject);
}

bool ArmatureAnimation::init(Armature *armature)
{
    bool bRet = false;
    do
    {
        _armature = armature;

        _tweenList.clear();

        bRet = true;
    }
    while (0);

    return bRet;
}


void ArmatureAnimation::pause()
{
    for (const auto& tween : _tweenList)
    {
        tween->pause();
    }
    ProcessBase::pause();
}

void ArmatureAnimation::resume()
{
    for (const auto& tween : _tweenList)
    {
        tween->resume();
    }
    ProcessBase::resume();
}

void ArmatureAnimation::stop()
{
    for (const auto& tween : _tweenList)
    {
        tween->stop();
    }
    _tweenList.clear();
    ProcessBase::stop();
}

void ArmatureAnimation::setAnimationScale(float animationScale )
{
    setSpeedScale(animationScale);
}

float ArmatureAnimation::getAnimationScale() const
{
    return getSpeedScale();
}


void ArmatureAnimation::setSpeedScale(float speedScale)
{
    if(speedScale == _speedScale)
    {
        return;
    }

    _speedScale = speedScale;

    _processScale = !_movementData ? _speedScale : _speedScale * _movementData->scale;

    const Map<std::string, Bone*>& map = _armature->getBoneDic();
    for(auto& element : map)
    {
        Bone *bone = element.second;

        bone->getTween()->setProcessScale(_processScale);
        if (bone->getChildArmature())
        {
            bone->getChildArmature()->getAnimation()->setSpeedScale(_processScale);
        }
    }
}

float ArmatureAnimation::getSpeedScale() const
{
    return _speedScale;
}


void ArmatureAnimation::play(const std::string& animationName, int durationTo,  int loop)
{
    if (animationName.empty())
    {
        CCLOG("_animationData can not be null");
        return;
    }
//    CCASSERT(_animationData, "_animationData can not be null");

    _movementData = _animationData->getMovement(animationName.c_str());
    if (nullptr == _movementData)
    {
        CCLOG("_movementData can not be null");
        return;
    }
//    CCASSERT(_movementData, "_movementData can not be null");

    //! Get key frame count
    _rawDuration = _movementData->duration;

    _movementID = animationName;

    _processScale = _speedScale * _movementData->scale;

    //! Further processing parameters
    durationTo = (durationTo == -1) ? _movementData->durationTo : durationTo;

    int durationTween = _movementData->durationTween == 0 ? _rawDuration : _movementData->durationTween;

    cocos2d::tweenfunc::TweenType tweenEasing = _movementData->tweenEasing;
    loop = (loop < 0) ? _movementData->loop : loop;

    _onMovementList = false;

    ProcessBase::play(durationTo, durationTween, loop, tweenEasing);


    if (_rawDuration == 0)
    {
        _loopType = SINGLE_FRAME;
    }
    else
    {
        if (loop)
        {
            _loopType = ANIMATION_TO_LOOP_FRONT;
        }
        else
        {
            _loopType = ANIMATION_NO_LOOP;
        }
        _durationTween = durationTween;
    }

    MovementBoneData *movementBoneData = nullptr;
    _tweenList.clear();

    const Map<std::string, Bone*>& map = _armature->getBoneDic();
    for(auto& element : map)
    {
        Bone *bone = element.second;
        movementBoneData = static_cast<MovementBoneData *>(_movementData->movBoneDataDic.at(bone->getName()));

        Tween *tween = bone->getTween();
        if(movementBoneData && movementBoneData->frameList.size() > 0)
        {
            _tweenList.pushBack(tween);
            movementBoneData->duration = _movementData->duration;
            tween->play(movementBoneData, durationTo, durationTween, loop, tweenEasing);

            tween->setProcessScale(_processScale);

            if (bone->getChildArmature())
            {
                bone->getChildArmature()->getAnimation()->setSpeedScale(_processScale);
            }
        }
        else
        {
            if(!bone->isIgnoreMovementBoneData())
            {
                //! this bone is not include in this movement, so hide it
                bone->getDisplayManager()->changeDisplayWithIndex(-1, false);
                tween->stop();
            }

        }
    }

    _armature->update(0);
}

void ArmatureAnimation::playByIndex(int animationIndex, int durationTo, int loop)
{
    playWithIndex(animationIndex, durationTo, loop);
}

void ArmatureAnimation::playWithIndex(int animationIndex, int durationTo, int loop)
{
    std::vector<std::string> &movName = _animationData->movementNames;
    CC_ASSERT((animationIndex > -1) && ((unsigned int)animationIndex < movName.size()));

    std::string animationName = movName.at(animationIndex);
    play(animationName.c_str(), durationTo, loop);
}


void ArmatureAnimation::playWithNames(const std::vector<std::string>& movementNames, int durationTo, bool loop)
{
    _movementList.clear();
    _movementListLoop = loop;
    _movementListDurationTo = durationTo;
    _onMovementList = true;
    _movementIndex = 0;

    _movementList = movementNames;

    updateMovementList();
}

void ArmatureAnimation::playWithIndexes(const std::vector<int>& movementIndexes, int durationTo, bool loop)
{
    _movementList.clear();
    _movementListLoop = loop;
    _movementListDurationTo = durationTo;
    _onMovementList = true;
    _movementIndex = 0;

    std::vector<std::string> &movName = _animationData->movementNames;

    for(auto& index : movementIndexes)
    {
        std::string name = movName.at(index);
        _movementList.push_back(name);
    }

    updateMovementList();
}

void ArmatureAnimation::gotoAndPlay(int frameIndex)
{
    if (!_movementData || frameIndex < 0 || frameIndex >= _movementData->duration)
    {
        CCLOG("Please ensure you have played a movement, and the frameIndex is in the range.");
        return;
    }

    bool ignoreFrameEvent = _ignoreFrameEvent;
    _ignoreFrameEvent = true;

    _isPlaying = true;
    _isComplete = _isPause = false;

    ProcessBase::gotoFrame(frameIndex);
    _currentPercent = (float)_curFrameIndex / ((float)_movementData->duration-1);
    _currentFrame = _nextFrameIndex * _currentPercent;

    
    for (const auto &tween : _tweenList)
    {
        tween->gotoAndPlay(frameIndex);
    }

    _armature->update(0);

    _ignoreFrameEvent = ignoreFrameEvent;
}

void ArmatureAnimation::gotoAndPause(int frameIndex)
{
    gotoAndPlay(frameIndex);
    pause();
}

ssize_t ArmatureAnimation::getMovementCount() const
{
    return _animationData->getMovementCount();
}

void ArmatureAnimation::update(float dt)
{
    ProcessBase::update(dt);
    
    for (const auto &tween : _tweenList)
    {
        tween->update(dt);
    }

    if(_frameEventQueue.size() > 0 || _movementEventQueue.size() > 0)
    {
        _armature->retain();
        _armature->autorelease();
    }

    while (_frameEventQueue.size() > 0)
    {
        FrameEvent *event = _frameEventQueue.front();
        _frameEventQueue.pop();

        _ignoreFrameEvent = true;
        
        if(_frameEventTarget)
        {
            (_frameEventTarget->*_frameEventCallFunc)(event->bone, event->frameEventName, event->originFrameIndex, event->currentFrameIndex);
        }
        
        if (_frameEventListener)
        {
            _frameEventListener(event->bone, event->frameEventName, event->originFrameIndex, event->currentFrameIndex);
        }
        
        
        _ignoreFrameEvent = false;

        CC_SAFE_DELETE(event);
    }

    while (_movementEventQueue.size() > 0)
    {
        MovementEvent *event = _movementEventQueue.front();
        _movementEventQueue.pop();
        
        if(_movementEventTarget)
        {
            (_movementEventTarget->*_movementEventCallFunc)(event->armature, event->movementType, event->movementID);
        }
        
        if (_movementEventListener)
        {
            _movementEventListener(event->armature, event->movementType, event->movementID);
        }
        
        CC_SAFE_DELETE(event);
    }
}

void ArmatureAnimation::updateHandler()
{
    if (_currentPercent >= 1)
    {
        switch(_loopType)
        {
        case ANIMATION_NO_LOOP:
        {
            _loopType = ANIMATION_MAX;
            _currentFrame = (_currentPercent - 1) * _nextFrameIndex;
            _currentPercent = _currentFrame / _durationTween;

            if (_currentPercent >= 1.0f)
            {
            }
            else
            {
                _nextFrameIndex = _durationTween;

                movementEvent(_armature, START, _movementID.c_str());

                break;
            }
        }
        break;
        case ANIMATION_MAX:
        case SINGLE_FRAME:
        {
            _currentPercent = 1;
            _isComplete = true;
            _isPlaying = false;

            movementEvent(_armature, COMPLETE, _movementID.c_str());

            updateMovementList();
        }
        break;
        case ANIMATION_TO_LOOP_FRONT:
        {
            _loopType = ANIMATION_LOOP_FRONT;
            _currentPercent = fmodf(_currentPercent, 1);
            _currentFrame = _nextFrameIndex == 0 ? 0 : fmodf(_currentFrame, _nextFrameIndex);
            _nextFrameIndex = _durationTween > 0 ? _durationTween : 1;

            movementEvent(_armature, START, _movementID.c_str());
        }
        break;
        default:
        {
            //_currentPercent = fmodf(_currentPercent, 1);
            _currentFrame = fmodf(_currentFrame, _nextFrameIndex);
            _toIndex = 0;

            movementEvent(_armature, LOOP_COMPLETE, _movementID.c_str());
        }
        break;
        }
    }
}

std::string ArmatureAnimation::getCurrentMovementID() const
{
    if (_isComplete)
    {
        return "";
    }
    return _movementID;
}

void ArmatureAnimation::setMovementEventCallFunc(Ref *target, SEL_MovementEventCallFunc callFunc)
{
    _movementEventTarget = target;
    _movementEventCallFunc = callFunc;
}

void ArmatureAnimation::setFrameEventCallFunc(Ref *target, SEL_FrameEventCallFunc callFunc)
{
    _frameEventTarget = target;
    _frameEventCallFunc = callFunc;
}

void ArmatureAnimation::setMovementEventCallFunc(std::function<void(Armature *armature, MovementEventType movementType, const std::string& movementID)> listener)
{
    _movementEventListener = listener;
}
void ArmatureAnimation::setFrameEventCallFunc(std::function<void(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)> listener)
{
    _frameEventListener = listener;
}

void ArmatureAnimation::setUserObject(Ref *pUserObject)
{
    CC_SAFE_RETAIN(pUserObject);
    CC_SAFE_RELEASE(_userObject);
    _userObject = pUserObject;
}

void ArmatureAnimation::frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)
{
    if ((_frameEventTarget && _frameEventCallFunc) || _frameEventListener)
    {
        FrameEvent *frameEvent = new (std::nothrow) FrameEvent();
        frameEvent->bone = bone;
        frameEvent->frameEventName = frameEventName;
        frameEvent->originFrameIndex = originFrameIndex;
        frameEvent->currentFrameIndex = currentFrameIndex;

        _frameEventQueue.push(frameEvent);
    }
}


void ArmatureAnimation::movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    if ((_movementEventTarget && _movementEventCallFunc) || _movementEventListener)
    {
        MovementEvent *movementEvent = new (std::nothrow) MovementEvent();
        movementEvent->armature = armature;
        movementEvent->movementType = movementType;
        movementEvent->movementID = movementID;
        _movementEventQueue.push(movementEvent);
    }
}


void ArmatureAnimation::updateMovementList()
{
    if (_onMovementList)
    {
        if (_movementListLoop)
        {
            play(_movementList.at(_movementIndex).c_str(), _movementListDurationTo, 0);
            _movementIndex++;

            if (_movementIndex >= _movementList.size())
             {
                 _movementIndex = 0;
            }
        }
        else
        {
            if (_movementIndex < _movementList.size())
            {
                play(_movementList.at(_movementIndex).c_str(), _movementListDurationTo, 0);
                _movementIndex++;
            }
            else
            {
                _onMovementList = false;
            }
        }

        _onMovementList = true;
    }
}

}
