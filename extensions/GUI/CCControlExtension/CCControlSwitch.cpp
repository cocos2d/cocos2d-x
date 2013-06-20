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
#include "cocos2d.h"

NS_CC_EXT_BEGIN
// ControlSwitchSprite

class ControlSwitchSprite : public Sprite, public ActionTweenDelegate
{
public:
    ControlSwitchSprite();
    virtual ~ControlSwitchSprite();
    bool initWithMaskSprite(
        Sprite *maskSprite, 
        Sprite *onSprite, 
        Sprite *offSprite,
        Sprite *thumbSprite,
        LabelTTF* onLabel, 
        LabelTTF* offLabel);
    void draw();
    void needsLayout();
    void setSliderXPosition(float sliderXPosition);
    float getSliderXPosition() {return _sliderXPosition;}
    float onSideWidth();
    float offSideWidth();
    virtual void updateTweenAction(float value, const char* key);
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
    CC_SYNTHESIZE_RETAIN(LabelTTF*, _onLabel, OnLabel)
    CC_SYNTHESIZE_RETAIN(LabelTTF*, _offLabel, OffLabel)
};

ControlSwitchSprite::ControlSwitchSprite()
: _sliderXPosition(0.0f)
, _onPosition(0.0f)
, _offPosition(0.0f)
, _maskTexture(NULL)
, _textureLocation(0)
, _maskLocation(0)
, _onSprite(NULL)
, _offSprite(NULL)
, _thumbSprite(NULL)
, _onLabel(NULL)
, _offLabel(NULL)
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
}

bool ControlSwitchSprite::initWithMaskSprite(
    Sprite *maskSprite, 
    Sprite *onSprite, 
    Sprite *offSprite,
    Sprite *thumbSprite,
    LabelTTF* onLabel, 
    LabelTTF* offLabel)
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

        addChild(_thumbSprite);

        // Set up the mask with the Mask shader
        setMaskTexture(maskSprite->getTexture());
        GLProgram* pProgram = new GLProgram();
        pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, ccExSwitchMask_frag);
        setShaderProgram(pProgram);
        pProgram->release();

        CHECK_GL_ERROR_DEBUG();

        getShaderProgram()->addAttribute(kAttributeNamePosition, kVertexAttrib_Position);
        getShaderProgram()->addAttribute(kAttributeNameColor, kVertexAttrib_Color);
        getShaderProgram()->addAttribute(kAttributeNameTexCoord, kVertexAttrib_TexCoords);
        CHECK_GL_ERROR_DEBUG();

        getShaderProgram()->link();
        CHECK_GL_ERROR_DEBUG();

        getShaderProgram()->updateUniforms();
        CHECK_GL_ERROR_DEBUG();                

        _textureLocation    = glGetUniformLocation( getShaderProgram()->getProgram(), "u_texture");
        _maskLocation       = glGetUniformLocation( getShaderProgram()->getProgram(), "u_mask");
        CHECK_GL_ERROR_DEBUG();

        setContentSize(_maskTexture->getContentSize());

        needsLayout();
        return true;
    }
    return false;
}

void ControlSwitchSprite::updateTweenAction(float value, const char* key)
{
    CCLOG("key = %s, value = %f", key, value);
    setSliderXPosition(value);
}

void ControlSwitchSprite::draw()
{
    CC_NODE_DRAW_SETUP();

    ccGLEnableVertexAttribs(kVertexAttribFlag_PosColorTex);
    ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    getShaderProgram()->setUniformsForBuiltins();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture( GL_TEXTURE_2D, getTexture()->getName());
    glUniform1i(_textureLocation, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture( GL_TEXTURE_2D, _maskTexture->getName() );
    glUniform1i(_maskLocation, 1);

#define kQuadSize sizeof(_quad.bl)
#ifdef EMSCRIPTEN
    long offset = 0;
    setGLBufferData(&_quad, 4 * kQuadSize, 0);
#else
    long offset = (long)&_quad;
#endif // EMSCRIPTEN

    // vertex
    int diff = offsetof( ccV3F_C4B_T2F, vertices);
    glVertexAttribPointer(kVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

    // texCoods
    diff = offsetof( ccV3F_C4B_T2F, texCoords);
    glVertexAttribPointer(kVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

    // color
    diff = offsetof( ccV3F_C4B_T2F, colors);
    glVertexAttribPointer(kVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);    
    glActiveTexture(GL_TEXTURE0);
}

void ControlSwitchSprite::needsLayout()
{
    _onSprite->setPosition(ccp(_onSprite->getContentSize().width / 2 + _sliderXPosition,
        _onSprite->getContentSize().height / 2));
    _offSprite->setPosition(ccp(_onSprite->getContentSize().width + _offSprite->getContentSize().width / 2 + _sliderXPosition, 
        _offSprite->getContentSize().height / 2));
    _thumbSprite->setPosition(ccp(_onSprite->getContentSize().width + _sliderXPosition,
        _maskTexture->getContentSize().height / 2));

    if (_onLabel)
    {
        _onLabel->setPosition(ccp(_onSprite->getPosition().x - _thumbSprite->getContentSize().width / 6,
            _onSprite->getContentSize().height / 2));
    }
    if (_offLabel)
    {
        _offLabel->setPosition(ccp(_offSprite->getPosition().x + _thumbSprite->getContentSize().width / 6,
            _offSprite->getContentSize().height / 2));
    }

    RenderTexture *rt = RenderTexture::create((int)_maskTexture->getContentSize().width, (int)_maskTexture->getContentSize().height);

    rt->begin();
    _onSprite->visit();
    _offSprite->visit();

    if (_onLabel)
    {
        _onLabel->visit();
    }
    if (_offLabel)
    {
        _offLabel->visit();
    }

    rt->end();

    setTexture(rt->getSprite()->getTexture());
    setFlipY(true);
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
: _switchSprite(NULL)
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
    return initWithMaskSprite(maskSprite, onSprite, offSprite, thumbSprite, NULL, NULL);
}

ControlSwitch* ControlSwitch::create(Sprite *maskSprite, Sprite * onSprite, Sprite * offSprite, Sprite * thumbSprite)
{
    ControlSwitch* pRet = new ControlSwitch();
    if (pRet && pRet->initWithMaskSprite(maskSprite, onSprite, offSprite, thumbSprite, NULL, NULL))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool ControlSwitch::initWithMaskSprite(Sprite *maskSprite, Sprite * onSprite, Sprite * offSprite, Sprite * thumbSprite, LabelTTF* onLabel, LabelTTF* offLabel)
{
    if (Control::init())
    {
        CCAssert(maskSprite,    "Mask must not be nil.");
        CCAssert(onSprite,      "onSprite must not be nil.");
        CCAssert(offSprite,     "offSprite must not be nil.");
        CCAssert(thumbSprite,   "thumbSprite must not be nil.");
        
        setTouchEnabled(true);
        _on = true;

        _switchSprite = new ControlSwitchSprite();
        _switchSprite->initWithMaskSprite(maskSprite,
                                            onSprite,
                                           offSprite,
                                           thumbSprite,
                                           onLabel,
                                           offLabel);
        _switchSprite->setPosition(ccp (_switchSprite->getContentSize().width / 2, _switchSprite->getContentSize().height / 2));
        addChild(_switchSprite);
        
        ignoreAnchorPointForPosition(false);
        setAnchorPoint(ccp (0.5f, 0.5f));
        setContentSize(_switchSprite->getContentSize());
        return true;
    }
    return false;
}

ControlSwitch* ControlSwitch::create(Sprite *maskSprite, Sprite * onSprite, Sprite * offSprite, Sprite * thumbSprite, LabelTTF* onLabel, LabelTTF* offLabel)
{
    ControlSwitch* pRet = new ControlSwitch();
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
    _on     = isOn;
    
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
    
    sendActionsForControlEvents(ControlEventValueChanged);
}

void ControlSwitch::setEnabled(bool enabled)
{
    _enabled = enabled;
    if (_switchSprite != NULL)
    {
        _switchSprite->setOpacity((enabled) ? 255 : 128);
    } 
}

Point ControlSwitch::locationFromTouch(Touch* pTouch)
{
    Point touchLocation   = pTouch->getLocation();                      // Get the touch position
    touchLocation           = this->convertToNodeSpace(touchLocation);                  // Convert to the node space of this class
    
    return touchLocation;
}

bool ControlSwitch::ccTouchBegan(Touch *pTouch, Event *pEvent)
{
    if (!isTouchInside(pTouch) || !isEnabled() || !isVisible())
    {
        return false;
    }
    
    _moved = false;
    
    Point location = this->locationFromTouch(pTouch);
    
    _initialTouchXPosition = location.x - _switchSprite->getSliderXPosition();
    
    _switchSprite->getThumbSprite()->setColor(ccGRAY);
    _switchSprite->needsLayout();
    
    return true;
}

void ControlSwitch::ccTouchMoved(Touch *pTouch, Event *pEvent)
{
    Point location    = this->locationFromTouch(pTouch);
    location            = ccp (location.x - _initialTouchXPosition, 0);
    
    _moved              = true;
    
    _switchSprite->setSliderXPosition(location.x);
}

void ControlSwitch::ccTouchEnded(Touch *pTouch, Event *pEvent)
{
    Point location   = this->locationFromTouch(pTouch);
    
    _switchSprite->getThumbSprite()->setColor(ccWHITE);
    
    if (hasMoved())
    {
        setOn(!(location.x < _switchSprite->getContentSize().width / 2), true);
    } 
    else
    {
        setOn(!_on, true);
    }
}

void ControlSwitch::ccTouchCancelled(Touch *pTouch, Event *pEvent)
{
    Point location   = this->locationFromTouch(pTouch);
    
    _switchSprite->getThumbSprite()->setColor(ccWHITE);
    
    if (hasMoved())
    {
        setOn(!(location.x < _switchSprite->getContentSize().width / 2), true);
    } else
    {
        setOn(!_on, true);
    }
}

NS_CC_EXT_END
