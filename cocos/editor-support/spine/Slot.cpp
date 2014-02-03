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

#include <spine/Slot.h>
#include <spine/extension.h>
#include <spine/Skeleton.h>

typedef struct {
	spSlot super;
	float attachmentTime;
} _spSlot;

spSlot* spSlot_create (spSlotData* data, spSkeleton* skeleton, spBone* bone) {
	spSlot* self = SUPER(NEW(_spSlot));
	CONST_CAST(spSlotData*, self->data) = data;
	CONST_CAST(spSkeleton*, self->skeleton) = skeleton;
	CONST_CAST(spBone*, self->bone) = bone;
	spSlot_setToSetupPose(self);
	return self;
}

void spSlot_dispose (spSlot* self) {
	FREE(self);
}

void spSlot_setAttachment (spSlot* self, spAttachment* attachment) {
	CONST_CAST(spAttachment*, self->attachment) = attachment;
	SUB_CAST(_spSlot, self) ->attachmentTime = self->skeleton->time;
}

void spSlot_setAttachmentTime (spSlot* self, float time) {
	SUB_CAST(_spSlot, self) ->attachmentTime = self->skeleton->time - time;
}

float spSlot_getAttachmentTime (const spSlot* self) {
	return self->skeleton->time - SUB_CAST(_spSlot, self) ->attachmentTime;
}

void spSlot_setToSetupPose (spSlot* self) {
	spAttachment* attachment = 0;
	self->r = self->data->r;
	self->g = self->data->g;
	self->b = self->data->b;
	self->a = self->data->a;

	if (self->data->attachmentName) {
		/* Find slot index. */
		int i;
		for (i = 0; i < self->skeleton->data->slotCount; ++i) {
			if (self->data == self->skeleton->data->slots[i]) {
				attachment = spSkeleton_getAttachmentForSlotIndex(self->skeleton, i, self->data->attachmentName);
				break;
			}
		}
	}
	spSlot_setAttachment(self, attachment);
}
