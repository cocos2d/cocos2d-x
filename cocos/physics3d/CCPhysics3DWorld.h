/****************************************************************************
 Copyright (c) 2015-2017 Chukong Technologies Inc.
 
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

#ifndef __PHYSICS_3D_WORLD_H__
#define __PHYSICS_3D_WORLD_H__

#include "math/CCMath.h"
#include "base/CCRef.h"
#include "base/ccConfig.h"

#if CC_USE_3D_PHYSICS

#if (CC_ENABLE_BULLET_INTEGRATION)

class btDynamicsWorld;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btDbvtBroadphase;
class btSequentialImpulseConstraintSolver;
class btGhostPairCallback;
class btRigidBody;
class btCollisionObject;

NS_CC_BEGIN
/**
 * @addtogroup _3d
 * @{
 */

class Physics3DObject;
class Physics3DConstraint;
class Physics3DDebugDrawer;
class Physics3DComponent;
class Physics3DShape;
class Renderer;

/**
 * @brief The description of Physics3DWorld.
 */
struct CC_DLL Physics3DWorldDes
{
    bool           isDebugDrawEnabled; //using physics debug draw?, false by default
    cocos2d::Vec3  gravity;//gravity, (0, -9.8, 0)
    Physics3DWorldDes()
    {
        isDebugDrawEnabled = false;
        gravity = cocos2d::Vec3(0.f, -9.8f, 0.f);
    }
};

/**
 * @brief The physics information container, include Physics3DObjects, Physics3DConstraints, collision information and so on.
 */
class CC_DLL Physics3DWorld : public Ref
{
    friend class Physics3DComponent;
public:
    
    struct HitResult
    {
        cocos2d::Vec3 hitPosition;
        cocos2d::Vec3 hitNormal;
        Physics3DObject* hitObj;
    };
    
    /**
     * Creates a Physics3DWorld with Physics3DWorldDes. 
     *
     * @return An autoreleased Physics3DWorld object.
     */
    static Physics3DWorld* create(Physics3DWorldDes* info);
    
    /** set gravity for the physics world */
    void setGravity(const Vec3& gravity);
    
    /** get current gravity */
    Vec3 getGravity() const;
    
    /** Add a Physics3DObject. */
    void addPhysics3DObject(Physics3DObject* physicsObj);
    
    /** Remove a Physics3DObject. */
    void removePhysics3DObject(Physics3DObject* physicsObj);
    
    /** Remove all Physics3DObjects. */
    void removeAllPhysics3DObjects();
    
    /** Add a Physics3DConstraint. */
    void addPhysics3DConstraint(Physics3DConstraint* constraint, bool disableCollisionsBetweenLinkedObjs = true);
    
    /** Remove a Physics3DConstraint. */
    void removePhysics3DConstraint(Physics3DConstraint* constraint);
    
    /** Remove all Physics3DConstraint. */
    void removeAllPhysics3DConstraints();
    
    /** Simulate one frame. */
    void stepSimulate(float dt);
    
    /** Enable or disable debug drawing. */
    void setDebugDrawEnable(bool enableDebugDraw);
    
    /** Check debug drawing is enabled. */
    bool isDebugDrawEnabled() const;
    
    /** Internal method, the updater of debug drawing, need called each frame. */
    void debugDraw(cocos2d::Renderer* renderer);
    
    /** Get the list of Physics3DObjects. */
    const std::vector<Physics3DObject*>& getPhysicsObjects() const { return _objects; }
    
    /**
     * Ray cast method
     * @param startPos The start position of ray.
     * @param endPos The end position of ray.
     * @param result the result of ray cast.
     */
    bool rayCast(const cocos2d::Vec3& startPos, const cocos2d::Vec3& endPos, HitResult* result);
    
    /** Performs a swept shape cast on all objects in the Physics3DWorld. */
    bool sweepShape(Physics3DShape* shape, const cocos2d::Mat4& startTransform, const cocos2d::Mat4& endTransform, HitResult* result);
    
CC_CONSTRUCTOR_ACCESS:
    
    Physics3DWorld();
    virtual ~Physics3DWorld();
    
    bool init(Physics3DWorldDes* info);
    
    Physics3DObject* getPhysicsObject(const btCollisionObject* btObj);

    void collisionChecking();
    bool needCollisionChecking();
    void setGhostPairCallback();
    
protected:
    std::vector<Physics3DObject*>      _objects;
    std::vector<Physics3DComponent*>   _physicsComponents; //physics3d components
    bool _needCollisionChecking;
    bool _collisionCheckingFlag;
    bool _needGhostPairCallbackChecking;
    
#if (CC_ENABLE_BULLET_INTEGRATION)
    btDynamicsWorld* _btPhyiscsWorld;
    btDefaultCollisionConfiguration* _collisionConfiguration;
    btCollisionDispatcher* _dispatcher;
    btDbvtBroadphase* _broadphase;
    btSequentialImpulseConstraintSolver* _solver;
    btGhostPairCallback *_ghostCallback;
    Physics3DDebugDrawer*                _debugDrawer;
#endif // CC_ENABLE_BULLET_INTEGRATION
};

// end of 3d group
/// @}
NS_CC_END

#endif

#endif //CC_USE_3D_PHYSICS

#endif // __PHYSICS_3D_WORLD_H__
