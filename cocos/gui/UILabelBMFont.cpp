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

#include "gui/UILabelBMFont.h"

namespace gui {
    
UILabelBMFont::UILabelBMFont():
_labelBMFontRenderer(nullptr),
_fntFileHasInit(false),
_fntFileName(""),
_stringValue("")
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
    return nullptr;
}

void UILabelBMFont::initRenderer()
{
    UIWidget::initRenderer();
    _labelBMFontRenderer = cocos2d::LabelBMFont::create();
    _renderer->addChild(_labelBMFontRenderer);
}

void UILabelBMFont::setFntFile(const char *fileName)
{
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return;
    }
    _fntFileName = fileName;
    _labelBMFontRenderer->initWithString("", fileName);
    updateAnchorPoint();
    labelBMFontScaleChangedWithSize();
    _fntFileHasInit = true;
    setText(_stringValue.c_str());
}

void UILabelBMFont::setText(const char* value)
{
    if (!value)
	{
		return;
	}
    _stringValue = value;
    if (!_fntFileHasInit)
    {
        return;
    }
    _labelBMFontRenderer->setString(value);
    labelBMFontScaleChangedWithSize();
}

const char* UILabelBMFont::getStringValue()
{
    return _stringValue.c_str();
}

void UILabelBMFont::setAnchorPoint(const cocos2d::Point &pt)
{
    UIWidget::setAnchorPoint(pt);
    _labelBMFontRenderer->setAnchorPoint(pt);
}

void UILabelBMFont::onSizeChanged()
{
    labelBMFontScaleChangedWithSize();
}

const cocos2d::Size& UILabelBMFont::getContentSize() const
{
    return _labelBMFontRenderer->getContentSize();
}

cocos2d::Node* UILabelBMFont::getVirtualRenderer()
{
    return _labelBMFontRenderer;
}

void UILabelBMFont::labelBMFontScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        _labelBMFontRenderer->setScale(1.0f);
        _size = _labelBMFontRenderer->getContentSize();
    }
    else
    {
        cocos2d::Size textureSize = _labelBMFontRenderer->getContentSize();
        if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
        {
            _labelBMFontRenderer->setScale(1.0f);
            return;
        }
        float scaleX = _size.width / textureSize.width;
        float scaleY = _size.height / textureSize.height;
        _labelBMFontRenderer->setScaleX(scaleX);
        _labelBMFontRenderer->setScaleY(scaleY);
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
        setFntFile(labelBMFont->_fntFileName.c_str());
        setText(labelBMFont->_stringValue.c_str());
    }
}

}