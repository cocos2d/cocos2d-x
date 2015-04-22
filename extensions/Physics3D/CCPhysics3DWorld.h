/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
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
#include "extensions/ExtensionMacros.h"
#include "extensions/ExtensionExport.h"

namespace cocos2d{
    class Renderer;
}

#if (CC_ENABLE_BULLET_INTEGRATION)

class btDynamicsWorld;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btDbvtBroadphase;
class btSequentialImpulseConstraintSolver;
class btRigidBody;
class btCollisionObject;

NS_CC_EXT_BEGIN

class Physics3DObject;
class Physics3DConstraint;
class Physics3DDebugDrawer;
class Physics3DComponent;
class Physics3DShape;

struct CC_EX_DLL Physics3DWorldDes
{
    bool           isDebugDrawEnabled; //using physics debug draw?, false by default
    cocos2d::Vec3  gravity;//gravity, (0, -9.8, 0)
    Physics3DWorldDes()
    {
        isDebugDrawEnabled = false;
        gravity = cocos2d::Vec3(0.f, -9.8f, 0.f);
    }
};

class CC_EX_DLL Physics3DWorld : public Ref
{
    friend class Physics3DComponent;
public:
    
    struct HitResult
    {
        cocos2d::Vec3 hitPosition;
        cocos2d::Vec3 hitNormal;
        Physics3DObject* hitObj;
    };
    
    static Physics3DWorld* create(Physics3DWorldDes* info);
    
    void addPhysics3DObject(Physics3DObject* physicsObj);
    
    void removePhysics3DObject(Physics3DObject* physicsObj);
    
    void removeAllPhysics3DObjects();
    
    void addPhysics3DConstraint(Physics3DConstraint* constraint, bool disableCollisionsBetweenLinkedObjs = true);
    
    void removePhysics3DConstraint(Physics3DConstraint* constraint);
    
    void removeAllPhysics3DConstraints();
    
    void stepSimulate(float dt);
    
    void setDebugDrawEnable(bool enableDebugDraw);
    
    bool isDebugDrawEnabled() const;
    
    void debugDraw(cocos2d::Renderer* renderer);
    
    const std::vector<Physics3DObject*>& getPhysicsObjects() const { return _objects; }
    
    bool rayCast(const cocos2d::Vec3& startPos, const cocos2d::Vec3& endPos, HitResult* result);
    
    bool sweepShape(Physics3DShape* shape, const cocos2d::Mat4& startTransform, const cocos2d::Mat4& endTransform, HitResult* result);
    
CC_CONSTRUCTOR_ACCESS:
    
    Physics3DWorld();
    virtual ~Physics3DWorld();
    
    bool init(Physics3DWorldDes* info);
    
    Physics3DObject* getPhysicsObject(const btCollisionObject* btObj);
    
protected:
    std::vector<Physics3DObject*>      _objects;
    std::vector<Physics3DComponent*>   _physicsComponents; //physics3d components
    
#if (CC_ENABLE_BULLET_INTEGRATION)
    btDynamicsWorld* _btPhyiscsWorld;
    btDefaultCollisionConfiguration* _collisionConfiguration;
    btCollisionDispatcher* _dispatcher;
    btDbvtBroadphase* _broadphase;
    btSequentialImpulseConstraintSolver* _solver;
    Physics3DDebugDrawer*                _debugDrawer;
#endif // CC_ENABLE_BULLET_INTEGRATION
};

NS_CC_EXT_END

#endif

#endif // __PHYSICS_3D_WORLD_H__
