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

#include <spine/Skeleton.h>
#include <string.h>
#include <spine/extension.h>

namespace cocos2d { namespace extension {

Skeleton* Skeleton_create (SkeletonData* data) {
	Skeleton* self = NEW(Skeleton);
	CONST_CAST(SkeletonData*, self->data) = data;

	self->boneCount = self->data->boneCount;
	self->bones = MALLOC(Bone*, self->boneCount);
	int i, ii;
	for (i = 0; i < self->boneCount; ++i) {
		BoneData* boneData = self->data->bones[i];
		Bone* parent = 0;
		if (boneData->parent) {
			/* Find parent bone. */
			for (ii = 0; ii < self->boneCount; ++ii) {
				if (data->bones[ii] == boneData->parent) {
					parent = self->bones[ii];
					break;
				}
			}
		}
		self->bones[i] = Bone_create(boneData, parent);
	}
	CONST_CAST(Bone*, self->root) = self->bones[0];

	self->slotCount = data->slotCount;
	self->slots = MALLOC(Slot*, self->slotCount);
	for (i = 0; i < self->slotCount; ++i) {
		SlotData *slotData = data->slots[i];

		/* Find bone for the slotData's boneData. */
		Bone *bone = NULL;
		for (ii = 0; ii < self->boneCount; ++ii) {
			if (data->bones[ii] == slotData->boneData) {
				bone = self->bones[ii];
				break;
			}
		}

		self->slots[i] = Slot_create(slotData, self, bone);
	}

	self->drawOrder = MALLOC(Slot*, self->slotCount);
	memcpy(self->drawOrder, self->slots, sizeof(Slot*) * self->slotCount);

	self->r = 1;
	self->g = 1;
	self->b = 1;
	self->a = 1;

	return self;
}

void Skeleton_dispose (Skeleton* self) {
	int i;
	for (i = 0; i < self->boneCount; ++i)
		Bone_dispose(self->bones[i]);
	FREE(self->bones);

	for (i = 0; i < self->slotCount; ++i)
		Slot_dispose(self->slots[i]);
	FREE(self->slots);

	FREE(self->drawOrder);
}

void Skeleton_updateWorldTransform (const Skeleton* self) {
	int i;
	for (i = 0; i < self->boneCount; ++i)
		Bone_updateWorldTransform(self->bones[i], self->flipX, self->flipY);
}

void Skeleton_setToBindPose (const Skeleton* self) {
	Skeleton_setBonesToBindPose(self);
	Skeleton_setSlotsToBindPose(self);
}

void Skeleton_setBonesToBindPose (const Skeleton* self) {
	int i;
	for (i = 0; i < self->boneCount; ++i)
		Bone_setToBindPose(self->bones[i]);
}

void Skeleton_setSlotsToBindPose (const Skeleton* self) {
	int i;
	for (i = 0; i < self->slotCount; ++i)
		Slot_setToBindPose(self->slots[i]);
}

Bone* Skeleton_findBone (const Skeleton* self, const char* boneName) {
	int i;
	for (i = 0; i < self->boneCount; ++i)
		if (strcmp(self->data->bones[i]->name, boneName) == 0) return self->bones[i];
	return 0;
}

int Skeleton_findBoneIndex (const Skeleton* self, const char* boneName) {
	int i;
	for (i = 0; i < self->boneCount; ++i)
		if (strcmp(self->data->bones[i]->name, boneName) == 0) return i;
	return -1;
}

Slot* Skeleton_findSlot (const Skeleton* self, const char* slotName) {
	int i;
	for (i = 0; i < self->slotCount; ++i)
		if (strcmp(self->data->slots[i]->name, slotName) == 0) return self->slots[i];
	return 0;
}

int Skeleton_findSlotIndex (const Skeleton* self, const char* slotName) {
	int i;
	for (i = 0; i < self->slotCount; ++i)
		if (strcmp(self->data->slots[i]->name, slotName) == 0) return i;
	return -1;
}

int Skeleton_setSkinByName (Skeleton* self, const char* skinName) {
	if (!skinName) {
		Skeleton_setSkin(self, 0);
		return 1;
	}
	Skin *skin = SkeletonData_findSkin(self->data, skinName);
	if (!skin) return 0;
	Skeleton_setSkin(self, skin);
	return 1;
}

void Skeleton_setSkin (Skeleton* self, Skin* newSkin) {
	if (self->skin && newSkin) Skin_attachAll(newSkin, self, self->skin);
	CONST_CAST(Skin*, self->skin) = newSkin;
}

Attachment* Skeleton_getAttachmentForSlotName (const Skeleton* self, const char* slotName, const char* attachmentName) {
	int slotIndex = SkeletonData_findSlotIndex(self->data, slotName);
	return Skeleton_getAttachmentForSlotIndex(self, slotIndex, attachmentName);
}

Attachment* Skeleton_getAttachmentForSlotIndex (const Skeleton* self, int slotIndex, const char* attachmentName) {
	if (slotIndex == -1) return 0;
	if (self->skin) {
		Attachment *attachment = Skin_getAttachment(self->skin, slotIndex, attachmentName);
		if (attachment) return attachment;
	}
	if (self->data->defaultSkin) {
		Attachment *attachment = Skin_getAttachment(self->data->defaultSkin, slotIndex, attachmentName);
		if (attachment) return attachment;
	}
	return 0;
}

int Skeleton_setAttachment (Skeleton* self, const char* slotName, const char* attachmentName) {
	int i;
	for (i = 0; i < self->slotCount; ++i) {
		Slot *slot = self->slots[i];
		if (strcmp(slot->data->name, slotName) == 0) {
			Attachment* attachment = Skeleton_getAttachmentForSlotIndex(self, i, attachmentName);
			if (!attachment) return 0;
			Slot_setAttachment(slot, attachment);
			return 1;
		}
	}
	return 0;
}

void Skeleton_update (Skeleton* self, float deltaTime) {
	self->time += deltaTime;
}

}} // namespace cocos2d { namespace extension {
