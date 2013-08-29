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


NS_CC_EXT_BEGIN

CCTween *CCTween::create(CCBone *bone)
{
    CCTween *pTween = new CCTween();
    if (pTween && pTween->init(bone))
    {
        pTween->autorelease();
        return pTween;
    }
    CC_SAFE_DELETE(pTween);
    return NULL;

}



CCTween::CCTween()
    : m_pMovementBoneData(NULL)
    , m_pTweenData(NULL)
	, m_pFrom(NULL)
	, m_pTo(NULL)
	, m_pBetween(NULL)
	, m_pCurrentKeyFrame(NULL)
    , m_pBone(NULL)
    
    , m_eFrameTweenEasing(Linear)
    , m_iFromIndex(0)
    , m_iToIndex(0)
    , m_pAnimation(NULL)
{

}


CCTween::~CCTween(void)
{
    CC_SAFE_DELETE( m_pFrom );
    CC_SAFE_DELETE( m_pBetween );
}


bool CCTween::init(CCBone *bone)
{
    bool bRet = false;
    do
    {
        m_pFrom = new CCFrameData();
        m_pBetween = new CCFrameData();

        m_pBone = bone;
        m_pTweenData = m_pBone->getTweenData();

        m_pAnimation = m_pBone->getArmature() != NULL ? m_pBone->getArmature()->getAnimation() : NULL;

        bRet = true;
    }
    while (0);

    return bRet;
}


void CCTween::play(CCMovementBoneData *_movementBoneData, int _durationTo, int _durationTween,  int _loop, int _tweenEasing)
{
    CCProcessBase::play(NULL, _durationTo, _durationTween, _loop, _tweenEasing);

    m_eLoopType = (AnimationType)_loop;

    m_pCurrentKeyFrame = NULL;
    m_bIsTweenKeyFrame = false;

    m_iTotalDuration = 0;
    betweenDuration = 0;
    m_iToIndex = 0;

    setMovementBoneData(_movementBoneData);


    if (m_pMovementBoneData->frameList.count() == 1)
    {
        m_eLoopType = SINGLE_FRAME;
        CCFrameData *_nextKeyFrame = m_pMovementBoneData->getFrameData(0);
        if(_durationTo == 0)
        {
            setBetween(_nextKeyFrame, _nextKeyFrame);
        }
        else
        {
            m_pTweenData->displayIndex = _nextKeyFrame->displayIndex;
            setBetween(m_pTweenData, _nextKeyFrame);
        }
        m_bIsTweenKeyFrame = true;
        m_eFrameTweenEasing = Linear;
        m_iRawDuration = m_pMovementBoneData->duration;
        m_iFromIndex = m_iToIndex = 0;
    }
    else if (m_pMovementBoneData->frameList.count() > 1)
    {
        if (_loop)
        {
            m_eLoopType = ANIMATION_TO_LOOP_BACK;
            m_iRawDuration = m_pMovementBoneData->duration;
        }
        else
        {
            m_eLoopType = ANIMATION_NO_LOOP;
            m_iRawDuration = m_pMovementBoneData->duration - 1;
        }

        m_iDurationTween = _durationTween * m_pMovementBoneData->scale;

        if (_loop && m_pMovementBoneData->delay != 0)
        {
            setBetween(m_pTweenData, tweenNodeTo(updateFrameData(1 - m_pMovementBoneData->delay), m_pBetween));

        }
        else
        {
            CCFrameData *_nextKeyFrame = m_pMovementBoneData->getFrameData(0);
            setBetween(m_pTweenData, _nextKeyFrame);
            m_bIsTweenKeyFrame = true;
        }
    }
}

void CCTween::updateHandler()
{


    if (m_fCurrentPercent >= 1)
    {
        switch(m_eLoopType)
        {
        case SINGLE_FRAME:
        {
            m_fCurrentPercent = 1;
            m_bIsComplete = true;
        }
        break;
        case ANIMATION_NO_LOOP:
        {
            m_eLoopType = ANIMATION_MAX;


            if (m_iDurationTween <= 0)
            {
                m_fCurrentPercent = 1;
            }
            else
            {
                m_fCurrentPercent = (m_fCurrentPercent - 1) * m_iNextFrameIndex / m_iDurationTween;
            }

            if (m_fCurrentPercent >= 1)
            {
                m_fCurrentPercent = 1;
                m_bIsComplete = true;
                break;
            }
            else
            {
                m_iNextFrameIndex = m_iDurationTween;
                m_fCurrentFrame = m_fCurrentPercent * m_iNextFrameIndex;
                m_iTotalDuration = 0;
                betweenDuration = 0;
                m_iToIndex = 0;
                break;
            }
        }
        break;
        case ANIMATION_TO_LOOP_BACK:
        {
            m_eLoopType = ANIMATION_LOOP_BACK;

            m_iNextFrameIndex = m_iDurationTween > 0 ? m_iDurationTween : 1;

            if (m_pMovementBoneData->delay != 0)
            {
                //
                m_fCurrentFrame = (1 - m_pMovementBoneData->delay) * (float)m_iNextFrameIndex;
                m_fCurrentPercent = m_fCurrentFrame / m_iNextFrameIndex;


            }
            else
            {
                m_fCurrentPercent = 0;
                m_fCurrentFrame = 0;
            }

            m_iTotalDuration = 0;
            betweenDuration = 0;
            m_iToIndex = 0;
        }
        break;
        case ANIMATION_MAX:
        {
            m_fCurrentPercent = 1;
            m_bIsComplete = true;
        }
        break;
        default:
        {
            m_fCurrentPercent = fmodf(m_fCurrentPercent, 1);
            m_fCurrentFrame = fmodf(m_fCurrentFrame, m_iNextFrameIndex);

            m_iTotalDuration = 0;
            betweenDuration = 0;
            m_iToIndex = 0;
        }
        break;
        }
    }


    if (m_fCurrentPercent < 1 && m_eLoopType <= ANIMATION_TO_LOOP_BACK)
    {
        m_fCurrentPercent = sin(m_fCurrentPercent * CC_HALF_PI);
    }

    float percent  = m_fCurrentPercent;

    if (m_eLoopType > ANIMATION_TO_LOOP_BACK)
    {
        percent = updateFrameData(percent, true);
    }

    if(m_eFrameTweenEasing != TWEEN_EASING_MAX)
    {
        tweenNodeTo(percent);
    }
    else if(m_pCurrentKeyFrame)
    {
        tweenNodeTo(0);
    }
}

void CCTween::setBetween(CCFrameData *from, CCFrameData *to)
{
    do
    {
        if(to->displayIndex < 0 && from->displayIndex > 0)
        {
            m_pFrom->copy(from);
            m_pBetween->subtract(to, to);
            break;
        }
        else if(from->displayIndex < 0 && to->displayIndex > 0)
        {
            m_pFrom->copy(to);
            m_pBetween->subtract(to, to);
            break;
        }

        m_pFrom->copy(from);
        m_pBetween->subtract(from, to);
    }
    while (0);

    arriveKeyFrame(from);
}


void CCTween::arriveKeyFrame(CCFrameData *keyFrameData)
{
    if(keyFrameData)
    {
        int displayIndex = keyFrameData->displayIndex;

        if (!m_pBone->getDisplayManager()->getForceChangeDisplay())
        {
            m_pBone->getDisplayManager()->changeDisplayByIndex(displayIndex, false);
        }


        m_pBone->setZOrder(keyFrameData->zOrder);

        CCArmature *childAramture = m_pBone->getChildArmature();

        if(childAramture)
        {
            if(keyFrameData->m_strMovement.length() != 0)
            {
                childAramture->getAnimation()->play(keyFrameData->m_strMovement.c_str());
            }
        }

        if(keyFrameData->m_strEvent.length() != 0)
        {
            m_pAnimation->FrameEventSignal.emit(m_pBone, keyFrameData->m_strEvent.c_str());
        }
        // 		if(keyFrameData->m_strSound.length() != 0)
        // 		{
        // 			//soundManager.dispatchEventWith(Event.SOUND_FRAME, m_pCurrentKeyFrame->sound);
        // 		}
    }
}


CCFrameData *CCTween::tweenNodeTo(float percent, CCFrameData *node)
{
    node = node == NULL ? m_pTweenData : node;

    node->x = m_pFrom->x + percent * m_pBetween->x;
    node->y = m_pFrom->y + percent * m_pBetween->y;
    node->scaleX = m_pFrom->scaleX + percent * m_pBetween->scaleX;
    node->scaleY = m_pFrom->scaleY + percent * m_pBetween->scaleY;
    node->skewX = m_pFrom->skewX + percent * m_pBetween->skewX;
    node->skewY = m_pFrom->skewY + percent * m_pBetween->skewY;

    m_pBone->setTransformDirty(true);

    if(m_pBetween->isUseColorInfo)
    {
        node->a = m_pFrom->a + percent * m_pBetween->a;
        node->r = m_pFrom->r + percent * m_pBetween->r;
        node->g = m_pFrom->g + percent * m_pBetween->g;
        node->b = m_pFrom->b + percent * m_pBetween->b;
        m_pBone->updateColor();
    }

    //    CCPoint p1 = ccp(m_pFrom->x, m_pFrom->y);
    //    CCPoint p2 = ccp(100, 0);
    //    CCPoint p3 = ccp(200, 400);
    //    CCPoint p4 = ccp(m_pFrom->x + m_pBetween->x, m_pFrom->y + m_pBetween->y);
    //
    //    CCPoint p = bezierTo(percent, p1, p2, p3, p4);
    //    node->x = p.x;
    //    node->y = p.y;

    return node;
}

float CCTween::updateFrameData(float currentPrecent, bool activeFrame)
{

    float playedTime = (float)m_iRawDuration * currentPrecent;


    CCFrameData *from;
    CCFrameData *to;
    bool isListEnd;

    //! If play to current frame's front or back, then find current frame again
    if (playedTime >= m_iTotalDuration || playedTime < m_iTotalDuration - betweenDuration)
    {
        /*
         *  Get frame length, if m_iToIndex >= _length, then set m_iToIndex to 0, start anew.
         *  m_iToIndex is next index will play
         */
        int length = m_pMovementBoneData->frameList.count();
        do
        {
            betweenDuration = m_pMovementBoneData->getFrameData(m_iToIndex)->duration;
            m_iTotalDuration += betweenDuration;
            m_iFromIndex = m_iToIndex;

            if (++m_iToIndex >= length)
            {
                m_iToIndex = 0;
            }
        }
        while (playedTime >= m_iTotalDuration);


        isListEnd = m_eLoopType == ANIMATION_MAX && m_iToIndex == 0;

        if(isListEnd)
        {
            to = from = m_pMovementBoneData->getFrameData(m_iFromIndex);
        }
        else
        {
            from = m_pMovementBoneData->getFrameData(m_iFromIndex);
            to = m_pMovementBoneData->getFrameData(m_iToIndex);
        }

        m_eFrameTweenEasing = from->tweenEasing;

        setBetween(from, to);

    }
    currentPrecent = 1 - (m_iTotalDuration - playedTime) / (float)betweenDuration;


    /*
     *  If frame tween easing equal to TWEEN_EASING_MAX, then it will not do tween.
     */

    CCTweenType tweenType;

    if ( m_eFrameTweenEasing != TWEEN_EASING_MAX)
    {
        tweenType = (m_eTweenEasing == TWEEN_EASING_MAX) ? m_eFrameTweenEasing : m_eTweenEasing;
        if (tweenType != TWEEN_EASING_MAX)
        {
            currentPrecent = CCTweenFunction::tweenTo(0, 1, currentPrecent, 1, tweenType);
        }
    }

    return currentPrecent;
}

NS_CC_EXT_END
