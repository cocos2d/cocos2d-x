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

class PhysicsJoint
{
protected:
    PhysicsJoint();
    virtual ~PhysicsJoint();
    
private:
    PhysicsBody* _bodyA;
    PhysicsBody* _bodyB;
};

class PhysicsJointFixed : public PhysicsJoint
{
public:
    PhysicsJointFixed* create();
    
protected:
    bool init();
    
protected:
    PhysicsJointFixed();
    ~PhysicsJointFixed();
};

class PhysicsJointSliding : public PhysicsJoint
{
public:
    PhysicsJointSliding* create();
    
protected:
    bool init();
    
protected:
    PhysicsJointSliding();
    ~PhysicsJointSliding();
};

class PhysicsJointSpring : public PhysicsJoint
{
public:
    PhysicsJointSpring* create();
    
protected:
    bool init();
    
protected:
    PhysicsJointSpring();
    ~PhysicsJointSpring();
};

class PhysicsJointLimit : public PhysicsJoint
{
public:
    PhysicsJointLimit* create();
    
protected:
    bool init();
    
protected:
    PhysicsJointLimit();
    ~PhysicsJointLimit();
};

class PhysicsJointPin : public PhysicsJoint
{
public:
    PhysicsJointPin* create();
    
protected:
    bool init();
    
protected:
    PhysicsJointPin();
    ~PhysicsJointPin();
};

NS_CC_END

#endif // __CCPHYSICS_JOINT_H__

#endif // CC_USE_PHYSICS
