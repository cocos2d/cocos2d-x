/****************************************************************************
 Copyright (c) 2014-2017 Chukong Technologies Inc.
 
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

#include "3d/CCPlane.h"

NS_CC_BEGIN

Plane::Plane()
:
_normal(0.f, 0.f, 1.f),
_dist(0.f)
{
    
}

// create plane from tree point
Plane::Plane(const Vec3& p1, const Vec3& p2, const Vec3& p3)
{
    initPlane(p1, p2, p3);
}

// create plane from normal and dist
Plane::Plane(const Vec3& normal, float dist)
{
    initPlane(normal, dist);
}

// create plane from normal and a point on plane
Plane::Plane(const Vec3& normal, const Vec3& point)
{
    initPlane(normal, point);
}

void Plane::initPlane(const Vec3& p1, const Vec3& p2, const Vec3& p3)
{
    Vec3 p21 = p2 - p1;
    Vec3 p32 = p3 - p2;
    Vec3::cross(p21, p32, &_normal);
    _normal.normalize();
    _dist = _normal.dot(p1);
}

void Plane::initPlane(const Vec3& normal, float dist)
{
    float oneOverLength = 1 / normal.length();
    _normal = normal * oneOverLength;
    _dist = dist * oneOverLength;
}

void Plane::initPlane(const Vec3& normal, const Vec3& point)
{
    _normal = normal;
    _normal.normalize();
    _dist = _normal.dot(point);
}

float Plane::dist2Plane(const Vec3& p) const
{
    return _normal.dot(p) - _dist;
}


PointSide Plane::getSide(const Vec3& point) const
{
    float dist = dist2Plane(point);
    if (dist > 0)
        return PointSide::FRONT_PLANE;
    else if (dist < 0)
        return PointSide::BEHIND_PLANE;
    else
        return PointSide::IN_PLANE;
}

NS_CC_END
