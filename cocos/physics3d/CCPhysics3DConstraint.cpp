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

#include "CCPhysics3D.h"

#if CC_USE_3D_PHYSICS

#if (CC_ENABLE_BULLET_INTEGRATION)

NS_CC_BEGIN

Physics3DConstraint::Physics3DConstraint()
: _bodyA(nullptr)
, _bodyB(nullptr)
, _constraint(nullptr)
, _type(Physics3DConstraint::ConstraintType::UNKNOWN)
, _userData(nullptr)
{
    
}

Physics3DConstraint::~Physics3DConstraint()
{
    CC_SAFE_RELEASE(_bodyA);
    CC_SAFE_RELEASE(_bodyB);
    CC_SAFE_DELETE(_constraint);
}

float Physics3DConstraint::getBreakingImpulse() const
{
    return _constraint->getBreakingImpulseThreshold();
}

void Physics3DConstraint::setBreakingImpulse(float impulse)
{
    _constraint->setBreakingImpulseThreshold(impulse);
}

bool Physics3DConstraint::isEnabled() const
{
    return _constraint->isEnabled();
}

void Physics3DConstraint::setEnabled(bool enabled)
{
    return _constraint->setEnabled(enabled);
}

int	Physics3DConstraint::getOverrideNumSolverIterations() const
{
    return _constraint->getOverrideNumSolverIterations();
}

///override the number of constraint solver iterations used to solve this constraint
///-1 will use the default number of iterations, as specified in SolverInfo.m_numIterations
void Physics3DConstraint::setOverrideNumSolverIterations(int overideNumIterations)
{
    _constraint->setOverrideNumSolverIterations(overideNumIterations);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Physics3DPointToPointConstraint* Physics3DPointToPointConstraint::create(Physics3DRigidBody* rbA, const cocos2d::Vec3& pivotPointInA)
{
    auto ret = new (std::nothrow) Physics3DPointToPointConstraint();
    if (ret && ret->init(rbA, pivotPointInA))
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return ret;
}


Physics3DPointToPointConstraint* Physics3DPointToPointConstraint::create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Vec3& pivotPointInA, const cocos2d::Vec3& pivotPointInB)
{
    auto ret = new (std::nothrow) Physics3DPointToPointConstraint();
    if (ret && ret->init(rbA, rbB, pivotPointInA, pivotPointInB))
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return ret;
}

bool Physics3DPointToPointConstraint::init(Physics3DRigidBody* rbA, const cocos2d::Vec3& pivotPointInA)
{
    
    _constraint = new btPoint2PointConstraint(*rbA->getRigidBody(), convertVec3TobtVector3(pivotPointInA));
    _bodyA = rbA;
    _bodyA->retain();
    
    return true;
}

bool Physics3DPointToPointConstraint::init(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Vec3& pivotPointInA, const cocos2d::Vec3& pivotPointInB)
{
    _constraint = new btPoint2PointConstraint(*rbA->getRigidBody(), *rbB->getRigidBody(), convertVec3TobtVector3(pivotPointInA), convertVec3TobtVector3(pivotPointInB));
    _bodyA = rbA;
    _bodyB = rbB;
    _bodyA->retain();
    _bodyB->retain();
    
    return true;
}

void	Physics3DPointToPointConstraint::setPivotPointInA(const cocos2d::Vec3& pivotA)
{
    auto point = convertVec3TobtVector3(pivotA);
    static_cast<btPoint2PointConstraint*>(_constraint)->setPivotA(point);
}

void	Physics3DPointToPointConstraint::setPivotPointInB(const cocos2d::Vec3& pivotB)
{
    auto point = convertVec3TobtVector3(pivotB);
    static_cast<btPoint2PointConstraint*>(_constraint)->setPivotB(point);
}

cocos2d::Vec3 Physics3DPointToPointConstraint::getPivotPointInA() const
{
    const auto& point = static_cast<btPoint2PointConstraint*>(_constraint)->getPivotInA();
    return convertbtVector3ToVec3(point);
}

cocos2d::Vec3 Physics3DPointToPointConstraint::getPivotPointInB() const
{
    const auto& point = static_cast<btPoint2PointConstraint*>(_constraint)->getPivotInB();
    return convertbtVector3ToVec3(point);
}

Physics3DPointToPointConstraint::Physics3DPointToPointConstraint()
{
    _type = Physics3DConstraint::ConstraintType::POINT_TO_POINT;
}

Physics3DPointToPointConstraint::~Physics3DPointToPointConstraint()
{
    
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Physics3DHingeConstraint* Physics3DHingeConstraint::create(Physics3DRigidBody* rbA, const cocos2d::Mat4& rbAFrame, bool useReferenceFrameA)
{
    auto ret = new (std::nothrow) Physics3DHingeConstraint();
    ret->_constraint = new btHingeConstraint(*rbA->getRigidBody(), convertMat4TobtTransform(rbAFrame), useReferenceFrameA);
    ret->_bodyA = rbA;
    rbA->retain();
    
    ret->autorelease();
    return ret;
}

Physics3DHingeConstraint* Physics3DHingeConstraint::create(Physics3DRigidBody* rbA, const cocos2d::Vec3& pivotInA, const cocos2d::Vec3& axisInA, bool useReferenceFrameA)
{
    auto ret = new (std::nothrow) Physics3DHingeConstraint();
    ret->_constraint = new btHingeConstraint(*rbA->getRigidBody(), convertVec3TobtVector3(pivotInA), convertVec3TobtVector3(axisInA), useReferenceFrameA);
    ret->_bodyA = rbA;
    rbA->retain();
    
    ret->autorelease();
    return ret;
}

Physics3DHingeConstraint* Physics3DHingeConstraint::create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Vec3& pivotInA,const cocos2d::Vec3& pivotInB, cocos2d::Vec3& axisInA, cocos2d::Vec3& axisInB, bool useReferenceFrameA)
{
    auto ret = new (std::nothrow) Physics3DHingeConstraint();
    ret->_constraint = new btHingeConstraint(*rbA->getRigidBody(), *rbB->getRigidBody(), convertVec3TobtVector3(pivotInA), convertVec3TobtVector3(pivotInB), convertVec3TobtVector3(axisInA), convertVec3TobtVector3(axisInB), useReferenceFrameA);
    ret->_bodyA = rbA;
    rbA->retain();
    ret->_bodyB = rbB;
    rbB->retain();
    
    ret->autorelease();
    return ret;
}

Physics3DHingeConstraint* Physics3DHingeConstraint::create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Mat4& rbAFrame, const cocos2d::Mat4& rbBFrame, bool useReferenceFrameA)
{
    auto ret = new (std::nothrow) Physics3DHingeConstraint();
    ret->_constraint = new btHingeConstraint(*rbA->getRigidBody(), *rbB->getRigidBody(), convertMat4TobtTransform(rbAFrame), convertMat4TobtTransform(rbBFrame), useReferenceFrameA);
    ret->_bodyA = rbA;
    rbA->retain();
    ret->_bodyB = rbB;
    rbB->retain();
    
    ret->autorelease();
    return ret;
}

cocos2d::Mat4 Physics3DHingeConstraint::getFrameOffsetA() const
{
    const auto& transform = static_cast<btHingeConstraint*>(_constraint)->getFrameOffsetA();
    return convertbtTransformToMat4(transform);
}

cocos2d::Mat4 Physics3DHingeConstraint::getFrameOffsetB() const
{
    const auto& transform = static_cast<btHingeConstraint*>(_constraint)->getFrameOffsetB();
    return convertbtTransformToMat4(transform);
}

void Physics3DHingeConstraint::setFrames(const cocos2d::Mat4& frameA, const cocos2d::Mat4& frameB)
{
    auto transformA = convertMat4TobtTransform(frameA);
    auto transformB = convertMat4TobtTransform(frameB);
    static_cast<btHingeConstraint*>(_constraint)->setFrames(transformA, transformB);
}

void	Physics3DHingeConstraint::setAngularOnly(bool angularOnly)
{
    static_cast<btHingeConstraint*>(_constraint)->setAngularOnly(angularOnly);
}

void	Physics3DHingeConstraint::enableAngularMotor(bool enableMotor, float targetVelocity, float maxMotorImpulse)
{
    static_cast<btHingeConstraint*>(_constraint)->enableAngularMotor(enableMotor, targetVelocity, maxMotorImpulse);
}

void Physics3DHingeConstraint::enableMotor(bool enableMotor)
{
    static_cast<btHingeConstraint*>(_constraint)->enableMotor(enableMotor);
}
void Physics3DHingeConstraint::setMaxMotorImpulse(float maxMotorImpulse)
{
    static_cast<btHingeConstraint*>(_constraint)->setMaxMotorImpulse(maxMotorImpulse);
}
void Physics3DHingeConstraint::setMotorTarget(const cocos2d::Quaternion& qAinB, float dt)
{
    static_cast<btHingeConstraint*>(_constraint)->setMotorTarget(convertQuatTobtQuat(qAinB), dt);
}
void Physics3DHingeConstraint::setMotorTarget(float targetAngle, float dt)
{
    static_cast<btHingeConstraint*>(_constraint)->setMotorTarget(targetAngle, dt);
}


void	Physics3DHingeConstraint::setLimit(float low, float high, float softness, float biasFactor, float relaxationFactor)
{
    static_cast<btHingeConstraint*>(_constraint)->setLimit(low, high, softness, biasFactor, relaxationFactor);
}

void	Physics3DHingeConstraint::setAxis(const cocos2d::Vec3& axisInA)
{
    auto axis = convertVec3TobtVector3(axisInA);
    static_cast<btHingeConstraint*>(_constraint)->setAxis(axis);
}

float	Physics3DHingeConstraint::getLowerLimit() const
{
    return static_cast<btHingeConstraint*>(_constraint)->getLowerLimit();
}

float	Physics3DHingeConstraint::getUpperLimit() const
{
    return static_cast<btHingeConstraint*>(_constraint)->getUpperLimit();
}

float Physics3DHingeConstraint::getHingeAngle() const
{
    return static_cast<btHingeConstraint*>(_constraint)->getHingeAngle();
}

float Physics3DHingeConstraint::getHingeAngle(const cocos2d::Mat4& transA, const cocos2d::Mat4& transB)
{
    auto btTransA = convertMat4TobtTransform(transA);
    auto btTransB = convertMat4TobtTransform(transB);
    return static_cast<btHingeConstraint*>(_constraint)->getHingeAngle(btTransA, btTransB);
}

cocos2d::Mat4 Physics3DHingeConstraint::getAFrame() const
{
    const auto& trans = static_cast<btHingeConstraint*>(_constraint)->getAFrame();
    return convertbtTransformToMat4(trans);
}
cocos2d::Mat4 Physics3DHingeConstraint::getBFrame() const
{
    const auto& trans = static_cast<btHingeConstraint*>(_constraint)->getBFrame();
    return convertbtTransformToMat4(trans);
}

bool Physics3DHingeConstraint::getAngularOnly() const
{
    return static_cast<btHingeConstraint*>(_constraint)->getAngularOnly();
}
bool Physics3DHingeConstraint::getEnableAngularMotor() const
{
    return static_cast<btHingeConstraint*>(_constraint)->getEnableAngularMotor();
}
float Physics3DHingeConstraint::getMotorTargetVelosity() const
{
    return static_cast<btHingeConstraint*>(_constraint)->getMotorTargetVelosity();
}
float Physics3DHingeConstraint::getMaxMotorImpulse() const
{
    return static_cast<btHingeConstraint*>(_constraint)->getMaxMotorImpulse();
}

bool Physics3DHingeConstraint::getUseFrameOffset() const
{
    return static_cast<btHingeConstraint*>(_constraint)->getUseFrameOffset();
}
void Physics3DHingeConstraint::setUseFrameOffset(bool frameOffsetOnOff)
{
    static_cast<btHingeConstraint*>(_constraint)->setUseFrameOffset(frameOffsetOnOff);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Physics3DSliderConstraint* Physics3DSliderConstraint::create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Mat4& frameInA, const cocos2d::Mat4& frameInB ,bool useLinearReferenceFrameA)
{
    auto ret = new (std::nothrow) Physics3DSliderConstraint();
    ret->_bodyA = rbA;
    ret->_bodyB = rbB;
    rbA->retain();
    rbB->retain();
    
    auto transformA = convertMat4TobtTransform(frameInA);
    auto transformB = convertMat4TobtTransform(frameInB);
    ret->_constraint = new btSliderConstraint(*rbA->getRigidBody(), *rbB->getRigidBody(), transformA, transformB, useLinearReferenceFrameA);
    ret->autorelease();
    return ret;
}

cocos2d::Mat4 Physics3DSliderConstraint::getFrameOffsetA() const
{
    const auto& frameOff = static_cast<btSliderConstraint*>(_constraint)->getFrameOffsetA();
    return convertbtTransformToMat4(frameOff);
}
cocos2d::Mat4 Physics3DSliderConstraint::getFrameOffsetB() const
{
    const auto& frameOff = static_cast<btSliderConstraint*>(_constraint)->getFrameOffsetB();
    return convertbtTransformToMat4(frameOff);
}
float Physics3DSliderConstraint::getLowerLinLimit() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getLowerLinLimit();
}
void Physics3DSliderConstraint::setLowerLinLimit(float lowerLimit)
{
    static_cast<btSliderConstraint*>(_constraint)->setLowerLinLimit(lowerLimit);
}
float Physics3DSliderConstraint::getUpperLinLimit() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getUpperLinLimit();
}
void Physics3DSliderConstraint::setUpperLinLimit(float upperLimit)
{
    static_cast<btSliderConstraint*>(_constraint)->setUpperLinLimit(upperLimit);
}
float Physics3DSliderConstraint::getLowerAngLimit() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getLowerAngLimit();
}
void Physics3DSliderConstraint::setLowerAngLimit(float lowerLimit)
{
    static_cast<btSliderConstraint*>(_constraint)->setLowerAngLimit(lowerLimit);
}
float Physics3DSliderConstraint::getUpperAngLimit() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getUpperAngLimit();
}
void Physics3DSliderConstraint::setUpperAngLimit(float upperLimit)
{
    static_cast<btSliderConstraint*>(_constraint)->setUpperAngLimit(upperLimit);
}
bool Physics3DSliderConstraint::getUseLinearReferenceFrameA() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getUseLinearReferenceFrameA();
}
float Physics3DSliderConstraint::getSoftnessDirLin() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getSoftnessDirLin();
}
float Physics3DSliderConstraint::getRestitutionDirLin() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getRestitutionDirLin();
}
float Physics3DSliderConstraint::getDampingDirLin() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getDampingDirLin();
}
float Physics3DSliderConstraint::getSoftnessDirAng() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getSoftnessDirAng();
}
float Physics3DSliderConstraint::getRestitutionDirAng() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getRestitutionDirAng();
}
float Physics3DSliderConstraint::getDampingDirAng() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getDampingDirAng();
}
float Physics3DSliderConstraint::getSoftnessLimLin() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getSoftnessLimLin();
}
float Physics3DSliderConstraint::getRestitutionLimLin() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getRestitutionLimLin();
}
float Physics3DSliderConstraint::getDampingLimLin() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getDampingLimAng();
}
float Physics3DSliderConstraint::getSoftnessLimAng() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getSoftnessLimAng();
}
float Physics3DSliderConstraint::getRestitutionLimAng() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getRestitutionLimAng();
}
float Physics3DSliderConstraint::getDampingLimAng() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getDampingLimAng();
}
float Physics3DSliderConstraint::getSoftnessOrthoLin() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getSoftnessOrthoLin();
}
float Physics3DSliderConstraint::getRestitutionOrthoLin() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getRestitutionOrthoAng();
}
float Physics3DSliderConstraint::getDampingOrthoLin() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getDampingOrthoLin();
}
float Physics3DSliderConstraint::getSoftnessOrthoAng() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getSoftnessOrthoAng();
}
float Physics3DSliderConstraint::getRestitutionOrthoAng() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getRestitutionOrthoAng();
}
float Physics3DSliderConstraint::getDampingOrthoAng() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getDampingOrthoAng();
}
void Physics3DSliderConstraint::setSoftnessDirLin(float softnessDirLin)
{
    static_cast<btSliderConstraint*>(_constraint)->setSoftnessDirLin(softnessDirLin);
}
void Physics3DSliderConstraint::setRestitutionDirLin(float restitutionDirLin)
{
    static_cast<btSliderConstraint*>(_constraint)->setRestitutionDirLin(restitutionDirLin);
}
void Physics3DSliderConstraint::setDampingDirLin(float dampingDirLin)
{
    static_cast<btSliderConstraint*>(_constraint)->setDampingDirLin(dampingDirLin);
}
void Physics3DSliderConstraint::setSoftnessDirAng(float softnessDirAng)
{
    static_cast<btSliderConstraint*>(_constraint)->setSoftnessDirAng(softnessDirAng);
}
void Physics3DSliderConstraint::setRestitutionDirAng(float restitutionDirAng)
{
    static_cast<btSliderConstraint*>(_constraint)->setRestitutionDirAng(restitutionDirAng);
}
void Physics3DSliderConstraint::setDampingDirAng(float dampingDirAng)
{
    static_cast<btSliderConstraint*>(_constraint)->setDampingDirAng(dampingDirAng);
}
void Physics3DSliderConstraint::setSoftnessLimLin(float softnessLimLin)
{
    static_cast<btSliderConstraint*>(_constraint)->setSoftnessLimLin(softnessLimLin);
}
void Physics3DSliderConstraint::setRestitutionLimLin(float restitutionLimLin)
{
    static_cast<btSliderConstraint*>(_constraint)->setRestitutionDirLin(restitutionLimLin);
}
void Physics3DSliderConstraint::setDampingLimLin(float dampingLimLin)
{
    static_cast<btSliderConstraint*>(_constraint)->setDampingLimLin(dampingLimLin);
}
void Physics3DSliderConstraint::setSoftnessLimAng(float softnessLimAng)
{
    static_cast<btSliderConstraint*>(_constraint)->setSoftnessLimAng(softnessLimAng);
}
void Physics3DSliderConstraint::setRestitutionLimAng(float restitutionLimAng)
{
    static_cast<btSliderConstraint*>(_constraint)->setRestitutionLimAng(restitutionLimAng);
}
void Physics3DSliderConstraint::setDampingLimAng(float dampingLimAng)
{
    static_cast<btSliderConstraint*>(_constraint)->setDampingLimAng(dampingLimAng);
}
void Physics3DSliderConstraint::setSoftnessOrthoLin(float softnessOrthoLin)
{
    static_cast<btSliderConstraint*>(_constraint)->setSoftnessOrthoLin(softnessOrthoLin);
}
void Physics3DSliderConstraint::setRestitutionOrthoLin(float restitutionOrthoLin)
{
    static_cast<btSliderConstraint*>(_constraint)->setRestitutionOrthoLin(restitutionOrthoLin);
}
void Physics3DSliderConstraint::setDampingOrthoLin(float dampingOrthoLin)
{
    static_cast<btSliderConstraint*>(_constraint)->setDampingLimLin(dampingOrthoLin);
}
void Physics3DSliderConstraint::setSoftnessOrthoAng(float softnessOrthoAng)
{
    static_cast<btSliderConstraint*>(_constraint)->setSoftnessOrthoAng(softnessOrthoAng);
}
void Physics3DSliderConstraint::setRestitutionOrthoAng(float restitutionOrthoAng)
{
    static_cast<btSliderConstraint*>(_constraint)->setRestitutionOrthoAng(restitutionOrthoAng);
}
void Physics3DSliderConstraint::setDampingOrthoAng(float dampingOrthoAng)
{
    static_cast<btSliderConstraint*>(_constraint)->setDampingOrthoAng(dampingOrthoAng);
}
void Physics3DSliderConstraint::setPoweredLinMotor(bool onOff)
{
    static_cast<btSliderConstraint*>(_constraint)->setPoweredLinMotor(onOff);
}
bool Physics3DSliderConstraint::getPoweredLinMotor() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getPoweredLinMotor();
}
void Physics3DSliderConstraint::setTargetLinMotorVelocity(float targetLinMotorVelocity)
{
    static_cast<btSliderConstraint*>(_constraint)->setTargetLinMotorVelocity(targetLinMotorVelocity);
}
float Physics3DSliderConstraint::getTargetLinMotorVelocity() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getTargetLinMotorVelocity();
}
void Physics3DSliderConstraint::setMaxLinMotorForce(float maxLinMotorForce)
{
    static_cast<btSliderConstraint*>(_constraint)->setMaxLinMotorForce(maxLinMotorForce);
}
float Physics3DSliderConstraint::getMaxLinMotorForce() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getMaxLinMotorForce();
}
void Physics3DSliderConstraint::setPoweredAngMotor(bool onOff)
{
    static_cast<btSliderConstraint*>(_constraint)->setPoweredAngMotor(onOff);
}
bool Physics3DSliderConstraint::getPoweredAngMotor() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getPoweredAngMotor();
}
void Physics3DSliderConstraint::setTargetAngMotorVelocity(float targetAngMotorVelocity)
{
    return static_cast<btSliderConstraint*>(_constraint)->setTargetAngMotorVelocity(targetAngMotorVelocity);
}
float Physics3DSliderConstraint::getTargetAngMotorVelocity() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getTargetAngMotorVelocity();
}
void Physics3DSliderConstraint::setMaxAngMotorForce(float maxAngMotorForce)
{
    return static_cast<btSliderConstraint*>(_constraint)->setMaxAngMotorForce(maxAngMotorForce);
}
float Physics3DSliderConstraint::getMaxAngMotorForce() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getMaxAngMotorForce();
}

float Physics3DSliderConstraint::getLinearPos() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getLinearPos();
}
float Physics3DSliderConstraint::getAngularPos() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getAngularPos();
}

// access for UseFrameOffset
bool Physics3DSliderConstraint::getUseFrameOffset() const
{
    return static_cast<btSliderConstraint*>(_constraint)->getUseFrameOffset();
}
void Physics3DSliderConstraint::setUseFrameOffset(bool frameOffsetOnOff)
{
    static_cast<btSliderConstraint*>(_constraint)->setUseFrameOffset(frameOffsetOnOff);
}

void Physics3DSliderConstraint::setFrames(const cocos2d::Mat4& frameA, const cocos2d::Mat4& frameB)
{
    auto btFrameA = convertMat4TobtTransform(frameA);
    auto btFrameB = convertMat4TobtTransform(frameB);
    static_cast<btSliderConstraint*>(_constraint)->setFrames(btFrameA, btFrameB);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Physics3DConeTwistConstraint* Physics3DConeTwistConstraint::create(Physics3DRigidBody* rbA, const cocos2d::Mat4& frameA)
{
    auto ret = new (std::nothrow) Physics3DConeTwistConstraint();
    ret->_bodyA = rbA;
    rbA->retain();
    
    auto btFrame = convertMat4TobtTransform(frameA);
    ret->_constraint = new btConeTwistConstraint(*rbA->getRigidBody(), btFrame);
    
    ret->autorelease();
    return ret;
}
Physics3DConeTwistConstraint* Physics3DConeTwistConstraint::create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Mat4& frameA, const cocos2d::Mat4& frameB)
{
    auto ret = new (std::nothrow) Physics3DConeTwistConstraint();
    ret->_bodyA = rbA;
    ret->_bodyB = rbB;
    rbA->retain();
    rbB->retain();
    
    auto btFrameA = convertMat4TobtTransform(frameA);
    auto btFrameB = convertMat4TobtTransform(frameB);
    
    ret->_constraint = new btConeTwistConstraint(*rbA->getRigidBody(), *rbB->getRigidBody(), btFrameA, btFrameB);
    
    ret->autorelease();
    return ret;
}

void	Physics3DConeTwistConstraint::setLimit(float swingSpan1,float swingSpan2,float twistSpan, float softness, float biasFactor, float relaxationFactor)
{
    static_cast<btConeTwistConstraint*>(_constraint)->setLimit(swingSpan1, swingSpan2, twistSpan, softness, biasFactor, relaxationFactor);
}

cocos2d::Mat4 Physics3DConeTwistConstraint::getAFrame() const
{
    const auto& frame = static_cast<btConeTwistConstraint*>(_constraint)->getAFrame();
    return convertbtTransformToMat4(frame);
}
cocos2d::Mat4 Physics3DConeTwistConstraint::getBFrame() const
{
    const auto& frame = static_cast<btConeTwistConstraint*>(_constraint)->getBFrame();
    return convertbtTransformToMat4(frame);
}

float Physics3DConeTwistConstraint::getSwingSpan1() const
{
    return static_cast<btConeTwistConstraint*>(_constraint)->getSwingSpan1();
}
float Physics3DConeTwistConstraint::getSwingSpan2() const
{
    return static_cast<btConeTwistConstraint*>(_constraint)->getSwingSpan2();
}
float Physics3DConeTwistConstraint::getTwistSpan() const
{
    return static_cast<btConeTwistConstraint*>(_constraint)->getTwistSpan();
}
float Physics3DConeTwistConstraint::getTwistAngle() const
{
    return static_cast<btConeTwistConstraint*>(_constraint)->getTwistAngle();
}

void Physics3DConeTwistConstraint::setDamping(float damping)
{
    static_cast<btConeTwistConstraint*>(_constraint)->setDamping(damping);
}

void Physics3DConeTwistConstraint::enableMotor(bool b)
{
    static_cast<btConeTwistConstraint*>(_constraint)->enableMotor(b);
}
void Physics3DConeTwistConstraint::setMaxMotorImpulse(float maxMotorImpulse)
{
    static_cast<btConeTwistConstraint*>(_constraint)->setMaxMotorImpulse(maxMotorImpulse);
}
void Physics3DConeTwistConstraint::setMaxMotorImpulseNormalized(float maxMotorImpulse)
{
    static_cast<btConeTwistConstraint*>(_constraint)->setMaxMotorImpulseNormalized(maxMotorImpulse);
}

float Physics3DConeTwistConstraint::getFixThresh() const
{
    return static_cast<btConeTwistConstraint*>(_constraint)->getFixThresh();
}
void Physics3DConeTwistConstraint::setFixThresh(float fixThresh)
{
    static_cast<btConeTwistConstraint*>(_constraint)->setFixThresh(fixThresh);
}

void Physics3DConeTwistConstraint::setMotorTarget(const btQuaternion &q)
{
    static_cast<btConeTwistConstraint*>(_constraint)->setMotorTarget(q);
}

// same as above, but q is the desired rotation of frameA wrt frameB in constraint space
void Physics3DConeTwistConstraint::setMotorTargetInConstraintSpace(const btQuaternion &q)
{
    static_cast<btConeTwistConstraint*>(_constraint)->setMotorTargetInConstraintSpace(q);
}

cocos2d::Vec3 Physics3DConeTwistConstraint::GetPointForAngle(float fAngleInRadians, float fLength) const
{
    const auto& point = static_cast<btConeTwistConstraint*>(_constraint)->GetPointForAngle(fAngleInRadians, fLength);
    return convertbtVector3ToVec3(point);
}

void Physics3DConeTwistConstraint::setFrames(const cocos2d::Mat4& frameA, const cocos2d::Mat4& frameB)
{
    const auto& btFrameA = convertMat4TobtTransform(frameA);
    const auto& btFrameB = convertMat4TobtTransform(frameB);
    
    static_cast<btConeTwistConstraint*>(_constraint)->setFrames(btFrameA, btFrameB);
}

cocos2d::Mat4 Physics3DConeTwistConstraint::getFrameOffsetA() const
{
    const auto& trans = static_cast<btConeTwistConstraint*>(_constraint)->getFrameOffsetA();
    return convertbtTransformToMat4(trans);
}

cocos2d::Mat4 Physics3DConeTwistConstraint::getFrameOffsetB() const
{
    const auto& trans = static_cast<btConeTwistConstraint*>(_constraint)->getFrameOffsetB();
    return convertbtTransformToMat4(trans);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Physics3D6DofConstraint* Physics3D6DofConstraint::create(Physics3DRigidBody* rbB, const cocos2d::Mat4& frameInB, bool useLinearReferenceFrameB)
{
    auto ret = new Physics3D6DofConstraint();
    ret->_bodyB = rbB;
    rbB->retain();
    
    auto frameB = convertMat4TobtTransform(frameInB);
    ret->_constraint = new btGeneric6DofConstraint(*rbB->getRigidBody(), frameB, useLinearReferenceFrameB);
    
    ret->autorelease();
    return ret;
}

Physics3D6DofConstraint* Physics3D6DofConstraint::create(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Mat4& frameInA, const cocos2d::Mat4& frameInB, bool useLinearReferenceFrameA)
{
    auto ret = new Physics3D6DofConstraint();
    ret->_bodyA = rbA;
    ret->_bodyB = rbB;
    rbA->retain();
    rbB->retain();
    
    auto frameA = convertMat4TobtTransform(frameInA);
    auto frameB = convertMat4TobtTransform(frameInB);
    ret->_constraint = new btGeneric6DofConstraint(*rbA->getRigidBody(), *rbB->getRigidBody(), frameA, frameB, useLinearReferenceFrameA);
    
    ret->autorelease();
    return ret;
}

void	Physics3D6DofConstraint::setLinearLowerLimit(const cocos2d::Vec3& linearLower)
{
    auto lower = convertVec3TobtVector3(linearLower);
    static_cast<btGeneric6DofConstraint*>(_constraint)->setLinearLowerLimit(lower);
}

cocos2d::Vec3	Physics3D6DofConstraint::getLinearLowerLimit() const
{
    btVector3 lower;
    static_cast<btGeneric6DofConstraint*>(_constraint)->getLinearLowerLimit(lower);
    return convertbtVector3ToVec3(lower);
}

void	Physics3D6DofConstraint::setLinearUpperLimit(const cocos2d::Vec3& linearUpper)
{
    auto upper = convertVec3TobtVector3(linearUpper);
    static_cast<btGeneric6DofConstraint*>(_constraint)->setLinearUpperLimit(upper);
}

cocos2d::Vec3	Physics3D6DofConstraint::getLinearUpperLimit() const
{
    btVector3 upper;
    static_cast<btGeneric6DofConstraint*>(_constraint)->getLinearUpperLimit(upper);
    return convertbtVector3ToVec3(upper);
}

void	Physics3D6DofConstraint::setAngularLowerLimit(const cocos2d::Vec3& angularLower)
{
    auto lower = convertVec3TobtVector3(angularLower);
    static_cast<btGeneric6DofConstraint*>(_constraint)->setAngularLowerLimit(lower);
}

cocos2d::Vec3	Physics3D6DofConstraint::getAngularLowerLimit() const
{
    btVector3 lower;
    static_cast<btGeneric6DofConstraint*>(_constraint)->getAngularLowerLimit(lower);
    return convertbtVector3ToVec3(lower);
}

void	Physics3D6DofConstraint::setAngularUpperLimit(const cocos2d::Vec3& angularUpper)
{
    auto upper = convertVec3TobtVector3(angularUpper);
    static_cast<btGeneric6DofConstraint*>(_constraint)->setAngularUpperLimit(upper);
}

cocos2d::Vec3	Physics3D6DofConstraint::getAngularUpperLimit() const
{
    btVector3 upper;
    static_cast<btGeneric6DofConstraint*>(_constraint)->getAngularUpperLimit(upper);
    return convertbtVector3ToVec3(upper);
}

bool	Physics3D6DofConstraint::isLimited(int limitIndex) const
{
    return static_cast<btGeneric6DofConstraint*>(_constraint)->isLimited(limitIndex);
}

bool Physics3D6DofConstraint::getUseFrameOffset() const
{
    return static_cast<btGeneric6DofConstraint*>(_constraint)->getUseFrameOffset();
}
void Physics3D6DofConstraint::setUseFrameOffset(bool frameOffsetOnOff) const
{
    static_cast<btGeneric6DofConstraint*>(_constraint)->setUseFrameOffset(frameOffsetOnOff);
}

NS_CC_END

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif //CC_USE_3D_PHYSICS
