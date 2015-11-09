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

#ifndef __CCPHYSICS_WORLD_H__
#define __CCPHYSICS_WORLD_H__

#include "base/ccConfig.h"
#if CC_USE_PHYSICS

#include <list>
#include "base/CCVector.h"
#include "math/CCGeometry.h"
#include "physics/CCPhysicsBody.h"

struct cpSpace;

NS_CC_BEGIN

class PhysicsBody;
class PhysicsJoint;
class PhysicsShape;
class PhysicsContact;

class Director;
class Node;
class Sprite;
class Scene;
class DrawNode;
class PhysicsDebugDraw;
class EventDispatcher;

class PhysicsWorld;

typedef struct PhysicsRayCastInfo
{
    PhysicsShape* shape;
    Vec2 start;
    Vec2 end;              //< in lua, it's name is "ended"
    Vec2 contact;
    Vec2 normal;
    float fraction;
    void* data;
}PhysicsRayCastInfo;

typedef std::function<bool(PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data)> PhysicsRayCastCallbackFunc;
typedef std::function<bool(PhysicsWorld&, PhysicsShape&, void*)> PhysicsQueryRectCallbackFunc;
typedef PhysicsQueryRectCallbackFunc PhysicsQueryPointCallbackFunc;

/**
 * @addtogroup physics
 * @{
 * @addtogroup physics_2d
 * @{
 */

/**
 * @class PhysicsWorld CCPhysicsWorld.h
 * @brief @~english An PhysicsWorld object simulates collisions and other physical properties. You do not create PhysicsWorld objects directly; instead, you can get it from an Scene object.
 * @~chinese 一个PhysicsWorld对象,用于模拟物理碰撞和其他物理行为。你不需要直接创建PhysicsWorld对象;相反,你可以从一个场景对象获取它。
 */
class CC_DLL PhysicsWorld
{
public:
    static const int DEBUGDRAW_NONE;        ///< draw nothing
    static const int DEBUGDRAW_SHAPE;       ///< draw shapes
    static const int DEBUGDRAW_JOINT;       ///< draw joints
    static const int DEBUGDRAW_CONTACT;     ///< draw contact
    static const int DEBUGDRAW_ALL;         ///< draw all
    
public:
    /**@~english
     * Adds a joint to this physics world.
     *
     * This joint will be added to this physics world at next frame.
     * @~chinese 
     * 添加一个关节到物理世界中。
     * 
     * 这个关节将在下一个帧被添加到物理世界中。
     * @attention @~english If this joint is already added to another physics world, it will be removed from that world first and then add to this world.
     * @~chinese 如果这个关节已经添加到另一个物理世界,它将首先从那个物理世界删除,然后再添加到这个物理世界。
     * @param   joint   @~english A pointer to an existing PhysicsJoint object.
     * @~chinese 一个指向已有PhysicsJoint对象的指针
     */
    virtual void addJoint(PhysicsJoint* joint);

    /**@~english
     * Remove a joint from this physics world.
     *
     * If this world is not locked, the joint is removed immediately, otherwise at next frame.
     * If this joint is connected with a body, it will be removed from the body also.
     * @~chinese 
     * 把关节从物理世界中删除。
     * 
     * 如果物理世界没有被锁住,那么此关节会被立即删除,否则等到下一帧再删除。
     * 如果这个关节与一个物理刚体绑在了一起,那么它也将从刚体中删除.
     * @param   joint   @~english A pointer to an existing PhysicsJoint object.
     * @~chinese 一个已有的PhysicsJoint对象的指针。
     * @param   destroy   @~english true this joint will be destroyed after remove from this world, false otherwise.
     * @~chinese True意味着关节从物理世界移除以后会被销毁，False则表示从物理世界移除后并不会销毁。
     */
    virtual void removeJoint(PhysicsJoint* joint, bool destroy = true);

    /**@~english
     * Remove all joints from this physics world.
     *
     * @~chinese 
     * 从物理世界删除所有关节。
     * 
     * @attention @~english This function is invoked in the destructor of this physics world, you do not use this api in common.
     * @~chinese 这个函数会在物理世界析构的时候被调用,一般情况下你不要直接使用这个API。
     * @param   destroy   @~english true all joints will be destroyed after remove from this world, false otherwise.
     * @~chinese 传Ture，意味着当关节从物理世界删除后，它们都会被销毁,False则表示不会被销毁。
     */
    virtual void removeAllJoints(bool destroy = true);
    
    /**@~english
     * Remove a body from this physics world.
     *
     * If this world is not locked, the body is removed immediately, otherwise at next frame.
     * @~chinese 
     * 从物理世界移除一个刚体。
     * 
     * 如果物理世界没有锁住,则刚体被立即删除,否则等到下一帧再删除。
     * @attention @~english If this body has joints, those joints will be removed also.
     * @~chinese 如果这个刚体包含关节,那么这些关节也将被删除。
     * @param   body   @~english A pointer to an existing PhysicsBody object.
     * @~chinese 一个已有的PhysicsBody对象的指针。
     */
    virtual void removeBody(PhysicsBody* body);
    
    /**@~english
     * Remove body by tag.
     *
     * If this world is not locked, the object is removed immediately, otherwise at next frame.
     * @~chinese 
     * 使用一个tag来移除一个刚体。
     * 
     * 如果物理世界没有加锁,则刚体对象被立即删除,否则等于下一帧再删除。
     * @attention @~english If this body has joints, those joints will be removed also.
     * @~chinese 如果这个刚体包含关节,那么这些关节也将被删除。
     * @param   tag   @~english An interger number that identifies a PhysicsBody object.
     * @~chinese 一个整数，用来标识一个 PhysicsBody对象。
     */
    virtual void removeBody(int tag);

    /**@~english
     * Remove all bodies from physics world.
     *
     * If this world is not locked, those body are removed immediately, otherwise at next frame.
     * @~chinese 
     * 删除物理世界中的所有的刚体。
     * 
     * 如果物理世界没有加锁,那么这些刚体会被立即删除,否则等到下一帧再删除。
     */
    virtual void removeAllBodies();
    
    /**@~english
     * Searches for physics shapes that intersects the ray.
     *
     * Query this physics world along the line segment from start to end.
     * @~chinese 
     * 搜索与射线相交的物理形状。
     * 
     * 沿着射线的始点和终点，查询当前物理世界中与该射线相交的物理形状。
     * @param   func   @~english Func is called for each shape found.
     * @~chinese 每当找到一个满足条件的形状的时候，该函数就会被调用。
     * @param   start   @~english A Vec2 object contains the begin position of the ray.
     * @~chinese Vec2对象,它是射线的始点位置
     * @param   end   @~english A Vec2 object contains the end position of the ray.
     * @~chinese Vec2对象,它是射线的终点位置
     * @param   data   @~english User defined data, it is passed to func.
     * @~chinese 用户定义的数据,用来传给回调函数。
     */
    void rayCast(PhysicsRayCastCallbackFunc func, const Vec2& start, const Vec2& end, void* data);
    
    /**@~english
     * Searches for physics shapes that contains in the rect.
     *
     * Query this physics world to find all shapes overlap rect.
     * @~chinese 
     * 查询包含在矩形内的物理形状。
     * 
     * 查询物理世界中所有与该矩形有交集的物理形状。
     * @param   func   @~english Func is called for each shape whose bounding box overlaps rect.
     * @~chinese 每当找到一个满足条件的形状的时候，该函数就会被调用
     * @param   rect   @~english A Rect object contains a rectangle's x, y, width and height.
     * @~chinese 一个矩阵对象，它是一个由起始点和宽高组成的结构体。
     * @param   data   @~english User defined data, it is passed to func.
     * @~chinese 用户定义的数据,用来传给回调函数。
     */
    void queryRect(PhysicsQueryRectCallbackFunc func, const Rect& rect, void* data);
    
    /**@~english
     * Searches for physics shapes that contains the point.
     *
     * @~chinese 
     * 查询包含指定点坐标的所有的物理形状。
     * 
     * @attention @~english The point must lie inside a shape.
     * @~chinese 这个点必须在一个形状内。
     * @param   func   @~english Func is called for each shape contains the point.
     * @~chinese 每当找到一个满足条件的点的时候，该函数就会被调用
     * @param   point   @~english A Vec2 object contains the position of the point.
     * @~chinese 一个Vec2对象
     * @param   data   @~english User defined data, it is passed to func.
     * @~chinese 用户定义的数据,用来传给回调函数。
     */
    void queryPoint(PhysicsQueryPointCallbackFunc func, const Vec2& point, void* data);
    
    /**@~english
     * Get phsyics shapes that contains the point.
     *
     * All shapes contains the point will be pushed in a Vector<PhysicsShape*> object.
     * @~chinese 
     * 查询指定点坐标上的所有的物理形状。
     * 
     * 所有包含此点的物理形状会被添加到一个Vector<PhysicsShape*>对象中去。
     * @attention @~english The point must lie inside a shape.
     * @~chinese 这个点必须在一个物理形状内。
     * @param   point   @~english A Vec2 object contains the position of the point.
     * @~chinese 一个Vec2对象
     * @return @~english A Vector<PhysicsShape*> object contains all found PhysicsShape pointer.
     * @~chinese 一个Vector<PhysicsShape *>对象,它包含所有找到的PhysicsShape指针。
     */
    Vector<PhysicsShape*> getShapes(const Vec2& point) const;
    
    /**@~english
     * Get the nearest phsyics shape that contains the point.
     *
     * Query this physics world at point and return the closest shape.
     * @~chinese 
     * 获取包含指定坐标点的最近的物理形状。
     * 
     * 查询物理世界中包含指定点坐标的最近的物理形状。
     * @param   point   @~english A Vec2 object contains the position of the point.
     * @~chinese 一个Vec2对象。
     * @return @~english A PhysicsShape object pointer or nullptr if no shapes were found
     * @~chinese 一个PhysicsShape对象指针; 或者，如果没有找到符合条件的物理形状，则返回nullptr。
     */
    PhysicsShape* getShape(const Vec2& point) const;

    /**@~english
     * Get all the bodys that in this physics world.
     *
     * @~chinese 
     * 获取物理世界中所有的刚体。
     * 
     * @return @~english A Vector<PhysicsBody*>& object contains all bodies in this physics world.
     * @~chinese 一个<PhysicsBody *>向量对象,它包含物理世界中所有的刚体。
     */
    const Vector<PhysicsBody*>& getAllBodies() const;

    /**@~english
     * Get a body by tag.
     *
     * @~chinese 
     * 通过一个tag来获取一个刚体。
     * 
     * @param   tag   @~english An interger number that identifies a PhysicsBody object.
     * @~chinese 一个整数标识。
     * @return @~english A PhysicsBody object pointer or nullptr if no shapes were found.
     * @~chinese 一个PhysicsBody对象指针或nullptr
     */
    PhysicsBody* getBody(int tag) const;
    
    /**@~english
     * Get a scene contain this physics world.
     *
     * @~chinese 
     * 获取包含物理世界的场景对象。
     * 
     * @attention @~english This value is initialized in constructor
     * @~chinese 这个值是在构造函数中初始化的
     * @return @~english A Scene object reference.
     * @~chinese 一个场景对象引用。
     */
    inline Scene& getScene() const { return *_scene; }
    
    /**@~english
     * Get the gravity value of this physics world.
     *
     * @~chinese 
     * 获取物理世界的重力值。
     * 
     * @return @~english A Vect object.
     * @~chinese 一个Vect对象。 @see Vec2
     */
    inline Vec2 getGravity() const { return _gravity; }
    
    /**@~english
     * set the gravity value of this physics world.
     *
     * @~chinese 
     * 设置物理世界的重力值。
     * 
     * @param gravity @~english A gravity value of this physics world.
     * @~chinese 物理世界的重力值。
     */
    void setGravity(const Vec2& gravity);
    
    /**@~english
     * Set the speed of this physics world.
     *
     * @~chinese 
     * 设置物理世界的仿真执行速度。
     * 
     * @attention @~english if you setAutoStep(false), this won't work.
     * @~chinese 如果setAutoStep(false),那么这个函数将不起作用。
     * @param speed  @~english A float number. Speed is the rate at which the simulation executes. default value is 1.0.
     * @~chinese 一个浮点数。速度指的是物理仿真的执行速度。默认址是1.0
     */
    inline void setSpeed(float speed) { if(speed >= 0.0f) { _speed = speed; } }
    
    /**@~english
     * Get the speed of this physics world.
     *
     * @~chinese 
     * 得到物理世界仿真执行速度
     * 
     * @return @~english A float number.
     * @~chinese 一个浮点数
     */
    inline float getSpeed() { return _speed; }
    
    /**@~english
     * Set the update rate of this physics world
     * 
     * Update rate is the value of EngineUpdateTimes/PhysicsWorldUpdateTimes.
     * Set it higher can improve performance, set it lower can improve accuracy of physics world simulation.
     * @~chinese 
     * 设置物理世界的更新速率
     * 
     * 更新速率等于EngineUpdateTimes/PhysicsWorldUpdateTimes
     * 设置的值越高，越可以提高性能,把它降低，则可以提高物理世界的仿真精度。
     * @attention @~english if you setAutoStep(false), this won't work.
     * @~chinese 如果你设置setAutoStep(false),那么该函数不起作用。
     * @param rate @~english An interger number, default value is 1.0.
     * @~chinese interger数量,默认值是1.0
     */
    inline void setUpdateRate(int rate) { if(rate > 0) { _updateRate = rate; } }


    /**@~english
     * Get the update rate of this physics world.
     *
     * @~chinese 
     * 获取物理世界的更新速率。
     * 
     * @return @~english An interger number.
     * @~chinese 一个interger的数字。
     */
    inline int getUpdateRate() { return _updateRate; }

    /**@~english
     * set the number of substeps in an update of the physics world.
     * 
     * One physics update will be divided into several substeps to increase its accuracy.
     * @~chinese 
     * 设置更新物理世界的子步骤的数量。
     * 
     * 一个物理更新将被分为几个子步骤,可以提高物理仿真的准确性。
     * @param steps @~english An interger number, default value is 1.
     * @~chinese 一个interger的数字,默认值是1。
     */
    void setSubsteps(int steps);

    /**@~english
     * Get the number of substeps of this physics world.
     *
     * @~chinese 
     * 获取物理世界的子步骤的数量。
     * 
     * @return @~english An interger number.
     * @~chinese 一个interger的数字。
     */
    inline int getSubsteps() const { return _substeps; }

    /**@~english
     * Set the debug draw mask of this physics world.
     *
     * This physics world will draw shapes and joints by DrawNode acoording to mask.
     * @~chinese 
     * 设置物理世界的调试绘制掩码
     * 
     * 物理世界会根据设置好的调试绘制掩码，调用DrawNode来绘制物理形状和物理关节。
     * @param mask @~english Mask has four value:DEBUGDRAW_NONE, DEBUGDRAW_SHAPE, DEBUGDRAW_JOINT, DEBUGDRAW_CONTACT and DEBUGDRAW_ALL, default is DEBUGDRAW_NONE
     * @~chinese 掩码有以下4个取值: DEBUGDRAW_NONE DEBUGDRAW_SHAPE, DEBUGDRAW_JOINT, DEBUGDRAW_CONTACT and DEBUGDRAW_ALL, default is DEBUGDRAW_NONE
     */
    void setDebugDrawMask(int mask);

    /**@~english
     * Get the bebug draw mask.
     *
     * @~chinese 
     * 查询调试绘制掩码。
     * 
     * @return @~english An interger number.
     * @~chinese 一个interger的数字。
     */
    inline int getDebugDrawMask() { return _debugDrawMask; }
    
    /**@~english
     * To control the step of physics.
     *
     * If you want control it by yourself( fixed-timestep for example ), you can set this to false and call step by yourself.
     * @~chinese 
     * 控制物理迭代的方法
     * 
     * 如果你想要自己控制物理迭代方法,例如使用固定时间步长(fixed-timestep)的迭代方法,你可以传False.
     * @attention @~english If you set auto step to false, setSpeed setSubsteps and setUpdateRate won't work, you need to control the time step by yourself.
     * @~chinese 如果你设置False的话，那么`setSpeed`和`setSubsteps`,以及`setUpdateRate`函数都不能正常工作了，所以这些行为你都必须自己来控制。
     * @param autoStep @~english A bool object, defaut value is true.
     * @~chinese 一个bool对象,默认值为True.
     */
    void setAutoStep(bool autoStep){ _autoStep = autoStep; }


    /**@~english
     * Get the auto step of this physics world.
     *
     * @~chinese 
     * 获取物理世界是否使用自动迭代方法。
     * 
     * @return @~english A bool object.
     * @~chinese 一个bool对象。
     */
    bool isAutoStep() { return _autoStep; }

    /**@~english
     * The step for physics world.
     *
     * The times passing for simulate the physics.
     * @~chinese 
     * 物理世界的迭代步长。
     * 
     * 传递一次模拟物理所需要的时间。
     * @attention @~english You need to setAutoStep(false) first before it can work.
     * @~chinese 让这个函数生效前，你需要调用setAutoStep(false)。
     * @param   delta   @~english A float number.
     * @~chinese 一个浮点数
     */
    void step(float delta);
    
protected:
    static PhysicsWorld* construct(Scene* scene);
    bool init();
    
    
    virtual void addBody(PhysicsBody* body);
    virtual void addShape(PhysicsShape* shape);
    virtual void removeShape(PhysicsShape* shape);
    virtual void update(float delta, bool userCall = false);
    
    virtual void debugDraw();
    
    virtual int collisionBeginCallback(PhysicsContact& contact);
    virtual int collisionPreSolveCallback(PhysicsContact& contact);
    virtual void collisionPostSolveCallback(PhysicsContact& contact);
    virtual void collisionSeparateCallback(PhysicsContact& contact);
    
    virtual void doAddBody(PhysicsBody* body);
    virtual void doRemoveBody(PhysicsBody* body);
    virtual void doRemoveJoint(PhysicsJoint* joint);
    virtual void addBodyOrDelay(PhysicsBody* body);
    virtual void removeBodyOrDelay(PhysicsBody* body);
    virtual void updateBodies();
    virtual void updateJoints();
    
protected:
    Vec2 _gravity;
    float _speed;
    int _updateRate;
    int _updateRateCount;
    float _updateTime;
    int _substeps;
    cpSpace* _cpSpace;
    
    bool _updateBodyTransform;
    Vector<PhysicsBody*> _bodies;
    std::list<PhysicsJoint*> _joints;
    Scene* _scene;
    
    bool _autoStep;
    PhysicsDebugDraw* _debugDraw;
    int _debugDrawMask;
    
    EventDispatcher* _eventDispatcher;

    Vector<PhysicsBody*> _delayAddBodies;
    Vector<PhysicsBody*> _delayRemoveBodies;
    std::vector<PhysicsJoint*> _delayAddJoints;
    std::vector<PhysicsJoint*> _delayRemoveJoints;
    
protected:
    PhysicsWorld();
    virtual ~PhysicsWorld();
    
    void beforeSimulation(Node *node, const Mat4& parentToWorldTransform, float nodeParentScaleX, float nodeParentScaleY, float parentRotation);
    void afterSimulation(Node* node, const Mat4& parentToWorldTransform, float parentRotation);

    friend class Node;
    friend class Sprite;
    friend class Scene;
    friend class Director;
    friend class PhysicsBody;
    friend class PhysicsShape;
    friend class PhysicsJoint;
    friend class PhysicsWorldCallback;
    friend class PhysicsDebugDraw;
};

/** @~english A physics helper class. Draw physics shape, joint in debug mode. 
 *  You do not create PhysicsDebugDraw objects directly; Instead, you can activate it by PhysicsWorld::setDebugDrawMask.
 * @~chinese 一个物理的辅助类。它可以在调试状态下绘制形状和关节。
 * 你不需要直接创建一个 PhysicsDebugDraw对象； 你可以通过调用 `PhysicsWorld::setDebugDrawMask`方法来创建该对象。
 */
class CC_DLL PhysicsDebugDraw
{
protected:
    virtual bool begin();
    virtual void end();
    virtual void drawShape(PhysicsShape& shape);
    virtual void drawJoint(PhysicsJoint& joint);
    virtual void drawContact();
    
protected:
    PhysicsDebugDraw(PhysicsWorld& world);
    virtual ~PhysicsDebugDraw();
    
protected:
    DrawNode* _drawNode;
    PhysicsWorld& _world;
    
    friend class PhysicsWorld;
};
extern const float CC_DLL PHYSICS_INFINITY;

/** @} */
/** @} */

NS_CC_END

#endif // CC_USE_PHYSICS
#endif // __CCPHYSICS_WORLD_H__
