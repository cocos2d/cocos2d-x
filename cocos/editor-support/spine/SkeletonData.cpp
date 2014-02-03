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

#include <spine/SkeletonData.h>
#include <string.h>
#include <spine/extension.h>

spSkeletonData* spSkeletonData_create () {
	return NEW(spSkeletonData);
}

void spSkeletonData_dispose (spSkeletonData* self) {
	int i;
	for (i = 0; i < self->boneCount; ++i)
		spBoneData_dispose(self->bones[i]);
	FREE(self->bones);

	for (i = 0; i < self->slotCount; ++i)
		spSlotData_dispose(self->slots[i]);
	FREE(self->slots);

	for (i = 0; i < self->skinCount; ++i)
		spSkin_dispose(self->skins[i]);
	FREE(self->skins);

	for (i = 0; i < self->animationCount; ++i)
		spAnimation_dispose(self->animations[i]);
	FREE(self->animations);

	for (i = 0; i < self->eventCount; ++i)
		spEventData_dispose(self->events[i]);
	FREE(self->events);

	FREE(self);
}

spBoneData* spSkeletonData_findBone (const spSkeletonData* self, const char* boneName) {
	int i;
	for (i = 0; i < self->boneCount; ++i)
		if (strcmp(self->bones[i]->name, boneName) == 0) return self->bones[i];
	return 0;
}

int spSkeletonData_findBoneIndex (const spSkeletonData* self, const char* boneName) {
	int i;
	for (i = 0; i < self->boneCount; ++i)
		if (strcmp(self->bones[i]->name, boneName) == 0) return i;
	return -1;
}

spSlotData* spSkeletonData_findSlot (const spSkeletonData* self, const char* slotName) {
	int i;
	for (i = 0; i < self->slotCount; ++i)
		if (strcmp(self->slots[i]->name, slotName) == 0) return self->slots[i];
	return 0;
}

int spSkeletonData_findSlotIndex (const spSkeletonData* self, const char* slotName) {
	int i;
	for (i = 0; i < self->slotCount; ++i)
		if (strcmp(self->slots[i]->name, slotName) == 0) return i;
	return -1;
}

spSkin* spSkeletonData_findSkin (const spSkeletonData* self, const char* skinName) {
	int i;
	for (i = 0; i < self->skinCount; ++i)
		if (strcmp(self->skins[i]->name, skinName) == 0) return self->skins[i];
	return 0;
}

spEventData* spSkeletonData_findEvent (const spSkeletonData* self, const char* eventName) {
	int i;
	for (i = 0; i < self->eventCount; ++i)
		if (strcmp(self->events[i]->name, eventName) == 0) return self->events[i];
	return 0;
}

spAnimation* spSkeletonData_findAnimation (const spSkeletonData* self, const char* animationName) {
	int i;
	for (i = 0; i < self->animationCount; ++i)
		if (strcmp(self->animations[i]->name, animationName) == 0) return self->animations[i];
	return 0;
}
