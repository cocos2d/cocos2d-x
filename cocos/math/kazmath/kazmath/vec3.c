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

/**
 * @file vec3.c
 */

#include <assert.h>
#include <memory.h>

#include "utility.h"
#include "vec4.h"
#include "mat4.h"
#include "mat3.h"
#include "vec3.h"
#include "plane.h"
#include "ray3.h"

const kmVec3 KM_VEC3_POS_Z = { 0, 0, 1 };
const kmVec3 KM_VEC3_NEG_Z = { 0, 0, -1 };
const kmVec3 KM_VEC3_POS_Y = { 0, 1, 0 };
const kmVec3 KM_VEC3_NEG_Y = { 0, -1, 0 };
const kmVec3 KM_VEC3_NEG_X = { -1, 0, 0 };
const kmVec3 KM_VEC3_POS_X = { 1, 0, 0 };
const kmVec3 KM_VEC3_ZERO = { 0, 0, 0 };

/**
 * Fill a kmVec3 structure using 3 floating point values
 * The result is store in pOut, returns pOut
 */
kmVec3* kmVec3Fill(kmVec3* pOut, kmScalar x, kmScalar y, kmScalar z)
{
    pOut->x = x;
    pOut->y = y;
    pOut->z = z;
    return pOut;
}


/**
 * Returns the length of the vector
 */
kmScalar kmVec3Length(const kmVec3* pIn)
{
	return sqrtf(kmSQR(pIn->x) + kmSQR(pIn->y) + kmSQR(pIn->z));
}

/**
 * Returns the square of the length of the vector
 */
kmScalar kmVec3LengthSq(const kmVec3* pIn)
{
	return kmSQR(pIn->x) + kmSQR(pIn->y) + kmSQR(pIn->z);
}

/// Returns the interpolation of 2 4D vectors based on t.
kmVec3* kmVec3Lerp(kmVec3* pOut, const kmVec3* pV1, const kmVec3* pV2, kmScalar t) {
    pOut->x = pV1->x + t * ( pV2->x - pV1->x ); 
    pOut->y = pV1->y + t * ( pV2->y - pV1->y ); 
    pOut->z = pV1->z + t * ( pV2->z - pV1->z ); 
    return pOut;
}

 /**
  * Returns the vector passed in set to unit length
  * the result is stored in pOut.
  */
kmVec3* kmVec3Normalize(kmVec3* pOut, const kmVec3* pIn)
{
        if (!pIn->x && !pIn->y && !pIn->z)
                return kmVec3Assign(pOut, pIn);

        kmScalar l = 1.0f / kmVec3Length(pIn);

	kmVec3 v;
	v.x = pIn->x * l;
	v.y = pIn->y * l;
	v.z = pIn->z * l;

	pOut->x = v.x;
	pOut->y = v.y;
	pOut->z = v.z;

	return pOut;
}

/**
 * Returns a vector perpendicular to 2 other vectors.
 * The result is stored in pOut.
 */
kmVec3* kmVec3Cross(kmVec3* pOut, const kmVec3* pV1, const kmVec3* pV2)
{

	kmVec3 v;

	v.x = (pV1->y * pV2->z) - (pV1->z * pV2->y);
	v.y = (pV1->z * pV2->x) - (pV1->x * pV2->z);
	v.z = (pV1->x * pV2->y) - (pV1->y * pV2->x);

	pOut->x = v.x;
	pOut->y = v.y;
	pOut->z = v.z;

	return pOut;
}

/**
 * Returns the cosine of the angle between 2 vectors
 */
kmScalar kmVec3Dot(const kmVec3* pV1, const kmVec3* pV2)
{
	return (  pV1->x * pV2->x
			+ pV1->y * pV2->y
			+ pV1->z * pV2->z );
}

/**
 * Adds 2 vectors and returns the result. The resulting
 * vector is stored in pOut.
 */
kmVec3* kmVec3Add(kmVec3* pOut, const kmVec3* pV1, const kmVec3* pV2)
{
	kmVec3 v;

	v.x = pV1->x + pV2->x;
	v.y = pV1->y + pV2->y;
	v.z = pV1->z + pV2->z;

	pOut->x = v.x;
	pOut->y = v.y;
	pOut->z = v.z;

	return pOut;
}

 /**
  * Subtracts 2 vectors and returns the result. The result is stored in
  * pOut.
  */
kmVec3* kmVec3Subtract(kmVec3* pOut, const kmVec3* pV1, const kmVec3* pV2)
{
	kmVec3 v;

	v.x = pV1->x - pV2->x;
	v.y = pV1->y - pV2->y;
	v.z = pV1->z - pV2->z;

	pOut->x = v.x;
	pOut->y = v.y;
	pOut->z = v.z;

	return pOut;
}

kmVec3* kmVec3Mul( kmVec3* pOut,const kmVec3* pV1, const kmVec3* pV2 ) {
    pOut->x = pV1->x * pV2->x;
    pOut->y = pV1->y * pV2->y;
    pOut->z = pV1->z * pV2->z;
    return pOut;
}

kmVec3* kmVec3Div( kmVec3* pOut,const kmVec3* pV1, const kmVec3* pV2 ) {
    if ( pV2->x && pV2->y && pV2->z ){
        pOut->x = pV1->x / pV2->x;
        pOut->y = pV1->y / pV2->y;
        pOut->z = pV1->z / pV2->z;
    }
    return pOut;
}

kmVec3* kmVec3MultiplyMat3(kmVec3* pOut, const kmVec3* pV, const kmMat3* pM) {
    kmVec3 v;

    v.x = pV->x * pM->mat[0] + pV->y * pM->mat[3] + pV->z * pM->mat[6];
    v.y = pV->x * pM->mat[1] + pV->y * pM->mat[4] + pV->z * pM->mat[7];
    v.z = pV->x * pM->mat[2] + pV->y * pM->mat[5] + pV->z * pM->mat[8];

    pOut->x = v.x;
    pOut->y = v.y;
    pOut->z = v.z;

    return pOut;
}

/**
 * Multiplies vector (x, y, z, 1) by a given matrix. The result
 * is stored in pOut. pOut is returned.
 */

kmVec3* kmVec3MultiplyMat4(kmVec3* pOut, const kmVec3* pV, const kmMat4* pM) {
    kmVec3 v;

    v.x = pV->x * pM->mat[0] + pV->y * pM->mat[4] + pV->z * pM->mat[8] + pM->mat[12];
    v.y = pV->x * pM->mat[1] + pV->y * pM->mat[5] + pV->z * pM->mat[9] + pM->mat[13];
    v.z = pV->x * pM->mat[2] + pV->y * pM->mat[6] + pV->z * pM->mat[10] + pM->mat[14];

    pOut->x = v.x;
    pOut->y = v.y;
    pOut->z = v.z;

    return pOut;
}


kmVec3* kmVec3Transform(kmVec3* pOut, const kmVec3* pV, const kmMat4* pM)
{
	/*
        @deprecated Should intead use kmVec3MultiplyMat4
	*/
    return kmVec3MultiplyMat4(pOut, pV, pM);
}

kmVec3* kmVec3InverseTransform(kmVec3* pOut, const kmVec3* pVect, const kmMat4* pM)
{
	kmVec3 v1, v2;

	v1.x = pVect->x - pM->mat[12];
	v1.y = pVect->y - pM->mat[13];
	v1.z = pVect->z - pM->mat[14];

	v2.x = v1.x * pM->mat[0] + v1.y * pM->mat[1] + v1.z * pM->mat[2];
	v2.y = v1.x * pM->mat[4] + v1.y * pM->mat[5] + v1.z * pM->mat[6];
	v2.z = v1.x * pM->mat[8] + v1.y * pM->mat[9] + v1.z * pM->mat[10];

	pOut->x = v2.x;
	pOut->y = v2.y;
	pOut->z = v2.z;

	return pOut;
}

kmVec3* kmVec3InverseTransformNormal(kmVec3* pOut, const kmVec3* pVect, const kmMat4* pM)
{
	kmVec3 v;

	v.x = pVect->x * pM->mat[0] + pVect->y * pM->mat[1] + pVect->z * pM->mat[2];
	v.y = pVect->x * pM->mat[4] + pVect->y * pM->mat[5] + pVect->z * pM->mat[6];
	v.z = pVect->x * pM->mat[8] + pVect->y * pM->mat[9] + pVect->z * pM->mat[10];

	pOut->x = v.x;
	pOut->y = v.y;
	pOut->z = v.z;

	return pOut;
}


kmVec3* kmVec3TransformCoord(kmVec3* pOut, const kmVec3* pV, const kmMat4* pM)
{
	/*
        a = (Vx, Vy, Vz, 1)
        b = (a×M)T
        Out = 1⁄bw(bx, by, bz)
	*/

    kmVec4 v;
    kmVec4 inV;
    kmVec4Fill(&inV, pV->x, pV->y, pV->z, 1.0);

    kmVec4Transform(&v, &inV,pM);

	pOut->x = v.x / v.w;
	pOut->y = v.y / v.w;
	pOut->z = v.z / v.w;

	return pOut;
}

kmVec3* kmVec3TransformNormal(kmVec3* pOut, const kmVec3* pV, const kmMat4* pM)
{
/*
    a = (Vx, Vy, Vz, 0)
    b = (a×M)T
    Out = (bx, by, bz)
*/
    //Omits the translation, only scaling + rotating
	kmVec3 v;

	v.x = pV->x * pM->mat[0] + pV->y * pM->mat[4] + pV->z * pM->mat[8];
	v.y = pV->x * pM->mat[1] + pV->y * pM->mat[5] + pV->z * pM->mat[9];
	v.z = pV->x * pM->mat[2] + pV->y * pM->mat[6] + pV->z * pM->mat[10];

	pOut->x = v.x;
	pOut->y = v.y;
	pOut->z = v.z;

    return pOut;

}

/**
 * Scales a vector to length s. Does not normalize first,
 * you should do that!
 */
kmVec3* kmVec3Scale(kmVec3* pOut, const kmVec3* pIn, const kmScalar s)
{
	pOut->x = pIn->x * s;
	pOut->y = pIn->y * s;
	pOut->z = pIn->z * s;

	return pOut;
}

/**
 * Returns KM_TRUE if the 2 vectors are approximately equal
 */
int kmVec3AreEqual(const kmVec3* p1, const kmVec3* p2)
{
	if ((p1->x < (p2->x + kmEpsilon) && p1->x > (p2->x - kmEpsilon)) &&
		(p1->y < (p2->y + kmEpsilon) && p1->y > (p2->y - kmEpsilon)) &&
		(p1->z < (p2->z + kmEpsilon) && p1->z > (p2->z - kmEpsilon))) {
		return 1;
	}

	return 0;
}

/**
 * Assigns pIn to pOut. Returns pOut. If pIn and pOut are the same
 * then nothing happens but pOut is still returned
 */
kmVec3* kmVec3Assign(kmVec3* pOut, const kmVec3* pIn) {
	if (pOut == pIn) {
		return pOut;
	}

	pOut->x = pIn->x;
	pOut->y = pIn->y;
	pOut->z = pIn->z;

	return pOut;
}

/**
 * Sets all the elements of pOut to zero. Returns pOut.
 */
kmVec3* kmVec3Zero(kmVec3* pOut) {
	pOut->x = 0.0f;
	pOut->y = 0.0f;
	pOut->z = 0.0f;

	return pOut;
}

/**
 * Get the rotations that would make a (0,0,1) direction vector point in the same direction as this direction vector.
 * Useful for orienting vector towards a point.
 *
 * Returns a rotation vector containing the X (pitch) and Y (raw) rotations (in degrees) that when applied to a
 * +Z (e.g. 0, 0, 1) direction vector would make it point in the same direction as this vector. The Z (roll) rotation
 * is always 0, since two Euler rotations are sufficient to point in any given direction.
 *
 * Code ported from Irrlicht: http://irrlicht.sourceforge.net/
 */
kmVec3* kmVec3GetHorizontalAngle(kmVec3* pOut, const kmVec3 *pIn) {
   const kmScalar z1 = sqrt(pIn->x * pIn->x + pIn->z * pIn->z);

   pOut->y = kmRadiansToDegrees(atan2(pIn->x, pIn->z));
   if (pOut->y < 0)
      pOut->y += 360;
   if (pOut->y >= 360)
      pOut->y -= 360;

   pOut->x = kmRadiansToDegrees(atan2(z1, pIn->y)) - 90.0;
   if (pOut->x < 0)
      pOut->x += 360;
   if (pOut->x >= 360)
      pOut->x -= 360;

   return pOut;
}

/**
 * Builds a direction vector from input vector.
 * Input vector is assumed to be rotation vector composed from 3 Euler angle rotations, in degrees.
 * The forwards vector will be rotated by the input vector
 *
 * Code ported from Irrlicht: http://irrlicht.sourceforge.net/
 */
kmVec3* kmVec3RotationToDirection(kmVec3* pOut, const kmVec3* pIn, const kmVec3* forwards)
{
   const kmScalar xr = kmDegreesToRadians(pIn->x);
   const kmScalar yr = kmDegreesToRadians(pIn->y);
   const kmScalar zr = kmDegreesToRadians(pIn->z);
   const kmScalar cr = cos(xr), sr = sin(xr);
   const kmScalar cp = cos(yr), sp = sin(yr);
   const kmScalar cy = cos(zr), sy = sin(zr);

   const kmScalar srsp = sr*sp;
   const kmScalar crsp = cr*sp;

   const kmScalar pseudoMatrix[] = {
      (cp*cy), (cp*sy), (-sp),
      (srsp*cy-cr*sy), (srsp*sy+cr*cy), (sr*cp),
      (crsp*cy+sr*sy), (crsp*sy-sr*cy), (cr*cp)
   };

   pOut->x = forwards->x * pseudoMatrix[0] +
             forwards->y * pseudoMatrix[3] +
             forwards->z * pseudoMatrix[6];

   pOut->y = forwards->x * pseudoMatrix[1] +
             forwards->y * pseudoMatrix[4] +
             forwards->z * pseudoMatrix[7];

   pOut->z = forwards->x * pseudoMatrix[2] +
             forwards->y * pseudoMatrix[5] +
             forwards->z * pseudoMatrix[8];

   return pOut;
}

kmVec3* kmVec3ProjectOnToPlane(kmVec3* pOut, const kmVec3* point, const struct kmPlane* plane) {
    kmRay3 ray;
    kmVec3Assign(&ray.start, point);
    ray.dir.x = -plane->a;
    ray.dir.y = -plane->b;
    ray.dir.z = -plane->c;

    kmRay3IntersectPlane(pOut, &ray, plane);
    return pOut;
}
