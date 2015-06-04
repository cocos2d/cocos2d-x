/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
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

#ifndef __CC_PLANE_H_
#define __CC_PLANE_H_

#include "base/ccMacros.h"
#include "math/CCMath.h"

NS_CC_BEGIN
/**
* @addtogroup _3d
* @{
*/
/**
 * @enum PointSide
 * @brief @~english This enum define the location relationship between the specified point an specified plane.
 * @~chinese 该枚举类型定义了一个给定点与给定平面之间的位置关系
 **/
enum class PointSide
{
    /** @~english The Point which in the plane. @~chinese 点在平面上*/
    IN_PLANE, 
    /**
     * @~english The point which in the front side of the plane, which means the dot product for point and normal is greater  than 0 
     * @~chinese 点在平面的正面，即点向量（原点到该点的向量）与平面法线的点积大于零
     */
    FRONT_PLANE,
    /**
     * @~english The point which in the back side of the plane, which means the dot product for point and normal is less  than 0 
     * @~chinese 点在平面的反面，即点向量（原点到该点的向量）与平面法线的点积小于零
     */
    BEHIND_PLANE,
};

/**
 * @class Plane
 * @brief @~english Defines plane
 * @~chinese 该类定义了一个平面
 * @js NA
 * @lua NA
 **/
class CC_DLL Plane
{
public:
    /**
    * @~english Create plane from tree point.
    * @~chinese 通过三个点创建一个平面
    * @param p1 @~english The point #1 which's in the plane.
    * @~chinese 平面上的第一个点
    * @param p2 @~english The point #2 which's in the plane.
    * @~chinese 平面上的第二个点
    * @param p3 @~english The point #3 which's in the plane.
    * @~chinese 平面上的第三个点
    */
    Plane(const Vec3& p1, const Vec3& p2, const Vec3& p3);

    /**
    * @~english Create plane from normal and dist.
    * @~chinese 通过平面的法线与坐标系原点沿着法线到平面的距离来创建平面
    * @param normal @~english The normal vector of the plane.
    * @~chinese 平面的法线
    * @param dist @~english The distance from the origin along the normal.
    * @~chinese 坐标系原点沿着法线到平面的距离
    */
    Plane(const Vec3& normal, float dist);

    /**
    * @~english Create plane from normal and a point on plane.
    * @~chinese 通过平面法线与平面上一点创建平面
    * @param normal @~english The normal vector of the plane.
    * @~chinese 平面法线
    * @param point @~english The point which's in the plane.
    * @~chinese 平面上一点
    */
    Plane(const Vec3& normal, const Vec3& point);
    
    /**
     * @~english Create a default plan whose normal is (0, 0, 1), and _dist is 0, xoy plan in fact.
     * @~chinese 创建默认参数的平面，默认法线为(0,0,1)，与远点的距离为0（即XOY平面）
     */
    Plane();
    
    /**
    * @~english Init plane from tree point.
    * @~chinese 通过三个在平面上的点来初始化平面
    * @param p1 @~english The point #1 which's in the plane.
    * @~chinese 平面上第一个点
    * @param p2 @~english The point #2 which's in the plane.
    * @~chinese 平面上第二个点
    * @param p3 @~english The point #3 which's in the plane.
    * @~chinese 平面上第三个点
    */
    void initPlane(const Vec3& p1, const Vec3& p2, const Vec3& p3);

    /**
    * @~english Init plane from normal and dist.
    * @~chinese 通过平面法线，原点沿法线方向到平面的距离来初始化平面
    * @param normal @~english The normal vector of the plane.
    * @~chinese 平面法线
    * @param dist @~english The distance from the origin.
    * @~chinese 坐标原点沿着法线方向到平面的距离
    */
    void initPlane(const Vec3& normal, float dist);

    /**
    * @~english Init plane from normal and a point on plane.
    * @~chinese 通过平面的法线以及平面上一点来初始化平面
    * @param normal @~english The normal vector of the plane.
    * @~chinese 平面的法线
    * @param point @~english The point which's in the plane.
    * @~chinese 平面上一点
    */
    void initPlane(const Vec3& normal, const Vec3& point);

    /**
    * @~english Get the specified point's distance to the plane.
    * @~chinese 获得给定点沿着法线方向到平面的距离
    * @param p @~english The specified point.
    * @~chinese 给定的任意一点
    * @return @~english The distance, > 0 in the normal side.
    * @~chinese 点到平面的距离，值大于零表示点在平面的法线朝向的它的一侧，反之则表示点在平面的法线背向它的一侧
    */
    float dist2Plane(const Vec3& p) const;

    /**
    * @~english Gets the plane's normal.
    * @~chinese 获取平面法线
    * @return @~english The normal of the plane.
    * @~chinese 平面的法线
    */
    const Vec3& getNormal() const { return _normal; }

    /**
    * @~english Gets the distance which origin along its normal reach the plane.
    * @~chinese 获取原点沿着法线到平面的距离
    * @return @~english The distance to the origin.
    * @~chinese 距离值
    */
    float getDist() const  { return _dist; }

    /**
    * @~english Return the side where the point is.
    * @~chinese 获取给定任意一点与平面的位置关系
    * @return @~english The side.
    * @~chinese 位置关系
    */
    PointSide getSide(const Vec3& point) const;

protected:
    Vec3 _normal; // the normal line of the plane
    float _dist; // original displacement of the normal
};
// end of 3d group
/// @}
NS_CC_END

#endif
