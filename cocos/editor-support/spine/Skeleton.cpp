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

#include <spine/Skeleton.h>
#include <string.h>
#include <spine/extension.h>

spSkeleton* spSkeleton_create (spSkeletonData* data) {
	int i, ii;

	spSkeleton* self = NEW(spSkeleton);
	CONST_CAST(spSkeletonData*, self->data) = data;

	self->boneCount = self->data->boneCount;
	self->bones = MALLOC(spBone*, self->boneCount);

	for (i = 0; i < self->boneCount; ++i) {
		spBoneData* boneData = self->data->bones[i];
		spBone* parent = 0;
		if (boneData->parent) {
			/* Find parent bone. */
			for (ii = 0; ii < self->boneCount; ++ii) {
				if (data->bones[ii] == boneData->parent) {
					parent = self->bones[ii];
					break;
				}
			}
		}
		self->bones[i] = spBone_create(boneData, parent);
	}
	CONST_CAST(spBone*, self->root) = self->bones[0];

	self->slotCount = data->slotCount;
	self->slots = MALLOC(spSlot*, self->slotCount);
	for (i = 0; i < self->slotCount; ++i) {
		spSlotData *slotData = data->slots[i];

		/* Find bone for the slotData's boneData. */
		spBone* bone = 0;
		for (ii = 0; ii < self->boneCount; ++ii) {
			if (data->bones[ii] == slotData->boneData) {
				bone = self->bones[ii];
				break;
			}
		}
		self->slots[i] = spSlot_create(slotData, self, bone);
	}

	self->drawOrder = MALLOC(spSlot*, self->slotCount);
	memcpy(self->drawOrder, self->slots, sizeof(spSlot*) * self->slotCount);

	self->r = 1;
	self->g = 1;
	self->b = 1;
	self->a = 1;

	return self;
}

void spSkeleton_dispose (spSkeleton* self) {
	int i;
	for (i = 0; i < self->boneCount; ++i)
		spBone_dispose(self->bones[i]);
	FREE(self->bones);

	for (i = 0; i < self->slotCount; ++i)
		spSlot_dispose(self->slots[i]);
	FREE(self->slots);

	FREE(self->drawOrder);
	FREE(self);
}

void spSkeleton_updateWorldTransform (const spSkeleton* self) {
	int i;
	for (i = 0; i < self->boneCount; ++i)
		spBone_updateWorldTransform(self->bones[i], self->flipX, self->flipY);
}

void spSkeleton_setToSetupPose (const spSkeleton* self) {
	spSkeleton_setBonesToSetupPose(self);
	spSkeleton_setSlotsToSetupPose(self);
}

void spSkeleton_setBonesToSetupPose (const spSkeleton* self) {
	int i;
	for (i = 0; i < self->boneCount; ++i)
		spBone_setToSetupPose(self->bones[i]);
}

void spSkeleton_setSlotsToSetupPose (const spSkeleton* self) {
	int i;
	memcpy(self->drawOrder, self->slots, self->slotCount * sizeof(int));
	for (i = 0; i < self->slotCount; ++i)
		spSlot_setToSetupPose(self->slots[i]);
}

spBone* spSkeleton_findBone (const spSkeleton* self, const char* boneName) {
	int i;
	for (i = 0; i < self->boneCount; ++i)
		if (strcmp(self->data->bones[i]->name, boneName) == 0) return self->bones[i];
	return 0;
}

int spSkeleton_findBoneIndex (const spSkeleton* self, const char* boneName) {
	int i;
	for (i = 0; i < self->boneCount; ++i)
		if (strcmp(self->data->bones[i]->name, boneName) == 0) return i;
	return -1;
}

spSlot* spSkeleton_findSlot (const spSkeleton* self, const char* slotName) {
	int i;
	for (i = 0; i < self->slotCount; ++i)
		if (strcmp(self->data->slots[i]->name, slotName) == 0) return self->slots[i];
	return 0;
}

int spSkeleton_findSlotIndex (const spSkeleton* self, const char* slotName) {
	int i;
	for (i = 0; i < self->slotCount; ++i)
		if (strcmp(self->data->slots[i]->name, slotName) == 0) return i;
	return -1;
}

int spSkeleton_setSkinByName (spSkeleton* self, const char* skinName) {
	spSkin *skin;
	if (!skinName) {
		spSkeleton_setSkin(self, 0);
		return 1;
	}
	skin = spSkeletonData_findSkin(self->data, skinName);
	if (!skin) return 0;
	spSkeleton_setSkin(self, skin);
	return 1;
}

void spSkeleton_setSkin (spSkeleton* self, spSkin* newSkin) {
	if (self->skin && newSkin) spSkin_attachAll(newSkin, self, self->skin);
	CONST_CAST(spSkin*, self->skin) = newSkin;
}

spAttachment* spSkeleton_getAttachmentForSlotName (const spSkeleton* self, const char* slotName, const char* attachmentName) {
	int slotIndex = spSkeletonData_findSlotIndex(self->data, slotName);
	return spSkeleton_getAttachmentForSlotIndex(self, slotIndex, attachmentName);
}

spAttachment* spSkeleton_getAttachmentForSlotIndex (const spSkeleton* self, int slotIndex, const char* attachmentName) {
	if (slotIndex == -1) return 0;
	if (self->skin) {
		spAttachment *attachment = spSkin_getAttachment(self->skin, slotIndex, attachmentName);
		if (attachment) return attachment;
	}
	if (self->data->defaultSkin) {
		spAttachment *attachment = spSkin_getAttachment(self->data->defaultSkin, slotIndex, attachmentName);
		if (attachment) return attachment;
	}
	return 0;
}

int spSkeleton_setAttachment (spSkeleton* self, const char* slotName, const char* attachmentName) {
	int i;
	for (i = 0; i < self->slotCount; ++i) {
		spSlot *slot = self->slots[i];
		if (strcmp(slot->data->name, slotName) == 0) {
			if (!attachmentName)
				spSlot_setAttachment(slot, 0);
			else {
				spAttachment* attachment = spSkeleton_getAttachmentForSlotIndex(self, i, attachmentName);
				if (!attachment) return 0;
				spSlot_setAttachment(slot, attachment);
			}
			return 1;
		}
	}
	return 0;
}

void spSkeleton_update (spSkeleton* self, float deltaTime) {
	self->time += deltaTime;
}
