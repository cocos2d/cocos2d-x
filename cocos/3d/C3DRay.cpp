#include "Base.h"
#include "C3DRay.h"

#include "C3DAABB.h"
#include "C3DOBB.h"
#include "C3DCone.h"
#include "C3DCylinder.h"
#include "C3DPlane.h"

namespace cocos3d
{

C3DRay::C3DRay()
    : _direction(0, 0, 1)
{
}

C3DRay::C3DRay(const C3DVector3& origin, const C3DVector3& direction)
{
    set(origin, direction);
}



C3DRay::~C3DRay()
{
}

const C3DVector3& C3DRay::getOrigin() const
{
    return _origin;
}

void C3DRay::setOrigin(const C3DVector3& origin)
{
    _origin = origin;
}

const C3DVector3& C3DRay::getDirection() const
{
    return _direction;
}

void C3DRay::setDirection(const C3DVector3& direction)
{
    _direction = direction;
    normalize();
}

bool C3DRay::intersects(const C3DOBB* obb) const
{
    C3DAABB box;
    box._min = - obb->extents;
    box._max = obb->extents;
    
    C3DRay ray;
    ray._direction = _direction;
    ray._origin = _origin;
    
    C3DMatrix mat = C3DMatrix::identity();
    mat.m[0] = obb->xAxis.x;
    mat.m[1] = obb->xAxis.y;
    mat.m[2] = obb->xAxis.z;
    
    mat.m[4] = obb->yAxis.x;
    mat.m[5] = obb->yAxis.y;
    mat.m[6] = obb->yAxis.z;
    
    mat.m[8] = obb->zAxis.x;
    mat.m[9] = obb->zAxis.y;
    mat.m[10] = obb->zAxis.z;
    
    mat.m[12] = obb->center.x;
    mat.m[13] = obb->center.y;
    mat.m[14] = obb->center.z;
    
    mat.invertOrthMat();
    
    ray.transform(mat);
    
    return ray.intersects(&box);
}

bool C3DRay::intersects( const C3DAABB* box ) const
{
	C3DVector3 ptOnPlane;
	C3DVector3 min = box->_min;
	C3DVector3 max = box->_max;

	const C3DVector3& origin = getOrigin();
    const C3DVector3& dir = getDirection();
	
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

//INLINE
//Vector3 PlaneEq::intersectRay( const Vector3 & source,
//	const Vector3 & dir ) const
//{
//	return source +
//		this->intersectRayHalf( source, normal_.dotProduct( dir ) ) * dir;
//}
//
float C3DRay::dist(const C3DPlane* plane) const
{
	float ndd = C3DVector3::dot(plane->getNormal(),this->getDirection());
	if(ndd == 0)
		return 0.0f;
	float ndo = C3DVector3::dot(plane->getNormal(),this->getOrigin());
	return (plane->getDist() - ndo) / ndd;
}

C3DVector3 C3DRay::intersects(const C3DPlane* plane) const
{
	return this->getOrigin() + this->dist(plane) * this->getDirection();
}
//
//float C3DRay::intersects(const C3DPlane* plane) const
//{
//	if (!plane)	return 0.f;
//
//	const C3DVector3& normal = plane->getNormal();
//	// If the origin of the ray is on the plane then the distance is zero.
//	float alpha = (normal.dot(_origin) + plane->getDist());
//	if (fabs(alpha) < MATH_EPSILON)
//	{
//		return 0.0f;
//	}
//
//	float dot = normal.dot(_direction);
//
//	// If the dot product of the plane's normal and this ray's direction is zero,
//	// then the ray is parallel to the plane and does not intersect it.
//	if (dot == 0.0f)
//	{
//		return INTERSECTS_NONE;
//	}
//
//	// Calculate the distance along the ray's direction vector to the point where
//	// the ray intersects the plane (if it is negative the plane is behind the ray).
//	float d = -alpha / dot;
//	if (d < 0.0f)
//	{
//		return INTERSECTS_NONE;
//	}
//	return d;
//}

bool C3DRay::intersects(const C3DCone* cone) const
{
	if (!cone)
		return false;

	return cone->Intersect(this);
}

bool C3DRay::intersects(const C3DCylinder* pCylinder) const
{
	if (!pCylinder)
		return false;

	return pCylinder->Intersect(this);
}

void C3DRay::set(const C3DVector3& origin, const C3DVector3& direction)
{
    _origin = origin;
    _direction = direction;
    normalize();
}

void C3DRay::set(const C3DRay& ray)
{
    _origin = ray._origin;
    _direction = ray._direction;
    normalize();
}

void C3DRay::transform(const C3DMatrix& matrix)
{
    matrix.transformPoint(&_origin);
    matrix.transformVector(&_direction);
    _direction.normalize();
}

void C3DRay::normalize()
{
    if (_direction.isZero())
    {       
        return;
    }

    // Normalize the ray's direction vector.
    float normalizeFactor = 1.0f / sqrt(_direction.x * _direction.x + _direction.y * _direction.y + _direction.z * _direction.z);
    if (normalizeFactor != 1.0f)
    {
        _direction.x *= normalizeFactor;
        _direction.y *= normalizeFactor;
        _direction.z *= normalizeFactor;
    }
}

}
