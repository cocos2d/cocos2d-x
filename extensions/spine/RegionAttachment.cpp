/*******************************************************************************
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#include <spine/RegionAttachment.h>
#include <math.h>
#include <spine/extension.h>

namespace cocos2d { namespace extension {

RegionAttachment* RegionAttachment_create (const char* name) {
	RegionAttachment* self = NEW(RegionAttachment);
	self->scaleX = 1;
	self->scaleY = 1;
	_Attachment_init(SUPER(self), name, ATTACHMENT_REGION, _Attachment_deinit);
	return self;
}

void RegionAttachment_setUVs (RegionAttachment* self, float u, float v, float u2, float v2, int/*bool*/rotate) {
	if (rotate) {
		self->uvs[VERTEX_X2] = u;
		self->uvs[VERTEX_Y2] = v2;
		self->uvs[VERTEX_X3] = u;
		self->uvs[VERTEX_Y3] = v;
		self->uvs[VERTEX_X4] = u2;
		self->uvs[VERTEX_Y4] = v;
		self->uvs[VERTEX_X1] = u2;
		self->uvs[VERTEX_Y1] = v2;
	} else {
		self->uvs[VERTEX_X1] = u;
		self->uvs[VERTEX_Y1] = v2;
		self->uvs[VERTEX_X2] = u;
		self->uvs[VERTEX_Y2] = v;
		self->uvs[VERTEX_X3] = u2;
		self->uvs[VERTEX_Y3] = v;
		self->uvs[VERTEX_X4] = u2;
		self->uvs[VERTEX_Y4] = v2;
	}
}

void RegionAttachment_updateOffset (RegionAttachment* self) {
	float regionScaleX = self->width / self->regionOriginalWidth * self->scaleX;
	float regionScaleY = self->height / self->regionOriginalHeight * self->scaleY;
	float localX = -self->width / 2 * self->scaleX + self->regionOffsetX * regionScaleX;
	float localY = -self->height / 2 * self->scaleY + self->regionOffsetY * regionScaleY;
	float localX2 = localX + self->regionWidth * regionScaleX;
	float localY2 = localY + self->regionHeight * regionScaleY;
	float radians = (float)(self->rotation * 3.1415926535897932385 / 180);
#ifdef __STDC_VERSION__
	float cosine = cosf(radians);
	float sine = sinf(radians);
#else
	float cosine = (float)cos(radians);
	float sine = (float)sin(radians);
#endif
	float localXCos = localX * cosine + self->x;
	float localXSin = localX * sine;
	float localYCos = localY * cosine + self->y;
	float localYSin = localY * sine;
	float localX2Cos = localX2 * cosine + self->x;
	float localX2Sin = localX2 * sine;
	float localY2Cos = localY2 * cosine + self->y;
	float localY2Sin = localY2 * sine;
	self->offset[VERTEX_X1] = localXCos - localYSin;
	self->offset[VERTEX_Y1] = localYCos + localXSin;
	self->offset[VERTEX_X2] = localXCos - localY2Sin;
	self->offset[VERTEX_Y2] = localY2Cos + localXSin;
	self->offset[VERTEX_X3] = localX2Cos - localY2Sin;
	self->offset[VERTEX_Y3] = localY2Cos + localX2Sin;
	self->offset[VERTEX_X4] = localX2Cos - localYSin;
	self->offset[VERTEX_Y4] = localYCos + localX2Sin;
}

void RegionAttachment_computeVertices (RegionAttachment* self, float x, float y, Bone* bone, float* vertices) {
	float* offset = self->offset;
	x += bone->worldX;
	y += bone->worldY;
	vertices[VERTEX_X1] = offset[VERTEX_X1] * bone->m00 + offset[VERTEX_Y1] * bone->m01 + x;
	vertices[VERTEX_Y1] = offset[VERTEX_X1] * bone->m10 + offset[VERTEX_Y1] * bone->m11 + y;
	vertices[VERTEX_X2] = offset[VERTEX_X2] * bone->m00 + offset[VERTEX_Y2] * bone->m01 + x;
	vertices[VERTEX_Y2] = offset[VERTEX_X2] * bone->m10 + offset[VERTEX_Y2] * bone->m11 + y;
	vertices[VERTEX_X3] = offset[VERTEX_X3] * bone->m00 + offset[VERTEX_Y3] * bone->m01 + x;
	vertices[VERTEX_Y3] = offset[VERTEX_X3] * bone->m10 + offset[VERTEX_Y3] * bone->m11 + y;
	vertices[VERTEX_X4] = offset[VERTEX_X4] * bone->m00 + offset[VERTEX_Y4] * bone->m01 + x;
	vertices[VERTEX_Y4] = offset[VERTEX_X4] * bone->m10 + offset[VERTEX_Y4] * bone->m11 + y;
}

}} // namespace cocos2d { namespace extension {