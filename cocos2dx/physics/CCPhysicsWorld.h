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


#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)
typedef struct cpArbiter cpArbiter;
typedef struct cpSpace cpSpace;
#endif

NS_CC_BEGIN

class PhysicsBody;
class PhysicsJoint;
class PhysicsWorldInfo;
class PhysicsShape;
class PhysicsContact;
class PhysicsContactPreSolve;
class PhysicsContactPostSolve;
class PhysicsContactListener;
class Array;

class Sprite;
class Scene;
class DrawNode;

/**
 * @brief An PhysicsWorld object simulates collisions and other physical properties. You do not create PhysicsWorld objects directly; instead, you can get it from an Scene object.
 */
class PhysicsWorld
{
public:
    /** Adds a joint to the physics world.*/
    void addJoint(PhysicsJoint* joint);
    /** Removes a joint from the physics world.*/
    void removeJoint(PhysicsJoint* joint);
    /** Remove all joints from the physics world.*/
    void removeAllJoints();
    
    Array* getBodysAlongRay(Point start, Point end) const;
    Array* getBodysAtPoint(Point point) const;
    Array* getBodysInRect(Rect rect) const;
    Array* getAllBody() const;
    
    /** Register a listener to receive contact callbacks*/
    inline void registerContactListener(PhysicsContactListener* delegate) { _listener = delegate; }
    /** Unregister a listener. */
    inline void unregisterContactListener() { _listener = nullptr; }
    
    /** get the gravity value */
    inline Point getGravity() { return _gravity; }
    /** set the gravity value */
    void setGravity(Point gravity);
    
    /** test the debug draw is enabled */
    inline bool isDebugDraw() { return _debugDraw; }
    /** set the debug draw */
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
    
#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)
    static int collisionBeginCallbackFunc(cpArbiter *arb, struct cpSpace *space, void *data);
    static int collisionPreSolveCallbackFunc(cpArbiter *arb, cpSpace *space, void *data);
    static void collisionPostSolveCallbackFunc(cpArbiter *arb, cpSpace *space, void *data);
    static void collisionSeparateCallbackFunc(cpArbiter *arb, cpSpace *space, void *data);
#endif
    
protected:
    Point _gravity;
    float _speed;
    PhysicsWorldInfo* _info;
    PhysicsContactListener* _listener;
    
    
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
};

NS_CC_END

#endif // __CCPHYSICS_WORLD_H__

#endif // CC_USE_PHYSICS
