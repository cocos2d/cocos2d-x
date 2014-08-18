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
    : m_pAnimationData(NULL)
    , m_fSpeedScale(1)
    , m_pMovementData(NULL)
    , m_pArmature(NULL)
    , m_strMovementID("")
    , m_iToIndex(0)
    , m_pTweenList(NULL)
    , m_bIgnoreFrameEvent(false)
    , m_bOnMovementList(false)
    , m_bMovementListLoop(false)
    , m_iMovementListDurationTo(-1)
    , m_pUserObject(NULL)

    , m_sMovementEventCallFunc(NULL)
    , m_sFrameEventCallFunc(NULL)
    , m_sMovementEventTarget(NULL)
    , m_sFrameEventTarget(NULL)
    , m_pScriptObjectDict(NULL)
{

}

CCArmatureAnimation::~CCArmatureAnimation(void)
{
    CC_SAFE_RELEASE_NULL(m_pTweenList);
    CC_SAFE_RELEASE_NULL(m_pAnimationData);

    CC_SAFE_RELEASE_NULL(m_pUserObject);
    CC_SAFE_RELEASE_NULL(m_pScriptObjectDict);

}

bool CCArmatureAnimation::init(CCArmature *armature)
{
    bool bRet = false;
    do
    {
        m_pArmature = armature;

        m_pTweenList = new CCArray();
        m_pTweenList->init();

        bRet = true;
    }
    while (0);

    return bRet;
}


void CCArmatureAnimation:: pause()
{
    CCObject *object = NULL;
    CCARRAY_FOREACH(m_pTweenList, object)
    {
        ((CCTween *)object)->pause();
    }
    CCProcessBase::pause();
}

void CCArmatureAnimation::resume()
{
    CCObject *object = NULL;
    CCARRAY_FOREACH(m_pTweenList, object)
    {
        ((CCTween *)object)->resume();
    }
    CCProcessBase::resume();
}

void CCArmatureAnimation::stop()
{
    CCObject *object = NULL;
    CCARRAY_FOREACH(m_pTweenList, object)
    {
        ((CCTween *)object)->stop();
    }
    m_pTweenList->removeAllObjects();
    CCProcessBase::stop();
}

void CCArmatureAnimation::setAnimationScale(float animationScale )
{
    setSpeedScale(animationScale);
}

float CCArmatureAnimation::getAnimationScale() const
{
    return getSpeedScale();
}


void CCArmatureAnimation::setSpeedScale(float speedScale)
{
    if(speedScale == m_fSpeedScale)
    {
        return;
    }

    m_fSpeedScale = speedScale;

    m_fProcessScale = !m_pMovementData ? m_fSpeedScale : m_fSpeedScale * m_pMovementData->scale;

    CCDictElement *element = NULL;
    CCDictionary *dict = m_pArmature->getBoneDic();
    CCDICT_FOREACH(dict, element)
    {
        CCBone *bone = (CCBone *)element->getObject();

        bone->getTween()->setProcessScale(m_fProcessScale);
        if (bone->getChildArmature())
        {
            bone->getChildArmature()->getAnimation()->setSpeedScale(m_fProcessScale);
        }
    }
}

float CCArmatureAnimation::getSpeedScale() const
{
    return m_fSpeedScale;
}


void CCArmatureAnimation::play(const char *animationName, int durationTo, int durationTween,  int loop, int tweenEasing)
{
    CCAssert(m_pAnimationData, "m_pAnimationData can not be null");

    m_pMovementData = m_pAnimationData->getMovement(animationName);
    CCAssert(m_pMovementData, "m_pMovementData can not be null");

    //! Get key frame count
    m_iRawDuration = m_pMovementData->duration;

    m_strMovementID = animationName;

    m_fProcessScale = m_fSpeedScale * m_pMovementData->scale;

    //! Further processing parameters
    durationTo = (durationTo == -1) ? m_pMovementData->durationTo : durationTo;

    durationTween = (durationTween == -1) ? m_pMovementData->durationTween : durationTween;
    durationTween = (durationTween == 0) ? m_pMovementData->duration : durationTween;

    tweenEasing	= (tweenEasing == TWEEN_EASING_MAX) ? m_pMovementData->tweenEasing : tweenEasing;
    loop = (loop < 0) ? m_pMovementData->loop : loop;

    m_bOnMovementList = false;

    CCProcessBase::play(durationTo, durationTween, loop, tweenEasing);


    if (m_iRawDuration == 0)
    {
        m_eLoopType = SINGLE_FRAME;
    }
    else
    {
        if (loop)
        {
            m_eLoopType = ANIMATION_TO_LOOP_FRONT;
        }
        else
        {
            m_eLoopType = ANIMATION_NO_LOOP;
        }
        m_iDurationTween = durationTween;
    }

    CCMovementBoneData *movementBoneData = NULL;
    m_pTweenList->removeAllObjects();

    CCDictElement *element = NULL;
    CCDictionary *dict = m_pArmature->getBoneDic();

    CCDICT_FOREACH(dict, element)
    {
        CCBone *bone = (CCBone *)element->getObject();
        movementBoneData = (CCMovementBoneData *)m_pMovementData->movBoneDataDic.objectForKey(bone->getName());

        CCTween *tween = bone->getTween();
        if(movementBoneData && movementBoneData->frameList.count() > 0)
        {
            m_pTweenList->addObject(tween);
            movementBoneData->duration = m_pMovementData->duration;
            tween->play(movementBoneData, durationTo, durationTween, loop, tweenEasing);

            tween->setProcessScale(m_fProcessScale);

            if (bone->getChildArmature())
            {
                bone->getChildArmature()->getAnimation()->setSpeedScale(m_fProcessScale);
            }
        }
        else
        {
            if(!bone->getIgnoreMovementBoneData())
            {
                //! this bone is not include in this movement, so hide it
                bone->getDisplayManager()->changeDisplayWithIndex(-1, false);
                tween->stop();
            }

        }
    }

    m_pArmature->update(0);
}

void CCArmatureAnimation::playByIndex(int animationIndex, int durationTo, int durationTween,  int loop, int tweenEasing)
{
    playWithIndex(animationIndex, durationTo, durationTween, loop, tweenEasing);
}

void CCArmatureAnimation::playWithIndex(int animationIndex, int durationTo, int durationTween,  int loop, int tweenEasing)
{
    std::vector<std::string> &movName = m_pAnimationData->movementNames;
    CC_ASSERT((animationIndex > -1) && ((unsigned int)animationIndex < movName.size()));

    std::string animationName = movName.at(animationIndex);
    play(animationName.c_str(), durationTo, durationTween, loop, tweenEasing);
}


void CCArmatureAnimation::playWithNames(const std::vector<std::string>& movementNames, int durationTo, bool loop)
{
    m_sMovementList.clear();
    m_bMovementListLoop = loop;
    m_iMovementListDurationTo = durationTo;
    m_bOnMovementList = true;
    m_uMovementIndex = 0;

    m_sMovementList = movementNames;

    updateMovementList();
}

void CCArmatureAnimation::playWithIndexes(const std::vector<int>& movementIndexes, int durationTo, bool loop)
{
    m_sMovementList.clear();
    m_bMovementListLoop = loop;
    m_iMovementListDurationTo = durationTo;
    m_bOnMovementList = true;
    m_uMovementIndex = 0;

    std::vector<std::string> &movName = m_pAnimationData->movementNames;

    for (size_t i = 0; i<movementIndexes.size(); i++)
    {
        std::string name = movName.at(movementIndexes[i]);
        m_sMovementList.push_back(name);
    }

    updateMovementList();
}

void CCArmatureAnimation::playWithArray(CCArray *movementNames, int durationTo, bool loop)
{
    std::vector<std::string> names;
    
    CCObject *object = NULL;
    CCARRAY_FOREACH(movementNames, object)
    {
        names.push_back(static_cast<CCString*>(object)->getCString());
    }
    playWithNames(names, durationTo, loop);
}

void CCArmatureAnimation::playWithIndexArray(CCArray *movementIndexes, int durationTo, bool loop)
{
    std::vector<int> indexes;

    CCObject *object = NULL;
    CCARRAY_FOREACH(movementIndexes, object)
    {
        indexes.push_back(static_cast<CCInteger*>(object)->getValue());
    }
    playWithIndexes(indexes, durationTo, loop);
}

void CCArmatureAnimation::gotoAndPlay(int frameIndex)
{
    if (!m_pMovementData || frameIndex < 0 || frameIndex >= m_pMovementData->duration)
    {
        CCLOG("Please ensure you have played a movement, and the frameIndex is in the range.");
        return;
    }

    bool ignoreFrameEvent = m_bIgnoreFrameEvent;
    m_bIgnoreFrameEvent = true;

    m_bIsPlaying = true;
    m_bIsComplete = m_bIsPause = false;

    CCProcessBase::gotoFrame(frameIndex);
    m_fCurrentPercent = (float)m_iCurFrameIndex / ((float)m_pMovementData->duration - 1);
    m_fCurrentFrame = m_iNextFrameIndex * m_fCurrentPercent;

    CCObject *object = NULL;
    CCARRAY_FOREACH(m_pTweenList, object)
    {
        ((CCTween *)object)->gotoAndPlay(frameIndex);
    }

    m_pArmature->update(0);

    m_bIgnoreFrameEvent = ignoreFrameEvent;
}

void CCArmatureAnimation::gotoAndPause(int frameIndex)
{
    gotoAndPlay(frameIndex);
    pause();
}

int CCArmatureAnimation::getMovementCount()
{
    return m_pAnimationData->getMovementCount();
}

void CCArmatureAnimation::update(float dt)
{
    CCProcessBase::update(dt);
    CCObject *object = NULL;
    CCARRAY_FOREACH(m_pTweenList, object)
    {
        ((CCTween *)object)->update(dt);
    }

    while (m_sFrameEventQueue.size() > 0)
    {
        CCFrameEvent *event = m_sFrameEventQueue.front();
        m_sFrameEventQueue.pop();

        m_bIgnoreFrameEvent = true;
        (m_sFrameEventTarget->*m_sFrameEventCallFunc)(event->bone, event->frameEventName, event->originFrameIndex, event->currentFrameIndex);
        m_bIgnoreFrameEvent = false;

        CC_SAFE_DELETE(event);
    }

    while (m_sMovementEventQueue.size() > 0)
    {
        CCMovementEvent *event = m_sMovementEventQueue.front();
        m_sMovementEventQueue.pop();

        (m_sMovementEventTarget->*m_sMovementEventCallFunc)(event->armature, event->movementType, event->movementID);

        CC_SAFE_DELETE(event);
    }
}

void CCArmatureAnimation::updateHandler()
{
    if (m_fCurrentPercent >= 1)
    {
        switch(m_eLoopType)
        {
        case ANIMATION_NO_LOOP:
        {
            m_eLoopType = ANIMATION_MAX;
            m_fCurrentFrame = (m_fCurrentPercent - 1) * m_iNextFrameIndex;
            m_fCurrentPercent = m_fCurrentFrame / m_iDurationTween;

            if (m_fCurrentPercent >= 1.0f)
            {
            }
            else
            {
                m_iNextFrameIndex = m_iDurationTween;

                if (m_sMovementEventTarget && m_sMovementEventCallFunc)
                {
                    movementEvent(m_pArmature, START, m_strMovementID.c_str());
                }

                break;
            }
        }
        break;
        case ANIMATION_MAX:
        case SINGLE_FRAME:
        {
            m_fCurrentPercent = 1;
            m_bIsComplete = true;
            m_bIsPlaying = false;

            if (m_sMovementEventTarget && m_sMovementEventCallFunc)
            {
                movementEvent(m_pArmature, COMPLETE, m_strMovementID.c_str());
            }

            updateMovementList();
        }
        break;
        case ANIMATION_TO_LOOP_FRONT:
        {
            m_eLoopType = ANIMATION_LOOP_FRONT;
            m_fCurrentPercent = fmodf(m_fCurrentPercent, 1);
            m_fCurrentFrame = m_iNextFrameIndex == 0 ? 0 : fmodf(m_fCurrentFrame, m_iNextFrameIndex);
            m_iNextFrameIndex = m_iDurationTween > 0 ? m_iDurationTween : 1;

            if (m_sMovementEventTarget && m_sMovementEventCallFunc)
            {
                movementEvent(m_pArmature, START, m_strMovementID.c_str());
            }
        }
        break;
        default:
        {
            //m_fCurrentPercent = fmodf(m_fCurrentPercent, 1);
            m_fCurrentFrame = fmodf(m_fCurrentFrame, m_iNextFrameIndex);
            m_iToIndex = 0;

            if (m_sMovementEventTarget && m_sMovementEventCallFunc)
            {
                movementEvent(m_pArmature, LOOP_COMPLETE, m_strMovementID.c_str());
            }
        }
        break;
        }
    }
}

std::string CCArmatureAnimation::getCurrentMovementID()
{
    if (m_bIsComplete)
    {
        return "";
    }
    return m_strMovementID;
}

void CCArmatureAnimation::setMovementEventCallFunc(CCObject *target, SEL_MovementEventCallFunc callFunc)
{
    m_sMovementEventTarget = target;
    m_sMovementEventCallFunc = callFunc;
}

void CCArmatureAnimation::setFrameEventCallFunc(CCObject *target, SEL_FrameEventCallFunc callFunc)
{
    m_sFrameEventTarget = target;
    m_sFrameEventCallFunc = callFunc;
}

void CCArmatureAnimation::setUserObject(CCObject *pUserObject)
{
    CC_SAFE_RETAIN(pUserObject);
    CC_SAFE_RELEASE(m_pUserObject);
    m_pUserObject = pUserObject;
}

CCObject* CCArmatureAnimation::getUserObject()
{
    return m_pUserObject;
}

void CCArmatureAnimation::frameEvent(CCBone *bone, const char *frameEventName, int originFrameIndex, int currentFrameIndex)
{
    if (m_sFrameEventTarget && m_sFrameEventCallFunc)
    {
        CCFrameEvent *frameEvent = new CCFrameEvent();
        frameEvent->bone = bone;
        frameEvent->frameEventName = frameEventName;
        frameEvent->originFrameIndex = originFrameIndex;
        frameEvent->currentFrameIndex = currentFrameIndex;

        m_sFrameEventQueue.push(frameEvent);
    }
}

void CCArmatureAnimation::movementEvent(CCArmature *armature, MovementEventType movementType, const char *movementID)
{
    if (m_sMovementEventTarget && m_sMovementEventCallFunc)
    {
        CCMovementEvent *movementEvent = new CCMovementEvent();
        movementEvent->armature = armature;
        movementEvent->movementType = movementType;
        movementEvent->movementID = movementID;

        m_sMovementEventQueue.push(movementEvent);
    }
}

void CCArmatureAnimation::updateMovementList()
{
    if (m_bOnMovementList)
    {
        if (m_bMovementListLoop)
        {
            play(m_sMovementList.at(m_uMovementIndex).c_str(), m_iMovementListDurationTo, -1, 0);
            m_uMovementIndex++;
            if (m_uMovementIndex >= m_sMovementList.size())
            {
                m_uMovementIndex = 0;
            }
        }
        else
        {
            if (m_uMovementIndex < m_sMovementList.size())
            {
                play(m_sMovementList.at(m_uMovementIndex).c_str(), m_iMovementListDurationTo, -1, 0);
                m_uMovementIndex++;
            }
            else
            {
                m_bOnMovementList = false;
            }
        }

        m_bOnMovementList = true;
    }
}

cocos2d::CCDictionary * CCArmatureAnimation::getScriptObjectDict()
{
    return m_pScriptObjectDict;
}
void CCArmatureAnimation::setScriptObjectDict(cocos2d::CCDictionary* pScriptObjectDict)
{
    CC_SAFE_RETAIN(pScriptObjectDict);
    CC_SAFE_RELEASE(m_pScriptObjectDict);
    m_pScriptObjectDict = pScriptObjectDict;
}

NS_CC_EXT_END
