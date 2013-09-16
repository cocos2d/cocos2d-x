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

#ifndef __CCPHYSICS_WORLD_H__
#define __CCPHYSICS_WORLD_H__

#include "cocoa/CCObject.h"
#include "cocoa/CCGeometry.h"

NS_CC_BEGIN

class PhysicsBody;
class PhysicsJoint;
class PhysicsWorldInfo;
class PhysicsShape;
class PhysicsContact;
class PhysicsContactPreSolve;
class PhysicsContactPostSolve;
class PhysicsContactDelegate;
class Array;

class Sprite;
class Scene;
class DrawNode;

namespace PhysicsInnerCallbackFunctions
{
#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)
    int collisionBeginCallbackFunc(cpArbiter *arb, struct cpSpace *space, void *data);
    int collisionPreSolveCallbackFunc(cpArbiter *arb, cpSpace *space, void *data);
    void collisionPostSolveCallbackFunc(cpArbiter *arb, cpSpace *space, void *data);
    void collisionSeparateCallbackFunc(cpArbiter *arb, cpSpace *space, void *data);
#endif
}

class PhysicsWorld
{
public:
    void addJoint(PhysicsJoint* joint);
    void removeJoint(PhysicsJoint* joint);
    void removeAllJoints();
    
    Array* getBodysAlongRay(Point start, Point end) const;
    Array* getBodysAtPoint(Point point) const;
    Array* getBodysInRect(Rect rect) const;
    Array* getAllBody() const;
    
    inline void registerContactDelegate(PhysicsContactDelegate* delegate) { _delegate = delegate; }
    inline void unregisterContactDelegate() { _delegate = nullptr; }
    
    inline Point getGravity() { return _gravity; }
    inline void setGravity(Point gravity) { _gravity = gravity; }
    
    inline bool getDebugDraw() { return _debugDraw; }
    inline void setDebugDraw(bool debugDraw) { _debugDraw = debugDraw; }
    
protected:
    static PhysicsWorld* create();
    bool init();
    
    void setScene(Scene* scene);
    
    virtual void addChild(PhysicsBody* body);
    virtual void addShape(PhysicsShape* shape);
    virtual void update(float delta);
    
    virtual void debugDraw();
    virtual void drawWithShape(DrawNode* node, PhysicsShape* shape);
    
    
    virtual int collisionBeginCallback(const PhysicsContact& contact);
    virtual int collisionPreSolveCallback(const PhysicsContact& contact, const PhysicsContactPreSolve& solve);
    virtual void collisionPostSolveCallback(const PhysicsContact& contact, const PhysicsContactPostSolve& solve);
    virtual void collisionSeparateCallback(const PhysicsContact& contact);
    
protected:
    Point _gravity;
    float _speed;
    PhysicsWorldInfo* _info;
    PhysicsContactDelegate* _delegate;
    
    
    Array* _bodys;
    Scene* _scene;
    
    bool _debugDraw;
    DrawNode* _drawNode;
    
protected:
    PhysicsWorld();
    virtual ~PhysicsWorld();
    
    friend class Sprite;
    friend class Scene;
    friend class PhysicsBody;
    
#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)
    friend int PhysicsInnerCallbackFunctions::collisionBeginCallbackFunc(cpArbiter *arb, struct cpSpace *space, void *data);
    friend int PhysicsInnerCallbackFunctions::collisionPreSolveCallbackFunc(cpArbiter *arb, cpSpace *space, void *data);
    friend void PhysicsInnerCallbackFunctions::collisionPostSolveCallbackFunc(cpArbiter *arb, cpSpace *space, void *data);
    friend void PhysicsInnerCallbackFunctions::collisionSeparateCallbackFunc(cpArbiter *arb, cpSpace *space, void *data);
#endif
};

NS_CC_END

#endif // __CCPHYSICS_WORLD_H__

#endif // CC_USE_PHYSICS
