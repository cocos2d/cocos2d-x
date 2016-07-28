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

#ifndef SPINE_PATHCONSTRAINT_H_
#define SPINE_PATHCONSTRAINT_H_

#include <spine/PathConstraintData.h>
#include <spine/Bone.h>
#include <spine/Slot.h>
#include "PathAttachment.h"

#ifdef __cplusplus
extern "C" {
#endif

struct spSkeleton;

typedef struct spPathConstraint {
	spPathConstraintData* const data;
	int bonesCount;
	spBone** const bones;
	spSlot* target;
	float position, spacing, rotateMix, translateMix;

	int spacesCount;
	float* spaces;

	int positionsCount;
	float* positions;

	int worldCount;
	float* world;

	int curvesCount;
	float* curves;

	int lengthsCount;
	float* lengths;

	float segments[10];

#ifdef __cplusplus
	spPathConstraint() :
		data(0),
		bonesCount(0),
		bones(0),
		target(0),
		position(0),
		spacing(0),
		rotateMix(0),
		translateMix(0),
		spacesCount(0),
		spaces(0),
		positionsCount(0),
		positions(0),
		worldCount(0),
		world(0),
		curvesCount(0),
		curves(0),
		lengthsCount(0),
		lengths(0) {
	}
#endif
} spPathConstraint;

#define SP_PATHCONSTRAINT_

spPathConstraint* spPathConstraint_create (spPathConstraintData* data, const struct spSkeleton* skeleton);
void spPathConstraint_dispose (spPathConstraint* self);

void spPathConstraint_apply (spPathConstraint* self);
float* spPathConstraint_computeWorldPositions(spPathConstraint* self, spPathAttachment* path, int spacesCount, int/*bool*/ tangents, int/*bool*/percentPosition, int/**/percentSpacing);

#ifdef SPINE_SHORT_NAMES
typedef spPathConstraint PathConstraint;
#define PathConstraint_create(...) spPathConstraint_create(__VA_ARGS__)
#define PathConstraint_dispose(...) spPathConstraint_dispose(__VA_ARGS__)
#define PathConstraint_apply(...) spPathConstraint_apply(__VA_ARGS__)
#endif

#ifdef __cplusplus
}
#endif

#endif /* SPINE_PATHCONSTRAINT_H_ */
