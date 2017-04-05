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

#ifndef SPINE_TRANSFORMCONSTRAINTDATA_H_
#define SPINE_TRANSFORMCONSTRAINTDATA_H_

#include <spine/BoneData.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct spTransformConstraintData {
	const char* const name;
	int order;
	int bonesCount;
	spBoneData** const bones;
	spBoneData* target;
	float rotateMix, translateMix, scaleMix, shearMix;
	float offsetRotation, offsetX, offsetY, offsetScaleX, offsetScaleY, offsetShearY;

#ifdef __cplusplus
	spTransformConstraintData() :
		name(0),
		bonesCount(0),
		bones(0),
		target(0),
		rotateMix(0),
		translateMix(0),
		scaleMix(0),
		shearMix(0),
		offsetRotation(0),
		offsetX(0),
		offsetY(0),
		offsetScaleX(0),
		offsetScaleY(0),
		offsetShearY(0) {
	}
#endif
} spTransformConstraintData;

spTransformConstraintData* spTransformConstraintData_create (const char* name);
void spTransformConstraintData_dispose (spTransformConstraintData* self);

#ifdef SPINE_SHORT_NAMES
typedef spTransformConstraintData TransformConstraintData;
#define TransformConstraintData_create(...) spTransformConstraintData_create(__VA_ARGS__)
#define TransformConstraintData_dispose(...) spTransformConstraintData_dispose(__VA_ARGS__)
#endif

#ifdef __cplusplus
}
#endif

#endif /* SPINE_TRANSFORMCONSTRAINTDATA_H_ */
