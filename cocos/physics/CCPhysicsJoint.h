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

#ifndef __CCPHYSICS_JOINT_H__
#define __CCPHYSICS_JOINT_H__

#include "base/ccConfig.h"
#if CC_USE_PHYSICS

#include "base/CCRef.h"
#include "math/CCGeometry.h"

NS_CC_BEGIN

class Node;
class PhysicsBody;
class PhysicsWorld;
class PhysicsJointInfo;
class PhysicsBodyInfo;

/*
 * @brief 一个PhysicsJoint 对象把两个物理body连接在一起。
 */
class PhysicsJoint
{
protected:
    PhysicsJoint();
    virtual ~PhysicsJoint() = 0;

public:
    inline PhysicsBody* getBodyA() const { return _bodyA; }
    inline PhysicsBody* getBodyB() const { return _bodyB; }
    inline PhysicsWorld* getWorld() const { return _world; }
    inline int getTag() const { return _tag; }
    inline void setTag(int tag) { _tag = tag; }
    inline bool isEnabled() const { return _enable; }
    /** 设置关节点是否激活 */
    void setEnable(bool enable);
    inline bool isCollisionEnabled() const { return _collisionEnable; }
    /** 设置两个连接的body间是否发生冲突 */
    void setCollisionEnable(bool enable);
    /** 从物理世界移除这个关节点 */
    void removeFormWorld();
    /** 销毁某个关节点 */
    static void destroy(PhysicsJoint* joint);
    
    /** 设置两个连接的body相互间最大的作用力 */
    void setMaxForce(float force);
    /** 获取两个连接的body相互间最大的作用力 */
    float getMaxForce() const;
    
protected:
    bool init(PhysicsBody* a, PhysicsBody* b);
    
    /**
     * PhysicsShape 是 PhsicsBody的友元类，但是它的子类们不是。所以这个方法是让它的子类们能够从physicsBody中获取信息。
     */
    PhysicsBodyInfo* getBodyInfo(PhysicsBody* body) const;
    Node* getBodyNode(PhysicsBody* body) const;
    
protected:
    PhysicsBody* _bodyA;
    PhysicsBody* _bodyB;
    PhysicsWorld* _world;
    PhysicsJointInfo* _info;
    bool _enable;
    bool _collisionEnable;
    bool _destoryMark;
    int _tag;
    
    friend class PhysicsBody;
    friend class PhysicsWorld;
    friend class PhysicsDebugDraw;
};

/*
 * @brief 一个固定的关节点在某一个参考点把两个body融合在一起。固定的关节点对于创建复杂的、可以在之后断裂的形状很有用。
 */
class PhysicsJointFixed : public PhysicsJoint
{
public:
    static PhysicsJointFixed* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr);
    
protected:
    bool init(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr);
    
protected:
    PhysicsJointFixed() {}
    virtual ~PhysicsJointFixed() {}
};

/*
 * @brief 一个有限的关节限定了两个body间最大的距离，就像他们之间被一条绳子连接一样。
 */
class PhysicsJointLimit : public PhysicsJoint
{
public:
    static PhysicsJointLimit* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2);
    static PhysicsJointLimit* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2, float min, float max);
    
    Vec2 getAnchr1() const;
    void setAnchr1(const Vec2& anchr1);
    Vec2 getAnchr2() const;
    void setAnchr2(const Vec2& anchr2);
    float getMin() const;
    void setMin(float min);
    float getMax() const;
    void setMax(float max);
    
protected:
    bool init(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2, float min, float max);
    
protected:
    PhysicsJointLimit() {}
    virtual ~PhysicsJointLimit() {}
};

/*
 * @brief 一个pin 关节点允许两个body独立地以锚点为轴旋转如果pinned在一起。
 */
class PhysicsJointPin : public PhysicsJoint
{
public:
    static PhysicsJointPin* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr);
    
protected:
    bool init(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr);
    
protected:
    PhysicsJointPin() {}
    virtual ~PhysicsJointPin() {}
};

/** 设置两个body之间固定的距离。 */
class PhysicsJointDistance : public PhysicsJoint
{
public:
    static PhysicsJointDistance* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2);
    
    float getDistance() const;
    void setDistance(float distance);
    
protected:
    bool init(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2);
    
protected:
    PhysicsJointDistance() {}
    virtual ~PhysicsJointDistance() {}
};

/** 用一个弹簧连接两个物理body */
class PhysicsJointSpring : public PhysicsJoint
{
public:
    static PhysicsJointSpring* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2, float stiffness, float damping);
    Vec2 getAnchr1() const;
    void setAnchr1(const Vec2& anchr1);
    Vec2 getAnchr2() const;
    void setAnchr2(const Vec2& anchr2);
    float getRestLength() const;
    void setRestLength(float restLength);
    float getStiffness() const;
    void setStiffness(float stiffness);
    float getDamping() const;
    void setDamping(float damping);
    
protected:
    bool init(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2, float stiffness, float damping);
    
protected:
    PhysicsJointSpring() {}
    virtual ~PhysicsJointSpring() {}
};

/** 连接一个body a到一条线、连接一个body b到一个点 */
class PhysicsJointGroove : public PhysicsJoint
{
public:
    static PhysicsJointGroove* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& grooveA, const Vec2& grooveB, const Vec2& anchr2);
    
    Vec2 getGrooveA() const;
    void setGrooveA(const Vec2& grooveA);
    Vec2 getGrooveB() const;
    void setGrooveB(const Vec2& grooveB);
    Vec2 getAnchr2() const;
    void setAnchr2(const Vec2& anchr2);
    
protected:
    bool init(PhysicsBody* a, PhysicsBody* b, const Vec2& grooveA, const Vec2& grooveB, const Vec2& anchr);
    
protected:
    PhysicsJointGroove() {}
    virtual ~PhysicsJointGroove() {}
};

/** 像一个弹簧关节点，但是能够可以旋转 */
class PhysicsJointRotarySpring : public PhysicsJoint
{
public:
    static PhysicsJointRotarySpring* construct(PhysicsBody* a, PhysicsBody* b, float stiffness, float damping);
    
    float getRestAngle() const;
    void setRestAngle(float restAngle);
    float getStiffness() const;
    void setStiffness(float stiffness);
    float getDamping() const;
    void setDamping(float damping);
    
protected:
    bool init(PhysicsBody* a, PhysicsBody* b, float stiffness, float damping);
    
protected:
    PhysicsJointRotarySpring() {}
    virtual ~PhysicsJointRotarySpring() {}
};

/** 跟有限关节点差不多,不过能够旋转 */
class PhysicsJointRotaryLimit : public PhysicsJoint
{
public:
    static PhysicsJointRotaryLimit* construct(PhysicsBody* a, PhysicsBody* b, float min, float max);
    static PhysicsJointRotaryLimit* construct(PhysicsBody* a, PhysicsBody* b);
    
    float getMin() const;
    void setMin(float min);
    float getMax() const;
    void setMax(float max);
    
protected:
    bool init(PhysicsBody* a, PhysicsBody* b, float min, float max);
    
protected:
    PhysicsJointRotaryLimit() {}
    virtual ~PhysicsJointRotaryLimit() {}
};

/** 跟插座扳手关节点差不多 */
class PhysicsJointRatchet : public PhysicsJoint
{
public:
    static PhysicsJointRatchet* construct(PhysicsBody* a, PhysicsBody* b, float phase, float ratchet);
    
    float getAngle() const;
    void setAngle(float angle);
    float getPhase() const;
    void setPhase(float phase);
    float getRatchet() const;
    void setRatchet(float ratchet);
    
protected:
    bool init(PhysicsBody* a, PhysicsBody* b, float phase, float ratchet);
    
protected:
    PhysicsJointRatchet() {}
    virtual ~PhysicsJointRatchet() {}
};

/** 保持一对body的恒定角速率. */
class PhysicsJointGear : public PhysicsJoint
{
public:
    static PhysicsJointGear* construct(PhysicsBody* a, PhysicsBody* b, float phase, float ratio);
    
    float getPhase() const;
    void setPhase(float phase);
    float getRatio() const;
    void setRatio(float ratchet);
    
protected:
    bool init(PhysicsBody* a, PhysicsBody* b, float phase, float ratio);
    
protected:
    PhysicsJointGear() {}
    virtual ~PhysicsJointGear() {}
};

/** 保持一对body的恒定相对角速率 */
class PhysicsJointMotor : public PhysicsJoint
{
public:
    static PhysicsJointMotor* construct(PhysicsBody* a, PhysicsBody* b, float rate);
    
    float getRate() const;
    void setRate(float rate);
    
protected:
    bool init(PhysicsBody* a, PhysicsBody* b, float rate);
    
protected:
    PhysicsJointMotor() {}
    virtual ~PhysicsJointMotor() {}
};

NS_CC_END

#endif // CC_USE_PHYSICS
#endif // __CCPHYSICS_JOINT_H__
