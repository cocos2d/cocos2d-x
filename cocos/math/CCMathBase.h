#ifndef __CCMATHBASE_H__
#define __CCMATHBASE_H__

#include <math.h>
#include <memory>
#include <string.h>
#include "base/CCPlatformMacros.h"

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

#ifdef __cplusplus
    #define NS_CC_MATH_BEGIN                     namespace cocos2d {
    #define NS_CC_MATH_END                       }
    #define USING_NS_CC_MATH                     using namespace cocos2d
#else
    #define NS_CC_MATH_BEGIN 
    #define NS_CC_MATH_END 
    #define USING_NS_CC_MATH 
#endif

#ifdef __SSE2__
#define CC_MATH_USE_DOUBLES 1
#else
#define CC_MATH_USE_DOUBLES 0
#endif // __SSE2__

#ifndef CC_MATH_USE_DOUBLES
#define CC_MATH_USE_DOUBLES 0 // use float by default
#endif

// NOTE: ccScalar is not fully supported, use it only in Mat4, Vec4, Vec3 now.

#if CC_MATH_USE_DOUBLES
    typedef double ccScalar;
    #define ccsqrt sqrt
    #define ccsin sin
    #define cccos cos
    #define ccacos acos
    #define ccatan2 atan2
    #define ccmod fmod
    #define ccexp exp
    #define ccpow pow
    #define ccfloor floor
    #define ccceil ceil
    #define ccfmod fmod
#else
    typedef float ccScalar;
    #define ccsqrt sqrtf
    #define ccsin sinf
    #define cccos cosf
    #define ccacos acosf
    #define ccatan2 atan2f
    #define ccmod fmodf
    #define ccexp expf
    #define ccpow powf
    #define ccfloor floorf
    #define ccceil ceilf
    #define ccfmod fmodf
#endif

#endif // __CCMATHBASE_H__
