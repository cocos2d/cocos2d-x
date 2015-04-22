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

#ifndef __PHYSICS_3D_CONSTRAINT_H__
#define __PHYSICS_3D_CONSTRAINT_H__

#include "math/CCMath.h"
#include "base/CCRef.h"
#include "extensions/ExtensionMacros.h"
#include "extensions/ExtensionExport.h"

#if (CC_ENABLE_BULLET_INTEGRATION)

class btTypedConstraint;

NS_CC_EXT_BEGIN

class Physics3DRigidBody;

class CC_EX_DLL Physics3DConstraint : public Ref
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
    float getBreakingImpulse() const;
    
    void setBreakingImpulse(float impulse);
    
    bool isEnabled() const;
    
    void setEnabled(bool enabled);
    
    Physics3DRigidBody* getBodyA() const { return _bodyA; }
    
    Physics3DRigidBody* getBodyB() const { return _bodyB; }
    
    ConstraintType getConstraintType() const { return _type; }
    
    void setUserData(void* userData) { _userData = userData; }
    
    void* getUserData() const { return _userData; }
    
    int	getOverrideNumSolverIterations() const;
    
	///override the number of constraint solver iterations used to solve this constraint
	///-1 will use the default number of iterations, as specified in SolverInfo.m_numIterations
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
 * Point to point constraint limits the translation so that the local pivot points of 2 rigidbodies match in worldspace.
 */
class CC_EX_DLL Physics3DPointToPointConstraint : public Physics3DConstraint
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
    
    void	setPivotPointInA(const cocos2d::Vec3& pivotA);
    
	void	setPivotPointInB(const cocos2d::Vec3&& pivotB);
    
	cocos2d::Vec3 getPivotPointInA() const;
    
	cocos2d::Vec3 getPivotPointInB() const;
    
CC_CONSTRUCTOR_ACCESS:
    Physics3DPointToPointConstraint();
    virtual ~Physics3DPointToPointConstraint();
    
protected:
    bool init(Physics3DRigidBody* rbA, const cocos2d::Vec3& pivotPointInA);
    bool init(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Vec3& pivotPointInA, const cocos2d::Vec3& pivotPointInB);
    
};

/**
 * Hinge constraint restricts two additional angular degrees of freedom, so the body can only rotate around one axis, the hinge axis. This can be useful to represent doors or wheels rotating around one axis.
 * hinge constraint between two rigidbodies each with a pivotpoint that descibes the axis location in local space
 */
class CC_EX_DLL Physics3DHingeConstraint : public Physics3DConstraint
{
public:
    static Physics3DHingeConstraint* create(Physics3DRigidBody* rbA, const cocos2d::Mat4& rbAFrame, bool useReferenceFrameA = false);
    
    static Physics3DHingeConstraint* create(Physics3DRigidBody* rbA, const cocos2d::Vec3& pivotInA, const cocos2d::Vec3& axisInA, bool useReferenceFrameA = false);

    static Physics3DHingeConstraint* create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Vec3& pivotInA,const cocos2d::Vec3& pivotInB, cocos2d::Vec3& axisInA, cocos2d::Vec3& axisInB, bool useReferenceFrameA = false);
    
    static Physics3DHingeConstraint* create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Mat4& rbAFrame, const cocos2d::Mat4& rbBFrame, bool useReferenceFrameA = false);
    
    
    cocos2d::Mat4 getFrameOffsetA() const;
    
	cocos2d::Mat4 getFrameOffsetB() const;
    
	void setFrames(const cocos2d::Mat4& frameA, const cocos2d::Mat4& frameB);
	
	void	setAngularOnly(bool angularOnly);
    
	void	enableAngularMotor(bool enableMotor, float targetVelocity, float maxMotorImpulse);
    
	// extra motor API, including ability to set a target rotation (as opposed to angular velocity)
	// note: setMotorTarget sets angular velocity under the hood, so you must call it every tick to
	//       maintain a given angular target.
	void enableMotor(bool enableMotor);
	void setMaxMotorImpulse(float maxMotorImpulse);
	void setMotorTarget(const cocos2d::Quaternion& qAinB, float dt); // qAinB is rotation of body A wrt body B.
	void setMotorTarget(float targetAngle, float dt);
    
    
	void	setLimit(float low, float high, float _softness = 0.9f, float _biasFactor = 0.3f, float _relaxationFactor = 1.0f);
    
	void	setAxis(const cocos2d::Vec3& axisInA);
    
	float	getLowerLimit() const;
    
	float	getUpperLimit() const;
    
	float getHingeAngle();
    
	float getHingeAngle(const cocos2d::Mat4& transA, const cocos2d::Mat4& transB);
    
	void testLimit(const cocos2d::Mat4& transA,const cocos2d::Mat4& transB);
    
	cocos2d::Mat4 getAFrame();
	cocos2d::Mat4 getBFrame();
    
	bool getAngularOnly();
	bool getEnableAngularMotor();
	float getMotorTargetVelosity();
	float getMaxMotorImpulse();
    
	// access for UseFrameOffset
	bool getUseFrameOffset();
	void setUseFrameOffset(bool frameOffsetOnOff);
    
CC_CONSTRUCTOR_ACCESS:
    Physics3DHingeConstraint()
    {
        _type = ConstraintType::HINGE;
    }
    virtual ~Physics3DHingeConstraint(){}
};

/**
 * It allows the body to rotate around one axis and translate along this axis.
 */
class CC_EX_DLL Physics3DSliderConstraint : public Physics3DConstraint
{
public:
    /**
     * slide along x axis
     */
    static Physics3DSliderConstraint* create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Mat4& frameInA, const cocos2d::Mat4& frameInB ,bool useLinearReferenceFrameA);
    
    cocos2d::Mat4 getFrameOffsetA() const;
    cocos2d::Mat4 getFrameOffsetB() const;
    float getLowerLinLimit();
    void setLowerLinLimit(float lowerLimit);
    float getUpperLinLimit();
    void setUpperLinLimit(float upperLimit);
    float getLowerAngLimit();
    void setLowerAngLimit(float lowerLimit);
    float getUpperAngLimit();
    void setUpperAngLimit(float upperLimit);
	bool getUseLinearReferenceFrameA();
	float getSoftnessDirLin();
	float getRestitutionDirLin();
	float getDampingDirLin();
	float getSoftnessDirAng();
	float getRestitutionDirAng();
	float getDampingDirAng();
	float getSoftnessLimLin();
	float getRestitutionLimLin();
	float getDampingLimLin();
	float getSoftnessLimAng();
	float getRestitutionLimAng();
	float getDampingLimAng();
	float getSoftnessOrthoLin();
	float getRestitutionOrthoLin();
	float getDampingOrthoLin();
	float getSoftnessOrthoAng();
	float getRestitutionOrthoAng();
	float getDampingOrthoAng();
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
	bool getPoweredLinMotor();
	void setTargetLinMotorVelocity(float targetLinMotorVelocity);
	float getTargetLinMotorVelocity();
	void setMaxLinMotorForce(float maxLinMotorForce);
	float getMaxLinMotorForce();
	void setPoweredAngMotor(bool onOff);
	bool getPoweredAngMotor();
	void setTargetAngMotorVelocity(float targetAngMotorVelocity);
	float getTargetAngMotorVelocity();
	void setMaxAngMotorForce(float maxAngMotorForce);
	float getMaxAngMotorForce();
    
	float getLinearPos() const;
	float getAngularPos() const;
	
	// access for UseFrameOffset
	bool getUseFrameOffset();
	void setUseFrameOffset(bool frameOffsetOnOff);
    
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
class CC_EX_DLL Physics3DConeTwistConstraint : public Physics3DConstraint
{
public:
    static Physics3DConeTwistConstraint* create(Physics3DRigidBody* rbA, const cocos2d::Mat4& frameA);
    static Physics3DConeTwistConstraint* create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Mat4& frameA, const cocos2d::Mat4& frameB);
    
    // setLimit(), a few notes:
	// _softness:
	//		0->1, recommend ~0.8->1.
	//		describes % of limits where movement is free.
	//		beyond this softness %, the limit is gradually enforced until the "hard" (1.0) limit is reached.
	// _biasFactor:
	//		0->1?, recommend 0.3 +/-0.3 or so.
	//		strength with which constraint resists zeroth order (angular, not angular velocity) limit violation.
	// __relaxationFactor:
	//		0->1, recommend to stay near 1.
	//		the lower the value, the less the constraint will fight velocities which violate the angular limits.
	void	setLimit(float swingSpan1,float swingSpan2,float twistSpan, float softness = 1.f, float biasFactor = 0.3f, float relaxationFactor = 1.0f);
    
	cocos2d::Mat4 getAFrame();
	cocos2d::Mat4 getBFrame();
    
	float getSwingSpan1();
	float getSwingSpan2();
	float getTwistSpan();
	float getTwistAngle();
    
	void setDamping(float damping);
    
	void enableMotor(bool b);
	void setMaxMotorImpulse(float maxMotorImpulse);
	void setMaxMotorImpulseNormalized(float maxMotorImpulse);
    
	float getFixThresh();
	void setFixThresh(float fixThresh);
    
	// setMotorTarget:
	// q: the desired rotation of bodyA wrt bodyB.
	// note: if q violates the joint limits, the internal target is clamped to avoid conflicting impulses (very bad for stability)
	// note: don't forget to enableMotor()
	void setMotorTarget(const btQuaternion &q);
    
	// same as above, but q is the desired rotation of frameA wrt frameB in constraint space
	void setMotorTargetInConstraintSpace(const btQuaternion &q);
    
	cocos2d::Vec3 GetPointForAngle(float fAngleInRadians, float fLength) const;
    
	virtual void setFrames(const cocos2d::Mat4& frameA, const cocos2d::Mat4& frameB);
    
	cocos2d::Mat4 getFrameOffsetA() const;
    
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
class CC_EX_DLL Physics3D6DofConstraint : public Physics3DConstraint
{
public:
    static Physics3D6DofConstraint* create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Mat4& frameInA, const cocos2d::Mat4& frameInB, bool useLinearReferenceFrameA);
    
    static Physics3D6DofConstraint* create(Physics3DRigidBody* rbB, const cocos2d::Mat4& frameInB, bool useLinearReferenceFrameB);
    
    void	setLinearLowerLimit(const cocos2d::Vec3& linearLower);
    
	cocos2d::Vec3	getLinearLowerLimit();
    
	void	setLinearUpperLimit(const cocos2d::Vec3& linearUpper);
    
	cocos2d::Vec3	getLinearUpperLimit();
    
    void	setAngularLowerLimit(const cocos2d::Vec3& angularLower);
    
	cocos2d::Vec3	getAngularLowerLimit();
    
    void	setAngularUpperLimit(const cocos2d::Vec3& angularUpper);
    
	cocos2d::Vec3	getAngularUpperLimit();
    
	//! Test limit
	/*!
     - free means upper < lower,
     - locked means upper == lower
     - limited means upper > lower
     - limitIndex: first 3 are linear, next 3 are angular
     */
    bool	isLimited(int limitIndex);
    
	// access for UseFrameOffset
	bool getUseFrameOffset();
	void setUseFrameOffset(bool frameOffsetOnOff);

    
CC_CONSTRUCTOR_ACCESS:
    Physics3D6DofConstraint()
    {
        _type = ConstraintType::SIX_DOF;
    }
    virtual ~Physics3D6DofConstraint(){}
};

NS_CC_EXT_END

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif // __PHYSICS_3D_CONSTRAINT_H__
