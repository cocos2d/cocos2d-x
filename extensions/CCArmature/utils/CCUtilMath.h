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

#include "CCArmatureDefine.h"
#include <math.h>

NS_CC_EXT_BEGIN

#define CC_DOUBLE_PI (M_PI*2)

#define CC_HALF_PI  (M_PI * 0.5f)


//! hit test function
bool isSpriteContainPoint(CCSprite *sprite, CCPoint point);
bool isSpriteContainPoint(CCSprite *sprite, CCPoint point, CCPoint &outPoint);

#define CC_SPRITE_CONTAIN_POINT(sprite, point) isSpriteContainPoint((sprite), (point))
#define CC_SPRITE_CONTAIN_POINT_WITH_RETURN(sprite, point, outPoint) isSpriteContainPoint((sprite), (point), outPoint)


//! motion curve function
CCPoint bezierTo(float t, CCPoint &point1, CCPoint &point2, CCPoint &point3);
CCPoint bezierTo(float t, CCPoint &point1, CCPoint &point2, CCPoint &point3, CCPoint &point4);

CCPoint circleTo(float t, CCPoint &center, float radius, float fromRadian, float radianDif);


NS_CC_EXT_END

#endif /*__CCUTILMATH_H__*/
