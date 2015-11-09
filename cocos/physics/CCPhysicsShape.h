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

struct cpShape;

NS_CC_BEGIN

class PhysicsBody;

typedef struct CC_DLL PhysicsMaterial
{
    float density;          ///< The density of the object.
    float restitution;      ///< The bounciness of the physics body.
    float friction;         ///< The roughness of the surface of a shape.
    
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

const PhysicsMaterial PHYSICSSHAPE_MATERIAL_DEFAULT;

/**
 *  @addtogroup physics
 *  @{
 *  @addtogroup physics_2d
 *  @{

 */

/**
 * @brief @~english A shape for body, you can view PhysicsBody to see how to create it.
 * @~chinese 一个刚体的形状，你可以查看PhysicsBody看如何创建它。
 */
class CC_DLL PhysicsShape : public Ref
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
    /** @~english
     * Get the body that this shape attaches.
     *
     * @~chinese 
     * 获取拥有这个形状的刚体。
     * 
     * @return @~english A PhysicsBody object pointer.
     * @~chinese PhysicsBody对象指针。
     */
    inline PhysicsBody* getBody() const { return _body; }
    
    /** @~english
     * Return this shape's type.
     *
     * @~chinese 
     * 返回这个形状的类型。
     * 
     * @return @~english A Type object.
     * @~chinese 一个类型对象。
     */
    inline Type getType() const { return _type; }

    /**@~english
     * Return this shape's area.
     *
     * @~chinese 
     * 返回这个形状的面积。
     * 
     * @return @~english A float number.
     * @~chinese 面积的浮点值。
     */
    inline float getArea() const { return _area; }
    
    /**@~english
     * Get this shape's moment.
     *
     * @~chinese 
     * 获取这个形状的力矩。
     * 
     * @return @~english A float number.
     * @~chinese 一个浮点数。
     */
    inline float getMoment() const { return _moment; }
    
    /**@~english
     * Set this shape's moment.
     * It will change the body's moment this shape attaches.
     *
     * @~chinese 
     * 设置这个形状的力矩。
     * 它会改变这个形状所属刚体的力矩。
     * 
     * @param moment @~english A float number.
     * @~chinese 一个浮点数。
     */
    void setMoment(float moment);
    
    /**@~english
     * Set this shape's tag.
     * @~chinese 
     * 设置这个形状的标记。
     * 
     * @param tag @~english An interger number that identifies a shape object.
     * @~chinese 用来标识形状的整形值。
     */
    inline void setTag(int tag) { _tag = tag; }
    
    /**@~english
     * Get this shape's tag.
     * @~chinese 
     * 获取这个形状的标记。
     * 
     * @return @~english An interger number.
     * @~chinese 一个整形数字。
     */
    inline int getTag() const { return _tag; }
    
    /**@~english
     * Get the mass of this shape.
     * @~chinese 
     * 获取这个形状的质量。
     * 
     * @return @~english A float number.
     * @~chinese 一个浮点数。
     */
    inline float getMass() const { return _mass; }
    
    /**@~english
     * Set this shape's mass.
     * It will change the body's mass this shape attaches.
     *
     * @~chinese 
     * 设置这个形状的质量。
     * 它会改变这个形状所属的形状的质量。
     * 
     * @param mass @~english A float number.
     * @~chinese 一个浮点数。
     */
    void setMass(float mass);
    
    /**@~english
     * Get this shape's density.
     * @~chinese 
     * 获取这个形状的密度。
     * 
     * @return @~english A float number.
     * @~chinese 一个浮点数。
     */
    inline float getDensity() const { return _material.density; }
    
    /**@~english
     * Set this shape's density.
     * It will change the body's mass this shape attaches.
     *
     * @~chinese 
     * 设置这个形状的密度。
     * 它会改变这个形状所属刚体的质量。
     * 
     * @param density @~english A float number.
     * @~chinese 一个浮点数。
     */
    void setDensity(float density);
    
    /**@~english
     * Get this shape's restitution.
     * @~chinese 
     * 获取这个形状的恢复系数。
     * 
     * @return @~english A float number.
     * @~chinese 一个浮点数。
     */
    inline float getRestitution() const { return _material.restitution; }
    
    /**@~english
     * Set this shape's restitution.
     * It will change the shape's elasticity.
     * @~chinese 
     * 设置这个形状的恢复系数。
     * 它将改变形状的弹性。
     * 
     * @param restitution @~english A float number.
     * @~chinese 一个浮点数。
     */
    void setRestitution(float restitution);
    
    /**@~english
     * Get this shape's friction.
     * @~chinese 
     * 获取这个形状的摩擦系数。
     * 
     * @return @~english A float number.
     * @~chinese 一个浮点数。
     */
    inline float getFriction() const { return _material.friction; }
    
    /**@~english
     * Set this shape's friction.
     * It will change the shape's friction.
     *
     * @~chinese 
     * 这个形状的摩擦系数。
     * 
     * @param friction @~english A float number.
     * @~chinese 一个浮点数。
     */
    void setFriction(float friction);
    
    /**@~english
     * Get this shape's PhysicsMaterial object.
     * @~chinese 
     * 获取这个形状的材料（PhysicsMaterial）对象。
     * 
     * @return @~english A PhysicsMaterial object reference.
     * @~chinese PhysicsMaterial对象引用。
     */
    const PhysicsMaterial& getMaterial() const { return _material; }
    
    /**@~english
     * Set this shape's material.
     * It will change the shape's mass, elasticity and friction.
     * @~chinese 
     * 设置这个形状的材料（PhysicsMaterial）对象。
     * 它将改变形状的质量，弹性和摩擦系数。
     * 
     * @param material @~english A PhysicsMaterial object.
     * @~chinese 材料（PhysicsMaterial）对象。
     */
    void setMaterial(const PhysicsMaterial& material);
    inline bool isSensor() const { return _sensor; }
    void setSensor(bool sensor);
    
    /** @~english
     * Calculate the default moment value.
     * This function should be overridden in inherit classes.
     * @~chinese 
     * 计算默认的力矩。
     * 这个函数应该在继承类中被覆盖。
     * @return @~english A float number, equals 0.0.
     * @~chinese 浮点数，等于0.0。
     */
    virtual float calculateDefaultMoment() { return 0.0f; }
    
    /**@~english
     * Get this shape's position offset.
     * This function should be overridden in inherit classes.
     * @~chinese 
     * 得到这个形状的位置偏移量。
     * 这个函数应该在继承类中被覆盖。
     * @return @~english A Vec2 object.
     * @~chinese 一个Vec2对象。
     */
    virtual Vec2 getOffset() { return Vec2::ZERO; }
    
    /**@~english
     * Get this shape's center position.
     * This function should be overridden in inherit classes.
     * @~chinese 
     * 这个形状的中心位置。
     * 这个函数应该在继承类中被覆盖。
     * @return @~english A Vec2 object.
     * @~chinese Vec2对象。
     */
    virtual Vec2 getCenter() { return getOffset(); }
    
    /** @~english
     * Test point is inside this shape or not.
     * @~chinese 
     * 测试点是否在这个形状中。
     * 
     * @param point @~english A Vec2 object.
     * @~chinese 一个点对象。
     * @return @~english A bool object.
     * @~chinese 用来指示结果的布尔值。
     */
    bool containsPoint(const Vec2& point) const;
    
    /** @~english
     * Move the points to the center.
     * @~chinese 
     * 移动点到中心。
     * 
     * @param points @~english A Vec2 object pointer.
     * @~chinese 一个点对象。
     * @param count @~english An interger number.
     * @~chinese 一个整型值。
     * @param center @~english A Vec2 object, default value is Vec2(0,0).
     * @~chinese 一个Vec2对象，默认值是Vec2(0,0)。
     */
    static void recenterPoints(Vec2* points, int count, const Vec2& center = Vec2::ZERO);

    /**@~english
     * Get center of the polyon points.
     * @~chinese 
     * 得到多边形的中心。
     * 
     * @param points @~english A Vec2 object pointer.
     * @~chinese 一个点对象指针。
     * @param count @~english An interger number.
     * @~chinese 一个整型数字。
     * @return @~english A Vec2 object.
     * @~chinese 中心点对象。
     */
    static Vec2 getPolyonCenter(const Vec2* points, int count);
    
    /**@~english
     * Set a mask that defines which categories this physics shape belongs to.
     *
     * Every physics shape in a scene can be assigned to up to 32 different categories, each corresponding to a bit in the bit mask. You define the mask values used in your game. 
     * In conjunction with the collisionBitMask and contactTestBitMask properties, you define which physics bodies interact with each other and when your game is notified of these interactions.
     * @~chinese 
     * 为物理形状设置一个类别字节掩码以标识它属于哪个类别
     * 
     * 场景中的每个物理形状可以分配给多达32个不同的类别，每一个对应于字节掩码的一位。在你的游戏定义并使用掩码值。
     * 结合碰撞掩码（collisionBitMask）和接触掩码（contactTestBitMask）属性，你定义哪些物理形状彼此交互以及何时你可以得到交互的通知。
     * @param bitmask @~english An interger number, the default value is 0xFFFFFFFF (all bits set).
     * @~chinese 字节掩码是一个整型值，默认值是0xffffffff。
     */
    inline void setCategoryBitmask(int bitmask) { _categoryBitmask = bitmask; }
    
    /**@~english
     * Get a mask that defines which categories this physics shape belongs to.
     *
     * @~chinese 
     * 得到用于标识物理形状属于哪个类别的类别字节掩码。
     * 
     * @return @~english An interger number.
     * @~chinese 字节掩码是一个整型值。
     */
    inline int getCategoryBitmask() const { return _categoryBitmask; }
    
    
    /**@~english
     * A mask that defines which categories of bodies cause intersection notifications with this physics shape.
     *
     * When two bodies share the same space, each shape’s category mask is tested against the other shape’s contact mask by performing a logical AND operation. If either comparison results in a non-zero value, an PhysicsContact object is created and passed to the physics world’s delegate. For best performance, only set bits in the contacts mask for interactions you are interested in.
     * @~chinese 
     * 设置接触字节掩码，用于定义哪些类别的形状与这个形状接触时会收到通知。
     * 
     * 当两个形状在相同的物理空间中，一个形状的分组掩码会与另一个的分组掩码做逻辑与操作，如果结果非0，一个PhysicsContact接触对象会被创建并传递給物理世界的代理。
     * 为了优化性能，可以只为那些你需要处理接触的形状之间设置不同的分组掩码。
     * @param bitmask @~english An interger number, the default value is 0x00000000 (all bits cleared).
     * @~chinese 字节掩码是一个整型值，默认值是0x00000000(所有位清除)。
     */
    inline void setContactTestBitmask(int bitmask) { _contactTestBitmask = bitmask; }
    
    /**@~english
     * Get a mask that defines which categories of bodies cause intersection notifications with this physics shape.
     *
     * @~chinese 
     * 得到接触字节掩码，用于定义哪些类别的形状与这个形状接触时会收到通知。
     * 
     * @return @~english An interger number.
     * @~chinese 字节掩码是一个整型值。
     */
    inline int getContactTestBitmask() const { return _contactTestBitmask; }

    /**@~english
     * A mask that defines which categories of physics bodies can collide with this physics shape.
     *
     * When two physics bodies contact each other, a collision may occur. This shape’s collision mask is compared to the other shape’s category mask by performing a logical AND operation. If the result is a non-zero value, then this shape is affected by the collision. Each shape independently chooses whether it wants to be affected by the other shape. For example, you might use this to avoid collision calculations that would make negligible changes to a shape’s velocity.
     * @~chinese 
     * 设置形状的碰撞字节掩码，用于定义哪些类别的形状会与这个形状发生碰撞。
     * 
     * 当两个形状在同一个空间中接触时，一个需要处理的碰撞就有可能产生，一个形状的碰撞掩码会与另一个的碰撞掩码做逻辑与操作，如果结果非0，那么形状就会受碰撞所影响。形状分别选择是否对碰撞做出响应并影响自己的运动。打个比方，你可以避免碰撞计算所引起的对形状速度的微小影响。
     * @param bitmask @~english An interger number, the default value is 0xFFFFFFFF (all bits set).
     * @~chinese 字节掩码是一个整型值，默认值是0xffffffff(开启所有位)。
     */
    inline void setCollisionBitmask(int bitmask) { _collisionBitmask = bitmask; }
    
    /**@~english
     * Get a mask that defines which categories of physics bodies can collide with this physics shape.
     *
     * @~chinese 
     * 得到形状的碰撞字节掩码，用于定义哪些类别的形状会与这个形状发生碰撞。
     * 
     * @return @~english An interger number.
     * @~chinese 字节掩码是一个整型值。
     */
    inline int getCollisionBitmask() const { return _collisionBitmask; }
    
    /**@~english
     * Set the group of shape.
     *
     * Collision groups let you specify an integral group index. You can have all shapes with the same group index always collide (positive index) or never collide (negative index).
     * @~chinese 
     * 设置形状的碰撞组。
     * 
     * 碰撞组是一个整型分组索引。你可以用同一组指数都装置总是碰撞(正数)或从不碰撞(负数)。
     * @param group @~english An interger number, it have high priority than bit masks.
     * @~chinese 整型值，它比字节掩码有更高的优先级。
     */
    void setGroup(int group);
    
    /**@~english
     * Get the group of shape.
     *
     * @~chinese 
     * 获取形状的碰撞组。
     * 
     * @return @~english An interger number.
     * @~chinese 整型值。
     */
    inline int getGroup() { return _group; }
    
protected:
    void setBody(PhysicsBody* body);
    
    /** @~english calculate the area of this shape  @~chinese 计算形状的面积*/
    virtual float calculateArea() { return 0.0f; }
    
    virtual void setScale(float scaleX, float scaleY);
    virtual void updateScale();
    void addShape(cpShape* shape);
    
protected:
    PhysicsShape();
    virtual ~PhysicsShape() = 0;
    
protected:
    PhysicsBody* _body;
    std::vector<cpShape*> _cpShapes;

    Type _type;
    float _area;
    float _mass;
    float _moment;
    bool _sensor;
    float _scaleX;
    float _scaleY;
    float _newScaleX;
    float _newScaleY;
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

/** @~english A circle shape.  @~chinese 一个圆形形状。*/
class CC_DLL PhysicsShapeCircle : public PhysicsShape
{
public:
    /**@~english
     * Creates a PhysicsShapeCircle with specified value.
     *
     * @~chinese 
     * 用指定参数创建一个圆形形状PhysicsShapeCircle对象。
     * 
     * @param   radius @~english A float number, it is the circle's radius.
     * @~chinese 圆的半径，它是浮点数。
     * @param   material @~english A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @~chinese PhysicsMaterial材质对象，默认值是PHYSICSSHAPE_MATERIAL_DEFAULT。
     * @param   offset @~english A Vec2 object, it is the offset from the body’s center of gravity in body local coordinates.
     * @~chinese 形状的位置，形状在刚体局部坐标中相对于重心的偏移量。
     * @return @~english  An autoreleased PhysicsShapeCircle object pointer.
     * @~chinese 一个自释放的PhysicsShapeCircle对象指针。
     */
    static PhysicsShapeCircle* create(float radius, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2(0, 0));
    
    /**@~english
     * Calculate the area of a circle with specified radius.
     *
     * @~chinese 
     * 使用指定的半径计算圆的面积。
     * 
     * @param radius @~english A float number
     * @~chinese 半径，浮点数
     * @return @~english A float number
     * @~chinese 面积，浮点数
     */
    static float calculateArea(float radius);
    
    /**@~english
     * Calculate the moment of a circle with specified value.
     *
     * @~chinese 
     * 用指定值计算一个圆形形状的力矩。
     * 
     * @param mass @~english A float number
     * @~chinese 质量，浮点数
     * @param radius @~english A float number
     * @~chinese 半径，浮点数
     * @param offset @~english A Vec2 object, it is the offset from the body’s center of gravity in body local coordinates.
     * @~chinese 形状的位置，形状在刚体局部坐标中相对于重心的偏移量。
     * @return @~english A float number
     * @~chinese 力矩，浮点数
     */
    static float calculateMoment(float mass, float radius, const Vec2& offset = Vec2::ZERO);
    
    /**@~english
     * Calculate the moment for a circle.
     * @~chinese 
     * 计算这个圆形形状的力矩。
     * 
     * @return @~english A float number.
     * @~chinese 力矩，浮点数。
     */
    virtual float calculateDefaultMoment() override;
    
    /**@~english
     * Get the circle's radius.
     * @~chinese 
     * 获取圆形的半径。
     * 
     * @return @~english A float number.
     * @~chinese 半径，浮点数。
     */
    float getRadius() const;
    
    /**@~english
     * Get this circle's position offset.
     *
     * @~chinese 
     * 得到这个圆形的位置偏移量。
     * 
     * @return @~english A Vec2 object.
     * @~chinese 位置偏移量。
     */
    virtual Vec2 getOffset() override;
    
protected:
    bool init(float radius, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    virtual float calculateArea() override;
    virtual void updateScale() override;
    
protected:
    PhysicsShapeCircle();
    virtual ~PhysicsShapeCircle();
};

/** @~english A polygon shape.  @~chinese 一个多边形形状。*/
class CC_DLL PhysicsShapePolygon : public PhysicsShape
{
public:
    /**@~english
     * Creates a PhysicsShapePolygon with specified value.
     *
     * @~chinese 
     * 用指定参数创建一个多边形形状PhysicsShapePolygon对象。
     * 
     * @param   points @~english A Vec2 object pointer, it is an array of Vec2.
     * @~chinese 多边形顶点数组。
     * @param   count @~english An interger number, contains the count of the points array.
     * @~chinese 顶点数量。
     * @param   material @~english A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @~chinese PhysicsMaterial物理材质对象，默认值是PHYSICSSHAPE_MATERIAL_DEFAULT。
     * @param   offset @~english A Vec2 object, it is the offset from the body’s center of gravity in body local coordinates.
     * @~chinese 形状在刚体局部坐标中相对于重心的偏移量。
     * @return @~english  An autoreleased PhysicsShapePolygon object pointer.
     * @~chinese 一个自释放的PhysicsShapePolygon对象指针。
     */
    static PhysicsShapePolygon* create(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    
    /**@~english
     * Calculate the area of a polygon with specified value.
     *
     * @~chinese 
     * 用指定参数计算一个多边形的面积。
     * 
     * @param   points @~english A Vec2 object pointer, it is an array of Vec2.
     * @~chinese 多边形顶点数组。
     * @param   count @~english An interger number, contains the count of the points array.
     * @~chinese 顶点数量。
     * @return @~english A float number.
     * @~chinese 多边形面积。
     */
    static float calculateArea(const Vec2* points, int count);
    
    /**@~english
     * Calculate the moment of a polygon with specified value.
     * @~chinese 
     * 用指定参数计算一个多边形的力矩。
     * 
     * @param mass @~english A float number
     * @~chinese 质量
     * @param   points @~english A Vec2 object pointer, it is an array of Vec2.
     * @~chinese 多边形顶点数组。
     * @param   count @~english An interger number, contains the count of the points array.
     * @~chinese 顶点数量。
     * @param offset @~english A Vec2 object, it is the offset from the body’s center of gravity in body local coordinates.
     * @~chinese 形状在刚体局部坐标中相对于重心的偏移量。
     * @return @~english A float number
     * @~chinese 力矩
     */
    static float calculateMoment(float mass, const Vec2* points, int count, const Vec2& offset = Vec2::ZERO);
    
    /**@~english
     * Calculate the moment for a polygon.
     *
     * @~chinese 
     * 计算多边形的力矩。
     * 
     * @return @~english A float number.
     * @~chinese 力矩。
     */
    float calculateDefaultMoment() override;
    
    /**@~english
     * Get a point of this polygon's points array.
     *
     * @~chinese 
     * 按数组中的位置获取这个多边形的一个顶点。
     * 
     * @param i @~english A index of this polygon's points array.
     * @~chinese 数组中的位置。
     * @return @~english A point value.
     * @~chinese 一个点。
     */
    Vec2 getPoint(int i) const;
    
    /**@~english
     * Get this polygon's points array.
     *
     * @~chinese 
     * 获取这个多边形的顶点数组。
     * 
     * @param outPoints @~english A Vec2 array pointer.
     * @~chinese 多边形的顶点数组。
     */
    void getPoints(Vec2* outPoints) const;
    
    /**@~english
     * Get this polygon's points array count.
     *
     * @~chinese 
     * 得到这个多边形的顶点数量。
     * 
     * @return @~english An interger number.
     * @~chinese 一个interger的数字。
     */
    int getPointsCount() const;
    
    /**@~english
     * Get this polygon's center position.
     *
     * @~chinese 
     * 得到这个多边形的中心位置。
     * 
     * @return @~english A Vec2 object.
     * @~chinese 中心位置。
     */
    virtual Vec2 getCenter() override;
protected:
    bool init(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    float calculateArea() override;
    virtual void updateScale() override;
    
protected:
    PhysicsShapePolygon();
    virtual ~PhysicsShapePolygon();
};

/** @~english A box shape.  @~chinese 一个矩形形状。*/
class CC_DLL PhysicsShapeBox : public PhysicsShapePolygon
{
public:
    /**@~english
     * Creates a PhysicsShapeBox with specified value.
     *
     * @~chinese 
     * 创建一个矩形形状PhysicsShapeBox对象。
     * 
     * @param   size @~english Size contains this box's width and height.
     * @~chinese 大小，包含这个矩形的宽度和高度。
     * @param   material @~english A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @~chinese 物理材质PhysicsMaterial对象，默认值是PHYSICSSHAPE_MATERIAL_DEFAULT。
     * @param   offset @~english A Vec2 object, it is the offset from the body’s center of gravity in body local coordinates.
     * @~chinese 形状在刚体局部坐标中相对于重心的偏移量。
     * @return @~english  An autoreleased PhysicsShapeBox object pointer.
     * @~chinese 一个自释放的PhysicsShapeBox对象指针。
     */
    static PhysicsShapeBox* create(const Size& size, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    
    /**@~english
     * Get this box's width and height.
     *
     * @~chinese 
     * 获取这个箱子的宽度和高度。
     * 
     * @return @~english An Size object.
     * @~chinese 一个尺寸对象。
     */
    Size getSize() const;
    
    /**@~english
     * Get this box's position offset.
     *
     * @~chinese 
     * 获取这个箱子的位置偏移量。
     * 
     * @return @~english A Vec2 object.
     * @~chinese 位置偏移量。
     */
    virtual Vec2 getOffset() override { return getCenter(); }
    
protected:
    bool init(const Size& size, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    
protected:
    PhysicsShapeBox();
    virtual ~PhysicsShapeBox();
};

/** @~english A segment shape.  @~chinese 一段线段形状。*/
class CC_DLL PhysicsShapeEdgeSegment : public PhysicsShape
{
public:
    /**@~english
     * Creates a PhysicsShapeEdgeSegment with specified value.
     *
     * @~chinese 
     * 创建一个线段形状PhysicsShapeEdgeSegment对象。
     * 
     * @param   a @~english It's the edge's begin position.
     * @~chinese 线段的开始位置。
     * @param   b @~english It's the edge's end position.
     * @~chinese 线段的结束位置。
     * @param   material @~english A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @~chinese 物理材质PhysicsMaterial对象，默认值是PHYSICSSHAPE_MATERIAL_DEFAULT。
     * @param   border @~english It's a edge's border width.
     * @~chinese 线段宽度。
     * @return @~english  An autoreleased PhysicsShapeEdgeSegment object pointer.
     * @~chinese 一个自释放的PhysicsShapeEdgeSegment对象指针。
     */
    static PhysicsShapeEdgeSegment* create(const Vec2& a, const Vec2& b, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
    /**@~english
     * Get this edge's begin position.
     *
     * @~chinese 
     * 得到这个线段的开始位置。
     * 
     * @return @~english A Vec2 object.
     * @~chinese 开始位置。
     */
    Vec2 getPointA() const;
    
    /**@~english
     * Get this edge's end position.
     *
     * @~chinese 
     * 得到这个线段的结束位置。
     * 
     * @return @~english A Vec2 object.
     * @~chinese 结束位置。
     */
    Vec2 getPointB() const;
    
    /**@~english
     * Get this edge's center position.
     *
     * @~chinese 
     * 得到这个线段的中心位置。
     * 
     * @return @~english A Vec2 object.
     * @~chinese 中心位置。
     */
    virtual Vec2 getCenter() override;
    
protected:
    bool init(const Vec2& a, const Vec2& b, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    virtual void updateScale() override;
    
protected:
    PhysicsShapeEdgeSegment();
    virtual ~PhysicsShapeEdgeSegment();
    
    friend class PhysicsBody;
};

/** @~english An edge polygon shape.  @~chinese 一个空心多边形形状。*/
class CC_DLL PhysicsShapeEdgePolygon : public PhysicsShape
{
public:
    /**@~english
     * Creates a PhysicsShapeEdgePolygon with specified value.
     *
     * @~chinese 
     * 创建一个空心多边形形状PhysicsShapeEdgePolygon对象。
     * 
     * @param   points @~english A Vec2 object pointer, it contains an array of points.
     * @~chinese 多边形顶点数组。
     * @param   count @~english An interger number, contains the count of the points array.
     * @~chinese 多边形顶点数量。
     * @param   material @~english A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @~chinese 物理材质PhysicsMaterial对象，默认值是PHYSICSSHAPE_MATERIAL_DEFAULT。
     * @param   border @~english It's a edge's border width.
     * @~chinese 这是多边形的边框宽度。
     * @return @~english  An autoreleased PhysicsShapeEdgePolygon object pointer.
     * @~chinese 一个自释放的PhysicsShapeEdgePolygon对象指针。
     */
    static PhysicsShapeEdgePolygon* create(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
    /**@~english
     * Get this polygon's center position.
     *
     * @~chinese 
     * 得到这个多边形的中心位置。
     * 
     * @return @~english A Vec2 object.
     * @~chinese 中心位置。
     */
    virtual Vec2 getCenter() override;
    
    /**@~english
     * Get this polygon's points array.
     *
     * @~chinese 
     * 得到这个多边形的顶点数组。
     * 
     * @param outPoints @~english A Vec2 array pointer.
     * @~chinese 顶点数组。
     */
    void getPoints(Vec2* outPoints) const;
    
    /**@~english
     * Get this polygon's points array count.
     *
     * @~chinese 
     * 得到这个多边形的顶点数量。
     * 
     * @return @~english An interger number.
     * @~chinese 顶点数量。
     */
    int getPointsCount() const;
    
protected:
    bool init(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    virtual void updateScale() override;
    
protected:
    PhysicsShapeEdgePolygon();
    virtual ~PhysicsShapeEdgePolygon();
    
    friend class PhysicsBody;
};

/** @~english An edge box shape.  @~chinese 矩形形状。*/
class CC_DLL PhysicsShapeEdgeBox : public PhysicsShapeEdgePolygon
{
public:
    /**@~english
     * Creates a PhysicsShapeEdgeBox with specified value.
     *
     * @~chinese 
     * 创建一个矩形形状PhysicsShapeEdgeBox对象。
     * 
     * @param   size @~english Size contains this box's width and height.
     * @~chinese 大小，包含这个矩形的宽度和高度。
     * @param   material @~english A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @~chinese 物理材质PhysicsMaterial对象，默认值是PHYSICSSHAPE_MATERIAL_DEFAULT。
     * @param   border @~english It's a edge's border width.
     * @~chinese 矩形的边框宽度。
     * @param   offset @~english A Vec2 object, it is the offset from the body’s center of gravity in body local coordinates.
     * @~chinese 形状在刚体局部坐标中相对于重心的偏移量。
     * @return @~english  An autoreleased PhysicsShapeEdgeBox object pointer.
     * @~chinese 一个自释放的PhysicsShapeEdgeBox对象指针。
     */
    static PhysicsShapeEdgeBox* create(const Size& size, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 0, const Vec2& offset = Vec2::ZERO);
    
    /**@~english
     * Get this box's position offset.
     *
     * @~chinese 
     * 这个矩形的位置偏移量。
     * 
     * @return @~english A Vec2 object.
     * @~chinese 位置偏移量。
     */
    virtual Vec2 getOffset() override { return getCenter(); }
    
protected:
    bool init(const Size& size, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1, const Vec2& offset = Vec2::ZERO);
    
protected:
    PhysicsShapeEdgeBox();
    virtual ~PhysicsShapeEdgeBox();
    
    friend class PhysicsBody;
};

/** @~english A chain shape.  @~chinese 链形状。*/
class CC_DLL PhysicsShapeEdgeChain : public PhysicsShape
{
public:
    /**@~english
     * Creates a PhysicsShapeEdgeChain with specified value.
     *
     * @~chinese 
     * 创建一个链形状PhysicsShapeEdgeChain对象。
     * 
     * @param   points @~english A Vec2 object pointer, it contains an array of points.
     * @~chinese 链的顶点。
     * @param   count @~english An interger number, contains the count of the points array.
     * @~chinese 链的顶点数量。
     * @param   material @~english A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @~chinese 物理材质PhysicsMaterial对象，默认值是PHYSICSSHAPE_MATERIAL_DEFAULT。
     * @param   border @~english It's a edge's border width.
     * @~chinese 链的边框宽度。
     * @return @~english  An autoreleased PhysicsShapeEdgeChain object pointer.
     * @~chinese 一个自释放的PhysicsShapeEdgeChain对象指针。
     */
    static PhysicsShapeEdgeChain* create(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    
    /**@~english
     * Get this chain's center position.
     *
     * @~chinese 
     * 得到这个链的中心位置。
     * 
     * @return @~english A Vec2 object.
     * @~chinese 中心位置。
     */
    virtual Vec2 getCenter() override;
    
    /**@~english
     * Get this chain's points array.
     *
     * @~chinese 
     * 把这个链的顶点数组。
     * 
     * @param outPoints @~english A Vec2 array pointer.
     * @~chinese 顶点数组。
     */
    void getPoints(Vec2* outPoints) const;
    
    /**@~english
     * Get this chain's points array count.
     *
     * @~chinese 
     * 得到这个链的顶点数量。
     * 
     * @return @~english An interger number.
     * @~chinese 顶点数量。
     */
    int getPointsCount() const;
    
protected:
    bool init(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSSHAPE_MATERIAL_DEFAULT, float border = 1);
    virtual void updateScale() override;
    
protected:
    PhysicsShapeEdgeChain();
    virtual ~PhysicsShapeEdgeChain();

    friend class PhysicsBody;
};

/** @} */
/** @} */

NS_CC_END

#endif // CC_USE_PHYSICS
#endif // __CCPHYSICS_FIXTURE_H__
