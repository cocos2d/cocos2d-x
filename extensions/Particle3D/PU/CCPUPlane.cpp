/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "CCPUPlane.h"

NS_CC_BEGIN
//-----------------------------------------------------------------------
PUPlane::PUPlane ()
{
    // Vec3 default constructor zero
	//normal = Vec3::ZERO;
	d = 0.0;
}
//-----------------------------------------------------------------------
PUPlane::PUPlane (const PUPlane& rhs)
{
	normal = rhs.normal;
	d = rhs.d;
}
//-----------------------------------------------------------------------
PUPlane::PUPlane (const Vec3& rkNormal, float fConstant)
{
	normal = rkNormal;
	d = -fConstant;
}
//---------------------------------------------------------------------
PUPlane::PUPlane (float a, float b, float c, float _d)
	: normal(a, b, c), d(_d)
{
}
//-----------------------------------------------------------------------
PUPlane::PUPlane (const Vec3& rkNormal, const Vec3& rkPoint)
{
	redefine(rkNormal, rkPoint);
}
//-----------------------------------------------------------------------
PUPlane::PUPlane (const Vec3& rkPoint0, const Vec3& rkPoint1,
			  const Vec3& rkPoint2)
{
	redefine(rkPoint0, rkPoint1, rkPoint2);
}
//-----------------------------------------------------------------------
float PUPlane::getDistance (const Vec3& rkPoint) const
{
	return normal.dot(rkPoint) + d;
}
//-----------------------------------------------------------------------
//Plane::Side Plane::getSide (const Vec3& rkPoint) const
//{
//	float fDistance = getDistance(rkPoint);
//
//	if ( fDistance < 0.0 )
//		return Plane::NEGATIVE_SIDE;
//
//	if ( fDistance > 0.0 )
//		return Plane::POSITIVE_SIDE;
//
//	return Plane::NO_SIDE;
//}
//
//
////-----------------------------------------------------------------------
//Plane::Side Plane::getSide (const AABB& box) const
//{
//	if (box.isEmpty()) 
//		return NO_SIDE;
//	if (box.isInfinite())
//		return BOTH_SIDE;
//
//	return getSide(box.getCenter(), box);
//}
////-----------------------------------------------------------------------
//Plane::Side Plane::getSide (const Vec3& centre, const Vec3& halfSize) const
//{
//	// Calculate the distance between box centre and the plane
//	float dist = getDistance(centre);
//
//	// Calculate the maximise allows absolute distance for
//	// the distance between box centre and plane
//	float maxAbsDist = normal.absDotProduct(halfSize);
//
//	if (dist < -maxAbsDist)
//		return Plane::NEGATIVE_SIDE;
//
//	if (dist > +maxAbsDist)
//		return Plane::POSITIVE_SIDE;
//
//	return Plane::BOTH_SIDE;
//}
//-----------------------------------------------------------------------
void PUPlane::redefine(const Vec3& rkPoint0, const Vec3& rkPoint1,
					 const Vec3& rkPoint2)
{
	Vec3 kEdge1 = rkPoint1 - rkPoint0;
	Vec3 kEdge2 = rkPoint2 - rkPoint0;
	Vec3::cross(kEdge1, kEdge2, &normal);
	normal.normalize();
	d = -normal.dot(rkPoint0);
}
//-----------------------------------------------------------------------
void PUPlane::redefine(const Vec3& rkNormal, const Vec3& rkPoint)
{
	normal = rkNormal;
	d = -rkNormal.dot(rkPoint);
}
//-----------------------------------------------------------------------
Vec3 PUPlane::projectVector(const Vec3& p) const
{
	// We know plane normal is unit length, so use simple method
	//Matrix3 xform;
	//xform[0][0] = 1.0f - normal.x * normal.x;
	//xform[0][1] = -normal.x * normal.y;
	//xform[0][2] = -normal.x * normal.z;
	//xform[1][0] = -normal.y * normal.x;
	//xform[1][1] = 1.0f - normal.y * normal.y;
	//xform[1][2] = -normal.y * normal.z;
	//xform[2][0] = -normal.z * normal.x;
	//xform[2][1] = -normal.z * normal.y;
	//xform[2][2] = 1.0f - normal.z * normal.z;

	Mat4 xform;
	xform.m[0] = 1.0f - normal.x * normal.x;
	xform.m[1] = -normal.x * normal.y;
	xform.m[2] = -normal.x * normal.z;
	xform.m[4] = -normal.y * normal.x;
	xform.m[5] = 1.0f - normal.y * normal.y;
	xform.m[6] = -normal.y * normal.z;
	xform.m[8] = -normal.z * normal.x;
	xform.m[9] = -normal.z * normal.y;
	xform.m[10] = 1.0f - normal.z * normal.z;
	return xform * p;

}
//-----------------------------------------------------------------------
float PUPlane::normalize()
{
	float fLength = normal.length();

	// Will also work for zero-sized vectors, but will change nothing
	// We're not using epsilons because we don't need to.
	// Read http://www.ogre3d.org/forums/viewtopic.php?f=4&t=61259
	if ( fLength > float(0.0f) )
	{
		float fInvLength = 1.0f / fLength;
		normal *= fInvLength;
		d *= fInvLength;
	}

	return fLength;
}
NS_CC_END
