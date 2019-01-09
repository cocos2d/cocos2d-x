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

#ifndef Spine_RTTI_h
#define Spine_RTTI_h

#include <spine/SpineObject.h>

#include <string>

namespace spine {
class SP_API RTTI : public SpineObject {
public:
	explicit RTTI(const std::string &className);

	RTTI(const std::string &className, const RTTI &baseRTTI);

	const std::string &getClassName() const;

	bool isExactly(const RTTI &rtti) const;

	bool instanceOf(const RTTI &rtti) const;

private:
	// Prevent copying
	RTTI(const RTTI &obj);

	RTTI &operator=(const RTTI &obj);

	const std::string _className;
	const RTTI *_pBaseRTTI;
};
}

#define RTTI_DECL \
public: \
static const spine::RTTI rtti; \
virtual const spine::RTTI& getRTTI() const;

#define RTTI_IMPL_NOPARENT(name) \
const spine::RTTI name::rtti(#name); \
const spine::RTTI& name::getRTTI() const { return rtti; }

#define RTTI_IMPL(name, parent) \
const spine::RTTI name::rtti(#name, parent::rtti); \
const spine::RTTI& name::getRTTI() const { return rtti; }

#endif /* Spine_RTTI_h */

