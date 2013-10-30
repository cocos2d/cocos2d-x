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

NS_CC_EXT_BEGIN

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

void UICCLabelAtlas::setProperty(const char *string, const char *charMapFile, unsigned int itemWidth, unsigned int itemHeight, unsigned int startCharMap)
{
    initWithString(string, charMapFile, itemWidth, itemHeight, startCharMap);
}

void UICCLabelAtlas::setProperty(const char *string, CCTexture2D *texture, unsigned int itemWidth, unsigned int itemHeight, unsigned int startCharMap)
{
    initWithString(string, texture, itemWidth, itemHeight, startCharMap);
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




UILabelAtlas::UILabelAtlas():
m_pLaberAtlasRenderer(NULL),
m_strStringValue(""),
m_strCharMapFileName(""),
m_nItemWidth(0),
m_nItemHeight(0),
m_strStartCharMap("")
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
    return NULL;
}

void UILabelAtlas::initRenderer()
{
    UIWidget::initRenderer();
    m_pLaberAtlasRenderer = UICCLabelAtlas::create();
    m_pRenderer->addChild(m_pLaberAtlasRenderer);
}

void UILabelAtlas::setProperty(const char *stringValue, const char *charMapFile, int itemWidth, int itemHeight, const char *startCharMap)
{
    m_strStringValue = stringValue;
    m_strCharMapFileName = charMapFile;
    m_nItemWidth = itemWidth;
    m_nItemHeight = itemHeight;
    m_strStartCharMap = startCharMap;
    m_pLaberAtlasRenderer->setProperty(stringValue, charMapFile, itemWidth, itemHeight, (int)(startCharMap[0]));
    updateAnchorPoint();
    labelAtlasScaleChangedWithSize();
}

void UILabelAtlas::setStringValue(const char *value)
{
    m_strStringValue = value;
    m_pLaberAtlasRenderer->setString(value);
    labelAtlasScaleChangedWithSize();
}

const char* UILabelAtlas::getStringValue()
{
    return m_pLaberAtlasRenderer->getString();
}

void UILabelAtlas::setAnchorPoint(const CCPoint &pt)
{
    UIWidget::setAnchorPoint(pt);
    m_pLaberAtlasRenderer->setAnchorPoint(ccp(pt.x, pt.y));
}

void UILabelAtlas::onSizeChanged()
{
    labelAtlasScaleChangedWithSize();
}

const CCSize& UILabelAtlas::getContentSize() const
{
    return m_pLaberAtlasRenderer->getContentSize();
}

CCNode* UILabelAtlas::getVirtualRenderer()
{
    return m_pLaberAtlasRenderer;
}

void UILabelAtlas::labelAtlasScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
        m_pLaberAtlasRenderer->setScale(1.0f);
        m_size = m_pLaberAtlasRenderer->getContentSize();
    }
    else
    {
        CCSize textureSize = m_pLaberAtlasRenderer->getContentSize();
        if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
        {
            m_pLaberAtlasRenderer->setScale(1.0f);
            return;
        }
        float scaleX = m_size.width / textureSize.width;
        float scaleY = m_size.height / textureSize.height;
        m_pLaberAtlasRenderer->setScaleX(scaleX);
        m_pLaberAtlasRenderer->setScaleY(scaleY);
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
        setProperty(labelAtlas->m_strStringValue.c_str(), labelAtlas->m_strCharMapFileName.c_str(), labelAtlas->m_nItemWidth, labelAtlas->m_nItemHeight, labelAtlas->m_strStartCharMap.c_str());
    }
}

NS_CC_EXT_END