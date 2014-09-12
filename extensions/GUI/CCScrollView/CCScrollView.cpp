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
#include "platform/CCDevice.h"
#include "2d/CCActionInstant.h"
#include "2d/CCActionInterval.h"
#include "2d/CCActionTween.h"
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"
#include "renderer/CCRenderer.h"

#include <algorithm>

NS_CC_EXT_BEGIN

#define SCROLL_DEACCEL_RATE  0.95f
#define SCROLL_DEACCEL_DIST  1.0f
#define BOUNCE_DURATION      0.15f
#define INSET_RATIO          0.2f
#define MOVE_INCH            7.0f/160.0f
#define BOUNCE_BACK_FACTOR   0.35f

static float convertDistanceFromPointToInch(float pointDis)
{
    auto glview = Director::getInstance()->getOpenGLView();
    float factor = ( glview->getScaleX() + glview->getScaleY() ) / 2;
    return pointDis * factor / Device::getDPI();
}


ScrollView::ScrollView()
: _delegate(nullptr)
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
, _scissorRestored(false)
{

}

ScrollView::~ScrollView()
{

}

ScrollView* ScrollView::create(Size size, Node* container/* = nullptr*/)
{
    ScrollView* pRet = new (std::nothrow) ScrollView();
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
    ScrollView* pRet = new (std::nothrow) ScrollView();
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


bool ScrollView::initWithViewSize(Size size, Node *container/* = nullptr*/)
{
    if (Layer::init())
    {
        _container = container;
        
        if (!this->_container)
        {
            _container = Layer::create();
            _container->ignoreAnchorPointForPosition(false);
            _container->setAnchorPoint(Vec2(0.0f, 0.0f));
        }

        this->setViewSize(size);

        setTouchEnabled(true);
        
        _touches.reserve(EventTouch::MAX_TOUCHES);
        
        _delegate = nullptr;
        _bounceable = true;
        _clippingToBounds = true;
        //_container->setContentSize(Size::ZERO);
        _direction  = Direction::BOTH;
        _container->setPosition(0.0f, 0.0f);
        _touchLength = 0.0f;
        
        this->addChild(_container);
        _minScale = _maxScale = 1.0f;

        
        return true;
    }
    return false;
}

bool ScrollView::init()
{
    return this->initWithViewSize(Size(200, 200), nullptr);
}

bool ScrollView::isNodeVisible(Node* node)
{
    const Vec2 offset = this->getContentOffset();
    const Size  size   = this->getViewSize();
    const float   scale  = this->getZoomScale();
    
    Rect viewRect;
    
    viewRect = Rect(-offset.x/scale, -offset.y/scale, size.width/scale, size.height/scale); 
    
    return viewRect.intersectsRect(node->getBoundingBox());
}

void ScrollView::pause(Ref* sender)
{
    _container->pause();

    auto& children = _container->getChildren();
    for(const auto &child : children) {
        child->pause();
    }
}

void ScrollView::resume(Ref* sender)
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

void ScrollView::setContentOffset(Vec2 offset, bool animated/* = false*/)
{
    if (animated)
    { //animate scrolling
        this->setContentOffsetInDuration(offset, BOUNCE_DURATION);
    } 
    else
    { //set the container position directly
        if (!_bounceable)
        {
            const Vec2 minOffset = this->minContainerOffset();
            const Vec2 maxOffset = this->maxContainerOffset();
            
            offset.x = MAX(minOffset.x, MIN(maxOffset.x, offset.x));
            offset.y = MAX(minOffset.y, MIN(maxOffset.y, offset.y));
        }

        _container->setPosition(offset);

        if (_delegate != nullptr)
        {
            _delegate->scrollViewDidScroll(this);   
        }
    }
}

void ScrollView::setContentOffsetInDuration(Vec2 offset, float dt)
{
    FiniteTimeAction *scroll, *expire;
    
    scroll = MoveTo::create(dt, offset);
    expire = CallFuncN::create(CC_CALLBACK_1(ScrollView::stoppedAnimatedScroll,this));
    _container->runAction(Sequence::create(scroll, expire, nullptr));
    this->schedule(schedule_selector(ScrollView::performedAnimatedScroll));
}

Vec2 ScrollView::getContentOffset()
{
    return _container->getPosition();
}

void ScrollView::setZoomScale(float s)
{
    if (_container->getScale() != s)
    {
        Vec2 oldCenter, newCenter;
        Vec2 center;
        
        if (_touchLength == 0.0f) 
        {
            center = Vec2(_viewSize.width*0.5f, _viewSize.height*0.5f);
            center = this->convertToWorldSpace(center);
        }
        else
        {
            center = _touchPoint;
        }
        
        oldCenter = _container->convertToNodeSpace(center);
        _container->setScale(MAX(_minScale, MIN(_maxScale, s)));
        newCenter = _container->convertToWorldSpace(oldCenter);
        
        const Vec2 offset = center - newCenter;
        if (_delegate != nullptr)
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

void ScrollView::updateTweenAction(float value, const std::string& key)
{
    this->setZoomScale(value);
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
    // Make sure that '_container' has a non-nullptr value since there are
    // lots of logic that use '_container'.
    if (nullptr == pContainer)
        return;

    this->removeAllChildrenWithCleanup(true);
    this->_container = pContainer;

    this->_container->ignoreAnchorPointForPosition(false);
    this->_container->setAnchorPoint(Vec2(0.0f, 0.0f));

    this->addChild(this->_container);

    this->setViewSize(this->_viewSize);
}

bool ScrollView::hasVisibleParents() const
{
    auto parent = this->getParent();
    for( auto c = parent; c != nullptr; c = c->getParent() )
    {
        if( !c->isVisible() )
        {
            return false;
        }
    }
    return true;
}

void ScrollView::relocateContainer(bool animated)
{
    Vec2 oldPoint, min, max;
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
        this->setContentOffset(Vec2(newX, newY), animated);
    }
}

Vec2 ScrollView::maxContainerOffset()
{
    return Vec2(0.0f, 0.0f);
}

Vec2 ScrollView::minContainerOffset()
{
    return Vec2(_viewSize.width - _container->getContentSize().width*_container->getScaleX(), 
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
    Vec2 maxInset, minInset;
    
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
    
    newX = _container->getPosition().x;
    newY = _container->getPosition().y;
    
    _scrollDistance     = _scrollDistance * SCROLL_DEACCEL_RATE;
    this->setContentOffset(Vec2(newX,newY));
    
    if ((fabsf(_scrollDistance.x) <= SCROLL_DEACCEL_DIST &&
         fabsf(_scrollDistance.y) <= SCROLL_DEACCEL_DIST) ||
        newY >= maxInset.y || newY <= minInset.y ||
        newX >= maxInset.x || newX <= minInset.x)
    {
        this->unschedule(schedule_selector(ScrollView::deaccelerateScrolling));
        this->relocateContainer(true);
    }
}

void ScrollView::stoppedAnimatedScroll(Node * node)
{
    this->unschedule(schedule_selector(ScrollView::performedAnimatedScroll));
    // After the animation stopped, "scrollViewDidScroll" should be invoked, this could fix the bug of lack of tableview cells.
    if (_delegate != nullptr)
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

    if (_delegate != nullptr)
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
    if (this->getContainer() != nullptr)
    {
        this->getContainer()->setContentSize(size);
		this->updateInset();
    }
}

void ScrollView::updateInset()
{
	if (this->getContainer() != nullptr)
	{
		_maxInset = this->maxContainerOffset();
		_maxInset = Vec2(_maxInset.x + _viewSize.width * INSET_RATIO,
			_maxInset.y + _viewSize.height * INSET_RATIO);
		_minInset = this->minContainerOffset();
		_minInset = Vec2(_minInset.x - _viewSize.width * INSET_RATIO,
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

void ScrollView::addChild(Node * child, int zOrder, const std::string &name)
{
    if (_container != child)
    {
        _container->addChild(child, zOrder, name);
    }
    else
    {
        Layer::addChild(child, zOrder, name);
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

void ScrollView::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    // quick return if not visible
    if (!isVisible())
    {
        return;
    }

    uint32_t flags = processParentFlags(parentTransform, parentFlags);

    // IMPORTANT:
    // To ease the migration to v3.0, we still support the Mat4 stack,
    // but it is deprecated and your code should not rely on it
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);

    this->beforeDraw();
    bool visibleByCamera = isVisitableByVisitingCamera();

    if (!_children.empty())
    {
        int i=0;
		
		// draw children zOrder < 0
        for( ; i < _children.size(); i++ )
        {
            Node *child = _children.at(i);
            if ( child->getLocalZOrder() < 0 )
            {
                child->visit(renderer, _modelViewTransform, flags);
            }
            else
            {
                break;
            }
        }
		
		// this draw
        if (visibleByCamera)
            this->draw(renderer, _modelViewTransform, flags);
        
        // draw children zOrder >= 0
        for( ; i < _children.size(); i++ )
        {
			Node *child = _children.at(i);
			child->visit(renderer, _modelViewTransform, flags);
        }
    }
    else if (visibleByCamera)
    {
        this->draw(renderer, _modelViewTransform, flags);
    }

    this->afterDraw();

    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

bool ScrollView::onTouchBegan(Touch* touch, Event* event)
{
    if (!this->isVisible() || !this->hasVisibleParents())
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
        _scrollDistance = Vec2(0.0f, 0.0f);
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
            Vec2 moveDistance, newPoint;
            Rect  frame;
            float newX, newY;
            
            frame = getViewRect();

            newPoint     = this->convertTouchToNodeSpace(_touches[0]);
            moveDistance = newPoint - _touchPoint;
            
            float dis = 0.0f;
            if (_direction == Direction::VERTICAL)
            {
                dis = moveDistance.y;
                float pos = _container->getPosition().y;
                if (!(minContainerOffset().y <= pos && pos <= maxContainerOffset().y)) {
                    moveDistance.y *= BOUNCE_BACK_FACTOR;
                }
            }
            else if (_direction == Direction::HORIZONTAL)
            {
                dis = moveDistance.x;
                float pos = _container->getPosition().x;
                if (!(minContainerOffset().x <= pos && pos <= maxContainerOffset().x)) {
                    moveDistance.x *= BOUNCE_BACK_FACTOR;
                }
            }
            else
            {
                dis = sqrtf(moveDistance.x*moveDistance.x + moveDistance.y*moveDistance.y);
                
                float pos = _container->getPosition().y;
                if (!(minContainerOffset().y <= pos && pos <= maxContainerOffset().y)) {
                    moveDistance.y *= BOUNCE_BACK_FACTOR;
                }
                
                pos = _container->getPosition().x;
                if (!(minContainerOffset().x <= pos && pos <= maxContainerOffset().x)) {
                    moveDistance.x *= BOUNCE_BACK_FACTOR;
                }
            }

            if (!_touchMoved && fabs(convertDistanceFromPointToInch(dis)) < MOVE_INCH )
            {
                //CCLOG("Invalid movement, distance = [%f, %f], disInch = %f", moveDistance.x, moveDistance.y);
                return;
            }
            
            if (!_touchMoved)
            {
                moveDistance = Vec2::ZERO;
            }
            
            _touchPoint = newPoint;
            _touchMoved = true;
            
            if (_dragging)
            {
                switch (_direction)
                {
                    case Direction::VERTICAL:
                        moveDistance = Vec2(0.0f, moveDistance.y);
                        break;
                    case Direction::HORIZONTAL:
                        moveDistance = Vec2(moveDistance.x, 0.0f);
                        break;
                    default:
                        break;
                }

                newX     = _container->getPosition().x + moveDistance.x;
                newY     = _container->getPosition().y + moveDistance.y;

                _scrollDistance = moveDistance;
                this->setContentOffset(Vec2(newX, newY));
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
    Vec2 screenPos = this->convertToWorldSpace(Vec2::ZERO);
    
    float scaleX = this->getScaleX();
    float scaleY = this->getScaleY();
    
    for (Node *p = _parent; p != nullptr; p = p->getParent()) {
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
