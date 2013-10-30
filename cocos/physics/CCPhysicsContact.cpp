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
#include "CCPhysicsContact.h"
#ifdef CC_USE_PHYSICS

#if (CC_PHYSICS_ENGINE == CC_PHYSICS_CHIPMUNK)
#include "chipmunk.h"
#elif (CC_PHYSICS_ENGINE == CCPHYSICS_BOX2D)
#include "Box2D.h"
#endif

#include "chipmunk/CCPhysicsContactInfo.h"
#include "box2d/CCPhysicsContactInfo.h"
#include "chipmunk/CCPhysicsHelper.h"
#include "box2d/CCPhysicsHelper.h"

NS_CC_BEGIN

PhysicsContact::PhysicsContact()
: _shapeA(nullptr)
, _shapeB(nullptr)
, _info(nullptr)
, _notify(true)
, _begin(false)
, _data(nullptr)
, _contactInfo(nullptr)
, _contactData(nullptr)
{
    
}

PhysicsContact::~PhysicsContact()
{
    CC_SAFE_DELETE(_info);
    CC_SAFE_DELETE(_contactData);
}

PhysicsContact* PhysicsContact::create(PhysicsShape* a, PhysicsShape* b)
{
    PhysicsContact * contact = new PhysicsContact();
    if(contact && contact->init(a, b))
    {
        return contact;
    }
    
    CC_SAFE_DELETE(contact);
    return nullptr;
}

bool PhysicsContact::init(PhysicsShape* a, PhysicsShape* b)
{
    do
    {
        CC_BREAK_IF(a == nullptr || b == nullptr);
        
        CC_BREAK_IF(!(_info = new PhysicsContactInfo(this)));
        
        _shapeA = a;
        _shapeB = b;
        
        return true;
    } while(false);
    
    return false;
}

void PhysicsContact::generateContactData()
{
    if (_contactInfo == nullptr)
    {
        return;
    }
    
    cpArbiter* arb = (cpArbiter*)_contactInfo;
    _contactData = new PhysicsContactData();
    _contactData->count = cpArbiterGetCount(arb);
    for (int i=0; i<_contactData->count; ++i)
    {
        _contactData->points[i] = PhysicsHelper::cpv2point(cpArbiterGetPoint(arb, i));
    }
    
    _contactData->normal = _contactData->count > 0 ? PhysicsHelper::cpv2point(cpArbiterGetNormal(arb, 0)) : Point::ZERO;
}

// PhysicsContactPreSolve implementation
PhysicsContactPreSolve::PhysicsContactPreSolve(PhysicsContactData* data, void* contactInfo)
: _preContactData(data)
, _contactInfo(contactInfo)
{
}

float PhysicsContactPreSolve::getElasticity()
{
    return ((cpArbiter*)_contactInfo)->e;
}

float PhysicsContactPreSolve::getFriciton()
{
    return ((cpArbiter*)_contactInfo)->u;
}

Point PhysicsContactPreSolve::getSurfaceVelocity()
{
    return PhysicsHelper::cpv2point(((cpArbiter*)_contactInfo)->surface_vr);
}

void PhysicsContactPreSolve::setElasticity(float elasticity)
{
    ((cpArbiter*)_contactInfo)->e = elasticity;
}

void PhysicsContactPreSolve::setFriction(float friction)
{
    ((cpArbiter*)_contactInfo)->u = friction;
}

void PhysicsContactPreSolve::setSurfaceVelocity(Point surfaceVelocity)
{
    ((cpArbiter*)_contactInfo)->surface_vr = PhysicsHelper::point2cpv(surfaceVelocity);
}

PhysicsContactPreSolve::~PhysicsContactPreSolve()
{
    CC_SAFE_DELETE(_preContactData);
}

// PhysicsContactPostSolve implementation
PhysicsContactPostSolve::PhysicsContactPostSolve(void* contactInfo)
: _contactInfo(contactInfo)
{
    
}

PhysicsContactPostSolve::~PhysicsContactPostSolve()
{
    
}

float PhysicsContactPostSolve::getElasticity()
{
    return ((cpArbiter*)_contactInfo)->e;
}

float PhysicsContactPostSolve::getFriciton()
{
    return ((cpArbiter*)_contactInfo)->u;
}

Point PhysicsContactPostSolve::getSurfaceVelocity()
{
    return PhysicsHelper::cpv2point(((cpArbiter*)_contactInfo)->surface_vr);
}

PhysicsContactListener::PhysicsContactListener()
: onContactBegin(nullptr)
, onContactPreSolve(nullptr)
, onContactPostSolve(nullptr)
, onContactEnd(nullptr)
{
    
}

PhysicsContactListener::~PhysicsContactListener()
{
    
}

PhysicsContactListener* PhysicsContactListener::create()
{
    PhysicsContactListener* obj = new PhysicsContactListener();
    
    if (obj != nullptr)
    {
        obj->autorelease();
        return obj;
    }
    
    CC_SAFE_DELETE(obj);
    return nullptr;
}

bool PhysicsContactListener::test(PhysicsShape* shapeA, PhysicsShape* shapeB)
{
    CC_UNUSED_PARAM(shapeA);
    CC_UNUSED_PARAM(shapeB);
    return true;
}

bool PhysicsContactListener::checkAvaiable()
{
    if (onContactBegin == nullptr && onContactPreSolve == nullptr
        && onContactPostSolve == nullptr && onContactEnd == nullptr)
    {
        CCASSERT(false, "Invalid PhysicsContactListener.");
        return false;
    }
    
    return true;
}

EventListener* PhysicsContactListener::clone()
{
    PhysicsContactListener* obj = PhysicsContactListener::create();
    
    if (obj != nullptr)
    {
        obj->onContactBegin = onContactBegin;
        obj->onContactPreSolve = onContactPreSolve;
        obj->onContactPostSolve = onContactPostSolve;
        obj->onContactEnd = onContactEnd;
        
        return obj;
    }
    
    CC_SAFE_DELETE(obj);
    return nullptr;
}




PhysicsContactWithBodysListener* PhysicsContactWithBodysListener::create(PhysicsShape* shapeA, PhysicsShape* shapeB)
{
    PhysicsContactWithBodysListener* obj = new PhysicsContactWithBodysListener();
    
    if (obj != nullptr)
    {
        obj->_a = shapeA;
        obj->_b = shapeB;
        obj->autorelease();
        return obj;
    }
    
    CC_SAFE_DELETE(obj);
    return nullptr;
}

bool PhysicsContactWithBodysListener::test(PhysicsShape* shapeA, PhysicsShape* shapeB)
{
    if ((shapeA == _a && shapeB == _b)
        || (shapeA == _b && shapeB == _a))
    {
        return true;
    }
    
    return false;
}

EventListener* PhysicsContactWithBodysListener::clone()
{
    PhysicsContactWithBodysListener* obj = PhysicsContactWithBodysListener::create(_a, _b);
    
    if (obj != nullptr)
    {
        obj->onContactBegin = onContactBegin;
        obj->onContactPreSolve = onContactPreSolve;
        obj->onContactPostSolve = onContactPostSolve;
        obj->onContactEnd = onContactEnd;
        
        return obj;
    }
    
    CC_SAFE_DELETE(obj);
    return nullptr;
}

NS_CC_END
#endif // CC_USE_PHYSICS
