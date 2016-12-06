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

#include "physics3d/CCPhysics3D.h"
#include "base/ccUTF8.h"

#if CC_USE_3D_PHYSICS

#if (CC_ENABLE_BULLET_INTEGRATION)

#include "bullet/btBulletCollisionCommon.h"
#include "bullet/btBulletDynamicsCommon.h"

NS_CC_BEGIN

Physics3DRigidBody::Physics3DRigidBody()
: _btRigidBody(nullptr)
, _physics3DShape(nullptr)
{
    
}

Physics3DRigidBody::~Physics3DRigidBody()
{
    if (_physicsWorld)
    {
        for(auto constraint : _constraintList)
        {
            _physicsWorld->removePhysics3DConstraint(constraint);
        }
        _constraintList.clear();
    }
    auto ms = _btRigidBody->getMotionState();
    CC_SAFE_DELETE(ms);
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
    if (info->disableSleep)
        _btRigidBody->setActivationState(DISABLE_DEACTIVATION);
    return true;
}

void Physics3DRigidBody::setActive(bool active)
{
    if (_btRigidBody)
    {
        _btRigidBody->setActivationState(active ? ACTIVE_TAG : WANTS_DEACTIVATION);
    }
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

void Physics3DRigidBody::setCcdMotionThreshold( float ccdMotionThreshold )
{
    _btRigidBody->setCcdMotionThreshold(ccdMotionThreshold);
}

float Physics3DRigidBody::getCcdMotionThreshold() const
{
    return _btRigidBody->getCcdMotionThreshold();
}

void Physics3DRigidBody::setCcdSweptSphereRadius( float radius )
{
    _btRigidBody->setCcdSweptSphereRadius(radius);
}

float Physics3DRigidBody::getCcdSweptSphereRadius() const
{
    return _btRigidBody->getCcdSweptSphereRadius();
}

void Physics3DRigidBody::addConstraint( Physics3DConstraint *constraint )
{
    auto iter = std::find(_constraintList.begin(), _constraintList.end(), constraint);
    if (iter == _constraintList.end()){
        _constraintList.push_back(constraint);
        constraint->retain();
    }
}

void Physics3DRigidBody::removeConstraint( Physics3DConstraint *constraint )
{
    auto iter = std::find(_constraintList.begin(), _constraintList.end(), constraint);
    if (iter != _constraintList.end()){
        constraint->release();
        _constraintList.erase(iter);
    }
}

void Physics3DRigidBody::removeConstraint( unsigned int idx )
{
    CCASSERT(idx < _constraintList.size(), "idx < _constraintList.size()");
    removeConstraint(_constraintList[idx]);
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

void Physics3DRigidBody::setKinematic(bool kinematic)
{
    if (kinematic)
    {
        _btRigidBody->setCollisionFlags(_btRigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
        _btRigidBody->setActivationState(DISABLE_DEACTIVATION);
    }
    else
    {
        _btRigidBody->setCollisionFlags(_btRigidBody->getCollisionFlags() & ~btCollisionObject::CF_KINEMATIC_OBJECT);
        _btRigidBody->setActivationState(ACTIVE_TAG);
    }
}

bool Physics3DRigidBody::isKinematic() const
{
    if (_btRigidBody)
        return _btRigidBody->isKinematicObject();
    return false;
}

class btCollider : public btGhostObject
{
public:
    btCollider(Physics3DCollider *collider)
        : _collider(collider)
    {};
    ~btCollider(){};

    ///this method is mainly for expert/internal use only.
    virtual void addOverlappingObjectInternal(btBroadphaseProxy* otherProxy, btBroadphaseProxy* thisProxy = nullptr) override
    {
        btCollisionObject* otherObject = (btCollisionObject*)otherProxy->m_clientObject;
        btAssert(otherObject);
        ///if this linearSearch becomes too slow (too many overlapping objects) we should add a more appropriate data structure
        int index = m_overlappingObjects.findLinearSearch(otherObject);
        if (index == m_overlappingObjects.size())
        {
            //not found
            m_overlappingObjects.push_back(otherObject);
            if (_collider->onTriggerEnter != nullptr && _collider->isTrigger())
                _collider->onTriggerEnter(getPhysicsObject(otherObject));
        }
    }

    ///this method is mainly for expert/internal use only.
    virtual void removeOverlappingObjectInternal(btBroadphaseProxy* otherProxy, btDispatcher* /*dispatcher*/, btBroadphaseProxy* thisProxy = nullptr) override
    {
        btCollisionObject* otherObject = (btCollisionObject*)otherProxy->m_clientObject;
        btAssert(otherObject);
        int index = m_overlappingObjects.findLinearSearch(otherObject);
        if (index < m_overlappingObjects.size())
        {
            m_overlappingObjects[index] = m_overlappingObjects[m_overlappingObjects.size() - 1];
            m_overlappingObjects.pop_back();

            if (_collider->onTriggerExit != nullptr && _collider->isTrigger())
                _collider->onTriggerExit(getPhysicsObject(otherObject));
        }
    }

    Physics3DObject* getPhysicsObject(const btCollisionObject* btObj)
    {
        for (auto it : _collider->getPhysicsWorld()->getPhysicsObjects())
        {
            if (it->getObjType() == Physics3DObject::PhysicsObjType::RIGID_BODY)
            {
                if (static_cast<Physics3DRigidBody*>(it)->getRigidBody() == btObj)
                    return it;
            }
            else if (it->getObjType() == Physics3DObject::PhysicsObjType::COLLIDER)
            {
                if (static_cast<Physics3DCollider*>(it)->getGhostObject() == btObj)
                    return it;
            }
        }
        return nullptr;
    }

private:
    Physics3DCollider *_collider;
};

Physics3DCollider::Physics3DCollider()
: _btGhostObject(nullptr)
, _physics3DShape(nullptr)
{

}

Physics3DCollider::~Physics3DCollider()
{
    CC_SAFE_DELETE(_btGhostObject);
    CC_SAFE_RELEASE(_physics3DShape);
}

Physics3DCollider* Physics3DCollider::create(Physics3DColliderDes *info)
{
    auto ret = new (std::nothrow) Physics3DCollider();
    if (ret->init(info))
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return ret;
}

float Physics3DCollider::getCcdSweptSphereRadius() const
{
    return _btGhostObject->getCcdSweptSphereRadius();
}

void Physics3DCollider::setCcdSweptSphereRadius(float radius)
{
    _btGhostObject->setCcdSweptSphereRadius(radius);
}

float Physics3DCollider::getCcdMotionThreshold() const
{
    return _btGhostObject->getCcdMotionThreshold();
}

void Physics3DCollider::setCcdMotionThreshold(float ccdMotionThreshold)
{
    _btGhostObject->setCcdMotionThreshold(ccdMotionThreshold);
}

float Physics3DCollider::getHitFraction() const
{
    return _btGhostObject->getHitFraction();
}

void Physics3DCollider::setHitFraction(float hitFraction)
{
    _btGhostObject->setHitFraction(hitFraction);
}

float Physics3DCollider::getRollingFriction() const
{
    return _btGhostObject->getRollingFriction();
}

void Physics3DCollider::setRollingFriction(float frict)
{
    _btGhostObject->setRollingFriction(frict);
}

float Physics3DCollider::getFriction() const
{
    return _btGhostObject->getFriction();
}

void Physics3DCollider::setFriction(float frict)
{
    _btGhostObject->setFriction(frict);
}

float Physics3DCollider::getRestitution() const
{
    return _btGhostObject->getRestitution();
}

void Physics3DCollider::setRestitution(float rest)
{
    _btGhostObject->setRestitution(rest);
}

bool Physics3DCollider::isTrigger() const
{
    return (_btGhostObject->getCollisionFlags() & btCollisionObject::CF_NO_CONTACT_RESPONSE) != 0;
}

void Physics3DCollider::setTrigger(bool isTrigger)
{
    _btGhostObject->setCollisionFlags(isTrigger == true ?
        _btGhostObject->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE : 
        _btGhostObject->getCollisionFlags() & ~btCollisionObject::CF_NO_CONTACT_RESPONSE);
}

bool Physics3DCollider::init(Physics3DColliderDes *info)
{
    _physics3DShape = info->shape;
    _physics3DShape->retain();
    _btGhostObject = new btCollider(this);
    _btGhostObject->setCollisionShape(_physics3DShape->getbtShape());
    
    setTrigger(info->isTrigger);
    setFriction(info->friction);
    setRollingFriction(info->rollingFriction);
    setRestitution(info->restitution);
    setHitFraction(info->hitFraction);
    setCcdSweptSphereRadius(info->ccdSweptSphereRadius);
    setCcdMotionThreshold(info->ccdMotionThreshold);
    
    _type = Physics3DObject::PhysicsObjType::COLLIDER;
    return true;
}

cocos2d::Mat4 Physics3DCollider::getWorldTransform() const
{
    return convertbtTransformToMat4(_btGhostObject->getWorldTransform());
}

NS_CC_END

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif // CC_USE_3D_PHYSICS
