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


#include <assert.h>
#include <memory.h>
#include <string.h>
#include "mat4.h"
#include "utility.h"
#include "mat3.h"
#include "vec3.h"
#include "quaternion.h"

int kmQuaternionAreEqual(const kmQuaternion* p1, const kmQuaternion* p2) {
    if ((p1->x < (p2->x + kmEpsilon) && p1->x > (p2->x - kmEpsilon)) &&
        (p1->y < (p2->y + kmEpsilon) && p1->y > (p2->y - kmEpsilon)) &&
        (p1->z < (p2->z + kmEpsilon) && p1->z > (p2->z - kmEpsilon)) &&
        (p1->w < (p2->w + kmEpsilon) && p1->w > (p2->w - kmEpsilon))) {
        return 1;
    }

    return 0;
}

kmQuaternion* kmQuaternionFill(kmQuaternion* pOut, kmScalar x, kmScalar y, kmScalar z, kmScalar w) {
	pOut->x = x;
	pOut->y = y;
	pOut->z = z;
	pOut->w = w;
	return pOut;
}
///< Returns the dot product of the 2 quaternions
kmScalar kmQuaternionDot(const kmQuaternion* q1, const kmQuaternion* q2)
{
	/* A dot B = B dot A = AtBt + AxBx + AyBy + AzBz */

	return (q1->w * q2->w +
			q1->x * q2->x +
			q1->y * q2->y +
			q1->z * q2->z);
}

///< Returns the exponential of the quaternion
kmQuaternion* kmQuaternionExp(kmQuaternion* pOut, const kmQuaternion* pIn)
{
	assert(0);

	return pOut;
}

///< Makes the passed quaternion an identity quaternion
kmQuaternion* kmQuaternionIdentity(kmQuaternion* pOut)
{
	pOut->x = 0.0;
	pOut->y = 0.0;
	pOut->z = 0.0;
	pOut->w = 1.0;

	return pOut;
}

///< Returns the inverse of the passed Quaternion
kmQuaternion* kmQuaternionInverse(kmQuaternion* pOut,
											const kmQuaternion* pIn)
{
	kmScalar l = kmQuaternionLength(pIn);

	if (fabs(l) < kmEpsilon)
	{
		pOut->x = 0.0;
		pOut->y = 0.0;
		pOut->z = 0.0;
		pOut->w = 0.0;

		return pOut;
	}

    pOut->x = -pIn->x;
    pOut->y = -pIn->y;
    pOut->z = -pIn->z;
    pOut->w = pIn->w;

	return pOut;
}

///< Returns true if the quaternion is an identity quaternion
int kmQuaternionIsIdentity(const kmQuaternion* pIn)
{
	return (pIn->x == 0.0 && pIn->y == 0.0 && pIn->z == 0.0 &&
				pIn->w == 1.0);
}

///< Returns the length of the quaternion
kmScalar kmQuaternionLength(const kmQuaternion* pIn)
{
    return sqrt(kmQuaternionLengthSq(pIn));
}

///< Returns the length of the quaternion squared (prevents a sqrt)
kmScalar kmQuaternionLengthSq(const kmQuaternion* pIn)
{
    return pIn->x * pIn->x + pIn->y * pIn->y + pIn->z * pIn->z + pIn->w * pIn->w;
}

///< Returns the natural logarithm
kmQuaternion* kmQuaternionLn(kmQuaternion* pOut,
										const kmQuaternion* pIn)
{
	/*
		A unit quaternion, is defined by:
		Q == (cos(theta), sin(theta) * v) where |v| = 1
		The natural logarithm of Q is, ln(Q) = (0, theta * v)
	*/

	assert(0);

	return pOut;
}

///< Multiplies 2 quaternions together
extern
kmQuaternion* kmQuaternionMultiply(kmQuaternion* pOut,
                                 const kmQuaternion* qu1,
                                 const kmQuaternion* qu2)
{
    kmQuaternion tmp1, tmp2;
    kmQuaternionAssign(&tmp1, qu1);
    kmQuaternionAssign(&tmp2, qu2);

    //Just aliasing
    kmQuaternion* q1 = &tmp1;
    kmQuaternion* q2 = &tmp2;

	pOut->x = q1->w * q2->x + q1->x * q2->w + q1->y * q2->z - q1->z * q2->y;
	pOut->y = q1->w * q2->y + q1->y * q2->w + q1->z * q2->x - q1->x * q2->z;
	pOut->z = q1->w * q2->z + q1->z * q2->w + q1->x * q2->y - q1->y * q2->x;
    pOut->w = q1->w * q2->w - q1->x * q2->x - q1->y * q2->y - q1->z * q2->z;

	return pOut;
}

///< Normalizes a quaternion
kmQuaternion* kmQuaternionNormalize(kmQuaternion* pOut,
											const kmQuaternion* pIn)
{
	kmScalar length = kmQuaternionLength(pIn);

    if (fabs(length) < kmEpsilon)
    {
        pOut->x = 0.0;
        pOut->y = 0.0;
        pOut->z = 0.0;
        pOut->w = 0.0;

        return pOut;
    }

    kmQuaternionFill(pOut,
        pOut->x / length,
        pOut->y / length,
        pOut->z / length,
        pOut->w / length
    );

	return pOut;
}

///< Rotates a quaternion around an axis
kmQuaternion* kmQuaternionRotationAxisAngle(kmQuaternion* pOut,
									const kmVec3* pV,
									kmScalar angle)
{
    kmScalar rad = angle * 0.5f;
	kmScalar scale	= sinf(rad);

	pOut->x = pV->x * scale;
	pOut->y = pV->y * scale;
	pOut->z = pV->z * scale;
    pOut->w = cosf(rad);

	kmQuaternionNormalize(pOut, pOut);

	return pOut;
}

///< Creates a quaternion from a rotation matrix
kmQuaternion* kmQuaternionRotationMatrix(kmQuaternion* pOut,
										const kmMat3* pIn)
{
/*
Note: The OpenGL matrices are transposed from the description below
taken from the Matrix and Quaternion FAQ

    if ( mat[0] > mat[5] && mat[0] > mat[10] )  {	// Column 0:
        S  = sqrt( 1.0 + mat[0] - mat[5] - mat[10] ) * 2;
        X = 0.25 * S;
        Y = (mat[4] + mat[1] ) / S;
        Z = (mat[2] + mat[8] ) / S;
        W = (mat[9] - mat[6] ) / S;
    } else if ( mat[5] > mat[10] ) {			// Column 1:
        S  = sqrt( 1.0 + mat[5] - mat[0] - mat[10] ) * 2;
        X = (mat[4] + mat[1] ) / S;
        Y = 0.25 * S;
        Z = (mat[9] + mat[6] ) / S;
        W = (mat[2] - mat[8] ) / S;
    } else {						// Column 2:
        S  = sqrt( 1.0 + mat[10] - mat[0] - mat[5] ) * 2;
        X = (mat[2] + mat[8] ) / S;
        Y = (mat[9] + mat[6] ) / S;
        Z = 0.25 * S;
        W = (mat[4] - mat[1] ) / S;
    }
*/

	kmScalar x, y, z, w;
	kmScalar *pMatrix = NULL;
	kmScalar m4x4[16] = {0};
	kmScalar scale = 0.0f;
	kmScalar diagonal = 0.0f;

	if(!pIn) {
		return NULL;
	}

/*	0 3 6
	1 4 7
	2 5 8

	0 1 2 3
	4 5 6 7
	8 9 10 11
	12 13 14 15*/

	m4x4[0]  = pIn->mat[0];
	m4x4[1]  = pIn->mat[3];
	m4x4[2]  = pIn->mat[6];
	m4x4[4]  = pIn->mat[1];
	m4x4[5]  = pIn->mat[4];
	m4x4[6]  = pIn->mat[7];
	m4x4[8]  = pIn->mat[2];
	m4x4[9]  = pIn->mat[5];
	m4x4[10] = pIn->mat[8];
	m4x4[15] = 1;
	pMatrix = &m4x4[0];

	diagonal = pMatrix[0] + pMatrix[5] + pMatrix[10] + 1;

	if(diagonal > kmEpsilon) {
		// Calculate the scale of the diagonal
		scale = (kmScalar)sqrt(diagonal ) * 2;

		// Calculate the x, y, x and w of the quaternion through the respective equation
		x = ( pMatrix[9] - pMatrix[6] ) / scale;
		y = ( pMatrix[2] - pMatrix[8] ) / scale;
		z = ( pMatrix[4] - pMatrix[1] ) / scale;
		w = 0.25f * scale;
	}
	else
	{
		// If the first element of the diagonal is the greatest value
		if ( pMatrix[0] > pMatrix[5] && pMatrix[0] > pMatrix[10] )
		{
			// Find the scale according to the first element, and double that value
			scale = (kmScalar)sqrt( 1.0f + pMatrix[0] - pMatrix[5] - pMatrix[10] ) * 2.0f;

			// Calculate the x, y, x and w of the quaternion through the respective equation
			x = 0.25f * scale;
			y = (pMatrix[4] + pMatrix[1] ) / scale;
			z = (pMatrix[2] + pMatrix[8] ) / scale;
			w = (pMatrix[9] - pMatrix[6] ) / scale;
		}
		// Else if the second element of the diagonal is the greatest value
		else if (pMatrix[5] > pMatrix[10])
		{
			// Find the scale according to the second element, and double that value
			scale = (kmScalar)sqrt( 1.0f + pMatrix[5] - pMatrix[0] - pMatrix[10] ) * 2.0f;

			// Calculate the x, y, x and w of the quaternion through the respective equation
			x = (pMatrix[4] + pMatrix[1] ) / scale;
			y = 0.25f * scale;
			z = (pMatrix[9] + pMatrix[6] ) / scale;
			w = (pMatrix[2] - pMatrix[8] ) / scale;
		}
		// Else the third element of the diagonal is the greatest value
		else
		{
			// Find the scale according to the third element, and double that value
			scale  = (kmScalar)sqrt( 1.0f + pMatrix[10] - pMatrix[0] - pMatrix[5] ) * 2.0f;

			// Calculate the x, y, x and w of the quaternion through the respective equation
			x = (pMatrix[2] + pMatrix[8] ) / scale;
			y = (pMatrix[9] + pMatrix[6] ) / scale;
			z = 0.25f * scale;
			w = (pMatrix[4] - pMatrix[1] ) / scale;
		}
	}

	pOut->x = x;
	pOut->y = y;
	pOut->z = z;
	pOut->w = w;

	return pOut;
}

///< Create a quaternion from yaw, pitch and roll
kmQuaternion* kmQuaternionRotationPitchYawRoll(kmQuaternion* pOut,
                                                kmScalar pitch,
                                                kmScalar yaw,
												kmScalar roll)
{
    assert(pitch <= 2*kmPI);
    assert(yaw <= 2*kmPI);
    assert(roll <= 2*kmPI);

    // Finds the Sin and Cosin for each half angles.
    float sY = sinf(yaw * 0.5);
    float cY = cosf(yaw * 0.5);
    float sZ = sinf(roll * 0.5);
    float cZ = cosf(roll * 0.5);
    float sX = sinf(pitch * 0.5);
    float cX = cosf(pitch * 0.5);

    // Formula to construct a new Quaternion based on Euler Angles.
    pOut->w = cY * cZ * cX - sY * sZ * sX;
    pOut->x = sY * sZ * cX + cY * cZ * sX;
    pOut->y = sY * cZ * cX + cY * sZ * sX;
    pOut->z = cY * sZ * cX - sY * cZ * sX;

    return pOut;
}

///< Interpolate between 2 quaternions
kmQuaternion* kmQuaternionSlerp(kmQuaternion* pOut,
								const kmQuaternion* q1,
								const kmQuaternion* q2,
								kmScalar t)
{

    kmScalar dot = kmQuaternionDot(q1, q2);
    const double DOT_THRESHOLD = 0.9995;

    if (dot > DOT_THRESHOLD) {
        kmQuaternion diff;
        kmQuaternionSubtract(&diff, q2, q1);
        kmQuaternionScale(&diff, &diff, t);

        kmQuaternionAdd(pOut, q1, &diff);
        kmQuaternionNormalize(pOut, pOut);
        return pOut;
    }

    dot = kmClamp(dot, -1, 1);

    kmScalar theta_0 = acos(dot);
    kmScalar theta = theta_0 * t;

    kmQuaternion tmp;
    kmQuaternionScale(&tmp, q1, dot);
    kmQuaternionSubtract(&tmp, q2, &tmp);
    kmQuaternionNormalize(&tmp, &tmp);

    kmQuaternion t1, t2;
    kmQuaternionScale(&t1, q1, cos(theta));
    kmQuaternionScale(&t2, &tmp, sin(theta));

    kmQuaternionAdd(pOut, &t1, &t2);

	return pOut;
}

///< Get the axis and angle of rotation from a quaternion
void kmQuaternionToAxisAngle(const kmQuaternion* pIn,
								kmVec3* pAxis,
								kmScalar* pAngle)
{
	kmScalar 	tempAngle;		// temp angle
	kmScalar	scale;			// temp vars

	tempAngle = acosf(pIn->w);
	scale = sqrtf(kmSQR(pIn->x) + kmSQR(pIn->y) + kmSQR(pIn->z));

	if (((scale > -kmEpsilon) && scale < kmEpsilon)
		|| (scale < 2*kmPI + kmEpsilon && scale > 2*kmPI - kmEpsilon))		// angle is 0 or 360 so just simply set axis to 0,0,1 with angle 0
	{
		*pAngle = 0.0f;

		pAxis->x = 0.0f;
		pAxis->y = 0.0f;
		pAxis->z = 1.0f;
	}
	else
	{
		*pAngle = tempAngle * 2.0f;		// angle in radians

		pAxis->x = pIn->x / scale;
		pAxis->y = pIn->y / scale;
		pAxis->z = pIn->z / scale;
		kmVec3Normalize(pAxis, pAxis);
	}
}

kmQuaternion* kmQuaternionScale(kmQuaternion* pOut,
										const kmQuaternion* pIn,
										kmScalar s)
{
	pOut->x = pIn->x * s;
	pOut->y = pIn->y * s;
	pOut->z = pIn->z * s;
	pOut->w = pIn->w * s;

	return pOut;
}

kmQuaternion* kmQuaternionAssign(kmQuaternion* pOut, const kmQuaternion* pIn)
{
	memcpy(pOut, pIn, sizeof(kmScalar) * 4);

	return pOut;
}

kmQuaternion* kmQuaternionSubtract(kmQuaternion* pOut, const kmQuaternion* pQ1, const kmQuaternion* pQ2) {
    pOut->x = pQ1->x - pQ2->x;
    pOut->y = pQ1->y - pQ2->y;
    pOut->z = pQ1->z - pQ2->z;
    pOut->w = pQ1->w - pQ2->w;

    return pOut;
}

kmQuaternion* kmQuaternionAdd(kmQuaternion* pOut, const kmQuaternion* pQ1, const kmQuaternion* pQ2)
{
	pOut->x = pQ1->x + pQ2->x;
	pOut->y = pQ1->y + pQ2->y;
	pOut->z = pQ1->z + pQ2->z;
	pOut->w = pQ1->w + pQ2->w;

	return pOut;
}

/** Adapted from the OGRE engine!

	Gets the shortest arc quaternion to rotate this vector to the destination
	vector.
@remarks
	If you call this with a dest vector that is close to the inverse
	of this vector, we will rotate 180 degrees around the 'fallbackAxis'
	(if specified, or a generated axis if not) since in this case
	ANY axis of rotation is valid.
*/

kmQuaternion* kmQuaternionRotationBetweenVec3(kmQuaternion* pOut, const kmVec3* vec1, const kmVec3* vec2, const kmVec3* fallback) {

	kmVec3 v1, v2;
    kmScalar a;

	kmVec3Assign(&v1, vec1);
	kmVec3Assign(&v2, vec2);

	kmVec3Normalize(&v1, &v1);
	kmVec3Normalize(&v2, &v2);

	a = kmVec3Dot(&v1, &v2);

	if (a >= 1.0) {
		kmQuaternionIdentity(pOut);
		return pOut;
	}

	if (a < (1e-6f - 1.0f))	{
		if (fabs(kmVec3LengthSq(fallback)) < kmEpsilon) {
            kmQuaternionRotationAxisAngle(pOut, fallback, kmPI);
		} else {
			kmVec3 axis;
			kmVec3 X;
			X.x = 1.0;
			X.y = 0.0;
			X.z = 0.0;


			kmVec3Cross(&axis, &X, vec1);

			//If axis is zero
			if (fabs(kmVec3LengthSq(&axis)) < kmEpsilon) {
				kmVec3 Y;
				Y.x = 0.0;
				Y.y = 1.0;
				Y.z = 0.0;

				kmVec3Cross(&axis, &Y, vec1);
			}

			kmVec3Normalize(&axis, &axis);

            kmQuaternionRotationAxisAngle(pOut, &axis, kmPI);
		}
	} else {
		kmScalar s = sqrtf((1+a) * 2);
		kmScalar invs = 1 / s;

		kmVec3 c;
		kmVec3Cross(&c, &v1, &v2);

		pOut->x = c.x * invs;
		pOut->y = c.y * invs;
        pOut->z = c.z * invs;
        pOut->w = s * 0.5f;

		kmQuaternionNormalize(pOut, pOut);
	}

	return pOut;

}

kmVec3* kmQuaternionMultiplyVec3(kmVec3* pOut, const kmQuaternion* q, const kmVec3* v) {
	kmVec3 uv, uuv, qvec;

	qvec.x = q->x;
	qvec.y = q->y;
	qvec.z = q->z;

	kmVec3Cross(&uv, &qvec, v);
	kmVec3Cross(&uuv, &qvec, &uv);

	kmVec3Scale(&uv, &uv, (2.0f * q->w));
	kmVec3Scale(&uuv, &uuv, 2.0f);

	kmVec3Add(pOut, v, &uv);
	kmVec3Add(pOut, pOut, &uuv);

	return pOut;
}

kmVec3* kmQuaternionGetUpVec3(kmVec3* pOut, const kmQuaternion* pIn) {
    return kmQuaternionMultiplyVec3(pOut, pIn, &KM_VEC3_POS_Y);
}

kmVec3* kmQuaternionGetRightVec3(kmVec3* pOut, const kmQuaternion* pIn) {
    return kmQuaternionMultiplyVec3(pOut, pIn, &KM_VEC3_POS_X);
}

kmVec3* kmQuaternionGetForwardVec3RH(kmVec3* pOut, const kmQuaternion* pIn) {
    return kmQuaternionMultiplyVec3(pOut, pIn, &KM_VEC3_NEG_Z);
}

kmVec3* kmQuaternionGetForwardVec3LH(kmVec3* pOut, const kmQuaternion* pIn) {
    return kmQuaternionMultiplyVec3(pOut, pIn, &KM_VEC3_POS_Z);
}

kmScalar kmQuaternionGetPitch(const kmQuaternion* q) {
    float result = atan2(2 * (q->y * q->z + q->w * q->x), q->w * q->w - q->x * q->x - q->y * q->y + q->z * q->z);
    return result;
}

kmScalar kmQuaternionGetYaw(const kmQuaternion* q) {
    float result = asin(-2 * (q->x * q->z - q->w * q->y));
    return result;
}

kmScalar kmQuaternionGetRoll(const kmQuaternion* q) {
    float result = atan2(2 * (q->x * q->y + q->w * q->z), q->w * q->w + q->x * q->x - q->y * q->y - q->z * q->z);
    return result;
}

kmQuaternion* kmQuaternionLookRotation(kmQuaternion* pOut, const kmVec3* direction, const kmVec3* up) {
    kmMat3 tmp;
    kmMat3LookAt(&tmp, &KM_VEC3_ZERO, direction, up);
    return kmQuaternionNormalize(pOut, kmQuaternionRotationMatrix(pOut, &tmp));
/*
    if(!direction->x && !direction->y && !direction->z) {
        return kmQuaternionIdentity(pOut);
    }

    kmVec3 right;
    kmVec3Cross(&right, up, direction);

    pOut->w = sqrtf(1.0f + right.x + up->y + direction->z) * 0.5f;

    float w4_recip = 1.0f / (4.0f * pOut->w);

    pOut->x = (up->z - direction->y) * w4_recip;
    pOut->y = (direction->x - right.z) * w4_recip;
    pOut->z = (right.y - up->x) * w4_recip;

    return kmQuaternionNormalize(pOut, pOut);*/
}
