/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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

#include "CCTextureCache.h"
#include "CCSpriteFrame.h"
#include "ccMacros.h"
#include "CCTexture2D.h"
#include "cocoa/CGGeometry.h"

// implementation of CCAnimation

CCAnimation* CCAnimation::animationWithName(const char *pszName)
{
	CCAnimation *pAnimation = new CCAnimation();
	pAnimation->initWithName(pszName);
	pAnimation->autorelease();

	return pAnimation;
}

CCAnimation* CCAnimation::animationWithName(const char *pszName, NSMutableArray<CCSpriteFrame*> *pFrames)
{
    CCAnimation *pAnimation = new CCAnimation();
	pAnimation->initWithName(pszName, pFrames);
	pAnimation->autorelease();

	return pAnimation;
}

CCAnimation* CCAnimation::animationWithName(const char *pszName, float fDelay, NSMutableArray<CCSpriteFrame*> pFrames)
{
    CCAnimation *pAnimation = new CCAnimation();
	pAnimation->initWithName(pszName, fDelay, pFrames);
	pAnimation->autorelease();

	return pAnimation;
}

CCAnimation* CCAnimation::animationWithName(const char *pszName, float fDelay)
{
	CCAnimation *pAnimation = new CCAnimation();
	pAnimation->initWithName(pszName, fDelay);
	pAnimation->autorelease();

	return pAnimation;
}

CCAnimation* CCAnimation::initWithName(char *pszName)
{
	return initWithName(pszName, 0, NULL);
}

CCAnimation* CCAnimation::initWithName(char *pszName, float fDelay)
{
	return initWithName(pszName, fDelay, NULL);
}

CCAnimation* CCAnimation::initWithName(char *pszName, NSMutableArray<CCSpriteFrame*> *pFrames)
{
	return initWithName(pszName, 0, pFrames);
}

CCAnimation* CCAnimation::initWithName(char *pszName, float fDelay, NSMutableArray<CCSpriteFrame*> *pFrames)
{
	m_fDelay = fDelay;
	m_pszName = pszName;
	m_pobFrames = NSMutableArray<CCSpriteFrame*>::arrayWithArray(pFrames);

	return this;
}

CCAnimation::~CCAnimation(void)
{
	CCLOGINFO("cocos2d, deallocing %p", this);
	// [name_ release];
	m_pobFrames->release();
}

void CCAnimation::addFrame(CCSpriteFrame *pFrame)
{
	m_pobFrames->addObject(pFrame);
}

void CCAnimation::addFrameWithFileName(char *pszFileName)
{
	CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(pszFileName);
	CGRect rect = CGRectZero;
	rect.size = pTexture->getContentSize();
	CCSpriteFrame *pFrame = CCSpriteFrame::frameWithTexture(pTexture, rect, CGPointZero);
	m_pobFrames->addObject(pFrame);
}

void CCAnimation::addFrameWithTexture(CCTexture2D *pobTexture, CGRect rect)
{
	CCSpriteFrame *pFrame = CCSpriteFrame::frameWithTexture(pobTexture, rect, CGPointZero);
	m_pobFrames->addObject(pFrame);
}


// implementation of CCSpriteFrame

CCSpriteFrame* CCSpriteFrame::frameWithTexture(CCTexture2D *pobTexture, CGRect rect, CGPoint offset)
{
	CCSpriteFrame *pSpriteFrame = new CCSpriteFrame();;
	pSpriteFrame->initWithTexture(pobTexture, rect, offset, rect.size);
	pSpriteFrame->autorelease();

	return pSpriteFrame;
}

CCSpriteFrame* CCSpriteFrame::frameWithTexture(CCTexture2D *pobTexture, CGRect rect, CGPoint offset, CGSize originalSize)
{
    CCSpriteFrame *pSpriteFrame = new CCSpriteFrame();;
	pSpriteFrame->initWithTexture(pobTexture, rect, offset, originalSize);
	pSpriteFrame->autorelease();

	return pSpriteFrame;
}

CCSpriteFrame* CCSpriteFrame::initWithTexture(CCTexture2D *pobTexture, CGRect rect, CGPoint offset)
{
	return initWithTexture(pobTexture, rect, offset, rect.size);
}

CCSpriteFrame* CCSpriteFrame::initWithTexture(CCTexture2D *pobTexture, CGRect rect, CGPoint offset, CGSize originalSize)
{
	m_pobTexture = pobTexture;
	m_obOffset = offset;
	m_obRect = rect;
	m_obOriginalSize = originalSize;

	return this;
}

CCSpriteFrame::~CCSpriteFrame(void)
{
	CCLOGINFO("cocos2d: deallocing %p", this);
	m_pobTexture->release();
}

NSObject* CCSpriteFrame::copyWithZone(NSZone *pZone)
{
	CCSpriteFrame *pCopy = new CCSpriteFrame();
	
	pCopy->initWithTexture(m_texture, m_rect, m_offset, m_originalSize);
	
	return pCopy;
}
