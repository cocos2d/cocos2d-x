/*
 * Copyright (c) 2012 cocos2d-x.org
 * http://www.cocos2d-x.org
 *
 * Copyright 2011 Yannick Loriot.
 * http://yannickloriot.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Converted to c++ / cocos2d-x by Angus C
*
 */

#include "CCControlSlider.h"
#include "support/CCPointExtension.h"
#include "touch_dispatcher/CCTouch.h"
#include "CCDirector.h"

NS_CC_EXT_BEGIN

CCControlSlider::CCControlSlider()
: m_value(0.0f)
, m_minimumValue(0.0f)
, m_maximumValue(0.0f)
, m_minimumAllowedValue(0.0f)
, m_maximumAllowedValue(0.0f)
, m_thumbSprite(NULL)
, m_progressSprite(NULL)
, m_backgroundSprite(NULL)
{

}

CCControlSlider::~CCControlSlider()
{
    CC_SAFE_RELEASE(m_thumbSprite);
    CC_SAFE_RELEASE(m_progressSprite);
    CC_SAFE_RELEASE(m_backgroundSprite);
}

CCControlSlider* CCControlSlider::sliderWithFiles(const char* bgFile, const char* progressFile, const char* thumbFile)
{
    return CCControlSlider::create(bgFile, progressFile, thumbFile);
}

CCControlSlider* CCControlSlider::create(const char* bgFile, const char* progressFile, const char* thumbFile)
{
    // Prepare background for slider
    CCSprite *backgroundSprite      = CCSprite::create(bgFile);
    
    // Prepare progress for slider
    CCSprite *progressSprite        = CCSprite::create(progressFile);
    
    // Prepare thumb (menuItem) for slider
    CCSprite *thumbSprite           = CCSprite::create(thumbFile);
    
    return CCControlSlider::create(backgroundSprite, progressSprite, thumbSprite);
}

CCControlSlider* CCControlSlider::sliderWithSprites(CCSprite * backgroundSprite, CCSprite* pogressSprite, CCSprite* thumbSprite)
{
    return CCControlSlider::create(backgroundSprite, pogressSprite, thumbSprite);
}

CCControlSlider* CCControlSlider::create(CCSprite * backgroundSprite, CCSprite* pogressSprite, CCSprite* thumbSprite)
{
    CCControlSlider *pRet = new CCControlSlider();
    pRet->initWithSprites(backgroundSprite, pogressSprite, thumbSprite);
    pRet->autorelease();
    return pRet;
}

 bool CCControlSlider::initWithSprites(CCSprite * backgroundSprite, CCSprite* progressSprite, CCSprite* thumbSprite)
 {
     if (CCControl::init())
     {
        CCAssert(backgroundSprite,  "Background sprite must be not nil");
        CCAssert(progressSprite,    "Progress sprite must be not nil");
        CCAssert(thumbSprite,       "Thumb sprite must be not nil");

        ignoreAnchorPointForPosition(false);
        setTouchEnabled(true);

        this->setBackgroundSprite(backgroundSprite);
        this->setProgressSprite(progressSprite);
        this->setThumbSprite(thumbSprite);

        // Defines the content size
        CCRect maxRect   = CCControlUtils::CCRectUnion(backgroundSprite->boundingBox(), thumbSprite->boundingBox());

        setContentSize(CCSizeMake(maxRect.size.width, maxRect.size.height));
        
        // Add the slider background
        m_backgroundSprite->setAnchorPoint(ccp(0.5f, 0.5f));
        m_backgroundSprite->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().height / 2));
        addChild(m_backgroundSprite);

        // Add the progress bar
        m_progressSprite->setAnchorPoint(ccp(0.0f, 0.5f));
        m_progressSprite->setPosition(ccp(0.0f, this->getContentSize().height / 2));
        addChild(m_progressSprite);

        // Add the slider thumb  
        m_thumbSprite->setPosition(ccp(0.0f, this->getContentSize().height / 2));
        addChild(m_thumbSprite);
        
        // Init default values
        m_minimumValue                   = 0.0f;
        m_maximumValue                   = 1.0f;

        setValue(m_minimumValue);
        return true;
     }
     else
     {
         return false;
     }
 }


void CCControlSlider::setEnabled(bool enabled)
{
    CCControl::setEnabled(enabled);
    if (m_thumbSprite != NULL) 
    {
        m_thumbSprite->setOpacity((enabled) ? 255 : 128);
    }
}

 void CCControlSlider::setValue(float value)
 {
     // set new value with sentinel
     if (value < m_minimumValue)
     {
         value = m_minimumValue;
     }

     if (value > m_maximumValue) 
     {
         value = m_maximumValue;
     }

     m_value = value;

     this->needsLayout();

     this->sendActionsForControlEvents(CCControlEventValueChanged);
 }

 void CCControlSlider::setMinimumValue(float minimumValue)
 {
     m_minimumValue=minimumValue;
     m_minimumAllowedValue = minimumValue;
     if (m_minimumValue >= m_maximumValue)    
     {
        m_maximumValue   = m_minimumValue + 1.0f;
     }
     setValue(m_value);
 }

 void CCControlSlider::setMaximumValue(float maximumValue)
 {
     m_maximumValue=maximumValue;
     m_maximumAllowedValue = maximumValue;
     if (m_maximumValue <= m_minimumValue)   
     {
        m_minimumValue   = m_maximumValue - 1.0f;
     }
     setValue(m_value);
 }

bool CCControlSlider::isTouchInside(CCTouch * touch)
{
  CCPoint touchLocation   = touch->getLocation();
  touchLocation           = this->getParent()->convertToNodeSpace(touchLocation);

  CCRect rect             = this->boundingBox();
  rect.size.width         += m_thumbSprite->getContentSize().width;
  rect.origin.x           -= m_thumbSprite->getContentSize().width / 2;

  return rect.containsPoint(touchLocation);
}

CCPoint CCControlSlider::locationFromTouch(CCTouch* touch)
{
  CCPoint touchLocation   = touch->getLocation();                      // Get the touch position
  touchLocation           = this->convertToNodeSpace(touchLocation);                  // Convert to the node space of this class

  if (touchLocation.x < 0)
  {
      touchLocation.x     = 0;
  } else if (touchLocation.x > m_backgroundSprite->getContentSize().width)
  {
      touchLocation.x     = m_backgroundSprite->getContentSize().width;
  }

  return touchLocation;
}


bool CCControlSlider::ccTouchBegan(CCTouch* touch, CCEvent* pEvent)
{
    if (!isTouchInside(touch) || !isEnabled() || !isVisible())
    {
        return false;
    }

    CCPoint location = locationFromTouch(touch);
    sliderBegan(location);
    return true;
}

void CCControlSlider::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint location = locationFromTouch(pTouch);
    sliderMoved(location);
}

void CCControlSlider::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    sliderEnded(CCPointZero);
}

void CCControlSlider::needsLayout()
{
    if (NULL == m_thumbSprite || NULL == m_backgroundSprite || NULL == m_progressSprite)
    {
        return;
    }
    // Update thumb position for new value
    float percent               = (m_value - m_minimumValue) / (m_maximumValue - m_minimumValue);

    CCPoint pos                 = m_thumbSprite->getPosition();
    pos.x                       = percent * m_backgroundSprite->getContentSize().width;
    m_thumbSprite->setPosition(pos);

    // Stretches content proportional to newLevel
    CCRect textureRect          = m_progressSprite->getTextureRect();
    textureRect                 = CCRectMake(textureRect.origin.x, textureRect.origin.y, pos.x, textureRect.size.height);
    m_progressSprite->setTextureRect(textureRect, m_progressSprite->isTextureRectRotated(), textureRect.size);
}

void CCControlSlider::sliderBegan(CCPoint location)
{
    this->setSelected(true);
    this->getThumbSprite()->setColor(ccGRAY);
    setValue(valueForLocation(location));
}

void CCControlSlider::sliderMoved(CCPoint location)
{
    setValue(valueForLocation(location));
}

void CCControlSlider::sliderEnded(CCPoint location)
{
    if (this->isSelected())
    {
        setValue(valueForLocation(m_thumbSprite->getPosition()));
    }
    this->getThumbSprite()->setColor(ccWHITE);
    this->setSelected(false);
}

float CCControlSlider::valueForLocation(CCPoint location)
{
    float percent = location.x/ m_backgroundSprite->getContentSize().width;
    return MAX(MIN(m_minimumValue + percent * (m_maximumValue - m_minimumValue), m_maximumAllowedValue), m_minimumAllowedValue);
}

NS_CC_EXT_END
