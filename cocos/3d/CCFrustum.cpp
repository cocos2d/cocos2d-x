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

#include "3d/CCFrustum.h"
#include "2d/CCCamera.h"

NS_CC_BEGIN

bool Frustum::initFrustum(const Camera* camera)
{
    _initialized = true;
    createPlane(camera);
    return true;
}
bool Frustum::isOutOfFrustum(const AABB& aabb) const
{
    if (_initialized)
    {
        Vec3 point;

        int plane = _clipZ ? 6 : 4;
        for (int i = 0; i < plane; i++)
        {
            const Vec3& normal = _plane[i].getNormal();
            point.x = normal.x < 0 ? aabb._max.x : aabb._min.x;
            point.y = normal.y < 0 ? aabb._max.y : aabb._min.y;
            point.z = normal.z < 0 ? aabb._max.z : aabb._min.z;
            
            if (_plane[i].getSide(point) == PointSide::FRONT_PLANE )
                return true;
        }
    }
    return false;
}

bool Frustum::isOutOfFrustum(const OBB& obb) const
{
    if (_initialized)
    {
        Vec3 point;
        int plane = _clipZ ? 6 : 4;
        Vec3 obbExtentX = obb._xAxis * obb._extents.x;
        Vec3 obbExtentY = obb._yAxis * obb._extents.y;
        Vec3 obbExtentZ = obb._zAxis * obb._extents.z;
        
        for (int i = 0; i < plane; i++)
        {
            const Vec3& normal = _plane[i].getNormal();
            point = obb._center;
            point = normal.dot(obb._xAxis) > 0 ? point - obbExtentX : point + obbExtentX;
            point = normal.dot(obb._yAxis) > 0 ? point - obbExtentY : point + obbExtentY;
            point = normal.dot(obb._zAxis) > 0 ? point - obbExtentZ : point + obbExtentZ;

            if (_plane[i].getSide(point) == PointSide::FRONT_PLANE)
                return true;
        }
    }
    return  false;
}

void Frustum::createPlane(const Camera* camera)
{
    const Mat4& mat = camera->getViewProjectionMatrix();
    //ref http://www.lighthouse3d.com/tutorials/view-frustum-culling/clip-space-approach-extracting-the-planes/
    //extract frustum plane
    _plane[0].initPlane(-Vec3(mat.m[3] + mat.m[0], mat.m[7] + mat.m[4], mat.m[11] + mat.m[8]), (mat.m[15] + mat.m[12]));//left
    _plane[1].initPlane(-Vec3(mat.m[3] - mat.m[0], mat.m[7] - mat.m[4], mat.m[11] - mat.m[8]), (mat.m[15] - mat.m[12]));//right
    _plane[2].initPlane(-Vec3(mat.m[3] + mat.m[1], mat.m[7] + mat.m[5], mat.m[11] + mat.m[9]), (mat.m[15] + mat.m[13]));//bottom
    _plane[3].initPlane(-Vec3(mat.m[3] - mat.m[1], mat.m[7] - mat.m[5], mat.m[11] - mat.m[9]), (mat.m[15] - mat.m[13]));//top
    _plane[4].initPlane(-Vec3(mat.m[3] + mat.m[2], mat.m[7] + mat.m[6], mat.m[11] + mat.m[10]), (mat.m[15] + mat.m[14]));//near
    _plane[5].initPlane(-Vec3(mat.m[3] - mat.m[2], mat.m[7] - mat.m[6], mat.m[11] - mat.m[10]), (mat.m[15] - mat.m[14]));//far
}

NS_CC_END
