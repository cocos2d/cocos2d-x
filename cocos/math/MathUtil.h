/**@~english
 Copyright 2013 BlackBerry Inc.
 Copyright (c) 2014-2015 Chukong Technologies

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

 Original file from GamePlay3D: http://gameplay3d.org

 This file was modified to fit the cocos2d-x project
 * @~chinese 
 * 黑莓公司2013年版权所有。
 * 版权(c)2014 - 2015 Chukong技术
 * 
 * 在Apache许可下的2.0版本(“许可证”);
 * 你不可以使用这个文件除了遵守许可证。
 * 你可以获得许可证的副本
 * 
 * 网址:
 * 
 * Unless required by applicable law or agreed to in writing, software
 * 分布式的许可下分布在一个“目前的”基础上,
 * 没有任何形式的保证或条件,无论是明示或默示。
 * 看到的许可证管理权限和特定的语言
 * limitations under the License.
 * 
 * 原始文件从GamePlay3D:http:
 * 
 * 这个文件被修改以适应cocos2d-x项目
 */

#ifndef MATHUTIL_H_
#define MATHUTIL_H_

#ifdef __SSE__
#include <xmmintrin.h>
#endif

#include "CCMathBase.h"

/**
 * @addtogroup base
 * @{
 */

NS_CC_MATH_BEGIN

/**
@class MathUtil
@brief
@~english
 * Defines a math utility class.
 *
 * This is primarily used for optimized internal math operations.
 * @~chinese 
 * 定义了一个数学工具类。
 * 
 * 主要用于优化数学操作。
 */
class CC_DLL MathUtil
{
    friend class Mat4;
    friend class Vec3;

public:

    /**@~english
     * Updates the given scalar towards the given target using a smoothing function.
     * The given response time determines the amount of smoothing (lag). A longer
     * response time yields a smoother result and more lag. To force the scalar to
     * follow the target closely, provide a response time that is very small relative
     * to the given elapsed time.
     *
     * @~chinese 
     * 通过算法让x平滑过渡到target。
     * 响应时间responseTime决定了平滑的程序和响应的时间。更长的
     * 响应时间意味着过渡更平滑，时间更长。如果要让x紧跟target的值，需要提供一个比流逝时间elapsedTime小的多的过渡时间
     * 
     * @param x @~english the scalar to update.
     * @~chinese 要平滑过渡的值。
     * @param target @~english target value.
     * @~chinese 要过渡到的目标值。
     * @param elapsedTime @~english elapsed time between calls.
     * @~chinese 流逝时间，两次调用的间隔时间。
     * @param responseTime @~english response time (in the same units as elapsedTime).
     * @~chinese 响应时间。
     */
    static void smooth(float* x, float target, float elapsedTime, float responseTime);

    /**@~english
     * Updates the given scalar towards the given target using a smoothing function.
     * The given rise and fall times determine the amount of smoothing (lag). Longer
     * rise and fall times yield a smoother result and more lag. To force the scalar to
     * follow the target closely, provide rise and fall times that are very small relative
     * to the given elapsed time.
     *
     * @~chinese 
     * 通过算法让x平滑过渡到target。
     * 给定的上升和下降时间决定了的平滑的程度。
     * 较长的上升和下降时间意味着更加过渡平滑，延迟更大，如果要让x紧跟目标值，
     * 需要提供比流逝时间小的多的上升和下降时间。
     * 
     * @param x @~english the scalar to update.
     * @~chinese 要平滑过渡的值。
     * @param target @~english target value.
     * @~chinese 目标值。
     * @param elapsedTime @~english elapsed time between calls.
     * @~chinese 流逝时间，两次调用的间隔时间。
     * @param riseTime @~english response time for rising slope (in the same units as elapsedTime).
     * @~chinese 上升的响应时间。
     * @param fallTime @~english response time for falling slope (in the same units as elapsedTime).
     * @~chinese 下降的响应时间。
     */
    static void smooth(float* x, float target, float elapsedTime, float riseTime, float fallTime);
    
    /**@~english
     * Linearly interpolates between from value to to value by alpha which is in
     * the range [0,1]
     *
     * @~chinese 
     * 在from和to两个数值之间进行线性差值，alplha表示差值系数，位于[0,1]范围
     * 
     * @param from @~english the from value.
     * @~chinese 差值的初值。
     * @param to @~english the to value.
     * @~chinese 差值的终值。
     * @param alpha @~english the alpha value between [0,1]
     *
     * @~chinese 差值系数alpha值[0,1]
     * 
     * @return @~english interpolated float value
     * @~chinese 差值的结果
     */
    static float lerp(float from, float to, float alpha);
private:
    //Indicates that if neon is enabled
    static bool isNeon32Enabled();
    static bool isNeon64Enabled();
private:
#ifdef __SSE__
    static void addMatrix(const __m128 m[4], float scalar, __m128 dst[4]);
    
    static void addMatrix(const __m128 m1[4], const __m128 m2[4], __m128 dst[4]);
    
    static void subtractMatrix(const __m128 m1[4], const __m128 m2[4], __m128 dst[4]);
    
    static void multiplyMatrix(const __m128 m[4], float scalar, __m128 dst[4]);
    
    static void multiplyMatrix(const __m128 m1[4], const __m128 m2[4], __m128 dst[4]);
    
    static void negateMatrix(const __m128 m[4], __m128 dst[4]);
    
    static void transposeMatrix(const __m128 m[4], __m128 dst[4]);
        
    static void transformVec4(const __m128 m[4], const __m128& v, __m128& dst);
#endif
    static void addMatrix(const float* m, float scalar, float* dst);

    static void addMatrix(const float* m1, const float* m2, float* dst);

    static void subtractMatrix(const float* m1, const float* m2, float* dst);

    static void multiplyMatrix(const float* m, float scalar, float* dst);

    static void multiplyMatrix(const float* m1, const float* m2, float* dst);

    static void negateMatrix(const float* m, float* dst);

    static void transposeMatrix(const float* m, float* dst);

    static void transformVec4(const float* m, float x, float y, float z, float w, float* dst);

    static void transformVec4(const float* m, const float* v, float* dst);

    static void crossVec3(const float* v1, const float* v2, float* dst);

};

NS_CC_MATH_END
/**
 end of base group
 @}
 */
#define MATRIX_SIZE ( sizeof(float) * 16)

#endif
