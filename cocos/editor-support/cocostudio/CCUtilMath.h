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


    /**
    * @~english Detect whether a point is inside a sprite
    * @~chinese 判断点坐标是否包含在精灵范围内
    *
    * @parame sprite   @~english the sprite to be check @~chinese 待检测的精灵
    *
    * @parame point    @~english hit point @~chinese 测试点
    *
    * @return @~english if hit point is inside sprite rect @~chinese 测试点是否在精灵范围内
    */
    bool CC_STUDIO_DLL isSpriteContainPoint(cocos2d::Sprite *sprite, cocos2d::Vec2 point);
    /**
    * @~english Detect whether a point is inside a sprite
    * @~chinese 判断点坐标是否包含在精灵范围内
    *
    * @parame sprite   @~english the sprite to be check @~chinese 待检测的精灵
    *
    * @parame point    @~english hit point @~chinese 测试点
    *
    * @parame outPoint @~english output buffer to receive hit point position in sprite coordinate
    *                  @~chinese 保存待测试点相对于精灵坐标系位置的buffer
    *
    * @return @~english if hit point is inside sprite rect @~chinese 测试点是否在精灵范围内
    */
    bool CC_STUDIO_DLL isSpriteContainPoint(cocos2d::Sprite *sprite, cocos2d::Vec2 point, cocos2d::Vec2 &outPoint);

#define CC_SPRITE_CONTAIN_POINT(sprite, point) isSpriteContainPoint((sprite), (point))
#define CC_SPRITE_CONTAIN_POINT_WITH_RETURN(sprite, point, outPoint) isSpriteContainPoint((sprite), (point), outPoint)


    /**
    * @~english Calculate current position by bezier curve
    * @~chinese 根据bezier曲线计算当前位置
    *
    * @parame t     @~english current time @~chinese 当前时间
    *
    * @parame point1,point2,point3     @~english Reference points @~chinese 参考点
    *
    * @return @~english if hit point is inside sprite rect @~chinese 测试点是否在精灵范围内
    */
    cocos2d::Vec2 CC_STUDIO_DLL bezierTo(float t, cocos2d::Vec2 &point1, cocos2d::Vec2 &point2, cocos2d::Vec2 &point3);
    /**
    * @~english Calculate current position by bezier curve
    * @~chinese 根据bezier曲线计算当前位置
    *
    * @parame t     @~english current time @~chinese 当前时间
    *
    * @parame point1,point2,point3,point4     @~english Reference points @~chinese 参考点
    *
    * @return @~english if hit point is inside sprite rect @~chinese 测试点是否在精灵范围内
    */
    cocos2d::Vec2 CC_STUDIO_DLL bezierTo(float t, cocos2d::Vec2 &point1, cocos2d::Vec2 &point2, cocos2d::Vec2 &point3, cocos2d::Vec2 &point4);

    /**
    * @~english Calculate current position by circle curve
    * @~chinese 根据圆形曲线计算当前位置
    *
    * @parame t     @~english current time @~chinese 当前时间
    *
    * @parame center  @~english circle center @~chinese 圆心坐标
    *
    * @parame radius  @~english radius @~chinese 半径
    *
    * @parame fromRadian  @~english begin radian @~chinese 起始角度
    *
    * @parame radianDif   @~english diffrence from begin radian @~chinese 结束角度和起始角度的角度差
    */
    cocos2d::Vec2 CC_STUDIO_DLL circleTo(float t, cocos2d::Vec2 &center, float radius, float fromRadian, float radianDif);


}

#endif /*__CCUTILMATH_H__*/
