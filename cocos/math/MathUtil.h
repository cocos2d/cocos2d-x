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
 * Defines a math utility class.
 *
 * This is primarily used for optimized internal math operations.
 */
class CC_DLL MathUtil
{
    friend class Mat4;
    friend class Vec3;

public:

    /**
     * Updates the given scalar towards the given target using a smoothing function.
     * The given response time determines the amount of smoothing (lag). A longer
     * response time yields a smoother result and more lag. To force the scalar to
     * follow the target closely, provide a response time that is very small relative
     * to the given elapsed time.
     *
     * @param x the scalar to update.
     * @param target target value.
     * @param elapsedTime elapsed time between calls.
     * @param responseTime response time (in the same units as elapsedTime).
     */
    static void smooth(float* x, float target, float elapsedTime, float responseTime);

    /**
     * Updates the given scalar towards the given target using a smoothing function.
     * The given rise and fall times determine the amount of smoothing (lag). Longer
     * rise and fall times yield a smoother result and more lag. To force the scalar to
     * follow the target closely, provide rise and fall times that are very small relative
     * to the given elapsed time.
     *
     * @param x the scalar to update.
     * @param target target value.
     * @param elapsedTime elapsed time between calls.
     * @param riseTime response time for rising slope (in the same units as elapsedTime).
     * @param fallTime response time for falling slope (in the same units as elapsedTime).
     */
    static void smooth(float* x, float target, float elapsedTime, float riseTime, float fallTime);

private:

    inline static void addMatrix(const ccScalar* m, ccScalar scalar, ccScalar* dst);

    inline static void addMatrix(const ccScalar* m1, const ccScalar* m2, ccScalar* dst);

    inline static void subtractMatrix(const ccScalar* m1, const ccScalar* m2, ccScalar* dst);

    inline static void multiplyMatrix(const ccScalar* m, ccScalar scalar, ccScalar* dst);

    inline static void multiplyMatrix(const ccScalar* m1, const ccScalar* m2, ccScalar* dst);

    inline static void negateMatrix(const ccScalar* m, ccScalar* dst);

    inline static void transposeMatrix(const ccScalar* m, ccScalar* dst);

    inline static void transformVec4(const ccScalar* m, ccScalar x, ccScalar y, ccScalar z, ccScalar w, ccScalar* dst);

    inline static void transformVec4(const ccScalar* m, const ccScalar* v, ccScalar* dst);

    inline static void crossVec3(const ccScalar* v1, const ccScalar* v2, ccScalar* dst);

    MathUtil();
};

NS_CC_MATH_END

#define MATRIX_SIZE ( sizeof(ccScalar) * 16)

#if defined(USE_NEON)
#if CC_MATH_USE_DOUBLES
#error "Only float supported via Neon, try: #define CC_MATH_USE_DOUBLES 0"
#else
#include "MathUtilNeon.inl"
#endif // CC_MATH_USE_DOUBLES
#else
#include "MathUtil.inl"
#endif

#endif
