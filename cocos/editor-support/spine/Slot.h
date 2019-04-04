/******************************************************************************
 * Spine Runtimes Software License v2.5
 *
 * Copyright (c) 2013-2016, Esoteric Software
 * All rights reserved.
 *
 * You are granted a perpetual, non-exclusive, non-sublicensable, and
 * non-transferable license to use, install, execute, and perform the Spine
 * Runtimes software and derivative works solely for personal or internal
 * use. Without the written permission of Esoteric Software (see Section 2 of
 * the Spine Software License Agreement), you may not (a) modify, translate,
 * adapt, or develop new applications using the Spine Runtimes or otherwise
 * create derivative works or improvements of the Spine Runtimes or (b) remove,
 * delete, alter, or obscure any trademarks or any copyright, trademark, patent,
 * or other intellectual property or proprietary rights notices on or in the
 * Software, including any copy thereof. Redistributions in binary or source
 * form must include this license and terms.
 *
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, BUSINESS INTERRUPTION, OR LOSS OF
 * USE, DATA, OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef SPINE_SLOT_H_
#define SPINE_SLOT_H_

#include "spine/dll.h"
#include "spine/Bone.h"
#include "spine/Attachment.h"
#include "spine/SlotData.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct spSlot {
	spSlotData* const data;
	spBone* const bone;
	spColor color;
	spColor* darkColor;
	spAttachment* const attachment;

	int attachmentVerticesCapacity;
	int attachmentVerticesCount;
	float* attachmentVertices;

#ifdef __cplusplus
	spSlot() :
		data(0),
		bone(0),
		color(),
		darkColor(0),
		attachment(0),
		attachmentVerticesCapacity(0),
		attachmentVerticesCount(0),
		attachmentVertices(0) {
	}
#endif
} spSlot;

SP_API spSlot* spSlot_create (spSlotData* data, spBone* bone);
SP_API void spSlot_dispose (spSlot* self);

/* @param attachment May be 0 to clear the attachment for the slot. */
SP_API void spSlot_setAttachment (spSlot* self, spAttachment* attachment);

SP_API void spSlot_setAttachmentTime (spSlot* self, float time);
SP_API float spSlot_getAttachmentTime (const spSlot* self);

SP_API void spSlot_setToSetupPose (spSlot* self);

#ifdef SPINE_SHORT_NAMES
typedef spSlot Slot;
#define Slot_create(...) spSlot_create(__VA_ARGS__)
#define Slot_dispose(...) spSlot_dispose(__VA_ARGS__)
#define Slot_setAttachment(...) spSlot_setAttachment(__VA_ARGS__)
#define Slot_setAttachmentTime(...) spSlot_setAttachmentTime(__VA_ARGS__)
#define Slot_getAttachmentTime(...) spSlot_getAttachmentTime(__VA_ARGS__)
#define Slot_setToSetupPose(...) spSlot_setToSetupPose(__VA_ARGS__)
#endif

#ifdef __cplusplus
}
#endif

#endif /* SPINE_SLOT_H_ */
