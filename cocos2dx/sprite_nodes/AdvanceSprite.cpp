//
//  AdvanceSprite.cpp
//  FlyingFreak
//
//  Created by varadharaj on 16/05/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "AdvanceSprite.h"
#include "CCSpriteFrameCache.h"
#include "CCFileUtils.h"
#include "CCString.h"

namespace   cocos2d {
AdvanceSprite::AdvanceSprite()
:m_pfnSelectorDelegate(0)
,m_pTarget(0)
,m_isPlistLoaded(false)
,m_ElaspeTime(0.0)
,m_IncrementValue(0)
,m_isAnimationRunning(false)
{
   
}

AdvanceSprite::~AdvanceSprite()
{
    if(m_isPlistLoaded)
        CC_SAFE_DELETE_ARRAY(m_AnimationFrames);
}

void AdvanceSprite::addFrames(const char *pList)
{
    m_isPlistLoaded = true;
    m_AnimationFrames = new CCMutableArray<CCSpriteFrame *>;
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pList);
    
    const char *pszPath = CCFileUtils::fullPathFromRelativePath(pList);
	CCDictionary<std::string, CCObject*> *dict = CCFileUtils::dictionaryWithContentsOfFile(pszPath);
    CCDictionary<std::string, CCObject*> *framesDict = (CCDictionary<std::string, CCObject*>*)dict->objectForKey(std::string("frames"));
    
    framesDict->begin();
	std::string key = "";
	while((CCDictionary<std::string, CCObject*>*)framesDict->next(&key))
	{
        m_AnimationFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(key.c_str()));
    }
    setDisplayFrame(m_AnimationFrames->getObjectAtIndex(0));
}

void AdvanceSprite::addFrames(const char *pList, const char *textureFileName)
{
    m_isPlistLoaded = true;
    m_AnimationFrames = new CCMutableArray<CCSpriteFrame *>;
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pList, textureFileName);
    
    const char *pszPath = CCFileUtils::fullPathFromRelativePath(pList);
	CCDictionary<std::string, CCObject*> *dict = CCFileUtils::dictionaryWithContentsOfFile(pszPath);
    CCDictionary<std::string, CCObject*> *framesDict = (CCDictionary<std::string, CCObject*>*)dict->objectForKey(std::string("frames"));
    
    framesDict->begin();
	std::string key = "";
	while((CCDictionary<std::string, CCObject*>*)framesDict->next(&key))
	{
        m_AnimationFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(key.c_str()));
    }
    setDisplayFrame(m_AnimationFrames->getObjectAtIndex(0));    
}

void AdvanceSprite::addFrames(CCMutableArray<cocos2d::CCSpriteFrame *> *frames)
{
    m_AnimationFrames = frames;
    setDisplayFrame(m_AnimationFrames->getObjectAtIndex(0));
}

void AdvanceSprite::addFrames(CCMutableArray<cocos2d::CCSpriteFrame *> *frames, int displayTextureIndex)
{
    m_AnimationFrames = frames;
    setDisplayFrame(m_AnimationFrames->getObjectAtIndex(displayTextureIndex));
}

void AdvanceSprite::increaseCurrentIndex()
{
    if(m_AnimationMode && (m_EndingIndex - m_CurrentIndex) != 0)
        m_IncrementValue += (m_EndingIndex - m_CurrentIndex) / abs(m_EndingIndex - m_CurrentIndex);
    else if((m_StartingIndex - m_CurrentIndex) != 0)
        m_IncrementValue += (m_StartingIndex - m_CurrentIndex) / abs(m_StartingIndex - m_CurrentIndex);
}

void AdvanceSprite::update(ccTime dt)
{
    m_ElaspeTime += dt;
    while (m_ElaspeTime >= m_FrameRate) 
    {
        m_ElaspeTime -= m_FrameRate;
        
        m_CurrentIndex += m_IncrementValue;
        setDisplayFrame(m_AnimationFrames->getObjectAtIndex(m_CurrentIndex));
        
         //Forward Animation....
        if (m_CurrentIndex == m_EndingIndex) 
        {
            if(m_NeedToRunReverseAnimation)
            {
                m_AnimationMode = false;
                increaseCurrentIndex();
                return;
            }
            
            m_RunningLoop++;
            if(m_RunningLoop == m_NumberOfLoop)
            {
                stopAnimaiton();
                //Raising Callback.
                if(m_pTarget != 0 && m_pfnSelectorDelegate != 0)
                    (m_pTarget->*m_pfnSelectorDelegate)();
                
                //Remove Object by Itself.
                if(m_NeedToDeleteItself)
                    removeObjectItself();
                return;
            }
            else
            {
                m_CurrentIndex = m_StartingIndex;
            }
        }
        
        //Reverse Animation...
        else if(m_CurrentIndex == m_StartingIndex)
        {
            m_RunningLoop++;
            if(m_RunningLoop == m_NumberOfLoop)
            {
                stopAnimaiton();
                //Raising Callback.
                if(m_pTarget != 0 && m_pfnSelectorDelegate != 0)
                    (m_pTarget->*m_pfnSelectorDelegate)();
                
                //Remove Object by Itself.
                if(m_NeedToDeleteItself)
                    removeObjectItself();
                return;
            }
            else
            {
                m_AnimationMode = true;
                increaseCurrentIndex();
            }
        }
    }
}

void AdvanceSprite::startAnimation(int startInd, int endInd, int number_Loop, SEL_CallFunc pfnSelectorDelegate, cocos2d::SelectorProtocol *pTarget, int NumberOfFramesPerSecond, bool NeedToRunReverseAnimation, bool NeedToDeleteItself)
{
    if(m_isAnimationRunning)
    {
        stopAnimaiton();
        
        //Reset pointer.
        m_pfnSelectorDelegate = 0;
        m_pTarget = 0;
        m_ElaspeTime = 0.0f;
    }
    
    //Assign values.
    m_isAnimationRunning = true;
    
    m_StartingIndex = startInd - 1;
    m_EndingIndex = endInd - 1;
    
    m_NumberOfLoop = number_Loop;
    
    m_pfnSelectorDelegate = pfnSelectorDelegate;
    m_pTarget = pTarget;
    if(NumberOfFramesPerSecond != -1)
        m_FrameRate = calculateFrameRate(NumberOfFramesPerSecond);
    
    //Initilize values....
    m_NeedToRunReverseAnimation = NeedToRunReverseAnimation;
    m_AnimationMode = true;
    m_CurrentIndex = m_StartingIndex;
    m_RunningLoop = 0;
    m_IncrementValue = 0;
    m_NeedToDeleteItself = NeedToDeleteItself;
    increaseCurrentIndex();
    this->scheduleUpdateWithPriority(-1);
    resumeAnimation();
}

void AdvanceSprite::stopAnimaiton()
{
    m_isAnimationRunning = false;
    this->unscheduleUpdate();
}

void AdvanceSprite::removeObjectItself()
{
    this->removeFromParentAndCleanup(true);
    delete (this);
}
}//namespace   cocos2d 