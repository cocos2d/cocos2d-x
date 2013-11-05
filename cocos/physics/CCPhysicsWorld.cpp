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
        PhysicsRayCastCallback* callback;
        Point p1;
        Point p2;
        void* data;
    }RayCastCallbackInfo;
    
    typedef struct RectQueryCallbackInfo
    {
        PhysicsWorld* world;
        PhysicsRectQueryCallback* callback;
        void* data;
    }RectQueryCallbackInfo;
}

class PhysicsWorldCallback
{
public:
    static int collisionBeginCallbackFunc(cpArbiter *arb, struct cpSpace *space, PhysicsWorld *world);
    static int collisionPreSolveCallbackFunc(cpArbiter *arb, cpSpace *space, PhysicsWorld *world);
    static void collisionPostSolveCallbackFunc(cpArbiter *arb, cpSpace *space, PhysicsWorld *world);
    static void collisionSeparateCallbackFunc(cpArbiter *arb, cpSpace *space, PhysicsWorld *world);
    static void rayCastCallbackFunc(cpShape *shape, cpFloat t, cpVect n, RayCastCallbackInfo *info);
    static void rectQueryCallbackFunc(cpShape *shape, RectQueryCallbackInfo *info);
    static void nearestPointQueryFunc(cpShape *shape, cpFloat distance, cpVect point, Array *arr);
    
public:
    static bool continues;
};

bool PhysicsWorldCallback::continues = true;

int PhysicsWorldCallback::collisionBeginCallbackFunc(cpArbiter *arb, struct cpSpace *space, PhysicsWorld *world)
{
    CP_ARBITER_GET_SHAPES(arb, a, b);
    
    auto ita = PhysicsShapeInfo::map.find(a);
    auto itb = PhysicsShapeInfo::map.find(b);
    CC_ASSERT(ita != PhysicsShapeInfo::map.end() && itb != PhysicsShapeInfo::map.end());
    
    PhysicsContact* contact = PhysicsContact::create(ita->second->shape, itb->second->shape);
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
    
    auto it = PhysicsShapeInfo::map.find(shape);
    CC_ASSERT(it != PhysicsShapeInfo::map.end());
    
    PhysicsWorldCallback::continues = info->callback->report(*info->world,
                   *it->second->shape,
                   Point(info->p1.x+(info->p2.x-info->p1.x)*t, info->p1.y+(info->p2.y-info->p1.y)*t),
                   Point(n.x, n.y),
                   (float)t,
                   info->data);
}

void PhysicsWorldCallback::rectQueryCallbackFunc(cpShape *shape, RectQueryCallbackInfo *info)
{
    auto it = PhysicsShapeInfo::map.find(shape);
    
    CC_ASSERT(it != PhysicsShapeInfo::map.end());
    
    if (!PhysicsWorldCallback::continues)
    {
        return;
    }
    
    PhysicsWorldCallback::continues = info->callback->report(*info->world,
                                                             *it->second->shape,
                                                             info->data);
}

void PhysicsWorldCallback::nearestPointQueryFunc(cpShape *shape, cpFloat distance, cpVect point, Array *arr)
{
    auto it = PhysicsShapeInfo::map.find(shape);
    
    CC_ASSERT(it != PhysicsShapeInfo::map.end());
    
    arr->addObject(it->second->shape);
}

bool PhysicsWorld::init(Scene& scene)
{
    do
    {
        _info = new PhysicsWorldInfo();
        CC_BREAK_IF(_info == nullptr);
        _bodies = Array::create();
        CC_BREAK_IF(_bodies == nullptr);
        _bodies->retain();

        _scene = &scene;
        
        cpSpaceSetGravity(_info->space, PhysicsHelper::point2cpv(_gravity));
        
        cpSpaceSetDefaultCollisionHandler(_info->space,
                                          (cpCollisionBeginFunc)PhysicsWorldCallback::collisionBeginCallbackFunc,
                                          (cpCollisionPreSolveFunc)PhysicsWorldCallback::collisionPreSolveCallbackFunc,
                                          (cpCollisionPostSolveFunc)PhysicsWorldCallback::collisionPostSolveCallbackFunc,
                                          (cpCollisionSeparateFunc)PhysicsWorldCallback::collisionSeparateCallbackFunc,
                                          this);
        
        return true;
    } while (false);
    
    return false;
}

void PhysicsWorld::addJoint(PhysicsJoint* joint)
{
    auto it = std::find(_joints.begin(), _joints.end(), joint);
    
    if (it == _joints.end())
    {
        for (auto subjoint : joint->_info->joints)
        {
            if (!cpSpaceContainsConstraint(_info->space, subjoint))
            {
                cpSpaceAddConstraint(_info->space, subjoint);
            }
        }
        
        _joints.push_back(joint);
    }
    
}

void PhysicsWorld::removeJoint(PhysicsJoint* joint)
{
    auto it = std::find(_joints.begin(), _joints.end(), joint);
    
    if (it != _joints.end())
    {
        for (auto subjoint : joint->_info->joints)
        {
            if (cpSpaceContainsConstraint(_info->space, subjoint))
            {
                cpSpaceRemoveConstraint(_info->space, subjoint);
            }
        }
        
        _joints.remove(joint);
    }
}

void PhysicsWorld::removeAllJoints()
{
    for (auto joint : _joints)
    {
        for (auto subjoint : joint->_info->joints)
        {
            if (!cpSpaceContainsConstraint(_info->space, subjoint))
            {
                cpSpaceRemoveConstraint(_info->space, subjoint);
            }
        }
    }
    
    _joints.clear();
}

PhysicsShape* PhysicsWorld::addShape(PhysicsShape* shape)
{
    for (auto cps : shape->_info->shapes)
    {
        if (cpSpaceContainsShape(_info->space, cps))
        {
            continue;
        }
        
        if (cpBodyIsStatic(shape->getBody()->_info->body))
        {
            cpSpaceAddStaticShape(_info->space, cps);
        }
        else
        {
            cpSpaceAddShape(_info->space, cps);
        }
    }
    
    return shape;
}

PhysicsBody* PhysicsWorld::addBody(PhysicsBody* body)
{
    CCASSERT(body != nullptr, "the body can not be nullptr");
    
    if (body->getWorld() != this && body->getWorld() != nullptr)
    {
        body->removeFromWorld();
    }
    
    if (body->isEnable())
    {
        body->_world = this;
        
        //is gravity enable
        if (!body->isGravityEnable())
        {
            body->applyForce(-_gravity);
        }
        
        // add body to space
        if (body->isDynamic())
        {
            cpSpaceAddBody(_info->space, body->_info->body);
        }
        
        // add shapes to space
        for (auto shape : *body->getShapes())
        {
            addShape(dynamic_cast<PhysicsShape*>(shape));
        }
    }
    
    _bodies->addObject(body);
    
    return body;
}

void PhysicsWorld::removeBody(PhysicsBody* body)
{
    CCASSERT(body != nullptr, "the body can not be nullptr");
    
    if (body->getWorld() != this)
    {
        return;
    }
    
    // reset the gravity
    if (!body->isGravityEnable())
    {
        body->applyForce(-_gravity);
    }
    
    // remove joints
    for (auto joint : body->_joints)
    {
        removeJoint(joint);
    }
    
    // remove shaps
    for (auto shape : *body->getShapes())
    {
        removeShape(dynamic_cast<PhysicsShape*>(shape));
    }
    
    // remove body
    if (cpSpaceContainsBody(_info->space, body->_info->body))
    {
        cpSpaceRemoveBody(_info->space, body->_info->body);
    }
    
    body->_world = nullptr;
    _bodies->removeObject(body);
}

void PhysicsWorld::removeBodyByTag(int tag)
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

void PhysicsWorld::removeAllBodies()
{
    for (Object* obj : *_bodies)
    {
        PhysicsBody* body = dynamic_cast<PhysicsBody*>(obj);
        
        // reset the gravity
        if (!body->isGravityEnable())
        {
            body->applyForce(-_gravity);
        }
        
        // remove joints
        for (auto joint : body->_joints)
        {
            removeJoint(joint);
        }
        
        // remove shaps
        for (auto shape : *body->getShapes())
        {
            removeShape(dynamic_cast<PhysicsShape*>(shape));
        }
        
        // remove body
        if (cpSpaceContainsBody(_info->space, body->_info->body))
        {
            cpSpaceRemoveBody(_info->space, body->_info->body);
        }
        
        body->_world = nullptr;
    }

    _bodies->removeAllObjects();
    CC_SAFE_RELEASE(_bodies);
}

void PhysicsWorld::removeShape(PhysicsShape* shape)
{
    for (auto cps : shape->_info->shapes)
    {
        if (cpSpaceContainsShape(_info->space, cps))
        {
            cpSpaceRemoveShape(_info->space, cps);
        }
    }
}

void PhysicsWorld::update(float delta)
{
    for (auto body : *_bodies)
    {
        body->update(delta);
    }
    
    cpSpaceStep(_info->space, delta);
    
    if (_drawNode)
    {
        _drawNode->removeFromParent();
        _drawNode = nullptr;
    }
    
    if (_debugDraw)
    {
        debugDraw();
    }
}

void PhysicsWorld::debugDraw()
{
    if (_debugDraw && _bodies != nullptr)
    {
        _drawNode= DrawNode::create();

        for (Object* obj : *_bodies)
        {
            PhysicsBody* body = dynamic_cast<PhysicsBody*>(obj);
            
            for (auto shape : *body->getShapes())
            {
                drawWithShape(_drawNode, dynamic_cast<PhysicsShape*>(shape));
            }
        }
        
        for (auto joint : _joints)
        {
            drawWithJoint(_drawNode, joint);
        }
        
        if (_scene)
        {
            _scene->addChild(_drawNode);
        }
    }
}

void PhysicsWorld::drawWithJoint(DrawNode* node, PhysicsJoint* joints)
{
    for (auto it = joints->_info->joints.begin(); it != joints->_info->joints.end(); ++it)
    {
        cpConstraint *constraint = *it;
        
        
        cpBody *body_a = constraint->a;
        cpBody *body_b = constraint->b;
        
        const cpConstraintClass *klass = constraint->klass_private;
        if(klass == cpPinJointGetClass())
        {
            cpPinJoint *joint = (cpPinJoint *)constraint;
            
            cpVect a = cpvadd(body_a->p, cpvrotate(joint->anchr1, body_a->rot));
            cpVect b = cpvadd(body_b->p, cpvrotate(joint->anchr2, body_b->rot));
            
            node->drawSegment(PhysicsHelper::cpv2point(a), PhysicsHelper::cpv2point(b), 1, Color4F(0.0f, 0.0f, 1.0f, 1.0f));
            node->drawDot(PhysicsHelper::cpv2point(a), 2, Color4F(0.0f, 1.0f, 0.0f, 1.0f));
            node->drawDot(PhysicsHelper::cpv2point(b), 2, Color4F(0.0f, 1.0f, 0.0f, 1.0f));
        }
        else if(klass == cpSlideJointGetClass())
        {
            cpSlideJoint *joint = (cpSlideJoint *)constraint;
            
            cpVect a = cpvadd(body_a->p, cpvrotate(joint->anchr1, body_a->rot));
            cpVect b = cpvadd(body_b->p, cpvrotate(joint->anchr2, body_b->rot));
            
            node->drawSegment(PhysicsHelper::cpv2point(a), PhysicsHelper::cpv2point(b), 1, Color4F(0.0f, 0.0f, 1.0f, 1.0f));
            node->drawDot(PhysicsHelper::cpv2point(a), 2, Color4F(0.0f, 1.0f, 0.0f, 1.0f));
            node->drawDot(PhysicsHelper::cpv2point(b), 2, Color4F(0.0f, 1.0f, 0.0f, 1.0f));
        }
        else if(klass == cpPivotJointGetClass())
        {
            cpPivotJoint *joint = (cpPivotJoint *)constraint;
            
            cpVect a = cpvadd(body_a->p, cpvrotate(joint->anchr1, body_a->rot));
            cpVect b = cpvadd(body_b->p, cpvrotate(joint->anchr2, body_b->rot));
            
            node->drawDot(PhysicsHelper::cpv2point(a), 2, Color4F(0.0f, 1.0f, 0.0f, 1.0f));
            node->drawDot(PhysicsHelper::cpv2point(b), 2, Color4F(0.0f, 1.0f, 0.0f, 1.0f));
        }
        else if(klass == cpGrooveJointGetClass())
        {
            cpGrooveJoint *joint = (cpGrooveJoint *)constraint;
            
            cpVect a = cpvadd(body_a->p, cpvrotate(joint->grv_a, body_a->rot));
            cpVect b = cpvadd(body_a->p, cpvrotate(joint->grv_b, body_a->rot));
            cpVect c = cpvadd(body_b->p, cpvrotate(joint->anchr2, body_b->rot));
            
            node->drawSegment(PhysicsHelper::cpv2point(a), PhysicsHelper::cpv2point(b), 1, Color4F(0.0f, 0.0f, 1.0f, 1.0f));
            node->drawDot(PhysicsHelper::cpv2point(c), 2, Color4F(0.0f, 1.0f, 0.0f, 1.0f));
        }
        else if(klass == cpDampedSpringGetClass())
        {
            
        }
    }
}

void PhysicsWorld::drawWithShape(DrawNode* node, PhysicsShape* shapes)
{
    for (auto it = shapes->_info->shapes.begin(); it != shapes->_info->shapes.end(); ++it)
    {
        cpShape *shape = *it;
        
        switch ((*it)->klass_private->type)
        {
            case CP_CIRCLE_SHAPE:
            {
                float radius = PhysicsHelper::cpfloat2float(cpCircleShapeGetRadius(shape));
                Point centre = PhysicsHelper::cpv2point(cpBodyGetPos(cpShapeGetBody(shape)))
                + PhysicsHelper::cpv2point(cpCircleShapeGetOffset(shape));
                
                static const int CIRCLE_SEG_NUM = 12;
                Point seg[CIRCLE_SEG_NUM] = {};
                
                for (int i = 0; i < CIRCLE_SEG_NUM; ++i)
                {
                    float angle = (float)i * M_PI / (float)CIRCLE_SEG_NUM * 2.0f;
                    Point d(radius * cosf(angle), radius * sinf(angle));
                    seg[i] = centre + d;
                }
                node->drawPolygon(seg, CIRCLE_SEG_NUM, Color4F(1.0f, 0.0f, 0.0f, 0.3f), 1, Color4F(1, 0, 0, 1));
                break;
            }
            case CP_SEGMENT_SHAPE:
            {
                cpSegmentShape *seg = (cpSegmentShape *)shape;
                node->drawSegment(PhysicsHelper::cpv2point(seg->ta),
                                  PhysicsHelper::cpv2point(seg->tb),
                                  PhysicsHelper::cpfloat2float(seg->r==0 ? 1 : seg->r), Color4F(1, 0, 0, 1));
                break;
            }
            case CP_POLY_SHAPE:
            {
                cpPolyShape* poly = (cpPolyShape*)shape;
                int num = poly->numVerts;
                Point* seg = new Point[num];
                
                PhysicsHelper::cpvs2points(poly->tVerts, seg, num);
                
                node->drawPolygon(seg, num, Color4F(1.0f, 0.0f, 0.0f, 0.3f), 1.0f, Color4F(1.0f, 0.0f, 0.0f, 1.0f));
                
                delete[] seg;
                break;
            }
            default:
                break;
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
        
        if (!joint->isCollisionEnable())
        {
            PhysicsBody* body = joint->getBodyA() == bodyA ? joint->getBodyB() : joint->getBodyA();
            
            if (body == bodyB)
            {
                contact.setNotify(false);
                return false;
            }
        }
    }
    
    // bitmask check
    if ((shapeA->getCategoryBitmask() & shapeB->getContactTestBitmask()) == 0
        || (shapeB->getContactTestBitmask() & shapeA->getCategoryBitmask()) == 0)
    {
        contact.setNotify(false);
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
    if (!contact.getNotify())
    {
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
    if (!contact.getNotify())
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
    if (!contact.getNotify())
    {
        return;
    }
    
    contact.setEventCode(PhysicsContact::EventCode::SEPERATE);
    contact.setWorld(this);
    EventCustom event(PHYSICSCONTACT_EVENT_NAME);
    event.setUserData(&contact);
    _scene->getEventDispatcher()->dispatchEvent(&event);
}

void PhysicsWorld::setGravity(Point gravity)
{
    if (_bodies != nullptr)
    {
        for (auto child : *_bodies)
        {
            PhysicsBody* body = dynamic_cast<PhysicsBody*>(child);
            
            // reset gravity for body
            if (!body->isGravityEnable())
            {
                body->applyForce(-_gravity);
                body->applyForce(gravity);
            }
        }
    }
    
    _gravity = gravity;
    cpSpaceSetGravity(_info->space, PhysicsHelper::point2cpv(gravity));
}


void PhysicsWorld::rayCast(PhysicsRayCastCallback& callback, Point point1, Point point2, void* data)
{
    if (callback.report != nullptr)
    {
        RayCastCallbackInfo info = { this, &callback, point1, point2, data };
        
        PhysicsWorldCallback::continues = true;
        cpSpaceSegmentQuery(this->_info->space,
                            PhysicsHelper::point2cpv(point1),
                            PhysicsHelper::point2cpv(point2),
                            CP_ALL_LAYERS,
                            CP_NO_GROUP,
                            (cpSpaceSegmentQueryFunc)PhysicsWorldCallback::rayCastCallbackFunc,
                            &info);
    }
}


void PhysicsWorld::rectQuery(PhysicsRectQueryCallback& callback, Rect rect, void* data)
{
    if (callback.report != nullptr)
    {
        RectQueryCallbackInfo info = {this, &callback, data};
        
        PhysicsWorldCallback::continues = true;
        cpSpaceBBQuery(this->_info->space,
                       PhysicsHelper::rect2cpbb(rect),
                       CP_ALL_LAYERS,
                       CP_NO_GROUP,
                       (cpSpaceBBQueryFunc)PhysicsWorldCallback::rectQueryCallbackFunc,
                       &info);
    }
}

Array* PhysicsWorld::getShapesAtPoint(Point point) const
{
    Array* arr = Array::create();
    cpSpaceNearestPointQuery(this->_info->space,
                             PhysicsHelper::point2cpv(point),
                             0,
                             CP_ALL_LAYERS,
                             CP_NO_GROUP,
                             (cpSpaceNearestPointQueryFunc)PhysicsWorldCallback::nearestPointQueryFunc,
                             arr);
    
    return arr;
}

PhysicsShape* PhysicsWorld::getShapeAtPoint(Point point) const
{
    cpShape* shape = cpSpaceNearestPointQueryNearest(this->_info->space,
                                    PhysicsHelper::point2cpv(point),
                                    0,
                                    CP_ALL_LAYERS,
                                    CP_NO_GROUP,
                                    nullptr);
    
    return shape == nullptr ? nullptr : PhysicsShapeInfo::map.find(shape)->second->shape;
}

Array* PhysicsWorld::getAllBodies() const
{
    return _bodies;
}

PhysicsBody* PhysicsWorld::getBodyByTag(int tag) const
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

#elif (CC_PHYSICS_ENGINE == CC_PHYSICS_BOX2D)

#endif

PhysicsWorld* PhysicsWorld::create(Scene& scene)
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
, _debugDraw(false)
, _drawNode(nullptr)
{
    
}

PhysicsWorld::~PhysicsWorld()
{
    removeAllBodies();
    removeAllJoints();
    CC_SAFE_DELETE(_info);
}

NS_CC_END

#endif // CC_USE_PHYSICS
