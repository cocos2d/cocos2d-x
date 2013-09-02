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
    : m_fProcessScale(1)
    , m_bIsPause(true)
    , m_bIsComplete(true)
    , m_bIsPlaying(false)
    , m_fCurrentPercent(0.0f)
    , m_iRawDuration(0)
    , m_eLoopType(ANIMATION_LOOP_BACK)
    , m_eTweenEasing(Linear)
    , m_iDurationTween(0)
    , m_fCurrentFrame(0)
    , m_iCurFrameIndex(0)
    , m_bIsLoopBack(false)
{
    /*
     *  set m_fAnimationInternal defualt value to CCDirector::sharedDirector()
     *  ->getAnimationInterval(), in line with game update speed
     */
    m_fAnimationInternal = CCDirector::sharedDirector()->getAnimationInterval();
}


CCProcessBase::~CCProcessBase(void)
{
}


void CCProcessBase::pause()
{
    m_bIsPause = true;
    m_bIsPlaying = false;
}


void CCProcessBase::resume()
{
    m_bIsPause = false;
    m_bIsPlaying = true;
}

void CCProcessBase::stop()
{
    m_bIsComplete = true;
    m_bIsPlaying = false;
    m_fCurrentFrame = 0;
    m_fCurrentPercent = 0;
}

void CCProcessBase::play(void *animation, int durationTo, int durationTween,  int loop, int tweenEasing)
{
    m_bIsComplete = false;
    m_bIsPause = false;
    m_bIsPlaying = true;
    m_fCurrentFrame = 0;

    /*
     *  Set m_iTotalFrames to durationTo, it is used for change tween between two animation.
     *  When changing end, m_iTotalFrames will be setted to _durationTween
     */
    m_iNextFrameIndex = durationTo;
    m_eTweenEasing = (CCTweenType)tweenEasing;

}

void CCProcessBase::update(float dt)
{

    if (m_bIsComplete || m_bIsPause)
    {
        return;
    }

    /*
     *  Fileter the m_iDuration <=0 and dt >1
     *  If dt>1, generally speaking  the reason is the device is stuck.
     */
    if(m_iRawDuration <= 0 || dt > 1)
    {
        return;
    }

    if (m_iNextFrameIndex <= 0)
    {
        m_fCurrentPercent = 1;
        m_fCurrentFrame = 0;
    }
    else
    {
        /*
        *  update m_fCurrentFrame, every update add the frame passed.
        *  dt/m_fAnimationInternal determine it is not a frame animation. If frame speed changed, it will not make our
        *  animation speed slower or quicker.
        */
        m_fCurrentFrame += m_fProcessScale * (dt / m_fAnimationInternal);


        m_fCurrentPercent = m_fCurrentFrame / m_iNextFrameIndex;

        /*
        *	if m_fCurrentFrame is bigger or equal than m_iTotalFrames, then reduce it util m_fCurrentFrame is
        *  smaller than m_iTotalFrames
        */
        m_fCurrentFrame = fmodf(m_fCurrentFrame, m_iNextFrameIndex);
    }

    updateHandler();
}



void CCProcessBase::gotoFrame(int frameIndex)
{
    m_iCurFrameIndex = frameIndex;
    pause();
}

int CCProcessBase::getCurrentFrameIndex()
{
    m_iCurFrameIndex = m_iRawDuration * m_fCurrentPercent;
    return m_iCurFrameIndex;
}

NS_CC_EXT_END
