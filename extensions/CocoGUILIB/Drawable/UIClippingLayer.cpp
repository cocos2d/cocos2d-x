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

static void checkNodeClippingOption(cocos2d::CCNode *node)
{
    for (int i=0; i<node->getChildrenCount(); i++)
    {
        CCObject * oChild = node->getChildren()->objectAtIndex(i);
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
m_fScissorWidth(0.0f),
m_fScissorHeight(0.0f),
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
m_nCOpacity(255)
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
    CCLayer::onEnter();
    m_loacationInWorld = convertToWorldSpace(CCPointZero);
    checkClippingOption();
}

void UIClippingLayer::onExit()
{
    CCLayer::onExit();
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
        
        if (m_bEnableCustomArea)
        {
            CCRect clippingRect = getClippingRect();
            CCEGLView::sharedOpenGLView()->setScissorInPoints(clippingRect.origin.x, clippingRect.origin.y, clippingRect.size.width, clippingRect.size.height);
        }
        else
        {
            CCSize s = boundingBox().size;
            CCEGLView::sharedOpenGLView()->setScissorInPoints(m_loacationInWorld.x, m_loacationInWorld.y, s.width, s.height);
        }
        CCLayer::visit();
        if (m_bHandleScissor)
        {
            glDisable(GL_SCISSOR_TEST);
        }
        else
        {
            if (m_pClippingParent)
            {
                CCRect pClippingRect = m_pClippingParent->getClippingRect();
                CCEGLView::sharedOpenGLView()->setScissorInPoints(pClippingRect.origin.x, pClippingRect.origin.y, pClippingRect.size.width, pClippingRect.size.height);
            }
        }
    }
    else
    {
        CCLayer::visit();
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
    for (int i=0; i<m_pChildren->count(); i++)
    {
        CCObject * oChild = m_pChildren->objectAtIndex(i);
        UIClippingLayer* cChild = dynamic_cast<UIClippingLayer*>(oChild);
        if (cChild)
        {
            cChild->checkClippingOption();
            cChild->updateChildrenClippingOptions();
            CCLOG("zenmekeneng");
        }
        else
        {
            CCNode* nChild = dynamic_cast<CCNode*>(oChild);
            checkNodeClippingOption(nChild);
//            CCLOG("bukeneng");
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
            this->addChild(m_pColorRender,-1);
            break;
        case UL_C_GRADIENT:
            m_pGradientRender = CCLayerGradient::create();
            m_pGradientRender->setContentSize(getContentSize());
            m_pGradientRender->setOpacity(m_nCOpacity);
            m_pGradientRender->setStartColor(m_gStartColor);
            m_pGradientRender->setEndColor(m_gEndColor);
            this->addChild(m_pGradientRender,-1);
            break;
        default:
            break;
    }
}

bool UIClippingLayer::getColorType()
{
    return m_colorType;
}

void UIClippingLayer::setClipRect(const cocos2d::CCRect &rect)
{
    
}

const CCRect& UIClippingLayer::getClippingRect()
{
    if (m_pClippingParent)
    {
        CCRect pRect = m_pClippingParent->getClippingRect();
        float finalX = m_loacationInWorld.x;
        float finalY = m_loacationInWorld.y;
        float finalWidth = m_fScissorWidth;
        float finalHeight = m_fScissorHeight;
        
        float leftOffset = m_loacationInWorld.x - pRect.origin.x;
        if (leftOffset <= 0.0f)
        {
            finalX = pRect.origin.x;
            finalWidth += leftOffset;
        }
        float rightOffset = (m_loacationInWorld.x + m_fScissorWidth) - (pRect.origin.x + pRect.size.width);
        if (rightOffset >= 0.0f)
        {
            finalWidth -= rightOffset;
        }
        float topOffset = (m_loacationInWorld.y + m_fScissorHeight) - (pRect.origin.y + pRect.size.height);
        if (topOffset >= 0.0f)
        {
            finalHeight -= topOffset;
        }
        float bottomOffset = m_loacationInWorld.y - pRect.origin.y;
        if (bottomOffset <= 0.0f)
        {
            finalY = pRect.origin.x;
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
        m_clippingRect.size.width = m_fScissorWidth;
        m_clippingRect.size.height = m_fScissorHeight;
    }
    return m_clippingRect;
    
}

void UIClippingLayer::setClipSize(float width, float height)
{
    m_bEnableCustomArea = true;
    m_fScissorWidth = width;
    m_fScissorHeight = height;
}

void UIClippingLayer::setPosition(const cocos2d::CCPoint &pos)
{
    CCLayer::setPosition(pos);
    m_loacationInWorld = convertToWorldSpace(CCPointZero);
}

void UIClippingLayer::setColor(const ccColor3B &color)
{
    m_cColor = color;
    if (m_pColorRender)
    {
        m_pColorRender->setColor(color);
    }
}

void UIClippingLayer::setStartColor(const ccColor3B &color)
{
    m_gStartColor = color;
    if (m_pGradientRender)
    {
        m_pGradientRender->setStartColor(color);
    }
}

void UIClippingLayer::setEndColor(const ccColor3B &color)
{
    m_gEndColor = color;
    if (m_pGradientRender)
    {
        m_pGradientRender->setEndColor(color);
    }
}

void UIClippingLayer::setColorOpacity(int opacity)
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

void UIClippingLayer::setContentSize(const cocos2d::CCSize &size)
{
    CCLayer::setContentSize(size);
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
