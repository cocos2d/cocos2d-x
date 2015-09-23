/****************************************************************************
 Copyright (c) 2013 Chukong Technologies Inc.
 
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

#include "physics/CCPhysicsWorld.h"
#if CC_USE_PHYSICS
#include <algorithm>
#include <climits>

#include "chipmunk.h"
#include "CCPhysicsBody.h"
#include "CCPhysicsShape.h"
#include "CCPhysicsContact.h"
#include "CCPhysicsJoint.h"
#include "CCPhysicsContact.h"
#include "CCPhysicsHelper.h"

#include "2d/CCDrawNode.h"
#include "2d/CCScene.h"
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventCustom.h"

NS_CC_BEGIN
const float PHYSICS_INFINITY = INFINITY;
extern const char* PHYSICSCONTACT_EVENT_NAME;
extern std::unordered_map<cpShape*, PhysicsShape*> s_physicsShapeMap;

const int PhysicsWorld::DEBUGDRAW_NONE = 0x00;
const int PhysicsWorld::DEBUGDRAW_SHAPE = 0x01;
const int PhysicsWorld::DEBUGDRAW_JOINT = 0x02;
const int PhysicsWorld::DEBUGDRAW_CONTACT = 0x04;
const int PhysicsWorld::DEBUGDRAW_ALL = DEBUGDRAW_SHAPE | DEBUGDRAW_JOINT | DEBUGDRAW_CONTACT;

namespace
{
    typedef struct RayCastCallbackInfo
    {
        PhysicsWorld* world;
        PhysicsRayCastCallbackFunc func;
        Vec2 p1;
        Vec2 p2;
        void* data;
    }RayCastCallbackInfo;
    
    typedef struct RectQueryCallbackInfo
    {
        PhysicsWorld* world;
        PhysicsQueryRectCallbackFunc func;
        void* data;
    }RectQueryCallbackInfo;
    
    typedef struct PointQueryCallbackInfo
    {
        PhysicsWorld* world;
        PhysicsQueryPointCallbackFunc func;
        void* data;
    }PointQueryCallbackInfo;
}

class PhysicsWorldCallback
{
public:
    static int collisionBeginCallbackFunc(cpArbiter *arb, struct cpSpace *space, PhysicsWorld *world);
    static int collisionPreSolveCallbackFunc(cpArbiter *arb, cpSpace *space, PhysicsWorld *world);
    static void collisionPostSolveCallbackFunc(cpArbiter *arb, cpSpace *space, PhysicsWorld *world);
    static void collisionSeparateCallbackFunc(cpArbiter *arb, cpSpace *space, PhysicsWorld *world);
    static void rayCastCallbackFunc(cpShape *shape, cpFloat t, cpVect n, RayCastCallbackInfo *info);
    static void queryRectCallbackFunc(cpShape *shape, RectQueryCallbackInfo *info);
    static void queryPointFunc(cpShape *shape, cpFloat distance, cpVect point, PointQueryCallbackInfo *info);
    static void getShapesAtPointFunc(cpShape *shape, cpFloat distance, cpVect point, Vector<PhysicsShape*>* arr);
    
public:
    static bool continues;
};

bool PhysicsWorldCallback::continues = true;

int PhysicsWorldCallback::collisionBeginCallbackFunc(cpArbiter *arb, struct cpSpace *space, PhysicsWorld *world)
{
    CP_ARBITER_GET_SHAPES(arb, a, b);
    
    auto ita = s_physicsShapeMap.find(a);
    auto itb = s_physicsShapeMap.find(b);
    CC_ASSERT(ita != s_physicsShapeMap.end() && itb != s_physicsShapeMap.end());
    
    auto contact = PhysicsContact::construct(ita->second, itb->second);
    arb->data = contact;
    contact->_contactInfo = arb;
    
    return world->collisionBeginCallback(*contact);
}

int PhysicsWorldCallback::collisionPreSolveCallbackFunc(cpArbiter *arb, cpSpace *space, PhysicsWorld *world)
{
    return world->collisionPreSolveCallback(*static_cast<PhysicsContact*>(arb->data));
}

void PhysicsWorldCallback::collisionPostSolveCallbackFunc(cpArbiter *arb, cpSpace *space, PhysicsWorld *world)
{
    world->collisionPostSolveCallback(*static_cast<PhysicsContact*>(arb->data));
}

void PhysicsWorldCallback::collisionSeparateCallbackFunc(cpArbiter *arb, cpSpace *space, PhysicsWorld *world)
{
    PhysicsContact* contact = static_cast<PhysicsContact*>(arb->data);
    
    world->collisionSeparateCallback(*contact);
    
    delete contact;
}

void PhysicsWorldCallback::rayCastCallbackFunc(cpShape *shape, cpFloat t, cpVect n, RayCastCallbackInfo *info)
{
    if (!PhysicsWorldCallback::continues)
    {
        return;
    }
    
    auto it = s_physicsShapeMap.find(shape);
    CC_ASSERT(it != s_physicsShapeMap.end());
    
    PhysicsRayCastInfo callbackInfo =
    {
        it->second,
        info->p1,
        info->p2,
        Vec2(info->p1.x+(info->p2.x-info->p1.x)*t, info->p1.y+(info->p2.y-info->p1.y)*t),
        Vec2(n.x, n.y),
        (float)t,
    };
    
    PhysicsWorldCallback::continues = info->func(*info->world, callbackInfo, info->data);
}

void PhysicsWorldCallback::queryRectCallbackFunc(cpShape *shape, RectQueryCallbackInfo *info)
{
    auto it = s_physicsShapeMap.find(shape);
    
    CC_ASSERT(it != s_physicsShapeMap.end());
    
    if (!PhysicsWorldCallback::continues)
    {
        return;
    }
    
    PhysicsWorldCallback::continues = info->func(*info->world, *it->second, info->data);
}

void PhysicsWorldCallback::getShapesAtPointFunc(cpShape *shape, cpFloat distance, cpVect point, Vector<PhysicsShape*>* arr)
{
    auto it = s_physicsShapeMap.find(shape);
    
    CC_ASSERT(it != s_physicsShapeMap.end());
    
    arr->pushBack(it->second);
}

void PhysicsWorldCallback::queryPointFunc(cpShape *shape, cpFloat distance, cpVect point, PointQueryCallbackInfo *info)
{
    auto it = s_physicsShapeMap.find(shape);
    
    CC_ASSERT(it != s_physicsShapeMap.end());
    
    PhysicsWorldCallback::continues = info->func(*info->world, *it->second, info->data);
}

void PhysicsWorld::debugDraw()
{
    if (_debugDraw == nullptr)
    {
        _debugDraw = new (std::nothrow) PhysicsDebugDraw(*this);
    }
    
    if (_debugDraw && !_bodies.empty())
    {
        if (_debugDraw->begin())
        {
            if (_debugDrawMask & DEBUGDRAW_SHAPE)
            {
                for (Ref* obj : _bodies)
                {
                    PhysicsBody* body = dynamic_cast<PhysicsBody*>(obj);
                    
                    if (!body->isEnabled())
                    {
                        continue;
                    }
                    
                    for (auto& shape : body->getShapes())
                    {
                        _debugDraw->drawShape(*dynamic_cast<PhysicsShape*>(shape));
                    }
                }
            }
            
            if (_debugDrawMask & DEBUGDRAW_JOINT)
            {
                for (auto joint : _joints)
                {
                    _debugDraw->drawJoint(*joint);
                }
            }
            
            _debugDraw->end();
        }
    }
}

int PhysicsWorld::collisionBeginCallback(PhysicsContact& contact)
{
    bool ret = true;
    
    PhysicsShape* shapeA = contact.getShapeA();
    PhysicsShape* shapeB = contact.getShapeB();
    PhysicsBody* bodyA = shapeA->getBody();
    PhysicsBody* bodyB = shapeB->getBody();
    std::vector<PhysicsJoint*> jointsA = bodyA->getJoints();
    
    // check the joint is collision enable or not
    for (PhysicsJoint* joint : jointsA)
    {
        if (std::find(_joints.begin(), _joints.end(), joint) == _joints.end())
        {
            continue;
        }
        
        if (!joint->isCollisionEnabled())
        {
            PhysicsBody* body = joint->getBodyA() == bodyA ? joint->getBodyB() : joint->getBodyA();
            
            if (body == bodyB)
            {
                contact.setNotificationEnable(false);
                return false;
            }
        }
    }
    
    // bitmask check
    if ((shapeA->getCategoryBitmask() & shapeB->getContactTestBitmask()) == 0
        || (shapeA->getContactTestBitmask() & shapeB->getCategoryBitmask()) == 0)
    {
        contact.setNotificationEnable(false);
    }
    
    if (shapeA->getGroup() != 0 && shapeA->getGroup() == shapeB->getGroup())
    {
        ret = shapeA->getGroup() > 0;
    }
    else
    {
        if ((shapeA->getCategoryBitmask() & shapeB->getCollisionBitmask()) == 0
            || (shapeB->getCategoryBitmask() & shapeA->getCollisionBitmask()) == 0)
        {
            ret = false;
        }
    }
    
    if (contact.isNotificationEnabled())
    {
        contact.setEventCode(PhysicsContact::EventCode::BEGIN);
        contact.setWorld(this);
        _eventDispatcher->dispatchEvent(&contact);
    }
    
    return ret ? contact.resetResult() : false;
}

int PhysicsWorld::collisionPreSolveCallback(PhysicsContact& contact)
{
    if (!contact.isNotificationEnabled())
    {
        return true;
    }
    
    contact.setEventCode(PhysicsContact::EventCode::PRESOLVE);
    contact.setWorld(this);
    _eventDispatcher->dispatchEvent(&contact);
    
    return contact.resetResult();
}

void PhysicsWorld::collisionPostSolveCallback(PhysicsContact& contact)
{
    if (!contact.isNotificationEnabled())
    {
        return;
    }
    
    contact.setEventCode(PhysicsContact::EventCode::POSTSOLVE);
    contact.setWorld(this);
    _eventDispatcher->dispatchEvent(&contact);
}

void PhysicsWorld::collisionSeparateCallback(PhysicsContact& contact)
{
    if (!contact.isNotificationEnabled())
    {
        return;
    }
    
    contact.setEventCode(PhysicsContact::EventCode::SEPARATE);
    contact.setWorld(this);
    _eventDispatcher->dispatchEvent(&contact);
}

void PhysicsWorld::rayCast(PhysicsRayCastCallbackFunc func, const Vec2& point1, const Vec2& point2, void* data)
{
    CCASSERT(func != nullptr, "func shouldn't be nullptr");
    
    if (func != nullptr)
    {
        if (!_delayAddBodies.empty() || !_delayRemoveBodies.empty())
        {
            updateBodies();
        }
        RayCastCallbackInfo info = { this, func, point1, point2, data };
        
        PhysicsWorldCallback::continues = true;
        cpSpaceSegmentQuery(_cpSpace,
                            PhysicsHelper::point2cpv(point1),
                            PhysicsHelper::point2cpv(point2),
                            CP_ALL_LAYERS,
                            CP_NO_GROUP,
                            (cpSpaceSegmentQueryFunc)PhysicsWorldCallback::rayCastCallbackFunc,
                            &info);
    }
}

void PhysicsWorld::queryRect(PhysicsQueryRectCallbackFunc func, const Rect& rect, void* data)
{
    CCASSERT(func != nullptr, "func shouldn't be nullptr");
    
    if (func != nullptr)
    {
        if (!_delayAddBodies.empty() || !_delayRemoveBodies.empty())
        {
            updateBodies();
        }
        RectQueryCallbackInfo info = {this, func, data};
        
        PhysicsWorldCallback::continues = true;
        cpSpaceBBQuery(_cpSpace,
                       PhysicsHelper::rect2cpbb(rect),
                       CP_ALL_LAYERS,
                       CP_NO_GROUP,
                       (cpSpaceBBQueryFunc)PhysicsWorldCallback::queryRectCallbackFunc,
                       &info);
    }
}

void PhysicsWorld::queryPoint(PhysicsQueryPointCallbackFunc func, const Vec2& point, void* data)
{
    CCASSERT(func != nullptr, "func shouldn't be nullptr");
    
    if (func != nullptr)
    {
        if (!_delayAddBodies.empty() || !_delayRemoveBodies.empty())
        {
            updateBodies();
        }
        PointQueryCallbackInfo info = {this, func, data};
        
        PhysicsWorldCallback::continues = true;
        cpSpaceNearestPointQuery(_cpSpace,
                                 PhysicsHelper::point2cpv(point),
                                 0,
                                 CP_ALL_LAYERS,
                                 CP_NO_GROUP,
                                 (cpSpaceNearestPointQueryFunc)PhysicsWorldCallback::queryPointFunc,
                                 &info);
    }
}

Vector<PhysicsShape*> PhysicsWorld::getShapes(const Vec2& point) const
{
    Vector<PhysicsShape*> arr;
    cpSpaceNearestPointQuery(_cpSpace,
                             PhysicsHelper::point2cpv(point),
                             0,
                             CP_ALL_LAYERS,
                             CP_NO_GROUP,
                             (cpSpaceNearestPointQueryFunc)PhysicsWorldCallback::getShapesAtPointFunc,
                             &arr);
    
    return arr;
}

PhysicsShape* PhysicsWorld::getShape(const Vec2& point) const
{
    cpShape* shape = cpSpaceNearestPointQueryNearest(_cpSpace,
                                    PhysicsHelper::point2cpv(point),
                                    0,
                                    CP_ALL_LAYERS,
                                    CP_NO_GROUP,
                                    nullptr);
    
    return shape == nullptr ? nullptr : s_physicsShapeMap.find(shape)->second;
}

bool PhysicsWorld::init()
{
    do
    {
        _cpSpace = cpSpaceNew();
        CC_BREAK_IF(_cpSpace == nullptr);
        
        cpSpaceSetGravity(_cpSpace, PhysicsHelper::point2cpv(_gravity));
        
        cpSpaceSetDefaultCollisionHandler(_cpSpace,
                                          (cpCollisionBeginFunc)PhysicsWorldCallback::collisionBeginCallbackFunc,
                                          (cpCollisionPreSolveFunc)PhysicsWorldCallback::collisionPreSolveCallbackFunc,
                                          (cpCollisionPostSolveFunc)PhysicsWorldCallback::collisionPostSolveCallbackFunc,
                                          (cpCollisionSeparateFunc)PhysicsWorldCallback::collisionSeparateCallbackFunc,
                                          this);
        
        return true;
    } while (false);
    
    return false;
}

void PhysicsWorld::addBody(PhysicsBody* body)
{
    CCASSERT(body != nullptr, "the body can not be nullptr");
    
    if (body->getWorld() == this)
    {
        return;
    }
    
    if (body->getWorld() != nullptr)
    {
        body->removeFromWorld();
    }
    
    addBodyOrDelay(body);
    _bodies.pushBack(body);
    body->_world = this;
}

void PhysicsWorld::doAddBody(PhysicsBody* body)
{
    if (body->isEnabled())
    {
        // add body to space
        if (body->isDynamic() && !cpSpaceContainsBody(_cpSpace, body->_cpBody))
        {
            cpSpaceAddBody(_cpSpace, body->_cpBody);
        }
        
        // add shapes to space
        for (auto& shape : body->getShapes())
        {
            addShape(dynamic_cast<PhysicsShape*>(shape));
        }
    }
}

void PhysicsWorld::addBodyOrDelay(PhysicsBody* body)
{
    auto removeBodyIter = _delayRemoveBodies.find(body);
    if (removeBodyIter != _delayRemoveBodies.end())
    {
        _delayRemoveBodies.erase(removeBodyIter);
        return;
    }
    
    if (_delayAddBodies.find(body) == _delayAddBodies.end())
    {
        _delayAddBodies.pushBack(body);
    }
}

void PhysicsWorld::updateBodies()
{
    if (cpSpaceIsLocked(_cpSpace))
    {
        return;
    }
    
    // issue #4944, contact callback will be invoked when add/remove body, _delayAddBodies maybe changed, so we need make a copy.
    auto addCopy = _delayAddBodies;
    _delayAddBodies.clear();
    for (auto& body : addCopy)
    {
        doAddBody(body);
    }
    
    auto removeCopy = _delayRemoveBodies;
    _delayRemoveBodies.clear();
    for (auto& body : removeCopy)
    {
        doRemoveBody(body);
    }
}

void PhysicsWorld::removeBody(int tag)
{
    for (auto& body : _bodies)
    {
        if (body->getTag() == tag)
        {
            removeBody(body);
            return;
        }
    }
}

void PhysicsWorld::removeBody(PhysicsBody* body)
{
    if (body->getWorld() != this)
    {
        CCLOG("Physics Warning: this body doesn't belong to this world");
        return;
    }
    
    // destroy the body's joints
    auto removeCopy = body->_joints;
    for (auto joint : removeCopy)
    {
        removeJoint(joint, true);
    }
    body->_joints.clear();
    
    removeBodyOrDelay(body);
    _bodies.eraseObject(body);
    body->_world = nullptr;
}

void PhysicsWorld::removeBodyOrDelay(PhysicsBody* body)
{
    if (_delayAddBodies.getIndex(body) != CC_INVALID_INDEX)
    {
        _delayAddBodies.eraseObject(body);
        return;
    }
    
    if (cpSpaceIsLocked(_cpSpace))
    {
        if (_delayRemoveBodies.getIndex(body) == CC_INVALID_INDEX)
        {
            _delayRemoveBodies.pushBack(body);
        }
    }else
    {
        doRemoveBody(body);
    }
}

void PhysicsWorld::removeJoint(PhysicsJoint* joint, bool destroy)
{
    if (joint)
    {
        if (joint->getWorld() != this && destroy)
        {
            CCLOG("physics warning: the joint is not in this world, it won't be destroyed until the body it connects is destroyed");
            return;
        }

        joint->_destoryMark = destroy;
        if (cpSpaceIsLocked(_cpSpace))
        {
            auto it = std::find(_delayAddJoints.begin(), _delayAddJoints.end(), joint);
            if (it != _delayAddJoints.end())
            {
                _delayAddJoints.erase(it);
                return;
            }

            if (std::find(_delayRemoveJoints.rbegin(), _delayRemoveJoints.rend(), joint) == _delayRemoveJoints.rend())
            {
                _delayRemoveJoints.push_back(joint);
            }
        }
        else
        {
            doRemoveJoint(joint);
        }
    }
}

void PhysicsWorld::updateJoints()
{
    if (cpSpaceIsLocked(_cpSpace))
    {
        return;
    }
    
    for (auto joint : _delayAddJoints)
    {
        joint->_world = this;
        if (joint->initJoint())
        {
            _joints.push_back(joint);
        }
        else
        {
            delete joint;
        }
    }
    _delayAddJoints.clear();

    for (auto joint : _delayRemoveJoints)
    {
        doRemoveJoint(joint);
    }
    _delayRemoveJoints.clear();
}

void PhysicsWorld::removeShape(PhysicsShape* shape)
{
    if (shape)
    {
        for (auto cps : shape->_cpShapes)
        {
            if (cpSpaceContainsShape(_cpSpace, cps))
            {
                cpSpaceRemoveShape(_cpSpace, cps);
            }
        }
    }
}

void PhysicsWorld::addJoint(PhysicsJoint* joint)
{
    if (joint)
    {
        if (joint->getWorld() && joint->getWorld() != this)
        {
            joint->removeFormWorld();
        }

        auto it = std::find(_delayRemoveJoints.begin(), _delayRemoveJoints.end(), joint);
        if (it != _delayRemoveJoints.end())
        {
            _delayRemoveJoints.erase(it);
            return;
        }

        if (std::find(_delayAddJoints.begin(), _delayAddJoints.end(), joint) == _delayAddJoints.end())
        {
            _delayAddJoints.push_back(joint);
        }
    }
}

void PhysicsWorld::removeAllJoints(bool destroy)
{
    auto removeCopy = _joints;
    for (auto joint : removeCopy)
    {
        removeJoint(joint, destroy);
    }
}

void PhysicsWorld::addShape(PhysicsShape* physicsShape)
{
    if (physicsShape)
    {
        for (auto shape : physicsShape->_cpShapes)
        {
            cpSpaceAddShape(_cpSpace, shape);
        }
    }
}

void PhysicsWorld::doRemoveBody(PhysicsBody* body)
{
    CCASSERT(body != nullptr, "the body can not be nullptr");
    
    // remove shapes
    for (auto& shape : body->getShapes())
    {
        removeShape(shape);
    }
    
    // remove body
    if (cpSpaceContainsBody(_cpSpace, body->_cpBody))
    {
        cpSpaceRemoveBody(_cpSpace, body->_cpBody);
    }
}

void PhysicsWorld::doRemoveJoint(PhysicsJoint* joint)
{
    for (auto constraint : joint->_cpConstraints)
    {
        cpSpaceRemoveConstraint(_cpSpace, constraint);
    }
    _joints.remove(joint);
    joint->_world = nullptr;

    if (joint->getBodyA())
    {
        joint->getBodyA()->removeJoint(joint);
    }

    if (joint->getBodyB())
    {
        joint->getBodyB()->removeJoint(joint);
    }

    if (joint->_destoryMark)
    {
        delete joint;
    }
}

void PhysicsWorld::removeAllBodies()
{
    for (auto& child : _bodies)
    {
        removeBodyOrDelay(child);
        child->_world = nullptr;
    }
    
    _bodies.clear();
}

void PhysicsWorld::setDebugDrawMask(int mask)
{
    if (mask == DEBUGDRAW_NONE)
    {
        CC_SAFE_DELETE(_debugDraw);
    }
    
    _debugDrawMask = mask;
}

const Vector<PhysicsBody*>& PhysicsWorld::getAllBodies() const
{
    return _bodies;
}

PhysicsBody* PhysicsWorld::getBody(int tag) const
{
    for (auto& body : _bodies)
    {
        if (body->getTag() == tag)
        {
            return body;
        }
    }
    
    return nullptr;
}

void PhysicsWorld::setGravity(const Vec2& gravity)
{
    _gravity = gravity;
    cpSpaceSetGravity(_cpSpace, PhysicsHelper::point2cpv(gravity));
}

void PhysicsWorld::setSubsteps(int steps)
{
    if(steps > 0)
    {
        _substeps = steps;
        if (steps > 1)
        {
          _updateRate = 1;
        }
    }
}

void PhysicsWorld::step(float delta)
{
    if (_autoStep)
    {
        CCLOG("Physics Warning: You need to close auto step( setAutoStep(false) ) first");
    }
    else
    {
        update(delta, true);
    }
}

void PhysicsWorld::update(float delta, bool userCall/* = false*/)
{
    if(!_delayAddBodies.empty())
    {
        updateBodies();
    }
    else if (!_delayRemoveBodies.empty())
    {
        updateBodies();
    }
    
    auto sceneToWorldTransform = _scene->getNodeToParentTransform();
    beforeSimulation(_scene, sceneToWorldTransform, 1.f, 1.f, 0.f);

    if (!_delayAddJoints.empty() || !_delayRemoveJoints.empty())
    {
        updateJoints();
    }
    
    if (delta < FLT_EPSILON)
    {
        return;
    }
    
    if (userCall)
    {
        cpSpaceStep(_cpSpace, delta);
        for (auto& body : _bodies)
        {
            body->update(delta);
        }
    }
    else
    {
        _updateTime += delta;
        if (++_updateRateCount >= _updateRate)
        {
            const float dt = _updateTime * _speed / _substeps;
            for (int i = 0; i < _substeps; ++i)
            {
                cpSpaceStep(_cpSpace, dt);
                for (auto& body : _bodies)
                {
                    body->update(dt);
                }
            }
            _updateRateCount = 0;
            _updateTime = 0.0f;
        }
    }
    
    if (_debugDrawMask != DEBUGDRAW_NONE)
    {
        debugDraw();
    }

    // Update physics position, should loop as the same sequence as node tree.
    // PhysicsWorld::afterSimulation() will depend on the sequence.
    afterSimulation(_scene, sceneToWorldTransform, 0.f);
}

PhysicsWorld* PhysicsWorld::construct(Scene* scene)
{
    PhysicsWorld * world = new (std::nothrow) PhysicsWorld();
    if (world && world->init())
    {
        world->_scene = scene;
        world->_eventDispatcher = scene->getEventDispatcher();
        return world;
    }

    CC_SAFE_DELETE(world);
    return nullptr;
}

PhysicsWorld::PhysicsWorld()
: _gravity(Vec2(0.0f, -98.0f))
, _speed(1.0f)
, _updateRate(1)
, _updateRateCount(0)
, _updateTime(0.0f)
, _substeps(1)
, _cpSpace(nullptr)
, _updateBodyTransform(false)
, _scene(nullptr)
, _autoStep(true)
, _debugDraw(nullptr)
, _debugDrawMask(DEBUGDRAW_NONE)
, _eventDispatcher(nullptr)
{
    
}

PhysicsWorld::~PhysicsWorld()
{
    removeAllJoints(true);
    removeAllBodies();
    if (_cpSpace)
    {
        cpSpaceFree(_cpSpace);
    }
    CC_SAFE_DELETE(_debugDraw);
}

void PhysicsWorld::beforeSimulation(Node *node, const Mat4& parentToWorldTransform, float nodeParentScaleX, float nodeParentScaleY, float parentRotation)
{
    auto scaleX = nodeParentScaleX * node->getScaleX();
    auto scaleY = nodeParentScaleY * node->getScaleY();
    auto rotation = parentRotation + node->getRotation();

    auto nodeToWorldTransform = parentToWorldTransform * node->getNodeToParentTransform();

    auto physicsBody = node->getPhysicsBody();
    if (physicsBody)
    {
        physicsBody->beforeSimulation(parentToWorldTransform, nodeToWorldTransform, scaleX, scaleY, rotation);
    }

    for (auto child : node->getChildren())
        beforeSimulation(child, nodeToWorldTransform, scaleX, scaleY, rotation);
}

void PhysicsWorld::afterSimulation(Node *node, const Mat4& parentToWorldTransform, float parentRotation)
{
    auto nodeToWorldTransform = parentToWorldTransform * node->getNodeToParentTransform();
    auto nodeRotation = parentRotation + node->getRotation();

    auto physicsBody = node->getPhysicsBody();
    if (physicsBody)
    {
        physicsBody->afterSimulation(parentToWorldTransform, parentRotation);
    }

    for (auto child : node->getChildren())
        afterSimulation(child, nodeToWorldTransform, nodeRotation);
}


PhysicsDebugDraw::PhysicsDebugDraw(PhysicsWorld& world)
: _drawNode(nullptr)
, _world(world)
{
    _drawNode = DrawNode::create();
    Director::getInstance()->getRunningScene()->addChild(_drawNode);
}

PhysicsDebugDraw::~PhysicsDebugDraw()
{
    _drawNode->removeFromParent();
    _drawNode = nullptr;
}

bool PhysicsDebugDraw::begin()
{
    _drawNode->clear();
    return true;
}

void PhysicsDebugDraw::end()
{
}

void PhysicsDebugDraw::drawShape(PhysicsShape& shape)
{
    const Color4F fillColor(1.0f, 0.0f, 0.0f, 0.3f);
    const Color4F outlineColor(1.0f, 0.0f, 0.0f, 1.0f);
    
    for (auto it = shape._cpShapes.begin(); it != shape._cpShapes.end(); ++it)
    {
        cpShape *subShape = *it;
        
        switch ((*it)->klass_private->type)
        {
            case CP_CIRCLE_SHAPE:
            {
                
                float radius = PhysicsHelper::cpfloat2float(cpCircleShapeGetRadius(subShape));
                Vec2 centre = PhysicsHelper::cpv2point(cpBodyGetPos(cpShapeGetBody(subShape)));
                Vec2 offset = PhysicsHelper::cpv2point(cpCircleShapeGetOffset(subShape));
                Vec2 rotation(PhysicsHelper::cpv2point(cpBodyGetRot(cpShapeGetBody(subShape))));
		              centre += offset.rotate(rotation);
                
                static const int CIRCLE_SEG_NUM = 12;
                Vec2 seg[CIRCLE_SEG_NUM] = {};
                
                for (int i = 0; i < CIRCLE_SEG_NUM; ++i)
                {
                    float angle = (float)i * M_PI / (float)CIRCLE_SEG_NUM * 2.0f;
                    Vec2 d(radius * cosf(angle), radius * sinf(angle));
                    seg[i] = centre + d;
                }
                _drawNode->drawPolygon(seg, CIRCLE_SEG_NUM, fillColor, 1, outlineColor);
                break;
            }
            case CP_SEGMENT_SHAPE:
            {
                cpSegmentShape *seg = (cpSegmentShape *)subShape;
                _drawNode->drawSegment(PhysicsHelper::cpv2point(seg->ta),
                                      PhysicsHelper::cpv2point(seg->tb),
                                      PhysicsHelper::cpfloat2float(seg->r==0 ? 1 : seg->r), outlineColor);
                break;
            }
            case CP_POLY_SHAPE:
            {
                cpPolyShape* poly = (cpPolyShape*)subShape;
                int num = poly->numVerts;
                Vec2* seg = new (std::nothrow) Vec2[num];
                
                PhysicsHelper::cpvs2points(poly->tVerts, seg, num);
                
                _drawNode->drawPolygon(seg, num, fillColor, 1.0f, outlineColor);
                
                delete[] seg;
                break;
            }
            default:
                break;
        }
    }
}

void PhysicsDebugDraw::drawJoint(PhysicsJoint& joint)
{
    const Color4F lineColor(0.0f, 0.0f, 1.0f, 1.0f);
    const Color4F jointPointColor(0.0f, 1.0f, 0.0f, 1.0f);
    
    for (auto it = joint._cpConstraints.begin(); it != joint._cpConstraints.end(); ++it)
    {
        cpConstraint *constraint = *it;
        
        
        cpBody *body_a = constraint->a;
        cpBody *body_b = constraint->b;
        
        const cpConstraintClass *klass = constraint->klass_private;
        if(klass == cpPinJointGetClass())
        {
            cpPinJoint *subJoint = (cpPinJoint *)constraint;
            
            cpVect a = cpvadd(body_a->p, cpvrotate(subJoint->anchr1, body_a->rot));
            cpVect b = cpvadd(body_b->p, cpvrotate(subJoint->anchr2, body_b->rot));
            
            _drawNode->drawSegment(PhysicsHelper::cpv2point(a), PhysicsHelper::cpv2point(b), 1, lineColor);
            _drawNode->drawDot(PhysicsHelper::cpv2point(a), 2, jointPointColor);
            _drawNode->drawDot(PhysicsHelper::cpv2point(b), 2, jointPointColor);
        }
        else if(klass == cpSlideJointGetClass())
        {
            cpSlideJoint *subJoint = (cpSlideJoint *)constraint;
            
            cpVect a = cpvadd(body_a->p, cpvrotate(subJoint->anchr1, body_a->rot));
            cpVect b = cpvadd(body_b->p, cpvrotate(subJoint->anchr2, body_b->rot));
            
            _drawNode->drawSegment(PhysicsHelper::cpv2point(a), PhysicsHelper::cpv2point(b), 1, lineColor);
            _drawNode->drawDot(PhysicsHelper::cpv2point(a), 2, jointPointColor);
            _drawNode->drawDot(PhysicsHelper::cpv2point(b), 2, jointPointColor);
        }
        else if(klass == cpPivotJointGetClass())
        {
            cpPivotJoint *subJoint = (cpPivotJoint *)constraint;
            
            cpVect a = cpvadd(body_a->p, cpvrotate(subJoint->anchr1, body_a->rot));
            cpVect b = cpvadd(body_b->p, cpvrotate(subJoint->anchr2, body_b->rot));
            
            _drawNode->drawDot(PhysicsHelper::cpv2point(a), 2, jointPointColor);
            _drawNode->drawDot(PhysicsHelper::cpv2point(b), 2, jointPointColor);
        }
        else if(klass == cpGrooveJointGetClass())
        {
            cpGrooveJoint *subJoint = (cpGrooveJoint *)constraint;
            
            cpVect a = cpvadd(body_a->p, cpvrotate(subJoint->grv_a, body_a->rot));
            cpVect b = cpvadd(body_a->p, cpvrotate(subJoint->grv_b, body_a->rot));
            cpVect c = cpvadd(body_b->p, cpvrotate(subJoint->anchr2, body_b->rot));
            
            _drawNode->drawSegment(PhysicsHelper::cpv2point(a), PhysicsHelper::cpv2point(b), 1, lineColor);
            _drawNode->drawDot(PhysicsHelper::cpv2point(c), 2, jointPointColor);
        }
        else if(klass == cpDampedSpringGetClass())
        {
            cpDampedSpring *subJoint = (cpDampedSpring *)constraint;
            
            cpVect a = cpvadd(body_a->p, cpvrotate(subJoint->anchr1, body_a->rot));
            cpVect b = cpvadd(body_b->p, cpvrotate(subJoint->anchr2, body_b->rot));
            
            _drawNode->drawSegment(PhysicsHelper::cpv2point(a), PhysicsHelper::cpv2point(b), 1, lineColor);
            _drawNode->drawDot(PhysicsHelper::cpv2point(a), 2, jointPointColor);
            _drawNode->drawDot(PhysicsHelper::cpv2point(b), 2, jointPointColor);
        }
    }
}

void PhysicsDebugDraw::drawContact()
{
    
}

NS_CC_END

#endif // CC_USE_PHYSICS
