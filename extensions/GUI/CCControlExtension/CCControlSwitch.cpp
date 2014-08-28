/*
 * Copyright (c) 2012 cocos2d-x.org
 * http://www.cocos2d-x.org
 *
 * Copyright 2012 Yannick Loriot. All rights reserved.
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
 */

#include "CCControlSwitch.h"
#include "2d/CCSprite.h"
#include "2d/CCActionTween.h"
#include "2d/CCLabel.h"
#include "2d/CCClippingNode.h"
#include "renderer/ccShaders.h"
#include "2d/CCRenderTexture.h"

NS_CC_EXT_BEGIN
// ControlSwitchSprite

class ControlSwitchSprite : public Sprite, public ActionTweenDelegate
{
public:
    /** creates an autorelease instance of ControlSwitchSprite */
    static ControlSwitchSprite* create(
                            Sprite *maskSprite,
                            Sprite *onSprite,
                            Sprite *offSprite,
                            Sprite *thumbSprite,
                            Label* onLabel,
                            Label* offLabel);

    /**
     * @js NA
     * @lua NA
     */
    void needsLayout();
    /**
     * @js NA
     * @lua NA
     */
    void setSliderXPosition(float sliderXPosition);
    /**
     * @js NA
     * @lua NA
     */
    float getSliderXPosition() {return _sliderXPosition;}
    /**
     * @js NA
     * @lua NA
     */
    float onSideWidth();
    /**
     * @js NA
     * @lua NA
     */
    float offSideWidth();
    /**
     * @js NA
     * @lua NA
     */
    virtual void updateTweenAction(float value, const std::string& key) override;

/** Contains the position (in x-axis) of the slider inside the receiver. */
    float _sliderXPosition;
    CC_SYNTHESIZE(float, _onPosition, OnPosition)
    CC_SYNTHESIZE(float, _offPosition, OffPosition)
    
    CC_SYNTHESIZE_RETAIN(Texture2D*, _maskTexture, MaskTexture)
    CC_SYNTHESIZE(GLuint, _textureLocation, TextureLocation)
    CC_SYNTHESIZE(GLuint, _maskLocation, MaskLocation)
    
    CC_SYNTHESIZE_RETAIN(Sprite*, _onSprite, OnSprite)
    CC_SYNTHESIZE_RETAIN(Sprite*, _offSprite, OffSprite)
    CC_SYNTHESIZE_RETAIN(Sprite*, _thumbSprite, ThumbSprite)
    CC_SYNTHESIZE_RETAIN(Label*, _onLabel, OnLabel)
    CC_SYNTHESIZE_RETAIN(Label*, _offLabel, OffLabel)
    
    Sprite* _clipperStencil;

protected:
    /**
     * @js NA
     * @lua NA
     */
    ControlSwitchSprite();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ControlSwitchSprite();
    /**
     * @js NA
     * @lua NA
     */
    bool initWithMaskSprite(
                            Sprite *maskSprite,
                            Sprite *onSprite,
                            Sprite *offSprite,
                            Sprite *thumbSprite,
                            Label* onLabel, 
                            Label* offLabel);
private:
    CC_DISALLOW_COPY_AND_ASSIGN(ControlSwitchSprite);
};

ControlSwitchSprite* ControlSwitchSprite::create(Sprite *maskSprite,
                                            Sprite *onSprite,
                                            Sprite *offSprite,
                                            Sprite *thumbSprite,
                                            Label* onLabel,
                                            Label* offLabel)
{
    auto ret = new (std::nothrow) ControlSwitchSprite();
    ret->initWithMaskSprite(maskSprite, onSprite, offSprite, thumbSprite, onLabel, offLabel);
    ret->autorelease();
    return ret;
}

ControlSwitchSprite::ControlSwitchSprite()
: _sliderXPosition(0.0f)
, _onPosition(0.0f)
, _offPosition(0.0f)
, _maskTexture(nullptr)
, _textureLocation(0)
, _maskLocation(0)
, _onSprite(nullptr)
, _offSprite(nullptr)
, _thumbSprite(nullptr)
, _onLabel(nullptr)
, _offLabel(nullptr)
, _clipperStencil(nullptr)
{

}

ControlSwitchSprite::~ControlSwitchSprite()
{
    CC_SAFE_RELEASE(_onSprite);
    CC_SAFE_RELEASE(_offSprite);
    CC_SAFE_RELEASE(_thumbSprite);
    CC_SAFE_RELEASE(_onLabel);
    CC_SAFE_RELEASE(_offLabel);
    CC_SAFE_RELEASE(_maskTexture);
    CC_SAFE_RELEASE(_clipperStencil);
}

bool ControlSwitchSprite::initWithMaskSprite(
    Sprite *maskSprite, 
    Sprite *onSprite, 
    Sprite *offSprite,
    Sprite *thumbSprite,
    Label* onLabel, 
    Label* offLabel)
{
    if (Sprite::initWithTexture(maskSprite->getTexture()))
    {
        // Sets the default values
        _onPosition             = 0;
        _offPosition            = -onSprite->getContentSize().width + thumbSprite->getContentSize().width / 2;
        _sliderXPosition        = _onPosition; 

        setOnSprite(onSprite);
        setOffSprite(offSprite);
        setThumbSprite(thumbSprite);
        setOnLabel(onLabel);
        setOffLabel(offLabel);

        ClippingNode* clipper = ClippingNode::create();
        _clipperStencil = Sprite::createWithTexture(maskSprite->getTexture());
        _clipperStencil->retain();
        clipper->setAlphaThreshold(0.1f);
        
        clipper->setStencil(_clipperStencil);
        
        clipper->addChild(onSprite);
        clipper->addChild(offSprite);
        clipper->addChild(onLabel);
        clipper->addChild(offLabel);
        clipper->addChild(thumbSprite);
        
        addChild(clipper);

        // Set up the mask with the Mask shader
        setMaskTexture(maskSprite->getTexture());

        setContentSize(_maskTexture->getContentSize());

        needsLayout();
        return true;
    }
    return false;
}

void ControlSwitchSprite::updateTweenAction(float value, const std::string& key)
{
    CCLOGINFO("key = %s, value = %f", key.c_str(), value);
    setSliderXPosition(value);
}

void ControlSwitchSprite::needsLayout()
{
    _onSprite->setPosition(_onSprite->getContentSize().width / 2 + _sliderXPosition,
        _onSprite->getContentSize().height / 2);
    _offSprite->setPosition(_onSprite->getContentSize().width + _offSprite->getContentSize().width / 2 + _sliderXPosition,
        _offSprite->getContentSize().height / 2);
    _thumbSprite->setPosition(_onSprite->getContentSize().width + _sliderXPosition,
        _maskTexture->getContentSize().height / 2);

    _clipperStencil->setPosition(_maskTexture->getContentSize().width/2,
                                    _maskTexture->getContentSize().height / 2);

    if (_onLabel)
    {
        _onLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        _onLabel->setPosition(_onSprite->getPosition().x - _thumbSprite->getContentSize().width / 6,
            _onSprite->getContentSize().height / 2);
    }
    if (_offLabel)
    {
        _offLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        _offLabel->setPosition(_offSprite->getPosition().x + _thumbSprite->getContentSize().width / 6,
            _offSprite->getContentSize().height / 2);
    }

    setFlippedY(true);
}

void ControlSwitchSprite::setSliderXPosition(float sliderXPosition)
{
    if (sliderXPosition <= _offPosition)
    {
        // Off
        sliderXPosition = _offPosition;
    } else if (sliderXPosition >= _onPosition)
    {
        // On
        sliderXPosition = _onPosition;
    }

    _sliderXPosition    = sliderXPosition;

    needsLayout();
}


float ControlSwitchSprite::onSideWidth()
{
    return _onSprite->getContentSize().width;
}

float ControlSwitchSprite::offSideWidth()
{
    return _offSprite->getContentSize().height;
}


// ControlSwitch

ControlSwitch::ControlSwitch()
: _switchSprite(nullptr)
, _initialTouchXPosition(0.0f)
, _moved(false)
, _on(false)
{

}

ControlSwitch::~ControlSwitch()
{
    CC_SAFE_RELEASE(_switchSprite);
}

bool ControlSwitch::initWithMaskSprite(Sprite *maskSprite, Sprite * onSprite, Sprite * offSprite, Sprite * thumbSprite)
{
    return initWithMaskSprite(maskSprite, onSprite, offSprite, thumbSprite, nullptr, nullptr);
}

ControlSwitch* ControlSwitch::create(Sprite *maskSprite, Sprite * onSprite, Sprite * offSprite, Sprite * thumbSprite)
{
    ControlSwitch* pRet = new (std::nothrow) ControlSwitch();
    if (pRet && pRet->initWithMaskSprite(maskSprite, onSprite, offSprite, thumbSprite, nullptr, nullptr))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool ControlSwitch::initWithMaskSprite(Sprite *maskSprite, Sprite * onSprite, Sprite * offSprite, Sprite * thumbSprite, Label* onLabel, Label* offLabel)
{
    if (Control::init())
    {
        CCASSERT(maskSprite,    "Mask must not be nil.");
        CCASSERT(onSprite,      "onSprite must not be nil.");
        CCASSERT(offSprite,     "offSprite must not be nil.");
        CCASSERT(thumbSprite,   "thumbSprite must not be nil.");
        
        _on = true;

        _switchSprite = ControlSwitchSprite::create(maskSprite,
                                        onSprite,
                                        offSprite,
                                        thumbSprite,
                                        onLabel,
                                        offLabel);
        _switchSprite->retain();
        _switchSprite->setPosition(_switchSprite->getContentSize().width / 2, _switchSprite->getContentSize().height / 2);
        addChild(_switchSprite);
        
        ignoreAnchorPointForPosition(false);
        setAnchorPoint(Vec2(0.5f, 0.5f));
        setContentSize(_switchSprite->getContentSize());
        return true;
    }
    return false;
}

ControlSwitch* ControlSwitch::create(Sprite *maskSprite, Sprite * onSprite, Sprite * offSprite, Sprite * thumbSprite, Label* onLabel, Label* offLabel)
{
    ControlSwitch* pRet = new (std::nothrow) ControlSwitch();
    if (pRet && pRet->initWithMaskSprite(maskSprite, onSprite, offSprite, thumbSprite, onLabel, offLabel))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

void ControlSwitch::setOn(bool isOn)
{
    setOn(isOn, false);
}

void ControlSwitch::setOn(bool isOn, bool animated)
{
    _on = isOn;
    
    if (animated) {
        _switchSprite->runAction
        (
            ActionTween::create
                (
                    0.2f,
                    "sliderXPosition",
                    _switchSprite->getSliderXPosition(),
                    (_on) ? _switchSprite->getOnPosition() : _switchSprite->getOffPosition()
                )
         );
    }
    else {
        _switchSprite->setSliderXPosition((_on) ? _switchSprite->getOnPosition() : _switchSprite->getOffPosition());
    }
    
    sendActionsForControlEvents(Control::EventType::VALUE_CHANGED);
}

void ControlSwitch::setEnabled(bool enabled)
{
    _enabled = enabled;
    if (_switchSprite != nullptr)
    {
        _switchSprite->setOpacity((enabled) ? 255 : 128);
    } 
}

Vec2 ControlSwitch::locationFromTouch(Touch* pTouch)
{
    Vec2 touchLocation   = pTouch->getLocation();                      // Get the touch position
    touchLocation           = this->convertToNodeSpace(touchLocation);                  // Convert to the node space of this class
    
    return touchLocation;
}

bool ControlSwitch::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    if (!isTouchInside(pTouch) || !isEnabled() || !isVisible())
    {
        return false;
    }
    
    _moved = false;
    
    Vec2 location = this->locationFromTouch(pTouch);
    
    _initialTouchXPosition = location.x - _switchSprite->getSliderXPosition();
    
    _switchSprite->getThumbSprite()->setColor(Color3B::GRAY);
    _switchSprite->needsLayout();
    
    return true;
}

void ControlSwitch::onTouchMoved(Touch *pTouch, Event *pEvent)
{
    Vec2 location    = this->locationFromTouch(pTouch);
    location            = Vec2(location.x - _initialTouchXPosition, 0);
    
    _moved              = true;
    
    _switchSprite->setSliderXPosition(location.x);
}

void ControlSwitch::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    Vec2 location   = this->locationFromTouch(pTouch);
    
    _switchSprite->getThumbSprite()->setColor(Color3B::WHITE);
    
    if (hasMoved())
    {
        setOn(!(location.x < _switchSprite->getContentSize().width / 2), true);
    } 
    else
    {
        setOn(!_on, true);
    }
}

void ControlSwitch::onTouchCancelled(Touch *pTouch, Event *pEvent)
{
    Vec2 location   = this->locationFromTouch(pTouch);
    
    _switchSprite->getThumbSprite()->setColor(Color3B::WHITE);
    
    if (hasMoved())
    {
        setOn(!(location.x < _switchSprite->getContentSize().width / 2), true);
    } else
    {
        setOn(!_on, true);
    }
}

NS_CC_EXT_END
