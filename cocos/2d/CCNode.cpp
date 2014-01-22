/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Valentin Milea
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

#include "CCNode.h"

#include <algorithm>

#include "CCString.h"
#include "ccCArray.h"
#include "TransformUtils.h"
#include "CCGrid.h"
#include "CCDirector.h"
#include "CCScheduler.h"
#include "CCTouch.h"
#include "CCActionManager.h"
#include "CCScriptSupport.h"
#include "CCGLProgram.h"
#include "CCEventDispatcher.h"
#include "CCEvent.h"
#include "CCEventTouch.h"
#include "CCScene.h"

#if CC_USE_PHYSICS
#include "CCPhysicsBody.h"
#endif

// externals
#include "kazmath/GL/matrix.h"
#include "CCComponent.h"
#include "CCComponentContainer.h"



#if CC_NODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL(__ARGS__) (ceil(__ARGS__))
#endif

NS_CC_BEGIN

bool nodeComparisonLess(Node* n1, Node* n2)
{
    return( n1->getLocalZOrder() < n2->getLocalZOrder() ||
           ( n1->getLocalZOrder() == n2->getLocalZOrder() && n1->getOrderOfArrival() < n2->getOrderOfArrival() )
           );
}

// XXX: Yes, nodes might have a sort problem once every 15 days if the game runs at 60 FPS and each frame sprites are reordered.
static int s_globalOrderOfArrival = 1;

Node::Node(void)
: _rotationX(0.0f)
, _rotationY(0.0f)
, _scaleX(1.0f)
, _scaleY(1.0f)
, _vertexZ(0.0f)
, _position(Point::ZERO)
, _skewX(0.0f)
, _skewY(0.0f)
, _anchorPointInPoints(Point::ZERO)
, _anchorPoint(Point::ZERO)
, _contentSize(Size::ZERO)
, _useAdditionalTransform(false)
, _transformDirty(true)
, _inverseDirty(true)
// children (lazy allocs)
// lazy alloc
, _localZOrder(0)
, _globalZOrder(0)
, _parent(nullptr)
// "whole screen" objects. like Scenes and Layers, should set _ignoreAnchorPointForPosition to true
, _tag(Node::INVALID_TAG)
// userData is always inited as nil
, _userData(nullptr)
, _userObject(nullptr)
, _shaderProgram(nullptr)
, _orderOfArrival(0)
, _running(false)
, _visible(true)
, _ignoreAnchorPointForPosition(false)
, _reorderChildDirty(false)
, _isTransitionFinished(false)
, _updateScriptHandler(0)
, _componentContainer(nullptr)
#if CC_USE_PHYSICS
, _physicsBody(nullptr)
#endif
, _displayedOpacity(255)
, _realOpacity(255)
, _displayedColor(Color3B::WHITE)
, _realColor(Color3B::WHITE)
, _cascadeColorEnabled(false)
, _cascadeOpacityEnabled(false)
{
    // set default scheduler and actionManager
    Director *director = Director::getInstance();
    _actionManager = director->getActionManager();
    _actionManager->retain();
    _scheduler = director->getScheduler();
    _scheduler->retain();
    _eventDispatcher = director->getEventDispatcher();
    _eventDispatcher->retain();
    
    ScriptEngineProtocol* engine = ScriptEngineManager::getInstance()->getScriptEngine();
    _scriptType = engine != nullptr ? engine->getScriptType() : kScriptTypeNone;

    kmMat4Identity(&_transform);
    kmMat4Identity(&_inverse);
    kmMat4Identity(&_additionalTransform);
}

Node::~Node()
{
    CCLOGINFO( "deallocing Node: %p - tag: %i", this, _tag );
    
    if (_updateScriptHandler)
    {
        ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptHandler(_updateScriptHandler);
    }

    CC_SAFE_RELEASE(_actionManager);
    CC_SAFE_RELEASE(_scheduler);
    
    _eventDispatcher->cleanTarget(this);
    CC_SAFE_RELEASE(_eventDispatcher);
    
    // attributes
    CC_SAFE_RELEASE(_shaderProgram);
    CC_SAFE_RELEASE(_userObject);

    for (auto& child : _children)
    {
        child->_parent = nullptr;
    }

    removeAllComponents();
    
    CC_SAFE_DELETE(_componentContainer);
    
#if CC_USE_PHYSICS
    CC_SAFE_RELEASE(_physicsBody);
#endif
}

bool Node::init()
{
    return true;
}

float Node::getSkewX() const
{
    return _skewX;
}

void Node::setSkewX(float newSkewX)
{
    _skewX = newSkewX;
    _transformDirty = _inverseDirty = true;
}

float Node::getSkewY() const
{
    return _skewY;
}

void Node::setSkewY(float newSkewY)
{
    _skewY = newSkewY;

    _transformDirty = _inverseDirty = true;
}


/// zOrder setter : private method
/// used internally to alter the zOrder variable. DON'T call this method manually 
void Node::_setLocalZOrder(int z)
{
    _localZOrder = z;
}

void Node::setLocalZOrder(int z)
{
    _localZOrder = z;
    if (_parent)
    {
        _parent->reorderChild(this, z);
    }

    _eventDispatcher->setDirtyForNode(this);
}

void Node::setGlobalZOrder(float globalZOrder)
{
    if (_globalZOrder != globalZOrder)
    {
        _globalZOrder = globalZOrder;
        _eventDispatcher->setDirtyForNode(this);
    }
}

/// vertexZ getter
float Node::getVertexZ() const
{
    return _vertexZ;
}


/// vertexZ setter
void Node::setVertexZ(float zOrder)
{
    _vertexZ = zOrder;
    setGlobalZOrder(zOrder);
}


/// rotation getter
float Node::getRotation() const
{
    CCASSERT(_rotationX == _rotationY, "CCNode#rotation. RotationX != RotationY. Don't know which one to return");
    return _rotationX;
}

/// rotation setter
void Node::setRotation(float newRotation)
{
    _rotationX = _rotationY = newRotation;
    _transformDirty = _inverseDirty = true;
    
#if CC_USE_PHYSICS
    if (_physicsBody)
    {
        _physicsBody->setRotation(newRotation);
    }
#endif
}

float Node::getRotationX() const
{
    return _rotationX;
}

void Node::setRotationX(float fRotationX)
{
    _rotationX = fRotationX;
    _transformDirty = _inverseDirty = true;
}

float Node::getRotationY() const
{
    return _rotationY;
}

void Node::setRotationY(float rotationY)
{
    _rotationY = rotationY;
    _transformDirty = _inverseDirty = true;
}

/// scale getter
float Node::getScale(void) const
{
    CCASSERT( _scaleX == _scaleY, "CCNode#scale. ScaleX != ScaleY. Don't know which one to return");
    return _scaleX;
}

/// scale setter
void Node::setScale(float scale)
{
    _scaleX = _scaleY = scale;
    _transformDirty = _inverseDirty = true;
}

/// scaleX getter
float Node::getScaleX() const
{
    return _scaleX;
}

/// scale setter
void Node::setScale(float scaleX,float scaleY)
{
    _scaleX = scaleX;
    _scaleY = scaleY;
    _transformDirty = _inverseDirty = true;
}

/// scaleX setter
void Node::setScaleX(float newScaleX)
{
    _scaleX = newScaleX;
    _transformDirty = _inverseDirty = true;
}

/// scaleY getter
float Node::getScaleY() const
{
    return _scaleY;
}

/// scaleY setter
void Node::setScaleY(float newScaleY)
{
    _scaleY = newScaleY;
    _transformDirty = _inverseDirty = true;
}

/// position getter
const Point& Node::getPosition() const
{
    return _position;
}

/// position setter
void Node::setPosition(const Point& newPosition)
{
    _position = newPosition;
    _transformDirty = _inverseDirty = true;
    
#if CC_USE_PHYSICS
    if (_physicsBody)
    {
        _physicsBody->setPosition(newPosition);
    }
#endif
}

void Node::getPosition(float* x, float* y) const
{
    *x = _position.x;
    *y = _position.y;
}

void Node::setPosition(float x, float y)
{
    setPosition(Point(x, y));
}

float Node::getPositionX() const
{
    return _position.x;
}

float Node::getPositionY() const
{
    return  _position.y;
}

void Node::setPositionX(float x)
{
    setPosition(Point(x, _position.y));
}

void Node::setPositionY(float y)
{
    setPosition(Point(_position.x, y));
}

ssize_t Node::getChildrenCount() const
{
    return _children.size();
}

/// isVisible getter
bool Node::isVisible() const
{
    return _visible;
}

/// isVisible setter
void Node::setVisible(bool var)
{
    _visible = var;
}

const Point& Node::getAnchorPointInPoints() const
{
    return _anchorPointInPoints;
}

/// anchorPoint getter
const Point& Node::getAnchorPoint() const
{
    return _anchorPoint;
}

void Node::setAnchorPoint(const Point& point)
{
    if( ! point.equals(_anchorPoint))
    {
        _anchorPoint = point;
        _anchorPointInPoints = Point(_contentSize.width * _anchorPoint.x, _contentSize.height * _anchorPoint.y );
        _transformDirty = _inverseDirty = true;
    }
}

/// contentSize getter
const Size& Node::getContentSize() const
{
    return _contentSize;
}

void Node::setContentSize(const Size & size)
{
    if ( ! size.equals(_contentSize))
    {
        _contentSize = size;

        _anchorPointInPoints = Point(_contentSize.width * _anchorPoint.x, _contentSize.height * _anchorPoint.y );
        _transformDirty = _inverseDirty = true;
    }
}

// isRunning getter
bool Node::isRunning() const
{
    return _running;
}

/// parent setter
void Node::setParent(Node * var)
{
    _parent = var;
}

/// isRelativeAnchorPoint getter
bool Node::isIgnoreAnchorPointForPosition() const
{
    return _ignoreAnchorPointForPosition;
}
/// isRelativeAnchorPoint setter
void Node::ignoreAnchorPointForPosition(bool newValue)
{
    if (newValue != _ignoreAnchorPointForPosition) 
    {
		_ignoreAnchorPointForPosition = newValue;
		_transformDirty = _inverseDirty = true;
	}
}

/// tag getter
int Node::getTag() const
{
    return _tag;
}

/// tag setter
void Node::setTag(int var)
{
    _tag = var;
}

/// userData setter
void Node::setUserData(void *var)
{
    _userData = var;
}

int Node::getOrderOfArrival() const
{
    return _orderOfArrival;
}

void Node::setOrderOfArrival(int orderOfArrival)
{
    CCASSERT(orderOfArrival >=0, "Invalid orderOfArrival");
    _orderOfArrival = orderOfArrival;
}

void Node::setUserObject(Object *pUserObject)
{
    CC_SAFE_RETAIN(pUserObject);
    CC_SAFE_RELEASE(_userObject);
    _userObject = pUserObject;
}

void Node::setShaderProgram(GLProgram *pShaderProgram)
{
    CC_SAFE_RETAIN(pShaderProgram);
    CC_SAFE_RELEASE(_shaderProgram);
    _shaderProgram = pShaderProgram;
}

Scene* Node::getScene()
{
    if(!_parent)
        return nullptr;
    return _parent->getScene();
}

Rect Node::getBoundingBox() const
{
    Rect rect = Rect(0, 0, _contentSize.width, _contentSize.height);
    return RectApplyAffineTransform(rect, getNodeToParentAffineTransform());
}

Node * Node::create(void)
{
	Node * ret = new Node();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
	return ret;
}

void Node::cleanup()
{
    // actions
    this->stopAllActions();
    this->unscheduleAllSelectors();
    
    if ( _scriptType != kScriptTypeNone)
    {
        int action = kNodeOnCleanup;
        BasicScriptData data(this,(void*)&action);
        ScriptEvent scriptEvent(kNodeEvent,(void*)&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&scriptEvent);
    }
    
    // timers
    for( const auto &child: _children)
        child->cleanup();
}


std::string Node::getDescription() const
{
    return StringUtils::format("<Node | Tag = %d", _tag);
}

// lazy allocs
void Node::childrenAlloc(void)
{
    _children.reserve(4);
}

Node* Node::getChildByTag(int tag)
{
    CCASSERT( tag != Node::INVALID_TAG, "Invalid tag");

    for (auto& child : _children)
    {
        if(child && child->_tag == tag)
            return child;
    }
    return nullptr;
}

/* "add" logic MUST only be on this method
* If a class want's to extend the 'addChild' behavior it only needs
* to override this method
*/
void Node::addChild(Node *child, int zOrder, int tag)
{    
    CCASSERT( child != nullptr, "Argument must be non-nil");
    CCASSERT( child->_parent == nullptr, "child already added. It can't be added again");

    if (_children.empty())
    {
        this->childrenAlloc();
    }

    this->insertChild(child, zOrder);
    
#if CC_USE_PHYSICS
    for (Node* node = this->getParent(); node != nullptr; node = node->getParent())
    {
        if (dynamic_cast<Scene*>(node) != nullptr)
        {
            (dynamic_cast<Scene*>(node))->addChildToPhysicsWorld(child);
            break;
        }
    }
#endif

    child->_tag = tag;

    child->setParent(this);
    child->setOrderOfArrival(s_globalOrderOfArrival++);

    if( _running )
    {
        child->onEnter();
        // prevent onEnterTransitionDidFinish to be called twice when a node is added in onEnter
        if (_isTransitionFinished) {
            child->onEnterTransitionDidFinish();
        }
    }
    
    if (_cascadeColorEnabled)
    {
        updateCascadeColor();
    }
    
    if (_cascadeOpacityEnabled)
    {
        updateCascadeOpacity();
    }
}

void Node::addChild(Node *child, int zOrder)
{
    CCASSERT( child != nullptr, "Argument must be non-nil");
    this->addChild(child, zOrder, child->_tag);
}

void Node::addChild(Node *child)
{
    CCASSERT( child != nullptr, "Argument must be non-nil");
    this->addChild(child, child->_localZOrder, child->_tag);
}

void Node::removeFromParent()
{
    this->removeFromParentAndCleanup(true);
}

void Node::removeFromParentAndCleanup(bool cleanup)
{
    if (_parent != nullptr)
    {
        _parent->removeChild(this,cleanup);
    } 
}

/* "remove" logic MUST only be on this method
* If a class want's to extend the 'removeChild' behavior it only needs
* to override this method
*/
void Node::removeChild(Node* child, bool cleanup /* = true */)
{
    // explicit nil handling
    if (_children.empty())
    {
        return;
    }

    ssize_t index = _children.getIndex(child);
    if( index != CC_INVALID_INDEX )
        this->detachChild( child, index, cleanup );
}

void Node::removeChildByTag(int tag, bool cleanup/* = true */)
{
    CCASSERT( tag != Node::INVALID_TAG, "Invalid tag");

    Node *child = this->getChildByTag(tag);

    if (child == nullptr)
    {
        CCLOG("cocos2d: removeChildByTag(tag = %d): child not found!", tag);
    }
    else
    {
        this->removeChild(child, cleanup);
    }
}

void Node::removeAllChildren()
{
    this->removeAllChildrenWithCleanup(true);
}

void Node::removeAllChildrenWithCleanup(bool cleanup)
{
    // not using detachChild improves speed here
    for (auto& child : _children)
    {
        // IMPORTANT:
        //  -1st do onExit
        //  -2nd cleanup
        if(_running)
        {
            child->onExitTransitionDidStart();
            child->onExit();
        }

        if (cleanup)
        {
            child->cleanup();
        }
        // set parent nil at the end
        child->setParent(nullptr);
    }
    
    _children.clear();
}

void Node::detachChild(Node *child, ssize_t childIndex, bool doCleanup)
{
    // IMPORTANT:
    //  -1st do onExit
    //  -2nd cleanup
    if (_running)
    {
        child->onExitTransitionDidStart();
        child->onExit();
    }
    
#if CC_USE_PHYSICS
    if (child->_physicsBody != nullptr)
    {
        child->_physicsBody->removeFromWorld();
    }
    
#endif

    // If you don't do cleanup, the child's actions will not get removed and the
    // its scheduledSelectors_ dict will not get released!
    if (doCleanup)
    {
        child->cleanup();
    }

    // set parent nil at the end
    child->setParent(nullptr);

    _children.erase(childIndex);
}


// helper used by reorderChild & add
void Node::insertChild(Node* child, int z)
{
    _reorderChildDirty = true;
    _children.pushBack(child);
    child->_setLocalZOrder(z);
}

void Node::reorderChild(Node *child, int zOrder)
{
    CCASSERT( child != nullptr, "Child must be non-nil");
    _reorderChildDirty = true;
    child->setOrderOfArrival(s_globalOrderOfArrival++);
    child->_setLocalZOrder(zOrder);
}

void Node::sortAllChildren()
{
    if( _reorderChildDirty ) {
        std::sort( std::begin(_children), std::end(_children), nodeComparisonLess );
        _reorderChildDirty = false;
    }
}


 void Node::draw()
 {
     //CCASSERT(0);
     // override me
     // Only use- this function to draw your stuff.
     // DON'T draw your stuff outside this method
 }

void Node::visit()
{
    // quick return if not visible. children won't be drawn.
    if (!_visible)
    {
        return;
    }
    
    kmGLPushMatrix();

    this->transform();
    int i = 0;

    if(!_children.empty())
    {
        sortAllChildren();
        // draw children zOrder < 0
        for( ; i < _children.size(); i++ )
        {
            auto node = _children.at(i);

            if ( node && node->_localZOrder < 0 )
                node->visit();
            else
                break;
        }
        // self draw
        this->draw();

        for(auto it=_children.cbegin()+i; it != _children.cend(); ++it)
            (*it)->visit();
    }
    else
    {
        this->draw();
    }

    // reset for next frame
    _orderOfArrival = 0;
 
    kmGLPopMatrix();
}

void Node::transformAncestors()
{
    if( _parent != nullptr  )
    {
        _parent->transformAncestors();
        _parent->transform();
    }
}

void Node::transform()
{
#if CC_USE_PHYSICS
    updatePhysicsTransform();
#endif

    kmMat4 transfrom4x4 = this->getNodeToParentTransform();

    kmGLMultMatrix( &transfrom4x4 );

    // saves the MV matrix
    kmGLGetMatrix(KM_GL_MODELVIEW, &_modelViewTransform);
}

void Node::onEnter()
{
    _isTransitionFinished = false;

    if (_scriptType != kScriptTypeNone)
    {
        int action = kNodeOnEnter;
        BasicScriptData data(this,(void*)&action);
        ScriptEvent scriptEvent(kNodeEvent,(void*)&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&scriptEvent);
    }
    
    for( const auto &child: _children)
        child->onEnter();

    this->resume();
    
    _running = true;
}

void Node::onEnterTransitionDidFinish()
{
    _isTransitionFinished = true;

    if (_scriptType != kScriptTypeNone)
    {
        int action = kNodeOnEnterTransitionDidFinish;
        BasicScriptData data(this,(void*)&action);
        ScriptEvent scriptEvent(kNodeEvent,(void*)&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&scriptEvent);
    }
    
    for( const auto &child: _children)
        child->onEnterTransitionDidFinish();
}

void Node::onExitTransitionDidStart()
{
    for( const auto &child: _children)
        child->onExitTransitionDidStart();
    
    if (_scriptType != kScriptTypeNone)
    {
        int action = kNodeOnExitTransitionDidStart;
        BasicScriptData data(this,(void*)&action);
        ScriptEvent scriptEvent(kNodeEvent,(void*)&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&scriptEvent);
    }
}

void Node::onExit()
{
    this->pause();

    _running = false;

    for( const auto &child: _children)
        child->onExit();
    
    if (_scriptType != kScriptTypeNone)
    {
        int action = kNodeOnExit;
        BasicScriptData data(this,(void*)&action);
        ScriptEvent scriptEvent(kNodeEvent,(void*)&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&scriptEvent);
    }
}

void Node::setEventDispatcher(EventDispatcher* dispatcher)
{
    if (dispatcher != _eventDispatcher)
    {
        _eventDispatcher->cleanTarget(this);
        CC_SAFE_RETAIN(dispatcher);
        CC_SAFE_RELEASE(_eventDispatcher);
        _eventDispatcher = dispatcher;
    }
}

void Node::setActionManager(ActionManager* actionManager)
{
    if( actionManager != _actionManager ) {
        this->stopAllActions();
        CC_SAFE_RETAIN(actionManager);
        CC_SAFE_RELEASE(_actionManager);
        _actionManager = actionManager;
    }
}

Action * Node::runAction(Action* action)
{
    CCASSERT( action != nullptr, "Argument must be non-nil");
    _actionManager->addAction(action, this, !_running);
    return action;
}

void Node::stopAllActions()
{
    _actionManager->removeAllActionsFromTarget(this);
}

void Node::stopAction(Action* action)
{
    _actionManager->removeAction(action);
}

void Node::stopActionByTag(int tag)
{
    CCASSERT( tag != Action::INVALID_TAG, "Invalid tag");
    _actionManager->removeActionByTag(tag, this);
}

Action * Node::getActionByTag(int tag)
{
    CCASSERT( tag != Action::INVALID_TAG, "Invalid tag");
    return _actionManager->getActionByTag(tag, this);
}

ssize_t Node::getNumberOfRunningActions() const
{
    return _actionManager->getNumberOfRunningActionsInTarget(this);
}

// Node - Callbacks

void Node::setScheduler(Scheduler* scheduler)
{
    if( scheduler != _scheduler ) {
        this->unscheduleAllSelectors();
        CC_SAFE_RETAIN(scheduler);
        CC_SAFE_RELEASE(_scheduler);
        _scheduler = scheduler;
    }
}

bool Node::isScheduled(SEL_SCHEDULE selector)
{
    return _scheduler->isScheduledForTarget(selector, this);
}

void Node::scheduleUpdate()
{
    scheduleUpdateWithPriority(0);
}

void Node::scheduleUpdateWithPriority(int priority)
{
    _scheduler->scheduleUpdateForTarget(this, priority, !_running);
}

void Node::scheduleUpdateWithPriorityLua(int nHandler, int priority)
{
    unscheduleUpdate();
    _updateScriptHandler = nHandler;
    _scheduler->scheduleUpdateForTarget(this, priority, !_running);
}

void Node::unscheduleUpdate()
{
    _scheduler->unscheduleUpdateForTarget(this);
    if (_updateScriptHandler)
    {
        ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptHandler(_updateScriptHandler);
        _updateScriptHandler = 0;
    }
}

void Node::schedule(SEL_SCHEDULE selector)
{
    this->schedule(selector, 0.0f, kRepeatForever, 0.0f);
}

void Node::schedule(SEL_SCHEDULE selector, float interval)
{
    this->schedule(selector, interval, kRepeatForever, 0.0f);
}

void Node::schedule(SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay)
{
    CCASSERT( selector, "Argument must be non-nil");
    CCASSERT( interval >=0, "Argument must be positive");

    _scheduler->scheduleSelector(selector, this, interval , repeat, delay, !_running);
}

void Node::scheduleOnce(SEL_SCHEDULE selector, float delay)
{
    this->schedule(selector, 0.0f, 0, delay);
}

void Node::unschedule(SEL_SCHEDULE selector)
{
    // explicit nil handling
    if (selector == 0)
        return;

    _scheduler->unscheduleSelector(selector, this);
}

void Node::unscheduleAllSelectors()
{
    _scheduler->unscheduleAllForTarget(this);
}

void Node::resume()
{
    _scheduler->resumeTarget(this);
    _actionManager->resumeTarget(this);
    _eventDispatcher->resumeTarget(this);
}

void Node::pause()
{
    _scheduler->pauseTarget(this);
    _actionManager->pauseTarget(this);
    _eventDispatcher->pauseTarget(this);
}

void Node::resumeSchedulerAndActions()
{
    resume();
}

void Node::pauseSchedulerAndActions()
{
    pause();
}

// override me
void Node::update(float fDelta)
{
    if (0 != _updateScriptHandler)
    {
        //only lua use
        SchedulerScriptData data(_updateScriptHandler,fDelta);
        ScriptEvent event(kScheduleEvent,&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
    
    if (_componentContainer && !_componentContainer->isEmpty())
    {
        _componentContainer->visit(fDelta);
    }
}

AffineTransform Node::getNodeToParentAffineTransform() const
{
    AffineTransform ret;
    kmMat4 ret4 = getNodeToParentTransform();
    GLToCGAffine(ret4.mat, &ret);

    return ret;
}

const kmMat4& Node::getNodeToParentTransform() const
{
    if (_transformDirty)
    {
        // Translate values
        float x = _position.x;
        float y = _position.y;

        if (_ignoreAnchorPointForPosition)
        {
            x += _anchorPointInPoints.x;
            y += _anchorPointInPoints.y;
        }

        // Rotation values
		// Change rotation code to handle X and Y
		// If we skew with the exact same value for both x and y then we're simply just rotating
        float cx = 1, sx = 0, cy = 1, sy = 0;
        if (_rotationX || _rotationY)
        {
            float radiansX = -CC_DEGREES_TO_RADIANS(_rotationX);
            float radiansY = -CC_DEGREES_TO_RADIANS(_rotationY);
            cx = cosf(radiansX);
            sx = sinf(radiansX);
            cy = cosf(radiansY);
            sy = sinf(radiansY);
        }

        bool needsSkewMatrix = ( _skewX || _skewY );


        // optimization:
        // inline anchor point calculation if skew is not needed
        // Adjusted transform calculation for rotational skew
        if (! needsSkewMatrix && !_anchorPointInPoints.equals(Point::ZERO))
        {
            x += cy * -_anchorPointInPoints.x * _scaleX + -sx * -_anchorPointInPoints.y * _scaleY;
            y += sy * -_anchorPointInPoints.x * _scaleX +  cx * -_anchorPointInPoints.y * _scaleY;
        }


        // Build Transform Matrix
        // Adjusted transform calculation for rotational skew
        kmScalar mat[] = { cy * _scaleX, sy * _scaleX, 0,  0,
                      -sx * _scaleY, cx * _scaleY, 0,  0,
                        0,  0,  1,  0,
                        x,  y,  0,  1 };
        
        kmMat4Fill(&_transform, mat);

        // XXX: Try to inline skew
        // If skew is needed, apply skew and then anchor point
        if (needsSkewMatrix)
        {
            kmMat4 skewMatrix = { 1, (float)tanf(CC_DEGREES_TO_RADIANS(_skewY)), 0, 0,
                                  (float)tanf(CC_DEGREES_TO_RADIANS(_skewX)), 1, 0, 0,
                                  0,  0,  1, 0,
                                  0,  0,  0, 1};

            kmMat4Multiply(&_transform, &_transform, &skewMatrix);

            // adjust anchor point
            if (!_anchorPointInPoints.equals(Point::ZERO))
            {
                // XXX: Argh, kmMat needs a "translate" method.
                // XXX: Although this is faster than multiplying a vec4 * mat4
                _transform.mat[12] += _transform.mat[0] * -_anchorPointInPoints.x + _transform.mat[4] * -_anchorPointInPoints.y;
                _transform.mat[13] += _transform.mat[1] * -_anchorPointInPoints.x + _transform.mat[5] * -_anchorPointInPoints.y;
            }
        }

        // vertex Z
        _transform.mat[14] = _vertexZ;

        if (_useAdditionalTransform)
        {
            kmMat4Multiply(&_transform, &_transform, &_additionalTransform);
        }

        _transformDirty = false;
    }

    return _transform;
}

void Node::setNodeToParentTransform(const kmMat4& transform)
{
    _transform = transform;
    _transformDirty = false;
}

void Node::setAdditionalTransform(const AffineTransform& additionalTransform)
{
    CGAffineToGL(additionalTransform, _additionalTransform.mat);
    _transformDirty = true;
    _useAdditionalTransform = true;
}

void Node::setAdditionalTransform(const kmMat4& additionalTransform)
{
    _additionalTransform = additionalTransform;
    _transformDirty = true;
    _useAdditionalTransform = true;
}


AffineTransform Node::getParentToNodeAffineTransform() const
{
    AffineTransform ret;
    kmMat4 ret4 = getParentToNodeTransform();

    GLToCGAffine(ret4.mat,&ret);
    return ret;
}

const kmMat4& Node::getParentToNodeTransform() const
{
    if ( _inverseDirty ) {
        kmMat4Inverse(&_inverse, &_transform);
        _inverseDirty = false;
    }

    return _inverse;
}


AffineTransform Node::getNodeToWorldAffineTransform() const
{
    AffineTransform t = this->getNodeToParentAffineTransform();

    for (Node *p = _parent; p != nullptr; p = p->getParent())
        t = AffineTransformConcat(t, p->getNodeToParentAffineTransform());

    return t;
}

kmMat4 Node::getNodeToWorldTransform() const
{
    kmMat4 t = this->getNodeToParentTransform();

    for (Node *p = _parent; p != nullptr; p = p->getParent())
        kmMat4Multiply(&t, &p->getNodeToParentTransform(), &t);

    return t;
}

AffineTransform Node::getWorldToNodeAffineTransform() const
{
    return AffineTransformInvert(this->getNodeToWorldAffineTransform());
}

kmMat4 Node::getWorldToNodeTransform() const
{
    kmMat4 tmp, tmp2;

    tmp2 = this->getNodeToWorldTransform();
    kmMat4Inverse(&tmp, &tmp2);
    return tmp;
}


Point Node::convertToNodeSpace(const Point& worldPoint) const
{
    kmMat4 tmp = getWorldToNodeTransform();
    kmVec3 vec3 = {worldPoint.x, worldPoint.y, 0};
    kmVec3 ret;
    kmVec3Transform(&ret, &vec3, &tmp);
    return Point(ret.x, ret.y);
}

Point Node::convertToWorldSpace(const Point& nodePoint) const
{
    kmMat4 tmp = getNodeToWorldTransform();
    kmVec3 vec3 = {nodePoint.x, nodePoint.y, 0};
    kmVec3 ret;
    kmVec3Transform(&ret, &vec3, &tmp);
    return Point(ret.x, ret.y);

}

Point Node::convertToNodeSpaceAR(const Point& worldPoint) const
{
    Point nodePoint = convertToNodeSpace(worldPoint);
    return nodePoint - _anchorPointInPoints;
}

Point Node::convertToWorldSpaceAR(const Point& nodePoint) const
{
    Point pt = nodePoint + _anchorPointInPoints;
    return convertToWorldSpace(pt);
}

Point Node::convertToWindowSpace(const Point& nodePoint) const
{
    Point worldPoint = this->convertToWorldSpace(nodePoint);
    return Director::getInstance()->convertToUI(worldPoint);
}

// convenience methods which take a Touch instead of Point
Point Node::convertTouchToNodeSpace(Touch *touch) const
{
    Point point = touch->getLocation();
    return this->convertToNodeSpace(point);
}
Point Node::convertTouchToNodeSpaceAR(Touch *touch) const
{
    Point point = touch->getLocation();
    return this->convertToNodeSpaceAR(point);
}

#if CC_USE_PHYSICS
bool Node::updatePhysicsTransform()
{
    if (_physicsBody != nullptr && _physicsBody->getWorld() != nullptr && !_physicsBody->isResting())
    {
        _position = _physicsBody->getPosition();
        _rotationX = _rotationY = _physicsBody->getRotation();
        _transformDirty = _inverseDirty = true;
        return true;
    }
    
    return false;
}
#endif

void Node::updateTransform()
{
    // Recursively iterate over children
    for( const auto &child: _children)
        child->updateTransform();
}

Component* Node::getComponent(const std::string& pName)
{
    if( _componentContainer )
        return _componentContainer->get(pName);
    return nullptr;
}

bool Node::addComponent(Component *pComponent)
{
    // lazy alloc
    if( !_componentContainer )
        _componentContainer = new ComponentContainer(this);
    return _componentContainer->add(pComponent);
}

bool Node::removeComponent(const std::string& pName)
{
    if( _componentContainer )
        return _componentContainer->remove(pName);
    return false;
}

void Node::removeAllComponents()
{
    if( _componentContainer )
        _componentContainer->removeAll();
}

#if CC_USE_PHYSICS
void Node::setPhysicsBody(PhysicsBody* body)
{
    if (_physicsBody != nullptr)
    {
        _physicsBody->_node = nullptr;
        _physicsBody->release();
    }
    
    _physicsBody = body;
    _physicsBody->_node = this;
    _physicsBody->retain();
    _physicsBody->setPosition(getPosition());
    _physicsBody->setRotation(getRotation());
}

PhysicsBody* Node::getPhysicsBody() const
{
    return _physicsBody;
}
#endif //CC_USE_PHYSICS

GLubyte Node::getOpacity(void) const
{
	return _realOpacity;
}

GLubyte Node::getDisplayedOpacity(void) const
{
	return _displayedOpacity;
}

void Node::setOpacity(GLubyte opacity)
{
    _displayedOpacity = _realOpacity = opacity;
    
    updateCascadeOpacity();
}

void Node::updateDisplayedOpacity(GLubyte parentOpacity)
{
	_displayedOpacity = _realOpacity * parentOpacity/255.0;
    updateColor();
    
    if (_cascadeOpacityEnabled)
    {
        for(auto child : _children){
            child->updateDisplayedOpacity(_displayedOpacity);
        }
    }
}

bool Node::isCascadeOpacityEnabled(void) const
{
    return _cascadeOpacityEnabled;
}

void Node::setCascadeOpacityEnabled(bool cascadeOpacityEnabled)
{
    if (_cascadeOpacityEnabled == cascadeOpacityEnabled)
    {
        return;
    }
    
    _cascadeOpacityEnabled = cascadeOpacityEnabled;
    
    if (cascadeOpacityEnabled)
    {
        updateCascadeOpacity();
    }
    else
    {
        disableCascadeOpacity();
    }
}

void Node::updateCascadeOpacity()
{
    GLubyte parentOpacity = 255;
    
    if (_parent != nullptr && _parent->isCascadeOpacityEnabled())
    {
        parentOpacity = _parent->getDisplayedOpacity();
    }
    
    updateDisplayedOpacity(parentOpacity);
}

void Node::disableCascadeOpacity()
{
    _displayedOpacity = _realOpacity;
    
    for(auto child : _children){
        child->updateDisplayedOpacity(255);
    }
}

const Color3B& Node::getColor(void) const
{
	return _realColor;
}

const Color3B& Node::getDisplayedColor() const
{
	return _displayedColor;
}

void Node::setColor(const Color3B& color)
{
	_displayedColor = _realColor = color;
	
	updateCascadeColor();
}

void Node::updateDisplayedColor(const Color3B& parentColor)
{
	_displayedColor.r = _realColor.r * parentColor.r/255.0;
	_displayedColor.g = _realColor.g * parentColor.g/255.0;
	_displayedColor.b = _realColor.b * parentColor.b/255.0;
    updateColor();
    
    if (_cascadeColorEnabled)
    {
        for(const auto &child : _children){
            child->updateDisplayedColor(_displayedColor);
        }
    }
}

bool Node::isCascadeColorEnabled(void) const
{
    return _cascadeColorEnabled;
}

void Node::setCascadeColorEnabled(bool cascadeColorEnabled)
{
    if (_cascadeColorEnabled == cascadeColorEnabled)
    {
        return;
    }
    
    _cascadeColorEnabled = cascadeColorEnabled;
    
    if (_cascadeColorEnabled)
    {
        updateCascadeColor();
    }
    else
    {
        disableCascadeColor();
    }
}

void Node::updateCascadeColor()
{
	Color3B parentColor = Color3B::WHITE;
    if (_parent && _parent->isCascadeColorEnabled())
    {
        parentColor = _parent->getDisplayedColor();
    }
    
    updateDisplayedColor(parentColor);
}

void Node::disableCascadeColor()
{
    for(auto child : _children){
        child->updateDisplayedColor(Color3B::WHITE);
    }
}

__NodeRGBA::__NodeRGBA()
{
    CCLOG("NodeRGBA deprecated.");
}

NS_CC_END
