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
#include "2d/CCLabel.h"

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
    TextBMFont* widget = new (std::nothrow) TextBMFont();
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
    TextBMFont* widget = new (std::nothrow) TextBMFont();
    if (widget && widget->init())
    {
        widget->setFntFile(filename);
        widget->setString(text);
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
    
    _fntFileHasInit = true;
    setString(_stringValue);
}

void TextBMFont::setString(const std::string& value)
{
    if (value == _labelBMFontRenderer->getString())
    {
        return;
    }
    _stringValue = value;
    if (!_fntFileHasInit)
    {
        return;
    }
    _labelBMFontRenderer->setString(value);
    updateContentSizeWithTextureSize(_labelBMFontRenderer->getContentSize());
    _labelBMFontRendererAdaptDirty = true;
}

const std::string& TextBMFont::getString()const
{
    return _stringValue;
}
    
ssize_t TextBMFont::getStringLength()const
{
    return _labelBMFontRenderer->getStringLength();
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

Size TextBMFont::getVirtualRendererSize() const
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
        float scaleX = _contentSize.width / textureSize.width;
        float scaleY = _contentSize.height / textureSize.height;
        _labelBMFontRenderer->setScaleX(scaleX);
        _labelBMFontRenderer->setScaleY(scaleY);
    }
    _labelBMFontRenderer->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
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
        setFntFile(labelBMFont->_fntFileName);
        setString(labelBMFont->_stringValue);
    }
}

}

NS_CC_END
