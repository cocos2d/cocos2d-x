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

#include "UILoadingBar.h"
#include "../../GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_EXT_BEGIN

#define DYNAMIC_CAST_CCSPRITE dynamic_cast<cocos2d::CCSprite*>(m_pBarRenderer)

UILoadingBar::UILoadingBar():
m_nBarType(LoadingBarTypeLeft),
m_nPercent(100),
m_fTotalLength(0),
m_pBarRenderer(NULL),
m_eRenderBarTexType(UI_TEX_TYPE_LOCAL),
m_bScale9Enabled(false),
m_capInsets(CCRectZero),
m_strTextureFile(""),
m_bPrevIgnoreSize(true)
{
}

UILoadingBar::~UILoadingBar()
{
    
}

UILoadingBar* UILoadingBar::create()
{
    UILoadingBar* widget = new UILoadingBar();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

void UILoadingBar::initRenderer()
{
    UIWidget::initRenderer();
    m_pBarRenderer = CCSprite::create();
    m_pRenderer->addChild(m_pBarRenderer);
    m_pBarRenderer->setAnchorPoint(ccp(0.0,0.5));
}

void UILoadingBar::setDirection(LoadingBarType dir)
{
    if (m_nBarType == dir)
    {
        return;
    }
    m_nBarType = dir;

    switch (m_nBarType)
    {
        case LoadingBarTypeLeft:
            m_pBarRenderer->setAnchorPoint(ccp(0.0f,0.5f));
            m_pBarRenderer->setPosition(ccp(-m_fTotalLength*0.5f,0.0f));
            if (!m_bScale9Enabled)
            {
                dynamic_cast<CCSprite*>(m_pBarRenderer)->setFlipX(false);
            }
            break;
        case LoadingBarTypeRight:
            m_pBarRenderer->setAnchorPoint(ccp(1.0f,0.5f));
            m_pBarRenderer->setPosition(ccp(m_fTotalLength*0.5f,0.0f));
            if (!m_bScale9Enabled)
            {
                dynamic_cast<CCSprite*>(m_pBarRenderer)->setFlipX(true);
            }
            break;
    }
}

int UILoadingBar::getDirection()
{
    return m_nBarType;
}

void UILoadingBar::loadTexture(const char* texture,TextureResType texType)
{
    if (!texture || strcmp(texture, "") == 0)
    {
        return;
    }
    m_eRenderBarTexType = texType;
    m_strTextureFile = texture;
    switch (m_eRenderBarTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            if (m_bScale9Enabled)
            {
                dynamic_cast<CCScale9Sprite*>(m_pBarRenderer)->initWithFile(texture);
            }
            else
            {
                dynamic_cast<CCSprite*>(m_pBarRenderer)->initWithFile(texture);
            }
            break;
        case UI_TEX_TYPE_PLIST:
            if (m_bScale9Enabled)
            {
                dynamic_cast<CCScale9Sprite*>(m_pBarRenderer)->initWithSpriteFrameName(texture);
            }
            else
            {
                dynamic_cast<CCSprite*>(m_pBarRenderer)->initWithSpriteFrameName(texture);
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
    m_barRendererTextureSize.width = m_pBarRenderer->getContentSize().width;
    m_barRendererTextureSize.height = m_pBarRenderer->getContentSize().height;
    
    switch (m_nBarType)
    {
    case LoadingBarTypeLeft:
        m_pBarRenderer->setAnchorPoint(ccp(0.0f,0.5f));
        if (!m_bScale9Enabled)
        {
            dynamic_cast<CCSprite*>(m_pBarRenderer)->setFlipX(false);
        }
        break;
    case LoadingBarTypeRight:
        m_pBarRenderer->setAnchorPoint(ccp(1.0f,0.5f));
        if (!m_bScale9Enabled)
        {
            dynamic_cast<CCSprite*>(m_pBarRenderer)->setFlipX(true);
        }
        break;
    }
    barRendererScaleChangedWithSize();
}

void UILoadingBar::setScale9Enabled(bool enabled)
{
    if (m_bScale9Enabled == enabled)
    {
        return;
    }
    m_bScale9Enabled = enabled;
    m_pRenderer->removeChild(m_pBarRenderer, true);
    m_pBarRenderer = NULL;
    if (m_bScale9Enabled)
    {
        m_pBarRenderer = CCScale9Sprite::create();
    }
    else
    {
        m_pBarRenderer = CCSprite::create();
    }
    loadTexture(m_strTextureFile.c_str(),m_eRenderBarTexType);
    m_pRenderer->addChild(m_pBarRenderer);
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

void UILoadingBar::setCapInsets(const CCRect &capInsets)
{
    if (!m_bScale9Enabled)
    {
        return;
    }
    m_capInsets = capInsets;
    
    dynamic_cast<CCScale9Sprite*>(m_pBarRenderer)->setCapInsets(capInsets);
}

void UILoadingBar::setPercent(int percent)
{
    if ( percent < 0 || percent > 100)
    {
        return;
    }
    if (m_fTotalLength <= 0)
    {
        return;
    }
    m_nPercent = percent;
    float res = m_nPercent/100.0;
    
    int x = 0, y = 0;
    switch (m_eRenderBarTexType)
    {
        case UI_TEX_TYPE_PLIST:
        {
            CCSprite* barNode = DYNAMIC_CAST_CCSPRITE;
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
    if (m_bScale9Enabled)
    {
        setScale9Scale();
    }
    else
    {
        dynamic_cast<CCSprite*>(m_pBarRenderer)->setTextureRect(CCRectMake(x, y, m_barRendererTextureSize.width * res, m_barRendererTextureSize.height));
    }
}

int UILoadingBar::getPercent()
{
    return m_nPercent;
}

void UILoadingBar::onSizeChanged()
{
    barRendererScaleChangedWithSize();
}

void UILoadingBar::ignoreContentAdaptWithSize(bool ignore)
{
    if (!m_bScale9Enabled || (m_bScale9Enabled && !ignore))
    {
        UIWidget::ignoreContentAdaptWithSize(ignore);
        m_bPrevIgnoreSize = ignore;
    }
}

const CCSize& UILoadingBar::getContentSize() const
{
    return m_barRendererTextureSize;
}

CCNode* UILoadingBar::getVirtualRenderer()
{
    return m_pBarRenderer;
}

void UILoadingBar::barRendererScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
        if (!m_bScale9Enabled)
        {
            m_fTotalLength = m_barRendererTextureSize.width;
            m_pBarRenderer->setScale(1.0f);
            m_size = m_barRendererTextureSize;
        }
    }
    else
    {
        m_fTotalLength = m_size.width;
        if (m_bScale9Enabled)
        {
            setScale9Scale();
        }
        else
        {
            
            CCSize textureSize = m_pBarRenderer->getContentSize();
            if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
            {
                m_pBarRenderer->setScale(1.0f);
                return;
            }
            float scaleX = m_size.width / textureSize.width;
            float scaleY = m_size.height / textureSize.height;
            m_pBarRenderer->setScaleX(scaleX);
            m_pBarRenderer->setScaleY(scaleY);
        }
    }
    m_pBarRenderer->setPosition(ccp(-m_fTotalLength * 0.5f, 0.0f));
}

void UILoadingBar::setScale9Scale()
{
    switch (m_nBarType)
    {
        case LoadingBarTypeLeft:
            m_pBarRenderer->setPosition(ccp(-m_fTotalLength * 0.5f, 0.0f));
            break;
            
        case LoadingBarTypeRight:
            m_pBarRenderer->setPosition(ccp(m_fTotalLength * 0.5f, 0.0f));
            break;
            
        default:
            break;
    }
    float width = (float)(m_nPercent) / 100 * m_fTotalLength;
    dynamic_cast<CCScale9Sprite*>(m_pBarRenderer)->setPreferredSize(CCSizeMake(width, m_barRendererTextureSize.height));
}

NS_CC_EXT_END