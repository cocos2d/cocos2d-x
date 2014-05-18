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

#include "base/CCVector.h"
#include "base/CCRef.h"
#include "math/CCGeometry.h"

#include <list>

NS_CC_BEGIN

class PhysicsBody;
class PhysicsJoint;
class PhysicsWorldInfo;
class PhysicsShape;
class PhysicsContact;

typedef Vec2 Vect;

class Node;
class Sprite;
class Scene;
class DrawNode;
class PhysicsDebugDraw;

class PhysicsWorld;

typedef struct PhysicsRayCastInfo
{
    PhysicsShape* shape;
    Vec2 start;
    Vec2 end;              //< 在lua 中，它的名字是"ended"
    Vec2 contact;
    Vect normal;
    float fraction;
    void* data;
}PhysicsRayCastInfo;

/**
 * @brief  当被查询中找到时被调用。你通过返回一个float控制光线投射怎么被处理。
 * 返回true: 继续
 * 返回false: 终止光线投射
 * @param fixture 被光线投射的设备
 * @param point 初始的交叉点
 * @param normal 交叉点的方向矢量
 * @return true to continue, false to terminate 返回true继续，返回false终止。
 
 */
typedef std::function<bool(PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data)> PhysicsRayCastCallbackFunc;
typedef std::function<bool(PhysicsWorld&, PhysicsShape&, void*)> PhysicsQueryRectCallbackFunc;
typedef PhysicsQueryRectCallbackFunc PhysicsQueryPointCallbackFunc;

/**
 * @brief 一个PhysicsWorld对象模拟冲突和其他物理属性。你可以不直接创建PhysicsWorld对象，以之代替的，你可以从一个Scene对象获取它。
 */
class PhysicsWorld
{
public:
    static const int DEBUGDRAW_NONE;        ///< 什么都不画
    static const int DEBUGDRAW_SHAPE;       ///< 画形状
    static const int DEBUGDRAW_JOINT;       ///< 画关节点
    static const int DEBUGDRAW_CONTACT;     ///< 画接触
    static const int DEBUGDRAW_ALL;         ///< 画所有东西
    
public:
    /** 向PhysicsWorld增加一个关节点 */
    virtual void addJoint(PhysicsJoint* joint);
    /** 从PhysicsWorld删除一个节点 */
    virtual void removeJoint(PhysicsJoint* joint, bool destroy = true);
    /** 从PhysicsWorld删除所有的关节点*/
    virtual void removeAllJoints(bool destroy = true);
    
    /** 从PhysicsWorld移除body */
    virtual void removeBody(PhysicsBody* body);
    /** 通过tag移除body */
    virtual void removeBody(int tag);
    /** 从PhysicsWorld移除所有body */
    virtual void removeAllBodies();
    
    /** 寻找和光线相交的物理形状 */
    void rayCast(PhysicsRayCastCallbackFunc func, const Vec2& start, const Vec2& end, void* data);
    /** 寻找包含在矩形中的物理形状 */
    void queryRect(PhysicsQueryRectCallbackFunc func, const Rect& rect, void* data);
    /** 寻找包含某个点的物理形状 */
    void queryPoint(PhysicsQueryPointCallbackFunc func, const Vec2& point, void* data);
    /** 寻找包含某个点的物理形状 */
    Vector<PhysicsShape*> getShapes(const Vec2& point) const;
    /** 寻找包含某个点的物理形状 */
    PhysicsShape* getShape(const Vec2& point) const;
    /** 获取所有在物理世界的body */
    const Vector<PhysicsBody*>& getAllBodies() const;
    /** 通过tag获取body */
    PhysicsBody* getBody(int tag) const;
    
    /** 获取被物理世界包含的场景 */
    inline Scene& getScene() const { return *_scene; }
    /** 获取重力值 */
    inline Vect getGravity() const { return _gravity; }
    /** 设置重力值 */
    void setGravity(const Vect& gravity);
    /** 设置物理世界的速度，速度是模拟执行的速率，默认值是1.0  */
    inline void setSpeed(float speed) { if(speed >= 0.0f) { _speed = speed; } }
    /** 获取物理世界的速度。 */
    inline float getSpeed() { return _speed; }
    /** 
     * 设置物理世界的更新速率，更新速率是EngineUpdateTimes/PhysicsWorldUpdateTimes的值
     * 把它设置高点可以提高表现，把它设置低点能提高物理世界模拟的准确性。
     * 默认值是1.0
     */
    inline void setUpdateRate(int rate) { if(rate > 0) { _updateRate = rate; } }
    /** 获取更新速率 */
    inline int getUpdateRate() { return _updateRate; }
    
    /** 设置debug draw mask */
    void setDebugDrawMask(int mask);
    /** 获取debug draw mask */
    inline int getDebugDrawMask() { return _debugDrawMask; }
    
protected:
    static PhysicsWorld* construct(Scene& scene);
    bool init(Scene& scene);
    
    virtual void addBody(PhysicsBody* body);
    virtual void addShape(PhysicsShape* shape);
    virtual void removeShape(PhysicsShape* shape);
    virtual void update(float delta);
    
    virtual void debugDraw();
    
    virtual int collisionBeginCallback(PhysicsContact& contact);
    virtual int collisionPreSolveCallback(PhysicsContact& contact);
    virtual void collisionPostSolveCallback(PhysicsContact& contact);
    virtual void collisionSeparateCallback(PhysicsContact& contact);
    
    virtual void doAddBody(PhysicsBody* body);
    virtual void doRemoveBody(PhysicsBody* body);
    virtual void doAddJoint(PhysicsJoint* joint);
    virtual void doRemoveJoint(PhysicsJoint* joint);
    virtual void addBodyOrDelay(PhysicsBody* body);
    virtual void removeBodyOrDelay(PhysicsBody* body);
    virtual void addJointOrDelay(PhysicsJoint* joint);
    virtual void removeJointOrDelay(PhysicsJoint* joint);
    virtual void updateBodies();
    virtual void updateJoints();
    
protected:
    Vect _gravity;
    float _speed;
    int _updateRate;
    int _updateRateCount;
    float _updateTime;
    PhysicsWorldInfo* _info;
    
    Vector<PhysicsBody*> _bodies;
    std::list<PhysicsJoint*> _joints;
    Scene* _scene;
    
    bool _delayDirty;
    PhysicsDebugDraw* _debugDraw;
    int _debugDrawMask;
    
    
    Vector<PhysicsBody*> _delayAddBodies;
    Vector<PhysicsBody*> _delayRemoveBodies;
    std::vector<PhysicsJoint*> _delayAddJoints;
    std::vector<PhysicsJoint*> _delayRemoveJoints;
    
protected:
    PhysicsWorld();
    virtual ~PhysicsWorld();
    
    friend class Node;
    friend class Sprite;
    friend class Scene;
    friend class PhysicsBody;
    friend class PhysicsShape;
    friend class PhysicsJoint;
    friend class PhysicsWorldCallback;
    friend class PhysicsDebugDraw;
};


class PhysicsDebugDraw
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
extern const float PHYSICS_INFINITY;

NS_CC_END

#endif // CC_USE_PHYSICS
#endif // __CCPHYSICS_WORLD_H__
