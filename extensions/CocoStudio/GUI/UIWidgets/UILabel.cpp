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

#include "UILabel.h"

NS_CC_EXT_BEGIN

UILabel::UILabel():
m_bTouchScaleChangeEnabled(false),
m_fNormalScaleValueX(1.0f),
m_fNormalScaleValueY(1.0f),
m_sFontName("Thonburi"),
m_nFontSize(10),
m_fOnSelectedScaleOffset(0.5),
m_pLabelRenderer(NULL)
{
}

UILabel::~UILabel()
{
    
}

UILabel* UILabel::create()
{
    UILabel* widget = new UILabel();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UILabel::init()
{
    if (UIWidget::init())
    {
        return true;
    }
    return false;
}

void UILabel::initRenderer()
{
    UIWidget::initRenderer();
    m_pLabelRenderer = CCLabelTTF::create();
    m_pRenderer->addChild(m_pLabelRenderer);
}

void UILabel::setText(const char* text)
{
	if (!text)
	{
		return;
	}
    std::string strText(text);
    m_pLabelRenderer->setString(strText.c_str());
    labelScaleChangedWithSize();
}

const char* UILabel::getStringValue()
{
    return m_pLabelRenderer->getString();
}

int UILabel::getStringLength()
{
    const char* str = m_pLabelRenderer->getString();
    return strlen(str);
}

void UILabel::setFontSize(int size)
{
    m_nFontSize = size;
    m_pLabelRenderer->setFontSize(size);
    labelScaleChangedWithSize();
}

void UILabel::setFontName(const char* name)
{
    m_sFontName = name;
    m_pLabelRenderer->setFontName(name);
    labelScaleChangedWithSize();
}

void UILabel::setTextAreaSize(const CCSize &size)
{
    m_pLabelRenderer->setDimensions(size);
    labelScaleChangedWithSize();
}

void UILabel::setTextHorizontalAlignment(CCTextAlignment alignment)
{
    m_pLabelRenderer->setHorizontalAlignment(alignment);
    labelScaleChangedWithSize();
}

void UILabel::setTextVerticalAlignment(CCVerticalTextAlignment alignment)
{
    m_pLabelRenderer->setVerticalAlignment(alignment);
    labelScaleChangedWithSize();
}

void UILabel::setTouchScaleChangeEnabled(bool enable)
{
    m_bTouchScaleChangeEnabled = enable;
    m_fNormalScaleValueX = getScaleX();
    m_fNormalScaleValueY = getScaleY();
}

bool UILabel::isTouchScaleChangeEnabled()
{
    return m_bTouchScaleChangeEnabled;
}

void UILabel::onPressStateChangedToNormal()
{
    if (!m_bTouchScaleChangeEnabled)
    {
        return;
    }
    clickScale(m_fNormalScaleValueX, m_fNormalScaleValueY);
}

void UILabel::onPressStateChangedToPressed()
{
    if (!m_bTouchScaleChangeEnabled)
    {
        return;
    }
    clickScale(m_fNormalScaleValueX + m_fOnSelectedScaleOffset, m_fNormalScaleValueY + m_fOnSelectedScaleOffset);
}

void UILabel::onPressStateChangedToDisabled()
{
    
}

void UILabel::setScale(float fScale)
{
    UIWidget::setScale(fScale);
    m_fNormalScaleValueX = m_fNormalScaleValueY = fScale;
}

void UILabel::setScaleX(float fScaleX)
{
    UIWidget::setScaleX(fScaleX);
    m_fNormalScaleValueX = fScaleX;
}

void UILabel::setScaleY(float fScaleY)
{
    UIWidget::setScaleY(fScaleY);
    m_fNormalScaleValueY = fScaleY;
}

void UILabel::clickScale(float scaleX, float scaleY)
{
    m_pRenderer->setScaleX(scaleX);
    m_pRenderer->setScaleY(scaleY);
}

void UILabel::setFlipX(bool flipX)
{
    m_pLabelRenderer->setFlipX(flipX);
}

void UILabel::setFlipY(bool flipY)
{
    m_pLabelRenderer->setFlipY(flipY);
}

bool UILabel::isFlipX()
{
    return m_pLabelRenderer->isFlipX();
}

bool UILabel::isFlipY()
{
    return m_pLabelRenderer->isFlipY();
}

void UILabel::setAnchorPoint(const CCPoint &pt)
{
    UIWidget::setAnchorPoint(pt);
    m_pLabelRenderer->setAnchorPoint(pt);
}

void UILabel::onSizeChanged()
{
    labelScaleChangedWithSize();
}

const CCSize& UILabel::getContentSize() const
{
    return m_pLabelRenderer->getContentSize();
}

CCNode* UILabel::getVirtualRenderer()
{
    return m_pLabelRenderer;
}

void UILabel::labelScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
        m_pLabelRenderer->setScale(1.0f);
        m_size = m_pLabelRenderer->getContentSize();
    }
    else
    {
        CCSize textureSize = m_pLabelRenderer->getContentSize();
        if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
        {
            m_pLabelRenderer->setScale(1.0f);
            return;
        }
        float scaleX = m_size.width / textureSize.width;
        float scaleY = m_size.height / textureSize.height;
        m_pLabelRenderer->setScaleX(scaleX);
        m_pLabelRenderer->setScaleY(scaleY);
    }
    
}

const char* UILabel::getDescription() const
{
    return "Label";
}

UIWidget* UILabel::createCloneInstance()
{
    return UILabel::create();
}

void UILabel::copySpecialProperties(UIWidget *widget)
{
    UILabel* label = dynamic_cast<UILabel*>(widget);
    if (label)
    {
        setFontName(label->m_sFontName.c_str());
        setFontSize(label->m_pLabelRenderer->getFontSize());
        setText(label->getStringValue());
        setTouchScaleChangeEnabled(label->m_bTouchScaleChangeEnabled);
    }
}

NS_CC_EXT_END