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

#include "spine/VertexEffect.h"
#include "spine/extension.h"

void _spJitterVertexEffect_begin(spVertexEffect* self, spSkeleton* skeleton) {
}

void _spJitterVertexEffect_transform(spVertexEffect* self, float* x, float* y, float* u, float* v, spColor* light, spColor* dark) {
	spJitterVertexEffect* internal = (spJitterVertexEffect*)self;
	float jitterX = internal->jitterX;
	float jitterY = internal->jitterY;
	(*x) += _spMath_randomTriangular(-jitterX, jitterY);
	(*y) += _spMath_randomTriangular(-jitterX, jitterY);
}

void _spJitterVertexEffect_end(spVertexEffect* self) {
}

spJitterVertexEffect* spJitterVertexEffect_create(float jitterX, float jitterY) {
	spJitterVertexEffect* effect = CALLOC(spJitterVertexEffect, 1);
	effect->super.begin = _spJitterVertexEffect_begin;
	effect->super.transform = _spJitterVertexEffect_transform;
	effect->super.end = _spJitterVertexEffect_end;
	effect->jitterX = jitterX;
	effect->jitterY = jitterY;
	return effect;
}

void spJitterVertexEffect_dispose(spJitterVertexEffect* effect) {
	FREE(effect);
}

void _spSwirlVertexEffect_begin(spVertexEffect* self, spSkeleton* skeleton) {
	spSwirlVertexEffect* internal = (spSwirlVertexEffect*)self;
	internal->worldX = skeleton->x + internal->centerX;
	internal->worldY = skeleton->y + internal->centerY;
}

void _spSwirlVertexEffect_transform(spVertexEffect* self, float* positionX, float* positionY, float* u, float* v, spColor* light, spColor* dark) {
	spSwirlVertexEffect* internal = (spSwirlVertexEffect*)self;
	float radAngle = internal->angle * DEG_RAD;
	float x = *positionX - internal->worldX;
	float y = *positionY - internal->worldY;
	float dist = SQRT(x * x + y * y);
	if (dist < internal->radius) {
		float theta = _spMath_interpolate(_spMath_pow2_apply, 0, radAngle, (internal->radius - dist) / internal->radius);
		float cosine = COS(theta);
		float sine = SIN(theta);
		(*positionX) = cosine * x - sine * y + internal->worldX;
		(*positionY) = sine * x + cosine * y + internal->worldY;
	}
}

void _spSwirlVertexEffect_end(spVertexEffect* self) {
}

spSwirlVertexEffect* spSwirlVertexEffect_create(float radius) {
	spSwirlVertexEffect* effect = CALLOC(spSwirlVertexEffect, 1);
	effect->super.begin = _spSwirlVertexEffect_begin;
	effect->super.transform = _spSwirlVertexEffect_transform;
	effect->super.end = _spSwirlVertexEffect_end;
	effect->radius = radius;
	return effect;
}

void spSwirlVertexEffect_dispose(spSwirlVertexEffect* effect) {
	FREE(effect);
}

