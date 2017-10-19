/******************************************************************************
 * Spine Runtimes Software License v2.5
 *
 * Copyright (c) 2013-2016, Esoteric Software
 * All rights reserved.
 *
 * You are granted a perpetual, non-exclusive, non-sublicensable, and
 * non-transferable license to use, install, execute, and perform the Spine
 * Runtimes software and derivative works solely for personal or internal
 * use. Without the written permission of Esoteric Software (see Section 2 of
 * the Spine Software License Agreement), you may not (a) modify, translate,
 * adapt, or develop new applications using the Spine Runtimes or otherwise
 * create derivative works or improvements of the Spine Runtimes or (b) remove,
 * delete, alter, or obscure any trademarks or any copyright, trademark, patent,
 * or other intellectual property or proprietary rights notices on or in the
 * Software, including any copy thereof. Redistributions in binary or source
 * form must include this license and terms.
 *
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, BUSINESS INTERRUPTION, OR LOSS OF
 * USE, DATA, OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef SPINE_SKELETONCLIPPING_H
#define SPINE_SKELETONCLIPPING_H

#include <spine/dll.h>
#include <spine/Array.h>
#include <spine/ClippingAttachment.h>
#include <spine/Slot.h>
#include <spine/Triangulator.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct spSkeletonClipping {
	spTriangulator* triangulator;
	spFloatArray* clippingPolygon;
	spFloatArray* clipOutput;
	spFloatArray* clippedVertices;
	spFloatArray* clippedUVs;
	spUnsignedShortArray* clippedTriangles;
	spFloatArray* scratch;
	spClippingAttachment* clipAttachment;
	spArrayFloatArray* clippingPolygons;
} spSkeletonClipping;

SP_API spSkeletonClipping* spSkeletonClipping_create();
SP_API int spSkeletonClipping_clipStart(spSkeletonClipping* self, spSlot* slot, spClippingAttachment* clip);
SP_API void spSkeletonClipping_clipEnd(spSkeletonClipping* self, spSlot* slot);
SP_API void spSkeletonClipping_clipEnd2(spSkeletonClipping* self);
SP_API int /*boolean*/ spSkeletonClipping_isClipping(spSkeletonClipping* self);
SP_API void spSkeletonClipping_clipTriangles(spSkeletonClipping* self, float* vertices, int verticesLength, unsigned short* triangles, int trianglesLength, float* uvs, int stride);
SP_API void spSkeletonClipping_dispose(spSkeletonClipping* self);

#ifdef __cplusplus
}
#endif

#endif /* SPINE_SKELETONCLIPPING_H */
