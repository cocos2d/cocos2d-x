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
#include <stdlib.h>

#include "kazmath/vec3.h"
#include "kazmath/vec4.h"
#include "kazmath/plane.h"

const kmScalar kmPlaneDot(const kmPlane* pP, const kmVec4* pV)
{
    //a*x + b*y + c*z + d*w

    return (pP->a * pV->x +
	    pP->b * pV->y +
	    pP->c * pV->z +
	    pP->d * pV->w);
}

const kmScalar kmPlaneDotCoord(const kmPlane* pP, const kmVec3* pV)
{
    return (pP->a * pV->x +
	    pP->b * pV->y +
	    pP->c * pV->z + pP->d);
}

const kmScalar kmPlaneDotNormal(const kmPlane* pP, const kmVec3* pV)
{
    return (pP->a * pV->x +
	    pP->b * pV->y +
	    pP->c * pV->z);
}

kmPlane* const kmPlaneFromPointNormal(kmPlane* pOut, const kmVec3* pPoint, const kmVec3* pNormal)
{
    /*
	Planea = Nx
	Planeb = Ny
	Planec = Nz
	Planed = −N⋅P
    */


    pOut->a = pNormal->x;
    pOut->b = pNormal->y;
    pOut->c = pNormal->z;
    pOut->d = -kmVec3Dot(pNormal, pPoint);

    return pOut;
}

/**
 * Creates a plane from 3 points. The result is stored in pOut.
 * pOut is returned.
 */
kmPlane* const kmPlaneFromPoints(kmPlane* pOut, const kmVec3* p1, const kmVec3* p2, const kmVec3* p3)
{
    /*
    v = (B − A) × (C − A)
    n = 1⁄|v| v
    Outa = nx
    Outb = ny
    Outc = nz
    Outd = −n⋅A
    */

    kmVec3 n, v1, v2;
    kmVec3Subtract(&v1, p2, p1); //Create the vectors for the 2 sides of the triangle
    kmVec3Subtract(&v2, p3, p1);
    kmVec3Cross(&n, &v1, &v2); //Use the cross product to get the normal

    kmVec3Normalize(&n, &n); //Normalize it and assign to pOut->m_N

    pOut->a = n.x;
    pOut->b = n.y;
    pOut->c = n.z;
    pOut->d = kmVec3Dot(kmVec3Scale(&n, &n, -1.0), p1);

    return pOut;
}

kmVec3* const kmPlaneIntersectLine(kmVec3* pOut, const kmPlane* pP, const kmVec3* pV1, const kmVec3* pV2)
{
    /*
	    n = (Planea, Planeb, Planec)
	    d = V − U
	    Out = U − d⋅(Pd + n⋅U)⁄(d⋅n) [iff d⋅n ≠ 0]
    */
    kmVec3 d;
    assert(0 && "Not implemented");


    kmVec3Subtract(&d, pV2, pV1); //Get the direction vector


    //TODO: Continue here!
    /*if (fabs(kmVec3Dot(&pP->m_N, &d)) > kmEpsilon)
    {
	    //If we get here then the plane and line are parallel (i.e. no intersection)
	    pOut = nullptr; //Set to nullptr

	    return pOut;
    } */

    return NULL;
}

kmPlane* const kmPlaneNormalize(kmPlane* pOut, const kmPlane* pP)
{
	kmVec3 n;
    kmScalar l = 0;

	n.x = pP->a;
	n.y = pP->b;
	n.z = pP->c;

	l = 1.0f / kmVec3Length(&n); //Get 1/length
	kmVec3Normalize(&n, &n); //Normalize the vector and assign to pOut

	pOut->a = n.x;
	pOut->b = n.y;
	pOut->c = n.z;

	pOut->d = pP->d * l; //Scale the D value and assign to pOut

	return pOut;
}

kmPlane* const kmPlaneScale(kmPlane* pOut, const kmPlane* pP, kmScalar s)
{
	assert(0 && "Not implemented");
    return NULL;
}

/**
 * Returns POINT_INFRONT_OF_PLANE if pP is infront of pIn. Returns
 * POINT_BEHIND_PLANE if it is behind. Returns POINT_ON_PLANE otherwise
 */
const POINT_CLASSIFICATION kmPlaneClassifyPoint(const kmPlane* pIn, const kmVec3* pP)
{
   // This function will determine if a point is on, in front of, or behind
   // the plane.  First we store the dot product of the plane and the point.
   float distance = pIn->a * pP->x + pIn->b * pP->y + pIn->c * pP->z + pIn->d;

   // Simply put if the dot product is greater than 0 then it is infront of it.
   // If it is less than 0 then it is behind it.  And if it is 0 then it is on it.
   if(distance > 0.001) return POINT_INFRONT_OF_PLANE;
   if(distance < -0.001) return POINT_BEHIND_PLANE;

   return POINT_ON_PLANE;
}

