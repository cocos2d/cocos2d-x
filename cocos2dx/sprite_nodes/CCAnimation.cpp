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
: _spriteFrame(NULL)
, _delayUnits(0.0f)
, _userInfo(NULL)
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
    CCLOGINFO( "cocos2d: deallocing %p", this);

    CC_SAFE_RELEASE(_spriteFrame);
    CC_SAFE_RELEASE(_userInfo);
}

CCAnimationFrame* CCAnimationFrame::clone() const
{
	// no copy constructor
	auto frame = new CCAnimationFrame();
    frame->initWithSpriteFrame(_spriteFrame->clone(),
							   _delayUnits,
							   _userInfo != NULL ? (CCDictionary*)_userInfo->copy()->autorelease() : NULL);

	frame->autorelease();
	return frame;
}

CCObject* CCAnimationFrame::copyWithZone(CCZone* pZone)
{
    CCZone* pNewZone = NULL;
    CCAnimationFrame* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCAnimationFrame*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCAnimationFrame();
        pNewZone = new CCZone(pCopy);
    }

    pCopy->initWithSpriteFrame((CCSpriteFrame*)_spriteFrame->copy()->autorelease(),
        _delayUnits, _userInfo != NULL ? (CCDictionary*)_userInfo->copy()->autorelease() : NULL);

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

    _loops = 1;
    _delayPerUnit = delay;
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
            _frames->addObject(animFrame);
            animFrame->release();

            _totalDelayUnits++;
        }
    }

    return true;
}

bool CCAnimation::initWithAnimationFrames(CCArray* arrayOfAnimationFrames, float delayPerUnit, unsigned int loops)
{
    CCARRAY_VERIFY_TYPE(arrayOfAnimationFrames, CCAnimationFrame*);

    _delayPerUnit = delayPerUnit;
    _loops = loops;

    setFrames(CCArray::createWithArray(arrayOfAnimationFrames));

    CCObject* pObj = NULL;
    CCARRAY_FOREACH(_frames, pObj)
    {
        CCAnimationFrame* animFrame = (CCAnimationFrame*)pObj;
        _totalDelayUnits += animFrame->getDelayUnits();
    }
    return true;
}

CCAnimation::CCAnimation()
: _totalDelayUnits(0.0f)
, _delayPerUnit(0.0f)
, _duration(0.0f)
, _frames(NULL)
, _restoreOriginalFrame(false)
, _loops(0)
{

}

CCAnimation::~CCAnimation(void)
{
    CCLOGINFO("cocos2d, deallocing %p", this);
    CC_SAFE_RELEASE(_frames);
}

void CCAnimation::addSpriteFrame(CCSpriteFrame *pFrame)
{
    CCAnimationFrame *animFrame = new CCAnimationFrame();
    animFrame->initWithSpriteFrame(pFrame, 1.0f, NULL);
    _frames->addObject(animFrame);
    animFrame->release();

    // update duration
    _totalDelayUnits++;
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

float CCAnimation::getDuration(void) const
{
    return _totalDelayUnits * _delayPerUnit;
}

CCAnimation* CCAnimation::clone() const
{
	// no copy constructor	
	auto a = new CCAnimation();
    a->initWithAnimationFrames(_frames, _delayPerUnit, _loops);
    a->setRestoreOriginalFrame(_restoreOriginalFrame);
	a->autorelease();
	return a;
}

CCObject* CCAnimation::copyWithZone(CCZone* pZone)
{
    CCZone* pNewZone = NULL;
    CCAnimation* pCopy = NULL;
    if(pZone && pZone->_copyObject) 
    {
        //in case of being called at sub class
        pCopy = (CCAnimation*)(pZone->_copyObject);
    }
    else
    {
        pCopy = new CCAnimation();
        pNewZone = new CCZone(pCopy);
    }

    pCopy->initWithAnimationFrames(_frames, _delayPerUnit, _loops);
    pCopy->setRestoreOriginalFrame(_restoreOriginalFrame);

    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

NS_CC_END