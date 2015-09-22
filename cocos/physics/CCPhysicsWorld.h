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

#include <list>
#include "base/CCVector.h"
#include "math/CCGeometry.h"
#include "physics/CCPhysicsBody.h"

struct cpSpace;

NS_CC_BEGIN

class PhysicsBody;
class PhysicsJoint;
class PhysicsShape;
class PhysicsContact;

class Director;
class Node;
class Sprite;
class Scene;
class DrawNode;
class PhysicsDebugDraw;
class EventDispatcher;

class PhysicsWorld;

typedef struct PhysicsRayCastInfo
{
    PhysicsShape* shape;
    Vec2 start;
    Vec2 end;              //< in lua, it's name is "ended"
    Vec2 contact;
    Vec2 normal;
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
 * @addtogroup physics
 * @{
 * @addtogroup physics_2d
 * @{
 */

/**
 * @class PhysicsWorld CCPhysicsWorld.h
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
    /**
    * Adds a joint to this physics world.
    *
    * This joint will be added to this physics world at next frame.
    * @attention If this joint is already added to another physics world, it will be removed from that world first and then add to this world.
    * @param   joint   A pointer to an existing PhysicsJoint object.
    */
    virtual void addJoint(PhysicsJoint* joint);

    /**
    * Remove a joint from this physics world.
    *
    * If this world is not locked, the joint is removed immediately, otherwise at next frame. 
    * If this joint is connected with a body, it will be removed from the body also.
    * @param   joint   A pointer to an existing PhysicsJoint object.
    * @param   destroy   true this joint will be destroyed after remove from this world, false otherwise.
    */
    virtual void removeJoint(PhysicsJoint* joint, bool destroy = true);

    /**
    * Remove all joints from this physics world.
    * 
    * @attention This function is invoked in the destructor of this physics world, you do not use this api in common.
    * @param   destroy   true all joints will be destroyed after remove from this world, false otherwise.
    */
    virtual void removeAllJoints(bool destroy = true);
    
    /**
    * Remove a body from this physics world. 
    * 
    * If this world is not locked, the body is removed immediately, otherwise at next frame.
    * @attention If this body has joints, those joints will be removed also.
    * @param   body   A pointer to an existing PhysicsBody object.
    */
    virtual void removeBody(PhysicsBody* body);
    
    /**
    * Remove body by tag. 
    * 
    * If this world is not locked, the object is removed immediately, otherwise at next frame.
    * @attention If this body has joints, those joints will be removed also.    
    * @param   tag   An integer number that identifies a PhysicsBody object.
    */
    virtual void removeBody(int tag);

    /**
    * Remove all bodies from physics world. 
    * 
    * If this world is not locked, those body are removed immediately, otherwise at next frame.
    */
    virtual void removeAllBodies();
    
    /**
    * Searches for physics shapes that intersects the ray. 
    *
    * Query this physics world along the line segment from start to end.
    * @param   func   Func is called for each shape found.
    * @param   start   A Vec2 object contains the begin position of the ray.
    * @param   end   A Vec2 object contains the end position of the ray.
    * @param   data   User defined data, it is passed to func. 
    */
    void rayCast(PhysicsRayCastCallbackFunc func, const Vec2& start, const Vec2& end, void* data);
    
    /**
    * Searches for physics shapes that contains in the rect. 
    *
    * Query this physics world to find all shapes overlap rect.
    * @param   func   Func is called for each shape whose bounding box overlaps rect. 
    * @param   rect   A Rect object contains a rectangle's x, y, width and height.
    * @param   data   User defined data, it is passed to func. 
    */
    void queryRect(PhysicsQueryRectCallbackFunc func, const Rect& rect, void* data);
    
    /**
    * Searches for physics shapes that contains the point. 
    *
    * @attention The point must lie inside a shape.
    * @param   func   Func is called for each shape contains the point.
    * @param   point   A Vec2 object contains the position of the point.
    * @param   data   User defined data, it is passed to func. 
    */
    void queryPoint(PhysicsQueryPointCallbackFunc func, const Vec2& point, void* data);
    
    /**
    * Get physics shapes that contains the point. 
    * 
    * All shapes contains the point will be pushed in a Vector<PhysicsShape*> object.
    * @attention The point must lie inside a shape.
    * @param   point   A Vec2 object contains the position of the point.
    * @return A Vector<PhysicsShape*> object contains all found PhysicsShape pointer.
    */
    Vector<PhysicsShape*> getShapes(const Vec2& point) const;
    
    /**
    * Get the nearest physics shape that contains the point. 
    * 
    * Query this physics world at point and return the closest shape.
    * @param   point   A Vec2 object contains the position of the point.
    * @return A PhysicsShape object pointer or nullptr if no shapes were found
    */
    PhysicsShape* getShape(const Vec2& point) const;

    /**
    * Get all the bodies that in this physics world.
    *
    * @return A Vector<PhysicsBody*>& object contains all bodies in this physics world. 
    */
    const Vector<PhysicsBody*>& getAllBodies() const;

    /**
    * Get a body by tag. 
    * 
    * @param   tag   An integer number that identifies a PhysicsBody object. 
    * @return A PhysicsBody object pointer or nullptr if no shapes were found.
    */
    PhysicsBody* getBody(int tag) const;
    
    /**
    * Get a scene contain this physics world.
    * 
    * @attention This value is initialized in constructor
    * @return A Scene object reference.
    */
    inline Scene& getScene() const { return *_scene; }
    
    /**
    * Get the gravity value of this physics world.
    *
    * @return A Vec2 object.
    */
    inline Vec2 getGravity() const { return _gravity; }
    
    /**
    * set the gravity value of this physics world.
    *
    * @param gravity A gravity value of this physics world.
    */
    void setGravity(const Vec2& gravity);
    
    /**
     * Set the speed of this physics world.
     *
     * @attention if you setAutoStep(false), this won't work.
     * @param speed  A float number. Speed is the rate at which the simulation executes. default value is 1.0.
     */
    inline void setSpeed(float speed) { if(speed >= 0.0f) { _speed = speed; } }
    
    /**
    * Get the speed of this physics world.
    *
    * @return A float number.
    */
    inline float getSpeed() { return _speed; }
    
    /**
     * Set the update rate of this physics world
     * 
     * Update rate is the value of EngineUpdateTimes/PhysicsWorldUpdateTimes.
     * Set it higher can improve performance, set it lower can improve accuracy of physics world simulation.
     * @attention if you setAutoStep(false), this won't work.
     * @param rate An integer number, default value is 1.0.
     */
    inline void setUpdateRate(int rate) { if(rate > 0) { _updateRate = rate; } }


    /**
    * Get the update rate of this physics world.
    *
    * @return An integer number.
    */
    inline int getUpdateRate() { return _updateRate; }

    /**
     * set the number of substeps in an update of the physics world.
     * 
     * One physics update will be divided into several substeps to increase its accuracy.
     * @param steps An integer number, default value is 1.
     */
    void setSubsteps(int steps);

    /**
    * Get the number of substeps of this physics world.
    *
    * @return An integer number.
    */
    inline int getSubsteps() const { return _substeps; }

    /**
    * Set the debug draw mask of this physics world.
    * 
    * This physics world will draw shapes and joints by DrawNode according to mask.
    * @param mask Mask has four value:DEBUGDRAW_NONE, DEBUGDRAW_SHAPE, DEBUGDRAW_JOINT, DEBUGDRAW_CONTACT and DEBUGDRAW_ALL, default is DEBUGDRAW_NONE
    */
    void setDebugDrawMask(int mask);

    /**
    * Get the debug draw mask.
    *
    * @return An integer number.
    */
    inline int getDebugDrawMask() { return _debugDrawMask; }
    
    /**
     * To control the step of physics.
     *
     * If you want control it by yourself( fixed-timestep for example ), you can set this to false and call step by yourself.
     * @attention If you set auto step to false, setSpeed setSubsteps and setUpdateRate won't work, you need to control the time step by yourself.
     * @param autoStep A bool object, default value is true.
     */
    void setAutoStep(bool autoStep){ _autoStep = autoStep; }


    /**
    * Get the auto step of this physics world.
    *
    * @return A bool object.
    */
    bool isAutoStep() { return _autoStep; }

    /**
     * The step for physics world.
     *
     * The times passing for simulate the physics.
     * @attention You need to setAutoStep(false) first before it can work.
     * @param   delta   A float number.
     */
    void step(float delta);
    
protected:
    static PhysicsWorld* construct(Scene* scene);
    bool init();
    
    
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
    Vec2 _gravity;
    float _speed;
    int _updateRate;
    int _updateRateCount;
    float _updateTime;
    int _substeps;
    cpSpace* _cpSpace;
    
    bool _updateBodyTransform;
    Vector<PhysicsBody*> _bodies;
    std::list<PhysicsJoint*> _joints;
    Scene* _scene;
    
    bool _autoStep;
    PhysicsDebugDraw* _debugDraw;
    int _debugDrawMask;
    
    EventDispatcher* _eventDispatcher;

    Vector<PhysicsBody*> _delayAddBodies;
    Vector<PhysicsBody*> _delayRemoveBodies;
    std::vector<PhysicsJoint*> _delayAddJoints;
    std::vector<PhysicsJoint*> _delayRemoveJoints;
    
protected:
    PhysicsWorld();
    virtual ~PhysicsWorld();
    
    void beforeSimulation(Node *node, const Mat4& parentToWorldTransform, float nodeParentScaleX, float nodeParentScaleY, float parentRotation);
    void afterSimulation(Node* node, const Mat4& parentToWorldTransform, float parentRotation);

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

/** A physics helper class. Draw physics shape, joint in debug mode. 
 
 *  You do not create PhysicsDebugDraw objects directly; Instead, you can activate it by PhysicsWorld::setDebugDrawMask.
 */
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

/** @} */
/** @} */

NS_CC_END

#endif // CC_USE_PHYSICS
#endif // __CCPHYSICS_WORLD_H__
