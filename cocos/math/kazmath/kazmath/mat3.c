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

#include <stdlib.h>
#include <memory.h>
#include <assert.h>

#include "utility.h"
#include "vec3.h"
#include "mat3.h"
#include "mat4.h"
#include "quaternion.h"

kmMat3* kmMat3Fill(kmMat3* pOut, const kmScalar* pMat)
{
    memcpy(pOut->mat, pMat, sizeof(kmScalar) * 9);
    return pOut;
}

/** Sets pOut to an identity matrix returns pOut*/
kmMat3* kmMat3Identity(kmMat3* pOut)
{
	memset(pOut->mat, 0, sizeof(kmScalar) * 9);
	pOut->mat[0] = pOut->mat[4] = pOut->mat[8] = 1.0f;
	return pOut;
}

kmScalar kmMat3Determinant(const kmMat3* pIn)
{
    kmScalar output;
    /*
    calculating the determinant following the rule of sarus,
        | 0  3  6 | 0  3 |
    m = | 1  4  7 | 1  4 |
        | 2  5  8 | 2  5 |
    now sum up the products of the diagonals going to the right (i.e. 0,4,8)
    and substract the products of the other diagonals (i.e. 2,4,6)
    */

    output = pIn->mat[0] * pIn->mat[4] * pIn->mat[8] + pIn->mat[1] * pIn->mat[5] * pIn->mat[6] + pIn->mat[2] * pIn->mat[3] * pIn->mat[7];
    output -= pIn->mat[2] * pIn->mat[4] * pIn->mat[6] + pIn->mat[0] * pIn->mat[5] * pIn->mat[7] + pIn->mat[1] * pIn->mat[3] * pIn->mat[8];

    return output;
}


kmMat3* kmMat3Adjugate(kmMat3* pOut, const kmMat3* pIn)
{
    pOut->mat[0] = pIn->mat[4] * pIn->mat[8] - pIn->mat[5] * pIn->mat[7];
    pOut->mat[1] = pIn->mat[2] * pIn->mat[7] - pIn->mat[1] * pIn->mat[8];
    pOut->mat[2] = pIn->mat[1] * pIn->mat[5] - pIn->mat[2] * pIn->mat[4];
    pOut->mat[3] = pIn->mat[5] * pIn->mat[6] - pIn->mat[3] * pIn->mat[8];
    pOut->mat[4] = pIn->mat[0] * pIn->mat[8] - pIn->mat[2] * pIn->mat[6];
    pOut->mat[5] = pIn->mat[2] * pIn->mat[3] - pIn->mat[0] * pIn->mat[5];
    pOut->mat[6] = pIn->mat[3] * pIn->mat[7] - pIn->mat[4] * pIn->mat[6];
    pOut->mat[7] = pIn->mat[1] * pIn->mat[6] - pIn->mat[0] * pIn->mat[7];
    pOut->mat[8] = pIn->mat[0] * pIn->mat[4] - pIn->mat[1] * pIn->mat[3];

    return pOut;
}

kmMat3* kmMat3Inverse(kmMat3* pOut, const kmMat3* pM)
{
    kmScalar determinate = kmMat3Determinant(pM);
    kmScalar detInv;
    kmMat3 adjugate;

    if(determinate == 0.0)
    {
        return NULL;
    }

    detInv = 1.0 / determinate;

	kmMat3Adjugate(&adjugate, pM);
	kmMat3ScalarMultiply(pOut, &adjugate, detInv);

	return pOut;
}

/** Returns true if pIn is an identity matrix */
int kmMat3IsIdentity(const kmMat3* pIn)
{
	static kmScalar identity [] = { 	1.0f, 0.0f, 0.0f,
										0.0f, 1.0f, 0.0f,
										0.0f, 0.0f, 1.0f};

	return (memcmp(identity, pIn->mat, sizeof(kmScalar) * 9) == 0);
}

/** Sets pOut to the transpose of pIn, returns pOut */
kmMat3* kmMat3Transpose(kmMat3* pOut, const kmMat3* pIn)
{
    kmScalar temp[9];
    
    temp[0] = pIn->mat[0];
    temp[1] = pIn->mat[3];
    temp[2] = pIn->mat[6];

    temp[3] = pIn->mat[1];
    temp[4] = pIn->mat[4];
    temp[5] = pIn->mat[7];

    temp[6] = pIn->mat[2];
    temp[7] = pIn->mat[5];
    temp[8] = pIn->mat[8];
        
    memcpy(&pOut->mat, temp, sizeof(kmScalar)*9);

	return pOut;
}

/* Multiplies pM1 with pM2, stores the result in pOut, returns pOut */
kmMat3* kmMat3Multiply(kmMat3* pOut, const kmMat3* pM1, const kmMat3* pM2)
{
	kmScalar mat[9];

	const kmScalar *m1 = pM1->mat, *m2 = pM2->mat;

	mat[0] = m1[0] * m2[0] + m1[3] * m2[1] + m1[6] * m2[2];
	mat[1] = m1[1] * m2[0] + m1[4] * m2[1] + m1[7] * m2[2];
	mat[2] = m1[2] * m2[0] + m1[5] * m2[1] + m1[8] * m2[2];

	mat[3] = m1[0] * m2[3] + m1[3] * m2[4] + m1[6] * m2[5];
	mat[4] = m1[1] * m2[3] + m1[4] * m2[4] + m1[7] * m2[5];
	mat[5] = m1[2] * m2[3] + m1[5] * m2[4] + m1[8] * m2[5];

	mat[6] = m1[0] * m2[6] + m1[3] * m2[7] + m1[6] * m2[8];
	mat[7] = m1[1] * m2[6] + m1[4] * m2[7] + m1[7] * m2[8];
	mat[8] = m1[2] * m2[6] + m1[5] * m2[7] + m1[8] * m2[8];

	memcpy(pOut->mat, mat, sizeof(kmScalar)*9);

	return pOut;
}

kmMat3* kmMat3ScalarMultiply(kmMat3* pOut, const kmMat3* pM, const kmScalar pFactor)
{
    kmScalar mat[9];
    int i;

    for(i = 0; i < 9; i++)
    {
        mat[i] = pM->mat[i] * pFactor;
    }

    memcpy(pOut->mat, mat, sizeof(kmScalar)*9);

	return pOut;
}

/** Assigns the value of pIn to pOut */
kmMat3* kmMat3Assign(kmMat3* pOut, const kmMat3* pIn)
{
	assert(pOut != pIn); //You have tried to self-assign!!

	memcpy(pOut->mat, pIn->mat, sizeof(kmScalar)*9);

	return pOut;
}

kmMat3* kmMat3AssignMat4(kmMat3* pOut, const kmMat4* pIn) {
    pOut->mat[0] = pIn->mat[0];
    pOut->mat[1] = pIn->mat[1];
    pOut->mat[2] = pIn->mat[2];

    pOut->mat[3] = pIn->mat[4];
    pOut->mat[4] = pIn->mat[5];
    pOut->mat[5] = pIn->mat[6];

    pOut->mat[6] = pIn->mat[8];
    pOut->mat[7] = pIn->mat[9];
    pOut->mat[8] = pIn->mat[10];
    return pOut;
}

/** Returns true if the 2 matrices are equal (approximately) */
int kmMat3AreEqual(const kmMat3* pMat1, const kmMat3* pMat2)
{
	int i;
	if (pMat1 == pMat2) {
		return KM_TRUE;
	}

	for (i = 0; i < 9; ++i) {
		if (!(pMat1->mat[i] + kmEpsilon > pMat2->mat[i] &&
            pMat1->mat[i] - kmEpsilon < pMat2->mat[i])) {
			return KM_FALSE;
        }
	}

	return KM_TRUE;
}

/* Rotation around the z axis so everything stays planar in XY */
kmMat3* kmMat3Rotation(kmMat3* pOut, const kmScalar radians)
{
	/*
         |  cos(A)  -sin(A)   0  |
     M = |  sin(A)   cos(A)   0  |
         |  0        0        1  |
	*/

	pOut->mat[0] = cosf(radians);
	pOut->mat[1] = sinf(radians);
	pOut->mat[2] = 0.0f;

	pOut->mat[3] = -sinf(radians);
	pOut->mat[4] = cosf(radians);
	pOut->mat[5] = 0.0f;

	pOut->mat[6] = 0.0f;
	pOut->mat[7] = 0.0f;
	pOut->mat[8] = 1.0f;

	return pOut;
}

/** Builds a scaling matrix */
kmMat3* kmMat3Scaling(kmMat3* pOut, const kmScalar x, const kmScalar y)
{
//	memset(pOut->mat, 0, sizeof(kmScalar) * 9);
	kmMat3Identity(pOut);
	pOut->mat[0] = x;
	pOut->mat[4] = y;

	return pOut;
}

kmMat3* kmMat3Translation(kmMat3* pOut, const kmScalar x, const kmScalar y)
{
//    memset(pOut->mat, 0, sizeof(kmScalar) * 9);
	kmMat3Identity(pOut);
	pOut->mat[6] = x;
	pOut->mat[7] = y;
//    pOut->mat[8] = 1.0;

    return pOut;
}


kmMat3* kmMat3RotationQuaternion(kmMat3* pOut, const kmQuaternion* pIn)
{
    if (!pIn || !pOut) {
	return NULL;
    }

    // First row
    pOut->mat[0] = 1.0f - 2.0f * (pIn->y * pIn->y + pIn->z * pIn->z);
    pOut->mat[1] = 2.0f * (pIn->x * pIn->y - pIn->w * pIn->z);
    pOut->mat[2] = 2.0f * (pIn->x * pIn->z + pIn->w * pIn->y);

    // Second row
    pOut->mat[3] = 2.0f * (pIn->x * pIn->y + pIn->w * pIn->z);
    pOut->mat[4] = 1.0f - 2.0f * (pIn->x * pIn->x + pIn->z * pIn->z);
    pOut->mat[5] = 2.0f * (pIn->y * pIn->z - pIn->w * pIn->x);

    // Third row
    pOut->mat[6] = 2.0f * (pIn->x * pIn->z - pIn->w * pIn->y);
    pOut->mat[7] = 2.0f * (pIn->y * pIn->z + pIn->w * pIn->x);
    pOut->mat[8] = 1.0f - 2.0f * (pIn->x * pIn->x + pIn->y * pIn->y);

    return pOut;
}

kmMat3* kmMat3RotationAxisAngle(kmMat3* pOut, const struct kmVec3* axis, kmScalar radians)
{
    kmScalar rcos = cosf(radians);
    kmScalar rsin = sinf(radians);

    pOut->mat[0] = rcos + axis->x * axis->x * (1 - rcos);
    pOut->mat[1] = axis->z * rsin + axis->y * axis->x * (1 - rcos);
    pOut->mat[2] = -axis->y * rsin + axis->z * axis->x * (1 - rcos);

    pOut->mat[3] = -axis->z * rsin + axis->x * axis->y * (1 - rcos);
    pOut->mat[4] = rcos + axis->y * axis->y * (1 - rcos);
    pOut->mat[5] = axis->x * rsin + axis->z * axis->y * (1 - rcos);

    pOut->mat[6] = axis->y * rsin + axis->x * axis->z * (1 - rcos);
    pOut->mat[7] = -axis->x * rsin + axis->y * axis->z * (1 - rcos);
    pOut->mat[8] = rcos + axis->z * axis->z * (1 - rcos);

    return pOut;
}

kmVec3* kmMat3RotationToAxisAngle(kmVec3* pAxis, kmScalar* radians, const kmMat3* pIn)
{
    /*Surely not this easy?*/
    kmQuaternion temp;
    kmQuaternionRotationMatrix(&temp, pIn);
    kmQuaternionToAxisAngle(&temp, pAxis, radians);
    return pAxis;
}

/**
 * Builds an X-axis rotation matrix and stores it in pOut, returns pOut
 */
kmMat3* kmMat3RotationX(kmMat3* pOut, const kmScalar radians)
{
	/*
		 |  1  0       0      |
	 M = |  0  cos(A) -sin(A) |
	     |  0  sin(A)  cos(A) |

	*/

	pOut->mat[0] = 1.0f;
	pOut->mat[1] = 0.0f;
	pOut->mat[2] = 0.0f;

	pOut->mat[3] = 0.0f;
	pOut->mat[4] = cosf(radians);
	pOut->mat[5] = sinf(radians);

	pOut->mat[6] = 0.0f;
	pOut->mat[7] = -sinf(radians);
	pOut->mat[8] = cosf(radians);

	return pOut;
}

/**
 * Builds a rotation matrix using the rotation around the Y-axis
 * The result is stored in pOut, pOut is returned.
 */
kmMat3* kmMat3RotationY(kmMat3* pOut, const kmScalar radians)
{
	/*
	     |  cos(A)  0   sin(A) |
	 M = |  0       1   0      |
	     | -sin(A)  0   cos(A) |
	*/

	pOut->mat[0] = cosf(radians);
	pOut->mat[1] = 0.0f;
	pOut->mat[2] = -sinf(radians);

	pOut->mat[3] = 0.0f;
	pOut->mat[4] = 1.0f;
	pOut->mat[5] = 0.0f;

	pOut->mat[6] = sinf(radians);
	pOut->mat[7] = 0.0f;
	pOut->mat[8] = cosf(radians);

	return pOut;
}

/**
 * Builds a rotation matrix around the Z-axis. The resulting
 * matrix is stored in pOut. pOut is returned.
 */
kmMat3* kmMat3RotationZ(kmMat3* pOut, const kmScalar radians)
{
	/*
	     |  cos(A)  -sin(A)   0  |
	 M = |  sin(A)   cos(A)   0  |
	     |  0        0        1  |
	*/

	pOut->mat[0] = cosf(radians);
	pOut->mat[1] =-sinf(radians);
	pOut->mat[2] = 0.0f;

	pOut->mat[3] = sinf(radians);
	pOut->mat[4] = cosf(radians);
	pOut->mat[5] = 0.0f;

	pOut->mat[6] = 0.0f;
	pOut->mat[7] = 0.0f;
	pOut->mat[8] = 1.0f;

	return pOut;
}

kmVec3* kmMat3GetUpVec3(kmVec3* pOut, const kmMat3* pIn) {
	pOut->x = pIn->mat[3];
	pOut->y = pIn->mat[4];
	pOut->z = pIn->mat[5];

	kmVec3Normalize(pOut, pOut);

	return pOut;
}

kmVec3* kmMat3GetRightVec3(kmVec3* pOut, const kmMat3* pIn) {
	pOut->x = pIn->mat[0];
	pOut->y = pIn->mat[1];
	pOut->z = pIn->mat[2];

	kmVec3Normalize(pOut, pOut);

	return pOut;
}

kmVec3* kmMat3GetForwardVec3(kmVec3* pOut, const kmMat3* pIn) {
	pOut->x = pIn->mat[6];
	pOut->y = pIn->mat[7];
	pOut->z = pIn->mat[8];

	kmVec3Normalize(pOut, pOut);

	return pOut;
}

kmMat3* kmMat3LookAt(kmMat3* pOut, const kmVec3* pEye,
                     const kmVec3* pCenter, const kmVec3* pUp)
{
    kmVec3 f, up, s, u;

    kmVec3Subtract(&f, pCenter, pEye);
    kmVec3Normalize(&f, &f);

    kmVec3Assign(&up, pUp);
    kmVec3Normalize(&up, &up);

    kmVec3Cross(&s, &f, &up);
    kmVec3Normalize(&s, &s);

    kmVec3Cross(&u, &s, &f);
    kmVec3Normalize(&s, &s);

    pOut->mat[0] = s.x;
    pOut->mat[3] = s.y;
    pOut->mat[6] = s.z;

    pOut->mat[1] = u.x;
    pOut->mat[4] = u.y;
    pOut->mat[7] = u.z;

    pOut->mat[2] = -f.x;
    pOut->mat[5] = -f.y;
    pOut->mat[8] = -f.z;

    return pOut;
}
