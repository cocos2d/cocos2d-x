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
#include "../../System/UILayer.h"

NS_CC_EXT_BEGIN

UIScrollView::UIScrollView():
_innerContainer(NULL),
_direction(SCROLLVIEW_DIR_VERTICAL),
_moveDirection(SCROLLVIEW_MOVE_DIR_NONE),
_touchStartLocation(0.0f),
_touchEndLocation(0.0f),
_touchMoveStartLocation(0.0f),
_topBoundary(0.0f),
_bottomBoundary(0.0f),
_leftBoundary(0.0f),
_rightBoundary(0.0f),
_topEnd(false),
_bottomEnd(false),
_leftEnd(false),
_rightEnd(false),
_autoScroll(false),
_autoScrollOriginalSpeed(0.0f),
_autoScrollAcceleration(600.0f),
_bePressed(false),
_slidTime(0.0f),
_moveChildPoint(Point::ZERO),
_childFocusCancelOffset(5.0f),
_eventListener(NULL),
_eventSelector(NULL)
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
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

void UIScrollView::releaseResoures()
{
    setUpdateEnabled(false);
    removeAllChildren();
    _renderer->removeAllChildrenWithCleanup(true);
    _renderer->removeFromParentAndCleanup(true);
    _renderer->release();
    
    Layout::removeChild(_innerContainer);

    _children->release();
}

bool UIScrollView::init()
{
    if (Layout::init())
    {
        setUpdateEnabled(true);
        setTouchEnabled(true);
        setClippingEnabled(true);
        _innerContainer->setTouchEnabled(false);
        return true;
    }
    return false;
}

void UIScrollView::initRenderer()
{
    Layout::initRenderer();
    _innerContainer = Layout::create();
    Layout::addChild(_innerContainer);
}

void UIScrollView::onSizeChanged()
{
    Layout::onSizeChanged();
    _topBoundary = _size.height;
    _rightBoundary = _size.width;
    Size innerSize = _innerContainer->getSize();
    float orginInnerSizeWidth = innerSize.width;
    float orginInnerSizeHeight = innerSize.height;
    float innerSizeWidth = MAX(orginInnerSizeWidth, _size.width);
    float innerSizeHeight = MAX(orginInnerSizeHeight, _size.height);
    _innerContainer->setSize(Size(innerSizeWidth, innerSizeHeight));
    _innerContainer->setPosition(Point(0, _size.height - _innerContainer->getSize().height));
}

void UIScrollView::setInnerContainerSize(const Size &size)
{
    float innerSizeWidth = _size.width;
    float innerSizeHeight = _size.height;
    if (size.width < _size.width)
    {
        CCLOG("Inner width <= scrollview width, it will be force sized!");
    }
    else
    {
        innerSizeWidth = size.width;
    }
    if (size.height < _size.height)
    {
        CCLOG("Inner height <= scrollview height, it will be force sized!");
    }
    else
    {
        innerSizeHeight = size.height;
    }
    _innerContainer->setSize(Size(innerSizeWidth, innerSizeHeight));
    _innerContainer->setPosition(Point(0, _size.height - _innerContainer->getSize().height));
}

const Size& UIScrollView::getInnerContainerSize() const
{
	return _innerContainer->getSize();
}

bool UIScrollView::addChild(UIWidget* widget)
{
    return _innerContainer->addChild(widget);
}

void UIScrollView::removeAllChildren()
{
    _innerContainer->removeAllChildren();
}

bool UIScrollView::removeChild(UIWidget* child)
{
	return _innerContainer->removeChild(child);
}

Array* UIScrollView::getChildren()
{
    return _innerContainer->getChildren();
}

void UIScrollView::moveChildren(float offset)
{
    switch (_direction)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
        {
            _moveChildPoint.x = _innerContainer->getPosition().x;
            _moveChildPoint.y = _innerContainer->getPosition().y + offset;
            _innerContainer->setPosition(_moveChildPoint);
            break;
        }
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
        {
            _moveChildPoint.x = _innerContainer->getPosition().x + offset;
            _moveChildPoint.y = _innerContainer->getPosition().y;
            _innerContainer->setPosition(_moveChildPoint);
            break;
        }
        default:
            break;
    }
}

void UIScrollView::autoScrollChildren(float dt)
{
    switch (_direction)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            switch (_moveDirection)
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
            switch (_moveDirection)
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
    _autoScrollOriginalSpeed = v;
    _autoScroll = true;
}

void UIScrollView::stopAutoScrollChildren()
{
    _autoScroll = false;
    _autoScrollOriginalSpeed = 0.0f;
}

float UIScrollView::getCurAutoScrollDistance(float time)
{
    float dt = time;
    _autoScrollOriginalSpeed -= _autoScrollAcceleration*dt;
    return _autoScrollOriginalSpeed*dt;
}

bool UIScrollView::scrollChildren(float touchOffset)
{    
    float realOffset = touchOffset;
    
    switch (_direction)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            switch (_moveDirection)
            {                        
                case SCROLLVIEW_MOVE_DIR_UP: // up
                {
                    float icBottomPos = _innerContainer->getBottomInParent();
                    if (icBottomPos + touchOffset >= _bottomBoundary)
                    {
                        realOffset = _bottomBoundary - icBottomPos;
                        moveChildren(realOffset);
                        _bottomEnd = true;
                        scrollToBottomEvent();
                        return false;
                    }
                    break;
                }
                case SCROLLVIEW_MOVE_DIR_DOWN: // down
                {
                    float icTopPos = _innerContainer->getTopInParent();
                    if (icTopPos + touchOffset <= _topBoundary)
                    {
                        realOffset = _topBoundary - icTopPos;
                        moveChildren(realOffset);
                        _topEnd = true;
                        scrollToTopEvent();
                        return false;
                    }
                    break;
                }
                default:
                    break;
            }
            moveChildren(realOffset);
            _topEnd = false;
            _bottomEnd = false;
            return true;
            break;
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            switch (_moveDirection)
            {
                case SCROLLVIEW_MOVE_DIR_LEFT: // left
                {
                    float icRightPos = _innerContainer->getRightInParent();
                    if (icRightPos + touchOffset <= _rightBoundary)
                    {
                        realOffset = _rightBoundary - icRightPos;
                        moveChildren(realOffset);
                        _rightEnd = true;
                        scrollToRightEvent();
                        return false;
                    }
                    break;
                }
                case SCROLLVIEW_MOVE_DIR_RIGHT: // right
                {
                    float icLeftPos = _innerContainer->getLeftInParent();
                    if (icLeftPos + touchOffset >= _leftBoundary)
                    {
                        realOffset = _leftBoundary - icLeftPos;
                        moveChildren(realOffset);
                        _leftEnd = true;
                        scrollToLeftEvent();
                        return false;
                    }
                    break;
                }
                default:
                    break;
            }
            moveChildren(realOffset);
            _leftEnd = false;
            _rightEnd = false;
            return true;
            break;
            
        default:
            break;
    }
    
    return false;
}

void UIScrollView::scrollToBottom()
{
    _moveDirection = SCROLLVIEW_MOVE_DIR_UP; // up
    scrollChildren(_innerContainer->getSize().height);
}

void UIScrollView::scrollToTop()
{
    _moveDirection = SCROLLVIEW_MOVE_DIR_DOWN; // down
    scrollChildren(-_innerContainer->getSize().height);
}

void UIScrollView::startRecordSlidAction()
{
    if (_children->count() <= 0)
    {
        return;
    }
    if (_autoScroll){
        stopAutoScrollChildren();
    }
    _bePressed = true;
    _slidTime = 0.0;
}

void UIScrollView::endRecordSlidAction()
{
    if (_children->count() <= 0)
    {
        return;
    }
    if (_slidTime <= 0.016f)
    {
        return;
    }
    float totalDis = 0;
    totalDis = _touchEndLocation-_touchStartLocation;
    float orSpeed = fabs(totalDis)/(_slidTime);
    startAutoScrollChildren(orSpeed);
    
    _bePressed = false;
    _slidTime = 0.0;
}

void UIScrollView::handlePressLogic(const Point &touchPoint)
{        
    Point nsp = _renderer->convertToNodeSpace(touchPoint);
    switch (_direction)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            _touchMoveStartLocation = nsp.y;
            _touchStartLocation = nsp.y;
            break;
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            _touchMoveStartLocation = nsp.x;
            _touchStartLocation = nsp.x;
            break;
        default:
            break;
    }
    startRecordSlidAction();
}

void UIScrollView::handleMoveLogic(const Point &touchPoint)
{
    Point nsp = _renderer->convertToNodeSpace(touchPoint);
    float offset = 0.0f;
    
    switch (_direction)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            {
                float moveY = nsp.y;
                offset = moveY - _touchMoveStartLocation;
                _touchMoveStartLocation = moveY;
                
                if (offset < 0.0f)
                {
                    _moveDirection = SCROLLVIEW_MOVE_DIR_DOWN; // down
                }
                else if (offset > 0.0f)
                {
                    _moveDirection = SCROLLVIEW_MOVE_DIR_UP; // up
                }
            }
            break;
            
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            {
                float moveX = nsp.x;
                offset = moveX - _touchMoveStartLocation;
                _touchMoveStartLocation = moveX;
                
                if (offset < 0)
                {
                    _moveDirection = SCROLLVIEW_MOVE_DIR_LEFT; // left
                }
                else if (offset > 0)
                {
                    _moveDirection = SCROLLVIEW_MOVE_DIR_RIGHT; // right
                }
            }
            break;
            
        default:
            break;
    }
    scrollChildren(offset);
}

void UIScrollView::handleReleaseLogic(const Point &touchPoint)
{
    Point nsp = _renderer->convertToNodeSpace(touchPoint);
    switch (_direction)
    {
        case SCROLLVIEW_DIR_VERTICAL: // vertical
            _touchEndLocation = nsp.y;
            break;
            
        case SCROLLVIEW_DIR_HORIZONTAL: // horizontal
            _touchEndLocation = nsp.x;
            break;
            
        default:
            break;
    }
    endRecordSlidAction();
}    

bool UIScrollView::onTouchBegan(const Point &touchPoint)
{
    bool pass = Layout::onTouchBegan(touchPoint);
    handlePressLogic(touchPoint);
    return pass;
}

void UIScrollView::onTouchMoved(const Point &touchPoint)
{
    Layout::onTouchMoved(touchPoint);
    handleMoveLogic(touchPoint);
}

void UIScrollView::onTouchEnded(const Point &touchPoint)
{
    Layout::onTouchEnded(touchPoint);
    handleReleaseLogic(touchPoint);
}

void UIScrollView::onTouchCancelled(const Point &touchPoint)
{
    Layout::onTouchCancelled(touchPoint);
}

void UIScrollView::onTouchLongClicked(const Point &touchPoint)
{
    
}

void UIScrollView::update(float dt)
{
    if (_autoScroll)
    {
        autoScrollChildren(dt);
    }
    recordSlidTime(dt);
}

void UIScrollView::recordSlidTime(float dt)
{
    if (_bePressed)
    {
        _slidTime += dt;
    }
}

void UIScrollView::interceptTouchEvent(int handleState, UIWidget *sender, const Point &touchPoint)
{
    switch (handleState)
    {
        case 0:
            handlePressLogic(touchPoint);
            break;
            
        case 1:
        {
            float offset = 0;
            switch (_direction)
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
            if (offset > _childFocusCancelOffset)
            {
                sender->setFocused(false);
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

void UIScrollView::checkChildInfo(int handleState,UIWidget* sender,const Point &touchPoint)
{
    interceptTouchEvent(handleState, sender, touchPoint);
}

void UIScrollView::scrollToTopEvent()
{
    if (_eventListener && _eventSelector)
    {
        (_eventListener->*_eventSelector)(this, SCROLLVIEW_EVENT_SCROLL_TO_TOP);
    }
}

void UIScrollView::scrollToBottomEvent()
{
    if (_eventListener && _eventSelector)
    {
        (_eventListener->*_eventSelector)(this, SCROLLVIEW_EVENT_SCROLL_TO_BOTTOM);
    }
}

void UIScrollView::scrollToLeftEvent()
{
    if (_eventListener && _eventSelector)
    {
        (_eventListener->*_eventSelector)(this, SCROLLVIEW_EVENT_SCROLL_TO_LEFT);
    }
}

void UIScrollView::scrollToRightEvent()
{
    if (_eventListener && _eventSelector)
    {
        (_eventListener->*_eventSelector)(this, SCROLLVIEW_EVENT_SCROLL_TO_RIGHT);
    }
}

void UIScrollView::addEventListener(Object *target, SEL_ScrollViewEvent selector)
{
    _eventListener = target;
    _eventSelector = selector;
}

void UIScrollView::setDirection(SCROLLVIEW_DIR dir)
{
    _direction = dir;
}

SCROLLVIEW_DIR UIScrollView::getDirection()
{
    return _direction;
}

void UIScrollView::setMoveDirection(SCROLLVIEW_MOVE_DIR dir)
{
    _moveDirection = dir;
}

SCROLLVIEW_MOVE_DIR UIScrollView::getMoveDirection()
{
    return _moveDirection;
}

Layout* UIScrollView::getInnerContainer()
{
    return _innerContainer;
}

void UIScrollView::setLayoutExecutant(LayoutExecutant *exe)
{
    _innerContainer->setLayoutExecutant(exe);
}

LayoutExecutant* UIScrollView::getLayoutExecutant() const
{
    return _innerContainer->getLayoutExecutant();
}

const char* UIScrollView::getDescription() const
{
    return "ScrollView";
}

NS_CC_EXT_END