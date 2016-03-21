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

#include "editor-support/cocostudio/CCProcessBase.h"
#include "editor-support/cocostudio/CCUtilMath.h"

using namespace cocos2d;

namespace cocostudio {

ProcessBase::ProcessBase(void)
    : _processScale(1)
    , _isPause(true)
    , _isComplete(true)
    , _isPlaying(false)
    , _currentPercent(0.0f)
    , _rawDuration(0)
    , _loopType(ANIMATION_LOOP_BACK)
    , _tweenEasing(cocos2d::tweenfunc::Linear)
    , _animationInternal(1/60.0f)
    , _durationTween(0)
    , _currentFrame(0)
    , _curFrameIndex(0)
    , _isLoopBack(false)
{
}


ProcessBase::~ProcessBase(void)
{
}


void ProcessBase::pause()
{
    _isPause = true;
    _isPlaying = false;
}


void ProcessBase::resume()
{
    _isPause = false;
    _isPlaying = true;
}

void ProcessBase::stop()
{
    _isComplete = true;
    _isPlaying = false;
}

void ProcessBase::play(int durationTo, int durationTween,  int loop, int tweenEasing)
{
    _isComplete = false;
    _isPause = false;
    _isPlaying = true;
    _currentFrame = 0;

    /*
     *  Set m_iTotalFrames to durationTo, it is used for change tween between two animation.
     *  When changing end, m_iTotalFrames will be set to _durationTween
     */
    _nextFrameIndex = durationTo;
    _tweenEasing = (cocos2d::tweenfunc::TweenType)tweenEasing;

}

void ProcessBase::update(float dt)
{

    if (_isComplete || _isPause)
    {
        return;
    }

    /*
     *  Filter the m_iDuration <=0 and dt >1
     *  If dt>1, generally speaking  the reason is the device is stuck.
     */
    if(_rawDuration <= 0 || dt > 1)
    {
        return;
    }

    if (_nextFrameIndex <= 0)
    {
        _currentPercent = 1;
        _currentFrame = 0;
    }
    else
    {
        /*
        *  update _currentFrame, every update add the frame passed.
        *  dt/_animationInternal determine it is not a frame animation. If frame speed changed, it will not make our
        *  animation speed slower or quicker.
        */
        _currentFrame += _processScale * (dt / _animationInternal);


        _currentPercent = _currentFrame / _nextFrameIndex;

        /*
        *	if _currentFrame is bigger or equal than m_iTotalFrames, then reduce it until _currentFrame is
        *  smaller than m_iTotalFrames
        */
        _currentFrame = fmodf(_currentFrame, _nextFrameIndex);
    }

    updateHandler();
}



void ProcessBase::gotoFrame(int frameIndex)
{
    if (_loopType == ANIMATION_NO_LOOP)
    {
        _loopType = ANIMATION_MAX;
    }
    else if (_loopType == ANIMATION_TO_LOOP_FRONT)
    {
        _loopType = ANIMATION_LOOP_FRONT;
    }

    _curFrameIndex = frameIndex;
    
    _nextFrameIndex = _durationTween;
}

int ProcessBase::getCurrentFrameIndex()
{
    _curFrameIndex = (_rawDuration-1) * _currentPercent;
    return _curFrameIndex;
}

}
