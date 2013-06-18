/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Valentin Milea
Copyright (c) 2011      Zynga Inc.

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
#include "cocoa/CCString.h"
#include "CCNode.h"
#include "support/CCPointExtension.h"
#include "support/TransformUtils.h"
#include "CCCamera.h"
#include "effects/CCGrid.h"
#include "CCDirector.h"
#include "CCScheduler.h"
#include "touch_dispatcher/CCTouch.h"
#include "actions/CCActionManager.h"
#include "script_support/CCScriptSupport.h"
#include "shaders/CCGLProgram.h"
// externals
#include "kazmath/GL/matrix.h"
#include "support/component/CCComponent.h"
#include "support/component/CCComponentContainer.h"

#if CC_NODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL(__ARGS__) (ceil(__ARGS__))
#endif

NS_CC_BEGIN

// XXX: Yes, nodes might have a sort problem once every 15 days if the game runs at 60 FPS and each frame sprites are reordered.
static int s_globalOrderOfArrival = 1;

CCNode::CCNode(void)
: _rotationX(0.0f)
, _rotationY(0.0f)
, _scaleX(1.0f)
, _scaleY(1.0f)
, _vertexZ(0.0f)
, _position(CCPointZero)
, _skewX(0.0f)
, _skewY(0.0f)
, _anchorPointInPoints(CCPointZero)
, _anchorPoint(CCPointZero)
, _contentSize(CCSizeZero)
, _additionalTransform(CCAffineTransformMakeIdentity())
, _camera(NULL)
// children (lazy allocs)
// lazy alloc
, _grid(NULL)
, _ZOrder(0)
, _children(NULL)
, _parent(NULL)
// "whole screen" objects. like Scenes and Layers, should set _ignoreAnchorPointForPosition to true
, _tag(kCCNodeTagInvalid)
// userData is always inited as nil
, _userData(NULL)
, _userObject(NULL)
, _shaderProgram(NULL)
, _GLServerState(ccGLServerState(0))
, _orderOfArrival(0)
, _running(false)
, _transformDirty(true)
, _inverseDirty(true)
, _additionalTransformDirty(false)
, _visible(true)
, _ignoreAnchorPointForPosition(false)
, _reorderChildDirty(false)
, _isTransitionFinished(false)
, _scriptHandler(0)
, _updateScriptHandler(0)
, _componentContainer(NULL)
{
    // set default scheduler and actionManager
    CCDirector *director = CCDirector::sharedDirector();
    _actionManager = director->getActionManager();
    _actionManager->retain();
    _scheduler = director->getScheduler();
    _scheduler->retain();

    CCScriptEngineProtocol* pEngine = CCScriptEngineManager::sharedManager()->getScriptEngine();
    _scriptType = pEngine != NULL ? pEngine->getScriptType() : kScriptTypeNone;
    _componentContainer = new CCComponentContainer(this);
}

CCNode::~CCNode(void)
{
    CCLOGINFO( "cocos2d: deallocing: %p", this );
    
    unregisterScriptHandler();
    if (_updateScriptHandler)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(_updateScriptHandler);
    }

    CC_SAFE_RELEASE(_actionManager);
    CC_SAFE_RELEASE(_scheduler);
    // attributes
    CC_SAFE_RELEASE(_camera);

    CC_SAFE_RELEASE(_grid);
    CC_SAFE_RELEASE(_shaderProgram);
    CC_SAFE_RELEASE(_userObject);

    if(_children && _children->count() > 0)
    {
        CCObject* child;
        CCARRAY_FOREACH(_children, child)
        {
            CCNode* pChild = (CCNode*) child;
            if (pChild)
            {
                pChild->_parent = NULL;
            }
        }
    }

    // children
    CC_SAFE_RELEASE(_children);
    
          // _comsContainer
    _componentContainer->removeAll();
    CC_SAFE_DELETE(_componentContainer);
}

bool CCNode::init()
{
    return true;
}

float CCNode::getSkewX()
{
    return _skewX;
}

void CCNode::setSkewX(float newSkewX)
{
    _skewX = newSkewX;
    _transformDirty = _inverseDirty = true;
}

float CCNode::getSkewY()
{
    return _skewY;
}

void CCNode::setSkewY(float newSkewY)
{
    _skewY = newSkewY;

    _transformDirty = _inverseDirty = true;
}

/// zOrder getter
int CCNode::getZOrder()
{
    return _ZOrder;
}

/// zOrder setter : private method
/// used internally to alter the zOrder variable. DON'T call this method manually 
void CCNode::_setZOrder(int z)
{
    _ZOrder = z;
}

void CCNode::setZOrder(int z)
{
    _setZOrder(z);
    if (_parent)
    {
        _parent->reorderChild(this, z);
    }
}

/// vertexZ getter
float CCNode::getVertexZ()
{
    return _vertexZ;
}


/// vertexZ setter
void CCNode::setVertexZ(float var)
{
    _vertexZ = var;
}


/// rotation getter
float CCNode::getRotation()
{
    CCAssert(_rotationX == _rotationY, "CCNode#rotation. RotationX != RotationY. Don't know which one to return");
    return _rotationX;
}

/// rotation setter
void CCNode::setRotation(float newRotation)
{
    _rotationX = _rotationY = newRotation;
    _transformDirty = _inverseDirty = true;
}

float CCNode::getRotationX()
{
    return _rotationX;
}

void CCNode::setRotationX(float fRotationX)
{
    _rotationX = fRotationX;
    _transformDirty = _inverseDirty = true;
}

float CCNode::getRotationY()
{
    return _rotationY;
}

void CCNode::setRotationY(float fRotationY)
{
    _rotationY = fRotationY;
    _transformDirty = _inverseDirty = true;
}

/// scale getter
float CCNode::getScale(void)
{
    CCAssert( _scaleX == _scaleY, "CCNode#scale. ScaleX != ScaleY. Don't know which one to return");
    return _scaleX;
}

/// scale setter
void CCNode::setScale(float scale)
{
    _scaleX = _scaleY = scale;
    _transformDirty = _inverseDirty = true;
}

/// scaleX getter
float CCNode::getScaleX()
{
    return _scaleX;
}

/// scaleX setter
void CCNode::setScaleX(float newScaleX)
{
    _scaleX = newScaleX;
    _transformDirty = _inverseDirty = true;
}

/// scaleY getter
float CCNode::getScaleY()
{
    return _scaleY;
}

/// scaleY setter
void CCNode::setScaleY(float newScaleY)
{
    _scaleY = newScaleY;
    _transformDirty = _inverseDirty = true;
}

/// position getter
const CCPoint& CCNode::getPosition()
{
    return _position;
}

/// position setter
void CCNode::setPosition(const CCPoint& newPosition)
{
    _position = newPosition;
    _transformDirty = _inverseDirty = true;
}

void CCNode::getPosition(float* x, float* y)
{
    *x = _position.x;
    *y = _position.y;
}

void CCNode::setPosition(float x, float y)
{
    setPosition(ccp(x, y));
}

float CCNode::getPositionX(void)
{
    return _position.x;
}

float CCNode::getPositionY(void)
{
    return  _position.y;
}

void CCNode::setPositionX(float x)
{
    setPosition(ccp(x, _position.y));
}

void CCNode::setPositionY(float y)
{
    setPosition(ccp(_position.x, y));
}

/// children getter
CCArray* CCNode::getChildren()
{
    return _children;
}

unsigned int CCNode::getChildrenCount(void) const
{
    return _children ? _children->count() : 0;
}

/// camera getter: lazy alloc
CCCamera* CCNode::getCamera()
{
    if (!_camera)
    {
        _camera = new CCCamera();
    }
    
    return _camera;
}


/// grid getter
CCGridBase* CCNode::getGrid()
{
    return _grid;
}

/// grid setter
void CCNode::setGrid(CCGridBase* pGrid)
{
    CC_SAFE_RETAIN(pGrid);
    CC_SAFE_RELEASE(_grid);
    _grid = pGrid;
}


/// isVisible getter
bool CCNode::isVisible()
{
    return _visible;
}

/// isVisible setter
void CCNode::setVisible(bool var)
{
    _visible = var;
}

const CCPoint& CCNode::getAnchorPointInPoints()
{
    return _anchorPointInPoints;
}

/// anchorPoint getter
const CCPoint& CCNode::getAnchorPoint()
{
    return _anchorPoint;
}

void CCNode::setAnchorPoint(const CCPoint& point)
{
    if( ! point.equals(_anchorPoint))
    {
        _anchorPoint = point;
        _anchorPointInPoints = ccp(_contentSize.width * _anchorPoint.x, _contentSize.height * _anchorPoint.y );
        _transformDirty = _inverseDirty = true;
    }
}

/// contentSize getter
const CCSize& CCNode::getContentSize() const
{
    return _contentSize;
}

void CCNode::setContentSize(const CCSize & size)
{
    if ( ! size.equals(_contentSize))
    {
        _contentSize = size;

        _anchorPointInPoints = ccp(_contentSize.width * _anchorPoint.x, _contentSize.height * _anchorPoint.y );
        _transformDirty = _inverseDirty = true;
    }
}

// isRunning getter
bool CCNode::isRunning()
{
    return _running;
}

/// parent getter
CCNode * CCNode::getParent()
{
    return _parent;
}
/// parent setter
void CCNode::setParent(CCNode * var)
{
    _parent = var;
}

/// isRelativeAnchorPoint getter
bool CCNode::isIgnoreAnchorPointForPosition()
{
    return _ignoreAnchorPointForPosition;
}
/// isRelativeAnchorPoint setter
void CCNode::ignoreAnchorPointForPosition(bool newValue)
{
    if (newValue != _ignoreAnchorPointForPosition) 
    {
		_ignoreAnchorPointForPosition = newValue;
		_transformDirty = _inverseDirty = true;
	}
}

/// tag getter
int CCNode::getTag() const
{
    return _tag;
}

/// tag setter
void CCNode::setTag(int var)
{
    _tag = var;
}

/// userData getter
void * CCNode::getUserData()
{
    return _userData;
}

/// userData setter
void CCNode::setUserData(void *var)
{
    _userData = var;
}

unsigned int CCNode::getOrderOfArrival()
{
    return _orderOfArrival;
}

void CCNode::setOrderOfArrival(unsigned int uOrderOfArrival)
{
    _orderOfArrival = uOrderOfArrival;
}

CCGLProgram* CCNode::getShaderProgram()
{
    return _shaderProgram;
}

CCObject* CCNode::getUserObject()
{
    return _userObject;
}

ccGLServerState CCNode::getGLServerState()
{
    return _GLServerState;
}

void CCNode::setGLServerState(ccGLServerState glServerState)
{
    _GLServerState = glServerState;
}

void CCNode::setUserObject(CCObject *pUserObject)
{
    CC_SAFE_RELEASE(_userObject);
    CC_SAFE_RETAIN(pUserObject);
    _userObject = pUserObject;
}

void CCNode::setShaderProgram(CCGLProgram *pShaderProgram)
{
    CC_SAFE_RELEASE(_shaderProgram);
    _shaderProgram = pShaderProgram;
    CC_SAFE_RETAIN(_shaderProgram);
}

CCRect CCNode::boundingBox()
{
    CCRect rect = CCRectMake(0, 0, _contentSize.width, _contentSize.height);
    return CCRectApplyAffineTransform(rect, nodeToParentTransform());
}

CCNode * CCNode::create(void)
{
	CCNode * pRet = new CCNode();
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

void CCNode::cleanup()
{
    // actions
    this->stopAllActions();
    this->unscheduleAllSelectors();
    
    if ( _scriptType != kScriptTypeNone)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeNodeEvent(this, kCCNodeOnCleanup);
    }
    
    // timers
    arrayMakeObjectsPerformSelector(_children, cleanup, CCNode*);
}


const char* CCNode::description()
{
    return CCString::createWithFormat("<CCNode | Tag = %d>", _tag)->getCString();
}

// lazy allocs
void CCNode::childrenAlloc(void)
{
    _children = CCArray::createWithCapacity(4);
    _children->retain();
}

CCNode* CCNode::getChildByTag(int aTag)
{
    CCAssert( aTag != kCCNodeTagInvalid, "Invalid tag");

    if(_children && _children->count() > 0)
    {
        CCObject* child;
        CCARRAY_FOREACH(_children, child)
        {
            CCNode* pNode = (CCNode*) child;
            if(pNode && pNode->_tag == aTag)
                return pNode;
        }
    }
    return NULL;
}

/* "add" logic MUST only be on this method
* If a class want's to extend the 'addChild' behavior it only needs
* to override this method
*/
void CCNode::addChild(CCNode *child, int zOrder, int tag)
{    
    CCAssert( child != NULL, "Argument must be non-nil");
    CCAssert( child->_parent == NULL, "child already added. It can't be added again");

    if( ! _children )
    {
        this->childrenAlloc();
    }

    this->insertChild(child, zOrder);

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
}

void CCNode::addChild(CCNode *child, int zOrder)
{
    CCAssert( child != NULL, "Argument must be non-nil");
    this->addChild(child, zOrder, child->_tag);
}

void CCNode::addChild(CCNode *child)
{
    CCAssert( child != NULL, "Argument must be non-nil");
    this->addChild(child, child->_ZOrder, child->_tag);
}

void CCNode::removeFromParent()
{
    this->removeFromParentAndCleanup(true);
}

void CCNode::removeFromParentAndCleanup(bool cleanup)
{
    if (_parent != NULL)
    {
        _parent->removeChild(this,cleanup);
    } 
}

void CCNode::removeChild(CCNode* child)
{
    this->removeChild(child, true);
}

/* "remove" logic MUST only be on this method
* If a class want's to extend the 'removeChild' behavior it only needs
* to override this method
*/
void CCNode::removeChild(CCNode* child, bool cleanup)
{
    // explicit nil handling
    if (_children == NULL)
    {
        return;
    }

    if ( _children->containsObject(child) )
    {
        this->detachChild(child,cleanup);
    }
}

void CCNode::removeChildByTag(int tag)
{
    this->removeChildByTag(tag, true);
}

void CCNode::removeChildByTag(int tag, bool cleanup)
{
    CCAssert( tag != kCCNodeTagInvalid, "Invalid tag");

    CCNode *child = this->getChildByTag(tag);

    if (child == NULL)
    {
        CCLOG("cocos2d: removeChildByTag(tag = %d): child not found!", tag);
    }
    else
    {
        this->removeChild(child, cleanup);
    }
}

void CCNode::removeAllChildren()
{
    this->removeAllChildrenWithCleanup(true);
}

void CCNode::removeAllChildrenWithCleanup(bool cleanup)
{
    // not using detachChild improves speed here
    if ( _children && _children->count() > 0 )
    {
        CCObject* child;
        CCARRAY_FOREACH(_children, child)
        {
            CCNode* pNode = (CCNode*) child;
            if (pNode)
            {
                // IMPORTANT:
                //  -1st do onExit
                //  -2nd cleanup
                if(_running)
                {
                    pNode->onExitTransitionDidStart();
                    pNode->onExit();
                }

                if (cleanup)
                {
                    pNode->cleanup();
                }
                // set parent nil at the end
                pNode->setParent(NULL);
            }
        }
        
        _children->removeAllObjects();
    }
    
}

void CCNode::detachChild(CCNode *child, bool doCleanup)
{
    // IMPORTANT:
    //  -1st do onExit
    //  -2nd cleanup
    if (_running)
    {
        child->onExitTransitionDidStart();
        child->onExit();
    }

    // If you don't do cleanup, the child's actions will not get removed and the
    // its scheduledSelectors_ dict will not get released!
    if (doCleanup)
    {
        child->cleanup();
    }

    // set parent nil at the end
    child->setParent(NULL);

    _children->removeObject(child);
}


// helper used by reorderChild & add
void CCNode::insertChild(CCNode* child, int z)
{
    _reorderChildDirty = true;
    ccArrayAppendObjectWithResize(_children->data, child);
    child->_setZOrder(z);
}

void CCNode::reorderChild(CCNode *child, int zOrder)
{
    CCAssert( child != NULL, "Child must be non-nil");
    _reorderChildDirty = true;
    child->setOrderOfArrival(s_globalOrderOfArrival++);
    child->_setZOrder(zOrder);
}

void CCNode::sortAllChildren()
{
    if (_reorderChildDirty)
    {
        int i,j,length = _children->data->num;
        CCNode ** x = (CCNode**)_children->data->arr;
        CCNode *tempItem;

        // insertion sort
        for(i=1; i<length; i++)
        {
            tempItem = x[i];
            j = i-1;

            //continue moving element downwards while zOrder is smaller or when zOrder is the same but mutatedIndex is smaller
            while(j>=0 && ( tempItem->_ZOrder < x[j]->_ZOrder || ( tempItem->_ZOrder== x[j]->_ZOrder && tempItem->_orderOfArrival < x[j]->_orderOfArrival ) ) )
            {
                x[j+1] = x[j];
                j = j-1;
            }
            x[j+1] = tempItem;
        }

        //don't need to check children recursively, that's done in visit of each child

        _reorderChildDirty = false;
    }
}


 void CCNode::draw()
 {
     //CCAssert(0);
     // override me
     // Only use- this function to draw your stuff.
     // DON'T draw your stuff outside this method
 }

void CCNode::visit()
{
    // quick return if not visible. children won't be drawn.
    if (!_visible)
    {
        return;
    }
    kmGLPushMatrix();

     if (_grid && _grid->isActive())
     {
         _grid->beforeDraw();
     }

    this->transform();

    CCNode* pNode = NULL;
    unsigned int i = 0;

    if(_children && _children->count() > 0)
    {
        sortAllChildren();
        // draw children zOrder < 0
        ccArray *arrayData = _children->data;
        for( ; i < arrayData->num; i++ )
        {
            pNode = (CCNode*) arrayData->arr[i];

            if ( pNode && pNode->_ZOrder < 0 ) 
            {
                pNode->visit();
            }
            else
            {
                break;
            }
        }
        // self draw
        this->draw();

        for( ; i < arrayData->num; i++ )
        {
            pNode = (CCNode*) arrayData->arr[i];
            if (pNode)
            {
                pNode->visit();
            }
        }        
    }
    else
    {
        this->draw();
    }

    // reset for next frame
    _orderOfArrival = 0;

     if (_grid && _grid->isActive())
     {
         _grid->afterDraw(this);
    }
 
    kmGLPopMatrix();
}

void CCNode::transformAncestors()
{
    if( _parent != NULL  )
    {
        _parent->transformAncestors();
        _parent->transform();
    }
}

void CCNode::transform()
{    
    kmMat4 transfrom4x4;

    // Convert 3x3 into 4x4 matrix
    CCAffineTransform tmpAffine = this->nodeToParentTransform();
    CGAffineToGL(&tmpAffine, transfrom4x4.mat);

    // Update Z vertex manually
    transfrom4x4.mat[14] = _vertexZ;

    kmGLMultMatrix( &transfrom4x4 );


    // XXX: Expensive calls. Camera should be integrated into the cached affine matrix
    if ( _camera != NULL && !(_grid != NULL && _grid->isActive()) )
    {
        bool translate = (_anchorPointInPoints.x != 0.0f || _anchorPointInPoints.y != 0.0f);

        if( translate )
            kmGLTranslatef(RENDER_IN_SUBPIXEL(_anchorPointInPoints.x), RENDER_IN_SUBPIXEL(_anchorPointInPoints.y), 0 );

        _camera->locate();

        if( translate )
            kmGLTranslatef(RENDER_IN_SUBPIXEL(-_anchorPointInPoints.x), RENDER_IN_SUBPIXEL(-_anchorPointInPoints.y), 0 );
    }

}


void CCNode::onEnter()
{
    _isTransitionFinished = false;

    arrayMakeObjectsPerformSelector(_children, onEnter, CCNode*);

    this->resumeSchedulerAndActions();

    _running = true;

    if (_scriptType != kScriptTypeNone)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeNodeEvent(this, kCCNodeOnEnter);
    }
}

void CCNode::onEnterTransitionDidFinish()
{
    _isTransitionFinished = true;

    arrayMakeObjectsPerformSelector(_children, onEnterTransitionDidFinish, CCNode*);

    if (_scriptType == kScriptTypeJavascript)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeNodeEvent(this, kCCNodeOnEnterTransitionDidFinish);
    }
}

void CCNode::onExitTransitionDidStart()
{
    arrayMakeObjectsPerformSelector(_children, onExitTransitionDidStart, CCNode*);

    if (_scriptType == kScriptTypeJavascript)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeNodeEvent(this, kCCNodeOnExitTransitionDidStart);
    }
}

void CCNode::onExit()
{
    this->pauseSchedulerAndActions();

    _running = false;

    if ( _scriptType != kScriptTypeNone)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeNodeEvent(this, kCCNodeOnExit);
    }

    arrayMakeObjectsPerformSelector(_children, onExit, CCNode*);    
}

void CCNode::registerScriptHandler(int nHandler)
{
    unregisterScriptHandler();
    _scriptHandler = nHandler;
    LUALOG("[LUA] Add CCNode event handler: %d", _scriptHandler);
}

void CCNode::unregisterScriptHandler(void)
{
    if (_scriptHandler)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(_scriptHandler);
        LUALOG("[LUA] Remove CCNode event handler: %d", _scriptHandler);
        _scriptHandler = 0;
    }
}

void CCNode::setActionManager(CCActionManager* actionManager)
{
    if( actionManager != _actionManager ) {
        this->stopAllActions();
        CC_SAFE_RETAIN(actionManager);
        CC_SAFE_RELEASE(_actionManager);
        _actionManager = actionManager;
    }
}

CCActionManager* CCNode::getActionManager()
{
    return _actionManager;
}

CCAction * CCNode::runAction(CCAction* action)
{
    CCAssert( action != NULL, "Argument must be non-nil");
    _actionManager->addAction(action, this, !_running);
    return action;
}

void CCNode::stopAllActions()
{
    _actionManager->removeAllActionsFromTarget(this);
}

void CCNode::stopAction(CCAction* action)
{
    _actionManager->removeAction(action);
}

void CCNode::stopActionByTag(int tag)
{
    CCAssert( tag != kCCActionTagInvalid, "Invalid tag");
    _actionManager->removeActionByTag(tag, this);
}

CCAction * CCNode::getActionByTag(int tag)
{
    CCAssert( tag != kCCActionTagInvalid, "Invalid tag");
    return _actionManager->getActionByTag(tag, this);
}

unsigned int CCNode::numberOfRunningActions()
{
    return _actionManager->numberOfRunningActionsInTarget(this);
}

// CCNode - Callbacks

void CCNode::setScheduler(CCScheduler* scheduler)
{
    if( scheduler != _scheduler ) {
        this->unscheduleAllSelectors();
        CC_SAFE_RETAIN(scheduler);
        CC_SAFE_RELEASE(_scheduler);
        _scheduler = scheduler;
    }
}

CCScheduler* CCNode::getScheduler()
{
    return _scheduler;
}

void CCNode::scheduleUpdate()
{
    scheduleUpdateWithPriority(0);
}

void CCNode::scheduleUpdateWithPriority(int priority)
{
    _scheduler->scheduleUpdateForTarget(this, priority, !_running);
}

void CCNode::scheduleUpdateWithPriorityLua(int nHandler, int priority)
{
    unscheduleUpdate();
    _updateScriptHandler = nHandler;
    _scheduler->scheduleUpdateForTarget(this, priority, !_running);
}

void CCNode::unscheduleUpdate()
{
    _scheduler->unscheduleUpdateForTarget(this);
    if (_updateScriptHandler)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(_updateScriptHandler);
        _updateScriptHandler = 0;
    }
}

void CCNode::schedule(SEL_SCHEDULE selector)
{
    this->schedule(selector, 0.0f, kCCRepeatForever, 0.0f);
}

void CCNode::schedule(SEL_SCHEDULE selector, float interval)
{
    this->schedule(selector, interval, kCCRepeatForever, 0.0f);
}

void CCNode::schedule(SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay)
{
    CCAssert( selector, "Argument must be non-nil");
    CCAssert( interval >=0, "Argument must be positive");

    _scheduler->scheduleSelector(selector, this, interval , repeat, delay, !_running);
}

void CCNode::scheduleOnce(SEL_SCHEDULE selector, float delay)
{
    this->schedule(selector, 0.0f, 0, delay);
}

void CCNode::unschedule(SEL_SCHEDULE selector)
{
    // explicit nil handling
    if (selector == 0)
        return;

    _scheduler->unscheduleSelector(selector, this);
}

void CCNode::unscheduleAllSelectors()
{
    _scheduler->unscheduleAllForTarget(this);
}

void CCNode::resumeSchedulerAndActions()
{
    _scheduler->resumeTarget(this);
    _actionManager->resumeTarget(this);
}

void CCNode::pauseSchedulerAndActions()
{
    _scheduler->pauseTarget(this);
    _actionManager->pauseTarget(this);
}

// override me
void CCNode::update(float fDelta)
{
    if (_updateScriptHandler)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeSchedule(_updateScriptHandler, fDelta, this);
    }
    
    if (_componentContainer && !_componentContainer->isEmpty())
    {
        _componentContainer->visit(fDelta);
    }
}

CCAffineTransform CCNode::nodeToParentTransform(void)
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
        if (! needsSkewMatrix && !_anchorPointInPoints.equals(CCPointZero))
        {
            x += cy * -_anchorPointInPoints.x * _scaleX + -sx * -_anchorPointInPoints.y * _scaleY;
            y += sy * -_anchorPointInPoints.x * _scaleX +  cx * -_anchorPointInPoints.y * _scaleY;
        }


        // Build Transform Matrix
        // Adjusted transform calculation for rotational skew
        _transform = CCAffineTransformMake( cy * _scaleX,  sy * _scaleX,
            -sx * _scaleY, cx * _scaleY,
            x, y );

        // XXX: Try to inline skew
        // If skew is needed, apply skew and then anchor point
        if (needsSkewMatrix) 
        {
            CCAffineTransform skewMatrix = CCAffineTransformMake(1.0f, tanf(CC_DEGREES_TO_RADIANS(_skewY)),
                tanf(CC_DEGREES_TO_RADIANS(_skewX)), 1.0f,
                0.0f, 0.0f );
            _transform = CCAffineTransformConcat(skewMatrix, _transform);

            // adjust anchor point
            if (!_anchorPointInPoints.equals(CCPointZero))
            {
                _transform = CCAffineTransformTranslate(_transform, -_anchorPointInPoints.x, -_anchorPointInPoints.y);
            }
        }
        
        if (_additionalTransformDirty)
        {
            _transform = CCAffineTransformConcat(_transform, _additionalTransform);
            _additionalTransformDirty = false;
        }

        _transformDirty = false;
    }

    return _transform;
}

void CCNode::setAdditionalTransform(const CCAffineTransform& additionalTransform)
{
    _additionalTransform = additionalTransform;
    _transformDirty = true;
    _additionalTransformDirty = true;
}

CCAffineTransform CCNode::parentToNodeTransform(void)
{
    if ( _inverseDirty ) {
        _inverse = CCAffineTransformInvert(this->nodeToParentTransform());
        _inverseDirty = false;
    }

    return _inverse;
}

CCAffineTransform CCNode::nodeToWorldTransform()
{
    CCAffineTransform t = this->nodeToParentTransform();

    for (CCNode *p = _parent; p != NULL; p = p->getParent())
        t = CCAffineTransformConcat(t, p->nodeToParentTransform());

    return t;
}

CCAffineTransform CCNode::worldToNodeTransform(void)
{
    return CCAffineTransformInvert(this->nodeToWorldTransform());
}

CCPoint CCNode::convertToNodeSpace(const CCPoint& worldPoint)
{
    CCPoint ret = CCPointApplyAffineTransform(worldPoint, worldToNodeTransform());
    return ret;
}

CCPoint CCNode::convertToWorldSpace(const CCPoint& nodePoint)
{
    CCPoint ret = CCPointApplyAffineTransform(nodePoint, nodeToWorldTransform());
    return ret;
}

CCPoint CCNode::convertToNodeSpaceAR(const CCPoint& worldPoint)
{
    CCPoint nodePoint = convertToNodeSpace(worldPoint);
    return ccpSub(nodePoint, _anchorPointInPoints);
}

CCPoint CCNode::convertToWorldSpaceAR(const CCPoint& nodePoint)
{
    CCPoint pt = ccpAdd(nodePoint, _anchorPointInPoints);
    return convertToWorldSpace(pt);
}

CCPoint CCNode::convertToWindowSpace(const CCPoint& nodePoint)
{
    CCPoint worldPoint = this->convertToWorldSpace(nodePoint);
    return CCDirector::sharedDirector()->convertToUI(worldPoint);
}

// convenience methods which take a CCTouch instead of CCPoint
CCPoint CCNode::convertTouchToNodeSpace(CCTouch *touch)
{
    CCPoint point = touch->getLocation();
    return this->convertToNodeSpace(point);
}
CCPoint CCNode::convertTouchToNodeSpaceAR(CCTouch *touch)
{
    CCPoint point = touch->getLocation();
    return this->convertToNodeSpaceAR(point);
}

void CCNode::updateTransform()
{
    // Recursively iterate over children
    arrayMakeObjectsPerformSelector(_children, updateTransform, CCNode*);
}

CCComponent* CCNode::getComponent(const char *pName) const
{
    return _componentContainer->get(pName);
}

bool CCNode::addComponent(CCComponent *pComponent)
{
    return _componentContainer->add(pComponent);
}

bool CCNode::removeComponent(const char *pName)
{
    return _componentContainer->remove(pName);
}

void CCNode::removeAllComponents()
{
    _componentContainer->removeAll();
}

// CCNodeRGBA
CCNodeRGBA::CCNodeRGBA()
: _displayedOpacity(255)
, _realOpacity(255)
, _displayedColor(ccWHITE)
, _realColor(ccWHITE)
, _cascadeColorEnabled(false)
, _cascadeOpacityEnabled(false)
{}

CCNodeRGBA::~CCNodeRGBA() {}

bool CCNodeRGBA::init()
{
    if (CCNode::init())
    {
        _displayedOpacity = _realOpacity = 255;
        _displayedColor = _realColor = ccWHITE;
        _cascadeOpacityEnabled = _cascadeColorEnabled = false;
        return true;
    }
    return false;
}

GLubyte CCNodeRGBA::getOpacity(void)
{
	return _realOpacity;
}

GLubyte CCNodeRGBA::getDisplayedOpacity(void)
{
	return _displayedOpacity;
}

void CCNodeRGBA::setOpacity(GLubyte opacity)
{
    _displayedOpacity = _realOpacity = opacity;
    
	if (_cascadeOpacityEnabled)
    {
		GLubyte parentOpacity = 255;
        CCRGBAProtocol* pParent = dynamic_cast<CCRGBAProtocol*>(_parent);
        if (pParent && pParent->isCascadeOpacityEnabled())
        {
            parentOpacity = pParent->getDisplayedOpacity();
        }
        this->updateDisplayedOpacity(parentOpacity);
	}
}

void CCNodeRGBA::updateDisplayedOpacity(GLubyte parentOpacity)
{
	_displayedOpacity = _realOpacity * parentOpacity/255.0;
	
    if (_cascadeOpacityEnabled)
    {
        CCObject* pObj;
        CCARRAY_FOREACH(_children, pObj)
        {
            CCRGBAProtocol* item = dynamic_cast<CCRGBAProtocol*>(pObj);
            if (item)
            {
                item->updateDisplayedOpacity(_displayedOpacity);
            }
        }
    }
}

bool CCNodeRGBA::isCascadeOpacityEnabled(void)
{
    return _cascadeOpacityEnabled;
}

void CCNodeRGBA::setCascadeOpacityEnabled(bool cascadeOpacityEnabled)
{
    _cascadeOpacityEnabled = cascadeOpacityEnabled;
}

const ccColor3B& CCNodeRGBA::getColor(void)
{
	return _realColor;
}

const ccColor3B& CCNodeRGBA::getDisplayedColor()
{
	return _displayedColor;
}

void CCNodeRGBA::setColor(const ccColor3B& color)
{
	_displayedColor = _realColor = color;
	
	if (_cascadeColorEnabled)
    {
		ccColor3B parentColor = ccWHITE;
        CCRGBAProtocol *parent = dynamic_cast<CCRGBAProtocol*>(_parent);
		if (parent && parent->isCascadeColorEnabled())
        {
            parentColor = parent->getDisplayedColor(); 
        }
        
        updateDisplayedColor(parentColor);
	}
}

void CCNodeRGBA::updateDisplayedColor(const ccColor3B& parentColor)
{
	_displayedColor.r = _realColor.r * parentColor.r/255.0;
	_displayedColor.g = _realColor.g * parentColor.g/255.0;
	_displayedColor.b = _realColor.b * parentColor.b/255.0;
    
    if (_cascadeColorEnabled)
    {
        CCObject *obj = NULL;
        CCARRAY_FOREACH(_children, obj)
        {
            CCRGBAProtocol *item = dynamic_cast<CCRGBAProtocol*>(obj);
            if (item)
            {
                item->updateDisplayedColor(_displayedColor);
            }
        }
    }
}

bool CCNodeRGBA::isCascadeColorEnabled(void)
{
    return _cascadeColorEnabled;
}

void CCNodeRGBA::setCascadeColorEnabled(bool cascadeColorEnabled)
{
    _cascadeColorEnabled = cascadeColorEnabled;
}

NS_CC_END
