﻿/****************************************************************************
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

#ifndef __PHYSICS_3D_CONSTRAINT_H__
#define __PHYSICS_3D_CONSTRAINT_H__

#include "math/CCMath.h"
#include "base/CCRef.h"
#include "base/ccConfig.h"

#if CC_USE_3D_PHYSICS

#if (CC_ENABLE_BULLET_INTEGRATION)

class btTypedConstraint;

NS_CC_BEGIN

/**
    @addtogroup _3d
    @{
*/

class Physics3DRigidBody;

/**
    @class Physics3DConstraint
    @brief @~english Constraint affects the movement of physics object, it usually connet one or two physics object. There are some types of physics constraints.
    @~chinese 约束影响物理对象的运动，它通常连接一个或两个物理对象。
*/
class CC_DLL Physics3DConstraint : public Ref
{
public:
    enum class ConstraintType
    {
        UNKNOWN,
        POINT_TO_POINT,
        HINGE,
        SLIDER,
        CONE_TWIST,
        SIX_DOF,
    };
    /** @~english get the impulse that break the constraint
        @~chinese 获取打破约束的阀值
        @return @~english the impulse that break the constraint @~chinese 打破约束的阀值
    */
    float getBreakingImpulse() const;

    /** @~english set the impulse that break the constraint
        @~chinese 设置打破约束的阀值
        @param impulse @~english  the impulse that break the constraint @~chinese 打破约束的阀值
    */
    void setBreakingImpulse(float impulse);

    /** @~english is it enabled
        @~chinese 约束是否启用
        @return @~english whether the constraint is enabled @~chinese 约束是否启用
    */
    bool isEnabled() const;

    /** @~english set enable or not
        @~chinese 启用约束
        @param enabled @~english  whether the constraint will be enabled @~chinese 约束是否启用
    */
    void setEnabled(bool enabled);

    /** @~english get rigid body a
        @~chinese 得到刚体a
        @return @~english the Physics3DRigidBody A @~chinese 刚体a
    */
    Physics3DRigidBody* getBodyA() const { return _bodyA; }

    /** @~english get rigid body b
        @~chinese 得到刚体b
        @return @~english the Physics3DRigidBody B @~chinese 刚体b
    */
    Physics3DRigidBody* getBodyB() const { return _bodyB; }

    /** @~english get constraint type
        @~chinese 得到约束类型
        @return @~english the constraint type @~chinese 约束类型
    */
    ConstraintType getConstraintType() const { return _type; }

    /** @~english get user data
        @~chinese 设置用户数据
        @param the @~english  user data will be seted @~chinese 用户数据将
    */
    void setUserData(void* userData) { _userData = userData; }

    /** @~english get user data
        @~chinese 获取用户数据
        @return @~english the user data @~chinese 用户数据
    */
    void* getUserData() const { return _userData; }

    /** @~english get override number of solver iterations
        @~chinese 得到覆盖求解迭代次数
        @return @~english the override number of solver iterations @~chinese 覆盖求解迭代次数
    */
    int getOverrideNumSolverIterations() const;

    /** @~english override the number of constraint solver iterations used to solve this constraint, -1 will use the default number of iterations, as specified in SolverInfo.m_numIterations
        @~chinese 覆盖约束求解的求解迭代次数，1将使用默认迭代次数
        @param overideNumIterations @~english  the number of constraint solver iterations @~chinese 约束求解的迭代次数
    */
    void setOverrideNumSolverIterations(int overideNumIterations);

#if (CC_ENABLE_BULLET_INTEGRATION)
    btTypedConstraint* getbtContraint() { return _constraint; }
#endif

protected:

    Physics3DConstraint();
    virtual ~Physics3DConstraint();

    btTypedConstraint* _constraint;

    Physics3DRigidBody* _bodyA;
    Physics3DRigidBody* _bodyB;

    ConstraintType      _type;
    void*               _userData;
};

/**
    Point to point constraint limits the translation so that the local pivot points of 2 rigidbodies match in worldspace.
    @~chinese
*/
class CC_DLL Physics3DPointToPointConstraint : public Physics3DConstraint
{
public:
    /** @~english create point to point constraint, limits the translation of local pivot point of rigid body A
        @~chinese 建立点对点的约束，限制刚体A的枢轴的平移
        @param rbA @~english  The rigid body going to be fixed @~chinese 刚体A
        @param pivotPointInA @~english  local pivot point in A's local space @~chinese 在一个局部空间的局部支点
        @return @~english created constraint @~chinese 创建约束
    */
    static Physics3DPointToPointConstraint* create(Physics3DRigidBody* rbA, const cocos2d::Vec3& pivotPointInA);

    /** @~english create point to point constraint, make the local pivot points of 2 rigid bodies match in worldspace.
        @~chinese 建立点对点的约束，使两个刚体的枢轴在世界空间内相匹配。
        @param rbA @~english  The rigid body A going to be fixed @~chinese 要约束的刚体A
        @param rbB @~english  The rigid body B going to be fixed @~chinese 要约束的刚体B
        @param pivotPointInA @~english  local pivot point in A's local space @~chinese 在A的局部空间的局部支点
        @param pivotPointInB @~english  local pivot point in B's local space @~chinese 在B的局部空间的局部支点
        @return @~english created constraint @~chinese 创建约束
    */
    static Physics3DPointToPointConstraint* create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Vec3& pivotPointInA, const cocos2d::Vec3& pivotPointInB);

    /** @~english set pivot point in A's local space
        @~chinese 在A的局部空间设置支点
        @param pivotA @~english  pivot point in A's local space @~chinese 在A的局部空间的支点
    */
    void setPivotPointInA(const cocos2d::Vec3& pivotA);

    /** @~english set pivot point in B's local space
        @~chinese 在B的局部空间设置支点
        @param pivotB @~english  pivot point in B's local space @~chinese 在B的局部空间的支点
    */
    void setPivotPointInB(const cocos2d::Vec3& pivotB);

    /** @~english get pivot point in A's local space
        @~chinese 得到A的局部空间的支点
        @return @~english pivot point in A's local space @~chinese A的局部空间的支点
    */
    cocos2d::Vec3 getPivotPointInA() const;

    /** @~english get pivot point in B's local space
        @~chinese 得到B的局部空间的支点
        @return @~english pivot point in B's local space @~chinese B的局部空间的支点
    */
    cocos2d::Vec3 getPivotPointInB() const;

CC_CONSTRUCTOR_ACCESS:
    Physics3DPointToPointConstraint();
    virtual ~Physics3DPointToPointConstraint();

protected:
    bool init(Physics3DRigidBody* rbA, const cocos2d::Vec3& pivotPointInA);
    bool init(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Vec3& pivotPointInA, const cocos2d::Vec3& pivotPointInB);

};

/** @~english Hinge constraint restricts two additional angular degrees of freedom, so the body can only rotate around one axis, the hinge axis. This can be useful to represent doors or wheels rotating around one axis.    hinge constraint between two rigidbodies each with a pivotpoint that descibes the axis location in local space
    @~chinese 铰链约束限制两个附加的角自由度，所以刚体只能绕一个轴，铰链轴。铰链十分适合表示门或车轮围绕一个轴旋转。两个刚体之间的铰链约束由各自局部空间内的枢轴来表示
*/
class CC_DLL Physics3DHingeConstraint : public Physics3DConstraint
{
public:
    /** @~english create hinge constraint
        @~chinese 创建铰链约束
        @param rbA @~english  rigid body A @~chinese 刚体A
        @param rbAFrame @~english  rigid body A's frame @~chinese 刚体的框架
        @param useReferenceFrameA @~english  use frame A as reference @~chinese 使用框架作为参考
        @return @~english return an autoreleased Physics3DHingeConstraint object. @~chinese 返回一个自动释放的physics3dhingeconstraint。
    */
    static Physics3DHingeConstraint* create(Physics3DRigidBody* rbA, const cocos2d::Mat4& rbAFrame, bool useReferenceFrameA = false);

    /** @~english create hinge constraint
        @~chinese 创建铰链约束
        @param rbA @~english  rigid body A @~chinese 刚体A
        @param pivotInA @~english  pivot in rigid body A's local space @~chinese 在刚体A的局部空间内的枢轴
        @param axisInA @~english  axis in rigid body A's local space @~chinese 在刚体A的局部空间内的轴向
        @param useReferenceFrameA @~english  use frame A as reference @~chinese 使用框架作为引用
        @return @~english return an autoreleased Physics3DHingeConstraint object. @~chinese 返回一个自动释放的physics3dhingeconstraint。
    */
    static Physics3DHingeConstraint* create(Physics3DRigidBody* rbA, const cocos2d::Vec3& pivotInA, const cocos2d::Vec3& axisInA, bool useReferenceFrameA = false);

    /** @~english create hinge constraint
        @~chinese 创建铰链约束
        @param rbA @~english  rigid body A @~chinese 刚体A
        @param rbB @~english  rigid body B @~chinese 刚体B
        @param pivotInA @~english  pivot point in A's local space @~chinese 在A的局部空间的枢轴
        @param pivotInB @~english  pivot point in B's local space @~chinese 在B的局部空间的枢轴
        @param axisInA @~english  axis in A's local space @~chinese 在A的局部空间轴
        @param axisInB @~english  axis in B's local space @~chinese 在B的局部空间轴
        @param useReferenceFrameA @~english  use frame A as reference @~chinese 使用帧作为参考
        @return @~english return an autoreleased Physics3DHingeConstraint object. @~chinese 返回一个自动释放的physics3dhingeconstraint。
    */
    static Physics3DHingeConstraint* create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Vec3& pivotInA,const cocos2d::Vec3& pivotInB, cocos2d::Vec3& axisInA, cocos2d::Vec3& axisInB, bool useReferenceFrameA = false);

    /** @~english create hinge constraint
        @~chinese 创建铰链约束
        @param rbA @~english  rigid body A @~chinese 刚体A
        @param rbB @~english  rigid body B @~chinese 刚体B
        @param rbAFrame @~english  rigid body A's frame @~chinese 刚体A的框架
        @param rbBFrame @~english  rigid body B's frame @~chinese 刚体B的框架
        @param useReferenceFrameA @~english  use frame A as reference @~chinese 使用帧作为参考
        @return @~english return an autoreleased Physics3DHingeConstraint object. @~chinese 返回一个自动释放的physics3dhingeconstraint。
    */
    static Physics3DHingeConstraint* create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Mat4& rbAFrame, const cocos2d::Mat4& rbBFrame, bool useReferenceFrameA = false);

    /** @~english get rigid body A's frame offset
        @~chinese 得到刚体的帧偏移
        @return @~english rigid body A's frame offset @~chinese 刚体的帧偏移
    */
    cocos2d::Mat4 getFrameOffsetA() const;

    /** @~english get rigid body B's frame offset
        @~chinese 得到刚体B帧偏移
        @return @~english rigid body B's frame offset @~chinese 刚体B帧偏移
    */
    cocos2d::Mat4 getFrameOffsetB() const;

    /** @~english set frames for rigid body A and B
        @~chinese 为刚体A和B设置帧
        @param frameA @~english  frame will be seted to rigid body A @~chinese 设置给刚体A的框架
        @param frameB @~english  frame will be seted to rigid body B @~chinese 设置给刚体B的框架
    */
    void setFrames(const cocos2d::Mat4& frameA, const cocos2d::Mat4& frameB);

    /** @~english set angular only
        @~chinese 设置角
        @param angularOnly @~english  angular will be set @~chinese 将要设置的角
    */
    void setAngularOnly(bool angularOnly);

    /** @~english enable angular motor
        @~chinese 使角电机
        @param enableMotor @~english  whether to enable AngularMotor @~chinese 是否启用angularmotor
        @param targetVeloctiy @~english  target velocity @~chinese 目标速度
        @param maxMotorImpulse @~english  max motor impulse @~chinese 最大电机脉冲
    */
    void enableAngularMotor(bool enableMotor, float targetVelocity, float maxMotorImpulse);

    /** @~english extra motor API, including ability to set a target rotation (as opposed to angular velocity)
        @~chinese 额外的电机的API，包括设定一个目标旋转能力（与角速度）
        @param enableMotor @~english  whether to enable AngularMotor @~chinese 是否启用angularmotor
        @note: setMotorTarget sets angular velocity under the hood, so you must call it every tick to
           maintain a given angular target.
    */
    void enableMotor(bool enableMotor);

    /** @~english set max motor impulse
        @~chinese 设置最大电机脉冲
        @param maxMotorImpulse @~english   max motor impulse @~chinese 最大电机脉冲
    */
    void setMaxMotorImpulse(float maxMotorImpulse);

    /** @~english set motor target
        @~chinese 设置电机的目标
    */
    void setMotorTarget(const cocos2d::Quaternion& qAinB, float dt);
    /** @~english set motor target
        @~chinese 设置运动目标
    */
    void setMotorTarget(float targetAngle, float dt);

    /** @~english set limit
        @~chinese 设置限制
    */
    void setLimit(float low, float high, float _softness = 0.9f, float _biasFactor = 0.3f, float _relaxationFactor = 1.0f);
    /** set axis
        @~chinese
    */
    void setAxis(const cocos2d::Vec3& axisInA);
    /** @~english get lower limit
        @~chinese 获得较低的极限
    */
    float getLowerLimit() const;
    /** @~english get upper limit
        @~chinese 获得上限
    */
    float getUpperLimit() const;
    /** @~english get hinge angle
        @~chinese 把铰链转角
    */
    float getHingeAngle() const;
    /** @~english get hinge angle
        @~chinese 把铰链转角
    */
    float getHingeAngle(const cocos2d::Mat4& transA, const cocos2d::Mat4& transB);

    /** @~english get A's frame
        @~chinese 得到的框架
    */
    cocos2d::Mat4 getAFrame() const;
    /** @~english get B's frame
        @~chinese 得到B的框架
    */
    cocos2d::Mat4 getBFrame() const;
    /** @~english get angular only
        @~chinese 只有获得角
    */
    bool getAngularOnly() const;
    /** @~english get enable angular motor
        @~chinese 能使角电机
    */
    bool getEnableAngularMotor() const;
    /** @~english get motor target velosity
        @~chinese 得到运动目标速度
    */
    float getMotorTargetVelosity() const;
    /** @~english get max motor impulse
        @~chinese 最大电机脉冲
    */
    float getMaxMotorImpulse() const;

    /** @~english access for UseFrameOffset
        @~chinese 访问useframeoffset
    */
    bool getUseFrameOffset() const;
    /** @~english set use frame offset
        @~chinese 使用帧偏移
    */
    void setUseFrameOffset(bool frameOffsetOnOff);

CC_CONSTRUCTOR_ACCESS:
    Physics3DHingeConstraint()
    {
        _type = ConstraintType::HINGE;
    }
    virtual ~Physics3DHingeConstraint() {}
};

/**
    It allows the body to rotate around x axis and translate along this axis.
    softness, restitution and damping for different cases
    DirLin - moving inside linear limits
    LimLin - hitting linear limit
    DirAng - moving inside angular limits
    LimAng - hitting angular limit
    OrthoLin, OrthoAng - against constraint axis
*/
class CC_DLL Physics3DSliderConstraint : public Physics3DConstraint
{
public:
    /** @~english create slider constraint
        @~chinese 创建滑块约束

        @param rbA @~english  rigid body A @~chinese 刚体A
        @param rbB @~english  rigid body B @~chinese 刚体B
        @param frameInA @~english  frame in A's local space @~chinese 在A的局部空间框架
        @param frameInB @~english  frame in B's local space @~chinese 在B的局部空间框架
        @param useLinearReferenceFrameA @~english  use fixed frame A for linear limits @~chinese 使用固定框架的线性范围
    */
    static Physics3DSliderConstraint* create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Mat4& frameInA, const cocos2d::Mat4& frameInB ,bool useLinearReferenceFrameA);

    /** @~english get A's frame offset
        @~chinese 得到的帧偏移
    */
    cocos2d::Mat4 getFrameOffsetA() const;
    /** @~english get B's frame offset
        @~chinese 得到B的帧偏移
    */
    cocos2d::Mat4 getFrameOffsetB() const;
    /** @~english get lower linear limit
        @~chinese 获得较低的线性限制
    */
    float getLowerLinLimit() const;
    /** @~english set lower linear limit
        @~chinese 设置较低的线性限制
    */
    void setLowerLinLimit(float lowerLimit);
    /** @~english get upper linear limit
        @~chinese 拿上线性极限
    */
    float getUpperLinLimit() const;
    /** @~english set upper linear limit
        @~chinese 集上的线性限制
    */
    void setUpperLinLimit(float upperLimit);
    /** @~english get lower angular limit
        @~chinese 获得较低的极限角
    */
    float getLowerAngLimit() const;
    /** @~english set lower angualr limit
        @~chinese 低角限制
    */
    void setLowerAngLimit(float lowerLimit);
    /** @~english get upper anglular limit
        @~chinese 有上角的限制
    */
    float getUpperAngLimit() const;
    /** @~english set upper anglular limit
        @~chinese 套上角限制
    */
    void setUpperAngLimit(float upperLimit);
    /** @~english use A's frame as linear refference
        @~chinese 使用线性参考的框架
    */
    bool getUseLinearReferenceFrameA() const;

    float getSoftnessDirLin() const;
    float getRestitutionDirLin() const;
    float getDampingDirLin() const;
    float getSoftnessDirAng() const;
    float getRestitutionDirAng() const;
    float getDampingDirAng() const;
    float getSoftnessLimLin() const;
    float getRestitutionLimLin() const;
    float getDampingLimLin() const;
    float getSoftnessLimAng() const;
    float getRestitutionLimAng() const;
    float getDampingLimAng() const;
    float getSoftnessOrthoLin() const;
    float getRestitutionOrthoLin() const;
    float getDampingOrthoLin() const;
    float getSoftnessOrthoAng() const;
    float getRestitutionOrthoAng() const;
    float getDampingOrthoAng() const;
    void setSoftnessDirLin(float softnessDirLin);
    void setRestitutionDirLin(float restitutionDirLin);
    void setDampingDirLin(float dampingDirLin);
    void setSoftnessDirAng(float softnessDirAng);
    void setRestitutionDirAng(float restitutionDirAng);
    void setDampingDirAng(float dampingDirAng);
    void setSoftnessLimLin(float softnessLimLin);
    void setRestitutionLimLin(float restitutionLimLin);
    void setDampingLimLin(float dampingLimLin);
    void setSoftnessLimAng(float softnessLimAng);
    void setRestitutionLimAng(float restitutionLimAng);
    void setDampingLimAng(float dampingLimAng);
    void setSoftnessOrthoLin(float softnessOrthoLin);
    void setRestitutionOrthoLin(float restitutionOrthoLin);
    void setDampingOrthoLin(float dampingOrthoLin);
    void setSoftnessOrthoAng(float softnessOrthoAng);
    void setRestitutionOrthoAng(float restitutionOrthoAng);
    void setDampingOrthoAng(float dampingOrthoAng);
    void setPoweredLinMotor(bool onOff);
    bool getPoweredLinMotor() const;
    void setTargetLinMotorVelocity(float targetLinMotorVelocity);
    float getTargetLinMotorVelocity() const;
    void setMaxLinMotorForce(float maxLinMotorForce);
    float getMaxLinMotorForce() const;
    void setPoweredAngMotor(bool onOff);
    bool getPoweredAngMotor() const;
    void setTargetAngMotorVelocity(float targetAngMotorVelocity);
    float getTargetAngMotorVelocity() const;
    void setMaxAngMotorForce(float maxAngMotorForce);
    float getMaxAngMotorForce() const;

    float getLinearPos() const;
    float getAngularPos() const;

    /** @~english access for UseFrameOffset
        @~chinese 获取useframeoffset
    */
    bool getUseFrameOffset() const;
    /** @~english set use frame offset
        @~chinese 使用帧偏移
    */
    void setUseFrameOffset(bool frameOffsetOnOff);

    /** @~english set frames for rigid body A and B
        @~chinese 设置刚体A和B的帧
    */
    void setFrames(const cocos2d::Mat4& frameA, const cocos2d::Mat4& frameB);

CC_CONSTRUCTOR_ACCESS:
    Physics3DSliderConstraint()
    {
        _type = ConstraintType::SLIDER;
    }
    virtual ~Physics3DSliderConstraint() {}
};

/**
    It is a special point to point constraint that adds cone and twist axis limits. The x-axis serves as twist axis.
    @~chinese
*/
class CC_DLL Physics3DConeTwistConstraint : public Physics3DConstraint
{
public:
    /** @~english create cone twist constraint
        @~chinese 创建圆锥扭转约束
        rbA rigid body A
        frameA A's local frame
    */
    static Physics3DConeTwistConstraint* create(Physics3DRigidBody* rbA, const cocos2d::Mat4& frameA);
    /** @~english create cone twist constraint
        @~chinese 创建圆锥扭转约束
        rbA rigid body A
        rbB rigid body B
        frameA rigid body A's local frame
        frameB rigid body B's local frame
    */
    static Physics3DConeTwistConstraint* create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Mat4& frameA, const cocos2d::Mat4& frameB);

    /** @~english set limits
        @~chinese 设定限制

        @param swingSpan1 @~english  swing span1 @~chinese 摆span1
        @param swingSpan2 @~english  swing span2 @~chinese 摆span2
        @param twistSpan @~english  twist span @~chinese 扭跨
        @param softness @~english  0->1, recommend ~0.8->1. Describes % of limits where movement is free. Beyond this softness %, the limit is gradually enforced until the "hard" (1.0) limit is reached. @~chinese 0 -> 1，推荐~ 0.8 -> 1。极限运动的自由了。除此之外的柔软性，限制逐步执行直到“硬”（1）达到极限。
        @param biasFactor @~english  0->1?, recommend 0.3 +/-0.3 or so. Strength with which constraint resists zeroth order (angular, not angular velocity) limit violation. @~chinese 0＞1？，推荐0.3 / 0.3左右。力量与约束抵制零阶（角，没有角速度）违反限制。
        @param relaxationFactor @~english  0->1, recommend to stay near 1. the lower the value, the less the constraint will fight velocities which violate the angular limits. @~chinese 0 -> 1，建议在1附近。值越低，越少的约束将打击违反角极限速度。
    */
    void setLimit(float swingSpan1,float swingSpan2,float twistSpan, float softness = 1.f, float biasFactor = 0.3f, float relaxationFactor = 1.0f);

    /** @~english get A's frame
        @~chinese 得到的框架
    */
    cocos2d::Mat4 getAFrame() const;
    /** @~english get B's frame
        @~chinese 得到B的框架
    */
    cocos2d::Mat4 getBFrame() const;

    /** @~english get swing span1
        @~chinese 得到span1摆动
    */
    float getSwingSpan1() const;
    /** @~english get swing span2
        @~chinese 得到span2摆动
    */
    float getSwingSpan2() const;
    /** @~english get twist span
        @~chinese 得到扭跨
    */
    float getTwistSpan() const;
    /** @~english get twist angle
        @~chinese 得到扭角
    */
    float getTwistAngle() const;

    /** @~english set damping
        @~chinese 设置阻尼
    */
    void setDamping(float damping);

    /** @~english enable motor
        @~chinese 使电机
    */
    void enableMotor(bool b);
    /** @~english set max motor impulse
        @~chinese 设置最大电机脉冲
    */
    void setMaxMotorImpulse(float maxMotorImpulse);
    /** @~english set max motor impulse normalize
        @~chinese 设置最大电机脉冲规范
    */
    void setMaxMotorImpulseNormalized(float maxMotorImpulse);
    /** @~english get fix thresh
        @~chinese 得到固定阈值
    */
    float getFixThresh() const;
    /** @~english set fix thresh
        @~chinese 设定固定阈值
    */
    void setFixThresh(float fixThresh);

    /** @~english setMotorTarget
        @~chinese setmotortarget
        @param q @~english  the desired rotation of bodyA wrt bodyB. Note: if q violates the joint limits, the internal target is clamped to avoid conflicting impulses (very bad for stability), also don't forget to enableMotor() @~chinese 关于身体的体内所需的旋转。注意：如果Q侵犯关节限制，内部目标是夹紧避免冲突的冲动（稳定性很差），也别忘了enablemotor()
    */
    void setMotorTarget(const btQuaternion& q);

    /** @~english setMotorTarget, q is the desired rotation of frameA wrt frameB in constraint space
        @~chinese setmotortarget，Q是理想的旋转坐标WRT FRAMEB在约束空间
    */
    void setMotorTargetInConstraintSpace(const btQuaternion& q);

    /** @~english get point for angle
        @~chinese 获取Angle的点
    */
    cocos2d::Vec3 GetPointForAngle(float fAngleInRadians, float fLength) const;

    /** @~english set A and B's frame
        @~chinese 集合A和B的框架
    */
    virtual void setFrames(const cocos2d::Mat4& frameA, const cocos2d::Mat4& frameB);

    /** @~english get A's frame offset
        @~chinese 得到的帧偏移
    */
    cocos2d::Mat4 getFrameOffsetA() const;

    /** @~english get B's frame offset
        @~chinese 得到B的帧偏移
    */
    cocos2d::Mat4 getFrameOffsetB() const;

CC_CONSTRUCTOR_ACCESS:
    Physics3DConeTwistConstraint()
    {
        _type = ConstraintType::CONE_TWIST;
    }
    virtual ~Physics3DConeTwistConstraint() {}
};

/**
    This generic constraint can emulate a variety of standard constraints, by configuring each of the 6 degrees of freedom (dof).
    The first 3 dof axis are linear axis, which represent translation of rigidbodies, and the latter 3 dof axis represent the angular motion.
    Each axis can be either locked, free or limited. All axis are locked by default.
    For each axis:

    Lowerlimit == Upperlimit -> axis is locked.
    Lowerlimit > Upperlimit -> axis is free
    Lowerlimit < Upperlimit -> axis it limited in that range

    @~chinese
*/
class CC_DLL Physics3D6DofConstraint : public Physics3DConstraint
{
public:
    /** @~english create 6 dof constraint
        @~chinese 建立6自由度约束
        @param rbA @~english  rigid body A @~chinese 刚体A
        @param rbB @~english  rigid body B @~chinese 刚体B
        @param frameInA @~english  frame in A's local space @~chinese 在一个局部空间框架
        @param frameInB @~english  frame in B's local space @~chinese 在B的局部空间框架
        @param useLinearReferenceFrameA @~english  use fixed frame A for linear limits @~chinese 使用固定框架的线性范围
    */
    static Physics3D6DofConstraint* create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Mat4& frameInA, const cocos2d::Mat4& frameInB, bool useLinearReferenceFrameA);

    /** @~english create 6 dof constraint
        @~chinese 建立6自由度约束
        @param rbB @~english  rigid body B @~chinese 刚体B
        @param frameInB @~english  frame in B's local space @~chinese 在B的局部空间框架
        @param useLinearReferenceFrameB @~english  use fixed frame B for linear limits @~chinese 使用固定的B帧的线性范围
    */
    static Physics3D6DofConstraint* create(Physics3DRigidBody* rbB, const cocos2d::Mat4& frameInB, bool useLinearReferenceFrameB);

    /** @~english set linear lower limit
        @~chinese 设置线性下限
    */
    void setLinearLowerLimit(const cocos2d::Vec3& linearLower);

    /** @~english get linear lower limit
        @~chinese 得到线性下限
    */
    cocos2d::Vec3 getLinearLowerLimit() const;

    /** @~english set linear upper limit
        @~chinese 设置线性上限
    */
    void setLinearUpperLimit(const cocos2d::Vec3& linearUpper);

    /** @~english get linear upper limit
        @~chinese 得到线性上限
    */
    cocos2d::Vec3 getLinearUpperLimit() const;

    /** @~english set angular lower limit
        @~chinese 设置角下限
    */
    void setAngularLowerLimit(const cocos2d::Vec3& angularLower);

    /** @~english get angular lower limit
        @~chinese 获得角下限
    */
    cocos2d::Vec3 getAngularLowerLimit() const;

    /** @~english set angular upper limit
        @~chinese 设置角上限
    */
    void setAngularUpperLimit(const cocos2d::Vec3& angularUpper);

    /** @~english get angular upper limit
        @~chinese 获得角上限
    */
    cocos2d::Vec3 getAngularUpperLimit() const;

    /** @~english is limited?
        @~chinese 是有限的？
        @param limitIndex @~english  first 3 are linear, next 3 are angular @~chinese 前3个都是线性的，接下来的3角
    */
    bool isLimited(int limitIndex) const;

    /** @~english access for UseFrameOffset
        @~chinese 访问useframeoffset
    */
    bool getUseFrameOffset() const;
    /** @~english set use frame offset
        @~chinese 使用帧偏移
    */
    void setUseFrameOffset(bool frameOffsetOnOff) const;


CC_CONSTRUCTOR_ACCESS:
    Physics3D6DofConstraint()
    {
        _type = ConstraintType::SIX_DOF;
    }
    virtual ~Physics3D6DofConstraint() {}
};

// end of 3d group
/// @}

NS_CC_END

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif // CC_USE_3D_PHYSICS

#endif // __PHYSICS_3D_CONSTRAINT_H__
