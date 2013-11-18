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

#ifndef __CCPHYSICS_WORLD_H__
#define __CCPHYSICS_WORLD_H__

#include "CCPhysicsSetting.h"
#ifdef CC_USE_PHYSICS

#include <list>
#include <vector>

#include "CCObject.h"
#include "CCGeometry.h"

NS_CC_BEGIN

class PhysicsBody;
class PhysicsJoint;
class PhysicsWorldInfo;
class PhysicsShape;
class PhysicsContact;
class Array;

class Sprite;
class Scene;
class DrawNode;
class PhysicsDebugDraw;

class PhysicsWorld;

typedef struct PhysicsRayCastInfo
{
    PhysicsShape* shape;
    Point start;
    Point end;
    Point contact;
    Vect normal;
    float fraction;
    void* data;
}PhysicsRayCastInfo;

/**
 * @brief Called for each fixture found in the query. You control how the ray cast
 * proceeds by returning a float:
 * return true: continue
 * return false: terminate the ray cast
 * @param fixture the fixture hit by the ray
 * @param point the point of initial intersection
 * @param normal the normal vector at the point of intersection
 * @return true to continue, false to terminate
 */
typedef std::function<bool(PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data)> PhysicsRayCastCallbackFunc;
typedef std::function<bool(PhysicsWorld&, PhysicsShape&, void*)> PhysicsRectQueryCallbackFunc;
typedef PhysicsRectQueryCallbackFunc PhysicsPointQueryCallbackFunc;

/**
 * @brief An PhysicsWorld object simulates collisions and other physical properties. You do not create PhysicsWorld objects directly; instead, you can get it from an Scene object.
 */
class PhysicsWorld
{
public:
    static const long DEBUGDRAW_NONE = 0x00;
    static const long DEBUGDRAW_SHAPE = 0x01;
    static const long DEBUGDRAW_JOINT = 0x02;
    static const long DEBUGDRAW_CONTACT = 0x04;
    static const long DEBUGDRAW_ALL = DEBUGDRAW_SHAPE | DEBUGDRAW_JOINT | DEBUGDRAW_CONTACT;
    
public:
    /** Adds a joint to the physics world.*/
    virtual void addJoint(PhysicsJoint* joint);
    /** Removes a joint from the physics world.*/
    virtual void removeJoint(PhysicsJoint* joint, bool destroy);
    /** Remove all joints from the physics world.*/
    virtual void removeAllJoints(bool destroy);
    
    virtual void removeBody(PhysicsBody* body);
    virtual void removeBody(int tag);
    virtual void removeAllBodies();
    
    void rayCast(PhysicsRayCastCallbackFunc func, const Point& point1, const Point& point2, void* data);
    void queryRect(PhysicsRectQueryCallbackFunc func, const Rect& rect, void* data);
    void queryPoint(PhysicsPointQueryCallbackFunc func, const Point& point, void* data);
    Array* getShapes(const Point& point) const;
    PhysicsShape* getShape(const Point& point) const;
    Array* getAllBodies() const;
    PhysicsBody* getBody(int tag) const;
    
    /** Register a listener to receive contact callbacks*/
    //inline void registerContactListener(EventListenerPhysicsContact* delegate) { _listener = delegate; }
    /** Unregister a listener. */
    //inline void unregisterContactListener() { _listener = nullptr; }
    
    inline Scene& getScene() const { return *_scene; }
    /** get the gravity value */
    inline Vect getGravity() const { return _gravity; }
    /** set the gravity value */
    void setGravity(const Vect& gravity);
    
    /** set the debug draw */
    void setDebugDrawMask(int mask);
    inline int getDebugDrawMask() { return _debugDrawMask; }
    
protected:
    static PhysicsWorld* construct(Scene& scene);
    bool init(Scene& scene);
    
    virtual void addBody(PhysicsBody* body);
    virtual void addShape(PhysicsShape* shape);
    virtual void removeShape(PhysicsShape* shape);
    virtual void update(float delta);
    
    virtual void debugDraw();
    
    virtual int collisionBeginCallback(PhysicsContact& contact);
    virtual int collisionPreSolveCallback(PhysicsContact& contact);
    virtual void collisionPostSolveCallback(PhysicsContact& contact);
    virtual void collisionSeparateCallback(PhysicsContact& contact);
    
    virtual void doAddBody(PhysicsBody* body);
    virtual void doRemoveBody(PhysicsBody* body);
    virtual void doAddJoint(PhysicsJoint* joint);
    virtual void doRemoveJoint(PhysicsJoint* joint);
    virtual void addBodyOrDelay(PhysicsBody* body);
    virtual void removeBodyOrDelay(PhysicsBody* body);
    virtual void addJointOrDelay(PhysicsJoint* joint);
    virtual void removeJointOrDelay(PhysicsJoint* joint);
    virtual void updateBodies();
    virtual void updateJoints();
    
protected:
    Vect _gravity;
    float _speed;
    PhysicsWorldInfo* _info;
    
    Array* _bodies;
    std::list<PhysicsJoint*> _joints;
    Scene* _scene;
    
    bool _delayDirty;
    PhysicsDebugDraw* _debugDraw;
    int _debugDrawMask;
    
    
    Array* _delayAddBodies;
    Array* _delayRemoveBodies;
    std::vector<PhysicsJoint*> _delayAddJoints;
    std::vector<PhysicsJoint*> _delayRemoveJoints;
    
protected:
    PhysicsWorld();
    virtual ~PhysicsWorld();
    
    friend class Sprite;
    friend class Scene;
    friend class PhysicsBody;
    friend class PhysicsShape;
    friend class PhysicsJoint;
    friend class PhysicsWorldCallback;
    friend class PhysicsDebugDraw;
};


class PhysicsDebugDraw
{
protected:
    virtual bool begin();
    virtual void end();
    virtual void drawShape(PhysicsShape& shape);
    virtual void drawJoint(PhysicsJoint& joint);
    virtual void drawContact();
    
protected:
    PhysicsDebugDraw(PhysicsWorld& world);
    virtual ~PhysicsDebugDraw();
    
protected:
    DrawNode* _drawNode;
    PhysicsWorld& _world;
    
    friend class PhysicsWorld;
};

NS_CC_END

#endif // CC_USE_PHYSICS
#endif // __CCPHYSICS_WORLD_H__
