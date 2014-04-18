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

#include "ui/UITextBMFont.h"

NS_CC_BEGIN

namespace ui {
    
static const int LABELBMFONT_RENDERER_Z = (-1);
    
IMPLEMENT_CLASS_GUI_INFO(TextBMFont)
    
TextBMFont::TextBMFont():
_labelBMFontRenderer(nullptr),
_fntFileHasInit(false),
_fntFileName(""),
_stringValue(""),
_labelBMFontRendererAdaptDirty(true)
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
    
TextBMFont* TextBMFont::create(const std::string &text, const std::string &filename)
{
    TextBMFont* widget = new TextBMFont();
    if (widget && widget->init())
    {
        widget->setFntFile(filename);
        widget->setText(text);
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

void TextBMFont::initRenderer()
{
    _labelBMFontRenderer = cocos2d::Label::create();
    addProtectedChild(_labelBMFontRenderer, LABELBMFONT_RENDERER_Z, -1);
}

void TextBMFont::setFntFile(const std::string& fileName)
{
    if (fileName.empty())
    {
        return;
    }
    _fntFileName = fileName;
    _labelBMFontRenderer->setBMFontFilePath(fileName);
    updateRGBAToRenderer(_labelBMFontRenderer);
    _fntFileHasInit = true;
    setText(_stringValue);
}

void TextBMFont::setText(const std::string& value)
{
    _stringValue = value;
    if (!_fntFileHasInit)
    {
        return;
    }
    _labelBMFontRenderer->setString(value);
    updateContentSizeWithTextureSize(_labelBMFontRenderer->getContentSize());
    _labelBMFontRendererAdaptDirty = true;
}

const std::string TextBMFont::getStringValue()
{
    return _stringValue;
}

void TextBMFont::onSizeChanged()
{
    Widget::onSizeChanged();
    _labelBMFontRendererAdaptDirty = true;
}
    
void TextBMFont::adaptRenderers()
{
    if (_labelBMFontRendererAdaptDirty)
    {
        labelBMFontScaleChangedWithSize();
        _labelBMFontRendererAdaptDirty = false;
    }
}

const Size& TextBMFont::getVirtualRendererSize() const
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
    _labelBMFontRenderer->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
}

std::string TextBMFont::getDescription() const
{
    return "TextBMFont";
}
    
void TextBMFont::updateTextureColor()
{
    updateColorToRenderer(_labelBMFontRenderer);
}

void TextBMFont::updateTextureOpacity()
{
    updateOpacityToRenderer(_labelBMFontRenderer);
}

void TextBMFont::updateTextureRGBA()
{
    updateRGBAToRenderer(_labelBMFontRenderer);
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
        setFntFile(labelBMFont->_fntFileName);
        setText(labelBMFont->_stringValue);
    }
}

}

NS_CC_END
