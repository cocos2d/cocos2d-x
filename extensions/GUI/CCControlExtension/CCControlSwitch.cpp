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
// CCControlSwitchSprite

class CCControlSwitchSprite : public CCSprite, public CCActionTweenDelegate
{
public:
    CCControlSwitchSprite();
    virtual ~CCControlSwitchSprite();
    bool initWithMaskSprite(
        CCSprite *maskSprite, 
        CCSprite *onSprite, 
        CCSprite *offSprite,
        CCSprite *thumbSprite,
        CCLabelTTF* onLabel, 
        CCLabelTTF* offLabel);
    void draw();
    void needsLayout();
    void setSliderXPosition(float sliderXPosition);
    float getSliderXPosition() {return m_fSliderXPosition;}
    float onSideWidth();
    float offSideWidth();
    virtual void updateTweenAction(float value, const char* key);
/** Contains the position (in x-axis) of the slider inside the receiver. */
    float m_fSliderXPosition;
    CC_SYNTHESIZE(float, m_fOnPosition, OnPosition)
    CC_SYNTHESIZE(float, m_fOffPosition, OffPosition)
    
    CC_SYNTHESIZE_RETAIN(CCTexture2D*, m_pMaskTexture, MaskTexture)
    CC_SYNTHESIZE(GLuint, m_uTextureLocation, TextureLocation)
    CC_SYNTHESIZE(GLuint, m_uMaskLocation, MaskLocation)
    
    CC_SYNTHESIZE_RETAIN(CCSprite*, m_pOnSprite, OnSprite)
    CC_SYNTHESIZE_RETAIN(CCSprite*, m_pOffSprite, OffSprite)
    CC_SYNTHESIZE_RETAIN(CCSprite*, m_ThumbSprite, ThumbSprite)
    CC_SYNTHESIZE_RETAIN(CCLabelTTF*, m_pOnLabel, OnLabel)
    CC_SYNTHESIZE_RETAIN(CCLabelTTF*, m_pOffLabel, OffLabel)
};

CCControlSwitchSprite::CCControlSwitchSprite()
: m_fSliderXPosition(0.0f)
, m_fOnPosition(0.0f)
, m_fOffPosition(0.0f)
, m_pMaskTexture(NULL)
, m_uTextureLocation(0)
, m_uMaskLocation(0)
, m_pOnSprite(NULL)
, m_pOffSprite(NULL)
, m_ThumbSprite(NULL)
, m_pOnLabel(NULL)
, m_pOffLabel(NULL)
{

}

CCControlSwitchSprite::~CCControlSwitchSprite()
{
    CC_SAFE_RELEASE(m_pOnSprite);
    CC_SAFE_RELEASE(m_pOffSprite);
    CC_SAFE_RELEASE(m_ThumbSprite);
    CC_SAFE_RELEASE(m_pOnLabel);
    CC_SAFE_RELEASE(m_pOffLabel);
    CC_SAFE_RELEASE(m_pMaskTexture);
}

bool CCControlSwitchSprite::initWithMaskSprite(
    CCSprite *maskSprite, 
    CCSprite *onSprite, 
    CCSprite *offSprite,
    CCSprite *thumbSprite,
    CCLabelTTF* onLabel, 
    CCLabelTTF* offLabel)
{
    if (CCSprite::initWithTexture(maskSprite->getTexture()))
    {
        // Sets the default values
        m_fOnPosition             = 0;
        m_fOffPosition            = -onSprite->getContentSize().width + thumbSprite->getContentSize().width / 2;
        m_fSliderXPosition        = m_fOnPosition; 

        setOnSprite(onSprite);
        setOffSprite(offSprite);
        setThumbSprite(thumbSprite);
        setOnLabel(onLabel);
        setOffLabel(offLabel);

        addChild(m_ThumbSprite);

        // Set up the mask with the Mask shader
        setMaskTexture(maskSprite->getTexture());
        CCGLProgram* pProgram = new CCGLProgram();
        pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, ccExSwitchMask_frag);
        setShaderProgram(pProgram);
        pProgram->release();

        CHECK_GL_ERROR_DEBUG();

        getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
        getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
        getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
        CHECK_GL_ERROR_DEBUG();

        getShaderProgram()->link();
        CHECK_GL_ERROR_DEBUG();

        getShaderProgram()->updateUniforms();
        CHECK_GL_ERROR_DEBUG();                

        m_uTextureLocation    = glGetUniformLocation( getShaderProgram()->getProgram(), "u_texture");
        m_uMaskLocation       = glGetUniformLocation( getShaderProgram()->getProgram(), "u_mask");
        CHECK_GL_ERROR_DEBUG();

        setContentSize(m_pMaskTexture->getContentSize());

        needsLayout();
        return true;
    }
    return false;
}

void CCControlSwitchSprite::updateTweenAction(float value, const char* key)
{
    CCLOG("key = %s, value = %f", key, value);
    setSliderXPosition(value);
}

void CCControlSwitchSprite::draw()
{
    CC_NODE_DRAW_SETUP();

    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);
    ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    getShaderProgram()->setUniformsForBuiltins();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture( GL_TEXTURE_2D, getTexture()->getName());
    glUniform1i(m_uTextureLocation, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture( GL_TEXTURE_2D, m_pMaskTexture->getName() );
    glUniform1i(m_uMaskLocation, 1);

#define kQuadSize sizeof(m_sQuad.bl)
    long offset = (long)&m_sQuad;

    // vertex
    int diff = offsetof( ccV3F_C4B_T2F, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

    // texCoods
    diff = offsetof( ccV3F_C4B_T2F, texCoords);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

    // color
    diff = offsetof( ccV3F_C4B_T2F, colors);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);    
    glActiveTexture(GL_TEXTURE0);
}

void CCControlSwitchSprite::needsLayout()
{
    m_pOnSprite->setPosition(ccp(m_pOnSprite->getContentSize().width / 2 + m_fSliderXPosition,
        m_pOnSprite->getContentSize().height / 2));
    m_pOffSprite->setPosition(ccp(m_pOnSprite->getContentSize().width + m_pOffSprite->getContentSize().width / 2 + m_fSliderXPosition, 
        m_pOffSprite->getContentSize().height / 2));
    m_ThumbSprite->setPosition(ccp(m_pOnSprite->getContentSize().width + m_fSliderXPosition,
        m_pMaskTexture->getContentSize().height / 2));

    if (m_pOnLabel)
    {
        m_pOnLabel->setPosition(ccp(m_pOnSprite->getPosition().x - m_ThumbSprite->getContentSize().width / 6,
            m_pOnSprite->getContentSize().height / 2));
    }
    if (m_pOffLabel)
    {
        m_pOffLabel->setPosition(ccp(m_pOffSprite->getPosition().x + m_ThumbSprite->getContentSize().width / 6,
            m_pOffSprite->getContentSize().height / 2));
    }

    CCRenderTexture *rt = CCRenderTexture::create((int)m_pMaskTexture->getContentSize().width, (int)m_pMaskTexture->getContentSize().height);

    rt->begin();
    m_pOnSprite->visit();
    m_pOffSprite->visit();

    if (m_pOnLabel)
    {
        m_pOnLabel->visit();
    }
    if (m_pOffLabel)
    {
        m_pOffLabel->visit();
    }

    rt->end();

    setTexture(rt->getSprite()->getTexture());
    setFlipY(true);
}

void CCControlSwitchSprite::setSliderXPosition(float sliderXPosition)
{
    if (sliderXPosition <= m_fOffPosition)
    {
        // Off
        sliderXPosition = m_fOffPosition;
    } else if (sliderXPosition >= m_fOnPosition)
    {
        // On
        sliderXPosition = m_fOnPosition;
    }

    m_fSliderXPosition    = sliderXPosition;

    needsLayout();
}


float CCControlSwitchSprite::onSideWidth()
{
    return m_pOnSprite->getContentSize().width;
}

float CCControlSwitchSprite::offSideWidth()
{
    return m_pOffSprite->getContentSize().height;
}


// CCControlSwitch

CCControlSwitch::CCControlSwitch()
: m_pSwitchSprite(NULL)
, m_fInitialTouchXPosition(0.0f)
, m_bMoved(false)
, m_bOn(false)
{

}

CCControlSwitch::~CCControlSwitch()
{
    CC_SAFE_RELEASE(m_pSwitchSprite);
}

bool CCControlSwitch::initWithMaskSprite(CCSprite *maskSprite, CCSprite * onSprite, CCSprite * offSprite, CCSprite * thumbSprite)
{
    return initWithMaskSprite(maskSprite, onSprite, offSprite, thumbSprite, NULL, NULL);
}

CCControlSwitch* CCControlSwitch::create(CCSprite *maskSprite, CCSprite * onSprite, CCSprite * offSprite, CCSprite * thumbSprite)
{
    CCControlSwitch* pRet = new CCControlSwitch();
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

bool CCControlSwitch::initWithMaskSprite(CCSprite *maskSprite, CCSprite * onSprite, CCSprite * offSprite, CCSprite * thumbSprite, CCLabelTTF* onLabel, CCLabelTTF* offLabel)
{
    if (CCControl::init())
    {
        CCAssert(maskSprite,    "Mask must not be nil.");
        CCAssert(onSprite,      "onSprite must not be nil.");
        CCAssert(offSprite,     "offSprite must not be nil.");
        CCAssert(thumbSprite,   "thumbSprite must not be nil.");
        
        setTouchEnabled(true);
        m_bOn = true;

        m_pSwitchSprite = new CCControlSwitchSprite();
        m_pSwitchSprite->initWithMaskSprite(maskSprite,
                                            onSprite,
                                           offSprite,
                                           thumbSprite,
                                           onLabel,
                                           offLabel);
        m_pSwitchSprite->setPosition(ccp (m_pSwitchSprite->getContentSize().width / 2, m_pSwitchSprite->getContentSize().height / 2));
        addChild(m_pSwitchSprite);
        
        ignoreAnchorPointForPosition(false);
        setAnchorPoint(ccp (0.5f, 0.5f));
        setContentSize(m_pSwitchSprite->getContentSize());
        return true;
    }
    return false;
}

CCControlSwitch* CCControlSwitch::create(CCSprite *maskSprite, CCSprite * onSprite, CCSprite * offSprite, CCSprite * thumbSprite, CCLabelTTF* onLabel, CCLabelTTF* offLabel)
{
    CCControlSwitch* pRet = new CCControlSwitch();
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

void CCControlSwitch::setOn(bool isOn)
{
    setOn(isOn, false);
}

void CCControlSwitch::setOn(bool isOn, bool animated)
{
    m_bOn     = isOn;

    m_pSwitchSprite->runAction
    (
        CCActionTween::create
            (
                0.2f, 
                "sliderXPosition",
                m_pSwitchSprite->getSliderXPosition(),
                (m_bOn) ? m_pSwitchSprite->getOnPosition() : m_pSwitchSprite->getOffPosition()
            )
    );
    
    sendActionsForControlEvents(CCControlEventValueChanged);
}

void CCControlSwitch::setEnabled(bool enabled)
{
    m_bEnabled = enabled;
    if (m_pSwitchSprite != NULL)
    {
        m_pSwitchSprite->setOpacity((enabled) ? 255 : 128);
    } 
}

CCPoint CCControlSwitch::locationFromTouch(CCTouch* pTouch)
{
    CCPoint touchLocation   = pTouch->getLocation();                      // Get the touch position
    touchLocation           = this->convertToNodeSpace(touchLocation);                  // Convert to the node space of this class
    
    return touchLocation;
}

bool CCControlSwitch::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!isTouchInside(pTouch) || !isEnabled() || !isVisible())
    {
        return false;
    }
    
    m_bMoved = false;
    
    CCPoint location = this->locationFromTouch(pTouch);
    
    m_fInitialTouchXPosition = location.x - m_pSwitchSprite->getSliderXPosition();
    
    m_pSwitchSprite->getThumbSprite()->setColor(ccGRAY);
    m_pSwitchSprite->needsLayout();
    
    return true;
}

void CCControlSwitch::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint location    = this->locationFromTouch(pTouch);
    location            = ccp (location.x - m_fInitialTouchXPosition, 0);
    
    m_bMoved              = true;
    
    m_pSwitchSprite->setSliderXPosition(location.x);
}

void CCControlSwitch::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint location   = this->locationFromTouch(pTouch);
    
    m_pSwitchSprite->getThumbSprite()->setColor(ccWHITE);
    
    if (hasMoved())
    {
        setOn(!(location.x < m_pSwitchSprite->getContentSize().width / 2), true);
    } 
    else
    {
        setOn(!m_bOn, true);
    }
}

void CCControlSwitch::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint location   = this->locationFromTouch(pTouch);
    
    m_pSwitchSprite->getThumbSprite()->setColor(ccWHITE);
    
    if (hasMoved())
    {
        setOn(!(location.x < m_pSwitchSprite->getContentSize().width / 2), true);
    } else
    {
        setOn(!m_bOn, true);
    }
}

NS_CC_EXT_END
