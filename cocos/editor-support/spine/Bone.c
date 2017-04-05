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

#include <spine/Bone.h>
#include <spine/extension.h>
#include <stdio.h>
static int yDown;

void spBone_setYDown (int value) {
	yDown = value;
}

int spBone_isYDown () {
	return yDown;
}

spBone* spBone_create (spBoneData* data, spSkeleton* skeleton, spBone* parent) {
	spBone* self = NEW(spBone);
	CONST_CAST(spBoneData*, self->data) = data;
	CONST_CAST(spSkeleton*, self->skeleton) = skeleton;
	CONST_CAST(spBone*, self->parent) = parent;
	spBone_setToSetupPose(self);
	return self;
}

void spBone_dispose (spBone* self) {
	FREE(self->children);
	FREE(self);
}

void spBone_updateWorldTransform (spBone* self) {
	spBone_updateWorldTransformWith(self, self->x, self->y, self->rotation, self->scaleX, self->scaleY, self->shearX, self->shearY);
}

void spBone_updateWorldTransformWith (spBone* self, float x, float y, float rotation, float scaleX, float scaleY, float shearX, float shearY) {
	float cosine, sine;
	float pa, pb, pc, pd;
	spBone* parent = self->parent;

	self->ax = x;
	self->ay = y;
	self->arotation = rotation;
	self->ascaleX = scaleX;
	self->ascaleY = scaleY;
	self->ashearX = shearX;
	self->ashearY = shearY;
	self->appliedValid = 1;

	if (!parent) { /* Root bone. */
		float rotationY = rotation + 90 + shearY;
		float la = COS_DEG(rotation + shearX) * scaleX;
		float lb = COS_DEG(rotationY) * scaleY;
		float lc = SIN_DEG(rotation + shearX) * scaleX;
		float ld = SIN_DEG(rotationY) * scaleY;
		if (self->skeleton->flipX) {
			x = -x;
			la = -la;
			lb = -lb;
		}
		if (self->skeleton->flipY != yDown) {
			y = -y;
			lc = -lc;
			ld = -ld;
		}
		CONST_CAST(float, self->a) = la;
		CONST_CAST(float, self->b) = lb;
		CONST_CAST(float, self->c) = lc;
		CONST_CAST(float, self->d) = ld;
		CONST_CAST(float, self->worldX) = x + self->skeleton->x;
		CONST_CAST(float, self->worldY) = y + self->skeleton->y;
		return;
	}

	pa = parent->a;
	pb = parent->b;
	pc = parent->c;
	pd = parent->d;

	CONST_CAST(float, self->worldX) = pa * x + pb * y + parent->worldX;
	CONST_CAST(float, self->worldY) = pc * x + pd * y + parent->worldY;

	switch (self->data->transformMode) {
		case SP_TRANSFORMMODE_NORMAL: {
			float rotationY = rotation + 90 + shearY;
			float la = COS_DEG(rotation + shearX) * scaleX;
			float lb = COS_DEG(rotationY) * scaleY;
			float lc = SIN_DEG(rotation + shearX) * scaleX;
			float ld = SIN_DEG(rotationY) * scaleY;
			CONST_CAST(float, self->a) = pa * la + pb * lc;
			CONST_CAST(float, self->b) = pa * lb + pb * ld;
			CONST_CAST(float, self->c) = pc * la + pd * lc;
			CONST_CAST(float, self->d) = pc * lb + pd * ld;
			return;
		}
		case SP_TRANSFORMMODE_ONLYTRANSLATION: {
			float rotationY = rotation + 90 + shearY;
			CONST_CAST(float, self->a) = COS_DEG(rotation + shearX) * scaleX;
			CONST_CAST(float, self->b) = COS_DEG(rotationY) * scaleY;
			CONST_CAST(float, self->c) = SIN_DEG(rotation + shearX) * scaleX;
			CONST_CAST(float, self->d) = SIN_DEG(rotationY) * scaleY;
			break;
		}
		case SP_TRANSFORMMODE_NOROTATIONORREFLECTION: {
			float s = pa * pa + pc * pc;
			float prx, rx, ry, la, lb, lc, ld;
			if (s > 0.0001f) {
				s = ABS(pa * pd - pb * pc) / s;
				pb = pc * s;
				pd = pa * s;
				prx = ATAN2(pc, pa) * RAD_DEG;
			} else {
				pa = 0;
				pc = 0;
				prx = 90 - ATAN2(pd, pb) * RAD_DEG;
			}
			rx = rotation + shearX - prx;
			ry = rotation + shearY - prx + 90;
			la = COS_DEG(rx) * scaleX;
			lb = COS_DEG(ry) * scaleY;
			lc = SIN_DEG(rx) * scaleX;
			ld = SIN_DEG(ry) * scaleY;
			CONST_CAST(float, self->a) = pa * la - pb * lc;
			CONST_CAST(float, self->b) = pa * lb - pb * ld;
			CONST_CAST(float, self->c) = pc * la + pd * lc;
			CONST_CAST(float, self->d) = pc * lb + pd * ld;
			break;
		}
		case SP_TRANSFORMMODE_NOSCALE:
		case SP_TRANSFORMMODE_NOSCALEORREFLECTION: {
			float za, zc, s;
			float r, zb, zd, la, lb, lc, ld;
			cosine = COS_DEG(rotation); sine = SIN_DEG(rotation);
			za = pa * cosine + pb * sine;
			zc = pc * cosine + pd * sine;
			s = SQRT(za * za + zc * zc);
			if (s > 0.00001f) s = 1 / s;
			za *= s;
			zc *= s;
			s = SQRT(za * za + zc * zc);
			r = PI / 2 + atan2(zc, za);
			zb = COS(r) * s;
			zd = SIN(r) * s;
			la = COS_DEG(shearX) * scaleX;
			lb = COS_DEG(90 + shearY) * scaleY;
			lc = SIN_DEG(shearX) * scaleX;
			ld = SIN_DEG(90 + shearY) * scaleY;
			CONST_CAST(float, self->a) = za * la + zb * lc;
			CONST_CAST(float, self->b) = za * lb + zb * ld;
			CONST_CAST(float, self->c) = zc * la + zd * lc;
			CONST_CAST(float, self->d) = zc * lb + zd * ld;
			if (self->data->transformMode != SP_TRANSFORMMODE_NOSCALEORREFLECTION ? pa * pd - pb * pc < 0 : self->skeleton->flipX != self->skeleton->flipY) {
				CONST_CAST(float, self->b) = -self->b;
				CONST_CAST(float, self->d) = -self->d;
			}
			return;
		}
	}
	if (self->skeleton->flipX) {
		CONST_CAST(float, self->a) = -self->a;
		CONST_CAST(float, self->b) = -self->b;
	}
	if (self->skeleton->flipY != yDown) {
		CONST_CAST(float, self->c) = -self->c;
		CONST_CAST(float, self->d) = -self->d;
	}
}

void spBone_setToSetupPose (spBone* self) {
	self->x = self->data->x;
	self->y = self->data->y;
	self->rotation = self->data->rotation;
	self->scaleX = self->data->scaleX;
	self->scaleY = self->data->scaleY;
	self->shearX = self->data->shearX;
	self->shearY = self->data->shearY;
}

float spBone_getWorldRotationX (spBone* self) {
	return ATAN2(self->c, self->a) * RAD_DEG;
}

float spBone_getWorldRotationY (spBone* self) {
	return ATAN2(self->d, self->b) * RAD_DEG;
}

float spBone_getWorldScaleX (spBone* self) {
	return SQRT(self->a * self->a + self->c * self->c);
}

float spBone_getWorldScaleY (spBone* self) {
	return SQRT(self->b * self->b + self->d * self->d);
}

float spBone_worldToLocalRotationX (spBone* self) {
	spBone* parent = self->parent;
	if (!parent) return self->arotation;
	return ATAN2(parent->a * self->c - parent->c * self->a, parent->d * self->a - parent->b * self->c) * RAD_DEG;
}

float spBone_worldToLocalRotationY (spBone* self) {
	spBone* parent = self->parent;
	if (!parent) return self->arotation;
	return ATAN2(parent->a * self->d - parent->c * self->b, parent->d * self->b - parent->b * self->d) * RAD_DEG;
}

void spBone_rotateWorld (spBone* self, float degrees) {
	float a = self->a, b = self->b, c = self->c, d = self->d;
	float cosine = COS_DEG(degrees), sine = SIN_DEG(degrees);
	CONST_CAST(float, self->a) = cosine * a - sine * c;
	CONST_CAST(float, self->b) = cosine * b - sine * d;
	CONST_CAST(float, self->c) = sine * a + cosine * c;
	CONST_CAST(float, self->d) = sine * b + cosine * d;
	CONST_CAST(int, self->appliedValid) = 1;
}


/** Computes the individual applied transform values from the world transform. This can be useful to perform processing using
 * the applied transform after the world transform has been modified directly (eg, by a constraint).
 * <p>
 * Some information is ambiguous in the world transform, such as -1,-1 scale versus 180 rotation. */
void spBone_updateAppliedTransform (spBone* self) {
	spBone* parent = self->parent;
	self->appliedValid = 1;
	if (!parent) {
		self->ax = self->worldX;
		self->ay = self->worldY;
		self->arotation = ATAN2(self->c, self->a) * RAD_DEG;
		self->ascaleX = SQRT(self->a * self->a + self->c * self->c);
		self->ascaleY = SQRT(self->b * self->b + self->d * self->d);
		self->ashearX = 0;
		self->ashearY = ATAN2(self->a * self->b + self->c * self->d, self->a * self->d - self->b * self->c) * RAD_DEG;
	} else {
		float pa = parent->a, pb = parent->b, pc = parent->c, pd = parent->d;
		float pid = 1 / (pa * pd - pb * pc);
		float dx = self->worldX - parent->worldX, dy = self->worldY - parent->worldY;
		float ia = pid * pd;
		float id = pid * pa;
		float ib = pid * pb;
		float ic = pid * pc;
		float ra = ia * self->a - ib * self->c;
		float rb = ia * self->b - ib * self->d;
		float rc = id * self->c - ic * self->a;
		float rd = id * self->d - ic * self->b;
		self->ax = (dx * pd * pid - dy * pb * pid);
		self->ay = (dy * pa * pid - dx * pc * pid);
		self->ashearX = 0;
		self->ascaleX = SQRT(ra * ra + rc * rc);
		if (self->ascaleX > 0.0001f) {
			float det = ra * rd - rb * rc;
			self->ascaleY = det / self->ascaleX;
			self->ashearY = ATAN2(ra * rb + rc * rd, det) * RAD_DEG;
			self->arotation = ATAN2(rc, ra) * RAD_DEG;
		} else {
			self->ascaleX = 0;
			self->ascaleY = SQRT(rb * rb + rd * rd);
			self->ashearY = 0;
			self->arotation = 90 - ATAN2(rd, rb) * RAD_DEG;
		}
	}
}

void spBone_worldToLocal (spBone* self, float worldX, float worldY, float* localX, float* localY) {
	float a = self->a, b = self->b, c = self->c, d = self->d;
	float invDet = 1 / (a * d - b * c);
	float x = worldX - self->worldX, y = worldY - self->worldY;
	*localX = (x * d * invDet - y * b * invDet);
	*localY = (y * a * invDet - x * c * invDet);
}

void spBone_localToWorld (spBone* self, float localX, float localY, float* worldX, float* worldY) {
	float x = localX, y = localY;
	*worldX = x * self->a + y * self->b + self->worldX;
	*worldY = x * self->c + y * self->d + self->worldY;
}
