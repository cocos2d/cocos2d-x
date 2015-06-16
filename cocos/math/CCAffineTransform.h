/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef __MATH_CCAFFINETRANSFORM_H__
#define __MATH_CCAFFINETRANSFORM_H__

#include "platform/CCPlatformMacros.h"

#include "math/CCGeometry.h"
#include "math/CCMath.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_BEGIN

/**
@struct AffineTransform
@brief
@~english
 Affine transform
 a   b    0
 c   d    0
 tx  ty   1
 
 Identity
 1   0    0
 0   1    0
 0   0    1
 * @~chinese 
 * 仿射变换
 a   b    0
 c   d    0
 tx  ty   1
 * 
 * 单位变换
 1   0    0
 0   1    0
 0   0    1
 */
struct CC_DLL AffineTransform {
    float a, b, c, d;
    float tx, ty;
    /**@~english indentity AffineTransform. @~chinese 单位变换。*/
    static const AffineTransform IDENTITY;
};

/**@~english Make affine transform from a, b, c, d, tx, ty.. @~chinese 从a,b,c,d,tx,ty构建仿射变换。*/
CC_DLL AffineTransform __CCAffineTransformMake(float a, float b, float c, float d, float tx, float ty);
#define AffineTransformMake __CCAffineTransformMake

/**@~english Multiply point (x,y,1) by a  affine tranform. @~chinese 用仿射矩阵变换点(x,y,1)。*/
CC_DLL Vec2 __CCPointApplyAffineTransform(const Vec2& point, const AffineTransform& t);
#define PointApplyAffineTransform __CCPointApplyAffineTransform

/**@~english Multiply size (width,height,0) by a  affine tranform. @~chinese 用仿射矩阵变换(width,height,0)。*/
CC_DLL Size __CCSizeApplyAffineTransform(const Size& size, const AffineTransform& t);
#define SizeApplyAffineTransform __CCSizeApplyAffineTransform
/**@~english Make identity affine transform. @~chinese 构建一个单位仿射变换矩阵。*/
CC_DLL AffineTransform AffineTransformMakeIdentity();
/**@~english Transform Rect, which will transform the four vertice of the point. @~chinese 变换矩形,这将逐个变换矩形的四个顶点。*/
CC_DLL Rect RectApplyAffineTransform(const Rect& rect, const AffineTransform& anAffineTransform);
/**@~english
 Transform Rect by Mat4.
 * @~chinese 
 * 使用Mat4变换Rect.
 */
CC_DLL Rect RectApplyTransform(const Rect& rect, const Mat4& transform);
/**@~english
 Transform Rect by Mat4.
 * @~chinese 
 * 使用Mat4变换Vec2.
 */
CC_DLL Vec2 PointApplyTransform(const Vec2& point, const Mat4& transform);
/**@~english
 Translation, equals
 1  0  1
 0  1  0   * affinetransform
 tx ty 1
 * @~chinese 
 * 进行平移,其效果等价于
 1  0  1
 0  1  0   * affinetransform
 tx ty 1
 */
CC_DLL AffineTransform AffineTransformTranslate(const AffineTransform& t, float tx, float ty);
/**@~english
 Rotation, equals
 cos(angle)   sin(angle)   0
 -sin(angle)  cos(angle)   0  * AffineTransform
 0            0            1
 * @~chinese 
 * 进行旋转,等价于
 cos(angle)   sin(angle)   0
 -sin(angle)  cos(angle)   0  * AffineTransform
 0            0            1
 */
CC_DLL AffineTransform AffineTransformRotate(const AffineTransform& aTransform, float anAngle);
/**@~english
 Scale, equals
 sx   0   0
 0    sy  0  * affineTransform
 0    0   1
 * @~chinese 
 * 进行缩放,等价于
 sx   0   0
 0    sy  0  * affineTransform
 0    0   1
 */
CC_DLL AffineTransform AffineTransformScale(const AffineTransform& t, float sx, float sy);
/**@~english Concat two affine transform, t1*t2.  @~chinese 连乘两个仿射变换t1*t2 */
CC_DLL AffineTransform AffineTransformConcat(const AffineTransform& t1, const AffineTransform& t2);
/**@~english Compare affine transform. @~chinese 判断仿射变换是否相等。*/
CC_DLL bool AffineTransformEqualToTransform(const AffineTransform& t1, const AffineTransform& t2);
/**@~english Get the inverse of affine transform. @~chinese 得到仿射变换的逆。*/
CC_DLL AffineTransform AffineTransformInvert(const AffineTransform& t);
/**@~english Concat Mat4, return t1*t2  @~chinese 连乘矩阵t1*t2。*/
CC_DLL Mat4 TransformConcat(const Mat4& t1, const Mat4& t2);
/**@~english identity affineTransform. @~chinese 单位仿射变换矩阵。*/
extern CC_DLL const AffineTransform AffineTransformIdentity;

NS_CC_END

// end of base transform
/// @}

#endif // __MATH_CCAFFINETRANSFORM_H__
