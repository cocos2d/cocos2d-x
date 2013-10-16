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

#ifndef __CCUTILMATH_H__
#define __CCUTILMATH_H__

#include "cocostudio/CCArmatureDefine.h"
#include <math.h>

namespace cocostudio {

#define CC_DOUBLE_PI (M_PI*2)

#define CC_HALF_PI  (M_PI * 0.5f)


//! hit test function
bool isSpriteContainPoint(cocos2d::Sprite *sprite, cocos2d::Point point);
bool isSpriteContainPoint(cocos2d::Sprite *sprite, cocos2d::Point point, cocos2d::Point &outPoint);

#define CC_SPRITE_CONTAIN_POINT(sprite, point) isSpriteContainPoint((sprite), (point))
#define CC_SPRITE_CONTAIN_POINT_WITH_RETURN(sprite, point, outPoint) isSpriteContainPoint((sprite), (point), outPoint)


//! motion curve function
cocos2d::Point bezierTo(float t, cocos2d::Point &point1, cocos2d::Point &point2, cocos2d::Point &point3);
cocos2d::Point bezierTo(float t, cocos2d::Point &point1, cocos2d::Point &point2, cocos2d::Point &point3, cocos2d::Point &point4);

cocos2d::Point circleTo(float t, cocos2d::Point &center, float radius, float fromRadian, float radianDif);


}

#endif /*__CCUTILMATH_H__*/
