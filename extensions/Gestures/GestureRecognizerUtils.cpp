/****************************************************************************
Copyright (c) 2016 Alfonso Grillo

    drakon.cocos@gmail.com

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

#include "GestureRecognizerUtils.h"

bool nodeContainsThePoint(cocos2d::Node* node, const cocos2d::Vec2& pt)
{
    auto nodeSz = node->getContentSize();
    cocos2d::Rect bbox = cocos2d::Rect(0, 0, nodeSz.width, nodeSz.height);
    cocos2d::Vec2 locationInNodeSpace = node->convertToNodeSpace(pt);
    return bbox.containsPoint(locationInNodeSpace);
}

float computeSignedAngle(const cocos2d::Vec2& v1, const cocos2d::Vec2& v2)
{
    float result = 0;
    if (not v1.isZero() and not v2.isZero())
    {
        auto a = CC_RADIANS_TO_DEGREES(cocos2d::Vec2::angle(v1, v2));
        cocos2d::Vec3 normal;
        cocos2d::Vec3::cross({v1.x, v1.y, 0}, {v2.x, v2.y, 0}, &normal);
        result = normal.z <= 0 ? a : -a; 
    }
    return result;
}