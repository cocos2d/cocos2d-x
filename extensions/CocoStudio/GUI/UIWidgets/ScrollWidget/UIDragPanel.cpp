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

#include "UIDragPanel.h"
#include "../../System/UILayer.h"

NS_CC_EXT_BEGIN

UIDragPanel::UIDragPanel()
: _innerContainer(NULL)
, _touchPressed(false)
, _touchMoved(false)
, _touchReleased(false)
, _touchCanceld(false)
, _touchStartNodeSpace(Point::ZERO)
, _touchStartWorldSpace(Point::ZERO)
, _touchEndWorldSpace(Point::ZERO)
, _slidTime(0.0f)
, _moveType(DRAGPANEL_MOVE_TYPE_AUTOMOVE)
, _autoMoveDuration(0.5f)
, _autoMoveEaseRate(2.0f)
, _eventLister(NULL)
, _eventSelector(NULL)
, _berthDirection(DRAGPANEL_BERTH_DIR_NONE)
, _bounceEnable(false)
, _bounceDirection(DRAGPANEL_BOUNCE_DIR_NONE)
, _bounceDuration(0.5f)
, _bounceEaseRate(2.0f)
, _runningAction(false)
, _actionType(0)
, _actionWidget(NULL)
, _duration(0.0f)
, _elapsed(0.0f)
, _firstTick(false)
, _positionDelta(Point::ZERO)
, _startPosition(Point::ZERO)
, _previousPosition(Point::ZERO)
, _endPosition(Point::ZERO)
{
    
}

UIDragPanel::~UIDragPanel()
{
    
}

UIDragPanel* UIDragPanel::create()
{
    UIDragPanel* widget = new UIDragPanel();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UIDragPanel::init()
{
    if (Layout::init())
    {
        setUpdateEnabled(true);
        setTouchEnabled(true);
        setClippingEnabled(true);
        return true;
    }
    return false;
}

void UIDragPanel::initRenderer()
{
    Layout::initRenderer();
    
    _innerContainer = Layout::create();
    Layout::addChild(_innerContainer);

}

void UIDragPanel::releaseResoures()
{
    setUpdateEnabled(false);
    removeAllChildren();
    _renderer->removeAllChildrenWithCleanup(true);
    _renderer->removeFromParentAndCleanup(true);
    _renderer->release();
    
    Layout::removeChild(_innerContainer);
    
    _children->release();
}

bool UIDragPanel::onTouchBegan(const Point &touchPoint)
{
    bool pass = Layout::onTouchBegan(touchPoint);
    handlePressLogic(touchPoint);
    return pass;
}

void UIDragPanel::onTouchMoved(const Point &touchPoint)
{
    Layout::onTouchMoved(touchPoint);
    handleMoveLogic(touchPoint);
}

void UIDragPanel::onTouchEnded(const Point &touchPoint)
{
    Layout::onTouchEnded(touchPoint);
    handleReleaseLogic(touchPoint);
}

void UIDragPanel::onTouchCancelled(const Point &touchPoint)
{
    Layout::onTouchCancelled(touchPoint);
}

void UIDragPanel::onTouchLongClicked(const Point &touchPoint)
{
    
}

void UIDragPanel::update(float dt)
{
    // widget action
    if (_runningAction)
    {
        if (actionIsDone())
        {
            actionDone();
            actionStop();
        }
        else
        {
            actionStep(dt);
        }
    }
    
    recordSlidTime(dt);
}

bool UIDragPanel::addChild(UIWidget *widget)
{
    _innerContainer->addChild(widget);
    return true;
}

bool UIDragPanel::removeChild(UIWidget *child)
{
    bool value = false;
    if (_innerContainer->removeChild(child))
    {
        value = true;
    }
    
    return value;
}

void UIDragPanel::removeAllChildren()
{
    _innerContainer->removeAllChildren();
}

Array* UIDragPanel::getChildren()
{
    return _innerContainer->getChildren();
}

void UIDragPanel::onSizeChanged()
{
    Layout::onSizeChanged();
    Size innerSize = _innerContainer->getSize();
    float orginInnerSizeWidth = innerSize.width;
    float orginInnerSizeHeight = innerSize.height;
    float innerSizeWidth = MAX(orginInnerSizeWidth, _size.width);
    float innerSizeHeight = MAX(orginInnerSizeHeight, _size.height);
    _innerContainer->setSize(Size(innerSizeWidth, innerSizeHeight));
}

const Size& UIDragPanel::getInnerContainerSize() const
{
	return _innerContainer->getContentSize();
}

void UIDragPanel::setInnerContainerSize(const cocos2d::Size &size)
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

const Point& UIDragPanel::getInnerContainerPosition() const
{
    return _innerContainer->getPosition();
}

void UIDragPanel::setInnerContainerPosition(const Point &point, bool animated)
{
    Point delta = point - _innerContainer->getPosition();

//    Point delta = ccpSub(point, _innerContainer->getPosition());
    setInnerContainerOffset(delta, animated);
}

void UIDragPanel::setInnerContainerOffset(const Point &offset, bool animated)
{
    if (animated)
    {
        Point delta = offset;
        
        if (checkToBoundaryWithDeltaPosition(delta))
        {
            delta = calculateToBoundaryDeltaPosition(delta);
        }
        actionStartWithWidget(_innerContainer);
        moveByWithDuration(_autoMoveDuration, delta);
    }
    else
    {
        setInnerContainerOffset(offset);
    }
}

void UIDragPanel::setInnerContainerOffset(const Point &offset)
{
    Point delta = offset;
    
    if (checkToBoundaryWithDeltaPosition(delta))
    {
        delta = calculateToBoundaryDeltaPosition(delta);
    }
    moveWithDelta(delta);
    if (checkBerth())
    {
        berthEvent();
    }
}


void UIDragPanel::handlePressLogic(const Point &touchPoint)
{
    // check inner rect < drag panel rect
    if (checkContainInnerRect())
    {
        _touchPressed = false;
        return;
    }        
    
    _touchPressed = true;
    _touchMoved = false;
    _touchReleased = false;
    _touchCanceld = false;
    
    if (_runningAction)
    {
        switch (_moveType)
        {
            case DRAGPANEL_MOVE_TYPE_AUTOMOVE:
                stopAutoMove();
                actionStop();
                break;
                
            case DRAGPANEL_MOVE_TYPE_BOUNCE:
                _touchPressed = false;
                break;
                
            default:
                break;
        }
    }
    
    Point nsp = _renderer->convertToNodeSpace(touchPoint);
    _touchStartNodeSpace = nsp;
    
    _touchStartWorldSpace = touchPoint;
}

void UIDragPanel::handleMoveLogic(const Point &touchPoint)
{
    if (!_touchPressed)
    {
        return;
    }
    
    // check touch out of drag panel boundary
    if (_touchCanceld)
    {
        return;
    }
        
    _touchMoved = true;
    
    Point nsp = _renderer->convertToNodeSpace(touchPoint);
    Point delta = nsp - _touchStartNodeSpace;
//    Point delta = ccpSub(nsp, _touchStartNodeSpace);
    _touchStartNodeSpace = nsp;
    
    // reset berth dir to none
    if (!_bounceEnable)
    {
        _berthDirection = DRAGPANEL_BERTH_DIR_NONE;
    }
    
    // check will berth (bounce disable)
    if (!_bounceEnable)
    {
        if (checkToBoundaryWithDeltaPosition(delta))
        {
            delta = calculateToBoundaryDeltaPosition(delta);
        }                        
    }
    // move
    moveWithDelta(delta);
    // check bounce or berth
    if (_bounceEnable)
    {
        // bounce
        if (!hitTest(touchPoint))
        {
            _touchMoved = false;
            
            if (checkNeedBounce())
            {
                _touchCanceld = true;
                startBounce();
            }
        }
    }
    else
    {
        // berth
        if (checkBerth())
        {
            berthEvent();
        }
    }
}

void UIDragPanel::handleReleaseLogic(const Point &touchPoint)
{
    if (!_touchPressed)
    {
        return;
    }
    
    _touchPressed = false;
    _touchMoved = false;
    _touchReleased = true;
    _touchCanceld = false;
    
    // check touch out of drag panel boundary
    if (_touchCanceld)
    {
        return;
    }
    
    if (hitTest(touchPoint))
    {
        _touchEndWorldSpace = touchPoint;
        startAutoMove();
    }
}

void UIDragPanel::checkChildInfo(int handleState, UIWidget *sender, const Point &touchPoint)
{
    interceptTouchEvent(handleState, sender, touchPoint);
}

void UIDragPanel::interceptTouchEvent(int handleState, UIWidget *sender, const Point &touchPoint)
{
    switch (handleState)
    {
        case 0:
            handlePressLogic(touchPoint);
            break;
            
        case 1:
        {
//            float offset = ccpDistance(sender->getTouchStartPos(), touchPoint);
            float offset = sender->getTouchStartPos().getDistance(touchPoint);
            if (offset > 5.0)
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

void UIDragPanel::recordSlidTime(float dt)
{
    if (_touchPressed)
    {
        _slidTime += dt;
    }
}

// check if dragpanel rect contain inner rect
bool UIDragPanel::checkContainInnerRect()
{
    float width = _size.width;
    float height = _size.height;
    float innerWidth = _innerContainer->getSize().width;
    float innerHeight = _innerContainer->getSize().height;
    
    if (innerWidth <= width && innerHeight <= height)
    {
        return true;
    }
    
    return false;
}

// move
void UIDragPanel::moveWithDelta(const Point &delta)
{
    Point newPos = _innerContainer->getPosition() + delta;
//    Point newPos = ccpAdd(_innerContainer->getPosition(), delta);
    _innerContainer->setPosition(newPos);
}

// auto move
void UIDragPanel::autoMove()
{
    if (_bounceEnable)
    {
        if (checkNeedBounce())
        {
            stopAutoMove();
            startBounce();
        }
    }
}

void UIDragPanel::autoMoveOver()
{
    stopAutoMove();
    
    if (checkBerth())
    {        
        berthEvent();
        _berthDirection = DRAGPANEL_BERTH_DIR_NONE;
    }
}

void UIDragPanel::startAutoMove()
{    
    _moveType = DRAGPANEL_MOVE_TYPE_AUTOMOVE;
    
    actionStop();

    Point delta = _touchEndWorldSpace - _touchStartWorldSpace;
//    Point delta = ccpSub(m_touchEndWorldSpace, _touchStartWorldSpace);
    delta.x /= _slidTime * 60;
    delta.y /= _slidTime * 60;
    _slidTime = 0.0;
    
    // bounceEnable is disable
    if (!_bounceEnable)
    {
        if (checkToBoundaryWithDeltaPosition(delta))
        {
            delta = calculateToBoundaryDeltaPosition(delta);
        }
    }
    actionStartWithWidget(_innerContainer);
    moveByWithDuration(_autoMoveDuration, delta);
}

void UIDragPanel::stopAutoMove()
{
    _moveType = DRAGPANEL_MOVE_TYPE_NONE;
}

void UIDragPanel::setAutoMoveDuration(float duration)
{
    _autoMoveDuration = duration;
}

void UIDragPanel::setAutoMoveEaseRate(float rate)
{
    _autoMoveEaseRate = rate;
}

// berth

// check if move to boundary

bool UIDragPanel::checkToBoundaryWithDeltaPosition(const Point&  delta)
{
    float innerLeft = _innerContainer->getLeftInParent();
    float innerTop = _innerContainer->getTopInParent();
    float innerRight = _innerContainer->getRightInParent();
    float innerBottom = _innerContainer->getBottomInParent();
    
    float left = 0;
    float top = _size.height;
    float right = _size.width;
    float bottom = 0;
    
    bool toLeftBottom = false;
    bool toLeftTop = false;
    bool toRightBottom = false;
    bool toRightTop = false;
    bool toLeft = false;
    bool toRight = false;
    bool toTop = false;
    bool toBottom = false;
    
    if (innerLeft + delta.x > left && innerBottom + delta.y > bottom) // left bottom
    {
        toLeftBottom = true;
    }
    else if (innerLeft + delta.x > left && innerTop + delta.y < top) // left top
    {
        toLeftTop = true;
    }
    else if (innerRight + delta.x < right && innerBottom + delta.y > bottom) // right bottom
    {
        toRightBottom = true;
    }
    else if (innerRight + delta.x < right && innerTop + delta.y < top) // right top
    {
        toRightTop = true;
    }
    else if (innerLeft + delta.x > left) // left
    {
        toLeft = true;
    }
    else if (innerRight + delta.x < right) // right
    {
        toRight = true;
    }
    else if (innerTop + delta.y < top) // top
    {
        toTop = true;
    }
    else if (innerBottom + delta.y > bottom) // bottom
    {
        toBottom = true;
    }
    
    if (toLeft || toTop || toRight || toBottom
        || toLeftBottom || toLeftTop || toRightBottom || toRightTop)
    {
        return true;
    }
    
    return false;
}

Point UIDragPanel::calculateToBoundaryDeltaPosition(const Point& paramDelta)
{
    float innerLeft = _innerContainer->getLeftInParent();
    float innerTop = _innerContainer->getTopInParent();
    float innerRight = _innerContainer->getRightInParent();
    float innerBottom = _innerContainer->getBottomInParent();
    
    float left = 0;
    float top = _size.height;
    float right = _size.width;
    float bottom = 0;
    
    Point delta = paramDelta;
    
    if (innerLeft + delta.x > left && innerBottom + delta.y > bottom) // left bottom
    {
        delta.x = left - innerLeft;
        delta.y = bottom - innerBottom;
    }
    else if (innerLeft + delta.x > left && innerTop + delta.y < top) // left top
    {
        delta.x = left - innerLeft;
        delta.y = top - innerTop;
    }
    else if (innerRight + delta.x < right && innerBottom + delta.y > bottom) // right bottom
    {
        delta.x = right - innerRight;
        delta.y = bottom - innerBottom;
    }
    else if (innerRight + delta.x < right && innerTop + delta.y < top) // right bottom
    {
        delta.x = right - innerRight;
        delta.y = top - innerTop;
    }
    else if (innerLeft + delta.x > left) // left
    {
        delta.x = left - innerLeft;
    }
    else if (innerRight + delta.x < right) // right
    {
        delta.x = right - innerRight;
    }
    else if (innerTop + delta.y < top) // top
    {
        delta.y = top - innerTop;
    }
    else if (innerBottom + delta.y > bottom) // bottom
    {
        delta.y = bottom - innerBottom;
    }
    
    return delta;
}

bool UIDragPanel::isBerth()
{
    return _berthDirection != DRAGPANEL_BERTH_DIR_NONE;
}

// check berth
bool UIDragPanel::checkBerth()
{
    float innerLeft = _innerContainer->getLeftInParent();
    float innerTop = _innerContainer->getTopInParent();
    float innerRight = _innerContainer->getRightInParent();
    float innerBottom = _innerContainer->getBottomInParent();
    
    float left = 0;
    float top = _size.height;
    float right = _size.width;
    float bottom = 0;
    
    if (innerLeft == left && innerBottom == bottom) // left bottom
    {
        _berthDirection = DRAGPANEL_BERTH_DIR_LEFTBOTTOM;
    }
    else if (innerLeft == left && innerTop == top) // left top
    {
        _berthDirection = DRAGPANEL_BERTH_DIR_LFETTOP;
    }
    else if (innerRight == right && innerBottom == bottom) // right bottom
    {
        _berthDirection = DRAGPANEL_BERTH_DIR_RIGHTBOTTOM;
    }
    else if (innerRight == right && innerTop == top) // right top
    {
        _berthDirection = DRAGPANEL_BERTH_DIR_RIGHTTOP;
    }
    else if (innerLeft == left) // left
    {
        _berthDirection = DRAGPANEL_BERTH_DIR_LEFT;
    }
    else if (innerRight == right) // right
    {
        _berthDirection = DRAGPANEL_BERTH_DIR_RIGHT;
    }
    else if (innerTop == top) // top
    {
        _berthDirection = DRAGPANEL_BERTH_DIR_TOP;
    }
    else if (innerBottom == bottom) // bottom
    {
        _berthDirection = DRAGPANEL_BERTH_DIR_BOTTOM;
    }
    
    if (_berthDirection != DRAGPANEL_BERTH_DIR_NONE)
    {
        return true;
    }    
    
    return false;
}

void UIDragPanel::berthEvent()
{
    switch (_berthDirection)
    {
        case DRAGPANEL_BERTH_DIR_LEFTBOTTOM:
            berthToLeftBottomEvent();
            break;
            
        case DRAGPANEL_BERTH_DIR_LFETTOP:
            berthToLeftTopEvent();
            break;
            
        case DRAGPANEL_BERTH_DIR_RIGHTBOTTOM:
            berthToRightBottomEvent();
            break;
            
        case DRAGPANEL_BERTH_DIR_RIGHTTOP:
            berthToRightTopEvent();
            break;
            
        case DRAGPANEL_BERTH_DIR_LEFT:
            berthToLeftEvent();
            break;
            
        case DRAGPANEL_BERTH_DIR_TOP:
            berthToTopEvent();
            break;
            
        case DRAGPANEL_BERTH_DIR_RIGHT:
            berthToRightEvent();
            break;
            
        case DRAGPANEL_BERTH_DIR_BOTTOM:
            berthToBottomEvent();
            break;
            
        default:
            break;
    }
}

void UIDragPanel::berthToLeftBottomEvent()
{
    if (_eventLister && _eventSelector)
    {
        (_eventLister->*_eventSelector)(this, DRAGPANEL_EVENT_BERTH_LEFTBOTTOM);
    }
}

void UIDragPanel::berthToLeftTopEvent()
{
    if (_eventLister && _eventSelector)
    {
        (_eventLister->*_eventSelector)(this, DRAGPANEL_EVENT_BERTH_LFETTOP);
    }
}

void UIDragPanel::berthToRightBottomEvent()
{
    if (_eventLister && _eventSelector)
    {
        (_eventLister->*_eventSelector)(this, DRAGPANEL_EVENT_BERTH_RIGHTBOTTOM);
    }
}

void UIDragPanel::berthToRightTopEvent()
{
    if (_eventLister && _eventSelector)
    {
        (_eventLister->*_eventSelector)(this, DRAGPANEL_EVENT_BERTH_RIGHTTOP);
    }
}

void UIDragPanel::berthToLeftEvent()
{
    if (_eventLister && _eventSelector)
    {
        (_eventLister->*_eventSelector)(this, DRAGPANEL_EVENT_BERTH_LEFT);
    }
}

void UIDragPanel::berthToTopEvent()
{
    if (_eventLister && _eventSelector)
    {
        (_eventLister->*_eventSelector)(this, DRAGPANEL_EVENT_BERTH_TOP);
    }
}

void UIDragPanel::berthToRightEvent()
{
    if (_eventLister && _eventSelector)
    {
        (_eventLister->*_eventSelector)(this, DRAGPANEL_EVENT_BERTH_RIGHT);
    }
}

void UIDragPanel::berthToBottomEvent()
{
    if (_eventLister && _eventSelector)
    {
        (_eventLister->*_eventSelector)(this, DRAGPANEL_EVENT_BERTH_BOTTOM);
    }
}

void UIDragPanel::addEventListener(Object *target, SEL_DragPanelEvent selector)
{
    _eventLister = target;
    _eventSelector = selector;
}

// bounce
bool UIDragPanel::isBounceEnable()
{
    return _bounceEnable;
}

void UIDragPanel::setBounceEnable(bool bounce)
{
    _bounceEnable = bounce;
}

bool UIDragPanel::checkNeedBounce()
{
    float innerLeft = _innerContainer->getLeftInParent();
    float innerTop = _innerContainer->getTopInParent();
    float innerRight = _innerContainer->getRightInParent();
    float innerBottom = _innerContainer->getBottomInParent();
    
    float left = 0;
    float top = _size.height;
    float right = _size.width;
    float bottom = 0;        
    
    bool need = ((innerLeft > left && innerBottom > bottom)
                 || (innerLeft > left && innerTop < top)
                 || (innerRight < right && innerBottom > bottom)
                 || (innerRight < right && innerTop < top)
                 || (innerLeft > left)
                 || (innerTop < top)
                 || (innerRight < right)
                 || (innerBottom > bottom));
    return need;
}

void UIDragPanel::startBounce()
{
    if (_moveType == DRAGPANEL_MOVE_TYPE_BOUNCE)
    {
        return;
    }
    
    actionStop();
    _moveType = DRAGPANEL_MOVE_TYPE_BOUNCE;
    bounceToCorner();
}

void UIDragPanel::stopBounce()
{
    _moveType = DRAGPANEL_MOVE_TYPE_NONE;
}

void UIDragPanel::bounceToCorner()
{
    float innerLeft = _innerContainer->getLeftInParent();
    float innerTop = _innerContainer->getTopInParent();
    float innerRight = _innerContainer->getRightInParent();
    float innerBottom = _innerContainer->getBottomInParent();
    
    float width = _size.width;
    float height = _size.height;
    float left = 0;
    float top = height;
    float right = width;
    float bottom = 0;
    
    float from_x = 0;
    float from_y = 0;
    float to_x = 0;
    float to_y = 0;
    Point delta = Point::ZERO;
    
    if (innerLeft > left && innerBottom > bottom) // left bottom
    {
        from_x = innerLeft;
        from_y = innerBottom;
        to_x = left;
        to_y = bottom;
        
        _bounceDirection = DRAGPANEL_BOUNCE_DIR_LEFTBOTTOM;
    }
    else if (innerLeft > left && innerTop < top) // left top
    {
        from_x = innerLeft;
        from_y = innerTop;
        to_x = left;
        to_y = top;
        
        _bounceDirection = DRAGPANEL_BOUNCE_DIR_LEFTTOP;
    }
    else if (innerRight < right && innerBottom > bottom) // right bottom
    {
        from_x = innerRight;
        from_y = innerBottom;
        to_x = right;
        to_y = bottom;
        
        _bounceDirection = DRAGPANEL_BOUNCE_DIR_RIGHTBOTTOM;
    }
    else if (innerRight < right && innerTop < top) // right top
    {
        from_x = innerRight;
        from_y = innerTop;
        to_x = right;
        to_y = top;
        
        _bounceDirection = DRAGPANEL_BOUNCE_DIR_RIGHTTOP;
    }
    else if (innerLeft > left) // left
    {
        from_x = innerLeft;
        from_y = innerBottom;
        to_x = left;
        to_y = from_y;
        
        _bounceDirection = DRAGPANEL_BOUNCE_DIR_LEFT;
    }
    else if (innerTop < top) // top
    {
        from_x = innerLeft;
        from_y = innerTop;
        to_x = from_x;
        to_y = top;
        
        _bounceDirection = DRAGPANEL_BOUNCE_DIR_TOP;
    }
    else if (innerRight < right) // right
    {
        from_x = innerRight;
        from_y = innerBottom;
        to_x = right;
        to_y = from_y;
        
        _bounceDirection = DRAGPANEL_BOUNCE_DIR_RIGHT;
    }
    else if (innerBottom > bottom) // bottom
    {
        from_x = innerLeft;
        from_y = innerBottom;
        to_x = from_x;
        to_y = bottom;
        
        _bounceDirection = DRAGPANEL_BOUNCE_DIR_BOTTOM;
    }
    delta = Point(to_x, to_y) - Point(from_x, from_y);
//    delta = ccpSub(ccp(to_x, to_y), ccp(from_x, from_y));
    
    actionStartWithWidget(_innerContainer);
    moveByWithDuration(_bounceDuration, delta);
}

void UIDragPanel::bounceOver()
{
    stopBounce();
    
    switch (_bounceDirection)
    {
        case DRAGPANEL_BOUNCE_DIR_LEFTBOTTOM:
            bounceToLeftBottomEvent();
            break;
            
        case DRAGPANEL_BOUNCE_DIR_LEFTTOP:
            bounceToLeftTopEvent();
            break;
            
        case DRAGPANEL_BOUNCE_DIR_RIGHTBOTTOM:
            bounceToRightBottomEvent();
            break;
            
        case DRAGPANEL_BOUNCE_DIR_RIGHTTOP:
            bounceToRightTopEvent();
            break;
            
        case DRAGPANEL_BOUNCE_DIR_LEFT:
            bounceToLeftEvent();
            break;
            
        case DRAGPANEL_BOUNCE_DIR_TOP:
            bounceToTopEvent();
            break;
            
        case DRAGPANEL_BOUNCE_DIR_RIGHT:
            bounceToRightEvent();
            break;
            
        case DRAGPANEL_BOUNCE_DIR_BOTTOM:
            bounceToBottomEvent();
            break;
            
        default:
            break;
    }
    
    _bounceDirection = DRAGPANEL_BOUNCE_DIR_NONE;
}

void UIDragPanel::bounceToLeftBottomEvent()
{
    if (_eventLister && _eventSelector)
    {
        (_eventLister->*_eventSelector)(this, DRAGPANEL_EVENT_BOUNCE_LEFTBOTTOM);
    }
}

void UIDragPanel::bounceToLeftTopEvent()
{
    if (_eventLister && _eventSelector)
    {
        (_eventLister->*_eventSelector)(this, DRAGPANEL_EVENT_BOUNCE_LEFTTOP);
    }
}

void UIDragPanel::bounceToRightBottomEvent()
{
    if (_eventLister && _eventSelector)
    {
        (_eventLister->*_eventSelector)(this, DRAGPANEL_EVENT_BOUNCE_RIGHTBOTTOM);
    }
}

void UIDragPanel::bounceToRightTopEvent()
{
    if (_eventLister && _eventSelector)
    {
        (_eventLister->*_eventSelector)(this, DRAGPANEL_EVENT_BOUNCE_RIGHTTOP);
    }
}

void UIDragPanel::bounceToLeftEvent()
{
    if (_eventLister && _eventSelector)
    {
        (_eventLister->*_eventSelector)(this, DRAGPANEL_EVENT_BOUNCE_LEFT);
    }
}

void UIDragPanel::bounceToTopEvent()
{
    if (_eventLister && _eventSelector)
    {
        (_eventLister->*_eventSelector)(this, DRAGPANEL_EVENT_BOUNCE_TOP);
    }
}

void UIDragPanel::bounceToRightEvent()
{
    if (_eventLister && _eventSelector)
    {
        (_eventLister->*_eventSelector)(this, DRAGPANEL_EVENT_BOUNCE_RIGHT);
    }
}

void UIDragPanel::bounceToBottomEvent()
{
    if (_eventLister && _eventSelector)
    {
        (_eventLister->*_eventSelector)(this, DRAGPANEL_EVENT_BOUNCE_BOTTOM);
    }
}

// widget action
void UIDragPanel::actionWithDuration(float duration)
{
    _duration = duration;
        
    if (_duration == 0)
    {
        _duration = FLT_EPSILON;
    }
    
    _elapsed = 0;
    _firstTick = true;
}

bool UIDragPanel::actionIsDone()
{
    bool value = (_elapsed >= _duration);
    return value;
}

void UIDragPanel::actionStartWithWidget(UIWidget *widget)
{
    _runningAction = true;
    _actionWidget = widget;
}

void UIDragPanel::actionStep(float dt)
{
    if (_firstTick)
    {
        _firstTick = false;
        _elapsed = 0;
    }
    else
    {
        _elapsed += dt;
    }
    
    actionUpdate(MAX (0,
                      MIN(1, _elapsed /
                          MAX(_duration, FLT_EPSILON)
                          )
                      )
                 );        
}

void UIDragPanel::actionUpdate(float dt)
{
    switch (_actionType)
    {
        case 1: // move by
            moveByUpdate(dt);
            break;
            
        case 2: // move to
            moveToUpdate(dt);
            break;
            
        default:
            break;
    }
}

void UIDragPanel::actionStop()
{
    _runningAction = false;
}

void UIDragPanel::actionDone()
{
    switch (_moveType)
    {
        case DRAGPANEL_MOVE_TYPE_AUTOMOVE:
            autoMoveOver();
            break;
            
        case DRAGPANEL_MOVE_TYPE_BOUNCE:
            bounceOver();
            break;
            
        default:
            break;
    }
}

// move by
void UIDragPanel::moveByWithDuration(float duration, const Point& deltaPosition)
{
    actionWithDuration(duration);
    _positionDelta = deltaPosition;
    moveByInit();
    _actionType = 1;
}

void UIDragPanel::moveByInit()
{
    _previousPosition = _startPosition = _actionWidget->getPosition();
}

void UIDragPanel::moveByUpdate(float t)
{
    float easeRate = 0.0f;
    switch (_moveType)
    {
        case DRAGPANEL_MOVE_TYPE_AUTOMOVE:
            easeRate = _autoMoveEaseRate;
            break;
            
        case DRAGPANEL_MOVE_TYPE_BOUNCE:
            easeRate = _bounceEaseRate;
            break;
            
        default:
            break;
    }
    t = powf(t, 1 / easeRate);
    
    Point currentPos = _actionWidget->getPosition();
    Point diff = currentPos - _previousPosition;
    _startPosition = _startPosition + diff;
//    Point diff = ccpSub(currentPos, _previousPosition);
//    _startPosition = ccpAdd( _startPosition, diff);
    
//    Point newPos = ccpAdd( _startPosition, ccpMult(_positionDelta, t) );
    Point newPos = _startPosition + (_positionDelta * t);
    
    _actionWidget->setPosition(newPos);
    _previousPosition = newPos;
    
    switch (_moveType)
    {
        case DRAGPANEL_MOVE_TYPE_AUTOMOVE:
            autoMove();
            break;
            
        default:
            break;
    }
}

// move to
void UIDragPanel::moveToWithDuration(float duration, const Point& position)
{
    actionWithDuration(duration);
    _endPosition = position;
    moveToInit();
    _actionType = 2;
}

void UIDragPanel::moveToInit()
{
    moveByInit();
    _positionDelta = _endPosition - _actionWidget->getPosition();
//    _positionDelta = ccpSub( _endPosition, _actionWidget->getPosition() );
}

void UIDragPanel::moveToUpdate(float t)
{
    moveByUpdate(t);
}

Layout* UIDragPanel::getInnerContainer()
{
    return _innerContainer;
}

const char* UIDragPanel::getDescription() const
{
    return "DragPanel";
}

NS_CC_EXT_END