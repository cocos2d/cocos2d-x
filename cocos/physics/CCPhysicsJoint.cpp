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

#include "CCPhysicsJoint.h"
#ifdef CC_USE_PHYSICS

#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)
#include "chipmunk.h"
#elif (CC_PHYSICS_ENGINE == CCPHYSICS_BOX2D)
#include "Box2D.h"
#endif

#include "CCPhysicsBody.h"

#include "chipmunk/CCPhysicsJointInfo.h"
#include "box2d/CCPhysicsJointInfo.h"
#include "chipmunk/CCPhysicsBodyInfo.h"
#include "box2d/CCPhysicsBodyInfo.h"
#include "chipmunk/CCPhysicsShapeInfo.h"
#include "box2d/CCPhysicsShapeInfo.h"
#include "chipmunk/CCPhysicsHelper.h"
#include "box2d/CCPhysicsHelper.h"
#include "CCNode.h"

NS_CC_BEGIN

PhysicsJoint::PhysicsJoint()
: _bodyA(nullptr)
, _bodyB(nullptr)
, _info(nullptr)
, _enable(false)
, _collisionEnable(true)
, _tag(0)
{
    
}

PhysicsJoint::~PhysicsJoint()
{
    // reset the shapes collision group
    setCollisionEnable(true);
    
    CC_SAFE_DELETE(_info);
}

bool PhysicsJoint::init(cocos2d::PhysicsBody *a, cocos2d::PhysicsBody *b)
{
    do
    {
        CC_BREAK_IF(!(_info = new PhysicsJointInfo(this)));
        
        if (a != nullptr)
        {
            _bodyA = a;
            _bodyA->_joints.push_back(this);
        }
        
        if (b != nullptr)
        {
            _bodyB = b;
            _bodyB->_joints.push_back(this);
        }
        
        return true;
    } while (false);
    
    return false;
}

void PhysicsJoint::setEnable(bool enable)
{
    if (_enable != enable)
    {
        _enable = enable;
        
        if (enable)
        {
            
        }else
        {
            
        }
    }
}

PhysicsJointPin::PhysicsJointPin()
{
    
}

PhysicsJointPin::~PhysicsJointPin()
{
    
}

PhysicsJointFixed::PhysicsJointFixed()
{
    
}

PhysicsJointFixed::~PhysicsJointFixed()
{
    
}

PhysicsJointSliding::PhysicsJointSliding()
{
    
}

PhysicsJointSliding::~PhysicsJointSliding()
{
    
}

PhysicsJointLimit::PhysicsJointLimit()
{
    
}

PhysicsJointLimit::~PhysicsJointLimit()
{
    
}

#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)
PhysicsBodyInfo* PhysicsJoint::bodyInfo(PhysicsBody* body) const
{
    return body->_info;
}

Node* PhysicsJoint::bodyOwner(PhysicsBody* body) const
{
    return body->_owner;
}


void PhysicsJoint::setCollisionEnable(bool enable)
{
    if (_collisionEnable != enable)
    {
        _collisionEnable = enable;
        
//        for (auto shape : _bodyB->_shapes)
//        {
//            shape->_info->setGroup(enable ? _bodyB->_info->group : _bodyA->_info->group);
//        }
    }
}

PhysicsJointFixed* PhysicsJointFixed::create(PhysicsBody* a, PhysicsBody* b, const Point& anchr)
{
    PhysicsJointFixed* joint = new PhysicsJointFixed();
    
    if (joint && joint->init(a, b, anchr))
    {
        return joint;
    }
    
    CC_SAFE_DELETE(joint);
    return nullptr;
}

bool PhysicsJointFixed::init(PhysicsBody* a, PhysicsBody* b, const Point& anchr)
{
    do
    {
        CC_BREAK_IF(!PhysicsJoint::init(a, b));
        
        bodyOwner(a)->setPosition(anchr);
        bodyOwner(b)->setPosition(anchr);
        
        // add a pivot joint to fixed two body together
        cpConstraint* joint = cpPivotJointNew(bodyInfo(a)->body, bodyInfo(b)->body,
                                        PhysicsHelper::point2cpv(anchr));
        CC_BREAK_IF(joint == nullptr);
        _info->add(joint);
        
        // add a gear joint to make two body have the same rotation.
        joint = cpGearJointNew(bodyInfo(a)->body, bodyInfo(b)->body, 0, 1);
        CC_BREAK_IF(joint == nullptr);
        _info->add(joint);
        
        setCollisionEnable(false);
        
        return true;
    } while (false);
    
    return false;
}

PhysicsJointPin* PhysicsJointPin::create(PhysicsBody* a, PhysicsBody* b, const Point& anchr)
{
    PhysicsJointPin* joint = new PhysicsJointPin();
    
    if (joint && joint->init(a, b, anchr))
    {
        return joint;
    }
    
    CC_SAFE_DELETE(joint);
    return nullptr;
}

bool PhysicsJointPin::init(PhysicsBody *a, PhysicsBody *b, const Point& anchr)
{
    do
    {
        CC_BREAK_IF(!PhysicsJoint::init(a, b));
        cpConstraint* joint = cpPivotJointNew(bodyInfo(a)->body, bodyInfo(b)->body,
                                       PhysicsHelper::point2cpv(anchr));
        
        CC_BREAK_IF(joint == nullptr);
        
        _info->add(joint);
        
        //setCollisionEnable(false);
        
        return true;
    } while (false);
    
    return false;
}

void PhysicsJointPin::setMaxForce(float force)
{
    _info->joints.front()->maxForce = PhysicsHelper::float2cpfloat(force);
}

float PhysicsJointPin::getMaxForce()
{
    return PhysicsHelper::cpfloat2float(_info->joints.front()->maxForce);
}

PhysicsJointSliding* PhysicsJointSliding::create(PhysicsBody* a, PhysicsBody* b, const Point& grooveA, const Point& grooveB, const Point& anchr)
{
    PhysicsJointSliding* joint = new PhysicsJointSliding();
    
    if (joint && joint->init(a, b, grooveA, grooveB, anchr))
    {
        return joint;
    }
    
    CC_SAFE_DELETE(joint);
    return nullptr;
}

bool PhysicsJointSliding::init(PhysicsBody* a, PhysicsBody* b, const Point& grooveA, const Point& grooveB, const Point& anchr)
{
    do
    {
        CC_BREAK_IF(!PhysicsJoint::init(a, b));
        
        cpConstraint* joint = cpGrooveJointNew(bodyInfo(a)->body, bodyInfo(b)->body,
                                       PhysicsHelper::point2cpv(grooveA),
                                       PhysicsHelper::point2cpv(grooveB),
                                       PhysicsHelper::point2cpv(anchr));
        
        CC_BREAK_IF(joint == nullptr);
        
        _info->add(joint);
        
        return true;
    } while (false);
    
    return false;
}


PhysicsJointLimit* PhysicsJointLimit::create(PhysicsBody* a, PhysicsBody* b, const Point& anchr1, const Point& anchr2)
{
    PhysicsJointLimit* joint = new PhysicsJointLimit();
    
    if (joint && joint->init(a, b, anchr1, anchr2))
    {
        return joint;
    }
    
    CC_SAFE_DELETE(joint);
    return nullptr;
}

bool PhysicsJointLimit::init(PhysicsBody* a, PhysicsBody* b, const Point& anchr1, const Point& anchr2)
{
    do
    {
        CC_BREAK_IF(!PhysicsJoint::init(a, b));
        
        cpConstraint* joint = cpSlideJointNew(bodyInfo(a)->body, bodyInfo(b)->body,
                                       PhysicsHelper::point2cpv(anchr1),
                                       PhysicsHelper::point2cpv(anchr2),
                                       0,
                                       PhysicsHelper::float2cpfloat(anchr1.getDistance(anchr2)));
        
        CC_BREAK_IF(joint == nullptr);
        
        _info->add(joint);
        
        return true;
    } while (false);
    
    return false;
}

float PhysicsJointLimit::getMin()
{
    return PhysicsHelper::cpfloat2float(cpSlideJointGetMin(_info->joints.front()));
}

void PhysicsJointLimit::setMin(float min)
{
    cpSlideJointSetMin(_info->joints.front(), PhysicsHelper::float2cpfloat(min));
}

float PhysicsJointLimit::getMax()
{
    return PhysicsHelper::cpfloat2float(cpSlideJointGetMax(_info->joints.front()));
}

void PhysicsJointLimit::setMax(float max)
{
    cpSlideJointSetMax(_info->joints.front(), PhysicsHelper::float2cpfloat(max));
}

#elif (CC_PHYSICS_ENGINE == CC_PHYSICS_BOX2D)

#endif

NS_CC_END
#endif // CC_USE_PHYSICS
