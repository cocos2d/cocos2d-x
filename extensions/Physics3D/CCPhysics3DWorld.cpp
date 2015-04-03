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

Physics3DWorld::Physics3DWorld()
: _btPhyiscsWorld(nullptr)
, _collisionConfiguration(nullptr)
, _dispatcher(nullptr)
, _broadphase(nullptr)
, _solver(nullptr)
, _debugDrawer(nullptr)
{
    
}
Physics3DWorld::~Physics3DWorld()
{
    removeAllPhysics3DObjects();
    removeAllPhysics3DConstraints();
    CC_SAFE_DELETE(_collisionConfiguration);
    CC_SAFE_DELETE(_dispatcher);
    CC_SAFE_DELETE(_broadphase);
    CC_SAFE_DELETE(_solver);
    CC_SAFE_DELETE(_btPhyiscsWorld);
    CC_SAFE_DELETE(_debugDrawer);
}

Physics3DWorld* Physics3DWorld::create(Physics3DWorldDes* info)
{
    auto world = new (std::nothrow) Physics3DWorld();
    world->init(info);
    world->autorelease();
    return world;
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
        physicsObj->release();
        _objects.erase(it);
    }
}

void Physics3DWorld::removeAllPhysics3DObjects()
{
    for (auto it : _objects) {
        if (it->getObjType() == Physics3DObject::PhysicsObjType::RIGID_BODY)
        {
            _btPhyiscsWorld->removeRigidBody(static_cast<Physics3DRigidBody*>(it)->getRigidBody());
        }
        it->release();
    }
    _objects.clear();
}

void Physics3DWorld::addPhysics3DConstraint(Physics3DConstraint* constraint)
{
    
}

void Physics3DWorld::removePhysics3DConstraint(Physics3DConstraint* constraint)
{
    
}

void Physics3DWorld::removeAllPhysics3DConstraints()
{
    
}

void Physics3DWorld::stepSimulate(float dt)
{
    if (_btPhyiscsWorld)
    {
        _btPhyiscsWorld->stepSimulation(dt);
    }
}



NS_CC_EXT_END

#endif // CC_ENABLE_BULLET_INTEGRATION
