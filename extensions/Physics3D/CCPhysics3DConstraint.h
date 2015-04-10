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
 */
class CC_EX_DLL Physics3DHingeConstraint : public Physics3DConstraint
{
public:
    //static Physics3DHingeConstraint* create();
    
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
    
    
CC_CONSTRUCTOR_ACCESS:
    Physics3DConeTwistConstraint()
    {
        _type = ConstraintType::CONE_TWIST;
    }
    virtual ~Physics3DConeTwistConstraint(){}
};

/**
 * It is a special point to point constraint that adds cone and twist axis limits. The x-axis serves as twist axis.
 */
class CC_EX_DLL Physics3D6DofConstraint : public Physics3DConstraint
{
public:
    
    
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
