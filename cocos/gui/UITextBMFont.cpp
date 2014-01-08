/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "gui/UITextBMFont.h"

NS_CC_BEGIN

namespace gui {
    
static const int LABELBMFONT_RENDERER_Z = (-1);
    
TextBMFont::TextBMFont():
_labelBMFontRenderer(nullptr),
_fntFileHasInit(false),
_fntFileName(""),
_stringValue("")
{
}

TextBMFont::~TextBMFont()
{
    
}

TextBMFont* TextBMFont::create()
{
    TextBMFont* widget = new TextBMFont();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

void TextBMFont::initRenderer()
{
    _labelBMFontRenderer = cocos2d::LabelBMFont::create();
    Node::addChild(_labelBMFontRenderer, LABELBMFONT_RENDERER_Z, -1);
}

void TextBMFont::setFntFile(const char *fileName)
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

void TextBMFont::setText(const char* value)
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

const char* TextBMFont::getStringValue()
{
    return _stringValue.c_str();
}

void TextBMFont::setAnchorPoint(const Point &pt)
{
    Widget::setAnchorPoint(pt);
    _labelBMFontRenderer->setAnchorPoint(pt);
}

void TextBMFont::onSizeChanged()
{
    Widget::onSizeChanged();
    labelBMFontScaleChangedWithSize();
}

const Size& TextBMFont::getContentSize() const
{
    return _labelBMFontRenderer->getContentSize();
}

Node* TextBMFont::getVirtualRenderer()
{
    return _labelBMFontRenderer;
}

void TextBMFont::labelBMFontScaleChangedWithSize()
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

std::string TextBMFont::getDescription() const
{
    return "TextBMFont";
}

Widget* TextBMFont::createCloneInstance()
{
    return TextBMFont::create();
}

void TextBMFont::copySpecialProperties(Widget *widget)
{
    TextBMFont* labelBMFont = dynamic_cast<TextBMFont*>(widget);
    if (labelBMFont)
    {
        setFntFile(labelBMFont->_fntFileName.c_str());
        setText(labelBMFont->_stringValue.c_str());
    }
}

}

NS_CC_END