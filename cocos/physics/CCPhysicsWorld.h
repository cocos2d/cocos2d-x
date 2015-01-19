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

#include "base/ccConfig.h"
#if CC_USE_PHYSICS

#include "base/CCVector.h"
#include "base/CCRef.h"
#include "math/CCGeometry.h"
#include "physics/CCPhysicsBody.h"
#include <list>

struct cpSpace;

NS_CC_BEGIN

class PhysicsBody;
class PhysicsJoint;
class PhysicsShape;
class PhysicsContact;

typedef Vec2 Vect;

class Director;
class Node;
class Sprite;
class Scene;
class DrawNode;
class PhysicsDebugDraw;

class PhysicsWorld;

typedef struct PhysicsRayCastInfo
{
    PhysicsShape* shape;
    Vec2 start;
    Vec2 end;              //< in lua, it's name is "ended"
    Vec2 contact;
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
class CC_DLL PhysicsWorld
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
    virtual void removeJoint(PhysicsJoint* joint, bool destroy = true);
    /** Remove all joints from physics world.*/
    virtual void removeAllJoints(bool destroy = true);
    
    /** Remove a body from physics world. */
    virtual void removeBody(PhysicsBody* body);
    /** Remove body by tag. */
    virtual void removeBody(int tag);
    /** Remove all bodies from physics world. */
    virtual void removeAllBodies();
    
    /** Searches for physics shapes that intersects the ray. */
    void rayCast(PhysicsRayCastCallbackFunc func, const Vec2& start, const Vec2& end, void* data);
    /** Searches for physics shapes that contains in the rect. */
    void queryRect(PhysicsQueryRectCallbackFunc func, const Rect& rect, void* data);
    /** Searches for physics shapes that contains the point. */
    void queryPoint(PhysicsQueryPointCallbackFunc func, const Vec2& point, void* data);
    /** Get phsyics shapes that contains the point. */
    Vector<PhysicsShape*> getShapes(const Vec2& point) const;
    /** return physics shape that contains the point. */
    PhysicsShape* getShape(const Vec2& point) const;
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
    /**
     * Set the speed of physics world, speed is the rate at which the simulation executes. default value is 1.0
     * Note: if you setAutoStep(false), this won't work.
     */
    inline void setSpeed(float speed) { if(speed >= 0.0f) { _speed = speed; } }
    /** get the speed of physics world */
    inline float getSpeed() { return _speed; }
    /**
     * set the update rate of physics world, update rate is the value of EngineUpdateTimes/PhysicsWorldUpdateTimes.
     * set it higher can improve performance, set it lower can improve accuracy of physics world simulation.
     * default value is 1.0
     * Note: if you setAutoStep(false), this won't work.
     */
    inline void setUpdateRate(int rate) { if(rate > 0) { _updateRate = rate; } }
    /** get the update rate */
    inline int getUpdateRate() { return _updateRate; }
    /**
     * set the number of substeps in an update of the physics world.
     * One physics update will be divided into several substeps to increase its accuracy.
     * default value is 1
     */
    void setSubsteps(int steps);
    /** get the number of substeps */
    inline int getSubsteps() const { return _substeps; }

    /** set the debug draw mask */
    void setDebugDrawMask(int mask);
    /** get the bebug draw mask */
    inline int getDebugDrawMask() { return _debugDrawMask; }
    
    /**
     * To control the step of physics, if you want control it by yourself( fixed-timestep for example ), you can set this to false and call step by yourself.
     * Defaut value is true.
     * Note: if you set auto step to false, setSpeed setSubsteps and setUpdateRate won't work, you need to control the time step by yourself.
     */
    void setAutoStep(bool autoStep){ _autoStep = autoStep; }
    /** Get the auto step */
    bool isAutoStep() { return _autoStep; }
    /**
     * The step for physics world, The times passing for simulate the physics.
     * Note: you need to setAutoStep(false) first before it can work.
     */
    void step(float delta);
    
protected:
    static PhysicsWorld* construct(Scene& scene);
    bool init(Scene& scene);
    
    virtual void addBody(PhysicsBody* body);
    virtual void addShape(PhysicsShape* shape);
    virtual void removeShape(PhysicsShape* shape);
    virtual void update(float delta, bool userCall = false);
    
    virtual void debugDraw();
    
    virtual int collisionBeginCallback(PhysicsContact& contact);
    virtual int collisionPreSolveCallback(PhysicsContact& contact);
    virtual void collisionPostSolveCallback(PhysicsContact& contact);
    virtual void collisionSeparateCallback(PhysicsContact& contact);
    
    virtual void doAddBody(PhysicsBody* body);
    virtual void doRemoveBody(PhysicsBody* body);
    virtual void doRemoveJoint(PhysicsJoint* joint);
    virtual void addBodyOrDelay(PhysicsBody* body);
    virtual void removeBodyOrDelay(PhysicsBody* body);
    virtual void updateBodies();
    virtual void updateJoints();
    
protected:
    Vect _gravity;
    float _speed;
    int _updateRate;
    int _updateRateCount;
    float _updateTime;
    int _substeps;
    cpSpace* _cpSpace;
    
    Vector<PhysicsBody*> _bodies;
    std::list<PhysicsJoint*> _joints;
    Scene* _scene;
    
    bool _autoStep;
    PhysicsDebugDraw* _debugDraw;
    int _debugDrawMask;
    
    
    Vector<PhysicsBody*> _delayAddBodies;
    Vector<PhysicsBody*> _delayRemoveBodies;
    std::vector<PhysicsJoint*> _delayAddJoints;
    std::vector<PhysicsJoint*> _delayRemoveJoints;
    
protected:
    PhysicsWorld();
    virtual ~PhysicsWorld();
    
    friend class Node;
    friend class Sprite;
    friend class Scene;
    friend class Director;
    friend class PhysicsBody;
    friend class PhysicsShape;
    friend class PhysicsJoint;
    friend class PhysicsWorldCallback;
    friend class PhysicsDebugDraw;
};


class CC_DLL PhysicsDebugDraw
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
extern const float CC_DLL PHYSICS_INFINITY;

NS_CC_END

#endif // CC_USE_PHYSICS
#endif // __CCPHYSICS_WORLD_H__
