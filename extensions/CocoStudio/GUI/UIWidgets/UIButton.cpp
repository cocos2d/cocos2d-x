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

#include "UIButton.h"
#include "../../../GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_EXT_BEGIN

#define NORMALRENDERERZ (0)
#define PRESSEDRENDERERZ (0)
#define DISABLEDRENDERERZ (0)
#define TITLERENDERERZ (1)
    
UIButton::UIButton():
m_pButtonNormalRenderer(NULL),
m_pButtonClickedRenderer(NULL),
m_pButtonDisableRenderer(NULL),
m_pTitleRenderer(NULL),
m_strNormalFileName(""),
m_strClickedFileName(""),
m_strDisabledFileName(""),
m_bPrevIgnoreSize(true),
m_bScale9Enabled(false),
m_capInsetsNormal(CCRectZero),
m_capInsetsPressed(CCRectZero),
m_capInsetsDisabled(CCRectZero),
m_eNormalTexType(UI_TEX_TYPE_LOCAL),
m_ePressedTexType(UI_TEX_TYPE_LOCAL),
m_eDisabledTexType(UI_TEX_TYPE_LOCAL),
m_normalTextureSize(m_size),
m_pressedTextureSize(m_size),
m_disabledTextureSize(m_size),
m_bPressedActionEnabled(false),
m_titleColor(ccWHITE)
{
    
}

UIButton::~UIButton()
{
}

UIButton* UIButton::create()
{
    UIButton* widget = new UIButton();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UIButton::init()
{
    if (UIWidget::init())
    {
        return true;
    }
    return false;
}

void UIButton::initRenderer()
{
    UIWidget::initRenderer();
    m_pButtonNormalRenderer = CCSprite::create();
    m_pButtonClickedRenderer = CCSprite::create();
    m_pButtonDisableRenderer = CCSprite::create();
    m_pTitleRenderer = CCLabelTTF::create();
    m_pRenderer->addChild(m_pButtonNormalRenderer,NORMALRENDERERZ);
    m_pRenderer->addChild(m_pButtonClickedRenderer,PRESSEDRENDERERZ);
    m_pRenderer->addChild(m_pButtonDisableRenderer,DISABLEDRENDERERZ);
    m_pRenderer->addChild(m_pTitleRenderer,TITLERENDERERZ);
}

void UIButton::setScale9Enabled(bool able)
{
    if (m_bScale9Enabled == able)
    {
        return;
    }
    m_eBrightStyle = BRIGHT_NONE;
    m_bScale9Enabled = able;

    
    m_pRenderer->removeChild(m_pButtonNormalRenderer, true);
    m_pRenderer->removeChild(m_pButtonClickedRenderer, true);
    m_pRenderer->removeChild(m_pButtonDisableRenderer, true);
    
    m_pButtonNormalRenderer = NULL;
    m_pButtonClickedRenderer = NULL;
    m_pButtonDisableRenderer = NULL;
    if (m_bScale9Enabled)
    {
        m_pButtonNormalRenderer = CCScale9Sprite::create();
        m_pButtonClickedRenderer = CCScale9Sprite::create();
        m_pButtonDisableRenderer = CCScale9Sprite::create();
    }
    else
    {
        m_pButtonNormalRenderer = CCSprite::create();
        m_pButtonClickedRenderer = CCSprite::create();
        m_pButtonDisableRenderer = CCSprite::create();
    }

    loadTextureNormal(m_strNormalFileName.c_str(), m_eNormalTexType);
    loadTexturePressed(m_strClickedFileName.c_str(), m_ePressedTexType);
    loadTextureDisabled(m_strDisabledFileName.c_str(), m_eDisabledTexType);
    m_pRenderer->addChild(m_pButtonNormalRenderer,NORMALRENDERERZ);
    m_pRenderer->addChild(m_pButtonClickedRenderer,PRESSEDRENDERERZ);
    m_pRenderer->addChild(m_pButtonDisableRenderer,DISABLEDRENDERERZ);
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
    setCapInsetsNormalRenderer(m_capInsetsNormal);
    setCapInsetsPressedRenderer(m_capInsetsPressed);
    setCapInsetsDisabledRenderer(m_capInsetsDisabled);
    setBright(m_bBright);
}

void UIButton::ignoreContentAdaptWithSize(bool ignore)
{
    if (!m_bScale9Enabled || (m_bScale9Enabled && !ignore))
    {
        UIWidget::ignoreContentAdaptWithSize(ignore);
        m_bPrevIgnoreSize = ignore;
    }
}

void UIButton::loadTextures(const char* normal,const char* selected,const char* disabled,TextureResType texType)
{
    loadTextureNormal(normal,texType);
    loadTexturePressed(selected,texType);
    loadTextureDisabled(disabled,texType);
}

void UIButton::loadTextureNormal(const char* normal,TextureResType texType)
{
    if (!normal || strcmp(normal, "") == 0)
    {
        return;
    }
    m_strNormalFileName = normal;
    m_eNormalTexType = texType;
    if (m_bScale9Enabled)
    {
        switch (m_eNormalTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<CCScale9Sprite*>(m_pButtonNormalRenderer)->initWithFile(normal);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<CCScale9Sprite*>(m_pButtonNormalRenderer)->initWithSpriteFrameName(normal);
                break;
            default:
                break;
        }
        dynamic_cast<CCScale9Sprite*>(m_pButtonNormalRenderer)->setColor(getColor());
        dynamic_cast<CCScale9Sprite*>(m_pButtonNormalRenderer)->setOpacity(getOpacity());
        dynamic_cast<CCScale9Sprite*>(m_pButtonNormalRenderer)->setCapInsets(m_capInsetsNormal);
    }
    else
    {
        switch (m_eNormalTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<CCSprite*>(m_pButtonNormalRenderer)->initWithFile(normal);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<CCSprite*>(m_pButtonNormalRenderer)->initWithSpriteFrameName(normal);
                break;
            default:
                break;
        }
        dynamic_cast<CCSprite*>(m_pButtonNormalRenderer)->setColor(getColor());
        dynamic_cast<CCSprite*>(m_pButtonNormalRenderer)->setOpacity(getOpacity());
    }
    m_normalTextureSize = m_pButtonNormalRenderer->getContentSize();
    updateAnchorPoint();
    normalTextureScaleChangedWithSize();
}

void UIButton::loadTexturePressed(const char* selected,TextureResType texType)
{
    if (!selected || strcmp(selected, "") == 0)
    {
        return;
    }
    m_strClickedFileName = selected;
    m_ePressedTexType = texType;
    if (m_bScale9Enabled)
    {
        switch (m_ePressedTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<CCScale9Sprite*>(m_pButtonClickedRenderer)->initWithFile(selected);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<CCScale9Sprite*>(m_pButtonClickedRenderer)->initWithSpriteFrameName(selected);
                break;
            default:
                break;
        }
        dynamic_cast<CCScale9Sprite*>(m_pButtonClickedRenderer)->setColor(getColor());
        dynamic_cast<CCScale9Sprite*>(m_pButtonClickedRenderer)->setOpacity(getOpacity());
        dynamic_cast<CCScale9Sprite*>(m_pButtonClickedRenderer)->setCapInsets(m_capInsetsPressed);
    }
    else
    {
        switch (m_ePressedTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<CCSprite*>(m_pButtonClickedRenderer)->initWithFile(selected);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<CCSprite*>(m_pButtonClickedRenderer)->initWithSpriteFrameName(selected);
                break;
            default:
                break;
        }
        dynamic_cast<CCSprite*>(m_pButtonClickedRenderer)->setColor(getColor());
        dynamic_cast<CCSprite*>(m_pButtonClickedRenderer)->setOpacity(getOpacity());
    }
    m_pressedTextureSize = m_pButtonClickedRenderer->getContentSize();
    updateAnchorPoint();
    pressedTextureScaleChangedWithSize();
}

void UIButton::loadTextureDisabled(const char* disabled,TextureResType texType)
{
    if (!disabled || strcmp(disabled, "") == 0)
    {
        return;
    }
    m_strDisabledFileName = disabled;
    m_eDisabledTexType = texType;
    if (m_bScale9Enabled)
    {
        switch (m_eDisabledTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<CCScale9Sprite*>(m_pButtonDisableRenderer)->initWithFile(disabled);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<CCScale9Sprite*>(m_pButtonDisableRenderer)->initWithSpriteFrameName(disabled);
                break;
            default:
                break;
        }
        dynamic_cast<CCScale9Sprite*>(m_pButtonDisableRenderer)->setColor(getColor());
        dynamic_cast<CCScale9Sprite*>(m_pButtonDisableRenderer)->setOpacity(getOpacity());
        dynamic_cast<CCScale9Sprite*>(m_pButtonDisableRenderer)->setCapInsets(m_capInsetsDisabled);
    }
    else
    {
        switch (m_eDisabledTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<CCSprite*>(m_pButtonDisableRenderer)->initWithFile(disabled);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<CCSprite*>(m_pButtonDisableRenderer)->initWithSpriteFrameName(disabled);
                break;
            default:
                break;
        }
        dynamic_cast<CCSprite*>(m_pButtonDisableRenderer)->setColor(getColor());
        dynamic_cast<CCSprite*>(m_pButtonDisableRenderer)->setOpacity(getOpacity());
    }
    m_disabledTextureSize = m_pButtonDisableRenderer->getContentSize();
    updateAnchorPoint();
    disabledTextureScaleChangedWithSize();
}

void UIButton::setCapInsets(const CCRect &capInsets)
{
    setCapInsetsNormalRenderer(capInsets);
    setCapInsetsPressedRenderer(capInsets);
    setCapInsetsDisabledRenderer(capInsets);
}

void UIButton::setCapInsetsNormalRenderer(const CCRect &capInsets)
{
    m_capInsetsNormal = capInsets;
    if (!m_bScale9Enabled)
    {
        return;
    }
    dynamic_cast<CCScale9Sprite*>(m_pButtonNormalRenderer)->setCapInsets(capInsets);
}

void UIButton::setCapInsetsPressedRenderer(const CCRect &capInsets)
{
    m_capInsetsPressed = capInsets;
    if (!m_bScale9Enabled)
    {
        return;
    }
    dynamic_cast<CCScale9Sprite*>(m_pButtonClickedRenderer)->setCapInsets(capInsets);
}

void UIButton::setCapInsetsDisabledRenderer(const CCRect &capInsets)
{
    m_capInsetsDisabled = capInsets;
    if (!m_bScale9Enabled)
    {
        return;
    }
    dynamic_cast<CCScale9Sprite*>(m_pButtonDisableRenderer)->setCapInsets(capInsets);
}

void UIButton::onPressStateChangedToNormal()
{
    m_pButtonNormalRenderer->setVisible(true);
    m_pButtonClickedRenderer->setVisible(false);
    m_pButtonDisableRenderer->setVisible(false);
    if (m_bPressedActionEnabled)
    {
        m_pButtonNormalRenderer->stopAllActions();
        m_pButtonClickedRenderer->stopAllActions();
        m_pButtonDisableRenderer->stopAllActions();
        CCAction *zoomAction = CCScaleTo::create(0.05f, 1.0f);
        CCAction *zoomAction1 = CCScaleTo::create(0.05f, 1.0f);
        CCAction *zoomAction2 = CCScaleTo::create(0.05f, 1.0f);
        m_pButtonNormalRenderer->runAction(zoomAction);
        m_pButtonClickedRenderer->runAction(zoomAction1);
        m_pButtonDisableRenderer->runAction(zoomAction2);
    }
}

void UIButton::onPressStateChangedToPressed()
{
    m_pButtonNormalRenderer->setVisible(false);
    m_pButtonClickedRenderer->setVisible(true);
    m_pButtonDisableRenderer->setVisible(false);
    if (m_bPressedActionEnabled)
    {
        m_pButtonNormalRenderer->stopAllActions();
        m_pButtonClickedRenderer->stopAllActions();
        m_pButtonDisableRenderer->stopAllActions();
        CCAction *zoomAction = CCScaleTo::create(0.05f, 1.1f);
        CCAction *zoomAction1 = CCScaleTo::create(0.05f, 1.1f);
        CCAction *zoomAction2 = CCScaleTo::create(0.05f, 1.1f);
        m_pButtonNormalRenderer->runAction(zoomAction);
        m_pButtonClickedRenderer->runAction(zoomAction1);
        m_pButtonDisableRenderer->runAction(zoomAction2);
    }
}

void UIButton::onPressStateChangedToDisabled()
{
    m_pButtonNormalRenderer->setVisible(false);
    m_pButtonClickedRenderer->setVisible(false);
    m_pButtonDisableRenderer->setVisible(true);
}

void UIButton::setFlipX(bool flipX)
{
    m_pTitleRenderer->setFlipX(flipX);
    if (m_bScale9Enabled)
    {
        return;
    }
    dynamic_cast<CCSprite*>(m_pButtonNormalRenderer)->setFlipX(flipX);
    dynamic_cast<CCSprite*>(m_pButtonClickedRenderer)->setFlipX(flipX);
    dynamic_cast<CCSprite*>(m_pButtonDisableRenderer)->setFlipX(flipX);
}

void UIButton::setFlipY(bool flipY)
{
    m_pTitleRenderer->setFlipY(flipY);
    if (m_bScale9Enabled)
    {
        return;
    }
    dynamic_cast<CCSprite*>(m_pButtonNormalRenderer)->setFlipY(flipY);
    dynamic_cast<CCSprite*>(m_pButtonClickedRenderer)->setFlipY(flipY);
    dynamic_cast<CCSprite*>(m_pButtonDisableRenderer)->setFlipY(flipY);
}

bool UIButton::isFlipX()
{
    if (m_bScale9Enabled)
    {
        return false;
    }
    return dynamic_cast<CCSprite*>(m_pButtonNormalRenderer)->isFlipX();
}

bool UIButton::isFlipY()
{
    if (m_bScale9Enabled)
    {
        return false;
    }
    return dynamic_cast<CCSprite*>(m_pButtonNormalRenderer)->isFlipY();
}

void UIButton::setAnchorPoint(const CCPoint &pt)
{
    UIWidget::setAnchorPoint(pt);
    m_pButtonNormalRenderer->setAnchorPoint(pt);
    m_pButtonClickedRenderer->setAnchorPoint(pt);
    m_pButtonDisableRenderer->setAnchorPoint(pt);
    m_pTitleRenderer->setPosition(ccp(m_size.width*(0.5f-m_anchorPoint.x), m_size.height*(0.5f-m_anchorPoint.y)));
}

void UIButton::onSizeChanged()
{
    normalTextureScaleChangedWithSize();
    pressedTextureScaleChangedWithSize();
    disabledTextureScaleChangedWithSize();
}

const CCSize& UIButton::getContentSize() const
{
    return m_normalTextureSize;
}

CCNode* UIButton::getVirtualRenderer()
{
    if (m_bBright)
    {
        switch (m_eBrightStyle)
        {
            case BRIGHT_NORMAL:
                return m_pButtonNormalRenderer;
            case BRIGHT_HIGHLIGHT:
                return m_pButtonClickedRenderer;
            default:
                return NULL;
        }
    }
    else
    {
        return m_pButtonDisableRenderer;
    }
}

void UIButton::normalTextureScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
        if (!m_bScale9Enabled)
        {
            m_pButtonNormalRenderer->setScale(1.0f);
            m_size = m_normalTextureSize;
        }
    }
    else
    {
        if (m_bScale9Enabled)
        {
            dynamic_cast<CCScale9Sprite*>(m_pButtonNormalRenderer)->setPreferredSize(m_size);
        }
        else
        {
            CCSize textureSize = m_normalTextureSize;
            if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
            {
                m_pButtonNormalRenderer->setScale(1.0f);
                return;
            }
            float scaleX = m_size.width / textureSize.width;
            float scaleY = m_size.height / textureSize.height;
            m_pButtonNormalRenderer->setScaleX(scaleX);
            m_pButtonNormalRenderer->setScaleY(scaleY);
        }
    }
}

void UIButton::pressedTextureScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
        if (!m_bScale9Enabled)
        {
            m_pButtonClickedRenderer->setScale(1.0f);
        }
    }
    else
    {
        if (m_bScale9Enabled)
        {
            dynamic_cast<CCScale9Sprite*>(m_pButtonClickedRenderer)->setPreferredSize(m_size);
        }
        else
        {
            CCSize textureSize = m_pressedTextureSize;
            if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
            {
                m_pButtonClickedRenderer->setScale(1.0f);
                return;
            }
            float scaleX = m_size.width / m_pressedTextureSize.width;
            float scaleY = m_size.height / m_pressedTextureSize.height;
            m_pButtonClickedRenderer->setScaleX(scaleX);
            m_pButtonClickedRenderer->setScaleY(scaleY);
        }
    }
}

void UIButton::disabledTextureScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
        if (!m_bScale9Enabled)
        {
            m_pButtonDisableRenderer->setScale(1.0f);
        }
    }
    else
    {
        if (m_bScale9Enabled)
        {
            dynamic_cast<CCScale9Sprite*>(m_pButtonDisableRenderer)->setPreferredSize(m_size);
        }
        else
        {
            CCSize textureSize = m_disabledTextureSize;
            if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
            {
                m_pButtonDisableRenderer->setScale(1.0f);
                return;
            }
            float scaleX = m_size.width / m_disabledTextureSize.width;
            float scaleY = m_size.height / m_disabledTextureSize.height;
            m_pButtonDisableRenderer->setScaleX(scaleX);
            m_pButtonDisableRenderer->setScaleY(scaleY);
        }
    }
}

void UIButton::setPressedActionEnabled(bool enabled)
{
    m_bPressedActionEnabled = enabled;
}

void UIButton::setTitleText(const char* text)
{
    m_pTitleRenderer->setString(text);
}

const char* UIButton::getTitleText() const
{
    return m_pTitleRenderer->getString();
}

void UIButton::setTitleColor(const ccColor3B& color)
{
    m_titleColor = color;
    m_pTitleRenderer->setColor(color);
}

const ccColor3B& UIButton::getTitleColor() const
{
    return m_pTitleRenderer->getColor();
}

void UIButton::setTitleFontSize(float size)
{
    m_pTitleRenderer->setFontSize(size);
}

float UIButton::getTitleFontSize() const
{
    return m_pTitleRenderer->getFontSize();
}

void UIButton::setTitleFontName(const char* fontName)
{
    m_pTitleRenderer->setFontName(fontName);
}

const char* UIButton::getTitleFontName() const
{
    return m_pTitleRenderer->getFontName();
}

void UIButton::setColor(const ccColor3B &color)
{
    UIWidget::setColor(color);
    setTitleColor(m_titleColor);
}

const char* UIButton::getDescription() const
{
    return "Button";
}

UIWidget* UIButton::createCloneInstance()
{
    return UIButton::create();
}

void UIButton::copySpecialProperties(UIWidget *widget)
{
    UIButton* button = dynamic_cast<UIButton*>(widget);
    if (button)
    {   
        m_bPrevIgnoreSize = button->m_bPrevIgnoreSize;
        setScale9Enabled(button->m_bScale9Enabled);
        loadTextureNormal(button->m_strNormalFileName.c_str(), button->m_eNormalTexType);
        loadTexturePressed(button->m_strClickedFileName.c_str(), button->m_ePressedTexType);
        loadTextureDisabled(button->m_strDisabledFileName.c_str(), button->m_eDisabledTexType);
        setCapInsetsNormalRenderer(button->m_capInsetsNormal);
        setCapInsetsPressedRenderer(button->m_capInsetsPressed);
        setCapInsetsDisabledRenderer(button->m_capInsetsDisabled);
        setTitleText(button->getTitleText());
        setTitleFontName(button->getTitleFontName());
        setTitleFontSize(button->getTitleFontSize());
        setTitleColor(button->getTitleColor());
        setPressedActionEnabled(button->m_bPressedActionEnabled);
    }
}


NS_CC_EXT_END