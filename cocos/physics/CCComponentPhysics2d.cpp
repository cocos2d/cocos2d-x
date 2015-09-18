/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
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

#include "base/ccConfig.h" // to include defination of CC_USE_PHYSICS
#if CC_USE_PHYSICS

#include "physics/CCComponentPhysics2d.h"
#include "physics/CCPhysicsBody.h"
#include "physics/CCPhysicsManager.h"
#include "2d/CCNode.h"
#include "base/CCDirector.h"

NS_CC_BEGIN

const std::string ComponentPhysics2d::COMPONENT_NAME = "physics2d";

ComponentPhysics2d* ComponentPhysics2d::create()
{
    return create(nullptr);
}

ComponentPhysics2d* ComponentPhysics2d::create(PhysicsBody *physicsBody)
{
    auto ret = new (std::nothrow) ComponentPhysics2d(physicsBody);
    if (ret)
        ret->autorelease();
    
    return ret;
}

ComponentPhysics2d::ComponentPhysics2d()
: _physicsBody(nullptr)
, _physicsRotation(0.0f)
, _ownerOriginRotation(0.0f)
{
    _name = COMPONENT_NAME;
}

ComponentPhysics2d::ComponentPhysics2d(PhysicsBody* physicsBody)
: _physicsRotation(0.0f)
, _ownerOriginRotation(0.0f)
, _physicsBody(nullptr) // should set to null to invoke setPhysicsBody()
{
    _name = COMPONENT_NAME;
    setPhysicsBody(physicsBody);
}

ComponentPhysics2d::~ComponentPhysics2d()
{
    removePhysicsBody();
}

// true if two Vec3 equals, false else
bool ComponentPhysics2d::isVec3Equal(const cocos2d::Vec3 &v1, const cocos2d::Vec3 &v2) const
{
    return fabs(v1.x - v2.x) < FLT_EPSILON &&
    fabs(v1.x - v2.y) < FLT_EPSILON;
}

void ComponentPhysics2d::beforeSimulation()
{
    if (nullptr == _physicsBody)
        return;
    
    _nodeToWorldTransform = _owner->getNodeToWorldTransform();
    
    // set scale
    _nodeToWorldTransform.getScale(&_scale);
    if (! isVec3Equal(_scale, _recordScale))
    {
        _physicsBody->setScale(_scale.x, _scale.y);
        _recordScale = _scale;
    }
    
    // set rotation
    if (_owner->getParent())
    {
        _physicsRotation = getPhysicsRotation(_owner->getParent()) + _owner->getRotation();
    }
    _physicsBody->setRotation(_physicsRotation - _ownerOriginRotation);
    
    // set position
    auto worldPosition = _ownerCenterOffset;
    _nodeToWorldTransform.transformPoint(&worldPosition);
    _physicsBody->setPosition(Vec2(worldPosition.x, worldPosition.y));
    
    getParentToWorldTransform().getInversed().transformPoint(&worldPosition);
    _offset.x = worldPosition.x - _owner->getPosition().x;
    _offset.y = worldPosition.y - _owner->getPosition().y;
}

void ComponentPhysics2d::afterSimulation()
{
    if (nullptr == _physicsBody)
        return;
    
    // set Node position
    auto worldPosition = _physicsBody->getPosition();
    Vec3 positionInParent(worldPosition.x, worldPosition.y, 0);
    getParentToWorldTransform().getInversed().transformPoint(&positionInParent);
    _owner->setPosition(positionInParent.x - _offset.x, positionInParent.y - _offset.y);
    
    // set Node rotation
    _physicsRotation = _physicsBody->getRotation();
    _owner->setRotation(_physicsRotation - getPhysicsRotation(_owner->getParent()) + _ownerOriginRotation);
}

void ComponentPhysics2d::setPhysicsBody(PhysicsBody *physicsBody)
{
    removeFromPhysicsManager();
    
    if (physicsBody != _physicsBody)
    {
        if (nullptr != _physicsBody)
        {
            _physicsBody->release();
            _physicsBody->_componentBelongsTo = nullptr;
        }
        
        // two components should not share the same physics body
        if (physicsBody && physicsBody->_componentBelongsTo != nullptr)
            physicsBody->_componentBelongsTo->_physicsBody = nullptr;
        
        _physicsBody = physicsBody;
        
        if (nullptr != _physicsBody)
        {
            _physicsBody->retain();
            _physicsBody->_componentBelongsTo = this;
        }
    }
    
    addToPhysicsManager();
}

PhysicsBody* ComponentPhysics2d::getPhysicsBody() const
{
    return _physicsBody;
}

void ComponentPhysics2d::setEnabled(bool value)
{
    Component::setEnabled(value);
    
    if (value)
        addToPhysicsManager();
    else
        removeFromPhysicsManager();
}

void ComponentPhysics2d::onEnter()
{
    addToPhysicsManager();
}

void ComponentPhysics2d::onExit()
{
    removeFromPhysicsManager();
}

void ComponentPhysics2d::onAdd()
{
    auto contentSize = _owner->getContentSize();
    _ownerCenterOffset.x = 0.5 * contentSize.width;
    _ownerCenterOffset.y = 0.5 * contentSize.height;
    
    _ownerOriginRotation = _owner->getRotation();
    
    // component may be added after onEnter() has been invoked, so we should add
    // this line to make sure physics body is added to physics world
    addToPhysicsManager();
}

void ComponentPhysics2d::onRemove()
{
    removePhysicsBody();
}

void ComponentPhysics2d::removePhysicsBody()
{
    removeFromPhysicsManager();
    
    if (_physicsBody)
    {
        _physicsBody->_componentBelongsTo = nullptr;
        _physicsBody->release();
        _physicsBody = nullptr;
    }
}

void ComponentPhysics2d::addToPhysicsManager()
{
    if (_owner)
    {
        auto scene = _owner->getScene();
        if (scene)
            scene->getPhysicsManager()->addPhysicsComponent(this);
    }
    
}

void ComponentPhysics2d::removeFromPhysicsManager()
{
    if (_owner)
    {
        auto scene = _owner->getScene();
        if (scene)
            scene->getPhysicsManager()->removePhysicsComponent(this);
    }
}

Mat4 ComponentPhysics2d::getParentToWorldTransform() const
{
    if (_owner->getParent())
        return _owner->getParent()->getNodeToWorldTransform();
    else
        return _owner->getNodeToWorldTransform();
}

float ComponentPhysics2d::getPhysicsRotation(Node *node) const
{
    if (!node)
        return 0.0f;
    
    auto physicsComponent = node->getComponent<ComponentPhysics2d>();
    if (physicsComponent)
    {
        return physicsComponent->_physicsRotation;
    }
    else
    {
        auto parent = node->getParent();
        if (parent)
            return getPhysicsRotation(parent) + node->getRotation();
        else
            return 0.0f;
    }
}

NS_CC_END

#endif // CC_USE_PHYSICS
