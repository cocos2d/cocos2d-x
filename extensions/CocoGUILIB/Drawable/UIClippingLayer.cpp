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

#include "UIClippingLayer.h"

NS_CC_EXT_BEGIN

static void checkNodeClippingOption(CCNode *node)
{
    CCArray* nodeChildren = node->getChildren();
    if (!nodeChildren)
    {
        return;
    }
    ccArray* arrayNodeChildren = nodeChildren->data;
    int length = arrayNodeChildren->num;
    for (int i=0; i<length; i++)
    {
        CCObject * oChild = arrayNodeChildren->arr[i];
        UIClippingLayer* cChild = dynamic_cast<UIClippingLayer*>(oChild);
        if (cChild)
        {
            cChild->checkClippingOption();
            cChild->updateChildrenClippingOptions();
        }
        else
        {
            CCNode* nChild = dynamic_cast<CCNode*>(oChild);
            checkNodeClippingOption(nChild);
        }
    }
}

UIClippingLayer::UIClippingLayer():
m_bClippingEnable(false),
m_fScissorX(0.0f),
m_fScissorY(0.0f),
m_bEnableCustomArea(false),
m_colorType(UL_C_NONE),
m_loacationInWorld(CCPointZero),
m_pClippingParent(NULL),
m_bHandleScissor(true),
m_pColorRender(NULL),
m_pGradientRender(NULL),
m_cColor(ccWHITE),
m_gStartColor(ccWHITE),
m_gEndColor(ccWHITE),
m_nCOpacity(255),
m_parentClippingRect(CCRectZero),
m_clippingRect(CCRectZero),
m_AlongVector(ccp(0.0f, -1.0f))
{
    
}

UIClippingLayer::~UIClippingLayer()
{
}

UIClippingLayer* UIClippingLayer::create()
{
    UIClippingLayer * pLayer = new UIClippingLayer();
    if( pLayer && pLayer->init())
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

void UIClippingLayer::onEnter()
{
    CCLayerRGBA::onEnter();
    m_loacationInWorld = convertToWorldSpace(CCPointZero);
    checkClippingOption();
}

void UIClippingLayer::onExit()
{
    CCLayerRGBA::onExit();
    m_pClippingParent = NULL;
    m_bHandleScissor = true;
}

void UIClippingLayer::checkClippingOption()
{
    if (!m_bClippingEnable)
    {
        return;
    }
    CCNode* parent = this;
    while (parent)
    {
        parent = parent->getParent();
        if(parent)
        {
            m_pClippingParent = dynamic_cast<UIClippingLayer*>(parent);
            if (m_pClippingParent && m_pClippingParent->isClippingEnable())
            {
                m_bHandleScissor = false;
                break;
            }
            else
            {
                m_pClippingParent = NULL;
            }
        }
    }
}

void UIClippingLayer::visit()
{
    if (m_bClippingEnable)
    {
        if (m_bHandleScissor)
        {
            glEnable(GL_SCISSOR_TEST);
        }
        CCRect clippingRect = getClippingRect();
        CCEGLView::sharedOpenGLView()->setScissorInPoints(clippingRect.origin.x, clippingRect.origin.y, clippingRect.size.width, clippingRect.size.height);
        CCLayerRGBA::visit();
        if (m_bHandleScissor)
        {
            glDisable(GL_SCISSOR_TEST);
        }
        else
        {
            if (m_pClippingParent)
            {
                CCEGLView::sharedOpenGLView()->setScissorInPoints(m_parentClippingRect.origin.x, m_parentClippingRect.origin.y, m_parentClippingRect.size.width, m_parentClippingRect.size.height);
            }
        }
    }
    else
    {
        CCLayerRGBA::visit();
    }
}

void UIClippingLayer::setClippingEnable(bool able)
{
    m_bClippingEnable = able;
    checkClippingOption();
    updateChildrenClippingOptions();
}

void UIClippingLayer::updateChildrenClippingOptions()
{
    if (!m_pChildren)
    {
        return;
    }
    ccArray* arrayChildren = m_pChildren->data;
    int childrenCount = arrayChildren->num;
    for (int i=0; i<childrenCount; i++)
    {
        CCObject * oChild = arrayChildren->arr[i];
        UIClippingLayer* cChild = dynamic_cast<UIClippingLayer*>(oChild);
        if (cChild)
        {
            cChild->checkClippingOption();
            cChild->updateChildrenClippingOptions();
        }
        else
        {
            CCNode* nChild = dynamic_cast<CCNode*>(oChild);
            checkNodeClippingOption(nChild);
        }
    }
}

bool UIClippingLayer::isClippingEnable()
{
    return m_bClippingEnable;
}

void UIClippingLayer::setColorType(UILayerColorType type)
{
    if (m_colorType == type)
    {
        return;
    }
    switch (m_colorType)
    {
        case UL_C_NONE:
            if (m_pColorRender)
            {
                this->removeChild(m_pColorRender, true);
                m_pColorRender = NULL;
            }
            if (m_pGradientRender)
            {
                this->removeChild(m_pGradientRender, true);
                m_pGradientRender = NULL;
            }
            break;
        case UL_C_COLOR:
            if (m_pColorRender)
            {
                this->removeChild(m_pColorRender, true);
                m_pColorRender = NULL;
            }
            break;
        case UL_C_GRADIENT:
            if (m_pGradientRender)
            {
                this->removeChild(m_pGradientRender, true);
                m_pGradientRender = NULL;
            }
            break;
        default:
            break;
    }
    m_colorType = type;
    switch (m_colorType)
    {
        case UL_C_NONE:
            break;
        case UL_C_COLOR:
            m_pColorRender = CCLayerColor::create();
            m_pColorRender->setContentSize(getContentSize());
            m_pColorRender->setOpacity(m_nCOpacity);
            m_pColorRender->setColor(m_cColor);
            this->addChild(m_pColorRender,-2);
            break;
        case UL_C_GRADIENT:
            m_pGradientRender = CCLayerGradient::create();
            m_pGradientRender->setContentSize(getContentSize());
            m_pGradientRender->setOpacity(m_nCOpacity);
            m_pGradientRender->setStartColor(m_gStartColor);
            m_pGradientRender->setEndColor(m_gEndColor);
            m_pGradientRender->setVector(m_AlongVector);
            this->addChild(m_pGradientRender,-2);
            break;
        default:
            break;
    }
}

bool UIClippingLayer::getColorType()
{
    return m_colorType;
}

void UIClippingLayer::setClipRect(const CCRect &rect)
{
    
}

const CCRect& UIClippingLayer::getClippingRect()
{
//    CCSize s;
    m_loacationInWorld = convertToWorldSpace(CCPointZero);
    CCAffineTransform t = nodeToWorldTransform();
    float scissorWidth = m_obContentSize.width*t.a;
    float scissorHeight = m_obContentSize.height*t.d;
    if (m_pClippingParent)
    {
        m_parentClippingRect = m_pClippingParent->getClippingRect();
        float finalX = m_loacationInWorld.x;
        float finalY = m_loacationInWorld.y;
        float finalWidth = scissorWidth;
        float finalHeight = scissorHeight;
        
        float leftOffset = m_loacationInWorld.x - m_parentClippingRect.origin.x;
        if (leftOffset < 0.0f)
        {
            finalX = m_parentClippingRect.origin.x;
            finalWidth += leftOffset;
        }
        float rightOffset = (m_loacationInWorld.x + scissorWidth) - (m_parentClippingRect.origin.x + m_parentClippingRect.size.width);
        if (rightOffset > 0.0f)
        {
            finalWidth -= rightOffset;
        }
        float topOffset = (m_loacationInWorld.y + scissorHeight) - (m_parentClippingRect.origin.y + m_parentClippingRect.size.height);
        if (topOffset > 0.0f)
        {
            finalHeight -= topOffset;
        }
        float bottomOffset = m_loacationInWorld.y - m_parentClippingRect.origin.y;
        if (bottomOffset < 0.0f)
        {
            finalY = m_parentClippingRect.origin.x;
            finalHeight += bottomOffset;
        }
        if (finalWidth < 0.0f)
        {
            finalWidth = 0.0f;
        }
        if (finalHeight < 0.0f)
        {
            finalHeight = 0.0f;
        }
        m_clippingRect.origin.x = finalX;
        m_clippingRect.origin.y = finalY;
        m_clippingRect.size.width = finalWidth;
        m_clippingRect.size.height = finalHeight;
    }
    else
    {
        m_clippingRect.origin = m_loacationInWorld;
        m_clippingRect.size.width = scissorWidth;
        m_clippingRect.size.height = scissorHeight;
    }
    return m_clippingRect;
}

void UIClippingLayer::setPosition(const CCPoint &pos)
{
    CCLayerRGBA::setPosition(pos);
//    m_loacationInWorld = convertToWorldSpace(CCPointZero);
}

void UIClippingLayer::setBGColor(const ccColor3B &color)
{
    m_cColor = color;
    if (m_pColorRender)
    {
        m_pColorRender->setColor(color);
    }
}

void UIClippingLayer::setBGStartColor(const ccColor3B &color)
{
    m_gStartColor = color;
    if (m_pGradientRender)
    {
        m_pGradientRender->setStartColor(color);
    }
}

void UIClippingLayer::setBGEndColor(const ccColor3B &color)
{
    m_gEndColor = color;
    if (m_pGradientRender)
    {
        m_pGradientRender->setEndColor(color);
    }
}

void UIClippingLayer::setBGVector(const CCPoint &vector)
{
    m_AlongVector = vector;
    if (m_pGradientRender)
    {
        m_pGradientRender->setVector(vector);
    }
}

void UIClippingLayer::setBGColorOpacity(int opacity)
{
    m_nCOpacity = opacity;
    switch (m_colorType)
    {
        case UL_C_NONE:
            break;
        case UL_C_COLOR:
            m_pColorRender->setOpacity(opacity);
            break;
        case UL_C_GRADIENT:
            m_pGradientRender->setOpacity(opacity);
            break;
        default:
            break;
    }
}

void UIClippingLayer::setContentSize(const CCSize &size)
{
    CCLayerRGBA::setContentSize(size);
    if (m_pColorRender)
    {
        m_pColorRender->setContentSize(size);
    }
    if (m_pGradientRender)
    {
        m_pGradientRender->setContentSize(size);
    }
}

NS_CC_EXT_END
