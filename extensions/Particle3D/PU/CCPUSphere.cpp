/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
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

#include "CCPUSphere.h"

NS_CC_BEGIN

PUSphere::PUSphere()
 : _radius(1.0)
{

}

PUSphere::PUSphere( const Vec3& center, float radius )
: _radius(radius)
, _center(center)
{

}

void PUSphere::merge( const PUSphere& oth )
{
    Vec3 diff =  oth.getCenter() - _center;
    float lengthSq = diff.lengthSquared();
    float radiusDiff = oth.getRadius() - _radius;

    // Early-out
    if ((radiusDiff * radiusDiff) >= lengthSq) 
    {
        // One fully contains the other
        if (radiusDiff <= 0.0f) 
            return; // no change
        else 
        {
            _center = oth.getCenter();
            _radius = oth.getRadius();
            return;
        }
    }

    float length = lengthSq * lengthSq;

    Vec3 newCenter;
    float newRadius;
    if ((length + oth.getRadius()) > _radius) 
    {
        float t = (length + radiusDiff) / (2.0f * length);
        newCenter = _center + diff * t;
    } 
    // otherwise, we keep our existing center

    newRadius = 0.5f * (length + _radius + oth.getRadius());

    _center = newCenter;
    _radius = newRadius;
}

NS_CC_END
