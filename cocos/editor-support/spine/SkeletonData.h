/******************************************************************************
 * Spine Runtime Software License - Version 1.1
 * 
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms in whole or in part, with
 * or without modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. A Spine Essential, Professional, Enterprise, or Education License must
 *    be purchased from Esoteric Software and the license must remain valid:
 *    http://esotericsoftware.com/
 * 2. Redistributions of source code must retain this license, which is the
 *    above copyright notice, this declaration of conditions and the following
 *    disclaimer.
 * 3. Redistributions in binary form must reproduce this license, which is the
 *    above copyright notice, this declaration of conditions and the following
 *    disclaimer, in the documentation and/or other materials provided with the
 *    distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef SPINE_SKELETONDATA_H_
#define SPINE_SKELETONDATA_H_

#include <spine/BoneData.h>
#include <spine/SlotData.h>
#include <spine/Skin.h>
#include <spine/EventData.h>
#include <spine/Animation.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	int boneCount;
	spBoneData** bones;

	int slotCount;
	spSlotData** slots;

	int skinCount;
	spSkin** skins;
	spSkin* defaultSkin;

	int eventCount;
	spEventData** events;

	int animationCount;
	spAnimation** animations;
} spSkeletonData;

spSkeletonData* spSkeletonData_create ();
void spSkeletonData_dispose (spSkeletonData* self);

spBoneData* spSkeletonData_findBone (const spSkeletonData* self, const char* boneName);
int spSkeletonData_findBoneIndex (const spSkeletonData* self, const char* boneName);

spSlotData* spSkeletonData_findSlot (const spSkeletonData* self, const char* slotName);
int spSkeletonData_findSlotIndex (const spSkeletonData* self, const char* slotName);

spSkin* spSkeletonData_findSkin (const spSkeletonData* self, const char* skinName);

spEventData* spSkeletonData_findEvent (const spSkeletonData* self, const char* eventName);

spAnimation* spSkeletonData_findAnimation (const spSkeletonData* self, const char* animationName);

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
