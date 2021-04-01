/******************************************************************************
 * Spine Runtimes License Agreement
 * Last updated May 1, 2019. Replaces all prior versions.
 *
 * Copyright (c) 2013-2019, Esoteric Software LLC
 *
 * Integration of the Spine Runtimes into software or otherwise creating
 * derivative works of the Spine Runtimes is permitted under the terms and
 * conditions of Section 2 of the Spine Editor License Agreement:
 * http://esotericsoftware.com/spine-editor-license
 *
 * Otherwise, it is permitted to integrate the Spine Runtimes into software
 * or otherwise create derivative works of the Spine Runtimes (collectively,
 * "Products"), provided that each user of the Products must obtain their own
 * Spine Editor license and redistribution of the Products in any form must
 * include this license and copyright notice.
 *
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE LLC "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 * NO EVENT SHALL ESOTERIC SOFTWARE LLC BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, BUSINESS
 * INTERRUPTION, OR LOSS OF USE, DATA, OR PROFITS) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/
#ifdef SPINE_UE4
#include "SpinePluginPrivatePCH.h"
#endif

#include <spine/MathUtil.h>
#include <math.h>
#include <stdlib.h>

// Required for division by 0 in _isNaN on MSVC
#ifdef _MSC_VER
#pragma warning(disable:4723)
#endif

using namespace spine;

const float MathUtil::Pi = 3.1415926535897932385f;
const float MathUtil::Pi_2 = 3.1415926535897932385f * 2;
const float MathUtil::Deg_Rad = (3.1415926535897932385f / 180.0f);
const float MathUtil::Rad_Deg = (180.0f / 3.1415926535897932385f);

float MathUtil::abs(float v) {
	return ((v) < 0 ? -(v) : (v));
}

float MathUtil::sign(float v) {
	return ((v) < 0 ? -1.0f : (v) > 0 ? 1.0f : 0.0f);
}

float MathUtil::clamp(float x, float min, float max) {
	return ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)));
}

float MathUtil::fmod(float a, float b) {
	return (float)::fmod(a, b);
}

/// Returns atan2 in radians, faster but less accurate than Math.Atan2. Average error of 0.00231 radians (0.1323
/// degrees), largest error of 0.00488 radians (0.2796 degrees).
float MathUtil::atan2(float y, float x) {
	return (float)::atan2(y, x);
}

/// Returns the cosine in radians from a lookup table.
float MathUtil::cos(float radians) {
	return (float)::cos(radians);
}

/// Returns the sine in radians from a lookup table.
float MathUtil::sin(float radians) {
	return (float)::sin(radians);
}

float MathUtil::sqrt(float v) {
	return (float)::sqrt(v);
}

float MathUtil::acos(float v) {
	return (float)::acos(v);
}

/// Returns the sine in radians from a lookup table.
float MathUtil::sinDeg(float degrees) {
	return (float)::sin(degrees * MathUtil::Deg_Rad);
}

/// Returns the cosine in radians from a lookup table.
float MathUtil::cosDeg(float degrees) {
	return (float)::cos(degrees * MathUtil::Deg_Rad);
}

/* Need to pass 0 as an argument, so VC++ doesn't error with C2124 */
static bool _isNan(float value, float zero) {
	float _nan = (float) 0.0 / zero;
	return 0 == memcmp((void *) &value, (void *) &_nan, sizeof(value));
}

bool MathUtil::isNan(float v) {
	return _isNan(v, 0);
}

float MathUtil::random() {
	return ::rand() / (float)RAND_MAX;
}

float MathUtil::randomTriangular(float min, float max) {
	return randomTriangular(min, max, (min + max) * 0.5f);
}

float MathUtil::randomTriangular(float min, float max, float mode) {
	float u = random();
	float d = max - min;
	if (u <= (mode - min) / d) return min + sqrt(u * d * (mode - min));
	return max - sqrt((1 - u) * d * (max - mode));
}

float MathUtil::pow(float a, float b) {
	return (float)::pow(a, b);
}
