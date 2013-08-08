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

#include "UIListView.h"

NS_CC_EXT_BEGIN

UIListView::UIListView() :    
m_pInitChildListener(NULL),
m_pfnInitChildSelector(NULL),
m_pUpdateChildListener(NULL),
m_pfnUpdateChildSelector(NULL),
m_pChildPool(NULL),
m_pUpdatePool(NULL),
m_nDataLength(0),
m_nBegin(0),
m_nEnd(0),
m_pUpdateChild(NULL),
m_nUpdateDataIndex(-1),
m_bUpdateSuccess(false),
m_overTopArray(NULL),
m_overBottomArray(NULL),
m_overLeftArray(NULL),
m_overRightArray(NULL)
{
    m_WidgetName = WIDGET_LISTVIEW;
}

UIListView::~UIListView()
{    
    CC_SAFE_RELEASE_NULL(m_pChildPool);
    CC_SAFE_RELEASE_NULL(m_pUpdatePool);
    CC_SAFE_RELEASE_NULL(m_overTopArray);
    CC_SAFE_RELEASE_NULL(m_overBottomArray);
    CC_SAFE_RELEASE_NULL(m_overLeftArray);
    CC_SAFE_RELEASE_NULL(m_overRightArray);        
}

UIListView* UIListView::create()
{
    UIListView* widget = new UIListView();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UIListView::init()
{
    if (UIScrollView::init())
    {
        m_pChildPool = CCArray::create();
        m_pUpdatePool = CCArray::create();
        CC_SAFE_RETAIN(m_pChildPool);
        CC_SAFE_RETAIN(m_pUpdatePool);
        m_overTopArray = cocos2d::CCArray::create();
        m_overBottomArray = cocos2d::CCArray::create();
        m_overLeftArray = cocos2d::CCArray::create();
        m_overRightArray = cocos2d::CCArray::create();
        CC_SAFE_RETAIN(m_overTopArray);
        CC_SAFE_RETAIN(m_overBottomArray);
        CC_SAFE_RETAIN(m_overLeftArray);
        CC_SAFE_RETAIN(m_overRightArray);
        
        return true;
    }
    return false;
}

bool UIListView::addChild(UIWidget *widget)
{
    UIScrollView::addChild(widget);
    
    return true;
}

void UIListView::removeAllChildrenAndCleanUp(bool cleanup)
{
    UIScrollView::removeAllChildrenAndCleanUp(cleanup);
    
    m_pUpdatePool->removeAllObjects();
    m_pChildPool->removeAllObjects();
    /*
    m_pUpdatePool->clear();
    m_pChildPool->clear();
     */
}

void UIListView::endRecordSlidAction()
{
    if (m_children->count() <= 0)
    {
        return;
    }
    if (m_fSlidTime <= 0.016f)
    {
        CCLOG("m_fSlidTime <= 0.016f");
        return;
    }
    float totalDis = 0;
    totalDis = m_fTouchEndLocation-m_fTouchStartLocation;
    float orSpeed = fabs(totalDis)/(m_fSlidTime);
    startAutoScrollChildren(orSpeed / 2);
    
    m_bBePressed = false;
    m_fSlidTime = 0.0;
}

bool UIListView::scrollChildren(float touchOffset)
{
    if (m_children->count() <= 0)
    {
        return false;
    }
    
    float realOffset = touchOffset;
    
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical            
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_UP: // up
                    {
                        UIWidget* child_last = dynamic_cast<UIWidget*>(m_pChildPool->lastObject());
//                        UIWidget* child_last = m_pChildPool->rbegin();                        
                        float child_last_bottom = child_last->getRelativeBottomPos();
                        float scroll_bottom = m_fBottomBoundary;
                        
                        if (m_nEnd == m_nDataLength - 1)
                        {
                            if (realOffset > scroll_bottom - child_last_bottom)
                            {
                                realOffset = scroll_bottom - child_last_bottom;
                            }
                            UIScrollView::moveChildren(realOffset);
                            return false;
                        }
                        UIScrollView::moveChildren(realOffset);
                        
                        if (m_nEnd < m_nDataLength - 1)
                        {
                            collectOverTopChild();
                            int count = m_overTopArray->count();
                            if (count > 0)
                            {
                                updateChild();
                                setLoopPosition();
                                m_overTopArray->removeAllObjects();
                            }
                        }
                    }
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_DOWN: // down
                    {
                        UIWidget* child_0 = dynamic_cast<UIWidget*>(m_pChildPool->objectAtIndex(0));
//                        UIWidget* child_0 = m_pChildPool->begin();
                        float child_0_top = child_0->getRelativeTopPos();
                        float scroll_top = m_fTopBoundary;
                        
                        if (m_nBegin == 0)
                        {
                            if (realOffset < scroll_top - child_0_top)
                            {
                                realOffset = scroll_top - child_0_top;
                            }
                            UIScrollView::moveChildren(realOffset);
                            return false;
                        }
                        UIScrollView::moveChildren(realOffset);
                                                
                        if (m_nBegin > 0)
                        {
                            collectOverBottomChild();
                            int count = m_overBottomArray->count();
                            if (count > 0)
                            {
                                updateChild();
                                setLoopPosition();
                                m_overBottomArray->removeAllObjects();
                            }
                        }
                    }
                    break;
                    
                default:
                    break;
            }                                                                
            return true;
            break;
            
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_LEFT: // left
                    {
                        UIWidget* child_last = dynamic_cast<UIWidget*>(m_pChildPool->lastObject());
//                        UIWidget* child_last = m_pChildPool->rbegin();
                        float child_last_right = child_last->getRelativeRightPos();
                        float scroll_right = m_fRightBoundary;
                        
                        if (m_nEnd == m_nDataLength - 1)
                        {
                            if (realOffset < scroll_right - child_last_right)
                            {
                                realOffset = scroll_right - child_last_right;
                            }
                        }
                        UIScrollView::moveChildren(realOffset);
                        if (m_nEnd == m_nDataLength - 1)
                        {
                            return false;
                        }
                                                
                        if (m_nEnd < m_nDataLength - 1)
                        {
                            collectOverLeftChild();
                            int count = m_overLeftArray->count();
                            if (count > 0)
                            {
                                updateChild();
                                setLoopPosition();
                                m_overLeftArray->removeAllObjects();
                            }
                        }                                                                                                                
                    }
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                    {
                        UIWidget* child_0 = dynamic_cast<UIWidget*>(m_pChildPool->objectAtIndex(0));
//                        UIWidget* child_0 = m_pChildPool->begin();
                        float child_0_left = child_0->getRelativeLeftPos();
                        float scroll_left = m_fLeftBoundary;
                        
                        if (m_nBegin == 0)
                        {
                            if (realOffset > scroll_left - child_0_left)
                            {
                                realOffset = scroll_left - child_0_left;
                            }
                        }
                        UIScrollView::moveChildren(realOffset);
                        if (m_nBegin == 0)
                        {
                            return false;
                        }
                                                
                        collectOverRightChild();
                        int count = m_overRightArray->count();
                        if (count > 0)
                        {
                            updateChild();
                            setLoopPosition();
                            m_overRightArray->removeAllObjects();
                        }                                                                                    
                    }
                    break;
                    
                default:
                    break;
            }                                                                                                      
            return true;
            break;
            
        default:
            break;
    }
    
    return false;
}        

void UIListView::drag(float offset)
{
    if (m_children->count() <= 0)
    {
        return;
    }
    
    scrollChildren(offset);        
}        

UIWidget* UIListView::getCheckPositionChild()
{
    UIWidget* child = NULL;
    
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_UP: // up
                    child = dynamic_cast<UIWidget*>(m_pChildPool->lastObject());
//                    child = m_pChildPool->rbegin();
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_DOWN: // down
                    child = dynamic_cast<UIWidget*>(m_pChildPool->objectAtIndex(0));
//                    child = m_pChildPool->begin();
                    break;
                    
                default:
                    break;
            }
            break;
            
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_LEFT: // left
                    child = dynamic_cast<UIWidget*>(m_pChildPool->lastObject());
//                    child = m_pChildPool->rbegin();
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                    child = dynamic_cast<UIWidget*>(m_pChildPool->objectAtIndex(0));
//                    child = m_pChildPool->begin();
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

void UIListView::initChildWithDataLength(int length)
{
    m_nDataLength = length;
    m_nBegin = 0;
    m_nEnd = 0;        
    
    // init child pool
    ccArray* arrayChildren = m_children->data;
    int times = arrayChildren->num;
    for (int i = 0; i < times; ++i)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
        setUpdateChild(child);
        setUpdateDataIndex(i);
        initChildEvent();
        m_pChildPool->addObject(child);
//        m_pChildPool->push_back(child);
        m_nEnd = i;
    }
}

UIWidget* UIListView::getChildFromUpdatePool()
{
    UIWidget* child = dynamic_cast<UIWidget*>(m_pUpdatePool->lastObject());
    m_pUpdatePool->removeLastObject();
//    UIWidget* child = m_pUpdatePool->rbegin();
//    m_pUpdatePool->pop_back();
    return child;
}

void UIListView::pushChildToPool()
{
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_UP: // up
                    {
                        UIWidget* child = dynamic_cast<UIWidget*>(m_pChildPool->objectAtIndex(0));
                        m_pUpdatePool->insertObject(child, 0);
                        m_pChildPool->removeObjectAtIndex(0);
//                        UIWidget* child = m_pChildPool->begin();
//                        m_pUpdatePool->push_front(child);
//                        m_pChildPool->pop_front();
                    }
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_DOWN: // down
                    {
                        UIWidget* child = dynamic_cast<UIWidget*>(m_pChildPool->lastObject());
                        m_pUpdatePool->insertObject(child, 0);
                        m_pChildPool->removeLastObject();
//                        UIWidget* child = m_pChildPool->rbegin();
//                        m_pUpdatePool->push_front(child);
//                        m_pChildPool->pop_back();
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
                        UIWidget* child = dynamic_cast<UIWidget*>(m_pChildPool->objectAtIndex(0));
                        m_pUpdatePool->insertObject(child, 0);
                        m_pChildPool->removeObjectAtIndex(0);
//                        UIWidget* child = m_pChildPool->begin();
//                        m_pUpdatePool->push_front(child);
//                        m_pChildPool->pop_front();
                    }
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                    {
                        UIWidget* child = dynamic_cast<UIWidget*>(m_pChildPool->lastObject());
                        m_pUpdatePool->insertObject(child, 0);
                        m_pChildPool->removeLastObject();
//                        UIWidget* child = m_pChildPool->rbegin();
//                        m_pUpdatePool->push_front(child);
//                        m_pChildPool->pop_back();
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

void UIListView::getAndCallback()
{
    UIWidget* child = getChildFromUpdatePool();
    
    if (child == NULL)
    {
        return;
    }
    
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_UP: // up
                    ++m_nEnd;
                    setUpdateChild(child);
                    setUpdateDataIndex(m_nEnd);
                    updateChildEvent();
                    
                    if (m_bUpdateSuccess == false)
                    {
                        --m_nEnd;
                        m_pChildPool->insertObject(child, 0);
//                        m_pChildPool->push_front(child);
                        return;
                    }
                    ++m_nBegin;
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_DOWN: // down
                    --m_nBegin;
                    setUpdateChild(child);
                    setUpdateDataIndex(m_nBegin);
                    updateChildEvent();
                    
                    if (m_bUpdateSuccess == false)
                    {
                        ++m_nBegin;
                        m_pChildPool->addObject(child);
//                        m_pChildPool->push_back(child);
                        return;
                    }
                    --m_nEnd;
                    break;
                    
                default:
                    break;
            }
            break;
            
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_LEFT: // left
                    ++m_nEnd;
                    setUpdateChild(child);
                    setUpdateDataIndex(m_nEnd);
                    updateChildEvent();
                    
                    if (m_bUpdateSuccess == false)
                    {
                        --m_nEnd;
                        m_pChildPool->insertObject(child, 0);
//                        m_pChildPool->push_front(child);
                        return;
                    }
                    ++m_nBegin;
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                    --m_nBegin;
                    setUpdateChild(child);
                    setUpdateDataIndex(m_nBegin);
                    updateChildEvent();
                    
                    if (m_bUpdateSuccess == false)
                    {
                        ++m_nBegin;
                        m_pChildPool->addObject(child);
//                        m_pChildPool->push_back(child);
                        return;
                    }
                    --m_nEnd;
                    break;
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
    
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_UP: // up
                    m_pChildPool->addObject(child);
//                    m_pChildPool->push_back(child);
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_DOWN: // down
                    m_pChildPool->insertObject(child, 0);
//                    m_pChildPool->push_front(child);
                    break;
                    
                default:
                    break;
            }
            break;
            
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_LEFT: // left
                    m_pChildPool->addObject(child);
//                    m_pChildPool->push_back(child);
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                    m_pChildPool->insertObject(child, 0);
//                    m_pChildPool->push_front(child);
                    break;
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
}

int UIListView::getDataLength()
{
    return m_nDataLength;
}        

UIWidget* UIListView::getUpdateChild()
{
    return m_pUpdateChild;
}

void UIListView::setUpdateChild(UIWidget* child)
{
    m_pUpdateChild = child;
}

int UIListView::getUpdateDataIndex()
{
    return m_nUpdateDataIndex;
}

void UIListView::setUpdateDataIndex(int index)
{
    m_nUpdateDataIndex = index;
}

bool UIListView::getUpdateSuccess()
{
    return m_bUpdateSuccess;
}

void UIListView::setUpdateSuccess(bool sucess)
{
    m_bUpdateSuccess = sucess;
}

void UIListView::collectOverTopChild()
{
    float scroll_top = m_fTopBoundary;
    
    if (m_overTopArray->count() > 0)
    {
        m_overTopArray->removeAllObjects();
    }
    
    
    ccArray* arrayChildren = m_children->data;
    int times = arrayChildren->num;
    for (int i = 0; i < times; ++i)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
        float child_bottom = child->getRelativeBottomPos();
        
        if (child_bottom >= scroll_top)
        {
            m_overTopArray->addObject(child);                
        }
    }
}

void UIListView::collectOverBottomChild()
{
    float scroll_bottom = m_fBottomBoundary;
    
    if (m_overBottomArray->count() > 0)
    {
        m_overBottomArray->removeAllObjects();
    }
    
    ccArray* arrayChildren = m_children->data;
    int times = arrayChildren->num;
    for (int i = 0; i < times; ++i)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
        float child_top = child->getRelativeTopPos();
        
        if (child_top <= scroll_bottom)
        {
            m_overBottomArray->addObject(child);                
        }
    }
}

void UIListView::collectOverLeftChild()
{
    float scroll_left = m_fLeftBoundary;
    
    if (m_overLeftArray->count() > 0)
    {
        m_overLeftArray->removeAllObjects();
    }
    
    ccArray* arrayChildren = m_children->data;
    int times = arrayChildren->num;
    for (int i = 0; i < times; ++i)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
        float child_right = child->getRelativeRightPos();
        
        if (child_right <= scroll_left)
        {
            m_overLeftArray->addObject(child);                
        }
    }
}

void UIListView::collectOverRightChild()
{
    float scroll_right = m_fRightBoundary;
    
    if (m_overRightArray->count() > 0)
    {
        m_overRightArray->removeAllObjects();
    }
    
    ccArray* arrayChildren = m_children->data;
    int times = arrayChildren->num;
    for (int i = 0; i < times; ++i)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
        float child_left = child->getRelativeLeftPos();
        
        if (child_left >= scroll_right)
        {
            m_overRightArray->addObject(child);                
        }
    }
}

void UIListView::setLoopPosition()
{
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_UP: // up
                    if (m_overTopArray->count() == m_children->count())
                    {
                        int count = m_overTopArray->count();
                        for (int i = 0; i < count; ++i)
                        {   
                            UIWidget* child = dynamic_cast<UIWidget*>(m_overTopArray->objectAtIndex(i));
                            
                            if (i == 0)
                            {
                                float y = (count - 1);
//                                float y = (0 - m_fDisBetweenChild) + m_fDisBetweenChild * (count - 1);
                                child->setPosition(ccp(child->getPosition().x, y));
                            }
                            else
                            {
                                UIWidget* prev_child = dynamic_cast<UIWidget*>(m_overTopArray->objectAtIndex(i - 1));
                                child->setPosition(ccp(child->getPosition().x, prev_child->getPosition().y));
                            }
                        }
                    }
                    else
                    {
                        float scroll_top = m_fTopBoundary;
                        
                        int count = m_children->count();
                        for (int i = 0; i < count; ++i)
                        {
                            UIWidget* child = dynamic_cast<UIWidget*>(m_children->objectAtIndex(i));
                            float child_bottom = child->getRelativeBottomPos();
                            
                            if (child_bottom >= scroll_top)
                            {
                                int index = (i == 0) ? (count - 1) : (i - 1);
                                UIWidget* prev_child = dynamic_cast<UIWidget*>(m_children->objectAtIndex(index));
                                child->setPosition(ccp(child->getPosition().x, prev_child->getPosition().y));
                            }
                        }
                    }
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_DOWN: // down
                    if (m_overBottomArray->count() == m_children->count())
                    {
                        int count = m_overBottomArray->count();
                        for (int i = 0; i < count; ++i)
                        {
                            UIWidget* child = dynamic_cast<UIWidget*>(m_overBottomArray->objectAtIndex(i));
                            
                            if (i == 0)
                            {
                                float y = (m_fTopBoundary) * (count - 1);
//                                float y = (m_fTopBoundary) - m_fDisBetweenChild * (count - 1);
                                child->setPosition(ccp(child->getPosition().x, y));
                            }
                            else
                            {
                                UIWidget* prev_child = dynamic_cast<UIWidget*>(m_overBottomArray->objectAtIndex(i - 1));
                                child->setPosition(ccp(child->getPosition().x, prev_child->getPosition().y));                                    
                            }
                        }
                    }
                    else
                    {
                        float scroll_bottom = m_fBottomBoundary;
                        
                        int count = m_children->count();
                        for (int i = count - 1; i >= 0; --i)
                        {
                            UIWidget* child = dynamic_cast<UIWidget*>(m_children->objectAtIndex(i));
                            float child_top = child->getRelativeTopPos();
                            
                            if (child_top <= scroll_bottom)
                            {
                                int index = (i == count - 1) ? 0 : (i + 1);
                                UIWidget* next_child = dynamic_cast<UIWidget*>(m_children->objectAtIndex(index));
                                child->setPosition(ccp(child->getPosition().x, next_child->getPosition().y));                                    
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
                    if (m_overLeftArray->count() == m_children->count())
                    {
                        int count = m_overLeftArray->count();
                        for (int i = 0; i < count; ++i)
                        {
                            UIWidget* child = dynamic_cast<UIWidget*>(m_overLeftArray->objectAtIndex(i));
                            
                            if (i == 0)
                            {
                                float x = m_fRightBoundary * (count - 1);
//                                float x = (m_fRightBoundary + m_fDisBetweenChild) - m_fDisBetweenChild * (count - 1);
                                child->setPosition(ccp(x, child->getPosition().y));
                            }
                            else
                            {
                                UIWidget* prev_child = dynamic_cast<UIWidget*>(m_overLeftArray->objectAtIndex(i - 1));
                                child->setPosition(ccp(prev_child->getPosition().x, child->getPosition().y));                                    
                            }
                        }
                    }
                    else
                    {
                        float scroll_left = m_fLeftBoundary;
                        
                        int count = m_children->count();
                        for (int i = 0; i < count; ++i)
                        {
                            UIWidget* child = dynamic_cast<UIWidget*>(m_children->objectAtIndex(i));
                            float child_right = child->getRelativeRightPos();
                            
                            if (child_right <= scroll_left)
                            {
                                int index = (i == 0) ? (count - 1) : (i - 1);
                                UIWidget* prev_child = dynamic_cast<UIWidget*>(m_children->objectAtIndex(index));
                                child->setPosition(ccp(prev_child->getPosition().x, child->getPosition().y));
                            }
                        }
                    }
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                    if (m_overRightArray->count() == m_children->count())
                    {
                        int count = m_overRightArray->count();
                        for (int i = 0; i < count; ++i)
                        {
                            UIWidget* child = dynamic_cast<UIWidget*>(m_overRightArray->objectAtIndex(i));
                            
                            if (i == 0)
                            {
                                float x = (count - 1);
//                                float x = (0 - m_fDisBetweenChild) + m_fDisBetweenChild * (count - 1);
                                child->setPosition(ccp(x, child->getPosition().y));
                            }
                            else
                            {
                                UIWidget* prev_child = dynamic_cast<UIWidget*>(m_overRightArray->objectAtIndex(i - 1));
                                child->setPosition(ccp(prev_child->getPosition().x, child->getPosition().y));                                    
                            }
                        }
                    }
                    else
                    {
                        float scroll_right = m_fRightBoundary;
                        
                        int count = m_children->count();
                        for (int i = count - 1; i >= 0; --i)
                        {
                            UIWidget* child = dynamic_cast<UIWidget*>(m_children->objectAtIndex(i));
                            float child_left = child->getRelativeLeftPos();
                            
                            if (child_left >= scroll_right)
                            {
                                int index = (i == count - 1) ? 0 : (i + 1);
                                UIWidget* next_child = dynamic_cast<UIWidget*>(m_children->objectAtIndex(index));
                                child->setPosition(ccp(next_child->getPosition().x, child->getPosition().y));
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

void UIListView::updateChild()
{
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_UP: // up
                    {
                        int count = m_overTopArray->count();
                        for (int i = 0; i < count; ++i)
                        {
                            if (m_nEnd < m_nDataLength - 1)
                            {
                                pushChildToPool();
                                getAndCallback();
                            }
                        }                            
                    }
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_DOWN: // down
                    {
                        int count = m_overBottomArray->count();
                        for (int i = 0; i < count; ++i)
                        {
                            if (m_nBegin > 0)
                            {
                                pushChildToPool();
                                getAndCallback();                                        
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
                        int count = m_overLeftArray->count();
                        for (int i = 0; i < count; ++i)
                        {
                            if (m_nEnd < m_nDataLength - 1)
                            {
                                pushChildToPool();
                                getAndCallback();
                            }
                        }
                    }
                    break;
                    
                case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                    {
                        int count = m_overBottomArray->count();
                        for (int i = 0; i < count; ++i)
                        {
                            if (m_nBegin > 0)
                            {
                                pushChildToPool();
                                getAndCallback();
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

void UIListView::initChildEvent()
{
    if (m_pInitChildListener && m_pfnInitChildSelector)
    {
        (m_pInitChildListener->*m_pfnInitChildSelector)(this);
    }
}

void UIListView::updateChildEvent()
{
    if (m_pUpdateChildListener && m_pfnUpdateChildSelector)
    {
        (m_pUpdateChildListener->*m_pfnUpdateChildSelector)(this);
    }
}

void UIListView::addInitChildEvent(cocos2d::CCObject *target, SEL_ListViewInitChildEvent seletor)
{
    m_pInitChildListener = target;
    m_pfnInitChildSelector = seletor;
}

void UIListView::addUpdateChildEvent(cocos2d::CCObject *target, SEL_ListViewUpdateChildEvent selector)
{
    m_pUpdateChildListener = target;
    m_pfnUpdateChildSelector = selector;
}

NS_CC_EXT_END