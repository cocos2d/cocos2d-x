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

#ifndef __CCUTILMATH_H__
#define __CCUTILMATH_H__

#include "2d/CCSprite.h"
#include "cocostudio/CCArmatureDefine.h"
#include "cocostudio/CocosStudioExport.h"
#include <math.h>

namespace cocostudio {

#define CC_DOUBLE_PI (M_PI*2)

#define CC_HALF_PI  (M_PI * 0.5f)


//! hit test function
bool CC_STUDIO_DLL isSpriteContainPoint(cocos2d::Sprite *sprite, cocos2d::Vec2 point);
bool CC_STUDIO_DLL isSpriteContainPoint(cocos2d::Sprite *sprite, cocos2d::Vec2 point, cocos2d::Vec2 &outPoint);

#define CC_SPRITE_CONTAIN_POINT(sprite, point) isSpriteContainPoint((sprite), (point))
#define CC_SPRITE_CONTAIN_POINT_WITH_RETURN(sprite, point, outPoint) isSpriteContainPoint((sprite), (point), outPoint)


//! motion curve function
cocos2d::Vec2 CC_STUDIO_DLL bezierTo(float t, cocos2d::Vec2 &point1, cocos2d::Vec2 &point2, cocos2d::Vec2 &point3);
cocos2d::Vec2 CC_STUDIO_DLL bezierTo(float t, cocos2d::Vec2 &point1, cocos2d::Vec2 &point2, cocos2d::Vec2 &point3, cocos2d::Vec2 &point4);

cocos2d::Vec2 CC_STUDIO_DLL circleTo(float t, cocos2d::Vec2 &center, float radius, float fromRadian, float radianDif);


}

#endif /*__CCUTILMATH_H__*/
