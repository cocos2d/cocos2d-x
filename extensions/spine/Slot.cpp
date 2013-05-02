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

#include <spine/Slot.h>
#include <spine/extension.h>
#include <spine/Skeleton.h>

namespace cocos2d { namespace extension {

typedef struct {
	Slot super;
	float attachmentTime;
} _Internal;

Slot* Slot_create (SlotData* data, Skeleton* skeleton, Bone* bone) {
	Slot* self = SUPER(NEW(_Internal));
	CONST_CAST(SlotData*, self->data) = data;
	CONST_CAST(Skeleton*, self->skeleton) = skeleton;
	CONST_CAST(Bone*, self->bone) = bone;
	Slot_setToBindPose(self);
	return self;
}

void Slot_dispose (Slot* self) {
	FREE(self);
}

void Slot_setAttachment (Slot* self, Attachment* attachment) {
	CONST_CAST(Attachment*, self->attachment) = attachment;
	SUB_CAST(_Internal, self) ->attachmentTime = self->skeleton->time;
}

void Slot_setAttachmentTime (Slot* self, float time) {
	SUB_CAST(_Internal, self) ->attachmentTime = self->skeleton->time - time;
}

float Slot_getAttachmentTime (const Slot* self) {
	return self->skeleton->time - SUB_CAST(_Internal, self) ->attachmentTime;
}

void Slot_setToBindPose (Slot* self) {
	self->r = self->data->r;
	self->g = self->data->g;
	self->b = self->data->b;
	self->a = self->data->a;

	Attachment* attachment = 0;
	if (self->data->attachmentName) {
		/* Find slot index. */
		int i;
		for (i = 0; i < self->skeleton->data->slotCount; ++i) {
			if (self->data == self->skeleton->data->slots[i]) {
				attachment = Skeleton_getAttachmentForSlotIndex(self->skeleton, i, self->data->attachmentName);
				break;
			}
		}
	}
	Slot_setAttachment(self, attachment);
}

}} // namespace cocos2d { namespace extension {
