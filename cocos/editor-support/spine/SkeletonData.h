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

#ifndef SPINE_SKELETONDATA_H_
#define SPINE_SKELETONDATA_H_

#include <spine/dll.h>
#include <spine/BoneData.h>
#include <spine/SlotData.h>
#include <spine/Skin.h>
#include <spine/EventData.h>
#include <spine/Animation.h>
#include <spine/IkConstraintData.h>
#include <spine/TransformConstraintData.h>
#include <spine/PathConstraintData.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct spSkeletonData {
	const char* version;
	const char* hash;
	float width, height;

	int bonesCount;
	spBoneData** bones;

	int slotsCount;
	spSlotData** slots;

	int skinsCount;
	spSkin** skins;
	spSkin* defaultSkin;

	int eventsCount;
	spEventData** events;

	int animationsCount;
	spAnimation** animations;

	int ikConstraintsCount;
	spIkConstraintData** ikConstraints;

	int transformConstraintsCount;
	spTransformConstraintData** transformConstraints;

	int pathConstraintsCount;
	spPathConstraintData** pathConstraints;
} spSkeletonData;

SP_API spSkeletonData* spSkeletonData_create ();
SP_API void spSkeletonData_dispose (spSkeletonData* self);

SP_API spBoneData* spSkeletonData_findBone (const spSkeletonData* self, const char* boneName);
SP_API int spSkeletonData_findBoneIndex (const spSkeletonData* self, const char* boneName);

SP_API spSlotData* spSkeletonData_findSlot (const spSkeletonData* self, const char* slotName);
SP_API int spSkeletonData_findSlotIndex (const spSkeletonData* self, const char* slotName);

SP_API spSkin* spSkeletonData_findSkin (const spSkeletonData* self, const char* skinName);

SP_API spEventData* spSkeletonData_findEvent (const spSkeletonData* self, const char* eventName);

SP_API spAnimation* spSkeletonData_findAnimation (const spSkeletonData* self, const char* animationName);

SP_API spIkConstraintData* spSkeletonData_findIkConstraint (const spSkeletonData* self, const char* constraintName);

SP_API spTransformConstraintData* spSkeletonData_findTransformConstraint (const spSkeletonData* self, const char* constraintName);

SP_API spPathConstraintData* spSkeletonData_findPathConstraint (const spSkeletonData* self, const char* constraintName);

#ifdef SPINE_SHORT_NAMES
typedef spSkeletonData SkeletonData;
#define SkeletonData_create(...) spSkeletonData_create(__VA_ARGS__)
#define SkeletonData_dispose(...) spSkeletonData_dispose(__VA_ARGS__)
#define SkeletonData_findBone(...) spSkeletonData_findBone(__VA_ARGS__)
#define SkeletonData_findBoneIndex(...) spSkeletonData_findBoneIndex(__VA_ARGS__)
#define SkeletonData_findSlot(...) spSkeletonData_findSlot(__VA_ARGS__)
#define SkeletonData_findSlotIndex(...) spSkeletonData_findSlotIndex(__VA_ARGS__)
#define SkeletonData_findSkin(...) spSkeletonData_findSkin(__VA_ARGS__)
#define SkeletonData_findEvent(...) spSkeletonData_findEvent(__VA_ARGS__)
#define SkeletonData_findAnimation(...) spSkeletonData_findAnimation(__VA_ARGS__)
#endif

#ifdef __cplusplus
}
#endif

#endif /* SPINE_SKELETONDATA_H_ */
