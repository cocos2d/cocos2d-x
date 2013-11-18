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
#include "CCPhysicsWorld.h"

#include "chipmunk/CCPhysicsJointInfo_chipmunk.h"
#include "box2d/CCPhysicsJointInfo_box2d.h"
#include "chipmunk/CCPhysicsBodyInfo_chipmunk.h"
#include "box2d/CCPhysicsBodyInfo_box2d.h"
#include "chipmunk/CCPhysicsShapeInfo_chipmunk.h"
#include "box2d/CCPhysicsShapeInfo_box2d.h"
#include "chipmunk/CCPhysicsHelper_chipmunk.h"
#include "box2d/CCPhysicsHelper_box2d.h"
#include "CCNode.h"

NS_CC_BEGIN

PhysicsJoint::PhysicsJoint()
: _bodyA(nullptr)
, _bodyB(nullptr)
, _world(nullptr)
, _info(nullptr)
, _enable(false)
, _collisionEnable(true)
, _destoryMark(false)
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
        
        if (_world != nullptr)
        {
            if (enable)
            {
                _world->addJointOrDelay(this);
            }else
            {
                _world->removeJointOrDelay(this);
            }
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

PhysicsJointLimit::PhysicsJointLimit()
{
    
}

PhysicsJointLimit::~PhysicsJointLimit()
{
    
}

PhysicsJointDistance::PhysicsJointDistance()
{
    
}

PhysicsJointDistance::~PhysicsJointDistance()
{
    
}

#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)
PhysicsBodyInfo* PhysicsJoint::getBodyInfo(PhysicsBody* body) const
{
    return body->_info;
}

Node* PhysicsJoint::getBodyNode(PhysicsBody* body) const
{
    return body->_node;
}


void PhysicsJoint::setCollisionEnable(bool enable)
{
    if (_collisionEnable != enable)
    {
        _collisionEnable = enable;
    }
}

void PhysicsJoint::removeFormWorld()
{
    if (_world)
    {
        _world->removeJoint(this, false);
    }
}

void PhysicsJoint::destroy(PhysicsJoint* joint)
{
    if (joint!= nullptr)
    {
        // remove the joint and delete it.
        if (joint->_world != nullptr)
        {
            joint->_world->removeJoint(joint, true);
        }
        else
        {
            if (joint->_bodyA != nullptr)
            {
                joint->_bodyA->removeJoint(joint);
            }
            
            if (joint->_bodyB != nullptr)
            {
                joint->_bodyB->removeJoint(joint);
            }
            
            delete joint;
        }
    }
}

PhysicsJointFixed* PhysicsJointFixed::construct(PhysicsBody* a, PhysicsBody* b, const Point& anchr)
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
        
        getBodyNode(a)->setPosition(anchr);
        getBodyNode(b)->setPosition(anchr);
        
        // add a pivot joint to fixed two body together
        cpConstraint* joint = cpPivotJointNew(getBodyInfo(a)->getBody(), getBodyInfo(b)->getBody(),
                                        PhysicsHelper::point2cpv(anchr));
        CC_BREAK_IF(joint == nullptr);
        _info->add(joint);
        
        // add a gear joint to make two body have the same rotation.
        joint = cpGearJointNew(getBodyInfo(a)->getBody(), getBodyInfo(b)->getBody(), 0, 1);
        CC_BREAK_IF(joint == nullptr);
        _info->add(joint);
        
        setCollisionEnable(false);
        
        return true;
    } while (false);
    
    return false;
}

PhysicsJointPin* PhysicsJointPin::construct(PhysicsBody* a, PhysicsBody* b, const Point& anchr)
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
        cpConstraint* joint = cpPivotJointNew(getBodyInfo(a)->getBody(), getBodyInfo(b)->getBody(),
                                       PhysicsHelper::point2cpv(anchr));
        
        CC_BREAK_IF(joint == nullptr);
        
        _info->add(joint);
        
        return true;
    } while (false);
    
    return false;
}

void PhysicsJointPin::setMaxForce(float force)
{
    _info->getJoints().front()->maxForce = PhysicsHelper::float2cpfloat(force);
}

float PhysicsJointPin::getMaxForce() const
{
    return PhysicsHelper::cpfloat2float(_info->getJoints().front()->maxForce);
}

PhysicsJointLimit* PhysicsJointLimit::construct(PhysicsBody* a, PhysicsBody* b, const Point& anchr1, const Point& anchr2)
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
        
        cpConstraint* joint = cpSlideJointNew(getBodyInfo(a)->getBody(), getBodyInfo(b)->getBody(),
                                       PhysicsHelper::point2cpv(anchr1),
                                       PhysicsHelper::point2cpv(anchr2),
                                       0,
                                       PhysicsHelper::float2cpfloat(_bodyA->local2World(anchr1).getDistance(_bodyB->local2World(anchr2))));
        
        CC_BREAK_IF(joint == nullptr);
        
        _info->add(joint);
        
        return true;
    } while (false);
    
    return false;
}

float PhysicsJointLimit::getMin() const
{
    return PhysicsHelper::cpfloat2float(cpSlideJointGetMin(_info->getJoints().front()));
}

void PhysicsJointLimit::setMin(float min)
{
    cpSlideJointSetMin(_info->getJoints().front(), PhysicsHelper::float2cpfloat(min));
}

float PhysicsJointLimit::getMax() const
{
    return PhysicsHelper::cpfloat2float(cpSlideJointGetMax(_info->getJoints().front()));
}

void PhysicsJointLimit::setMax(float max)
{
    cpSlideJointSetMax(_info->getJoints().front(), PhysicsHelper::float2cpfloat(max));
}

PhysicsJointDistance* PhysicsJointDistance::construct(PhysicsBody* a, PhysicsBody* b, const Point& anchr1, const Point& anchr2)
{
    PhysicsJointDistance* joint = new PhysicsJointDistance();
    
    if (joint && joint->init(a, b, anchr1, anchr2))
    {
        return joint;
    }
    
    CC_SAFE_DELETE(joint);
    return nullptr;
}

bool PhysicsJointDistance::init(PhysicsBody* a, PhysicsBody* b, const Point& anchr1, const Point& anchr2)
{
    do
    {
        CC_BREAK_IF(!PhysicsJoint::init(a, b));
        
        cpConstraint* joint = cpPinJointNew(getBodyInfo(a)->getBody(),
                                            getBodyInfo(b)->getBody(),
                                            PhysicsHelper::point2cpv(anchr1),
                                            PhysicsHelper::point2cpv(anchr2));
        
        CC_BREAK_IF(joint == nullptr);
        
        _info->add(joint);
        
        return true;
    } while (false);
    
    return false;
}

#elif (CC_PHYSICS_ENGINE == CC_PHYSICS_BOX2D)

#endif

NS_CC_END
#endif // CC_USE_PHYSICS
