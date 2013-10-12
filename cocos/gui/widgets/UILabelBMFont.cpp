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
_labelBMFontRenderer(NULL),
_fntFileHasInit(false)
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
    _labelBMFontRenderer = CCLabelBMFont::create();
    _renderer->addChild(_labelBMFontRenderer);
}

void UILabelBMFont::setFntFile(const char *fileName)
{
    if (!fileName || std::strcmp(fileName, "") == 0)
    {
        return;
    }
    _labelBMFontRenderer->initWithString("", fileName);
    updateAnchorPoint();
    labelBMFontScaleChangedWithSize();
    _fntFileHasInit = true;
}

void UILabelBMFont::setText(const char* value)
{
	if (!value || !_fntFileHasInit)
	{
		return;
	}
	_labelBMFontRenderer->setString(value);
    labelBMFontScaleChangedWithSize();
}

const char* UILabelBMFont::getStringValue()
{
    return _labelBMFontRenderer->getString();
}

void UILabelBMFont::setAnchorPoint(const Point &pt)
{
    UIWidget::setAnchorPoint(pt);
    _labelBMFontRenderer->setAnchorPoint(pt);
}

void UILabelBMFont::onSizeChanged()
{
    labelBMFontScaleChangedWithSize();
}

const Size& UILabelBMFont::getContentSize() const
{
    return _labelBMFontRenderer->getContentSize();
}

Node* UILabelBMFont::getVirtualRenderer()
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
        Size textureSize = _labelBMFontRenderer->getContentSize();
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


NS_CC_EXT_END