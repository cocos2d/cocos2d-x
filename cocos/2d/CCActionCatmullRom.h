/*
 * Copyright (c) 2008 Radu Gruian
 * Copyright (c) 2011 Vit Valentin
 * Copyright (c) 2012 cocos2d-x.org
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *
 * Original code by Radu Gruian: http://www.codeproject.com/Articles/30838/Overhauser-Catmull-Rom-Splines-for-Camera-Animatio.So
 *
 * Adapted to cocos2d-x by Vit Valentin
 *
 * Adapted from cocos2d-x to cocos2d-iphone by Ricardo Quesada
 */


#ifndef __CCACTION_CATMULLROM_H__
#define __CCACTION_CATMULLROM_H__

#include <vector>

#include "2d/CCActionInterval.h"
#include "2d/CCNode.h"
#include "math/CCGeometry.h"

NS_CC_BEGIN;

/**
 * @addtogroup actions
 * @{
 */

/** 一个包含控制坐标的数组.
 它所使用的是笛卡尔曲线和CatmullRom线曲线动作 .
@ingroup Actions
 */
class CC_DLL PointArray : public Ref, public Clonable
{
public:
    
    /** 创建或初始化这个数组集合的容量大小
     * @js NA
     */
    static PointArray* create(ssize_t capacity);
    
    /**
     * @js NA
     * @lua NA
     */
    virtual ~PointArray();
    /**
     * @js NA
     * @lua NA
     */
    PointArray();
    
    /** 初始化一条指定大小的曲线 
     * @js NA
     */
    bool initWithCapacity(ssize_t capacity);
    
    /** 添加一个控制点 
     * @js NA
     */
    void addControlPoint(Vec2 controlPoint);
    
    /** 插入一个控制点
     * @js NA
     */
    void insertControlPoint(Vec2 &controlPoint, ssize_t index);
    
    /** 替换现有的控制点
     * @js NA
     */
    void replaceControlPoint(Vec2 &controlPoint, ssize_t index);
    
    /** 获得一个指定索引的控制点的值
     * @js NA
     */
    Vec2 getControlPointAtIndex(ssize_t index);
    
    /** 删除指定索引的控制点deletes a control point at a given index 
     * @js NA
     */
    void removeControlPointAtIndex(ssize_t index);
    
    /** 返回这个控制点数组里面的所有节点的总数 
     * @js NA
     */
    ssize_t count() const;
    
    /** 返回一个新的逆向的数组集合. 用户必须主动释放这个副本 
     * @js NA
     */
    PointArray* reverse() const;
    
    /** 将这个内联的数组的控制点逆向化, 他不会产生一个新的数组
     * @js NA
     */
    void reverseInline();
    /**
     * @js NA
     * @lua NA
     */
    virtual PointArray* clone() const;
    /**
     * @js NA
     */
    const std::vector<Vec2*>* getControlPoints() const;
    /**
     * @js NA
     */
    void setControlPoints(std::vector<Vec2*> *controlPoints);
private:
    /** 这个包含控制点的数组集合 */
    std::vector<Vec2*> *_controlPoints;
};

/** 基础曲线路径.
 http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline
@ingroup Actions
 */
class CC_DLL CardinalSplineTo : public ActionInterval
{
public:

    /** 创建一个连续的基础曲线动作的点数组集合
     * @code
     * 当这个函数绑定到js或lua,输入参数会发生变化
     * in js: var create(var t,var table)
     * in lua: lcaol create(local t, local table)
     * @endcode
     */
    static CardinalSplineTo* create(float duration, PointArray* points, float tension);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~CardinalSplineTo();
    /**
     * @js NA
     * @lua NA
     */
    CardinalSplineTo();
    
    /** 初始化一个持续动作的点的数组集合 */
    bool initWithDuration(float duration, PointArray* points, float tension);

    virtual void updatePosition(Vec2 &newPos);

    inline PointArray* getPoints() { return _points; }
    /**
     * @js NA
     * @lua NA
     */
    inline void setPoints(PointArray* points)
    {
        CC_SAFE_RETAIN(points);
        CC_SAFE_RELEASE(_points);
        _points = points;
    }

    // 可重载
	virtual CardinalSplineTo *clone() const override;
    virtual CardinalSplineTo* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;

protected:
    /** 这个控制点的数组实体 */
    PointArray *_points;
    float _deltaT;
    float _tension;
    Vec2	_previousPosition;
    Vec2	_accumulatedDiff;
};

/** 基础曲线路径..
 http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline
 @ingroup Actions
 */
class CC_DLL CardinalSplineBy : public CardinalSplineTo 
{
public:
    
    /** 创建一个连续的基础曲线动作的点数组集合
     * @code
     * 当这个函数绑定到js或lua,输入参数会发生变化
     * in js: var create(var t,var table)
     * in lua: lcaol create(local t, local table)
     * @endcode
     */
    static CardinalSplineBy* create(float duration, PointArray* points, float tension);

    CardinalSplineBy();
    
    // 可重载
    virtual void startWithTarget(Node *target) override;
    virtual void updatePosition(Vec2 &newPos) override;
	virtual CardinalSplineBy *clone() const override;
    virtual CardinalSplineBy* reverse() const override;

protected:
    Vec2 _startPosition;
};

/** 这是一个按照CatmullRom曲线移动目标点的动作.
 这个Catmull Rom曲线路径的弧度为0.5.
 http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull.E2.80.93Rom_spline
 @ingroup Actions
 */
class CC_DLL CatmullRomTo : public CardinalSplineTo
{
public:
    
    /** 这个方法创建了一个连续的笛卡尔曲线的数组
     * @code
     * 当这个函数绑定到js或lua,输入参数会发生变化
     * in js: var create(var dt,var table)
     * in lua: lcaol create(local dt, local table)
     * @endcode
     */
    static CatmullRomTo* create(float dt, PointArray* points);

    /** 这个方法初始化了一个可持续的点的数组集合 */
    bool initWithDuration(float dt, PointArray* points);

    // Override
	virtual CatmullRomTo *clone() const override;
	virtual CatmullRomTo *reverse() const override;
};

/**
    这是一个按照笛卡尔曲线移动目标点的动作.
    这个笛卡尔曲线路径的弧度为0.5.
 http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull.E2.80.93Rom_spline
 @ingroup Actions
 */
class CC_DLL CatmullRomBy : public CardinalSplineBy
{
public:
    /** 这个方法创建了一个连续的笛卡尔曲线的数组
     * @code
     * 当这个函数绑定到js或lua,输入参数会发生变化
     * in js: var create(var dt,var table)
     * in lua: lcaol create(local dt, local table)
     * @endcode
     */
    static CatmullRomBy* create(float dt, PointArray* points);

    /** 这个方法初始化了一个可持续的点的数组集合 */
    bool initWithDuration(float dt, PointArray* points);

    // 可重载方法
	virtual CatmullRomBy *clone() const override;
	virtual CatmullRomBy *reverse() const override;

};

/** Returns the Cardinal Spline position for a given set of control points, tension and time */
extern CC_DLL Vec2 ccCardinalSplineAt(Vec2 &p0, Vec2 &p1, Vec2 &p2, Vec2 &p3, float tension, float t);

// end of actions group
/// @}

NS_CC_END;

#endif // __CCACTION_CATMULLROM_H__
