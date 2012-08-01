/*
 * CCControlSlider
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

CCControlSlider::~CCControlSlider()
{

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
    CCSprite *thumbNormal           = CCSprite::create(thumbFile);
    CCSprite *thumbSelected         = CCSprite::create(thumbFile);
    thumbSelected->setColor(ccGRAY);
    
    CCMenuItemSprite* thumbMenuItem =CCMenuItemSprite::create(thumbNormal, thumbSelected);
    
    return CCControlSlider::create(backgroundSprite, progressSprite, thumbMenuItem);
}

CCControlSlider* CCControlSlider::sliderWithSprites(CCSprite * backgroundSprite, CCSprite* pogressSprite, CCMenuItem* thumbItem)
{
    return CCControlSlider::create(backgroundSprite, pogressSprite, thumbItem);
}

CCControlSlider* CCControlSlider::create(CCSprite * backgroundSprite, CCSprite* pogressSprite, CCMenuItem* thumbItem)
{
    CCControlSlider *pRet = new CCControlSlider();
    pRet->initWithSprites(backgroundSprite, pogressSprite, thumbItem);
    pRet->autorelease();
    return pRet;
}

 bool CCControlSlider::initWithSprites(CCSprite * backgroundSprite, CCSprite* progessSprite, CCMenuItem* thumbItem)
 {
     if (CCControl::init())
     {
        ignoreAnchorPointForPosition(false);
        setTouchEnabled(true);

        m_backgroundSprite=backgroundSprite;
        m_progressSprite=progessSprite;
        m_thumbItem=thumbItem;

        // Defines the content size
        CCRect maxRect                  = CCControlUtils::CCRectUnion(backgroundSprite->boundingBox(), thumbItem->boundingBox());
        CCSize size=CCSizeMake(maxRect.size.width+2*SLIDER_MARGIN_H, maxRect.size.height+2*SLIDER_MARGIN_V);
        setContentSize(size);
        //setContentSize(CCSizeMake(backgroundSprite->getContentSize().width, thumbItem->getContentSize().height));
        // Add the slider background
        m_backgroundSprite->setAnchorPoint(ccp(0.5f, 0.5f));
        m_backgroundSprite->setPosition(ccp(size.width / 2, size.height / 2));
        addChild(m_backgroundSprite);

        // Add the progress bar
        m_progressSprite->setAnchorPoint(ccp(0.0f, 0.5f));
        m_progressSprite->setPosition(ccp(0.0f+SLIDER_MARGIN_H, size.height / 2));
        addChild(m_progressSprite);

        // Add the slider thumb  
        m_thumbItem->setPosition(ccp(0+SLIDER_MARGIN_H, size.height / 2));
        addChild(m_thumbItem);
        
        // Init default values
        m_minimumValue                   = 0.0f;
        m_maximumValue                   = 1.0f;
        m_snappingInterval=-1.0f;
        setValue(m_minimumValue);
        return true;
     }
     else
     {
         return false;
     }
 }


 void CCControlSlider::setValue(float value)
 {
     //clamp between the two bounds
     value=MAX(value, m_minimumValue);
     value=MIN(value, m_maximumValue);

     //if we're snapping
     if (m_snappingInterval>=0)
     {
         //int nTotal=(int)(ceil(m_maximumValue-m_minimumValue)/m_snappingInterval);
         //floor (n + 0.5f) == round(n)
         value=floor(0.5f + value/m_snappingInterval)*m_snappingInterval;
     }
     m_value=value;

    // Update thumb position for new value
    float percent               = (m_value - m_minimumValue) / (m_maximumValue - m_minimumValue);
    CCPoint pos= m_thumbItem->getPosition();
    pos.x                       = percent * m_backgroundSprite->getContentSize().width+SLIDER_MARGIN_H;
    m_thumbItem->setPosition(pos);
    
    // Stretches content proportional to newLevel
    CCRect textureRect          = m_progressSprite->getTextureRect();
    textureRect                 = CCRectMake(textureRect.origin.x, textureRect.origin.y, percent * m_backgroundSprite->getContentSize().width, textureRect.size.height);
    m_progressSprite->setTextureRect(textureRect, m_progressSprite->isTextureRectRotated(), textureRect.size);
    sendActionsForControlEvents(CCControlEventValueChanged);    
 }

 void CCControlSlider::setMinimumValue(float minimumValue)
 {
     m_minimumValue=minimumValue;
     if (m_minimumValue >= m_maximumValue)    
        m_maximumValue   = m_minimumValue + 1.0f;
     setValue(m_value);
 }

  void CCControlSlider::setMaximumValue(float maximumValue)
 {
     m_maximumValue=maximumValue;
     if (m_maximumValue <= m_minimumValue)    
        m_minimumValue   = m_maximumValue - 1.0f;
     setValue(m_value);
 }

  //this is the same as CCControl::getTouchLocation, but it returns the position relative to the position of this control
  CCPoint CCControlSlider::getTouchLocationInControl(CCTouch* touch)
{
    CCPoint touchLocation = touch->getLocation();;                      // Get the touch position
    touchLocation = convertToNodeSpace(touchLocation);         // Convert to the node space of this class
    
   if (touchLocation.x < 0)
   {
        touchLocation.x     = 0;
   } 
   else if (touchLocation.x > m_backgroundSprite->getContentSize().width+SLIDER_MARGIN_H)
   {
        touchLocation.x     = m_backgroundSprite->getContentSize().width+SLIDER_MARGIN_H;
   }    
    return touchLocation;
}

 bool CCControlSlider::ccTouchBegan(CCTouch* touch, CCEvent* pEvent)
  {
      if (!isTouchInside(touch))
          return false;

    CCPoint location = getTouchLocationInControl(touch);
    sliderBegan(location);
    return true;
}

void CCControlSlider::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint location = getTouchLocationInControl(pTouch);
    sliderMoved(location);
}

void CCControlSlider::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint location = getTouchLocationInControl(pTouch);
    sliderEnded(CCPointZero);
}

void CCControlSlider::sliderBegan(CCPoint location)
{
    m_thumbItem->selected();
    setValue(valueForLocation(location));
}

void CCControlSlider::sliderMoved(CCPoint location)
{
    setValue(valueForLocation(location));
}

void CCControlSlider::sliderEnded(CCPoint location)
{
    if (m_thumbItem->isSelected())
    {
        m_thumbItem->unselected();
        setValue(valueForLocation(m_thumbItem->getPosition()));
    }
}

float CCControlSlider::valueForLocation(CCPoint location)
{
    float percent = (location.x-SLIDER_MARGIN_H)/ m_backgroundSprite->getContentSize().width;
    return m_minimumValue + percent * (m_maximumValue - m_minimumValue);
}

NS_CC_EXT_END
