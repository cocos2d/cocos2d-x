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

NS_CC_BEGIN

namespace ui {
    
static const int LABELBMFONT_RENDERER_Z = (-1);
    
    
IMPLEMENT_CLASS_GUI_INFO(LabelBMFont)
    
LabelBMFont::LabelBMFont():
_labelBMFontRenderer(NULL),
_fntFileHasInit(false),
_fntFileName(""),
_stringValue("")
{
}

LabelBMFont::~LabelBMFont()
{
    
}

LabelBMFont* LabelBMFont::create()
{
    LabelBMFont* widget = new LabelBMFont();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

void LabelBMFont::initRenderer()
{
    _labelBMFontRenderer = cocos2d::CCLabelBMFont::create();
    CCNode::addChild(_labelBMFontRenderer, LABELBMFONT_RENDERER_Z, -1);
}

void LabelBMFont::setFntFile(const char *fileName)
{
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return;
    }
    _fntFileName = fileName;
    
    if (_labelBMFontRenderer)
    {
        CCNode::removeChild(_labelBMFontRenderer, true);
        initRenderer();
    }
    
    _labelBMFontRenderer->initWithString("", fileName);
    
    updateAnchorPoint();
    labelBMFontScaleChangedWithSize();
    _fntFileHasInit = true;
    setText(_stringValue.c_str());
}

void LabelBMFont::setText(const char* value)
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

const char* LabelBMFont::getStringValue()
{
    return _stringValue.c_str();
}

void LabelBMFont::setAnchorPoint(const CCPoint &pt)
{
    Widget::setAnchorPoint(pt);
    _labelBMFontRenderer->setAnchorPoint(pt);
}

void LabelBMFont::onSizeChanged()
{
    Widget::onSizeChanged();
    labelBMFontScaleChangedWithSize();
}

const CCSize& LabelBMFont::getContentSize() const
{
    return _labelBMFontRenderer->getContentSize();
}

CCNode* LabelBMFont::getVirtualRenderer()
{
    return _labelBMFontRenderer;
}

void LabelBMFont::labelBMFontScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        _labelBMFontRenderer->setScale(1.0f);
        _size = _labelBMFontRenderer->getContentSize();
    }
    else
    {
        CCSize textureSize = _labelBMFontRenderer->getContentSize();
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
    
void LabelBMFont::updateTextureColor()
{
    updateColorToRenderer(_labelBMFontRenderer);
}

void LabelBMFont::updateTextureOpacity()
{
    updateOpacityToRenderer(_labelBMFontRenderer);
}

void LabelBMFont::updateTextureRGBA()
{
    updateRGBAToRenderer(_labelBMFontRenderer);
}

std::string LabelBMFont::getDescription() const
{
    return "LabelBMFont";
}

Widget* LabelBMFont::createCloneInstance()
{
    return LabelBMFont::create();
}

void LabelBMFont::copySpecialProperties(Widget *widget)
{
    LabelBMFont* labelBMFont = dynamic_cast<LabelBMFont*>(widget);
    if (labelBMFont)
    {
        setFntFile(labelBMFont->_fntFileName.c_str());
        setText(labelBMFont->_stringValue.c_str());
    }
}

}

NS_CC_END