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
#include "Box2D/CCPhysicsBodyInfo.h"
#include "chipmunk/CCPhysicsJointInfo.h"
#include "Box2D/CCPhysicsJointInfo.h"
#include "chipmunk/CCPhysicsWorldInfo.h"
#include "Box2D/CCPhysicsWorldInfo.h"
#include "chipmunk/CCPhysicsShapeInfo.h"
#include "Box2D/CCPhysicsShapeInfo.h"

#include "chipmunk/CCPhysicsHelper.h"
#include "Box2D/CCPhysicsHelper.h"

NS_CC_BEGIN


#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)

namespace
{
    static const float MASS_DEFAULT = 1.0;
    static const float MOMENT_DEFAULT = 200;
}

PhysicsBody::PhysicsBody()
: _owner(nullptr)
, _world(nullptr)
, _info(nullptr)
, _dynamic(true)
, _enable(true)
, _massDefault(true)
, _momentDefault(true)
, _mass(MASS_DEFAULT)
, _area(0.0)
, _density(0)
, _moment(MOMENT_DEFAULT)
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
        
        _info->body = cpBodyNew(PhysicsHelper::float2cpfloat(_mass), PhysicsHelper::float2cpfloat(_moment));
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
            cpBodySetMoment(_info->body, PhysicsHelper::float2cpfloat(_moment));
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
        
        // calculate the area, mass, and desity
        // area must update before mass, because the density changes depend on it.
        _area += shape->getArea();
        addMass(shape->getMass());
        addMoment(shape->getMoment());
        
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
    
    cpBodySetMass(_info->body, PhysicsHelper::float2cpfloat(_mass));
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
    else if (_mass != PHYSICS_INFINITY)
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
    
    cpBodySetMass(_info->body, PhysicsHelper::float2cpfloat(_mass));
}

void PhysicsBody::addMoment(float moment)
{
    if (moment == PHYSICS_INFINITY)
    {
        // if moment is INFINITY, the moment of the body will become INFINITY
        _moment = PHYSICS_INFINITY;
        _momentDefault = false;
    }
    else if (moment == -PHYSICS_INFINITY)
    {
        // if moment is -INFINITY, it won't change
        return;
    }
    else
    {
        // if moment of the body is INFINITY is has no effect
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
    
    cpBodySetMoment(_info->body, PhysicsHelper::float2cpfloat(_moment));
}

void PhysicsBody::setVelocity(Point velocity)
{
    cpBodySetVel(_info->body, PhysicsHelper::point2cpv(velocity));
}

Point PhysicsBody::getVelocity()
{
    return PhysicsHelper::cpv2point(cpBodyGetVel(_info->body));
}

void PhysicsBody::setMoment(float moment)
{
    _moment = moment;
    _momentDefault = false;
    
    cpBodySetMoment(_info->body, PhysicsHelper::float2cpfloat(_moment));
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
        
        
        // deduce the area, mass and moment
        // area must update before mass, because the density changes depend on it.
        _area -= shape->getArea();
        addMass(-shape->getMass());
        addMoment(-shape->getMoment());
        
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
