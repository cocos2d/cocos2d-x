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

#ifndef SPINE_SKELETON_H_
#define SPINE_SKELETON_H_

#include <spine/SkeletonData.h>
#include <spine/Slot.h>
#include <spine/Skin.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct spSkeleton spSkeleton;
struct spSkeleton {
	spSkeletonData* const data;

	int boneCount;
	spBone** bones;
	spBone* const root;

	int slotCount;
	spSlot** slots;
	spSlot** drawOrder;

	spSkin* const skin;
	float r, g, b, a;
	float time;
	int/*bool*/flipX, flipY;
	float x, y;
};

spSkeleton* spSkeleton_create (spSkeletonData* data);
void spSkeleton_dispose (spSkeleton* self);

void spSkeleton_updateWorldTransform (const spSkeleton* self);

void spSkeleton_setToSetupPose (const spSkeleton* self);
void spSkeleton_setBonesToSetupPose (const spSkeleton* self);
void spSkeleton_setSlotsToSetupPose (const spSkeleton* self);

/* Returns 0 if the bone was not found. */
spBone* spSkeleton_findBone (const spSkeleton* self, const char* boneName);
/* Returns -1 if the bone was not found. */
int spSkeleton_findBoneIndex (const spSkeleton* self, const char* boneName);

/* Returns 0 if the slot was not found. */
spSlot* spSkeleton_findSlot (const spSkeleton* self, const char* slotName);
/* Returns -1 if the slot was not found. */
int spSkeleton_findSlotIndex (const spSkeleton* self, const char* slotName);

/* Sets the skin used to look up attachments not found in the SkeletonData defaultSkin. Attachments from the new skin are
 * attached if the corresponding attachment from the old skin was attached.
 * @param skin May be 0.*/
void spSkeleton_setSkin (spSkeleton* self, spSkin* skin);
/* Returns 0 if the skin was not found. See spSkeleton_setSkin.
 * @param skinName May be 0. */
int spSkeleton_setSkinByName (spSkeleton* self, const char* skinName);

/* Returns 0 if the slot or attachment was not found. */
spAttachment* spSkeleton_getAttachmentForSlotName (const spSkeleton* self, const char* slotName, const char* attachmentName);
/* Returns 0 if the slot or attachment was not found. */
spAttachment* spSkeleton_getAttachmentForSlotIndex (const spSkeleton* self, int slotIndex, const char* attachmentName);
/* Returns 0 if the slot or attachment was not found. */
int spSkeleton_setAttachment (spSkeleton* self, const char* slotName, const char* attachmentName);

void spSkeleton_update (spSkeleton* self, float deltaTime);

#ifdef SPINE_SHORT_NAMES
typedef spSkeleton Skeleton;
#define Skeleton_create(...) spSkeleton_create(__VA_ARGS__)
#define Skeleton_dispose(...) spSkeleton_dispose(__VA_ARGS__)
#define Skeleton_updateWorldTransform(...) spSkeleton_updateWorldTransform(__VA_ARGS__)
#define Skeleton_setToSetupPose(...) spSkeleton_setToSetupPose(__VA_ARGS__)
#define Skeleton_setBonesToSetupPose(...) spSkeleton_setBonesToSetupPose(__VA_ARGS__)
#define Skeleton_setSlotsToSetupPose(...) spSkeleton_setSlotsToSetupPose(__VA_ARGS__)
#define Skeleton_findBone(...) spSkeleton_findBone(__VA_ARGS__)
#define Skeleton_findBoneIndex(...) spSkeleton_findBoneIndex(__VA_ARGS__)
#define Skeleton_findSlot(...) spSkeleton_findSlot(__VA_ARGS__)
#define Skeleton_findSlotIndex(...) spSkeleton_findSlotIndex(__VA_ARGS__)
#define Skeleton_setSkin(...) spSkeleton_setSkin(__VA_ARGS__)
#define Skeleton_setSkinByName(...) spSkeleton_setSkinByName(__VA_ARGS__)
#define Skeleton_getAttachmentForSlotName(...) spSkeleton_getAttachmentForSlotName(__VA_ARGS__)
#define Skeleton_getAttachmentForSlotIndex(...) spSkeleton_getAttachmentForSlotIndex(__VA_ARGS__)
#define Skeleton_setAttachment(...) spSkeleton_setAttachment(__VA_ARGS__)
#define Skeleton_update(...) spSkeleton_update(__VA_ARGS__)
#endif

#ifdef __cplusplus
}
#endif

#endif /* SPINE_SKELETON_H_*/
