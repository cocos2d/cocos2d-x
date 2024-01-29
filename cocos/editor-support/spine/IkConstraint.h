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

#ifndef SPINE_IKCONSTRAINT_H_
#define SPINE_IKCONSTRAINT_H_

#include "spine/dll.h"
#include "spine/IkConstraintData.h"
#include "spine/Bone.h"

#ifdef __cplusplus
extern "C" {
#endif

struct spSkeleton;

typedef struct spIkConstraint {
	spIkConstraintData* const data;

	int bonesCount;
	spBone** bones;

	spBone* target;
	int bendDirection;
	float mix;

#ifdef __cplusplus
	spIkConstraint() :
		data(0),
		bonesCount(0),
		bones(0),
		target(0),
		bendDirection(0),
		mix(0) {
	}
#endif
} spIkConstraint;

SP_API spIkConstraint* spIkConstraint_create (spIkConstraintData* data, const struct spSkeleton* skeleton);
SP_API void spIkConstraint_dispose (spIkConstraint* self);

SP_API void spIkConstraint_apply (spIkConstraint* self);

SP_API void spIkConstraint_apply1 (spBone* bone, float targetX, float targetY, float alpha);
SP_API void spIkConstraint_apply2 (spBone* parent, spBone* child, float targetX, float targetY, int bendDirection, float alpha);

#ifdef SPINE_SHORT_NAMES
typedef spIkConstraint IkConstraint;
#define IkConstraint_create(...) spIkConstraint_create(__VA_ARGS__)
#define IkConstraint_dispose(...) spIkConstraint_dispose(__VA_ARGS__)
#define IkConstraint_apply(...) spIkConstraint_apply(__VA_ARGS__)
#define IkConstraint_apply1(...) spIkConstraint_apply1(__VA_ARGS__)
#define IkConstraint_apply2(...) spIkConstraint_apply2(__VA_ARGS__)
#endif

#ifdef __cplusplus
}
#endif

#endif /* SPINE_IKCONSTRAINT_H_ */
