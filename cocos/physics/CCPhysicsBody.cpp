/****************************************************************************
 Copyright (c) 2013 Chukong Technologies Inc.
 
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

#include "chipmunk.h"

#include "2d/CCScene.h"
#include "physics/CCPhysicsShape.h"
#include "physics/CCPhysicsJoint.h"
#include "physics/CCPhysicsWorld.h"
#include "chipmunk/CCPhysicsHelper_chipmunk.h"

inline void cpBodyUpdateVelocityWithoutGravity(cpBody *body, cpVect gravity, cpFloat damping, cpFloat dt) 
{
    cpBodyUpdateVelocity(body, cpvzero, damping, dt);
}

NS_CC_BEGIN
extern const float PHYSICS_INFINITY;

namespace
{
    static const float MASS_DEFAULT = 1.0;
    static const float MOMENT_DEFAULT = 200;
}

PhysicsBody::PhysicsBody()
: _node(nullptr)
, _world(nullptr)
, _body(nullptr)
, _dynamic(true)
, _enabled(true)
, _rotationEnabled(true)
, _gravityEnabled(true)
, _massDefault(true)
, _momentDefault(true)
, _mass(MASS_DEFAULT)
, _area(0.0f)
, _density(0.0f)
, _moment(MOMENT_DEFAULT)
, _isDamping(false)
, _linearDamping(0.0f)
, _angularDamping(0.0f)
, _tag(0)
, _rotationOffset(0)
, _recordPosition(Vec2::ZERO)
, _rotation(0)
, _scaleX(1.0f)
, _scaleY(1.0f)
{
}

PhysicsBody::~PhysicsBody()
{
    for (auto it = _joints.begin(); it != _joints.end(); ++it)
    {
        PhysicsJoint* joint = *it;
        
        PhysicsBody* other = joint->getBodyA() == this ? joint->getBodyB() : joint->getBodyA();
        other->removeJoint(joint);
        delete joint;
    }
    
    if (_body)
    {
        cpBodyFree(_body);
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
        body->_dynamic = false;
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
        body->_dynamic = false;
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
        body->_dynamic = false;
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
        body->_dynamic = false;
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
        _body = cpBodyNew(PhysicsHelper::float2cpfloat(_mass), PhysicsHelper::float2cpfloat(_moment));
        
        CC_BREAK_IF(_body == nullptr);
        
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
            
            if (_world && _body->space_private)
            {
                cpSpaceConvertBodyToDynamic(_world->_space, _body, _mass, _moment);
                if (!cpSpaceContainsBody(_world->_space, _body))
                {
                    cpSpaceAddBody(_world->_space, _body);
                }
            }
            else
            {
                cpBodySetMass(_body, _mass);
                cpBodySetMoment(_body, _moment);
                _body->node_private.idleTime = 0.0f;
            }
        }
        else
        {
            if (_world && _body->space_private)
            {
                if (cpSpaceContainsBody(_world->_space, _body))
                {
                    cpSpaceRemoveBody(_world->_space, _body);
                }
                cpSpaceConvertBodyToStatic(_world->_space, _body);
            }
            else
            {
                cpBodySetMass(_body, (cpFloat)INFINITY);
                cpBodySetMoment(_body, (cpFloat)INFINITY);
                _body->node_private.idleTime = (cpFloat)INFINITY;
            }
        }
    }
}

void PhysicsBody::setRotationEnable(bool enable)
{
    if (_rotationEnabled != enable)
    {
        cpBodySetMoment(_body, enable ? _moment : PHYSICS_INFINITY);
        _rotationEnabled = enable;
    }
}

void PhysicsBody::setGravityEnable(bool enable)
{
    if (_gravityEnabled != enable)
    {
        _gravityEnabled = enable;
        
        if (enable)
        {
            _body->velocity_func = cpBodyUpdateVelocity;
        } 
        else
        {
            _body->velocity_func = cpBodyUpdateVelocityWithoutGravity;
        }
    }
}

void PhysicsBody::setPosition(const Vec2& position)
{
    _recordPosition = position;
    cpBodySetPos(_body, PhysicsHelper::point2cpv(position + _positionOffset));
}

void PhysicsBody::setRotation(float rotation)
{
    _rotation = rotation;
    cpBodySetAngle(_body, -PhysicsHelper::float2cpfloat((rotation + _rotationOffset) * (M_PI / 180.0f)));
}

void PhysicsBody::setScale(float scaleX, float scaleY)
{
    _scaleX = scaleX;
    _scaleY = scaleY;
    for (auto shape : _shapes)
    {
        shape->setScale(scaleX, scaleY);
    }
}

Vec2 PhysicsBody::getPosition() const
{
    cpVect vec = cpBodyGetPos(_body);
    return PhysicsHelper::cpv2point(vec) - _positionOffset;
}

float PhysicsBody::getRotation() const
{
    return -PhysicsHelper::cpfloat2float(cpBodyGetAngle(_body) * (180.0f / M_PI)) - _rotationOffset;
}

PhysicsShape* PhysicsBody::addShape(PhysicsShape* shape, bool addMassAndMoment/* = true*/)
{
    if (shape == nullptr) return nullptr;
    
    // add shape to body
    if (_shapes.getIndex(shape) == -1)
    {
        shape->setBody(this);
        shape->setScale(_scaleX, _scaleY);
        
        // calculate the area, mass, and desity
        // area must update before mass, because the density changes depend on it.
        if (addMassAndMoment)
        {
            _area += shape->getArea();
            addMass(shape->getMass());
            addMoment(shape->getMoment());
        }
        
        if (_world && _body->space_private)
        {
            _world->addShape(shape);
        }
        
        _shapes.pushBack(shape);
    }
    
    return shape;
}

void PhysicsBody::applyForce(const Vect& force)
{
    applyForce(force, Vec2::ZERO);
}

void PhysicsBody::applyForce(const Vect& force, const Vec2& offset)
{
    if (_dynamic && _mass != PHYSICS_INFINITY)
    {
        cpBodyApplyForce(_body, PhysicsHelper::point2cpv(force), PhysicsHelper::point2cpv(offset));
    }
}

void PhysicsBody::resetForces()
{
    cpBodyResetForces(_body);
}

void PhysicsBody::applyImpulse(const Vect& impulse)
{
    applyImpulse(impulse, Vec2());
}

void PhysicsBody::applyImpulse(const Vect& impulse, const Vec2& offset)
{
    cpBodyApplyImpulse(_body, PhysicsHelper::point2cpv(impulse), PhysicsHelper::point2cpv(offset));
}

void PhysicsBody::applyTorque(float torque)
{
    cpBodySetTorque(_body, PhysicsHelper::float2cpfloat(torque));
}

void PhysicsBody::setMass(float mass)
{
    if (mass <= 0)
    {
        return;
    }

    _mass = mass;
    _massDefault = false;
    
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
        cpBodySetMass(_body, _mass);
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
        cpBodySetMass(_body, _mass);
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
        cpBodySetMoment(_body, PhysicsHelper::float2cpfloat(_moment));
    }
}

void PhysicsBody::setVelocity(const Vec2& velocity)
{
    if (!_dynamic)
    {
        CCLOG("physics warning: your can't set velocity for a static body.");
        return;
    }
    
    cpBodySetVel(_body, PhysicsHelper::point2cpv(velocity));
}

Vec2 PhysicsBody::getVelocity()
{
    return PhysicsHelper::cpv2point(cpBodyGetVel(_body));
}

Vec2 PhysicsBody::getVelocityAtLocalPoint(const Vec2& point)
{
    return PhysicsHelper::cpv2point(cpBodyGetVelAtLocalPoint(_body, PhysicsHelper::point2cpv(point)));
}

Vec2 PhysicsBody::getVelocityAtWorldPoint(const Vec2& point)
{
    return PhysicsHelper::cpv2point(cpBodyGetVelAtWorldPoint(_body, PhysicsHelper::point2cpv(point)));
}

void PhysicsBody::setAngularVelocity(float velocity)
{
    if (!_dynamic)
    {
        CCLOG("physics warning: your can't set angular velocity for a static body.");
        return;
    }
    
    cpBodySetAngVel(_body, PhysicsHelper::float2cpfloat(velocity));
}

float PhysicsBody::getAngularVelocity()
{
    return PhysicsHelper::cpfloat2float(cpBodyGetAngVel(_body));
}

void PhysicsBody::setVelocityLimit(float limit)
{
    cpBodySetVelLimit(_body, PhysicsHelper::float2cpfloat(limit));
}

float PhysicsBody::getVelocityLimit()
{
    return PhysicsHelper::cpfloat2float(cpBodyGetVelLimit(_body));
}

void PhysicsBody::setAngularVelocityLimit(float limit)
{
    cpBodySetAngVelLimit(_body, PhysicsHelper::float2cpfloat(limit));
}

float PhysicsBody::getAngularVelocityLimit()
{
    return PhysicsHelper::cpfloat2float(cpBodyGetAngVelLimit(_body));
}

void PhysicsBody::setMoment(float moment)
{
    _moment = moment;
    _momentDefault = false;
    
    // the static body's mass and moment is always infinity
    if (_rotationEnabled && _dynamic)
    {
        cpBodySetMoment(_body, PhysicsHelper::float2cpfloat(_moment));
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
    if (_world)
    {
        _world->removeBody(this);
    }
}

void PhysicsBody::setEnable(bool enable)
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
    return CP_PRIVATE(_body->node).root != ((cpBody*)0);
}

void PhysicsBody::setResting(bool rest) const
{
    if (rest && !isResting())
    {
        cpBodySleep(_body);
    }else if(!rest && isResting())
    {
        cpBodyActivate(_body);
    }
}

void PhysicsBody::update(float delta)
{
    if (_node)
    {
        auto parent = _node->getParent();
        
        float newRotation = getRotation();
        if (newRotation != _rotation)
        {
            auto scene = &_world->getScene();
            _rotation = newRotation;
            for (; parent != scene; parent = parent->getParent())
            {
                newRotation -= parent->getRotation();
            }
            _node->setRotation(newRotation);
        }
        
        // damping compute
        if (_isDamping && _dynamic && !isResting())
        {
            _body->v.x *= cpfclamp(1.0f - delta * _linearDamping, 0.0f, 1.0f);
            _body->v.y *= cpfclamp(1.0f - delta * _linearDamping, 0.0f, 1.0f);
            _body->w *= cpfclamp(1.0f - delta * _angularDamping, 0.0f, 1.0f);
        }
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

void PhysicsBody::setPositionOffset(const Vec2& position)
{
    if (!_positionOffset.equals(position))
    {
        Vec2 pos = getPosition();
        _positionOffset = position;
        setPosition(pos);
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
    return PhysicsHelper::cpv2point(cpBodyWorld2Local(_body, PhysicsHelper::point2cpv(point)));
}

Vec2 PhysicsBody::local2World(const Vec2& point)
{
    return PhysicsHelper::cpv2point(cpBodyLocal2World(_body, PhysicsHelper::point2cpv(point)));
}

NS_CC_END

#endif // CC_USE_PHYSICS
