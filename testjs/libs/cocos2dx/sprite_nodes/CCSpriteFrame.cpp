/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2011 Ricardo Quesada
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

#include "CCSpriteFrame.h"
#include "CCDirector.h"

namespace   cocos2d {
// implementation of CCSpriteFrame

CCSpriteFrame* CCSpriteFrame::frameWithTexture(CCTexture2D *pobTexture, const CCRect& rect)
{
	CCSpriteFrame *pSpriteFrame = new CCSpriteFrame();;
	pSpriteFrame->initWithTexture(pobTexture, rect);
	pSpriteFrame->autorelease();

	return pSpriteFrame;
}

CCSpriteFrame* CCSpriteFrame::frameWithTexture(CCTexture2D* pobTexture, const CCRect& rect, bool rotated, const CCPoint& offset, const CCSize& originalSize)
{
    CCSpriteFrame *pSpriteFrame = new CCSpriteFrame();;
	pSpriteFrame->initWithTexture(pobTexture, rect, rotated, offset, originalSize);
	pSpriteFrame->autorelease();

	return pSpriteFrame;
}

bool CCSpriteFrame::initWithTexture(CCTexture2D* pobTexture, const CCRect& rect)
{
	CCRect rectInPixels = CC_RECT_POINTS_TO_PIXELS(rect);
	return initWithTexture(pobTexture, rectInPixels, false, CCPointZero, rectInPixels.size);
}

bool CCSpriteFrame::initWithTexture(CCTexture2D* pobTexture, const CCRect& rect, bool rotated, const CCPoint& offset, const CCSize& originalSize)
{
	m_pobTexture = pobTexture;

    if (pobTexture)
    {
        pobTexture->retain();
    }

	m_obRectInPixels = rect;
	m_obRect = CC_RECT_PIXELS_TO_POINTS(rect);
	m_bRotated = rotated;
	m_obOffsetInPixels = offset;

	m_obOriginalSizeInPixels = originalSize;

	return true;
}

CCSpriteFrame::~CCSpriteFrame(void)
{
	CCLOGINFO("cocos2d: deallocing %p", this);
	CC_SAFE_RELEASE(m_pobTexture);
}

CCObject* CCSpriteFrame::copyWithZone(CCZone *pZone)
{
    CC_UNUSED_PARAM(pZone);
	CCSpriteFrame *pCopy = new CCSpriteFrame();
	
	pCopy->initWithTexture(m_pobTexture, m_obRectInPixels, m_bRotated, m_obOffsetInPixels, m_obOriginalSizeInPixels);
	
	return pCopy;
}

void CCSpriteFrame::setRect(const CCRect& rect)
{
    m_obRect = rect;
    m_obRectInPixels = CC_RECT_POINTS_TO_PIXELS(m_obRect);
}

void CCSpriteFrame::setRectInPixels(const CCRect& rectInPixels)
{
    m_obRectInPixels = rectInPixels;
    m_obRect = CC_RECT_PIXELS_TO_POINTS(rectInPixels);
}

}//namespace   cocos2d 
