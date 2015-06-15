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
 * @addtogroup core
 * @{
 */

/**
@class PhysicsJoint
 * @brief @~english An PhysicsJoint object connects two physics bodies together.
 * @~chinese 一个PhysicsJoint(物理关节)对象用于将两个刚体连接在一起。
 */
class CC_DLL PhysicsJoint
{
protected:
    PhysicsJoint();
    virtual ~PhysicsJoint() = 0;

public:
    /**
    @~english Get the first physics body a connected to this joint. 
    @~chinese 得到连接到这个关节的第一个物理刚体。
    */
    inline PhysicsBody* getBodyA() const { return _bodyA; }
    
    /**
    @~english Get the second physics body b connected to this joint. 
    @~chinese 得到连接到这个关节的第二个物理刚体。
    */
    inline PhysicsBody* getBodyB() const { return _bodyB; }

    /**@~english Get the physics world. @~chinese 获取物理世界。*/
    inline PhysicsWorld* getWorld() const { return _world; }
    
    /**@~english
     * Get this joint's tag.
     *
     * @~chinese 
     * 得到关节的tag。
     * 
     * @return @~english An interger number.
     * @~chinese tag值。
     */
    inline int getTag() const { return _tag; }
    
    /**@~english
     * Set this joint's tag.
     *
     * @~chinese 
     * 设置tag。
     * 
     * @param tag @~english An interger number that identifies a PhysicsJoint.
     * @~chinese tag的值。
     */
    inline void setTag(int tag) { _tag = tag; }
    
    /** @~english Determines if the joint is enable.  @~chinese 关节是否处于开启状态。*/
    inline bool isEnabled() const { return _enable; }

    /** @~english Enable or disable the joint. @~chinese 启用或者禁用关节。*/
    void setEnable(bool enable);
    
    /** @~english Determines if the collsion is enable.  @~chinese 碰撞体是否启用。*/
    inline bool isCollisionEnabled() const { return _collisionEnable; }
    
    /** @~english Enable or disable collision. @~chinese 启用或者禁用碰撞体。
    void setCollisionEnable(bool enable);
    
    /** @~english Remove the joint from the world.  @~chinese 删除关节。*/
    void removeFormWorld();

    /** @~english Set the max force between two bodies.  @~chinese 设置两个物理刚体之间的最大力量。*/
    void setMaxForce(float force);
    
    /** @~english Get the max force setting.  @~chinese 得到物理刚体之间的最大力量。*/
    float getMaxForce() const { return _maxForce; }

protected:
    bool init(PhysicsBody* a, PhysicsBody* b);

    bool initJoint();
    
    /** @~english Create constraints for this type joint  @~chinese 为这类联合创建约束*/
    virtual bool createConstraints() { return false; }

    std::vector<cpConstraint*> _cpConstraints;
    PhysicsBody* _bodyA;
    PhysicsBody* _bodyB;
    PhysicsWorld* _world;

    bool _enable;
    bool _collisionEnable;
    bool _destoryMark;
    int _tag;
    float _maxForce;

    bool _initDirty;

    friend class PhysicsBody;
    friend class PhysicsWorld;
    friend class PhysicsDebugDraw;
};

/**
@class PhysicsJointFixed
* @brief 
@~english A fixed joint fuses the two bodies together at a reference point. Fixed joints are useful for creating complex shapes that can be broken apart later.
 @~chinese 固定关节把两个物理刚体连接到一起。它可以用于创建复杂的形状，这些形状在后面可以被破环成独立的刚体。
*/
class CC_DLL PhysicsJointFixed : public PhysicsJoint
{
public:
    /** @~english Create a fixed joint.
     
     * @~chinese 创建一个固定关节。
     * 
     @param a @~english A is the body to connect.
     * @~chinese 连接的第一个刚体。
     @param b @~english B is the body to connect.
     * @~chinese 连接的第二个刚体。
     @param anchr @~english It's the pivot position.
     * @~chinese 连接点的位置。
     @return @~english A object pointer.
     * @~chinese 固定物体关节。
     */
    static PhysicsJointFixed* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr);

    virtual bool createConstraints() override;

protected:
    PhysicsJointFixed() {}
    virtual ~PhysicsJointFixed() {}

    Vec2 _anchr;
};

/**
@class PhysicsJointLimit
* @brief @~english A limit joint imposes a maximum distance between the two bodies, as if they were connected by a rope.
 * @~chinese PhysicsJointLimit限制了两个物体之间的最大距离，就好像他们被一根绳子连接起来一样。
*/
class CC_DLL PhysicsJointLimit : public PhysicsJoint
{
public:
    /** @~english Create a limit joint.
     
     * @~chinese 创建一个PhysicsJointLimit。
     * 
     @param a @~english A is the body to connect.
     * @~chinese 连接的第一个刚体。
     @param b @~english B is the body to connect.
     * @~chinese 连接的第二个刚体。
     @param anchr1 @~english Anchr1 is the anchor point on body a.
     * @~chinese 连接第一个刚体的点。
     @param anchr2 @~english Anchr2 is the anchor point on body b.
     * @~chinese 连接第二个刚体的点。
     @return @~english A object pointer.
     * @~chinese 返回PhysicsJointLimit。
     */
    static PhysicsJointLimit* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2);
    
    /** @~english Create a limit joint.
     
     * @~chinese 创建一个PhysicsJointLimit。
     * 
     @param a @~english A is the body to connect.
     * @~chinese 连接的第一个刚体。
     @param b @~english B is the body to connect.
     * @~chinese 连接的第二个刚体。
     @param anchr1 @~english Anchr1 is the anchor point on body a.
     * @~chinese 连接第一个刚体的点。
     @param anchr2 @~english Anchr2 is the anchor point on body b.
     * @~chinese 连接第二个刚体的点。
     @param min @~english Define the allowed min distance of the anchor points.
     * @~chinese 两个连接点的最小距离。
     @param max @~english Define the allowed max distance of the anchor points.
     * @~chinese 两个连接点的最大距离。
     @return @~english A object pointer.
     * @~chinese 返回PhysicsJointLimit。
     */
    static PhysicsJointLimit* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2, float min, float max);

    /** @~english Get the anchor point on body a. @~chinese 得到连接第一个刚体的点。*/
    Vec2 getAnchr1() const;
    
    /** @~english Set the anchor point on body a. @~chinese 设置连接第一个刚体的点。*/
    void setAnchr1(const Vec2& anchr1);
    
    /** @~english Get the anchor point on body b. @~chinese 得到连接第二个刚体的点。*/
    Vec2 getAnchr2() const;
    
    /** @~english Set the anchor point on body b. @~chinese 设置连接第二个刚体的点。*/
    void setAnchr2(const Vec2& anchr2);
    
    /** @~english Get the allowed min distance of the anchor points. @~chinese 得到两个连接点的最小距离。*/
    float getMin() const;
    /** @~english Set the min distance of the anchor points. @~chinese 设置两个连接点的最小距离。*/
    void setMin(float min);
  
    /** @~english Get the allowed max distance of the anchor points. @~chinese 得到两个连接点的最大距离。*/
    float getMax() const;
    /** @~english Set the max distance of the anchor points. @~chinese 设置两个连接点的最大距离。*/
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
@class PhysicsJointPin
* @brief 
@~english A pin joint allows the two bodies to independently rotate around the anchor point as if pinned together.
 * @~chinese PhysicsJointPin允许两个物体独立旋转，就好像他们被钉在一起一样。
*/
class CC_DLL PhysicsJointPin : public PhysicsJoint
{
public:
    /** @~english Create a pin joint.
     
     * @~chinese 创建一个PhysicsJointPin。
     * 
     @param a @~english A is the body to connect.
     * @~chinese 连接的第一个刚体。
     @param b @~english B is the body to connect.
     * @~chinese 连接的第二个刚体。
     @param pivot @~english It's the pivot position.
     * @~chinese 连接点的位置。
     @return @~english A object pointer.
     * @~chinese 返回PhysicsJointPin。
     */
    static PhysicsJointPin* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& pivot);

    /** @~english Create a pin joint.
     
     * @~chinese 创建一个PhysicsJointPin。
     * 
     @param a @~english A is the body to connect.
     * @~chinese 连接的第一个刚体。
     @param b @~english B is the body to connect.
     * @~chinese 连接的第二个刚体。
     @param anchr1 @~english Anchr1 is the anchor point on body a.
     * @~chinese 连接的第一个刚体的点。
     @param anchr2 @~english Anchr2 is the anchor point on body b.
     * @~chinese 连接的第二个刚体的点。
     @return @~english A object pointer.
     * @~chinese 返回PhysicsJointPin。
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

/** 
@class PhysicsJointDistance
@brief
@~english Set the fixed distance with two bodies  
@~chinese 该关节用于在两个刚体之间设置一个固定距离。
*/
class CC_DLL PhysicsJointDistance : public PhysicsJoint
{
public:
    /** @~english Create a fixed distance joint.
     
     * @~chinese 创建一个PhysicsJointDistance。
     * 
     @param a @~english A is the body to connect.
     * @~chinese 连接的第一个刚体。
     @param b @~english B is the body to connect.
     * @~chinese 连接的第二个刚体。
     @param anchr1 @~english Anchr1 is the anchor point on body a.
     * @~chinese 连接的第一个刚体的点。
     @param anchr2 @~english Anchr2 is the anchor point on body b.
     * @~chinese 连接的第二个刚体的点。
     @return @~english A object pointer.
     * @~chinese 返回创建一个PhysicsJointDistance。
     */
    static PhysicsJointDistance* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2);

    /** @~english Get the distance of the anchor points. @~chinese 得到连接点之间的距离。*/
    float getDistance() const;
    /** @~english Set the distance of the anchor points. @~chinese 设置连接点之间的距离。*/
    void setDistance(float distance);
    virtual bool createConstraints() override;

protected:
    PhysicsJointDistance() {}
    virtual ~PhysicsJointDistance() {}

    Vec2 _anchr1;
    Vec2 _anchr2;
};

/** 
@class PhysicsJointSpring
@brief
@~english Connecting two physics bodies together with a spring.  
@~chinese PhysicsJointSpring用于连接两个刚体，其效果相当于一个弹簧。
*/
class CC_DLL PhysicsJointSpring : public PhysicsJoint
{
public:
    /** @~english Create a spring joint.
     
     * @~chinese 创建一个PhysicsJointSpring。
     * 
     @param a @~english A is the body to connect.
     * @~chinese 连接的第一个刚体。
     @param b @~english B is the body to connect.
     * @~chinese 连接的第二个刚体。
     @param anchr1 @~english Anchr1 is the anchor point on body a.
     * @~chinese 连接的第一个刚体的点。
     @param anchr2 @~english Anchr2 is the anchor point on body b.
     * @~chinese 连接的第二个刚体的点。
     @param stiffness @~english It's the spring constant.
     * @~chinese 关节的弹力系数。
     @param damping @~english It's how soft to make the damping of the spring.
     * @~chinese 关节的阻尼。
     @return @~english A object pointer.
     * @~chinese 返回PhysicsJointSpring。
     */
    static PhysicsJointSpring* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& anchr1, const Vec2& anchr2, float stiffness, float damping);

    /** @~english Get the anchor point on body a. @~chinese 得到连接的第一个刚体的点。*/
    Vec2 getAnchr1() const;

    /** @~english Set the anchor point on body a. @~chinese 设置连接的第一个刚体的点。*/
    void setAnchr1(const Vec2& anchr1);

    /** @~english Get the anchor point on body b. @~chinese 得到连接的第二个刚体的点。*/
    Vec2 getAnchr2() const;

    /** @~english Set the anchor point on body b. @~chinese 设置连接的第二个刚体的点。*/
    void setAnchr2(const Vec2& anchr2);
    
    /** @~english Get the distance of the anchor points. @~chinese 得到连接点之间的距离。*/
    float getRestLength() const;
    
    /** @~english Set the distance of the anchor points. @~chinese 设置连接点之间的距离。*/
    void setRestLength(float restLength);
    
    /** @~english Get the spring constant. @~chinese 得到弹力常数。*/
    float getStiffness() const;
    
    /** @~english Set the spring constant. @~chinese 设置弹力常数。*/
    void setStiffness(float stiffness);
    
    /** @~english Get the spring soft constant. @~chinese 得到阻尼系数。*/
    float getDamping() const;
    
    /** @~english Set the spring soft constant. @~chinese 设置阻尼系数。*/
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

/** 
@class PhysicsJointGroove
@brief
@~english Attach body a to a line, and attach body b to a dot.  
@~chinese 把第一个物体A连接到一条线上，把第二个物体连接到一个点上。
*/
class CC_DLL PhysicsJointGroove : public PhysicsJoint
{
public:
    /** @~english Create a groove joint.
     
     * @~chinese 创建一个PhysicsJointGroove。
     * 
     @param a @~english A is the body to connect.
     * @~chinese 连接的第一个刚体。
     @param b @~english B is the body to connect.
     * @~chinese 连接的第二个刚体。
     @param grooveA @~english The line begin position.
     * @~chinese 连接的第一个刚体的线的第一个端点。
     @param grooveB @~english The line end position.
     * @~chinese 连接的第一个刚体的线的第二个端点。
     @param anchr2 @~english Anchr2 is the anchor point on body b.
     * @~chinese 连接的第二个刚体的点。
     @return @~english A object pointer.
     * @~chinese 得到PhysicsJointGroove。
     */
    static PhysicsJointGroove* construct(PhysicsBody* a, PhysicsBody* b, const Vec2& grooveA, const Vec2& grooveB, const Vec2& anchr2);

    /** @~english Get the line begin position @~chinese 得到第一个物体连接线的第一个端点。*/
    Vec2 getGrooveA() const;

    /** @~english Set the line begin position @~chinese 设置第一个物体连接线的第一个端点。*/
    void setGrooveA(const Vec2& grooveA);
    
    /** @~english Get the line end position @~chinese 得到第一个物体连接线的第二个端点。*/
    Vec2 getGrooveB() const;
    
    /** @~english Set the line end position @~chinese 设置得到第一个物体连接线的第二个端点。*/
    void setGrooveB(const Vec2& grooveB);
    
    /** @~english Get the anchor point on body b. @~chinese 得到连接的第二个刚体的点。*/
    Vec2 getAnchr2() const;
    
    /** @~english Set the anchor point on body b. @~chinese 设置连接的第二个刚体的点。*/
    void setAnchr2(const Vec2& anchr2);
    
    virtual bool createConstraints() override;

protected:
    PhysicsJointGroove() {}
    virtual ~PhysicsJointGroove() {}

    Vec2 _grooveA;
    Vec2 _grooveB;
    Vec2 _anchr2;
};

/** 
@class PhysicsJointRotarySpring
@brief
@~english Likes a spring joint, but works with rotary.  
@~chinese 与PhysicsJointSpring类似，但是刚体可以自由旋转。
*/
class CC_DLL PhysicsJointRotarySpring : public PhysicsJoint
{
public:
    /** @~english Create a damped rotary spring joint.
     
     * @~chinese 创建一个PhysicsJointRotarySpring。
     * 
     @param a @~english A is the body to connect.
     * @~chinese 连接的第一个刚体。
     @param b @~english B is the body to connect.
     * @~chinese 连接的第二个刚体。
     @param stiffness @~english It's the spring constant.
     * @~chinese 关节的弹力系数。
     @param damping @~english It's how soft to make the damping of the spring.
     * @~chinese 关节的阻尼。
     @return @~english A object pointer.
     * @~chinese 派发了瞄准。
     */
    static PhysicsJointRotarySpring* construct(PhysicsBody* a, PhysicsBody* b, float stiffness, float damping);

    /** @~english Get the relative angle in radians from the body a to b. @~chinese 得到两个刚体物体之间的相对弧度角。*/
    float getRestAngle() const;

    /** @~english Set the relative angle in radians from the body a to b. @~chinese 设置两个刚体物体之间的相对弧度角。*/
    void setRestAngle(float restAngle);

    /** @~english Get the spring constant. @~chinese 得到弹力系数。*/
    float getStiffness() const;
    
    /** @~english Set the spring constant. @~chinese 设置弹力系数。*/
    void setStiffness(float stiffness);
    
    /** @~english Get the spring soft constant. @~chinese 得到阻尼系数。*/
    float getDamping() const;

    /** @~english Set the spring soft constant. @~chinese 设置阻尼系数。*/
    void setDamping(float damping);
    
    virtual bool createConstraints() override;

protected:
    PhysicsJointRotarySpring() {}
    virtual ~PhysicsJointRotarySpring() {}

    float _stiffness;
    float _damping;
};

/** 
@~english Likes a limit joint, but works with rotary.  
@~chinese 与PhysicsJointLimit类似，但是刚体可以自由旋转。
*/
class CC_DLL PhysicsJointRotaryLimit : public PhysicsJoint
{
public:
    /** @~english Create a limit rotary joint.
     
     * @~chinese 创建一个PhysicsJointRotaryLimit。
     * 
     @param a @~english A is the body to connect.
     * @~chinese 连接的第一个刚体。
     @param b @~english B is the body to connect.
     * @~chinese 连接的第二个刚体。
     @param min @~english It's min rotation limit in radians.
     * @~chinese 两个物体之间的最小旋转角度。
     @param max @~english It's max rotation limit in radians.
     * @~chinese 两个物体之间的最大旋转角度。
     @return @~english A object pointer.
     * @~chinese 返回PhysicsJointRotaryLimit。
     */
    static PhysicsJointRotaryLimit* construct(PhysicsBody* a, PhysicsBody* b, float min, float max);

    /** @~english Create a limit rotary joint.
     
     * @~chinese 创建一个PhysicsJointRotaryLimit。
     * 
     @param a @~english A is the body to connect.
     * @~chinese 连接的第一个刚体。
     @param b @~english B is the body to connect.
     * @~chinese 连接的第二个刚体。
     @return @~english A object pointer.
     * @~chinese 返回PhysicsJointRotaryLimit。
     */
    static PhysicsJointRotaryLimit* construct(PhysicsBody* a, PhysicsBody* b);

    /** @~english Get the min rotation limit. @~chinese 得到最小旋转角度。*/
    float getMin() const;
    
    /** @~english Set the min rotation limit. @~chinese 设置最小旋转角度。*/
    void setMin(float min);
    
    /** @~english Get the max rotation limit. @~chinese 得到最大旋转角度。*/
    float getMax() const;
    
    /** @~english Set the max rotation limit. @~chinese 设置最大旋转角度。*/
    void setMax(float max);
    
    virtual bool createConstraints() override;

protected:
    PhysicsJointRotaryLimit() {}
    virtual ~PhysicsJointRotaryLimit() {}

    float _min;
    float _max;
};

/** 
@~english Works like a socket wrench.  
@~chinese PhysicsJointRatchet就像一个连接器一样涌来连接两个身体。
*/
class CC_DLL PhysicsJointRatchet : public PhysicsJoint
{
public:
    /** @~english Create a ratchet joint.
     
     * @~chinese 创建一个PhysicsJointRatchet。
     * 
     @param a @~english A is the body to connect.
     * @~chinese 要被连接的身体A。
     @param b @~english B is the body to connect.
     * @~chinese 要被连接的身体B。
     @param phase @~english Phase is the initial offset to use when deciding where the ratchet angles are.
     * @~chinese 阶段的初始偏移量使用当决定棘轮角度在哪里。
     @param ratchet @~english Ratchet is the distance between "clicks".
     * @~chinese 棘轮是“点击”之间的距离。
     @return @~english A object pointer.
     * @~chinese 创建成功返回PhysicsJointRatchet对象，否则返回空指针。
     */
    static PhysicsJointRatchet* construct(PhysicsBody* a, PhysicsBody* b, float phase, float ratchet);

    /** @~english Get the ratchet angle. @~chinese 棘轮角。*/
    float getAngle() const;
    
    /** @~english Set the ratchet angle. @~chinese 设置棘轮角。*/
    void setAngle(float angle);
    
    /** @~english Get the initial offset. @~chinese 获得的初始偏移量。*/
    float getPhase() const;
    
    /** @~english Set the initial offset. @~chinese 设置初始偏移量。*/
    void setPhase(float phase);
    
    /** @~english Get the distance between "clicks". @~chinese “点击”之间的距离。*/
    float getRatchet() const;

    /** @~english Set the distance between "clicks". @~chinese “点击”之间的距离。*/
    void setRatchet(float ratchet);
    virtual bool createConstraints() override;

protected:
    PhysicsJointRatchet() {}
    virtual ~PhysicsJointRatchet() {}

    float _phase;
    float _ratchet;
};

/** 
@~english Keeps the angular velocity ratio of a pair of bodies constant.  
@~chinese 让两个刚体之间的旋转角速度保持一个常数。
*/
class CC_DLL PhysicsJointGear : public PhysicsJoint
{
public:
    /** @~english Create a gear joint.
     
     * @~chinese 创建一个PhysicsJointGear。
     * 
     @param a @~english A is the body to connect.
     * @~chinese 连接的第一个刚体。
     @param b @~english B is the body to connect.
     * @~chinese 连接的第二个刚体。
     @param phase @~english Phase is the initial angular offset of the two bodies.
     * @~chinese 两个物体的初始角度差。
     @param ratio @~english Ratio is always measured in absolute terms.
     * @~chinese 两个物体的旋转角速度比。
     @return @~english A object pointer.
     * @~chinese 返回的PhysicsJointGear。
     */
    static PhysicsJointGear* construct(PhysicsBody* a, PhysicsBody* b, float phase, float ratio);

    /** @~english Get the angular offset of the two bodies. @~chinese 得到两个物体的初始角度差。*/
    float getPhase() const;
    
    /** @~english Set the angular offset of the two bodies. @~chinese 设置两个物体的初始角度差。*/
    void setPhase(float phase);
    
    /** @~english Get the ratio. @~chinese 得到旋转角速度比率。*/
    float getRatio() const;
    
    /** @~english Set the ratio. @~chinese 设置旋转角速度比率。*/
    void setRatio(float ratchet);

    virtual bool createConstraints() override;

protected:
    PhysicsJointGear() {}
    virtual ~PhysicsJointGear() {}

    float _phase;
    float _ratio;
};

/** 
@~english Keeps the relative angular velocity of a pair of bodies constant.  
@~chinese PhysicsJointMotor用于保证两个物体的相对角速度是一个常数。
*/
class CC_DLL PhysicsJointMotor : public PhysicsJoint
{
public:
    /** @~english Create a motor joint.
     
     * @~chinese 创建一个PhysicsJointMotor。
     * 
     @param a @~english A is the body to connect.
     * @~chinese 连接的第一个刚体。
     @param b @~english B is the body to connect.
     * @~chinese 连接的第二个刚体。
     @param rate @~english Rate is the desired relative angular velocity.
     * @~chinese 两个物体的相对角速度
     @return @~english A object pointer.
     * @~chinese 返回PhysicsJointMotor。
     */
    static PhysicsJointMotor* construct(PhysicsBody* a, PhysicsBody* b, float rate);

    /** @~english Get the relative angular velocity. @~chinese 得到相对角速度。*/
    float getRate() const;
    
    /** @~english Set the relative angular velocity. @~chinese 设置相对角速度。*/
    void setRate(float rate);
    virtual bool createConstraints() override;

protected:
    PhysicsJointMotor() {}
    virtual ~PhysicsJointMotor() {}

    float _rate;
};

/** @} */

NS_CC_END

#endif // CC_USE_PHYSICS
#endif // __CCPHYSICS_JOINT_H__
