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

#include "spine/VertexAttachment.h"
#include "spine/extension.h"

/* FIXME this is not thread-safe */
static int nextID = 0;

void _spVertexAttachment_init (spVertexAttachment* attachment) {
	attachment->id = (nextID++ & 65535) << 11;
}

void _spVertexAttachment_deinit (spVertexAttachment* attachment) {
	_spAttachment_deinit(SUPER(attachment));
	FREE(attachment->bones);
	FREE(attachment->vertices);
}

void spVertexAttachment_computeWorldVertices (spVertexAttachment* self, spSlot* slot, int start, int count, float* worldVertices, int offset, int stride) {
	spSkeleton* skeleton;
	int deformLength;
	float* deform;
	float* vertices;
	int* bones;

	count += offset;
	skeleton = slot->bone->skeleton;
	deformLength = slot->attachmentVerticesCount;
	deform = slot->attachmentVertices;
	vertices = self->vertices;
	bones = self->bones;
	if (!bones) {
		spBone* bone;
		int v, w;
		float x, y;
		if (deformLength > 0) vertices = deform;
		bone = slot->bone;
		x = bone->worldX;
		y = bone->worldY;
		for (v = start, w = offset; w < count; v += 2, w += stride) {
			float vx = vertices[v], vy = vertices[v + 1];
			worldVertices[w] = vx * bone->a + vy * bone->b + x;
			worldVertices[w + 1] = vx * bone->c + vy * bone->d + y;
		}
	} else {
		int v = 0, skip = 0, i;
		spBone** skeletonBones;
		for (i = 0; i < start; i += 2) {
			int n = bones[v];
			v += n + 1;
			skip += n;
		}
		skeletonBones = skeleton->bones;
		if (deformLength == 0) {
			int w, b;
			for (w = offset, b = skip * 3; w < count; w += stride) {
				float wx = 0, wy = 0;
				int n = bones[v++];
				n += v;
				for (; v < n; v++, b += 3) {
					spBone* bone = skeletonBones[bones[v]];
					float vx = vertices[b], vy = vertices[b + 1], weight = vertices[b + 2];
					wx += (vx * bone->a + vy * bone->b + bone->worldX) * weight;
					wy += (vx * bone->c + vy * bone->d + bone->worldY) * weight;
				}
				worldVertices[w] = wx;
				worldVertices[w + 1] = wy;
			}
		} else {
			int w, b, f;
			for (w = offset, b = skip * 3, f = skip << 1; w < count; w += stride) {
				float wx = 0, wy = 0;
				int n = bones[v++];
				n += v;
				for (; v < n; v++, b += 3, f += 2) {
					spBone* bone = skeletonBones[bones[v]];
					float vx = vertices[b] + deform[f], vy = vertices[b + 1] + deform[f + 1], weight = vertices[b + 2];
					wx += (vx * bone->a + vy * bone->b + bone->worldX) * weight;
					wy += (vx * bone->c + vy * bone->d + bone->worldY) * weight;
				}
				worldVertices[w] = wx;
				worldVertices[w + 1] = wy;
			}
		}
	}
}
