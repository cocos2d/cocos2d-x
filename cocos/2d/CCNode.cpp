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

#include "2d/CCNode.h"

#include <algorithm>
#include <string>
#include <regex>

#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "base/CCTouch.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEvent.h"
#include "base/CCEventTouch.h"
#include "base/ccCArray.h"
#include "2d/CCGrid.h"
#include "2d/CCActionManager.h"
#include "base/CCScriptSupport.h"
#include "2d/CCScene.h"
#include "2d/CCComponent.h"
#include "2d/CCComponentContainer.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramState.h"
#include "math/TransformUtils.h"

#include "deprecated/CCString.h"

#if CC_USE_PHYSICS
#include "physics/CCPhysicsBody.h"
#endif


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
int Node::s_globalOrderOfArrival = 1;

Node::Node(void)
: _rotationX(0.0f)
, _rotationY(0.0f)
, _rotationZ_X(0.0f)
, _rotationZ_Y(0.0f)
, _scaleX(1.0f)
, _scaleY(1.0f)
, _scaleZ(1.0f)
, _positionZ(0.0f)
, _position(Vec2::ZERO)
, _skewX(0.0f)
, _skewY(0.0f)
, _anchorPointInPoints(Vec2::ZERO)
, _anchorPoint(Vec2::ZERO)
, _contentSize(Size::ZERO)
, _useAdditionalTransform(false)
, _transformDirty(true)
, _inverseDirty(true)
, _transformUpdated(true)
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
, _glProgramState(nullptr)
, _orderOfArrival(0)
, _running(false)
, _visible(true)
, _ignoreAnchorPointForPosition(false)
, _reorderChildDirty(false)
, _isTransitionFinished(false)
#if CC_ENABLE_SCRIPT_BINDING
, _updateScriptHandler(0)
#endif
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
, _usingNormalizedPosition(false)
, _name("")
, _hashOfName(0)
{
    // set default scheduler and actionManager
    Director *director = Director::getInstance();
    _actionManager = director->getActionManager();
    _actionManager->retain();
    _scheduler = director->getScheduler();
    _scheduler->retain();
    _eventDispatcher = director->getEventDispatcher();
    _eventDispatcher->retain();
    
#if CC_ENABLE_SCRIPT_BINDING
    ScriptEngineProtocol* engine = ScriptEngineManager::getInstance()->getScriptEngine();
    _scriptType = engine != nullptr ? engine->getScriptType() : kScriptTypeNone;
#endif
    _transform = _inverse = _additionalTransform = Mat4::IDENTITY;
}

Node::~Node()
{
    CCLOGINFO( "deallocing Node: %p - tag: %i", this, _tag );
    
#if CC_ENABLE_SCRIPT_BINDING
    if (_updateScriptHandler)
    {
        ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptHandler(_updateScriptHandler);
    }
#endif

    // User object has to be released before others, since userObject may have a weak reference of this node
    // It may invoke `node->stopAllAction();` while `_actionManager` is null if the next line is after `CC_SAFE_RELEASE_NULL(_actionManager)`.
    CC_SAFE_RELEASE_NULL(_userObject);
    
    // attributes
    CC_SAFE_RELEASE_NULL(_glProgramState);

    for (auto& child : _children)
    {
        child->_parent = nullptr;
    }

    removeAllComponents();
    
    CC_SAFE_DELETE(_componentContainer);
    
#if CC_USE_PHYSICS
    setPhysicsBody(nullptr);

#endif
    
    CC_SAFE_RELEASE_NULL(_actionManager);
    CC_SAFE_RELEASE_NULL(_scheduler);
    
    _eventDispatcher->removeEventListenersForTarget(this);
    
#if CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS && COCOS2D_DEBUG > 0
    _eventDispatcher->debugCheckNodeHasNoEventListenersOnDestruction(this);
#endif

    CCASSERT(!_running, "Node still marked as running on node destruction! Was base class onExit() called in derived class onExit() implementations?");
    CC_SAFE_RELEASE(_eventDispatcher);
}

bool Node::init()
{
    return true;
}

float Node::getSkewX() const
{
    return _skewX;
}

void Node::setSkewX(float skewX)
{
    if (_skewX == skewX)
        return;
    
    _skewX = skewX;
    _transformUpdated = _transformDirty = _inverseDirty = true;
}

float Node::getSkewY() const
{
    return _skewY;
}

void Node::setSkewY(float skewY)
{
    if (_skewY == skewY)
        return;
    
    _skewY = skewY;
    _transformUpdated = _transformDirty = _inverseDirty = true;
}


/// zOrder setter : private method
/// used internally to alter the zOrder variable. DON'T call this method manually 
void Node::_setLocalZOrder(int z)
{
    _localZOrder = z;
}

void Node::setLocalZOrder(int z)
{
    if (_localZOrder == z)
        return;
    
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

/// rotation getter
float Node::getRotation() const
{
    CCASSERT(_rotationZ_X == _rotationZ_Y, "CCNode#rotation. RotationX != RotationY. Don't know which one to return");
    return _rotationZ_X;
}

/// rotation setter
void Node::setRotation(float rotation)
{
    if (_rotationZ_X == rotation)
        return;
    
    _rotationZ_X = _rotationZ_Y = rotation;
    _transformUpdated = _transformDirty = _inverseDirty = true;

#if CC_USE_PHYSICS
    if (_physicsBody && !_physicsBody->_rotationResetTag)
    {
        Scene* scene = _physicsBody->getWorld() != nullptr ? &_physicsBody->getWorld()->getScene() : nullptr;
        updatePhysicsBodyRotation(scene);
    }
#endif
}

float Node::getRotationSkewX() const
{
    return _rotationZ_X;
}

void Node::setRotation3D(const Vec3& rotation)
{
    if (_rotationX == rotation.x &&
        _rotationY == rotation.y &&
        _rotationZ_X == rotation.z)
        return;
    
    _transformUpdated = _transformDirty = _inverseDirty = true;

    _rotationX = rotation.x;
    _rotationY = rotation.y;

    // rotation Z is decomposed in 2 to simulate Skew for Flash animations
    _rotationZ_Y = _rotationZ_X = rotation.z;

#if CC_USE_PHYSICS
    if (_physicsBody)
    {
        Scene* scene = _physicsBody->getWorld() != nullptr ? &_physicsBody->getWorld()->getScene() : nullptr;
        updatePhysicsBodyRotation(scene);
    }
#endif
}

Vec3 Node::getRotation3D() const
{
    // rotation Z is decomposed in 2 to simulate Skew for Flash animations
    CCASSERT(_rotationZ_X == _rotationZ_Y, "_rotationZ_X != _rotationZ_Y");

    return Vec3(_rotationX,_rotationY,_rotationZ_X);
}

void Node::setRotationSkewX(float rotationX)
{
    if (_rotationZ_X == rotationX)
        return;
    
    _rotationZ_X = rotationX;
    _transformUpdated = _transformDirty = _inverseDirty = true;
}

float Node::getRotationSkewY() const
{
    return _rotationZ_Y;
}

void Node::setRotationSkewY(float rotationY)
{
    if (_rotationZ_Y == rotationY)
        return;
    
    _rotationZ_Y = rotationY;
    _transformUpdated = _transformDirty = _inverseDirty = true;
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
    if (_scaleX == scale)
        return;

    _scaleX = _scaleY = _scaleZ = scale;
    _transformUpdated = _transformDirty = _inverseDirty = true;
}

/// scaleX getter
float Node::getScaleX() const
{
    return _scaleX;
}

/// scale setter
void Node::setScale(float scaleX,float scaleY)
{
    if (_scaleX == scaleX && _scaleY == scaleY)
        return;
    
    _scaleX = scaleX;
    _scaleY = scaleY;
    _transformUpdated = _transformDirty = _inverseDirty = true;
}

/// scaleX setter
void Node::setScaleX(float scaleX)
{
    if (_scaleX == scaleX)
        return;
    
    _scaleX = scaleX;
    _transformUpdated = _transformDirty = _inverseDirty = true;
}

/// scaleY getter
float Node::getScaleY() const
{
    return _scaleY;
}

/// scaleY setter
void Node::setScaleZ(float scaleZ)
{
    if (_scaleZ == scaleZ)
        return;
    
    _scaleZ = scaleZ;
    _transformUpdated = _transformDirty = _inverseDirty = true;
}

/// scaleY getter
float Node::getScaleZ() const
{
    return _scaleZ;
}

/// scaleY setter
void Node::setScaleY(float scaleY)
{
    if (_scaleY == scaleY)
        return;
    
    _scaleY = scaleY;
    _transformUpdated = _transformDirty = _inverseDirty = true;
}


/// position getter
const Vec2& Node::getPosition() const
{
    return _position;
}

/// position setter
void Node::setPosition(const Vec2& position)
{
    if (_position.equals(position))
        return;
    
    _position = position;
    _transformUpdated = _transformDirty = _inverseDirty = true;
    _usingNormalizedPosition = false;

#if CC_USE_PHYSICS
    if (_physicsBody != nullptr && !_physicsBody->_positionResetTag)
    {
        Scene* scene = _physicsBody->getWorld() != nullptr ? &_physicsBody->getWorld()->getScene() : nullptr;
        updatePhysicsBodyPosition(scene);
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
    setPosition(Vec2(x, y));
}

void Node::setPosition3D(const Vec3& position)
{
    _positionZ = position.z;
    setPosition(Vec2(position.x, position.y));
}

Vec3 Node::getPosition3D() const
{
    Vec3 ret;
    ret.x = _position.x;
    ret.y = _position.y;
    ret.z = _positionZ;
    return ret;
}

float Node::getPositionX() const
{
    return _position.x;
}

void Node::setPositionX(float x)
{
    setPosition(Vec2(x, _position.y));
}

float Node::getPositionY() const
{
    return  _position.y;
}

void Node::setPositionY(float y)
{
    setPosition(Vec2(_position.x, y));
}

float Node::getPositionZ() const
{
    return _positionZ;
}

void Node::setPositionZ(float positionZ)
{
    if (_positionZ == positionZ)
        return;
    
    _transformUpdated = _transformDirty = _inverseDirty = true;

    _positionZ = positionZ;

    // XXX BUG
    // Global Z Order should based on the modelViewTransform
    setGlobalZOrder(positionZ);
}

/// position getter
const Vec2& Node::getNormalizedPosition() const
{
    return _normalizedPosition;
}

/// position setter
void Node::setNormalizedPosition(const Vec2& position)
{
    if (_normalizedPosition.equals(position))
        return;

    _normalizedPosition = position;
    _usingNormalizedPosition = true;
    _transformUpdated = _transformDirty = _inverseDirty = true;
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
void Node::setVisible(bool visible)
{
    if(visible != _visible)
    {
        _visible = visible;
        if(_visible) _transformUpdated = _transformDirty = _inverseDirty = true;
    }
}

const Vec2& Node::getAnchorPointInPoints() const
{
    return _anchorPointInPoints;
}

/// anchorPoint getter
const Vec2& Node::getAnchorPoint() const
{
    return _anchorPoint;
}

void Node::setAnchorPoint(const Vec2& point)
{
#if CC_USE_PHYSICS
    if (_physicsBody != nullptr && !point.equals(Vec2::ANCHOR_MIDDLE))
    {
        CCLOG("Node warning: This node has a physics body, the anchor must be in the middle, you cann't change this to other value.");
        return;
    }
#endif
    
    if( ! point.equals(_anchorPoint))
    {
        _anchorPoint = point;
        _anchorPointInPoints = Vec2(_contentSize.width * _anchorPoint.x, _contentSize.height * _anchorPoint.y );
        _transformUpdated = _transformDirty = _inverseDirty = true;
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

        _anchorPointInPoints = Vec2(_contentSize.width * _anchorPoint.x, _contentSize.height * _anchorPoint.y );
        _transformUpdated = _transformDirty = _inverseDirty = _contentSizeDirty = true;
    }
}

// isRunning getter
bool Node::isRunning() const
{
    return _running;
}

/// parent setter
void Node::setParent(Node * parent)
{
    _parent = parent;
    _transformUpdated = _transformDirty = _inverseDirty = true;
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
        _transformUpdated = _transformDirty = _inverseDirty = true;
	}
}

/// tag getter
int Node::getTag() const
{
    return _tag;
}

/// tag setter
void Node::setTag(int tag)
{
    _tag = tag ;
}

std::string Node::getName() const
{
    return _name;
}

void Node::setName(const std::string& name)
{
    _name = name;
    std::hash<std::string> h;
    _hashOfName = h(name);
}

/// userData setter
void Node::setUserData(void *userData)
{
    _userData = userData;
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

void Node::setUserObject(Ref *userObject)
{
    CC_SAFE_RETAIN(userObject);
    CC_SAFE_RELEASE(_userObject);
    _userObject = userObject;
}

GLProgramState* Node::getGLProgramState() const
{
    return _glProgramState;
}

void Node::setGLProgramState(cocos2d::GLProgramState *glProgramState)
{
    if(glProgramState != _glProgramState) {
        CC_SAFE_RELEASE(_glProgramState);
        _glProgramState = glProgramState;
        CC_SAFE_RETAIN(_glProgramState);
    }
}

void Node::setGLProgram(GLProgram *glProgram)
{
    if (_glProgramState == nullptr || (_glProgramState && _glProgramState->getGLProgram() != glProgram))
    {
        CC_SAFE_RELEASE(_glProgramState);
        _glProgramState = GLProgramState::getOrCreateWithGLProgram(glProgram);
        _glProgramState->retain();
    }
}

GLProgram * Node::getGLProgram() const
{
    return _glProgramState ? _glProgramState->getGLProgram() : nullptr;
}

Scene* Node::getScene() const
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

Node * Node::create()
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
    
#if CC_ENABLE_SCRIPT_BINDING
    if ( _scriptType != kScriptTypeNone)
    {
        int action = kNodeOnCleanup;
        BasicScriptData data(this,(void*)&action);
        ScriptEvent scriptEvent(kNodeEvent,(void*)&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&scriptEvent);
    }
#endif // #if CC_ENABLE_SCRIPT_BINDING
    
    // timers
    for( const auto &child: _children)
        child->cleanup();
}


std::string Node::getDescription() const
{
    return StringUtils::format("<Node | Tag = %d", _tag);
}

// lazy allocs
void Node::childrenAlloc()
{
    _children.reserve(4);
}

Node* Node::getChildByTag(int tag) const
{
    CCASSERT( tag != Node::INVALID_TAG, "Invalid tag");

    for (auto& child : _children)
    {
        if(child && child->_tag == tag)
            return child;
    }
    return nullptr;
}

Node* Node::getChildByName(const std::string& name) const
{
    CCASSERT(name.length() != 0, "Invalid name");
    
    std::hash<std::string> h;
    size_t hash = h(name);
    
    for (const auto& child : _children)
    {
        // Different strings may have the same hash code, but can use it to compare first for speed
        if(child->_hashOfName == hash && child->_name.compare(name) == 0)
            return child;
    }
    return nullptr;
}

void Node::enumerateChildren(const std::string &name, std::function<bool (Node *)> callback) const
{
    CCASSERT(name.length() != 0, "Invalid name");
    CCASSERT(callback != nullptr, "Invalid callback function");
    
    size_t length = name.length();
    
    size_t subStrStartPos = 0;  // sub string start index
    size_t subStrlength = length; // sub string length
    
    // Starts with '/' or '//'?
    bool searchFromRoot = false;
    bool searchFromRootRecursive = false;
    if (name[0] == '/')
    {
        if (length > 2 && name[1] == '/')
        {
            searchFromRootRecursive = true;
            subStrStartPos = 2;
            subStrlength -= 2;
        }
        else
        {
            searchFromRoot = true;
            subStrStartPos = 1;
            subStrlength -= 1;
        }
    }
    
    // End with '/..'?
    bool searchFromParent = false;
    if (length > 3 &&
        name[length-3] == '/' &&
        name[length-2] == '.' &&
        name[length-1] == '.')
    {
        searchFromParent = true;
        subStrlength -= 3;
    }
    
    // Remove '/', '//' and '/..' if exist
    std::string newName = name.substr(subStrStartPos, subStrlength);
    // If search from parent, then add * at first to make it match its children, which will do make
    if (searchFromParent)
    {
        newName.insert(0, "[[:alnum:]]+/");
    }
    
    if (searchFromRoot)
    {
        // name is '/xxx'
        auto root = getScene();
        if (root)
        {
            root->doEnumerate(newName, callback);
        }
    }
    else if (searchFromRootRecursive)
    {
        // name is '//xxx'
        auto root = getScene();
        if (root)
        {
            doEnumerateRecursive(root, newName, callback);
        }
    }
    else
    {
        // name is xxx
        doEnumerate(newName, callback);
    }
}

bool Node::doEnumerateRecursive(const Node* node, const std::string &name, std::function<bool (Node *)> callback) const
{
    bool ret =false;
    
    if (node->doEnumerate(name, callback))
    {
        // search itself
        ret = true;
    }
    else
    {
        // search its children
        for (const auto& child : node->getChildren())
        {
            if (doEnumerateRecursive(child, name, callback))
            {
                ret = true;
                break;
            }
        }
    }
    
    return ret;
}

bool Node::doEnumerate(std::string name, std::function<bool (Node *)> callback) const
{
    // name may be xxx/yyy, should find its parent
    size_t pos = name.find('/');
    std::string searchName = name;
    bool needRecursive = false;
    if (pos != name.npos)
    {
        searchName = name.substr(0, pos);
        name.erase(0, pos+1);
        needRecursive = true;
    }
    
    bool ret = false;
    for (const auto& child : _children)
    {
        if(std::regex_match(child->_name, std::regex(searchName)))
        {
            if (!needRecursive)
            {
                // terminate enumeration if callback return true
                if (callback(child))
                {
                    ret = true;
                    break;
                }
            }
            else
            {
                ret = child->doEnumerate(name, callback);
                if (ret)
                    break;
            }
        }
    }
    
    return ret;
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

    child->_tag = tag;

    child->setParent(this);
    child->setOrderOfArrival(s_globalOrderOfArrival++);
    
#if CC_USE_PHYSICS
    // Recursive add children with which have physics body.
    for (Node* node = this; node != nullptr; node = node->getParent())
    {
        Scene* scene = dynamic_cast<Scene*>(node);
        if (scene != nullptr && scene->getPhysicsWorld() != nullptr)
        {
            scene->addChildToPhysicsWorld(child);
            break;
        }
    }
#endif

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

#if CC_USE_PHYSICS
        if (child->_physicsBody != nullptr)
        {
            child->_physicsBody->removeFromWorld();
        }
#endif

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
    _transformUpdated = true;
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
    auto renderer = Director::getInstance()->getRenderer();
    draw(renderer, _modelViewTransform, true);
}

void Node::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
}

void Node::visit()
{
    auto renderer = Director::getInstance()->getRenderer();
    Mat4 parentTransform = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    visit(renderer, parentTransform, true);
}

uint32_t Node::processParentFlags(const Mat4& parentTransform, uint32_t parentFlags)
{
    uint32_t flags = parentFlags;
    flags |= (_transformUpdated ? FLAGS_TRANSFORM_DIRTY : 0);
    flags |= (_contentSizeDirty ? FLAGS_CONTENT_SIZE_DIRTY : 0);

    if(_usingNormalizedPosition && (flags & FLAGS_CONTENT_SIZE_DIRTY)) {
        CCASSERT(_parent, "setNormalizedPosition() doesn't work with orphan nodes");
        auto s = _parent->getContentSize();
        _position.x = _normalizedPosition.x * s.width;
        _position.y = _normalizedPosition.y * s.height;
        _transformUpdated = _transformDirty = _inverseDirty = true;
    }

    if(flags & FLAGS_DIRTY_MASK)
        _modelViewTransform = this->transform(parentTransform);

    _transformUpdated = false;
    _contentSizeDirty = false;

    return flags;
}

void Node::visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    // quick return if not visible. children won't be drawn.
    if (!_visible)
    {
        return;
    }

    uint32_t flags = processParentFlags(parentTransform, parentFlags);

    // IMPORTANT:
    // To ease the migration to v3.0, we still support the Mat4 stack,
    // but it is deprecated and your code should not rely on it
    Director* director = Director::getInstance();
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);

    int i = 0;

    if(!_children.empty())
    {
        sortAllChildren();
        // draw children zOrder < 0
        for( ; i < _children.size(); i++ )
        {
            auto node = _children.at(i);

            if ( node && node->_localZOrder < 0 )
                node->visit(renderer, _modelViewTransform, flags);
            else
                break;
        }
        // self draw
        this->draw(renderer, _modelViewTransform, flags);

        for(auto it=_children.cbegin()+i; it != _children.cend(); ++it)
            (*it)->visit(renderer, _modelViewTransform, flags);
    }
    else
    {
        this->draw(renderer, _modelViewTransform, flags);
    }

    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

Mat4 Node::transform(const Mat4& parentTransform)
{
    Mat4 ret = this->getNodeToParentTransform();
    ret  = parentTransform * ret;
    return ret;
}

void Node::onEnter()
{
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeJavascript)
    {
        if (ScriptEngineManager::sendNodeEventToJS(this, kNodeOnEnter))
            return;
    }
#endif
    
    _isTransitionFinished = false;
    
    for( const auto &child: _children)
        child->onEnter();
    
    this->resume();
    
    _running = true;
    
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeLua)
    {
        ScriptEngineManager::sendNodeEventToLua(this, kNodeOnEnter);
    }
#endif
}

void Node::onEnterTransitionDidFinish()
{
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeJavascript)
    {
        if (ScriptEngineManager::sendNodeEventToJS(this, kNodeOnEnterTransitionDidFinish))
            return;
    }
#endif

    _isTransitionFinished = true;
    for( const auto &child: _children)
        child->onEnterTransitionDidFinish();
    
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeLua)
    {
        ScriptEngineManager::sendNodeEventToLua(this, kNodeOnEnterTransitionDidFinish);
    }
#endif
}

void Node::onExitTransitionDidStart()
{
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeJavascript)
    {
        if (ScriptEngineManager::sendNodeEventToJS(this, kNodeOnExitTransitionDidStart))
            return;
    }
#endif
    
    for( const auto &child: _children)
        child->onExitTransitionDidStart();
    
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeLua)
    {
        ScriptEngineManager::sendNodeEventToLua(this, kNodeOnExitTransitionDidStart);
    }
#endif
}

void Node::onExit()
{
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeJavascript)
    {
        if (ScriptEngineManager::sendNodeEventToJS(this, kNodeOnExit))
            return;
    }
#endif
    
    this->pause();
    
    _running = false;
    
    for( const auto &child: _children)
        child->onExit();
    
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeLua)
    {
        ScriptEngineManager::sendNodeEventToLua(this, kNodeOnExit);
    }
#endif
}

void Node::setEventDispatcher(EventDispatcher* dispatcher)
{
    if (dispatcher != _eventDispatcher)
    {
        _eventDispatcher->removeEventListenersForTarget(this);
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
    return _scheduler->isScheduled(selector, this);
}

void Node::scheduleUpdate()
{
    scheduleUpdateWithPriority(0);
}

void Node::scheduleUpdateWithPriority(int priority)
{
    _scheduler->scheduleUpdate(this, priority, !_running);
}

void Node::scheduleUpdateWithPriorityLua(int nHandler, int priority)
{
    unscheduleUpdate();
    
#if CC_ENABLE_SCRIPT_BINDING
    _updateScriptHandler = nHandler;
#endif
    
    _scheduler->scheduleUpdate(this, priority, !_running);
}

void Node::unscheduleUpdate()
{
    _scheduler->unscheduleUpdate(this);
    
#if CC_ENABLE_SCRIPT_BINDING
    if (_updateScriptHandler)
    {
        ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptHandler(_updateScriptHandler);
        _updateScriptHandler = 0;
    }
#endif
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

    _scheduler->schedule(selector, this, interval , repeat, delay, !_running);
}

void Node::scheduleOnce(SEL_SCHEDULE selector, float delay)
{
    this->schedule(selector, 0.0f, 0, delay);
}

void Node::unschedule(SEL_SCHEDULE selector)
{
    // explicit null handling
    if (selector == nullptr)
        return;
    
    _scheduler->unschedule(selector, this);
}

void Node::unscheduleAllSelectors()
{
    _scheduler->unscheduleAllForTarget(this);
}

void Node::resume()
{
    _scheduler->resumeTarget(this);
    _actionManager->resumeTarget(this);
    _eventDispatcher->resumeEventListenersForTarget(this);
}

void Node::pause()
{
    _scheduler->pauseTarget(this);
    _actionManager->pauseTarget(this);
    _eventDispatcher->pauseEventListenersForTarget(this);
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
#if CC_ENABLE_SCRIPT_BINDING
    if (0 != _updateScriptHandler)
    {
        //only lua use
        SchedulerScriptData data(_updateScriptHandler,fDelta);
        ScriptEvent event(kScheduleEvent,&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
    }
#endif
    
    if (_componentContainer && !_componentContainer->isEmpty())
    {
        _componentContainer->visit(fDelta);
    }
}

AffineTransform Node::getNodeToParentAffineTransform() const
{
    AffineTransform ret;
    GLToCGAffine(getNodeToParentTransform().m, &ret);

    return ret;
}

const Mat4& Node::getNodeToParentTransform() const
{
    if (_transformDirty)
    {
        // Translate values
        float x = _position.x;
        float y = _position.y;
        float z = _positionZ;

        if (_ignoreAnchorPointForPosition)
        {
            x += _anchorPointInPoints.x;
            y += _anchorPointInPoints.y;
        }

        // Rotation values
		// Change rotation code to handle X and Y
		// If we skew with the exact same value for both x and y then we're simply just rotating
        float cx = 1, sx = 0, cy = 1, sy = 0;
        if (_rotationZ_X || _rotationZ_Y)
        {
            float radiansX = -CC_DEGREES_TO_RADIANS(_rotationZ_X);
            float radiansY = -CC_DEGREES_TO_RADIANS(_rotationZ_Y);
            cx = cosf(radiansX);
            sx = sinf(radiansX);
            cy = cosf(radiansY);
            sy = sinf(radiansY);
        }

        bool needsSkewMatrix = ( _skewX || _skewY );


        // optimization:
        // inline anchor point calculation if skew is not needed
        // Adjusted transform calculation for rotational skew
        if (! needsSkewMatrix && !_anchorPointInPoints.equals(Vec2::ZERO))
        {
            x += cy * -_anchorPointInPoints.x * _scaleX + -sx * -_anchorPointInPoints.y * _scaleY;
            y += sy * -_anchorPointInPoints.x * _scaleX +  cx * -_anchorPointInPoints.y * _scaleY;
        }


        // Build Transform Matrix
        // Adjusted transform calculation for rotational skew
        float mat[] = {
                        cy * _scaleX,   sy * _scaleX,   0,          0,
                        -sx * _scaleY,  cx * _scaleY,   0,          0,
                        0,              0,              _scaleZ,    0,
                        x,              y,              z,          1 };
        
        _transform.set(mat);

        // XXX
        // FIX ME: Expensive operation.
        // FIX ME: It should be done together with the rotationZ
        if(_rotationY) {
            Mat4 rotY;
            Mat4::createRotationY(CC_DEGREES_TO_RADIANS(_rotationY), &rotY);
            _transform = _transform * rotY;
        }
        if(_rotationX) {
            Mat4 rotX;
            Mat4::createRotationX(CC_DEGREES_TO_RADIANS(_rotationX), &rotX);
            _transform = _transform * rotX;
        }

        // XXX: Try to inline skew
        // If skew is needed, apply skew and then anchor point
        if (needsSkewMatrix)
        {
            Mat4 skewMatrix(1, (float)tanf(CC_DEGREES_TO_RADIANS(_skewY)), 0, 0,
                              (float)tanf(CC_DEGREES_TO_RADIANS(_skewX)), 1, 0, 0,
                              0,  0,  1, 0,
                              0,  0,  0, 1);

            _transform = _transform * skewMatrix;

            // adjust anchor point
            if (!_anchorPointInPoints.equals(Vec2::ZERO))
            {
                // XXX: Argh, Mat4 needs a "translate" method.
                // XXX: Although this is faster than multiplying a vec4 * mat4
                _transform.m[12] += _transform.m[0] * -_anchorPointInPoints.x + _transform.m[4] * -_anchorPointInPoints.y;
                _transform.m[13] += _transform.m[1] * -_anchorPointInPoints.x + _transform.m[5] * -_anchorPointInPoints.y;
            }
        }

        if (_useAdditionalTransform)
        {
            _transform = _transform * _additionalTransform;
        }

        _transformDirty = false;
    }

    return _transform;
}

void Node::setNodeToParentTransform(const Mat4& transform)
{
    _transform = transform;
    _transformDirty = false;
    _transformUpdated = true;
}

void Node::setAdditionalTransform(const AffineTransform& additionalTransform)
{
    Mat4 tmp;
    CGAffineToGL(additionalTransform, tmp.m);
    setAdditionalTransform(&tmp);
}

void Node::setAdditionalTransform(Mat4* additionalTransform)
{
    if(additionalTransform == nullptr) {
        _useAdditionalTransform = false;
    } else {
        _additionalTransform = *additionalTransform;
        _useAdditionalTransform = true;
    }
    _transformUpdated = _transformDirty = _inverseDirty = true;
}


AffineTransform Node::getParentToNodeAffineTransform() const
{
    AffineTransform ret;
    Mat4 ret4 = getParentToNodeTransform();

    GLToCGAffine(ret4.m,&ret);
    return ret;
}

const Mat4& Node::getParentToNodeTransform() const
{
    if ( _inverseDirty ) {
        _inverse = _transform.getInversed();
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

Mat4 Node::getNodeToWorldTransform() const
{
    Mat4 t = this->getNodeToParentTransform();

    for (Node *p = _parent; p != nullptr; p = p->getParent())
    {
        t = p->getNodeToParentTransform() * t;
    }

    return t;
}

AffineTransform Node::getWorldToNodeAffineTransform() const
{
    return AffineTransformInvert(this->getNodeToWorldAffineTransform());
}

Mat4 Node::getWorldToNodeTransform() const
{
    return getNodeToWorldTransform().getInversed();
}


Vec2 Node::convertToNodeSpace(const Vec2& worldPoint) const
{
    Mat4 tmp = getWorldToNodeTransform();
    Vec3 vec3(worldPoint.x, worldPoint.y, 0);
    Vec3 ret;
    tmp.transformPoint(vec3,&ret);
    return Vec2(ret.x, ret.y);
}

Vec2 Node::convertToWorldSpace(const Vec2& nodePoint) const
{
    Mat4 tmp = getNodeToWorldTransform();
    Vec3 vec3(nodePoint.x, nodePoint.y, 0);
    Vec3 ret;
    tmp.transformPoint(vec3,&ret);
    return Vec2(ret.x, ret.y);

}

Vec2 Node::convertToNodeSpaceAR(const Vec2& worldPoint) const
{
    Vec2 nodePoint = convertToNodeSpace(worldPoint);
    return nodePoint - _anchorPointInPoints;
}

Vec2 Node::convertToWorldSpaceAR(const Vec2& nodePoint) const
{
    Vec2 pt = nodePoint + _anchorPointInPoints;
    return convertToWorldSpace(pt);
}

Vec2 Node::convertToWindowSpace(const Vec2& nodePoint) const
{
    Vec2 worldPoint = this->convertToWorldSpace(nodePoint);
    return Director::getInstance()->convertToUI(worldPoint);
}

// convenience methods which take a Touch instead of Vec2
Vec2 Node::convertTouchToNodeSpace(Touch *touch) const
{
    Vec2 point = touch->getLocation();
    return this->convertToNodeSpace(point);
}

Vec2 Node::convertTouchToNodeSpaceAR(Touch *touch) const
{
    Vec2 point = touch->getLocation();
    return this->convertToNodeSpaceAR(point);
}

void Node::updateTransform()
{
    // Recursively iterate over children
    for( const auto &child: _children)
        child->updateTransform();
}

Component* Node::getComponent(const std::string& name)
{
    if( _componentContainer )
        return _componentContainer->get(name);
    return nullptr;
}

bool Node::addComponent(Component *component)
{
    // lazy alloc
    if( !_componentContainer )
        _componentContainer = new ComponentContainer(this);
    return _componentContainer->add(component);
}

bool Node::removeComponent(const std::string& name)
{
    if( _componentContainer )
        return _componentContainer->remove(name);
    return false;
}

void Node::removeAllComponents()
{
    if( _componentContainer )
        _componentContainer->removeAll();
}

#if CC_USE_PHYSICS

void Node::updatePhysicsBodyPosition(Scene* scene)
{
    if (_physicsBody != nullptr)
    {
        if (scene != nullptr && scene->getPhysicsWorld() != nullptr)
        {
            Vec2 pos = getParent() == scene ? getPosition() : scene->convertToNodeSpace(_parent->convertToWorldSpace(getPosition()));
            _physicsBody->setPosition(pos);
        }
        else
        {
            _physicsBody->setPosition(getPosition());
        }
    }
}

void Node::updatePhysicsBodyRotation(Scene* scene)
{
    if (_physicsBody != nullptr)
    {
        if (scene != nullptr && scene->getPhysicsWorld() != nullptr)
        {
            float rotation = _rotationZ_X;
            for (Node* parent = _parent; parent != scene; parent = parent->getParent())
            {
                rotation += parent->getRotation();
            }
            _physicsBody->setRotation(rotation);
        }
        else
        {
            _physicsBody->setRotation(_rotationZ_X);
        }
    }
}

void Node::setPhysicsBody(PhysicsBody* body)
{
    if (_physicsBody == body)
    {
        return;
    }
    
    if (body != nullptr)
    {
        if (body->getNode() != nullptr)
        {
            body->getNode()->setPhysicsBody(nullptr);
        }
        
        body->_node = this;
        body->retain();
        
        // physics rotation based on body position, but node rotation based on node anthor point
        // it cann't support both of them, so I clear the anthor point to default.
        if (!getAnchorPoint().equals(Vec2::ANCHOR_MIDDLE))
        {
            CCLOG("Node warning: setPhysicsBody sets anchor point to Vec2::ANCHOR_MIDDLE.");
            setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        }
    }
    
    if (_physicsBody != nullptr)
    {
        PhysicsWorld* world = _physicsBody->getWorld();
        _physicsBody->removeFromWorld();
        _physicsBody->_node = nullptr;
        _physicsBody->release();
        
        if (world != nullptr && body != nullptr)
        {
            world->addBody(body);
        }
    }
    
    _physicsBody = body;
    
    if (body != nullptr)
    {
        Node* node;
        Scene* scene = nullptr;
        for (node = this->getParent(); node != nullptr; node = node->getParent())
        {
            Scene* tmpScene = dynamic_cast<Scene*>(node);
            if (tmpScene != nullptr && tmpScene->getPhysicsWorld() != nullptr)
            {
                scene = tmpScene;
                break;
            }
        }
        
        if (scene != nullptr)
        {
            scene->getPhysicsWorld()->addBody(body);
        }
        
        updatePhysicsBodyPosition(scene);
        updatePhysicsBodyRotation(scene);
    }
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

GLubyte Node::getDisplayedOpacity() const
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
