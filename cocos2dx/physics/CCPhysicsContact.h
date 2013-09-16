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

#ifndef __CCPHYSICS_CONTACT_H__
#define __CCPHYSICS_CONTACT_H__

#include "cocoa/CCObject.h"
#include "cocoa/CCGeometry.h"

NS_CC_BEGIN

class PhysicsShape;
class PhysicsWorld;

namespace PhysicsInnerCallbackFunctions
{
#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)
    int collisionBeginCallbackFunc(cpArbiter *arb, struct cpSpace *space, void *data);
    int collisionPreSolveCallbackFunc(cpArbiter *arb, cpSpace *space, void *data);
    void collisionPostSolveCallbackFunc(cpArbiter *arb, cpSpace *space, void *data);
    void collisionSeparateCallbackFunc(cpArbiter *arb, cpSpace *space, void *data);
#endif
}

class PhysicsContactInfo;

class PhysicsContact
{
public:
    inline PhysicsShape* getShapeA() { return _shapeA; }
    inline PhysicsShape* getShapeB() { return _shapeB; }
    inline void* getData() { return _data; }
    
private:
    static PhysicsContact* create(PhysicsShape* a, PhysicsShape* b);
    bool init(PhysicsShape* a, PhysicsShape* b);
    
private:
    PhysicsContact();
    ~PhysicsContact();
    
private:
    PhysicsShape* _shapeA;
    PhysicsShape* _shapeB;
    PhysicsContactInfo* _info;
    void* _data;
    
    friend class PhysicsWorld;
    
#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)
    friend int PhysicsInnerCallbackFunctions::collisionBeginCallbackFunc(cpArbiter *arb, struct cpSpace *space, void *data);
    friend int PhysicsInnerCallbackFunctions::collisionPreSolveCallbackFunc(cpArbiter *arb, cpSpace *space, void *data);
    friend void PhysicsInnerCallbackFunctions::collisionPostSolveCallbackFunc(cpArbiter *arb, cpSpace *space, void *data);
    friend void PhysicsInnerCallbackFunctions::collisionSeparateCallbackFunc(cpArbiter *arb, cpSpace *space, void *data);
#endif
};

class PhysicsContactPreSolve
{
private:
    PhysicsContactPreSolve();
    ~PhysicsContactPreSolve();
    
    static PhysicsContactPreSolve* create();
    bool init();
    
    friend class PhysicsWorld;
    
#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)
    friend int PhysicsInnerCallbackFunctions::collisionBeginCallbackFunc(cpArbiter *arb, struct cpSpace *space, void *data);
    friend int PhysicsInnerCallbackFunctions::collisionPreSolveCallbackFunc(cpArbiter *arb, cpSpace *space, void *data);
    friend void PhysicsInnerCallbackFunctions::collisionPostSolveCallbackFunc(cpArbiter *arb, cpSpace *space, void *data);
    friend void PhysicsInnerCallbackFunctions::collisionSeparateCallbackFunc(cpArbiter *arb, cpSpace *space, void *data);
#endif
};

class PhysicsContactPostSolve
{
private:
    PhysicsContactPostSolve();
    ~PhysicsContactPostSolve();
    
    static PhysicsContactPostSolve* create();
    bool init();
    
    friend class PhysicsWorld;
    
#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)
    friend int PhysicsInnerCallbackFunctions::collisionBeginCallbackFunc(cpArbiter *arb, struct cpSpace *space, void *data);
    friend int PhysicsInnerCallbackFunctions::collisionPreSolveCallbackFunc(cpArbiter *arb, cpSpace *space, void *data);
    friend void PhysicsInnerCallbackFunctions::collisionPostSolveCallbackFunc(cpArbiter *arb, cpSpace *space, void *data);
    friend void PhysicsInnerCallbackFunctions::collisionSeparateCallbackFunc(cpArbiter *arb, cpSpace *space, void *data);
#endif
};

class PhysicsContactDelegate
{
public:
    PhysicsContactDelegate();
    virtual ~PhysicsContactDelegate();
    
public:
    virtual bool onContactBegin(const PhysicsContact& contact) = 0;
    virtual bool onContactPreSolve(const PhysicsContact& contact, const PhysicsContactPreSolve& solve) = 0;
    virtual void onContactPostSove(const PhysicsContact& contact, const PhysicsContactPostSolve& solve)= 0;
    virtual void onContactEnd(const PhysicsContact& contact) = 0;
};

NS_CC_END
#endif //__CCPHYSICS_CONTACT_H__

#endif // CC_USE_PHYSICS
