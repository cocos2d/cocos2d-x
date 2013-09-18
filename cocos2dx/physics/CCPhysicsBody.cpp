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

#include "chipmunk/CCPhysicsHelper.h"
#include "Box2D/CCPhysicsHelper.h"

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
, _dynamic(false)
, _massDefault(true)
, _angularDampingDefault(true)
, _mass(MASS_DEFAULT)
, _area(0.0)
, _density(DENSITY_DEFAULT)
, _angularDamping(ANGULARDAMPING_DEFAULT)
{
}

PhysicsBody::~PhysicsBody()
{
    CC_SAFE_DELETE(_info);
    
    for (auto it = _shapes.begin(); it != _shapes.end(); ++it)
    {
        delete *it;
    }
    
    for (auto it = _joints.begin(); it != _joints.end(); ++it)
    {
        PhysicsJoint* joint = *it;
        PhysicsBody* other = joint->getBodyA() == this ? joint->getBodyA() : joint->getBodyB();
        
        other->_joints.erase(std::find(other->_joints.begin(), other->_joints.end(), joint));
        delete joint;
    }
}

PhysicsBody* PhysicsBody::createCircle(float radius)
{
    PhysicsBody* body = new PhysicsBody();
    if (body && body->init())
    {
        body->addCircle(radius);
        body->autorelease();
        return body;
    }
    
    CC_SAFE_DELETE(body);
    return nullptr;
}

PhysicsBody* PhysicsBody::createBox(Size size)
{
    PhysicsBody* body = new PhysicsBody();
    if (body && body->init())
    {
        body->addBox(size);
        body->autorelease();
        return body;
    }
    
    CC_SAFE_DELETE(body);
    return nullptr;
}

PhysicsBody* PhysicsBody::createPolygon(Point* points, int count)
{
    PhysicsBody* body = new PhysicsBody();
    if (body && body->init())
    {
        body->addPolygon(points, count);
        body->autorelease();
        return body;
    }
    
    CC_SAFE_DELETE(body);
    return nullptr;
}

PhysicsBody* PhysicsBody::createEdgeSegment(Point a, Point b, float border/* = 1*/)
{
    PhysicsBody* body = new PhysicsBody();
    if (body && body->initStatic())
    {
        body->addEdgeSegment(a, b, border);
        body->autorelease();
        return body;
    }
    
    CC_SAFE_DELETE(body);
    return nullptr;
}

PhysicsBody* PhysicsBody::createEdgeBox(Size size, float border/* = 1*/)
{
    PhysicsBody* body = new PhysicsBody();
    if (body && body->initStatic())
    {
        body->addEdgeBox(size, border);
        body->autorelease();
        return body;
    }
    
    CC_SAFE_DELETE(body);
    
    return nullptr;
}

PhysicsBody* PhysicsBody::createEdgePolygon(Point* points, int count, float border/* = 1*/)
{
    PhysicsBody* body = new PhysicsBody();
    if (body && body->initStatic())
    {
        body->addEdgePolygon(points, count, border);
        body->autorelease();
        return body;
    }
    
    CC_SAFE_DELETE(body);
    
    return nullptr;
}

PhysicsBody* PhysicsBody::createEdgeChain(Point* points, int count, float border/* = 1*/)
{
    PhysicsBody* body = new PhysicsBody();
    if (body && body->initStatic())
    {
        body->addEdgeChain(points, count);
        body->autorelease();
        return body;
    }
    
    CC_SAFE_DELETE(body);
    
    return nullptr;
}

PhysicsShapeCircle* PhysicsBody::addCircle(float radius, Point offset/* = Point(0, 0)*/)
{
    _area = PhysicsHelper::cpfloat2float(cpAreaForCircle(0, radius));
    setMass((_massDefault ? 0 : getMass()) + _area * _density);
    
    setAngularDamping((_angularDampingDefault ? 0 : getAngularDamping())
                      + PhysicsHelper::cpfloat2float(cpMomentForCircle(getMass(), 0, radius, PhysicsHelper::point2cpv(offset))));
    
    return PhysicsShapeCircle::create(this, radius, offset);
}

PhysicsShapeBox* PhysicsBody::addBox(Size size, Point offset/* = Point(0, 0)*/)
{
    cpVect cpOffset = PhysicsHelper::size2cpv(size);
    cpVect vec[4] = {};
    vec[0] = cpv(0, 0);
    vec[1] = cpv(0, cpOffset.y);
    vec[2] = cpv(cpOffset.x, cpOffset.y);
    vec[3] = cpv(cpOffset.x, 0);
    
    _area = PhysicsHelper::cpfloat2float(cpAreaForPoly(4, vec));
    setMass((_massDefault ? 0 : getMass()) + _area * _density);
    
    setAngularDamping((_angularDampingDefault ? 0 : getAngularDamping())
                      + PhysicsHelper::cpfloat2float(cpMomentForBox(getMass(), PhysicsHelper::float2cpfloat(size.width), PhysicsHelper::float2cpfloat(size.height))));
    
    return PhysicsShapeBox::create(this, size, offset);
}

PhysicsShapePolygon* PhysicsBody::addPolygon(Point* points, int count, Point offset/* = Point(0, 0)*/)
{
    cpVect* vec = new cpVect[count];
    PhysicsHelper::points2cpvs(points, vec, count);
    _area = PhysicsHelper::cpfloat2float(cpAreaForPoly(count, vec));
    
    setAngularDamping((_angularDampingDefault ? 0 : getAngularDamping())
                      + PhysicsHelper::cpfloat2float(cpMomentForPoly(getMass(), count, vec, PhysicsHelper::point2cpv(offset))));
    
    delete[] vec;
    
    return PhysicsShapePolygon::create(this, points, count, offset);
}

PhysicsShapeEdgeSegment* PhysicsBody::addEdgeSegment(Point a, Point b, float border/* = 1*/)
{
    return PhysicsShapeEdgeSegment::create(this, a, b, border);
}

PhysicsShapeEdgeBox* PhysicsBody::addEdgeBox(Size size, float border/* = 1*/, Point offset/* = Point(0, 0)*/)
{
    return PhysicsShapeEdgeBox::create(this, size, border, offset);
}

PhysicsShapeEdgePolygon* PhysicsBody::addEdgePolygon(Point* points, int count, float border/* = 1*/)
{
    return PhysicsShapeEdgePolygon::create(this, points, count);
}

PhysicsShapeEdgeChain* PhysicsBody::addEdgeChain(Point* points, int count, float border/* = 1*/)
{
    return PhysicsShapeEdgeChain::create(this, points, count, border);
}

bool PhysicsBody::init()
{
    do
    {
        _info = new PhysicsBodyInfo();
        CC_BREAK_IF(_info == nullptr);
        
        _info->body = cpBodyNew(PhysicsHelper::float2cpfloat(_mass), PhysicsHelper::float2cpfloat(_angularDamping));
        CC_BREAK_IF(_info->body == nullptr);
        _dynamic = true;
        
        return true;
    } while (false);
    
    return false;
}

void PhysicsBody::setDynamic(bool dynamic)
{
    _dynamic = dynamic;
    if (_world != nullptr && cpBodyIsStatic(_info->body) == (cpBool)_dynamic)
    {
        if (dynamic)
        {
            cpSpaceConvertBodyToDynamic(_world->_info->space, _info->body, _mass, _angularDamping);
        }else
        {
            cpSpaceConvertBodyToStatic(_world->_info->space, _info->body);
        }
    }
}

bool PhysicsBody::initStatic()
{
    do
    {
        _info = new PhysicsBodyInfo();
        CC_BREAK_IF(_info == nullptr);
        
        _info->body = cpBodyNewStatic();
        CC_BREAK_IF(_info->body == nullptr);
        _dynamic = false;
        
        return true;
    } while (false);
    
    return false;
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
    
    _shapes.push_back(shape);
    
    if (_world != nullptr) _world->addShape(shape);
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

void PhysicsBody::setAngularDamping(float angularDamping)
{
    _angularDamping = angularDamping;
    _angularDampingDefault = false;
    
    cpBodySetMoment(_info->body, _angularDamping);
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
