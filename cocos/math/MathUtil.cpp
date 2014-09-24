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

#ifdef USE_NEON

void MathUtil::addMatrix(const float* m, float scalar, float* dst)
{
    asm volatile(
                 "vld1.32 {q0, q1}, [%1]!    \n\t" // M[m0-m7]
                 "vld1.32 {q2, q3}, [%1]     \n\t" // M[m8-m15]
                 "vld1.32 {d8[0]},  [%2]     \n\t" // s
                 "vmov.f32 s17, s16          \n\t" // s
                 "vmov.f32 s18, s16          \n\t" // s
                 "vmov.f32 s19, s16          \n\t" // s
                 
                 "vadd.f32 q8, q0, q4        \n\t" // DST->M[m0-m3] = M[m0-m3] + s
                 "vadd.f32 q9, q1, q4        \n\t" // DST->M[m4-m7] = M[m4-m7] + s
                 "vadd.f32 q10, q2, q4       \n\t" // DST->M[m8-m11] = M[m8-m11] + s
                 "vadd.f32 q11, q3, q4       \n\t" // DST->M[m12-m15] = M[m12-m15] + s
                 
                 "vst1.32 {q8, q9}, [%0]!    \n\t" // DST->M[m0-m7]
                 "vst1.32 {q10, q11}, [%0]   \n\t" // DST->M[m8-m15]
                 :
                 : "r"(dst), "r"(m), "r"(&scalar)
                 : "q0", "q1", "q2", "q3", "q4", "q8", "q9", "q10", "q11", "memory"
                 );
}

void MathUtil::addMatrix(const float* m1, const float* m2, float* dst)
{
    asm volatile(
                 "vld1.32     {q0, q1},     [%1]! \n\t" // M1[m0-m7]
                 "vld1.32     {q2, q3},     [%1]  \n\t" // M1[m8-m15]
                 "vld1.32     {q8, q9},     [%2]! \n\t" // M2[m0-m7]
                 "vld1.32     {q10, q11}, [%2]    \n\t" // M2[m8-m15]
                 
                 "vadd.f32   q12, q0, q8          \n\t" // DST->M[m0-m3] = M1[m0-m3] + M2[m0-m3]
                 "vadd.f32   q13, q1, q9          \n\t" // DST->M[m4-m7] = M1[m4-m7] + M2[m4-m7]
                 "vadd.f32   q14, q2, q10         \n\t" // DST->M[m8-m11] = M1[m8-m11] + M2[m8-m11]
                 "vadd.f32   q15, q3, q11         \n\t" // DST->M[m12-m15] = M1[m12-m15] + M2[m12-m15]
                 
                 "vst1.32    {q12, q13}, [%0]!    \n\t" // DST->M[m0-m7]
                 "vst1.32    {q14, q15}, [%0]     \n\t" // DST->M[m8-m15]
                 :
                 : "r"(dst), "r"(m1), "r"(m2)
                 : "q0", "q1", "q2", "q3", "q8", "q9", "q10", "q11", "q12", "q13", "q14", "q15", "memory"
                 );
}

void MathUtil::subtractMatrix(const float* m1, const float* m2, float* dst)
{
    asm volatile(
                 "vld1.32     {q0, q1},     [%1]!  \n\t" // M1[m0-m7]
                 "vld1.32     {q2, q3},     [%1]   \n\t" // M1[m8-m15]
                 "vld1.32     {q8, q9},     [%2]!  \n\t" // M2[m0-m7]
                 "vld1.32     {q10, q11}, [%2]     \n\t" // M2[m8-m15]
                 
                 "vsub.f32   q12, q0, q8         \n\t" // DST->M[m0-m3] = M1[m0-m3] - M2[m0-m3]
                 "vsub.f32   q13, q1, q9         \n\t" // DST->M[m4-m7] = M1[m4-m7] - M2[m4-m7]
                 "vsub.f32   q14, q2, q10        \n\t" // DST->M[m8-m11] = M1[m8-m11] - M2[m8-m11]
                 "vsub.f32   q15, q3, q11        \n\t" // DST->M[m12-m15] = M1[m12-m15] - M2[m12-m15]
                 
                 "vst1.32    {q12, q13}, [%0]!   \n\t" // DST->M[m0-m7]
                 "vst1.32    {q14, q15}, [%0]    \n\t" // DST->M[m8-m15]
                 :
                 : "r"(dst), "r"(m1), "r"(m2)
                 : "q0", "q1", "q2", "q3", "q8", "q9", "q10", "q11", "q12", "q13", "q14", "q15", "memory"
                 );
}

void MathUtil::multiplyMatrix(const float* m, float scalar, float* dst)
{
    asm volatile(
                 "vld1.32     {d0[0]},         [%2]        \n\t" // M[m0-m7]
                 "vld1.32    {q4-q5},          [%1]!       \n\t" // M[m8-m15]
                 "vld1.32    {q6-q7},          [%1]        \n\t" // s
                 
                 "vmul.f32     q8, q4, d0[0]               \n\t" // DST->M[m0-m3] = M[m0-m3] * s
                 "vmul.f32     q9, q5, d0[0]               \n\t" // DST->M[m4-m7] = M[m4-m7] * s
                 "vmul.f32     q10, q6, d0[0]              \n\t" // DST->M[m8-m11] = M[m8-m11] * s
                 "vmul.f32     q11, q7, d0[0]              \n\t" // DST->M[m12-m15] = M[m12-m15] * s
                 
                 "vst1.32     {q8-q9},           [%0]!     \n\t" // DST->M[m0-m7]
                 "vst1.32     {q10-q11},         [%0]      \n\t" // DST->M[m8-m15]
                 :
                 : "r"(dst), "r"(m), "r"(&scalar)
                 : "q0", "q4", "q5", "q6", "q7", "q8", "q9", "q10", "q11", "memory"
                 );
}

void MathUtil::multiplyMatrix(const float* m1, const float* m2, float* dst)
{
    asm volatile(
                 "vld1.32     {d16 - d19}, [%1]! \n\t"       // M1[m0-m7]
                 "vld1.32     {d20 - d23}, [%1]  \n\t"       // M1[m8-m15]
                 "vld1.32     {d0 - d3}, [%2]!   \n\t"       // M2[m0-m7]
                 "vld1.32     {d4 - d7}, [%2]    \n\t"       // M2[m8-m15]
                 
                 "vmul.f32    q12, q8, d0[0]     \n\t"         // DST->M[m0-m3] = M1[m0-m3] * M2[m0]
                 "vmul.f32    q13, q8, d2[0]     \n\t"         // DST->M[m4-m7] = M1[m4-m7] * M2[m4]
                 "vmul.f32    q14, q8, d4[0]     \n\t"         // DST->M[m8-m11] = M1[m8-m11] * M2[m8]
                 "vmul.f32    q15, q8, d6[0]     \n\t"         // DST->M[m12-m15] = M1[m12-m15] * M2[m12]
                 
                 "vmla.f32    q12, q9, d0[1]     \n\t"         // DST->M[m0-m3] += M1[m0-m3] * M2[m1]
                 "vmla.f32    q13, q9, d2[1]     \n\t"         // DST->M[m4-m7] += M1[m4-m7] * M2[m5]
                 "vmla.f32    q14, q9, d4[1]     \n\t"         // DST->M[m8-m11] += M1[m8-m11] * M2[m9]
                 "vmla.f32    q15, q9, d6[1]     \n\t"         // DST->M[m12-m15] += M1[m12-m15] * M2[m13]
                 
                 "vmla.f32    q12, q10, d1[0]    \n\t"         // DST->M[m0-m3] += M1[m0-m3] * M2[m2]
                 "vmla.f32    q13, q10, d3[0]    \n\t"         // DST->M[m4-m7] += M1[m4-m7] * M2[m6]
                 "vmla.f32    q14, q10, d5[0]    \n\t"         // DST->M[m8-m11] += M1[m8-m11] * M2[m10]
                 "vmla.f32    q15, q10, d7[0]    \n\t"         // DST->M[m12-m15] += M1[m12-m15] * M2[m14]
                 
                 "vmla.f32    q12, q11, d1[1]    \n\t"         // DST->M[m0-m3] += M1[m0-m3] * M2[m3]
                 "vmla.f32    q13, q11, d3[1]    \n\t"         // DST->M[m4-m7] += M1[m4-m7] * M2[m7]
                 "vmla.f32    q14, q11, d5[1]    \n\t"         // DST->M[m8-m11] += M1[m8-m11] * M2[m11]
                 "vmla.f32    q15, q11, d7[1]    \n\t"         // DST->M[m12-m15] += M1[m12-m15] * M2[m15]
                 
                 "vst1.32    {d24 - d27}, [%0]!  \n\t"       // DST->M[m0-m7]
                 "vst1.32    {d28 - d31}, [%0]   \n\t"       // DST->M[m8-m15]
                 
                 : // output
                 : "r"(dst), "r"(m1), "r"(m2) // input - note *value* of pointer doesn't change.
                 : "memory", "q0", "q1", "q2", "q3", "q8", "q9", "q10", "q11", "q12", "q13", "q14", "q15"
                 );
}

void MathUtil::negateMatrix(const float* m, float* dst)
{
    asm volatile(
                 "vld1.32     {q0-q1},  [%1]!     \n\t" // load m0-m7
                 "vld1.32     {q2-q3},  [%1]      \n\t" // load m8-m15
                 
                 "vneg.f32     q4, q0             \n\t" // negate m0-m3
                 "vneg.f32     q5, q1             \n\t" // negate m4-m7
                 "vneg.f32     q6, q2             \n\t" // negate m8-m15
                 "vneg.f32     q7, q3             \n\t" // negate m8-m15
                 
                 "vst1.32     {q4-q5},  [%0]!     \n\t" // store m0-m7
                 "vst1.32     {q6-q7},  [%0]      \n\t" // store m8-m15
                 :
                 : "r"(dst), "r"(m)
                 : "q0", "q1", "q2", "q3", "q4", "q5", "q6", "q7", "memory"
                 );
}

void MathUtil::transposeMatrix(const float* m, float* dst)
{
    asm volatile(
                 "vld4.32 {d0[0], d2[0], d4[0], d6[0]}, [%1]!    \n\t" // DST->M[m0, m4, m8, m12] = M[m0-m3]
                 "vld4.32 {d0[1], d2[1], d4[1], d6[1]}, [%1]!    \n\t" // DST->M[m1, m5, m9, m12] = M[m4-m7]
                 "vld4.32 {d1[0], d3[0], d5[0], d7[0]}, [%1]!    \n\t" // DST->M[m2, m6, m10, m12] = M[m8-m11]
                 "vld4.32 {d1[1], d3[1], d5[1], d7[1]}, [%1]     \n\t" // DST->M[m3, m7, m11, m12] = M[m12-m15]
                 
                 "vst1.32 {q0-q1}, [%0]!                         \n\t" // DST->M[m0-m7]
                 "vst1.32 {q2-q3}, [%0]                          \n\t" // DST->M[m8-m15]
                 :
                 : "r"(dst), "r"(m)
                 : "q0", "q1", "q2", "q3", "memory"
                 );
}

void MathUtil::transformVec4(const float* m, float x, float y, float z, float w, float* dst)
{
    asm volatile(
                 "vld1.32    {d0[0]},        [%1]    \n\t"    // V[x]
                 "vld1.32    {d0[1]},        [%2]    \n\t"    // V[y]
                 "vld1.32    {d1[0]},        [%3]    \n\t"    // V[z]
                 "vld1.32    {d1[1]},        [%4]    \n\t"    // V[w]
                 "vld1.32    {d18 - d21},    [%5]!   \n\t"    // M[m0-m7]
                 "vld1.32    {d22 - d25},    [%5]    \n\t"    // M[m8-m15]
                 
                 "vmul.f32 q13,  q9, d0[0]           \n\t"    // DST->V = M[m0-m3] * V[x]
                 "vmla.f32 q13, q10, d0[1]           \n\t"    // DST->V += M[m4-m7] * V[y]
                 "vmla.f32 q13, q11, d1[0]           \n\t"    // DST->V += M[m8-m11] * V[z]
                 "vmla.f32 q13, q12, d1[1]           \n\t"    // DST->V += M[m12-m15] * V[w]
                 
                 "vst1.32 {d26}, [%0]!               \n\t"    // DST->V[x, y]
                 "vst1.32 {d27[0]}, [%0]             \n\t"    // DST->V[z]
                 :
                 : "r"(dst), "r"(&x), "r"(&y), "r"(&z), "r"(&w), "r"(m)
                 : "q0", "q9", "q10","q11", "q12", "q13", "memory"
                 );
}

void MathUtil::transformVec4(const float* m, const float* v, float* dst)
{
    asm volatile
    (
     "vld1.32    {d0, d1}, [%1]     \n\t"   // V[x, y, z, w]
     "vld1.32    {d18 - d21}, [%2]! \n\t"   // M[m0-m7]
     "vld1.32    {d22 - d25}, [%2]  \n\t"    // M[m8-m15]
     
     "vmul.f32   q13, q9, d0[0]     \n\t"   // DST->V = M[m0-m3] * V[x]
     "vmla.f32   q13, q10, d0[1]    \n\t"   // DST->V = M[m4-m7] * V[y]
     "vmla.f32   q13, q11, d1[0]    \n\t"   // DST->V = M[m8-m11] * V[z]
     "vmla.f32   q13, q12, d1[1]    \n\t"   // DST->V = M[m12-m15] * V[w]
     
     "vst1.32    {d26, d27}, [%0]   \n\t"   // DST->V
     :
     : "r"(dst), "r"(v), "r"(m)
     : "q0", "q9", "q10","q11", "q12", "q13", "memory"
     );
}

void MathUtil::crossVec3(const float* v1, const float* v2, float* dst)
{
    asm volatile(
                 "vld1.32 {d1[1]},  [%1]         \n\t" //
                 "vld1.32 {d0},     [%2]         \n\t" //
                 "vmov.f32 s2, s1                \n\t" // q0 = (v1y, v1z, v1z, v1x)
                 
                 "vld1.32 {d2[1]},  [%3]         \n\t" //
                 "vld1.32 {d3},     [%4]         \n\t" //
                 "vmov.f32 s4, s7                  \n\t" // q1 = (v2z, v2x, v2y, v2z)
                 
                 "vmul.f32 d4, d0, d2            \n\t" // x = v1y * v2z, y = v1z * v2x
                 "vmls.f32 d4, d1, d3            \n\t" // x -= v1z * v2y, y-= v1x - v2z
                 
                 "vmul.f32 d5, d3, d1[1]         \n\t" // z = v1x * v2y
                 "vmls.f32 d5, d0, d2[1]         \n\t" // z-= v1y * vx
                 
                 "vst1.32 {d4},       [%0]!      \n\t" // V[x, y]
                 "vst1.32 {d5[0]}, [%0]          \n\t" // V[z]
                 :
                 : "r"(dst), "r"(v1), "r"((v1+1)), "r"(v2), "r"((v2+1))
                 : "q0", "q1", "q2", "memory"
                 );
}

#else

void MathUtil::addMatrix(const float* m, float scalar, float* dst)
{
    dst[0]  = m[0]  + scalar;
    dst[1]  = m[1]  + scalar;
    dst[2]  = m[2]  + scalar;
    dst[3]  = m[3]  + scalar;
    dst[4]  = m[4]  + scalar;
    dst[5]  = m[5]  + scalar;
    dst[6]  = m[6]  + scalar;
    dst[7]  = m[7]  + scalar;
    dst[8]  = m[8]  + scalar;
    dst[9]  = m[9]  + scalar;
    dst[10] = m[10] + scalar;
    dst[11] = m[11] + scalar;
    dst[12] = m[12] + scalar;
    dst[13] = m[13] + scalar;
    dst[14] = m[14] + scalar;
    dst[15] = m[15] + scalar;
}

void MathUtil::addMatrix(const float* m1, const float* m2, float* dst)
{
    dst[0]  = m1[0]  + m2[0];
    dst[1]  = m1[1]  + m2[1];
    dst[2]  = m1[2]  + m2[2];
    dst[3]  = m1[3]  + m2[3];
    dst[4]  = m1[4]  + m2[4];
    dst[5]  = m1[5]  + m2[5];
    dst[6]  = m1[6]  + m2[6];
    dst[7]  = m1[7]  + m2[7];
    dst[8]  = m1[8]  + m2[8];
    dst[9]  = m1[9]  + m2[9];
    dst[10] = m1[10] + m2[10];
    dst[11] = m1[11] + m2[11];
    dst[12] = m1[12] + m2[12];
    dst[13] = m1[13] + m2[13];
    dst[14] = m1[14] + m2[14];
    dst[15] = m1[15] + m2[15];
}

void MathUtil::subtractMatrix(const float* m1, const float* m2, float* dst)
{
    dst[0]  = m1[0]  - m2[0];
    dst[1]  = m1[1]  - m2[1];
    dst[2]  = m1[2]  - m2[2];
    dst[3]  = m1[3]  - m2[3];
    dst[4]  = m1[4]  - m2[4];
    dst[5]  = m1[5]  - m2[5];
    dst[6]  = m1[6]  - m2[6];
    dst[7]  = m1[7]  - m2[7];
    dst[8]  = m1[8]  - m2[8];
    dst[9]  = m1[9]  - m2[9];
    dst[10] = m1[10] - m2[10];
    dst[11] = m1[11] - m2[11];
    dst[12] = m1[12] - m2[12];
    dst[13] = m1[13] - m2[13];
    dst[14] = m1[14] - m2[14];
    dst[15] = m1[15] - m2[15];
}

void MathUtil::multiplyMatrix(const float* m, float scalar, float* dst)
{
    dst[0]  = m[0]  * scalar;
    dst[1]  = m[1]  * scalar;
    dst[2]  = m[2]  * scalar;
    dst[3]  = m[3]  * scalar;
    dst[4]  = m[4]  * scalar;
    dst[5]  = m[5]  * scalar;
    dst[6]  = m[6]  * scalar;
    dst[7]  = m[7]  * scalar;
    dst[8]  = m[8]  * scalar;
    dst[9]  = m[9]  * scalar;
    dst[10] = m[10] * scalar;
    dst[11] = m[11] * scalar;
    dst[12] = m[12] * scalar;
    dst[13] = m[13] * scalar;
    dst[14] = m[14] * scalar;
    dst[15] = m[15] * scalar;
}

void MathUtil::multiplyMatrix(const float* m1, const float* m2, float* dst)
{
    // Support the case where m1 or m2 is the same array as dst.
    float product[16];
    
    product[0]  = m1[0] * m2[0]  + m1[4] * m2[1] + m1[8]   * m2[2]  + m1[12] * m2[3];
    product[1]  = m1[1] * m2[0]  + m1[5] * m2[1] + m1[9]   * m2[2]  + m1[13] * m2[3];
    product[2]  = m1[2] * m2[0]  + m1[6] * m2[1] + m1[10]  * m2[2]  + m1[14] * m2[3];
    product[3]  = m1[3] * m2[0]  + m1[7] * m2[1] + m1[11]  * m2[2]  + m1[15] * m2[3];
    
    product[4]  = m1[0] * m2[4]  + m1[4] * m2[5] + m1[8]   * m2[6]  + m1[12] * m2[7];
    product[5]  = m1[1] * m2[4]  + m1[5] * m2[5] + m1[9]   * m2[6]  + m1[13] * m2[7];
    product[6]  = m1[2] * m2[4]  + m1[6] * m2[5] + m1[10]  * m2[6]  + m1[14] * m2[7];
    product[7]  = m1[3] * m2[4]  + m1[7] * m2[5] + m1[11]  * m2[6]  + m1[15] * m2[7];
    
    product[8]  = m1[0] * m2[8]  + m1[4] * m2[9] + m1[8]   * m2[10] + m1[12] * m2[11];
    product[9]  = m1[1] * m2[8]  + m1[5] * m2[9] + m1[9]   * m2[10] + m1[13] * m2[11];
    product[10] = m1[2] * m2[8]  + m1[6] * m2[9] + m1[10]  * m2[10] + m1[14] * m2[11];
    product[11] = m1[3] * m2[8]  + m1[7] * m2[9] + m1[11]  * m2[10] + m1[15] * m2[11];
    
    product[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8]  * m2[14] + m1[12] * m2[15];
    product[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9]  * m2[14] + m1[13] * m2[15];
    product[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
    product[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];
    
    memcpy(dst, product, MATRIX_SIZE);
}

void MathUtil::negateMatrix(const float* m, float* dst)
{
    dst[0]  = -m[0];
    dst[1]  = -m[1];
    dst[2]  = -m[2];
    dst[3]  = -m[3];
    dst[4]  = -m[4];
    dst[5]  = -m[5];
    dst[6]  = -m[6];
    dst[7]  = -m[7];
    dst[8]  = -m[8];
    dst[9]  = -m[9];
    dst[10] = -m[10];
    dst[11] = -m[11];
    dst[12] = -m[12];
    dst[13] = -m[13];
    dst[14] = -m[14];
    dst[15] = -m[15];
}

void MathUtil::transposeMatrix(const float* m, float* dst)
{
    float t[16] = {
        m[0], m[4], m[8], m[12],
        m[1], m[5], m[9], m[13],
        m[2], m[6], m[10], m[14],
        m[3], m[7], m[11], m[15]
    };
    memcpy(dst, t, MATRIX_SIZE);
}

void MathUtil::transformVec4(const float* m, float x, float y, float z, float w, float* dst)
{
    dst[0] = x * m[0] + y * m[4] + z * m[8] + w * m[12];
    dst[1] = x * m[1] + y * m[5] + z * m[9] + w * m[13];
    dst[2] = x * m[2] + y * m[6] + z * m[10] + w * m[14];
}

void MathUtil::transformVec4(const float* m, const float* v, float* dst)
{
    // Handle case where v == dst.
    float x = v[0] * m[0] + v[1] * m[4] + v[2] * m[8] + v[3] * m[12];
    float y = v[0] * m[1] + v[1] * m[5] + v[2] * m[9] + v[3] * m[13];
    float z = v[0] * m[2] + v[1] * m[6] + v[2] * m[10] + v[3] * m[14];
    float w = v[0] * m[3] + v[1] * m[7] + v[2] * m[11] + v[3] * m[15];
    
    dst[0] = x;
    dst[1] = y;
    dst[2] = z;
    dst[3] = w;
}

void MathUtil::crossVec3(const float* v1, const float* v2, float* dst)
{
    float x = (v1[1] * v2[2]) - (v1[2] * v2[1]);
    float y = (v1[2] * v2[0]) - (v1[0] * v2[2]);
    float z = (v1[0] * v2[1]) - (v1[1] * v2[0]);
    
    dst[0] = x;
    dst[1] = y;
    dst[2] = z;
}

#endif

NS_CC_MATH_END
