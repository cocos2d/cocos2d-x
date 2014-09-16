/****************************************************************************
Copyright (c) Chukong Technologies Inc.

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

#include "3d/CCRay.h"

NS_CC_BEGIN

Ray::Ray()
: _direction(0, 0, 1)
{
}

Ray::Ray(const Vec3& origin, const Vec3& direction)
{
    set(origin, direction);
}

Ray::~Ray()
{
}

bool Ray::intersects(const AABB& aabb) const
{
    Vec3 ptOnPlane;
    Vec3 min = aabb._min;
    Vec3 max = aabb._max;
    
    const Vec3& origin = _origin;
    const Vec3& dir = _direction;
    
    float t;
    
    if (dir.x != 0.f)
    {
        if (dir.x > 0)
            t = (min.x - origin.x) / dir.x;
        else
            t = (max.x - origin.x) / dir.x;
        
        if (t > 0.f)
        {
            ptOnPlane = origin + t * dir;

            if (min.y < ptOnPlane.y && ptOnPlane.y < max.y && min.z < ptOnPlane.z && ptOnPlane.z < max.z)
            {
                return true;
            }
        }
    }
    
    if (dir.y != 0.f)
    {
        if (dir.y > 0)
            t = (min.y - origin.y) / dir.y;
        else
            t = (max.y - origin.y) / dir.y;
        
        if (t > 0.f)
        {
            ptOnPlane = origin + t * dir;

            if (min.z < ptOnPlane.z && ptOnPlane.z < max.z && min.x < ptOnPlane.x && ptOnPlane.x < max.x)
            {
                return true;
            }
        }
    }
    
	if (dir.z != 0.f)
	{
        if (dir.z > 0)
            t = (min.z - origin.z) / dir.z;
        else
            t = (max.z - origin.z) / dir.z;
        
        if (t > 0.f)
        {
            ptOnPlane = origin + t * dir;
            
            if (min.x < ptOnPlane.x && ptOnPlane.x < max.x && min.y < ptOnPlane.y && ptOnPlane.y < max.y)
            {
                return true;
            }
        }
    }
    
    return false;
}

bool Ray::intersects(const OBB& obb) const
{
    AABB aabb;
    aabb._min = - obb._extents;
    aabb._max = obb._extents;

    Ray ray;
    ray._direction = _direction;
    ray._origin = _origin;

    Mat4 mat = Mat4::IDENTITY;
    mat.m[0] = obb._xAxis.x;
    mat.m[1] = obb._xAxis.y;
    mat.m[2] = obb._xAxis.z;

    mat.m[4] = obb._yAxis.x;
    mat.m[5] = obb._yAxis.y;
    mat.m[6] = obb._yAxis.z;

    mat.m[8] = obb._zAxis.x;
    mat.m[9] = obb._zAxis.y;
    mat.m[10] = obb._zAxis.z;

    mat.m[12] = obb._center.x;
    mat.m[13] = obb._center.y;
    mat.m[14] = obb._center.z;

    mat = mat.getInversed();

    ray.transform(mat);

    return ray.intersects(aabb);
}

void Ray::set(const Vec3& origin, const Vec3& direction)
{
    _origin = origin;
    _direction = direction;
}

void Ray::transform(const Mat4& matrix)
{
    matrix.transformPoint(&_origin);
    matrix.transformVector(&_direction);
    _direction.normalize();
}

NS_CC_END
