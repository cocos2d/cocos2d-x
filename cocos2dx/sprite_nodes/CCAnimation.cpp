/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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
#include "CCAnimation.h"
#include "textures/CCTextureCache.h"
#include "textures/CCTexture2D.h"
#include "ccMacros.h"
#include "sprite_nodes/CCSpriteFrame.h"
#include "cocoa/CCZone.h"

NS_CC_BEGIN

CCAnimationFrame::CCAnimationFrame()
: m_pSpriteFrame(NULL)
, m_fDelayUnits(0.0f)
, m_pUserInfo(NULL)
{

}

bool CCAnimationFrame::initWithSpriteFrame(CCSpriteFrame* spriteFrame, float delayUnits, CCDictionary* userInfo)
{
    setSpriteFrame(spriteFrame);
    setDelayUnits(delayUnits);
    setUserInfo(userInfo);

    return true;
}

CCAnimationFrame::~CCAnimationFrame()
{    
    CCLOGINFO( "cocos2d: deallocing %s", this);

    CC_SAFE_RELEASE(m_pSpriteFrame);
    CC_SAFE_RELEASE(m_pUserInfo);
}

CCObject* CCAnimationFrame::copyWithZone(CCZone* pZone)
{
    CCZone* pNewZone = NULL;
    CCAnimationFrame* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCAnimationFrame*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCAnimationFrame();
        pNewZone = new CCZone(pCopy);
    }

    pCopy->initWithSpriteFrame((CCSpriteFrame*)m_pSpriteFrame->copy()->autorelease(),
        m_fDelayUnits, m_pUserInfo != NULL ? (CCDictionary*)m_pUserInfo->copy()->autorelease() : NULL);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

// implementation of CCAnimation

CCAnimation* CCAnimation::create(void)
{
    CCAnimation *pAnimation = new CCAnimation();
    pAnimation->init();
    pAnimation->autorelease();

    return pAnimation;
} 

CCAnimation* CCAnimation::createWithSpriteFrames(CCArray *frames, float delay/* = 0.0f*/)
{
    CCAnimation *pAnimation = new CCAnimation();
    pAnimation->initWithSpriteFrames(frames, delay);
    pAnimation->autorelease();

    return pAnimation;
}

CCAnimation* CCAnimation::create(CCArray* arrayOfAnimationFrameNames, float delayPerUnit, unsigned int loops)
{
    CCAnimation *pAnimation = new CCAnimation();
    pAnimation->initWithAnimationFrames(arrayOfAnimationFrameNames, delayPerUnit, loops);
    pAnimation->autorelease();
    return pAnimation;
}

bool CCAnimation::init()
{
    return initWithSpriteFrames(NULL, 0.0f);
}

bool CCAnimation::initWithSpriteFrames(CCArray *pFrames, float delay/* = 0.0f*/)
{
    CCARRAY_VERIFY_TYPE(pFrames, CCSpriteFrame*);

    m_uLoops = 1;
    m_fDelayPerUnit = delay;
    CCArray* pTmpFrames = CCArray::create();
    setFrames(pTmpFrames);

    if (pFrames != NULL)
    {
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(pFrames, pObj)
        {
            CCSpriteFrame* frame = (CCSpriteFrame*)pObj;
            CCAnimationFrame *animFrame = new CCAnimationFrame();
            animFrame->initWithSpriteFrame(frame, 1, NULL);
            m_pFrames->addObject(animFrame);
            animFrame->release();

            m_fTotalDelayUnits++;
        }
    }

    return true;
}

bool CCAnimation::initWithAnimationFrames(CCArray* arrayOfAnimationFrames, float delayPerUnit, unsigned int loops)
{
    CCARRAY_VERIFY_TYPE(arrayOfAnimationFrames, CCAnimationFrame*);

    m_fDelayPerUnit = delayPerUnit;
    m_uLoops = loops;

    setFrames(CCArray::createWithArray(arrayOfAnimationFrames));

    CCObject* pObj = NULL;
    CCARRAY_FOREACH(m_pFrames, pObj)
    {
        CCAnimationFrame* animFrame = (CCAnimationFrame*)pObj;
        m_fTotalDelayUnits += animFrame->getDelayUnits();
    }
    return true;
}

CCAnimation::CCAnimation()
: m_fTotalDelayUnits(0.0f)
, m_fDelayPerUnit(0.0f)
, m_fDuration(0.0f)
, m_pFrames(NULL)
, m_bRestoreOriginalFrame(false)
, m_uLoops(0)
{

}

CCAnimation::~CCAnimation(void)
{
    CCLOGINFO("cocos2d, deallocing %p", this);
    CC_SAFE_RELEASE(m_pFrames);
}

void CCAnimation::addSpriteFrame(CCSpriteFrame *pFrame)
{
    CCAnimationFrame *animFrame = new CCAnimationFrame();
    animFrame->initWithSpriteFrame(pFrame, 1.0f, NULL);
    m_pFrames->addObject(animFrame);
    animFrame->release();

    // update duration
    m_fTotalDelayUnits++;
}

void CCAnimation::addSpriteFrameWithFileName(const char *pszFileName)
{
    CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(pszFileName);
    CCRect rect = CCRectZero;
    rect.size = pTexture->getContentSize();
    CCSpriteFrame *pFrame = CCSpriteFrame::createWithTexture(pTexture, rect);
    addSpriteFrame(pFrame);
}

void CCAnimation::addSpriteFrameWithTexture(CCTexture2D *pobTexture, const CCRect& rect)
{
    CCSpriteFrame *pFrame = CCSpriteFrame::createWithTexture(pobTexture, rect);
    addSpriteFrame(pFrame);
}

float CCAnimation::getDuration(void)
{
    return m_fTotalDelayUnits * m_fDelayPerUnit;
}

CCObject* CCAnimation::copyWithZone(CCZone* pZone)
{
    CCZone* pNewZone = NULL;
    CCAnimation* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCAnimation*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCAnimation();
        pNewZone = new CCZone(pCopy);
    }

    pCopy->initWithAnimationFrames(m_pFrames, m_fDelayPerUnit, m_uLoops);
    pCopy->setRestoreOriginalFrame(m_bRestoreOriginalFrame);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

NS_CC_END