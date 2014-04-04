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

#include "vec3.h"
#include "vec4.h"
#include "plane.h"
#include "mat4.h"

kmScalar kmPlaneDot(const kmPlane* pP, const kmVec4* pV)
{
    //a*x + b*y + c*z + d*w

    return (pP->a * pV->x +
	    pP->b * pV->y +
	    pP->c * pV->z +
	    pP->d * pV->w);
}

kmScalar kmPlaneDotCoord(const kmPlane* pP, const kmVec3* pV)
{
    return (pP->a * pV->x +
	    pP->b * pV->y +
	    pP->c * pV->z + pP->d);
}

kmScalar kmPlaneDotNormal(const kmPlane* pP, const kmVec3* pV)
{
    return (pP->a * pV->x +
	    pP->b * pV->y +
	    pP->c * pV->z);
}

kmPlane* kmPlaneFromNormalAndDistance(kmPlane* plane, const struct kmVec3* normal, const kmScalar dist) {
    plane->a = normal->x;
    plane->b = normal->y;
    plane->c = normal->z;
    plane->d = dist;

    return plane;
}

kmPlane* kmPlaneFromPointAndNormal(kmPlane* pOut, const kmVec3* pPoint, const kmVec3* pNormal)
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
kmPlane* kmPlaneFromPoints(kmPlane* pOut, const kmVec3* p1, const kmVec3* p2, const kmVec3* p3)
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

// Added by tlensing (http://icedcoffee-framework.org)
kmVec3* kmPlaneIntersectLine(kmVec3* pOut, const kmPlane* pP, const kmVec3* pV1, const kmVec3* pV2)
{
    /*
     n = (Planea, Planeb, Planec)
     d = V − U
     Out = U − d⋅(Pd + n⋅U)⁄(d⋅n) [iff d⋅n ≠ 0]
     */
    kmVec3 d; // direction from V1 to V2
    kmVec3Subtract(&d, pV2, pV1); // Get the direction vector
    
    kmVec3 n; // plane normal
    n.x = pP->a;
    n.y = pP->b;
    n.z = pP->c;
    kmVec3Normalize(&n, &n);
    
    kmScalar nt = -(n.x * pV1->x + n.y * pV1->y + n.z * pV1->z + pP->d);
    kmScalar dt = (n.x * d.x + n.y * d.y + n.z * d.z);
    
    if (fabs(dt) < kmEpsilon) {
        pOut = NULL;
        return pOut; // line parallel or contained
    }
    
    kmScalar t = nt/dt;
    pOut->x = pV1->x + d.x * t;
    pOut->y = pV1->y + d.y * t;
    pOut->z = pV1->z + d.z * t;
    
    return pOut;
}

kmPlane* kmPlaneNormalize(kmPlane* pOut, const kmPlane* pP)
{
	kmVec3 n;
        kmScalar l = 0;

        if (!pP->a && !pP->b && !pP->c) {
                pOut->a = pP->a;
                pOut->b = pP->b;
                pOut->c = pP->c;
                pOut->d = pP->d;
                return pOut;
        }

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

kmPlane* kmPlaneScale(kmPlane* pOut, const kmPlane* pP, kmScalar s)
{
	assert(0 && "Not implemented");
    return NULL;
}

/**
 * Returns POINT_INFRONT_OF_PLANE if pP is infront of pIn. Returns
 * POINT_BEHIND_PLANE if it is behind. Returns POINT_ON_PLANE otherwise
 */
KM_POINT_CLASSIFICATION kmPlaneClassifyPoint(const kmPlane* pIn, const kmVec3* pP)
{
   // This function will determine if a point is on, in front of, or behind
   // the plane.  First we store the dot product of the plane and the point.
   kmScalar distance = pIn->a * pP->x + pIn->b * pP->y + pIn->c * pP->z + pIn->d;

   // Simply put if the dot product is greater than 0 then it is infront of it.
   // If it is less than 0 then it is behind it.  And if it is 0 then it is on it.
   if(distance > kmEpsilon) return POINT_INFRONT_OF_PLANE;
   if(distance < -kmEpsilon) return POINT_BEHIND_PLANE;

   return POINT_ON_PLANE;
}

kmPlane* kmPlaneExtractFromMat4(kmPlane* pOut, const struct kmMat4* pIn, kmInt row) {
    int scale = (row < 0) ? -1 : 1;
	row = abs(row) - 1;
	
	pOut->a = pIn->mat[3] + scale * pIn->mat[row];
	pOut->b = pIn->mat[7] + scale * pIn->mat[row + 4];
	pOut->c = pIn->mat[11] + scale * pIn->mat[row + 8];
	pOut->d = pIn->mat[15] + scale * pIn->mat[row + 12];
	
	return kmPlaneNormalize(pOut, pOut);
}

kmVec3* kmPlaneGetIntersection(kmVec3* pOut, const kmPlane* p1, const kmPlane* p2, const kmPlane* p3) {
    kmVec3 n1, n2, n3, cross;
    kmVec3 r1, r2, r3;
    double denom = 0;
    
    kmVec3Fill(&n1, p1->a, p1->b, p1->c);
    kmVec3Fill(&n2, p2->a, p2->b, p2->c);
    kmVec3Fill(&n3, p3->a, p3->b, p3->c);
    
    kmVec3Cross(&cross, &n2, &n3);

    denom = kmVec3Dot(&n1, &cross);

    if (kmAlmostEqual(denom, 0.0)) {
        return NULL;
    }

    kmVec3Cross(&r1, &n2, &n3);
    kmVec3Cross(&r2, &n3, &n1);
    kmVec3Cross(&r3, &n1, &n2);

    kmVec3Scale(&r1, &r1, -p1->d);
    kmVec3Scale(&r2, &r2, p2->d);
    kmVec3Scale(&r3, &r3, p3->d);

    kmVec3Subtract(pOut, &r1, &r2);
    kmVec3Subtract(pOut, pOut, &r3);
    kmVec3Scale(pOut, pOut, 1.0 / denom);

    //p = -d1 * ( n2.Cross ( n3 ) ) – d2 * ( n3.Cross ( n1 ) ) – d3 * ( n1.Cross ( n2 ) ) / denom;

    return pOut;
}

kmPlane* kmPlaneFill(kmPlane* plane, kmScalar a, kmScalar b, kmScalar c, kmScalar d) {
    plane->a = a;
    plane->b = b;
    plane->c = c;
    plane->d = d;

    return plane;
}
