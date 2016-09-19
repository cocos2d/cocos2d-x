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
	float rotationY = rotation + 90 + shearY;
	float la = COS_DEG(rotation + shearX) * scaleX, lb = COS_DEG(rotationY) * scaleY;
	float lc = SIN_DEG(rotation + shearX) * scaleX, ld = SIN_DEG(rotationY) * scaleY;
	float pa, pb, pc, pd, temp;
	spBone* parent = self->parent;

	CONST_CAST(float, self->appliedRotation) = rotation;

	if (!parent) { /* Root bone. */
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
		CONST_CAST(float, self->worldX) = x;
		CONST_CAST(float, self->worldY) = y;
		CONST_CAST(float, self->worldSignX) = scaleX > 0 ? 1.0f : -1.0f;
		CONST_CAST(float, self->worldSignY) = scaleY > 0 ? 1.0f : -1.0f;
		return;
	}

	pa = parent->a;
	pb = parent->b;
	pc = parent->c;
	pd = parent->d;

	CONST_CAST(float, self->worldX) = pa * x + pb * y + parent->worldX;
	CONST_CAST(float, self->worldY) = pc * x + pd * y + parent->worldY;
	CONST_CAST(float, self->worldSignX) = parent->worldSignX * (scaleX > 0 ? 1 : -1);
	CONST_CAST(float, self->worldSignY) = parent->worldSignY * (scaleY > 0 ? 1 : -1);

	if (self->data->inheritRotation && self->data->inheritScale) {
		CONST_CAST(float, self->a) = pa * la + pb * lc;
		CONST_CAST(float, self->b) = pa * lb + pb * ld;
		CONST_CAST(float, self->c) = pc * la + pd * lc;
		CONST_CAST(float, self->d) = pc * lb + pd * ld;
	} else {
		if (self->data->inheritRotation) { /* No scale inheritance. */
			pa = 1;
			pb = 0;
			pc = 0;
			pd = 1;
			do {
				cosine = COS_DEG(parent->appliedRotation); sine = SIN_DEG(parent->appliedRotation);
				temp = pa * cosine + pb * sine;
				pb = pb * cosine - pa * sine;
				pa = temp;
				temp = pc * cosine + pd * sine;
				pd = pd * cosine - pc * sine;
				pc = temp;

				if (!parent->data->inheritRotation) break;
				parent = parent->parent;
			} while (parent);
			CONST_CAST(float, self->a) = pa * la + pb * lc;
			CONST_CAST(float, self->b) = pa * lb + pb * ld;
			CONST_CAST(float, self->c) = pc * la + pd * lc;
			CONST_CAST(float, self->d) = pc * lb + pd * ld;
		} else if (self->data->inheritScale) { /* No rotation inheritance. */
			pa = 1;
			pb = 0;
			pc = 0;
			pd = 1;
			do {
				float za, zb, zc, zd;
				float psx = parent->scaleX, psy = parent->scaleY;
				cosine = COS_DEG(parent->appliedRotation);
				sine = SIN_DEG(parent->appliedRotation);
				za = cosine * psx; zb = sine * psy; zc = sine * psx; zd = cosine * psy;
				temp = pa * za + pb * zc;
				pb = pb * zd - pa * zb;
				pa = temp;
				temp = pc * za + pd * zc;
				pd = pd * zd - pc * zb;
				pc = temp;

				if (psx >= 0) sine = -sine;
				temp = pa * cosine + pb * sine;
				pb = pb * cosine - pa * sine;
				pa = temp;
				temp = pc * cosine + pd * sine;
				pd = pd * cosine - pc * sine;
				pc = temp;

				if (!parent->data->inheritScale) break;
				parent = parent->parent;
			} while (parent);
			CONST_CAST(float, self->a) = pa * la + pb * lc;
			CONST_CAST(float, self->b) = pa * lb + pb * ld;
			CONST_CAST(float, self->c) = pc * la + pd * lc;
			CONST_CAST(float, self->d) = pc * lb + pd * ld;
		} else {
			CONST_CAST(float, self->a) = la;
			CONST_CAST(float, self->b) = lb;
			CONST_CAST(float, self->c) = lc;
			CONST_CAST(float, self->d) = ld;
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
	return SQRT(self->a * self->a + self->b * self->b) * self->worldSignX;
}

float spBone_getWorldScaleY (spBone* self) {
	return SQRT(self->c * self->c + self->d * self->d) * self->worldSignY;
}

float spBone_worldToLocalRotationX (spBone* self) {
	spBone* parent = self->parent;
	if (!parent) return self->rotation;
	return ATAN2(parent->a * self->c - parent->c * self->a, parent->d * self->a - parent->b * self->c) * RAD_DEG;
}

float spBone_worldToLocalRotationY (spBone* self) {
	spBone* parent = self->parent;
	if (!parent) return self->rotation;
	return ATAN2(parent->a * self->d - parent->c * self->b, parent->d * self->b - parent->b * self->d) * RAD_DEG;
}

void spBone_rotateWorld (spBone* self, float degrees) {
	float a = self->a, b = self->b, c = self->c, d = self->d;
	float cosine = COS_DEG(degrees), sine = SIN_DEG(degrees);
	CONST_CAST(float, self->a) = cosine * a - sine * c;
	CONST_CAST(float, self->b) = cosine * b - sine * d;
	CONST_CAST(float, self->c) = sine * a + cosine * c;
	CONST_CAST(float, self->d) = sine * b + cosine * d;
}

/** Computes the local transform from the world transform. This can be useful to perform processing on the local transform
 * after the world transform has been modified directly (eg, by a constraint).
 * <p>
 * Some redundant information is lost by the world transform, such as -1,-1 scale versus 180 rotation. The computed local
 * transform values may differ from the original values but are functionally the same. */
void spBone_updateLocalTransform (spBone* self) {
	spBone* parent = self->parent;
	if (!parent) {
		float det = self->a * self->d - self->b * self->c;
		self->x = self->worldX;
		self->y = self->worldY;
		self->rotation = ATAN2(self->c, self->a) * RAD_DEG;
		self->scaleX = SQRT(self->a * self->a + self->c * self->c);
		self->scaleY = SQRT(self->b * self->b + self->d * self->d);
		self->shearX = 0;
		self->shearY = ATAN2(self->a * self->b + self->c * self->d, det) * RAD_DEG;
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
		self->x = (dx * pd * pid - dy * pb * pid);
		self->y = (dy * pa * pid - dx * pc * pid);
		self->shearX = 0;
		self->scaleX = SQRT(ra * ra + rc * rc);
		if (self->scaleX > 0.0001f) {
			float det = ra * rd - rb * rc;
			self->scaleY = det / self->scaleX;
			self->shearY = ATAN2(ra * rb + rc * rd, det) * RAD_DEG;
			self->rotation = ATAN2(rc, ra) * RAD_DEG;
		} else {
			self->scaleX = 0;
			self->scaleY = SQRT(rb * rb + rd * rd);
			self->shearY = 0;
			self->rotation = 90 - ATAN2(rd, rb) * RAD_DEG;
		}
		self->appliedRotation = self->rotation;
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
