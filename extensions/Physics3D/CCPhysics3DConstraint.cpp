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

#if (CC_ENABLE_BULLET_INTEGRATION)



NS_CC_EXT_BEGIN

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
    
    return true;
}

bool Physics3DPointToPointConstraint::init(Physics3DRigidBody* rbA, Physics3DRigidBody* rbB, const cocos2d::Vec3& pivotPointInA, const cocos2d::Vec3& pivotPointInB)
{
    _constraint = new btPoint2PointConstraint(*rbA->getRigidBody(), *rbB->getRigidBody(), convertVec3TobtVector3(pivotPointInA), convertVec3TobtVector3(pivotPointInB));
    
    return true;
}

void	Physics3DPointToPointConstraint::setPivotPointInA(const cocos2d::Vec3& pivotA)
{
    auto point = convertVec3TobtVector3(pivotA);
    static_cast<btPoint2PointConstraint*>(_constraint)->setPivotA(point);
}

void	Physics3DPointToPointConstraint::setPivotPointInB(const cocos2d::Vec3&& pivotB)
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

NS_CC_EXT_END

#endif // CC_ENABLE_BULLET_INTEGRATION
