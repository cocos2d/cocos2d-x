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
#include "CCPhysicsContact.h"
#if CC_USE_PHYSICS
#include "chipmunk.h"

#include "CCPhysicsBody.h"

#include "chipmunk/CCPhysicsContactInfo_chipmunk.h"
#include "chipmunk/CCPhysicsHelper_chipmunk.h"

#include "CCEventCustom.h"

NS_CC_BEGIN

const char* PHYSICSCONTACT_EVENT_NAME = "PhysicsContactEvent";

PhysicsContact::PhysicsContact()
: EventCustom(PHYSICSCONTACT_EVENT_NAME)
, _world(nullptr)
, _shapeA(nullptr)
, _shapeB(nullptr)
, _eventCode(EventCode::NONE)
, _info(nullptr)
, _notificationEnable(true)
, _result(true)
, _data(nullptr)
, _contactInfo(nullptr)
, _contactData(nullptr)
, _preContactData(nullptr)
{
    
}

PhysicsContact::~PhysicsContact()
{
    CC_SAFE_DELETE(_info);
    CC_SAFE_DELETE(_contactData);
    CC_SAFE_DELETE(_preContactData);
}

PhysicsContact* PhysicsContact::construct(PhysicsShape* a, PhysicsShape* b)
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
    
    cpArbiter* arb = static_cast<cpArbiter*>(_contactInfo);
    CC_SAFE_DELETE(_preContactData);
    _preContactData = _contactData;
    _contactData = new PhysicsContactData();
    _contactData->count = cpArbiterGetCount(arb);
    for (int i=0; i<_contactData->count && i<PhysicsContactData::POINT_MAX; ++i)
    {
        _contactData->points[i] = PhysicsHelper::cpv2point(cpArbiterGetPoint(arb, i));
    }
    
    _contactData->normal = _contactData->count > 0 ? PhysicsHelper::cpv2point(cpArbiterGetNormal(arb, 0)) : Point::ZERO;
}

// PhysicsContactPreSolve implementation
PhysicsContactPreSolve::PhysicsContactPreSolve(void* contactInfo)
: _contactInfo(contactInfo)
{
}

PhysicsContactPreSolve::~PhysicsContactPreSolve()
{
}

float PhysicsContactPreSolve::getRestitution() const
{
    return static_cast<cpArbiter*>(_contactInfo)->e;
}

float PhysicsContactPreSolve::getFriction() const
{
    return static_cast<cpArbiter*>(_contactInfo)->u;
}

Point PhysicsContactPreSolve::getSurfaceVelocity() const
{
    return PhysicsHelper::cpv2point(static_cast<cpArbiter*>(_contactInfo)->surface_vr);
}

void PhysicsContactPreSolve::setRestitution(float restitution)
{
    static_cast<cpArbiter*>(_contactInfo)->e = restitution;
}

void PhysicsContactPreSolve::setFriction(float friction)
{
    static_cast<cpArbiter*>(_contactInfo)->u = friction;
}

void PhysicsContactPreSolve::setSurfaceVelocity(const Vect& velocity)
{
    static_cast<cpArbiter*>(_contactInfo)->surface_vr = PhysicsHelper::point2cpv(velocity);
}

void PhysicsContactPreSolve::ignore()
{
    cpArbiterIgnore(static_cast<cpArbiter*>(_contactInfo));
}

// PhysicsContactPostSolve implementation
PhysicsContactPostSolve::PhysicsContactPostSolve(void* contactInfo)
: _contactInfo(contactInfo)
{
    
}

PhysicsContactPostSolve::~PhysicsContactPostSolve()
{
    
}

float PhysicsContactPostSolve::getRestitution() const
{
    return static_cast<cpArbiter*>(_contactInfo)->e;
}

float PhysicsContactPostSolve::getFriction() const
{
    return static_cast<cpArbiter*>(_contactInfo)->u;
}

Point PhysicsContactPostSolve::getSurfaceVelocity() const
{
    return PhysicsHelper::cpv2point(static_cast<cpArbiter*>(_contactInfo)->surface_vr);
}

EventListenerPhysicsContact::EventListenerPhysicsContact()
: onContactBegin(nullptr)
, onContactPreSolve(nullptr)
, onContactPostSolve(nullptr)
, onContactSeperate(nullptr)
{
}

bool EventListenerPhysicsContact::init()
{
    auto func = [this](EventCustom* event) -> void
    {
        onEvent(event);
    };
    
    return EventListenerCustom::init(PHYSICSCONTACT_EVENT_NAME, func);
}

void EventListenerPhysicsContact::onEvent(EventCustom* event)
{
    PhysicsContact* contact = dynamic_cast<PhysicsContact*>(event);
    
    if (contact == nullptr)
    {
        return;
    }
    
    switch (contact->getEventCode())
    {
        case PhysicsContact::EventCode::BEGIN:
        {
            bool ret = true;
            
            if (onContactBegin != nullptr
                && hitTest(contact->getShapeA(), contact->getShapeB()))
            {
                contact->generateContactData();
                ret = onContactBegin(*contact);
            }
            
            contact->setResult(ret);
            break;
        }
        case PhysicsContact::EventCode::PRESOLVE:
        {
            bool ret = true;
            
            if (onContactPreSolve != nullptr
                && hitTest(contact->getShapeA(), contact->getShapeB()))
            {
                PhysicsContactPreSolve solve(contact->_contactInfo);
                contact->generateContactData();
                
                ret = onContactPreSolve(*contact, solve);
            }
            
            contact->setResult(ret);
            break;
        }
        case PhysicsContact::EventCode::POSTSOLVE:
        {
            if (onContactPostSolve != nullptr
                && hitTest(contact->getShapeA(), contact->getShapeB()))
            {
                PhysicsContactPostSolve solve(contact->_contactInfo);
                onContactPostSolve(*contact, solve);
            }
            break;
        }
        case PhysicsContact::EventCode::SEPERATE:
        {
            if (onContactSeperate != nullptr
                && hitTest(contact->getShapeA(), contact->getShapeB()))
            {
                onContactSeperate(*contact);
            }
            break;
        }
        default:
            break;
    }
}

EventListenerPhysicsContact::~EventListenerPhysicsContact()
{
    
}

EventListenerPhysicsContact* EventListenerPhysicsContact::create()
{
    EventListenerPhysicsContact* obj = new EventListenerPhysicsContact();
    
    if (obj != nullptr && obj->init())
    {
        obj->autorelease();
        return obj;
    }
    
    CC_SAFE_DELETE(obj);
    return nullptr;
}

bool EventListenerPhysicsContact::hitTest(PhysicsShape* shapeA, PhysicsShape* shapeB)
{
    CC_UNUSED_PARAM(shapeA);
    CC_UNUSED_PARAM(shapeB);
    return true;
}

bool EventListenerPhysicsContact::checkAvailable()
{
    if (onContactBegin == nullptr && onContactPreSolve == nullptr
        && onContactPostSolve == nullptr && onContactSeperate == nullptr)
    {
        CCASSERT(false, "Invalid PhysicsContactListener.");
        return false;
    }
    
    return true;
}

EventListenerPhysicsContact* EventListenerPhysicsContact::clone()
{
    EventListenerPhysicsContact* obj = EventListenerPhysicsContact::create();
    
    if (obj != nullptr)
    {
        obj->onContactBegin = onContactBegin;
        obj->onContactPreSolve = onContactPreSolve;
        obj->onContactPostSolve = onContactPostSolve;
        obj->onContactSeperate = onContactSeperate;
        
        return obj;
    }
    
    CC_SAFE_DELETE(obj);
    return nullptr;
}

EventListenerPhysicsContactWithBodies* EventListenerPhysicsContactWithBodies::create(PhysicsBody* bodyA, PhysicsBody* bodyB)
{
    EventListenerPhysicsContactWithBodies* obj = new EventListenerPhysicsContactWithBodies();
    
    if (obj != nullptr && obj->init())
    {
        obj->_a = bodyA;
        obj->_b = bodyB;
        obj->autorelease();
        return obj;
    }
    
    CC_SAFE_DELETE(obj);
    return nullptr;
}

EventListenerPhysicsContactWithBodies::EventListenerPhysicsContactWithBodies()
: _a(nullptr)
, _b(nullptr)
{
    
}

EventListenerPhysicsContactWithBodies::~EventListenerPhysicsContactWithBodies()
{
    
}


bool EventListenerPhysicsContactWithBodies::hitTest(PhysicsShape* shapeA, PhysicsShape* shapeB)
{
    if ((shapeA->getBody() == _a && shapeB->getBody() == _b)
        || (shapeA->getBody() == _b && shapeB->getBody() == _a))
    {
        return true;
    }
    
    return false;
}

EventListenerPhysicsContactWithBodies* EventListenerPhysicsContactWithBodies::clone()
{
    EventListenerPhysicsContactWithBodies* obj = EventListenerPhysicsContactWithBodies::create(_a, _b);
    
    if (obj != nullptr)
    {
        obj->onContactBegin = onContactBegin;
        obj->onContactPreSolve = onContactPreSolve;
        obj->onContactPostSolve = onContactPostSolve;
        obj->onContactSeperate = onContactSeperate;
        
        return obj;
    }
    
    CC_SAFE_DELETE(obj);
    return nullptr;
}

EventListenerPhysicsContactWithShapes::EventListenerPhysicsContactWithShapes()
: _a(nullptr)
, _b(nullptr)
{
}

EventListenerPhysicsContactWithShapes::~EventListenerPhysicsContactWithShapes()
{
}

EventListenerPhysicsContactWithShapes* EventListenerPhysicsContactWithShapes::create(PhysicsShape* shapeA, PhysicsShape* shapeB)
{
    EventListenerPhysicsContactWithShapes* obj = new EventListenerPhysicsContactWithShapes();
    
    if (obj != nullptr && obj->init())
    {
        obj->_a = shapeA;
        obj->_b = shapeB;
        obj->autorelease();
        return obj;
    }
    
    CC_SAFE_DELETE(obj);
    return nullptr;
}

bool EventListenerPhysicsContactWithShapes::hitTest(PhysicsShape* shapeA, PhysicsShape* shapeB)
{
    if ((shapeA == _a && shapeB == _b)
        || (shapeA == _b && shapeB == _a))
    {
        return true;
    }
    
    return false;
}

EventListenerPhysicsContactWithShapes* EventListenerPhysicsContactWithShapes::clone()
{
    EventListenerPhysicsContactWithShapes* obj = EventListenerPhysicsContactWithShapes::create(_a, _b);
    
    if (obj != nullptr)
    {
        obj->onContactBegin = onContactBegin;
        obj->onContactPreSolve = onContactPreSolve;
        obj->onContactPostSolve = onContactPostSolve;
        obj->onContactSeperate = onContactSeperate;
        
        return obj;
    }
    
    CC_SAFE_DELETE(obj);
    return nullptr;
}

EventListenerPhysicsContactWithGroup::EventListenerPhysicsContactWithGroup()
: _group(CP_NO_GROUP)
{
}

EventListenerPhysicsContactWithGroup::~EventListenerPhysicsContactWithGroup()
{
}

EventListenerPhysicsContactWithGroup* EventListenerPhysicsContactWithGroup::create(int group)
{
    EventListenerPhysicsContactWithGroup* obj = new EventListenerPhysicsContactWithGroup();
    
    if (obj != nullptr && obj->init())
    {
        obj->_group = group;
        obj->autorelease();
        return obj;
    }
    
    CC_SAFE_DELETE(obj);
    return nullptr;
}

bool EventListenerPhysicsContactWithGroup::hitTest(PhysicsShape* shapeA, PhysicsShape* shapeB)
{
    if (shapeA->getGroup() == _group || shapeB->getGroup() == _group)
    {
        return true;
    }
    
    return false;
}

EventListenerPhysicsContactWithGroup* EventListenerPhysicsContactWithGroup::clone()
{
    EventListenerPhysicsContactWithGroup* obj = EventListenerPhysicsContactWithGroup::create(_group);
    
    if (obj != nullptr)
    {
        obj->onContactBegin = onContactBegin;
        obj->onContactPreSolve = onContactPreSolve;
        obj->onContactPostSolve = onContactPostSolve;
        obj->onContactSeperate = onContactSeperate;
        
        return obj;
    }
    
    CC_SAFE_DELETE(obj);
    return nullptr;
}

NS_CC_END
#endif // CC_USE_PHYSICS
