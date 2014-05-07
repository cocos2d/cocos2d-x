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

#include "cocostudio/CCUtilMath.h"

using namespace cocos2d;


namespace cocostudio {

bool isSpriteContainPoint(Sprite *sprite, Vector2 point, Vector2 &outPoint)
{
    outPoint = sprite->convertToNodeSpace(point);

    Size s  = sprite->getContentSize();
    Rect r(0, 0, s.width, s.height);

    return r.containsPoint(outPoint);
}

bool isSpriteContainPoint(Sprite *sprite, Vector2 point)
{
    Vector2 p = Vector2(0, 0);
    return isSpriteContainPoint(sprite, point, p);
}


Vector2 bezierTo(float t, Vector2 &point1, Vector2 &point2, Vector2 &point3)
{

    Vector2 p;

    p.x = pow((1 - t), 2) * point1.x + 2 * t * (1 - t) * point2.x + pow(t, 2) * point3.x;
    p.y = pow((1 - t), 2) * point1.y + 2 * t * (1 - t) * point2.y + pow(t, 2) * point3.y;

    return p;
}

Vector2 bezierTo(float t, Vector2 &point1, Vector2 &point2, Vector2 &point3, Vector2 &point4)
{
    Vector2 p;

    p.x = point1.x * pow((1 - t), 3) + 3 * t * point2.x * pow((1 - t), 2) + 3 * point3.x * pow(t, 2) * (1 - t) + point4.x * pow(t, 3);
    p.y = point1.y * pow((1 - t), 3) + 3 * t * point2.y * pow((1 - t), 2) + 3 * point3.y * pow(t, 2) * (1 - t) + point4.y * pow(t, 3);

    return p;
}

Vector2 circleTo(float t, Vector2 &center, float radius, float fromRadian, float radianDif)
{
    Vector2 p;

    p.x = center.x + radius * cos(fromRadian + radianDif * t);
    p.y = center.y + radius * sin(fromRadian + radianDif * t);

    return p;
}

}
