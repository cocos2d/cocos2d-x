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


#include "CCTween.h"
#include "CCArmatureAnimation.h"
#include "../CCBone.h"
#include "../CCArmature.h"
#include "../utils/CCUtilMath.h"
#include "../utils/CCTweenFunction.h"
#include "../utils/CCTransformHelp.h"


NS_CC_EXT_ARMATURE_BEGIN

Tween *Tween::create(Bone *bone)
{
    Tween *pTween = new Tween();
    if (pTween && pTween->init(bone))
    {
        pTween->autorelease();
        return pTween;
    }
    CC_SAFE_DELETE(pTween);
    return NULL;

}



Tween::Tween()
    : _movementBoneData(NULL)
    , _tweenData(NULL)
    , _from(NULL)
    , _to(NULL)
    , _between(NULL)
    , _bone(NULL)

    , _frameTweenEasing(Linear)
    , _fromIndex(0)
    , _toIndex(0)
    , _animation(NULL)
{

}


Tween::~Tween(void)
{
    CC_SAFE_DELETE( _from );
    CC_SAFE_DELETE( _between );
}


bool Tween::init(Bone *bone)
{
    bool bRet = false;
    do
    {
        _from = new FrameData();
        _between = new FrameData();

        _bone = bone;
        _tweenData = _bone->getTweenData();
        _tweenData->displayIndex = -1;

        _animation = _bone->getArmature() != NULL ? _bone->getArmature()->getAnimation() : NULL;

        bRet = true;
    }
    while (0);

    return bRet;
}


void Tween::play(MovementBoneData *movementBoneData, int durationTo, int durationTween,  int loop, int tweenEasing)
{
    ProcessBase::play(NULL, durationTo, durationTween, loop, tweenEasing);

    _loopType = (AnimationType)loop;

    _totalDuration = 0;
    _betweenDuration = 0;
    _fromIndex = _toIndex = 0;

    bool difMovement = movementBoneData != _movementBoneData;

    setMovementBoneData(movementBoneData);
    _rawDuration = _movementBoneData->duration;

    FrameData *nextKeyFrame = _movementBoneData->getFrameData(0);
    _tweenData->displayIndex = nextKeyFrame->displayIndex;

    if (_bone->getArmature()->getArmatureData()->dataVersion >= VERSION_COMBINED)
    {
        TransformHelp::nodeSub(*_tweenData, *_bone->getBoneData());
        _tweenData->scaleX += 1;
        _tweenData->scaleY += 1;
    }

    if (_rawDuration == 0 )
    {
        _loopType = SINGLE_FRAME;
        if(durationTo == 0)
        {
            setBetween(nextKeyFrame, nextKeyFrame);
        }
        else
        {
            setBetween(_tweenData, nextKeyFrame);
        }
        _frameTweenEasing = Linear;
    }
    else if (_movementBoneData->frameList.count() > 1)
    {
        if (loop)
        {
            _loopType = ANIMATION_TO_LOOP_BACK;
        }
        else
        {
            _loopType = ANIMATION_NO_LOOP;
        }

        _durationTween = durationTween * _movementBoneData->scale;

        if (loop && _movementBoneData->delay != 0)
        {
            setBetween(_tweenData, tweenNodeTo(updateFrameData(1 - _movementBoneData->delay), _between));
        }
        else
        {
            if (!difMovement || durationTo == 0)
            {
                setBetween(nextKeyFrame, nextKeyFrame);
            }
            else
            {
                setBetween(_tweenData, nextKeyFrame);
            }
        }
    }

    tweenNodeTo(0);
}

void Tween::updateHandler()
{
    if (_currentPercent >= 1)
    {
        switch(_loopType)
        {
        case SINGLE_FRAME:
        {
            _currentPercent = 1;
            _isComplete = true;
            _isPlaying = false;
        }
        break;
        case ANIMATION_NO_LOOP:
        {
            _loopType = ANIMATION_MAX;


            if (_durationTween <= 0)
            {
                _currentPercent = 1;
            }
            else
            {
                _currentPercent = (_currentPercent - 1) * _nextFrameIndex / _durationTween;
            }

            if (_currentPercent >= 1)
            {
                _currentPercent = 1;
                _isComplete = true;
                _isPlaying = false;
                break;
            }
            else
            {
                _nextFrameIndex = _durationTween;
                _currentFrame = _currentPercent * _nextFrameIndex;
                _totalDuration = 0;
                _betweenDuration = 0;
                _fromIndex = _toIndex = 0;
                break;
            }
        }
        break;
        case ANIMATION_TO_LOOP_BACK:
        {
            _loopType = ANIMATION_LOOP_BACK;

            _nextFrameIndex = _durationTween > 0 ? _durationTween : 1;

            if (_movementBoneData->delay != 0)
            {
                //
                _currentFrame = (1 - _movementBoneData->delay) * (float)_nextFrameIndex;
                _currentPercent = _currentFrame / _nextFrameIndex;
            }
            else
            {
                _currentPercent = 0;
                _currentFrame = 0;
            }

            _totalDuration = 0;
            _betweenDuration = 0;
            _fromIndex = _toIndex = 0;
        }
        break;
        case ANIMATION_MAX:
        {
            _currentPercent = 1;
            _isComplete = true;
            _isPlaying = false;
        }
        break;
        default:
        {
            _currentFrame = fmodf(_currentFrame, _nextFrameIndex);

            _totalDuration = 0;
            _betweenDuration = 0;
            _fromIndex = _toIndex = 0;
        }
        break;
        }
    }

    if (_currentPercent < 1 && _loopType <= ANIMATION_TO_LOOP_BACK)
    {
        _currentPercent = sin(_currentPercent * CC_HALF_PI);
    }

    float percent  = _currentPercent;

    if (_loopType > ANIMATION_TO_LOOP_BACK)
    {
        percent = updateFrameData(percent);
    }

    if(_frameTweenEasing != TWEEN_EASING_MAX)
    {
        tweenNodeTo(percent);
    }
}

void Tween::setBetween(FrameData *from, FrameData *to, bool limit)
{
    do
    {
        if(from->displayIndex < 0 && to->displayIndex >= 0)
        {
            _from->copy(to);
            _between->subtract(to, to, limit);
            break;
        }
        else if(to->displayIndex < 0 && from->displayIndex >= 0)
        {
            _from->copy(from);
            _between->subtract(to, to, limit);
            break;
        }

        _from->copy(from);
        _between->subtract(from, to, limit);
    }
    while (0);

    if (!from->isTween)
    {
        _tweenData->copy(from);
        _tweenData->isTween = true;
    }

    arriveKeyFrame(from);
}


void Tween::arriveKeyFrame(FrameData *keyFrameData)
{
    if(keyFrameData)
    {
        DisplayManager *displayManager = _bone->getDisplayManager();

        //! Change bone's display
        int displayIndex = keyFrameData->displayIndex;

        if (!displayManager->getForceChangeDisplay())
        {
            displayManager->changeDisplayByIndex(displayIndex, false);
        }

        //! Update bone zorder, bone's zorder is determined by frame zorder and bone zorder
        _tweenData->zOrder = keyFrameData->zOrder;
        _bone->updateZOrder();

        //! Update blend type
        _bone->setBlendType(keyFrameData->blendType);

        //! Update child armature's movement
        Armature *childAramture = _bone->getChildArmature();
        if(childAramture)
        {
            if(keyFrameData->strMovement.length() != 0)
            {
                childAramture->getAnimation()->play(keyFrameData->strMovement.c_str());
            }
        }
    }
}

FrameData *Tween::tweenNodeTo(float percent, FrameData *node)
{
    node = node == NULL ? _tweenData : node;

    if (!_from->isTween)
    {
        return _from;
    }

    node->x = _from->x + percent * _between->x;
    node->y = _from->y + percent * _between->y;
    node->scaleX = _from->scaleX + percent * _between->scaleX;
    node->scaleY = _from->scaleY + percent * _between->scaleY;
    node->skewX = _from->skewX + percent * _between->skewX;
    node->skewY = _from->skewY + percent * _between->skewY;

    _bone->setTransformDirty(true);

    if (node && _between->isUseColorInfo)
    {
        tweenColorTo(percent, node);
    }

    return node;
}

void Tween::tweenColorTo(float percent, FrameData *node)
{
    node->a = _from->a + percent * _between->a;
    node->r = _from->r + percent * _between->r;
    node->g = _from->g + percent * _between->g;
    node->b = _from->b + percent * _between->b;
    _bone->updateColor();
}

float Tween::updateFrameData(float currentPercent)
{
    if (currentPercent > 1 && _movementBoneData->delay != 0)
    {
        currentPercent = fmodf(currentPercent, 1);
    }

    float playedTime = (float)_rawDuration * currentPercent;


    //! If play to current frame's front or back, then find current frame again
    if (playedTime < _totalDuration || playedTime >= _totalDuration + _betweenDuration)
    {
        /*
         *  Get frame length, if _toIndex >= _length, then set _toIndex to 0, start anew.
         *  _toIndex is next index will play
         */
        int length = _movementBoneData->frameList.count();
        FrameData **frames = (FrameData **)_movementBoneData->frameList.data->arr;

        FrameData *from = NULL;
        FrameData *to = NULL;

        if (playedTime < frames[0]->frameID)
        {
            from = to = frames[0];
            setBetween(from, to);
            return currentPercent;
        }
        else if(playedTime >= frames[length - 1]->frameID)
        {
            from = to = frames[length - 1];
            setBetween(from, to);
            return currentPercent;
        }


        do
        {
            from = frames[_fromIndex];
            _totalDuration  = from->frameID;

            if (++_toIndex >= length)
            {
                _toIndex = 0;
            }

            _fromIndex = _toIndex;
            to = frames[_toIndex];

            //! Guaranteed to trigger frame event
            if(from->strEvent.length() != 0)
            {
                _animation->frameEvent(_bone, from->strEvent.c_str(), from->frameID, playedTime);
            }

            if (playedTime == from->frameID)
            {
                break;
            }
        }
        while (playedTime < from->frameID || playedTime >= to->frameID);

        _betweenDuration = to->frameID - from->frameID;

        _frameTweenEasing = from->tweenEasing;

        setBetween(from, to, false);

    }
    currentPercent = _betweenDuration == 0 ? 0 : (playedTime - _totalDuration) / (float)_betweenDuration;


    /*
     *  If frame tween easing equal to TWEEN_EASING_MAX, then it will not do tween.
     */

    CCTweenType tweenType;

    if ( _frameTweenEasing != TWEEN_EASING_MAX)
    {
        tweenType = (_tweenEasing == TWEEN_EASING_MAX) ? _frameTweenEasing : _tweenEasing;
        if (tweenType != TWEEN_EASING_MAX && tweenType != Linear)
        {
            currentPercent = TweenFunction::tweenTo(0, 1, currentPercent, 1, tweenType);
        }
    }

    return currentPercent;
}

NS_CC_EXT_ARMATURE_END
