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
m_nMoveDirection(0),
m_bTopEnd(false),
m_bBottomEnd(false),
m_bLeftEnd(false),
m_bRightEnd(false),
m_bAutoScroll(false),
m_fAutoScrollOriginalSpeed(0.0f),
m_fAutoScrollAcceleration(600.0f),
m_bBePressed(false),
m_fSlidTime(0.0f),
m_fChildFocusCancelOffset(5.0f),
m_pScrollToTopListener(NULL),
m_pfnScrollToTopSelector(NULL),
m_pScrollToBottomListener(NULL),
m_pfnScrollToBottomSelector(NULL),
m_pScrollToLeftListener(NULL),
m_pfnScrollToLeftSelector(NULL),
m_pScrollToRightListener(NULL),
m_pfnScrollToRightSelector(NULL),
m_pInnerContainer(NULL),
m_fScrollDegreeRange(45.0f)
{
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

void UIScrollView::releaseResoures()
{
    Layout::releaseResoures();
    m_pInnerContainer->structureChangedEvent();
    m_pInnerContainer->releaseResoures();
    m_pInnerContainer->setParent(NULL);
    delete m_pInnerContainer;
    m_pInnerContainer = NULL;
}

bool UIScrollView::init()
{
    if (Layout::init())
    {
        setUpdateEnabled(true);
        setTouchEnabled(true);
        setClippingEnabled(true);
        m_pInnerContainer->setTouchEnabled(false);
        return true;
    }
    return false;
}

void UIScrollView::initRenderer()
{
    Layout::initRenderer();
    m_pInnerContainer = Layout::create();
    Layout::addChild(m_pInnerContainer);
}

void UIScrollView::onSizeChanged()
{
    Layout::onSizeChanged();
    m_fTopBoundary = m_size.height;
    m_fRightBoundary = m_size.width;
    CCSize innerSize = m_pInnerContainer->getSize();
    float orginInnerSizeWidth = innerSize.width;
    float orginInnerSizeHeight = innerSize.height;
    float innerSizeWidth = MAX(orginInnerSizeWidth, m_size.width);
    float innerSizeHeight = MAX(orginInnerSizeHeight, m_size.height);
    m_pInnerContainer->setSize(CCSizeMake(innerSizeWidth, innerSizeHeight));
    m_pInnerContainer->setPosition(ccp(0, m_size.height - m_pInnerContainer->getSize().height));
}

void UIScrollView::setInnerContainerSize(const cocos2d::CCSize &size)
{
    float innerSizeWidth = m_size.width;
    float innerSizeHeight = m_size.height;
    if (size.width < m_size.width)
    {
        CCLOG("Inner width <= scrollview width, it will be force sized!");
    }
    else
    {
        innerSizeWidth = size.width;
    }
    if (size.height < m_size.height)
    {
        CCLOG("Inner height <= scrollview height, it will be force sized!");
    }
    else
    {
        innerSizeHeight = size.height;
    }
    m_pInnerContainer->setSize(CCSizeMake(innerSizeWidth, innerSizeHeight));
    m_pInnerContainer->setPosition(ccp(0, m_size.height - m_pInnerContainer->getSize().height));
}

const CCSize& UIScrollView::getInnerContainerSize() const
{
	return m_pInnerContainer->getSize();
}

bool UIScrollView::addChild(UIWidget* widget)
{
    return m_pInnerContainer->addChild(widget);
}

void UIScrollView::removeAllChildrenAndCleanUp(bool cleanup)
{
    m_pInnerContainer->removeAllChildrenAndCleanUp(cleanup);
}

bool UIScrollView::removeChild(UIWidget* child,bool cleanup)
{
	return m_pInnerContainer->removeChild(child, cleanup);
}

CCArray* UIScrollView::getChildren()
{
    return m_pInnerContainer->getChildren();
}

void UIScrollView::moveChildren(float offset)
{
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
        {
            moveChildPoint.x = m_pInnerContainer->getPosition().x;
            moveChildPoint.y = m_pInnerContainer->getPosition().y + offset;
            m_pInnerContainer->setPosition(moveChildPoint);
            break;
        }
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
        {
            moveChildPoint.x = m_pInnerContainer->getPosition().x + offset;
            moveChildPoint.y = m_pInnerContainer->getPosition().y;
            m_pInnerContainer->setPosition(moveChildPoint);
            break;
        }
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
    m_fAutoScrollOriginalSpeed = 0.0f;
}

float UIScrollView::getCurAutoScrollDistance(float time)
{
    float dt = time;
    m_fAutoScrollOriginalSpeed -= m_fAutoScrollAcceleration*dt;
    return m_fAutoScrollOriginalSpeed*dt;
}

bool UIScrollView::scrollChildren(float touchOffset)
{    
    float realOffset = touchOffset;
    
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            switch (m_eMoveDirection)
            {                        
                case SCROLLVIEW_MOVE_DIR_UP: // up
                {
                    float icBottomPos = m_pInnerContainer->getBottomInParent();
                    if (icBottomPos + touchOffset >= m_fBottomBoundary)
                    {
                        realOffset = m_fBottomBoundary - icBottomPos;
                        moveChildren(realOffset);
                        m_bBottomEnd = true;
                        scrollToBottomEvent();
                        return false;
                    }
                    break;
                }
                case SCROLLVIEW_MOVE_DIR_DOWN: // down
                {
                    float icTopPos = m_pInnerContainer->getTopInParent();
                    if (icTopPos + touchOffset <= m_fTopBoundary)
                    {
                        realOffset = m_fTopBoundary - icTopPos;
                        moveChildren(realOffset);
                        m_bTopEnd = true;
                        scrollToTopEvent();
                        return false;
                    }
                    break;
                }
                default:
                    break;
            }
            moveChildren(realOffset);
            m_bTopEnd = false;
            m_bBottomEnd = false;
            return true;
            break;
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            switch (m_eMoveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_LEFT: // left
                {
                    float icRightPos = m_pInnerContainer->getRightInParent();
                    if (icRightPos + touchOffset <= m_fRightBoundary)
                    {
                        realOffset = m_fRightBoundary - icRightPos;
                        moveChildren(realOffset);
                        m_bRightEnd = true;
                        scrollToRightEvent();
                        return false;
                    }
                    break;
                }
                case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                {
                    float icLeftPos = m_pInnerContainer->getLeftInParent();
                    if (icLeftPos + touchOffset >= m_fLeftBoundary)
                    {
                        realOffset = m_fLeftBoundary - icLeftPos;
                        moveChildren(realOffset);
                        m_bLeftEnd = true;
                        scrollToLeftEvent();
                        return false;
                    }
                    break;
                }
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
    scrollChildren(m_pInnerContainer->getSize().height);
}

void UIScrollView::scrollToTop()
{
    m_eMoveDirection = SCROLLVIEW_MOVE_DIR_DOWN; // down
    scrollChildren(-m_pInnerContainer->getSize().height);
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

void UIScrollView::handlePressLogic(const CCPoint &touchPoint)
{        
    CCPoint nsp = m_pRenderer->convertToNodeSpace(touchPoint);
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

void UIScrollView::handleMoveLogic(const CCPoint &touchPoint)
{
    CCPoint nsp = m_pRenderer->convertToNodeSpace(touchPoint);
    float offset = 0.0f;
    
    switch (m_eDirection)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            {
                float moveY = nsp.y;
                offset = moveY - m_fTouchMoveStartLocation;
                m_fTouchMoveStartLocation = moveY;
                
                if (offset < 0.0f)
                {
                    m_eMoveDirection = SCROLLVIEW_MOVE_DIR_DOWN; // down
                }
                else if (offset > 0.0f)
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
    scrollChildren(offset);
}

void UIScrollView::handleReleaseLogic(const CCPoint &touchPoint)
{
    CCPoint nsp = m_pRenderer->convertToNodeSpace(touchPoint);
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

bool UIScrollView::onTouchBegan(const CCPoint &touchPoint)
{
    bool pass = Layout::onTouchBegan(touchPoint);
    handlePressLogic(touchPoint);
    return pass;
}

void UIScrollView::onTouchMoved(const CCPoint &touchPoint)
{
    Layout::onTouchMoved(touchPoint);
    //temp mark
//    if (isInScrollDegreeRange(this))
    {
        handleMoveLogic(touchPoint);
    }
}

void UIScrollView::onTouchEnded(const CCPoint &touchPoint)
{
    Layout::onTouchEnded(touchPoint);
    handleReleaseLogic(touchPoint);
}

void UIScrollView::onTouchCancelled(const CCPoint &touchPoint)
{
    Layout::onTouchCancelled(touchPoint);
}

void UIScrollView::onTouchLongClicked(const CCPoint &touchPoint)
{
    
}

void UIScrollView::update(float dt)
{
    if (m_bAutoScroll)
    {
        autoScrollChildren(dt);
    }
    recordSlidTime(dt);
}

void UIScrollView::recordSlidTime(float dt)
{
    if (m_bBePressed)
    {
        m_fSlidTime += dt;
    }
}

void UIScrollView::interceptTouchEvent(int handleState, UIWidget *sender, const CCPoint &touchPoint)
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
                
                //temp mark
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

void UIScrollView::checkChildInfo(int handleState,UIWidget* sender,const CCPoint &touchPoint)
{
    interceptTouchEvent(handleState, sender, touchPoint);
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

void UIScrollView::addScrollToTopEvent(CCObject *target, SEL_ScrollToTopEvent selector)
{
    m_pScrollToTopListener = target;
    m_pfnScrollToTopSelector = selector;
}

void UIScrollView::addScrollToBottomEvent(CCObject *target, SEL_ScrollToBottomEvent selector)
{
    m_pScrollToBottomListener = target;
    m_pfnScrollToBottomSelector = selector;
}

void UIScrollView::addScrollToLeftEvent(CCObject *target, SEL_ScrollToLeftEvent selector)
{
    m_pScrollToLeftListener = target;
    m_pfnScrollToLeftSelector = selector;
}

void UIScrollView::addScrollToRightEvent(CCObject *target, SEL_ScrollToRightEvent selector)
{
    m_pScrollToRightListener = target;
    m_pfnScrollToRightSelector = selector;
}

void UIScrollView::setDirection(SCROLLVIEW_DIR dir)
{
    m_eDirection = dir;
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

Layout* UIScrollView::getInnerContainer()
{
    return m_pInnerContainer;
}

void UIScrollView::setLayoutExecutant(LayoutExecutant *exe)
{
    m_pInnerContainer->setLayoutExecutant(exe);
}

LayoutExecutant* UIScrollView::getLayoutExecutant() const
{
    return m_pInnerContainer->getLayoutExecutant();
}

//float UIScrollView::getScrollDegreeRange() const
//{
//    return m_fScrollDegreeRange;
//}
//
//void UIScrollView::setScrollDegreeRange(float range)
//{
//    m_fScrollDegreeRange = range;
//}

//bool UIScrollView::isInScrollDegreeRange(UIWidget* widget)
//{
//    CCPoint vector = ccpSub(widget->getTouchMovePos(), widget->getTouchStartPos());
//    float radians = ccpToAngle(vector);
//    float degrees = CC_RADIANS_TO_DEGREES(radians);
//    
//    float compare = m_fScrollDegreeRange / 2.0f;
//    
//    switch (m_eDirection)
//    {
//        case SCROLLVIEW_DIR_VERTICAL:
//            if ((degrees >= 90.0f - compare && degrees <= 90.0f + compare)
//                || (degrees >= -90.0f - compare && degrees <= -90.0f + compare))
//            {
//                return true;
//            }
//            break;
//            
//        case SCROLLVIEW_DIR_HORIZONTAL:
//            if ((degrees >= -compare && degrees <= compare)
//                || (degrees >= -179.99f && degrees <= -179.99f + compare)
//                || (degrees >= 180.0f - compare && degrees <= 180.0f))
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

NS_CC_EXT_END