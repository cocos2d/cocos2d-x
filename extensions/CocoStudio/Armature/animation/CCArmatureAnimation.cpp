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
    : m_pAnimationData(NULL)
    , m_fSpeedScale(1)
    , m_pMovementData(NULL)
    , m_pArmature(NULL)
    , m_strMovementID("")
    , m_iToIndex(0)

    , m_sMovementEventCallFunc(NULL)
    , m_sFrameEventCallFunc(NULL)
    , m_sMovementEventTarget(NULL)
    , m_sFrameEventTarget(NULL)
{

}

ArmatureAnimation::~ArmatureAnimation(void)
{
    CC_SAFE_RELEASE_NULL(m_pTweenList);
    CC_SAFE_RELEASE_NULL(m_pAnimationData);

    CC_SAFE_RELEASE_NULL(m_sMovementEventTarget);
    CC_SAFE_RELEASE_NULL(m_sFrameEventTarget);
}

bool ArmatureAnimation::init(Armature *armature)
{
    bool bRet = false;
    do
    {
        m_pArmature = armature;

        m_pTweenList = new Array();
        m_pTweenList->init();

        bRet = true;
    }
    while (0);

    return bRet;
}


void ArmatureAnimation:: pause()
{
    Object *object = NULL;
    CCARRAY_FOREACH(m_pTweenList, object)
    {
        ((Tween *)object)->pause();
    }
    ProcessBase::pause();
}

void ArmatureAnimation::resume()
{
    Object *object = NULL;
    CCARRAY_FOREACH(m_pTweenList, object)
    {
        ((Tween *)object)->resume();
    }
    ProcessBase::resume();
}

void ArmatureAnimation::stop()
{
    Object *object = NULL;
    CCARRAY_FOREACH(m_pTweenList, object)
    {
        ((Tween *)object)->stop();
    }
    m_pTweenList->removeAllObjects();
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
    if(speedScale == m_fSpeedScale)
    {
        return;
    }

    m_fSpeedScale = speedScale;

    m_fProcessScale = !m_pMovementData ? m_fSpeedScale : m_fSpeedScale * m_pMovementData->scale;

    DictElement *element = NULL;
    Dictionary *dict = m_pArmature->getBoneDic();
    CCDICT_FOREACH(dict, element)
    {
        Bone *bone = (Bone *)element->getObject();

        bone->getTween()->setProcessScale(m_fProcessScale);
        if (bone->getChildArmature())
        {
            bone->getChildArmature()->getAnimation()->setProcessScale(m_fProcessScale);
        }
    }
}

float ArmatureAnimation::getSpeedScale() const
{
    return m_fSpeedScale;
}

void ArmatureAnimation::setAnimationInternal(float animationInternal)
{
    if(animationInternal == m_fAnimationInternal)
    {
        return;
    }

    m_fAnimationInternal = animationInternal;

    DictElement *element = NULL;
    Dictionary *dict = m_pArmature->getBoneDic();
    CCDICT_FOREACH(dict, element)
    {
        Bone *bone = (Bone *)element->getObject();
        bone->getTween()->setAnimationInternal(m_fAnimationInternal);
        if (bone->getChildArmature())
        {
            bone->getChildArmature()->getAnimation()->setAnimationInternal(m_fAnimationInternal);
        }
    }
}


void ArmatureAnimation::play(const char *animationName, int durationTo, int durationTween,  int loop, int tweenEasing)
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


    ProcessBase::play((void *)animationName, durationTo, durationTween, loop, tweenEasing);


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
            m_iRawDuration --;
        }
        m_iDurationTween = durationTween;
    }

    MovementBoneData *movementBoneData = NULL;
    m_pTweenList->removeAllObjects();

    DictElement *element = NULL;
    Dictionary *dict = m_pArmature->getBoneDic();

    CCDICT_FOREACH(dict, element)
    {
        Bone *bone = (Bone *)element->getObject();
        movementBoneData = (MovementBoneData *)m_pMovementData->movBoneDataDic.objectForKey(bone->getName());

        Tween *tween = bone->getTween();
        if(movementBoneData && movementBoneData->frameList.count() > 0)
        {
            m_pTweenList->addObject(tween);
            movementBoneData->duration = m_pMovementData->duration;
            tween->play(movementBoneData, durationTo, durationTween, loop, tweenEasing);

            tween->setProcessScale(m_fProcessScale);
            tween->setAnimationInternal(m_fAnimationInternal);

            if (bone->getChildArmature())
            {
                bone->getChildArmature()->getAnimation()->setProcessScale(m_fProcessScale);
                bone->getChildArmature()->getAnimation()->setAnimationInternal(m_fAnimationInternal);
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
    std::vector<std::string> &movName = m_pAnimationData->movementNames;
    CC_ASSERT((animationIndex > -1) && ((unsigned int)animationIndex < movName.size()));

    std::string animationName = movName.at(animationIndex);
    play(animationName.c_str(), durationTo, durationTween, loop, tweenEasing);
}



int ArmatureAnimation::getMovementCount()
{
    return m_pAnimationData->getMovementCount();
}

void ArmatureAnimation::update(float dt)
{
    ProcessBase::update(dt);
    Object *object = NULL;
    CCARRAY_FOREACH(m_pTweenList, object)
    {
        ((Tween *)object)->update(dt);
    }
}

void ArmatureAnimation::updateHandler()
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
                    (m_sMovementEventTarget->*m_sMovementEventCallFunc)(m_pArmature, START, m_strMovementID.c_str());
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
                (m_sMovementEventTarget->*m_sMovementEventCallFunc)(m_pArmature, COMPLETE, m_strMovementID.c_str());
            }
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
                (m_sMovementEventTarget->*m_sMovementEventCallFunc)(m_pArmature, START, m_strMovementID.c_str());
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
                (m_sMovementEventTarget->*m_sMovementEventCallFunc)(m_pArmature, LOOP_COMPLETE, m_strMovementID.c_str());
            }
        }
        break;
        }
    }
}

std::string ArmatureAnimation::getCurrentMovementID()
{
    if (m_bIsComplete)
    {
        return "";
    }
    return m_strMovementID;
}

void ArmatureAnimation::setMovementEventCallFunc(Object *target, SEL_MovementEventCallFunc callFunc)
{
    if (target != m_sMovementEventTarget)
    {
        CC_SAFE_RETAIN(target);
        CC_SAFE_RELEASE_NULL(m_sMovementEventTarget);
        m_sMovementEventTarget = target;
    }
    m_sMovementEventCallFunc = callFunc;
}

void ArmatureAnimation::setFrameEventCallFunc(Object *target, SEL_FrameEventCallFunc callFunc)
{
    if (target != m_sFrameEventTarget)
    {
        CC_SAFE_RETAIN(target);
        CC_SAFE_RELEASE_NULL(m_sFrameEventTarget);
        m_sFrameEventTarget = target;
    }
    m_sFrameEventCallFunc = callFunc;
}

void ArmatureAnimation::frameEvent(Bone *bone, const char *frameEventName, int originFrameIndex, int currentFrameIndex)
{
    if (m_sFrameEventTarget && m_sFrameEventCallFunc)
    {
        (m_sFrameEventTarget->*m_sFrameEventCallFunc)(bone, frameEventName, originFrameIndex, currentFrameIndex);
    }
}
NS_CC_EXT_ARMATURE_END
