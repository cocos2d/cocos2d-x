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

#include "chipmunk/CCPhysicsWorldInfo.h"
#include "Box2D/CCPhysicsWorldInfo.h"
#include "chipmunk/CCPhysicsBodyInfo.h"
#include "Box2D/CCPhysicsBodyInfo.h"
#include "chipmunk/CCPhysicsShapeInfo.h"
#include "Box2D/CCPhysicsShapeInfo.h"
#include "chipmunk/CCPhysicsContactInfo.h"
#include "Box2D/CCPhysicsContactInfo.h"
#include "chipmunk/CCPhysicsHelper.h"

#include "draw_nodes/CCDrawNode.h"
#include "cocoa/CCArray.h"
#include "layers_scenes_transitions_nodes/CCScene.h"
#include "CCDirector.h"

NS_CC_BEGIN

#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)

int PhysicsWorld::collisionBeginCallbackFunc(cpArbiter *arb, struct cpSpace *space, void *data)
{
    PhysicsWorld* world = static_cast<PhysicsWorld*>(data);
    
    CP_ARBITER_GET_SHAPES(arb, a, b);
    
    auto ita = PhysicsShapeInfo::map.find(a);
    auto itb = PhysicsShapeInfo::map.find(b);
    CC_ASSERT(ita != PhysicsShapeInfo::map.end() && itb != PhysicsShapeInfo::map.end());
    
    PhysicsContact* contact = PhysicsContact::create(ita->second->shape, itb->second->shape);
    arb->data = contact;
    
    return world->collisionBeginCallback(*static_cast<PhysicsContact*>(arb->data));
}

int PhysicsWorld::collisionPreSolveCallbackFunc(cpArbiter *arb, cpSpace *space, void *data)
{
    PhysicsWorld* world = static_cast<PhysicsWorld*>(data);
    return world->collisionPreSolveCallback(*static_cast<PhysicsContact*>(arb->data),
                                            PhysicsContactPreSolve());
}

void PhysicsWorld::collisionPostSolveCallbackFunc(cpArbiter *arb, cpSpace *space, void *data)
{
    PhysicsWorld* world = static_cast<PhysicsWorld*>(data);
    world->collisionPostSolveCallback(*static_cast<PhysicsContact*>(arb->data),
                                      PhysicsContactPostSolve());
}

void PhysicsWorld::collisionSeparateCallbackFunc(cpArbiter *arb, cpSpace *space, void *data)
{
    PhysicsWorld* world = static_cast<PhysicsWorld*>(data);
    PhysicsContact* contact = static_cast<PhysicsContact*>(arb->data);
    
    world->collisionSeparateCallback(*contact);
    
    delete contact;
}

bool PhysicsWorld::init()
{
    _info = new PhysicsWorldInfo();
    
    cpSpaceSetGravity(_info->space, PhysicsHelper::point2cpv(_gravity));
    
    cpSpaceSetDefaultCollisionHandler(_info->space,
                                      PhysicsWorld::collisionBeginCallbackFunc,
                                      PhysicsWorld::collisionPreSolveCallbackFunc,
                                      PhysicsWorld::collisionPostSolveCallbackFunc,
                                      PhysicsWorld::collisionSeparateCallbackFunc,
                                      this);
    
    return true;
}

void PhysicsWorld::addShape(PhysicsShape* shape)
{
    for (auto it = shape->_info->shapes.begin(); it != shape->_info->shapes.end(); it++)
    {
        if (cpBodyIsStatic(shape->getBody()->_info->body))
        {
            cpSpaceAddStaticShape(_info->space, *it);
        }else
        {
            cpSpaceAddShape(_info->space, *it);
        }
    }
}

void PhysicsWorld::addChild(PhysicsBody* body)
{
    auto shapes = body->getShapes();
    
    // add body to space
    if (body->isDynamic())
    {
        cpSpaceAddBody(_info->space, body->_info->body);
    }
    
    // add shapes to space
    for (auto it = shapes.begin(); it != shapes.end(); it++)
    {
        addShape(*it);
    }
    
    if (_bodys == nullptr)
    {
        _bodys = Array::create(body, NULL);
        _bodys->retain();
    }else
    {
        _bodys->addObject(body);
    }
}

void PhysicsWorld::update(float delta)
{
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
    if (_debugDraw && _bodys != nullptr)
    {
        _drawNode= DrawNode::create();
        
        Object* child = nullptr;
        CCARRAY_FOREACH(_bodys, child)
        {
            PhysicsBody* body = dynamic_cast<PhysicsBody*>(child);
            
            std::vector<PhysicsShape*> shapes = body->getShapes();
            
            for (auto it = shapes.begin(); it != shapes.end(); ++it)
            {
                drawWithShape(_drawNode, *it);
            }
        }
        
        if (_scene)
        {
            _scene->addChild(_drawNode);
        }
    }
}

void PhysicsWorld::setScene(Scene *scene)
{
    _scene = scene;
    scene->retain();
}

void PhysicsWorld::drawWithShape(DrawNode* node, PhysicsShape* shape)
{
    for (auto it = shape->_info->shapes.begin(); it != shape->_info->shapes.end(); ++it)
    {
        cpShape *shape = *it;
        
        switch ((*it)->klass_private->type)
        {
            case CP_CIRCLE_SHAPE:
            {
                float radius = PhysicsHelper::cpfloat2float(cpCircleShapeGetRadius(shape));
                Point centre = PhysicsHelper::cpv2point(cpBodyGetPos(cpShapeGetBody(shape)))
                + PhysicsHelper::cpv2point(cpCircleShapeGetOffset(shape));
                
                Point seg[4] = {};
                seg[0] = Point(centre.x - radius, centre.y - radius);
                seg[1] = Point(centre.x - radius, centre.y + radius);
                seg[2] = Point(centre.x + radius, centre.y + radius);
                seg[3] = Point(centre.x + radius, centre.y - radius);
                node->drawPolygon(seg, 4, Color4F(), 1, Color4F(1, 0, 0, 1));
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
                
                node->drawPolygon(seg, num, Color4F(1, 0, 0, 0.3), 1, Color4F(1, 0, 0, 1));
                
                delete[] seg;
                break;
            }
            default:
                break;
        }
    }
}

int PhysicsWorld::collisionBeginCallback(const PhysicsContact& contact)
{
    if (_listener && _listener->onContactBegin)
    {
        return _listener->onContactBegin(contact);
    }
    
    return true;
}

int PhysicsWorld::collisionPreSolveCallback(const PhysicsContact& contact, const PhysicsContactPreSolve& solve)
{
    if (_listener && _listener->onContactPreSolve)
    {
        return _listener->onContactPreSolve(contact, solve);
    }
    
    return true;
}

void PhysicsWorld::collisionPostSolveCallback(const PhysicsContact& contact, const PhysicsContactPostSolve& solve)
{
    if (_listener && _listener->onContactPreSolve)
    {
        _listener->onContactPostSolve(contact, solve);
    }
}

void PhysicsWorld::collisionSeparateCallback(const PhysicsContact& contact)
{
    if (_listener && _listener->onContactEnd)
    {
        _listener->onContactEnd(contact);
    }
}

void PhysicsWorld::setGravity(Point gravity)
{
    _gravity = gravity;
    cpSpaceSetGravity(_info->space, PhysicsHelper::point2cpv(_gravity));
}

#elif (CC_PHYSICS_ENGINE == CC_PHYSICS_BOX2D)

#endif

PhysicsWorld* PhysicsWorld::create()
{
    PhysicsWorld * world = new PhysicsWorld();
    if(world && world->init())
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
, _listener(nullptr)
, _bodys(nullptr)
, _scene(nullptr)
, _debugDraw(false)
, _drawNode(nullptr)
{
    
}

PhysicsWorld::~PhysicsWorld()
{
    CC_SAFE_DELETE(_info);
    CC_SAFE_RELEASE(_bodys);
    CC_SAFE_RELEASE(_scene);
}

NS_CC_END

#endif // CC_USE_PHYSICS
