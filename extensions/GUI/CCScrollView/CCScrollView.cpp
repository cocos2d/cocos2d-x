/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2010 Sangwoo Im
 
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

#include "CCScrollView.h"
#include "CCGLView.h"
#include "platform/CCDevice.h"
#include "CCActionInstant.h"
#include "CCActionInterval.h"
#include "CCActionTween.h"
#include "CCDirector.h"
#include "renderer/CCRenderer.h"

#include <algorithm>

NS_CC_EXT_BEGIN

#define SCROLL_DEACCEL_RATE  0.95f
#define SCROLL_DEACCEL_DIST  1.0f
#define BOUNCE_DURATION      0.15f
#define INSET_RATIO          0.2f
#define MOVE_INCH            7.0f/160.0f

static float convertDistanceFromPointToInch(float pointDis)
{
    auto glview = Director::getInstance()->getOpenGLView();
    float factor = ( glview->getScaleX() + glview->getScaleY() ) / 2;
    return pointDis * factor / Device::getDPI();
}


ScrollView::ScrollView()
: _zoomScale(0.0f)
, _minZoomScale(0.0f)
, _maxZoomScale(0.0f)
, _delegate(nullptr)
, _direction(Direction::BOTH)
, _dragging(false)
, _container(nullptr)
, _touchMoved(false)
, _bounceable(false)
, _clippingToBounds(false)
, _touchLength(0.0f)
, _minScale(0.0f)
, _maxScale(0.0f)
, _touchListener(nullptr)
{

}

ScrollView::~ScrollView()
{

}

ScrollView* ScrollView::create(Size size, Node* container/* = NULL*/)
{
    ScrollView* pRet = new ScrollView();
    if (pRet && pRet->initWithViewSize(size, container))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

ScrollView* ScrollView::create()
{
    ScrollView* pRet = new ScrollView();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}


bool ScrollView::initWithViewSize(Size size, Node *container/* = NULL*/)
{
    if (Layer::init())
    {
        _container = container;
        
        if (!this->_container)
        {
            _container = Layer::create();
            _container->ignoreAnchorPointForPosition(false);
            _container->setAnchorPoint(Point(0.0f, 0.0f));
        }

        this->setViewSize(size);

        setTouchEnabled(true);
        
        _touches.reserve(EventTouch::MAX_TOUCHES);
        
        _delegate = NULL;
        _bounceable = true;
        _clippingToBounds = true;
        //_container->setContentSize(Size::ZERO);
        _direction  = Direction::BOTH;
        _container->setPosition(Point(0.0f, 0.0f));
        _touchLength = 0.0f;
        
        this->addChild(_container);
        _minScale = _maxScale = 1.0f;

        
        return true;
    }
    return false;
}

bool ScrollView::init()
{
    return this->initWithViewSize(Size(200, 200), NULL);
}

bool ScrollView::isNodeVisible(Node* node)
{
    const Point offset = this->getContentOffset();
    const Size  size   = this->getViewSize();
    const float   scale  = this->getZoomScale();
    
    Rect viewRect;
    
    viewRect = Rect(-offset.x/scale, -offset.y/scale, size.width/scale, size.height/scale); 
    
    return viewRect.intersectsRect(node->getBoundingBox());
}

void ScrollView::pause(Object* sender)
{
    _container->pause();

    auto& children = _container->getChildren();
    for(const auto &child : children) {
        child->pause();
    }
}

void ScrollView::resume(Object* sender)
{
    auto& children = _container->getChildren();
    for(const auto &child : children) {
        child->resume();
    }

    _container->resume();
}

bool ScrollView::isTouchEnabled() const
{
	return _touchListener != nullptr;
}

void ScrollView::setTouchEnabled(bool enabled)
{
    _eventDispatcher->removeEventListener(_touchListener);
    _touchListener = nullptr;

    if (enabled)
    {
        _touchListener = EventListenerTouchOneByOne::create();
        _touchListener->onTouchBegan = CC_CALLBACK_2(ScrollView::onTouchBegan, this);
        _touchListener->onTouchMoved = CC_CALLBACK_2(ScrollView::onTouchMoved, this);
        _touchListener->onTouchEnded = CC_CALLBACK_2(ScrollView::onTouchEnded, this);
        _touchListener->onTouchCancelled = CC_CALLBACK_2(ScrollView::onTouchCancelled, this);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
    }
    else
    {
        _dragging = false;
        _touchMoved = false;
        _touches.clear();
    }
}

void ScrollView::setContentOffset(Point offset, bool animated/* = false*/)
{
    if (animated)
    { //animate scrolling
        this->setContentOffsetInDuration(offset, BOUNCE_DURATION);
    } 
    else
    { //set the container position directly
        if (!_bounceable)
        {
            const Point minOffset = this->minContainerOffset();
            const Point maxOffset = this->maxContainerOffset();
            
            offset.x = MAX(minOffset.x, MIN(maxOffset.x, offset.x));
            offset.y = MAX(minOffset.y, MIN(maxOffset.y, offset.y));
        }

        _container->setPosition(offset);

        if (_delegate != NULL)
        {
            _delegate->scrollViewDidScroll(this);   
        }
    }
}

void ScrollView::setContentOffsetInDuration(Point offset, float dt)
{
    FiniteTimeAction *scroll, *expire;
    
    scroll = MoveTo::create(dt, offset);
    expire = CallFuncN::create(CC_CALLBACK_1(ScrollView::stoppedAnimatedScroll,this));
    _container->runAction(Sequence::create(scroll, expire, NULL));
    this->schedule(schedule_selector(ScrollView::performedAnimatedScroll));
}

Point ScrollView::getContentOffset()
{
    return _container->getPosition();
}

void ScrollView::setZoomScale(float s)
{
    if (_container->getScale() != s)
    {
        Point oldCenter, newCenter;
        Point center;
        
        if (_touchLength == 0.0f) 
        {
            center = Point(_viewSize.width*0.5f, _viewSize.height*0.5f);
            center = this->convertToWorldSpace(center);
        }
        else
        {
            center = _touchPoint;
        }
        
        oldCenter = _container->convertToNodeSpace(center);
        _container->setScale(MAX(_minScale, MIN(_maxScale, s)));
        newCenter = _container->convertToWorldSpace(oldCenter);
        
        const Point offset = center - newCenter;
        if (_delegate != NULL)
        {
            _delegate->scrollViewDidZoom(this);
        }
        this->setContentOffset(_container->getPosition() + offset);
    }
}

float ScrollView::getZoomScale()
{
    return _container->getScale();
}

void ScrollView::setZoomScale(float s, bool animated)
{
    if (animated)
    {
        this->setZoomScaleInDuration(s, BOUNCE_DURATION);
    }
    else
    {
        this->setZoomScale(s);
    }
}

void ScrollView::setZoomScaleInDuration(float s, float dt)
{
    if (dt > 0)
    {
        if (_container->getScale() != s)
        {
            ActionTween *scaleAction;
            scaleAction = ActionTween::create(dt, "zoomScale", _container->getScale(), s);
            this->runAction(scaleAction);
        }
    }
    else
    {
        this->setZoomScale(s);
    }
}

void ScrollView::setViewSize(Size size)
{
    _viewSize = size;
    Layer::setContentSize(size);
}

Node * ScrollView::getContainer()
{
    return this->_container;
}

void ScrollView::setContainer(Node * pContainer)
{
    // Make sure that '_container' has a non-NULL value since there are
    // lots of logic that use '_container'.
    if (NULL == pContainer)
        return;

    this->removeAllChildrenWithCleanup(true);
    this->_container = pContainer;

    this->_container->ignoreAnchorPointForPosition(false);
    this->_container->setAnchorPoint(Point(0.0f, 0.0f));

    this->addChild(this->_container);

    this->setViewSize(this->_viewSize);
}

void ScrollView::relocateContainer(bool animated)
{
    Point oldPoint, min, max;
    float newX, newY;
    
    min = this->minContainerOffset();
    max = this->maxContainerOffset();
    
    oldPoint = _container->getPosition();

    newX     = oldPoint.x;
    newY     = oldPoint.y;
    if (_direction == Direction::BOTH || _direction == Direction::HORIZONTAL)
    {
        newX     = MAX(newX, min.x);
        newX     = MIN(newX, max.x);
    }

    if (_direction == Direction::BOTH || _direction == Direction::VERTICAL)
    {
        newY     = MIN(newY, max.y);
        newY     = MAX(newY, min.y);
    }

    if (newY != oldPoint.y || newX != oldPoint.x)
    {
        this->setContentOffset(Point(newX, newY), animated);
    }
}

Point ScrollView::maxContainerOffset()
{
    return Point(0.0f, 0.0f);
}

Point ScrollView::minContainerOffset()
{
    return Point(_viewSize.width - _container->getContentSize().width*_container->getScaleX(), 
               _viewSize.height - _container->getContentSize().height*_container->getScaleY());
}

void ScrollView::deaccelerateScrolling(float dt)
{
    if (_dragging)
    {
        this->unschedule(schedule_selector(ScrollView::deaccelerateScrolling));
        return;
    }
    
    float newX, newY;
    Point maxInset, minInset;
    
    _container->setPosition(_container->getPosition() + _scrollDistance);
    
    if (_bounceable)
    {
        maxInset = _maxInset;
        minInset = _minInset;
    }
    else
    {
        maxInset = this->maxContainerOffset();
        minInset = this->minContainerOffset();
    }
    
    //check to see if offset lies within the inset bounds
    newX     = MIN(_container->getPosition().x, maxInset.x);
    newX     = MAX(newX, minInset.x);
    newY     = MIN(_container->getPosition().y, maxInset.y);
    newY     = MAX(newY, minInset.y);
    
    newX = _container->getPosition().x;
    newY = _container->getPosition().y;
    
    _scrollDistance     = _scrollDistance - Point(newX - _container->getPosition().x, newY - _container->getPosition().y);
    _scrollDistance     = _scrollDistance * SCROLL_DEACCEL_RATE;
    this->setContentOffset(Point(newX,newY));
    
    if ((fabsf(_scrollDistance.x) <= SCROLL_DEACCEL_DIST &&
         fabsf(_scrollDistance.y) <= SCROLL_DEACCEL_DIST) ||
        newY > maxInset.y || newY < minInset.y ||
        newX > maxInset.x || newX < minInset.x ||
        newX == maxInset.x || newX == minInset.x ||
        newY == maxInset.y || newY == minInset.y)
    {
        this->unschedule(schedule_selector(ScrollView::deaccelerateScrolling));
        this->relocateContainer(true);
    }
}

void ScrollView::stoppedAnimatedScroll(Node * node)
{
    this->unschedule(schedule_selector(ScrollView::performedAnimatedScroll));
    // After the animation stopped, "scrollViewDidScroll" should be invoked, this could fix the bug of lack of tableview cells.
    if (_delegate != NULL)
    {
        _delegate->scrollViewDidScroll(this);
    }
}

void ScrollView::performedAnimatedScroll(float dt)
{
    if (_dragging)
    {
        this->unschedule(schedule_selector(ScrollView::performedAnimatedScroll));
        return;
    }

    if (_delegate != NULL)
    {
        _delegate->scrollViewDidScroll(this);
    }
}


const Size& ScrollView::getContentSize() const
{
	return _container->getContentSize();
}

void ScrollView::setContentSize(const Size & size)
{
    if (this->getContainer() != NULL)
    {
        this->getContainer()->setContentSize(size);
		this->updateInset();
    }
}

void ScrollView::updateInset()
{
	if (this->getContainer() != NULL)
	{
		_maxInset = this->maxContainerOffset();
		_maxInset = Point(_maxInset.x + _viewSize.width * INSET_RATIO,
			_maxInset.y + _viewSize.height * INSET_RATIO);
		_minInset = this->minContainerOffset();
		_minInset = Point(_minInset.x - _viewSize.width * INSET_RATIO,
			_minInset.y - _viewSize.height * INSET_RATIO);
	}
}

/**
 * make sure all children go to the container
 */
void ScrollView::addChild(Node * child, int zOrder, int tag)
{
    if (_container != child) {
        _container->addChild(child, zOrder, tag);
    } else {
        Layer::addChild(child, zOrder, tag);
    }
}

void ScrollView::beforeDraw()
{
    _beforeDrawCommand.init(_globalZOrder);
    _beforeDrawCommand.func = CC_CALLBACK_0(ScrollView::onBeforeDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_beforeDrawCommand);
}

/**
 * clip this view so that outside of the visible bounds can be hidden.
 */
void ScrollView::onBeforeDraw()
{
    if (_clippingToBounds)
    {
		_scissorRestored = false;
        Rect frame = getViewRect();
        auto glview = Director::getInstance()->getOpenGLView();

        if (glview->isScissorEnabled()) {
            _scissorRestored = true;
            _parentScissorRect = glview->getScissorRect();
            //set the intersection of _parentScissorRect and frame as the new scissor rect
            if (frame.intersectsRect(_parentScissorRect)) {
                float x = MAX(frame.origin.x, _parentScissorRect.origin.x);
                float y = MAX(frame.origin.y, _parentScissorRect.origin.y);
                float xx = MIN(frame.origin.x+frame.size.width, _parentScissorRect.origin.x+_parentScissorRect.size.width);
                float yy = MIN(frame.origin.y+frame.size.height, _parentScissorRect.origin.y+_parentScissorRect.size.height);
                glview->setScissorInPoints(x, y, xx-x, yy-y);
            }
        }
        else {
            glEnable(GL_SCISSOR_TEST);
            glview->setScissorInPoints(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height);
        }
    }
}

void ScrollView::afterDraw()
{
    _afterDrawCommand.init(_globalZOrder);
    _afterDrawCommand.func = CC_CALLBACK_0(ScrollView::onAfterDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_afterDrawCommand);
}

/**
 * retract what's done in beforeDraw so that there's no side effect to
 * other nodes.
 */
void ScrollView::onAfterDraw()
{
    if (_clippingToBounds)
    {
        if (_scissorRestored) {//restore the parent's scissor rect
            auto glview = Director::getInstance()->getOpenGLView();

            glview->setScissorInPoints(_parentScissorRect.origin.x, _parentScissorRect.origin.y, _parentScissorRect.size.width, _parentScissorRect.size.height);
        }
        else {
            glDisable(GL_SCISSOR_TEST);
        }
    }
}

void ScrollView::visit()
{
	// quick return if not visible
	if (!isVisible())
    {
		return;
    }

	kmGLPushMatrix();

	this->transform();
    this->beforeDraw();

	if (!_children.empty())
    {
		int i=0;
		
		// draw children zOrder < 0
		for( ; i < _children.size(); i++ )
        {
			Node *child = _children.at(i);
			if ( child->getLocalZOrder() < 0 )
            {
				child->visit();
			}
            else
            {
				break;
            }
		}
		
		// this draw
		this->draw();
        
		// draw children zOrder >= 0
		for( ; i < _children.size(); i++ )
        {
			Node *child = _children.at(i);
			child->visit();
		}
        
	}
    else
    {
		this->draw();
    }

    this->afterDraw();

	kmGLPopMatrix();
}

bool ScrollView::onTouchBegan(Touch* touch, Event* event)
{
    if (!this->isVisible())
    {
        return false;
    }
    
    Rect frame = getViewRect();

    //dispatcher does not know about clipping. reject touches outside visible bounds.
    if (_touches.size() > 2 ||
        _touchMoved          ||
        !frame.containsPoint(touch->getLocation()))
    {
        return false;
    }

    if (std::find(_touches.begin(), _touches.end(), touch) == _touches.end())
    {
        _touches.push_back(touch);
    }

    if (_touches.size() == 1)
    { // scrolling
        _touchPoint     = this->convertTouchToNodeSpace(touch);
        _touchMoved     = false;
        _dragging     = true; //dragging started
        _scrollDistance = Point(0.0f, 0.0f);
        _touchLength    = 0.0f;
    }
    else if (_touches.size() == 2)
    {
        _touchPoint = (this->convertTouchToNodeSpace(_touches[0]).getMidpoint(
                        this->convertTouchToNodeSpace(_touches[1])));
        
        _touchLength = _container->convertTouchToNodeSpace(_touches[0]).getDistance(
                       _container->convertTouchToNodeSpace(_touches[1]));
        
        _dragging  = false;
    } 
    return true;
}

void ScrollView::onTouchMoved(Touch* touch, Event* event)
{
    if (!this->isVisible())
    {
        return;
    }

    if (std::find(_touches.begin(), _touches.end(), touch) != _touches.end())
    {
        if (_touches.size() == 1 && _dragging)
        { // scrolling
            Point moveDistance, newPoint, maxInset, minInset;
            Rect  frame;
            float newX, newY;
            
            frame = getViewRect();

            newPoint     = this->convertTouchToNodeSpace(_touches[0]);
            moveDistance = newPoint - _touchPoint;
            
            float dis = 0.0f;
            if (_direction == Direction::VERTICAL)
            {
                dis = moveDistance.y;
            }
            else if (_direction == Direction::HORIZONTAL)
            {
                dis = moveDistance.x;
            }
            else
            {
                dis = sqrtf(moveDistance.x*moveDistance.x + moveDistance.y*moveDistance.y);
            }

            if (!_touchMoved && fabs(convertDistanceFromPointToInch(dis)) < MOVE_INCH )
            {
                //CCLOG("Invalid movement, distance = [%f, %f], disInch = %f", moveDistance.x, moveDistance.y);
                return;
            }
            
            if (!_touchMoved)
            {
                moveDistance = Point::ZERO;
            }
            
            _touchPoint = newPoint;
            _touchMoved = true;
            
            if (frame.containsPoint(this->convertToWorldSpace(newPoint)))
            {
                switch (_direction)
                {
                    case Direction::VERTICAL:
                        moveDistance = Point(0.0f, moveDistance.y);
                        break;
                    case Direction::HORIZONTAL:
                        moveDistance = Point(moveDistance.x, 0.0f);
                        break;
                    default:
                        break;
                }
                
                maxInset = _maxInset;
                minInset = _minInset;

                newX     = _container->getPosition().x + moveDistance.x;
                newY     = _container->getPosition().y + moveDistance.y;

                _scrollDistance = moveDistance;
                this->setContentOffset(Point(newX, newY));
            }
        }
        else if (_touches.size() == 2 && !_dragging)
        {
            const float len = _container->convertTouchToNodeSpace(_touches[0]).getDistance(
                                            _container->convertTouchToNodeSpace(_touches[1]));
            this->setZoomScale(this->getZoomScale()*len/_touchLength);
        }
    }
}

void ScrollView::onTouchEnded(Touch* touch, Event* event)
{
    if (!this->isVisible())
    {
        return;
    }
    
    auto touchIter = std::find(_touches.begin(), _touches.end(), touch);
    
    if (touchIter != _touches.end())
    {
        if (_touches.size() == 1 && _touchMoved)
        {
            this->schedule(schedule_selector(ScrollView::deaccelerateScrolling));
        }
        _touches.erase(touchIter);
    } 

    if (_touches.size() == 0)
    {
        _dragging = false;    
        _touchMoved = false;
    }
}

void ScrollView::onTouchCancelled(Touch* touch, Event* event)
{
    if (!this->isVisible())
    {
        return;
    }
    
    auto touchIter = std::find(_touches.begin(), _touches.end(), touch);
    _touches.erase(touchIter);
    
    if (_touches.size() == 0)
    {
        _dragging = false;    
        _touchMoved = false;
    }
}

Rect ScrollView::getViewRect()
{
    Point screenPos = this->convertToWorldSpace(Point::ZERO);
    
    float scaleX = this->getScaleX();
    float scaleY = this->getScaleY();
    
    for (Node *p = _parent; p != NULL; p = p->getParent()) {
        scaleX *= p->getScaleX();
        scaleY *= p->getScaleY();
    }

    // Support negative scaling. Not doing so causes intersectsRect calls
    // (eg: to check if the touch was within the bounds) to return false.
    // Note, Node::getScale will assert if X and Y scales are different.
    if(scaleX<0.f) {
        screenPos.x += _viewSize.width*scaleX;
        scaleX = -scaleX;
    }
    if(scaleY<0.f) {
        screenPos.y += _viewSize.height*scaleY;
        scaleY = -scaleY;
    }

    return Rect(screenPos.x, screenPos.y, _viewSize.width*scaleX, _viewSize.height*scaleY);
}
NS_CC_EXT_END
