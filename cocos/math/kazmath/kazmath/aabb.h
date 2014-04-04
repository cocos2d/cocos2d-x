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

#ifndef KAZMATH_AABB_H_INCLUDED
#define KAZMATH_AABB_H_INCLUDED

#include "CCPlatformMacros.h"

#include "vec3.h"
#include "utility.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A struture that represents an axis-aligned
 * bounding box.
 */
typedef struct kmAABB {
    kmVec3 min; /** The max corner of the box */
    kmVec3 max; /** The min corner of the box */
} kmAABB;


CC_DLL kmAABB* kmAABBInitialize(kmAABB* pBox, const kmVec3* centre, const kmScalar width, const kmScalar height, const kmScalar depth);
CC_DLL int kmAABBContainsPoint(const kmAABB* pBox, const kmVec3* pPoint);
CC_DLL kmAABB* kmAABBAssign(kmAABB* pOut, const kmAABB* pIn);
CC_DLL kmAABB* kmAABBScale(kmAABB* pOut, const kmAABB* pIn, kmScalar s);
CC_DLL kmBool kmAABBIntersectsTriangle(kmAABB* box, const kmVec3* p1, const kmVec3* p2, const kmVec3* p3);
CC_DLL kmEnum kmAABBContainsAABB(const kmAABB* container, const kmAABB* to_check);
CC_DLL kmScalar kmAABBDiameterX(const kmAABB* aabb);
CC_DLL kmScalar kmAABBDiameterY(const kmAABB* aabb);
CC_DLL kmScalar kmAABBDiameterZ(const kmAABB* aabb);
CC_DLL kmVec3* kmAABBCentre(const kmAABB* aabb, kmVec3* pOut);

#ifdef __cplusplus
}
#endif

#endif
