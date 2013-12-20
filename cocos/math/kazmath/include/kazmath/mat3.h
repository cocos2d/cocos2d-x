/*
Copyright (c) 2008, Luke Benstead.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#ifndef MAT3_H_INCLUDED
#define MAT3_H_INCLUDED

#include "CCPlatformMacros.h"
#include "utility.h"

struct kmVec3;
struct kmQuaternion;

typedef struct kmMat3{
    kmScalar mat[9];
} kmMat3;

#ifdef __cplusplus
extern "C" {
#endif

CC_DLL kmMat3* const kmMat3Fill(kmMat3* pOut, const kmScalar* pMat);
CC_DLL kmMat3* const kmMat3Adjugate(kmMat3* pOut, const kmMat3* pIn);
CC_DLL kmMat3* const kmMat3Identity(kmMat3* pOut);
CC_DLL kmMat3* const kmMat3Inverse(kmMat3* pOut, const kmScalar pDeterminate, const kmMat3* pM);
CC_DLL const int  kmMat3IsIdentity(const kmMat3* pIn);
CC_DLL kmMat3* const kmMat3Transpose(kmMat3* pOut, const kmMat3* pIn);
CC_DLL const kmScalar kmMat3Determinant(const kmMat3* pIn);
CC_DLL kmMat3* const kmMat3Multiply(kmMat3* pOut, const kmMat3* pM1, const kmMat3* pM2);
CC_DLL kmMat3* const kmMat3ScalarMultiply(kmMat3* pOut, const kmMat3* pM, const kmScalar pFactor);

CC_DLL kmMat3* const kmMat3RotationAxisAngle(kmMat3* pOut, const struct kmVec3* axis, kmScalar radians);
CC_DLL struct kmVec3* const kmMat3RotationToAxisAngle(struct kmVec3* pAxis, kmScalar* radians, const kmMat3* pIn);

CC_DLL kmMat3* const kmMat3Assign(kmMat3* pOut, const kmMat3* pIn);
CC_DLL const int  kmMat3AreEqual(const kmMat3* pM1, const kmMat3* pM2);

CC_DLL kmMat3* const kmMat3RotationX(kmMat3* pOut, const kmScalar radians);
CC_DLL kmMat3* const kmMat3RotationY(kmMat3* pOut, const kmScalar radians);
CC_DLL kmMat3* const kmMat3RotationZ(kmMat3* pOut, const kmScalar radians);

CC_DLL kmMat3* const kmMat3Rotation(kmMat3* pOut, const kmScalar radians);
CC_DLL kmMat3* const kmMat3Scaling(kmMat3* pOut, const kmScalar x, const kmScalar y);
CC_DLL kmMat3* const kmMat3Translation(kmMat3* pOut, const kmScalar x, const kmScalar y);

CC_DLL kmMat3* const kmMat3RotationQuaternion(kmMat3* pOut, const struct kmQuaternion* pIn);
CC_DLL kmMat3* const kmMat3RotationAxisAngle(kmMat3* pOut, const struct kmVec3* axis, kmScalar radians);
CC_DLL struct kmVec3* const kmMat3RotationToAxisAngle(struct kmVec3* pAxis, kmScalar* radians, const kmMat3* pIn);

#ifdef __cplusplus
}
#endif
#endif // MAT3_H_INCLUDED

