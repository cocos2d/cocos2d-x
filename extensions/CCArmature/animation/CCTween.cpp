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


namespace cocos2d { namespace extension { namespace armature {

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
	, _currentKeyFrame(NULL)
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

    _currentKeyFrame = NULL;
    _isTweenKeyFrame = false;

    _totalDuration = 0;
    betweenDuration = 0;
    _toIndex = 0;

    setMovementBoneData(movementBoneData);


    if (_movementBoneData->frameList.count() == 1)
    {
        _loopType = SINGLE_FRAME;
        FrameData *_nextKeyFrame = _movementBoneData->getFrameData(0);
        if(durationTo == 0)
        {
            setBetween(_nextKeyFrame, _nextKeyFrame);
        }
        else
        {
            _tweenData->displayIndex = _nextKeyFrame->displayIndex;
            setBetween(_tweenData, _nextKeyFrame);
        }
        _isTweenKeyFrame = true;
        _frameTweenEasing = Linear;
        _rawDuration = _movementBoneData->duration;
        _fromIndex = _toIndex = 0;
    }
    else if (_movementBoneData->frameList.count() > 1)
    {
        if (loop)
        {
            _loopType = ANIMATION_TO_LOOP_BACK;
            _rawDuration = _movementBoneData->duration;
        }
        else
        {
            _loopType = ANIMATION_NO_LOOP;
            _rawDuration = _movementBoneData->duration - 1;
        }

        _durationTween = durationTween * _movementBoneData->scale;

        if (loop && _movementBoneData->delay != 0)
        {
            setBetween(_tweenData, tweenNodeTo(updateFrameData(1 - _movementBoneData->delay), _between));

        }
        else
        {
            FrameData *_nextKeyFrame = _movementBoneData->getFrameData(0);
            setBetween(_tweenData, _nextKeyFrame);
            _isTweenKeyFrame = true;
        }
    }
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
                break;
            }
            else
            {
                _nextFrameIndex = _durationTween;
                _currentFrame = _currentPercent * _nextFrameIndex;
                _totalDuration = 0;
                betweenDuration = 0;
                _toIndex = 0;
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
            betweenDuration = 0;
            _toIndex = 0;
        }
        break;
        case ANIMATION_MAX:
        {
            _currentPercent = 1;
            _isComplete = true;
        }
        break;
        default:
        {
            _currentPercent = fmodf(_currentPercent, 1);
            _currentFrame = fmodf(_currentFrame, _nextFrameIndex);

            _totalDuration = 0;
            betweenDuration = 0;
            _toIndex = 0;
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
        percent = updateFrameData(percent, true);
    }

    if(_frameTweenEasing != TWEEN_EASING_MAX)
    {
        tweenNodeTo(percent);
    }
    else if(_currentKeyFrame)
    {
        tweenNodeTo(0);
    }
}

void Tween::setBetween(FrameData *from, FrameData *to)
{
    do
    {
        if(to->displayIndex < 0 && from->displayIndex > 0)
        {
            _from->copy(from);
            _between->subtract(to, to);
            break;
        }
        else if(from->displayIndex < 0 && to->displayIndex > 0)
        {
            _from->copy(to);
            _between->subtract(to, to);
            break;
        }

        _from->copy(from);
        _between->subtract(from, to);
    }
    while (0);

    arriveKeyFrame(from);
}


void Tween::arriveKeyFrame(FrameData *keyFrameData)
{
    if(keyFrameData)
    {
        int displayIndex = keyFrameData->displayIndex;

        if (!_bone->getDisplayManager()->getForceChangeDisplay())
        {
            _bone->getDisplayManager()->changeDisplayByIndex(displayIndex, false);
        }


        _bone->setZOrder(keyFrameData->zOrder);

        Armature *childAramture = _bone->getChildArmature();

        if(childAramture)
        {
            if(keyFrameData->_movement.length() != 0)
            {
                childAramture->getAnimation()->play(keyFrameData->_movement.c_str());
            }
        }

        if(keyFrameData->_event.length() != 0)
        {
            _animation->FrameEventSignal.emit(_bone, keyFrameData->_event.c_str());
        }
        // 		if(keyFrameData->_sound.length() != 0)
        // 		{
        // 			//soundManager.dispatchEventWith(Event.SOUND_FRAME, _currentKeyFrame->sound);
        // 		}
    }
}


FrameData *Tween::tweenNodeTo(float percent, FrameData *node)
{

    node = node == NULL ? _tweenData : node;

    node->x = _from->x + percent * _between->x;
    node->y = _from->y + percent * _between->y;
    node->scaleX = _from->scaleX + percent * _between->scaleX;
    node->scaleY = _from->scaleY + percent * _between->scaleY;
    node->skewX = _from->skewX + percent * _between->skewX;
    node->skewY = _from->skewY + percent * _between->skewY;

    _bone->setTransformDirty(true);

    if(_between->isUseColorInfo)
    {
        node->a = _from->a + percent * _between->a;
        node->r = _from->r + percent * _between->r;
        node->g = _from->g + percent * _between->g;
        node->b = _from->b + percent * _between->b;
        _bone->updateColor();
    }

    //    Point p1 = Point(_from->x, _from->y);
    //    Point p2 = Point(100, 0);
    //    Point p3 = Point(200, 400);
    //    Point p4 = Point(_from->x + _between->x, _from->y + _between->y);
    //
    //    Point p = bezierTo(percent, p1, p2, p3, p4);
    //    node->x = p.x;
    //    node->y = p.y;

    return node;
}

float Tween::updateFrameData(float currentPrecent, bool activeFrame)
{

    float playedTime = (float)_rawDuration * currentPrecent;


    FrameData *from;
    FrameData *to;
    bool isListEnd;

    //! If play to current frame's front or back, then find current frame again
    if (playedTime >= _totalDuration || playedTime < _totalDuration - betweenDuration)
    {
        /*
         *  Get frame length, if _toIndex >= _length, then set _toIndex to 0, start anew.
         *  _toIndex is next index will play
         */
        int length = _movementBoneData->frameList.count();
        do
        {
            betweenDuration = _movementBoneData->getFrameData(_toIndex)->duration;
            _totalDuration += betweenDuration;
            _fromIndex = _toIndex;

            if (++_toIndex >= length)
            {
                _toIndex = 0;
            }
        }
        while (playedTime >= _totalDuration);


        isListEnd = _loopType == ANIMATION_MAX && _toIndex == 0;

        if(isListEnd)
        {
            to = from = _movementBoneData->getFrameData(_fromIndex);
        }
        else
        {
            from = _movementBoneData->getFrameData(_fromIndex);
            to = _movementBoneData->getFrameData(_toIndex);
        }

        _frameTweenEasing = from->tweenEasing;

        setBetween(from, to);

    }
    currentPrecent = 1 - (_totalDuration - playedTime) / (float)betweenDuration;


    /*
     *  If frame tween easing equal to TWEEN_EASING_MAX, then it will not do tween.
     */

    TweenType tweenType;

    if ( _frameTweenEasing != TWEEN_EASING_MAX)
    {
        tweenType = (_tweenEasing == TWEEN_EASING_MAX) ? _frameTweenEasing : _tweenEasing;
        if (tweenType != TWEEN_EASING_MAX)
        {
            currentPrecent = TweenFunction::tweenTo(0, 1, currentPrecent, 1, tweenType);
        }
    }

    return currentPrecent;
}

}}} // namespace cocos2d { namespace extension { namespace armature {
