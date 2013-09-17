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
_touchScaleChangeEnabled(false),
_normalScaleValue(1.0f),
_fontName("Thonburi"),
_fontSize(10),
_onSelectedScaleOffset(0.5),
_labelRenderer(NULL)
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
    _labelRenderer = CCLabelTTF::create();
    _renderer->addChild(_labelRenderer);
}

void UILabel::setText(const char* text)
{
	if (!text)
	{
		return;
	}
    std::string strText(text);
    _labelRenderer->setString(strText.c_str());
    labelScaleChangedWithSize();
}

const char* UILabel::getStringValue()
{
    return _labelRenderer->getString();
}

int UILabel::getStringLength()
{
    const char* str = _labelRenderer->getString();
    return strlen(str);
}

void UILabel::setFontSize(int size)
{
    _labelRenderer->setFontSize(size);
    labelScaleChangedWithSize();
}

void UILabel::setFontName(const char* name)
{
    _labelRenderer->setFontName(name);
    labelScaleChangedWithSize();
}

void UILabel::setTextAreaSize(const Size &size)
{
    _labelRenderer->setDimensions(size);
    labelScaleChangedWithSize();
}

void UILabel::setTextHorizontalAlignment(TextHAlignment alignment)
{
    _labelRenderer->setHorizontalAlignment(alignment);
    labelScaleChangedWithSize();
}

void UILabel::setTextVerticalAlignment(TextVAlignment alignment)
{
    _labelRenderer->setVerticalAlignment(alignment);
    labelScaleChangedWithSize();
}

void UILabel::setTouchScaleChangeEnabled(bool enable)
{
    _touchScaleChangeEnabled = enable;
    _normalScaleValue = getScale();
}

bool UILabel::isTouchScaleChangeEnabled()
{
    return _touchScaleChangeEnabled;
}

void UILabel::onPressStateChangedToNormal()
{
    if (!_touchScaleChangeEnabled)
    {
        return;
    }
    clickScale(_normalScaleValue);
}

void UILabel::onPressStateChangedToPressed()
{
    if (!_touchScaleChangeEnabled)
    {
        return;
    }
    clickScale(_normalScaleValue + _onSelectedScaleOffset);
}

void UILabel::onPressStateChangedToDisabled()
{
    
}

void UILabel::clickScale(float scale)
{
    _renderer->setScale(scale);
}

void UILabel::setFlipX(bool flipX)
{
    _labelRenderer->setFlippedX(flipX);
}

void UILabel::setFlipY(bool flipY)
{
    _labelRenderer->setFlippedY(flipY);
}

bool UILabel::isFlipX()
{
    return _labelRenderer->isFlippedX();
}

bool UILabel::isFlipY()
{
    return _labelRenderer->isFlippedY();
}

void UILabel::setAnchorPoint(const Point &pt)
{
    UIWidget::setAnchorPoint(pt);
    _labelRenderer->setAnchorPoint(pt);
}

void UILabel::onSizeChanged()
{
    labelScaleChangedWithSize();
}

const Size& UILabel::getContentSize() const
{
    return _labelRenderer->getContentSize();
}

Node* UILabel::getVirtualRenderer()
{
    return _labelRenderer;
}

void UILabel::labelScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        _labelRenderer->setScale(1.0f);
        _size = _labelRenderer->getContentSize();
    }
    else
    {
        Size textureSize = _labelRenderer->getContentSize();
        if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
        {
            _labelRenderer->setScale(1.0f);
            return;
        }
        float scaleX = _size.width / textureSize.width;
        float scaleY = _size.height / textureSize.height;
        _labelRenderer->setScaleX(scaleX);
        _labelRenderer->setScaleY(scaleY);
    }
}

const char* UILabel::getDescription() const
{
    return "Label";
}

NS_CC_EXT_END