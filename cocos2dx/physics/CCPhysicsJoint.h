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

#include "CCPhysicsSetting.h"
#ifdef CC_USE_PHYSICS

#ifndef __CCPHYSICS_JOINT_H__
#define __CCPHYSICS_JOINT_H__

#include "cocoa/CCObject.h"
#include "cocoa/CCGeometry.h"

NS_CC_BEGIN

class PhysicsBody;
class PhysicsJointInfo;
class PhysicsBodyInfo;

/*
 * @brief An PhysicsJoint object connects two physics bodies together.
 */
class PhysicsJoint : public Object
{
protected:
    PhysicsJoint();
    virtual ~PhysicsJoint() = 0;

public:
    PhysicsBody* getBodyA() { return _bodyA; }
    PhysicsBody* getBodyB() { return _bodyB; }
    
protected:
    bool init(PhysicsBody* a, PhysicsBody* b);
    
    /**
     * PhysicsShape is PhysicsBody's friend class, but all the subclasses isn't. so this method is use for subclasses to catch the bodyInfo from PhysicsBody.
     */
    PhysicsBodyInfo* bodyInfo(PhysicsBody* body) const;
    
protected:
    PhysicsBody* _bodyA;
    PhysicsBody* _bodyB;
    PhysicsJointInfo* _info;
    
    friend class PhysicsBody;
};

/*
 * @brief A fixed joint fuses the two bodies together at a reference point. Fixed joints are useful for creating complex shapes that can be broken apart later.
 */
class PhysicsJointFixed : public PhysicsJoint
{
public:
    PhysicsJointFixed* create(PhysicsBody* a, PhysicsBody* b, const Point& anchr);
    
protected:
    bool init(PhysicsBody* a, PhysicsBody* b, const Point& anchr);
    
protected:
    PhysicsJointFixed();
    virtual ~PhysicsJointFixed();
};

/*
 * @brief A sliding joint allows the two bodies to slide along a chosen axis.
 */
class PhysicsJointSliding : public PhysicsJoint
{
public:
    PhysicsJointSliding* create(PhysicsBody* a, PhysicsBody* b, const Point& grooveA, const Point& grooveB, const Point& anchr);
    
protected:
    bool init(PhysicsBody* a, PhysicsBody* b, const Point& grooveA, const Point& grooveB, const Point& anchr);
    
protected:
    PhysicsJointSliding();
    virtual ~PhysicsJointSliding();
};

/*
 * @brief A spring joint connects the two bodies with a spring whose length is the initial distance between the two bodies.
 */
class PhysicsJointSpring : public PhysicsJoint
{
public:
    PhysicsJointSpring* create();
    
protected:
    bool init();
    
protected:
    PhysicsJointSpring();
    virtual ~PhysicsJointSpring();
};

/*
 * @brief A limit joint imposes a maximum distance between the two bodies, as if they were connected by a rope.
 */
class PhysicsJointLimit : public PhysicsJoint
{
public:
    PhysicsJointLimit* create(PhysicsBody* a, PhysicsBody* b, const Point& anchr1, const Point& anchr2, float min, float max);
    
protected:
    bool init(PhysicsBody* a, PhysicsBody* b, const Point& anchr1, const Point& anchr2, float min, float max);
    
protected:
    PhysicsJointLimit();
    virtual ~PhysicsJointLimit();
};

/*
 * @brief A pin joint allows the two bodies to independently rotate around the anchor point as if pinned together.
 */
class PhysicsJointPin : public PhysicsJoint
{
public:
    static PhysicsJointPin* create(PhysicsBody* a, PhysicsBody* b, const Point& anchr1, const Point& anchr2);
    
protected:
    bool init(PhysicsBody* a, PhysicsBody* b, const Point& anchr1, const Point& anchr2);
    
protected:
    PhysicsJointPin();
    virtual ~PhysicsJointPin();
};

NS_CC_END

#endif // __CCPHYSICS_JOINT_H__

#endif // CC_USE_PHYSICS
