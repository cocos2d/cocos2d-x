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

bool Ray::intersects(const AABB& box, float* distance) const
{
    float lowt = 0.0f;
    float t;
    bool hit = false;
    Vec3 hitpoint;
    const Vec3& min = box._min;
    const Vec3& max = box._max;
    const Vec3& rayorig = _origin;
    const Vec3& raydir = _direction;
    
    // Check origin inside first
    if (rayorig > min && rayorig < max)
        return true;
    
    // Check each face in turn, only check closest 3
    // Min x
    if (rayorig.x <= min.x && raydir.x > 0)
    {
        t = (min.x - rayorig.x) / raydir.x;
        if (t >= 0)
        {
            // Substitute t back into ray and check bounds and dist
            hitpoint = rayorig + raydir * t;
            if (hitpoint.y >= min.y && hitpoint.y <= max.y &&
                hitpoint.z >= min.z && hitpoint.z <= max.z &&
                (!hit || t < lowt))
            {
                hit = true;
                lowt = t;
            }
        }
    }
    // Max x
    if (rayorig.x >= max.x && raydir.x < 0)
    {
        t = (max.x - rayorig.x) / raydir.x;
        if (t >= 0)
        {
            // Substitute t back into ray and check bounds and dist
            hitpoint = rayorig + raydir * t;
            if (hitpoint.y >= min.y && hitpoint.y <= max.y &&
                hitpoint.z >= min.z && hitpoint.z <= max.z &&
                (!hit || t < lowt))
            {
                hit = true;
                lowt = t;
            }
        }
    }
    // Min y
    if (rayorig.y <= min.y && raydir.y > 0)
    {
        t = (min.y - rayorig.y) / raydir.y;
        if (t >= 0)
        {
            // Substitute t back into ray and check bounds and dist
            hitpoint = rayorig + raydir * t;
            if (hitpoint.x >= min.x && hitpoint.x <= max.x &&
                hitpoint.z >= min.z && hitpoint.z <= max.z &&
                (!hit || t < lowt))
            {
                hit = true;
                lowt = t;
            }
        }
    }
    // Max y
    if (rayorig.y >= max.y && raydir.y < 0)
    {
        t = (max.y - rayorig.y) / raydir.y;
        if
            
            
            (t >= 0)
        {
            // Substitute t back into ray and check bounds and dist
            hitpoint = rayorig + raydir * t;
            if (hitpoint.x >= min.x && hitpoint.x <= max.x &&
                hitpoint.z >= min.z && hitpoint.z <= max.z &&
                (!hit || t < lowt))
            {
                hit = true;
                lowt = t;
            }
        }
    }
    // Min z
    if (rayorig.z <= min.z && raydir.z > 0)
    {
        t = (min.z - rayorig.z) / raydir.z;
        if (t >= 0)
        {
            // Substitute t back into ray and check bounds and dist
            hitpoint = rayorig + raydir * t;
            if (hitpoint.x >= min.x && hitpoint.x <= max.x &&
                hitpoint.y >= min.y && hitpoint.y <= max.y &&
                (!hit || t < lowt))
            {
                hit = true;
                lowt = t;
            }
        }
    }
    // Max z
    if (rayorig.z >= max.z && raydir.z < 0)
    {
        t = (max.z - rayorig.z) / raydir.z;
        if (t >= 0)
        {
            // Substitute t back into ray and check bounds and dist
            hitpoint = rayorig + raydir * t;
            if (hitpoint.x >= min.x && hitpoint.x <= max.x &&
                hitpoint.y >= min.y && hitpoint.y <= max.y &&
                (!hit || t < lowt))
            {
                hit = true;
                lowt = t;
            }
        }
    }
    
    if (distance)
        *distance = lowt;
    
    return hit;
}

bool Ray::intersects(const OBB& obb, float* distance) const
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
    
    return ray.intersects(aabb, distance);
    
}

float Ray::dist(const Plane& plane) const
{
    float ndd = Vec3::dot(plane.getNormal(), _direction);
    if(ndd == 0)
        return 0.0f;
    float ndo = Vec3::dot(plane.getNormal(), _origin);
    return (plane.getDist() - ndo) / ndd;
}

Vec3 Ray::intersects(const Plane& plane) const
{
    float dis = this->dist(plane);
    return _origin + dis * _direction;
}

void Ray::set(const Vec3& origin, const Vec3& direction)
{
    _origin = origin;
    _direction = direction;
    _direction.normalize();
}

void Ray::transform(const Mat4& matrix)
{
    matrix.transformPoint(&_origin);
    matrix.transformVector(&_direction);
    _direction.normalize();
}

NS_CC_END
