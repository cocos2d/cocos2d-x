/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#include "UISlider.h"
#include "../../GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_EXT_BEGIN

UISlider::UISlider():
m_fBarLength(0.0),
m_nPercent(0),
m_fBarNodeScaleValue(1.0),
m_fTouchMoveStartLocation(0.0),
m_pBarRenderer(NULL),
m_pProgressBarRenderer(NULL),
m_pSlidBallNormalRenderer(NULL),
m_pSlidBallPressedRenderer(NULL),
m_pSlidBallDisabledRenderer(NULL),
m_pSlidBallRenderer(NULL),
m_pPercentListener(NULL),
m_pfnPercentSelector(NULL),
m_bScale9Enabled(false),
m_eBarTexType(UI_TEX_TYPE_LOCAL),
m_eBallNTexType(UI_TEX_TYPE_LOCAL),
m_eBallPTexType(UI_TEX_TYPE_LOCAL),
m_eBallDTexType(UI_TEX_TYPE_LOCAL),
m_eProgressBarTexType(UI_TEX_TYPE_LOCAL),
m_strTextureFile(""),
m_strProgressBarTextureFile(""),
m_strSlidBallNormalTextureFile(""),
m_strSlidBallPressedTextureFile(""),
m_strSlidBallDisabledTextureFile(""),
m_capInsets(CCRectZero),
m_ProgressBarTextureSize(CCSizeZero),
m_bPrevIgnoreSize(true)
{
}

UISlider::~UISlider()
{
    
}

UISlider* UISlider::create()
{
    UISlider* widget = new UISlider();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

void UISlider::initRenderer()
{
    UIWidget::initRenderer();
    m_pBarRenderer = CCSprite::create();
    m_pProgressBarRenderer = CCSprite::create();
    m_pProgressBarRenderer->setAnchorPoint(ccp(0.0f, 0.5f));
    m_pRenderer->addChild(m_pBarRenderer, -1);
    m_pRenderer->addChild(m_pProgressBarRenderer, -1);
    m_pSlidBallNormalRenderer = CCSprite::create();
    m_pSlidBallPressedRenderer = CCSprite::create();
    m_pSlidBallPressedRenderer->setVisible(false);
    m_pSlidBallDisabledRenderer = CCSprite::create();
    m_pSlidBallDisabledRenderer->setVisible(false);
    m_pSlidBallRenderer = CCNode::create();
    m_pSlidBallRenderer->addChild(m_pSlidBallNormalRenderer);
    m_pSlidBallRenderer->addChild(m_pSlidBallPressedRenderer);
    m_pSlidBallRenderer->addChild(m_pSlidBallDisabledRenderer);
    m_pRenderer->addChild(m_pSlidBallRenderer);
}

void UISlider::loadBarTexture(const char* fileName, TextureResType texType)
{
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return;
    }
    m_strTextureFile = fileName;
    m_eBarTexType = texType;
    switch (m_eBarTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            if (m_bScale9Enabled)
            {
                dynamic_cast<CCScale9Sprite*>(m_pBarRenderer)->initWithFile(fileName);
            }
            else
            {
                dynamic_cast<CCSprite*>(m_pBarRenderer)->initWithFile(fileName);
            }
            break;
        case UI_TEX_TYPE_PLIST:
            if (m_bScale9Enabled)
            {
                dynamic_cast<CCScale9Sprite*>(m_pBarRenderer)->initWithSpriteFrameName(fileName);
            }
            else
            {
                dynamic_cast<CCSprite*>(m_pBarRenderer)->initWithSpriteFrameName(fileName);
            }
            break;
        default:
            break;
    }
    if (m_bScale9Enabled)
    {
        dynamic_cast<CCScale9Sprite*>(m_pBarRenderer)->setColor(getColor());
        dynamic_cast<CCScale9Sprite*>(m_pBarRenderer)->setOpacity(getOpacity());
    }
    else
    {
        dynamic_cast<CCSprite*>(m_pBarRenderer)->setColor(getColor());
        dynamic_cast<CCSprite*>(m_pBarRenderer)->setOpacity(getOpacity());
    }
    barRendererScaleChangedWithSize();
}

void UISlider::loadProgressBarTexture(const char *fileName, TextureResType texType)
{
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return;
    }
    m_strProgressBarTextureFile = fileName;
    m_eProgressBarTexType = texType;
    switch (m_eProgressBarTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            if (m_bScale9Enabled)
            {
                dynamic_cast<CCScale9Sprite*>(m_pProgressBarRenderer)->initWithFile(fileName);
            }
            else
            {
                dynamic_cast<CCSprite*>(m_pProgressBarRenderer)->initWithFile(fileName);
            }
            break;
        case UI_TEX_TYPE_PLIST:
            if (m_bScale9Enabled)
            {
                dynamic_cast<CCScale9Sprite*>(m_pProgressBarRenderer)->initWithSpriteFrameName(fileName);
            }
            else
            {
                dynamic_cast<CCSprite*>(m_pProgressBarRenderer)->initWithSpriteFrameName(fileName);
            }
            break;
        default:
            break;
    }
    if (m_bScale9Enabled)
    {
        dynamic_cast<CCScale9Sprite*>(m_pProgressBarRenderer)->setColor(getColor());
        dynamic_cast<CCScale9Sprite*>(m_pProgressBarRenderer)->setOpacity(getOpacity());
    }
    else
    {
        dynamic_cast<CCSprite*>(m_pProgressBarRenderer)->setColor(getColor());
        dynamic_cast<CCSprite*>(m_pProgressBarRenderer)->setOpacity(getOpacity());
    }
    m_pProgressBarRenderer->setAnchorPoint(ccp(0.0f, 0.5f));
    m_ProgressBarTextureSize = m_pProgressBarRenderer->getContentSize();
    progressBarRendererScaleChangedWithSize();
}

void UISlider::setScale9Enabled(bool able)
{
    if (m_bScale9Enabled == able)
    {
        return;
    }
    
    m_bScale9Enabled = able;
    m_pRenderer->removeChild(m_pBarRenderer, true);
    m_pRenderer->removeChild(m_pProgressBarRenderer, true);
    m_pBarRenderer = NULL;
    m_pProgressBarRenderer = NULL;
    if (m_bScale9Enabled)
    {
        m_pBarRenderer = CCScale9Sprite::create();
        m_pProgressBarRenderer = CCScale9Sprite::create();
    }
    else
    {
        m_pBarRenderer = CCSprite::create();
        m_pProgressBarRenderer = CCSprite::create();
    }
    loadBarTexture(m_strTextureFile.c_str(), m_eBarTexType);
    loadProgressBarTexture(m_strProgressBarTextureFile.c_str(), m_eProgressBarTexType);
    m_pRenderer->addChild(m_pBarRenderer, -1);
    m_pRenderer->addChild(m_pProgressBarRenderer, -1);
    if (m_bScale9Enabled)
    {
        bool ignoreBefore = m_bIgnoreSize;
        ignoreContentAdaptWithSize(false);
        m_bPrevIgnoreSize = ignoreBefore;
    }
    else
    {
        ignoreContentAdaptWithSize(m_bPrevIgnoreSize);
    }
    setCapInsets(m_capInsets);
}

void UISlider::ignoreContentAdaptWithSize(bool ignore)
{
    if (!m_bScale9Enabled || (m_bScale9Enabled && !ignore))
    {
        UIWidget::ignoreContentAdaptWithSize(ignore);
        m_bPrevIgnoreSize = ignore;
    }
}

void UISlider::setCapInsets(const CCRect &capInsets)
{
    m_capInsets = capInsets;
    if (!m_bScale9Enabled)
    {
        return;
    }
    dynamic_cast<CCScale9Sprite*>(m_pBarRenderer)->setCapInsets(capInsets);
}

void UISlider::loadSlidBallTextures(const char* normal,const char* pressed,const char* disabled,TextureResType texType)
{
    loadSlidBallNormalTexture(normal, texType);
    loadSlidBallPressedTexture(pressed,texType);
    loadSlidBallDisabledTexture(disabled,texType);
}

void UISlider::loadSlidBallNormalTexture(const char* normal,TextureResType texType)
{
    if (!normal || strcmp(normal, "") == 0)
    {
        return;
    }
    m_strSlidBallNormalTextureFile = normal;
    m_eBallNTexType = texType;
    switch (m_eBallNTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            m_pSlidBallNormalRenderer->initWithFile(normal);
            break;
        case UI_TEX_TYPE_PLIST:
            m_pSlidBallNormalRenderer->initWithSpriteFrameName(normal);
            break;
        default:
            break;
    }
    m_pSlidBallNormalRenderer->setColor(getColor());
    m_pSlidBallNormalRenderer->setOpacity(getOpacity());
}

void UISlider::loadSlidBallPressedTexture(const char* pressed,TextureResType texType)
{
    if (!pressed || strcmp(pressed, "") == 0)
    {
        return;
    }
    m_strSlidBallPressedTextureFile = pressed;
    m_eBallPTexType = texType;
    switch (m_eBallPTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            m_pSlidBallPressedRenderer->initWithFile(pressed);
            break;
        case UI_TEX_TYPE_PLIST:
            m_pSlidBallPressedRenderer->initWithSpriteFrameName(pressed);
            break;
        default:
            break;
    }
    m_pSlidBallPressedRenderer->setColor(getColor());
    m_pSlidBallPressedRenderer->setOpacity(getOpacity());
}

void UISlider::loadSlidBallDisabledTexture(const char* disabled,TextureResType texType)
{
    if (!disabled || strcmp(disabled, "") == 0)
    {
        return;
    }
    m_strSlidBallDisabledTextureFile = disabled;
    m_eBallDTexType = texType;
    switch (m_eBallDTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            m_pSlidBallDisabledRenderer->initWithFile(disabled);
            break;
        case UI_TEX_TYPE_PLIST:
            m_pSlidBallDisabledRenderer->initWithSpriteFrameName(disabled);
            break;
        default:
            break;
    }
    m_pSlidBallDisabledRenderer->setColor(getColor());
    m_pSlidBallDisabledRenderer->setOpacity(getOpacity());
}

void UISlider::setPercent(int percent)
{
    if (percent > 100)
    {
        percent = 100;
    }
    if (percent < 0)
    {
        percent = 0;
    }
    m_nPercent = percent;
    float dis = m_fBarLength*(percent/100.0f);
    m_pSlidBallRenderer->setPosition(ccp(-m_fBarLength/2.0f + dis, 0.0f));
    if (m_bScale9Enabled)
    {
        dynamic_cast<CCScale9Sprite*>(m_pProgressBarRenderer)->setPreferredSize(CCSizeMake(dis,m_ProgressBarTextureSize.height));
    }
    else
    {
        int x = 0, y = 0;
        switch (m_eProgressBarTexType)
        {
            case UI_TEX_TYPE_PLIST:
            {
                CCSprite* barNode = dynamic_cast<CCSprite*>(m_pProgressBarRenderer);
                if (barNode)
                {
                    CCPoint to = barNode->getTextureRect().origin;
                    x = to.x;
                    y = to.y;
                }
                break;
            }
            default:
                break;
        }
        dynamic_cast<CCSprite*>(m_pProgressBarRenderer)->setTextureRect(CCRectMake(x, y, m_ProgressBarTextureSize.width * (percent/100.0f), m_ProgressBarTextureSize.height));
    }
}

bool UISlider::onTouchBegan(const CCPoint &touchPoint)
{
    bool pass = UIWidget::onTouchBegan(touchPoint);
    CCPoint nsp = m_pRenderer->convertToNodeSpace(touchPoint);
    setPercent(getPercentWithBallPos(nsp.x));
    percentChangedEvent();
    return pass;
}

void UISlider::onTouchMoved(const CCPoint &touchPoint)
{
    CCPoint nsp = m_pRenderer->convertToNodeSpace(touchPoint);
    m_pSlidBallRenderer->setPosition(ccp(nsp.x,0));
    setPercent(getPercentWithBallPos(nsp.x));
    percentChangedEvent();
}

void UISlider::onTouchEnded(const CCPoint &touchPoint)
{
    UIWidget::onTouchEnded(touchPoint);
}

void UISlider::onTouchCancelled(const CCPoint &touchPoint)
{
    UIWidget::onTouchCancelled(touchPoint);
}

float UISlider::getPercentWithBallPos(float px)
{
    return (((px-(-m_fBarLength/2.0f))/m_fBarLength)*100.0f);
}

void UISlider::addPercentChangedEvent(CCObject *target, SEL_PushEvent selector)
{
    m_pPercentListener = target;
    m_pfnPercentSelector = selector;
}

void UISlider::percentChangedEvent()
{
    if (m_pPercentListener && m_pfnPercentSelector)
    {
        (m_pPercentListener->*m_pfnPercentSelector)(this);
    }
}

int UISlider::getPercent()
{
    return m_nPercent;
}

void UISlider::onSizeChanged()
{
    barRendererScaleChangedWithSize();
    progressBarRendererScaleChangedWithSize();
}

const CCSize& UISlider::getContentSize() const
{
    return m_pBarRenderer->getContentSize();
}

CCNode* UISlider::getVirtualRenderer()
{
    return m_pBarRenderer;
}

void UISlider::barRendererScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
        
        m_pBarRenderer->setScale(1.0f);
        m_size = m_pBarRenderer->getContentSize();
        m_fBarLength = m_size.width;
    }
    else
    {
        m_fBarLength = m_size.width;
        if (m_bScale9Enabled)
        {
            dynamic_cast<CCScale9Sprite*>(m_pBarRenderer)->setPreferredSize(m_size);
        }
        else
        {
            CCSize btextureSize = m_pBarRenderer->getContentSize();
            if (btextureSize.width <= 0.0f || btextureSize.height <= 0.0f)
            {
                m_pBarRenderer->setScale(1.0f);
                return;
            }
            float bscaleX = m_size.width / btextureSize.width;
            float bscaleY = m_size.height / btextureSize.height;
            m_pBarRenderer->setScaleX(bscaleX);
            m_pBarRenderer->setScaleY(bscaleY);
        }
    }
    setPercent(m_nPercent);
}

void UISlider::progressBarRendererScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
        if (!m_bScale9Enabled)
        {
            CCSize ptextureSize = m_ProgressBarTextureSize;
            float pscaleX = m_size.width / ptextureSize.width;
            float pscaleY = m_size.height / ptextureSize.height;
            m_pProgressBarRenderer->setScaleX(pscaleX);
            m_pProgressBarRenderer->setScaleY(pscaleY);
        }
    }
    else
    {
        if (m_bScale9Enabled)
        {
            dynamic_cast<CCScale9Sprite*>(m_pProgressBarRenderer)->setPreferredSize(m_size);
        }
        else
        {
            CCSize ptextureSize = m_ProgressBarTextureSize;
            if (ptextureSize.width <= 0.0f || ptextureSize.height <= 0.0f)
            {
                m_pProgressBarRenderer->setScale(1.0f);
                return;
            }
            float pscaleX = m_size.width / ptextureSize.width;
            float pscaleY = m_size.height / ptextureSize.height;
            m_pProgressBarRenderer->setScaleX(pscaleX);
            m_pProgressBarRenderer->setScaleY(pscaleY);
        }
    }
    m_pProgressBarRenderer->setPosition(ccp(-m_fBarLength * 0.5f, 0.0f));
    setPercent(m_nPercent);
}

void UISlider::onPressStateChangedToNormal()
{
    m_pSlidBallNormalRenderer->setVisible(true);
    m_pSlidBallPressedRenderer->setVisible(false);
    m_pSlidBallDisabledRenderer->setVisible(false);
}

void UISlider::onPressStateChangedToPressed()
{
    m_pSlidBallNormalRenderer->setVisible(false);
    m_pSlidBallPressedRenderer->setVisible(true);
    m_pSlidBallDisabledRenderer->setVisible(false);
}

void UISlider::onPressStateChangedToDisabled()
{
    m_pSlidBallNormalRenderer->setVisible(false);
    m_pSlidBallPressedRenderer->setVisible(false);
    m_pSlidBallDisabledRenderer->setVisible(true);
}
NS_CC_EXT_END