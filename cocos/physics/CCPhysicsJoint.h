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
 * @brief An PhysicsJoint object connects two physics bodies together.
 */
class CC_DLL PhysicsJoint
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
    /** Enable/Disable the joint */
    void setEnable(bool enable);
    inline bool isCollisionEnabled() const { return _collisionEnable; }
    /** Enable/disable the collision between two bodies */
    void setCollisionEnable(bool enable);
    /** Remove the joint from the world */
    void removeFormWorld();
    /** Distory the joint*/
    static void destroy(PhysicsJoint* joint);
    
    /** Set the max force between two bodies */
    void setMaxForce(float force);
    /** Get the max force setting */
    float getMaxForce() const;
    
protected:
    bool init(PhysicsBody* a, PhysicsBody* b);
    
    /**
     * PhysicsShape is PhysicsBody's friend class, but all the subclasses isn't. so this method is use for subclasses to catch the bodyInfo from PhysicsBody.
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
 * @brief A fixed joint fuses the two bodies together at a reference point. Fixed joints are useful for creating complex shapes that can be broken apart later.
 */
class CC_DLL PhysicsJointFixed : public PhysicsJoint
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
 * @brief A limit joint imposes a maximum distance between the two bodies, as if they were connected by a rope.
 */
class CC_DLL PhysicsJointLimit : public PhysicsJoint
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
 * @brief A pin joint allows the two bodies to independently rotate around the anchor point as if pinned together.
 */
class CC_DLL PhysicsJointPin : public PhysicsJoint
{
public:
    static PhysicsJointPin* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr);
    
protected:
    bool init(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr);
    
protected:
    PhysicsJointPin() {}
    virtual ~PhysicsJointPin() {}
};

/** Set the fixed distance with two bodies */
class CC_DLL PhysicsJointDistance : public PhysicsJoint
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

/** Connecting two physics bodies together with a spring. */
class CC_DLL PhysicsJointSpring : public PhysicsJoint
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

/** Attach body a to a line, and attach body b to a dot */
class CC_DLL PhysicsJointGroove : public PhysicsJoint
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

/** Likes a spring joint, but works with rotary */
class CC_DLL PhysicsJointRotarySpring : public PhysicsJoint
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

/** Likes a limit joint, but works with rotary */
class CC_DLL PhysicsJointRotaryLimit : public PhysicsJoint
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

/** Works like a socket wrench. */
class CC_DLL PhysicsJointRatchet : public PhysicsJoint
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

/** Keeps the angular velocity ratio of a pair of bodies constant. */
class CC_DLL PhysicsJointGear : public PhysicsJoint
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

/** Keeps the relative angular velocity of a pair of bodies constant */
class CC_DLL PhysicsJointMotor : public PhysicsJoint
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
