/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#ifndef __CCCAMERA_ACTION_H__
#define __CCCAMERA_ACTION_H__

#include "CCActionInterval.h"
#include "kazmath/kazmath.h"

NS_CC_BEGIN

class Camera;

/**
 * @addtogroup actions
 * @{
 */

/** 
@brief Base class for Camera actions
@ingroup Actions
*/
class CC_DLL ActionCamera : public ActionInterval //<NSCopying> 
{
public:
    /**
     * @js ctor
     */
    ActionCamera();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ActionCamera(){};

    // 可重载
    virtual void startWithTarget(Node *target) override;
    virtual ActionCamera * reverse() const override;
	virtual ActionCamera *clone() const override;

    /* 设置人眼所在的位置坐标 */
    void setEye(const kmVec3 &eye);
    void setEye(float x, float y, float z);
    /* 返回人眼所在点的向量值 */
    const kmVec3& getEye() const { return _eye; }
    /* 设置中心点所在的位置 */
    void setCenter(const kmVec3 &center);
    /* 返回中心点所在的位置 */
    const kmVec3& getCenter() const { return _center; }
    /* 设置向上的向量值 */
    void setUp(const kmVec3 &up);
    /* 返回向上的向量值 */
    const kmVec3& getUp() const { return _up; }

protected:

    void restore();
    void updateTransform();

    kmVec3 _center;
    kmVec3 _eye;
    kmVec3 _up;
};

/** 
@brief OrbitCamera action
视角按照球面坐标轨迹 围绕屏幕中心进行旋转
@ingroup Actions
*/
class CC_DLL OrbitCamera : public ActionCamera //<NSCopying> 
{
public:
    /** 创建一个带有起始半径、半径差、起始z角、旋转z角的差、起始x角、旋转x角的差 这些参数的运动视角动作类 */
    static OrbitCamera* create(float t, float radius, float deltaRadius, float angleZ, float deltaAngleZ, float angleX, float deltaAngleX);
    
    /** 根据球面坐标确定视角的位置 */
    void sphericalRadius(float *r, float *zenith, float *azimuth);

    // 可重载
	OrbitCamera *clone() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    OrbitCamera();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~OrbitCamera();
    
    /** 初始化一个运动视角动作类的起始半径、半径差、起始z角、旋转z角的差、起始x角、旋转x角的差 */
    bool initWithDuration(float t, float radius, float deltaRadius, float angleZ, float deltaAngleZ, float angleX, float deltaAngleX);

protected:
    float _radius;
    float _deltaRadius;
    float _angleZ;
    float _deltaAngleZ;
    float _angleX;
    float _deltaAngleX;

    float _radZ;
    float _radDeltaZ;
    float _radX;
    float _radDeltaX;
};

// end of actions group
/// @}

NS_CC_END

#endif //__CCCAMERA_ACTION_H__