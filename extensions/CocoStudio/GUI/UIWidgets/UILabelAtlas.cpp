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

#include "UILabelAtlas.h"

NS_CC_BEGIN

namespace ui {

static const int LABELATLAS_RENDERER_Z = (-1);

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
    
    return NULL;
}

void UICCLabelAtlas::setProperty(const std::string& string, const std::string& charMapFile, unsigned int itemWidth, unsigned int itemHeight, unsigned int startCharMap)
{
    initWithString(string.c_str(), charMapFile.c_str(), itemWidth, itemHeight, startCharMap);
}

void UICCLabelAtlas::setProperty(const std::string& string, CCTexture2D *texture, unsigned int itemWidth, unsigned int itemHeight, unsigned int startCharMap)
{
    initWithString(string.c_str(), texture, itemWidth, itemHeight, startCharMap);
}

void UICCLabelAtlas::draw()
{
    if (!m_pTextureAtlas)
    {
        return;
    }
    
    CCAtlasNode::draw();
}

void UICCLabelAtlas::updateDisplayedOpacity(GLubyte opacity)
{
    CCAtlasNode::setOpacity(opacity);
}



    
IMPLEMENT_CLASS_GUI_INFO(LabelAtlas)
    

LabelAtlas::LabelAtlas():
_labelAtlasRenderer(NULL),
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
    return NULL;
}

void LabelAtlas::initRenderer()
{
    _labelAtlasRenderer = UICCLabelAtlas::create();
    CCNode::addChild(_labelAtlasRenderer, LABELATLAS_RENDERER_Z, -1);
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
    _labelAtlasRenderer->setString(value.c_str());
    labelAtlasScaleChangedWithSize();
}

const char* LabelAtlas::getStringValue() const
{
    return _labelAtlasRenderer->getString();
}

void LabelAtlas::setAnchorPoint(const CCPoint &pt)
{
    Widget::setAnchorPoint(pt);
    _labelAtlasRenderer->setAnchorPoint(CCPoint(pt.x, pt.y));
}

void LabelAtlas::onSizeChanged()
{
    Widget::onSizeChanged();
    labelAtlasScaleChangedWithSize();
}

const CCSize& LabelAtlas::getContentSize() const
{
    return _labelAtlasRenderer->getContentSize();
}

CCNode* LabelAtlas::getVirtualRenderer()
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
        CCSize textureSize = _labelAtlasRenderer->getContentSize();
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
    
void LabelAtlas::updateTextureColor()
{
    updateColorToRenderer(_labelAtlasRenderer);
}

void LabelAtlas::updateTextureOpacity()
{
    updateOpacityToRenderer(_labelAtlasRenderer);
}

void LabelAtlas::updateTextureRGBA()
{
    updateRGBAToRenderer(_labelAtlasRenderer);
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