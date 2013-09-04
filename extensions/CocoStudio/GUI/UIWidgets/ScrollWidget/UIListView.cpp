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

UIListView::UIListView()
: m_eDirection(LISTVIEW_DIR_VERTICAL)
, m_eMoveDirection(LISTVIEW_MOVE_DIR_NONE)
, m_fTouchStartLocation(0.0f)
, m_fTouchEndLocation(0.0f)
, m_fTouchMoveStartLocation(0.0f)
, m_fTopBoundary(0.0f)
, m_fBottomBoundary(0.0f)
, m_fLeftBoundary(0.0f)
, m_fRightBoundary(0.0f)
, m_bAutoScroll(false)
, m_fAutoScrollOriginalSpeed(0.0f)
, m_fAutoScrollAcceleration(600.0f)
, m_bBePressed(false)
, m_fSlidTime(0.0f)
, m_fChildFocusCancelOffset(5.0f)
, m_pInitChildListener(NULL)
, m_pfnInitChildSelector(NULL)
, m_pUpdateChildListener(NULL)
, m_pfnUpdateChildSelector(NULL)
, m_pChildPool(NULL)
, m_pUpdatePool(NULL)
, m_nDataLength(0)
, m_nBegin(0)
, m_nEnd(0)
, m_pUpdateChild(NULL)
, m_nUpdateDataIndex(-1)
, m_bUpdateSuccess(false)
, m_overTopArray(NULL)
, m_overBottomArray(NULL)
, m_overLeftArray(NULL)
, m_overRightArray(NULL)
, m_fDisBoundaryToChild_0(0.0f)
, m_fDisBetweenChild(0.0f)
/* gui mark */
, m_fScrollDegreeRange(45.0f)
/**/
{
}

UIListView::~UIListView()
{
    /* gui mark */
    CC_SAFE_RELEASE_NULL(m_pChildPool);
    CC_SAFE_RELEASE_NULL(m_pUpdatePool);
    /**/
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
    if (Layout::init())
    {
        setUpdateEnabled(true);
        setTouchEnabled(true);
        setClippingEnabled(true);
        
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

void UIListView::onSizeChanged()
{
    Layout::onSizeChanged();
    m_fTopBoundary = m_size.height;
    m_fRightBoundary = m_size.width;
}

bool UIListView::addChild(UIWidget* widget)
{
    Layout::addChild(widget);
    resetProperty();
    return true;
}

void UIListView::removeAllChildrenAndCleanUp(bool cleanup)
{
    m_pUpdatePool->removeAllObjects();
    m_pChildPool->removeAllObjects();
    Layout::removeAllChildrenAndCleanUp(cleanup);
    
    /*
    m_pUpdatePool->clear();
    m_pChildPool->clear();
     */
}

bool UIListView::removeChild(UIWidget* child,bool cleanup)
{
    bool value = false;
    
    if (Layout::removeChild(child, cleanup))
    {
        value = true;
        resetProperty();
    }
    
    return value;
}

bool UIListView::onTouchBegan(const CCPoint &touchPoint)
{
    bool pass = Layout::onTouchBegan(touchPoint);
    handlePressLogic(touchPoint);
    return pass;    
}

void UIListView::onTouchMoved(const CCPoint &touchPoint)
{
    Layout::onTouchMoved(touchPoint);
    /* gui mark */
//    if (isInScrollDegreeRange(this))
    {
        handleMoveLogic(touchPoint);
    }    
    // before
//    handleMoveLogic(touchPoint);
    /**/
}

void UIListView::onTouchEnded(const CCPoint &touchPoint)
{
    Layout::onTouchEnded(touchPoint);
    handleReleaseLogic(touchPoint);
}

void UIListView::onTouchCancelled(const CCPoint &touchPoint)
{
    Layout::onTouchCancelled(touchPoint);
}

void UIListView::onTouchLongClicked(const CCPoint &touchPoint)
{
    
}

void UIListView::update(float dt)
{
    if (m_bAutoScroll)
    {
        autoScrollChildren(dt);
    }
    recordSlidTime(dt);
}

void UIListView::setDirection(ListViewDirection dir)
{
    m_eDirection = dir;
}

ListViewDirection UIListView::getDirection()
{
    return m_eDirection;
}

void UIListView::resetProperty()
{
    ccArray* arrayChildren = m_children->data;
    
    if (arrayChildren->num <= 0)
    {
        return;
    }    
    
    switch (m_eDirection)
    {
        case LISTVIEW_DIR_VERTICAL: // vertical
            if (m_fTopBoundary == 0)
            {
                return;
            }
            break;
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
            if (m_fRightBoundary == 0)
            {
                return;
            }
            break;
            
        default:
            break;
    }
    
    float scroll_top = m_fTopBoundary;
    float scroll_left = m_fLeftBoundary;
    
    switch (m_children->count())
    {
        case 1:
        {
            UIWidget* child_0 = dynamic_cast<UIWidget*>(arrayChildren->arr[0]);            
            
            switch (m_eDirection)
            {
                case LISTVIEW_DIR_VERTICAL: // vertical
                {
                    float child_0_top = child_0->getTopInParent();
                    m_fDisBoundaryToChild_0 = scroll_top - child_0_top;
                }
                    break;
                    
                case LISTVIEW_DIR_HORIZONTAL: // horizontal
                {
                    float child_0_left = child_0->getLeftInParent();
                    m_fDisBoundaryToChild_0 = child_0_left - scroll_left;
                }
                    break;
                    
                default:
                    break;
            }
        }
            break;
            
        default:
        {
            UIWidget* child_0 = dynamic_cast<UIWidget*>(arrayChildren->arr[0]);
            UIWidget* child_1 = dynamic_cast<UIWidget*>(arrayChildren->arr[1]);                        
            
            switch (m_eDirection)
            {
                case LISTVIEW_DIR_VERTICAL: // vertical
                {
                    float child_0_top = child_0->getTopInParent();
                    m_fDisBoundaryToChild_0 = scroll_top - child_0_top;
                    m_fDisBetweenChild = child_0->getPosition().y - child_1->getPosition().y;
                }
                    break;
                    
                case LISTVIEW_DIR_HORIZONTAL: // horizontal
                {
                    float child_0_left = child_0->getLeftInParent();
                    m_fDisBoundaryToChild_0 = child_0_left - scroll_left;
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

void UIListView::handlePressLogic(const CCPoint &touchPoint)
{
    CCPoint nsp = m_pRenderer->convertToNodeSpace(touchPoint);
    
    switch (m_eDirection)
    {
        case LISTVIEW_DIR_VERTICAL: // vertical
            m_fTouchMoveStartLocation = nsp.y;
            m_fTouchStartLocation = nsp.y;
            break;
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
            m_fTouchMoveStartLocation = nsp.x;
            m_fTouchStartLocation = nsp.x;
            break;
            
        default:
            break;
    }
    startRecordSlidAction();
    clearCollectOverArray();
}

void UIListView::handleMoveLogic(const CCPoint &touchPoint)
{
    CCPoint nsp = m_pRenderer->convertToNodeSpace(touchPoint);
    float offset = 0.0f;
    
    switch (m_eDirection)
    {
        case LISTVIEW_DIR_VERTICAL: // vertical
        {
            float moveY = nsp.y;
            offset = moveY - m_fTouchMoveStartLocation;
            m_fTouchMoveStartLocation = moveY;
            
            if (offset < 0.0f)
            {
                m_eMoveDirection = LISTVIEW_MOVE_DIR_DOWN; // down
            }
            else if (offset > 0.0f)
            {
                m_eMoveDirection = LISTVIEW_MOVE_DIR_UP; // up
            }
        }
            break;
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
        {
            float moveX = nsp.x;
            offset = moveX - m_fTouchMoveStartLocation;
            m_fTouchMoveStartLocation = moveX;
            
            if (offset < 0)
            {
                m_eMoveDirection = LISTVIEW_MOVE_DIR_LEFT; // left
            }
            else if (offset > 0)
            {
                m_eMoveDirection = LISTVIEW_MOVE_DIR_RIGHT; // right
            }
        }
            break;
            
        default:
            break;
    }
    scrollChildren(offset);
}

void UIListView::handleReleaseLogic(const CCPoint &touchPoint)
{
    CCPoint nsp = m_pRenderer->convertToNodeSpace(touchPoint);
    
    switch (m_eDirection)
    {
        case LISTVIEW_DIR_VERTICAL: // vertical
            m_fTouchEndLocation = nsp.y;
            break;
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
            m_fTouchEndLocation = nsp.x;
            break;
            
        default:
            break;
    }
    endRecordSlidAction();
}

void UIListView::interceptTouchEvent(int handleState, UIWidget *sender, const CCPoint &touchPoint)
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
                case LISTVIEW_DIR_VERTICAL: // vertical
                    offset = fabs(sender->getTouchStartPos().y - touchPoint.y);
                    break;
                    
                case LISTVIEW_DIR_HORIZONTAL: // horizontal
                    offset = fabs(sender->getTouchStartPos().x - touchPoint.x);
                    break;
                    
                default:
                    break;
            }
            if (offset > m_fChildFocusCancelOffset)
            {
//                if (isInScrollDegreeRange(sender))
                {
                    sender->setFocus(false);
                    handleMoveLogic(touchPoint);
                }
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

void UIListView::checkChildInfo(int handleState,UIWidget* sender,const CCPoint &touchPoint)
{
    /* gui mark */
//    Layout::checkChildInfo(handleState, sender, touchPoint);
    /**/
    interceptTouchEvent(handleState, sender, touchPoint);
}

void UIListView::moveChildren(float offset)
{
    switch (m_eDirection)
    {
        case LISTVIEW_DIR_VERTICAL: // vertical
        {
            ccArray* arrayChildren = m_children->data;
            int childrenCount = arrayChildren->num;
            for (int i = 0; i < childrenCount; i++)
            {
                UIWidget* child = (UIWidget*)(arrayChildren->arr[i]);
                moveChildPoint.x = child->getPosition().x;
                moveChildPoint.y = child->getPosition().y + offset;
                child->setPosition(moveChildPoint);
            }
            break;
        }
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
        {
            ccArray* arrayChildren = m_children->data;
            int childrenCount = arrayChildren->num;
            for (int i=0;i<childrenCount;i++)
            {
                UIWidget* child = (UIWidget*)(arrayChildren->arr[i]);
                moveChildPoint.x = child->getPosition().x + offset;
                moveChildPoint.y = child->getPosition().y;
                child->setPosition(moveChildPoint);
            }
            break;
        }
            
        default:
            break;
    }
}

bool UIListView::scrollChildren(float touchOffset)
{
    float realOffset = touchOffset;
    
    switch (m_eDirection)
    {
        case LISTVIEW_DIR_VERTICAL: // vertical            
            switch (m_eMoveDirection)
            {
                case LISTVIEW_MOVE_DIR_UP: // up
                    {
                        realOffset = MIN(realOffset, m_fDisBetweenChild);
                        
                        UIWidget* child_last = dynamic_cast<UIWidget*>(m_pChildPool->lastObject());
                        float child_last_bottom = child_last->getBottomInParent();
                        float scroll_bottom = m_fBottomBoundary;
                        
                        if (m_nEnd == m_nDataLength - 1)
                        {
                            if (realOffset > scroll_bottom + m_fDisBoundaryToChild_0 - child_last_bottom)
                            {
                                realOffset = scroll_bottom + m_fDisBoundaryToChild_0 - child_last_bottom;
                            }
                            moveChildren(realOffset);
                            return false;
                        }
                        moveChildren(realOffset);
                        
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
                    
                case LISTVIEW_MOVE_DIR_DOWN: // down
                    {
                        realOffset = MAX(realOffset, -m_fDisBetweenChild);
                        
                        UIWidget* child_0 = dynamic_cast<UIWidget*>(m_pChildPool->objectAtIndex(0));
                        float child_0_top = child_0->getTopInParent();
                        float scroll_top = m_fTopBoundary;
                        
                        if (m_nBegin == 0)
                        {
                            if (realOffset < scroll_top - m_fDisBoundaryToChild_0 - child_0_top)
                            {
                                realOffset = scroll_top - m_fDisBoundaryToChild_0 - child_0_top;
                            }
                            moveChildren(realOffset);
                            return false;
                        }
                        moveChildren(realOffset);
                                                
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
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
            switch (m_eMoveDirection)
            {
                case LISTVIEW_MOVE_DIR_LEFT: // left
                    {
                        realOffset = MAX(realOffset, -m_fDisBetweenChild);
                        
                        UIWidget* child_last = dynamic_cast<UIWidget*>(m_pChildPool->lastObject());
                        float child_last_right = child_last->getRightInParent();
                        float scroll_right = m_fRightBoundary;
                        
                        if (m_nEnd == m_nDataLength - 1)
                        {
                            if (realOffset < scroll_right - m_fDisBoundaryToChild_0 - child_last_right)
                            {
                                realOffset = scroll_right - m_fDisBoundaryToChild_0 - child_last_right;
                            }
                            moveChildren(realOffset);
                            return false;
                        }
                        moveChildren(realOffset);
                                                
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
                    
                case LISTVIEW_MOVE_DIR_RIGHT: // right
                    {
                        realOffset = MIN(realOffset, m_fDisBetweenChild);
                        
                        UIWidget* child_0 = dynamic_cast<UIWidget*>(m_pChildPool->objectAtIndex(0));
                        float child_0_left = child_0->getLeftInParent();
                        float scroll_left = m_fLeftBoundary;
                        
                        if (m_nBegin == 0)
                        {
                            if (realOffset > scroll_left + m_fDisBoundaryToChild_0 - child_0_left)
                            {
                                realOffset = scroll_left + m_fDisBoundaryToChild_0 - child_0_left;
                            }
                            moveChildren(realOffset);
                            return false;
                        }
                        moveChildren(realOffset);
                                                
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

void UIListView::autoScrollChildren(float dt)
{
    switch (m_eDirection)
    {
        case LISTVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
        {
            case LISTVIEW_MOVE_DIR_UP: // up
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
                }
            }
                break;
                
            case LISTVIEW_MOVE_DIR_DOWN: // down
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
                }
            }
                break;
                
            default:
                break;
        }
            break;
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
            switch (m_eMoveDirection)
        {
            case LISTVIEW_MOVE_DIR_LEFT: // left
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
                }
            }
                break;
                
            case LISTVIEW_MOVE_DIR_RIGHT: // right
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

float UIListView::getCurAutoScrollDistance(float time)
{
    float dt = time;
    m_fAutoScrollOriginalSpeed -= m_fAutoScrollAcceleration*dt;
    return m_fAutoScrollOriginalSpeed*dt;
}

void UIListView::startAutoScrollChildren(float v)
{
    m_fAutoScrollOriginalSpeed = v;
    m_bAutoScroll = true;
}

void UIListView::stopAutoScrollChildren()
{
    m_bAutoScroll = false;
    m_fAutoScrollOriginalSpeed = 0.0f;
}

void UIListView::recordSlidTime(float dt)
{
    if (m_bBePressed)
    {
        m_fSlidTime += dt;
    }
}

void UIListView::startRecordSlidAction()
{
    if (m_children->count() <= 0)
    {
        return;
    }
    if (m_bAutoScroll)
    {
        stopAutoScrollChildren();
    }
    m_bBePressed = true;
    m_fSlidTime = 0.0;
}

void UIListView::endRecordSlidAction()
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
    startAutoScrollChildren(orSpeed / 4);
    
    m_bBePressed = false;
    m_fSlidTime = 0.0;
}

UIWidget* UIListView::getCheckPositionChild()
{
    UIWidget* child = NULL;
    
    switch (m_eDirection)
    {
        case LISTVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {
                case LISTVIEW_MOVE_DIR_UP: // up
                    child = dynamic_cast<UIWidget*>(m_pChildPool->lastObject());
//                    child = m_pChildPool->rbegin();
                    break;
                    
                case LISTVIEW_MOVE_DIR_DOWN: // down
                    child = dynamic_cast<UIWidget*>(m_pChildPool->objectAtIndex(0));
//                    child = m_pChildPool->begin();
                    break;
                    
                default:
                    break;
            }
            break;
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
            switch (m_eMoveDirection)
            {
                case LISTVIEW_MOVE_DIR_LEFT: // left
                    child = dynamic_cast<UIWidget*>(m_pChildPool->lastObject());
//                    child = m_pChildPool->rbegin();
                    break;
                    
                case LISTVIEW_MOVE_DIR_RIGHT: // right
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
    /*
    UIWidget* child = m_pUpdatePool->rbegin();
    m_pUpdatePool->pop_back();
     */
    return child;
}

void UIListView::pushChildToPool()
{
    switch (m_eDirection)
    {
        case LISTVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {
                case LISTVIEW_MOVE_DIR_UP: // up
                    {
                        UIWidget* child = dynamic_cast<UIWidget*>(m_pChildPool->objectAtIndex(0));
                        m_pUpdatePool->insertObject(child, 0);
                        m_pChildPool->removeObjectAtIndex(0);
                        /*
                        UIWidget* child = m_pChildPool->begin();
                        m_pUpdatePool->push_front(child);
                        m_pChildPool->pop_front();
                         */
                    }
                    break;
                    
                case LISTVIEW_MOVE_DIR_DOWN: // down
                    {
                        UIWidget* child = dynamic_cast<UIWidget*>(m_pChildPool->lastObject());
                        m_pUpdatePool->insertObject(child, 0);
                        m_pChildPool->removeLastObject();
                        /*
                        UIWidget* child = m_pChildPool->rbegin();
                        m_pUpdatePool->push_front(child);
                        m_pChildPool->pop_back();
                         */
                    }
                    break;
                    
                default:
                    break;
            }
            break;
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
            switch (m_eMoveDirection)
            {
                case LISTVIEW_MOVE_DIR_LEFT: // left
                    {
                        UIWidget* child = dynamic_cast<UIWidget*>(m_pChildPool->objectAtIndex(0));
                        m_pUpdatePool->insertObject(child, 0);
                        m_pChildPool->removeObjectAtIndex(0);
                        /*
                        UIWidget* child = m_pChildPool->begin();
                        m_pUpdatePool->push_front(child);
                        m_pChildPool->pop_front();
                         */
                    }
                    break;
                    
                case LISTVIEW_MOVE_DIR_RIGHT: // right
                    {
                        UIWidget* child = dynamic_cast<UIWidget*>(m_pChildPool->lastObject());
                        m_pUpdatePool->insertObject(child, 0);
                        m_pChildPool->removeLastObject();
                        /*
                        UIWidget* child = m_pChildPool->rbegin();
                        m_pUpdatePool->push_front(child);
                        m_pChildPool->pop_back();
                         */
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
        case LISTVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {
                case LISTVIEW_MOVE_DIR_UP: // up
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
                    
                case LISTVIEW_MOVE_DIR_DOWN: // down
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
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
            switch (m_eMoveDirection)
            {
                case LISTVIEW_MOVE_DIR_LEFT: // left
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
                    
                case LISTVIEW_MOVE_DIR_RIGHT: // right
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
        case LISTVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {
                case LISTVIEW_MOVE_DIR_UP: // up
                    m_pChildPool->addObject(child);
//                    m_pChildPool->push_back(child);
                    break;
                    
                case LISTVIEW_MOVE_DIR_DOWN: // down
                    m_pChildPool->insertObject(child, 0);
//                    m_pChildPool->push_front(child);
                    break;
                    
                default:
                    break;
            }
            break;
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
            switch (m_eMoveDirection)
            {
                case LISTVIEW_MOVE_DIR_LEFT: // left
                    m_pChildPool->addObject(child);
//                    m_pChildPool->push_back(child);
                    break;
                    
                case LISTVIEW_MOVE_DIR_RIGHT: // right
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

void UIListView::clearCollectOverArray()
{
    switch (m_eDirection)
    {
        case LISTVIEW_DIR_VERTICAL:
            m_overTopArray->removeAllObjects();
            m_overBottomArray->removeAllObjects();
            break;
            
        case LISTVIEW_DIR_HORIZONTAL:
            m_overLeftArray->removeAllObjects();
            m_overRightArray->removeAllObjects();
            break;
            
        default:
            break;
    }
}

void UIListView::collectOverTopChild()
{
    float scroll_top = m_fTopBoundary;
    
    ccArray* arrayChildren = m_children->data;
    int times = arrayChildren->num;
    for (int i = 0; i < times; ++i)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
        float child_bottom = child->getBottomInParent();
        
        if (child_bottom >= scroll_top)
        {
            m_overTopArray->addObject(child);                
        }
    }
}

void UIListView::collectOverBottomChild()
{
    float scroll_bottom = m_fBottomBoundary;        
    
    ccArray* arrayChildren = m_children->data;
    int times = arrayChildren->num;
    for (int i = 0; i < times; ++i)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
        float child_top = child->getTopInParent();
        
        if (child_top <= scroll_bottom)
        {
            m_overBottomArray->addObject(child);                
        }
    }
}

void UIListView::collectOverLeftChild()
{
    float scroll_left = m_fLeftBoundary;        
    
    ccArray* arrayChildren = m_children->data;
    int times = arrayChildren->num;
    for (int i = 0; i < times; ++i)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
        float child_right = child->getRightInParent();
        
        if (child_right <= scroll_left)
        {
            m_overLeftArray->addObject(child);                
        }
    }
}

void UIListView::collectOverRightChild()
{
    float scroll_right = m_fRightBoundary;
    
    ccArray* arrayChildren = m_children->data;
    int times = arrayChildren->num;
    for (int i = 0; i < times; ++i)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
        float child_left = child->getLeftInParent();
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
        case LISTVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {
                case LISTVIEW_MOVE_DIR_UP: // up
                {
                    ccArray* arrayChildren = m_children->data;
                    int childrenCount = arrayChildren->num;
                    
                    if (m_overTopArray->count() == childrenCount)
                    {
                        int count = childrenCount;
                        for (int i = 0; i < count; ++i)
                        {   
                            UIWidget* child = dynamic_cast<UIWidget*>(m_overTopArray->objectAtIndex(i));
                            
                            if (i == 0)
                            {
                                float height = child->getSize().height;
                                float offset = (child->getWidgetType() == WidgetTypeWidget) ? height / 2 : height;
                                float y = m_fTopBoundary - m_fDisBoundaryToChild_0 - offset;
                                child->setPosition(ccp(child->getPosition().x, y));
                            }
                            else
                            {
                                UIWidget* prev_child = dynamic_cast<UIWidget*>(m_overTopArray->objectAtIndex(i - 1));
                                child->setPosition(ccp(child->getPosition().x, prev_child->getPosition().y - m_fDisBetweenChild));
                            }
                        }
                    }
                    else
                    {
                        float scroll_top = m_fTopBoundary;
                        
                        ccArray* arrayChildren = m_children->data;
                        int count = arrayChildren->num;
                        for (int i = 0; i < count; ++i)
                        {
                            UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
                            float child_bottom = child->getBottomInParent();
                            
                            if (child_bottom >= scroll_top)
                            {
                                int index = (i == 0) ? (count - 1) : (i - 1);
                                UIWidget* prev_child = dynamic_cast<UIWidget*>(arrayChildren->arr[index]);
                                child->setPosition(ccp(child->getPosition().x, prev_child->getPosition().y - m_fDisBetweenChild));
                            }
                        }
                    }
                }
                    break;
                    
                case LISTVIEW_MOVE_DIR_DOWN: // down
                {
                    ccArray* arrayChildren = m_children->data;
                    int childrenCount = arrayChildren->num;
                    
                    if (m_overBottomArray->count() == childrenCount)
                    {
                        int count = childrenCount;
                        for (int i = 0; i < count; ++i)
                        {
                            UIWidget* child = dynamic_cast<UIWidget*>(m_overBottomArray->objectAtIndex(i));
                            
                            if (i == 0)
                            {                                
                                float y = m_fBottomBoundary + m_fDisBoundaryToChild_0 - m_fDisBetweenChild;
                                child->setPosition(ccp(child->getPosition().x, y));
                            }
                            else
                            {
                                UIWidget* prev_child = dynamic_cast<UIWidget*>(m_overBottomArray->objectAtIndex(i - 1));
                                child->setPosition(ccp(child->getPosition().x, prev_child->getPosition().y + m_fDisBetweenChild));                                    
                            }
                        }
                    }
                    else
                    {
                        float scroll_bottom = m_fBottomBoundary;
                        
                        ccArray* arrayChildren = m_children->data;
                        int count = arrayChildren->num;
                        for (int i = count - 1; i >= 0; --i)
                        {
                            UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
                            float child_top = child->getTopInParent();
                            
                            if (child_top <= scroll_bottom)
                            {
                                int index = (i == count - 1) ? 0 : (i + 1);
                                UIWidget* next_child = dynamic_cast<UIWidget*>(arrayChildren->arr[index]);
                                child->setPosition(ccp(child->getPosition().x, next_child->getPosition().y + m_fDisBetweenChild));                                    
                            }
                        }
                    }
                }
                    break;
                    
                default:
                    break;
            }
            break;
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
            switch (m_eMoveDirection)
            {
                case LISTVIEW_MOVE_DIR_LEFT: // left
                {
                    ccArray* arrayChildren = m_children->data;
                    int childrenCount = arrayChildren->num;
                    
                    if (m_overLeftArray->count() == childrenCount)
                    {
                        int count = childrenCount;
                        for (int i = 0; i < count; ++i)
                        {
                            UIWidget* child = dynamic_cast<UIWidget*>(m_overLeftArray->objectAtIndex(i));
                            
                            if (i == 0)
                            {
                                float width = child->getSize().width;
                                float offset = (child->getWidgetType() == WidgetTypeWidget) ? (width / 2) : 0;                                
                                float x = m_fLeftBoundary + m_fDisBoundaryToChild_0 + width + offset;
                                child->setPosition(ccp(x, child->getPosition().y));
                            }
                            else
                            {
                                UIWidget* prev_child = dynamic_cast<UIWidget*>(m_overLeftArray->objectAtIndex(i - 1));
                                child->setPosition(ccp(prev_child->getPosition().x + m_fDisBetweenChild, child->getPosition().y));                                    
                            }
                        }
                    }
                    else
                    {
                        float scroll_left = m_fLeftBoundary;
                        
                        ccArray* arrayChildren = m_children->data;
                        int count = arrayChildren->num;
                        for (int i = 0; i < count; ++i)
                        {
                            UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
                            float child_right = child->getRightInParent();
                            
                            if (child_right <= scroll_left)
                            {
                                int index = (i == 0) ? (count - 1) : (i - 1);
                                UIWidget* prev_child = dynamic_cast<UIWidget*>(arrayChildren->arr[index]);
                                child->setPosition(ccp(prev_child->getPosition().x + m_fDisBetweenChild, child->getPosition().y));
                            }
                        }
                    }
                }
                    break;
                    
                case LISTVIEW_MOVE_DIR_RIGHT: // right
                {
                    ccArray* arrayChildren = m_children->data;
                    int childrenCount = arrayChildren->num;
                    
                    if (m_overRightArray->count() == childrenCount)
                    {
                        int count = childrenCount;
                        for (int i = 0; i < count; ++i)
                        {
                            UIWidget* child = dynamic_cast<UIWidget*>(m_overRightArray->objectAtIndex(i));
                            
                            if (i == 0)
                            {
                                float x = m_fRightBoundary - m_fDisBoundaryToChild_0 + m_fDisBetweenChild;
                                child->setPosition(ccp(x, child->getPosition().y));
                            }
                            else
                            {
                                UIWidget* prev_child = dynamic_cast<UIWidget*>(m_overRightArray->objectAtIndex(i - 1));
                                child->setPosition(ccp(prev_child->getPosition().x - m_fDisBetweenChild, child->getPosition().y));                                                                
                            }
                        }
                    }
                    else
                    {
                        float scroll_right = m_fRightBoundary;
                        
                        ccArray* arrayChildren = m_children->data;
                        int count = arrayChildren->num;
                        for (int i = count - 1; i >= 0; --i)
                        {
                            UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
                            float child_left = child->getLeftInParent();
                            
                            if (child_left >= scroll_right)
                            {
                                int index = (i == count - 1) ? 0 : (i + 1);
                                UIWidget* next_child = dynamic_cast<UIWidget*>(arrayChildren->arr[index]);
                                child->setPosition(ccp(next_child->getPosition().x - m_fDisBetweenChild, child->getPosition().y));
                            }
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
        case LISTVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {
                case LISTVIEW_MOVE_DIR_UP: // up
                    {
                        int count = m_overTopArray->count();
                        for (int i = 0; i < count; ++i)
                        {
                            pushChildToPool();
                            getAndCallback();
                        }
                    }
                    break;
                    
                case LISTVIEW_MOVE_DIR_DOWN: // down
                    {
                        int count = m_overBottomArray->count();
                        for (int i = 0; i < count; ++i)
                        {
                            pushChildToPool();
                            getAndCallback();
                        }
                    }
                    break;
                    
                default:
                    break;
            }
            break;
            
        case LISTVIEW_DIR_HORIZONTAL: // horizontal
            switch (m_eMoveDirection)
            {
                case LISTVIEW_MOVE_DIR_LEFT: // left
                    {
                        int count = m_overLeftArray->count();
                        for (int i = 0; i < count; ++i)
                        {
                            pushChildToPool();
                            getAndCallback();
                        }
                    }
                    break;
                    
                case LISTVIEW_MOVE_DIR_RIGHT: // right
                    {
                        int count = m_overRightArray->count();
                        for (int i = 0; i < count; ++i)
                        {
                            pushChildToPool();
                            getAndCallback();
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

/* gui mark */
//float UIListView::getScrollDegreeRange() const
//{
//    return m_fScrollDegreeRange;
//}
//
//void UIListView::setScrollDegreeRange(float range)
//{
//    m_fScrollDegreeRange = range;
//}
//
//bool UIListView::isInScrollDegreeRange(UIWidget* widget)
//{
//    CCPoint vector = ccpSub(widget->getTouchMovePos(), widget->getTouchStartPos());
//    float radians = ccpToAngle(vector);
//    float degrees = CC_RADIANS_TO_DEGREES(radians);
//    
//    float compare = m_fScrollDegreeRange / 2;
//    
//    switch (m_eDirection)
//    {
//        case LISTVIEW_DIR_VERTICAL:
//            if ((degrees >= 90 - compare && degrees <= 90 + compare)
//                || (degrees >= -90 - compare && degrees <= -90 + compare))
//            {
//                return true;
//            }
//            break;
//            
//        case LISTVIEW_DIR_HORIZONTAL:
//            if ((degrees >= -compare && degrees <= compare)
//                || (degrees >= -179.99 && degrees <= -179.99 + compare)
//                || (degrees >= 180 - compare && degrees <= 180))
//            {
//                return true;
//            }
//            break;
//            
//        default:
//            break;
//    }
//    
//    return false;
//}
/**/

NS_CC_EXT_END