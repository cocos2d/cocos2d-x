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

#include "base/ccConfig.h"
#if CC_USE_PHYSICS

#include "base/CCRef.h"
#include "math/CCGeometry.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEvent.h"
#include "base/CCEventCustom.h"

NS_CC_BEGIN

class PhysicsShape;
class PhysicsBody;
class PhysicsWorld;

class PhysicsContactInfo;

typedef Vec2 Vect;

typedef struct PhysicsContactData
{
    static const int POINT_MAX = 4;
    Vec2 points[POINT_MAX];
    int   count;
    Vec2 normal;
    
    PhysicsContactData()
    : count(0)
    {}
}PhysicsContactData;

/**
 * @brief 碰撞信息。当两个形状彼此发生接触的时候会自动创建，当两个形状彼此分离的时候自动销毁。
 */
class PhysicsContact : public EventCustom
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
    
    /** 获取碰撞形状A. */
    inline PhysicsShape* getShapeA() const { return _shapeA; }
    /** 获取碰撞形状B. */
    inline PhysicsShape* getShapeB() const { return _shapeB; }
    /** 获取碰撞信息 */
    inline const PhysicsContactData* getContactData() const { return _contactData; }
    /** 获取之前碰撞信息 */
    inline const PhysicsContactData* getPreContactData() const { return _preContactData; }
    /** 获取data. */
    inline void* getData() const { return _data; }
    /**
     * @brief 设置碰撞信息。你必须自己管理内存，总体来说你可以在碰撞开始设置信息，在碰撞结束后销毁信息。
     */
    inline void setData(void* data) { _data = data; }
    /** 获取事件码 */
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
    bool _result;
    
    void* _data;
    void* _contactInfo;
    PhysicsContactData* _contactData;
    PhysicsContactData* _preContactData;
    
    friend class EventListenerPhysicsContact;
    friend class PhysicsWorldCallback;
    friend class PhysicsWorld;
};

/*
 * @brief 当 onContactPreSolve 被调用时生成presovle value
 */
class PhysicsContactPreSolve
{
public:
    /** 获取两个body间的恢复系数 */
    float getRestitution() const;
    /** 获取两个body间的摩擦系数 */
    float getFriction() const;
    /** 获取两个body间的表面速度 */
    Vec2 getSurfaceVelocity() const;
    /** 设置恢复系数 */
    void setRestitution(float restitution);
    /** 设置摩擦力 */
    void setFriction(float friction);
    /** 设置表面速度 */
    void setSurfaceVelocity(const Vect& velocity);
    /** 忽视碰撞的其他presolve 和 postsolve 回调。
     ignore the rest of the contact presolve and postsolve callbacks */
    void ignore();
    
private:
    PhysicsContactPreSolve(void* contactInfo);
    ~PhysicsContactPreSolve();
    
private:
    void* _contactInfo;
    
    friend class EventListenerPhysicsContact;
};

/*
 * @brief 当onContactPostSolve被调用时生成postsolve value
 postsolve value generated when onContactPostSolve called.
 */
class PhysicsContactPostSolve
{
public:
    /** 获取两个body间恢复系数 */
    float getRestitution() const;
    /** 获取两个body间摩擦系数 */
    float getFriction() const;
    /** 获取两个body间表面速度 */
    Vec2 getSurfaceVelocity() const;
    
private:
    PhysicsContactPostSolve(void* contactInfo);
    ~PhysicsContactPostSolve();
    
private:
    void* _contactInfo;
    
    friend class EventListenerPhysicsContact;
};

/* 碰撞监听器。它会收到所有的碰撞回调。 */
class EventListenerPhysicsContact : public EventListenerCustom
{
public:
    /** 创建监听器 */
    static EventListenerPhysicsContact* create();
    virtual bool checkAvailable() override;
    virtual EventListenerPhysicsContact* clone() override;
    
protected:
    /**
     * 当两个body有碰撞时会被调用。
     * 如果返回false,它不会调用回调。
     */
    virtual bool hitTest(PhysicsShape* shapeA, PhysicsShape* shapeB);
    
public:
    /*
     * @brief 当两个形状开始碰撞时被调用，只会被调用一次。
     */
    std::function<bool(PhysicsContact& contact)> onContactBegin;
    /*
     * @brief 在这个step中两个形状正在接触。从回调函数返回false使得物理世界在该step忽视这次冲突，返回true让物理世界正常地处理它。另外，你也许会重写冲突值,恢复系数，或是表面速度值。
     */
    std::function<bool(PhysicsContact& contact, PhysicsContactPreSolve& solve)> onContactPreSolve;
    /*
     * @brief 两个形状正在接触，她们的冲突响应已被处理。如果你想使用它去计算音量大小或是伤害值，在这个时候你可以检索这个冲突推动力或是动能。通过cpArbiter了解更多。
     */
    std::function<void(PhysicsContact& contact, const PhysicsContactPostSolve& solve)> onContactPostSolve;
    /*
     * @brief 当两个形状分离会被调用，只会被调用一次。
     * onContactBegin 和 onContactSeperate会被成对调用。
     */
    std::function<void(PhysicsContact& contact)> onContactSeperate;
    
protected:
    bool init();
    void onEvent(EventCustom* event);
    
protected:
    EventListenerPhysicsContact();
    virtual ~EventListenerPhysicsContact();
    
    friend class PhysicsWorld;
};

/** 这个时间监听器只会在bodyA和bodyB发生碰撞时被调用。 */
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

/** 这个事件监听器只会在shapeA和shapeB发生碰撞时会被调用。 */
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

/** 这个事件监听器只会在shapeA和shapeB是在你指定的分组下才会被调用。 */
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
