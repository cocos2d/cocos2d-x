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

#ifndef __C3DNEON_MATRIX_IMPL_H__
#define __C3DNEON_MATRIX_IMPL_H__

#ifdef __arm__
#if defined(__QNX__) || defined(CC_TARGET_QT5)|| defined(ANDROID) || defined(I3D_ARCH_ARM) || defined(__native_client__) || defined(TIZEN) // MARMALADE CHANGE: Added for Marmalade support
// blackberry and android don't have arm/arch.h but it defines __arm__
#else
#include "arm/arch.h"
#endif 
#endif // __arm__

// Matrices are assumed to be stored in column major format according to OpenGL
// specification.

#ifdef __cplusplus
extern "C" {
#endif


// Multiplies two 4x4 matrices (a,b) outputting a 4x4 matrix (output)
void NEON_Matrix4Mul(const float* a, const float* b, float* output );

// Multiplies a 4x4 matrix (m) with a vector 4 (v), outputting a vector 4
void NEON_Matrix4Vector4Mul(const float* m, const float* v, float* output);

// the following functions added by Xiao Yang 
//ref to https://github.com/manucorporat/FORZE2D/blob/master/FORZE/Optimized/neon_support.h
// copy matrix4 from src to dsts, 
void NEON_Matrix4Copy(const float * src, float* dst);

//rotate matrix4 by z axis, values[0] = cos(angle), values[1] = sin(angle)
void NEON_Matrix4RotateZ(float *mat, const float * values);

//translate matrix4, values[0] = x, values[1] = y, values[2] = z;
void NEON_Matrix4Translate(float* mat, const float* values);

//matrix4 multiply vec2
void NEON_Matrix4Vec2(const float* m1, const float* v1, float* vOut);

#ifdef __cplusplus
}
#endif

#endif // __NEON_MATRIX_IMPL_H__
