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

#ifndef __CCPHYSICS_CONTACT_H__
#define __CCPHYSICS_CONTACT_H__

#include "ccConfig.h"
#if CC_USE_PHYSICS

#include "CCObject.h"
#include "CCGeometry.h"
#include "CCEventListenerCustom.h"
#include "CCEvent.h"

NS_CC_BEGIN

class PhysicsShape;
class PhysicsBody;
class PhysicsWorld;

class PhysicsContactInfo;

typedef Point Vect;

typedef struct PhysicsContactData
{
    static const int POINT_MAX = 4;
    Point points[POINT_MAX];
    int   count;
    Point normal;
    
    PhysicsContactData()
    : count(0)
    {}
}PhysicsContactData;

/**
 * @brief Contact infomation. it will created automatically when two shape contact with each other. and it will destoried automatically when two shape separated.
 */
class PhysicsContact : public Event
{
public:
    
    enum class EventCode
    {
        NONE,
        BEGIN,
        PRESOLVE,
        POSTSOLVE,
        SEPERATE
    };
    
    /** get contact shape A. */
    inline PhysicsShape* getShapeA() const { return _shapeA; }
    /** get contact shape B. */
    inline PhysicsShape* getShapeB() const { return _shapeB; }
    /** get contact data */
    inline const PhysicsContactData* getContactData() const { return _contactData; }
    /** get data. */
    inline void* getData() const { return _data; }
    /**
     * @brief set data to contact. you must manage the memory yourself, Generally you can set data at contact begin, and distory it at contact seperate.
     */
    inline void setData(void* data) { _data = data; }
    /** get the event code */
    EventCode getEventCode() const { return _eventCode; };
    
private:
    static PhysicsContact* construct(PhysicsShape* a, PhysicsShape* b);
    bool init(PhysicsShape* a, PhysicsShape* b);
    
    void setEventCode(EventCode eventCode) { _eventCode = eventCode; };
    inline bool isNotificationEnabled() const { return _notificationEnable; }
    inline void setNotificationEnable(bool enable) { _notificationEnable = enable; }
    inline PhysicsWorld* getWorld() const { return _world; }
    inline void setWorld(PhysicsWorld* world) { _world = world; }
    inline void setResult(bool result) { _result = result; }
    inline bool resetResult() { bool ret = _result; _result = true; return ret; }
    
    void generateContactData();
    
private:
    PhysicsContact();
    ~PhysicsContact();
    
private:
    PhysicsWorld* _world;
    PhysicsShape* _shapeA;
    PhysicsShape* _shapeB;
    EventCode _eventCode;
    PhysicsContactInfo* _info;
    bool _notificationEnable;
    bool _begin;
    bool _result;
    
    void* _data;
    void* _contactInfo;
    PhysicsContactData* _contactData;
    
    friend class EventListenerPhysicsContact;
    friend class PhysicsWorldCallback;
    friend class PhysicsWorld;
};

/*
 * @brief presolve value generated when onContactPreSolve called.
 */
class PhysicsContactPreSolve
{
public:
    /** get elasticity between two bodies*/
    float getElasticity() const;
    /** get friction between two bodies*/
    float getFriction() const;
    /** get surface velocity between two bodies*/
    Point getSurfaceVelocity() const;
    /** set the elasticity*/
    void setElasticity(float elasticity);
    /** set the friction*/
    void setFriction(float friction);
    /** set the surface velocity*/
    void setSurfaceVelocity(const Vect& velocity);
    /** ignore the rest of the contact presolve and postsolve callbacks */
    void ignore();
    
private:
    PhysicsContactPreSolve(PhysicsContactData* data, void* contactInfo);
    ~PhysicsContactPreSolve();
    
private:
    float _elasticity;
    float _friction;
    Point _surfaceVelocity;
    PhysicsContactData* _preContactData;
    void* _contactInfo;
    
    friend class EventListenerPhysicsContact;
};

/*
 * @brief postsolve value generated when onContactPostSolve called.
 */
class PhysicsContactPostSolve
{
public:
    /** get elasticity between two bodies*/
    float getElasticity() const;
    /** get friction between two bodies*/
    float getFriction() const;
    /** get surface velocity between two bodies*/
    Point getSurfaceVelocity() const;
    
private:
    PhysicsContactPostSolve(void* contactInfo);
    ~PhysicsContactPostSolve();
    
private:
    void* _contactInfo;
    
    friend class EventListenerPhysicsContact;
};

/* contact listener. it will recive all the contact callbacks. */
class EventListenerPhysicsContact : public EventListenerCustom
{
public:
    /** create the listener */
    static EventListenerPhysicsContact* create();
    virtual bool checkAvailable() override;
    virtual EventListenerPhysicsContact* clone() override;
    
protected:
    /**
     * it will be call when two body have contact.
     * if return false, it will not invoke callbacks
     */
    virtual bool hitTest(PhysicsShape* shapeA, PhysicsShape* shapeB);
    
public:
    /*
     * @brief it will called at two shapes start to contact, and only call it once.
     */
    std::function<bool(EventCustom* event, const PhysicsContact& contact)> onContactBegin;
    /*
     * @brief Two shapes are touching during this step. Return false from the callback to make world ignore the collision this step or true to process it normally. Additionally, you may override collision values, elasticity, or surface velocity values.
     */
    std::function<bool(EventCustom* event, const PhysicsContact& contact, const PhysicsContactPreSolve& solve)> onContactPreSolve;
    /*
     * @brief Two shapes are touching and their collision response has been processed. You can retrieve the collision impulse or kinetic energy at this time if you want to use it to calculate sound volumes or damage amounts. See cpArbiter for more info
     */
    std::function<void(EventCustom* event, const PhysicsContact& contact, const PhysicsContactPostSolve& solve)> onContactPostSolve;
    /*
     * @brief it will called at two shapes separated, and only call it once.
     * onContactBegin and onContactSeperate will called in pairs.
     */
    std::function<void(EventCustom* event, const PhysicsContact& contact)> onContactSeperate;
    
protected:
    bool init();
    void onEvent(EventCustom* event);
    
protected:
    EventListenerPhysicsContact();
    virtual ~EventListenerPhysicsContact();
    
    friend class PhysicsWorld;
};

/** this event listener only be called when bodyA and bodyB have contacts */
class EventListenerPhysicsContactWithBodies : public EventListenerPhysicsContact
{
public:
    static EventListenerPhysicsContactWithBodies* create(PhysicsBody* bodyA, PhysicsBody* bodyB);
    
    virtual bool hitTest(PhysicsShape* shapeA, PhysicsShape* shapeB) override;
    virtual EventListenerPhysicsContactWithBodies* clone() override;
    
protected:
    PhysicsBody* _a;
    PhysicsBody* _b;
    
protected:
    EventListenerPhysicsContactWithBodies();
    virtual ~EventListenerPhysicsContactWithBodies();
};

/** this event listener only be called when shapeA and shapeB have contacts */
class EventListenerPhysicsContactWithShapes : public EventListenerPhysicsContact
{
public:
    static EventListenerPhysicsContactWithShapes* create(PhysicsShape* shapeA, PhysicsShape* shapeB);
    
    virtual bool hitTest(PhysicsShape* shapeA, PhysicsShape* shapeB) override;
    virtual EventListenerPhysicsContactWithShapes* clone() override;
    
protected:
    PhysicsShape* _a;
    PhysicsShape* _b;
    
protected:
    EventListenerPhysicsContactWithShapes();
    virtual ~EventListenerPhysicsContactWithShapes();
};

/** this event listener only be called when shapeA or shapeB is in the group your specified */
class EventListenerPhysicsContactWithGroup : public EventListenerPhysicsContact
{
public:
    static EventListenerPhysicsContactWithGroup* create(int group);
    
    virtual bool hitTest(PhysicsShape* shapeA, PhysicsShape* shapeB) override;
    virtual EventListenerPhysicsContactWithGroup* clone() override;
    
protected:
    int _group;
    
protected:
    EventListenerPhysicsContactWithGroup();
    virtual ~EventListenerPhysicsContactWithGroup();
};

NS_CC_END

#endif // CC_USE_PHYSICS
#endif //__CCPHYSICS_CONTACT_H__
