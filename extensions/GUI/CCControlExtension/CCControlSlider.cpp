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
#include "base/CCTouch.h"
#include "base/CCDirector.h"

NS_CC_EXT_BEGIN

ControlSlider::ControlSlider()
: _value(0.0f)
, _minimumValue(0.0f)
, _maximumValue(0.0f)
, _minimumAllowedValue(0.0f)
, _maximumAllowedValue(0.0f)
, _thumbSprite(nullptr)
, _selectedThumbSprite(nullptr)
, _progressSprite(nullptr)
, _backgroundSprite(nullptr)
{

}

ControlSlider::~ControlSlider()
{
    CC_SAFE_RELEASE(_thumbSprite);
    CC_SAFE_RELEASE(_selectedThumbSprite);
    CC_SAFE_RELEASE(_progressSprite);
    CC_SAFE_RELEASE(_backgroundSprite);
}

ControlSlider* ControlSlider::create(const char* bgFile, const char* progressFile, const char* thumbFile)
{
    // Prepare background for slider
    Sprite *backgroundSprite      = Sprite::create(bgFile);

    // Prepare progress for slider
    Sprite *progressSprite        = Sprite::create(progressFile);

    // Prepare thumb (menuItem) for slider
    Sprite *thumbSprite           = Sprite::create(thumbFile);

    return ControlSlider::create(backgroundSprite, progressSprite, thumbSprite);
}

ControlSlider* ControlSlider::create(const char* bgFile, const char* progressFile, const char* thumbFile,
		const char* selectedThumbSpriteFile)
{
    // Prepare background for slider
    Sprite *backgroundSprite      = Sprite::create(bgFile);
    
    // Prepare progress for slider
    Sprite *progressSprite        = Sprite::create(progressFile);
    
    // Prepare thumb (menuItem) for slider
    Sprite *thumbSprite           = Sprite::create(thumbFile);
    
    // Prepare selected thumb (menuItem) for slider
    Sprite *selectedThumbSprite   = Sprite::create(selectedThumbSpriteFile);

    return ControlSlider::create(backgroundSprite, progressSprite, thumbSprite, selectedThumbSprite);
}

ControlSlider* ControlSlider::create(Sprite * backgroundSprite, Sprite* pogressSprite, Sprite* thumbSprite)
{
    ControlSlider *pRet = new (std::nothrow) ControlSlider();
    pRet->initWithSprites(backgroundSprite, pogressSprite, thumbSprite);
    pRet->autorelease();
    return pRet;
}

ControlSlider* ControlSlider::create(Sprite * backgroundSprite, Sprite* pogressSprite, Sprite* thumbSprite,
        Sprite* selectedThumbSprite)
{
    ControlSlider *pRet = new (std::nothrow) ControlSlider();
    pRet->initWithSprites(backgroundSprite, pogressSprite, thumbSprite, selectedThumbSprite);
    pRet->autorelease();
    return pRet;
}

bool ControlSlider::initWithSprites(Sprite * backgroundSprite, Sprite* progressSprite, Sprite* thumbSprite)
{
    Sprite* selectedThumbSprite = Sprite::createWithTexture(thumbSprite->getTexture(),
        thumbSprite->getTextureRect());
    selectedThumbSprite->setColor(Color3B::GRAY);
    return this->initWithSprites(backgroundSprite, progressSprite, thumbSprite, selectedThumbSprite);
}

 bool ControlSlider::initWithSprites(Sprite * backgroundSprite, Sprite* progressSprite, Sprite* thumbSprite,
        Sprite* selectedThumbSprite)
 {
     if (Control::init())
     {
        CCASSERT(backgroundSprite,      "Background sprite must be not nil");
        CCASSERT(progressSprite,        "Progress sprite must be not nil");
        CCASSERT(thumbSprite,           "Thumb sprite must be not nil");
        CCASSERT(selectedThumbSprite,   "Thumb sprite must be not nil");

        ignoreAnchorPointForPosition(false);

        this->setBackgroundSprite(backgroundSprite);
        this->setProgressSprite(progressSprite);
        this->setThumbSprite(thumbSprite);
        this->setSelectedThumbSprite(selectedThumbSprite);

        // Defines the content size
        Rect maxRect   = ControlUtils::RectUnion(backgroundSprite->getBoundingBox(), thumbSprite->getBoundingBox());

        setContentSize(Size(maxRect.size.width, maxRect.size.height));
        
        // Add the slider background
        _backgroundSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
        _backgroundSprite->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
        addChild(_backgroundSprite);

        // Add the progress bar
        _progressSprite->setAnchorPoint(Vec2(0.0f, 0.5f));
        _progressSprite->setPosition(0.0f, this->getContentSize().height / 2);
        addChild(_progressSprite);

        // Add the slider thumb  
        _thumbSprite->setPosition(0.0f, this->getContentSize().height / 2);
        addChild(_thumbSprite);
        
        _selectedThumbSprite->setPosition(0.0f, this->getContentSize().height / 2);
        _selectedThumbSprite->setVisible(false);
        addChild(_selectedThumbSprite);

        // Init default values
        _minimumValue                   = 0.0f;
        _maximumValue                   = 1.0f;

        setValue(_minimumValue);
        return true;
     }
     else
     {
         return false;
     }
 }


void ControlSlider::setEnabled(bool enabled)
{
    Control::setEnabled(enabled);
    if (_thumbSprite != nullptr) 
    {
        _thumbSprite->setOpacity((enabled) ? 255 : 128);
    }
}

 void ControlSlider::setValue(float value)
 {
     // set new value with sentinel
     if (value < _minimumValue)
     {
         value = _minimumValue;
     }

     if (value > _maximumValue) 
     {
         value = _maximumValue;
     }

     _value = value;

     this->needsLayout();

     this->sendActionsForControlEvents(Control::EventType::VALUE_CHANGED);
 }

 void ControlSlider::setMinimumValue(float minimumValue)
 {
     _minimumValue=minimumValue;
     _minimumAllowedValue = minimumValue;
     if (_minimumValue >= _maximumValue)    
     {
        _maximumValue   = _minimumValue + 1.0f;
     }
     setValue(_value);
 }

 void ControlSlider::setMaximumValue(float maximumValue)
 {
     _maximumValue=maximumValue;
     _maximumAllowedValue = maximumValue;
     if (_maximumValue <= _minimumValue)   
     {
        _minimumValue   = _maximumValue - 1.0f;
     }
     setValue(_value);
 }

bool ControlSlider::isTouchInside(Touch * touch)
{
  Vec2 touchLocation   = touch->getLocation();
  touchLocation           = this->getParent()->convertToNodeSpace(touchLocation);

  Rect rect             = this->getBoundingBox();
  rect.size.width         += _thumbSprite->getContentSize().width;
  rect.origin.x           -= _thumbSprite->getContentSize().width / 2;

  return rect.containsPoint(touchLocation);
}

Vec2 ControlSlider::locationFromTouch(Touch* touch)
{
  Vec2 touchLocation   = touch->getLocation();                      // Get the touch position
  touchLocation           = this->convertToNodeSpace(touchLocation);                  // Convert to the node space of this class

  if (touchLocation.x < 0)
  {
      touchLocation.x     = 0;
  } else if (touchLocation.x > _backgroundSprite->getContentSize().width)
  {
      touchLocation.x     = _backgroundSprite->getContentSize().width;
  }

  return touchLocation;
}


bool ControlSlider::onTouchBegan(Touch* touch, Event* pEvent)
{
    if (!isTouchInside(touch) || !isEnabled() || !isVisible())
    {
        return false;
    }

    Vec2 location = locationFromTouch(touch);
    sliderBegan(location);
    return true;
}

void ControlSlider::onTouchMoved(Touch *pTouch, Event *pEvent)
{
    Vec2 location = locationFromTouch(pTouch);
    sliderMoved(location);
}

void ControlSlider::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    sliderEnded(Vec2::ZERO);
}

void ControlSlider::needsLayout()
{
    if (nullptr == _thumbSprite || nullptr == _selectedThumbSprite || nullptr == _backgroundSprite
    		|| nullptr == _progressSprite)
    {
        return;
    }
    // Update thumb position for new value
    float percent               = (_value - _minimumValue) / (_maximumValue - _minimumValue);

    Vec2 pos                 = _thumbSprite->getPosition();
    pos.x                       = percent * _backgroundSprite->getContentSize().width;
    _thumbSprite->setPosition(pos);
    _selectedThumbSprite->setPosition(pos);

    // Stretches content proportional to newLevel
    Rect textureRect          = _progressSprite->getTextureRect();
    textureRect                 = Rect(textureRect.origin.x, textureRect.origin.y, pos.x, textureRect.size.height);
    _progressSprite->setTextureRect(textureRect, _progressSprite->isTextureRectRotated(), textureRect.size);
}

void ControlSlider::sliderBegan(Vec2 location)
{
    this->setSelected(true);
    _thumbSprite->setVisible(false);
    _selectedThumbSprite->setVisible(true);
    setValue(valueForLocation(location));
}

void ControlSlider::sliderMoved(Vec2 location)
{
    setValue(valueForLocation(location));
}

void ControlSlider::sliderEnded(Vec2 location)
{
    if (this->isSelected())
    {
        setValue(valueForLocation(_thumbSprite->getPosition()));
    }
    _thumbSprite->setVisible(true);
    _selectedThumbSprite->setVisible(false);
    this->setSelected(false);
}

float ControlSlider::valueForLocation(Vec2 location)
{
    float percent = location.x/ _backgroundSprite->getContentSize().width;
    return MAX(MIN(_minimumValue + percent * (_maximumValue - _minimumValue), _maximumAllowedValue), _minimumAllowedValue);
}

NS_CC_EXT_END
