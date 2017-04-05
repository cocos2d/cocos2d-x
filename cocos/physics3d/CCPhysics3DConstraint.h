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
 * @addtogroup _3d
 * @{
 */

class Physics3DRigidBody;

/** @brief Physics3DConstraint: Constraint affects the movement of physics object, it usually connect one or two physics object. There are some types of physics constraints. */
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
    /**
     * get the impulse that break the constraint
     */
    float getBreakingImpulse() const;
    
    /**
     * set the impulse that break the constraint
     */
    void setBreakingImpulse(float impulse);
    
    /**
     * is it enabled
     */
    bool isEnabled() const;
    
    /**
     * set enable or not
     */
    void setEnabled(bool enabled);
    
    /**
     * get rigid body a
     */
    Physics3DRigidBody* getBodyA() const { return _bodyA; }
    
    /**
     * get rigid body b
     */
    Physics3DRigidBody* getBodyB() const { return _bodyB; }
    
    /**
     * get constraint type
     */
    ConstraintType getConstraintType() const { return _type; }
    
    /**
     * get user data
     */
    void setUserData(void* userData) { _userData = userData; }
    
    /**
     * get user data
     */
    void* getUserData() const { return _userData; }
    
    /**
     * get override number of solver iterations
     */
    int getOverrideNumSolverIterations() const;
    
    /**
     * override the number of constraint solver iterations used to solve this constraint, -1 will use the default number of iterations, as specified in SolverInfo.m_numIterations
     */
    void setOverrideNumSolverIterations(int overrideNumIterations);
    
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
 * Point to point constraint limits the translation so that the local pivot points of 2 rigidbodies match in worldspace.
 */
class CC_DLL Physics3DPointToPointConstraint : public Physics3DConstraint
{
public:
    /**
     * create point to point constraint, limits the translation of local pivot point of rigid body A
     * @param rbA The rigid body going to be fixed
     * @param pivotPointInA local pivot point in A's local space
     * @return created constraint
     */
    static Physics3DPointToPointConstraint* create(Physics3DRigidBody* rbA, const cocos2d::Vec3& pivotPointInA);
    
    /**
     * create point to point constraint, make the local pivot points of 2 rigid bodies match in worldspace.
     * @param rbA The rigid body A going to be fixed
     * @param rbB The rigid body B going to be fixed
     * @param pivotPointInA local pivot point in A's local space
     * @param pivotPointInB local pivot point in B's local space
     * @return created constraint
     */
    static Physics3DPointToPointConstraint* create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Vec3& pivotPointInA, const cocos2d::Vec3& pivotPointInB);
    
    /**
     * set pivot point in A's local space
     */
    void setPivotPointInA(const cocos2d::Vec3& pivotA);
    
    /**
     * set pivot point in B's local space
     */
    void setPivotPointInB(const cocos2d::Vec3& pivotB);
    
    /**
     * get pivot point in A's local space
     */
    cocos2d::Vec3 getPivotPointInA() const;
    
    /**
     * get pivot point in B's local space
     */
    cocos2d::Vec3 getPivotPointInB() const;
    
CC_CONSTRUCTOR_ACCESS:
    Physics3DPointToPointConstraint();
    virtual ~Physics3DPointToPointConstraint();
    bool init(Physics3DRigidBody* rbA, const cocos2d::Vec3& pivotPointInA);
    bool init(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Vec3& pivotPointInA, const cocos2d::Vec3& pivotPointInB);
    
};

/**
 * Hinge constraint restricts two additional angular degrees of freedom, so the body can only rotate around one axis, the hinge axis. This can be useful to represent doors or wheels rotating around one axis.
 * hinge constraint between two rigidbodies each with a pivotpoint that describes the axis location in local space
 */
class CC_DLL Physics3DHingeConstraint : public Physics3DConstraint
{
public:
    /**
     * create hinge constraint
     * @param rbA rigid body A
     * @param rbAFrame rigid body A's frame
     * @param useReferenceFrameA use frame A as reference
     */
    static Physics3DHingeConstraint* create(Physics3DRigidBody* rbA, const cocos2d::Mat4& rbAFrame, bool useReferenceFrameA = false);
    
    /**
     * create hinge constraint
     * @param rbA rigid body A
     * @param pivotInA pivot in rigid body A's local space
     * @param axisInA axis in rigid body A's local space
     * @param useReferenceFrameA use frame A as reference
     */
    static Physics3DHingeConstraint* create(Physics3DRigidBody* rbA, const cocos2d::Vec3& pivotInA, const cocos2d::Vec3& axisInA, bool useReferenceFrameA = false);

    /**
     * create hinge constraint
     * @param rbA rigid body A
     * @param rbB rigid body B
     * @param pivotInA pivot point in A's local space
     * @param pivotInB pivot point in B's local space
     * @param axisInA axis in A's local space
     * @param axisInB axis in B's local space
     * @param useReferenceFrameA use frame A as reference
     */
    static Physics3DHingeConstraint* create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Vec3& pivotInA,const cocos2d::Vec3& pivotInB, cocos2d::Vec3& axisInA, cocos2d::Vec3& axisInB, bool useReferenceFrameA = false);
    
    /**
     * create hinge constraint
     * @param rbA rigid body A
     * @param rbB rigid body B
     * @param rbAFrame rigid body A's frame
     * @param rbBFrame rigid body B's frame
     * @param useReferenceFrameA use frame A as reference
     */
    static Physics3DHingeConstraint* create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Mat4& rbAFrame, const cocos2d::Mat4& rbBFrame, bool useReferenceFrameA = false);
    
    /**
     * get rigid body A's frame offset
     */
    cocos2d::Mat4 getFrameOffsetA() const;
    
    /**
     * get rigid body B's frame offset
     */
    cocos2d::Mat4 getFrameOffsetB() const;
    
    /**
     * set frames for rigid body A and B
     */
    void setFrames(const cocos2d::Mat4& frameA, const cocos2d::Mat4& frameB);
    
    /**
     * set angular only
     */
    void setAngularOnly(bool angularOnly);
    
    /** enable angular motor */
    void enableAngularMotor(bool enableMotor, float targetVelocity, float maxMotorImpulse);
    
    // extra motor API, including ability to set a target rotation (as opposed to angular velocity)
    // note: setMotorTarget sets angular velocity under the hood, so you must call it every tick to
    //       maintain a given angular target.
    void enableMotor(bool enableMotor);
    /** set max motor impulse */
    void setMaxMotorImpulse(float maxMotorImpulse);
    /**
     * set motor target
     */
    void setMotorTarget(const cocos2d::Quaternion& qAinB, float dt);
    /** set motor target */
    void setMotorTarget(float targetAngle, float dt);
    
    /** set limit */
    void setLimit(float low, float high, float _softness = 0.9f, float _biasFactor = 0.3f, float _relaxationFactor = 1.0f);
    /**set axis*/
    void setAxis(const cocos2d::Vec3& axisInA);
    /**get lower limit*/
    float getLowerLimit() const;
    /**get upper limit*/
    float getUpperLimit() const;
    /**get hinge angle*/
    float getHingeAngle() const;
    /**get hinge angle*/
    float getHingeAngle(const cocos2d::Mat4& transA, const cocos2d::Mat4& transB);
    
    /**get A's frame */
    cocos2d::Mat4 getAFrame() const;
    /**get B's frame*/
    cocos2d::Mat4 getBFrame() const;
    /**get angular only*/
    bool getAngularOnly() const;
    /**get enable angular motor*/
    bool getEnableAngularMotor() const;
    /**get motor target velocity*/
    float getMotorTargetVelosity() const;
    /**get max motor impulse*/
    float getMaxMotorImpulse() const;
    
    /** access for UseFrameOffset*/
    bool getUseFrameOffset() const;
    /**set use frame offset*/
    void setUseFrameOffset(bool frameOffsetOnOff);
    
CC_CONSTRUCTOR_ACCESS:
    Physics3DHingeConstraint()
    {
        _type = ConstraintType::HINGE;
    }
    virtual ~Physics3DHingeConstraint(){}
};

/**
 * It allows the body to rotate around x axis and translate along this axis.
 * softness, restitution and damping for different cases
 * DirLin - moving inside linear limits
 * LimLin - hitting linear limit
 * DirAng - moving inside angular limits
 * LimAng - hitting angular limit
 * OrthoLin, OrthoAng - against constraint axis
 */
class CC_DLL Physics3DSliderConstraint : public Physics3DConstraint
{
public:
    /**
     * create slider constraint
     * @param rbA rigid body A
     * @param rbB rigid body B
     * @param frameInA frame in A's local space
     * @param frameInB frame in B's local space
     * @param useLinearReferenceFrameA use fixed frame A for linear limits
     */
    static Physics3DSliderConstraint* create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Mat4& frameInA, const cocos2d::Mat4& frameInB ,bool useLinearReferenceFrameA);
    
    /**get A's frame offset*/
    cocos2d::Mat4 getFrameOffsetA() const;
    /**get B's frame offset*/
    cocos2d::Mat4 getFrameOffsetB() const;
    /**get lower linear limit*/
    float getLowerLinLimit() const;
    /**set lower linear limit*/
    void setLowerLinLimit(float lowerLimit);
    /**get upper linear limit*/
    float getUpperLinLimit() const;
    /**set upper linear limit*/
    void setUpperLinLimit(float upperLimit);
    /**get lower angular limit*/
    float getLowerAngLimit() const;
    /**set lower angular limit*/
    void setLowerAngLimit(float lowerLimit);
    /**get upper angular limit*/
    float getUpperAngLimit() const;
    /**set upper angular limit*/
    void setUpperAngLimit(float upperLimit);
    /**use A's frame as linear reference*/
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
    
    /** access for UseFrameOffset*/
    bool getUseFrameOffset() const;
    /**set use frame offset*/
    void setUseFrameOffset(bool frameOffsetOnOff);
    
    /**set frames for rigid body A and B*/
    void setFrames(const cocos2d::Mat4& frameA, const cocos2d::Mat4& frameB);
    
CC_CONSTRUCTOR_ACCESS:
    Physics3DSliderConstraint()
    {
        _type = ConstraintType::SLIDER;
    }
    virtual ~Physics3DSliderConstraint(){}
};

/**
 * It is a special point to point constraint that adds cone and twist axis limits. The x-axis serves as twist axis.
 */
class CC_DLL Physics3DConeTwistConstraint : public Physics3DConstraint
{
public:
    /**
     * create cone twist constraint 
     * rbA rigid body A
     * frameA A's local frame
     */
    static Physics3DConeTwistConstraint* create(Physics3DRigidBody* rbA, const cocos2d::Mat4& frameA);
    /**
     * create cone twist constraint
     * rbA rigid body A
     * rbB rigid body B
     * frameA rigid body A's local frame
     * frameB rigid body B's local frame
     */
    static Physics3DConeTwistConstraint* create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Mat4& frameA, const cocos2d::Mat4& frameB);
    
    /**
     * set limits
     * @param swingSpan1 swing span1
     * @param swingSpan2 swing span2
     * @param twistSpan twist span
     * @param softness 0->1, recommend ~0.8->1. Describes % of limits where movement is free. Beyond this softness %, the limit is gradually enforced until the "hard" (1.0) limit is reached.
     * @param biasFactor 0->1?, recommend 0.3 +/-0.3 or so. Strength with which constraint resists zeroth order (angular, not angular velocity) limit violation.
     * @param relaxationFactor 0->1, recommend to stay near 1. the lower the value, the less the constraint will fight velocities which violate the angular limits.
     */
    void setLimit(float swingSpan1,float swingSpan2,float twistSpan, float softness = 1.f, float biasFactor = 0.3f, float relaxationFactor = 1.0f);
    
    /**get A's frame*/
    cocos2d::Mat4 getAFrame() const;
    /**get B's frame*/
    cocos2d::Mat4 getBFrame() const;
    
    /**get swing span1*/
    float getSwingSpan1() const;
    /**get swing span2*/
    float getSwingSpan2() const;
    /**get twist span*/
    float getTwistSpan() const;
    /**get twist angle*/
    float getTwistAngle() const;
    
    /**set damping*/
    void setDamping(float damping);
    
    /**enable motor*/
    void enableMotor(bool b);
    /**set max motor impulse*/
    void setMaxMotorImpulse(float maxMotorImpulse);
    /**set max motor impulse normalize*/
    void setMaxMotorImpulseNormalized(float maxMotorImpulse);
    /**get fix thresh*/
    float getFixThresh() const;
    /**set fix thresh*/
    void setFixThresh(float fixThresh);
    
    /**
     * setMotorTarget
     * @param q the desired rotation of bodyA wrt bodyB. Note: if q violates the joint limits, the internal target is clamped to avoid conflicting impulses (very bad for stability), also don't forget to enableMotor()
     */
    void setMotorTarget(const btQuaternion &q);
    
    /** setMotorTarget, q is the desired rotation of frameA wrt frameB in constraint space*/
    void setMotorTargetInConstraintSpace(const btQuaternion &q);
    
    /**get point for angle*/
    cocos2d::Vec3 GetPointForAngle(float fAngleInRadians, float fLength) const;
    
    /**set A and B's frame*/
    virtual void setFrames(const cocos2d::Mat4& frameA, const cocos2d::Mat4& frameB);
    
    /**get A's frame offset*/
    cocos2d::Mat4 getFrameOffsetA() const;
    
    /**get B's frame offset*/
    cocos2d::Mat4 getFrameOffsetB() const;
    
CC_CONSTRUCTOR_ACCESS:
    Physics3DConeTwistConstraint()
    {
        _type = ConstraintType::CONE_TWIST;
    }
    virtual ~Physics3DConeTwistConstraint(){}
};

/**
 * This generic constraint can emulate a variety of standard constraints, by configuring each of the 6 degrees of freedom (dof). 
 * The first 3 dof axis are linear axis, which represent translation of rigidbodies, and the latter 3 dof axis represent the angular motion. 
 * Each axis can be either locked, free or limited. All axis are locked by default.
 * For each axis:
 * Lowerlimit == Upperlimit -> axis is locked.
 * Lowerlimit > Upperlimit -> axis is free
 * Lowerlimit < Upperlimit -> axis it limited in that range
 */
class CC_DLL Physics3D6DofConstraint : public Physics3DConstraint
{
public:
    /**
     * create 6 dof constraint
     * @param rbA rigid body A
     * @param rbB rigid body B
     * @param frameInA frame in A's local space
     * @param frameInB frame in B's local space
     * @param useLinearReferenceFrameA use fixed frame A for linear limits
     */
    static Physics3D6DofConstraint* create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Mat4& frameInA, const cocos2d::Mat4& frameInB, bool useLinearReferenceFrameA);
    
    /**
     * create 6 dof constraint
     * @param rbB rigid body B
     * @param frameInB frame in B's local space
     * @param useLinearReferenceFrameB use fixed frame B for linear limits
     */
    static Physics3D6DofConstraint* create(Physics3DRigidBody* rbB, const cocos2d::Mat4& frameInB, bool useLinearReferenceFrameB);
    
    /**set linear lower limit*/
    void setLinearLowerLimit(const cocos2d::Vec3& linearLower);
    
    /**get linear lower limit*/
    cocos2d::Vec3 getLinearLowerLimit() const;
    
    /**set linear upper limit*/
    void setLinearUpperLimit(const cocos2d::Vec3& linearUpper);
    
    /**get linear upper limit*/
    cocos2d::Vec3 getLinearUpperLimit() const;
    
    /**set angular lower limit*/
    void setAngularLowerLimit(const cocos2d::Vec3& angularLower);
    
    /**get angular lower limit*/
    cocos2d::Vec3 getAngularLowerLimit() const;
    
    /**set angular upper limit*/
    void setAngularUpperLimit(const cocos2d::Vec3& angularUpper);
    
    /**get angular upper limit*/
    cocos2d::Vec3 getAngularUpperLimit() const;
    
    /** 
     * is limited?
     * @param limitIndex first 3 are linear, next 3 are angular
     */
    bool isLimited(int limitIndex) const;
    
    /** access for UseFrameOffset*/
    bool getUseFrameOffset() const;
    /**set use frame offset*/
    void setUseFrameOffset(bool frameOffsetOnOff) const;

    
CC_CONSTRUCTOR_ACCESS:
    Physics3D6DofConstraint()
    {
        _type = ConstraintType::SIX_DOF;
    }
    virtual ~Physics3D6DofConstraint(){}
};

// end of 3d group
/// @}

NS_CC_END

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif // CC_USE_3D_PHYSICS

#endif // __PHYSICS_3D_CONSTRAINT_H__
