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


#include "cocostudio/CCTween.h"
#include "cocostudio/CCArmatureAnimation.h"
#include "cocostudio/CCBone.h"
#include "cocostudio/CCArmature.h"
#include "cocostudio/CCUtilMath.h"
#include "cocostudio/CCTransformHelp.h"


namespace cocostudio {

using cocos2d::tweenfunc::Linear;

Tween *Tween::create(Bone *bone)
{
    Tween *pTween = new (std::nothrow) Tween();
    if (pTween && pTween->init(bone))
    {
        pTween->autorelease();
        return pTween;
    }
    CC_SAFE_DELETE(pTween);
    return nullptr;

}



Tween::Tween()
    : _movementBoneData(nullptr)
    , _tweenData(nullptr)
    , _from(nullptr)
    , _to(nullptr)
    , _between(nullptr)
    , _bone(nullptr)

    , _frameTweenEasing(Linear)
    , _fromIndex(0)
    , _toIndex(0)
    , _animation(nullptr)
    , _passLastFrame(false)
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
        _from = new (std::nothrow) FrameData();
        _between = new (std::nothrow) FrameData();

        _bone = bone;
        _tweenData = _bone->getTweenData();
        _tweenData->displayIndex = -1;

        _animation = _bone->getArmature() != nullptr ? _bone->getArmature()->getAnimation() : nullptr;

        bRet = true;
    }
    while (0);

    return bRet;
}


void Tween::play(MovementBoneData *movementBoneData, int durationTo, int durationTween,  int loop, int tweenEasing)
{
    ProcessBase::play(durationTo, durationTween, loop, tweenEasing);

    if (loop)
    {
        _loopType = ANIMATION_TO_LOOP_FRONT;
    }
    else
    {
        _loopType = ANIMATION_NO_LOOP;
    }

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
    else if (_movementBoneData->frameList.size() > 1)
    {
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

void Tween::gotoAndPlay(int frameIndex)
{
    ProcessBase::gotoFrame(frameIndex);

    _totalDuration = 0;
    _betweenDuration = 0;
    _fromIndex = _toIndex = 0;

    _isPlaying = true;
    _isComplete = _isPause = false;

    _currentPercent = (float)_curFrameIndex / ((float)_rawDuration-1);
    _currentFrame = _nextFrameIndex * _currentPercent;
}

void Tween::gotoAndPause(int frameIndex)
{
    gotoAndPlay(frameIndex);
    pause();
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
        case ANIMATION_TO_LOOP_FRONT:
        {
            _loopType = ANIMATION_LOOP_FRONT;

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

    if(_frameTweenEasing != ::cocos2d::tweenfunc::TWEEN_EASING_MAX)
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

        if (!displayManager->isForceChangeDisplay())
        {
            displayManager->changeDisplayWithIndex(displayIndex, false);
        }

        //! Update bone zorder, bone's zorder is determined by frame zorder and bone zorder
        _tweenData->zOrder = keyFrameData->zOrder;
        _bone->updateZOrder();

        //! Update blend type
        _bone->setBlendFunc(keyFrameData->blendFunc);

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
    node = node == nullptr ? _tweenData : node;

    if (!_from->isTween)
    {
        percent = 0;
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

    float playedTime = ((float)_rawDuration-1) * currentPercent;


    //! If play to current frame's front or back, then find current frame again
    if (playedTime < _totalDuration || playedTime >= _totalDuration + _betweenDuration)
    {
        /*
         *  Get frame length, if _toIndex >= _length, then set _toIndex to 0, start anew.
         *  _toIndex is next index will play
         */
        long length = _movementBoneData->frameList.size();
        cocos2d::Vector<FrameData *> &frames = _movementBoneData->frameList;

        FrameData *from = nullptr;
        FrameData *to = nullptr;

        if (playedTime < frames.at(0)->frameID)
        {
            from = to = frames.at(0);
            setBetween(from, to);
            return _currentPercent;
        }
        
        if(playedTime >= frames.at(length - 1)->frameID)
        {
            // If _passLastFrame is true and playedTime >= frames[length - 1]->frameID, then do not need to go on. 
            if (_passLastFrame)
            {
                from = to = frames.at(length - 1);
                setBetween(from, to);
                return _currentPercent;
            }
            _passLastFrame = true;
        }
        else
        {
            _passLastFrame = false;
        }


        do
        {
            _fromIndex = _toIndex;
            from = frames.at(_fromIndex);
            _totalDuration  = from->frameID;

            _toIndex = _fromIndex + 1;
            if (_toIndex >= length)
            {
                _toIndex = 0;
            }

            to = frames.at(_toIndex);

            //! Guaranteed to trigger frame event
            if(from->strEvent.length() != 0 && !_animation->isIgnoreFrameEvent())
            {
                _animation->frameEvent(_bone, from->strEvent.c_str(), from->frameID, playedTime);
            }

            if (playedTime == from->frameID || (_passLastFrame && _fromIndex == length-1))
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
    TweenType tweenType = (_frameTweenEasing != Linear) ? _frameTweenEasing : _tweenEasing;
    if (tweenType != cocos2d::tweenfunc::TWEEN_EASING_MAX && tweenType != Linear && !_passLastFrame)
    {
        currentPercent = cocos2d::tweenfunc::tweenTo(currentPercent, tweenType, _from->easingParams);
    }

    return currentPercent;
}

}
