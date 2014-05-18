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

#ifndef __CCPHYSICS_SHAPE_H__
#define __CCPHYSICS_SHAPE_H__

#include "base/ccConfig.h"
#if CC_USE_PHYSICS

#include "base/CCRef.h"
#include "math/CCGeometry.h"

NS_CC_BEGIN

class PhysicsShapeInfo;
class PhysicsBody;
class PhysicsBodyInfo;


typedef struct PhysicsMaterial
{
    float density;          ///< 对象的密度
    float restitution;      ///< 物理body的恢复系数
    float friction;         ///< body的表面粗糙程度
    
    PhysicsMaterial()
    : density(0.0f)
    , restitution(0.0f)
    , friction(0.0f)
    {}
    
    PhysicsMaterial(float aDensity, float aRestitution, float aFriction)
    : density(aDensity)
    , restitution(aRestitution)
    , friction(aFriction)
    {}
}PhysicsMaterial;

const PhysicsMaterial PHYSICSSHAPE_MATERIAL_DEFAULT(0.0f, 0.5f, 0.5f);

/**
 * @brief 给body的一个形状。你不会直接创建PhysicsWorld 对象，与之代替的，你可以查看PhysicsBody去了解怎么创建它。
 */
class PhysicsShape : public Ref
{
public:
    enum class Type
    {
        UNKNOWN,
        CIRCLE,
        BOX,
        POLYGEN,
        EDGESEGMENT,
        EDGEBOX,
        EDGEPOLYGEN,
        EDGECHAIN,
    };
    
public:
    /** 获取这个形状连接到的body */
    inline PhysicsBody* getBody() const { return _body; }
    /** 返回形状的类型 */
    inline Type getType() const { return _type; }
    /** 返回形状所占的面积 */
    inline float getArea() const { return _area; }
    /** 获取力矩 */
    inline float getMoment() const { return _moment; }
    /** 设置力矩，它会更改这个形状关联的body的力矩 */
    void setMoment(float moment);
    inline void setTag(int tag) { _tag = tag; }
    inline int getTag() const { return _tag; }
    
    /** 获取质量 */
    inline float getMass() const { return _mass; }
    /** 设置质量，它会改变这个形状关联的body的质量 */
    void setMass(float mass);
    inline float getDensity() const { return _material.density; }
    void setDensity(float density);
    inline float getRestitution() const { return _material.restitution; }
    void setRestitution(float restitution);
    inline float getFriction() const { return _material.friction; }
    void setFriction(float friction);
    const PhysicsMaterial& getMaterial() const { return _material; }
    void setMaterial(const PhysicsMaterial& material);
    
    /** 计算默认的力矩值 */
    virtual float calculateDefaultMoment() { return 0.0f; }
    /** 获取偏移值 */
    virtual Vec2 getOffset() { return Vec2::ZERO; }
    /** 获取这个形状的中心 */
    virtual Vec2 getCenter() { return getOffset(); }
    /** 检测某个点是否在这个形状里 */
    bool containsPoint(const Vec2& point) const;
    
    /** 把那个点移动到中心点 */
    static void recenterPoints(Vec2* points, int count, const Vec2& center = Vec2::ZERO);
    /** 获取多边形的中心 */
    static Vec2 getPolyonCenter(const Vec2* points, int count);
    
    /**
     * 定义物理body属于哪种分类的一个mask
     * 在一个场景内的每一个物理body可以被分配到最多32个分类,每个对应1个bit在bit mask中。你定义你游戏中使用的mask值。和属性collisionBitMask、contactTestBitMask互相协调，你定义哪种物理body互相之间的交互和什么时候你的游戏会被这些交互通知。
     * 默认值是0xFFFFFFFF (所有位被设成1)。
     */
    inline void setCategoryBitmask(int bitmask) { _categoryBitmask = bitmask; }
    inline int getCategoryBitmask() const { return _categoryBitmask; }
    /**
     * 定义哪种分类的body导致和这个物理body发生交叉通知的一个mask
     * 当两个body共享同一片控件，每个body的分类mask会跟对方的contact mask通过“逻辑和”（即&&）操作。如果任意一个的结果是一个非0值，一个PhysicsContact的对象会被生成和传送到物理世界的委托。为了最好的表现，仅设置在contact mask里设置 你感兴趣的交互 所对应的bit。
     * 默认值是0x00000000 (所有位被设成0)。
     */
    inline void setContactTestBitmask(int bitmask) { _contactTestBitmask = bitmask; }
    inline int getContactTestBitmask() const { return _contactTestBitmask; }
    /**
     * 定义物理body可以跟那些分类的物理body发生冲突的一个mask
     * 当两个物理body彼此碰撞时，一个冲突可能会发生。这个body的冲突mask 会跟另一个body的分类mask 通过逻辑和的操作比较。如果结果是个非0值，那么这个body会被这个冲突影响。每个body独立的选择它是否会被另一个body影响。比如说ini可能会使用这个mask 去避免会发生对一个body的速率发生微小的变化的冲突计算。
     * 默认值是0xFFFFFFFF (所有位被设成1)。
     */
    inline void setCollisionBitmask(int bitmask) { _collisionBitmask = bitmask; }
    inline int getCollisionBitmask() const { return _collisionBitmask; }
    
    void setGroup(int group);
    inline int getGroup() { return _group; }
    
protected:
    bool init(Type type);
    
    /**
     * @brief PhysicsShape是PhysicsBody's 友元类，但它的友元类不是。所以这个方法是让子类们能够从PhysicsBody获取信息。
     */
    PhysicsBodyInfo* bodyInfo() const;
    
    void setBody(PhysicsBody* body);
    
    /** 计算这个形状所占的面积 */
    virtual float calculateArea() { return 0.0f; }
    
protected:
    PhysicsShape();
    virtual ~PhysicsShape() = 0;
    
protected:
    PhysicsBody* _body;
    PhysicsShapeInfo* _info;
    Type _type;
    float _area;
    float _mass;
    float _moment;
    PhysicsMaterial _material;
    int _tag;
    int    _categoryBitmask;
    int    _collisionBitmask;
    int    _contactTestBitmask;
    int    _group;
    
    friend class PhysicsWorld;
    friend class PhysicsBody;
    friend class PhysicsJoint;
    friend class PhysicsDebugDraw;
};

/** 圆形形状 */
class PhysicsShapeCircle : public PhysicsShape
{
public:
    static PhysicsShapeCircle* create(float radius, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2(0, 0));
    static float calculateArea(float radius);
    static float calculateMoment(float mass, float radius, const Vec2& offset = Vec2::ZERO);
    
    virtual float calculateDefaultMoment() override;
    
    float getRadius() const;
    virtual Vec2 getOffset() override;
protected:
    bool init(float radius, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    virtual float calculateArea() override;
    
protected:
    PhysicsShapeCircle();
    virtual ~PhysicsShapeCircle();
};

/** Box形状 */
class PhysicsShapeBox : public PhysicsShape
{
public:
    static PhysicsShapeBox* create(const Size& size, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    static float calculateArea(const Size& size);
    static float calculateMoment(float mass, const Size& size, const Vec2& offset = Vec2::ZERO);
    
    virtual float calculateDefaultMoment() override;
    
    void getPoints(Vec2* outPoints) const;
    int getPointsCount() const { return 4; }
    Size getSize() const;
    virtual Vec2 getOffset() override { return _offset; }
    
protected:
    bool init(const Size& size, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    virtual float calculateArea() override;
    
protected:
    PhysicsShapeBox();
    virtual ~PhysicsShapeBox();
    
protected:
    Vec2 _offset;
};

/** 多边形形状 */
class PhysicsShapePolygon : public PhysicsShape
{
public:
    static PhysicsShapePolygon* create(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    static float calculateArea(const Vec2* points, int count);
    static float calculateMoment(float mass, const Vec2* points, int count, const Vec2& offset = Vec2::ZERO);
    
    float calculateDefaultMoment() override;
    
    Vec2 getPoint(int i) const;
    void getPoints(Vec2* outPoints) const;
    int getPointsCount() const;
    virtual Vec2 getCenter() override;
protected:
    bool init(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    float calculateArea() override;
    
protected:
    PhysicsShapePolygon();
    virtual ~PhysicsShapePolygon();
    
protected:
    Vec2 _center;
};

/** 线段形状 */
class PhysicsShapeEdgeSegment : public PhysicsShape
{
public:
    static PhysicsShapeEdgeSegment* create(const Vec2& a, const Vec2& b, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
    Vec2 getPointA() const;
    Vec2 getPointB() const;
    virtual Vec2 getCenter() override;
    
protected:
    bool init(const Vec2& a, const Vec2& b, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
protected:
    PhysicsShapeEdgeSegment();
    virtual ~PhysicsShapeEdgeSegment();
    
protected:
    Vec2 _center;
    
    friend class PhysicsBody;
};

/** 获取一个边缘box形状 */
class PhysicsShapeEdgeBox : public PhysicsShape
{
public:
    static PhysicsShapeEdgeBox* create(const Size& size, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 0, const Vec2& offset = Vec2::ZERO);
    virtual Vec2 getOffset() override { return _offset; }
    void getPoints(Vec2* outPoints) const;
    int getPointsCount() const { return 4; }
    
protected:
    bool init(const Size& size, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1, const Vec2& offset = Vec2::ZERO);
    
protected:
    PhysicsShapeEdgeBox();
    virtual ~PhysicsShapeEdgeBox();
    
protected:
    Vec2 _offset;
    
    friend class PhysicsBody;
};

/** 边缘多边形的形状 */
class PhysicsShapeEdgePolygon : public PhysicsShape
{
public:
    static PhysicsShapeEdgePolygon* create(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    virtual Vec2 getCenter() override;
    void getPoints(Vec2* outPoints) const;
    int getPointsCount() const;
    
protected:
    bool init(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
protected:
    PhysicsShapeEdgePolygon();
    virtual ~PhysicsShapeEdgePolygon();
    
    friend class PhysicsBody;
    
protected:
    Vec2 _center;
};

/** 链形状 */
class PhysicsShapeEdgeChain : public PhysicsShape
{
public:
    static PhysicsShapeEdgeChain* create(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    virtual Vec2 getCenter() override;
    void getPoints(Vec2* outPoints) const;
    int getPointsCount() const;
    
protected:
    bool init(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
protected:
    PhysicsShapeEdgeChain();
    virtual ~PhysicsShapeEdgeChain();
    
protected:
    Vec2 _center;
    
    friend class PhysicsBody;
};

NS_CC_END

#endif // CC_USE_PHYSICS
#endif // __CCPHYSICS_FIXTURE_H__
