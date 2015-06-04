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

#ifndef __CC_RAY_H_
#define __CC_RAY_H_

#include "math/CCMath.h"
#include "3d/CCAABB.h"
#include "3d/CCOBB.h"
#include "3d/CCPlane.h"

NS_CC_BEGIN

/**
 * @addtogroup _3d
 * @{
 */

/**
 * @class Ray
 * @brief @~english Ray is a line with one end. usually use it to check intersects with some object,such as Plane, OBB, AABB
 * @~chinese 射线是朝单方向延伸的直线，通常用来与一些物体进行相交测试，如平面，OBB包围盒，AABB包围盒
 * @js NA
 **/
class CC_DLL Ray
{
public:
    /**
     * @~english Constructor.
     * @~chinese 构造函数
     * @lua new
     */
    Ray();

    /**
     * @~english Copy Constructor.
     * @~chinese 拷贝构造函数
     * @lua NA
     */
    Ray(const Ray& ray);
    
    /**
     * @~english Constructs a new ray initialized to the specified origin and direction.
     * @~chinese 通过给定的起始点以及方向用来创建射线
     * @param origin @~english The ray's origin.
     * @~chinese 射线的起点
     * @param direction @~english The ray's direction.
     * @~chinese 射线的方向
     * @lua new
     */
    Ray(const Vec3& origin, const Vec3& direction);

    /**
     * @~english Destructor.
     * @~chinese 析构函数
     * @lua NA
     */
    ~Ray();

    /**
     * @~english Check whether this ray intersects with the specified AABB.
     * @param aabb @~english The AABB object.
     * @param distance @~english The distance between the orign to the intersection point.
     * @return @~english Return true if the AABB intersect with the ray, otherwise return false.
     */
    bool intersects(const AABB& aabb, float* distance = nullptr) const;
    
    /**
     * @~english Check whether this ray intersects with the specified OBB.
     * @~chinese 检查该射线是否与给定的OBB包围盒相交
     * @param obb @~english The OBB object.
     * @~chinese 指定的OBB包围盒
     * @param distance @~english The distance between the orign to the intersection point.
     * @~chinese 从起始点到与包围盒橡胶垫的距离
     * @return @~english Return true if the OBB intersect with the ray, otherwise return false.
     * @~chinese 与OBB包围盒相交时返回true，反之返回false
     */
    bool intersects(const OBB& obb, float* distance = nullptr) const;

    /**
     * @~english Get the distance to the plane.
     * @~chinese 获取射线到平面的距离
     * @param plane @~english The specified plane.
     * @~chinese 指定的平面
     * @return @~english The distance to the plane.
     * @~chinese 射线起始点到平面的距离
     */
    float dist(const Plane& plane) const;

    /**
     * @~english Check whether this ray intersects with the specified Plane.
     * @~chinese 检查射线是否与指定平面相交
     * @param plane @~english The Plane object.
     * @~chinese 指定的平面对象
     * @return @~english The intersection point.
     * @~chinese 射线与平面的交点
     */
    Vec3 intersects(const Plane& plane) const;
    
    /**
     * @~english Sets this ray to the specified origin and direction.
     * @~chinese 设置射线的起点与方向
     * @param origin @~english The ray's origin.
     * @~chinese 射线的起点
     * @param direction @~english The ray's direction.
     * @~chinese 射线的方向
     */
    void set(const Vec3& origin, const Vec3& direction);

    /**
     * @~english Transforms this ray by the given transformation matrix.
     * @~chinese 通过给定的变换矩阵变换射线
     * @param matrix @~english The transformation matrix to transform by.
     * @~chinese 给定的变换矩阵
     */
    void transform(const Mat4& matrix);
    /**
     * @~english The ray origin position.
     * @~chinese 射线的起始点
     */
    Vec3 _origin;
    /**
     * @~english The ray direction vector.
     * @~chinese 射线的方向向量
     */
    Vec3 _direction; 
};

// end of 3d group
/// @}

NS_CC_END

#endif
