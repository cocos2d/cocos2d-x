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

#include "kazmath/mat3.h"
#include "kazmath/vec2.h"
#include "kazmath/utility.h"

kmVec2* kmVec2Fill(kmVec2* pOut, kmScalar x, kmScalar y)
{
    pOut->x = x;
    pOut->y = y;
    return pOut;
}

kmScalar kmVec2Length(const kmVec2* pIn)
{
    return sqrtf(kmSQR(pIn->x) + kmSQR(pIn->y));
}

kmScalar kmVec2LengthSq(const kmVec2* pIn)
{
    return kmSQR(pIn->x) + kmSQR(pIn->y);
}

kmVec2* kmVec2Normalize(kmVec2* pOut, const kmVec2* pIn)
{
	kmScalar l = 1.0f / kmVec2Length(pIn);

	kmVec2 v;
	v.x = pIn->x * l;
	v.y = pIn->y * l;

	pOut->x = v.x;
	pOut->y = v.y;

	return pOut;
}

kmVec2* kmVec2Add(kmVec2* pOut, const kmVec2* pV1, const kmVec2* pV2)
{
	pOut->x = pV1->x + pV2->x;
	pOut->y = pV1->y + pV2->y;

	return pOut;
}

kmScalar kmVec2Dot(const kmVec2* pV1, const kmVec2* pV2)
{
    return pV1->x * pV2->x + pV1->y * pV2->y;
}

kmVec2* kmVec2Subtract(kmVec2* pOut, const kmVec2* pV1, const kmVec2* pV2)
{
	pOut->x = pV1->x - pV2->x;
	pOut->y = pV1->y - pV2->y;

	return pOut;
}

kmVec2* kmVec2Transform(kmVec2* pOut, const kmVec2* pV, const kmMat3* pM)
{
    kmVec2 v;

    v.x = pV->x * pM->mat[0] + pV->y * pM->mat[3] + pM->mat[6];
    v.y = pV->x * pM->mat[1] + pV->y * pM->mat[4] + pM->mat[7];

    pOut->x = v.x;
    pOut->y = v.y;

    return pOut;
}

kmVec2* kmVec2TransformCoord(kmVec2* pOut, const kmVec2* pV, const kmMat3* pM)
{
	assert(0);
    return NULL;
}

kmVec2* kmVec2Scale(kmVec2* pOut, const kmVec2* pIn, const kmScalar s)
{
	pOut->x = pIn->x * s;
	pOut->y = pIn->y * s;

	return pOut;
}

int kmVec2AreEqual(const kmVec2* p1, const kmVec2* p2)
{
	return (
				(p1->x < p2->x + kmEpsilon && p1->x > p2->x - kmEpsilon) &&
				(p1->y < p2->y + kmEpsilon && p1->y > p2->y - kmEpsilon)
			);
}
