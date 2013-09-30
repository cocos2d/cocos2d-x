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
#include "Box2D/CCPhysicsJointInfo.h"
#include "chipmunk/CCPhysicsBodyInfo.h"
#include "Box2D/CCPhysicsBodyInfo.h"
#include "chipmunk/CCPhysicsHelper.h"
#include "Box2D/CCPhysicsHelper.h"

NS_CC_BEGIN

PhysicsJoint::PhysicsJoint()
: _bodyA(nullptr)
, _bodyB(nullptr)
, _info(nullptr)
{
    
}

PhysicsJoint::~PhysicsJoint()
{
    CC_SAFE_DELETE(_info);
    
    CC_SAFE_RELEASE(_bodyA);
    CC_SAFE_RELEASE(_bodyB);
}

bool PhysicsJoint::init(cocos2d::PhysicsBody *a, cocos2d::PhysicsBody *b)
{
    do
    {
        CC_BREAK_IF(a == nullptr || b == nullptr);
        
        CC_BREAK_IF(!(_info = new PhysicsJointInfo()));
        
        _bodyA = a;
        _bodyA->retain();
        _bodyA->_joints.push_back(this);
        _bodyB = b;
        _bodyB->retain();
        _bodyB->_joints.push_back(this);
        
        return true;
    } while (false);
    
    return false;
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



PhysicsJointFixed* PhysicsJointFixed::create(PhysicsBody* a, PhysicsBody* b, const Point& anchr)
{
    PhysicsJointFixed* joint = new PhysicsJointFixed();
    
    if (joint && joint->init(a, b, anchr))
    {
        joint->autorelease();
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
        
        _info->joint = cpPivotJointNew(bodyInfo(a)->body, bodyInfo(b)->body,
                                        PhysicsHelper::point2cpv(anchr));
        
        return true;
    } while (false);
    
    return false;
}

PhysicsJointPin* PhysicsJointPin::create(PhysicsBody* a, PhysicsBody* b, const Point& anchr1, const Point& anchr2)
{
    PhysicsJointPin* joint = new PhysicsJointPin();
    
    if (joint && joint->init(a, b, anchr1, anchr2))
    {
        joint->autorelease();
        return joint;
    }
    
    CC_SAFE_DELETE(joint);
    return nullptr;
}

bool PhysicsJointPin::init(PhysicsBody *a, PhysicsBody *b, const Point& anchr1, const Point& anchr2)
{
    do
    {
        CC_BREAK_IF(!PhysicsJoint::init(a, b));
        
        _info->joint = cpPinJointNew(bodyInfo(a)->body, bodyInfo(b)->body, PhysicsHelper::point2cpv(anchr1), PhysicsHelper::point2cpv(anchr2));
        
        return true;
    } while (false);
    
    return false;
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
        
        _info->joint = cpGrooveJointNew(bodyInfo(a)->body, bodyInfo(b)->body,
                                       PhysicsHelper::point2cpv(grooveA),
                                       PhysicsHelper::point2cpv(grooveB),
                                       PhysicsHelper::point2cpv(anchr));
        
        return true;
    } while (false);
    
    return false;
}


PhysicsJointLimit* PhysicsJointLimit::create(PhysicsBody* a, PhysicsBody* b, const Point& anchr1, const Point& anchr2, float min, float max)
{
    PhysicsJointLimit* joint = new PhysicsJointLimit();
    
    if (joint && joint->init(a, b, anchr1, anchr2, min, max))
    {
        return joint;
    }
    
    CC_SAFE_DELETE(joint);
    return nullptr;
}

bool PhysicsJointLimit::init(PhysicsBody* a, PhysicsBody* b, const Point& anchr1, const Point& anchr2, float min, float max)
{
    do
    {
        CC_BREAK_IF(!PhysicsJoint::init(a, b));
        
        _info->joint = cpSlideJointNew(bodyInfo(a)->body, bodyInfo(b)->body,
                                       PhysicsHelper::point2cpv(anchr1),
                                       PhysicsHelper::point2cpv(anchr2),
                                       PhysicsHelper::float2cpfloat(min),
                                       PhysicsHelper::float2cpfloat(max));
        
        return true;
    } while (false);
    
    return false;
}

#elif (CC_PHYSICS_ENGINE == CC_PHYSICS_BOX2D)

#endif

NS_CC_END
#endif // CC_USE_PHYSICS
