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

#include "UIScrollView.h"

NS_CC_EXT_BEGIN

UIScrollView::UIScrollView():
m_eDirection(SCROLLVIEW_DIR_VERTICAL),
m_eMoveDirection(SCROLLVIEW_MOVE_DIR_NONE),
m_fTouchStartLocation(0.0f),
m_fTouchEndLocation(0.0f),
m_fTouchMoveStartLocation(0.0f),
m_fTopBoundary(0.0f),
m_fBottomBoundary(0.0f),
m_fLeftBoundary(0.0f),
m_fRightBoundary(0.0f),
m_pTopChild(NULL),
m_pBottomChild(NULL),
m_pLeftChild(NULL),
m_pRightChild(NULL),
m_nHandleState(0),
m_nMoveDirection(0),
m_bTopEnd(false),
m_bBottomEnd(false),
m_bLeftEnd(false),
m_bRightEnd(false),
m_bBerthToTop(false),
m_bBerthToBottom(false),
m_bBerthToLeft(false),
m_bBerthToRight(false),
m_bBerthToVerticalCenter(false),
m_bBerthToHorizontalCenter(false),
m_bAutoScroll(false),
m_fAutoScrollOriginalSpeed(0.0f),
m_fAutoScrollAcceleration(600.0f),
m_bBePressed(false),
m_fSlidTime(0.0f),
m_fChildrenSizeHeight(0.0f),
m_fChildrenSizeWidth(0.0f),
m_fChildFocusCancelOffset(5.0f),
m_eMoveMode(SCROLLVIEW_MOVE_MODE_NORMAL),
isRunningAction(false),
m_eBerthOrientation(SCROLLVIEW_BERTH_ORI_TOP),
m_fDisBoundaryToChild_0(0.0f),
m_fDisBetweenChild(0.0f),
m_fDragForce(0.0f),
m_pScrollToTopListener(NULL),
m_pfnScrollToTopSelector(NULL),
m_pScrollToBottomListener(NULL),
m_pfnScrollToBottomSelector(NULL),
m_pScrollToLeftListener(NULL),
m_pfnScrollToLeftSelector(NULL),
m_pScrollToRightListener(NULL),
m_pfnScrollToRightSelector(NULL),
m_pBerthToTopListener(NULL),
m_pfnBerthToTopSelector(NULL),
m_pBerthToBottomListener(NULL),
m_pfnBerthToBottomSelector(NULL),
m_pBerthToVerticalCenterListener(NULL),
m_pfnBerthToVerticalCenterSelector(NULL),
m_pBerthToLeftListener(NULL),
m_pfnBerthToLeftSelector(NULL),
m_pBerthToRightListener(NULL),
m_pfnBerthToRightSelector(NULL),
m_pBerthToHorizontalCenterListener(NULL),
m_pfnBerthToHorizontalCenterSelector(NULL)
{
    m_WidgetName = WIDGET_SCROLLVIEW;
}

UIScrollView::~UIScrollView()
{
    
}

UIScrollView* UIScrollView::create()
{
    UIScrollView* widget = new UIScrollView();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

void UIScrollView::setSize(const cocos2d::CCSize &size)
{
    UIPanel::setSize(size);
    m_fTopBoundary = size.height;
    m_fRightBoundary = size.width;
    
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            m_fDragForce = size.height / 8 * 5;
            break;
            
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            m_fDragForce = size.width / 8 * 5;
            break;
            
        default:
            break;
    }
}

bool UIScrollView::addChild(UIWidget* widget)
{
    if (m_children->count() <= 0)
    {
        m_pTopChild = widget;
        m_pBottomChild = widget;
        m_pLeftChild = widget;
        m_pRightChild = widget;
    }
    else
    {
        if (widget->getRelativeRect().origin.y + widget->getRelativeRect().size.height > m_pTopChild->getRelativeRect().origin.y + m_pTopChild->getRelativeRect().size.height)
        {
            m_pTopChild = widget;
        }
        if (widget->getRelativeRect().origin.y < m_pBottomChild->getRelativeRect().origin.y)
        {
            m_pBottomChild = widget;
        }
        if (widget->getRelativeRect().origin.x + widget->getRelativeRect().size.width > m_pRightChild->getRelativeRect().origin.x + m_pRightChild->getRelativeRect().size.width)
        {
            m_pRightChild = widget;
        }
        if (widget->getRelativeRect().origin.x < m_pLeftChild->getRelativeRect().origin.x)
        {
            m_pLeftChild = widget;
        }
    }
    m_fChildrenSizeHeight = m_pTopChild->getRelativeTopPos()-m_pBottomChild->getRelativeBottomPos();
    m_fChildrenSizeWidth = m_pRightChild->getRelativeRightPos()-m_pLeftChild->getRelativeLeftPos();
    UIPanel::addChild(widget);
    widget->setVisible(widget->checkBeVisibleInParent());
    
    initProperty();
    
    return true;
}

void UIScrollView::removeChildMoveToTrash(UIWidget* child)
{
    if (!child)
    {
        return;
    }
    UIPanel::removeChildMoveToTrash(child);
    resortChildren();
}

void UIScrollView::removeChildReferenceOnly(UIWidget* child)
{
    if (!child)
    {
        return;
    }
    UIPanel::removeChildReferenceOnly(child);
    resortChildren();
}

void UIScrollView::removeAllChildrenAndCleanUp(bool cleanup)
{
    UIPanel::removeAllChildrenAndCleanUp(cleanup);
    m_pTopChild = NULL;
    m_pBottomChild = NULL;
    m_pLeftChild = NULL;
    m_pRightChild = NULL;
}

void UIScrollView::initProperty()
{
    switch (m_children->count())
    {
        case 1:
            {
                UIWidget* child_0 = dynamic_cast<UIWidget*>(m_children->objectAtIndex(0));
                
                switch (m_eDirection)
                {
                    case SCROLLVIEW_DIR_VERTICAL: // vertical
                        {
                            float scroll_top = m_fTopBoundary;
                            float child_0_top = child_0->getRelativeTopPos();
                            float offset = scroll_top - child_0_top;
                            m_fDisBoundaryToChild_0 = (offset > 0) ? offset : 0;
                        }
                        break;
                        
                    case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
                        {
                            float scroll_left = m_fLeftBoundary;
                            float child_0_left = child_0->getRelativeLeftPos();
                            float offset = child_0_left - scroll_left;
                            m_fDisBoundaryToChild_0 = (offset > 0) ? offset : 0;
                        }
                        break;
                        
                    default:
                        break;
                }
            }
            break;
            
        default:
            resetProperty();
            break;
    }
}

void UIScrollView::resetProperty()
{
    if (m_children->count() <= 0)
    {
        return;
    }
    
    float scroll_top = m_fTopBoundary;
    float scroll_left = m_fLeftBoundary;
    
    switch (m_children->count())
    {
        case 1:
            {
                UIWidget* child_0 = dynamic_cast<UIWidget*>(m_children->objectAtIndex(0));
                
                switch (m_eDirection)
                {
                    case SCROLLVIEW_DIR_VERTICAL: // vertical
                        {
                            float child_0_top = child_0->getRelativeTopPos();
                            float offset = scroll_top - child_0_top;
                            m_fDisBoundaryToChild_0 = (offset > 0) ? offset : 0;
                        }
                        break;
                        
                    case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
                        {
                            float child_0_left = child_0->getRelativeLeftPos();
                            float offset = child_0_left - scroll_left;
                            m_fDisBoundaryToChild_0 = (offset > 0) ? offset : 0;
                        }
                        break;
                        
                    default:
                        break;
                }
            }
            break;
            
        default:
            {
                UIWidget* child_0 = dynamic_cast<UIWidget*>(m_children->objectAtIndex(0));
                UIWidget* child_1 = dynamic_cast<UIWidget*>(m_children->objectAtIndex(1));
                
                switch (m_eDirection)
                {
                    case SCROLLVIEW_DIR_VERTICAL: // vertical
                        {
                            float child_0_top = child_0->getRelativeTopPos();
                            float offset = scroll_top - child_0_top;
                            m_fDisBoundaryToChild_0 = (offset > 0) ? offset : 0;
                            m_fDisBetweenChild = child_0->getPosition().y - child_1->getPosition().y;
                        }
                        break;
                        
                    case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
                        {
                            float child_0_left = child_0->getRelativeLeftPos();
                            float offset = child_0_left - scroll_left;
                            m_fDisBoundaryToChild_0 = (offset > 0) ? offset : 0;
                            m_fDisBetweenChild = child_1->getPosition().x - child_0->getPosition().x;
                        }
                        break;
                        
                    default:
                        break;
                }
            }
            break;
    }
}

void UIScrollView::resortChildren()
{
    if (!m_children || m_children->count() <= 0)
    {
        return;
    }
    UIWidget* leftChild = (UIWidget*)(m_children->objectAtIndex(0));
    UIWidget* rightChild = (UIWidget*)(m_children->objectAtIndex(0));
    UIWidget* topChild = (UIWidget*)(m_children->objectAtIndex(0));
    UIWidget* bottomChild = (UIWidget*)(m_children->objectAtIndex(0));
    for (int i = 0; i < m_children->count(); i++)
    {
        UIWidget* child = (UIWidget*)(m_children->objectAtIndex(i));
        if (leftChild->getRelativeRect().origin.x > child->getRelativeRect().origin.x)
        {
            leftChild = child;
        }
        if (rightChild->getRelativeRect().origin.x + rightChild->getRelativeRect().size.width < child->getRelativeRect().origin.x + child->getRelativeRect().size.width)
        {
            rightChild = child;
        }
        if (topChild->getRelativeRect().origin.y + topChild->getRelativeRect().size.height < child->getRelativeRect().origin.y + child->getRelativeRect().size.height)
        {
            topChild = child;
        }
        if (bottomChild->getRelativeRect().origin.y > child->getRelativeRect().origin.y){
            bottomChild = child;
        }
    }
    m_pTopChild = topChild;
    m_pBottomChild = bottomChild;
    m_pLeftChild = leftChild;
    m_pRightChild = rightChild;
}

void UIScrollView::moveChildren(float offset)
{
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            for (int i = 0; i < m_children->count(); i++)
            {
                UIWidget* child = (UIWidget*)(m_children->objectAtIndex(i));
                moveChildPoint.x = child->getPosition().x;
                moveChildPoint.y = child->getPosition().y + offset;
                child->setPosition(moveChildPoint);
                child->setVisible(child->checkBeVisibleInParent());
            }
            break;
            
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            for (int i=0;i<m_children->count();i++)
            {
                UIWidget* child = (UIWidget*)(m_children->objectAtIndex(i));
                moveChildPoint.x = child->getPosition().x + offset;
                moveChildPoint.y = child->getPosition().y;
                child->setPosition(moveChildPoint);
                child->setVisible(child->checkBeVisibleInParent());
            }
            break;
            
        default:
            break;
    }
}

void UIScrollView::autoScrollChildren(float dt)
{
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {                        
                case SCROLLVIEW_MOVE_DIR_UP: // up
                    {
                        float curDis = getCurAutoScrollDistance(dt);
                        if (curDis <= 0)
                        {
                            curDis = 0;
                            stopAutoScrollChildren();
                        }
                        if (!scrollChildren(curDis))
                        {
                            stopAutoScrollChildren();
                            
                            if (m_eMoveMode == SCROLLVIEW_MOVE_MODE_ACTION)
                            {
                                resetPositionWithAction();
                            }
                        }
                    }
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_DOWN: // down
                    {
                        float curDis = getCurAutoScrollDistance(dt);
                        if (curDis <= 0)
                        {
                            curDis = 0;
                            stopAutoScrollChildren();
                        }
                        if (!scrollChildren(-curDis))
                        {
                            stopAutoScrollChildren();
                            
                            if (m_eMoveMode == SCROLLVIEW_MOVE_MODE_ACTION)
                            {
                                resetPositionWithAction();
                            }
                        }
                    }
                    break;
                    
                default:
                    break;
            }
            break;
            
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_LEFT: // left
                    {
                        float curDis = getCurAutoScrollDistance(dt);
                        if (curDis <= 0)
                        {
                            curDis = 0;
                            stopAutoScrollChildren();
                        }
                        if (!scrollChildren(-curDis))
                        {
                            stopAutoScrollChildren();
                            
                            if (m_eMoveMode == SCROLLVIEW_MOVE_MODE_ACTION)
                            {
                                resetPositionWithAction();
                            }
                        }
                    }
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                    {
                        float curDis = getCurAutoScrollDistance(dt);
                        if (curDis <= 0)
                        {
                            curDis = 0;
                            stopAutoScrollChildren();
                        }
                        if (!scrollChildren(curDis))
                        {
                            stopAutoScrollChildren();
                            
                            if (m_eMoveMode == SCROLLVIEW_MOVE_MODE_ACTION)
                            {
                                resetPositionWithAction();
                            }
                        }
                    }
                    break;
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
}

void UIScrollView::startAutoScrollChildren(float v)
{
    m_fAutoScrollOriginalSpeed = v;
    m_bAutoScroll = true;
}

void UIScrollView::stopAutoScrollChildren()
{
    m_bAutoScroll = false;
    m_fAutoScrollOriginalSpeed = 0.0;
}

float UIScrollView::getCurAutoScrollDistance(float time)
{
    float dt = time;
    m_fAutoScrollOriginalSpeed -= m_fAutoScrollAcceleration*dt;
    float distance = m_fAutoScrollOriginalSpeed*dt;
    distance = MIN(distance, m_fDisBetweenChild);
    return distance;
}

void UIScrollView::resetPositionWithAction()
{
    using namespace cocos2d;
    CCPoint delta = CCPointZero;
    UIWidget* child = getCheckPositionChild();
    
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_UP: // up
                    delta.y = m_fBottomBoundary + m_fDisBoundaryToChild_0 - child->getRelativeBottomPos();;
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_DOWN: // down
                    delta.y = m_fTopBoundary - m_fDisBoundaryToChild_0 - child->getRelativeTopPos();
                    break;
                    
                default:
                    break;
            }
            break;
            
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_LEFT: // left
                    delta.x = m_fRightBoundary - m_fDisBoundaryToChild_0 - child->getRelativeRightPos();
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                    delta.x = m_fLeftBoundary + m_fDisBoundaryToChild_0 - child->getRelativeLeftPos();
                    break;
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
    
    int times = m_children->count();
    for (int i = 0; i < times - 1; ++i)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(m_children->objectAtIndex(i));
        CCMoveBy* moveBy = CCMoveBy::create(0.25, delta);
        CCEaseOut* ease = CCEaseOut::create(moveBy, 0.5);
        child->runAction(ease);
    }
    
    UIWidget* child_last = dynamic_cast<UIWidget*>(m_children->lastObject());
    CCMoveBy* moveBy = CCMoveBy::create(0.25, delta);
    CCEaseOut* ease = CCEaseOut::create(moveBy, 0.5);
    CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(UIScrollView::handleScrollActionEvent));
    CCSequence* seq = CCSequence::create(ease, callFunc, NULL);
    child_last->runAction(seq);
    
    isRunningAction = true;
}

UIWidget* UIScrollView::getCheckPositionChild()
{
    UIWidget* child = NULL;
    
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_UP: // up
                    child = dynamic_cast<UIWidget*>(m_children->lastObject());
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_DOWN: // down
                    child = dynamic_cast<UIWidget*>(m_children->objectAtIndex(0));
                    break;
                    
                default:
                    break;
            }
            break;
            
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_LEFT: // left
                    child = dynamic_cast<UIWidget*>(m_children->lastObject());
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                    child = dynamic_cast<UIWidget*>(m_children->objectAtIndex(0));
                    break;
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
    
    return child;
}

void UIScrollView::handleScrollActionEvent()
{
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_UP: // up
                    scrollToBottomEvent();
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_DOWN: // down
                    scrollToTopEvent();
                    break;
                    
                default:
                    break;
            }
            break;
            
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_LEFT: // left
                    scrollToRightEvent();
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                    scrollToLeftEvent();
                    break;
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
    
    isRunningAction = false;
}

float UIScrollView::calculateOffsetWithDragForce(float moveOffset)
{
    float offset = moveOffset;
    UIWidget* child = getCheckPositionChild();
    
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_UP: // up
                    {
                        float scroll_bottom = m_fBottomBoundary;
                        float child_bottom = child->getRelativeBottomPos();
                        
                        if (child_bottom > scroll_bottom)
                        {
                            offset -= m_fDragForce * offset / m_fHeight;
                        }
                    }
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_DOWN: // down
                    {
                        float scroll_top = m_fTopBoundary;
                        float child_top = child->getRelativeTopPos();
                        
                        if (child_top < scroll_top)
                        {
                            offset -= m_fDragForce * offset / m_fHeight;
                        }
                    }
                    break;
                    
                default:
                    break;
            }
            break;
            
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_LEFT: // left
                    {
                        float scroll_right = m_fRightBoundary;
                        float child_right = child->getRelativeRightPos();
                        
                        if (child_right < scroll_right)
                        {
                            offset -= m_fDragForce * offset / m_fWidth;
                        }
                    }
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                    {
                        float scroll_left = m_fLeftBoundary;
                        float child_left = child->getRelativeLeftPos();
                        
                        if (child_left > scroll_left)
                        {
                            offset -= m_fDragForce * offset / m_fWidth;
                        }
                    }
                    break;
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
    
    offset = MIN(offset, m_fDisBetweenChild);
    
    return offset;
}

void UIScrollView::berthChildren(SCROLLVIEW_DIR direction)
{
    switch (direction)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            switch (m_eBerthOrientation)
            {
                case SCROLLVIEW_BERTH_ORI_TOP : // berth top
                    moveChildren(m_fTopBoundary - m_pTopChild->getRelativeTopPos());
                    
                    if (!m_bBerthToTop)
                    {
                        berthToTopEvent();
                    }
                    m_bBerthToTop = true;
                    break;
                    
                case SCROLLVIEW_BERTH_ORI_BOTTOM: // berth bottom
                    moveChildren(m_fBottomBoundary - m_pBottomChild->getRelativeBottomPos());
                    
                    if (!m_bBerthToBottom)
                    {
                        berthToBottomEvent();
                    }
                    m_bBerthToBottom = true;
                    break;
                    
                case SCROLLVIEW_BERTH_ORI_VERTICAL_CENTER: // berth vertical center
                    {
                        float offset = (m_fHeight - m_fChildrenSizeHeight) * 0.5;
                        float distance = (m_fHeight - offset) - m_pTopChild->getRelativeTopPos();
                        moveChildren(distance);
                        
                        if (!m_bBerthToVerticalCenter)
                        {
                            berthToVerticalCenterEvent();
                        }
                        m_bBerthToVerticalCenter = true;
                    }
                    break;
                    
                default:
                    break;
            }
            m_bBerthToTop = false;
            m_bBerthToBottom = false;
            m_bBerthToVerticalCenter = false;
            break;
            
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            switch (m_eBerthOrientation)
            {
                case SCROLLVIEW_BERTH_ORI_LEFT: // berth left
                    moveChildren(m_fLeftBoundary - m_pLeftChild->getRelativeLeftPos());
                    
                    if (!m_bBerthToLeft)
                    {
                        berthToLeftEvent();
                    }
                    m_bBerthToLeft = true;
                    break;
                    
                case SCROLLVIEW_BERTH_ORI_RIGHT: // berth right
                    moveChildren(m_fRightBoundary - m_pRightChild->getRelativeRightPos());
                    
                    if (!m_bBerthToRight)
                    {
                        berthToRightEvent();
                    }
                    m_bBerthToRight = true;
                    break;
                    
                case SCROLLVIEW_BERTH_ORI_HORIZONTAL_CENTER: // berth horizontal center
                    {
                        float offset = (m_fWidth - m_fChildrenSizeWidth) * 0.5;
                        float distance = (m_fWidth - offset) - m_pRightChild->getRelativeRightPos();
                        moveChildren(distance);
                        
                        if (!m_bBerthToHorizontalCenter)
                        {
                            berthToHorizontalCenterEvent();
                        }
                        m_bBerthToHorizontalCenter = true;
                    }
                    break;
                    
                default:
                    break;
            }
            m_bBerthToLeft = false;
            m_bBerthToRight = false;
            m_bBerthToHorizontalCenter = false;
            break;
            
        default:
            break;
    }
}

bool UIScrollView::scrollChildren(float touchOffset)
{
    if (m_children->count() <= 0)
    {
        return false;
    }
    
    float realOffset = touchOffset;
    
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            if (m_fChildrenSizeHeight <= m_fHeight)
            {
                berthChildren(m_eDirection);
                
                return false;
            }
            
            switch (m_eMoveDirection)
            {                        
                case SCROLLVIEW_MOVE_DIR_UP: // up
                    if (!m_pBottomChild)
                    {
                        return false;
                    }
                    
                    switch (m_eMoveMode)
                    {
                        case SCROLLVIEW_MOVE_MODE_NORMAL: // normal
                            if (m_pBottomChild->getRelativeBottomPos() + touchOffset >= m_fBottomBoundary)
                            {
                                realOffset = m_fBottomBoundary - m_pBottomChild->getRelativeBottomPos();
                                moveChildren(realOffset);
                                
                                if (!m_bBottomEnd)
                                {
                                    scrollToBottomEvent();
                                }
                                m_bBottomEnd = true;
                                return false;
                            }
                            break;
                            
                        case SCROLLVIEW_MOVE_MODE_ACTION: // action
                            if (m_pBottomChild->getRelativeBottomPos() > m_fBottomBoundary)
                            {
                                return false;
                            }
                            break;
                            
                        default:
                            break;
                    }
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_DOWN: // down
                    if (!m_pTopChild)
                    {
                        return false;
                    }
                    
                    switch (m_eMoveMode)
                    {
                        case SCROLLVIEW_MOVE_MODE_NORMAL: // normal
                            if (m_pTopChild->getRelativeTopPos() + touchOffset <= m_fTopBoundary)
                            {
                                realOffset = m_fTopBoundary - m_pTopChild->getRelativeTopPos();
                                moveChildren(realOffset);
                                
                                if (!m_bTopEnd)
                                {
                                    scrollToTopEvent();
                                }
                                m_bTopEnd = true;
                                return false;
                            }
                            break;
                            
                        case SCROLLVIEW_MOVE_MODE_ACTION: // action
                            if (m_pTopChild->getRelativeTopPos() < m_fTopBoundary)
                            {
                                return false;
                            }
                            break;
                            
                        default:
                            break;
                    }
                    break;
                    
                default:
                    break;
            }
            
            moveChildren(realOffset);
            m_bTopEnd = false;
            m_bBottomEnd = false;
            return true;
            break;
            
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            if (m_fChildrenSizeWidth <= m_fWidth)
            {
                berthChildren(m_eDirection);
                
                return false;
            }
            
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_LEFT: // left
                    if (!m_pRightChild)
                    {
                        berthChildren(m_eDirection);
                        
                        return false;
                    }
                    
                    switch (m_eMoveMode)
                    {
                        case SCROLLVIEW_MOVE_MODE_NORMAL: // normal
                            if (m_pRightChild->getRelativeRightPos() + touchOffset <= m_fRightBoundary)
                            {
                                realOffset = m_fRightBoundary - m_pRightChild->getRelativeRightPos();
                                moveChildren(realOffset);
                                
                                if (!m_bRightEnd)
                                {
                                    scrollToRightEvent();
                                }
                                m_bRightEnd = true;
                                return false;
                            }
                            break;
                            
                        case SCROLLVIEW_MOVE_MODE_ACTION: // action
                            if (m_pRightChild->getRelativeRightPos() < m_fRightBoundary)
                            {
                                return false;
                            }
                            break;
                            
                        default:
                            break;
                    }
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                    if (!m_pLeftChild)
                    {
                        berthChildren(m_eDirection);

                        return false;
                    }
                    
                    switch (m_eMoveMode)
                    {
                        case SCROLLVIEW_MOVE_MODE_NORMAL: // normal
                            if (m_pLeftChild->getRelativeLeftPos() + touchOffset >= m_fLeftBoundary)
                            {
                                realOffset = m_fLeftBoundary - m_pLeftChild->getRelativeLeftPos();
                                moveChildren(realOffset);
                                
                                if (!m_bLeftEnd)
                                {
                                    scrollToLeftEvent();
                                }
                                m_bLeftEnd = true;
                                return false;
                            }
                            break;
                            
                        case SCROLLVIEW_MOVE_MODE_ACTION: // action
                            if (m_pLeftChild->getRelativeLeftPos() > m_fLeftBoundary)
                            {
                                return false;
                            }
                            break;
                            
                        default:
                            break;
                    }
                    break;
                    
                default:
                    break;
            }
            
            moveChildren(realOffset);
            m_bLeftEnd = false;
            m_bRightEnd = false;
            return true;
            break;
            
        default:
            break;
    }
    
    return false;
}

void UIScrollView::scrollToBottom()
{
    m_eMoveDirection = SCROLLVIEW_MOVE_DIR_UP; // up
    scrollChildren(m_fChildrenSizeHeight);
}

void UIScrollView::scrollToTop()
{
    m_eMoveDirection = SCROLLVIEW_MOVE_DIR_DOWN; // down
    scrollChildren(-m_fChildrenSizeHeight);
}

void UIScrollView::drag(float offset)
{
    if (m_children->count() <= 0)
    {
        return;
    }
    
    switch (m_eMoveMode)
    {
        case SCROLLVIEW_MOVE_MODE_NORMAL: // normal
            scrollChildren(offset);
            break;
            
        case SCROLLVIEW_MOVE_MODE_ACTION: // action
            offset = calculateOffsetWithDragForce(offset);
            moveChildren(offset);
            break;
            
        default:
            break;
    }
}

void UIScrollView::startRecordSlidAction()
{
    if (m_children->count() <= 0)
    {
        return;
    }
    if (m_bAutoScroll){
        stopAutoScrollChildren();
    }
    m_bBePressed = true;
    m_fSlidTime = 0.0;
    
    if (m_eMoveMode == SCROLLVIEW_MOVE_MODE_ACTION)
    {
        if (isRunningAction)
        {
            isRunningAction = false;
            stopAction();
        }
    }
}

void UIScrollView::endRecordSlidAction()
{
    if (m_children->count() <= 0)
    {
        return;
    }
    if (m_fSlidTime <= 0.016f)
    {
        return;
    }
    float totalDis = 0;
    totalDis = m_fTouchEndLocation-m_fTouchStartLocation;
    float orSpeed = fabs(totalDis)/(m_fSlidTime);
    startAutoScrollChildren(orSpeed);
    
    m_bBePressed = false;
    m_fSlidTime = 0.0;
}

void UIScrollView::handlePressLogic(cocos2d::CCPoint &touchPoint)
{        
    cocos2d::CCPoint nsp = m_pRender->convertToNodeSpace(touchPoint);
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            m_fTouchMoveStartLocation = nsp.y;
            m_fTouchStartLocation = nsp.y;
            break;
            
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            m_fTouchMoveStartLocation = nsp.x;
            m_fTouchStartLocation = nsp.x;
            break;
            
        default:
            break;
    }
    startRecordSlidAction();
}

void UIScrollView::handleMoveLogic(cocos2d::CCPoint &touchPoint)
{
    cocos2d::CCPoint nsp = m_pRender->convertToNodeSpace(touchPoint);
    float offset = 0.0;
    
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            {
                float moveY = nsp.y;
                offset = moveY - m_fTouchMoveStartLocation;
                m_fTouchMoveStartLocation = moveY;
                
                if (offset < 0)
                {
                    m_eMoveDirection = SCROLLVIEW_MOVE_DIR_DOWN; // down
                }
                else if (offset > 0)
                {
                    m_eMoveDirection = SCROLLVIEW_MOVE_DIR_UP; // up
                }
            }
            break;
            
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            {
                float moveX = nsp.x;
                offset = moveX - m_fTouchMoveStartLocation;
                m_fTouchMoveStartLocation = moveX;
                
                if (offset < 0)
                {
                    m_eMoveDirection = SCROLLVIEW_MOVE_DIR_LEFT; // left
                }
                else if (offset > 0)
                {
                    m_eMoveDirection = SCROLLVIEW_MOVE_DIR_RIGHT; // right
                }
            }
            break;
            
        default:
            break;
    }
    
    drag(offset);
}

void UIScrollView::handleReleaseLogic(cocos2d::CCPoint &touchPoint)
{
    cocos2d::CCPoint nsp = m_pRender->convertToNodeSpace(touchPoint);
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            m_fTouchEndLocation = nsp.y;
            break;
            
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            m_fTouchEndLocation = nsp.x;
            break;
            
        default:
            break;
    }
    endRecordSlidAction();
}    

void UIScrollView::onTouchBegan(cocos2d::CCPoint &touchPoint)
{
    UIPanel::onTouchBegan(touchPoint);
    handlePressLogic(touchPoint);
}

void UIScrollView::onTouchMoved(cocos2d::CCPoint &touchPoint)
{
    UIPanel::onTouchMoved(touchPoint);
    handleMoveLogic(touchPoint);
}

void UIScrollView::onTouchEnded(cocos2d::CCPoint &touchPoint)
{
    UIPanel::onTouchEnded(touchPoint);
    handleReleaseLogic(touchPoint);
}

void UIScrollView::onTouchCancelled(cocos2d::CCPoint &touchPoint)
{
    UIPanel::onTouchCancelled(touchPoint);
}

void UIScrollView::onTouchLongClicked(cocos2d::CCPoint &touchPoint)
{
    
}

void UIScrollView::update(float dt)
{
    if (m_bAutoScroll)
    {
        autoScrollChildren(dt);
    }
    recordSlidTime(dt);
    
    if (m_eMoveMode == SCROLLVIEW_MOVE_MODE_ACTION)
    {
        if (isRunningAction)
        {
            int times = m_children->count();
            
            for (int i = 0; i < times; ++i)
            {
                UIWidget* child = dynamic_cast<UIWidget*>(m_children->objectAtIndex(i));
                child->setVisible(child->checkBeVisibleInParent());
            }
        }
    }
}

void UIScrollView::recordSlidTime(float dt)
{
    if (m_bBePressed)
    {
        m_fSlidTime += dt;
    }
}

void UIScrollView::checkChildInfo(int handleState,UIWidget* sender,cocos2d::CCPoint &touchPoint)
{
    switch (handleState)
    {
        case 0:
            handlePressLogic(touchPoint);
            break;
            
        case 1:
            {
                float offset = 0;
                switch (m_eDirection)
                {
                    case SCROLLVIEW_DIR_VERTICAL: // vertical
                        offset = fabs(sender->getTouchStartPos().y - touchPoint.y);
                        break;
                        
                    case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
                        offset = fabs(sender->getTouchStartPos().x - touchPoint.x);
                        break;
                        
                    default:
                        break;
                }
                if (offset > m_fChildFocusCancelOffset)
                {
                    sender->setFocus(false);
                    handleMoveLogic(touchPoint);
                }
            }
            break;
            
        case 2:
            handleReleaseLogic(touchPoint);
            break;
            
        case 3:
            break;
    }
}

void UIScrollView::scrollToTopEvent()
{
    if (m_pScrollToTopListener && m_pfnScrollToTopSelector)
    {
        (m_pScrollToTopListener->*m_pfnScrollToTopSelector)(this);
    }
}

void UIScrollView::scrollToBottomEvent()
{
    if (m_pScrollToBottomListener && m_pfnScrollToBottomSelector)
    {
        (m_pScrollToBottomListener->*m_pfnScrollToBottomSelector)(this);
    }
}

void UIScrollView::scrollToLeftEvent()
{
    if (m_pScrollToLeftListener && m_pfnScrollToLeftSelector)
    {
        (m_pScrollToLeftListener->*m_pfnScrollToLeftSelector)(this);
    }
}

void UIScrollView::scrollToRightEvent()
{
    if (m_pScrollToRightListener && m_pfnScrollToRightSelector)
    {
        (m_pScrollToRightListener->*m_pfnScrollToRightSelector)(this);
    }
}

void UIScrollView::addScrollToTopEvent(cocos2d::CCObject *target, SEL_ScrollToTopEvent selector)
{
    m_pScrollToTopListener = target;
    m_pfnScrollToTopSelector = selector;
}

void UIScrollView::addScrollToBottomEvent(cocos2d::CCObject *target, SEL_ScrollToBottomEvent selector)
{
    m_pScrollToBottomListener = target;
    m_pfnScrollToBottomSelector = selector;
}

void UIScrollView::addScrollToLeftEvent(cocos2d::CCObject *target, SEL_ScrollToLeftEvent selector)
{
    m_pScrollToLeftListener = target;
    m_pfnScrollToLeftSelector = selector;
}

void UIScrollView::addScrollToRightEvent(cocos2d::CCObject *target, SEL_ScrollToRightEvent selector)
{
    m_pScrollToRightListener = target;
    m_pfnScrollToRightSelector = selector;
}

void UIScrollView::berthToTopEvent()
{
    if (m_pBerthToTopListener && m_pfnBerthToTopSelector)
    {
        (m_pBerthToTopListener->*m_pfnBerthToTopSelector)(this);
    }
}

void UIScrollView::berthToBottomEvent()
{
    if (m_pBerthToBottomListener && m_pfnBerthToBottomSelector)
    {
        (m_pBerthToBottomListener->*m_pfnBerthToBottomSelector)(this);
    }
}

void UIScrollView::berthToVerticalCenterEvent()
{
    if (m_pBerthToVerticalCenterListener && m_pfnBerthToVerticalCenterSelector)
    {
        (m_pBerthToVerticalCenterListener->*m_pfnBerthToVerticalCenterSelector)(this);
    }
}

void UIScrollView::berthToLeftEvent()
{
    if (m_pBerthToLeftListener && m_pfnBerthToLeftSelector)
    {
        (m_pBerthToLeftListener->*m_pfnBerthToLeftSelector)(this);
    }
}

void UIScrollView::berthToRightEvent()
{
    if (m_pBerthToRightListener && m_pfnBerthToRightSelector)
    {
        (m_pBerthToLeftListener->*m_pfnBerthToRightSelector)(this);
    }
}

void UIScrollView::berthToHorizontalCenterEvent()
{
    if (m_pBerthToHorizontalCenterListener && m_pfnBerthToHorizontalCenterSelector)
    {
        (m_pBerthToHorizontalCenterListener->*m_pfnBerthToHorizontalCenterSelector)(this);
    }
}

void UIScrollView::addBerthToTopEvent(cocos2d::CCObject *target, SEL_BerthToTopEvent selector)
{
    m_pBerthToTopListener = target;
    m_pfnBerthToTopSelector = selector;
}

void UIScrollView::addBerthToBottomEvent(cocos2d::CCObject *target, SEL_BerthToBottomEvent selector)
{
    m_pBerthToBottomListener = target;
    m_pfnBerthToBottomSelector = selector;
}

void UIScrollView::addBerthToVerticalCenterEvent(cocos2d::CCObject *target, SEL_BerthToVerticalCenterEvent selector)
{
    m_pBerthToVerticalCenterListener = target;
    m_pfnBerthToVerticalCenterSelector = selector;
}

void UIScrollView::addBerthToLeftEvent(cocos2d::CCObject *target, SEL_BerthToLeftEvent selector)
{
    m_pBerthToLeftListener = target;
    m_pfnBerthToLeftSelector = selector;
}

void UIScrollView::addBerthToRightEvent(cocos2d::CCObject *target, SEL_BerthToRightEvent selector)
{
    m_pBerthToRightListener = target;
    m_pfnBerthToRightSelector = selector;
}

void UIScrollView::addBerthToHorizontalCenterEvent(cocos2d::CCObject *target, SEL_BerthToHorizontalCenterEvent selector)
{
    m_pBerthToHorizontalCenterListener = target;
    m_pfnBerthToHorizontalCenterSelector = selector;
}

void UIScrollView::stopAction()
{
    int times = m_children->count();
    
    for (int i = 0; i < times; ++i)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(m_children->objectAtIndex(i));
        child->stopAllActions();
    }
}

void UIScrollView::setDirection(SCROLLVIEW_DIR dir)
{
    m_eDirection = dir;
    
    resetProperty();
}

SCROLLVIEW_DIR UIScrollView::getDirection()
{
    return m_eDirection;
}

void UIScrollView::setMoveDirection(SCROLLVIEW_MOVE_DIR dir)
{
    m_eMoveDirection = dir;
}

SCROLLVIEW_MOVE_DIR UIScrollView::getMoveDirection()
{
    return m_eMoveDirection;
}

void UIScrollView::setMoveMode(SCROLLVIEW_MOVE_MODE mode)
{
    m_eMoveMode = mode;
}

SCROLLVIEW_MOVE_MODE UIScrollView::getMoveMode()
{
    return m_eMoveMode;
}

void UIScrollView::setBerthOrientation(SCROLLVIEW_BERTH_ORI mode)
{
    m_eBerthOrientation = mode;
}

SCROLLVIEW_BERTH_ORI UIScrollView::getBerthOrientation()
{
    return m_eBerthOrientation;
}

NS_CC_EXT_END