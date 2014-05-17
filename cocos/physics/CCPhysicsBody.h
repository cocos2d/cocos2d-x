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

#ifndef __CCPHYSICS_BODY_H__
#define __CCPHYSICS_BODY_H__

#include "base/ccConfig.h"
#if CC_USE_PHYSICS

#include "base/CCRef.h"
#include "math/CCGeometry.h"
#include "physics/CCPhysicsShape.h"
#include "base/CCVector.h"

NS_CC_BEGIN

class Node;
class Sprite;
class PhysicsWorld;
class PhysicsJoint;
class PhysicsBodyInfo;

typedef Vec2 Vect;


const PhysicsMaterial PHYSICSBODY_MATERIAL_DEFAULT(0.1f, 0.5f, 0.5f);

/**
 * 一个被物理反应影响的body
 * 可以跟一个或多个形状关联
 * 如果你使用createXXX的函数创建body,它会使用你指定的密度(默认由PHYSICSBODY_MATERIAL_DEFAULT指定，默认值为0.1f)自动计算质量和力矩，基于计算公式：质量 = 密度 x 体积。
 * if you create body with createXXX, it will automatically compute mass and moment with density your specified(which is PHYSICSBODY_MATERIAL_DEFAULT by default, and the density value is 0.1f), and it based on the formular: mass = density * area.
 * 如果你使用createEdgeXXX创建body，质量和力矩将默认为PHYSICS_INFINITY的值，body将成为一个静态的body。
 * if you create body with createEdgeXXX, the mass and moment will be PHYSICS_INFINITY by default. and it's a static body.
 * 你可以改变质量和力矩 使用setMass 和 setMoment 函数，你可以通过setDynamic改变body使其成为静态的或是动态的。
 * you can change mass and moment with setMass() and setMoment(). and you can change the body to be dynamic or static by use function setDynamic().
 */
class PhysicsBody : public Ref
{
public:
    /** 使用默认的质量和力矩创建body */
    static PhysicsBody* create();
    /** 指定质量、使用默认的力矩创建body */
    static PhysicsBody* create(float mass);
    /** 指定质量、力矩创建body */
    static PhysicsBody* create(float mass, float moment);
    /** 创建一个包含圆形形状的body */
    static PhysicsBody* createCircle(float radius, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    /** 创建一个包含box形状的body */
    static PhysicsBody* createBox(const Size& size, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    /**
     * @brief 创建一个包含多边形的body。
     * points 是一个包含Vec2结构的数组，用顺时针的顶点定义凸多边形。
     */
    static PhysicsBody* createPolygon(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    
    /** 创建一个包含边缘片段形状的body */
    static PhysicsBody* createEdgeSegment(const Vec2& a, const Vec2& b, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, float border = 1);
    /** 创建一个包含边缘box形状的body */
    static PhysicsBody* createEdgeBox(const Size& size, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, float border = 1, const Vec2& offset = Vec2::ZERO);
    /** 创建一个包含边缘五边形形状的body */
    static PhysicsBody* createEdgePolygon(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, float border = 1);
    /** 创建一个包含边缘链形状的body */
    static PhysicsBody* createEdgeChain(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, float border = 1);
    
    /*
     * @brief 给body增加一个形状
     * @param shape 增加的形状
     * @param addMassAndMoment 如果true，这个形状的质量和力矩也将添加到body去
     */
    virtual PhysicsShape* addShape(PhysicsShape* shape, bool addMassAndMoment = true);
    /*
     * @brief 在body中移除一个形状
     * @param shape 移除的形状
     * @param reduceMassAndMoment 如果true，body的质量和力矩将被这个形状减少。默认是true。
     */
    void removeShape(PhysicsShape* shape, bool reduceMassAndMoment = true);
    /*
     * @brief 在body中移除一个形状
     * @param tag 移除的形状的tag
     * @param reduceMassAndMoment 如果true，body的质量和力矩将被这个形状减少。默认是true。
     */
    void removeShape(int tag, bool reduceMassAndMoment = true);
    /* 移除所有形状 */
    void removeAllShapes(bool reduceMassAndMoment = true);
    /* 获取body的形状 */
    inline const Vector<PhysicsShape*>& getShapes() const { return _shapes; }
    /* 获取body的第一个形状 */
    inline PhysicsShape* getFirstShape() const { return _shapes.size() >= 1 ? _shapes.at(0) : nullptr; }
    /* 根据tag获取body的形状 */
    PhysicsShape* getShape(int tag) const;
    
    /** 对body应用一个瞬时力 */
    virtual void applyForce(const Vect& force);
    /** 对body应用一个瞬时力 */
    virtual void applyForce(const Vect& force, const Vec2& offset);
    /** 重置对body应用的瞬时力 */
    virtual void resetForces();
    /** 对body应用一个持久力 */
    virtual void applyImpulse(const Vect& impulse);
    /** 对body应用一个持久力 */
    virtual void applyImpulse(const Vect& impulse, const Vec2& offset);
    /** 对body应用一个转矩 */
    virtual void applyTorque(float torque);
    
    /** 设置body的速度 */
    virtual void setVelocity(const Vect& velocity);
    /** 获取body的速度 */
    virtual Vec2 getVelocity();
    /** 设置body的角速率 */
    virtual void setAngularVelocity(float velocity);
    /** 基于局部坐标获取body的角速度 */
    virtual Vec2 getVelocityAtLocalPoint(const Vec2& point);
    /** 基于世界坐标获取body的角速度 */
    virtual Vec2 getVelocityAtWorldPoint(const Vec2& point);
    /**获取body的角速率 */
    virtual float getAngularVelocity();
    /** 设置body的最大速率 */
    virtual void setVelocityLimit(float limit);
    /**  获取body的最大速率 */
    virtual float getVelocityLimit();
    /** 设置body的最大角速率 */
    virtual void setAngularVelocityLimit(float limit);
    /** 获取body的最大角速率 */
    virtual float getAngularVelocityLimit();
    
    /** 从body添加到的世界中移除这个body */
    void removeFromWorld();
    
    /** 获取body添加到的世界 */
    inline PhysicsWorld* getWorld() const { return _world; }
    /** 获取body所拥有的关节点 */
    inline const std::vector<PhysicsJoint*>& getJoints() const { return _joints; }
    
    /** 获取body被设置的对应的sprite */
    inline Node* getNode() const { return _node; }
    
    /**
     * 定义物理body属于哪种分类的一个mask
     * 在一个场景内的每一个物理body可以被分配到最多32个分类,每个对应1个bit在bit mask中。你定义你游戏中使用的mask值。和属性collisionBitMask、contactTestBitMask互相协调，你定义哪种物理body互相之间的交互和什么时候你的游戏会被这些交互通知。
     * 默认值是0xFFFFFFFF (所有位被设成1)。
     */
    void setCategoryBitmask(int bitmask);
    /** 
     * 定义哪种分类的body导致和这个物理body发生交叉通知的一个mask
     * 当两个body共享同一片控件，每个body的分类mask会跟对方的contact mask通过“逻辑和”（即&&）操作。如果任意一个的结果是一个非0值，一个PhysicsContact的对象会被生成和传送到物理世界的委托。为了最好的表现，仅设置在contact mask里设置 你感兴趣的交互 所对应的bit。
     * 默认值是0x00000000 (所有位被设成0)。
     */
    void setContactTestBitmask(int bitmask);
    /**
     * 定义物理body可以跟那些分类的物理body发生冲突的一个mask
     * 当两个物理body彼此碰撞时，一个冲突可能会发生。这个body的冲突mask 会跟另一个body的分类mask 通过逻辑和的操作比较。如果结果是个非0值，那么这个body会被这个冲突影响。每个body独立的选择它是否会被另一个body影响。比如说ini可能会使用这个mask 去避免会发生对一个body的速率发生微小的变化的冲突计算。
     * 默认值是0xFFFFFFFF (所有位被设成1)。
     */
    void setCollisionBitmask(int bitmask);
    /** 获取 分类（category） mask bit*/
    inline int getCategoryBitmask() const { return _categoryBitmask; }
    /** 获取 碰撞（contact）  mask  bit */
    inline int getContactTestBitmask() const { return _contactTestBitmask; }
    /** 获取 冲突（collsion） mask bit */
    inline int getCollisionBitmask() const { return _collisionBitmask; }
    
    /** 
     * 设置body的分组
     * 冲突分组让你可以指定一个整数的分组的索引。你可以通过指定相同的index，（正数代表总是冲突，负数代表从不冲突）完成上述的操作。
     * 它比bit masks有更多的优先度
     */
    void setGroup(int group);
    /** 获取body的分组*/
    inline int getGroup() const { return _group; }
    
    /** 获取body的坐标 */
    Vec2 getPosition() const;
    /** 获取body的旋转角度 */
    float getRotation() const;
    
    /** 设置body的坐标偏移（相对于node的坐标来说） */
    void setPositionOffset(const Vec2& position);
    /** 获取body的坐标偏移 */
    Vec2 getPositionOffset() const;
    /** 设置body的旋转偏移（相对于node的旋转角度来说）*/
    void setRotationOffset(float rotation);
    /** 获取body的旋转偏移 */
    float getRotationOffset() const;
    
    /**
     * @brief 获取这个body是否动态的
     * 一个动态的body会受重力影响。
     */
    inline bool isDynamic() const { return _dynamic; }
    /**
     * @brief 设置body是否动态的
     *一个动态的body会受重力影响。
     */
    void setDynamic(bool dynamic);
    
    /**
     * @brief 设置body的质量
     * @note 如果你需要增加/减少 body 的质量，不要使用setMass(getMass() +/- mass),因为body的质量可能会等于PHYSICS_INFINITY，这样会导致一些不可预期的结果，请使用addMass()代替。
     */
    void setMass(float mass);
    /** 获取body的质量 */
    inline float getMass() const { return _mass; }
    /**
     * @brief 增加body的质量
     * 如果_mass 等于PHYSICS_INFINITY，它会保持原样。
     * 如果mass等于PHYSICS_INFINITY,_mass会变成PHYSICS_INFINITY.
     * 如果mass等于-PHYSICS_INFINITY,_mass不会改变。
     * 如果mass+_mass() <= 0,_mass会等于MASS_DEFAULT（1.0）
     * 否则，_mass = mass + _mass;
     */
    void addMass(float mass);
    
    /**
     * @brief 设置body的惯性力矩
     * @note 如果你需要增加/减少 body 的力矩，不要使用setMoment(getMoment() +/- moment),因为body的力矩可能会等于PHYSICS_INFINITY，这样会导致一些不可预期的结果，请使用addMoment()代替。
     if you need add/subtract moment to body, don't use setMoment(getMoment() +/- moment), because the moment of body may be equal to PHYSICS_INFINITY, it will cause some unexpected result, please use addMoment() instead.
     */
    void setMoment(float moment);
    /** 获取body惯性的力矩 */
    inline float getMoment() const { return _moment; }
    /**
     * @brief 增加body的力矩
     * 如果_moment == PHYSICS_INFINITY，它会保持。
     * 如果 moment == PHYSICS_INFINITY, _moment 会变成 PHYSICS_INFINITY.
     * 如果 moment == -PHYSICS_INFINITY, _moment 不会改变.
     * 如果 moment + _moment <= 0, _moment 会等于 MASS_DEFAULT(1.0)
     * 否则，moment = moment + _moment;
     */
    void addMoment(float moment);
    /** 获取线性阻尼 */
    inline float getLinearDamping() const { return _linearDamping; }
    /** 
     * 设置线性阻尼
     * 被用作模拟作用在body上德流体或是空气摩擦力
     * 值的范围是0.0f到1.0f
     */
    inline void setLinearDamping(float damping) { _linearDamping = damping; updateDamping(); }
    /** 获取角阻尼 */
    inline float getAngularDamping() const { return _angularDamping; }
    /**
     * 设置角阻尼。
     * 被用作模拟作用在body上德流体或是空气摩擦力
     * 值的范围是0.0f到1.0f
     */
    inline void setAngularDamping(float damping) { _angularDamping = damping; updateDamping(); }
    
    /** 获取body是否休眠 */
    bool isResting() const;
    /** 设置body休止 */
    void setResting(bool rest) const;
    /** 
     * 获取body是否激活的
     * 如果body没有被激活，它不会被世界模拟。
     */
    inline bool isEnabled() const { return _enabled; }
    /**
     * 设置是否激活
     * 如果body没有被激活，它不会被世界模拟。
     */
    void setEnable(bool enable);
    
    /** 获取这个body 是否能被旋转 */
    inline bool isRotationEnabled() const { return _rotationEnabled; }
    /** 设置body是否能被旋转 */
    void setRotationEnable(bool enable);
    
    /** 获取body是否会被物理世界重力影响 */
    inline bool isGravityEnabled() const { return _gravityEnabled; }
    /** 设置body是否会被物理世界重力影响 */
    void setGravityEnable(bool enable);
    
    /** 获取body的tag */
    inline int getTag() const { return _tag; }
    /** 设置body的tag */
    inline void setTag(int tag) { _tag = tag; }
    
    /** 将世界坐标转化成本地坐标 */
    Vec2 world2Local(const Vec2& point);
    /** 将本地坐标转化为世界坐标 */
    Vec2 local2World(const Vec2& point);
    
protected:
    
    bool init();
    
    virtual void setPosition(Vec2 position);
    virtual void setRotation(float rotation);
    
    void update(float delta);
    
    void removeJoint(PhysicsJoint* joint);
    inline void updateDamping() { _isDamping = _linearDamping != 0.0f ||  _angularDamping != 0.0f; }
    void updateMass(float oldMass, float newMass);
    
protected:
    PhysicsBody();
    virtual ~PhysicsBody();
    
protected:
    Node* _node;
    std::vector<PhysicsJoint*> _joints;
    Vector<PhysicsShape*> _shapes;
    PhysicsWorld* _world;
    PhysicsBodyInfo* _info;
    bool _dynamic;
    bool _enabled;
    bool _rotationEnabled;
    bool _gravityEnabled;
    bool _massDefault;
    bool _momentDefault;
    float _mass;
    float _area;
    float _density;
    float _moment;
    bool _isDamping;
    float _linearDamping;
    float _angularDamping;
    int _tag;
    
    int _categoryBitmask;
    int _collisionBitmask;
    int _contactTestBitmask;
    int _group;
    
    bool _positionResetTag;     /// 当body调用Node::setPosition()函数的时候避免重置body的坐标
    bool _rotationResetTag;     /// 当body调用Node::setRotation()函数的时候避免重置body的旋转角度
    Vec2 _positionOffset;
    float _rotationOffset;
    
    friend class PhysicsWorld;
    friend class PhysicsShape;
    friend class PhysicsJoint;
    friend class Node;
    friend class Layer;
    friend class ProtectedNode;
};

NS_CC_END

#endif // CC_USE_PHYSICS
#endif // __CCPHYSICS_BODY_H__
