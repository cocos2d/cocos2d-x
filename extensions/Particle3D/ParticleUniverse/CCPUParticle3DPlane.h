/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
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

#ifndef __CC_PU_PARTICLE_3D_PLANE_H__
#define __CC_PU_PARTICLE_3D_PLANE_H__

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "3d/CCAABB.h"
#include <vector>

NS_CC_BEGIN
/** Defines a plane in 3D space.
    @remarks
        A plane is defined in 3D space by the equation
        Ax + By + Cz + D = 0
    @par
        This equates to a vector (the normal of the plane, whose x, y
        and z components equate to the coefficients A, B and C
        respectively), and a constant (D) which is the distance along
        the normal you have to go to move the plane back to the origin.
    */
class PUPlane
{
public:
    /** Default constructor - sets everything to 0.
    */
    PUPlane ();
    PUPlane (const PUPlane& rhs);
    /** Construct a plane through a normal, and a distance to move the plane along the normal.*/
    PUPlane (const Vec3& rkNormal, float fConstant);
	/** Construct a plane using the 4 constants directly **/
	PUPlane (float a, float b, float c, float d);
    PUPlane (const Vec3& rkNormal, const Vec3& rkPoint);
    PUPlane (const Vec3& rkPoint0, const Vec3& rkPoint1,
        const Vec3& rkPoint2);

    /** The "positive side" of the plane is the half space to which the
        plane normal points. The "negative side" is the other half
        space. The flag "no side" indicates the plane itself.
    */
    enum Side
    {
        NO_SIDE,
        POSITIVE_SIDE,
        NEGATIVE_SIDE,
        BOTH_SIDE
    };

    //Side getSide (const Vec3& rkPoint) const;

    ///**
    //Returns the side where the alignedBox is. The flag BOTH_SIDE indicates an intersecting box.
    //One corner ON the plane is sufficient to consider the box and the plane intersecting.
    //*/
    //Side getSide (const AABB& rkBox) const;

    ///** Returns which side of the plane that the given box lies on.
    //    The box is defined as centre/half-size pairs for effectively.
    //@param centre The centre of the box.
    //@param halfSize The half-size of the box.
    //@return
    //    POSITIVE_SIDE if the box complete lies on the "positive side" of the plane,
    //    NEGATIVE_SIDE if the box complete lies on the "negative side" of the plane,
    //    and BOTH_SIDE if the box intersects the plane.
    //*/
    //Side getSide (const Vec3& centre, const Vec3& halfSize) const;

    /** This is a pseudodistance. The sign of the return value is
        positive if the point is on the positive side of the plane,
        negative if the point is on the negative side, and zero if the
        point is on the plane.
        @par
        The absolute value of the return value is the true distance only
        when the plane normal is a unit length vector.
    */
    float getDistance (const Vec3& rkPoint) const;

    /** Redefine this plane based on 3 points. */
    void redefine(const Vec3& rkPoint0, const Vec3& rkPoint1,
        const Vec3& rkPoint2);

	/** Redefine this plane based on a normal and a point. */
	void redefine(const Vec3& rkNormal, const Vec3& rkPoint);

	/** Project a vector onto the plane. 
	@remarks This gives you the element of the input vector that is perpendicular 
		to the normal of the plane. You can get the element which is parallel
		to the normal of the plane by subtracting the result of this method
		from the original vector, since parallel + perpendicular = original.
	@param v The input vector
	*/
	Vec3 projectVector(const Vec3& v) const;

    /** Normalises the plane.
        @remarks
            This method normalises the plane's normal and the length scale of d
            is as well.
        @note
            This function will not crash for zero-sized vectors, but there
            will be no changes made to their components.
        @return The previous length of the plane's normal.
    */
    float normalize(void);

	Vec3 normal;
    float d;

    /// Comparison operator
    bool operator==(const PUPlane& rhs) const
    {
        return (rhs.d == d && rhs.normal == normal);
    }
    bool operator!=(const PUPlane& rhs) const
    {
        return (rhs.d != d || rhs.normal != normal);
    }
};

typedef std::vector<PUPlane> PlaneList;
NS_CC_END

#endif
