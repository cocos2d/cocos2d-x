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

#if defined (__ARM_NEON__) || ((CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) &&!defined(__SSE__))
#include "MathUtilNeon.inl"
#endif

#include "MathUtil.inl"
#include "MathUtilSSE.inl"

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

void MathUtil::addMatrix(const float* m, float scalar, float* dst)
{
#ifdef __ARM_NEON__
    MathUtilNeon::addMatrix(m, scalar, dst);
#else
    MathUtilC::addMatrix(m, scalar, dst);
#endif
}

void MathUtil::addMatrix(const float* m1, const float* m2, float* dst)
{
#ifdef __ARM_NEON__
    MathUtilNeon::addMatrix(m1, m2, dst);
#else
    MathUtilC::addMatrix(m1, m2, dst);
#endif
}

void MathUtil::subtractMatrix(const float* m1, const float* m2, float* dst)
{
#ifdef __ARM_NEON__
    MathUtilNeon::subtractMatrix(m1, m2, dst);
#else
    MathUtilC::subtractMatrix(m1, m2, dst);
#endif
}

void MathUtil::multiplyMatrix(const float* m, float scalar, float* dst)
{
#ifdef __ARM_NEON__
    MathUtilNeon::multiplyMatrix(m, scalar, dst);
#else
    MathUtilC::multiplyMatrix(m, scalar, dst);
#endif
}

void MathUtil::multiplyMatrix(const float* m1, const float* m2, float* dst)
{
#ifdef __ARM_NEON__
    MathUtilNeon::multiplyMatrix(m1, m2, dst);
#else
    MathUtilC::multiplyMatrix(m1, m2, dst);
#endif
}

void MathUtil::negateMatrix(const float* m, float* dst)
{
#ifdef __ARM_NEON__
    MathUtilNeon::negateMatrix(m, dst);
#else
    MathUtilC::negateMatrix(m, dst);
#endif
}

void MathUtil::transposeMatrix(const float* m, float* dst)
{
#ifdef __ARM_NEON__
    MathUtilNeon::transposeMatrix(m, dst);
#else
    MathUtilC::transposeMatrix(m, dst);
#endif
}

void MathUtil::transformVec4(const float* m, float x, float y, float z, float w, float* dst)
{
#ifdef __ARM_NEON__
    MathUtilNeon::transformVec4(m, x, y, z, w, dst);
#else
    MathUtilC::transformVec4(m, x, y, z, w, dst);
#endif
}

void MathUtil::transformVec4(const float* m, const float* v, float* dst)
{
#ifdef __ARM_NEON__
    MathUtilNeon::transformVec4(m, v, dst);
#else
    MathUtilC::transformVec4(m, v, dst);
#endif
}

void MathUtil::crossVec3(const float* v1, const float* v2, float* dst)
{
#ifdef __ARM_NEON__
    MathUtilNeon::crossVec3(v1, v2, dst);
#else
    MathUtilC::crossVec3(v1, v2, dst);
#endif
}

NS_CC_MATH_END
