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

#ifndef SPINE_VERTEXATTACHMENT_H_
#define SPINE_VERTEXATTACHMENT_H_

#include <spine/dll.h>
#include <spine/Attachment.h>
#include <spine/Slot.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct spVertexAttachment spVertexAttachment;
struct spVertexAttachment {
	spAttachment super;

	int bonesCount;
	int* bones;

	int verticesCount;
	float* vertices;

	int worldVerticesLength;

	int id;
};

SP_API void spVertexAttachment_computeWorldVertices (spVertexAttachment* self, spSlot* slot, int start, int count, float* worldVertices, int offset, int stride);

#ifdef SPINE_SHORT_NAMES
typedef spVertexAttachment VertexAttachment;
#define VertexAttachment_computeWorldVertices(...) spVertexAttachment_computeWorldVertices(__VA_ARGS__)
#endif

#ifdef __cplusplus
}
#endif

#endif /* SPINE_VERTEXATTACHMENT_H_ */
