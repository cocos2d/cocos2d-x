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
#include "2d/CCTweenFunction.h"

NS_CC_BEGIN

namespace ui {

static const float INERTIA_DEACCELERATION = 3000.0f;
static const float BOUNCE_BACK_DURATION = 0.3f;

static long long getTimestamp()
{
	struct timeval tv;
	gettimeofday (&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
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
_childFocusCancelOffset(5.0f),
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
_scrollViewEventListener(nullptr),
_scrollViewEventSelector(nullptr),
_eventCallback(nullptr)
{
    setTouchEnabled(true);
}

ScrollView::~ScrollView()
{
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
    _innerContainer->setPosition(Vec2(0, _contentSize.height - _innerContainer->getContentSize().height));
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
	
	// Scroll children appropriately
	{
		float offsetX = originalInnerSize.height - innerSizeHeight;
		float offsetY = 0;
		if (_innerContainer->getRightBoundary() <= _contentSize.width)
		{
			offsetX = originalInnerSize.width - innerSizeWidth;
		}
		if(offsetX != 0 || offsetY != 0)
		{
			scrollChildren(offsetX, offsetY);
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
	_innerContainer->setPosition(pos);
}

const Size& ScrollView::getInnerContainerSize() const
{
	return _innerContainer->getContentSize();
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
    _innerContainer->setPosition(position);
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
		_innerContainer->setPosition(_autoScrollStartPosition + _autoScrollTargetDelta);
		_autoScrolling = false;
		_bouncingBack = false;
	}
	else
	{
		if(_autoScrollAttenuate)
		{
			percentage = tweenfunc::expoEaseOut(percentage);
		}
		Vec2 moveDelta = _autoScrollTargetDelta * percentage;
		
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
		_innerContainer->setPosition(_autoScrollStartPosition + moveDelta);
	}
}

bool ScrollView::isOutOfBoundary(MoveDirection dir) const
{
	switch(dir)
	{
		case MoveDirection::TOP:	return _innerContainer->getTopBoundary() < _topBoundary;
		case MoveDirection::BOTTOM:	return _innerContainer->getBottomBoundary() > _bottomBoundary;
		case MoveDirection::LEFT:	return _innerContainer->getLeftBoundary() > _leftBoundary;
		case MoveDirection::RIGHT:	return _innerContainer->getRightBoundary() < _rightBoundary;
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
    _innerContainer->setPosition(Vec2(finalOffsetX, finalOffsetY));
}

void ScrollView::startInertiaScroll()
{
	if(_inertiaTouchTimeDeltas.empty())
	{
		return;
	}
	
	float totalDuration = 0;
	for(auto i = _inertiaTouchTimeDeltas.begin(); i != _inertiaTouchTimeDeltas.end(); ++i)
	{
		totalDuration += (*i);
	}
	if(totalDuration >= 0.5f)
	{
		return;
	}
	
	_inertiaScrolling = true;
	
	// Calcualte the initial velocity
	Vec2 totalMovement;
	for(auto i = _inertiaTouchDisplacements.begin(); i != _inertiaTouchDisplacements.end(); ++i)
	{
		totalMovement += (*i);
	}
	totalMovement.x = (_direction == Direction::VERTICAL ? 0 : totalMovement.x);
	totalMovement.y = (_direction == Direction::HORIZONTAL ? 0 : totalMovement.y);
	
	_inertiaInitiVelocity = totalMovement / totalDuration;
	
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
		_inertiaScrollElapsedTime += dt * 15;
	}
	float percentage = _inertiaScrollElapsedTime / _inertiaScrollExpectedTime;
	if(percentage >= 1)
	{
		_inertiaScrolling = false;
		startBounceBackIfNeeded();
		return;
	}
	percentage = tweenfunc::expoEaseOut(percentage);
	
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

bool ScrollView::processScrollUp(float* offsetYResult, float touchOffsetY)
{
	float icBottomPos = _innerContainer->getBottomBoundary();
	if (icBottomPos + touchOffsetY < _bottomBoundary)
	{
		return true;
	}
	else if(!_bounceEnabled)
	{
		(*offsetYResult) = _bottomBoundary - icBottomPos;
	}
	processScrollEvent(MoveDirection::BOTTOM, false);
	return false;
}
	
bool ScrollView::processScrollDown(float* offsetYResult, float touchOffsetY)
{
	float icTopPos = _innerContainer->getTopBoundary();
	if (icTopPos + touchOffsetY > _topBoundary)
	{
		return true;
	}
	else if(!_bounceEnabled)
	{
		(*offsetYResult) = _topBoundary - icTopPos;
	}
	processScrollEvent(MoveDirection::TOP, false);
	return false;
}

bool ScrollView::processScrollLeft(float* offsetXResult, float touchOffsetX)
{
	float icRightPos = _innerContainer->getRightBoundary();
	if (icRightPos + touchOffsetX > _rightBoundary)
	{
		return true;
	}
	else if(!_bounceEnabled)
	{
		(*offsetXResult) = _rightBoundary - icRightPos;
	}
	processScrollEvent(MoveDirection::RIGHT, false);
	return false;
}

bool ScrollView::processScrollRight(float* offsetXResult, float touchOffsetX)
{
	float icLeftPos = _innerContainer->getLeftBoundary();
	if (icLeftPos + touchOffsetX < _leftBoundary)
	{
		return true;
	}
	else if(!_bounceEnabled)
	{
		(*offsetXResult) = _leftBoundary - icLeftPos;
	}
	processScrollEvent(MoveDirection::LEFT, false);
	return false;
}

bool ScrollView::scrollChildren(float touchOffsetX, float touchOffsetY)
{
    processScrollingEvent();
	
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
	
	bool scrollEnabledUpDown = true;
	bool scrollEnabledLeftRight = true;
	if (touchOffsetY > 0.0f) // up
	{
		scrollEnabledUpDown = processScrollUp(&realOffsetY, touchOffsetY);
	}
	else if (touchOffsetY < 0.0f) // down
	{
		scrollEnabledUpDown = processScrollDown(&realOffsetY, touchOffsetY);
	}
	
	if (touchOffsetX < 0.0f) // left
	{
		scrollEnabledLeftRight = processScrollLeft(&realOffsetX, touchOffsetX);
	}
	else if (touchOffsetX > 0.0f) // right
	{
		scrollEnabledLeftRight = processScrollRight(&realOffsetX, touchOffsetX);
	}
	moveChildren(realOffsetX, realOffsetY);
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
        CCLOG("Scroll diretion is not both!");
        return;
    }
    startAutoScrollChildrenWithDestination(Vec2(0.0f, _contentSize.height - _innerContainer->getContentSize().height), second, attenuated);
}

void ScrollView::scrollToTopRight(float second, bool attenuated)
{
    if (_direction != Direction::BOTH)
    {
        CCLOG("Scroll diretion is not both!");
        return;
    }
    startAutoScrollChildrenWithDestination(Vec2(_contentSize.width - _innerContainer->getContentSize().width,
                                                _contentSize.height - _innerContainer->getContentSize().height), second, attenuated);
}

void ScrollView::scrollToBottomLeft(float second, bool attenuated)
{
    if (_direction != Direction::BOTH)
    {
        CCLOG("Scroll diretion is not both!");
        return;
    }
    startAutoScrollChildrenWithDestination(Vec2::ZERO, second, attenuated);
}

void ScrollView::scrollToBottomRight(float second, bool attenuated)
{
    if (_direction != Direction::BOTH)
    {
        CCLOG("Scroll diretion is not both!");
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
        CCLOG("Scroll diretion is not both!");
        return;
    }
    jumpToDestination(Vec2(0.0f, _contentSize.height - _innerContainer->getContentSize().height));
}

void ScrollView::jumpToTopRight()
{
    if (_direction != Direction::BOTH)
    {
        CCLOG("Scroll diretion is not both!");
        return;
    }
    jumpToDestination(Vec2(_contentSize.width - _innerContainer->getContentSize().width,
                           _contentSize.height - _innerContainer->getContentSize().height));
}

void ScrollView::jumpToBottomLeft()
{
    if (_direction != Direction::BOTH)
    {
        CCLOG("Scroll diretion is not both!");
        return;
    }
    jumpToDestination(Vec2::ZERO);
}

void ScrollView::jumpToBottomRight()
{
    if (_direction != Direction::BOTH)
    {
        CCLOG("Scroll diretion is not both!");
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
	
	_inertiaPrevTouchTimestamp = getTimestamp();
	_inertiaTouchDisplacements.clear();
	_inertiaTouchTimeDeltas.clear();
}

void ScrollView::handleMoveLogic(Touch *touch)
{
    Vec2 touchPositionInNodeSpace = this->convertToNodeSpace(touch->getLocation());
    Vec2 previousTouchPositionInNodeSpace = this->convertToNodeSpace(touch->getPreviousLocation());
    Vec2 delta = touchPositionInNodeSpace - previousTouchPositionInNodeSpace;
	scrollChildren(delta.x, delta.y);
	
	while(_inertiaTouchDisplacements.size() > 5)
	{
		_inertiaTouchDisplacements.pop_front();
		_inertiaTouchTimeDeltas.pop_front();
	}
	_inertiaTouchDisplacements.push_back(delta);
	
	long long timestamp = getTimestamp();
	_inertiaTouchTimeDeltas.push_back((timestamp - _inertiaPrevTouchTimestamp) / 1000.0f);
	_inertiaPrevTouchTimestamp = timestamp;
}

void ScrollView::handleReleaseLogic(Touch *touch)
{
    endRecordSlidAction();
    _bePressed = false;
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
            float offset = (sender->getTouchBeganPosition() - touchPoint).getLength();
            _touchMovePosition = touch->getLocation();
            if (offset > _childFocusCancelOffset)
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
        setInnerContainerSize(scrollView->getInnerContainerSize());
        setDirection(scrollView->_direction);
        setBounceEnabled(scrollView->_bounceEnabled);
        setInertiaScrollEnabled(scrollView->_inertiaScrollEnabled);
        _scrollViewEventListener = scrollView->_scrollViewEventListener;
        _scrollViewEventSelector = scrollView->_scrollViewEventSelector;
        _eventCallback = scrollView->_eventCallback;
        _ccEventCallback = scrollView->_ccEventCallback;
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
