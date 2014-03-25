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

#ifndef SPINE_SKELETON_H_
#define SPINE_SKELETON_H_

#include <spine/SkeletonData.h>
#include <spine/Slot.h>
#include <spine/Skin.h>

namespace cocos2d { namespace extension {

typedef struct Skeleton Skeleton;
struct Skeleton {
	SkeletonData* const data;

	int boneCount;
	Bone** bones;
	Bone* const root;

	int slotCount;
	Slot** slots;
	Slot** drawOrder;

	Skin* const skin;
	float r, g, b, a;
	float time;
	int/*bool*/flipX, flipY;
	float x, y;
};

CC_EX_DLL Skeleton* Skeleton_create (SkeletonData* data);
CC_EX_DLL void Skeleton_dispose (Skeleton* self);

CC_EX_DLL void Skeleton_updateWorldTransform (const Skeleton* self);

CC_EX_DLL void Skeleton_setToSetupPose (const Skeleton* self);
CC_EX_DLL void Skeleton_setBonesToSetupPose (const Skeleton* self);
CC_EX_DLL void Skeleton_setSlotsToSetupPose (const Skeleton* self);

/* Returns 0 if the bone was not found. */
CC_EX_DLL Bone* Skeleton_findBone (const Skeleton* self, const char* boneName);
/* Returns -1 if the bone was not found. */
CC_EX_DLL int Skeleton_findBoneIndex (const Skeleton* self, const char* boneName);

/* Returns 0 if the slot was not found. */
CC_EX_DLL Slot* Skeleton_findSlot (const Skeleton* self, const char* slotName);
/* Returns -1 if the slot was not found. */
CC_EX_DLL int Skeleton_findSlotIndex (const Skeleton* self, const char* slotName);

/* Sets the skin used to look up attachments not found in the SkeletonData defaultSkin. Attachments from the new skin are
 * attached if the corresponding attachment from the old skin was attached.
 * @param skin May be 0.*/
CC_EX_DLL void Skeleton_setSkin (Skeleton* self, Skin* skin);
/* Returns 0 if the skin was not found. See Skeleton_setSkin.
 * @param skinName May be 0. */
CC_EX_DLL int Skeleton_setSkinByName (Skeleton* self, const char* skinName);

/* Returns 0 if the slot or attachment was not found. */
CC_EX_DLL Attachment* Skeleton_getAttachmentForSlotName (const Skeleton* self, const char* slotName, const char* attachmentName);
/* Returns 0 if the slot or attachment was not found. */
CC_EX_DLL Attachment* Skeleton_getAttachmentForSlotIndex (const Skeleton* self, int slotIndex, const char* attachmentName);
/* Returns 0 if the slot or attachment was not found. */
CC_EX_DLL int Skeleton_setAttachment (Skeleton* self, const char* slotName, const char* attachmentName);

CC_EX_DLL void Skeleton_update (Skeleton* self, float deltaTime);

}} // namespace cocos2d { namespace extension {

#endif /* SPINE_SKELETON_H_*/
