/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#include "CCArmatureAnimation.h"
#include "../CCArmature.h"
#include "../CCBone.h"
#include "../utils/CCArmatureDefine.h"
#include "../utils/CCUtilMath.h"
#include "../datas/CCDatas.h"


NS_CC_EXT_ARMATURE_BEGIN

ArmatureAnimation *ArmatureAnimation::create(Armature *armature)
{
    ArmatureAnimation *pArmatureAnimation = new ArmatureAnimation();
    if (pArmatureAnimation && pArmatureAnimation->init(armature))
    {
        pArmatureAnimation->autorelease();
        return pArmatureAnimation;
    }
    CC_SAFE_DELETE(pArmatureAnimation);
    return NULL;
}


ArmatureAnimation::ArmatureAnimation()
    : _animationData(NULL)
    , _speedScale(1)
    , _movementData(NULL)
    , _armature(NULL)
    , _movementID("")
    , _toIndex(0)

    , _movementEventCallFunc(NULL)
    , _frameEventCallFunc(NULL)
    , _movementEventTarget(NULL)
    , _frameEventTarget(NULL)
{

}

ArmatureAnimation::~ArmatureAnimation(void)
{
    CC_SAFE_RELEASE_NULL(_tweenList);
    CC_SAFE_RELEASE_NULL(_animationData);

    CC_SAFE_RELEASE_NULL(_movementEventTarget);
    CC_SAFE_RELEASE_NULL(_frameEventTarget);
}

bool ArmatureAnimation::init(Armature *armature)
{
    bool bRet = false;
    do
    {
        _armature = armature;

        _tweenList = new Array();
        _tweenList->init();

        bRet = true;
    }
    while (0);

    return bRet;
}


void ArmatureAnimation:: pause()
{
    Object *object = NULL;
    CCARRAY_FOREACH(_tweenList, object)
    {
		static_cast<Tween*>(object)->pause();
    }
    ProcessBase::pause();
}

void ArmatureAnimation::resume()
{
    Object *object = NULL;
    CCARRAY_FOREACH(_tweenList, object)
    {
        static_cast<Tween*>(object)->resume();
    }
    ProcessBase::resume();
}

void ArmatureAnimation::stop()
{
    Object *object = NULL;
    CCARRAY_FOREACH(_tweenList, object)
    {
        static_cast<Tween*>(object)->stop();
    }
    _tweenList->removeAllObjects();
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

    DictElement *element = NULL;
    Dictionary *dict = _armature->getBoneDic();
    CCDICT_FOREACH(dict, element)
    {
        Bone *bone = static_cast<Bone*>(element->getObject());

        bone->getTween()->setProcessScale(_processScale);
        if (bone->getChildArmature())
        {
            bone->getChildArmature()->getAnimation()->setProcessScale(_processScale);
        }
    }
}

float ArmatureAnimation::getSpeedScale() const
{
    return _speedScale;
}

void ArmatureAnimation::setAnimationInternal(float animationInternal)
{
    if(animationInternal == _animationInternal)
    {
        return;
    }

    _animationInternal = animationInternal;

    DictElement *element = NULL;
    Dictionary *dict = _armature->getBoneDic();
    CCDICT_FOREACH(dict, element)
    {
        Bone *bone = static_cast<Bone*>(element->getObject());
        bone->getTween()->setAnimationInternal(_animationInternal);
        if (bone->getChildArmature())
        {
            bone->getChildArmature()->getAnimation()->setAnimationInternal(_animationInternal);
        }
    }
}


void ArmatureAnimation::play(const char *animationName, int durationTo, int durationTween,  int loop, int tweenEasing)
{
    CCASSERT(_animationData, "_animationData can not be null");

    _movementData = _animationData->getMovement(animationName);
    CCASSERT(_movementData, "_movementData can not be null");

    //! Get key frame count
    _rawDuration = _movementData->duration;

    _movementID = animationName;

    _processScale = _speedScale * _movementData->scale;

    //! Further processing parameters
    durationTo = (durationTo == -1) ? _movementData->durationTo : durationTo;

    durationTween = (durationTween == -1) ? _movementData->durationTween : durationTween;
    durationTween = (durationTween == 0) ? _movementData->duration : durationTween;

    tweenEasing	= (tweenEasing == TWEEN_EASING_MAX) ? _movementData->tweenEasing : tweenEasing;
    loop = (loop < 0) ? _movementData->loop : loop;


    ProcessBase::play((void *)animationName, durationTo, durationTween, loop, tweenEasing);


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
            _rawDuration --;
        }
        _durationTween = durationTween;
    }

    MovementBoneData *movementBoneData = NULL;
    _tweenList->removeAllObjects();

    DictElement *element = NULL;
    Dictionary *dict = _armature->getBoneDic();

    CCDICT_FOREACH(dict, element)
    {
        Bone *bone = static_cast<Bone*>(element->getObject());
        movementBoneData = static_cast<MovementBoneData *>(_movementData->movBoneDataDic.objectForKey(bone->getName()));

        Tween *tween = bone->getTween();
        if(movementBoneData && movementBoneData->frameList.count() > 0)
        {
            _tweenList->addObject(tween);
            movementBoneData->duration = _movementData->duration;
            tween->play(movementBoneData, durationTo, durationTween, loop, tweenEasing);

            tween->setProcessScale(_processScale);
            tween->setAnimationInternal(_animationInternal);

            if (bone->getChildArmature())
            {
                bone->getChildArmature()->getAnimation()->setProcessScale(_processScale);
                bone->getChildArmature()->getAnimation()->setAnimationInternal(_animationInternal);
            }
        }
        else
        {
            if(!bone->getIgnoreMovementBoneData())
            {
                //! this bone is not include in this movement, so hide it
                bone->getDisplayManager()->changeDisplayByIndex(-1, false);
                tween->stop();
            }

        }
    }
}


void ArmatureAnimation::playByIndex(int animationIndex, int durationTo, int durationTween,  int loop, int tweenEasing)
{
    std::vector<std::string> &movName = _animationData->movementNames;
    CC_ASSERT((animationIndex > -1) && ((unsigned int)animationIndex < movName.size()));

    std::string animationName = movName.at(animationIndex);
    play(animationName.c_str(), durationTo, durationTween, loop, tweenEasing);
}



int ArmatureAnimation::getMovementCount()
{
    return _animationData->getMovementCount();
}

void ArmatureAnimation::update(float dt)
{
    ProcessBase::update(dt);
    Object *object = NULL;
    CCARRAY_FOREACH(_tweenList, object)
    {
		static_cast<Tween *>(object)->update(dt);
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

                if (_movementEventTarget && _movementEventCallFunc)
                {
                    (_movementEventTarget->*_movementEventCallFunc)(_armature, START, _movementID.c_str());
                }

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

            if (_movementEventTarget && _movementEventCallFunc)
            {
                (_movementEventTarget->*_movementEventCallFunc)(_armature, COMPLETE, _movementID.c_str());
            }
        }
        break;
        case ANIMATION_TO_LOOP_FRONT:
        {
            _loopType = ANIMATION_LOOP_FRONT;
            _currentPercent = fmodf(_currentPercent, 1);
            _currentFrame = _nextFrameIndex == 0 ? 0 : fmodf(_currentFrame, _nextFrameIndex);
            _nextFrameIndex = _durationTween > 0 ? _durationTween : 1;

            if (_movementEventTarget && _movementEventCallFunc)
            {
                (_movementEventTarget->*_movementEventCallFunc)(_armature, START, _movementID.c_str());
            }
        }
        break;
        default:
        {
            //_currentPercent = fmodf(_currentPercent, 1);
            _currentFrame = fmodf(_currentFrame, _nextFrameIndex);
            _toIndex = 0;

            if (_movementEventTarget && _movementEventCallFunc)
            {
                (_movementEventTarget->*_movementEventCallFunc)(_armature, LOOP_COMPLETE, _movementID.c_str());
            }
        }
        break;
        }
    }
}

std::string ArmatureAnimation::getCurrentMovementID()
{
    if (_isComplete)
    {
        return "";
    }
    return _movementID;
}

void ArmatureAnimation::setMovementEventCallFunc(Object *target, SEL_MovementEventCallFunc callFunc)
{
    if (target != _movementEventTarget)
    {
        CC_SAFE_RETAIN(target);
        CC_SAFE_RELEASE_NULL(_movementEventTarget);
        _movementEventTarget = target;
    }
    _movementEventCallFunc = callFunc;
}

void ArmatureAnimation::setFrameEventCallFunc(Object *target, SEL_FrameEventCallFunc callFunc)
{
    if (target != _frameEventTarget)
    {
        CC_SAFE_RETAIN(target);
        CC_SAFE_RELEASE_NULL(_frameEventTarget);
        _frameEventTarget = target;
    }
    _frameEventCallFunc = callFunc;
}

void ArmatureAnimation::frameEvent(Bone *bone, const char *frameEventName, int originFrameIndex, int currentFrameIndex)
{
    if (_frameEventTarget && _frameEventCallFunc)
    {
        (_frameEventTarget->*_frameEventCallFunc)(bone, frameEventName, originFrameIndex, currentFrameIndex);
    }
}
NS_CC_EXT_ARMATURE_END
