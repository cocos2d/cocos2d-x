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

#include "UILabelBMFont.h"

NS_CC_EXT_BEGIN
    
UILabelBMFont::UILabelBMFont():
m_pLabelBMFontRenderer(NULL),
m_bFntFileHasInit(false),
m_strFntFileName(""),
m_strStringValue("")
{
}

UILabelBMFont::~UILabelBMFont()
{
    
}

UILabelBMFont* UILabelBMFont::create()
{
    UILabelBMFont* widget = new UILabelBMFont();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

void UILabelBMFont::initRenderer()
{
    UIWidget::initRenderer();
    m_pLabelBMFontRenderer = CCLabelBMFont::create();
    m_pRenderer->addChild(m_pLabelBMFontRenderer);
}

void UILabelBMFont::setFntFile(const char *fileName)
{
    if (!fileName || std::strcmp(fileName, "") == 0)
    {
        return;
    }
    m_strFntFileName = fileName;
    m_pLabelBMFontRenderer->initWithString("", fileName);
    updateAnchorPoint();
    labelBMFontScaleChangedWithSize();
    m_bFntFileHasInit = true;
    setText(m_strStringValue.c_str());
}

void UILabelBMFont::setText(const char* value)
{
    if (!value)
	{
		return;
	}
    m_strStringValue = value;
    if (!m_bFntFileHasInit)
    {
        return;
    }
    m_pLabelBMFontRenderer->setString(value);
    labelBMFontScaleChangedWithSize();
}

const char* UILabelBMFont::getStringValue()
{
    return m_strStringValue.c_str();
}

void UILabelBMFont::setAnchorPoint(const CCPoint &pt)
{
    UIWidget::setAnchorPoint(pt);
    m_pLabelBMFontRenderer->setAnchorPoint(pt);
}

void UILabelBMFont::onSizeChanged()
{
    labelBMFontScaleChangedWithSize();
}

const CCSize& UILabelBMFont::getContentSize() const
{
    return m_pLabelBMFontRenderer->getContentSize();
}

CCNode* UILabelBMFont::getVirtualRenderer()
{
    return m_pLabelBMFontRenderer;
}

void UILabelBMFont::labelBMFontScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
        m_pLabelBMFontRenderer->setScale(1.0f);
        m_size = m_pLabelBMFontRenderer->getContentSize();
    }
    else
    {
        CCSize textureSize = m_pLabelBMFontRenderer->getContentSize();
        if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
        {
            m_pLabelBMFontRenderer->setScale(1.0f);
            return;
        }
        float scaleX = m_size.width / textureSize.width;
        float scaleY = m_size.height / textureSize.height;
        m_pLabelBMFontRenderer->setScaleX(scaleX);
        m_pLabelBMFontRenderer->setScaleY(scaleY);
    }
}

const char* UILabelBMFont::getDescription() const
{
    return "LabelBMFont";
}

UIWidget* UILabelBMFont::createCloneInstance()
{
    return UILabelBMFont::create();
}

void UILabelBMFont::copySpecialProperties(UIWidget *widget)
{
    UILabelBMFont* labelBMFont = dynamic_cast<UILabelBMFont*>(widget);
    if (labelBMFont)
    {
        setFntFile(labelBMFont->m_strFntFileName.c_str());
        setText(labelBMFont->m_strStringValue.c_str());
    }
}

NS_CC_EXT_END