/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

#include "CCPhysicsWorld.h"
#ifdef CC_USE_PHYSICS

#include <climits>

#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)
#include "chipmunk.h"
#elif (CC_PHYSICS_ENGINE == CCPHYSICS_BOX2D)
#include "Box2D.h"
#endif

#include "CCPhysicsBody.h"
#include "CCPhysicsShape.h"
#include "CCPhysicsContact.h"
#include "CCPhysicsJoint.h"
#include "CCPhysicsContact.h"

#include "chipmunk/CCPhysicsWorldInfo_chipmunk.h"
#include "box2d/CCPhysicsWorldInfo_box2d.h"
#include "chipmunk/CCPhysicsBodyInfo_chipmunk.h"
#include "box2d/CCPhysicsBodyInfo_box2d.h"
#include "chipmunk/CCPhysicsShapeInfo_chipmunk.h"
#include "box2d/CCPhysicsShapeInfo_box2d.h"
#include "chipmunk/CCPhysicsContactInfo_chipmunk.h"
#include "box2d/CCPhysicsContactInfo_box2d.h"
#include "chipmunk/CCPhysicsJointInfo_chipmunk.h"
#include "box2d/CCPhysicsJointInfo_box2d.h"
#include "chipmunk/CCPhysicsHelper_chipmunk.h"

#include "CCDrawNode.h"
#include "CCArray.h"
#include "CCScene.h"
#include "CCDirector.h"
#include "CCEventDispatcher.h"
#include "CCEventCustom.h"

#include <algorithm>

NS_CC_BEGIN

extern const char* PHYSICSCONTACT_EVENT_NAME;

#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)

const float PHYSICS_INFINITY = INFINITY;

namespace
{
    typedef struct RayCastCallbackInfo
    {
        PhysicsWorld* world;
        PhysicsRayCastCallbackFunc func;
        Point p1;
        Point p2;
        void* data;
    }RayCastCallbackInfo;
    
    typedef struct RectQueryCallbackInfo
    {
        PhysicsWorld* world;
        PhysicsRectQueryCallbackFunc func;
        void* data;
    }RectQueryCallbackInfo;
    
    typedef struct PointQueryCallbackInfo
    {
        PhysicsWorld* world;
        PhysicsPointQueryCallbackFunc func;
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
    static void getShapesAtPointFunc(cpShape *shape, cpFloat distance, cpVect point, Array *arr);
    
public:
    static bool continues;
};

bool PhysicsWorldCallback::continues = true;

int PhysicsWorldCallback::collisionBeginCallbackFunc(cpArbiter *arb, struct cpSpace *space, PhysicsWorld *world)
{
    CP_ARBITER_GET_SHAPES(arb, a, b);
    
    auto ita = PhysicsShapeInfo::getMap().find(a);
    auto itb = PhysicsShapeInfo::getMap().find(b);
    CC_ASSERT(ita != PhysicsShapeInfo::getMap().end() && itb != PhysicsShapeInfo::getMap().end());
    
    PhysicsContact* contact = PhysicsContact::construct(ita->second->getShape(), itb->second->getShape());
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
    
    auto it = PhysicsShapeInfo::getMap().find(shape);
    CC_ASSERT(it != PhysicsShapeInfo::getMap().end());
    
    PhysicsRayCastInfo callbackInfo =
    {
        it->second->getShape(),
        info->p1,
        info->p2,
        Point(info->p1.x+(info->p2.x-info->p1.x)*t, info->p1.y+(info->p2.y-info->p1.y)*t),
        Point(n.x, n.y),
        (float)t,
    };
    
    PhysicsWorldCallback::continues = info->func(*info->world, callbackInfo, info->data);
}

void PhysicsWorldCallback::queryRectCallbackFunc(cpShape *shape, RectQueryCallbackInfo *info)
{
    auto it = PhysicsShapeInfo::getMap().find(shape);
    
    CC_ASSERT(it != PhysicsShapeInfo::getMap().end());
    
    if (!PhysicsWorldCallback::continues)
    {
        return;
    }
    
    PhysicsWorldCallback::continues = info->func(*info->world, *it->second->getShape(), info->data);
}

void PhysicsWorldCallback::getShapesAtPointFunc(cpShape *shape, cpFloat distance, cpVect point, Array *arr)
{
    auto it = PhysicsShapeInfo::getMap().find(shape);
    
    CC_ASSERT(it != PhysicsShapeInfo::getMap().end());
    
    arr->addObject(it->second->getShape());
}

void PhysicsWorldCallback::queryPointFunc(cpShape *shape, cpFloat distance, cpVect point, PointQueryCallbackInfo *info)
{
    auto it = PhysicsShapeInfo::getMap().find(shape);
    
    CC_ASSERT(it != PhysicsShapeInfo::getMap().end());
    
    PhysicsWorldCallback::continues = info->func(*info->world, *it->second->getShape(), info->data);
}

bool PhysicsWorld::init(Scene& scene)
{
    do
    {
        _delayAddBodies = Array::create();
        _delayRemoveBodies = Array::create();
        CC_BREAK_IF(_delayAddBodies == nullptr || _delayRemoveBodies == nullptr);
        _delayAddBodies->retain();
        _delayRemoveBodies->retain();
        
        _info = new PhysicsWorldInfo();
        CC_BREAK_IF(_info == nullptr);
        _bodies = Array::create();
        CC_BREAK_IF(_bodies == nullptr);
        _bodies->retain();

        _scene = &scene;
        
        cpSpaceSetGravity(_info->getSpace(), PhysicsHelper::point2cpv(_gravity));
        
        cpSpaceSetDefaultCollisionHandler(_info->getSpace(),
                                          (cpCollisionBeginFunc)PhysicsWorldCallback::collisionBeginCallbackFunc,
                                          (cpCollisionPreSolveFunc)PhysicsWorldCallback::collisionPreSolveCallbackFunc,
                                          (cpCollisionPostSolveFunc)PhysicsWorldCallback::collisionPostSolveCallbackFunc,
                                          (cpCollisionSeparateFunc)PhysicsWorldCallback::collisionSeparateCallbackFunc,
                                          this);
        
        return true;
    } while (false);
    
    return false;
}

void PhysicsWorld::addBodyOrDelay(PhysicsBody* body)
{
    if (_delayRemoveBodies->getIndexOfObject(body) != CC_INVALID_INDEX)
    {
        _delayRemoveBodies->removeObject(body);
        return;
    }
    
    if (_info->getSpace()->locked_private)
    {
        if (_delayAddBodies->getIndexOfObject(body) == CC_INVALID_INDEX)
        {
            _delayAddBodies->addObject(body);
            _delayDirty = true;
        }
    }else
    {
        doAddBody(body);
    }
}

void PhysicsWorld::removeBodyOrDelay(PhysicsBody* body)
{
    if (_delayAddBodies->getIndexOfObject(body) != CC_INVALID_INDEX)
    {
        _delayAddBodies->removeObject(body);
        return;
    }
    
    if (_info->getSpace()->locked_private)
    {
        if (_delayRemoveBodies->getIndexOfObject(body) == CC_INVALID_INDEX)
        {
            _delayRemoveBodies->addObject(body);
            _delayDirty = true;
        }
    }else
    {
        doRemoveBody(body);
    }
}

void PhysicsWorld::addJointOrDelay(PhysicsJoint* joint)
{
    auto it = std::find(_delayRemoveJoints.begin(), _delayRemoveJoints.end(), joint);
    if (it != _delayRemoveJoints.end())
    {
        _delayRemoveJoints.erase(it);
        return;
    }
    
    if (_info->getSpace()->locked_private)
    {
        if (std::find(_delayAddJoints.begin(), _delayAddJoints.end(), joint) == _delayAddJoints.end())
        {
            _delayAddJoints.push_back(joint);
            _delayDirty = true;
        }
    }else
    {
        doAddJoint(joint);
    }
}

void PhysicsWorld::removeJointOrDelay(PhysicsJoint* joint)
{
    auto it = std::find(_delayAddJoints.begin(), _delayAddJoints.end(), joint);
    if (it != _delayAddJoints.end())
    {
        _delayAddJoints.erase(it);
        return;
    }
    
    if (_info->getSpace()->locked_private)
    {
        if (std::find(_delayRemoveJoints.begin(), _delayRemoveJoints.end(), joint) == _delayRemoveJoints.end())
        {
            _delayRemoveJoints.push_back(joint);
            _delayDirty = true;
        }
    }else
    {
        doRemoveJoint(joint);
    }
}

void PhysicsWorld::addJoint(PhysicsJoint* joint)
{
    if (joint->getWorld() != nullptr && joint->getWorld() != this)
    {
        joint->removeFormWorld();
    }
    
    addJointOrDelay(joint);
    _joints.push_back(joint);
    joint->_world = this;
}

void PhysicsWorld::removeJoint(PhysicsJoint* joint, bool destroy)
{
    if (joint->getWorld() != this)
    {
        if (destroy)
        {
            CCLOG("physics warnning: the joint is not in this world, it won't be destoried utill the body it conntect is destoried");
        }
        return;
    }
    
    removeJointOrDelay(joint);
    
    _joints.remove(joint);
    joint->_world = nullptr;
    
    // clean the connection to this joint
    if (destroy)
    {
        if (joint->getBodyA() != nullptr)
        {
            joint->getBodyA()->removeJoint(joint);
        }
        
        if (joint->getBodyB() != nullptr)
        {
            joint->getBodyB()->removeJoint(joint);
        }
        
        // test the distraction is delaied or not
        if (_delayRemoveJoints.size() > 0 && _delayRemoveJoints.back() == joint)
        {
            joint->_destoryMark = true;
        }
        else
        {
            delete joint;
        }
    }
}

void PhysicsWorld::removeAllJoints(bool destroy)
{
    for (auto joint : _joints)
    {
        removeJointOrDelay(joint);
        joint->_world = nullptr;
        
        // clean the connection to this joint
        if (destroy)
        {
            if (joint->getBodyA() != nullptr)
            {
                joint->getBodyA()->removeJoint(joint);
            }
            
            if (joint->getBodyB() != nullptr)
            {
                joint->getBodyB()->removeJoint(joint);
            }
            
            // test the distraction is delaied or not
            if (_delayRemoveJoints.size() > 0 && _delayRemoveJoints.back() == joint)
            {
                joint->_destoryMark = true;
            }
            else
            {
                delete joint;
            }
        }
    }
    
    _joints.clear();
}

void PhysicsWorld::addShape(PhysicsShape* shape)
{
    for (auto cps : shape->_info->getShapes())
    {
        _info->addShape(cps);
    }
    
    return;
}

void PhysicsWorld::doAddJoint(PhysicsJoint *joint)
{
    for (auto subjoint : joint->_info->getJoints())
    {
        _info->addJoint(subjoint);
    }
}

void PhysicsWorld::doAddBody(PhysicsBody* body)
{
    if (body->isEnabled())
    {
        //is gravity enable
        if (!body->isGravityEnabled())
        {
            body->applyForce(-_gravity);
        }
        
        // add body to space
        if (body->isDynamic())
        {
            _info->addBody(body->_info->getBody());
        }
        
        // add shapes to space
        for (auto shape : *body->getShapes())
        {
            addShape(dynamic_cast<PhysicsShape*>(shape));
        }
    }
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
    _bodies->addObject(body);
    body->_world = this;
}

void PhysicsWorld::removeBody(PhysicsBody* body)
{
    
    if (body->getWorld() != this)
    {
        CCLOG("Physics Warnning: this body doesn't belong to this world");
        return;
    }
    
    // destory the body's joints
    for (auto joint : body->_joints)
    {
        removeJoint(joint, true);
    }
    
    removeBodyOrDelay(body);
    _bodies->removeObject(body);
    body->_world = nullptr;
}

void PhysicsWorld::removeBody(int tag)
{
    for (Object* obj : *_bodies)
    {
        PhysicsBody* body = dynamic_cast<PhysicsBody*>(obj);
        if (body->getTag() == tag)
        {
            removeBody(body);
            return;
        }
    }
}

void PhysicsWorld::doRemoveBody(PhysicsBody* body)
{
    CCASSERT(body != nullptr, "the body can not be nullptr");
    
    // reset the gravity
    if (!body->isGravityEnabled())
    {
        body->applyForce(-_gravity);
    }
    
    // remove shaps
    for (auto shape : *body->getShapes())
    {
        removeShape(dynamic_cast<PhysicsShape*>(shape));
    }
    
    // remove body
    _info->removeBody(body->_info->getBody());
}

void PhysicsWorld::doRemoveJoint(PhysicsJoint* joint)
{
    for (auto subjoint : joint->_info->getJoints())
    {
        _info->removeJoint(subjoint);
    }
}

void PhysicsWorld::removeAllBodies()
{
    for (Object* obj : *_bodies)
    {
        PhysicsBody* child = dynamic_cast<PhysicsBody*>(obj);
        removeBodyOrDelay(child);
        child->_world = nullptr;
    }

    _bodies->removeAllObjects();
    CC_SAFE_RELEASE(_bodies);
}

void PhysicsWorld::removeShape(PhysicsShape* shape)
{
    for (auto cps : shape->_info->getShapes())
    {
        if (cpSpaceContainsShape(_info->getSpace(), cps))
        {
            cpSpaceRemoveShape(_info->getSpace(), cps);
        }
    }
}

void PhysicsWorld::updateBodies()
{
    if (_info->getSpace()->locked_private)
    {
        return;
    }
    
    for (auto body : *_delayAddBodies)
    {
        doAddBody(dynamic_cast<PhysicsBody*>(body));
    }
    
    for (auto body : *_delayRemoveBodies)
    {
        doRemoveBody(dynamic_cast<PhysicsBody*>(body));
    }
    
    _delayAddBodies->removeAllObjects();
    _delayRemoveBodies->removeAllObjects();
}

void PhysicsWorld::updateJoints()
{
    if (_info->getSpace()->locked_private)
    {
        return;
    }
    
    for (auto joint : _delayAddJoints)
    {
        doAddJoint(joint);
    }
    
    for (auto joint : _delayRemoveJoints)
    {
        doRemoveJoint(joint);
        
        if (joint->_destoryMark)
        {
            delete joint;
        }
    }
    
    _delayAddJoints.clear();
    _delayRemoveJoints.clear();
}

void PhysicsWorld::update(float delta)
{
    if (_delayDirty)
    {
        // the updateJoints must run before the updateBodies.
        updateJoints();
        updateBodies();
        _delayDirty = !(_delayAddBodies->count() == 0 && _delayRemoveBodies->count() == 0 && _delayAddJoints.size() == 0 && _delayRemoveJoints.size() == 0);
    }
    
    for (auto body : *_bodies)
    {
        body->update(delta);
    }
    
    cpSpaceStep(_info->getSpace(), delta);
    
    if (_debugDrawMask != DEBUGDRAW_NONE)
    {
        debugDraw();
    }
}

void PhysicsWorld::debugDraw()
{
    if (_debugDraw == nullptr)
    {
        _debugDraw = new PhysicsDebugDraw(*this);
    }
    
    if (_debugDraw && _bodies != nullptr)
    {
        if (_debugDraw->begin())
        {
            if (_debugDrawMask & DEBUGDRAW_SHAPE)
            {
                for (Object* obj : *_bodies)
                {
                    PhysicsBody* body = dynamic_cast<PhysicsBody*>(obj);
                    
                    for (auto shape : *body->getShapes())
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

void PhysicsWorld::setDebugDrawMask(int mask)
{
    if (mask == DEBUGDRAW_NONE)
    {
        CC_SAFE_DELETE(_debugDraw);
    }
    
    _debugDrawMask = mask;
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
        || (shapeB->getContactTestBitmask() & shapeA->getCategoryBitmask()) == 0)
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
    
    contact.setEventCode(PhysicsContact::EventCode::BEGIN);
    contact.setWorld(this);
    EventCustom event(PHYSICSCONTACT_EVENT_NAME);
    event.setUserData(&contact);
    _scene->getEventDispatcher()->dispatchEvent(&event);
    
    return ret ? contact.resetResult() : false;
}

int PhysicsWorld::collisionPreSolveCallback(PhysicsContact& contact)
{
    if (!contact.isNotificationEnabled())
    {
        cpArbiterIgnore(static_cast<cpArbiter*>(contact._contactInfo));
        return true;
    }
    
    contact.setEventCode(PhysicsContact::EventCode::PRESOLVE);
    contact.setWorld(this);
    EventCustom event(PHYSICSCONTACT_EVENT_NAME);
    event.setUserData(&contact);
    _scene->getEventDispatcher()->dispatchEvent(&event);
    
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
    EventCustom event(PHYSICSCONTACT_EVENT_NAME);
    event.setUserData(&contact);
    _scene->getEventDispatcher()->dispatchEvent(&event);
}

void PhysicsWorld::collisionSeparateCallback(PhysicsContact& contact)
{
    if (!contact.isNotificationEnabled())
    {
        return;
    }
    
    contact.setEventCode(PhysicsContact::EventCode::SEPERATE);
    contact.setWorld(this);
    EventCustom event(PHYSICSCONTACT_EVENT_NAME);
    event.setUserData(&contact);
    _scene->getEventDispatcher()->dispatchEvent(&event);
}

void PhysicsWorld::setGravity(const Vect& gravity)
{
    if (_bodies != nullptr)
    {
        for (auto child : *_bodies)
        {
            PhysicsBody* body = dynamic_cast<PhysicsBody*>(child);
            
            // reset gravity for body
            if (!body->isGravityEnabled())
            {
                body->applyForce(-_gravity);
                body->applyForce(gravity);
            }
        }
    }
    
    _gravity = gravity;
    cpSpaceSetGravity(_info->getSpace(), PhysicsHelper::point2cpv(gravity));
}


void PhysicsWorld::rayCast(PhysicsRayCastCallbackFunc func, const Point& point1, const Point& point2, void* data)
{
    CCASSERT(func != nullptr, "func shouldn't be nullptr");
    
    if (func != nullptr)
    {
        RayCastCallbackInfo info = { this, func, point1, point2, data };
        
        PhysicsWorldCallback::continues = true;
        cpSpaceSegmentQuery(this->_info->getSpace(),
                            PhysicsHelper::point2cpv(point1),
                            PhysicsHelper::point2cpv(point2),
                            CP_ALL_LAYERS,
                            CP_NO_GROUP,
                            (cpSpaceSegmentQueryFunc)PhysicsWorldCallback::rayCastCallbackFunc,
                            &info);
    }
}


void PhysicsWorld::queryRect(PhysicsRectQueryCallbackFunc func, const Rect& rect, void* data)
{
    CCASSERT(func != nullptr, "func shouldn't be nullptr");
    
    if (func != nullptr)
    {
        RectQueryCallbackInfo info = {this, func, data};
        
        PhysicsWorldCallback::continues = true;
        cpSpaceBBQuery(this->_info->getSpace(),
                       PhysicsHelper::rect2cpbb(rect),
                       CP_ALL_LAYERS,
                       CP_NO_GROUP,
                       (cpSpaceBBQueryFunc)PhysicsWorldCallback::queryRectCallbackFunc,
                       &info);
    }
}

void PhysicsWorld::queryPoint(PhysicsPointQueryCallbackFunc func, const Point& point, void* data)
{
    CCASSERT(func != nullptr, "func shouldn't be nullptr");
    
    if (func != nullptr)
    {
        PointQueryCallbackInfo info = {this, func, data};
        
        PhysicsWorldCallback::continues = true;
        cpSpaceNearestPointQuery(this->_info->getSpace(),
                                 PhysicsHelper::point2cpv(point),
                                 0,
                                 CP_ALL_LAYERS,
                                 CP_NO_GROUP,
                                 (cpSpaceNearestPointQueryFunc)PhysicsWorldCallback::queryPointFunc,
                                 &info);
    }
}

Array* PhysicsWorld::getShapes(const Point& point) const
{
    Array* arr = Array::create();
    cpSpaceNearestPointQuery(this->_info->getSpace(),
                             PhysicsHelper::point2cpv(point),
                             0,
                             CP_ALL_LAYERS,
                             CP_NO_GROUP,
                             (cpSpaceNearestPointQueryFunc)PhysicsWorldCallback::getShapesAtPointFunc,
                             arr);
    
    return arr;
}

PhysicsShape* PhysicsWorld::getShape(const Point& point) const
{
    cpShape* shape = cpSpaceNearestPointQueryNearest(this->_info->getSpace(),
                                    PhysicsHelper::point2cpv(point),
                                    0,
                                    CP_ALL_LAYERS,
                                    CP_NO_GROUP,
                                    nullptr);
    
    return shape == nullptr ? nullptr : PhysicsShapeInfo::getMap().find(shape)->second->getShape();
}

Array* PhysicsWorld::getAllBodies() const
{
    return _bodies;
}

PhysicsBody* PhysicsWorld::getBody(int tag) const
{
    for (auto body : *_bodies)
    {
        if (((PhysicsBody*)body)->getTag() == tag)
        {
            return (PhysicsBody*)body;
        }
    }
    
    return nullptr;
}



void PhysicsDebugDraw::drawShape(PhysicsShape& shape)
{
    for (auto it = shape._info->getShapes().begin(); it != shape._info->getShapes().end(); ++it)
    {
        cpShape *subShape = *it;
        
        switch ((*it)->klass_private->type)
        {
            case CP_CIRCLE_SHAPE:
            {
                float radius = PhysicsHelper::cpfloat2float(cpCircleShapeGetRadius(subShape));
                Point centre = PhysicsHelper::cpv2point(cpBodyGetPos(cpShapeGetBody(subShape)))
                + PhysicsHelper::cpv2point(cpCircleShapeGetOffset(subShape));
                
                static const int CIRCLE_SEG_NUM = 12;
                Point seg[CIRCLE_SEG_NUM] = {};
                
                for (int i = 0; i < CIRCLE_SEG_NUM; ++i)
                {
                    float angle = (float)i * M_PI / (float)CIRCLE_SEG_NUM * 2.0f;
                    Point d(radius * cosf(angle), radius * sinf(angle));
                    seg[i] = centre + d;
                }
                _drawNode->drawPolygon(seg, CIRCLE_SEG_NUM, Color4F(1.0f, 0.0f, 0.0f, 0.3f), 1, Color4F(1, 0, 0, 1));
                break;
            }
            case CP_SEGMENT_SHAPE:
            {
                cpSegmentShape *seg = (cpSegmentShape *)subShape;
                _drawNode->drawSegment(PhysicsHelper::cpv2point(seg->ta),
                                       PhysicsHelper::cpv2point(seg->tb),
                                       PhysicsHelper::cpfloat2float(seg->r==0 ? 1 : seg->r), Color4F(1, 0, 0, 1));
                break;
            }
            case CP_POLY_SHAPE:
            {
                cpPolyShape* poly = (cpPolyShape*)subShape;
                int num = poly->numVerts;
                Point* seg = new Point[num];
                
                PhysicsHelper::cpvs2points(poly->tVerts, seg, num);
                
                _drawNode->drawPolygon(seg, num, Color4F(1.0f, 0.0f, 0.0f, 0.3f), 1.0f, Color4F(1.0f, 0.0f, 0.0f, 1.0f));
                
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
    for (auto it = joint._info->getJoints().begin(); it != joint._info->getJoints().end(); ++it)
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
            
            _drawNode->drawSegment(PhysicsHelper::cpv2point(a), PhysicsHelper::cpv2point(b), 1, Color4F(0.0f, 0.0f, 1.0f, 1.0f));
            _drawNode->drawDot(PhysicsHelper::cpv2point(a), 2, Color4F(0.0f, 1.0f, 0.0f, 1.0f));
            _drawNode->drawDot(PhysicsHelper::cpv2point(b), 2, Color4F(0.0f, 1.0f, 0.0f, 1.0f));
        }
        else if(klass == cpSlideJointGetClass())
        {
            cpSlideJoint *subJoint = (cpSlideJoint *)constraint;
            
            cpVect a = cpvadd(body_a->p, cpvrotate(subJoint->anchr1, body_a->rot));
            cpVect b = cpvadd(body_b->p, cpvrotate(subJoint->anchr2, body_b->rot));
            
            _drawNode->drawSegment(PhysicsHelper::cpv2point(a), PhysicsHelper::cpv2point(b), 1, Color4F(0.0f, 0.0f, 1.0f, 1.0f));
            _drawNode->drawDot(PhysicsHelper::cpv2point(a), 2, Color4F(0.0f, 1.0f, 0.0f, 1.0f));
            _drawNode->drawDot(PhysicsHelper::cpv2point(b), 2, Color4F(0.0f, 1.0f, 0.0f, 1.0f));
        }
        else if(klass == cpPivotJointGetClass())
        {
            cpPivotJoint *subJoint = (cpPivotJoint *)constraint;
            
            cpVect a = cpvadd(body_a->p, cpvrotate(subJoint->anchr1, body_a->rot));
            cpVect b = cpvadd(body_b->p, cpvrotate(subJoint->anchr2, body_b->rot));
            
            _drawNode->drawDot(PhysicsHelper::cpv2point(a), 2, Color4F(0.0f, 1.0f, 0.0f, 1.0f));
            _drawNode->drawDot(PhysicsHelper::cpv2point(b), 2, Color4F(0.0f, 1.0f, 0.0f, 1.0f));
        }
        else if(klass == cpGrooveJointGetClass())
        {
            cpGrooveJoint *subJoint = (cpGrooveJoint *)constraint;
            
            cpVect a = cpvadd(body_a->p, cpvrotate(subJoint->grv_a, body_a->rot));
            cpVect b = cpvadd(body_a->p, cpvrotate(subJoint->grv_b, body_a->rot));
            cpVect c = cpvadd(body_b->p, cpvrotate(subJoint->anchr2, body_b->rot));
            
            _drawNode->drawSegment(PhysicsHelper::cpv2point(a), PhysicsHelper::cpv2point(b), 1, Color4F(0.0f, 0.0f, 1.0f, 1.0f));
            _drawNode->drawDot(PhysicsHelper::cpv2point(c), 2, Color4F(0.0f, 1.0f, 0.0f, 1.0f));
        }
    }
}

void PhysicsDebugDraw::drawContact()
{
    
}

#elif (CC_PHYSICS_ENGINE == CC_PHYSICS_BOX2D)

#endif

PhysicsWorld* PhysicsWorld::construct(Scene& scene)
{
    PhysicsWorld * world = new PhysicsWorld();
    if(world && world->init(scene))
    {
        return world;
    }
    
    CC_SAFE_DELETE(world);
    return nullptr;
}

PhysicsWorld::PhysicsWorld()
: _gravity(Point(0.0f, -98.0f))
, _speed(1.0f)
, _info(nullptr)
, _bodies(nullptr)
, _scene(nullptr)
, _delayDirty(false)
, _debugDraw(nullptr)
, _debugDrawMask(DEBUGDRAW_NONE)
, _delayAddBodies(nullptr)
, _delayRemoveBodies(nullptr)
{
    
}

PhysicsWorld::~PhysicsWorld()
{
    removeAllJoints(true);
    removeAllBodies();
    CC_SAFE_RELEASE(_delayRemoveBodies);
    CC_SAFE_RELEASE(_delayAddBodies);
    CC_SAFE_DELETE(_info);
    CC_SAFE_DELETE(_debugDraw);
}



PhysicsDebugDraw::PhysicsDebugDraw(PhysicsWorld& world)
: _drawNode(nullptr)
, _world(world)
{
}

PhysicsDebugDraw::~PhysicsDebugDraw()
{
    if (_drawNode != nullptr)
    {
        _drawNode->removeFromParent();
        _drawNode = nullptr;
    }
}

bool PhysicsDebugDraw::begin()
{
    if (_drawNode != nullptr)
    {
        _drawNode->removeFromParent();
        _drawNode = nullptr;
    }
    
    _drawNode = DrawNode::create();
    
    if (_drawNode == nullptr)
    {
        return false;
    }
    
    _world.getScene().addChild(_drawNode);
    
    return true;
}

void PhysicsDebugDraw::end()
{
}

NS_CC_END

#endif // CC_USE_PHYSICS
