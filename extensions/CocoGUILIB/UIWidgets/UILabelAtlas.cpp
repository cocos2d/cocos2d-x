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

UILabelAtlas::UILabelAtlas():
m_pRenderLaberAtlas(NULL)
{
    m_WidgetName = WIDGET_LABELATLAS;
}

UILabelAtlas::~UILabelAtlas()
{
    
}

UILabelAtlas* UILabelAtlas::create()
{
    UILabelAtlas* widget = new UILabelAtlas();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

void UILabelAtlas::initNodes()
{
    UIWidget::initNodes();
    m_pRenderLaberAtlas = UICCLabelAtlas::create();
    m_pRender->addChild(m_pRenderLaberAtlas);
}

void UILabelAtlas::setProperty(const char *stringValue, const char *charMapFile, int itemWidth, int itemHeight, const char *startCharMap,bool useSpriteFrame)
{
    m_pRenderLaberAtlas->setProperty(stringValue, charMapFile, itemWidth, itemHeight, (int)(startCharMap[0]));
}

void UILabelAtlas::setStringValue(const char *value)
{
    m_pRenderLaberAtlas->setString(value);
}

const char* UILabelAtlas::getStringValue()
{
    return m_pRenderLaberAtlas->getString();
}

void UILabelAtlas::setAnchorPoint(const CCPoint &pt)
{
    UIWidget::setAnchorPoint(pt);
    m_pRenderLaberAtlas->setAnchorPoint(ccp(pt.x, pt.y-0.25f));
}

CCNode* UILabelAtlas::getValidNode()
{
    return m_pRenderLaberAtlas;
}

NS_CC_EXT_END