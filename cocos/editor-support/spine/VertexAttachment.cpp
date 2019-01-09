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

#ifdef SPINE_UE4
#include "SpinePluginPrivatePCH.h"
#endif

#include <spine/VertexAttachment.h>

#include <spine/Slot.h>

#include <spine/Bone.h>
#include <spine/Skeleton.h>

using namespace spine;

RTTI_IMPL(VertexAttachment, Attachment)

VertexAttachment::VertexAttachment(const String &name) : Attachment(name), _worldVerticesLength(0), _id(getNextID()) {
}

VertexAttachment::~VertexAttachment() {
}

void VertexAttachment::computeWorldVertices(Slot &slot, Vector<float> &worldVertices) {
	computeWorldVertices(slot, 0, _worldVerticesLength, worldVertices, 0);
}

void VertexAttachment::computeWorldVertices(Slot &slot, float *worldVertices) {
	computeWorldVertices(slot, 0, _worldVerticesLength, worldVertices, 0);
}

void VertexAttachment::computeWorldVertices(Slot &slot, size_t start, size_t count, Vector<float> &worldVertices, size_t offset,
											size_t stride) {
	computeWorldVertices(slot, start, count, worldVertices.buffer(), offset, stride);
}

void VertexAttachment::computeWorldVertices(Slot &slot, size_t start, size_t count, float *worldVertices, size_t offset,
	size_t stride) {
	count = offset + (count >> 1) * stride;
	Skeleton &skeleton = slot._bone._skeleton;
	Vector<float> *deformArray = &slot.getAttachmentVertices();
	Vector<float> *vertices = &_vertices;
	Vector<size_t> &bones = _bones;
	if (bones.size() == 0) {
		if (deformArray->size() > 0) {
			vertices = deformArray;
		}

		Bone &bone = slot._bone;
		float x = bone._worldX;
		float y = bone._worldY;
		float a = bone._a, b = bone._b, c = bone._c, d = bone._d;
		for (size_t vv = start, w = offset; w < count; vv += 2, w += stride) {
			float vx = (*vertices)[vv];
			float vy = (*vertices)[vv + 1];
			worldVertices[w] = vx * a + vy * b + x;
			worldVertices[w + 1] = vx * c + vy * d + y;
		}
		return;
	}

	int v = 0, skip = 0;
	for (size_t i = 0; i < start; i += 2) {
		int n = bones[v];
		v += n + 1;
		skip += n;
	}

	Vector<Bone *> &skeletonBones = skeleton.getBones();
	if (deformArray->size() == 0) {
		for (size_t w = offset, b = skip * 3; w < count; w += stride) {
			float wx = 0, wy = 0;
			int n = bones[v++];
			n += v;
			for (; v < n; v++, b += 3) {
				Bone *boneP = skeletonBones[bones[v]];
				Bone &bone = *boneP;
				float vx = (*vertices)[b];
				float vy = (*vertices)[b + 1];
				float weight = (*vertices)[b + 2];
				wx += (vx * bone._a + vy * bone._b + bone._worldX) * weight;
				wy += (vx * bone._c + vy * bone._d + bone._worldY) * weight;
			}
			worldVertices[w] = wx;
			worldVertices[w + 1] = wy;
		}
	} else {
		for (size_t w = offset, b = skip * 3, f = skip << 1; w < count; w += stride) {
			float wx = 0, wy = 0;
			int n = bones[v++];
			n += v;
			for (; v < n; v++, b += 3, f += 2) {
				Bone *boneP = skeletonBones[bones[v]];
				Bone &bone = *boneP;
				float vx = (*vertices)[b] + (*deformArray)[f];
				float vy = (*vertices)[b + 1] + (*deformArray)[f + 1];
				float weight = (*vertices)[b + 2];
				wx += (vx * bone._a + vy * bone._b + bone._worldX) * weight;
				wy += (vx * bone._c + vy * bone._d + bone._worldY) * weight;
			}
			worldVertices[w] = wx;
			worldVertices[w + 1] = wy;
		}
	}
}

bool VertexAttachment::applyDeform(VertexAttachment *sourceAttachment) {
	return this == sourceAttachment;
}

int VertexAttachment::getId() {
	return _id;
}

Vector<size_t> &VertexAttachment::getBones() {
	return _bones;
}

Vector<float> &VertexAttachment::getVertices() {
	return _vertices;
}

size_t VertexAttachment::getWorldVerticesLength() {
	return _worldVerticesLength;
}

void VertexAttachment::setWorldVerticesLength(size_t inValue) {
	_worldVerticesLength = inValue;
}

int VertexAttachment::getNextID() {
	static int nextID = 0;

	return (nextID++ & 65535) << 11;
}
