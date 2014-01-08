/****************************************************************************
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

#ifndef __CC_FRUSTUM_H__
#define __CC_FRUSTUM_H__

#include "CCPlatformMacros.h"
#include "kazmath/kazmath.h"

NS_CC_BEGIN

class ViewTransform
{
public:
    ViewTransform();
    ~ViewTransform();
    void Init(const kmVec3& pos, const kmVec3& focus, const kmVec3& up);
    
    const kmVec3& getPosition() const { return _position; }
    const kmVec3& getFocus() const { return _focus; }
    const kmVec3& getDirection() const;
    const kmVec3& getRight() const;
    const kmVec3& getUp() const;
    
protected:
    void LazyAdjust() const;

    kmVec3 _position;
    kmVec3 _focus;
    kmVec3 _up;
    
    mutable bool _dirty;
    mutable kmMat4 _matrix;
    mutable kmVec3 _adjustDir;
    mutable kmVec3 _adjustRight;
    mutable kmVec3 _adjustUp;
};

class AABB
{
public:
    AABB(const kmVec3& min, const kmVec3& max);
    ~AABB();
    
    kmVec3 getCenter() const;
    
    float getDimensionX() const;
    float getDimensionY() const;
    float getDimensionZ() const;
    
    kmVec3 getPositivePoint(const kmVec3& direction) const;
    kmVec3 getNegativePoint(const kmVec3& direction) const;
    
    const AABB& expand(const kmVec3& point);

protected:
    kmVec3 _min;
    kmVec3 _max;
};

class Frustum
{
public:
    enum class IntersectResult
    {
        OUTSIDE = 0,
        INTERSECT = 1,
        INSIDE = 2
    };

    Frustum();
    ~Frustum();

    void setupProjectionOrthogonal(const ViewTransform& view, float width, float height, float near, float far);
    void setupProjectionPerspective(const ViewTransform& view, float left, float right, float top, float bottom, float near, float far);
    void setupProjectionPerspectiveFov(const ViewTransform& view, float fov, float ratio, float near, float far);
    
    void setupFromMatrix(const kmMat4& view, const kmMat4& projection);
    
    IntersectResult intersectPoint(const kmVec3& point) const;
    IntersectResult intersectAABB(const AABB& aabb) const;
    IntersectResult intersectSphere(const kmVec3& center, float radius) const;
    
protected:
    enum FrustumPlane
    {
        FRUSTUM_NEAR = 0,
        FRUSTUM_FAR = 1,
        FRUSTUM_BOTTOM = 2,
        FRUSTUM_TOP = 3,
        FRUSTUM_LEFT = 4,
        FRUSTUM_RIGHT = 5,
        FRUSTUM_NUMBER = 6
    };
    kmPlane _frustumPlanes[FrustumPlane::FRUSTUM_NUMBER];
};

NS_CC_END 

#endif