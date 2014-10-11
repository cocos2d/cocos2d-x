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

class CC_DLL OBB
{
public:
    OBB();

    /*
     * Construct obb from oriented bounding box
     */
    OBB(const AABB& aabb);
    
    /*
     * Construct obb from points
     */
    OBB(const Vec3* verts, int num);
    
    /*
     * Check point in
     */
    bool containPoint(const Vec3& point) const;

    /*
     * Specify obb values
     */
    void set(const Vec3& center, const Vec3& _xAxis, const Vec3& _yAxis, const Vec3& _zAxis, const Vec3& _extents);
    
    /*
     * Clear obb
     */ 
    void reset();

    /* face to the obb's -z direction
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
     */
    void getCorners(Vec3* verts) const;
    
    /*
     * Check intersect with other
     */
    bool intersects(const OBB& box) const;
    
	/**
     * Transforms the obb by the given transformation matrix.
     */
    void transform(const Mat4& mat);
    
protected:
    /*
     * Project point to the target axis
     */
    float projectPoint(const Vec3& point, const Vec3& axis) const;
    
    /*
     * Calculate the min and max project value of through the box's corners
     */
    void getInterval(const OBB& box, const Vec3& axis, float &min, float &max) const;
    
    /*
     * Get the edege of x y z axis direction
     */
    Vec3 getEdgeDirection(int index) const;
    
    /*
     * Get the face of x y z axis direction
     */
    Vec3 getFaceDirection(int index) const;

public:
    Vec3 _center;   // obb center
    Vec3 _xAxis;    // x axis of obb, unit vector
    Vec3 _yAxis;    // y axis of obb, unit vecotr
    Vec3 _zAxis;    // z axis of obb, unit vector
    Vec3 _extents;  // obb length along each axis
};

NS_CC_END

#endif
