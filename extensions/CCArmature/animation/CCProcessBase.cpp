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

#include "CCProcessBase.h"
#include "../utils/CCUtilMath.h"

NS_CC_EXT_BEGIN

CCProcessBase::CCProcessBase(void)
    : _animationScale(1)
    , _isPause(true)
    , _isComplete(true)
	, _isPlaying(false)
	, _currentPercent(0.0f)
	, _rawDuration(0)
	, _loopType(ANIMATION_LOOP_BACK)
	, _tweenEasing(Linear)
	, _durationTween(0)
    , _currentFrame(0)
    , _curFrameIndex(0)
    , _isLoopBack(false)
{
    /*
     *  set _animationInternal defualt value to CCDirector::sharedDirector()
     *  ->getAnimationInterval(), in line with game update speed
     */
    _animationInternal = CCDirector::sharedDirector()->getAnimationInterval();
}


CCProcessBase::~CCProcessBase(void)
{
}


void CCProcessBase::pause()
{
    _isPause = true;
}


void CCProcessBase::resume()
{
    _isPause = false;
}

void CCProcessBase::stop()
{
    _isComplete = true;
    _currentFrame = 0;
    _currentPercent = 0;
}

void CCProcessBase::play(void *animation, int durationTo, int durationTween,  int loop, int tweenEasing)
{
    _isComplete = false;
    _isPause = false;
    _isPlaying = true;
    _currentFrame = 0;

    /*
     *  Set _totalFrames to durationTo, it is used for change tween between two animation.
     *  When changing end, _totalFrames will be setted to _durationTween
     */
    _nextFrameIndex = durationTo;
    _tweenEasing = (CCTweenType)tweenEasing;

}

void CCProcessBase::update(float dt)
{

    if (_isComplete || _isPause)
    {
        return;
    }

    /*
     *  Fileter the _duration <=0 and dt >1
     *  If dt>1, generally speaking  the reason is the device is stuck.
     */
    if(_rawDuration <= 0 || dt > 1)
    {
        return;
    }

    if (_nextFrameIndex <= 0)
    {
        _currentFrame = _nextFrameIndex = 1;
    }

    /*
     *  update _currentFrame, every update add the frame passed.
     *  dt/_animationInternal determine it is not a frame animation. If frame speed changed, it will not make our
     *  animation speed slower or quicker.
     */
    _currentFrame += _animationScale * (dt / _animationInternal);


    _currentPercent = _currentFrame / _nextFrameIndex;

    /*
     *	if _currentFrame is bigger or equal than _totalFrames, then reduce it util _currentFrame is
     *  smaller than _totalFrames
     */
    _currentFrame = fmodf(_currentFrame, _nextFrameIndex);

    updateHandler();
}



void CCProcessBase::gotoFrame(int frameIndex)
{
    _curFrameIndex = frameIndex;
    stop();
}

int CCProcessBase::getCurrentFrameIndex()
{
    return _curFrameIndex;
}

NS_CC_EXT_END
