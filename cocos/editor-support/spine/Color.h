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

#ifndef SPINE_COLOR_H
#define SPINE_COLOR_H

#include <spine/MathUtil.h>

namespace spine {
class SP_API Color : public SpineObject {
public:
	Color() : r(0), g(0), b(0), a(0) {
	}

	Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {
		clamp();
	}

	inline Color &set(float _r, float _g, float _b, float _a) {
		this->r = _r;
		this->g = _g;
		this->b = _b;
		this->a = _a;
		clamp();
		return *this;
	}

	inline Color &set(const Color &other) {
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;
		clamp();
		return *this;
	}

	inline Color &add(float _r, float _g, float _b, float _a) {
		this->r += _r;
		this->g += _g;
		this->b += _b;
		this->a += _a;
		clamp();
		return *this;
	}

	inline Color &add(const Color &other) {
		r += other.r;
		g += other.g;
		b += other.b;
		a += other.a;
		clamp();
		return *this;
	}

	inline Color &clamp() {
		r = MathUtil::clamp(this->r, 0, 1);
		g = MathUtil::clamp(this->g, 0, 1);
		b = MathUtil::clamp(this->b, 0, 1);
		a = MathUtil::clamp(this->a, 0, 1);
		return *this;
	}

	float r, g, b, a;
};
}


#endif //SPINE_COLOR_H
