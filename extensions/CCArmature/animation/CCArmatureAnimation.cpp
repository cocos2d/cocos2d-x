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
#include "../utils/CCConstValue.h"
#include "../datas/CCDatas.h"


NS_CC_EXT_BEGIN

CCArmatureAnimation *CCArmatureAnimation::create(CCArmature *armature)
{
    CCArmatureAnimation *pArmatureAnimation = new CCArmatureAnimation();
    if (pArmatureAnimation && pArmatureAnimation->init(armature))
    {
        pArmatureAnimation->autorelease();
        return pArmatureAnimation;
    }
    CC_SAFE_DELETE(pArmatureAnimation);
    return NULL;
}


CCArmatureAnimation::CCArmatureAnimation()
	: _animationData(NULL)
	, _armature(NULL)
    , _movementID("")
    , _toIndex(0)
{

}

CCArmatureAnimation::~CCArmatureAnimation(void)
{
    CC_SAFE_RELEASE_NULL(_tweenList);
    CC_SAFE_RELEASE_NULL(_animationData);
}

bool CCArmatureAnimation::init(CCArmature *armature)
{
    bool bRet = false;
    do
    {
        _armature = armature;

        _tweenList = new CCArray();
        _tweenList->init();

        bRet = true;
    }
    while (0);

    return bRet;
}


void CCArmatureAnimation:: pause()
{
    CCObject *object = NULL;
    CCARRAY_FOREACH(_tweenList, object)
    {
        ((CCTween *)object)->pause();
    }
    CCProcessBase::pause();
}

void CCArmatureAnimation::resume()
{
    CCObject *object = NULL;
    CCARRAY_FOREACH(_tweenList, object)
    {
        ((CCTween *)object)->resume();
    }
    CCProcessBase::resume();
}

void CCArmatureAnimation::stop()
{
    CCObject *object = NULL;
    CCARRAY_FOREACH(_tweenList, object)
    {
        ((CCTween *)object)->stop();
    }
    _tweenList->removeAllObjects();
    CCProcessBase::stop();
}

void CCArmatureAnimation::setAnimationScale(float animationScale )
{
    if(animationScale == _animationScale)
    {
        return;
    }

    _animationScale = animationScale;

    CCDictElement *element = NULL;
    CCDictionary *dict = _armature->getBoneDic();
    CCDICT_FOREACH(dict, element)
    {
        CCBone *bone = (CCBone *)element->getObject();
        bone->getTween()->setAnimationScale(_animationScale);
        if (bone->getChildArmature())
        {
            bone->getChildArmature()->getAnimation()->setAnimationScale(_animationScale);
        }
    }
}


void CCArmatureAnimation::play(const char *animationName, int durationTo, int durationTween,  int loop, int tweenEasing)
{
    CCAssert(_animationData, "_animationData can not be null");

    _movementData = _animationData->getMovement(animationName);
    CCAssert(_movementData, "_movementData can not be null");

    //! Get key frame count
    _rawDuration = _movementData->duration;

    _movementID = animationName;

    //! Further processing parameters
    durationTo = (durationTo == -1) ? _movementData->durationTo : durationTo;

    durationTween = (durationTween == -1) ? _movementData->durationTween : durationTween;
    durationTween = (durationTween == 0) ? _movementData->duration : durationTween;

    tweenEasing	= (tweenEasing == TWEEN_EASING_MAX) ? _movementData->tweenEasing : tweenEasing;
    loop = (loop < 0) ? _movementData->loop : loop;


    CCProcessBase::play((void *)animationName, durationTo, durationTween, loop, tweenEasing);


    if (_rawDuration == 1)
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

    CCMovementBoneData *movementBoneData = NULL;
    _tweenList->removeAllObjects();

    CCDictElement *element = NULL;
    CCDictionary *dict = _armature->getBoneDic();

    CCDICT_FOREACH(dict, element)
    {
        CCBone *bone = (CCBone *)element->getObject();
        movementBoneData = (CCMovementBoneData *)_movementData->movBoneDataDic.objectForKey(bone->getName());

        CCTween *tween = bone->getTween();
        if(movementBoneData && movementBoneData->frameList.count() > 0)
        {
            _tweenList->addObject(tween);
            tween->play(movementBoneData, durationTo, durationTween, loop, tweenEasing);

            tween->setAnimationScale(_animationScale);
            if (bone->getChildArmature())
            {
                bone->getChildArmature()->getAnimation()->setAnimationScale(_animationScale);
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

    //_armature->update(0);
}


void CCArmatureAnimation::playByIndex(int animationIndex, int durationTo, int durationTween,  int loop, int tweenEasing)
{
    std::vector<std::string> &movName = _animationData->movementNames;
    CC_ASSERT((animationIndex > -1) && ((unsigned int)animationIndex < movName.size()));

    std::string animationName = movName.at(animationIndex);
    play(animationName.c_str(), durationTo, durationTween, loop, tweenEasing);
}



int CCArmatureAnimation::getMovementCount()
{
    return _animationData->getMovementCount();
}

void CCArmatureAnimation::update(float dt)
{
    CCProcessBase::update(dt);
    CCObject *object = NULL;
    CCARRAY_FOREACH(_tweenList, object)
    {
        ((CCTween *)object)->update(dt);
    }
}

void CCArmatureAnimation::updateHandler()
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

                MovementEventSignal.emit(_armature, START, _movementID.c_str());

                break;
            }
        }
        break;
        case ANIMATION_MAX:
        case SINGLE_FRAME:
        {
            _currentPercent = 1;
            _isComplete = true;

            MovementEventSignal.emit(_armature, COMPLETE, _movementID.c_str());
        }
        break;
        case ANIMATION_TO_LOOP_FRONT:
        {
            _loopType = ANIMATION_LOOP_FRONT;
            _currentPercent = fmodf(_currentPercent, 1);
            _currentFrame = fmodf(_currentFrame, _nextFrameIndex);
            _nextFrameIndex = _durationTween > 0 ? _durationTween : 1;

            MovementEventSignal.emit(_armature, START, _movementID.c_str());
        }
        break;
        default:
        {
            _currentPercent = fmodf(_currentPercent, 1);
            _currentFrame = fmodf(_currentFrame, _nextFrameIndex);
            _toIndex = 0;

            MovementEventSignal.emit(_armature, LOOP_COMPLETE, _movementID.c_str());
        }
        break;
        }
    }

    if (_loopType == ANIMATION_LOOP_FRONT || _loopType == ANIMATION_LOOP_BACK)
    {
        updateFrameData(_currentPercent);
    }
}


void CCArmatureAnimation::updateFrameData(float currentPercent)
{
    _prevFrameIndex = _curFrameIndex;
    _curFrameIndex = _rawDuration * currentPercent;
    _curFrameIndex = _curFrameIndex % _rawDuration;
}


NS_CC_EXT_END
