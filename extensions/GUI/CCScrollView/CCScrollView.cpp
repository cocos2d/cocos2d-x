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

NS_CC_EXT_BEGIN

#define SCROLL_DEACCEL_RATE  0.95f
#define SCROLL_DEACCEL_DIST  1.0f
#define BOUNCE_DURATION      0.15f
#define INSET_RATIO          0.2f
#define MOVE_INCH            7.0f/160.0f

static float convertDistanceFromPointToInch(float pointDis)
{
    float factor = ( EGLView::sharedOpenGLView()->getScaleX() + EGLView::sharedOpenGLView()->getScaleY() ) / 2;
    return pointDis * factor / Device::getDPI();
}


ScrollView::ScrollView()
: _zoomScale(0.0f)
, _minZoomScale(0.0f)
, _maxZoomScale(0.0f)
, _delegate(NULL)
, _direction(kScrollViewDirectionBoth)
, _dragging(false)
, _container(NULL)
, _touchMoved(false)
, _bounceable(false)
, _clippingToBounds(false)
, _touchLength(0.0f)
, _touches(NULL)
, _minScale(0.0f)
, _maxScale(0.0f)
{

}

ScrollView::~ScrollView()
{
    _touches->release();
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
            this->_container->ignoreAnchorPointForPosition(false);
            this->_container->setAnchorPoint(ccp(0.0f, 0.0f));
        }

        this->setViewSize(size);

        setTouchEnabled(true);
        _touches = new Array();
        _delegate = NULL;
        _bounceable = true;
        _clippingToBounds = true;
        //_container->setContentSize(SizeZero);
        _direction  = kScrollViewDirectionBoth;
        _container->setPosition(ccp(0.0f, 0.0f));
        _touchLength = 0.0f;
        
        this->addChild(_container);
        _minScale = _maxScale = 1.0f;
        return true;
    }
    return false;
}

bool ScrollView::init()
{
    return this->initWithViewSize(CCSizeMake(200, 200), NULL);
}

void ScrollView::registerWithTouchDispatcher()
{
    Director::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, Layer::getTouchPriority(), false);
}

bool ScrollView::isNodeVisible(Node* node)
{
    const Point offset = this->getContentOffset();
    const Size  size   = this->getViewSize();
    const float   scale  = this->getZoomScale();
    
    Rect viewRect;
    
    viewRect = CCRectMake(-offset.x/scale, -offset.y/scale, size.width/scale, size.height/scale); 
    
    return viewRect.intersectsRect(node->boundingBox());
}

void ScrollView::pause(Object* sender)
{
    _container->pauseSchedulerAndActions();

    Object* pObj = NULL;
    Array* pChildren = _container->getChildren();

    CCARRAY_FOREACH(pChildren, pObj)
    {
        Node* pChild = (Node*)pObj;
        pChild->pauseSchedulerAndActions();
    }
}

void ScrollView::resume(Object* sender)
{
    Object* pObj = NULL;
    Array* pChildren = _container->getChildren();

    CCARRAY_FOREACH(pChildren, pObj)
    {
        Node* pChild = (Node*)pObj;
        pChild->resumeSchedulerAndActions();
    }

    _container->resumeSchedulerAndActions();
}

void ScrollView::setTouchEnabled(bool e)
{
    Layer::setTouchEnabled(e);
    if (!e)
    {
        _dragging = false;
        _touchMoved = false;
        _touches->removeAllObjects();
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
    expire = CallFuncN::create(this, callfuncN_selector(ScrollView::stoppedAnimatedScroll));
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
            center = ccp(_viewSize.width*0.5f, _viewSize.height*0.5f);
            center = this->convertToWorldSpace(center);
        }
        else
        {
            center = _touchPoint;
        }
        
        oldCenter = _container->convertToNodeSpace(center);
        _container->setScale(MAX(_minScale, MIN(_maxScale, s)));
        newCenter = _container->convertToWorldSpace(oldCenter);
        
        const Point offset = ccpSub(center, newCenter);
        if (_delegate != NULL)
        {
            _delegate->scrollViewDidZoom(this);
        }
        this->setContentOffset(ccpAdd(_container->getPosition(),offset));
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
    this->_container->setAnchorPoint(ccp(0.0f, 0.0f));

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
    if (_direction == kScrollViewDirectionBoth || _direction == kScrollViewDirectionHorizontal)
    {
        newX     = MAX(newX, min.x);
        newX     = MIN(newX, max.x);
    }

    if (_direction == kScrollViewDirectionBoth || _direction == kScrollViewDirectionVertical)
    {
        newY     = MIN(newY, max.y);
        newY     = MAX(newY, min.y);
    }

    if (newY != oldPoint.y || newX != oldPoint.x)
    {
        this->setContentOffset(ccp(newX, newY), animated);
    }
}

Point ScrollView::maxContainerOffset()
{
    return ccp(0.0f, 0.0f);
}

Point ScrollView::minContainerOffset()
{
    return ccp(_viewSize.width - _container->getContentSize().width*_container->getScaleX(), 
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
    
    _container->setPosition(ccpAdd(_container->getPosition(), _scrollDistance));
    
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
    
    _scrollDistance     = ccpSub(_scrollDistance, ccp(newX - _container->getPosition().x, newY - _container->getPosition().y));
    _scrollDistance     = ccpMult(_scrollDistance, SCROLL_DEACCEL_RATE);
    this->setContentOffset(ccp(newX,newY));
    
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
		_maxInset = ccp(_maxInset.x + _viewSize.width * INSET_RATIO,
			_maxInset.y + _viewSize.height * INSET_RATIO);
		_minInset = this->minContainerOffset();
		_minInset = ccp(_minInset.x - _viewSize.width * INSET_RATIO,
			_minInset.y - _viewSize.height * INSET_RATIO);
	}
}

/**
 * make sure all children go to the container
 */
void ScrollView::addChild(Node * child, int zOrder, int tag)
{
    child->ignoreAnchorPointForPosition(false);
    child->setAnchorPoint(ccp(0.0f, 0.0f));
    if (_container != child) {
        _container->addChild(child, zOrder, tag);
    } else {
        Layer::addChild(child, zOrder, tag);
    }
}

void ScrollView::addChild(Node * child, int zOrder)
{
    this->addChild(child, zOrder, child->getTag());
}

void ScrollView::addChild(Node * child)
{
    this->addChild(child, child->getZOrder(), child->getTag());
}

/**
 * clip this view so that outside of the visible bounds can be hidden.
 */
void ScrollView::beforeDraw()
{
    if (_clippingToBounds)
    {
		_scissorRestored = false;
        Rect frame = getViewRect();
        if (EGLView::sharedOpenGLView()->isScissorEnabled()) {
            _scissorRestored = true;
            _parentScissorRect = EGLView::sharedOpenGLView()->getScissorRect();
            //set the intersection of _parentScissorRect and frame as the new scissor rect
            if (frame.intersectsRect(_parentScissorRect)) {
                float x = MAX(frame.origin.x, _parentScissorRect.origin.x);
                float y = MAX(frame.origin.y, _parentScissorRect.origin.y);
                float xx = MIN(frame.origin.x+frame.size.width, _parentScissorRect.origin.x+_parentScissorRect.size.width);
                float yy = MIN(frame.origin.y+frame.size.height, _parentScissorRect.origin.y+_parentScissorRect.size.height);
                EGLView::sharedOpenGLView()->setScissorInPoints(x, y, xx-x, yy-y);
            }
        }
        else {
            glEnable(GL_SCISSOR_TEST);
            EGLView::sharedOpenGLView()->setScissorInPoints(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height);
        }
    }
}

/**
 * retract what's done in beforeDraw so that there's no side effect to
 * other nodes.
 */
void ScrollView::afterDraw()
{
    if (_clippingToBounds)
    {
        if (_scissorRestored) {//restore the parent's scissor rect
            EGLView::sharedOpenGLView()->setScissorInPoints(_parentScissorRect.origin.x, _parentScissorRect.origin.y, _parentScissorRect.size.width, _parentScissorRect.size.height);
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
	
    if (_grid && _grid->isActive())
    {
        _grid->beforeDraw();
        this->transformAncestors();
    }

	this->transform();
    this->beforeDraw();

	if(_children)
    {
		ccArray *arrayData = _children->data;
		unsigned int i=0;
		
		// draw children zOrder < 0
		for( ; i < arrayData->num; i++ )
        {
			Node *child =  (Node*)arrayData->arr[i];
			if ( child->getZOrder() < 0 )
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
		for( ; i < arrayData->num; i++ )
        {
			Node* child = (Node*)arrayData->arr[i];
			child->visit();
		}
        
	}
    else
    {
		this->draw();
    }

    this->afterDraw();
	if ( _grid && _grid->isActive())
    {
		_grid->afterDraw(this);
    }

	kmGLPopMatrix();
}

bool ScrollView::ccTouchBegan(Touch* touch, Event* event)
{
    if (!this->isVisible())
    {
        return false;
    }
    
    Rect frame = getViewRect();

    //dispatcher does not know about clipping. reject touches outside visible bounds.
    if (_touches->count() > 2 ||
        _touchMoved          ||
        !frame.containsPoint(_container->convertToWorldSpace(_container->convertTouchToNodeSpace(touch))))
    {
        return false;
    }

    if (!_touches->containsObject(touch))
    {
        _touches->addObject(touch);
    }

    if (_touches->count() == 1)
    { // scrolling
        _touchPoint     = this->convertTouchToNodeSpace(touch);
        _touchMoved     = false;
        _dragging     = true; //dragging started
        _scrollDistance = ccp(0.0f, 0.0f);
        _touchLength    = 0.0f;
    }
    else if (_touches->count() == 2)
    {
        _touchPoint  = ccpMidpoint(this->convertTouchToNodeSpace((Touch*)_touches->objectAtIndex(0)),
                                   this->convertTouchToNodeSpace((Touch*)_touches->objectAtIndex(1)));
        _touchLength = ccpDistance(_container->convertTouchToNodeSpace((Touch*)_touches->objectAtIndex(0)),
                                   _container->convertTouchToNodeSpace((Touch*)_touches->objectAtIndex(1)));
        _dragging  = false;
    } 
    return true;
}

void ScrollView::ccTouchMoved(Touch* touch, Event* event)
{
    if (!this->isVisible())
    {
        return;
    }

    if (_touches->containsObject(touch))
    {
        if (_touches->count() == 1 && _dragging)
        { // scrolling
            Point moveDistance, newPoint, maxInset, minInset;
            Rect  frame;
            float newX, newY;
            
            frame = getViewRect();

            newPoint     = this->convertTouchToNodeSpace((Touch*)_touches->objectAtIndex(0));
            moveDistance = ccpSub(newPoint, _touchPoint);
            
            float dis = 0.0f;
            if (_direction == kScrollViewDirectionVertical)
            {
                dis = moveDistance.y;
            }
            else if (_direction == kScrollViewDirectionHorizontal)
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
                moveDistance = PointZero;
            }
            
            _touchPoint = newPoint;
            _touchMoved = true;
            
            if (frame.containsPoint(this->convertToWorldSpace(newPoint)))
            {
                switch (_direction)
                {
                    case kScrollViewDirectionVertical:
                        moveDistance = ccp(0.0f, moveDistance.y);
                        break;
                    case kScrollViewDirectionHorizontal:
                        moveDistance = ccp(moveDistance.x, 0.0f);
                        break;
                    default:
                        break;
                }
                
                maxInset = _maxInset;
                minInset = _minInset;

                newX     = _container->getPosition().x + moveDistance.x;
                newY     = _container->getPosition().y + moveDistance.y;

                _scrollDistance = moveDistance;
                this->setContentOffset(ccp(newX, newY));
            }
        }
        else if (_touches->count() == 2 && !_dragging)
        {
            const float len = ccpDistance(_container->convertTouchToNodeSpace((Touch*)_touches->objectAtIndex(0)),
                                            _container->convertTouchToNodeSpace((Touch*)_touches->objectAtIndex(1)));
            this->setZoomScale(this->getZoomScale()*len/_touchLength);
        }
    }
}

void ScrollView::ccTouchEnded(Touch* touch, Event* event)
{
    if (!this->isVisible())
    {
        return;
    }
    if (_touches->containsObject(touch))
    {
        if (_touches->count() == 1 && _touchMoved)
        {
            this->schedule(schedule_selector(ScrollView::deaccelerateScrolling));
        }
        _touches->removeObject(touch);
    } 

    if (_touches->count() == 0)
    {
        _dragging = false;    
        _touchMoved = false;
    }
}

void ScrollView::ccTouchCancelled(Touch* touch, Event* event)
{
    if (!this->isVisible())
    {
        return;
    }
    _touches->removeObject(touch); 
    if (_touches->count() == 0)
    {
        _dragging = false;    
        _touchMoved = false;
    }
}

Rect ScrollView::getViewRect()
{
    Point screenPos = this->convertToWorldSpace(PointZero);
    
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

    return CCRectMake(screenPos.x, screenPos.y, _viewSize.width*scaleX, _viewSize.height*scaleY);
}
NS_CC_EXT_END
