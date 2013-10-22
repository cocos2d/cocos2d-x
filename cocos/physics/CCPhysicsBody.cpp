/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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
#include "CCPhysicsBody.h"
#ifdef CC_USE_PHYSICS

#include <algorithm>

#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)
#include "chipmunk.h"
#elif (CC_PHYSICS_ENGINE == CCPHYSICS_BOX2D)
#include "Box2D.h"
#endif

#include "CCPhysicsShape.h"
#include "CCPhysicsJoint.h"
#include "CCPhysicsWorld.h"

#include "chipmunk/CCPhysicsBodyInfo.h"
#include "box2d/CCPhysicsBodyInfo.h"
#include "chipmunk/CCPhysicsJointInfo.h"
#include "box2d/CCPhysicsJointInfo.h"
#include "chipmunk/CCPhysicsWorldInfo.h"
#include "box2d/CCPhysicsWorldInfo.h"
#include "chipmunk/CCPhysicsShapeInfo.h"
#include "box2d/CCPhysicsShapeInfo.h"

#include "chipmunk/CCPhysicsHelper.h"
#include "box2d/CCPhysicsHelper.h"

NS_CC_BEGIN


#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)

namespace
{
    static const float MASS_DEFAULT = 1.0;
    static const float DENSITY_DEFAULT = 1.0;
    static const float ANGULARDAMPING_DEFAULT = 200;
}

PhysicsBody::PhysicsBody()
: _owner(nullptr)
, _world(nullptr)
, _info(nullptr)
, _dynamic(true)
, _enable(true)
, _massDefault(true)
, _angularDampingDefault(true)
, _mass(MASS_DEFAULT)
, _area(0.0)
, _density(DENSITY_DEFAULT)
, _angularDamping(ANGULARDAMPING_DEFAULT)
, _tag(0)
{
}

PhysicsBody::~PhysicsBody()
{
    CC_SAFE_DELETE(_info);
    
    removeAllShapes();
    
    for (auto it = _joints.begin(); it != _joints.end(); ++it)
    {
        PhysicsJoint* joint = *it;
        PhysicsBody* other = joint->getBodyA() == this ? joint->getBodyA() : joint->getBodyB();
        
        other->_joints.erase(std::find(other->_joints.begin(), other->_joints.end(), joint));
        delete joint;
    }
}

PhysicsBody* PhysicsBody::create()
{
    PhysicsBody* body = new PhysicsBody();
    if (body && body->init())
    {
        body->autorelease();
        return body;
    }
    
    CC_SAFE_DELETE(body);
    return nullptr;
}

PhysicsBody* PhysicsBody::createCircle(float radius, PhysicsMaterial material)
{
    PhysicsBody* body = new PhysicsBody();
    if (body && body->init())
    {
        body->addShape(PhysicsShapeCircle::create(radius, material));
        body->autorelease();
        return body;
    }
    
    CC_SAFE_DELETE(body);
    return nullptr;
}

PhysicsBody* PhysicsBody::createBox(Size size, PhysicsMaterial material)
{
    PhysicsBody* body = new PhysicsBody();
    if (body && body->init())
    {
        body->addShape(PhysicsShapeBox::create(size, material));
        body->autorelease();
        return body;
    }
    
    CC_SAFE_DELETE(body);
    return nullptr;
}

PhysicsBody* PhysicsBody::createPolygon(Point* points, int count, PhysicsMaterial material)
{
    PhysicsBody* body = new PhysicsBody();
    if (body && body->init())
    {
        body->addShape(PhysicsShapePolygon::create(points, count, material));
        body->autorelease();
        return body;
    }
    
    CC_SAFE_DELETE(body);
    return nullptr;
}

PhysicsBody* PhysicsBody::createEdgeSegment(Point a, Point b, PhysicsMaterial material, float border/* = 1*/)
{
    PhysicsBody* body = new PhysicsBody();
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

PhysicsBody* PhysicsBody::createEdgeBox(Size size, PhysicsMaterial material, float border/* = 1*/)
{
    PhysicsBody* body = new PhysicsBody();
    if (body && body->init())
    {
        body->addShape(PhysicsShapeEdgeBox::create(size, material, border));
        body->_dynamic = false;
        body->autorelease();
        return body;
    }
    
    CC_SAFE_DELETE(body);
    
    return nullptr;
}

PhysicsBody* PhysicsBody::createEdgePolygon(Point* points, int count, PhysicsMaterial material, float border/* = 1*/)
{
    PhysicsBody* body = new PhysicsBody();
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

PhysicsBody* PhysicsBody::createEdgeChain(Point* points, int count, PhysicsMaterial material, float border/* = 1*/)
{
    PhysicsBody* body = new PhysicsBody();
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
        _info = new PhysicsBodyInfo();
        CC_BREAK_IF(_info == nullptr);
        
        _info->body = cpBodyNew(PhysicsHelper::float2cpfloat(_mass), PhysicsHelper::float2cpfloat(_angularDamping));
        CC_BREAK_IF(_info->body == nullptr);
        
        return true;
    } while (false);
    
    return false;
}

void PhysicsBody::setDynamic(bool dynamic)
{
    if (dynamic != _dynamic)
    {
        if (dynamic)
        {
            cpBodySetMass(_info->body, PhysicsHelper::float2cpfloat(_mass));
            cpBodySetMoment(_info->body, PhysicsHelper::float2cpfloat(_angularDamping));
        }else
        {
            cpBodySetMass(_info->body, PHYSICS_INFINITY);
            cpBodySetMoment(_info->body, PHYSICS_INFINITY);
        }
        
        _dynamic = dynamic;
    }
}

void PhysicsBody::setPosition(Point position)
{
    cpBodySetPos(_info->body, PhysicsHelper::point2cpv(position));
}

void PhysicsBody::setRotation(float rotation)
{
    cpBodySetAngle(_info->body, PhysicsHelper::float2cpfloat(rotation));
}

Point PhysicsBody::getPosition() const
{
    cpVect vec = cpBodyGetPos(_info->body);
    return PhysicsHelper::cpv2point(vec);
}

float PhysicsBody::getRotation() const
{
    return -PhysicsHelper::cpfloat2float(cpBodyGetAngle(_info->body) / 3.14f * 180.0f);
}

void PhysicsBody::addShape(PhysicsShape* shape)
{
    if (shape == nullptr) return;
    
    // already added
    if (shape->getBody() == this)
    {
        return;
    }
    else if (shape->getBody() != nullptr)
    {
        shape->getBody()->removeShape(shape);
    }
    
    // reset the body
    if (shape->_info->body != _info->body)
    {
        for (cpShape* subShape : shape->_info->shapes)
        {
            cpShapeSetBody(subShape, _info->body);
        }
        shape->_info->body = _info->body;
    }
    
    // add shape to body
    if (std::find(_shapes.begin(), _shapes.end(), shape) == _shapes.end())
    {
        shape->setBody(this);
        _shapes.push_back(shape);
        
        // calculate the mass, area and desity
        _area += shape->getArea();
        if (_mass == PHYSICS_INFINITY || shape->getMass() == PHYSICS_INFINITY)
        {
            _mass = PHYSICS_INFINITY;
            _massDefault = false;
        }else
        {
            if (shape->getMass() > 0)
            {
                _mass = (_massDefault ? 0 : _mass) + shape->getMass();
                _massDefault = false;
            }
        }
        cpBodySetMass(_info->body, _mass);
        
        if (!_massDefault)
        {
            if (_mass == PHYSICS_INFINITY)
            {
                _density = PHYSICS_INFINITY;
            }else
            {
                _density = _mass / _area;
            }
        }
        
        if (shape->getAngularDumping() > 0)
        {
            if (shape->getAngularDumping() == INFINITY)
            {
                _angularDamping = INFINITY;
                _angularDampingDefault = false;
                cpBodySetMoment(_info->body, _angularDamping);
            }
            else if (_angularDamping != INFINITY)
            {
                _angularDamping = (_angularDampingDefault ? 0 : _angularDamping) + shape->getAngularDumping();
                _angularDampingDefault = false;
                cpBodySetMoment(_info->body, _angularDamping);
            }
        }
        
        if (_world != nullptr) _world->addShape(shape);
        
        shape->retain();
    }
}

void PhysicsBody::applyForce(Point force)
{
    applyForce(force, Point());
}

void PhysicsBody::applyForce(Point force, Point offset)
{
    cpBodyApplyForce(_info->body, PhysicsHelper::point2cpv(force), PhysicsHelper::point2cpv(offset));
}

void PhysicsBody::applyImpulse(Point impulse)
{
    applyImpulse(impulse, Point());
}

void PhysicsBody::applyImpulse(Point impulse, Point offset)
{
    cpBodyApplyImpulse(_info->body, PhysicsHelper::point2cpv(impulse), PhysicsHelper::point2cpv(offset));
}

void PhysicsBody::applyTorque(float torque)
{
    cpBodySetTorque(_info->body, PhysicsHelper::float2cpfloat(torque));
}

void PhysicsBody::setMass(float mass)
{
    _mass = mass;
    _massDefault = false;
    
    cpBodySetMass(_info->body, PhysicsHelper::float2cpfloat(_mass));
}

void PhysicsBody::setVelocity(Point velocity)
{
    cpBodySetVel(_info->body, PhysicsHelper::point2cpv(velocity));
}

Point PhysicsBody::getVelocity()
{
    return PhysicsHelper::cpv2point(cpBodyGetVel(_info->body));
}

void PhysicsBody::setAngularDamping(float angularDamping)
{
    _angularDamping = angularDamping;
    _angularDampingDefault = false;
    
    cpBodySetMoment(_info->body, _angularDamping);
}

PhysicsShape* PhysicsBody::getShapeByTag(int tag)
{
    for (auto shape : _shapes)
    {
        if (shape->getTag() == tag)
        {
            return shape;
        }
    }
    
    return nullptr;
}

void PhysicsBody::removeShapeByTag(int tag)
{
    for (auto shape : _shapes)
    {
        if (shape->getTag() == tag)
        {
            removeShape(shape);
            return;
        }
    }
}

void PhysicsBody::removeShape(PhysicsShape* shape)
{
    auto it = std::find(_shapes.begin(), _shapes.end(), shape);
    
    if (it != _shapes.end())
    {
        if (_world)
        {
            _world->removeShape(shape);
        }
        
        _shapes.erase(it);
        
        
        // deduce the mass, area and angularDamping
        if (_mass != PHYSICS_INFINITY && shape->getMass() != PHYSICS_INFINITY)
        {
            if (_mass - shape->getMass() <= 0)
            {
                _mass = MASS_DEFAULT;
                _massDefault = true;
            }else
            {
                _mass = _mass = shape->getMass();
            }
            
            _area -= shape->getArea();
            
            if (_mass == PHYSICS_INFINITY)
            {
                _density = PHYSICS_INFINITY;
            }
            else if (_area > 0)
            {
                _density = _mass / _area;
            }
            else
            {
                _density = DENSITY_DEFAULT;
            }
            
            if (_angularDamping - shape->getAngularDumping() > 0)
            {
                _angularDamping -= shape->getAngularDumping();
            }else
            {
                _angularDamping = ANGULARDAMPING_DEFAULT;
                _angularDampingDefault = true;
            }
        }
        
        shape->release();
    }
}

void PhysicsBody::removeAllShapes()
{
    for (auto shape : _shapes)
    {
        if (_world)
        {
            _world->removeShape(shape);
        }
        
        delete shape;
    }
    
    _shapes.clear();
}

void PhysicsBody::setEnable(bool enable)
{
    if (_enable != enable)
    {
        _enable = enable;
        
        if (_world)
        {
            if (enable)
            {
                _world->addBody(this);
            }else
            {
                _world->removeBody(this);
            }
        }
    }
}

//Clonable* PhysicsBody::clone() const
//{
//    PhysicsBody* body = new PhysicsBody();
//    
//    body->autorelease();
//    
//    return body;
//}

#elif (CC_PHYSICS_ENGINE == CC_PHYSICS_BOX2D)


#endif

NS_CC_END

#endif // CC_USE_PHYSICS
