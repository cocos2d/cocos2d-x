#ifndef __CCMATHBASE_H__
#define __CCMATHBASE_H__

#include <memory>
#include <string.h>
#include "platform/CCPlatformMacros.h"

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


#endif // __CCMATHBASE_H__
