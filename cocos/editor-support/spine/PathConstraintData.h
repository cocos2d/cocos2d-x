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

#ifndef SPINE_PATHCONSTRAINTDATA_H_
#define SPINE_PATHCONSTRAINTDATA_H_

#include <spine/BoneData.h>
#include <spine/SlotData.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	SP_POSITION_MODE_FIXED, SP_POSITION_MODE_PERCENT
} spPositionMode;

typedef enum {
	SP_SPACING_MODE_LENGTH, SP_SPACING_MODE_FIXED, SP_SPACING_MODE_PERCENT
} spSpacingMode;

typedef enum {
	SP_ROTATE_MODE_TANGENT, SP_ROTATE_MODE_CHAIN, SP_ROTATE_MODE_CHAIN_SCALE
} spRotateMode;

typedef struct spPathConstraintData {
	const char* const name;
	int order;
	int bonesCount;
	spBoneData** const bones;
	spSlotData* target;
	spPositionMode positionMode;
	spSpacingMode spacingMode;
	spRotateMode rotateMode;
	float offsetRotation;
	float position, spacing, rotateMix, translateMix;

#ifdef __cplusplus
	spPathConstraintData() :
		name(0),
		bonesCount(0),
		bones(0),
		target(0),
		positionMode(SP_POSITION_MODE_FIXED),
		spacingMode(SP_SPACING_MODE_LENGTH),
		rotateMode(SP_ROTATE_MODE_TANGENT),
		offsetRotation(0),
		position(0),
		spacing(0),
		rotateMix(0),
		translateMix(0) {
	}
#endif
} spPathConstraintData;

spPathConstraintData* spPathConstraintData_create (const char* name);
void spPathConstraintData_dispose (spPathConstraintData* self);

#ifdef SPINE_SHORT_NAMES
typedef spPathConstraintData PathConstraintData;
#define PathConstraintData_create(...) spPathConstraintData_create(__VA_ARGS__)
#define PathConstraintData_dispose(...) spPathConstraintData_dispose(__VA_ARGS__)
#endif

#ifdef __cplusplus
}
#endif

#endif /* SPINE_PATHCONSTRAINTDATA_H_ */
