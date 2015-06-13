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

typedef Vec2 Vect;

typedef struct CC_DLL PhysicsContactData
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
 * @addtogroup core
 * @{
 */

/** @class PhysicsContact
 * @brief @~english Contact infomation. 
 * It will created automatically when two shape contact with each other. And it will destoried automatically when two shape separated.
 *
 * @~chinese 碰撞信息。
 * 当刚体的形状间发生碰撞时会自动创建PhysicsContact对象，并在碰撞分离时自动销毁。
 */
class CC_DLL PhysicsContact : public EventCustom
{
public:
    
    enum class EventCode
    {
        NONE,
        BEGIN,
        PRESOLVE,
        POSTSOLVE,
        SEPARATE
    };
    
    /** @~english Get contact shape A. @~chinese 获取碰撞的形状A。*/
    inline PhysicsShape* getShapeA() const { return _shapeA; }
    
    /** @~english Get contact shape B. @~chinese 获取碰撞的形状B。*/
    inline PhysicsShape* getShapeB() const { return _shapeB; }
    
    /** @~english Get contact data. @~chinese 获取碰撞数据。*/
    inline const PhysicsContactData* getContactData() const { return _contactData; }
    
    /** @~english Get previous contact data. @~chinese 获取碰撞时两个形状接触前的碰撞数据。*/
    inline const PhysicsContactData* getPreContactData() const { return _preContactData; }
    
    /** 
     * @~english Get the user data.  
     * @~chinese 获取用户数据。
     * @lua NA
     */
    inline void* getData() const { return _data; }
    
    /**
     * @~english Set data to contact. 
     * You must manage the memory yourself, Generally you can set data at contact begin, and distory it at contact separate.
     *
     * @~chinese 设置用户数据。
     * 你需要自己负责这部分数据的释放，通常你可以在两个形状第一次接触的时候设置用户数据，然后在形状分离的时候释放数据。
     * @lua NA
     */
    inline void setData(void* data) { _data = data; }

    /** @~english Get the event code. @~chinese 获取碰撞事件代码。 */
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

/** @class PhysicsContactPreSolve
 * @brief @~english Presolve value generated when onContactPreSolve called.
 * @~chinese onContactPreSolve回调被调用的时候生成PhysicsContactPreSolve对象。
 */
class CC_DLL PhysicsContactPreSolve
{
public:
    /** @~english Get restitution between two bodies.
     * @~chinese 获取两个刚体间的弹力。
     */
    float getRestitution() const;
    
    /** @~english Get friction between two bodies. 
     * @~chinese 获取两个刚体间的摩擦力。
     */
    float getFriction() const;
    
    /** @~english Get surface velocity between two bodies.
     * @~chinese 获取两个刚体间的表面速度值。
     */
    Vec2 getSurfaceVelocity() const;
    
    /** @~english Set the restitution. 
     * @~chinese 设置弹力。
     */
    void setRestitution(float restitution);
    
    /** @~english Set the friction. 
     * @~chinese 设置摩擦力。
     */
    void setFriction(float friction);
    
    /** @~english Set the surface velocity. 
     * @~chinese 设置表面速度。
     */
    void setSurfaceVelocity(const Vect& velocity);
    
    /** @~english Ignore the rest of the contact presolve and postsolve callbacks.
     * @~chinese 忽略这一次的接触。
     */
    void ignore();
    
private:
    PhysicsContactPreSolve(void* contactInfo);
    ~PhysicsContactPreSolve();
    
private:
    void* _contactInfo;
    
    friend class EventListenerPhysicsContact;
};

/** @class PhysicsContactPostSolve
 * @brief @~english Postsolve value generated when onContactPostSolve called.
 * @~chinese onContactPreSolve回调被调用的时候生成PhysicsContactPostSolve对象。
 */
class CC_DLL PhysicsContactPostSolve
{
public:
    /** @~english Get restitution between two bodies.
     * @~chinese 获取两个刚体建的弹力。
     */
    float getRestitution() const;
    
    /** @~english Get friction between two bodies.
     * @~chinese 获取两个刚体间的摩擦力。
     */
    float getFriction() const;
    
    /** @~english Get surface velocity between two bodies.
     * @~chinese 获取两个刚体间的表面速度。
     */
    Vec2 getSurfaceVelocity() const;
    
private:
    PhysicsContactPostSolve(void* contactInfo);
    ~PhysicsContactPostSolve();
    
private:
    void* _contactInfo;
    
    friend class EventListenerPhysicsContact;
};

/** @class EventListenerPhysicsContact
 * @brief @~english Contact listener. It will recive all the contact callbacks. 
 * @~chinese 碰撞事件监听器，可以接收到所有碰撞事件。
 */
class CC_DLL EventListenerPhysicsContact : public EventListenerCustom
{
public:
    /** @~english Create the listener. @~chinese 创建监听器。*/
    static EventListenerPhysicsContact* create();
    
    virtual bool checkAvailable() override;
    
    virtual EventListenerPhysicsContact* clone() override;
    
protected:
    /**
     * @~english It will be call when two body have contact.
     * if return false, it will not invoke callbacks.
     * @~chinese 两个刚体碰撞时会调用这个函数。如果函数返回false的话，碰撞回调将不会被调用。
     */
    virtual bool hitTest(PhysicsShape* shapeA, PhysicsShape* shapeB);
    
public:
    /**
     * @~english It will called at two shapes start to contact, and only call it once.
     * @~chinese 这个回调在碰撞的两个形状第一次接触时被调用，并且只会被调用一次。
     */
    std::function<bool(PhysicsContact& contact)> onContactBegin;
        
    /**
     * @~english Two shapes are touching during this step. 
     * Return false from the callback to make world ignore the collision this step or true to process it normally. 
     * Additionally, you may override collision values, restitution, or surface velocity values.
     *
     * @~chinese 碰撞的两个形状相互接触。
     * 返回false的话，物理世界将忽略这一次的接触。负责正常处理两个形状的这一次接触。
     * 你可以在这个回调中自定义碰撞属性，例如弹力、表面速度等。
     */
    std::function<bool(PhysicsContact& contact, PhysicsContactPreSolve& solve)> onContactPreSolve;
    
    /**
     * @~english Two shapes are touching and their collision response has been processed. 
     * You can retrieve the collision impulse or kinetic energy at this time if you want to use it to calculate sound volumes or damage amounts. 
     *
     * @~chinese 两种形状相互接触并且它们的碰撞响应已被处理。
     * 如果你想使用它来计算音量或者伤害值，这时你可以检索碰撞冲力或动能。
     */
    std::function<void(PhysicsContact& contact, const PhysicsContactPostSolve& solve)> onContactPostSolve;
    
    /**
     * @~english It will called at two shapes separated, and only call it once.
     * onContactBegin and onContactSeparate will called in pairs.
     *
     * @~chinese 这个回调在两个碰撞的形状分离时被调用，并且只会被调用一次。
     * onContactBegin和onContactSeparate是成对被调用的。
     */
    std::function<void(PhysicsContact& contact)> onContactSeparate;
    
protected:
    bool init();
    void onEvent(EventCustom* event);
    
protected:
    EventListenerPhysicsContact();
    virtual ~EventListenerPhysicsContact();
    
    friend class PhysicsWorld;
};

/** @class EventListenerPhysicsContactWithBodies
 * @brief @~english This event listener only be called when bodyA and bodyB have contacts. 
 * @~chinese 碰撞事件监听器，只可以接收到刚体bodyA和刚体bodyB之间的碰撞事件。
 */
class CC_DLL EventListenerPhysicsContactWithBodies : public EventListenerPhysicsContact
{
public:
    /** @~english Create the listener. @~chinese 创建碰撞监听器。*/
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

/** @class EventListenerPhysicsContactWithShapes
 * @brief @~english This event listener only be called when shapeA and shapeB have contacts. 
 * @~chinese 碰撞事件监听器，只可以接收到形状shapeA和形状shapeB之间的碰撞事件。
 */
class CC_DLL EventListenerPhysicsContactWithShapes : public EventListenerPhysicsContact
{
public:
    /** @~english Create the listener. @~chinese 创建碰撞监听器。*/
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

/** @class EventListenerPhysicsContactWithGroup
 * @brief @~english This event listener only be called when shapeA or shapeB is in the group your specified.
 * @~chinese 碰撞事件监听器，只可以给定分组的形状之间的碰撞事件。
 */
class CC_DLL EventListenerPhysicsContactWithGroup : public EventListenerPhysicsContact
{
public:
    /** @~english Create the listener. @~chinese 创建碰撞监听器。 */
    static EventListenerPhysicsContactWithGroup* create(int group);
    
    virtual bool hitTest(PhysicsShape* shapeA, PhysicsShape* shapeB) override;
    virtual EventListenerPhysicsContactWithGroup* clone() override;
    
protected:
    int _group;
    
protected:
    EventListenerPhysicsContactWithGroup();
    virtual ~EventListenerPhysicsContactWithGroup();
};

/** @} */

NS_CC_END

#endif // CC_USE_PHYSICS
#endif //__CCPHYSICS_CONTACT_H__
