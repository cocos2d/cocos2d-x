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

#ifndef PLANE_H_INCLUDED
#define PLANE_H_INCLUDED

#define KM_PLANE_LEFT 0
#define KM_PLANE_RIGHT 1
#define KM_PLANE_BOTTOM 2
#define KM_PLANE_TOP 3
#define KM_PLANE_NEAR 4
#define KM_PLANE_FAR 5

#include "platform/CCPlatformMacros.h"
#include "utility.h"

struct kmVec3;
struct kmVec4;
struct kmMat4;

typedef struct kmPlane {
    kmScalar     a, b, c, d;
} kmPlane;

#ifdef __cplusplus
extern "C" {
#endif

typedef enum POINT_CLASSIFICATION {
    POINT_INFRONT_OF_PLANE = 0,
    POINT_BEHIND_PLANE,
    POINT_ON_PLANE,
} POINT_CLASSIFICATION;

CC_DLL const kmScalar kmPlaneDot(const kmPlane* pP, const struct kmVec4* pV);
CC_DLL const kmScalar kmPlaneDotCoord(const kmPlane* pP, const struct kmVec3* pV);
CC_DLL const kmScalar kmPlaneDotNormal(const kmPlane* pP, const struct kmVec3* pV);
CC_DLL kmPlane* const kmPlaneFromPointNormal(kmPlane* pOut, const struct kmVec3* pPoint, const struct kmVec3* pNormal);
CC_DLL kmPlane* const kmPlaneFromPoints(kmPlane* pOut, const struct kmVec3* p1, const struct kmVec3* p2, const struct kmVec3* p3);
CC_DLL kmVec3*  const kmPlaneIntersectLine(struct kmVec3* pOut, const kmPlane* pP, const struct kmVec3* pV1, const struct kmVec3* pV2);
CC_DLL kmPlane* const kmPlaneNormalize(kmPlane* pOut, const kmPlane* pP);
CC_DLL kmPlane* const kmPlaneScale(kmPlane* pOut, const kmPlane* pP, kmScalar s);
CC_DLL const POINT_CLASSIFICATION kmPlaneClassifyPoint(const kmPlane* pIn, const kmVec3* pP); /** Classifys a point against a plane */

#ifdef __cplusplus
}
#endif

#endif // PLANE_H_INCLUDED
