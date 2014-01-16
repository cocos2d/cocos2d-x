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

NS_CC_BEGIN

namespace gui {

static const int LABEL_RENDERER_Z = (-1);

Label::Label():
_touchScaleChangeEnabled(false),
_normalScaleValueX(1.0f),
_normalScaleValueY(1.0f),
_fontName("Thonburi"),
_fontSize(10),
_onSelectedScaleOffset(0.5),
_labelRenderer(NULL)
{
}

Label::~Label()
{
    
}

Label* Label::create()
{
    Label* widget = new Label();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool Label::init()
{
    if (Widget::init())
    {
        return true;
    }
    return false;
}

void Label::initRenderer()
{
    _labelRenderer = CCLabelTTF::create();
    CCNodeRGBA::addChild(_labelRenderer, LABEL_RENDERER_Z, -1);
}

void Label::setText(const std::string& text)
{
	if (text.size()==0)
		return;

    _labelRenderer->setString(text.c_str());
    labelScaleChangedWithSize();
}

const char* Label::getStringValue()
{
    return _labelRenderer->getString();
}

int Label::getStringLength()
{
    return std::strlen(_labelRenderer->getString());
}

void Label::setFontSize(int size)
{
    _fontSize = size;
    _labelRenderer->setFontSize(size);
    labelScaleChangedWithSize();
}

void Label::setFontName(const std::string& name)
{
    _fontName = name;
    _labelRenderer->setFontName(name.c_str());
    labelScaleChangedWithSize();
}

void Label::setTextAreaSize(const CCSize &size)
{
    _labelRenderer->setDimensions(size);
    labelScaleChangedWithSize();
}

void Label::setTextHorizontalAlignment(CCTextAlignment alignment)
{
    _labelRenderer->setHorizontalAlignment(alignment);
    labelScaleChangedWithSize();
}

void Label::setTextVerticalAlignment(CCVerticalTextAlignment alignment)
{
    _labelRenderer->setVerticalAlignment(alignment);
    labelScaleChangedWithSize();
}

void Label::setTouchScaleChangeEnabled(bool enable)
{
    _touchScaleChangeEnabled = enable;
    _normalScaleValueX = getScaleX();
    _normalScaleValueY = getScaleY();
}
    
void Label::setScale(float fScale)
{
    Widget::setScale(fScale);
    _normalScaleValueX = _normalScaleValueY = fScale;
}
    
void Label::setScaleX(float fScaleX)
{
    Widget::setScaleX(fScaleX);
}
    
void Label::setScaleY(float fScaleY)
{
    Widget::setScaleY(fScaleY);
}

bool Label::isTouchScaleChangeEnabled()
{
    return _touchScaleChangeEnabled;
}

void Label::onPressStateChangedToNormal()
{
    if (!_touchScaleChangeEnabled)
    {
        return;
    }
    clickScale(_normalScaleValueX, _normalScaleValueY);
}

void Label::onPressStateChangedToPressed()
{
    if (!_touchScaleChangeEnabled)
    {
        return;
    }
    _normalScaleValueX = getScaleX();
    _normalScaleValueY = getScaleY();
    clickScale(_normalScaleValueX + _onSelectedScaleOffset, _normalScaleValueY + _onSelectedScaleOffset);
}

void Label::onPressStateChangedToDisabled()
{
    
}

void Label::clickScale(float scaleX, float scaleY)
{
    setScaleX(scaleX);
    setScaleY(scaleY);
}

void Label::setFlipX(bool flipX)
{
    _labelRenderer->setFlipX(flipX);
}

void Label::setFlipY(bool flipY)
{
    _labelRenderer->setFlipY(flipY);
}

bool Label::isFlipX()
{
    return _labelRenderer->isFlipX();
}

bool Label::isFlipY()
{
    return _labelRenderer->isFlipY();
}

void Label::setAnchorPoint(const CCPoint &pt)
{
    Widget::setAnchorPoint(pt);
    _labelRenderer->setAnchorPoint(pt);
}

void Label::onSizeChanged()
{
    Widget::onSizeChanged();
    labelScaleChangedWithSize();
}

const CCSize& Label::getContentSize() const
{
    return _labelRenderer->getContentSize();
}

CCNode* Label::getVirtualRenderer()
{
    return _labelRenderer;
}

void Label::labelScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        _labelRenderer->setScale(1.0f);
        _size = _labelRenderer->getContentSize();
    }
    else
    {
        CCSize textureSize = _labelRenderer->getContentSize();
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

std::string Label::getDescription() const
{
    return "Label";
}

Widget* Label::createCloneInstance()
{
    return Label::create();
}

void Label::copySpecialProperties(Widget *widget)
{
    Label* label = dynamic_cast<Label*>(widget);
    if (label)
    {
        setFontName(label->_fontName.c_str());
        setFontSize(label->_labelRenderer->getFontSize());
        setText(label->getStringValue());
        setTouchScaleChangeEnabled(label->_touchScaleChangeEnabled);
        setTextHorizontalAlignment(label->_labelRenderer->getHorizontalAlignment());
        setTextVerticalAlignment(label->_labelRenderer->getVerticalAlignment());
        setTextAreaSize(label->_labelRenderer->getDimensions());
    }
}

}

NS_CC_END