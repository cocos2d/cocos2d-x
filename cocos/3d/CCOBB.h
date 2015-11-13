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

#ifndef __CC_OBB_H__
#define __CC_OBB_H__

#include "CCAABB.h"

NS_CC_BEGIN

/**
 * @addtogroup _3d
 * @{
 */

/**
 * @~english Oritened Bounding Box(OBB)
 * @class OBB
 * @brief @~english The OBB is similar to the AABB but the bounding box has the same direction as Sprite3D. so it's collistion detection more precise than AABB
 * @~chinese  OBB包围盒与AABB包围盒类似，但是其局部坐标系的三个轴并不与世界坐标系的三个轴平行，即，考虑了物体的旋转情况，因此它能提供比AABB更为准确的碰撞检测
 * @js NA
 */
class CC_DLL OBB
{
public:
    OBB();

    /*
     * @~english Construct obb from axis aligned bounding box(AABB).
     * @~chinese 通过AABB 创建OBB
     * @param aabb @~english The AABB object.
     * @~chinese AABB 对象
     * @lua NA
     */
    OBB(const AABB& aabb);
    
    /*
     * @~english Construct obb from points.
     * @~chinese 通过给定的顶点数组创建OBB
     * @param verts @~english Vertices array.
     * @~chinese 给定的顶点数组
     * @param num @~english The size of the verticies array. 
     * @~chinese 顶点数组的大小
     * @lua NA
     */
    OBB(const Vec3* verts, int num);
    
    /**
     * @~english Check if the point is contained in the bounding box.
     * @~chinese 检测一个点是否在包围盒内
     * @param point @~english The specified point.
     * @~chinese 给定的点
     * @return @~english Return true when the point is contained in the bounding box, otherwise return false.
     * @~chinese 当该点在包围盒内时，返回True，反之返回false.
     */
    bool containPoint(const Vec3& point) const;

    /*
     * @~english Specify obb values
     * @~chinese 指定OBB对象的属性
     * @param center @~english The obb's center.
     * @~chinese OBB中点
     * @param _xAxis @~english The obb's X axis in wrold space.
     * @~chinese OBB在世界坐标系下的X轴
     * @param _yAxis @~english The obb's Y axis in wrold space.
     * @~chinese OBB在世界坐标系下的Y轴
     * @param _zAxis @~english The obb's Z axis in wrold space.
     * @~chinese OBB在世界坐标系下的Z轴
     * @param _extents @~english The obb's size.
     * @~chinese OBB的尺寸(各边边长)
     */
    void set(const Vec3& center, const Vec3& _xAxis, const Vec3& _yAxis, const Vec3& _zAxis, const Vec3& _extents);
    
    /*
     * Clear obb
     * @~chinese 清除OBB数据
     */ 
    void reset();

    /** 
     * @~english Get Obb's corners.
     * @~chinese 获取OBB的各顶点
     * @param verts @~english The Corners vertices array.
     * @~chinese 顶点数组
     * @note @~english Face to the obb's -z direction
     * verts[0] : left top front
     * verts[1] : left bottom front
     * verts[2] : right bottom front
     * verts[3] : right top front
     *
     * face to the obb's z direction
     * verts[4] : right top back
     * verts[5] : right bottom back
     * verts[6] : left bottom back
     * verts[7] : left top back
     * @~chinese 假设在XOY平面朝-z方向望去，OBB各顶点的索引为
     * verts[0] : 左上前
     * verts[1] : 左下前
     * verts[2] : 右下前
     * verts[3] : 右上前
     *
     * verts[4] : 右上后
     * verts[5] : 右下后
     * verts[6] : 左下后
     * verts[7] : 左上后
     */
    void getCorners(Vec3* verts) const;
    
    /**
    * @~english Tests whether this bounding box intersects the specified bounding object.
    * @~chinese 检测指定的包围盒是否与其相交
    * @param box @~english The specified bounding box.
    * @~chinese 指定的包围盒
    * @return @~english Return true when two OOBBS intersect, otherwise return false.
    * @~chinese 当相交时返回true，反之返回false
    */
    bool intersects(const OBB& box) const;
    
	/**
     * @~english Transforms the obb by the given transformation matrix.
     * @~chinese 通过给定的矩阵变换OBB对象
     * @param mat @~english The transform matrix.
     * @~chinese 指定的变换矩阵
     */
    void transform(const Mat4& mat);
    
protected:
    /*
    * @~english Compute extX, extY, extZ
    */
    void computeExtAxis()
    {
        _extentX = _xAxis * _extents.x;
        _extentY = _yAxis * _extents.y;
        _extentZ = _zAxis * _extents.z;
    }
    
    /*
     * Project point to the target axis
     */
    float projectPoint(const Vec3& point, const Vec3& axis) const;
    
    /*
     * Calculate the min and max project value of through the box's corners
     */
    void getInterval(const OBB& box, const Vec3& axis, float &min, float &max) const;
    
    /*
     * Get the edge of x y z axis direction
     */
    Vec3 getEdgeDirection(int index) const;
    
    /*
     * Get the face of x y z axis direction
     */
    Vec3 getFaceDirection(int index) const;

public:
    Vec3 _center;   // obb center
    Vec3 _xAxis;    // x axis of obb, unit vector
    Vec3 _yAxis;    // y axis of obb, unit vector
    Vec3 _zAxis;    // z axis of obb, unit vector
    Vec3 _extentX;  // _xAxis * _extents.x
    Vec3 _extentY;  // _yAxis * _extents.y
    Vec3 _extentZ;  // _zAxis * _extents.z
    Vec3 _extents;  // obb length along each axis
};

// end of 3d group
/// @}

NS_CC_END

#endif
