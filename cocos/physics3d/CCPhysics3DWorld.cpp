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
#include "renderer/CCRenderer.h"

#if CC_USE_3D_PHYSICS

#if (CC_ENABLE_BULLET_INTEGRATION)

NS_CC_BEGIN

Physics3DWorld::Physics3DWorld()
: _btPhyiscsWorld(nullptr)
, _collisionConfiguration(nullptr)
, _dispatcher(nullptr)
, _broadphase(nullptr)
, _solver(nullptr)
, _ghostCallback(nullptr)
, _debugDrawer(nullptr)
, _needCollisionChecking(false)
, _collisionCheckingFlag(false)
, _needGhostPairCallbackChecking(false)
{
    
}
Physics3DWorld::~Physics3DWorld()
{
    removeAllPhysics3DConstraints();
    removeAllPhysics3DObjects();

    CC_SAFE_DELETE(_collisionConfiguration);
    CC_SAFE_DELETE(_dispatcher);
    CC_SAFE_DELETE(_broadphase);
    CC_SAFE_DELETE(_ghostCallback);
    CC_SAFE_DELETE(_solver);
    CC_SAFE_DELETE(_btPhyiscsWorld);
    CC_SAFE_DELETE(_debugDrawer);
    for (auto it : _physicsComponents)
        it->setPhysics3DObject(nullptr);
    _physicsComponents.clear();
}

Physics3DWorld* Physics3DWorld::create(Physics3DWorldDes* info)
{
    auto world = new (std::nothrow) Physics3DWorld();
    world->init(info);
    world->autorelease();
    return world;
}

void Physics3DWorld::setGravity(const Vec3& gravity)
{
    _btPhyiscsWorld->setGravity(convertVec3TobtVector3(gravity));
}

Vec3 Physics3DWorld::getGravity() const
{
    return convertbtVector3ToVec3(_btPhyiscsWorld->getGravity());
}

bool Physics3DWorld::init(Physics3DWorldDes* info)
{
    ///collision configuration contains default setup for memory, collision setup
    _collisionConfiguration = new (std::nothrow) btDefaultCollisionConfiguration();
    //_collisionConfiguration->setConvexConvexMultipointIterations();
    
    ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    _dispatcher = new (std::nothrow) btCollisionDispatcher(_collisionConfiguration);
    
    _broadphase = new (std::nothrow) btDbvtBroadphase();
    
    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    btSequentialImpulseConstraintSolver* sol = new btSequentialImpulseConstraintSolver();
    _solver = sol;

    btGhostPairCallback *ghostCallback = new btGhostPairCallback();
    _ghostCallback = ghostCallback;
    
    _btPhyiscsWorld = new btDiscreteDynamicsWorld(_dispatcher,_broadphase,_solver,_collisionConfiguration);
    _btPhyiscsWorld->setGravity(convertVec3TobtVector3(info->gravity));
    if (info->isDebugDrawEnabled)
    {
        _debugDrawer = new (std::nothrow) Physics3DDebugDrawer();
        _btPhyiscsWorld->setDebugDrawer(_debugDrawer);
    }
    
    return true;
}

void Physics3DWorld::setDebugDrawEnable(bool enableDebugDraw)
{
    if (enableDebugDraw && _btPhyiscsWorld->getDebugDrawer() == nullptr)
    {
        _debugDrawer = new (std::nothrow) Physics3DDebugDrawer();
    }
    enableDebugDraw ? _btPhyiscsWorld->setDebugDrawer(_debugDrawer) : _btPhyiscsWorld->setDebugDrawer(nullptr);
}

bool Physics3DWorld::isDebugDrawEnabled() const
{
    return _btPhyiscsWorld->getDebugDrawer() != nullptr;
}

void Physics3DWorld::addPhysics3DObject(Physics3DObject* physicsObj)
{
    auto it = std::find(_objects.begin(), _objects.end(), physicsObj);
    if (it == _objects.end())
    {
        _objects.push_back(physicsObj);
        physicsObj->retain();
        if (physicsObj->getObjType() == Physics3DObject::PhysicsObjType::RIGID_BODY)
        {
            _btPhyiscsWorld->addRigidBody(static_cast<Physics3DRigidBody*>(physicsObj)->getRigidBody());
        }
        else if (physicsObj->getObjType() == Physics3DObject::PhysicsObjType::COLLIDER)
        {
            _btPhyiscsWorld->addCollisionObject(static_cast<Physics3DCollider*>(physicsObj)->getGhostObject());
        }
        _collisionCheckingFlag = true;
        _needGhostPairCallbackChecking = true;
    }
}

void Physics3DWorld::removePhysics3DObject(Physics3DObject* physicsObj)
{
    auto it = std::find(_objects.begin(), _objects.end(), physicsObj);
    if (it != _objects.end())
    {
        if (physicsObj->getObjType() == Physics3DObject::PhysicsObjType::RIGID_BODY)
        {
            _btPhyiscsWorld->removeRigidBody(static_cast<Physics3DRigidBody*>(physicsObj)->getRigidBody());
        }
        else if (physicsObj->getObjType() == Physics3DObject::PhysicsObjType::COLLIDER)
        {
            _btPhyiscsWorld->removeCollisionObject(static_cast<Physics3DCollider*>(physicsObj)->getGhostObject());
        }
        physicsObj->release();
        _objects.erase(it);
        _collisionCheckingFlag = true;
        _needGhostPairCallbackChecking = true;
    }
}

void Physics3DWorld::removeAllPhysics3DObjects()
{
    for (auto it : _objects) {
        if (it->getObjType() == Physics3DObject::PhysicsObjType::RIGID_BODY)
        {
            _btPhyiscsWorld->removeRigidBody(static_cast<Physics3DRigidBody*>(it)->getRigidBody());
        }
        else if (it->getObjType() == Physics3DObject::PhysicsObjType::COLLIDER)
        {
            _btPhyiscsWorld->removeCollisionObject(static_cast<Physics3DCollider*>(it)->getGhostObject());
        }
        it->release();
    }
    _objects.clear();
    _collisionCheckingFlag = true;
    _needGhostPairCallbackChecking = true;
}

void Physics3DWorld::addPhysics3DConstraint(Physics3DConstraint* constraint, bool disableCollisionsBetweenLinkedObjs)
{
    auto body = constraint->getBodyA();
    if (body)
        body->addConstraint(constraint);
    
    body = constraint->getBodyB();
    if (body)
    {
        body->addConstraint(constraint);
    }
    _btPhyiscsWorld->addConstraint(constraint->getbtContraint(), disableCollisionsBetweenLinkedObjs);
}

void Physics3DWorld::removePhysics3DConstraint(Physics3DConstraint* constraint)
{
    _btPhyiscsWorld->removeConstraint(constraint->getbtContraint());
    
    auto bodyA = constraint->getBodyA();
    auto bodyB = constraint->getBodyB();
    if (bodyA)
        bodyA->removeConstraint(constraint);
    if (bodyB)
        bodyB->removeConstraint(constraint);
}

void Physics3DWorld::removeAllPhysics3DConstraints()
{
    for(auto it : _objects)
    {
        auto type = it->getObjType();
        if (type == Physics3DObject::PhysicsObjType::RIGID_BODY)
        {
            auto& constraints = static_cast<Physics3DRigidBody*>(it)->_constraintList;
            for (auto constraint : constraints) {
                _btPhyiscsWorld->removeConstraint(constraint->getbtContraint());
                constraint->release();
            }
            constraints.clear();
        }
    }
    
}

void Physics3DWorld::stepSimulate(float dt)
{
    if (_btPhyiscsWorld)
    {
        setGhostPairCallback();
        //should sync kinematic node before simulation
        for (auto it : _physicsComponents)
        {
            it->preSimulate();
        }
        _btPhyiscsWorld->stepSimulation(dt, 3);
        //sync dynamic node after simulation
        for (auto it : _physicsComponents)
        {
            it->postSimulate();
        }
        if (needCollisionChecking())
            collisionChecking();
    }
}

void Physics3DWorld::debugDraw(Renderer* renderer)
{
    if (_debugDrawer)
    {
        _debugDrawer->clear();
        _btPhyiscsWorld->debugDrawWorld();
        _debugDrawer->draw(renderer);
    }
}

bool Physics3DWorld::rayCast(const cocos2d::Vec3& startPos, const cocos2d::Vec3& endPos, Physics3DWorld::HitResult* result)
{
    auto btStart = convertVec3TobtVector3(startPos);
    auto btEnd = convertVec3TobtVector3(endPos);
    btCollisionWorld::ClosestRayResultCallback btResult(btStart, btEnd);
    _btPhyiscsWorld->rayTest(btStart, btEnd, btResult);
    if (btResult.hasHit())
    {
        result->hitObj = getPhysicsObject(btResult.m_collisionObject);
        result->hitPosition = convertbtVector3ToVec3(btResult.m_hitPointWorld);
        result->hitNormal = convertbtVector3ToVec3(btResult.m_hitNormalWorld);
        return true;
    }
    result->hitObj = nullptr;
    return false;
}

bool Physics3DWorld::sweepShape(Physics3DShape* shape, const cocos2d::Mat4& startTransform, const cocos2d::Mat4& endTransform, Physics3DWorld::HitResult* result)
{
    CC_ASSERT(shape->getShapeType() != Physics3DShape::ShapeType::HEIGHT_FIELD && shape->getShapeType() != Physics3DShape::ShapeType::MESH);
    auto btStart = convertMat4TobtTransform(startTransform);
    auto btEnd = convertMat4TobtTransform(endTransform);
    btCollisionWorld::ClosestConvexResultCallback btResult(btStart.getOrigin(), btEnd.getOrigin());
    _btPhyiscsWorld->convexSweepTest((btConvexShape*)shape->getbtShape(), btStart, btEnd, btResult);
    if (btResult.hasHit())
    {
        result->hitObj = getPhysicsObject(btResult.m_hitCollisionObject);
        result->hitPosition = convertbtVector3ToVec3(btResult.m_hitPointWorld);
        result->hitNormal = convertbtVector3ToVec3(btResult.m_hitNormalWorld);
        return true;
    }
    result->hitObj = nullptr;
    return false;
}

Physics3DObject* Physics3DWorld::getPhysicsObject(const btCollisionObject* btObj)
{
    for(auto it : _objects)
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

void Physics3DWorld::collisionChecking()
{
    int numManifolds = _dispatcher->getNumManifolds();
    for (int i = 0; i < numManifolds; ++i){
        btPersistentManifold * contactManifold = _dispatcher->getManifoldByIndexInternal(i);
        int numContacts = contactManifold->getNumContacts();
        if (0 < numContacts){
            const btCollisionObject* obA = static_cast<const btCollisionObject*>(contactManifold->getBody0());
            const btCollisionObject* obB = static_cast<const btCollisionObject*>(contactManifold->getBody1());
            Physics3DObject *poA = getPhysicsObject(obA);
            Physics3DObject *poB = getPhysicsObject(obB);
            if (poA->needCollisionCallback() || poB->needCollisionCallback()){
                Physics3DCollisionInfo ci;
                ci.objA = poA;
                ci.objB = poB;
                for (int c = 0; c < numContacts; ++c){
                    btManifoldPoint& pt = contactManifold->getContactPoint(c);
                    Physics3DCollisionInfo::CollisionPoint cp = {
                          convertbtVector3ToVec3(pt.m_localPointA), convertbtVector3ToVec3(pt.m_positionWorldOnA)
                        , convertbtVector3ToVec3(pt.m_localPointB), convertbtVector3ToVec3(pt.m_positionWorldOnB)
                        , convertbtVector3ToVec3(pt.m_normalWorldOnB)
                    };
                    ci.collisionPointList.push_back(cp);
                }

                if (poA->needCollisionCallback()){
                    poA->getCollisionCallback()(ci);
                }
                if (poB->needCollisionCallback()){
                    poB->getCollisionCallback()(ci);
                }
            }
        }
    }
}

bool Physics3DWorld::needCollisionChecking()
{
    if (_collisionCheckingFlag){
        _needCollisionChecking = false;
        for(auto it : _objects)
        {
            if (it->getCollisionCallback() != nullptr){
                _needCollisionChecking = true;
                break;
            }
        }
        _collisionCheckingFlag = false;
    }
    return _needCollisionChecking;
}

void Physics3DWorld::setGhostPairCallback()
{
    if (_needGhostPairCallbackChecking){
        bool needCallback = false;
        for (auto it : _objects)
        {
            if (it->getObjType() == Physics3DObject::PhysicsObjType::COLLIDER){
                needCallback = true;
                break;
            }
        }
        _btPhyiscsWorld->getPairCache()->setInternalGhostPairCallback(needCallback == true? _ghostCallback: nullptr);
        _needGhostPairCallbackChecking = false;
    }
}

NS_CC_END

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif //CC_USE_3D_PHYSICS
