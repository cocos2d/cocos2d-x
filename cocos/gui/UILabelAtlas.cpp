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

#include "gui/UILabelAtlas.h"

NS_CC_BEGIN

namespace gui {
    
#define LABELATLASRENDERERZ (-1)


UICCLabelAtlas::UICCLabelAtlas()
{
    
}

UICCLabelAtlas::~UICCLabelAtlas()
{
    
}

UICCLabelAtlas* UICCLabelAtlas::create()
{
    UICCLabelAtlas *pRet = new UICCLabelAtlas();
    if(pRet)
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    
    return nullptr;
}

void UICCLabelAtlas::setProperty(const std::string& string, const std::string& charMapFile, unsigned int itemWidth, unsigned int itemHeight, unsigned int startCharMap)
{
    initWithString(string, charMapFile, itemWidth, itemHeight, startCharMap);
}

void UICCLabelAtlas::setProperty(const std::string& string, Texture2D *texture, unsigned int itemWidth, unsigned int itemHeight, unsigned int startCharMap)
{
    initWithString(string, texture, itemWidth, itemHeight, startCharMap);
}

void UICCLabelAtlas::draw()
{
    if (!_textureAtlas)
    {
        return;
    }
    
    AtlasNode::draw();
}



LabelAtlas::LabelAtlas():
_labelAtlasRenderer(nullptr),
_stringValue(""),
_charMapFileName(""),
_itemWidth(0),
_itemHeight(0),
_startCharMap("")
{
    
}

LabelAtlas::~LabelAtlas()
{
    
}

LabelAtlas* LabelAtlas::create()
{
    LabelAtlas* widget = new LabelAtlas();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

void LabelAtlas::initRenderer()
{
    _labelAtlasRenderer = UICCLabelAtlas::create();
    Node::addChild(_labelAtlasRenderer, LABELATLASRENDERERZ, -1);
}

void LabelAtlas::setProperty(const std::string& stringValue, const std::string& charMapFile, int itemWidth, int itemHeight, const std::string& startCharMap)
{
    _stringValue = stringValue;
    _charMapFileName = charMapFile;
    _itemWidth = itemWidth;
    _itemHeight = itemHeight;
    _startCharMap = startCharMap;
    _labelAtlasRenderer->setProperty(stringValue, charMapFile, itemWidth, itemHeight, (int)(startCharMap[0]));
    updateAnchorPoint();
    labelAtlasScaleChangedWithSize();
}

void LabelAtlas::setStringValue(const std::string& value)
{
    _stringValue = value;
    _labelAtlasRenderer->setString(value);
    labelAtlasScaleChangedWithSize();
}

const std::string& LabelAtlas::getStringValue() const
{
    return _labelAtlasRenderer->getString();
}

void LabelAtlas::setAnchorPoint(const Point &pt)
{
    Widget::setAnchorPoint(pt);
    _labelAtlasRenderer->setAnchorPoint(Point(pt.x, pt.y));
}

void LabelAtlas::onSizeChanged()
{
    Widget::onSizeChanged();
    labelAtlasScaleChangedWithSize();
}

const Size& LabelAtlas::getContentSize() const
{
    return _labelAtlasRenderer->getContentSize();
}

Node* LabelAtlas::getVirtualRenderer()
{
    return _labelAtlasRenderer;
}

void LabelAtlas::labelAtlasScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        _labelAtlasRenderer->setScale(1.0f);
        _size = _labelAtlasRenderer->getContentSize();
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
}

std::string LabelAtlas::getDescription() const
{
    return "LabelAtlas";
}

Widget* LabelAtlas::createCloneInstance()
{
    return LabelAtlas::create();
}

void LabelAtlas::copySpecialProperties(Widget *widget)
{
    LabelAtlas* labelAtlas = dynamic_cast<LabelAtlas*>(widget);
    if (labelAtlas)
    {
        setProperty(labelAtlas->_stringValue, labelAtlas->_charMapFileName, labelAtlas->_itemWidth, labelAtlas->_itemHeight, labelAtlas->_startCharMap);
    }
}
    
}
NS_CC_END