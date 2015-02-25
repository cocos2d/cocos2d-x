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

#include "MathUtil.h"
#include "base/ccMacros.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <cpu-features.h>
#endif

//#define USE_NEON32        : neon 32 code will be used
//#define USE_NEON64        : neon 64 code will be used
//#define INCLUDE_NEON32    : neon 32 code included
//#define INCLUDE_NEON64    : neon 64 code included
//#define USE_SSE           : SSE code used
//#define INCLUDE_SSE       : SSE code included

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    #if defined (__arm64__)
    #define USE_NEON64
    #define INCLUDE_NEON64
    #elif defined (__ARM_NEON__)
    #define USE_NEON32
    #define INCLUDE_NEON32
    #else
    #endif
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #if defined (__arm64__) || defined (__aarch64__)
    #define USE_NEON64
    #define INCLUDE_NEON64
    #elif defined (__ARM_NEON__)
    #define INCLUDE_NEON32
    #else
    #endif
#else

#endif

#if defined (__SSE__)
#define USE_SSE
#define INCLUDE_SSE
#endif

#ifdef INCLUDE_NEON32
#include "MathUtilNeon.inl"
#endif

#ifdef INCLUDE_NEON64
#include "MathUtilNeon64.inl"
#endif

#ifdef INCLUDE_SSE
#include "MathUtilSSE.inl"
#endif

#include "MathUtil.inl"

NS_CC_MATH_BEGIN

void MathUtil::smooth(float* x, float target, float elapsedTime, float responseTime)
{
    GP_ASSERT(x);
    
    if (elapsedTime > 0)
    {
        *x += (target - *x) * elapsedTime / (elapsedTime + responseTime);
    }
}

void MathUtil::smooth(float* x, float target, float elapsedTime, float riseTime, float fallTime)
{
    GP_ASSERT(x);
    
    if (elapsedTime > 0)
    {
        float delta = target - *x;
        *x += delta * elapsedTime / (elapsedTime + (delta > 0 ? riseTime : fallTime));
    }
}

bool MathUtil::isNeon32Enabled()
{
#ifdef USE_NEON32
    return true;
#elif (defined (INCLUDE_NEON32) && (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) )
    class AnrdoidNeonChecker
    {
    public:
        AnrdoidNeonChecker()
        {
            if (android_getCpuFamily() == ANDROID_CPU_FAMILY_ARM && (android_getCpuFeatures() & ANDROID_CPU_ARM_FEATURE_NEON) != 0)
                _isNeonEnabled = true;
            else
                _isNeonEnabled = false;
        }
        bool isNeonEnabled() const { return _isNeonEnabled; }
    private:
        bool _isNeonEnabled;
    };
    static AnrdoidNeonChecker checker;
    return checker.isNeonEnabled();
#else
    return false;
#endif
}

bool MathUtil::isNeon64Enabled()
{
#ifdef USE_NEON64
    return true;
#else
    return false;
#endif
}

void MathUtil::addMatrix(const float* m, float scalar, float* dst)
{
#ifdef USE_NEON32
    MathUtilNeon::addMatrix(m, scalar, dst);
#elif defined (USE_NEON64)
    MathUtilNeon64::addMatrix(m, scalar, dst);
#elif defined (INCLUDE_NEON32)
    if(isNeon32Enabled()) MathUtilNeon::addMatrix(m, scalar, dst);
    else MathUtilC::addMatrix(m, scalar, dst);
#else
    MathUtilC::addMatrix(m, scalar, dst);
#endif
}

void MathUtil::addMatrix(const float* m1, const float* m2, float* dst)
{
#ifdef USE_NEON32
    MathUtilNeon::addMatrix(m1, m2, dst);
#elif defined (USE_NEON64)
    MathUtilNeon64::addMatrix(m1, m2, dst);
#elif defined (INCLUDE_NEON32)
    if(isNeon32Enabled()) MathUtilNeon::addMatrix(m1, m2, dst);
    else MathUtilC::addMatrix(m1, m2, dst);
#else
    MathUtilC::addMatrix(m1, m2, dst);
#endif
}

void MathUtil::subtractMatrix(const float* m1, const float* m2, float* dst)
{
#ifdef USE_NEON32
    MathUtilNeon::subtractMatrix(m1, m2, dst);
#elif defined (USE_NEON64)
    MathUtilNeon64::subtractMatrix(m1, m2, dst);
#elif defined (INCLUDE_NEON32)
    if(isNeon32Enabled()) MathUtilNeon::subtractMatrix(m1, m2, dst);
    else MathUtilC::subtractMatrix(m1, m2, dst);
#else
    MathUtilC::subtractMatrix(m1, m2, dst);
#endif
}

void MathUtil::multiplyMatrix(const float* m, float scalar, float* dst)
{
#ifdef USE_NEON32
    MathUtilNeon::multiplyMatrix(m, scalar, dst);
#elif defined (USE_NEON64)
    MathUtilNeon64::multiplyMatrix(m, scalar, dst);
#elif defined (INCLUDE_NEON32)
    if(isNeon32Enabled()) MathUtilNeon::multiplyMatrix(m, scalar, dst);
    else MathUtilC::multiplyMatrix(m, scalar, dst);
#else
    MathUtilC::multiplyMatrix(m, scalar, dst);
#endif
}

void MathUtil::multiplyMatrix(const float* m1, const float* m2, float* dst)
{
#ifdef USE_NEON32
    MathUtilNeon::multiplyMatrix(m1, m2, dst);
#elif defined (USE_NEON64)
    MathUtilNeon64::multiplyMatrix(m1, m2, dst);
#elif defined (INCLUDE_NEON32)
    if(isNeon32Enabled()) MathUtilNeon::multiplyMatrix(m1, m2, dst);
    else MathUtilC::multiplyMatrix(m1, m2, dst);
#else
    MathUtilC::multiplyMatrix(m1, m2, dst);
#endif
}

void MathUtil::negateMatrix(const float* m, float* dst)
{
#ifdef USE_NEON32
    MathUtilNeon::negateMatrix(m, dst);
#elif defined (USE_NEON64)
    MathUtilNeon64::negateMatrix(m, dst);
#elif defined (INCLUDE_NEON32)
    if(isNeon32Enabled()) MathUtilNeon::negateMatrix(m, dst);
    else MathUtilC::negateMatrix(m, dst);
#else
    MathUtilC::negateMatrix(m, dst);
#endif
}

void MathUtil::transposeMatrix(const float* m, float* dst)
{
#ifdef USE_NEON32
    MathUtilNeon::transposeMatrix(m, dst);
#elif defined (USE_NEON64)
    MathUtilNeon64::transposeMatrix(m, dst);
#elif defined (INCLUDE_NEON32)
    if(isNeon32Enabled()) MathUtilNeon::transposeMatrix(m, dst);
    else MathUtilC::transposeMatrix(m, dst);
#else
    MathUtilC::transposeMatrix(m, dst);
#endif
}

void MathUtil::transformVec4(const float* m, float x, float y, float z, float w, float* dst)
{
#ifdef USE_NEON32
    MathUtilNeon::transformVec4(m, x, y, z, w, dst);
#elif defined (USE_NEON64)
    MathUtilNeon64::transformVec4(m, x, y, z, w, dst);
#elif defined (INCLUDE_NEON32)
    if(isNeon32Enabled()) MathUtilNeon::transformVec4(m, x, y, z, w, dst);
    else MathUtilC::transformVec4(m, x, y, z, w, dst);
#else
    MathUtilC::transformVec4(m, x, y, z, w, dst);
#endif
}

void MathUtil::transformVec4(const float* m, const float* v, float* dst)
{
#ifdef USE_NEON32
    MathUtilNeon::transformVec4(m, v, dst);
#elif defined (USE_NEON64)
    MathUtilNeon64::transformVec4(m, v, dst);
#elif defined (INCLUDE_NEON32)
    if(isNeon32Enabled()) MathUtilNeon::transformVec4(m, v, dst);
    else MathUtilC::transformVec4(m, v, dst);
#else
    MathUtilC::transformVec4(m, v, dst);
#endif
}

void MathUtil::crossVec3(const float* v1, const float* v2, float* dst)
{
#ifdef USE_NEON32
    MathUtilNeon::crossVec3(v1, v2, dst);
#elif defined (USE_NEON64)
    MathUtilNeon64::crossVec3(v1, v2, dst);
#elif defined (INCLUDE_NEON32)
    if(isNeon32Enabled()) MathUtilNeon::crossVec3(v1, v2, dst);
    else MathUtilC::crossVec3(v1, v2, dst);
#else
    MathUtilC::crossVec3(v1, v2, dst);
#endif
}

NS_CC_MATH_END
