#ifndef MATHUTIL_H_
#define MATHUTIL_H_

#include <memory>

#define MATH_DEG_TO_RAD(x)          ((x) * 0.0174532925f)
#define MATH_RAD_TO_DEG(x)          ((x)* 57.29577951f)
//#define MATH_RANDOM_MINUS1_1()      ((2.0f*((float)rand()/RAND_MAX))-1.0f)      // Returns a random float between -1 and 1.
//#define MATH_RANDOM_0_1()           ((float)rand()/RAND_MAX)                    // Returns a random float between 0 and 1.
#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_TOLERANCE              2e-37f
//#define MATH_E                      2.71828182845904523536f
//#define MATH_LOG10E                 0.4342944819032518f
//#define MATH_LOG2E                  1.442695040888963387f
//#define MATH_PI                     3.14159265358979323846f
#define MATH_PIOVER2                1.57079632679489661923f
//#define MATH_PIOVER4                0.785398163397448309616f
//#define MATH_PIX2                   6.28318530717958647693f
#define MATH_EPSILON                0.000001f
//#define MATH_CLAMP(x, lo, hi)       ((x < lo) ? lo : ((x > hi) ? hi : x))
//#ifndef M_1_PI
//#define M_1_PI                      0.31830988618379067154

namespace gameplay
{
/**
 * Defines a math utility class.
 *
 * This is primarily used for optimized internal math operations.
 */
class MathUtil
{
    friend class Matrix;
    friend class Vector3;

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

    inline static void addMatrix(const float* m, float scalar, float* dst);

    inline static void addMatrix(const float* m1, const float* m2, float* dst);

    inline static void subtractMatrix(const float* m1, const float* m2, float* dst);

    inline static void multiplyMatrix(const float* m, float scalar, float* dst);

    inline static void multiplyMatrix(const float* m1, const float* m2, float* dst);

    inline static void negateMatrix(const float* m, float* dst);

    inline static void transposeMatrix(const float* m, float* dst);

    inline static void transformVector4(const float* m, float x, float y, float z, float w, float* dst);

    inline static void transformVector4(const float* m, const float* v, float* dst);

    inline static void crossVector3(const float* v1, const float* v2, float* dst);

    MathUtil();
};

}

#define MATRIX_SIZE ( sizeof(float) * 16)

#ifdef USE_NEON
#include "MathUtilNeon.inl"
#else
#include "MathUtil.inl"
#endif

#endif
