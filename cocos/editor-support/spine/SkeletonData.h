/*******************************************************************************
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
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
 ******************************************************************************/

#ifndef SPINE_SKELETONDATA_H_
#define SPINE_SKELETONDATA_H_

#include <spine/BoneData.h>
#include <spine/SlotData.h>
#include <spine/Skin.h>
#include <spine/Animation.h>

namespace cocos2d { namespace extension {

typedef struct {
	int boneCount;
	BoneData** bones;

	int slotCount;
	SlotData** slots;

	int skinCount;
	Skin** skins;
	Skin* defaultSkin;

	int animationCount;
	Animation** animations;
} SkeletonData;

SkeletonData* SkeletonData_create ();
void SkeletonData_dispose (SkeletonData* self);

BoneData* SkeletonData_findBone (const SkeletonData* self, const char* boneName);
int SkeletonData_findBoneIndex (const SkeletonData* self, const char* boneName);

SlotData* SkeletonData_findSlot (const SkeletonData* self, const char* slotName);
int SkeletonData_findSlotIndex (const SkeletonData* self, const char* slotName);

Skin* SkeletonData_findSkin (const SkeletonData* self, const char* skinName);

Animation* SkeletonData_findAnimation (const SkeletonData* self, const char* animationName);

}} // namespace cocos2d { namespace extension {

#endif /* SPINE_SKELETONDATA_H_ */
