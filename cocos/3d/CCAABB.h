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

#ifndef __CC_AABB_H__
#define __CC_AABB_H__

#include "base/ccMacros.h"
#include "math/CCMath.h"

NS_CC_BEGIN

/**
 * @addtogroup _3d
 * @{
 */

/**
 * @class AABB
 * @brief  @~english Axis Aligned Bounding Box (AABB), usually used to detect the collision at early step
 * @~chinese 轴对齐包围盒，轴对齐包围盒是一种特殊的包围盒，
 * 它的边与世界坐标系中的轴平行，通常用其在碰撞检测之间做前期判断.
 */
class CC_DLL AABB
{

public:
    /**
     * Constructor.
     * @lua new
     */
    AABB();
    
    /**
     * @~english Constructor. construct the AABB object from min & max vector. @~chinese 构造函数，通过输入最大和最小向量来构造AABB
     * @lua new
     * @param min @~english The min vector
     * @~chinese 最小向量
     * @param max The max vector
     * @~chinese 最大向量
     */
    AABB(const Vec3& min, const Vec3& max);
    
    /**
     * @~english Constructor.
     * @~chinese 拷贝构造函数
     */
    AABB(const AABB& box);
    
    /**
     * @~english Gets the center point of the bounding box.
     * @~chinese 获得包围盒的中点
     * @return @~english the centre point of the bounding box.
     * @~chinese 包围盒的中点
     */
    Vec3 getCenter();

    /**
     * @~english Gets the corners of the bounding box.
     * @~chinese 获取包围盒各个顶点
     * @param dst @~english A pointer to corners array.
     * @~chinese 定点数组的指针
     * @note @~english Near face, specified counter-clockwise looking towards the origin from the positive z-axis.
     * verts[0] : left top front
     * verts[1] : left bottom front
     * verts[2] : right bottom front
     * verts[3] : right top front
     *
     * Far face, specified counter-clockwise looking towards the origin from the negative z-axis.
     * verts[4] : right top back
     * verts[5] : right bottom back
     * verts[6] : left bottom back
     * verts[7] : left top back
     * @~chinese 数组内各个位置标示的顶点如下所示（前，后指朝着Y轴负方向看而言）：
     * verts[0] : 左上前
     * verts[1] : 坐下前
     * verts[2] : 右下前
     * verts[3] : 右上前
     *
     * verts[4] : 右上后
     * verts[5] : 右下后
     * verts[6] : 左下后
     * verts[7] : 左上后
     */
    void getCorners(Vec3 *dst) const;

    /**
     * @~english Tests whether this bounding box intersects with the specified bounding object.
     * @~chinese 测试与指定的AABB是否相交
     * @param aabb @~english The specified bounding box.
     * @~chinese 指定的AABB
     * @return @~english Return true when two AABBs intersect, otherwise return false.
     * @~chinese 当两AABB相交时返回true，反之则false
     */
    bool intersects(const AABB& aabb) const;

    /**
     * @~english Check if the point is contained in the bounding box.
     * @~chinese 检测指定点是否在包围盒内
     * @param point @~english The specified point @~chinese 指定的点
     * @return @~english Return true when the point is contained in the bounding box, otherwise return false.
     * @~chinese 当指定在包围盒内时返回true，反之返回false
     */
    bool containPoint(const Vec3& point) const;

    /**
     * @~english Sets this bounding box to the smallest bounding box that contains both this bounding object and the specified bounding box.
     * @~chinese 合并指定包围盒，使本包围盒变为最小能容纳两者的包围盒
     * @param box @~english The specified box. 
     * @~chinese 指定的包围盒
     */
    void merge(const AABB& box);

    /**
     * @~english Sets this bounding box to the specified values.
     * @~chinese 通过min max 向量 来设置包围盒
     * @param min @~english the min vector
     * @~chinese min向量
     * @param max @~english the max vector
     * @~chinese max向量
     */
    void set(const Vec3& min, const Vec3& max);
    
    /**
     * @~english Reset min and max value.If you invoke this method, isEmpty() shall return true.
     * @~chinese 重设包围盒
     */
    void reset();
    
    /**
     * @~english Check the AABB object is empty(reset).
     * @~chinese 检查包围盒是否为空
     * @return @~english Return true when the AABB object is empty, otherwise return false.
     * @~chinese 当包围盒对象为空时返回true，反之则返回false
     */
    bool isEmpty() const;

    /**
     * @~english Update the _min and _max from the given point.
     * @~chinese 通过一个顶点数组来更新包围盒
     * @param point @~english The points array.
     * @~chinese 顶点数组
     * @param num @~english The pints array's size.
     * @~chinese 数组的大小
     */
    void updateMinMax(const Vec3* point, ssize_t num);
    
    /**
     * @~english Transforms the bounding box by the given transformation matrix.
     * @~chinese 通过指定的变换矩阵来变换包围盒
     * @param mat @~english the specified transform-matrix.
     * @~chinese 指定的变换矩阵
     */
    void transform(const Mat4& mat);

public:
    Vec3 _min;
    Vec3 _max;
};

// end of 3d group
/// @}

NS_CC_END

#endif
