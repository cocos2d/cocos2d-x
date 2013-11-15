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

namespace gui {


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

void UICCLabelAtlas::setProperty(const std::string& string, cocos2d::Texture2D *texture, unsigned int itemWidth, unsigned int itemHeight, unsigned int startCharMap)
{
    initWithString(string, texture, itemWidth, itemHeight, startCharMap);
}

void UICCLabelAtlas::draw()
{
    if (!_textureAtlas)
    {
        return;
    }
    
    cocos2d::AtlasNode::draw();
}

void UICCLabelAtlas::updateDisplayedOpacity(GLubyte opacity)
{
    cocos2d::AtlasNode::setOpacity(opacity);
}




UILabelAtlas::UILabelAtlas():
_laberAtlasRenderer(nullptr),
_stringValue(""),
_charMapFileName(""),
_itemWidth(0),
_itemHeight(0),
_startCharMap("")
{
    
}

UILabelAtlas::~UILabelAtlas()
{
    
}

UILabelAtlas* UILabelAtlas::create()
{
    UILabelAtlas* widget = new UILabelAtlas();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

void UILabelAtlas::initRenderer()
{
    UIWidget::initRenderer();
    _laberAtlasRenderer = UICCLabelAtlas::create();
    _renderer->addChild(_laberAtlasRenderer);
}

void UILabelAtlas::setProperty(const std::string& stringValue, const std::string& charMapFile, int itemWidth, int itemHeight, const std::string& startCharMap)
{
    _stringValue = stringValue;
    _charMapFileName = charMapFile;
    _itemWidth = itemWidth;
    _itemHeight = itemHeight;
    _startCharMap = startCharMap;
    _laberAtlasRenderer->setProperty(stringValue, charMapFile, itemWidth, itemHeight, (int)(startCharMap[0]));
    updateAnchorPoint();
    labelAtlasScaleChangedWithSize();
}

void UILabelAtlas::setStringValue(const std::string& value)
{
    _stringValue = value;
    _laberAtlasRenderer->setString(value);
    labelAtlasScaleChangedWithSize();
}

const std::string& UILabelAtlas::getStringValue() const
{
    return _laberAtlasRenderer->getString();
}

void UILabelAtlas::setAnchorPoint(const cocos2d::Point &pt)
{
    UIWidget::setAnchorPoint(pt);
    _laberAtlasRenderer->setAnchorPoint(cocos2d::Point(pt.x, pt.y));
}

void UILabelAtlas::onSizeChanged()
{
    labelAtlasScaleChangedWithSize();
}

const cocos2d::Size& UILabelAtlas::getContentSize() const
{
    return _laberAtlasRenderer->getContentSize();
}

cocos2d::Node* UILabelAtlas::getVirtualRenderer()
{
    return _laberAtlasRenderer;
}

void UILabelAtlas::labelAtlasScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        _laberAtlasRenderer->setScale(1.0f);
        _size = _laberAtlasRenderer->getContentSize();
    }
    else
    {
        cocos2d::Size textureSize = _laberAtlasRenderer->getContentSize();
        if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
        {
            _laberAtlasRenderer->setScale(1.0f);
            return;
        }
        float scaleX = _size.width / textureSize.width;
        float scaleY = _size.height / textureSize.height;
        _laberAtlasRenderer->setScaleX(scaleX);
        _laberAtlasRenderer->setScaleY(scaleY);
    }
}

const char* UILabelAtlas::getDescription() const
{
    return "LabelAtlas";
}

UIWidget* UILabelAtlas::createCloneInstance()
{
    return UILabelAtlas::create();
}

void UILabelAtlas::copySpecialProperties(UIWidget *widget)
{
    UILabelAtlas* labelAtlas = dynamic_cast<UILabelAtlas*>(widget);
    if (labelAtlas)
    {
        setProperty(labelAtlas->_stringValue, labelAtlas->_charMapFileName, labelAtlas->_itemWidth, labelAtlas->_itemHeight, labelAtlas->_startCharMap);
    }
}
    
}