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

#include "UINodeContainer.h"

NS_CC_EXT_BEGIN
    
UINodeContainer::UINodeContainer()
{
    m_WidgetName = WIDGET_NODECONTAINER;
}

UINodeContainer::~UINodeContainer()
{
    
}

void UINodeContainer::releaseResoures()
{
    UIWidget::releaseResoures();
    if (m_pCCNode)
    {
        m_pCCNode->removeFromParentAndCleanup(true);
        m_pCCNode->release();
    }
}

UINodeContainer* UINodeContainer::create()
{
    UINodeContainer* widget = new UINodeContainer();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

void UINodeContainer::addCCNode(cocos2d::CCNode *node)
{
    if (!node || m_pCCNode == node)
    {
        return;
    }
    m_pCCNode = node;
    m_pCCNode->retain();
    m_pRender->addChild(node);
}

void UINodeContainer::removeCCNode(bool cleanup)
{
    if (!m_pCCNode)
    {
        return;
    }
    m_pCCNode->release();
    m_pRender->removeChild(m_pCCNode,cleanup);
    m_pCCNode = NULL;
}

NS_CC_EXT_END