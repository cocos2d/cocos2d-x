/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2009 Jason Booth

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
#include "CCMotionStreak.h"
#include "CCPointExtension.h"
#include "CCRibbon.h"
namespace cocos2d {

/*
 * Motion Streak manages a Ribbon based on it's motion in absolute space.
 * You construct it with a fadeTime, minimum segment size, texture path, texture
 * length and color. The fadeTime controls how long it takes each vertex in
 * the streak to fade out, the minimum segment size it how many pixels the
 * streak will move before adding a new ribbon segement, and the texture
 * length is the how many pixels the texture is stretched across. The texture
 * is vertically aligned along the streak segemnts. 
 */
//implementation CCMotionStreak

CCMotionStreak * CCMotionStreak::streakWithFade(float fade, float seg, const char *imagePath, float width, float length, ccColor4B color)
{
	CCMotionStreak *pRet = new CCMotionStreak();
	if(pRet && pRet->initWithFade(fade, seg, imagePath, width, length, color))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet)
	return NULL;
}

bool CCMotionStreak::initWithFade(float fade, float seg, const char *imagePath, float width, float length, ccColor4B color)
{
	m_fSegThreshold = seg;
	m_fWidth = width;
	m_tLastLocation = CCPointZero;
	m_pRibbon = CCRibbon::ribbonWithWidth(m_fWidth, imagePath, length, color, fade);
	this->addChild(m_pRibbon);

	// update ribbon position. Use schedule:interval and not scheduleUpdated. (cocos2d-iphone)issue #1075
	this->schedule(schedule_selector(CCMotionStreak::update), 0);
	return true;
}

void CCMotionStreak::update(ccTime delta)
{
	CCPoint location = this->convertToWorldSpace(CCPointZero);
	m_pRibbon->setPosition(ccp(-1*location.x, -1*location.y));
    float len = ccpLength(ccpSub(m_tLastLocation, location));
	if (len > m_fSegThreshold)
	{
		m_pRibbon->addPointAt(location, m_fWidth);
		m_tLastLocation = location;
	}
	m_pRibbon->update(delta);
}

//MotionStreak - CocosNodeTexture protocol

void CCMotionStreak::setTexture(CCTexture2D* texture)
{
	m_pRibbon->setTexture(texture);
}

CCTexture2D * CCMotionStreak::getTexture()
{
	return m_pRibbon->getTexture();
}

ccBlendFunc CCMotionStreak::getBlendFunc()
{
	return m_pRibbon->getBlendFunc();
}

void CCMotionStreak::setBlendFunc(ccBlendFunc blendFunc)
{
	m_pRibbon->setBlendFunc(blendFunc);
}

CCRibbon * CCMotionStreak::getRibbon()
{
	return m_pRibbon;
}

}// namespace cocos2d
