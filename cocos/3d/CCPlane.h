/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
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

#ifndef __CC_PLANE_H_
#define __CC_PLANE_H_

#include "base/ccMacros.h"
#include "math/CCMath.h"

NS_CC_BEGIN

enum class PointSide
{
    IN_PLANE,
    FRONT_PLANE,
    BEHIND_PLANE,
};

/**
 * Defines plane
 **/
class CC_DLL Plane
{
public:
    /**
    * create plane from tree point.
    */
    Plane(const Vec3& p1, const Vec3& p2, const Vec3& p3);

    /**
    * create plane from normal and dist.
    */
    Plane(const Vec3& normal, float dist);

    /**
    * create plane from normal and a point on plane.
    */
    Plane(const Vec3& normal, const Vec3& point);
    
    /**
     * create a default plan whose normal is (0, 0, 1), and _dist is 0, xoy plan in fact.
     */
    Plane();
    
    /**
    * init plane from tree point.
    */
    void initPlane(const Vec3& p1, const Vec3& p2, const Vec3& p3);

    /**
    * init plane from normal and dist.
    */
    void initPlane(const Vec3& normal, float dist);

    /**
    * init plane from normal and a point on plane.
    */
    void initPlane(const Vec3& normal, const Vec3& point);

    /**
    * dist to plane, > 0 normal direction
    */
    float dist2Plane(const Vec3& p) const;

    /**
    * Gets the plane's normal.
    */
    const Vec3& getNormal() const { return _normal; }

    /**
    * Gets the plane's distance to the origin along its normal.
    */
    float getDist() const  { return _dist; }

    /**
    * Return the side where the point is.
    */
    PointSide getSide(const Vec3& point) const;

protected:
    Vec3 _normal; // the normal line of the plane
    float _dist; // original displacement of the normal
};

NS_CC_END

#endif
