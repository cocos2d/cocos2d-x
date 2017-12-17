/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2009      Valentin Milea
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2017 Chukong Technologies Inc.

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
#include "base/CCEventDispatcher.h"
#include "base/ccUTF8.h"
#include "2d/CCCamera.h"
#include "2d/CCActionManager.h"
#include "2d/CCScene.h"
#include "2d/CCComponent.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCMaterial.h"
#include "math/TransformUtils.h"


#if CC_NODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL(__ARGS__) (ceil(__ARGS__))
#endif


NS_CC_BEGIN

// FIXME:: Yes, nodes might have a sort problem once every 30 days if the game runs at 60 FPS and each frame sprites are reordered.
std::uint32_t Node::s_globalOrderOfArrival = 0;
int Node::__attachedNodeCount = 0;

// MARK: Constructor, Destructor, Init

Node::Node()
: _rotationX(0.0f)
, _rotationY(0.0f)
, _rotationZ_X(0.0f)
, _rotationZ_Y(0.0f)
, _scaleX(1.0f)
, _scaleY(1.0f)
, _scaleZ(1.0f)
, _positionZ(0.0f)
, _usingNormalizedPosition(false)
, _normalizedPositionDirty(false)
, _skewX(0.0f)
, _skewY(0.0f)
, _contentSize(Size::ZERO)
, _contentSizeDirty(true)
, _transformDirty(true)
, _inverseDirty(true)
, _additionalTransform(nullptr)
, _additionalTransformDirty(false)
, _transformUpdated(true)
// children (lazy allocs)
// lazy alloc
, _localZOrder$Arrival(0LL)
, _globalZOrder(0)
, _parent(nullptr)
// "whole screen" objects. like Scenes and Layers, should set _ignoreAnchorPointForPosition to true
, _tag(Node::INVALID_TAG)
, _name("")
, _hashOfName(0)
// userData is always inited as nil
, _userData(nullptr)
, _userObject(nullptr)
, _glProgramState(nullptr)
, _running(false)
, _visible(true)
, _ignoreAnchorPointForPosition(false)
, _reorderChildDirty(false)
, _isTransitionFinished(false)
#if CC_ENABLE_SCRIPT_BINDING
, _updateScriptHandler(0)
#endif
, _componentContainer(nullptr)
, _displayedOpacity(255)
, _realOpacity(255)
, _displayedColor(Color3B::WHITE)
, _realColor(Color3B::WHITE)
, _cascadeColorEnabled(false)
, _cascadeOpacityEnabled(false)
, _cameraMask(1)
#if CC_USE_PHYSICS
, _physicsBody(nullptr)
#endif
, _anchorPoint(0, 0)
, _onEnterCallback(nullptr)
, _onExitCallback(nullptr)
, _onEnterTransitionDidFinishCallback(nullptr)
, _onExitTransitionDidStartCallback(nullptr)
{
    // set default scheduler and actionManager
    _director = Director::getInstance();
    _actionManager = _director->getActionManager();
    _actionManager->retain();
    _scheduler = _director->getScheduler();
    _scheduler->retain();
    _eventDispatcher = _director->getEventDispatcher();
    _eventDispatcher->retain();
    
#if CC_ENABLE_SCRIPT_BINDING
    ScriptEngineProtocol* engine = ScriptEngineManager::getInstance()->getScriptEngine();
    _scriptType = engine != nullptr ? engine->getScriptType() : kScriptTypeNone;
#endif
    _transform = _inverse = Mat4::IDENTITY;
}

Node * Node::create()
{
    Node * ret = new (std::nothrow) Node();
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
    // It may invoke `node->stopAllActions();` while `_actionManager` is null if the next line is after `CC_SAFE_RELEASE_NULL(_actionManager)`.
    CC_SAFE_RELEASE_NULL(_userObject);
    
    // attributes
    CC_SAFE_RELEASE_NULL(_glProgramState);

    for (auto& child : _children)
    {
        child->_parent = nullptr;
    }

    removeAllComponents();
    
    CC_SAFE_DELETE(_componentContainer);
    
    stopAllActions();
    unscheduleAllCallbacks();
    CC_SAFE_RELEASE_NULL(_actionManager);
    CC_SAFE_RELEASE_NULL(_scheduler);
    
    _eventDispatcher->removeEventListenersForTarget(this);
    
#if CC_NODE_DEBUG_VERIFY_EVENT_LISTENERS && COCOS2D_DEBUG > 0
    _eventDispatcher->debugCheckNodeHasNoEventListenersOnDestruction(this);
#endif

    CCASSERT(!_running, "Node still marked as running on node destruction! Was base class onExit() called in derived class onExit() implementations?");
    CC_SAFE_RELEASE(_eventDispatcher);

    delete[] _additionalTransform;
}

bool Node::init()
{
    return true;
}

void Node::cleanup()
{
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeJavascript)
    {
        if (ScriptEngineManager::sendNodeEventToJS(this, kNodeOnCleanup))
            return;
    }
    else if (_scriptType == kScriptTypeLua)
    {
        ScriptEngineManager::sendNodeEventToLua(this, kNodeOnCleanup);
    }
#endif // #if CC_ENABLE_SCRIPT_BINDING
    
    // actions
    this->stopAllActions();
    // timers
    this->unscheduleAllCallbacks();

    _eventDispatcher->removeEventListenersForTarget(this);
    
    for( const auto &child: _children)
        child->cleanup();
}

std::string Node::getDescription() const
{
    return StringUtils::format("<Node | Tag = %d", _tag);
}

// MARK: getters / setters

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

void Node::setLocalZOrder(std::int32_t z)
{
    if (getLocalZOrder() == z)
        return;
    
    _setLocalZOrder(z);
    if (_parent)
    {
        _parent->reorderChild(this, z);
    }

    _eventDispatcher->setDirtyForNode(this);
}

/// zOrder setter : private method
/// used internally to alter the zOrder variable. DON'T call this method manually
void Node::_setLocalZOrder(std::int32_t z)
{
    _localZOrder = z;
}

void Node::updateOrderOfArrival()
{
    _orderOfArrival = (++s_globalOrderOfArrival);
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
    
    updateRotationQuat();
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
    
    updateRotationQuat();
}

Vec3 Node::getRotation3D() const
{
    // rotation Z is decomposed in 2 to simulate Skew for Flash animations
    CCASSERT(_rotationZ_X == _rotationZ_Y, "_rotationZ_X != _rotationZ_Y");

    return Vec3(_rotationX,_rotationY,_rotationZ_X);
}

void Node::updateRotationQuat()
{
    // convert Euler angle to quaternion
    // when _rotationZ_X == _rotationZ_Y, _rotationQuat = RotationZ_X * RotationY * RotationX
    // when _rotationZ_X != _rotationZ_Y, _rotationQuat = RotationY * RotationX
    float halfRadx = CC_DEGREES_TO_RADIANS(_rotationX / 2.f), halfRady = CC_DEGREES_TO_RADIANS(_rotationY / 2.f), halfRadz = _rotationZ_X == _rotationZ_Y ? -CC_DEGREES_TO_RADIANS(_rotationZ_X / 2.f) : 0;
    float coshalfRadx = cosf(halfRadx), sinhalfRadx = sinf(halfRadx), coshalfRady = cosf(halfRady), sinhalfRady = sinf(halfRady), coshalfRadz = cosf(halfRadz), sinhalfRadz = sinf(halfRadz);
    _rotationQuat.x = sinhalfRadx * coshalfRady * coshalfRadz - coshalfRadx * sinhalfRady * sinhalfRadz;
    _rotationQuat.y = coshalfRadx * sinhalfRady * coshalfRadz + sinhalfRadx * coshalfRady * sinhalfRadz;
    _rotationQuat.z = coshalfRadx * coshalfRady * sinhalfRadz - sinhalfRadx * sinhalfRady * coshalfRadz;
    _rotationQuat.w = coshalfRadx * coshalfRady * coshalfRadz + sinhalfRadx * sinhalfRady * sinhalfRadz;
}

void Node::updateRotation3D()
{
    //convert quaternion to Euler angle
    float x = _rotationQuat.x, y = _rotationQuat.y, z = _rotationQuat.z, w = _rotationQuat.w;
    _rotationX = atan2f(2.f * (w * x + y * z), 1.f - 2.f * (x * x + y * y));
    float sy = 2.f * (w * y - z * x);
    sy = clampf(sy, -1, 1);
    _rotationY = asinf(sy);
    _rotationZ_X = atan2f(2.f * (w * z + x * y), 1.f - 2.f * (y * y + z * z));
    
    _rotationX = CC_RADIANS_TO_DEGREES(_rotationX);
    _rotationY = CC_RADIANS_TO_DEGREES(_rotationY);
    _rotationZ_X = _rotationZ_Y = -CC_RADIANS_TO_DEGREES(_rotationZ_X);
}

void Node::setRotationQuat(const Quaternion& quat)
{
    _rotationQuat = quat;
    updateRotation3D();
    _transformUpdated = _transformDirty = _inverseDirty = true;
}

Quaternion Node::getRotationQuat() const
{
    return _rotationQuat;
}

void Node::setRotationSkewX(float rotationX)
{
    if (_rotationZ_X == rotationX)
        return;
    
    _rotationZ_X = rotationX;
    _transformUpdated = _transformDirty = _inverseDirty = true;
    
    updateRotationQuat();
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
    
    updateRotationQuat();
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
    if (_scaleX == scale && _scaleY == scale && _scaleZ == scale)
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
    setPosition(position.x, position.y);
}

void Node::getPosition(float* x, float* y) const
{
    *x = _position.x;
    *y = _position.y;
}

void Node::setPosition(float x, float y)
{
    if (_position.x == x && _position.y == y)
        return;
    
    _position.x = x;
    _position.y = y;
    
    _transformUpdated = _transformDirty = _inverseDirty = true;
    _usingNormalizedPosition = false;
}

void Node::setPosition3D(const Vec3& position)
{
    setPositionZ(position.z);
    setPosition(position.x, position.y);
}

Vec3 Node::getPosition3D() const
{
    return Vec3(_position.x, _position.y, _positionZ);
}

float Node::getPositionX() const
{
    return _position.x;
}

void Node::setPositionX(float x)
{
    setPosition(x, _position.y);
}

float Node::getPositionY() const
{
    return  _position.y;
}

void Node::setPositionY(float y)
{
    setPosition(_position.x, y);
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
}

/// position getter
const Vec2& Node::getPositionNormalized() const
{
    return _normalizedPosition;
}

/// position setter
void Node::setPositionNormalized(const Vec2& position)
{
    if (_normalizedPosition.equals(position))
        return;

    _normalizedPosition = position;
    _usingNormalizedPosition = true;
    _normalizedPositionDirty = true;
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
        if(_visible)
            _transformUpdated = _transformDirty = _inverseDirty = true;
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
    if (! point.equals(_anchorPoint))
    {
        _anchorPoint = point;
        _anchorPointInPoints.set(_contentSize.width * _anchorPoint.x, _contentSize.height * _anchorPoint.y);
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
    if (! size.equals(_contentSize))
    {
        _contentSize = size;

        _anchorPointInPoints.set(_contentSize.width * _anchorPoint.x, _contentSize.height * _anchorPoint.y);
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
void Node::setIgnoreAnchorPointForPosition(bool newValue)
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

const std::string& Node::getName() const
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

void Node::setUserObject(Ref* userObject)
{
#if CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    auto sEngine = ScriptEngineManager::getInstance()->getScriptEngine();
    if (sEngine)
    {
        if (userObject)
            sEngine->retainScriptObject(this, userObject);
        if (_userObject)
            sEngine->releaseScriptObject(this, _userObject);
    }
#endif // CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    CC_SAFE_RETAIN(userObject);
    CC_SAFE_RELEASE(_userObject);
    _userObject = userObject;
}

GLProgramState* Node::getGLProgramState() const
{
    return _glProgramState;
}

void Node::setGLProgramState(cocos2d::GLProgramState* glProgramState)
{
    if (glProgramState != _glProgramState)
    {
        CC_SAFE_RELEASE(_glProgramState);
        _glProgramState = glProgramState;
        CC_SAFE_RETAIN(_glProgramState);

        if (_glProgramState)
            _glProgramState->setNodeBinding(this);
    }
}


void Node::setGLProgram(GLProgram* glProgram)
{
    if (_glProgramState == nullptr || (_glProgramState && _glProgramState->getGLProgram() != glProgram))
    {
        CC_SAFE_RELEASE(_glProgramState);
        _glProgramState = GLProgramState::getOrCreateWithGLProgram(glProgram);
        _glProgramState->retain();

        _glProgramState->setNodeBinding(this);
    }
}

GLProgram * Node::getGLProgram() const
{
    return _glProgramState ? _glProgramState->getGLProgram() : nullptr;
}

Scene* Node::getScene() const
{
    if (!_parent)
        return nullptr;
    
    auto sceneNode = _parent;
    while (sceneNode->_parent)
    {
        sceneNode = sceneNode->_parent;
    }

    return dynamic_cast<Scene*>(sceneNode);
}

Rect Node::getBoundingBox() const
{
    Rect rect(0, 0, _contentSize.width, _contentSize.height);
    return RectApplyAffineTransform(rect, getNodeToParentAffineTransform());
}

// MARK: Children logic

// lazy allocs
void Node::childrenAlloc()
{
    _children.reserve(4);
}

Node* Node::getChildByTag(int tag) const
{
    CCASSERT(tag != Node::INVALID_TAG, "Invalid tag");

    for (const auto child : _children)
    {
        if(child && child->_tag == tag)
            return child;
    }
    return nullptr;
}

Node* Node::getChildByName(const std::string& name) const
{
    CCASSERT(!name.empty(), "Invalid name");
    
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
    CCASSERT(!name.empty(), "Invalid name");
    CCASSERT(callback != nullptr, "Invalid callback function");
    
    size_t length = name.length();
    
    size_t subStrStartPos = 0;  // sub string start index
    size_t subStrlength = length; // sub string length
    
    // Starts with '//'?
    bool searchRecursively = false;
    if (length > 2 && name[0] == '/' && name[1] == '/')
    {
        searchRecursively = true;
        subStrStartPos = 2;
        subStrlength -= 2;
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
    
    // Remove '//', '/..' if exist
    std::string newName = name.substr(subStrStartPos, subStrlength);

    if (searchFromParent)
    {
        newName.insert(0, "[[:alnum:]]+/");
    }
    
    
    if (searchRecursively)
    {
        // name is '//xxx'
        doEnumerateRecursive(this, newName, callback);
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
    for (const auto& child : getChildren())
    {
        if (std::regex_match(child->_name, std::regex(searchName)))
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
void Node::addChild(Node *child, int localZOrder, int tag)
{    
    CCASSERT( child != nullptr, "Argument must be non-nil");
    CCASSERT( child->_parent == nullptr, "child already added. It can't be added again");

    addChildHelper(child, localZOrder, tag, "", true);
}

void Node::addChild(Node* child, int localZOrder, const std::string &name)
{
    CCASSERT(child != nullptr, "Argument must be non-nil");
    CCASSERT(child->_parent == nullptr, "child already added. It can't be added again");
    
    addChildHelper(child, localZOrder, INVALID_TAG, name, false);
}

void Node::addChildHelper(Node* child, int localZOrder, int tag, const std::string &name, bool setTag)
{
    auto assertNotSelfChild
        ( [ this, child ]() -> bool
          {
              for ( Node* parent( getParent() ); parent != nullptr;
                    parent = parent->getParent() )
                  if ( parent == child )
                      return false;
              
              return true;
          } );
    (void)assertNotSelfChild;
    
    CCASSERT( assertNotSelfChild(),
              "A node cannot be the child of his own children" );
    
    if (_children.empty())
    {
        this->childrenAlloc();
    }
    
    this->insertChild(child, localZOrder);
    
    if (setTag)
        child->setTag(tag);
    else
        child->setName(name);
    
    child->setParent(this);

    child->updateOrderOfArrival();

    if( _running )
    {
        child->onEnter();
        // prevent onEnterTransitionDidFinish to be called twice when a node is added in onEnter
        if (_isTransitionFinished)
        {
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
    this->addChild(child, zOrder, child->_name);
}

void Node::addChild(Node *child)
{
    CCASSERT( child != nullptr, "Argument must be non-nil");
    this->addChild(child, child->getLocalZOrder(), child->_name);
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

void Node::removeChildByName(const std::string &name, bool cleanup)
{
    CCASSERT(!name.empty(), "Invalid name");
    
    Node *child = this->getChildByName(name);
    
    if (child == nullptr)
    {
        CCLOG("cocos2d: removeChildByName(name = %s): child not found!", name.c_str());
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
    for (const auto& child : _children)
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
#if CC_ENABLE_GC_FOR_NATIVE_OBJECTS
        auto sEngine = ScriptEngineManager::getInstance()->getScriptEngine();
        if (sEngine)
        {
            sEngine->releaseScriptObject(this, child);
        }
#endif // CC_ENABLE_GC_FOR_NATIVE_OBJECTS
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

    // If you don't do cleanup, the child's actions will not get removed and the
    // its scheduledSelectors_ dict will not get released!
    if (doCleanup)
    {
        child->cleanup();
    }
    
#if CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    auto sEngine = ScriptEngineManager::getInstance()->getScriptEngine();
    if (sEngine)
    {
        sEngine->releaseScriptObject(this, child);
    }
#endif // CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    // set parent nil at the end
    child->setParent(nullptr);

    _children.erase(childIndex);
}


// helper used by reorderChild & add
void Node::insertChild(Node* child, int z)
{
#if CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    auto sEngine = ScriptEngineManager::getInstance()->getScriptEngine();
    if (sEngine)
    {
        sEngine->retainScriptObject(this, child);
    }
#endif // CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    _transformUpdated = true;
    _reorderChildDirty = true;
    _children.pushBack(child);
    child->_setLocalZOrder(z);
}

void Node::reorderChild(Node *child, int zOrder)
{
    CCASSERT( child != nullptr, "Child must be non-nil");
    _reorderChildDirty = true;
    child->updateOrderOfArrival();
    child->_setLocalZOrder(zOrder);
}

void Node::sortAllChildren()
{
    if (_reorderChildDirty)
    {
        sortNodes(_children);
        _reorderChildDirty = false;
        _eventDispatcher->setDirtyForNode(this);
    }
}

// MARK: draw / visit

void Node::draw()
{
    auto renderer = _director->getRenderer();
    draw(renderer, _modelViewTransform, true);
}

void Node::draw(Renderer* /*renderer*/, const Mat4 & /*transform*/, uint32_t /*flags*/)
{
}

void Node::visit()
{
    auto renderer = _director->getRenderer();
    auto& parentTransform = _director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    visit(renderer, parentTransform, true);
}

uint32_t Node::processParentFlags(const Mat4& parentTransform, uint32_t parentFlags)
{
    if(_usingNormalizedPosition)
    {
        CCASSERT(_parent, "setPositionNormalized() doesn't work with orphan nodes");
        if ((parentFlags & FLAGS_CONTENT_SIZE_DIRTY) || _normalizedPositionDirty)
        {
            auto& s = _parent->getContentSize();
            _position.x = _normalizedPosition.x * s.width;
            _position.y = _normalizedPosition.y * s.height;
            _transformUpdated = _transformDirty = _inverseDirty = true;
            _normalizedPositionDirty = false;
        }
    }

    // Fixes Github issue #16100. Basically when having two cameras, one camera might set as dirty the
    // node that is not visited by it, and might affect certain calculations. Besides, it is faster to do this.
    if (!isVisitableByVisitingCamera())
        return parentFlags;

    uint32_t flags = parentFlags;
    flags |= (_transformUpdated ? FLAGS_TRANSFORM_DIRTY : 0);
    flags |= (_contentSizeDirty ? FLAGS_CONTENT_SIZE_DIRTY : 0);
    

    if(flags & FLAGS_DIRTY_MASK)
        _modelViewTransform = this->transform(parentTransform);
    
    _transformUpdated = false;
    _contentSizeDirty = false;

    return flags;
}

bool Node::isVisitableByVisitingCamera() const
{
    auto camera = Camera::getVisitingCamera();
    bool visibleByCamera = camera ? ((unsigned short)camera->getCameraFlag() & _cameraMask) != 0 : true;
    return visibleByCamera;
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
    _director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    _director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);
    
    bool visibleByCamera = isVisitableByVisitingCamera();

    int i = 0;

    if(!_children.empty())
    {
        sortAllChildren();
        // draw children zOrder < 0
        for(auto size = _children.size(); i < size; ++i)
        {
            auto node = _children.at(i);

            if (node && node->_localZOrder < 0)
                node->visit(renderer, _modelViewTransform, flags);
            else
                break;
        }
        // self draw
        if (visibleByCamera)
            this->draw(renderer, _modelViewTransform, flags);

        for(auto it=_children.cbegin()+i, itCend = _children.cend(); it != itCend; ++it)
            (*it)->visit(renderer, _modelViewTransform, flags);
    }
    else if (visibleByCamera)
    {
        this->draw(renderer, _modelViewTransform, flags);
    }

    _director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
    // FIX ME: Why need to set _orderOfArrival to 0??
    // Please refer to https://github.com/cocos2d/cocos2d-x/pull/6920
    // reset for next frame
    // _orderOfArrival = 0;
}

Mat4 Node::transform(const Mat4& parentTransform)
{
    return parentTransform * this->getNodeToParentTransform();
}

// MARK: events

void Node::onEnter()
{
    if (!_running)
    {
        ++__attachedNodeCount;
    }
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeJavascript)
    {
        if (ScriptEngineManager::sendNodeEventToJS(this, kNodeOnEnter))
            return;
    }
#endif
    
    if (_onEnterCallback)
        _onEnterCallback();

    if (_componentContainer && !_componentContainer->isEmpty())
    {
        _componentContainer->onEnter();
    }
    
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
    
    if (_onEnterTransitionDidFinishCallback)
        _onEnterTransitionDidFinishCallback();

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
    
    if (_onExitTransitionDidStartCallback)
        _onExitTransitionDidStartCallback();
    
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
    if (_running)
    {
        --__attachedNodeCount;
    }
#if CC_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeJavascript)
    {
        if (ScriptEngineManager::sendNodeEventToJS(this, kNodeOnExit))
            return;
    }
#endif
    
    if (_onExitCallback)
        _onExitCallback();
    
    if (_componentContainer && !_componentContainer->isEmpty())
    {
        _componentContainer->onExit();
    }
    
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
    if( actionManager != _actionManager )
    {
        this->stopAllActions();
        CC_SAFE_RETAIN(actionManager);
        CC_SAFE_RELEASE(_actionManager);
        _actionManager = actionManager;
    }
}

// MARK: actions

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

void Node::stopAllActionsByTag(int tag)
{
    CCASSERT( tag != Action::INVALID_TAG, "Invalid tag");
    _actionManager->removeAllActionsByTag(tag, this);
}

void Node::stopActionsByFlags(unsigned int flags)
{
    if (flags > 0)
    {
        _actionManager->removeActionsByFlags(flags, this);
    }
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

ssize_t Node::getNumberOfRunningActionsByTag(int tag) const
{
    return _actionManager->getNumberOfRunningActionsInTargetByTag(this, tag);
}


// MARK: Callbacks

void Node::setScheduler(Scheduler* scheduler)
{
    if( scheduler != _scheduler )
    {
        this->unscheduleAllCallbacks();
        CC_SAFE_RETAIN(scheduler);
        CC_SAFE_RELEASE(_scheduler);
        _scheduler = scheduler;
    }
}

bool Node::isScheduled(SEL_SCHEDULE selector) const
{
    return _scheduler->isScheduled(selector, this);
}

bool Node::isScheduled(const std::string &key) const
{
    return _scheduler->isScheduled(key, this);
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
    this->schedule(selector, 0.0f, CC_REPEAT_FOREVER, 0.0f);
}

void Node::schedule(SEL_SCHEDULE selector, float interval)
{
    this->schedule(selector, interval, CC_REPEAT_FOREVER, 0.0f);
}

void Node::schedule(SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay)
{
    CCASSERT( selector, "Argument must be non-nil");
    CCASSERT( interval >=0, "Argument must be positive");

    _scheduler->schedule(selector, this, interval , repeat, delay, !_running);
}

void Node::schedule(const std::function<void(float)> &callback, const std::string &key)
{
    _scheduler->schedule(callback, this, 0, !_running, key);
}

void Node::schedule(const std::function<void(float)> &callback, float interval, const std::string &key)
{
    _scheduler->schedule(callback, this, interval, !_running, key);
}

void Node::schedule(const std::function<void(float)>& callback, float interval, unsigned int repeat, float delay, const std::string &key)
{
    _scheduler->schedule(callback, this, interval, repeat, delay, !_running, key);
}

void Node::scheduleOnce(SEL_SCHEDULE selector, float delay)
{
    this->schedule(selector, 0.0f, 0, delay);
}

void Node::scheduleOnce(const std::function<void(float)> &callback, float delay, const std::string &key)
{
    _scheduler->schedule(callback, this, 0, 0, delay, !_running, key);
}

void Node::unschedule(SEL_SCHEDULE selector)
{
    // explicit null handling
    if (selector == nullptr)
        return;
    
    _scheduler->unschedule(selector, this);
}

void Node::unschedule(const std::string &key)
{
    _scheduler->unschedule(key, this);
}

void Node::unscheduleAllCallbacks()
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

// MARK: coordinates

AffineTransform Node::getNodeToParentAffineTransform() const
{
    AffineTransform ret;
    GLToCGAffine(getNodeToParentTransform().m, &ret);

    return ret;
}


Mat4 Node::getNodeToParentTransform(Node* ancestor) const
{
    Mat4 t(this->getNodeToParentTransform());

    for (Node *p = _parent;  p != nullptr && p != ancestor ; p = p->getParent())
    {
        t = p->getNodeToParentTransform() * t;
    }

    return t;
}

AffineTransform Node::getNodeToParentAffineTransform(Node* ancestor) const
{
    AffineTransform t(this->getNodeToParentAffineTransform());

    for (Node *p = _parent; p != nullptr && p != ancestor; p = p->getParent())
        t = AffineTransformConcat(t, p->getNodeToParentAffineTransform());

    return t;
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
        
        bool needsSkewMatrix = ( _skewX || _skewY );

        // Build Transform Matrix = translation * rotation * scale
        Mat4 translation;
        //move to anchor point first, then rotate
        Mat4::createTranslation(x, y, z, &translation);
        
        Mat4::createRotation(_rotationQuat, &_transform);
        
        if (_rotationZ_X != _rotationZ_Y)
        {
            // Rotation values
            // Change rotation code to handle X and Y
            // If we skew with the exact same value for both x and y then we're simply just rotating
            float radiansX = -CC_DEGREES_TO_RADIANS(_rotationZ_X);
            float radiansY = -CC_DEGREES_TO_RADIANS(_rotationZ_Y);
            float cx = cosf(radiansX);
            float sx = sinf(radiansX);
            float cy = cosf(radiansY);
            float sy = sinf(radiansY);
            
            float m0 = _transform.m[0], m1 = _transform.m[1], m4 = _transform.m[4], m5 = _transform.m[5], m8 = _transform.m[8], m9 = _transform.m[9];
            _transform.m[0] = cy * m0 - sx * m1, _transform.m[4] = cy * m4 - sx * m5, _transform.m[8] = cy * m8 - sx * m9;
            _transform.m[1] = sy * m0 + cx * m1, _transform.m[5] = sy * m4 + cx * m5, _transform.m[9] = sy * m8 + cx * m9;
        }
        _transform = translation * _transform;

        if (_scaleX != 1.f)
        {
            _transform.m[0] *= _scaleX, _transform.m[1] *= _scaleX, _transform.m[2] *= _scaleX;
        }
        if (_scaleY != 1.f)
        {
            _transform.m[4] *= _scaleY, _transform.m[5] *= _scaleY, _transform.m[6] *= _scaleY;
        }
        if (_scaleZ != 1.f)
        {
            _transform.m[8] *= _scaleZ, _transform.m[9] *= _scaleZ, _transform.m[10] *= _scaleZ;
        }
        
        // FIXME:: Try to inline skew
        // If skew is needed, apply skew and then anchor point
        if (needsSkewMatrix)
        {
            float skewMatArray[16] =
            {
                1, (float)tanf(CC_DEGREES_TO_RADIANS(_skewY)), 0, 0,
                (float)tanf(CC_DEGREES_TO_RADIANS(_skewX)), 1, 0, 0,
                0,  0,  1, 0,
                0,  0,  0, 1
            };
            Mat4 skewMatrix(skewMatArray);
            
            _transform = _transform * skewMatrix;
        }

        // adjust anchor point
        if (!_anchorPointInPoints.isZero())
        {
            // FIXME:: Argh, Mat4 needs a "translate" method.
            // FIXME:: Although this is faster than multiplying a vec4 * mat4
            _transform.m[12] += _transform.m[0] * -_anchorPointInPoints.x + _transform.m[4] * -_anchorPointInPoints.y;
            _transform.m[13] += _transform.m[1] * -_anchorPointInPoints.x + _transform.m[5] * -_anchorPointInPoints.y;
            _transform.m[14] += _transform.m[2] * -_anchorPointInPoints.x + _transform.m[6] * -_anchorPointInPoints.y;
        }
    }

    if (_additionalTransform)
    {
        // This is needed to support both Node::setNodeToParentTransform() and Node::setAdditionalTransform()
        // at the same time. The scenario is this:
        // at some point setNodeToParentTransform() is called.
        // and later setAdditionalTransform() is called every time. And since _transform
        // is being overwritten everyframe, _additionalTransform[1] is used to have a copy
        // of the last "_transform without _additionalTransform"
        if (_transformDirty)
            _additionalTransform[1] = _transform;

        if (_transformUpdated)
            _transform = _additionalTransform[1] * _additionalTransform[0];
    }

    _transformDirty = _additionalTransformDirty = false;

    return _transform;
}

void Node::setNodeToParentTransform(const Mat4& transform)
{
    _transform = transform;
    _transformDirty = false;
    _transformUpdated = true;

    if (_additionalTransform)
        // _additionalTransform[1] has a copy of lastest transform
        _additionalTransform[1] = transform;
}

void Node::setAdditionalTransform(const AffineTransform& additionalTransform)
{
    Mat4 tmp;
    CGAffineToGL(additionalTransform, tmp.m);
    setAdditionalTransform(&tmp);
}

void Node::setAdditionalTransform(const Mat4* additionalTransform)
{
    if (additionalTransform == nullptr)
    {
        if(_additionalTransform)  _transform = _additionalTransform[1];
        delete[] _additionalTransform;
        _additionalTransform = nullptr;
    }
    else
    {
        if (!_additionalTransform) {
            _additionalTransform = new Mat4[2];

            // _additionalTransform[1] is used as a backup for _transform
            _additionalTransform[1] = _transform;
        }

        _additionalTransform[0] = *additionalTransform;
    }
    _transformUpdated = _additionalTransformDirty = _inverseDirty = true;
}

void Node::setAdditionalTransform(const Mat4& additionalTransform)
{
    setAdditionalTransform(&additionalTransform);
}

AffineTransform Node::getParentToNodeAffineTransform() const
{
    AffineTransform ret;

    GLToCGAffine(getParentToNodeTransform().m,&ret);
    return ret;
}

const Mat4& Node::getParentToNodeTransform() const
{
    if ( _inverseDirty )
    {
        _inverse = getNodeToParentTransform().getInversed();
        _inverseDirty = false;
    }

    return _inverse;
}


AffineTransform Node::getNodeToWorldAffineTransform() const
{
    return this->getNodeToParentAffineTransform(nullptr);
}

Mat4 Node::getNodeToWorldTransform() const
{
    return this->getNodeToParentTransform(nullptr);
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
    Vec2 nodePoint(convertToNodeSpace(worldPoint));
    return nodePoint - _anchorPointInPoints;
}

Vec2 Node::convertToWorldSpaceAR(const Vec2& nodePoint) const
{
    return convertToWorldSpace(nodePoint + _anchorPointInPoints);
}

Vec2 Node::convertToWindowSpace(const Vec2& nodePoint) const
{
    Vec2 worldPoint(this->convertToWorldSpace(nodePoint));
    return _director->convertToUI(worldPoint);
}

// convenience methods which take a Touch instead of Vec2
Vec2 Node::convertTouchToNodeSpace(Touch *touch) const
{
    return this->convertToNodeSpace(touch->getLocation());
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

// MARK: components

Component* Node::getComponent(const std::string& name)
{
    if (_componentContainer)
        return _componentContainer->get(name);
    
    return nullptr;
}

bool Node::addComponent(Component *component)
{
    // lazy alloc
    if (!_componentContainer)
        _componentContainer = new (std::nothrow) ComponentContainer(this);
    
    // should enable schedule update, then all components can receive this call back
    scheduleUpdate();
    
    return _componentContainer->add(component);
}

bool Node::removeComponent(const std::string& name)
{
    if (_componentContainer)
        return _componentContainer->remove(name);
    
    return false;
}

bool Node::removeComponent(Component *component)
{
    if (_componentContainer)
    {
        return _componentContainer->remove(component);
    }
    
    return false;
}

void Node::removeAllComponents()
{
    if (_componentContainer)
        _componentContainer->removeAll();
}

// MARK: Opacity and Color

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
        for(const auto& child : _children)
        {
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
    
    for(const auto& child : _children)
    {
        child->updateDisplayedOpacity(255);
    }
}

void Node::setOpacityModifyRGB(bool /*value*/)
{}

bool Node::isOpacityModifyRGB() const
{
    return false;
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
        for(const auto &child : _children)
        {
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
    for(const auto& child : _children)
    {
        child->updateDisplayedColor(Color3B::WHITE);
    }
}

bool isScreenPointInRect(const Vec2 &pt, const Camera* camera, const Mat4& w2l, const Rect& rect, Vec3 *p)
{
    if (nullptr == camera || rect.size.width <= 0 || rect.size.height <= 0)
    {
        return false;
    }
    
    // first, convert pt to near/far plane, get Pn and Pf
    Vec3 Pn(pt.x, pt.y, -1), Pf(pt.x, pt.y, 1);
    Pn = camera->unprojectGL(Pn);
    Pf = camera->unprojectGL(Pf);
    
    //  then convert Pn and Pf to node space
    w2l.transformPoint(&Pn);
    w2l.transformPoint(&Pf);

    // Pn and Pf define a line Q(t) = D + t * E which D = Pn
    auto E = Pf - Pn;
    
    // second, get three points which define content plane
    //  these points define a plane P(u, w) = A + uB + wC
    Vec3 A = Vec3(rect.origin.x, rect.origin.y, 0);
    Vec3 B(rect.origin.x + rect.size.width, rect.origin.y, 0);
    Vec3 C(rect.origin.x, rect.origin.y + rect.size.height, 0);
    B = B - A;
    C = C - A;
    
    //  the line Q(t) intercept with plane P(u, w)
    //  calculate the intercept point P = Q(t)
    //      (BxC).A - (BxC).D
    //  t = -----------------
    //          (BxC).E
    Vec3 BxC;
    Vec3::cross(B, C, &BxC);
    auto BxCdotE = BxC.dot(E);
    if (BxCdotE == 0) {
        return false;
    }
    auto t = (BxC.dot(A) - BxC.dot(Pn)) / BxCdotE;
    Vec3 P = Pn + t * E;
    if (p) {
        *p = P;
    }
    return rect.containsPoint(Vec2(P.x, P.y));
}

// MARK: Camera
void Node::setCameraMask(unsigned short mask, bool applyChildren)
{
    _cameraMask = mask;
    if (applyChildren)
    {
        for (const auto& child : _children)
        {
            child->setCameraMask(mask, applyChildren);
        }
    }
}

int Node::getAttachedNodeCount()
{
    return __attachedNodeCount;
}

// MARK: Deprecated

__NodeRGBA::__NodeRGBA()
{
    CCLOG("NodeRGBA deprecated.");
}

NS_CC_END
