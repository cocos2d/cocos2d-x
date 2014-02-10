/*
NEON math library for the iPhone / iPod touch

Copyright (c) 2009 Justin Saunders

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising
from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it freely,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must
not claim that you wrote the original software. If you use this
software in a product, an acknowledgment in the product documentation
would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must
not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.
*/


#include "neonmatriximpl.h"

#if defined(__ARM_NEON__) && !defined(__arm64__)


void NEON_Matrix4Mul(const float* a, const float* b, float* output )
{
    __asm__ volatile
        (
        // Store A & B leaving room for q4-q7, which should be preserved
        "vldmia %1, { q0-q3 } \n\t"
        "vldmia %2, { q8-q11 }\n\t"

        // result = first column of B x first row of A
        "vmul.f32 q12, q8, d0[0]\n\t"
        "vmul.f32 q13, q8, d2[0]\n\t"
        "vmul.f32 q14, q8, d4[0]\n\t"
        "vmul.f32 q15, q8, d6[0]\n\t"

        // result += second column of B x second row of A
        "vmla.f32 q12, q9, d0[1]\n\t"
        "vmla.f32 q13, q9, d2[1]\n\t"
        "vmla.f32 q14, q9, d4[1]\n\t"
        "vmla.f32 q15, q9, d6[1]\n\t"

        // result += third column of B x third row of A
        "vmla.f32 q12, q10, d1[0]\n\t"
        "vmla.f32 q13, q10, d3[0]\n\t"
        "vmla.f32 q14, q10, d5[0]\n\t"
        "vmla.f32 q15, q10, d7[0]\n\t"

        // result += last column of B x last row of A
        "vmla.f32 q12, q11, d1[1]\n\t"
        "vmla.f32 q13, q11, d3[1]\n\t"
        "vmla.f32 q14, q11, d5[1]\n\t"
        "vmla.f32 q15, q11, d7[1]\n\t"

        // output = result registers
        "vstmia %0, { q12-q15 }"
        : // no output
    : "r" (output), "r" (a), "r" (b)     // input - note *value* of pointer doesn't change
        : "memory", "q0", "q1", "q2", "q3", "q8", "q9", "q10", "q11", "q12", "q13", "q14", "q15" //clobber
        );
}

void NEON_Matrix4Vector4Mul(const float* m, const float* v, float* output)
{
    __asm__ volatile
        (
        // Store m & v - avoiding q4-q7 which need to be preserved - q0 = result
        "vldmia %1, { q8-q11 }    \n\t"    // q8-q11 = m
        "vldmia %2, { q1 }        \n\t"    // q1     = v

        // result = first column of A x V.x
        "vmul.f32 q0, q8, d2[0]\n\t"

        // result += second column of A x V.y
        "vmla.f32 q0, q9, d2[1]\n\t"

        // result += third column of A x V.z
        "vmla.f32 q0, q10, d3[0]\n\t"

        // result += last column of A x V.w
        "vmla.f32 q0, q11, d3[1]\n\t"

        // output = result registers
        "vstmia %0, { q0 }"

        : // no output
    : "r" (output), "r" (m), "r" (v)     // input - note *value* of pointer doesn't change
        : "memory", "q0", "q1", "q8", "q9", "q10", "q11" //clobber
        );
}

void NEON_Matrix4Copy(const float *src,float* dst)
{
    __asm__ volatile
        (
        "PLD [%0, #512]\n\t" // preloading src
        "vldmia %0, { q0-q3 }\n\t" // q0-q3 = src
        "vstmia %1, { q0-q3 }"     // dst = q0-q3
        :
    : "r" (src), "r" (dst)
        : "memory", "q0", "q1", "q2", "q3" //clobber
        );
}

//rotate matrix4 by z axis, values[0] = cos(angle), values[1] = sin(angle)
void NEON_Matrix4RotateZ(float *mat, const float * values)
{
    __asm__ volatile
        (
        // Load matrix into NEON registers
        "vldmia %0, { q8-q9 }\n\t" // q8-q12 = mat (128bits)
        "vldmia %1, { d0 }\n\t" // d0 = values (128bits)


        "vmul.f32    q10, q8, d0[0]\n\t" // mOut[0-2] = m[0-2] * x
        "vmla.f32    q10, q9, d0[1]\n\t" // mOut[0-2] += m[2-4] * y

        "vmul.f32    q11, q9, d0[0]\n\t" // mOut[2-4] = m[2-4] * x
        "vmls.f32    q11, q8, d0[1]\n\t" // mOut[2-4] -= m[0-2] * y

        "vstmia %0, { q10-q11 }" // mOut = mat = q10-q11

        : // no explicit output
    : "r" (mat), "r" (values)
        : "memory", "d0",   "q8", "q9",  "q10", "q11" //clobber
        );
}

//translate matrix4, values[0] = x, values[1] = y, values[2] = z;
void NEON_Matrix4Translate(float* mat, const float* values)
{
    __asm__ volatile
        (
        // Load matrix into NEON registers

        "vldmia %0, { q8-q11 }\n\t" // q8-q12 = mat (128bits)
        "vldmia %1, { d0-d1 }\n\t" // d0 = values (128bits)

        "vmla.f32    q11, q8, d0[0]\n\t" // mOut[0-2] = m[0-2] * x
        "vmla.f32    q11, q9, d0[1]\n\t" // mOut[0-2] += m[2-4] * y
        "vmla.f32    q11, q10, d1[0]\n\t" // mOut[0-2] += m[2-4] * y

        "vstmia %0, { q8-q11 }" // mOut = mat = q10-q11

        : // no explicit output
    : "r" (mat), "r" (values)
        : "memory", "d0", "d1",   "q8", "q9",  "q10", "q11" //clobber
        );
}

//matrix4 multiply vec2
void NEON_Matrix4Vec2(const float* m1, const float* v1, float* vOut)
{
    __asm__ volatile
        (
        "vldmia %0, { q4-q7 }\n\t"        // q8-q11 = matrix
        "vldmia %1, { q0-q1 }\n\t"        // q0-q1  = input vertices

        // result = first column of A x V.x
        "vmov.f32 d4, d14\n\t"
        "vmla.f32 d4, d8, d0[0]\n\t"
        "vmla.f32 d4, d10, d0[1]\n\t"

        "vmov.f32 d5, d14\n\t"
        "vmla.f32 d5, d8, d1[0]\n\t"
        "vmla.f32 d5, d10, d1[1]\n\t"

        // reverse order
        "vmov.f32 d7, d14\n\t"
        "vmla.f32 d7, d8, d2[0]\n\t"
        "vmla.f32 d7, d10, d2[1]\n\t"

        "vmov.f32 d6, d14\n\t"
        "vmla.f32 d6, d8, d3[0]\n\t"
        "vmla.f32 d6, d10, d3[1]\n\t"

        // output = result registers
        "vstmia %2, { q2-q3 }"

        : // no output
    : "r" (m1), "r" (v1), "r" (vOut)
        : "memory", "q0", "q1",    "q2", "q3",     "q4", "q5",  "q6", "q7"
        );
}

#endif
