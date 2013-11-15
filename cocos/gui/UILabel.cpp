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

#include "gui/UILabel.h"

namespace gui {


UILabel::UILabel():
_touchScaleChangeEnabled(false),
_normalScaleValueX(1.0f),
_normalScaleValueY(1.0f),
_fontName("Thonburi"),
_fontSize(10),
_onSelectedScaleOffset(0.5),
_labelRenderer(nullptr)
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
    return nullptr;
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
    _labelRenderer = cocos2d::LabelTTF::create();
    _renderer->addChild(_labelRenderer);
}

void UILabel::setText(const std::string& text)
{
	if (text.size()==0)
		return;

    _labelRenderer->setString(text);
    labelScaleChangedWithSize();
}

const std::string& UILabel::getStringValue()
{
    return _labelRenderer->getString();
}

int UILabel::getStringLength()
{
    return _labelRenderer->getString().size();
}

void UILabel::setFontSize(int size)
{
    _fontSize = size;
    _labelRenderer->setFontSize(size);
    labelScaleChangedWithSize();
}

void UILabel::setFontName(const std::string& name)
{
    _fontName = name;
    _labelRenderer->setFontName(name);
    labelScaleChangedWithSize();
}

void UILabel::setTextAreaSize(const cocos2d::Size &size)
{
    _labelRenderer->setDimensions(size);
    labelScaleChangedWithSize();
}

void UILabel::setTextHorizontalAlignment(cocos2d::TextHAlignment alignment)
{
    _labelRenderer->setHorizontalAlignment(alignment);
    labelScaleChangedWithSize();
}

void UILabel::setTextVerticalAlignment(cocos2d::TextVAlignment alignment)
{
    _labelRenderer->setVerticalAlignment(alignment);
    labelScaleChangedWithSize();
}

void UILabel::setTouchScaleChangeEnabled(bool enable)
{
    _touchScaleChangeEnabled = enable;
    _normalScaleValueX = getScaleX();
    _normalScaleValueY = getScaleY();
}
    
void UILabel::setScale(float fScale)
{
    UIWidget::setScale(fScale);
    _normalScaleValueX = _normalScaleValueY = fScale;
}
    
void UILabel::setScaleX(float fScaleX)
{
    UIWidget::setScaleX(fScaleX);
    _normalScaleValueX = fScaleX;
}
    
void UILabel::setScaleY(float fScaleY)
{
    UIWidget::setScaleY(fScaleY);
    _normalScaleValueY = fScaleY;
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
    clickScale(_normalScaleValueX, _normalScaleValueY);
}

void UILabel::onPressStateChangedToPressed()
{
    if (!_touchScaleChangeEnabled)
    {
        return;
    }
    clickScale(_normalScaleValueX + _onSelectedScaleOffset, _normalScaleValueY + _onSelectedScaleOffset);
}

void UILabel::onPressStateChangedToDisabled()
{
    
}

void UILabel::clickScale(float scaleX, float scaleY)
{
    _renderer->setScaleX(scaleX);
    _renderer->setScaleY(scaleY);
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

void UILabel::setAnchorPoint(const cocos2d::Point &pt)
{
    UIWidget::setAnchorPoint(pt);
    _labelRenderer->setAnchorPoint(pt);
}

void UILabel::onSizeChanged()
{
    labelScaleChangedWithSize();
}

const cocos2d::Size& UILabel::getContentSize() const
{
    return _labelRenderer->getContentSize();
}

cocos2d::Node* UILabel::getVirtualRenderer()
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
        cocos2d::Size textureSize = _labelRenderer->getContentSize();
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

UIWidget* UILabel::createCloneInstance()
{
    return UILabel::create();
}

void UILabel::copySpecialProperties(UIWidget *widget)
{
    UILabel* label = dynamic_cast<UILabel*>(widget);
    if (label)
    {
        setFontName(label->_fontName.c_str());
        setFontSize(label->_labelRenderer->getFontSize());
        setText(label->getStringValue());
        setTouchScaleChangeEnabled(label->_touchScaleChangeEnabled);
    }
}

}