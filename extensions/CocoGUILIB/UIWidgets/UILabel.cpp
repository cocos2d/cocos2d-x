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
m_bTouchScaleChangeAble(false),
m_nGravity(LabelGravityCenter),
m_sFontName("Thonburi"),
m_nFontSize(10),
m_fOnSelectedScaleOffset(0.5),
m_fNormalScaleValue(1),
m_pRenderLabel(NULL)
{
    m_WidgetName = WIDGET_LABEL;
}

UILabel::~UILabel()
{
    
}

UILabel* UILabel::create()
{
    UILabel* widget = new UILabel();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UILabel::init()
{
    if (UIWidget::init())
    {
        setPressState(WidgetStateNormal);
        return true;
    }
    return false;
}

void UILabel::initNodes()
{
    UIWidget::initNodes();
    m_pRenderLabel = CCLabelTTF::create();
    m_pRender->addChild(m_pRenderLabel);
}

void UILabel::setText(const char* text)
{
	if (!text)
	{
		return;
	}
    std::string strText(text);
    m_pRenderLabel->setString(strText.c_str());
}

const char* UILabel::getStringValue()
{
    return m_pRenderLabel->getString();
}

int UILabel::getStringLength()
{
    const char* str = m_pRenderLabel->getString();
    return strlen(str);
}

void UILabel::setFontSize(int size)
{
    m_pRenderLabel->setFontSize(size);
}

void UILabel::setFontName(const char* name)
{
    m_pRenderLabel->setFontName(name);
}

void UILabel::setTouchScaleChangeAble(bool able)
{
    m_bTouchScaleChangeAble = able;
    m_fNormalScaleValue = getScale();
}

bool UILabel::getTouchScaleChangeAble()
{
    return m_bTouchScaleChangeAble;
}

void UILabel::onPressStateChangedToNormal()
{
    if (!m_bTouchScaleChangeAble){
        return;
    }
    clickScale(m_fNormalScaleValue);
}

void UILabel::onPressStateChangedToPressed()
{
    if (!m_bTouchScaleChangeAble){
        return;
    }
    clickScale(m_fNormalScaleValue + m_fOnSelectedScaleOffset);
}

void UILabel::onPressStateChangedToDisabled()
{
    
}

void UILabel::clickScale(float scale)
{
    m_pRender->setScale(scale);
}

void UILabel::setFlipX(bool flipX)
{
    m_pRenderLabel->setFlipX(flipX);
}

void UILabel::setFlipY(bool flipY)
{
    m_pRenderLabel->setFlipY(flipY);
}

bool UILabel::isFlipX()
{
    return m_pRenderLabel->isFlipX();
}

bool UILabel::isFlipY()
{
    return m_pRenderLabel->isFlipY();
}

void UILabel::setGravity(LabelGravity gravity)
{
    m_nGravity = gravity;
    switch (m_nGravity)
    {
        case LabelGravityCenter:
            m_pRenderLabel->setAnchorPoint(ccp(0.5f, 0.5f));
            break;
        case LabelGravityLelf:
            m_pRenderLabel->setAnchorPoint(ccp(0.0f, 0.5f));
            break;
        case LabelGravityRight:
            m_pRenderLabel->setAnchorPoint(ccp(1.0f, 0.5f));
            break;
        default:
            break;
    }
}

void UILabel::adaptSize(float xProportion, float yProportion)
{
    float res = xProportion > yProportion ? xProportion : yProportion;
    m_pRenderLabel->setFontSize(m_pRenderLabel->getFontSize()*res);
}

CCNode* UILabel::getValidNode()
{
    return m_pRenderLabel;
}

void UILabel::setAnchorPoint(const CCPoint &pt)
{
    UIWidget::setAnchorPoint(pt);
    m_pRenderLabel->setAnchorPoint(pt);
}

NS_CC_EXT_END