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

#include <spine/RegionAttachment.h>
#include <spine/extension.h>

typedef enum {
	BLX = 0, BLY, ULX, ULY, URX, URY, BRX, BRY
} spVertexIndex;

void _spRegionAttachment_dispose (spAttachment* attachment) {
	spRegionAttachment* self = SUB_CAST(spRegionAttachment, attachment);
	_spAttachment_deinit(attachment);
	FREE(self->path);
	FREE(self);
}

spRegionAttachment* spRegionAttachment_create (const char* name) {
	spRegionAttachment* self = NEW(spRegionAttachment);
	self->scaleX = 1;
	self->scaleY = 1;
	spColor_setFromFloats(&self->color, 1, 1, 1, 1);
	_spAttachment_init(SUPER(self), name, SP_ATTACHMENT_REGION, _spRegionAttachment_dispose);
	return self;
}

void spRegionAttachment_setUVs (spRegionAttachment* self, float u, float v, float u2, float v2, int/*bool*/rotate) {
	if (rotate) {
		self->uvs[URX] = u;
		self->uvs[URY] = v2;
		self->uvs[BRX] = u;
		self->uvs[BRY] = v;
		self->uvs[BLX] = u2;
		self->uvs[BLY] = v;
		self->uvs[ULX] = u2;
		self->uvs[ULY] = v2;
	} else {
		self->uvs[ULX] = u;
		self->uvs[ULY] = v2;
		self->uvs[URX] = u;
		self->uvs[URY] = v;
		self->uvs[BRX] = u2;
		self->uvs[BRY] = v;
		self->uvs[BLX] = u2;
		self->uvs[BLY] = v2;
	}
}

void spRegionAttachment_updateOffset (spRegionAttachment* self) {
	float regionScaleX = self->width / self->regionOriginalWidth * self->scaleX;
	float regionScaleY = self->height / self->regionOriginalHeight * self->scaleY;
	float localX = -self->width / 2 * self->scaleX + self->regionOffsetX * regionScaleX;
	float localY = -self->height / 2 * self->scaleY + self->regionOffsetY * regionScaleY;
	float localX2 = localX + self->regionWidth * regionScaleX;
	float localY2 = localY + self->regionHeight * regionScaleY;
	float radians = self->rotation * DEG_RAD;
	float cosine = COS(radians), sine = SIN(radians);
	float localXCos = localX * cosine + self->x;
	float localXSin = localX * sine;
	float localYCos = localY * cosine + self->y;
	float localYSin = localY * sine;
	float localX2Cos = localX2 * cosine + self->x;
	float localX2Sin = localX2 * sine;
	float localY2Cos = localY2 * cosine + self->y;
	float localY2Sin = localY2 * sine;
	self->offset[BLX] = localXCos - localYSin;
	self->offset[BLY] = localYCos + localXSin;
	self->offset[ULX] = localXCos - localY2Sin;
	self->offset[ULY] = localY2Cos + localXSin;
	self->offset[URX] = localX2Cos - localY2Sin;
	self->offset[URY] = localY2Cos + localX2Sin;
	self->offset[BRX] = localX2Cos - localYSin;
	self->offset[BRY] = localYCos + localX2Sin;
}

void spRegionAttachment_computeWorldVertices (spRegionAttachment* self, spBone* bone, float* vertices, int offset, int stride) {
	const float* offsets = self->offset;
	float x = bone->worldX, y = bone->worldY;
	float offsetX, offsetY;

	offsetX = offsets[BRX];
	offsetY = offsets[BRY];
	vertices[offset] = offsetX * bone->a + offsetY * bone->b + x; /* br */
	vertices[offset + 1] = offsetX * bone->c + offsetY * bone->d + y;
	offset += stride;

	offsetX = offsets[BLX];
	offsetY = offsets[BLY];
	vertices[offset] = offsetX * bone->a + offsetY * bone->b + x; /* bl */
	vertices[offset + 1] = offsetX * bone->c + offsetY * bone->d + y;
	offset += stride;

	offsetX = offsets[ULX];
	offsetY = offsets[ULY];
	vertices[offset] = offsetX * bone->a + offsetY * bone->b + x; /* ul */
	vertices[offset + 1] = offsetX * bone->c + offsetY * bone->d + y;
	offset += stride;

	offsetX = offsets[URX];
	offsetY = offsets[URY];
	vertices[offset] = offsetX * bone->a + offsetY * bone->b + x; /* ur */
	vertices[offset + 1] = offsetX * bone->c + offsetY * bone->d + y;
}
