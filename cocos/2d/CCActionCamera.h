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

#include "2d/CCActionInterval.h"
#include "math/CCMath.h"

NS_CC_BEGIN

class Camera;

/**
 * @addtogroup actions
 * @{
 */

/**
 *@brief @~english Base class for Camera actions.
 * @~chinese 相机动作的基类。
 *@ingroup Actions
 */
class CC_DLL ActionCamera : public ActionInterval //<NSCopying> 
{
public:
    /**
     * @js ctor
     * @lua new
     */
    ActionCamera();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ActionCamera(){};

    // Overrides
    virtual void startWithTarget(Node *target) override;
    virtual ActionCamera * reverse() const override;
	virtual ActionCamera *clone() const override;

    /* @~english Sets the Vec3 poisition of Eye of the Camera. 
     * 
     * @~chinese 设置相机的视点的三维坐标。
     * 
     * @param eye @~english The Vec3 poisition of Eye of the Camera.
     * @~chinese 相机的视点的三维坐标。
     * @js NA
     */
    void setEye(const Vec3 &eye);
    void setEye(float x, float y, float z);
    /* @~english Returns the Vec3 poisition of Eye of the Camera. 
     *
     * @~chinese 返回相机的视点的三维坐标。
     * 
     * @return @~english The Vec3 poisition of Eye of the Camera.
     * @~chinese 相机的视点的三维坐标。
     * @js NA
     */
    const Vec3& getEye() const { return _eye; }
    /* @~english Sets the Center position of the Camera. 
     *
     * @~chinese 设置相机中心的三维坐标。
     * 
     * @param center @~english The Center position of the Camera.
     * @~chinese 相机的中心坐标。
     * @js NA
     */
    void setCenter(const Vec3 &center);
    /* @~english Returns the Center position of the Camera. 
     *
     * @~chinese 返回相机中心的三维坐标。
     * 
     * @return @~english The Center position of the Camera.
     * @~chinese 相机的中心坐标。
     * @js NA
     */
    const Vec3& getCenter() const { return _center; }
    /* @~english Sets the Up vector of the Camera. 
     *
     * @~chinese 设置相机的三维向上向量。
     * 
     * @param up @~english The Up vector of the Camera.
     * @~chinese 相机的三维向上向量。
     * @js NA
     */
    void setUp(const Vec3 &up);
    /* @~english Returns the Up vector of the Camera. 
     *
     * @~chinese 返回相机的三维向上向量。
     * 
     * @return @~english The Up vector of the Camera.
     * @~chinese 相机的三维向上向量。
     * @js NA
     */
    const Vec3& getUp() const { return _up; }

protected:

    void restore();
    void updateTransform();

    Vec3 _center;
    Vec3 _eye;
    Vec3 _up;
};

/** @class OrbitCamera
 *
 * @brief @~english OrbitCamera action.
 * Orbits the camera around the center of the screen using spherical coordinates.
 * @~chinese OrbitCamera动作。
 * 使用球面坐标为轨道绕屏幕中心移动相机。
 * @ingroup Actions
 */
class CC_DLL OrbitCamera : public ActionCamera //<NSCopying> 
{
public:
    /** @~english Creates a OrbitCamera action with radius, delta-radius,  z, deltaZ, x, deltaX. 
     *
     * @~chinese 用起始半径，半径增量，起始z轴角度，z轴角度增量，起始x轴角度，x轴角度增量作为参数创建一个OrbitCamera动作。
     * 
     * @param t @~english Duration in seconds.
     * @~chinese 以秒为单位的持续时间。
     * @param radius @~english The start radius.
     * @~chinese 起始半径。
     * @param deltaRadius @~english The delta radius.
     * @~chinese 半径增量。
     * @param angleZ @~english The start angle in Z.
     * @~chinese 起始z轴角度。
     * @param deltaAngleZ @~english The delta angle in Z.
     * @~chinese z轴角度增量。
     * @param angleX @~english The start angle in X.
     * @~chinese 起始x轴角度.
     * @param deltaAngleX @~english The delta angle in X.
     * @~chinese x轴角度增量。
     * @return @~english An OrbitCamera.
     * @~chinese 一个OrbitCamera动作。
     */
    static OrbitCamera* create(float t, float radius, float deltaRadius, float angleZ, float deltaAngleZ, float angleX, float deltaAngleX);
    
    /** @~english Positions the camera according to spherical coordinates. 
     *
     * @~chinese 根据球面坐标设置相机位置。
     * 
     * @param r @~english The spherical radius.
     * @~chinese 球面半径。
     * @param zenith @~english The spherical zenith.
     * @~chinese 球面天顶角。
     * @param azimuth @~english The spherical azimuth.
     * @~chinese 球面方位角.
     */
    void sphericalRadius(float *r, float *zenith, float *azimuth);

    // Overrides
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
    
    /** @~english Initializes a OrbitCamera action with radius, delta-radius,  z, deltaZ, x, deltaX.
     * @~chinese 用起始半径，半径增量，起始z轴角度，z轴角度增量，起始x轴角度，x轴角度增量作为参数初始化一个OrbitCamera动作。*/
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
