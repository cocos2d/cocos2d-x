/**
 Copyright 2013 BlackBerry Inc.

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
 */

#ifndef MATHUTIL_H_
#define MATHUTIL_H_

#include "CCMathBase.h"

NS_CC_MATH_BEGIN

/**
 * 定义一个数学工具类
 *
 * 这主要用于优化内部的数学运算
 */
class MathUtil
{
    friend class Mat4;
    friend class Vec3;

public:

    /**
     * 使用平滑函数和给定的标量对给定的目标进行处理。
     * 给定的响应时间决定了平滑的数量（延迟）。
     * 响应时间越长，平滑的结果越好，同时延迟的时间越长。
     * 给定的标量与目标是密切相关的，提供的响应时间相对于给定的运行时间是非常小的。
     *
     * @param x 更新的标量。
     * @param target 目标值。
     * @param elapsedTime 调用时的运行时间。
     * @param responseTime 响应时间（和运行时间单位相同）。
     */
    static void smooth(float* x, float target, float elapsedTime, float responseTime);

    /**
     * 使用平滑函数和给定的标量对给定的目标进行处理。
     * 给定的上升和下降时间决定了平滑的数量（延迟）。
     * 上升平滑处理和下降平滑处理的时间越长，平滑的结果越好，同时延迟的时间越长。
     * 给定的标量与目标是密切相关的，提供的响应时间相对于给定的运行时间是非常小的。
     *
     * @param x 更新的标量。
     * @param target 目标值。
     * @param elapsedTime 调用时的运行时间。
     * @param riseTime 平滑上升处理的响应时间（和运行时间单位相同）。
     * @param fallTime 平滑下降处理的响应时间（和运行时间单位相同）。
     */
    static void smooth(float* x, float target, float elapsedTime, float riseTime, float fallTime);

private:

    inline static void addMatrix(const float* m, float scalar, float* dst);

    inline static void addMatrix(const float* m1, const float* m2, float* dst);

    inline static void subtractMatrix(const float* m1, const float* m2, float* dst);

    inline static void multiplyMatrix(const float* m, float scalar, float* dst);

    inline static void multiplyMatrix(const float* m1, const float* m2, float* dst);

    inline static void negateMatrix(const float* m, float* dst);

    inline static void transposeMatrix(const float* m, float* dst);

    inline static void transformVec4(const float* m, float x, float y, float z, float w, float* dst);

    inline static void transformVec4(const float* m, const float* v, float* dst);

    inline static void crossVec3(const float* v1, const float* v2, float* dst);

    MathUtil();
};

NS_CC_MATH_END

#define MATRIX_SIZE ( sizeof(float) * 16)

#ifdef USE_NEON
#include "MathUtilNeon.inl"
#else
#include "MathUtil.inl"
#endif

#endif
