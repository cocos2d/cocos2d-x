/****************************************************************************
 Copyright (c) 2013 Chukong Technologies Inc.
 
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

#include "ccConfig.h"
#if CC_USE_PHYSICS

#include "CCVector.h"
#include "CCObject.h"
#include "CCGeometry.h"

#include <list>

NS_CC_BEGIN

class PhysicsBody;
class PhysicsJoint;
class PhysicsWorldInfo;
class PhysicsShape;
class PhysicsContact;

typedef Point Vect;

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
typedef std::function<bool(PhysicsWorld&, PhysicsShape&, void*)> PhysicsQueryRectCallbackFunc;
typedef PhysicsQueryRectCallbackFunc PhysicsQueryPointCallbackFunc;

/**
 * @brief An PhysicsWorld object simulates collisions and other physical properties. You do not create PhysicsWorld objects directly; instead, you can get it from an Scene object.
 */
class PhysicsWorld
{
public:
    static const int DEBUGDRAW_NONE;        ///< draw nothing
    static const int DEBUGDRAW_SHAPE;       ///< draw shapes
    static const int DEBUGDRAW_JOINT;       ///< draw joints
    static const int DEBUGDRAW_CONTACT;     ///< draw contact
    static const int DEBUGDRAW_ALL;         ///< draw all
    
public:
    /** Adds a joint to the physics world.*/
    virtual void addJoint(PhysicsJoint* joint);
    /** Remove a joint from physics world.*/
    virtual void removeJoint(PhysicsJoint* joint, bool destroy);
    /** Remove all joints from physics world.*/
    virtual void removeAllJoints(bool destroy);
    
    /** Remove a body from physics world. */
    virtual void removeBody(PhysicsBody* body);
    /** Remove body by tag. */
    virtual void removeBody(int tag);
    /** Remove all bodies from physics world. */
    virtual void removeAllBodies();
    
    /** Searches for physics shapes that intersects the ray. */
    void rayCast(PhysicsRayCastCallbackFunc func, const Point& start, const Point& end, void* data);
    /** Searches for physics shapes that contains in the rect. */
    void queryRect(PhysicsQueryRectCallbackFunc func, const Rect& rect, void* data);
    /** Searches for physics shapes that contains the point. */
    void queryPoint(PhysicsQueryPointCallbackFunc func, const Point& point, void* data);
    /** Get phsyics shapes that contains the point. */
    Vector<PhysicsShape*> getShapes(const Point& point) const;
    /** return physics shape that contains the point. */
    PhysicsShape* getShape(const Point& point) const;
    /** Get all the bodys that in the physics world. */
    const Vector<PhysicsBody*>& getAllBodies() const;
    /** Get body by tag */
    PhysicsBody* getBody(int tag) const;
    
    /** Get scene contain this physics world */
    inline Scene& getScene() const { return *_scene; }
    /** get the gravity value */
    inline Vect getGravity() const { return _gravity; }
    /** set the gravity value */
    void setGravity(const Vect& gravity);
    /** Set the speed of physics world, speed is the rate at which the simulation executes. default value is 1.0 */
    inline void setSpeed(float speed) { if(speed >= 0.0f) { _speed = speed; } }
    /** get the speed of physics world */
    inline float getSpeed() { return _speed; }
    /** 
     * set the update rate of physics world, update rate is the value of EngineUpdateTimes/PhysicsWorldUpdateTimes.
     * set it higher can improve performance, set it lower can improve accuracy of physics world simulation.
     * default value is 1.0
     */
    inline void setUpdateRate(int rate) { if(rate > 0) { _updateRate = rate; } }
    /** get the update rate */
    inline int getUpdateRate() { return _updateRate; }
    
    /** set the debug draw mask */
    void setDebugDrawMask(int mask);
    /** get the bebug draw mask */
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
    int _updateRate;
    int _updateRateCount;
    float _updateTime;
    PhysicsWorldInfo* _info;
    
    Vector<PhysicsBody*> _bodies;
    std::list<PhysicsJoint*> _joints;
    Scene* _scene;
    
    bool _delayDirty;
    PhysicsDebugDraw* _debugDraw;
    int _debugDrawMask;
    
    
    Vector<PhysicsBody*> _delayAddBodies;
    Vector<PhysicsBody*> _delayRemoveBodies;
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
extern const float PHYSICS_INFINITY;

NS_CC_END

#endif // CC_USE_PHYSICS
#endif // __CCPHYSICS_WORLD_H__
