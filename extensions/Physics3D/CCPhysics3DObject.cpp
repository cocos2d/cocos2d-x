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
#include "base/ccUTF8.h"

USING_NS_CC;

#if (CC_ENABLE_BULLET_INTEGRATION)

#include "bullet/btBulletCollisionCommon.h"
#include "bullet/btBulletDynamicsCommon.h"

NS_CC_EXT_BEGIN

Physics3DRigidBody::Physics3DRigidBody()
: _btRigidBody(nullptr)
, _physics3DShape(nullptr)
{
    
}

Physics3DRigidBody::~Physics3DRigidBody()
{
    CC_SAFE_DELETE(_btRigidBody);
    CC_SAFE_RELEASE(_physics3DShape);
}

Physics3DRigidBody* Physics3DRigidBody::create(Physics3DRigidBodyDes* info)
{
    auto ret = new (std::nothrow) Physics3DRigidBody();
    if (ret->init(info))
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return ret;
}

bool Physics3DRigidBody::init(Physics3DRigidBodyDes* info)
{
    if (info->shape == nullptr)
        return false;
    
    btScalar mass = info->mass;
    auto shape = info->shape->getbtShape();
    auto localInertia = convertVec3TobtVector3(info->localInertia);
    if (mass != 0.f)
    {
        shape->calculateLocalInertia(mass,localInertia);
    }
    
    auto transform = convertMat4TobtTransform(info->originalTransform);
    btDefaultMotionState* myMotionState = new btDefaultMotionState(transform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,shape,localInertia);
    _btRigidBody = new btRigidBody(rbInfo);
    _type = Physics3DObject::PhysicsObjType::RIGID_BODY;
    _physics3DShape = info->shape;
    _physics3DShape->retain();
    return true;
}

void Physics3DRigidBody::applyForce( const cocos2d::Vec3& force, const cocos2d::Vec3& rel_pos )
{
    _btRigidBody->applyForce(convertVec3TobtVector3(force), convertVec3TobtVector3(rel_pos));
}

void Physics3DRigidBody::setLinearVelocity( const cocos2d::Vec3& lin_vel )
{
    _btRigidBody->setLinearVelocity(convertVec3TobtVector3(lin_vel));
}

void Physics3DRigidBody::applyCentralForce( const cocos2d::Vec3& force )
{
    _btRigidBody->applyCentralForce(convertVec3TobtVector3(force));
}

void Physics3DRigidBody::applyCentralImpulse( const cocos2d::Vec3& impulse )
{
    _btRigidBody->applyCentralImpulse(convertVec3TobtVector3(impulse));
}

void Physics3DRigidBody::applyTorque( const cocos2d::Vec3& torque )
{
    _btRigidBody->applyTorque(convertVec3TobtVector3(torque));
}

void Physics3DRigidBody::applyTorqueImpulse( const cocos2d::Vec3& torque )
{
    _btRigidBody->applyTorqueImpulse(convertVec3TobtVector3(torque));
}

void Physics3DRigidBody::applyImpulse( const cocos2d::Vec3& impulse, const cocos2d::Vec3& rel_pos )
{
    _btRigidBody->applyImpulse(convertVec3TobtVector3(impulse), convertVec3TobtVector3(rel_pos));
}

void Physics3DRigidBody::applyDamping( float timeStep )
{
    _btRigidBody->applyDamping(timeStep);
}

cocos2d::Vec3 Physics3DRigidBody::getLinearVelocity() const
{
    return convertbtVector3ToVec3(_btRigidBody->getLinearVelocity());
}

void Physics3DRigidBody::setLinearFactor( const cocos2d::Vec3& linearFactor )
{
    _btRigidBody->setLinearFactor(convertVec3TobtVector3(linearFactor));
}

cocos2d::Vec3 Physics3DRigidBody::getLinearFactor() const
{
    return convertbtVector3ToVec3(_btRigidBody->getLinearFactor());
}

void Physics3DRigidBody::setAngularFactor( const cocos2d::Vec3& angFac )
{
    _btRigidBody->setAngularFactor(convertVec3TobtVector3(angFac));
}

void Physics3DRigidBody::setAngularFactor( float angFac )
{
    _btRigidBody->setAngularFactor(angFac);
}

cocos2d::Vec3 Physics3DRigidBody::getAngularFactor() const
{
    return convertbtVector3ToVec3(_btRigidBody->getAngularFactor());
}

void Physics3DRigidBody::setAngularVelocity( const cocos2d::Vec3& ang_vel )
{
    _btRigidBody->setAngularVelocity(convertVec3TobtVector3(ang_vel));
}

cocos2d::Vec3 Physics3DRigidBody::getAngularVelocity() const
{
    return convertbtVector3ToVec3(_btRigidBody->getAngularVelocity());
}

void Physics3DRigidBody::setCenterOfMassTransform( const cocos2d::Mat4& xform )
{
    _btRigidBody->setCenterOfMassTransform(convertMat4TobtTransform(xform));
}

cocos2d::Mat4 Physics3DRigidBody::getCenterOfMassTransform() const
{
    return convertbtTransformToMat4(_btRigidBody->getCenterOfMassTransform());
}

void Physics3DRigidBody::setDamping( float lin_damping, float ang_damping )
{
    _btRigidBody->setDamping(lin_damping, ang_damping);
}

float Physics3DRigidBody::getLinearDamping() const
{
    return _btRigidBody->getLinearDamping();
}

float Physics3DRigidBody::getAngularDamping() const
{
    return _btRigidBody->getAngularDamping();
}

void Physics3DRigidBody::setGravity( const cocos2d::Vec3& acceleration )
{
    _btRigidBody->setGravity(convertVec3TobtVector3(acceleration));
}

cocos2d::Vec3 Physics3DRigidBody::getGravity() const
{
    return convertbtVector3ToVec3(_btRigidBody->getGravity());
}

void Physics3DRigidBody::setInvInertiaDiagLocal( const cocos2d::Vec3& diagInvInertia )
{
    _btRigidBody->setInvInertiaDiagLocal(convertVec3TobtVector3(diagInvInertia));
}

cocos2d::Vec3 Physics3DRigidBody::getInvInertiaDiagLocal() const
{
    return convertbtVector3ToVec3(_btRigidBody->getInvInertiaDiagLocal());
}

void Physics3DRigidBody::setMassProps( float mass, const cocos2d::Vec3& inertia )
{
    _btRigidBody->setMassProps(mass, convertVec3TobtVector3(inertia));
}

float Physics3DRigidBody::getInvMass() const
{
    return _btRigidBody->getInvMass();
}

cocos2d::Vec3 Physics3DRigidBody::getTotalForce() const
{
    return convertbtVector3ToVec3(_btRigidBody->getTotalForce());
}

cocos2d::Vec3 Physics3DRigidBody::getTotalTorque() const
{
    return convertbtVector3ToVec3(_btRigidBody->getTotalTorque());
}

void Physics3DRigidBody::setRestitution( float rest )
{
    _btRigidBody->setRestitution(rest);
}

float Physics3DRigidBody::getRestitution() const
{
    return _btRigidBody->getRestitution();
}

void Physics3DRigidBody::setFriction( float frict )
{
    _btRigidBody->setFriction(frict);
}

float Physics3DRigidBody::getFriction() const
{
    return _btRigidBody->getFriction();
}

void Physics3DRigidBody::setRollingFriction( float frict )
{
    _btRigidBody->setRollingFriction(frict);
}

float Physics3DRigidBody::getRollingFriction() const
{
    return _btRigidBody->getRollingFriction();
}

void Physics3DRigidBody::setHitFraction( float hitFraction )
{
    _btRigidBody->setHitFraction(hitFraction);
}

float Physics3DRigidBody::getHitFraction() const
{
    return _btRigidBody->getHitFraction();
}

void Physics3DRigidBody::addConstraint( Physics3DConstraint *constraint )
{
    auto iter = std::find(_constraintList.begin(), _constraintList.end(), constraint);
    if (iter == _constraintList.end()){
        _constraintList.push_back(constraint);
        //_btRigidBody->addConstraintRef(constraint->get);
        //TODO: FIXME
    }
}

void Physics3DRigidBody::removeConstraint( Physics3DConstraint *constraint )
{
    auto iter = std::find(_constraintList.begin(), _constraintList.end(), constraint);
    if (iter != _constraintList.end()){
        //removeConstraint(iter - _constraintList.begin());
        _constraintList.erase(iter);
        //TODO: FIXME
    }
}

void Physics3DRigidBody::removeConstraint( unsigned int idx )
{
    CCASSERT(idx < _constraintList.size(), "idx < _constraintList.size()");
    //_btRigidBody->removeConstraintRef(_constraintList[idx]->get);
    _constraintList.erase(_constraintList.begin() + idx);
    //TODO: FIXME
}

Physics3DConstraint* Physics3DRigidBody::getConstraint( unsigned int idx ) const
{
    CCASSERT(idx < _constraintList.size(), "idx < _constraintList.size()");
    return _constraintList[idx];
}

unsigned int Physics3DRigidBody::getConstraintCount() const
{
    return (unsigned int)_constraintList.size();
}

cocos2d::Mat4 Physics3DRigidBody::getWorldTransform() const
{
    const auto& transform = _btRigidBody->getWorldTransform();
    return convertbtTransformToMat4(transform);
}

NS_CC_EXT_END

#endif // CC_ENABLE_BULLET_INTEGRATION
