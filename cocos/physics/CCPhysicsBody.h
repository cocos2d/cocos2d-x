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

struct cpBody;

NS_CC_BEGIN

class Node;
class Sprite;
class PhysicsWorld;
class PhysicsJoint;

typedef Vec2 Vect;


const PhysicsMaterial PHYSICSBODY_MATERIAL_DEFAULT(0.1f, 0.5f, 0.5f);

/**
 * @addtogroup core
 * @{
 */

/**@~english
 * A body affect by physics.
 *
 * It can attach one or more shapes.
 * If you create body with createXXX, it will automatically compute mass and moment with density your specified(which is PHYSICSBODY_MATERIAL_DEFAULT by default, and the density value is 0.1f), and it based on the formular: mass = density * area.
 * If you create body with createEdgeXXX, the mass and moment will be PHYSICS_INFINITY by default. And it's a static body.
 * You can change mass and moment with setMass() and setMoment(). And you can change the body to be dynamic or static by use function setDynamic().
 * @~chinese 
 * 受物理影响的刚体。
 * 
 * 它可以连接一个或多个形状。
 * 如果刚体是通过createXXX创建的,它会根据指定的密度（如果使用PHYSICSBODY_MATERIAL_DEFAULT，默认为0.1）来计算质量和力矩，计算公式如下: mass = density * area。
 * 如果刚体是通过createEdgeXXX创建的，质量和力矩默认设置为PHYSICS_INFINITY，并且这是一个静态刚体。
 * 你可以通过setMass()和setMoment()来改变质量和力矩。并且，你还可以通过setDynamic()来改变刚体的静态或动态属性。 
 */
class CC_DLL PhysicsBody : public Ref
{
public:
    /** @~english
     * Create a body with default mass and moment.
     
     * This default mass value is 1.0.
     * This default moment value is 200.
     * @~chinese 
     * 根据默认的质量和力矩值创建一个刚体。
     * 
     * 质量的默认值是1.0。
     * 力矩的默认值200。
     @return @~english  An autoreleased PhysicsBody object pointer.
     * @~chinese 一个自释放的PhysicsBody对象。
     */
    static PhysicsBody* create();
   
    /** @~english
     * Create a body with mass and default moment.
     
     * @~chinese 
     * 根据质量和默认的力矩创建一个刚体。
     * 
     @param mass @~english This body's mass.
     * @~chinese 刚体质量。
     @return @~english  An autoreleased PhysicsBody object pointer.
     * @~chinese 一个自释放的PhysicsBody对象。
     */
    static PhysicsBody* create(float mass);
    
    /** @~english
     * Create a body with mass and moment.
     
     * @~chinese 
     * 根据质量和力矩创建一个刚体。
     * 
     @param mass @~english This body's mass.
     * @~chinese 刚体质量。
     @param moment @~english This body's moment.
     * @~chinese 刚体力矩。
     @return @~english  An autoreleased PhysicsBody object pointer.
     * @~chinese 一个自释放的PhysicsBody对象。
     */
    static PhysicsBody* create(float mass, float moment);
    
    /** @~english
     Create a body contains a circle.
     * @~chinese 
     * 创建一个包含圆形的刚体。
     * 
     * @param   radius @~english A float number, it is the circle's radius.
     * @~chinese 浮点数,它是圆的半径。
     * @param   material @~english A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @~chinese PhysicsMaterial对象,默认值是PHYSICSSHAPE_MATERIAL_DEFAULT。
     * @param   offset @~english A Vec2 object, it is the offset from the body’s center of gravity in body local coordinates.
     * @~chinese Vec2对象，表示形状在刚体的本地坐标系中相对重心的偏移量。
     @return @~english  An autoreleased PhysicsBody object pointer.
     * @~chinese 一个自释放的PhysicsBody对象指针。
     */
    static PhysicsBody* createCircle(float radius, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    /** @~english
     * Create a body contains a box shape.
     *
     * @~chinese 
     * 创建一个矩形形状的物理刚体。
     * 
     * @param   size @~english Size contains this box's width and height.
     * @~chinese 大小包含这个矩形的宽度和高度。
     * @param   material @~english A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @~chinese PhysicsMaterial对象,默认值是PHYSICSSHAPE_MATERIAL_DEFAULT。
     * @param   offset @~english A Vec2 object, it is the offset from the body’s center of gravity in body local coordinates.
     * @~chinese 刚体形状在刚体局部坐标系中相对于重心的偏移量，它是一个Vec2对象。
     * @return @~english  An autoreleased PhysicsBody object pointer.
     * @~chinese 一个自释放的PhysicsBody对象。
     */
    static PhysicsBody* createBox(const Size& size, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    
    /**
     * @brief @~english Create a body contains a polygon shape.
     *
     * @~chinese 创建一个包含多边形的刚体。
     * 
     * @param   points @~english Points is an array of Vec2 structs defining a convex hull with a clockwise winding.
     * @~chinese   以顺时间方向采集到的凸多边形顶点数组。
     * @param   count @~english An interger number, contains the count of the points array.
     * @~chinese 顶点数组的大小。
     * @param   material @~english A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @~chinese PhysicsMaterial对象,默认值是PHYSICSSHAPE_MATERIAL_DEFAULT。
     * @param   offset @~english A Vec2 object, it is the offset from the body’s center of gravity in body local coordinates.
     * @~chinese 刚体形状在刚体局部坐标系中相对重心的偏移量，它是一个Vec2对象。
     * @return @~english  An autoreleased PhysicsBody object pointer.
     * @~chinese 一个自释放的PhysicsBody对象。
     */
    static PhysicsBody* createPolygon(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, const Vec2& offset = Vec2::ZERO);
    
    /** @~english
     * Create a body contains a EdgeSegment shape. 
     
     * @~chinese 
     * 创建一个包含线段形状的刚体。
     * 
     * @param   a @~english It's the edge's begin position.
     * @~chinese 线段起点的位置。
     * @param   b @~english It's the edge's end position.
     * @~chinese 线段终点的位置。
     * @param   material @~english A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @~chinese PhysicsMaterial对象,默认值是PHYSICSSHAPE_MATERIAL_DEFAULT。
     * @param   border @~english It's a edge's border width.
     * @~chinese 边缘的边框宽度。
     * @return @~english  An autoreleased PhysicsBody object pointer.
     * @~chinese 一个自释放的PhysicsBody对象。
     */
    static PhysicsBody* createEdgeSegment(const Vec2& a, const Vec2& b, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, float border = 1);
    
    /** @~english
     * Create a body contains a EdgeBox shape. 

     * @~chinese 
     * 创建一个包含空心矩形形状的刚体。
     * 
     * @param   size @~english Size contains this box's width and height.
     * @~chinese 包含空心矩形宽高的Size对象。
     * @param   material @~english A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @~chinese PhysicsMaterial对象,默认值是PHYSICSSHAPE_MATERIAL_DEFAULT。
     * @param   border @~english It's a edge's border width.
     * @~chinese 边缘的边框宽度。
     * @param   offset @~english A Vec2 object, it is the offset from the body’s center of gravity in body local coordinates.
     * @~chinese 刚体形状在刚体局部坐标系中相对重心的偏移量，它是一个Vec2对象。
     * @return @~english  An autoreleased PhysicsBody object pointer.
     * @~chinese 一个自释放的PhysicsBody对象。
     */
    static PhysicsBody* createEdgeBox(const Size& size, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, float border = 1, const Vec2& offset = Vec2::ZERO);
    
    /** @~english
     * Create a body contains a EdgePolygon shape. 
     
     * @~chinese 
     * 创建一个包含空心多边形形状的刚体。
     * 
     * @param   points @~english Points is an array of Vec2 structs defining a convex hull with a clockwise winding.
     * @~chinese 以顺时间方向采集到的凸多边形顶点数组。
     * @param   count @~english An interger number, contains the count of the points array.
     * @~chinese 顶点数组的大小。
     * @param   material @~english A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @~chinese PhysicsMaterial对象,默认值是PHYSICSSHAPE_MATERIAL_DEFAULT。
     * @param   border @~english It's a edge's border width.
     * @~chinese 边缘的边框宽度。
     * @return @~english  An autoreleased PhysicsBody object pointer.
     * @~chinese 一个自释放的PhysicsBody对象。
     */
    static PhysicsBody* createEdgePolygon(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, float border = 1);
    
    /** @~english
     * Create a body contains a EdgeChain shape.
     
     * @~chinese 
     * 创建一个包含EdgeChain形状的刚体。
     * 
     * @param   points @~english A Vec2 object pointer, it contains an array of points.
     * @~chinese 一个指向Vec2对象数组的指针。
     * @param   count @~english An interger number, contains the count of the points array.
     * @~chinese 顶点数组的大小。
     * @param   material @~english A PhysicsMaterial object, the default value is PHYSICSSHAPE_MATERIAL_DEFAULT.
     * @~chinese PhysicsMaterial对象,默认值是PHYSICSSHAPE_MATERIAL_DEFAULT。
     * @param   border @~english It's a edge's border width.
     * @~chinese 边缘的边框宽度。
     * @return @~english  An autoreleased PhysicsBody object pointer.     
     * @~chinese 一个自释放的PhysicsBody对象。
     */
    static PhysicsBody* createEdgeChain(const Vec2* points, int count, const PhysicsMaterial& material = PHYSICSBODY_MATERIAL_DEFAULT, float border = 1);
    
    /**
     * @brief @~english Add a shape to body.
     * @~chinese 添加一个形状到刚体。
     * @param shape @~english The shape to be added.
     * @~chinese 要添加的形状。
     * @param addMassAndMoment @~english If this is true, the shape's mass and moment will be added to body. The default is true.
     * @~chinese 如果这个值是true,那么形状的质量和力矩将会自动地加到刚体。默认值是true。
     * @return @~english This shape's pointer if added success or nullptr if failed.
     * @~chinese 如果添加成功返回形状的指针，否则返回nullptr。
     */
    virtual PhysicsShape* addShape(PhysicsShape* shape, bool addMassAndMoment = true);

    /**
     * @brief @~english Remove a shape from body.
     * @~chinese 从刚体中移除形状。
     * @param shape @~english Shape the shape to be removed.
     * @~chinese 要被移除的形状。
     * @param reduceMassAndMoment @~english If this is true, the body mass and moment will be reduced by shape. The default is true.
     * @~chinese 如果参数为true，刚体的质量和力矩将由于形状的移除而减小, 默认值为true。
     */
    void removeShape(PhysicsShape* shape, bool reduceMassAndMoment = true);

    /**
     * @brief @~english Remove a shape from body.
     * @~chinese 从刚体中移除形状。
     * @param tag @~english The tag of the shape to be removed.
     * @~chinese 将要被移除的形状的标签。
     * @param reduceMassAndMoment @~english If this is true, the body mass and moment will be reduced by shape. The default is true.
     * @~chinese 如果参数值为true，刚体的质量和力矩将由于形状的移除而减小，默认值为true。
     */
    void removeShape(int tag, bool reduceMassAndMoment = true);
    
    /** @~english
     * Remove all shapes.
     
     * @~chinese 
     * 删除所有的形状。
     * 
     * @param reduceMassAndMoment @~english If this is true, the body mass and moment will be reduced by shape. The default is true.
     * @~chinese 如果参数值是true，刚体的质量和力矩将由于形状的移除而减小，默认值为true。
     */
    void removeAllShapes(bool reduceMassAndMoment = true);

    /**@~english
     * Get the body shapes.

     * @~chinese 
     * 获取刚体的shape Vector。
     * 
     * @return @~english A Vector<PhysicsShape*> object contains PhysicsShape pointer.
     * @~chinese 一个包含PhysicsShape指针的Vector对象引用。
     */
    inline const Vector<PhysicsShape*>& getShapes() const { return _shapes; }
    
    /** @~english
     * Get the first shape of the body shapes.
     
     * @~chinese 
     * 获取刚体的第一个形状。
     * 
     @return @~english The first shape in this body.
     * @~chinese 刚体的第一个形状。
     */
    inline PhysicsShape* getFirstShape() const { return _shapes.size() >= 1 ? _shapes.at(0) : nullptr; }

    /** @~english
     * Get the shape of the body. 
     
     * @~chinese 
     * 获取刚体的形状。
     * 
     * @param   tag   @~english An interger number that identifies a PhysicsShape object.
     * @~chinese 用于查找PhysicsShape对象的整型标签。
     * @return @~english A PhysicsShape object pointer or nullptr if no shapes were found.
     * @~chinese 返回PhysicsShape对象指针和nullptr。
     */
    PhysicsShape* getShape(int tag) const;
    
    /** @~english
     * Applies a continuous force to body.
     
     * @~chinese 
     * 给一个刚体施加一个持续的力。
     * 
     * @param force @~english The force is applies to this body.
     * @~chinese 施加于刚体的力。
     */
    virtual void applyForce(const Vect& force);
    
    /** @~english
     * Applies a continuous force to body.
     
     * @~chinese 
     * 给一个刚体施加一个持续的力。
     * 
     @param force @~english The force is applies to this body.
     * @~chinese 施加于刚体的力。
     @param offset @~english A Vec2 object, it is the offset from the body’s center of gravity in world coordinates.
     * @~chinese 所施加的力相对于刚体的重心在世界坐标的偏移量，它是一个Vec2对象。
     */
    virtual void applyForce(const Vect& force, const Vec2& offset);

    /** @~english
     * reset all the force applied to body. 
     * @~chinese 
     * 重置所有施加于刚体的力。
     */
    virtual void resetForces();

    /**@~english
     * Applies a immediate force to body.
     
     * @~chinese 
     * 给刚体施加一个立即起效的冲量。
     * 
     * @param impulse @~english The impulse is applies to this body.
     * @~chinese 应用于刚体的脉冲。
     */
    virtual void applyImpulse(const Vect& impulse);

    /**@~english
     * Applies a immediate force to body.
     * @~chinese 
     * 给刚体施加一个立即起效的冲量。
     * 
     * @param impulse @~english The impulse is applies to this body.
     * @~chinese 应用于刚体的脉冲。
     * @param offset @~english A Vec2 object, it is the offset from the body’s center of gravity in world coordinates.
     * @~chinese 刚体的重心在世界坐标的偏移，它是一个Vec2对象。
     */
    virtual void applyImpulse(const Vect& impulse, const Vec2& offset);
    
    /** @~english
     * Applies a torque force to body. 
     
     * @~chinese 
     * 给刚体施加一个扭力。
     * 
     * @param torque @~english The torque is applies to this body.
     * @~chinese 应用于刚体的扭力。
     */
    virtual void applyTorque(float torque);
    
    /** @~english
     * Set the velocity of a body.

     * @~chinese 
     * 设置刚体的速度。
     * 
     @param velocity @~english The velocity is set to this body.
     * @~chinese 要设置的刚体速度。
     */
    virtual void setVelocity(const Vect& velocity);
    
    /** @~english Get the velocity of a body.  @~chinese 获取刚体的速度。*/
    virtual Vec2 getVelocity();
    
    /** @~english
     * Set the angular velocity of a body.
     
     * @~chinese 
     * 设置刚体的角速度。
     * 
     * @param velocity @~english The angular velocity is set to this body.
     * @~chinese 要设置的角速度。
     */
    virtual void setAngularVelocity(float velocity);
    
    /** @~english Get the angular velocity of a body at a local point. @~chinese 获取刚体在局部点上的角速度。*/
    virtual Vec2 getVelocityAtLocalPoint(const Vec2& point);
    
    /** @~english get the angular velocity of a body at a world point  @~chinese 获取刚体在世界点上的角速度。*/
    virtual Vec2 getVelocityAtWorldPoint(const Vec2& point);
    
    /** @~english get the angular velocity of a body  @~chinese 获取刚体的角速度。*/
    virtual float getAngularVelocity();
    
    /** @~english set the max of velocity  @~chinese 设置最大速度*/
    virtual void setVelocityLimit(float limit);
    
    /** @~english get the max of velocity  @~chinese 获取最大速度*/
    virtual float getVelocityLimit();
    
    /** @~english set the max of angular velocity  @~chinese 设置最大角速度*/
    virtual void setAngularVelocityLimit(float limit);
    
    /** @~english get the max of angular velocity  @~chinese 获取最大角速度*/
    virtual float getAngularVelocityLimit();
    
    /** @~english remove the body from the world it added to  @~chinese 将刚体从它添加到的世界中移除。*/
    void removeFromWorld();
    
    /** @~english get the world body added to.  @~chinese 获取刚体添加到的世界。*/
    inline PhysicsWorld* getWorld() const { return _world; }
    /** @~english get all joints the body have  @~chinese 获取刚体所有的关节*/
    inline const std::vector<PhysicsJoint*>& getJoints() const { return _joints; }
    
    /** @~english get the sprite the body set to.  @~chinese 获取刚体关联的node对象。*/
    inline Node* getNode() const { return _node; }
    
    /**@~english
     * A mask that defines which categories this physics body belongs to.
     * 
     * Every physics body in a scene can be assigned to up to 32 different categories, each corresponding to a bit in the bit mask. You define the mask values used in your game. In conjunction with the collisionBitMask and contactTestBitMask properties, you define which physics bodies interact with each other and when your game is notified of these interactions.
     * @~chinese 
     * 设置刚体所属种类的掩码值。
     * 
     * 每一个场景中的物理刚体被会分配32个种类，每一个对应一个掩码值。你可以在游戏中自定义掩码值。与collisionBitMask和contactTestBitMask属性结合,你可以定义哪些物理刚体以及什么时候会互相影响。
     * @param bitmask @~english An interger number, the default value is 0xFFFFFFFF (all bits set).
     * @~chinese 整型值,默认是0xffffffff(所有位都为1)。
     */
    void setCategoryBitmask(int bitmask);
    
    /** @~english
     * A mask that defines which categories of bodies cause intersection notifications with this physics body.
     *
     * When two bodies share the same space, each body’s category mask is tested against the other body’s contact mask by performing a logical AND operation. If either comparison results in a non-zero value, an PhysicsContact object is created and passed to the physics world’s delegate. For best performance, only set bits in the contacts mask for interactions you are interested in.
     * @~chinese 
     * 设置这个物理刚体的接触分组掩码，它决定有哪些物理刚体与它产生接触的时候代理会响应。
     * 
     * 当两个刚体在同一个空间中接触时，一个刚体的分组掩码会与另一个的分组掩码做逻辑与操作，如果结果非0，一个PhysicsContact接触对象会被创建并传递給物理世界的代理。为了优化性能，可以只为那些你需要处理接触的刚体之间设置不同的分组掩码。
     * @param bitmask @~english An interger number, the default value is 0x00000000 (all bits cleared).
     * @~chinese 整型值,默认值是0x00000000(所有位都是0)。
     */
    void setContactTestBitmask(int bitmask);
    
    /**@~english
     * A mask that defines which categories of physics bodies can collide with this physics body.
     *
     * When two physics bodies contact each other, a collision may occur. This body’s collision mask is compared to the other body’s category mask by performing a logical AND operation. If the result is a non-zero value, then this body is affected by the collision. Each body independently chooses whether it wants to be affected by the other body. For example, you might use this to avoid collision calculations that would make negligible changes to a body’s velocity.
     * @~chinese 
     * 设置这个物理刚体的碰撞分组掩码，它决定有哪些物理刚体会与它产生碰撞。
     *
     * 当两个刚体在同一个空间中接触时，一个需要处理的碰撞就有可能产生，一个刚体的分组掩码会与另一个的分组掩码做逻辑与操作，如果结果非0，那么刚体就会受碰撞所影响。刚体分别选择是否对碰撞做出响应并影响自己的运动。打个比方，你可以避免碰撞计算所引起的对刚体速度的微小影响。
     * @param bitmask @~english An interger number, the default value is 0xFFFFFFFF (all bits set).
     * @~chinese  整型值,默认值是0xFFFFFFFF(所有位都为1)。
     */
    void setCollisionBitmask(int bitmask);
    
    /** @~english
     * Return bitmask of first shape.
     * @~chinese 
     * 返回第一个形状的掩码值。
     * 
     * @return @~english If there is no shape in body, return default value(0xFFFFFFFF).
     * @~chinese 如果刚体中没有形状,返回默认值(0xFFFFFFFF)。
     */
    int getCategoryBitmask() const;
    
    /** @~english
     * Return bitmask of first shape.
     * @~chinese 
     * 返回第一个形状的掩码值。
     * 
     * @return @~english If there is no shape in body, return default value(0x00000000).
     * @~chinese 如果刚体中没有形状,返回默认值(0x00000000)。
     */
    int getContactTestBitmask() const;
    
    /** @~english
     * Return bitmask of first shape.
     * @~chinese 
     * 返回第一个形状的掩码值。
     * 
     @return @~english If there is no shape in body, return default value.(0xFFFFFFFF)
     * @~chinese 如果刚体中没有形状,返回默认值(0xFFFFFFFF)。
     */
    int getCollisionBitmask() const;
    
    /** @~english
     * Set the group of body.
     *
     * Collision groups let you specify an integral group index. You can have all shapes with the same group index always collide (positive index) or never collide (negative index).
     * It have high priority than bit masks.
     * @~chinese 
     * 设置刚体组。
     * 
     * 碰撞组让你可以指定一个整型索引，你可以让具有同样组索引的形状总是碰撞(正索引)或总不碰撞(负值)。
     * 它比掩码值有更高的优先级。
     */
    void setGroup(int group);
    
    /** @~english
     * Return group of first shape.
     
     * @~chinese 
     * 返回第一个形状的组。
     * 
     * @return @~english If there is no shape in body, return default value(0).
     * @~chinese 如果刚体中没有形状，返回默认值(0)
     */
    int getGroup() const;
    
    /** @~english get the body position.  @~chinese 获取刚体的位置。*/
    const Vec2& getPosition();
    
    /** @~english get the body rotation.  @~chinese 获取刚体的旋转值。*/
    float getRotation();
    
    /** @~english set body position offset, it's the position witch relative to node  @~chinese 设置刚体的偏移量，它是相对node的位置*/
    void setPositionOffset(const Vec2& position);
    
    /** @~english get body position offset.  @~chinese 获取刚体位置的偏移量。*/
    const Vec2& getPositionOffset() const { return _positionOffset; }
    
    /** @~english set body rotation offset, it's the rotation witch relative to node  @~chinese 设置刚体的旋转偏移量，它是相对于node的旋转*/
    void setRotationOffset(float rotation);
    
    /** @~english set the body rotation offset  @~chinese 获取刚体的旋转偏移*/
    float getRotationOffset() const { return _rotationOffset; }
    
    /**
     * @brief @~english Test the body is dynamic or not.
     *
     * A dynamic body will effect with gravity.
     * @~chinese 检查刚体是否是动态地。
     * 
     * 一个动态的刚体将会受重力的影响。
     */
    inline bool isDynamic() const { return _dynamic; }
    /**
     * @brief @~english Set dynamic to body.
     * 
     * A dynamic body will effect with gravity.
     * @~chinese 设置刚体为动态刚体。
     * 
     * 一个动态的刚体将会受重力的影响。
     */
    void setDynamic(bool dynamic);
    
    /**
     * @brief @~english Set the body mass.
     *
     * @~chinese 刚体质量。
     * 
     * @attention @~english If you need add/subtract mass to body, don't use setMass(getMass() +/- mass), because the mass of body may be equal to PHYSICS_INFINITY, it will cause some unexpected result, please use addMass() instead.
     * @~chinese 如果你需要+/-刚体的质量,不要使用setMass(getMass()  +/- mass),因为刚体的质量可能等于PHYSICS_INFINITY,它会导致一些意想不到的结果。所以，请使用addMass()。
     */
    void setMass(float mass);
    
    /** @~english Get the body mass.  @~chinese 获取刚体的质量。*/
    inline float getMass() const { return _mass; }
    /**
     * @brief @~english Add mass to body.
     *
     * @~chinese 增加刚体的质量。
     * 
     * @param mass @~english
     * if mass == PHYSICS_INFINITY, _mass will be PHYSICS_INFINITY.
     * if mass == -PHYSICS_INFINITY, _mass will not change.
     * if mass + _mass <= 0, _mass will equal to MASS_DEFAULT(1.0)
     * other wise, mass = mass + _mass;
     * @~chinese
     * 如果 mass == PHYSICS_INFINITY, _mass还是PHYSICS_INFINITY。
     * 如果 mass == -PHYSICS_INFINITY _mass将不会改变。
     * 如果 mass + _mass <= 0, _mass将等于MASS_DEFAULT(1.0)
     * 否则, mass =  mass + _mass;
     */
    void addMass(float mass);
    
    /**
     * @brief @~english Set the body moment of inertia.
     *
     * @~chinese 设置刚体的惯性力矩。
     * 
     * @note @~english If you need add/subtract moment to body, don't use setMoment(getMoment() +/- moment), because the moment of body may be equal to PHYSICS_INFINITY, it will cause some unexpected result, please use addMoment() instead.
     * @~chinese 如果你需要 +/- 刚体的力矩, 不要使用setMoment(getMoment() +/- moment),因为刚体的力矩可能等于PHYSICS_INFINITY,它会导致一些意想不到的结果。所以，请使用addMoment()。
     */
    void setMoment(float moment);
    
    /** @~english Get the body moment of inertia.  @~chinese 获取刚体的惯性力矩。*/
    inline float getMoment() const { return _moment; }
    
    /**
     * @brief @~english Add moment of inertia to body.
     * 
     * @~chinese 增加刚体的惯性力矩。
     * 
     * @param moment @~english
     * if moment == PHYSICS_INFINITY, _moment will be PHYSICS_INFINITY.
     * if moment == -PHYSICS_INFINITY, _moment will not change.
     * if moment + _moment <= 0, _moment will equal to MASS_DEFAULT(1.0)
     * other wise, moment = moment + _moment;
     * @~chinese
     * 如果 moment == PHYSICS_INFINITY,_moment为PHYSICS_INFINITY。
     * 如果 moment == -PHYSICS_INFINITY,_moment不会改变。
     * 如果 moment + _moment <= 0,_moment将等于MASS_DEFAULT(1.0)
     * 否则,moment = moment + _moment;
     */
    void addMoment(float moment);
    
    /** @~english get linear damping.  @~chinese 得到线性阻尼。*/
    inline float getLinearDamping() const { return _linearDamping; }
    
    /** @~english
     * Set linear damping.
     *
     * it is used to simulate fluid or air friction forces on the body.
     * @~chinese 
     * 设置线性阻尼。
     * 
     * 它是用来模拟液体或空气摩擦力对刚体的影响。
     * @param damping @~english The value is 0.0f to 1.0f.
     * @~chinese f取值的范围是0.0f到1.0f。
     */
    inline void setLinearDamping(float damping) { _linearDamping = damping; updateDamping(); }
    
    /** @~english Get angular damping.  @~chinese 获取角阴尼*/
    inline float getAngularDamping() const { return _angularDamping; }
    /**@~english
     * Set angular damping.
     *
     * It is used to simulate fluid or air friction forces on the body.
     * @~chinese 
     * 设置角阻尼。
     * 
     * 它是用来模拟液体或空气摩擦力对刚体的影响。
     * @param damping @~english The value is 0.0f to 1.0f.
     * @~chinese f f值是0.0到1.0。
     */
    inline void setAngularDamping(float damping) { _angularDamping = damping; updateDamping(); }
    
    /** @~english Whether the body is at rest.  @~chinese 刚体是否静止*/
    bool isResting() const;
    
    /** @~english set body to rest  @~chinese 设置刚体是否静止*/
    void setResting(bool rest) const;

    /**@~english
     * Whether the body is enabled.
     *
     * If the body it isn't enabled, it will not has simulation by world.
     * @~chinese 
     * 刚体是否有效。
     * 
     * 如果刚体无效,它不会有模拟世界。
     */
    inline bool isEnabled() const { return _enabled; }
    
    /**@~english
     * Set the enable value.
     *
     * If the body it isn't enabled, it will not has simulation by world.
     * @~chinese 
     * 设置刚体是否有效。
     * 
     * 如果刚体无效,它不会有模拟世界。
     */
    void setEnable(bool enable);
    
    /** @~english Whether the body can rotation.  @~chinese 刚体是否可以旋转。*/
    inline bool isRotationEnabled() const { return _rotationEnabled; }
    
    /** @~english Set the body is allow rotation or not  @~chinese 设置刚体是否可以旋转*/
    void setRotationEnable(bool enable);
    
    /** @~english Whether this physics body is affected by the physics world’s gravitational force.  @~chinese 刚体是否受物理世界重力的影响。*/
    inline bool isGravityEnabled() const { return _gravityEnabled; }
    
    /** @~english Set the body is affected by the physics world's gravitational force or not.  @~chinese 设置刚体是否受物理世界重力的影响*/
    void setGravityEnable(bool enable);
    
    /** @~english Get the body's tag.  @~chinese 获取刚体的标签。*/
    inline int getTag() const { return _tag; }
    
    /** @~english set the body's tag.  @~chinese 设置刚体的标签。*/
    inline void setTag(int tag) { _tag = tag; }
    
    /** @~english Convert the world point to local.  @~chinese 将世界坐标转换成本地坐标。*/
    Vec2 world2Local(const Vec2& point);
    
    /** @~english Convert the local point to world.  @~chinese 将本地坐标转换成世界坐标。*/
    Vec2 local2World(const Vec2& point);

    /** @~english Get the rigid body of chipmunk.  @~chinese 获取chipmunk中的刚体。*/
    cpBody* getCPBody() { return _cpBody; }
    
protected:
    
    bool init();
    
    virtual void setPosition(const Vec2& position);
    virtual void setRotation(float rotation);
    virtual void setScale(float scaleX, float scaleY);
    
    void update(float delta);
    
    void removeJoint(PhysicsJoint* joint);
    inline void updateDamping() { _isDamping = _linearDamping != 0.0f ||  _angularDamping != 0.0f; }
    
protected:
    PhysicsBody();
    virtual ~PhysicsBody();
    
protected:
    Node* _node;
    std::vector<PhysicsJoint*> _joints;
    Vector<PhysicsShape*> _shapes;
    PhysicsWorld* _world;
    cpBody* _cpBody;
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
    
    bool _positionInitDirty;
    Vec2 _recordedPosition;
    Vec2 _latestPosition;
    Vec2 _positionOffset;
    float _rotationOffset;
    float _recordedRotation;
    double _recordedAngle;
    
    friend class PhysicsWorld;
    friend class PhysicsShape;
    friend class PhysicsJoint;
    friend class Node;
    friend class Layer;
    friend class ProtectedNode;
};

/** @} */

NS_CC_END

#endif // CC_USE_PHYSICS
#endif // __CCPHYSICS_BODY_H__
