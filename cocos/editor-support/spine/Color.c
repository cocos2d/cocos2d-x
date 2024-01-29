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

#include "spine/Color.h"
#include "spine/extension.h"

spColor* spColor_create() {
	return MALLOC(spColor, 1);
}

void spColor_dispose(spColor* self) {
	if (self) FREE(self);
}

void spColor_setFromFloats(spColor* self, float r, float g, float b, float a) {
	self->r = r;
	self->g = g;
	self->b = b;
	self->a = a;
}

void spColor_setFromColor(spColor* self, spColor* otherColor) {
	self->r = otherColor->r;
	self->g = otherColor->g;
	self->b = otherColor->b;
	self->a = otherColor->a;
}

void spColor_addColor(spColor* self, spColor* otherColor) {
	self->r += otherColor->r;
	self->g += otherColor->g;
	self->b += otherColor->b;
	self->a += otherColor->a;
	spColor_clamp(self);
}

void spColor_addFloats(spColor* self, float r, float g, float b, float a) {
	self->r += r;
	self->g += g;
	self->b += b;
	self->a += a;
	spColor_clamp(self);
}

void spColor_clamp(spColor* self) {
	if (self->r < 0) self->r = 0;
	else if (self->r > 1) self->r = 1;

	if (self->g < 0) self->g = 0;
	else if (self->g > 1) self->g = 1;

	if (self->b < 0) self->b = 0;
	else if (self->b > 1) self->b = 1;

	if (self->a < 0) self->a = 0;
	else if (self->a > 1) self->a = 1;
}
