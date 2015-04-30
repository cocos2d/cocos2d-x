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

#ifndef __PHYSICS_3D_OBJECT_H__
#define __PHYSICS_3D_OBJECT_H__

#include "math/CCMath.h"
#include "base/CCRef.h"
#include "base/ccConfig.h"

#include <vector>

#if (CC_ENABLE_BULLET_INTEGRATION)

class btCollisionShape;
class btRigidBody;
class btPersistentManifold;

NS_CC_BEGIN

class Physics3DShape;
class Physics3DWorld;
class Physics3DConstraint;
class Physics3DObject;
struct CC_DLL Physics3DCollisionInfo
{
    struct CollisionPoint
    {
        Vec3 localPositionOnA;
        Vec3 worldPositionOnA;
        Vec3 localPositionOnB;
        Vec3 worldPositionOnB;
        Vec3 worldNormalOnB;
    };

    Physics3DObject *objA;
    Physics3DObject *objB;
    std::vector<CollisionPoint> collisionPointList;
};

class CC_DLL Physics3DObject : public Ref
{
public:
    typedef std::function<void(const Physics3DCollisionInfo &ci)> CollisionCallbackFunc;

    enum class PhysicsObjType
    {
        UNKNOWN = 0,
        RIGID_BODY,
    };
    
    virtual PhysicsObjType getObjType() const { return _type; }
    
    void setUserData(void* userData)  { _userData = userData; }
    
    void* getUserData() const { return _userData; }
    
    void setPhysicsWorld(Physics3DWorld* world) { _physicsWorld = world; };
    
    Physics3DWorld* getPhysicsWorld() const { return _physicsWorld; }
    
    virtual cocos2d::Mat4 getWorldTransform() const = 0;

    void setCollisionCallback(const CollisionCallbackFunc &func) { _collisionCallbackFunc = func; };
    const CollisionCallbackFunc& getCollisionCallback() const { return _collisionCallbackFunc; }

    bool needCollisionCallback() { return _collisionCallbackFunc != nullptr; };

    void setMask(unsigned int mask) { _mask = mask; };
    unsigned int getMask() const { return _mask; };
    
CC_CONSTRUCTOR_ACCESS:
    Physics3DObject()
    : _type(PhysicsObjType::UNKNOWN)
    , _userData(nullptr)
    , _isEnabled(true)
    , _physicsWorld(nullptr)
    , _mask(-1)
    {
        
    }
    virtual ~Physics3DObject(){}
    

protected:
    bool           _isEnabled;
    PhysicsObjType _type;
    void*          _userData;
    Physics3DWorld* _physicsWorld;
    CollisionCallbackFunc _collisionCallbackFunc;
    unsigned int _mask;
};

struct CC_DLL Physics3DRigidBodyDes
{
    float mass; //Note: mass equals zero means static, default 0
    cocos2d::Vec3 localInertia; //default (0, 0, 0)
    Physics3DShape* shape;
    cocos2d::Mat4 originalTransform;
    bool          disableSleep; //it is always active if disabled
    
    Physics3DRigidBodyDes()
    : mass(0.f)
    , localInertia(0.f, 0.f, 0.f)
    , shape(nullptr)
    , disableSleep(false)
    {
        
    }
};
class CC_DLL Physics3DRigidBody : public Physics3DObject
{
    friend class Physics3DWorld;
public:
    
    static Physics3DRigidBody* create(Physics3DRigidBodyDes* info);
    
    btRigidBody* getRigidBody() const { return _btRigidBody; }
    
    void applyForce(const cocos2d::Vec3& force, const cocos2d::Vec3& rel_pos);
    void applyCentralForce(const cocos2d::Vec3& force);
    void applyCentralImpulse(const cocos2d::Vec3& impulse);
    void applyTorque(const cocos2d::Vec3& torque);
    void applyTorqueImpulse(const cocos2d::Vec3& torque);
    void applyImpulse(const cocos2d::Vec3& impulse, const cocos2d::Vec3& rel_pos);
    void applyDamping(float timeStep);

    void setLinearVelocity(const cocos2d::Vec3& lin_vel);
    cocos2d::Vec3 getLinearVelocity() const;
    void setLinearFactor(const cocos2d::Vec3& linearFactor);
    cocos2d::Vec3 getLinearFactor() const;
    void setAngularFactor(const cocos2d::Vec3& angFac);
    void setAngularFactor(float angFac);
    cocos2d::Vec3 getAngularFactor() const;
    void setAngularVelocity(const cocos2d::Vec3& ang_vel);
    cocos2d::Vec3 getAngularVelocity() const;
    void setCenterOfMassTransform(const cocos2d::Mat4& xform);
    cocos2d::Mat4 getCenterOfMassTransform() const;
    void setDamping(float lin_damping, float ang_damping);
    float getLinearDamping() const;
    float getAngularDamping() const;
    void setGravity(const cocos2d::Vec3& acceleration); 
    cocos2d::Vec3 getGravity() const;
    void setInvInertiaDiagLocal(const cocos2d::Vec3& diagInvInertia);
    cocos2d::Vec3 getInvInertiaDiagLocal() const;
    void setMassProps(float mass, const cocos2d::Vec3& inertia);
    float getInvMass() const;
    cocos2d::Vec3 getTotalForce() const;
    cocos2d::Vec3 getTotalTorque() const;


    void setRestitution(float rest);
    float getRestitution() const;
    void setFriction(float frict);
    float getFriction() const;
    void setRollingFriction(float frict);
    float getRollingFriction() const;
    void setHitFraction(float hitFraction);
    float getHitFraction() const;
    void setCcdMotionThreshold(float ccdMotionThreshold);
    float getCcdMotionThreshold() const;
    void setCcdSweptSphereRadius(float radius);
    float getCcdSweptSphereRadius() const;
    
    void setKinematic(bool kinematic);
    
    bool isKinematic() const;
    
    virtual cocos2d::Mat4 getWorldTransform() const override;
    
    Physics3DConstraint* getConstraint(unsigned int idx) const;
    unsigned int getConstraintCount() const;
    
    void setActive(bool active);

CC_CONSTRUCTOR_ACCESS:
    Physics3DRigidBody();
    virtual ~Physics3DRigidBody();
    
    bool init(Physics3DRigidBodyDes* info);
    
    void addConstraint(Physics3DConstraint *constraint);
    void removeConstraint(Physics3DConstraint *constraint);
    void removeConstraint(unsigned int idx);
    
protected:
    btRigidBody* _btRigidBody;
    Physics3DShape *_physics3DShape;
    std::vector<Physics3DConstraint *> _constraintList;
};

NS_CC_END

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif // __PHYSICS_3D_OBJECT_H__
