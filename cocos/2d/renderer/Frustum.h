#ifndef __CC_FRUSTUM_H__
#define __CC_FRUSTUM_H__

#include "CCPlatformMacros.h"
#include "math/kazmath/include/kazmath/kazmath.h"

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
    
private:
    void LazyAdjust() const;
private:
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
private:
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
public:
    Frustum();
    ~Frustum();

    void setupProjectionOrthogonal(const ViewTransform& view, float width, float height, float near, float far);
    void setupProjectionPerspective(const ViewTransform& view, float left, float right, float top, float bottom, float near, float far);
    void setupProjectionPerspectiveFov(const ViewTransform& view, float fov, float ratio, float near, float far);
    
    void setupFromMatrix(const kmMat4& view, const kmMat4& projection);
    
    IntersectResult intersectPoint(const kmVec3& point) const;
    IntersectResult intersectAABB(const AABB& aabb) const;
    IntersectResult intersectSphere(const kmVec3& center, float radius) const;
    
private:
    enum FrustumPlane
    {
        NEAR = 0,
        FAR = 1,
        BOTTOM = 2,
        TOP = 3,
        LEFT = 4,
        RIGHT = 5,
        NUMBER = 6
    };
    kmPlane _frustumPlanes[FrustumPlane::NUMBER];
};

NS_CC_END 

#endif