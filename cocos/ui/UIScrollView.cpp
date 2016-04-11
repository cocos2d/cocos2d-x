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

static const int NUMBER_OF_GATHERED_TOUCHES_FOR_MOVE_SPEED = 5;
static const float OUT_OF_BOUNDARY_BREAKING_FACTOR = 0.05f;
static const float BOUNCE_BACK_DURATION = 1.0f;

#define MOVE_INCH            7.0f/160.0f

static float convertDistanceFromPointToInch(const Vec2& dis)
{
    auto glview = Director::getInstance()->getOpenGLView();
    int dpi = Device::getDPI();
    float distance = Vec2(dis.x * glview->getScaleX() / dpi, dis.y * glview->getScaleY() / dpi).getLength();
    return distance;
}

namespace ui {

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
_touchMovePreviousTimestamp(0),
_touchTotalTimeThreshold(0.5f),
_autoScrolling(false),
_autoScrollAttenuate(true),
_autoScrollTotalTime(0),
_autoScrollAccumulatedTime(0),
_autoScrollCurrentlyOutOfBoundary(false),
_autoScrollBraking(false),
_inertiaScrollEnabled(true),
_bounceEnabled(false),
_outOfBoundaryAmount(Vec2::ZERO),
_outOfBoundaryAmountDirty(true),
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

    if (_verticalScrollBar != nullptr)
    {
        _verticalScrollBar->onScrolled(getHowMuchOutOfBoundary());
    }
    if (_horizontalScrollBar != nullptr)
    {
        _horizontalScrollBar->onScrolled(getHowMuchOutOfBoundary());
    }
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

    // Calculate and set the position of the inner container.
    Vec2 pos = _innerContainer->getPosition();
    if (_innerContainer->getLeftBoundary() != 0.0f)
    {
        pos.x = _innerContainer->getAnchorPoint().x * _innerContainer->getContentSize().width;
    }
    if (_innerContainer->getTopBoundary() != _contentSize.height)
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
    if(position == _innerContainer->getPosition())
    {
        return;
    }
    _innerContainer->setPosition(position);
    _outOfBoundaryAmountDirty = true;
    
    // Process bouncing events
    if(_bounceEnabled)
    {
        for(int direction = (int) MoveDirection::TOP; direction < (int) MoveDirection::RIGHT; ++direction)
        {
            if(isOutOfBoundary((MoveDirection) direction))
            {
                processScrollEvent((MoveDirection) direction, true);
            }
        }
    }
    
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
    
const Vec2& ScrollView::getInnerContainerPosition() const
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

void ScrollView::moveInnerContainer(const Vec2& deltaMove, bool canStartBounceBack)
{
    Vec2 adjustedMove = flattenVectorByDirection(deltaMove);

    setInnerContainerPosition(getInnerContainerPosition() + adjustedMove);

    Vec2 outOfBoundary = getHowMuchOutOfBoundary();
    updateScrollBar(outOfBoundary);

    if(_bounceEnabled && canStartBounceBack)
    {
        startBounceBackIfNeeded();
    }
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

Vec2 ScrollView::calculateTouchMoveVelocity() const
{
    float totalTime = 0;
    for(auto &timeDelta : _touchMoveTimeDeltas)
    {
        totalTime += timeDelta;
    }
    if(totalTime == 0 || totalTime >= _touchTotalTimeThreshold)
    {
        return Vec2::ZERO;
    }
    
    Vec2 totalMovement;
    for(auto &displacement : _touchMoveDisplacements)
    {
        totalMovement += displacement;
    }
    return totalMovement / totalTime;
}

void ScrollView::startInertiaScroll(const Vec2& touchMoveVelocity)
{
    const float MOVEMENT_FACTOR = 0.7f;
    Vec2 inertiaTotalMovement = touchMoveVelocity * MOVEMENT_FACTOR;
    startAttenuatingAutoScroll(inertiaTotalMovement, touchMoveVelocity);
}

bool ScrollView::startBounceBackIfNeeded()
{
    if (!_bounceEnabled)
    {
        return false;
    }
    Vec2 bounceBackAmount = getHowMuchOutOfBoundary();
    if(fltEqualZero(bounceBackAmount))
    {
        return false;
    }
    
    startAutoScroll(bounceBackAmount, BOUNCE_BACK_DURATION, true);
    return true;
}

Vec2 ScrollView::flattenVectorByDirection(const Vec2& vector)
{
    Vec2 result = vector;
    result.x = (_direction == Direction::VERTICAL ? 0 : result.x);
    result.y = (_direction == Direction::HORIZONTAL ? 0 : result.y);
    return result;
}

Vec2 ScrollView::getHowMuchOutOfBoundary(const Vec2& addition)
{
    if(addition == Vec2::ZERO && !_outOfBoundaryAmountDirty)
    {
        return _outOfBoundaryAmount;
    }
    
    Vec2 outOfBoundaryAmount(Vec2::ZERO);
    if(_innerContainer->getLeftBoundary() + addition.x > _leftBoundary)
    {
        outOfBoundaryAmount.x = _leftBoundary - (_innerContainer->getLeftBoundary() + addition.x);
    }
    else if(_innerContainer->getRightBoundary() + addition.x < _rightBoundary)
    {
        outOfBoundaryAmount.x = _rightBoundary - (_innerContainer->getRightBoundary() + addition.x);
    }
    
    if(_innerContainer->getTopBoundary() + addition.y < _topBoundary)
    {
        outOfBoundaryAmount.y = _topBoundary - (_innerContainer->getTopBoundary() + addition.y);
    }
    else if(_innerContainer->getBottomBoundary() + addition.y > _bottomBoundary)
    {
        outOfBoundaryAmount.y = _bottomBoundary - (_innerContainer->getBottomBoundary() + addition.y);
    }
    
    if(addition == Vec2::ZERO)
    {
        _outOfBoundaryAmount = outOfBoundaryAmount;
        _outOfBoundaryAmountDirty = false;
    }
    return outOfBoundaryAmount;
}

bool ScrollView::isOutOfBoundary(MoveDirection dir)
{
    Vec2 outOfBoundary = getHowMuchOutOfBoundary();
    switch(dir)
    {
        case MoveDirection::TOP: return outOfBoundary.y > 0;
        case MoveDirection::BOTTOM: return outOfBoundary.y < 0;
        case MoveDirection::LEFT: return outOfBoundary.x < 0;
        case MoveDirection::RIGHT: return outOfBoundary.x > 0;
    }
    return false;
}

bool ScrollView::isOutOfBoundary()
{
    return !fltEqualZero(getHowMuchOutOfBoundary());
}

void ScrollView::startAutoScrollToDestination(const Vec2& destination, float timeInSec, bool attenuated)
{
    startAutoScroll(destination - _innerContainer->getPosition(), timeInSec, attenuated);
}

static float calculateAutoScrollTimeByInitialSpeed(float initialSpeed)
{
    // Calculate the time from the initial speed according to quintic polynomial.
    float time = sqrtf(sqrtf(initialSpeed / 5));
    return time;
}

void ScrollView::startAttenuatingAutoScroll(const Vec2& deltaMove, const Vec2& initialVelocity)
{
    float time = calculateAutoScrollTimeByInitialSpeed(initialVelocity.length());
    startAutoScroll(deltaMove, time, true);
}

void ScrollView::startAutoScroll(const Vec2& deltaMove, float timeInSec, bool attenuated)
{
    Vec2 adjustedDeltaMove = flattenVectorByDirection(deltaMove);
    
    _autoScrolling = true;
    _autoScrollTargetDelta = adjustedDeltaMove;
    _autoScrollAttenuate = attenuated;
    _autoScrollStartPosition = _innerContainer->getPosition();
    _autoScrollTotalTime = timeInSec;
    _autoScrollAccumulatedTime = 0;
    _autoScrollBraking = false;
    _autoScrollBrakingStartPosition = Vec2::ZERO;
    
    // If the destination is also out of boundary of same side, start brake from beginning.
    Vec2 currentOutOfBoundary = getHowMuchOutOfBoundary();
    if (!fltEqualZero(currentOutOfBoundary))
    {
        _autoScrollCurrentlyOutOfBoundary = true;
        Vec2 afterOutOfBoundary = getHowMuchOutOfBoundary(adjustedDeltaMove);
        if(currentOutOfBoundary.x * afterOutOfBoundary.x > 0 || currentOutOfBoundary.y * afterOutOfBoundary.y > 0)
        {
            _autoScrollBraking = true;
        }
    }
}

void ScrollView::stopAutoScroll()
{
    _autoScrolling = false;
    _autoScrollAttenuate = true;
    _autoScrollTotalTime = 0;
    _autoScrollAccumulatedTime = 0;
}

bool ScrollView::isNecessaryAutoScrollBrake()
{
    if(_autoScrollBraking)
    {
        return true;
    }
    
    if(isOutOfBoundary())
    {
        // It just went out of boundary.
        if(!_autoScrollCurrentlyOutOfBoundary)
        {
            _autoScrollCurrentlyOutOfBoundary = true;
            _autoScrollBraking = true;
            _autoScrollBrakingStartPosition = getInnerContainerPosition();
            return true;
        }
    }
    else
    {
        _autoScrollCurrentlyOutOfBoundary = false;
    }
    return false;
}
    
float ScrollView::getAutoScrollStopEpsilon() const
{
    return FLT_EPSILON;
}


bool ScrollView::fltEqualZero(const Vec2& point) const
{
    return (fabsf(point.x) <= 0.0001f && fabsf(point.y) <= 0.0001f);
}


    
void ScrollView::processAutoScrolling(float deltaTime)
{
    // Make auto scroll shorter if it needs to deaccelerate.
    float brakingFactor = (isNecessaryAutoScrollBrake() ? OUT_OF_BOUNDARY_BREAKING_FACTOR : 1);
    
    // Elapsed time
    _autoScrollAccumulatedTime += deltaTime * (1 / brakingFactor);
    
    // Calculate the progress percentage
    float percentage = MIN(1, _autoScrollAccumulatedTime / _autoScrollTotalTime);
    if(_autoScrollAttenuate)
    {
        // Use quintic(5th degree) polynomial
        percentage = tweenfunc::quintEaseOut(percentage);
    }
    
    // Calculate the new position
    Vec2 newPosition = _autoScrollStartPosition + (_autoScrollTargetDelta * percentage);
    bool reachedEnd = fabs(percentage - 1) <= this->getAutoScrollStopEpsilon();
    
    if(_bounceEnabled)
    {
        // The new position is adjusted if out of boundary
        newPosition = _autoScrollBrakingStartPosition + (newPosition - _autoScrollBrakingStartPosition) * brakingFactor;
    }
    else
    {
        // Don't let go out of boundary
        Vec2 moveDelta = newPosition - getInnerContainerPosition();
        Vec2 outOfBoundary = getHowMuchOutOfBoundary(moveDelta);
        if (!fltEqualZero(outOfBoundary))
        {
            newPosition += outOfBoundary;
            reachedEnd = true;
        }
    }

    // Finish auto scroll if it ended
    if(reachedEnd)
    {
        _autoScrolling = false;
        dispatchEvent(SCROLLVIEW_EVENT_AUTOSCROLL_ENDED, EventType::AUTOSCROLL_ENDED);
    }

    moveInnerContainer(newPosition - getInnerContainerPosition(), reachedEnd);
}

void ScrollView::jumpToDestination(const Vec2 &des)
{
    _autoScrolling = false;
    moveInnerContainer(des - getInnerContainerPosition(), true);
}

void ScrollView::scrollChildren(const Vec2& deltaMove)
{
    Vec2 realMove = deltaMove;
    if(_bounceEnabled)
    {
        // If the position of the inner container is out of the boundary, the offsets should be divided by two.
        Vec2 outOfBoundary = getHowMuchOutOfBoundary();
        realMove.x *= (outOfBoundary.x == 0 ? 1 : 0.5f);
        realMove.y *= (outOfBoundary.y == 0 ? 1 : 0.5f);
    }
    
    if(!_bounceEnabled)
    {
        Vec2 outOfBoundary = getHowMuchOutOfBoundary(realMove);
        realMove += outOfBoundary;
    }
    
    bool scrolledToLeft = false;
    bool scrolledToRight = false;
    bool scrolledToTop = false;
    bool scrolledToBottom = false;
    if (realMove.y > 0.0f) // up
    {
        float icBottomPos = _innerContainer->getBottomBoundary();
        if (icBottomPos + realMove.y >= _bottomBoundary)
        {
            scrolledToBottom = true;
        }
    }
    else if (realMove.y < 0.0f) // down
    {
        float icTopPos = _innerContainer->getTopBoundary();
        if (icTopPos + realMove.y <= _topBoundary)
        {
            scrolledToTop = true;
        }
    }
    
    if (realMove.x < 0.0f) // left
    {
        float icRightPos = _innerContainer->getRightBoundary();
        if (icRightPos + realMove.x <= _rightBoundary)
        {
            scrolledToRight = true;
        }
    }
    else if (realMove.x > 0.0f) // right
    {
        float icLeftPos = _innerContainer->getLeftBoundary();
        if (icLeftPos + realMove.x >= _leftBoundary)
        {
            scrolledToLeft = true;
        }
    }
    moveInnerContainer(realMove, false);
    
    if(realMove.x != 0 || realMove.y != 0)
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
}

void ScrollView::scrollToBottom(float timeInSec, bool attenuated)
{
    startAutoScrollToDestination(Vec2(_innerContainer->getPosition().x, 0.0f), timeInSec, attenuated);
}

void ScrollView::scrollToTop(float timeInSec, bool attenuated)
{
    startAutoScrollToDestination(Vec2(_innerContainer->getPosition().x,
                                                _contentSize.height - _innerContainer->getContentSize().height), timeInSec, attenuated);
}

void ScrollView::scrollToLeft(float timeInSec, bool attenuated)
{
    startAutoScrollToDestination(Vec2(0.0f, _innerContainer->getPosition().y), timeInSec, attenuated);
}

void ScrollView::scrollToRight(float timeInSec, bool attenuated)
{
    startAutoScrollToDestination(Vec2(_contentSize.width - _innerContainer->getContentSize().width,
                                                _innerContainer->getPosition().y), timeInSec, attenuated);
}

void ScrollView::scrollToTopLeft(float timeInSec, bool attenuated)
{
    if (_direction != Direction::BOTH)
    {
        CCLOG("Scroll direction is not both!");
        return;
    }
    startAutoScrollToDestination(Vec2(0.0f, _contentSize.height - _innerContainer->getContentSize().height), timeInSec, attenuated);
}

void ScrollView::scrollToTopRight(float timeInSec, bool attenuated)
{
    if (_direction != Direction::BOTH)
    {
        CCLOG("Scroll direction is not both!");
        return;
    }
    startAutoScrollToDestination(Vec2(_contentSize.width - _innerContainer->getContentSize().width,
                                                _contentSize.height - _innerContainer->getContentSize().height), timeInSec, attenuated);
}

void ScrollView::scrollToBottomLeft(float timeInSec, bool attenuated)
{
    if (_direction != Direction::BOTH)
    {
        CCLOG("Scroll direction is not both!");
        return;
    }
    startAutoScrollToDestination(Vec2::ZERO, timeInSec, attenuated);
}

void ScrollView::scrollToBottomRight(float timeInSec, bool attenuated)
{
    if (_direction != Direction::BOTH)
    {
        CCLOG("Scroll direction is not both!");
        return;
    }
    startAutoScrollToDestination(Vec2(_contentSize.width - _innerContainer->getContentSize().width, 0.0f), timeInSec, attenuated);
}

void ScrollView::scrollToPercentVertical(float percent, float timeInSec, bool attenuated)
{
    float minY = _contentSize.height - _innerContainer->getContentSize().height;
    float h = - minY;
    startAutoScrollToDestination(Vec2(_innerContainer->getPosition().x, minY + percent * h / 100.0f), timeInSec, attenuated);
}

void ScrollView::scrollToPercentHorizontal(float percent, float timeInSec, bool attenuated)
{
    float w = _innerContainer->getContentSize().width - _contentSize.width;
    startAutoScrollToDestination(Vec2(-(percent * w / 100.0f), _innerContainer->getPosition().y), timeInSec, attenuated);
}

void ScrollView::scrollToPercentBothDirection(const Vec2& percent, float timeInSec, bool attenuated)
{
    if (_direction != Direction::BOTH)
    {
        return;
    }
    float minY = _contentSize.height - _innerContainer->getContentSize().height;
    float h = - minY;
    float w = _innerContainer->getContentSize().width - _contentSize.width;
    startAutoScrollToDestination(Vec2(-(percent.x * w / 100.0f), minY + percent.y * h / 100.0f), timeInSec, attenuated);
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

bool ScrollView::calculateCurrAndPrevTouchPoints(Touch* touch, Vec3* currPt, Vec3* prevPt)
{
    if (nullptr == _hittedByCamera ||
        false == hitTest(touch->getLocation(), _hittedByCamera, currPt) ||
        false == hitTest(touch->getPreviousLocation(), _hittedByCamera, prevPt))
    {
        return false;
    }
    return true;
}

void ScrollView::gatherTouchMove(const Vec2& delta)
{
    while(_touchMoveDisplacements.size() >= NUMBER_OF_GATHERED_TOUCHES_FOR_MOVE_SPEED)
    {
        _touchMoveDisplacements.pop_front();
        _touchMoveTimeDeltas.pop_front();
    }
    _touchMoveDisplacements.push_back(delta);
    
    long long timestamp = utils::getTimeInMilliseconds();
    _touchMoveTimeDeltas.push_back((timestamp - _touchMovePreviousTimestamp) / 1000.0f);
    _touchMovePreviousTimestamp = timestamp;
}

void ScrollView::handlePressLogic(Touch *touch)
{
    _bePressed = true;
    _autoScrolling = false;
    
    // Clear gathered touch move information
    {
        _touchMovePreviousTimestamp = utils::getTimeInMilliseconds();
        _touchMoveDisplacements.clear();
        _touchMoveTimeDeltas.clear();
    }
    
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
    if(!calculateCurrAndPrevTouchPoints(touch, &currPt, &prevPt))
    {
        return;
    }
    Vec3 delta3 = currPt - prevPt;
    Vec2 delta(delta3.x, delta3.y);
    scrollChildren(delta);
    
    // Gather touch move information for speed calculation
    gatherTouchMove(delta);
}

void ScrollView::handleReleaseLogic(Touch *touch)
{
    // Gather the last touch information when released
    {
        Vec3 currPt, prevPt;
        if(calculateCurrAndPrevTouchPoints(touch, &currPt, &prevPt))
        {
            Vec3 delta3 = currPt - prevPt;
            Vec2 delta(delta3.x, delta3.y);
            gatherTouchMove(delta);
        }
    }

    _bePressed = false;
    
    bool bounceBackStarted = startBounceBackIfNeeded();
    if(!bounceBackStarted && _inertiaScrollEnabled)
    {
        Vec2 touchMoveVelocity = calculateTouchMoveVelocity();
        if(touchMoveVelocity != Vec2::ZERO)
        {
            startInertiaScroll(touchMoveVelocity);
        }
    }
    
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
    if (_autoScrolling)
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
    if(_direction == Direction::NONE)
        return;
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
    
void ScrollView::setTouchTotalTimeThreshold(float touchTotalTimeThreshold)
{
    _touchTotalTimeThreshold = touchTotalTimeThreshold;
}

float ScrollView::getTouchTotalTimeThreshold() const
{
    return _touchTotalTimeThreshold;
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
        setDirection(scrollView->_direction);
        setInnerContainerPosition(scrollView->getInnerContainerPosition());
        setInnerContainerSize(scrollView->getInnerContainerSize());
        _topBoundary = scrollView->_topBoundary;
        _bottomBoundary = scrollView->_bottomBoundary;
        _leftBoundary = scrollView->_leftBoundary;
        _rightBoundary = scrollView->_rightBoundary;
        _bePressed = scrollView->_bePressed;
        _childFocusCancelOffsetInInch = scrollView->_childFocusCancelOffsetInInch;
        _touchMoveDisplacements = scrollView->_touchMoveDisplacements;
        _touchMoveTimeDeltas = scrollView->_touchMoveTimeDeltas;
        _touchMovePreviousTimestamp = scrollView->_touchMovePreviousTimestamp;
        _autoScrolling = scrollView->_autoScrolling;
        _autoScrollAttenuate = scrollView->_autoScrollAttenuate;
        _autoScrollStartPosition = scrollView->_autoScrollStartPosition;
        _autoScrollTargetDelta = scrollView->_autoScrollTargetDelta;
        _autoScrollTotalTime = scrollView->_autoScrollTotalTime;
        _autoScrollAccumulatedTime = scrollView->_autoScrollAccumulatedTime;
        _autoScrollCurrentlyOutOfBoundary = scrollView->_autoScrollCurrentlyOutOfBoundary;
        _autoScrollBraking = scrollView->_autoScrollBraking;
        _autoScrollBrakingStartPosition = scrollView->_autoScrollBrakingStartPosition;
        setInertiaScrollEnabled(scrollView->_inertiaScrollEnabled);
        setBounceEnabled(scrollView->_bounceEnabled);
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
