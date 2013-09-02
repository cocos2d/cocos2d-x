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

#include "UITextButton.h"

NS_CC_EXT_BEGIN

UITextButton::UITextButton():
m_pTextLableRenderer(NULL)
{
}

UITextButton::~UITextButton()
{
    
}

UITextButton* UITextButton::create()
{
    UITextButton* widget = new UITextButton();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UITextButton::init()
{
    if (UIButton::init())
    {
        m_pTextLableRenderer = CCLabelTTF::create();
        m_pRenderer->addChild(m_pTextLableRenderer);
        return true;
    }
    return false;
}

void UITextButton::setText(const char* text)
{
	if (!text)
	{
		return;
	}
    std::string strText(text);
    m_pTextLableRenderer->setString(strText.c_str());
}

void UITextButton::setTextColor(int r,int g,int b)
{
    m_pTextLableRenderer->setColor(ccc3(r, g, b));
}

void UITextButton::setFontSize(int size)
{
    m_pTextLableRenderer->setFontSize(size);
}

void UITextButton::setFontName(const char *fontName)
{
    m_pTextLableRenderer->setFontName(fontName);
}

void UITextButton::setFlipX(bool flipX)
{
    UIButton::setFlipX(flipX);
    m_pTextLableRenderer->setFlipX(flipX);
}

void UITextButton::setFlipY(bool flipY)
{
    UIButton::setFlipY(flipY);
    m_pTextLableRenderer->setFlipY(flipY);
}

void UITextButton::setAnchorPoint(const CCPoint &pt)
{
    UIButton::setAnchorPoint(pt);
    m_pTextLableRenderer->setPosition(ccp(m_pButtonNormalRenderer->getContentSize().width*(0.5f-m_pButtonNormalRenderer->getAnchorPoint().x), m_pButtonNormalRenderer->getContentSize().height*(0.5f-m_pButtonNormalRenderer->getAnchorPoint().y)));
}

NS_CC_EXT_END