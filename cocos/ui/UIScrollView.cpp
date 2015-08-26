/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "ui/UIScrollView.h"
#include "base/CCDirector.h"
#include "base/ccUtils.h"
#include "platform/CCDevice.h"
#include "ui/UIScrollViewBar.h"
#include "2d/CCTweenFunction.h"
#include "2d/CCCamera.h"
NS_CC_BEGIN

namespace ui {

static const float INERTIA_DEACCELERATION = 700.0f;
static const float INERTIA_VELOCITY_MAX = 2500;
static const float BOUNCE_BACK_DURATION = 1.0f;
#define MOVE_INCH            7.0f/160.0f

static float convertDistanceFromPointToInch(const Vec2& dis)
{
    auto glview = Director::getInstance()->getOpenGLView();
    int dpi = Device::getDPI();
    float distance = Vec2(dis.x * glview->getScaleX() / dpi, dis.y * glview->getScaleY() / dpi).getLength();
    return distance;
}

IMPLEMENT_CLASS_GUI_INFO(ScrollView)

ScrollView::ScrollView():
_innerContainer(nullptr),
_direction(Direction::VERTICAL),
_topBoundary(0.0f),
_bottomBoundary(0.0f),
_leftBoundary(0.0f),
_rightBoundary(0.0f),
_bePressed(false),
_childFocusCancelOffsetInInch(MOVE_INCH),
_inertiaScrollEnabled(true),
_inertiaScrolling(false),
_inertiaPrevTouchTimestamp(0),
_inertiaScrollExpectedTime(0),
_inertiaScrollElapsedTime(0),
_autoScrolling(false),
_autoScrollAttenuate(true),
_autoScrollDuration(0),
_autoScrollAccumulatedTime(0),
_bounceEnabled(false),
_bouncingBack(false),
_scrollBarEnabled(true),
_verticalScrollBar(nullptr),
_horizontalScrollBar(nullptr),
_scrollViewEventListener(nullptr),
_scrollViewEventSelector(nullptr),
_eventCallback(nullptr)
{
    setTouchEnabled(true);
    _propagateTouchEvents = false;
}

ScrollView::~ScrollView()
{
    _verticalScrollBar = nullptr;
    _horizontalScrollBar = nullptr;
    _scrollViewEventListener = nullptr;
    _scrollViewEventSelector = nullptr;
}

ScrollView* ScrollView::create()
{
    ScrollView* widget = new (std::nothrow) ScrollView();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

void ScrollView::onEnter()
{
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeJavascript)
    {
        if (ScriptEngineManager::sendNodeEventToJSExtended(this, kNodeOnEnter))
            return;
    }
#endif

    Layout::onEnter();
    scheduleUpdate();
}

bool ScrollView::init()
{
    if (Layout::init())
    {
        setClippingEnabled(true);
        _innerContainer->setTouchEnabled(false);
        if(_scrollBarEnabled)
        {
            initScrollBar();
        }
        return true;
    }
    return false;
}

void ScrollView::initRenderer()
{
    Layout::initRenderer();
    _innerContainer = Layout::create();
    _innerContainer->setColor(Color3B(255,255,255));
    _innerContainer->setOpacity(255);
    _innerContainer->setCascadeColorEnabled(true);
    _innerContainer->setCascadeOpacityEnabled(true);
    addProtectedChild(_innerContainer, 1, 1);
}

void ScrollView::onSizeChanged()
{
    Layout::onSizeChanged();
    _topBoundary = _contentSize.height;
    _rightBoundary = _contentSize.width;
    Size innerSize = _innerContainer->getContentSize();
    float orginInnerSizeWidth = innerSize.width;
    float orginInnerSizeHeight = innerSize.height;
    float innerSizeWidth = MAX(orginInnerSizeWidth, _contentSize.width);
    float innerSizeHeight = MAX(orginInnerSizeHeight, _contentSize.height);
    _innerContainer->setContentSize(Size(innerSizeWidth, innerSizeHeight));
    setInnerContainerPosition(Vec2(0, _contentSize.height - _innerContainer->getContentSize().height));
}

void ScrollView::setInnerContainerSize(const Size &size)
{
    float innerSizeWidth = _contentSize.width;
    float innerSizeHeight = _contentSize.height;
    Size originalInnerSize = _innerContainer->getContentSize();
    if (size.width < _contentSize.width)
    {
        CCLOG("Inner width <= scrollview width, it will be force sized!");
    }
    else
    {
        innerSizeWidth = size.width;
    }
    if (size.height < _contentSize.height)
    {
        CCLOG("Inner height <= scrollview height, it will be force sized!");
    }
    else
    {
        innerSizeHeight = size.height;
    }
    _innerContainer->setContentSize(Size(innerSizeWidth, innerSizeHeight));

    // move children appropriately
    {
        Size newInnerSize = _innerContainer->getContentSize();
        float offsetY = originalInnerSize.height - newInnerSize.height;
        float offsetX = 0;
        if (_innerContainer->getRightBoundary() <= _contentSize.width)
        {
            offsetX = originalInnerSize.width - newInnerSize.width;
        }
        if(offsetX != 0 || offsetY != 0)
        {
            Vec2 position = _innerContainer->getPosition() + Vec2(offsetX, offsetY);
            setInnerContainerPosition(position);
        }
    }

    
    // Calculate and set the position of the inner container.
    Vec2 pos = _innerContainer->getPosition();
    if (_innerContainer->getLeftBoundary() > 0.0f)
    {
        pos.x = _innerContainer->getAnchorPoint().x * _innerContainer->getContentSize().width;
    }
    if (_innerContainer->getRightBoundary() < _contentSize.width)
    {
        pos.x = _contentSize.width - ((1.0f - _innerContainer->getAnchorPoint().x) * _innerContainer->getContentSize().width);
    }
    if (_innerContainer->getPosition().y > 0.0f)
    {
        pos.y = _innerContainer->getAnchorPoint().y * _innerContainer->getContentSize().height;
    }
    if (_innerContainer->getTopBoundary() < _contentSize.height)
    {
        pos.y = _contentSize.height - (1.0f - _innerContainer->getAnchorPoint().y) * _innerContainer->getContentSize().height;
    }
    setInnerContainerPosition(pos);
    
    updateScrollBar(Vec2::ZERO);
}

const Size& ScrollView::getInnerContainerSize() const
{
    return _innerContainer->getContentSize();
}

void ScrollView::setInnerContainerPosition(const Vec2 &position)
{
    _innerContainer->setPosition(position);
    
    this->retain();
    if (_eventCallback)
    {
        _eventCallback(this, EventType::CONTAINER_MOVED);
    }
    if (_ccEventCallback)
    {
        _ccEventCallback(this, static_cast<int>(EventType::CONTAINER_MOVED));
    }
    this->release();
}
    
const Vec2 ScrollView::getInnerContainerPosition() const
{
    return _innerContainer->getPosition();
}

void ScrollView::addChild(Node* child)
{
    ScrollView::addChild(child, child->getLocalZOrder(), child->getTag());
}

void ScrollView::addChild(Node * child, int localZOrder)
{
    ScrollView::addChild(child, localZOrder, child->getTag());
}

void ScrollView::addChild(Node *child, int zOrder, int tag)
{
    _innerContainer->addChild(child, zOrder, tag);
}

void ScrollView::addChild(Node* child, int zOrder, const std::string &name)
{
    _innerContainer->addChild(child, zOrder, name);
}

void ScrollView::removeAllChildren()
{
    removeAllChildrenWithCleanup(true);
}

void ScrollView::removeAllChildrenWithCleanup(bool cleanup)
{
    _innerContainer->removeAllChildrenWithCleanup(cleanup);
}

void ScrollView::removeChild(Node* child, bool cleanup)
{
    return _innerContainer->removeChild(child, cleanup);
}

Vector<Node*>& ScrollView::getChildren()
{
    return _innerContainer->getChildren();
}

const Vector<Node*>& ScrollView::getChildren() const
{
    return _innerContainer->getChildren();
}

ssize_t ScrollView::getChildrenCount() const
{
    return _innerContainer->getChildrenCount();
}

Node* ScrollView::getChildByTag(int tag) const
{
    return _innerContainer->getChildByTag(tag);
}

Node* ScrollView::getChildByName(const std::string& name)const
{
    return _innerContainer->getChildByName(name);
}

void ScrollView::moveChildren(float offsetX, float offsetY)
{
    Vec2 position = _innerContainer->getPosition() + Vec2(offsetX, offsetY);
    moveChildrenToPosition(position);
}
    
void ScrollView::moveChildrenToPosition(const Vec2& position)
{
    setInnerContainerPosition(position);
    
    Vec2 outOfBoundary = getHowMuchOutOfBoundary(Vec2::ZERO);
    updateScrollBar(outOfBoundary);
}

void ScrollView::updateScrollBar(const Vec2& outOfBoundary)
{
    if(_verticalScrollBar != nullptr)
    {
        _verticalScrollBar->onScrolled(outOfBoundary);
    }
    if(_horizontalScrollBar != nullptr)
    {
        _horizontalScrollBar->onScrolled(outOfBoundary);
    }
}

bool ScrollView::startBounceBackIfNeeded()
{
    if (!_bounceEnabled)
    {
        return false;
    }
    Vec2 outOfBoundary = getHowMuchOutOfBoundary(Vec2::ZERO);
    if(outOfBoundary == Vec2::ZERO)
    {
        return false;
    }

    _bouncingBack = true;
    startAutoScroll(outOfBoundary, BOUNCE_BACK_DURATION, true);
    return true;
}

Vec2 ScrollView::getHowMuchOutOfBoundary(const Vec2& addition) const
{
    Vec2 result;

    if(_innerContainer->getLeftBoundary() + addition.x > _leftBoundary)
    {
        result.x = _leftBoundary - (_innerContainer->getLeftBoundary() + addition.x);
    }
    else if(_innerContainer->getRightBoundary() + addition.x < _rightBoundary)
    {
        result.x = _rightBoundary - (_innerContainer->getRightBoundary() + addition.x);
    }

    if(_innerContainer->getTopBoundary() + addition.y < _topBoundary)
    {
        result.y = _topBoundary - (_innerContainer->getTopBoundary() + addition.y);
    }
    else if(_innerContainer->getBottomBoundary() + addition.y > _bottomBoundary)
    {
        result.y = _bottomBoundary - (_innerContainer->getBottomBoundary() + addition.y);
    }
    return result;
}

void ScrollView::processAutoScrolling(float deltaTime)
{
    _autoScrollAccumulatedTime += deltaTime;
    float percentage = _autoScrollAccumulatedTime / _autoScrollDuration;
    if(percentage >= 1)
    {
        moveChildrenToPosition(_autoScrollStartPosition + _autoScrollTargetDelta);
        _autoScrolling = false;
        _bouncingBack = false;
    }
    else
    {
        if(_autoScrollAttenuate)
        {
            percentage = tweenfunc::quintEaseOut(percentage);
        }
        Vec2 moveDelta = _autoScrollTargetDelta * percentage;
        moveChildrenToPosition(_autoScrollStartPosition + moveDelta);
        
        // Dispatch related events if bouncing
        if(_bouncingBack)
        {
            if(moveDelta.x > 0)
            {
                processScrollEvent(MoveDirection::RIGHT, true);
            }
            else if(moveDelta.x < 0)
            {
                processScrollEvent(MoveDirection::LEFT, true);
            }
            if(moveDelta.y > 0)
            {
                processScrollEvent(MoveDirection::TOP, true);
            }
            else if(moveDelta.y < 0)
            {
                processScrollEvent(MoveDirection::BOTTOM, true);
            }
        }
    }
}

bool ScrollView::isOutOfBoundary(MoveDirection dir) const
{
    switch(dir)
    {
    case MoveDirection::TOP: return _innerContainer->getTopBoundary() < _topBoundary;
    case MoveDirection::BOTTOM: return _innerContainer->getBottomBoundary() > _bottomBoundary;
    case MoveDirection::LEFT: return _innerContainer->getLeftBoundary() > _leftBoundary;
    case MoveDirection::RIGHT: return _innerContainer->getRightBoundary() < _rightBoundary;
    }
}

bool ScrollView::isOutOfBoundaryTopOrBottom() const
{
    return isOutOfBoundary(MoveDirection::TOP) || isOutOfBoundary(MoveDirection::BOTTOM);
}

bool ScrollView::isOutOfBoundaryLeftOrRight() const
{
    return isOutOfBoundary(MoveDirection::LEFT) || isOutOfBoundary(MoveDirection::RIGHT);
}

void ScrollView::startAutoScroll(const Vec2& deltaMove, float duration, bool attenuated)
{
    _autoScrolling = true;
    _autoScrollTargetDelta = deltaMove;
    _autoScrollAttenuate = attenuated;
    _autoScrollStartPosition = _innerContainer->getPosition();
    _autoScrollDuration = duration;
    _autoScrollAccumulatedTime = 0;
}

void ScrollView::startAutoScrollChildrenWithDestination(const Vec2& des, float second, bool attenuated)
{
    startAutoScroll(des - _innerContainer->getPosition(), second, attenuated);
}

void ScrollView::jumpToDestination(const Vec2 &des)
{
    float finalOffsetX = des.x;
    float finalOffsetY = des.y;
    if (des.y <= 0 && _direction != Direction::HORIZONTAL)
    {
        finalOffsetY = MAX(des.y, _contentSize.height - _innerContainer->getContentSize().height);
    }
    if (des.x <= 0 && _direction != Direction::VERTICAL)
    {
        finalOffsetX = MAX(des.x, _contentSize.width - _innerContainer->getContentSize().width);
    }
    moveChildrenToPosition(Vec2(finalOffsetX, finalOffsetY));
}

void ScrollView::startInertiaScroll()
{
    float totalDuration = 0;
	for(auto &timeDelta : _inertiaTouchTimeDeltas)
	{
		totalDuration += timeDelta;
	}
    if(totalDuration == 0 || totalDuration >= 0.5f)
    {
        return;
    }
    
    _inertiaScrolling = true;
    
    // Calcualte the initial velocity
    Vec2 totalMovement;
	for(auto &displacement : _inertiaTouchDisplacements)
	{
		totalMovement += displacement;
	}
	
    for(auto i = _inertiaTouchDisplacements.begin(); i != _inertiaTouchDisplacements.end(); ++i)
    {
        totalMovement += (*i);
    }
    totalMovement.x = (_direction == Direction::VERTICAL ? 0 : totalMovement.x);
    totalMovement.y = (_direction == Direction::HORIZONTAL ? 0 : totalMovement.y);
    
    _inertiaInitiVelocity = totalMovement / totalDuration;
    _inertiaInitiVelocity.x = MIN(_inertiaInitiVelocity.x, INERTIA_VELOCITY_MAX);
    _inertiaInitiVelocity.y = MIN(_inertiaInitiVelocity.y, INERTIA_VELOCITY_MAX);
    _inertiaInitiVelocity.x = MAX(_inertiaInitiVelocity.x, -INERTIA_VELOCITY_MAX);
    _inertiaInitiVelocity.y = MAX(_inertiaInitiVelocity.y, -INERTIA_VELOCITY_MAX);
    
    // Calculate values for ease out
    _inertiaScrollExpectedTime = _inertiaInitiVelocity.length() / INERTIA_DEACCELERATION;
    _inertiaScrollElapsedTime = 0;
}

void ScrollView::processInertiaScrolling(float dt)
{
    _inertiaScrollElapsedTime += dt;
    if(isOutOfBoundaryLeftOrRight() || isOutOfBoundaryTopOrBottom())
    {
        // If the inner container is out of boundary, shorten the inertia time.
        _inertiaScrollElapsedTime += dt * (45000 / INERTIA_DEACCELERATION);
    }
    float percentage = _inertiaScrollElapsedTime / _inertiaScrollExpectedTime;
    if(percentage >= 1)
    {
        _inertiaScrolling = false;
        startBounceBackIfNeeded();
        return;
    }
    percentage = tweenfunc::quartEaseOut(percentage);
    
    Vec2 inertiaVelocity = _inertiaInitiVelocity * (1 - percentage);
    Vec2 displacement = inertiaVelocity * dt;
    if(!_bounceEnabled)
    {
        Vec2 outOfBoundary = getHowMuchOutOfBoundary(displacement);
        if(outOfBoundary != Vec2::ZERO)
        {
            // Don't allow to go out of boundary
            displacement += outOfBoundary;
            _inertiaScrolling = false;
        }
    }
    moveChildren(displacement.x, displacement.y);
}

bool ScrollView::scrollChildren(float touchOffsetX, float touchOffsetY)
{
    touchOffsetX = (_direction == Direction::VERTICAL ? 0 : touchOffsetX);
    touchOffsetY = (_direction == Direction::HORIZONTAL ? 0 : touchOffsetY);
    if(_bounceEnabled)
    {
        // If the position of the inner container is out of the boundary, the offsets should be divided by two.
        touchOffsetX *= (isOutOfBoundaryLeftOrRight() ? 0.5f : 1);
        touchOffsetY *= (isOutOfBoundaryTopOrBottom() ? 0.5f : 1);
    }
    
    float realOffsetX = touchOffsetX;
    float realOffsetY = touchOffsetY;
    
    bool scrolledToLeft = false;
    bool scrolledToRight = false;
    bool scrolledToTop = false;
    bool scrolledToBottom = false;
    if (touchOffsetY > 0.0f) // up
    {
        float icBottomPos = _innerContainer->getBottomBoundary();
        if (icBottomPos + touchOffsetY >= _bottomBoundary)
        {
            if(!_bounceEnabled)
            {
                realOffsetY = _bottomBoundary - icBottomPos;
            }
            scrolledToBottom = true;
        }
    }
    else if (touchOffsetY < 0.0f) // down
    {
        float icTopPos = _innerContainer->getTopBoundary();
        if (icTopPos + touchOffsetY <= _topBoundary)
        {
            if(!_bounceEnabled)
            {
                realOffsetY = _topBoundary - icTopPos;
            }
            scrolledToTop = true;
        }
    }
    
    if (touchOffsetX < 0.0f) // left
    {
        float icRightPos = _innerContainer->getRightBoundary();
        if (icRightPos + touchOffsetX <= _rightBoundary)
        {
            if(!_bounceEnabled)
            {
                realOffsetX = _rightBoundary - icRightPos;
            }
            scrolledToRight = true;
        }
    }
    else if (touchOffsetX > 0.0f) // right
    {
        float icLeftPos = _innerContainer->getLeftBoundary();
        if (icLeftPos + touchOffsetX >= _leftBoundary)
        {
            if(!_bounceEnabled)
            {
                realOffsetX = _leftBoundary - icLeftPos;
            }
            scrolledToLeft = true;
        }
    }
    moveChildren(realOffsetX, realOffsetY);
    
    if(realOffsetX != 0 || realOffsetY != 0)
    {
        processScrollingEvent();
    }
    if(scrolledToBottom)
    {
        processScrollEvent(MoveDirection::BOTTOM, false);
    }
    if(scrolledToTop)
    {
        processScrollEvent(MoveDirection::TOP, false);
    }
    if(scrolledToLeft)
    {
        processScrollEvent(MoveDirection::LEFT, false);
    }
    if(scrolledToRight)
    {
        processScrollEvent(MoveDirection::RIGHT, false);
    }
    
    bool scrollEnabledUpDown = (!scrolledToBottom && !scrolledToTop);
    bool scrollEnabledLeftRight = (!scrolledToLeft && !scrolledToRight);
    return scrollEnabledUpDown || scrollEnabledLeftRight;
}

void ScrollView::scrollToBottom(float second, bool attenuated)
{
    startAutoScrollChildrenWithDestination(Vec2(_innerContainer->getPosition().x, 0.0f), second, attenuated);
}

void ScrollView::scrollToTop(float second, bool attenuated)
{
    startAutoScrollChildrenWithDestination(Vec2(_innerContainer->getPosition().x,
                                                _contentSize.height - _innerContainer->getContentSize().height), second, attenuated);
}

void ScrollView::scrollToLeft(float second, bool attenuated)
{
    startAutoScrollChildrenWithDestination(Vec2(0.0f, _innerContainer->getPosition().y), second, attenuated);
}

void ScrollView::scrollToRight(float second, bool attenuated)
{
    startAutoScrollChildrenWithDestination(Vec2(_contentSize.width - _innerContainer->getContentSize().width,
                                                _innerContainer->getPosition().y), second, attenuated);
}

void ScrollView::scrollToTopLeft(float second, bool attenuated)
{
    if (_direction != Direction::BOTH)
    {
        CCLOG("Scroll direction is not both!");
        return;
    }
    startAutoScrollChildrenWithDestination(Vec2(0.0f, _contentSize.height - _innerContainer->getContentSize().height), second, attenuated);
}

void ScrollView::scrollToTopRight(float second, bool attenuated)
{
    if (_direction != Direction::BOTH)
    {
        CCLOG("Scroll direction is not both!");
        return;
    }
    startAutoScrollChildrenWithDestination(Vec2(_contentSize.width - _innerContainer->getContentSize().width,
                                                _contentSize.height - _innerContainer->getContentSize().height), second, attenuated);
}

void ScrollView::scrollToBottomLeft(float second, bool attenuated)
{
    if (_direction != Direction::BOTH)
    {
        CCLOG("Scroll direction is not both!");
        return;
    }
    startAutoScrollChildrenWithDestination(Vec2::ZERO, second, attenuated);
}

void ScrollView::scrollToBottomRight(float second, bool attenuated)
{
    if (_direction != Direction::BOTH)
    {
        CCLOG("Scroll direction is not both!");
        return;
    }
    startAutoScrollChildrenWithDestination(Vec2(_contentSize.width - _innerContainer->getContentSize().width, 0.0f), second, attenuated);
}

void ScrollView::scrollToPercentVertical(float percent, float second, bool attenuated)
{
    float minY = _contentSize.height - _innerContainer->getContentSize().height;
    float h = - minY;
    startAutoScrollChildrenWithDestination(Vec2(_innerContainer->getPosition().x, minY + percent * h / 100.0f), second, attenuated);
}

void ScrollView::scrollToPercentHorizontal(float percent, float second, bool attenuated)
{
    float w = _innerContainer->getContentSize().width - _contentSize.width;
    startAutoScrollChildrenWithDestination(Vec2(-(percent * w / 100.0f), _innerContainer->getPosition().y), second, attenuated);
}

void ScrollView::scrollToPercentBothDirection(const Vec2& percent, float second, bool attenuated)
{
    if (_direction != Direction::BOTH)
    {
        return;
    }
    float minY = _contentSize.height - _innerContainer->getContentSize().height;
    float h = - minY;
    float w = _innerContainer->getContentSize().width - _contentSize.width;
    startAutoScrollChildrenWithDestination(Vec2(-(percent.x * w / 100.0f), minY + percent.y * h / 100.0f), second, attenuated);
}

void ScrollView::jumpToBottom()
{
    jumpToDestination(Vec2(_innerContainer->getPosition().x, 0.0f));
}

void ScrollView::jumpToTop()
{
    jumpToDestination(Vec2(_innerContainer->getPosition().x,
                           _contentSize.height - _innerContainer->getContentSize().height));
}

void ScrollView::jumpToLeft()
{
    jumpToDestination(Vec2(0.0f, _innerContainer->getPosition().y));
}

void ScrollView::jumpToRight()
{
    jumpToDestination(Vec2(_contentSize.width - _innerContainer->getContentSize().width, _innerContainer->getPosition().y));
}

void ScrollView::jumpToTopLeft()
{
    if (_direction != Direction::BOTH)
    {
        CCLOG("Scroll direction is not both!");
        return;
    }
    jumpToDestination(Vec2(0.0f, _contentSize.height - _innerContainer->getContentSize().height));
}

void ScrollView::jumpToTopRight()
{
    if (_direction != Direction::BOTH)
    {
        CCLOG("Scroll direction is not both!");
        return;
    }
    jumpToDestination(Vec2(_contentSize.width - _innerContainer->getContentSize().width,
                           _contentSize.height - _innerContainer->getContentSize().height));
}

void ScrollView::jumpToBottomLeft()
{
    if (_direction != Direction::BOTH)
    {
        CCLOG("Scroll direction is not both!");
        return;
    }
    jumpToDestination(Vec2::ZERO);
}

void ScrollView::jumpToBottomRight()
{
    if (_direction != Direction::BOTH)
    {
        CCLOG("Scroll direction is not both!");
        return;
    }
    jumpToDestination(Vec2(_contentSize.width - _innerContainer->getContentSize().width, 0.0f));
}

void ScrollView::jumpToPercentVertical(float percent)
{
    float minY = _contentSize.height - _innerContainer->getContentSize().height;
    float h = - minY;
    jumpToDestination(Vec2(_innerContainer->getPosition().x, minY + percent * h / 100.0f));
}

void ScrollView::jumpToPercentHorizontal(float percent)
{
    float w = _innerContainer->getContentSize().width - _contentSize.width;
    jumpToDestination(Vec2(-(percent * w / 100.0f), _innerContainer->getPosition().y));
}

void ScrollView::jumpToPercentBothDirection(const Vec2& percent)
{
    if (_direction != Direction::BOTH)
    {
        return;
    }
    float minY = _contentSize.height - _innerContainer->getContentSize().height;
    float h = - minY;
    float w = _innerContainer->getContentSize().width - _contentSize.width;
    jumpToDestination(Vec2(-(percent.x * w / 100.0f), minY + percent.y * h / 100.0f));
}

void ScrollView::startRecordSlidAction()
{
    if (_inertiaScrolling)
    {
        _inertiaScrolling = false;
    }
    if(_autoScrolling)
    {
        _autoScrolling = false;
        _bouncingBack = false;
    }
}

void ScrollView::endRecordSlidAction()
{
    bool bounceBackStarted = startBounceBackIfNeeded();
    if(!bounceBackStarted && _inertiaScrollEnabled)
    {
        startInertiaScroll();
    }
}

void ScrollView::handlePressLogic(Touch *touch)
{
    startRecordSlidAction();
    _bePressed = true;

    _inertiaPrevTouchTimestamp = utils::getTimeInMilliseconds();
    _inertiaTouchDisplacements.clear();
    _inertiaTouchTimeDeltas.clear();
    
    if(_verticalScrollBar != nullptr)
    {
        _verticalScrollBar->onTouchBegan();
    }
    if(_horizontalScrollBar != nullptr)
    {
        _horizontalScrollBar->onTouchBegan();
    }
}

void ScrollView::handleMoveLogic(Touch *touch)
{
    Vec3 currPt, prevPt;
    if (nullptr == _hittedByCamera ||
        false == hitTest(touch->getLocation(), _hittedByCamera, &currPt) ||
        false == hitTest(touch->getPreviousLocation(), _hittedByCamera, &prevPt))
    {
        return;
    }
    Vec3 delta3 = currPt - prevPt;
    Vec2 delta(delta3.x, delta3.y);
    scrollChildren(delta.x, delta.y);

    while(_inertiaTouchDisplacements.size() > 5)
    {
        _inertiaTouchDisplacements.pop_front();
        _inertiaTouchTimeDeltas.pop_front();
    }
    _inertiaTouchDisplacements.push_back(delta);

    long long timestamp = utils::getTimeInMilliseconds();
    _inertiaTouchTimeDeltas.push_back((timestamp - _inertiaPrevTouchTimestamp) / 1000.0f);
    _inertiaPrevTouchTimestamp = timestamp;
}

void ScrollView::handleReleaseLogic(Touch *touch)
{
    endRecordSlidAction();
    _bePressed = false;
    
    if(_verticalScrollBar != nullptr)
    {
        _verticalScrollBar->onTouchEnded();
    }
    if(_horizontalScrollBar != nullptr)
    {
        _horizontalScrollBar->onTouchEnded();
    }
}

bool ScrollView::onTouchBegan(Touch *touch, Event *unusedEvent)
{
    bool pass = Layout::onTouchBegan(touch, unusedEvent);
    if (!_isInterceptTouch)
    {
        if (_hitted)
        {
            handlePressLogic(touch);
        }
    }
    return pass;
}

void ScrollView::onTouchMoved(Touch *touch, Event *unusedEvent)
{
    Layout::onTouchMoved(touch, unusedEvent);
    if (!_isInterceptTouch)
    {
        handleMoveLogic(touch);
    }
}

void ScrollView::onTouchEnded(Touch *touch, Event *unusedEvent)
{
    Layout::onTouchEnded(touch, unusedEvent);
    if (!_isInterceptTouch)
    {
        handleReleaseLogic(touch);
    }
    _isInterceptTouch = false;
}

void ScrollView::onTouchCancelled(Touch *touch, Event *unusedEvent)
{
    Layout::onTouchCancelled(touch, unusedEvent);
    if (!_isInterceptTouch)
    {
        handleReleaseLogic(touch);
    }
    _isInterceptTouch = false;
}

void ScrollView::update(float dt)
{
    if (_inertiaScrolling)
    {
        processInertiaScrolling(dt);
    }
    else if (_autoScrolling)
    {
        processAutoScrolling(dt);
    }
}

void ScrollView::interceptTouchEvent(Widget::TouchEventType event, Widget *sender,Touch* touch)
{
    if(!_touchEnabled)
    {
        Layout::interceptTouchEvent(event, sender, touch);
        return;
    }

    Vec2 touchPoint = touch->getLocation();
    switch (event)
    {
        case TouchEventType::BEGAN:
        {
            _isInterceptTouch = true;
            _touchBeganPosition = touch->getLocation();
            handlePressLogic(touch);
        }
        break;
        case TouchEventType::MOVED:
        {
            _touchMovePosition = touch->getLocation();
            // calculates move offset in points
            float offsetInInch = 0;
            switch (_direction)
            {
                case Direction::HORIZONTAL:
                    offsetInInch = convertDistanceFromPointToInch(Vec2(fabs(sender->getTouchBeganPosition().x - touchPoint.x), 0));
                    break;
                case Direction::VERTICAL:
                    offsetInInch = convertDistanceFromPointToInch(Vec2(0, fabs(sender->getTouchBeganPosition().y - touchPoint.y)));
                    break;
                case Direction::BOTH:
                    offsetInInch = convertDistanceFromPointToInch(sender->getTouchBeganPosition() - touchPoint);
                    break;
                default:
                    break;
            }
            if (offsetInInch > _childFocusCancelOffsetInInch)
            {
                sender->setHighlighted(false);
                handleMoveLogic(touch);
            }
        }
        break;

        case TouchEventType::CANCELED:
        case TouchEventType::ENDED:
        {
            _touchEndPosition = touch->getLocation();
            handleReleaseLogic(touch);
            if (sender->isSwallowTouches())
            {
                _isInterceptTouch = false;
            }
        }
        break;
    }
}

void ScrollView::processScrollEvent(MoveDirection dir, bool bounce)
{
    ScrollviewEventType scrollEventType;
    EventType eventType;
    switch(dir) {
    case MoveDirection::TOP:
    {
        scrollEventType = (bounce ? SCROLLVIEW_EVENT_BOUNCE_TOP : SCROLLVIEW_EVENT_SCROLL_TO_TOP);
        eventType = (bounce ? EventType::BOUNCE_TOP : EventType::SCROLL_TO_TOP);
        break;
    }
    case MoveDirection::BOTTOM:
    {
        scrollEventType = (bounce ? SCROLLVIEW_EVENT_BOUNCE_BOTTOM : SCROLLVIEW_EVENT_SCROLL_TO_BOTTOM);
        eventType = (bounce ? EventType::BOUNCE_BOTTOM : EventType::SCROLL_TO_BOTTOM);
        break;
    }
    case MoveDirection::LEFT:
    {
        scrollEventType = (bounce ? SCROLLVIEW_EVENT_BOUNCE_LEFT : SCROLLVIEW_EVENT_SCROLL_TO_LEFT);
        eventType = (bounce ? EventType::BOUNCE_LEFT : EventType::SCROLL_TO_LEFT);
        break;
    }
    case MoveDirection::RIGHT:
    {
        scrollEventType = (bounce ? SCROLLVIEW_EVENT_BOUNCE_RIGHT : SCROLLVIEW_EVENT_SCROLL_TO_RIGHT);
        eventType = (bounce ? EventType::BOUNCE_RIGHT : EventType::SCROLL_TO_RIGHT);
        break;
        }
    }
    dispatchEvent(scrollEventType, eventType);
}

void ScrollView::processScrollingEvent()
{
    dispatchEvent(SCROLLVIEW_EVENT_SCROLLING, EventType::SCROLLING);
}

void ScrollView::dispatchEvent(ScrollviewEventType scrollEventType, EventType eventType)
{
    this->retain();
    if (_scrollViewEventListener && _scrollViewEventSelector)
    {
        (_scrollViewEventListener->*_scrollViewEventSelector)(this, scrollEventType);
    }
    if (_eventCallback)
    {
        _eventCallback(this, eventType);
    }
    if (_ccEventCallback)
    {
        _ccEventCallback(this, static_cast<int>(eventType));
    }
    this->release();
}

void ScrollView::addEventListenerScrollView(Ref *target, SEL_ScrollViewEvent selector)
{
    _scrollViewEventListener = target;
    _scrollViewEventSelector = selector;
}

void ScrollView::addEventListener(const ccScrollViewCallback& callback)
{
    _eventCallback = callback;
}

void ScrollView::setDirection(Direction dir)
{
    _direction = dir;
    if(_scrollBarEnabled)
    {
        removeScrollBar();
        initScrollBar();
    }
}

ScrollView::Direction ScrollView::getDirection()const
{
    return _direction;
}

void ScrollView::setBounceEnabled(bool enabled)
{
    _bounceEnabled = enabled;
}

bool ScrollView::isBounceEnabled() const
{
    return _bounceEnabled;
}

void ScrollView::setInertiaScrollEnabled(bool enabled)
{
    _inertiaScrollEnabled = enabled;
}

bool ScrollView::isInertiaScrollEnabled() const
{
    return _inertiaScrollEnabled;
}

void ScrollView::setScrollBarEnabled(bool enabled)
{
	if(_scrollBarEnabled == enabled)
	{
		return;
	}
	
    if(_scrollBarEnabled)
    {
        removeScrollBar();
    }
    _scrollBarEnabled = enabled;
    if(_scrollBarEnabled)
    {
        initScrollBar();
    }
}

bool ScrollView::isScrollBarEnabled() const
{
    return _scrollBarEnabled;
}

void ScrollView::setScrollBarPositionFromCorner(const Vec2& positionFromCorner)
{
    if(_direction != Direction::HORIZONTAL)
    {
        setScrollBarPositionFromCornerForVertical(positionFromCorner);
    }
    if(_direction != Direction::VERTICAL)
    {
        setScrollBarPositionFromCornerForHorizontal(positionFromCorner);
    }
}

void ScrollView::setScrollBarPositionFromCornerForVertical(const Vec2& positionFromCorner)
{
    CCASSERT(_scrollBarEnabled, "Scroll bar should be enabled!");
    CCASSERT(_direction != Direction::HORIZONTAL, "Scroll view doesn't have a vertical scroll bar!");
    _verticalScrollBar->setPositionFromCorner(positionFromCorner);
}

Vec2 ScrollView::getScrollBarPositionFromCornerForVertical() const
{
    CCASSERT(_scrollBarEnabled, "Scroll bar should be enabled!");
    CCASSERT(_direction != Direction::HORIZONTAL, "Scroll view doesn't have a vertical scroll bar!");
    return _verticalScrollBar->getPositionFromCorner();
}

void ScrollView::setScrollBarPositionFromCornerForHorizontal(const Vec2& positionFromCorner)
{
    CCASSERT(_scrollBarEnabled, "Scroll bar should be enabled!");
    CCASSERT(_direction != Direction::VERTICAL, "Scroll view doesn't have a horizontal scroll bar!");
    _horizontalScrollBar->setPositionFromCorner(positionFromCorner);
}

Vec2 ScrollView::getScrollBarPositionFromCornerForHorizontal() const
{
    CCASSERT(_scrollBarEnabled, "Scroll bar should be enabled!");
    CCASSERT(_direction != Direction::VERTICAL, "Scroll view doesn't have a horizontal scroll bar!");
    return _horizontalScrollBar->getPositionFromCorner();
}

void ScrollView::setScrollBarWidth(float width)
{
    CCASSERT(_scrollBarEnabled, "Scroll bar should be enabled!");
    if(_verticalScrollBar != nullptr)
    {
        _verticalScrollBar->setWidth(width);
    }
    if(_horizontalScrollBar != nullptr)
    {
        _horizontalScrollBar->setWidth(width);
    }
}

float ScrollView::getScrollBarWidth() const
{
    CCASSERT(_scrollBarEnabled, "Scroll bar should be enabled!");
    if(_verticalScrollBar != nullptr)
    {
        return _verticalScrollBar->getWidth();
    }
    else if(_horizontalScrollBar != nullptr)
    {
        return _horizontalScrollBar->getWidth();
    }
    return 0;
}

void ScrollView::setScrollBarColor(const Color3B& color)
{
    CCASSERT(_scrollBarEnabled, "Scroll bar should be enabled!");
    if(_verticalScrollBar != nullptr)
    {
        _verticalScrollBar->setColor(color);
    }
    if(_horizontalScrollBar != nullptr)
    {
        _horizontalScrollBar->setColor(color);
    }
}

const Color3B& ScrollView::getScrollBarColor() const
{
    CCASSERT(_scrollBarEnabled, "Scroll bar should be enabled!");
    if(_verticalScrollBar != nullptr)
    {
        return _verticalScrollBar->getColor();
    }
    else if(_horizontalScrollBar != nullptr)
    {
        return _horizontalScrollBar->getColor();
    }
    return Color3B::WHITE;
}

void ScrollView::setScrollBarOpacity(GLubyte opacity)
{
    CCASSERT(_scrollBarEnabled, "Scroll bar should be enabled!");
    if(_verticalScrollBar != nullptr)
    {
        _verticalScrollBar->setOpacity(opacity);
    }
    if(_horizontalScrollBar != nullptr)
    {
        _horizontalScrollBar->setOpacity(opacity);
    }
}

GLubyte ScrollView::getScrollBarOpacity() const
{
    CCASSERT(_scrollBarEnabled, "Scroll bar should be enabled!");
    if(_verticalScrollBar != nullptr)
    {
        return _verticalScrollBar->getOpacity();
    }
    else if(_horizontalScrollBar != nullptr)
    {
        return _horizontalScrollBar->getOpacity();
    }
    return -1;
}

void ScrollView::setScrollBarAutoHideEnabled(bool autoHideEnabled)
{
    CCASSERT(_scrollBarEnabled, "Scroll bar should be enabled!");
    if(_verticalScrollBar != nullptr)
    {
        _verticalScrollBar->setAutoHideEnabled(autoHideEnabled);
    }
    if(_horizontalScrollBar != nullptr)
    {
        _horizontalScrollBar->setAutoHideEnabled(autoHideEnabled);
    }
}

bool ScrollView::isScrollBarAutoHideEnabled() const
{
    CCASSERT(_scrollBarEnabled, "Scroll bar should be enabled!");
    if(_verticalScrollBar != nullptr)
    {
        return _verticalScrollBar->isAutoHideEnabled();
    }
    else if(_horizontalScrollBar != nullptr)
    {
        return _horizontalScrollBar->isAutoHideEnabled();
    }
    return false;
}

void ScrollView::setScrollBarAutoHideTime(float autoHideTime)
{
    CCASSERT(_scrollBarEnabled, "Scroll bar should be enabled!");
    if(_verticalScrollBar != nullptr)
    {
        _verticalScrollBar->setAutoHideTime(autoHideTime);
    }
    if(_horizontalScrollBar != nullptr)
    {
        _horizontalScrollBar->setAutoHideTime(autoHideTime);
    }
}
    
float ScrollView::getScrollBarAutoHideTime() const
{
    CCASSERT(_scrollBarEnabled, "Scroll bar should be enabled!");
    if(_verticalScrollBar != nullptr)
    {
        return _verticalScrollBar->getAutoHideTime();
    }
    else if(_horizontalScrollBar != nullptr)
    {
        return _horizontalScrollBar->getAutoHideTime();
    }
    return 0;
}

Layout* ScrollView::getInnerContainer()const
{
    return _innerContainer;
}

void ScrollView::setLayoutType(Type type)
{
    _innerContainer->setLayoutType(type);
}

Layout::Type ScrollView::getLayoutType() const
{
    return _innerContainer->getLayoutType();
}

void ScrollView::doLayout()
{
    if (!_doLayoutDirty)
    {
        return;
    }
    _doLayoutDirty = false;
}

std::string ScrollView::getDescription() const
{
    return "ScrollView";
}

Widget* ScrollView::createCloneInstance()
{
    return ScrollView::create();
}

void ScrollView::copyClonedWidgetChildren(Widget* model)
{
    Layout::copyClonedWidgetChildren(model);
}

void ScrollView::copySpecialProperties(Widget *widget)
{
    ScrollView* scrollView = dynamic_cast<ScrollView*>(widget);
    if (scrollView)
    {
        Layout::copySpecialProperties(widget);
        _innerContainer = scrollView->_innerContainer;
        setDirection(scrollView->_direction);
        setInnerContainerSize(scrollView->getInnerContainerSize());
        _topBoundary = scrollView->_topBoundary;
        _bottomBoundary = scrollView->_bottomBoundary;
        _leftBoundary = scrollView->_leftBoundary;
        _rightBoundary = scrollView->_rightBoundary;
        _bePressed = scrollView->_bePressed;
        _childFocusCancelOffsetInInch = scrollView->_childFocusCancelOffsetInInch;
        setInertiaScrollEnabled(scrollView->_inertiaScrollEnabled);
        _inertiaScrolling = scrollView->_inertiaScrolling;
        _inertiaInitiVelocity = scrollView->_inertiaInitiVelocity;
        _inertiaTouchDisplacements = scrollView->_inertiaTouchDisplacements;
        _inertiaTouchTimeDeltas = scrollView->_inertiaTouchTimeDeltas;
        _inertiaPrevTouchTimestamp = scrollView->_inertiaPrevTouchTimestamp;
        _inertiaScrollExpectedTime = scrollView->_inertiaScrollExpectedTime;
        _inertiaScrollElapsedTime = scrollView->_inertiaScrollElapsedTime;
        _autoScrolling = scrollView->_autoScrolling;
        _autoScrollAttenuate = scrollView->_autoScrollAttenuate;
        _autoScrollStartPosition = scrollView->_autoScrollStartPosition;
        _autoScrollTargetDelta = scrollView->_autoScrollTargetDelta;
        _autoScrollDuration = scrollView->_autoScrollDuration;
        _autoScrollAccumulatedTime = scrollView->_autoScrollAccumulatedTime;
        setBounceEnabled(scrollView->_bounceEnabled);
        _bouncingBack = scrollView->_bouncingBack;
        _scrollViewEventListener = scrollView->_scrollViewEventListener;
        _scrollViewEventSelector = scrollView->_scrollViewEventSelector;
        _eventCallback = scrollView->_eventCallback;
        _ccEventCallback = scrollView->_ccEventCallback;
        
        setScrollBarEnabled(scrollView->isScrollBarEnabled());
        if(isScrollBarEnabled())
        {
            if(_direction != Direction::HORIZONTAL)
            {
                setScrollBarPositionFromCornerForVertical(scrollView->getScrollBarPositionFromCornerForVertical());
            }
            if(_direction != Direction::VERTICAL)
            {
                setScrollBarPositionFromCornerForHorizontal(scrollView->getScrollBarPositionFromCornerForHorizontal());
            }
            setScrollBarWidth(scrollView->getScrollBarWidth());
            setScrollBarColor(scrollView->getScrollBarColor());
            setScrollBarAutoHideEnabled(scrollView->isScrollBarAutoHideEnabled());
            setScrollBarAutoHideTime(scrollView->getScrollBarAutoHideTime());
        }
    }
}

void ScrollView::initScrollBar()
{
    if(_direction != Direction::HORIZONTAL && _verticalScrollBar == nullptr)
    {
        _verticalScrollBar = ScrollViewBar::create(this, Direction::VERTICAL);
        addProtectedChild(_verticalScrollBar, 2);
    }
    if(_direction != Direction::VERTICAL && _horizontalScrollBar == nullptr)
    {
        _horizontalScrollBar = ScrollViewBar::create(this, Direction::HORIZONTAL);
        addProtectedChild(_horizontalScrollBar, 2);
    }
}

void ScrollView::removeScrollBar()
{
    if(_verticalScrollBar != nullptr)
    {
        removeProtectedChild(_verticalScrollBar);
        _verticalScrollBar = nullptr;
    }
    if(_horizontalScrollBar != nullptr)
    {
        removeProtectedChild(_horizontalScrollBar);
        _horizontalScrollBar = nullptr;
    }
}

Widget* ScrollView::findNextFocusedWidget(cocos2d::ui::Widget::FocusDirection direction, cocos2d::ui::Widget *current)
{
    if (this->getLayoutType() == Layout::Type::VERTICAL
        || this->getLayoutType() == Layout::Type::HORIZONTAL)
    {
        return _innerContainer->findNextFocusedWidget(direction, current);
    }
    else
    {
        return Widget::findNextFocusedWidget(direction, current);
    }
}
}

NS_CC_END
