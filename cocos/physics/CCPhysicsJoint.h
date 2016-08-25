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

struct cpConstraint;

NS_CC_BEGIN

class Node;
class PhysicsBody;
class PhysicsWorld;

/**
 * @addtogroup physics
 * @{
 * @addtogroup physics_2d
 * @{
 */

/**
 * @brief An PhysicsJoint object connects two physics bodies together.
 */
class CC_DLL PhysicsJoint
{
protected:
    PhysicsJoint();
    virtual ~PhysicsJoint() = 0;

public:
    /**Get physics body a connected to this joint.*/
    inline PhysicsBody* getBodyA() const { return _bodyA; }
    
    /**Get physics body b connected to this joint.*/
    inline PhysicsBody* getBodyB() const { return _bodyB; }

    /**Get the physics world.*/
    inline PhysicsWorld* getWorld() const { return _world; }
    
    /**
     * Get this joint's tag.
     *
     * @return An integer number.
     */
    inline int getTag() const { return _tag; }
    
    /**
     * Set this joint's tag.
     *
     * @param tag An integer number that identifies a PhysicsJoint.
     */
    inline void setTag(int tag) { _tag = tag; }
    
    /** Determines if the joint is enable. */
    inline bool isEnabled() const { return _enable; }

    /** Enable/Disable the joint. */
    void setEnable(bool enable);
    
    /** Determines if the collision is enable. */
    inline bool isCollisionEnabled() const { return _collisionEnable; }
    
    /** Enable/disable the collision between two bodies. */
    void setCollisionEnable(bool enable);
    
    /** Remove the joint from the world. */
    void removeFormWorld();

    /** Set the max force between two bodies. */
    void setMaxForce(float force);
    
    /** Get the max force setting. */
    float getMaxForce() const { return _maxForce; }

protected:
    bool init(PhysicsBody* a, PhysicsBody* b);

    bool initJoint();
    
    /** Create constraints for this type joint */
    virtual bool createConstraints() { return false; }

    std::vector<cpConstraint*> _cpConstraints;
    PhysicsBody* _bodyA;
    PhysicsBody* _bodyB;
    PhysicsWorld* _world;

    bool _enable;
    bool _collisionEnable;
    bool _destroyMark;
    int _tag;
    float _maxForce;

    bool _initDirty;

    friend class PhysicsBody;
    friend class PhysicsWorld;
    friend class PhysicsDebugDraw;
};

/**
* @brief A fixed joint fuses the two bodies together at a reference point. Fixed joints are useful for creating complex shapes that can be broken apart later.
*/
class CC_DLL PhysicsJointFixed : public PhysicsJoint
{
public:
    /** Create a fixed joint.
     
     @param a A is the body to connect.
     @param b B is the body to connect.
     @param anchr It's the pivot position.
     @return A object pointer.
     */
    static PhysicsJointFixed* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr);

    virtual bool createConstraints() override;

protected:
    PhysicsJointFixed() {}
    virtual ~PhysicsJointFixed() {}

    Vec2 _anchr;
};

/**
* @brief A limit joint imposes a maximum distance between the two bodies, as if they were connected by a rope.
*/
class CC_DLL PhysicsJointLimit : public PhysicsJoint
{
public:
    /** Create a limit joint.
     
     @param a A is the body to connect.
     @param b B is the body to connect.
     @param anchr1 Anchr1 is the anchor point on body a.
     @param anchr2 Anchr2 is the anchor point on body b.
     @return A object pointer.
     */
    static PhysicsJointLimit* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2);
    
    /** Create a limit joint.
     
     @param a A is the body to connect.
     @param b B is the body to connect.
     @param anchr1 Anchr1 is the anchor point on body a.
     @param anchr2 Anchr2 is the anchor point on body b.
     @param min Define the allowed min distance of the anchor points.
     @param max Define the allowed max distance of the anchor points.
     @return A object pointer.
     */
    static PhysicsJointLimit* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2, float min, float max);

    /** Get the anchor point on body a.*/
    Vec2 getAnchr1() const;
    
    /** Set the anchor point on body a.*/
    void setAnchr1(const Vec2& anchr1);
    
    /** Get the anchor point on body b.*/
    Vec2 getAnchr2() const;
    
    /** Set the anchor point on body b.*/
    void setAnchr2(const Vec2& anchr2);
    
    /** Get the allowed min distance of the anchor points.*/
    float getMin() const;
    /** Set the min distance of the anchor points.*/
    void setMin(float min);
  
    /** Get the allowed max distance of the anchor points.*/
    float getMax() const;
    /** Set the max distance of the anchor points.*/
    void setMax(float max);

    virtual bool createConstraints() override;

protected:
    PhysicsJointLimit() {}
    virtual ~PhysicsJointLimit() {}

    Vec2 _anchr1;
    Vec2 _anchr2;
    float _min;
    float _max;
};

/**
* @brief A pin joint allows the two bodies to independently rotate around the anchor point as if pinned together.
*/
class CC_DLL PhysicsJointPin : public PhysicsJoint
{
public:
    /** Create a pin joint.
     
     @param a A is the body to connect.
     @param b B is the body to connect.
     @param pivot It's the pivot position.
     @return A object pointer.
     */
    static PhysicsJointPin* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& pivot);

    /** Create a pin joint.
     
     @param a A is the body to connect.
     @param b B is the body to connect.
     @param anchr1 Anchr1 is the anchor point on body a.
     @param anchr2 Anchr2 is the anchor point on body b.
     @return A object pointer.
     */
    static PhysicsJointPin* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2);

    virtual bool createConstraints() override;

protected:
    PhysicsJointPin() {}
    virtual ~PhysicsJointPin() {}

    bool _useSpecificAnchr;
    Vec2 _anchr1;
    Vec2 _anchr2;
};

/** Set the fixed distance with two bodies */
class CC_DLL PhysicsJointDistance : public PhysicsJoint
{
public:
    /** Create a fixed distance joint.
     
     @param a A is the body to connect.
     @param b B is the body to connect.
     @param anchr1 Anchr1 is the anchor point on body a.
     @param anchr2 Anchr2 is the anchor point on body b.
     @return A object pointer.
     */
    static PhysicsJointDistance* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2);

    /** Get the distance of the anchor points.*/
    float getDistance() const;
    /** Set the distance of the anchor points.*/
    void setDistance(float distance);
    virtual bool createConstraints() override;

protected:
    PhysicsJointDistance() {}
    virtual ~PhysicsJointDistance() {}

    Vec2 _anchr1;
    Vec2 _anchr2;
};

/** Connecting two physics bodies together with a spring. */
class CC_DLL PhysicsJointSpring : public PhysicsJoint
{
public:
    /** Create a fixed distance joint.
     
     @param a A is the body to connect.
     @param b B is the body to connect.
     @param anchr1 Anchr1 is the anchor point on body a.
     @param anchr2 Anchr2 is the anchor point on body b.
     @param stiffness It's the spring constant.
     @param damping It's how soft to make the damping of the spring.
     @return A object pointer.
     */
    static PhysicsJointSpring* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2, float stiffness, float damping);

    /** Get the anchor point on body a.*/
    Vec2 getAnchr1() const;

    /** Set the anchor point on body a.*/
    void setAnchr1(const Vec2& anchr1);

    /** Get the anchor point on body b.*/
    Vec2 getAnchr2() const;

    /** Set the anchor point on body b.*/
    void setAnchr2(const Vec2& anchr2);
    
    /** Get the distance of the anchor points.*/
    float getRestLength() const;
    
    /** Set the distance of the anchor points.*/
    void setRestLength(float restLength);
    
    /** Get the spring constant.*/
    float getStiffness() const;
    
    /** Set the spring constant.*/
    void setStiffness(float stiffness);
    
    /** Get the spring soft constant.*/
    float getDamping() const;
    
    /** Set the spring soft constant.*/
    void setDamping(float damping);
    
    virtual bool createConstraints() override;

protected:
    PhysicsJointSpring() {}
    virtual ~PhysicsJointSpring() {}

    Vec2 _anchr1;
    Vec2 _anchr2;
    float _stiffness;
    float _damping;
};

/** Attach body a to a line, and attach body b to a dot. */
class CC_DLL PhysicsJointGroove : public PhysicsJoint
{
public:
    /** Create a groove joint.
     
     @param a A is the body to connect.
     @param b B is the body to connect.
     @param grooveA The line begin position.
     @param grooveB The line end position.
     @param anchr2 Anchr2 is the anchor point on body b.
     @return A object pointer.
     */
    static PhysicsJointGroove* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& grooveA, const Vec2& grooveB, const Vec2& anchr2);

    /** Get the line begin position*/
    Vec2 getGrooveA() const;

    /** Set the line begin position*/
    void setGrooveA(const Vec2& grooveA);
    
    /** Get the line end position*/
    Vec2 getGrooveB() const;
    
    /** Set the line end position*/
    void setGrooveB(const Vec2& grooveB);
    
    /** Get the anchor point on body b.*/
    Vec2 getAnchr2() const;
    
    /** Set the anchor point on body b.*/
    void setAnchr2(const Vec2& anchr2);
    
    virtual bool createConstraints() override;

protected:
    PhysicsJointGroove() {}
    virtual ~PhysicsJointGroove() {}

    Vec2 _grooveA;
    Vec2 _grooveB;
    Vec2 _anchr2;
};

/** Likes a spring joint, but works with rotary. */
class CC_DLL PhysicsJointRotarySpring : public PhysicsJoint
{
public:
    /** Create a damped rotary spring joint.
     
     @param a A is the body to connect.
     @param b B is the body to connect.
     @param stiffness It's the spring constant.
     @param damping It's how soft to make the damping of the spring.
     @return A object pointer.
     */
    static PhysicsJointRotarySpring* construct(PhysicsBody* a, PhysicsBody* b, float stiffness, float damping);

    /** Get the relative angle in radians from the body a to b.*/
    float getRestAngle() const;

    /** Set the relative angle in radians from the body a to b.*/
    void setRestAngle(float restAngle);

    /** Get the spring constant.*/
    float getStiffness() const;
    
    /** Set the spring constant.*/
    void setStiffness(float stiffness);
    
    /** Get the spring soft constant.*/
    float getDamping() const;

    /** Set the spring soft constant.*/
    void setDamping(float damping);
    
    virtual bool createConstraints() override;

protected:
    PhysicsJointRotarySpring() {}
    virtual ~PhysicsJointRotarySpring() {}

    float _stiffness;
    float _damping;
};

/** Likes a limit joint, but works with rotary. */
class CC_DLL PhysicsJointRotaryLimit : public PhysicsJoint
{
public:
    /** Create a limit rotary joint.
     
     @param a A is the body to connect.
     @param b B is the body to connect.
     @param min It's min rotation limit in radians.
     @param max It's max rotation limit in radians.
     @return A object pointer.
     */
    static PhysicsJointRotaryLimit* construct(PhysicsBody* a, PhysicsBody* b, float min, float max);

    /** Create a limit rotary joint.
     
     @param a A is the body to connect.
     @param b B is the body to connect.
     @return A object pointer.
     */
    static PhysicsJointRotaryLimit* construct(PhysicsBody* a, PhysicsBody* b);

    /** Get the min rotation limit.*/
    float getMin() const;
    
    /** Set the min rotation limit.*/
    void setMin(float min);
    
    /** Get the max rotation limit.*/
    float getMax() const;
    
    /** Set the max rotation limit.*/
    void setMax(float max);
    
    virtual bool createConstraints() override;

protected:
    PhysicsJointRotaryLimit() {}
    virtual ~PhysicsJointRotaryLimit() {}

    float _min;
    float _max;
};

/** Works like a socket wrench. */
class CC_DLL PhysicsJointRatchet : public PhysicsJoint
{
public:
    /** Create a ratchet joint.
     
     @param a A is the body to connect.
     @param b B is the body to connect.
     @param phase Phase is the initial offset to use when deciding where the ratchet angles are.
     @param ratchet Ratchet is the distance between "clicks".
     @return A object pointer.
     */
    static PhysicsJointRatchet* construct(PhysicsBody* a, PhysicsBody* b, float phase, float ratchet);

    /** Get the ratchet angle.*/
    float getAngle() const;
    
    /** Set the ratchet angle.*/
    void setAngle(float angle);
    
    /** Get the initial offset.*/
    float getPhase() const;
    
    /** Set the initial offset.*/
    void setPhase(float phase);
    
    /** Get the distance between "clicks".*/
    float getRatchet() const;

    /** Set the distance between "clicks".*/
    void setRatchet(float ratchet);
    virtual bool createConstraints() override;

protected:
    PhysicsJointRatchet() {}
    virtual ~PhysicsJointRatchet() {}

    float _phase;
    float _ratchet;
};

/** Keeps the angular velocity ratio of a pair of bodies constant. */
class CC_DLL PhysicsJointGear : public PhysicsJoint
{
public:
    /** Create a gear joint.
     
     @param a A is the body to connect.
     @param b B is the body to connect.
     @param phase Phase is the initial angular offset of the two bodies.
     @param ratio Ratio is always measured in absolute terms.
     @return A object pointer.
     */
    static PhysicsJointGear* construct(PhysicsBody* a, PhysicsBody* b, float phase, float ratio);

    /** Get the angular offset of the two bodies.*/
    float getPhase() const;
    
    /** Set the angular offset of the two bodies.*/
    void setPhase(float phase);
    
    /** Get the ratio.*/
    float getRatio() const;
    
    /** Set the ratio.*/
    void setRatio(float ratchet);

    virtual bool createConstraints() override;

protected:
    PhysicsJointGear() {}
    virtual ~PhysicsJointGear() {}

    float _phase;
    float _ratio;
};

/** Keeps the relative angular velocity of a pair of bodies constant. */
class CC_DLL PhysicsJointMotor : public PhysicsJoint
{
public:
    /** Create a motor joint.
     
     @param a A is the body to connect.
     @param b B is the body to connect.
     @param rate Rate is the desired relative angular velocity.
     @return A object pointer.
     */
    static PhysicsJointMotor* construct(PhysicsBody* a, PhysicsBody* b, float rate);

    /** Get the relative angular velocity.*/
    float getRate() const;
    
    /** Set the relative angular velocity.*/
    void setRate(float rate);
    virtual bool createConstraints() override;

protected:
    PhysicsJointMotor() {}
    virtual ~PhysicsJointMotor() {}

    float _rate;
};

/** @} */
/** @} */


NS_CC_END

#endif // CC_USE_PHYSICS
#endif // __CCPHYSICS_JOINT_H__
