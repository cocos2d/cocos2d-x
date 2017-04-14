/****************************************************************************
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
#include "physics/CCPhysicsBody.h"
#if CC_USE_PHYSICS

#include <climits>
#include <algorithm>
#include <cmath>

#include "chipmunk/chipmunk_private.h"

#include "2d/CCScene.h"
#include "physics/CCPhysicsShape.h"
#include "physics/CCPhysicsJoint.h"
#include "physics/CCPhysicsWorld.h"
#include "physics/CCPhysicsHelper.h"

static void internalBodySetMass(cpBody *body, cpFloat mass)
{
    cpBodyActivate(body);
    body->m = mass;
    body->m_inv = 1.0f/mass;
    //cpAssertSaneBody(body);
}

static void internalBodyUpdateVelocity(cpBody *body, cpVect gravity, cpFloat damping, cpFloat dt)
{
    cpBodyUpdateVelocity(body, cpvzero, damping, dt);
    // Skip kinematic bodies.
    if(cpBodyGetType(body) == CP_BODY_TYPE_KINEMATIC) return;
    
    cpAssertSoft(body->m > 0.0f && body->i > 0.0f, "Body's mass and moment must be positive to simulate. (Mass: %f Moment: f)", body->m, body->i);
    
    cocos2d::PhysicsBody *physicsBody = static_cast<cocos2d::PhysicsBody*>(body->userData);
    
    if(physicsBody->isGravityEnabled())
            body->v = cpvclamp(cpvadd(cpvmult(body->v, damping), cpvmult(cpvadd(gravity, cpvmult(body->f, body->m_inv)), dt)), physicsBody->getVelocityLimit());
    else
            body->v = cpvclamp(cpvadd(cpvmult(body->v, damping), cpvmult(cpvmult(body->f, body->m_inv), dt)), physicsBody->getVelocityLimit());
    cpFloat w_limit = physicsBody->getAngularVelocityLimit();
    body->w = cpfclamp(body->w*damping + body->t*body->i_inv*dt, -w_limit, w_limit);
    
    // Reset forces.
    body->f = cpvzero;
    //to check body sanity
    cpBodySetTorque(body, 0.0f);
}

NS_CC_BEGIN
extern const float PHYSICS_INFINITY;

const std::string PhysicsBody::COMPONENT_NAME = "PhysicsBody";

namespace
{
    static const float MASS_DEFAULT = 1.0;
    static const float MOMENT_DEFAULT = 200;
}

PhysicsBody::PhysicsBody()
: _world(nullptr)
, _cpBody(nullptr)
, _dynamic(true)
, _rotationEnabled(true)
, _gravityEnabled(true)
, _massDefault(true)
, _momentDefault(true)
, _mass(MASS_DEFAULT)
, _area(0.0f)
, _density(0.0f)
, _moment(MOMENT_DEFAULT)
, _velocityLimit(PHYSICS_INFINITY)
, _angularVelocityLimit(PHYSICS_INFINITY)
, _isDamping(false)
, _linearDamping(0.0f)
, _angularDamping(0.0f)
, _tag(0)
, _rotationOffset(0)
, _recordedRotation(0.0f)
, _recordedAngle(0.0)
, _massSetByUser(false)
, _momentSetByUser(false)
, _recordScaleX(1.f)
, _recordScaleY(1.f)
{
    _name = COMPONENT_NAME;
}

PhysicsBody::~PhysicsBody()
{
    for (auto& joint : _joints)
    {
        PhysicsBody* other = joint->getBodyA() == this ? joint->getBodyB() : joint->getBodyA();
        other->removeJoint(joint);
        delete joint;
    }
    
    if (_cpBody)
    {
        cpBodyFree(_cpBody);
    }
}

PhysicsBody* PhysicsBody::create()
{
    PhysicsBody* body = new (std::nothrow) PhysicsBody();
    if (body && body->init())
    {
        body->autorelease();
        return body;
    }
    
    CC_SAFE_DELETE(body);
    return nullptr;
}

PhysicsBody* PhysicsBody::create(float mass)
{
    PhysicsBody* body = new (std::nothrow) PhysicsBody();
    if (body)
    {
        body->_mass = mass;
        body->_massDefault = false;
        if (body->init())
        {
            body->autorelease();
            return body;
        }
    }
    
    CC_SAFE_DELETE(body);
    return nullptr;
}

PhysicsBody* PhysicsBody::create(float mass, float moment)
{
    PhysicsBody* body = new (std::nothrow) PhysicsBody();
    if (body)
    {
        body->_mass = mass;
        body->_massDefault = false;
        body->_moment = moment;
        body->_momentDefault = false;
        if (body->init())
        {
            body->autorelease();
            return body;
        }
    }
    
    CC_SAFE_DELETE(body);
    return nullptr;
    
}

PhysicsBody* PhysicsBody::createCircle(float radius, const PhysicsMaterial& material, const Vec2& offset)
{
    PhysicsBody* body = new (std::nothrow) PhysicsBody();
    if (body && body->init())
    {
        body->addShape(PhysicsShapeCircle::create(radius, material, offset));
        body->autorelease();
        return body;
    }
    
    CC_SAFE_DELETE(body);
    return nullptr;
}

PhysicsBody* PhysicsBody::createBox(const Size& size, const PhysicsMaterial& material, const Vec2& offset)
{
    PhysicsBody* body = new (std::nothrow) PhysicsBody();
    if (body && body->init())
    {
        body->addShape(PhysicsShapeBox::create(size, material, offset));
        body->autorelease();
        return body;
    }
    
    CC_SAFE_DELETE(body);
    return nullptr;
}

PhysicsBody* PhysicsBody::createPolygon(const Vec2* points, int count, const PhysicsMaterial& material, const Vec2& offset)
{
    PhysicsBody* body = new (std::nothrow) PhysicsBody();
    if (body && body->init())
    {
        body->addShape(PhysicsShapePolygon::create(points, count, material, offset));
        body->autorelease();
        return body;
    }
    
    CC_SAFE_DELETE(body);
    return nullptr;
}

PhysicsBody* PhysicsBody::createEdgeSegment(const Vec2& a, const Vec2& b, const PhysicsMaterial& material, float border/* = 1*/)
{
    PhysicsBody* body = new (std::nothrow) PhysicsBody();
    if (body && body->init())
    {
        body->addShape(PhysicsShapeEdgeSegment::create(a, b, material, border));
        body->setDynamic(false);
        body->autorelease();
        return body;
    }
    
    CC_SAFE_DELETE(body);
    return nullptr;
}

PhysicsBody* PhysicsBody::createEdgeBox(const Size& size, const PhysicsMaterial& material, float border/* = 1*/, const Vec2& offset)
{
    PhysicsBody* body = new (std::nothrow) PhysicsBody();
    if (body && body->init())
    {
        body->addShape(PhysicsShapeEdgeBox::create(size, material, border, offset));
        body->setDynamic(false);
        body->autorelease();
        return body;
    }
    
    CC_SAFE_DELETE(body);

    return nullptr;
}

PhysicsBody* PhysicsBody::createEdgePolygon(const Vec2* points, int count, const PhysicsMaterial& material, float border/* = 1*/)
{
    PhysicsBody* body = new (std::nothrow) PhysicsBody();
    if (body && body->init())
    {
        body->addShape(PhysicsShapeEdgePolygon::create(points, count, material, border));
        body->setDynamic(false);
        body->autorelease();
        return body;
    }
    
    CC_SAFE_DELETE(body);
    
    return nullptr;
}

PhysicsBody* PhysicsBody::createEdgeChain(const Vec2* points, int count, const PhysicsMaterial& material, float border/* = 1*/)
{
    PhysicsBody* body = new (std::nothrow) PhysicsBody();
    if (body && body->init())
    {
        body->addShape(PhysicsShapeEdgeChain::create(points, count, material, border));
        body->setDynamic(false);
        body->autorelease();
        return body;
    }
    
    CC_SAFE_DELETE(body);
    
    return nullptr;
}

bool PhysicsBody::init()
{
    do
    {
        _cpBody = cpBodyNew(_mass, _moment);
        internalBodySetMass(_cpBody, _mass);
        cpBodySetUserData(_cpBody, this);
        cpBodySetVelocityUpdateFunc(_cpBody, internalBodyUpdateVelocity);
        
        CC_BREAK_IF(_cpBody == nullptr);
        
        return true;
    } while (false);
    
    return false;
}

void PhysicsBody::removeJoint(PhysicsJoint* joint)
{
    auto it = std::find(_joints.begin(), _joints.end(), joint);
    
    if (it != _joints.end())
    {
        _joints.erase(it);
    }
}

void PhysicsBody::setDynamic(bool dynamic)
{
    if (dynamic != _dynamic)
    {
        _dynamic = dynamic;
        if (dynamic)
        {
            cpBodySetType(_cpBody, CP_BODY_TYPE_DYNAMIC);
            internalBodySetMass(_cpBody, _mass);
            cpBodySetMoment(_cpBody, _moment);
        }
        else
        {
            cpBodySetType(_cpBody, CP_BODY_TYPE_KINEMATIC);
        }
    }
}

void PhysicsBody::setRotationEnable(bool enable)
{
    if (_rotationEnabled != enable)
    {
        cpBodySetMoment(_cpBody, enable ? _moment : PHYSICS_INFINITY);
        _rotationEnabled = enable;
    }
}

void PhysicsBody::setGravityEnable(bool enable)
{
    _gravityEnabled = enable;
}

void PhysicsBody::setRotation(float rotation)
{
    _recordedRotation = rotation;
    _recordedAngle = - (rotation + _rotationOffset) * (M_PI / 180.0);
    cpBodySetAngle(_cpBody, _recordedAngle);
}

void PhysicsBody::setScale(float scaleX, float scaleY)
{
    for (auto& shape : _shapes)
    {
        _area -= shape->getArea();
        if (!_massSetByUser)
            addMass(-shape->getMass());
        if (!_momentSetByUser)
            addMoment(-shape->getMoment());
        
        shape->setScale(scaleX, scaleY);
        
        _area += shape->getArea();
        if (!_massSetByUser)
            addMass(shape->getMass());
        if (!_momentSetByUser)
            addMoment(shape->getMoment());
    }
}

void PhysicsBody::setPosition(float positionX, float positionY)
{
    cpVect tt;

    tt.x = positionX + _positionOffset.x;
    tt.y = positionY + _positionOffset.y;

    cpBodySetPosition(_cpBody, tt);
}

Vec2 PhysicsBody::getPosition() const
{
    cpVect tt = cpBodyGetPosition(_cpBody);
    return Vec2(tt.x - _positionOffset.x, tt.y - _positionOffset.y);
}

void PhysicsBody::setPositionOffset(const Vec2& position)
{
    if (!_positionOffset.equals(position))
    {
        Vec2 pos = getPosition();
        _positionOffset = position;
        setPosition(pos.x, pos.y);
    }
}

float PhysicsBody::getRotation()
{
    if (_recordedAngle != cpBodyGetAngle(_cpBody)) {
        _recordedAngle = cpBodyGetAngle(_cpBody);
        _recordedRotation = - _recordedAngle * 180.0 / M_PI - _rotationOffset;
    }
    return _recordedRotation;
}

PhysicsShape* PhysicsBody::addShape(PhysicsShape* shape, bool addMassAndMoment/* = true*/)
{
    if (shape == nullptr) return nullptr;
    
    // add shape to body
    if (_shapes.getIndex(shape) == -1)
    {
        shape->setBody(this);
        
        // calculate the area, mass, and density
        // area must update before mass, because the density changes depend on it.
        if (addMassAndMoment)
        {
            _area += shape->getArea();
            addMass(shape->getMass());
            addMoment(shape->getMoment());
        }
        
        if (_world && cpBodyGetSpace(_cpBody))
        {
            _world->addShape(shape);
        }
        
        _shapes.pushBack(shape);
    }
    
    return shape;
}

void PhysicsBody::applyForce(const Vec2& force, const Vec2& offset)
{
    if (_dynamic && _mass != PHYSICS_INFINITY)
    {
        cpBodyApplyForceAtLocalPoint(_cpBody, PhysicsHelper::point2cpv(force), PhysicsHelper::point2cpv(offset));
    }
}

void PhysicsBody::resetForces()
{
    cpBodySetForce(_cpBody,  PhysicsHelper::point2cpv(Vec2(0,0)));
}

void PhysicsBody::applyImpulse(const Vec2& impulse, const Vec2& offset)
{
    cpBodyApplyImpulseAtLocalPoint(_cpBody, PhysicsHelper::point2cpv(impulse), PhysicsHelper::point2cpv(offset));
}

void PhysicsBody::applyTorque(float torque)
{
    cpBodySetTorque(_cpBody, torque);
}

void PhysicsBody::setMass(float mass)
{
    if (mass <= 0)
    {
        return;
    }
    _mass = mass;
    _massDefault = false;
    _massSetByUser = true;
    
    // update density
    if (_mass == PHYSICS_INFINITY)
    {
        _density = PHYSICS_INFINITY;
    }
    else
    {
        if (_area > 0)
        {
            _density = _mass / _area;
        }else
        {
            _density = 0;
        }
    }
    
    // the static body's mass and moment is always infinity
    if (_dynamic)
    {
        internalBodySetMass(_cpBody, _mass);
    }
}

void PhysicsBody::addMass(float mass)
{
    if (mass == PHYSICS_INFINITY)
    {
        _mass = PHYSICS_INFINITY;
        _massDefault = false;
        _density = PHYSICS_INFINITY;
    }
    else if (mass == -PHYSICS_INFINITY)
    {
        return;
    }
    else
    {
        if (_massDefault)
        {
            _mass = 0;
            _massDefault = false;
        }
        
        if (_mass + mass > 0)
        {
            _mass +=  mass;
        }else
        {
            _mass = MASS_DEFAULT;
            _massDefault = true;
        }
        
        if (_area > 0)
        {
            _density = _mass / _area;
        }
        else
        {
            _density = 0;
        }
    }
    
    // the static body's mass and moment is always infinity
    if (_dynamic)
    {
        internalBodySetMass(_cpBody, _mass);
    }
}

void PhysicsBody::addMoment(float moment)
{
    if (moment == PHYSICS_INFINITY)
    {
        // if moment is PHYSICS_INFINITY, the moment of the body will become PHYSICS_INFINITY
        _moment = PHYSICS_INFINITY;
        _momentDefault = false;
    }
    else if (moment == -PHYSICS_INFINITY)
    {
        return;
    }
    else
    {
        // if moment of the body is PHYSICS_INFINITY is has no effect
        if (_moment != PHYSICS_INFINITY)
        {
            if (_momentDefault)
            {
                _moment = 0;
                _momentDefault = false;
            }
            
            if (_moment + moment > 0)
            {
                _moment += moment;
            }
            else
            {
                _moment = MOMENT_DEFAULT;
                _momentDefault = true;
            }
        }
    }
    
    // the static body's mass and moment is always infinity
    if (_rotationEnabled && _dynamic)
    {
        cpBodySetMoment(_cpBody, _moment);
    }
}

void PhysicsBody::setVelocity(const Vec2& velocity)
{
    if (cpBodyGetType(_cpBody) == CP_BODY_TYPE_STATIC)
    {
        CCLOG("physics warning: you can't set velocity for a static body.");
        return;
    }

    cpBodySetVelocity(_cpBody, PhysicsHelper::point2cpv(velocity));
}

Vec2 PhysicsBody::getVelocity()
{
    return PhysicsHelper::cpv2point(cpBodyGetVelocity(_cpBody));
}

Vec2 PhysicsBody::getVelocityAtLocalPoint(const Vec2& point)
{
    return PhysicsHelper::cpv2point(cpBodyGetVelocityAtLocalPoint(_cpBody, PhysicsHelper::point2cpv(point)));
}

Vec2 PhysicsBody::getVelocityAtWorldPoint(const Vec2& point)
{
    return PhysicsHelper::cpv2point(cpBodyGetVelocityAtWorldPoint(_cpBody, PhysicsHelper::point2cpv(point)));
}

void PhysicsBody::setAngularVelocity(float velocity)
{
    if (cpBodyGetType(_cpBody) == CP_BODY_TYPE_STATIC)
    {
        CCLOG("physics warning: you can't set angular velocity for a static body.");
        return;
    }

    cpBodySetAngularVelocity(_cpBody, velocity);
}

float PhysicsBody::getAngularVelocity()
{
    return PhysicsHelper::cpfloat2float(cpBodyGetAngularVelocity(_cpBody));
}

void PhysicsBody::setVelocityLimit(float limit)
{
    _velocityLimit = limit;
}

float PhysicsBody::getVelocityLimit()
{
    return _velocityLimit;
}

void PhysicsBody::setAngularVelocityLimit(float limit)
{
    _angularVelocityLimit = limit;
}

float PhysicsBody::getAngularVelocityLimit()
{
    return _angularVelocityLimit;
}

void PhysicsBody::setMoment(float moment)
{
    _moment = moment;
    _momentDefault = false;
    _momentSetByUser = true;
    
    // the static body's mass and moment is always infinity
    if (_rotationEnabled && _dynamic)
    {
        cpBodySetMoment(_cpBody, _moment);
    }
}

PhysicsShape* PhysicsBody::getShape(int tag) const
{
    for (auto& shape : _shapes)
    {
        if (shape->getTag() == tag)
        {
            return shape;
        }
    }
    
    return nullptr;
}

void PhysicsBody::removeShape(int tag, bool reduceMassAndMoment/* = true*/)
{
    for (auto& shape : _shapes)
    {
        if (shape->getTag() == tag)
        {
            removeShape(shape, reduceMassAndMoment);
            return;
        }
    }
}

void PhysicsBody::removeShape(PhysicsShape* shape, bool reduceMassAndMoment/* = true*/)
{
    if (_shapes.getIndex(shape) != -1)
    {
        // deduce the area, mass and moment
        // area must update before mass, because the density changes depend on it.
        if (reduceMassAndMoment)
        {
            _area -= shape->getArea();
            addMass(-shape->getMass());
            addMoment(-shape->getMoment());
        }
        
        //remove
        if (_world)
        {
            _world->removeShape(shape);
        }
        
        // set shape->_body = nullptr make the shape->setBody will not trigger the _body->removeShape function call.
        shape->_body = nullptr;
        shape->setBody(nullptr);
        _shapes.eraseObject(shape);
    }
}

void PhysicsBody::removeAllShapes(bool reduceMassAndMoment/* = true*/)
{
    for (auto& child : _shapes)
    {
        PhysicsShape* shape = dynamic_cast<PhysicsShape*>(child);
        
        // deduce the area, mass and moment
        // area must update before mass, because the density changes depend on it.
        if (reduceMassAndMoment)
        {
            _area -= shape->getArea();
            addMass(-shape->getMass());
            addMoment(-shape->getMoment());
        }
        
        if (_world)
        {
            _world->removeShape(shape);
        }
        
        // set shape->_body = nullptr make the shape->setBody will not trigger the _body->removeShape function call.
        shape->_body = nullptr;
        shape->setBody(nullptr);
    }
    
    _shapes.clear();
}

void PhysicsBody::removeFromWorld()
{
    removeFromPhysicsWorld();
}

void PhysicsBody::setEnabled(bool enable)
{
    if (_enabled != enable)
    {
        _enabled = enable;
        
        if (_world)
        {
            if (enable)
            {
                _world->addBodyOrDelay(this);
            }else
            {
                _world->removeBodyOrDelay(this);
            }
        }
    }
}

bool PhysicsBody::isResting() const
{
    return cpBodyIsSleeping(_cpBody) != cpFalse;
}

void PhysicsBody::setResting(bool rest) const
{
    if (rest && !isResting())
    {
        cpBodySleep(_cpBody);
    }
    else if(!rest && isResting())
    {
        cpBodyActivate(_cpBody);
    }
}

void PhysicsBody::update(float delta)
{
    // damping compute
    if (_isDamping && _dynamic && !isResting())
    {
        _cpBody->v.x *= cpfclamp(1.0f - delta * _linearDamping, 0.0f, 1.0f);
        _cpBody->v.y *= cpfclamp(1.0f - delta * _linearDamping, 0.0f, 1.0f);
        _cpBody->w *= cpfclamp(1.0f - delta * _angularDamping, 0.0f, 1.0f);
    }
}

void PhysicsBody::setCategoryBitmask(int bitmask)
{
    for (auto& shape : _shapes)
    {
        shape->setCategoryBitmask(bitmask);
    }
}

int PhysicsBody::getCategoryBitmask() const
{
    if (!_shapes.empty())
    {
        return _shapes.front()->getCategoryBitmask();
    }
    else
    {
        return UINT_MAX;
    }
}

void PhysicsBody::setContactTestBitmask(int bitmask)
{
    for (auto& shape : _shapes)
    {
        shape->setContactTestBitmask(bitmask);
    }
}

int PhysicsBody::getContactTestBitmask() const
{
    if (!_shapes.empty())
    {
        return _shapes.front()->getContactTestBitmask();
    }
    else
    {
        return 0x00000000;
    }
}

void PhysicsBody::setCollisionBitmask(int bitmask)
{
    for (auto& shape : _shapes)
    {
        shape->setCollisionBitmask(bitmask);
    }
}

int PhysicsBody::getCollisionBitmask() const
{
    if (!_shapes.empty())
    {
        return _shapes.front()->getCollisionBitmask();
    }
    else
    {
        return UINT_MAX;
    }
}

void PhysicsBody::setGroup(int group)
{
    for (auto& shape : _shapes)
    {
        shape->setGroup(group);
    }
}

int PhysicsBody::getGroup() const
{
    if (!_shapes.empty())
    {
        return _shapes.front()->getGroup();
    }
    else
    {
        return 0;
    }
}

void PhysicsBody::setRotationOffset(float rotation)
{
    if (std::abs(_rotationOffset - rotation) > 0.5f)
    {
        float rot = getRotation();
        _rotationOffset = rotation;
        setRotation(rot);
    }
}

Vec2 PhysicsBody::world2Local(const Vec2& point)
{
    return PhysicsHelper::cpv2point(cpBodyWorldToLocal(_cpBody, PhysicsHelper::point2cpv(point)));
}

Vec2 PhysicsBody::local2World(const Vec2& point)
{
    return PhysicsHelper::cpv2point(cpBodyLocalToWorld(_cpBody, PhysicsHelper::point2cpv(point)));
}

void PhysicsBody::beforeSimulation(const Mat4& parentToWorldTransform, const Mat4& nodeToWorldTransform, float scaleX, float scaleY, float rotation)
{
    if (_recordScaleX != scaleX || _recordScaleY != scaleY)
    {
        _recordScaleX = scaleX;
        _recordScaleY = scaleY;
        setScale(scaleX, scaleY);
    }

    // set rotation
    if (_recordedRotation != rotation)
    {
        setRotation(rotation);
    }

    // set position
    auto worldPosition = _ownerCenterOffset;
    nodeToWorldTransform.transformVector(worldPosition.x, worldPosition.y, worldPosition.z, 1.f, &worldPosition);
    setPosition(worldPosition.x, worldPosition.y);

    _recordPosX = worldPosition.x;
    _recordPosY = worldPosition.y;

    if (_owner->getAnchorPoint() != Vec2::ANCHOR_MIDDLE)
    {
        parentToWorldTransform.getInversed().transformVector(worldPosition.x, worldPosition.y, worldPosition.z, 1.f, &worldPosition);
        _offset.x = worldPosition.x - _owner->getPositionX();
        _offset.y = worldPosition.y - _owner->getPositionY();
    }
}

void PhysicsBody::afterSimulation(const Mat4& parentToWorldTransform, float parentRotation)
{
    // set Node position   
    auto tmp = getPosition();
    Vec3 positionInParent(tmp.x, tmp.y, 0.f);
    if (_recordPosX != positionInParent.x || _recordPosY != positionInParent.y)
    {
        parentToWorldTransform.getInversed().transformVector(positionInParent.x, positionInParent.y, positionInParent.z, 1.f, &positionInParent);
        _owner->setPosition(positionInParent.x - _offset.x, positionInParent.y - _offset.y);
    }

    // set Node rotation
    _owner->setRotation(getRotation() - parentRotation);
}

void PhysicsBody::onEnter()
{
    addToPhysicsWorld();
}

void PhysicsBody::onExit()
{
    removeFromPhysicsWorld();
}

void PhysicsBody::onAdd()
{
    _owner->_physicsBody = this;
    auto contentSize = _owner->getContentSize();
    _ownerCenterOffset.x = 0.5f * contentSize.width;
    _ownerCenterOffset.y = 0.5f * contentSize.height;

    setRotationOffset(_owner->getRotation());

    // component may be added after onEnter() has been invoked, so we should add
    // this line to make sure physics body is added to physics world
    addToPhysicsWorld();
}

void PhysicsBody::onRemove()
{
    CCASSERT(_owner != nullptr, "_owner can't be nullptr");

    removeFromPhysicsWorld();

    _owner->_physicsBody = nullptr;
}

void PhysicsBody::addToPhysicsWorld()
{
    if (_owner)
    {
        auto scene = _owner->getScene();
        if (scene)
            scene->getPhysicsWorld()->addBody(this);
    }
}

void PhysicsBody::removeFromPhysicsWorld()
{
    if (_owner)
    {
        auto scene = _owner->getScene();
        if (scene)
            scene->getPhysicsWorld()->removeBody(this);
    }
}

NS_CC_END

#endif // CC_USE_PHYSICS
