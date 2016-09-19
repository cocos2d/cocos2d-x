/******************************************************************************
 * Spine Runtimes Software License
 * Version 2.3
 * 
 * Copyright (c) 2013-2015, Esoteric Software
 * All rights reserved.
 * 
 * You are granted a perpetual, non-exclusive, non-sublicensable and
 * non-transferable license to use, install, execute and perform the Spine
 * Runtimes Software (the "Software") and derivative works solely for personal
 * or internal use. Without the written permission of Esoteric Software (see
 * Section 2 of the Spine Software License Agreement), you may not (a) modify,
 * translate, adapt or otherwise create derivative works, improvements of the
 * Software or develop new applications using the Software or (b) remove,
 * delete, alter or obscure any trademarks or any copyright, trademark, patent
 * or other intellectual property or proprietary rights notices on or in the
 * Software, including any copy thereof. Redistributions in binary or source
 * form must include this license and terms.
 * 
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#include <spine/Skeleton.h>
#include <stdlib.h>
#include <string.h>
#include <spine/extension.h>
#include <spine/Skin.h>

typedef enum {
	SP_UPDATE_BONE, SP_UPDATE_IK_CONSTRAINT, SP_UPDATE_PATH_CONSTRAINT, SP_UPDATE_TRANSFORM_CONSTRAINT
} _spUpdateType;

typedef struct {
	_spUpdateType type;
	void* object;
} _spUpdate;

typedef struct {
	spSkeleton super;

	int updateCacheCount;
	int updateCacheCapacity;
	_spUpdate* updateCache;
} _spSkeleton;

spSkeleton* spSkeleton_create (spSkeletonData* data) {
	int i;
	int* childrenCounts;

	_spSkeleton* internal = NEW(_spSkeleton);
	spSkeleton* self = SUPER(internal);
	CONST_CAST(spSkeletonData*, self->data) = data;

	self->bonesCount = self->data->bonesCount;
	self->bones = MALLOC(spBone*, self->bonesCount);
	childrenCounts = CALLOC(int, self->bonesCount);

	for (i = 0; i < self->bonesCount; ++i) {
		spBoneData* boneData = self->data->bones[i];
		spBone* bone;
		if (!boneData->parent)
			bone = spBone_create(boneData, self, 0);
		else {
			spBone* parent = self->bones[boneData->parent->index];
			bone = spBone_create(boneData, self, parent);
			++childrenCounts[boneData->parent->index];
		}
		self->bones[i] = bone;
	}
	for (i = 0; i < self->bonesCount; ++i) {
		spBoneData* boneData = self->data->bones[i];
		spBone* bone = self->bones[i];
		CONST_CAST(spBone**, bone->children) = MALLOC(spBone*, childrenCounts[boneData->index]);
	}
	for (i = 0; i < self->bonesCount; ++i) {
		spBone* bone = self->bones[i];
		spBone* parent = bone->parent;
		if (parent)
			parent->children[parent->childrenCount++] = bone;
	}
	CONST_CAST(spBone*, self->root) = (self->bonesCount > 0 ? self->bones[0] : NULL);

	self->slotsCount = data->slotsCount;
	self->slots = MALLOC(spSlot*, self->slotsCount);
	for (i = 0; i < self->slotsCount; ++i) {
		spSlotData *slotData = data->slots[i];
		spBone* bone = self->bones[slotData->boneData->index];
		self->slots[i] = spSlot_create(slotData, bone);
	}

	self->drawOrder = MALLOC(spSlot*, self->slotsCount);
	memcpy(self->drawOrder, self->slots, sizeof(spSlot*) * self->slotsCount);

	self->ikConstraintsCount = data->ikConstraintsCount;
	self->ikConstraints = MALLOC(spIkConstraint*, self->ikConstraintsCount);
	self->ikConstraintsSorted = MALLOC(spIkConstraint*, self->ikConstraintsCount);
	for (i = 0; i < self->data->ikConstraintsCount; ++i)
		self->ikConstraints[i] = spIkConstraint_create(self->data->ikConstraints[i], self);

	self->transformConstraintsCount = data->transformConstraintsCount;
	self->transformConstraints = MALLOC(spTransformConstraint*, self->transformConstraintsCount);
	for (i = 0; i < self->data->transformConstraintsCount; ++i)
		self->transformConstraints[i] = spTransformConstraint_create(self->data->transformConstraints[i], self);

	self->pathConstraintsCount = data->pathConstraintsCount;
	self->pathConstraints = MALLOC(spPathConstraint*, self->pathConstraintsCount);
	for (i = 0; i < self->data->pathConstraintsCount; i++)
		self->pathConstraints[i] = spPathConstraint_create(self->data->pathConstraints[i], self);

	self->r = 1; self->g = 1; self->b = 1; self->a = 1;

	spSkeleton_updateCache(self);

	FREE(childrenCounts);

	return self;
}

void spSkeleton_dispose (spSkeleton* self) {
	int i;
	_spSkeleton* internal = SUB_CAST(_spSkeleton, self);

	FREE(internal->updateCache);

	for (i = 0; i < self->bonesCount; ++i)
		spBone_dispose(self->bones[i]);
	FREE(self->bones);

	for (i = 0; i < self->slotsCount; ++i)
		spSlot_dispose(self->slots[i]);
	FREE(self->slots);

	for (i = 0; i < self->ikConstraintsCount; ++i)
		spIkConstraint_dispose(self->ikConstraints[i]);
	FREE(self->ikConstraints);
	FREE(self->ikConstraintsSorted);

	for (i = 0; i < self->transformConstraintsCount; ++i)
		spTransformConstraint_dispose(self->transformConstraints[i]);
	FREE(self->transformConstraints);

	for (i = 0; i < self->pathConstraintsCount; i++)
		spPathConstraint_dispose(self->pathConstraints[i]);
	FREE(self->pathConstraints);

	FREE(self->drawOrder);
	FREE(self);
}

static void _addToUpdateCache(_spSkeleton* const internal, _spUpdateType type, void *object) {
	_spUpdate* update;
	if (internal->updateCacheCount == internal->updateCacheCapacity) {
		internal->updateCacheCapacity *= 2;
		internal->updateCache = realloc(internal->updateCache, sizeof(_spUpdate) * internal->updateCacheCapacity);
	}
	update = internal->updateCache + internal->updateCacheCount;
	update->type = type;
	update->object = object;
	++internal->updateCacheCount;
}

static void _sortBone(_spSkeleton* const internal, spBone* bone) {
	if (bone->sorted) return;
	if (bone->parent) _sortBone(internal, bone->parent);
	bone->sorted = 1;
	_addToUpdateCache(internal, SP_UPDATE_BONE, bone);
}

static void _sortPathConstraintAttachmentBones(_spSkeleton* const internal, spAttachment* attachment, spBone* slotBone) {
	spPathAttachment* pathAttachment = (spPathAttachment*)attachment;
	int* pathBones;
	int pathBonesCount;
	if (pathAttachment->super.super.type != SP_ATTACHMENT_PATH) return;
	pathBones = pathAttachment->super.bones;
	pathBonesCount = pathAttachment->super.bonesCount;
	if (pathBones == 0)
		_sortBone(internal, slotBone);
	else {
		spBone** bones = internal->super.bones;
		int i;
		for (i = 0; i < pathBonesCount; i++)
			_sortBone(internal, bones[pathBones[i]]);
	}
}

static void _sortPathConstraintAttachment(_spSkeleton* const internal, spSkin* skin, int slotIndex, spBone* slotBone) {
	_Entry* entry = SUB_CAST(_spSkin, skin)->entries;
	while (entry) {
		if (entry->slotIndex == slotIndex) _sortPathConstraintAttachmentBones(internal, entry->attachment, slotBone);
		entry = entry->next;
	}
}

static void _sortReset(spBone** bones, int bonesCount) {
	int i;
	for (i = 0; i < bonesCount; ++i) {
		spBone* bone = bones[i];
		if (bone->sorted) _sortReset(bone->children, bone->childrenCount);
		bone->sorted = 0;
	}
}

void spSkeleton_updateCache (spSkeleton* self) {
	int i, ii, n, nn, level;
	spBone** bones;
	spIkConstraint** ikConstraints;
	spPathConstraint** pathConstraints;
	spTransformConstraint** transformConstraints;
	_spSkeleton* internal = SUB_CAST(_spSkeleton, self);
	internal->updateCacheCapacity = self->bonesCount + self->ikConstraintsCount + self->transformConstraintsCount + self->pathConstraintsCount;

	FREE(internal->updateCache);
	internal->updateCache = MALLOC(_spUpdate, internal->updateCacheCapacity);
	internal->updateCacheCount = 0;

	bones = self->bones;
	for (i = 0; i < self->bonesCount; ++i)
		bones[i]->sorted = 0;

	/* IK first, lowest hierarchy depth first. */
	if (self->ikConstraintsSorted) FREE(self->ikConstraintsSorted);
	self->ikConstraintsSorted = MALLOC(spIkConstraint*, self->ikConstraintsCount);
	ikConstraints = self->ikConstraintsSorted;
	for (i = 0; i < self->ikConstraintsCount; ++i)
		ikConstraints[i] = self->ikConstraints[i];
	for (i = 0; i < self->ikConstraintsCount; ++i) {
		spIkConstraint* ik = ikConstraints[i];
		spBone* bone = ik->bones[0]->parent;
		for (level = 0; bone; ++level)
			bone = bone->parent;
		ik->level = level;
	}
	for (i = 1; i < self->ikConstraintsCount; ++i) {
		spIkConstraint* ik = ikConstraints[i];
		level = ik->level;
		for (ii = i - 1; ii >= 0; --ii) {
			spIkConstraint* other = ikConstraints[ii];
			if (other->level < level) break;
			ikConstraints[ii + 1] = other;
		}
		ikConstraints[ii + 1] = ik;
	}
	for (i = 0; i < self->ikConstraintsCount; ++i) {
		spBone** constrained;
		spBone* parent;
		spIkConstraint* constraint = ikConstraints[i];
		spBone* target = constraint->target;
		_sortBone(internal, target);

		constrained = constraint->bones;
		parent = constrained[0];
		_sortBone(internal, parent);

		_addToUpdateCache(internal, SP_UPDATE_IK_CONSTRAINT, constraint);

		_sortReset(parent->children, parent->childrenCount);
		constrained[constraint->bonesCount - 1]->sorted = 1;
	}

	pathConstraints = self->pathConstraints;
	for (i = 0, n = self->pathConstraintsCount; i < n; i++) {
		spAttachment* attachment;
		spBone** constrained;
		int boneCount;
		spPathConstraint* constraint = pathConstraints[i];

		spSlot* slot = constraint->target;
		int slotIndex = slot->data->index;
		spBone* slotBone = slot->bone;
		if (self->skin) _sortPathConstraintAttachment(internal, self->skin, slotIndex, slotBone);
		if (self->data->defaultSkin && self->data->defaultSkin != self->skin)
			_sortPathConstraintAttachment(internal, self->data->defaultSkin, slotIndex, slotBone);
		for (ii = 0, nn = self->data->skinsCount; ii < nn; ii++)
			_sortPathConstraintAttachment(internal, self->data->skins[ii], slotIndex, slotBone);

		attachment = slot->attachment;
		if (attachment->type == SP_ATTACHMENT_PATH) _sortPathConstraintAttachmentBones(internal, attachment, slotBone);

		constrained = constraint->bones;
		boneCount = constraint->bonesCount;
		for (ii = 0; ii < boneCount; ii++)
			_sortBone(internal, constrained[ii]);

		_addToUpdateCache(internal, SP_UPDATE_PATH_CONSTRAINT, constraint);

		for (ii = 0; ii < boneCount; ii++)
			_sortReset(constrained[ii]->children, constrained[ii]->childrenCount);
		for (ii = 0; ii < boneCount; ii++)
			constrained[ii]->sorted = 1;
	}

	transformConstraints = self->transformConstraints;
	for (i = 0, n = self->transformConstraintsCount; i < n; ++i) {
		spTransformConstraint* constraint = transformConstraints[i];
		spBone** constrained = constraint->bones;

		_sortBone(internal, constraint->target);

		for (ii = 0; ii < constraint->bonesCount; ++ii)
			_sortBone(internal, constrained[ii]);

		_addToUpdateCache(internal, SP_UPDATE_TRANSFORM_CONSTRAINT, constraint);

		for (ii = 0; ii < constraint->bonesCount; ++ii) {
			spBone* bone = constrained[ii];
			_sortReset(bone->children, bone->childrenCount);
		}
		for (ii = 0; ii < constraint->bonesCount; ++ii)
			constrained[ii]->sorted = 1;
	}

	for (i = 0; i < self->bonesCount; ++i)
		_sortBone(internal, self->bones[i]);
}

void spSkeleton_updateWorldTransform (const spSkeleton* self) {
	int i;
	_spSkeleton* internal = SUB_CAST(_spSkeleton, self);

	for (i = 0; i < internal->updateCacheCount; ++i) {
		_spUpdate* update = internal->updateCache + i;
		switch (update->type) {
		case SP_UPDATE_BONE:
			spBone_updateWorldTransform((spBone*)update->object);
			break;
		case SP_UPDATE_IK_CONSTRAINT:
			spIkConstraint_apply((spIkConstraint*)update->object);
			break;
		case SP_UPDATE_TRANSFORM_CONSTRAINT:
			spTransformConstraint_apply((spTransformConstraint*)update->object);
			break;
		case SP_UPDATE_PATH_CONSTRAINT:
			spPathConstraint_apply((spPathConstraint*)update->object);
			break;
		}
	}
}

void spSkeleton_setToSetupPose (const spSkeleton* self) {
	spSkeleton_setBonesToSetupPose(self);
	spSkeleton_setSlotsToSetupPose(self);
}

void spSkeleton_setBonesToSetupPose (const spSkeleton* self) {
	int i;
	for (i = 0; i < self->bonesCount; ++i)
		spBone_setToSetupPose(self->bones[i]);

	for (i = 0; i < self->ikConstraintsCount; ++i) {
		spIkConstraint* ikConstraint = self->ikConstraints[i];
		ikConstraint->bendDirection = ikConstraint->data->bendDirection;
		ikConstraint->mix = ikConstraint->data->mix;
	}

	for (i = 0; i < self->transformConstraintsCount; ++i) {
		spTransformConstraint* constraint = self->transformConstraints[i];
		spTransformConstraintData* data = constraint->data;
		constraint->rotateMix = data->rotateMix;
		constraint->translateMix = data->translateMix;
		constraint->scaleMix = data->scaleMix;
		constraint->shearMix = data->shearMix;
	}

	for (i = 0; i < self->pathConstraintsCount; ++i) {
		spPathConstraint* constraint = self->pathConstraints[i];
		spPathConstraintData* data = constraint->data;
		constraint->position = data->position;
		constraint->spacing = data->spacing;
		constraint->rotateMix = data->rotateMix;
		constraint->translateMix = data->translateMix;
	}
}

void spSkeleton_setSlotsToSetupPose (const spSkeleton* self) {
	int i;
	memcpy(self->drawOrder, self->slots, self->slotsCount * sizeof(spSlot*));
	for (i = 0; i < self->slotsCount; ++i)
		spSlot_setToSetupPose(self->slots[i]);
}

spBone* spSkeleton_findBone (const spSkeleton* self, const char* boneName) {
	int i;
	for (i = 0; i < self->bonesCount; ++i)
		if (strcmp(self->data->bones[i]->name, boneName) == 0) return self->bones[i];
	return 0;
}

int spSkeleton_findBoneIndex (const spSkeleton* self, const char* boneName) {
	int i;
	for (i = 0; i < self->bonesCount; ++i)
		if (strcmp(self->data->bones[i]->name, boneName) == 0) return i;
	return -1;
}

spSlot* spSkeleton_findSlot (const spSkeleton* self, const char* slotName) {
	int i;
	for (i = 0; i < self->slotsCount; ++i)
		if (strcmp(self->data->slots[i]->name, slotName) == 0) return self->slots[i];
	return 0;
}

int spSkeleton_findSlotIndex (const spSkeleton* self, const char* slotName) {
	int i;
	for (i = 0; i < self->slotsCount; ++i)
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
	if (newSkin) {
		if (self->skin)
			spSkin_attachAll(newSkin, self, self->skin);
		else {
			/* No previous skin, attach setup pose attachments. */
			int i;
			for (i = 0; i < self->slotsCount; ++i) {
				spSlot* slot = self->slots[i];
				if (slot->data->attachmentName) {
					spAttachment* attachment = spSkin_getAttachment(newSkin, i, slot->data->attachmentName);
					if (attachment) spSlot_setAttachment(slot, attachment);
				}
			}
		}
	}
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
	for (i = 0; i < self->slotsCount; ++i) {
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

spIkConstraint* spSkeleton_findIkConstraint (const spSkeleton* self, const char* constraintName) {
	int i;
	for (i = 0; i < self->ikConstraintsCount; ++i)
		if (strcmp(self->ikConstraints[i]->data->name, constraintName) == 0) return self->ikConstraints[i];
	return 0;
}

spTransformConstraint* spSkeleton_findTransformConstraint (const spSkeleton* self, const char* constraintName) {
	int i;
	for (i = 0; i < self->transformConstraintsCount; ++i)
		if (strcmp(self->transformConstraints[i]->data->name, constraintName) == 0) return self->transformConstraints[i];
	return 0;
}

spPathConstraint* spSkeleton_findPathConstraint (const spSkeleton* self, const char* constraintName) {
	int i;
	for (i = 0; i < self->pathConstraintsCount; ++i)
		if (strcmp(self->pathConstraints[i]->data->name, constraintName) == 0) return self->pathConstraints[i];
	return 0;
}

void spSkeleton_update (spSkeleton* self, float deltaTime) {
	self->time += deltaTime;
}
