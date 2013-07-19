/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

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

#include "CCUtilMath.h"


NS_CC_EXT_BEGIN

bool isSpriteContainPoint(CCSprite *sprite, CCPoint _point, CCPoint &outPoint)
{
    outPoint = sprite->convertToNodeSpace(_point);

    CCSize _s  = sprite->getContentSize();
    CCRect _r(0, 0, _s.width, _s.height);

    return _r.containsPoint(outPoint);
}

bool isSpriteContainPoint(CCSprite *_sprite, CCPoint _point)
{
    CCPoint _p = ccp(0, 0);
    return isSpriteContainPoint(_sprite, _point, _p);
}


CCPoint bezierTo(float t, CCPoint &point1, CCPoint &point2, CCPoint &point3)
{

    CCPoint p;

    p.x = pow((1 - t), 2) * point1.x + 2 * t * (1 - t) * point2.x + pow(t, 2) * point3.x;
    p.y = pow((1 - t), 2) * point1.y + 2 * t * (1 - t) * point2.y + pow(t, 2) * point3.y;

    return p;
}

CCPoint bezierTo(float t, CCPoint &point1, CCPoint &point2, CCPoint &point3, CCPoint &point4)
{
    CCPoint p;

    p.x = point1.x * pow((1 - t), 3) + 3 * t * point2.x * pow((1 - t), 2) + 3 * point3.x * pow(t, 2) * (1 - t) + point4.x * pow(t, 3);
    p.y = point1.y * pow((1 - t), 3) + 3 * t * point2.y * pow((1 - t), 2) + 3 * point3.y * pow(t, 2) * (1 - t) + point4.y * pow(t, 3);

    return p;
}

CCPoint circleTo(float t, CCPoint &center, float radius, float fromRadian, float radianDif)
{
    CCPoint p;

    p.x = center.x + radius * cos(fromRadian + radianDif * t);
    p.y = center.y + radius * sin(fromRadian + radianDif * t);

    return p;
}

NS_CC_EXT_END
