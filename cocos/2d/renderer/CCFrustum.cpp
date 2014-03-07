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

#include "renderer/CCFrustum.h"
#include "CCConsole.h"

#include <stdlib.h>

NS_CC_BEGIN

ViewTransform::ViewTransform()
{
    kmVec3Fill(&_position,0,0,0);
    kmVec3Fill(&_focus,0,0,-1);
    kmVec3Fill(&_up,0,1,0);
    _dirty = true;
    kmMat4Identity(&_matrix);
}

ViewTransform::~ViewTransform()
{
}

void ViewTransform::Init(const kmVec3 &pos, const kmVec3 &focus, const kmVec3 &up)
{
    _position = pos;
    _focus = focus;
    _up = up;
    _dirty = true;
}

void ViewTransform::LazyAdjust() const
{
    if(!_dirty) return;
    kmVec3Subtract(&_adjustDir, &_focus, &_position);
    kmVec3Normalize(&_adjustDir, &_adjustDir);
    
    kmVec3Cross(&_adjustRight, &_adjustDir, &_up);
    kmVec3Normalize(&_adjustRight, &_adjustRight);
    
    kmVec3Cross(&_adjustUp, &_adjustRight, &_adjustDir);
    kmVec3Normalize(&_adjustUp, &_adjustUp);
    
    _dirty = false;
}

const kmVec3& ViewTransform::getDirection() const
{
    LazyAdjust();
    return _adjustDir;
}

const kmVec3& ViewTransform::getRight() const
{
    LazyAdjust();
    return _adjustRight;
}

const kmVec3& ViewTransform::getUp() const
{
    LazyAdjust();
    return _adjustUp;
}

AABB::AABB(const kmVec3& min, const kmVec3& max)
{
    _min = min;
    _max = max;
    if(_min.x > _max.x)
    {
        CCLOG("_min.x is greater than _max.x, it will be swapped!");
        float temp = _min.x; _min.x = _max.x; _max.x = temp;
    }
    if(_min.y > _max.y)
    {
        CCLOG("_min.y is greater than _max.y, it will be swapped!");
        float temp = _min.y; _min.y = _max.y; _max.y = temp;
    }
    if(_min.z > _max.z)
    {
        CCLOG("_min.z is greater than _max.z, it will be swapped!");
        float temp = _min.z; _min.z = _max.z; _max.z = temp;
    }
}

AABB::~AABB()
{
}

kmVec3 AABB::getCenter() const
{
    kmVec3 result;
    
    kmVec3Add(&result, &_min, &_max);
    kmVec3Scale(&result, &result, 0.5f);
    return result;
}

float AABB::getDimensionX() const
{
    return _max.x - _min.x;
}

float AABB::getDimensionY() const
{
    return _max.y - _min.y;
}

float AABB::getDimensionZ() const
{
    return _max.z - _min.z;
}

kmVec3 AABB::getPositivePoint(const kmVec3& direction) const
{
    kmVec3 result = _max;
    if( direction.x < 0 ) result.x = _min.x;
    if( direction.y < 0 ) result.y = _min.y;
    if( direction.z < 0 ) result.z = _min.z;
    
    return result;
}

const AABB& AABB::expand(const kmVec3& point)
{
    if(point.x > _max.x) _max.x = point.x;
    if(point.y > _max.y) _max.y = point.y;
    if(point.z > _max.z) _max.z = point.z;

    if(point.x < _min.x) _min.x = point.x;
    if(point.y < _min.y) _min.y = point.y;
    if(point.z < _min.z) _min.z = point.z;
    
    return *this;
}

kmVec3 AABB::getNegativePoint(const kmVec3& direction) const
{
    kmVec3 result = _min;
    if( direction.x < 0 ) result.x = _max.x;
    if( direction.y < 0 ) result.y = _max.y;
    if( direction.z < 0 ) result.z = _max.z;
    
    return result;
}

Frustum::Frustum()
{
}

Frustum::~Frustum()
{
}

void Frustum::setupProjectionOrthogonal(const cocos2d::ViewTransform &view, float width, float height, float nearPlane, float farPlane)
{
    kmVec3 cc = view.getPosition();
    kmVec3 cDir = view.getDirection();
    kmVec3 cRight = view.getRight();
    kmVec3 cUp = view.getUp();
    
    kmVec3Normalize(&cDir, &cDir);
    kmVec3Normalize(&cRight, &cRight);
    kmVec3Normalize(&cUp, &cUp);
    
    //near
    {
        kmVec3 point;
        kmVec3 normal;
        normal = cDir;
        kmVec3Scale(&point, &cDir, nearPlane);
        kmVec3Add(&point, &point, &cc);
        kmPlaneFromPointAndNormal(&_frustumPlanes[FrustumPlane::FRUSTUM_NEAR], &point, &normal);
    }
    
    //far
    {
        kmVec3 point;
        kmVec3 normal;
        kmVec3Scale(&normal, &cDir, -1);
        kmVec3Scale(&point, &cDir, farPlane);
        kmVec3Add(&point, &point, &cc);
        kmPlaneFromPointAndNormal(&_frustumPlanes[FrustumPlane::FRUSTUM_FAR], &point, &normal);
    }
    
    //left
    {
        kmVec3 point;
        kmVec3 normal;
        normal = cRight;
        kmVec3Scale(&point, &cRight, -width * 0.5);
        kmVec3Add(&point, &point, &cc);
        kmPlaneFromPointAndNormal(&_frustumPlanes[FrustumPlane::FRUSTUM_LEFT], &point, &normal);
    }
    
    //right
    {
        kmVec3 point;
        kmVec3 normal;
        kmVec3Scale(&normal, &cRight, -1);
        kmVec3Scale(&point, &cRight, width * 0.5);
        kmVec3Add(&point, &point, &cc);
        kmPlaneFromPointAndNormal(&_frustumPlanes[FrustumPlane::FRUSTUM_RIGHT], &point, &normal);
    }
    
    //bottom
    {
        kmVec3 point;
        kmVec3 normal;
        normal = cUp;
        kmVec3Scale(&point, &cUp, -height * 0.5);
        kmVec3Add(&point, &point, &cc);
        kmPlaneFromPointAndNormal(&_frustumPlanes[FrustumPlane::FRUSTUM_BOTTOM], &point, &normal);
    }
    
    //top
    {
        kmVec3 point;
        kmVec3 normal;
        kmVec3Scale(&normal, &cUp, -1);
        kmVec3Scale(&point, &cUp, height * 0.5);
        kmVec3Add(&point, &point, &cc);
        kmPlaneFromPointAndNormal(&_frustumPlanes[FrustumPlane::FRUSTUM_TOP], &point, &normal);
    }
}

void Frustum::setupProjectionPerspective(const ViewTransform& view, float left, float right, float top, float bottom, float nearPlane, float farPlane)
{
    kmVec3 cc = view.getPosition();
    kmVec3 cDir = view.getDirection();
    kmVec3 cRight = view.getRight();
    kmVec3 cUp = view.getUp();
    
    kmVec3Normalize(&cDir, &cDir);
    kmVec3Normalize(&cRight, &cRight);
    kmVec3Normalize(&cUp, &cUp);
    
    kmVec3 nearCenter;
    kmVec3 farCenter;
    
    kmVec3Scale(&nearCenter, &cDir, nearPlane);
    kmVec3Add(&nearCenter, &nearCenter, &cc);
    
    kmVec3Scale(&farCenter, &cDir, farPlane);
    kmVec3Add(&farCenter, &farCenter, &cc);
    
    //near
    {
        kmPlaneFromPointAndNormal(&_frustumPlanes[FrustumPlane::FRUSTUM_NEAR], &nearCenter, &cDir);
    }
    
    //far
    {
        kmVec3 normal;
        kmVec3Scale(&normal, &cDir, -1);
        kmPlaneFromPointAndNormal(&_frustumPlanes[FrustumPlane::FRUSTUM_FAR], &farCenter, &normal);
    }
    
    //left
    {
        kmVec3 point;
        kmVec3Scale(&point, &cRight, left);
        kmVec3Add(&point, &point, &nearCenter);
        
        kmVec3 normal;
        kmVec3Subtract(&normal, &point, &cc);
        kmVec3Cross(&normal, &normal, &cUp);
        kmVec3Normalize(&normal, &normal);
        
        kmPlaneFromPointAndNormal(&_frustumPlanes[FrustumPlane::FRUSTUM_LEFT], &point, &normal);
    }
    
    //right
    {
        kmVec3 point;
        kmVec3Scale(&point, &cRight, right);
        kmVec3Add(&point, &point, &nearCenter);
        
        kmVec3 normal;
        kmVec3Subtract(&normal, &point, &cc);
        kmVec3Cross(&normal, &cUp, &normal);
        kmVec3Normalize(&normal, &normal);
        
        kmPlaneFromPointAndNormal(&_frustumPlanes[FrustumPlane::FRUSTUM_RIGHT], &point, &normal);
    }
    
    //bottom
    {
        kmVec3 point;
        kmVec3Scale(&point, &cUp, bottom);
        kmVec3Add(&point, &point, &nearCenter);
        
        kmVec3 normal;
        kmVec3Subtract(&normal, &point, &cc);
        kmVec3Cross(&normal, &cRight, &normal);
        kmVec3Normalize(&normal, &normal);
        
        kmPlaneFromPointAndNormal(&_frustumPlanes[FrustumPlane::FRUSTUM_BOTTOM], &point, &normal);
    }
    
    //top
    {
        kmVec3 point;
        kmVec3Scale(&point, &cUp, top);
        kmVec3Add(&point, &point, &nearCenter);
        
        kmVec3 normal;
        kmVec3Subtract(&normal, &point, &cc);
        kmVec3Cross(&normal, &normal, &cRight);
        kmVec3Normalize(&normal, &normal);
        
        kmPlaneFromPointAndNormal(&_frustumPlanes[FrustumPlane::FRUSTUM_TOP], &point, &normal);
    }
    
}

void Frustum::setupProjectionPerspectiveFov(const ViewTransform& view, float fov, float ratio, float nearPlane, float farPlane)
{
    float width = 2 * nearPlane * tan(fov * 0.5);
    float height = width/ratio;
    setupProjectionPerspective(view, -width/2, width/2, height/2, -height/2, nearPlane, farPlane);
}

void Frustum::setupFromMatrix(const kmMat4 &view, const kmMat4 &projection)
{
    kmMat4 mvp;
    kmMat4Multiply(&mvp, &projection, &view);
    
    kmMat4ExtractPlane(&_frustumPlanes[FrustumPlane::FRUSTUM_NEAR], &mvp, KM_PLANE_NEAR);
    kmMat4ExtractPlane(&_frustumPlanes[FrustumPlane::FRUSTUM_FAR], &mvp, KM_PLANE_FAR);
    kmMat4ExtractPlane(&_frustumPlanes[FrustumPlane::FRUSTUM_LEFT], &mvp, KM_PLANE_LEFT);
    kmMat4ExtractPlane(&_frustumPlanes[FrustumPlane::FRUSTUM_RIGHT], &mvp, KM_PLANE_RIGHT);
    kmMat4ExtractPlane(&_frustumPlanes[FrustumPlane::FRUSTUM_BOTTOM], &mvp, KM_PLANE_BOTTOM);
    kmMat4ExtractPlane(&_frustumPlanes[FrustumPlane::FRUSTUM_TOP], &mvp, KM_PLANE_TOP);
}

Frustum::IntersectResult Frustum::intersectPoint(const kmVec3 &point) const
{
    int indexFirst = static_cast<int>(FrustumPlane::FRUSTUM_NEAR);
    int indexNumber = static_cast<int>(FrustumPlane::FRUSTUM_NUMBER);
    
    for(int planeIndex = indexFirst; planeIndex < indexNumber; ++planeIndex)
    {
        if(kmPlaneDotCoord(&_frustumPlanes[static_cast<FrustumPlane>(planeIndex)], &point) < 0)
            return IntersectResult::OUTSIDE;
    }
    return IntersectResult::INSIDE;
}

Frustum::IntersectResult Frustum::intersectAABB(const AABB& aabb) const
{
    IntersectResult result = IntersectResult::INSIDE;
    int indexFirst = static_cast<int>(FrustumPlane::FRUSTUM_NEAR);
    int indexNumber = static_cast<int>(FrustumPlane::FRUSTUM_NUMBER);
    
    for(int planeIndex = indexFirst; planeIndex < indexNumber; ++planeIndex)
    {
        kmPlane plane = _frustumPlanes[static_cast<FrustumPlane>(planeIndex)];
        kmVec3 normal = {plane.a, plane.b, plane.c};
        kmVec3Normalize(&normal, &normal);
        kmVec3 positivePoint = aabb.getPositivePoint(normal);
        kmVec3 negativePoint = aabb.getNegativePoint(normal);
        
        if(kmPlaneDotCoord(&plane, &positivePoint) < 0)
            return IntersectResult::OUTSIDE;
        if(kmPlaneDotCoord(&plane, &negativePoint) < 0)
            result = IntersectResult::INTERSECT;
    }
    
    return result;
}

Frustum::IntersectResult Frustum::intersectSphere(const kmVec3& center, float radius) const
{
    IntersectResult result = IntersectResult::INSIDE;
    int indexFirst = static_cast<int>(FrustumPlane::FRUSTUM_NEAR);
    int indexNumber = static_cast<int>(FrustumPlane::FRUSTUM_NUMBER);
    
    for(int planeIndex = indexFirst; planeIndex < indexNumber; ++planeIndex)
    {
        kmPlane plane = _frustumPlanes[static_cast<FrustumPlane>(planeIndex)];
        kmVec3 normal = {plane.a, plane.b, plane.c};
        
        float distance = kmPlaneDotCoord(&plane, &center);
        distance = distance / kmVec3Length(&normal);
        
        if(distance < -radius) return IntersectResult::OUTSIDE;
        if(distance <= radius && distance >= -radius) result = IntersectResult::INTERSECT;
    }
    
    return result;
}

NS_CC_END
