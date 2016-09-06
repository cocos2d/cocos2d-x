/******************************************************************************
 * Spine Runtimes Software License
 * Version 2.3
 * 
 * Copyright (c) 2013-2015, Esoteric Software
 * All rights reserved.
 * 
 * You are granted a perpetual, non-exclusive, non-sublicensable and
 * non-transferable license to use, install, execute and perform the Spine
 * Runtimes Software (the "Software") and derivative works solely for personal
 * or internal use. Without the written permission of Esoteric Software (see
 * Section 2 of the Spine Software License Agreement), you may not (a) modify,
 * translate, adapt or otherwise create derivative works, improvements of the
 * Software or develop new applications using the Software or (b) remove,
 * delete, alter or obscure any trademarks or any copyright, trademark, patent
 * or other intellectual property or proprietary rights notices on or in the
 * Software, including any copy thereof. Redistributions in binary or source
 * form must include this license and terms.
 * 
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#include <spine/VertexAttachment.h>
#include <spine/extension.h>

void _spVertexAttachment_deinit (spVertexAttachment* attachment) {
	_spAttachment_deinit(SUPER(attachment));
	FREE(attachment->bones);
	FREE(attachment->vertices);
}

void spVertexAttachment_computeWorldVertices (spVertexAttachment* self, spSlot* slot, float* worldVertices) {
	spVertexAttachment_computeWorldVertices1(self, 0, self->worldVerticesLength, slot, worldVertices, 0);
}

void spVertexAttachment_computeWorldVertices1 (spVertexAttachment* self, int start, int count, spSlot* slot, float* worldVertices, int offset) {
	spSkeleton* skeleton;
	float x, y;
	int deformLength;
	float* deform;
	float* vertices;
	int* bones;

	count += offset;
	skeleton = slot->bone->skeleton;
	x = skeleton->x;
	y = skeleton->y;
	deformLength = slot->attachmentVerticesCount;
	deform = slot->attachmentVertices;
	vertices = self->vertices;
	bones = self->bones;
	if (!bones) {
		spBone* bone;
		int v, w;
		if (deformLength > 0) vertices = deform;
		bone = slot->bone;
		x += bone->worldX;
		y += bone->worldY;
		for (v = start, w = offset; w < count; v += 2, w += 2) {
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
			for (w = offset, b = skip * 3; w < count; w += 2) {
				float wx = x, wy = y;
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
			for (w = offset, b = skip * 3, f = skip << 1; w < count; w += 2) {
				float wx = x, wy = y;
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
