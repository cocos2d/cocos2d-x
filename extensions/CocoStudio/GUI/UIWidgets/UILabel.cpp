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

namespace ui {

static const int LABEL_RENDERER_Z = (-1);
    
IMPLEMENT_CLASS_GUI_INFO(Label)

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
    CCNode::addChild(_labelRenderer, LABEL_RENDERER_Z, -1);
}

void Label::setText(const std::string& text)
{
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
    
int Label::getFontSize()
{
    return _fontSize;
}

void Label::setFontName(const std::string& name)
{
    _fontName = name;
    _labelRenderer->setFontName(name.c_str());
    labelScaleChangedWithSize();
}
    
const char* Label::getFontName()
{
    return _fontName.c_str();
}

void Label::setTextAreaSize(const CCSize &size)
{
    _labelRenderer->setDimensions(size);
    labelScaleChangedWithSize();
}
    
CCSize Label::getTextAreaSize()
{
    return _labelRenderer->getDimensions();
}

void Label::setTextHorizontalAlignment(CCTextAlignment alignment)
{
    _labelRenderer->setHorizontalAlignment(alignment);
    labelScaleChangedWithSize();
}
    
CCTextAlignment Label::getTextHorizontalAlignment()
{
    return _labelRenderer->getHorizontalAlignment();
}

void Label::setTextVerticalAlignment(CCVerticalTextAlignment alignment)
{
    _labelRenderer->setVerticalAlignment(alignment);
    labelScaleChangedWithSize();
}
    
CCVerticalTextAlignment Label::getTextVerticalAlignment()
{
    return _labelRenderer->getVerticalAlignment();
}

void Label::setTouchScaleChangeEnabled(bool enable)
{
    _touchScaleChangeEnabled = enable;
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
    _labelRenderer->setScaleX(_normalScaleValueX);
    _labelRenderer->setScaleY(_normalScaleValueY);
}

void Label::onPressStateChangedToPressed()
{
    if (!_touchScaleChangeEnabled)
    {
        return;
    }
    _labelRenderer->setScaleX(_normalScaleValueX + _onSelectedScaleOffset);
    _labelRenderer->setScaleY(_normalScaleValueY + _onSelectedScaleOffset);
}

void Label::onPressStateChangedToDisabled()
{
    
}
    
void Label::updateFlippedX()
{
    _labelRenderer->setFlipX(_flippedX);
}
    
void Label::updateFlippedY()
{
    _labelRenderer->setFlipY(_flippedY);
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
        _labelRenderer->setDimensions(CCSizeZero);
        _labelRenderer->setScale(1.0f);
        _size = _labelRenderer->getContentSize();
        _normalScaleValueX = _normalScaleValueY = 1.0f;        
    }
    else
    {
        _labelRenderer->setDimensions(_size);
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
        _normalScaleValueX = scaleX;
        _normalScaleValueY = scaleY;
    }
}
    
void Label::updateTextureColor()
{
    updateColorToRenderer(_labelRenderer);
}

void Label::updateTextureOpacity()
{
    updateOpacityToRenderer(_labelRenderer);
}

void Label::updateTextureRGBA()
{
    updateRGBAToRenderer(_labelRenderer);
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