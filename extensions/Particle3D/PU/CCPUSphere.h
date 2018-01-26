/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2017 Chukong Technologies Inc.
 
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

#ifndef __CC_PU_PARTICLE_3D_SPHERE_H__
#define __CC_PU_PARTICLE_3D_SPHERE_H__

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "3d/CCAABB.h"
#include <vector>

NS_CC_BEGIN
/** A sphere primitive, mostly used for bounds checking. 
@remarks
    A sphere in math texts is normally represented by the function
    x^2 + y^2 + z^2 = r^2 (for sphere's centered on the origin). Ogre stores spheres
    simply as a center point and a radius.
*/
class PUSphere
{
protected:
    float _radius;
    Vec3 _center;
public:
    /** Standard constructor - creates a unit sphere around the origin.*/
    PUSphere();
    /** Constructor allowing arbitrary spheres. 
        @param center The center point of the sphere.
        @param radius The radius of the sphere.
    */
    PUSphere(const Vec3& center, float radius);

    /** Returns the radius of the sphere. */
    float getRadius(void) const { return _radius; }

    /** Sets the radius of the sphere. */
    void setRadius(float radius) { _radius = radius; }

    /** Returns the center point of the sphere. */
    const Vec3& getCenter(void) const { return _center; }

    /** Sets the center point of the sphere. */
    void setCenter(const Vec3& center) { _center = center; }

    /** Returns whether or not this sphere intersects another sphere. */
    bool intersects(const PUSphere& s) const
    {
        return (s._center - _center).lengthSquared() <= (s._radius + _radius) * (s._radius + _radius);
    }
    ///** Returns whether or not this sphere intersects a box. */
    //bool intersects(const AABB& box) const
    //{
    //	return Math::intersects(*this, box);
    //}
    /** Returns whether or not this sphere intersects a plane. */
    //bool intersects(const Plane& plane) const
    //{
    //	return Math::intersects(*this, plane);
    //}
    /** Returns whether or not this sphere intersects a point. */
    bool intersects(const Vec3& v) const
    {
        return ((v - _center).lengthSquared() <= _radius * _radius);
    }
    /** Merges another Sphere into the current sphere */
    void merge(const PUSphere& oth);
        

};
NS_CC_END

#endif
