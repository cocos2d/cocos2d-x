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

#ifndef Spine_MathUtil_h
#define Spine_MathUtil_h

#include <spine/SpineObject.h>

#include <string.h>

namespace spine {

class SP_API MathUtil : public SpineObject {
private:
	MathUtil();

public:
	static const float Pi;
	static const float Pi_2;
	static const float Deg_Rad;
	static const float Rad_Deg;

	template<typename T>
	static inline T min(T a, T b) { return a < b ? a : b; }

	template<typename T>
	static inline T max(T a, T b) { return a > b ? a : b; }

	static float sign(float val);

	static float clamp(float x, float lower, float upper);

	static float abs(float v);

	/// Returns the sine in radians from a lookup table.
	static float sin(float radians);

	/// Returns the cosine in radians from a lookup table.
	static float cos(float radians);

	/// Returns the sine in radians from a lookup table.
	static float sinDeg(float degrees);

	/// Returns the cosine in radians from a lookup table.
	static float cosDeg(float degrees);

	/// Returns atan2 in radians, faster but less accurate than Math.Atan2. Average error of 0.00231 radians (0.1323
	/// degrees), largest error of 0.00488 radians (0.2796 degrees).
	static float atan2(float y, float x);

	static float acos(float v);

	static float sqrt(float v);

	static float fmod(float a, float b);

	static bool isNan(float v);

	static float random();

	static float randomTriangular(float min, float max);

	static float randomTriangular(float min, float max, float mode);

	static float pow(float a, float b);
};

struct SP_API Interpolation {
	virtual float apply(float a) = 0;

	virtual float interpolate(float start, float end, float a) {
		return start + (end - start) * apply(a);
	}

	virtual ~Interpolation() {};
};

struct SP_API PowInterpolation: public Interpolation {
	PowInterpolation(int power): power(power) {
	}

	float apply(float a) {
		if (a <= 0.5f) return MathUtil::pow(a * 2.0f, (float)power) / 2.0f;
		return MathUtil::pow((a - 1.0f) * 2.0f, (float)power) / (power % 2 == 0 ? -2.0f : 2.0f) + 1.0f;
	}

	int power;
};

struct SP_API PowOutInterpolation: public Interpolation {
	PowOutInterpolation(int power): power(power) {
	}

	float apply(float a) {
		return MathUtil::pow(a - 1, (float)power) * (power % 2 == 0 ? -1.0f : 1.0f) + 1.0f;
	}

	int power;
};

}

#endif /* Spine_MathUtil_h */
