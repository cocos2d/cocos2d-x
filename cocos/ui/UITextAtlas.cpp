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

#include "ui/UITextAtlas.h"

NS_CC_BEGIN

namespace ui {
    
static const int LABELATLAS_RENDERER_Z = (-1);
    
IMPLEMENT_CLASS_GUI_INFO(TextAtlas)

TextAtlas::TextAtlas():
_labelAtlasRenderer(nullptr),
_stringValue(""),
_charMapFileName(""),
_itemWidth(0),
_itemHeight(0),
_startCharMap(""),
_labelAtlasRendererAdaptDirty(true)
{
}

TextAtlas::~TextAtlas()
{
    
}

TextAtlas* TextAtlas::create()
{
    TextAtlas* widget = new TextAtlas();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

void TextAtlas::initRenderer()
{
    _labelAtlasRenderer = Label::create();
    _labelAtlasRenderer->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addProtectedChild(_labelAtlasRenderer, LABELATLAS_RENDERER_Z, -1);
}
    
TextAtlas* TextAtlas::create(const std::string &stringValue,
                             const std::string &charMapFile,
                             int itemWidth,
                             int itemHeight,
                             const std::string &startCharMap)
{
    TextAtlas* widget = new TextAtlas();
    if (widget && widget->init())
    {
        widget->autorelease();
        widget->setProperty(stringValue, charMapFile, itemWidth, itemHeight, startCharMap);
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

void TextAtlas::setProperty(const std::string& stringValue, const std::string& charMapFile, int itemWidth, int itemHeight, const std::string& startCharMap)
{
    _stringValue = stringValue;
    _charMapFileName = charMapFile;
    _itemWidth = itemWidth;
    _itemHeight = itemHeight;
    _startCharMap = startCharMap;
    
    _labelAtlasRenderer->setCharMap(_charMapFileName, _itemWidth, _itemHeight, (int)(_startCharMap[0]));
    _labelAtlasRenderer->setString(stringValue);
    
    updateContentSizeWithTextureSize(_labelAtlasRenderer->getContentSize());
    _labelAtlasRendererAdaptDirty = true;
//    CCLOG("cs w %f, h %f", _contentSize.width, _contentSize.height);
}

void TextAtlas::setString(const std::string& value)
{
    _stringValue = value;
    _labelAtlasRenderer->setString(value);
    updateContentSizeWithTextureSize(_labelAtlasRenderer->getContentSize());
    _labelAtlasRendererAdaptDirty = true;
//    CCLOG("cssss w %f, h %f", _contentSize.width, _contentSize.height);
}

const std::string& TextAtlas::getString() const
{
    return _labelAtlasRenderer->getString();
}
    
ssize_t TextAtlas::getStringLength()const
{
    return _labelAtlasRenderer->getStringLength();
}

void TextAtlas::onSizeChanged()
{
    Widget::onSizeChanged();
    _labelAtlasRendererAdaptDirty = true;
}
    
void TextAtlas::adaptRenderers()
{
    if (_labelAtlasRendererAdaptDirty)
    {
        labelAtlasScaleChangedWithSize();
        _labelAtlasRendererAdaptDirty = false;
    }
}

const Size& TextAtlas::getVirtualRendererSize() const
{
    return _labelAtlasRenderer->getContentSize();
}

Node* TextAtlas::getVirtualRenderer()
{
    return _labelAtlasRenderer;
}

void TextAtlas::labelAtlasScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        _labelAtlasRenderer->setScale(1.0f);
    }
    else
    {
        Size textureSize = _labelAtlasRenderer->getContentSize();
        if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
        {
            _labelAtlasRenderer->setScale(1.0f);
            return;
        }
        float scaleX = _size.width / textureSize.width;
        float scaleY = _size.height / textureSize.height;
        _labelAtlasRenderer->setScaleX(scaleX);
        _labelAtlasRenderer->setScaleY(scaleY);
    }
    _labelAtlasRenderer->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
}

std::string TextAtlas::getDescription() const
{
    return "TextAtlas";
}
    
void TextAtlas::updateTextureColor()
{
    updateColorToRenderer(_labelAtlasRenderer);
}

void TextAtlas::updateTextureOpacity()
{
    updateOpacityToRenderer(_labelAtlasRenderer);
}

void TextAtlas::updateTextureRGBA()
{
    updateRGBAToRenderer(_labelAtlasRenderer);
}

Widget* TextAtlas::createCloneInstance()
{
    return TextAtlas::create();
}

void TextAtlas::copySpecialProperties(Widget *widget)
{
    TextAtlas* labelAtlas = dynamic_cast<TextAtlas*>(widget);
    if (labelAtlas)
    {
        setProperty(labelAtlas->_stringValue, labelAtlas->_charMapFileName, labelAtlas->_itemWidth, labelAtlas->_itemHeight, labelAtlas->_startCharMap);
    }
}
    
}
NS_CC_END
