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

#if CC_USE_3D_PHYSICS

#if (CC_ENABLE_BULLET_INTEGRATION)

class btCollisionShape;
class btRigidBody;
class btPersistentManifold;
class btGhostObject;

NS_CC_BEGIN
/**
 * @addtogroup physics
 * @{
 * @addtogroup physics_3d
 * @{
*/

class Physics3DShape;
class Physics3DWorld;
class Physics3DConstraint;
class Physics3DObject;
/**
    @brief The collision information of Physics3DObject.
*/
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

    Physics3DObject* objA;
    Physics3DObject* objB;
    std::vector<CollisionPoint> collisionPointList;
};
/**
    @brief Inherit from Ref, base class
*/
class CC_DLL Physics3DObject : public Ref
{
public:
    typedef std::function<void(const Physics3DCollisionInfo& ci)> CollisionCallbackFunc;

    enum class PhysicsObjType
    {
        UNKNOWN = 0,
        RIGID_BODY,
        COLLIDER,
    };

    /** @~english Get the Physics3DObject Type.
        @~chinese 得到physics3dobject的类型。
    */
    virtual PhysicsObjType getObjType() const { return _type; }

    /** @~english Set the user data.
        @~chinese 设置用户数据。
    */
    void setUserData(void* userData) { _userData = userData; }

    /** @~english Get the user data.
        @~chinese 获取用户数据。
    */
    void* getUserData() const { return _userData; }

    /** @~english Internal method. Set the pointer of Physics3DWorld.
        @~chinese 内部方法。设置physics3dworld指针。
    */
    void setPhysicsWorld(Physics3DWorld* world) { _physicsWorld = world; };

    /** @~english Get the pointer of Physics3DWorld.
        @~chinese 得到physics3dworld指针。
    */
    Physics3DWorld* getPhysicsWorld() const { return _physicsWorld; }

    /** @~english Get the world matrix of Physics3DObject.
        @~chinese 得到physics3dobject世界矩阵。
    */
    virtual cocos2d::Mat4 getWorldTransform() const = 0;

    /** @~english Set the collision callback function.
        @~chinese 设置碰撞的回调函数。
    */
    void setCollisionCallback(const CollisionCallbackFunc& func) { _collisionCallbackFunc = func; };

    /** @~english Get the collision callback function.
        @~chinese 得到碰撞回调函数。
    */
    const CollisionCallbackFunc& getCollisionCallback() const { return _collisionCallbackFunc; }

    /** @~english Check has collision callback function.
        @~chinese 检查碰撞回调函数。
    */
    bool needCollisionCallback() { return _collisionCallbackFunc != nullptr; };

    /** @~english Set the mask of Physics3DObject.
        @~chinese 设置physics3dobject的掩码。
    */
    void setMask(unsigned int mask) { _mask = mask; };

    /** @~english Get the mask of Physics3DObject.
        @~chinese 得到physics3dobject的掩码。
    */
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
    virtual ~Physics3DObject() {}

protected:
    bool           _isEnabled;
    PhysicsObjType _type;
    void*          _userData;
    Physics3DWorld* _physicsWorld;
    CollisionCallbackFunc _collisionCallbackFunc;
    unsigned int _mask;
};

/**
    @brief @~english The description of Physics3DRigidBody.
    @~chinese Physics3DRigidBody的描述信息
*/
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

/**
    @brief Inherit from Physics3DObject, the main class for rigid body objects
*/
class CC_DLL Physics3DRigidBody : public Physics3DObject
{
    friend class Physics3DWorld;
public:

    /** @~english Creates a Physics3DRigidBody with Physics3DRigidBody.
        @~chinese 创建一个physics3drigidbody与physics3drigidbody。
        @return @~english An autoreleased Physics3DRigidBody object. @~chinese 一个自动释放的physics3drigidbody对象。
    */
    static Physics3DRigidBody* create(Physics3DRigidBodyDes* info);

    /** @~english Get the pointer of btRigidBody.
        @~chinese 得到btrigidbody指针。
    */
    btRigidBody* getRigidBody() const { return _btRigidBody; }

    /** @~english Apply a force.
        @~chinese 施加一个力。
        @param force @~english  the value of the force @~chinese 力的值
        @param rel_pos @~english the position of the force @~chinese rel_pos力的位置
    */
    void applyForce(const cocos2d::Vec3& force, const cocos2d::Vec3& rel_pos);

    /** @~english Apply a central force.
        @~chinese 应用中心力。
        @param force @~english the value of the force @~chinese 力的值
    */
    void applyCentralForce(const cocos2d::Vec3& force);

    /** @~english Apply a central impulse.
        @~chinese 应用中心的冲动。
        @param impulse  @~english the value of the impulse @~chinese 脉冲的脉冲值
    */
    void applyCentralImpulse(const cocos2d::Vec3& impulse);

    /** @~english Apply a torque.
        @~chinese 应用扭矩。
        @param torque @~english the value of the torque @~chinese 扭力值
    */
    void applyTorque(const cocos2d::Vec3& torque);

    /** @~english Apply a torque impulse.
        @~chinese 应用转矩脉冲。
        @param torque @~english the value of the torque @~chinese 扭力值
    */
    void applyTorqueImpulse(const cocos2d::Vec3& torque);

    /** @~english Apply a impulse.
        @~chinese 应用脉冲。
        @param impulse @~english the value of the impulse @~chinese 脉冲的脉冲值
        @param rel_pos @~englishthe position of the impulse @~chinese rel_pos脉冲的位置
    */
    void applyImpulse(const cocos2d::Vec3& impulse, const cocos2d::Vec3& rel_pos);

    /** @~english Damps the velocity, using the given linearDamping and angularDamping.
        @~chinese 衰减的速度，使用给定的lineardamping和angulardamping。
    */
    void applyDamping(float timeStep);

    /** @~english Set the linear velocity.
        @~chinese 设定线速度。
    */
    void setLinearVelocity(const cocos2d::Vec3& lin_vel);

    /** @~english Get the linear velocity.
        @~chinese 得到的线速度。
    */
    cocos2d::Vec3 getLinearVelocity() const;

    /** @~english Set the linear factor.
        @~chinese 设置线性因子。
    */
    void setLinearFactor(const cocos2d::Vec3& linearFactor);

    /** @~english Get the linear factor.
        @~chinese 得到的线性因子。
    */
    cocos2d::Vec3 getLinearFactor() const;

    /** @~english Set the angular factor.
        @~chinese 设置角因子。
    */
    void setAngularFactor(const cocos2d::Vec3& angFac);

    /** @~english Set the angular factor, use unified factor.
        @~chinese 设置角的因素，使用统一的因素。
    */
    void setAngularFactor(float angFac);

    /** @~english Get the angular factor.
        @~chinese 有角的因素。
    */
    cocos2d::Vec3 getAngularFactor() const;

    /** @~english Set the angular velocity.
        @~chinese 设置角速度。
    */
    void setAngularVelocity(const cocos2d::Vec3& ang_vel);

    /** @~english Get the angular velocity.
        @~chinese 得到角速度。
    */
    cocos2d::Vec3 getAngularVelocity() const;

    /** @~english Set the center of mass.
        @~chinese 设置质量中心。
    */
    void setCenterOfMassTransform(const cocos2d::Mat4& xform);

    /** @~english Get the center of mass.
        @~chinese 获得质量中心。
    */
    cocos2d::Mat4 getCenterOfMassTransform() const;

    /** @~english Set linear damping and angular damping.
        @~chinese 设置线性阻尼和阻尼角。
    */
    void setDamping(float lin_damping, float ang_damping);

    /** @~english Get linear damping.
        @~chinese 得到线性阻尼。
    */
    float getLinearDamping() const;

    /** @~english Get angular damping.
        @~chinese 获得角阻尼。
    */
    float getAngularDamping() const;

    /** @~english Set the acceleration.
        @~chinese 设置加速度。
    */
    void setGravity(const cocos2d::Vec3& acceleration);

    /** @~english Get the acceleration.
        @~chinese 得到加速度。
    */
    cocos2d::Vec3 getGravity() const;

    /** @~english Set the inverse of local inertia.
        @~chinese 组局部惯性反。
    */
    void setInvInertiaDiagLocal(const cocos2d::Vec3& diagInvInertia);

    /** @~english Get the inverse of local inertia.
        @~chinese 得到当地惯性反。
    */
    cocos2d::Vec3 getInvInertiaDiagLocal() const;

    /** @~english Set mass and inertia.
        @~chinese 设定质量和惯性。
    */
    void setMassProps(float mass, const cocos2d::Vec3& inertia);

    /** @~english Get inverse of mass.
        @~chinese 反求质量。
    */
    float getInvMass() const;

    /** @~english Get total force.
        @~chinese 得到的总力。
    */
    cocos2d::Vec3 getTotalForce() const;

    /** @~english Get total torque.
        @~chinese 得到的总力矩。
    */
    cocos2d::Vec3 getTotalTorque() const;

    /** @~english Set restitution.
        @~chinese 设置恢复。
    */
    void setRestitution(float rest);

    /** @~english Get restitution.
        @~chinese 恢复原状。
    */
    float getRestitution() const;

    /** @~english Set friction.
        @~chinese 设置摩擦。
    */
    void setFriction(float frict);

    /** @~english Get friction.
        @~chinese 受摩擦。
    */
    float getFriction() const;

    /** @~english Set rolling friction.
        @~chinese 设置滚动摩擦。
    */
    void setRollingFriction(float frict);

    /** @~english Get rolling friction.
        @~chinese 把滚动摩擦。
    */
    float getRollingFriction() const;

    /** @~english Set hit friction.
        @~chinese 套打摩擦。
    */
    void setHitFraction(float hitFraction);

    /** @~english Get hit friction.
        @~chinese 受到摩擦。
    */
    float getHitFraction() const;

    /** @~english Set motion threshold, don't do continuous collision detection if the motion (in one step) is less then ccdMotionThreshold
        @~chinese 设置运动阈值，不要连续碰撞检测，如果运动（一步）小于ccdmotionthreshold
    */
    void setCcdMotionThreshold(float ccdMotionThreshold);

    /** @~english Get motion threshold.
        @~chinese 得到的运动阈值。
    */
    float getCcdMotionThreshold() const;

    /** @~english Set swept sphere radius.
        @~chinese 集扫球半径。
    */
    void setCcdSweptSphereRadius(float radius);

    /** @~english Get swept sphere radius.
        @~chinese 被球半径。
    */
    float getCcdSweptSphereRadius() const;

    /** @~english Set kinematic object.
        @~chinese 设置运动目标。
    */
    void setKinematic(bool kinematic);

    /** @~english Check rigid body is kinematic object.
        @~chinese 检查刚体运动的对象。
    */
    bool isKinematic() const;

    /** @~english override.
        @~chinese 重写。
    */
    virtual cocos2d::Mat4 getWorldTransform() const override;

    /** @~english Get constraint by index.
        @~chinese 通过索引得到约束。
    */
    Physics3DConstraint* getConstraint(unsigned int idx) const;

    /** @~english Get the total number of constraints.
        @~chinese 得到的总数限制。
    */
    unsigned int getConstraintCount() const;

    /** @~english Active or inactive.
        @~chinese 是否是活跃的。
    */
    void setActive(bool active);

CC_CONSTRUCTOR_ACCESS:
    Physics3DRigidBody();
    virtual ~Physics3DRigidBody();

    bool init(Physics3DRigidBodyDes* info);

    void addConstraint(Physics3DConstraint* constraint);
    void removeConstraint(Physics3DConstraint* constraint);
    void removeConstraint(unsigned int idx);

protected:
    btRigidBody* _btRigidBody;
    Physics3DShape* _physics3DShape;
    std::vector<Physics3DConstraint*> _constraintList;
};

/**
 * @brief @~english The description of Physics3DCollider.
   @~chinese Physics3DCollider的描述信息
 */
struct CC_DLL Physics3DColliderDes
{
    /** @~english shape pointer
    *   @~chinese shape的指针
    */
    Physics3DShape* shape;
    /** @~english original world Transform
    *   @~chinese 初始的世界变换矩阵
    */
    cocos2d::Mat4 originalTransform;
    /** @~english Is collider a trigger?
    *   @~chinese 是否是一个trigger
    */
    bool          isTrigger;
    /** @~english the friction
    *   @~chinese 摩擦力
    */
    float friction;
    /** @~english the rolling friction
    *   @~chinese 滚动摩擦力
    */
    float rollingFriction;
    /** @~english the restitution
    *   @~chinese 恢复
    */
    float restitution;
    /** @~english the hit fraction
    *   @~chinese 碰撞摩擦力
    */
    float hitFraction;
    /** @~english the swep sphere radius
    *   @~chinese 扫球半径值
    */
    float ccdSweptSphereRadius;
    /** @~english the motion threshold
    *   @~chinese 运动阀值
    */
    float ccdMotionThreshold;

    Physics3DColliderDes()
        : shape(nullptr)
        , isTrigger(false)
        , friction(0.5f)
        , rollingFriction(0.0f)
        , restitution(0.0f)
        , hitFraction(1.0f)
        , ccdSweptSphereRadius(0.0f)
        , ccdMotionThreshold(0.0f)
    {

    }
};

/**
* @brief @~english Inherit from Physics3DObject, the main class for Colliders.
  @~chinese 继承自Physics3DObject，用来处理Colliders的类
*/
class CC_DLL Physics3DCollider : public Physics3DObject
{
public:

    /** @~english Creates a Physics3DCollider with Physics3DColliderDes.
    *  @~chinese 用Physics3DColliderDes来创建一个Physics3DCollider。
    *  @return @~english An autoreleased Physics3DCollider object. @~chinese 一个自动释放的Physics3DCollider对象。
    */
    static Physics3DCollider* create(Physics3DColliderDes *info);

    /** @~english Get the pointer of btGhostObject.
    *  @~chinese 获取btGhostObject的指针。
    *  @return The pointer of btGhostObject.
    */
    btGhostObject* getGhostObject() const { return _btGhostObject; }

    /** @~english Set trigger.
    *  @~chinese 设置是否是trigger。
    *  @param isTrigger @~english Is a trigger. @~chinese 是否是trigger
    */
    void setTrigger(bool isTrigger);

    /** @~english Check is a trigger.
    *  @~chinese 是否是trigger。
    *  @return @~english Is a trigger. @~chinese 是否是trigger。
    */
    bool isTrigger() const;

    /** @~english Set restitution.
    *  @~chinese 设置恢复。
    *  @param rest @~english The restitution. @~chinese 恢复值。
    */
    void setRestitution(float rest);

    /** @~english Get restitution.
    *  @~chinese 获取恢复。
    *  @return @~english The restitution. @~chinese 恢复值。
    */
    float getRestitution() const;

    /** @~english Set friction.
    *  @~chinese 设置摩擦。
    *  @param rest @~english The friction. @~chinese 摩擦值。
    */
    void setFriction(float frict);

    /** @~english Get friction.
    *  @~chinese 获取摩擦。
    *  @return @~english The friction. @~chinese 摩擦值。
    */
    float getFriction() const;

    /** @~english Set rolling friction.
    *  @~chinese 设置滚动摩擦。
    *  @param frict @~english The rolling friction. @~chinese 滚动摩擦值。
    */
    void setRollingFriction(float frict);

    /** @~english Get rolling friction.
    *  @~chinese 获取滚动摩擦。
    *  @return @~english The rolling friction.  @~chinese 滚动摩擦值。
    */
    float getRollingFriction() const;

    /** @~english Set hit friction.
    *  @~chinese 设置碰撞摩擦。
    *  @param hitFraction @~english The hit friction.  @~chinese 碰撞摩擦值。
    */
    void setHitFraction(float hitFraction);

    /** @~english Get hit friction.
    *  @~chinese 获取碰撞摩擦。
    *  @return @~english The hit friction.  @~chinese 碰撞摩擦值。
    */
    float getHitFraction() const;

    /** @~english Set motion threshold, don't do continuous collision detection if the motion (in one step) is less then ccdMotionThreshold.
    *  @~chinese 设置运动阈值，不要连续碰撞检测，如果运动（一步）小于ccdmotionthreshold。
    *  @param ccdMotionThreshold @~english The motion threshold.  @~chinese 运动阈值。
    */
    void setCcdMotionThreshold(float ccdMotionThreshold);

    /** @~english Get motion threshold.
    *  @~chinese 获取运动阈值。
    *  @return @~english The motion threshold. @~chinese 运动阈值。
    */
    float getCcdMotionThreshold() const;

    /** @~english Set swept sphere radius.
    *  @~chinese 设置扫球半径。
    *  @param radius @~english The swept sphere radius. @~chinese 扫球半径值。
    */
    void setCcdSweptSphereRadius(float radius);

    /** @~english Get swept sphere radius.
    *  @~chinese 获取扫球半径。
    *  @return @~english The swept sphere radius. @~chinese 扫球半径值。
    */
    float getCcdSweptSphereRadius() const;

    /** override. */
    virtual cocos2d::Mat4 getWorldTransform() const;

    /** @~english Set a callback when trigger enter.
        @~chinese 设置一个回调函数在trigger进入时响应。
    */
    std::function<void(Physics3DObject *otherObject)> onTriggerEnter;

    /** @~english Set a callback when trigger exit.
        @~chinese 设置一个回调函数在trigger离开时响应。
    */
    std::function<void(Physics3DObject *otherObject)> onTriggerExit;

CC_CONSTRUCTOR_ACCESS :
    Physics3DCollider();
    virtual ~Physics3DCollider();

    bool init(Physics3DColliderDes *info);

protected:

    btGhostObject *_btGhostObject;
    Physics3DShape *_physics3DShape;
};

// end of physics_3d group
/// @}
// end of physics group
/// @}

NS_CC_END

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif //CC_USE_3D_PHYSICS

#endif // __PHYSICS_3D_OBJECT_H__
