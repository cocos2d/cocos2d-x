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

#ifndef SPINE_COLOR_H_
#define SPINE_COLOR_H_

#include <spine/dll.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct spColor {
	float r, g, b, a;

#ifdef __cplusplus
	spColor() :
		r(0), g(0), b(0), a(0) {
	}

	bool operator==(const spColor& rhs) {
		return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a;
	}
#endif
} spColor;

/* @param attachmentName May be 0 for no setup pose attachment. */
SP_API spColor* spColor_create();
SP_API void spColor_dispose(spColor* self);
SP_API void spColor_setFromFloats(spColor* color, float r, float g, float b, float a);
SP_API void spColor_setFromColor(spColor* color, spColor* otherColor);
SP_API void spColor_addFloats(spColor* color, float r, float g, float b, float a);
SP_API void spColor_addColor(spColor* color, spColor* otherColor);
SP_API void spColor_clamp(spColor* color);

#ifdef SPINE_SHORT_NAMES
typedef spColor color;
#define Color_create() spColor_create()
#define Color_dispose(...) spColor_dispose(__VA_ARGS__)
#define Color_setFromFloats(...) spColor_setFromFloats(__VA_ARGS__)
#define Color_setFromColor(...) spColor_setFromColor(__VA_ARGS__)
#define Color_addColor(...) spColor_addColor(__VA_ARGS__)
#define Color_addFloats(...) spColor_addFloats(__VA_ARGS__)
#define Color_clamp(...) spColor_clamp(__VA_ARGS__)
#endif

#ifdef __cplusplus
}
#endif

#endif /* SPINE_COLOR_H_ */
