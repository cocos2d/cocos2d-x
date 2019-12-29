/******************************************************************************
 * Spine Runtimes License Agreement
 * Last updated May 1, 2019. Replaces all prior versions.
 *
 * Copyright (c) 2013-2019, Esoteric Software LLC
 *
 * Integration of the Spine Runtimes into software or otherwise creating
 * derivative works of the Spine Runtimes is permitted under the terms and
 * conditions of Section 2 of the Spine Editor License Agreement:
 * http://esotericsoftware.com/spine-editor-license
 *
 * Otherwise, it is permitted to integrate the Spine Runtimes into software
 * or otherwise create derivative works of the Spine Runtimes (collectively,
 * "Products"), provided that each user of the Products must obtain their own
 * Spine Editor license and redistribution of the Products in any form must
 * include this license and copyright notice.
 *
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE LLC "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 * NO EVENT SHALL ESOTERIC SOFTWARE LLC BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, BUSINESS
 * INTERRUPTION, OR LOSS OF USE, DATA, OR PROFITS) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifdef SPINE_UE4
#include "SpinePluginPrivatePCH.h"
#endif

#include <spine/AttachmentTimeline.h>

#include <spine/Skeleton.h>
#include <spine/Event.h>

#include <spine/Animation.h>
#include <spine/Bone.h>
#include <spine/TimelineType.h>
#include <spine/Slot.h>
#include <spine/SlotData.h>

using namespace spine;

RTTI_IMPL(AttachmentTimeline, Timeline)

AttachmentTimeline::AttachmentTimeline(int frameCount) : Timeline(), _slotIndex(0) {
	_frames.ensureCapacity(frameCount);
	_attachmentNames.ensureCapacity(frameCount);

	_frames.setSize(frameCount, 0);

	for (int i = 0; i < frameCount; ++i) {
		_attachmentNames.add(String());
	}
}

void AttachmentTimeline::apply(Skeleton &skeleton, float lastTime, float time, Vector<Event *> *pEvents, float alpha,
	MixBlend blend, MixDirection direction
) {
	SP_UNUSED(lastTime);
	SP_UNUSED(pEvents);
	SP_UNUSED(alpha);

	assert(_slotIndex < skeleton._slots.size());

	String *attachmentName;
	Slot *slotP = skeleton._slots[_slotIndex];
	Slot &slot = *slotP;
	if (!slot._bone.isActive()) return;

	if (direction == MixDirection_Out && blend == MixBlend_Setup) {
		attachmentName = &slot._data._attachmentName;
		slot.setAttachment(attachmentName->length() == 0 ? NULL : skeleton.getAttachment(_slotIndex, *attachmentName));
		return;
	}

	if (time < _frames[0]) {
		// Time is before first frame.
		if (blend == MixBlend_Setup || blend == MixBlend_First) {
			attachmentName = &slot._data._attachmentName;
			slot.setAttachment(attachmentName->length() == 0 ? NULL : skeleton.getAttachment(_slotIndex, *attachmentName));
		}
		return;
	}

	size_t frameIndex;
	if (time >= _frames[_frames.size() - 1]) {
		// Time is after last frame.
		frameIndex = _frames.size() - 1;
	} else {
		frameIndex = Animation::binarySearch(_frames, time, 1) - 1;
	}

	attachmentName = &_attachmentNames[frameIndex];
	slot.setAttachment(attachmentName->length() == 0 ? NULL : skeleton.getAttachment(_slotIndex, *attachmentName));
}

int AttachmentTimeline::getPropertyId() {
	return ((int) TimelineType_Attachment << 24) + _slotIndex;
}

void AttachmentTimeline::setFrame(int frameIndex, float time, const String &attachmentName) {
	_frames[frameIndex] = time;
	_attachmentNames[frameIndex] = attachmentName;
}

size_t AttachmentTimeline::getSlotIndex() {
	return _slotIndex;
}

void AttachmentTimeline::setSlotIndex(size_t inValue) {
	_slotIndex = inValue;
}

const Vector<float> &AttachmentTimeline::getFrames() {
	return _frames;
}

const Vector<String> &AttachmentTimeline::getAttachmentNames() {
	return _attachmentNames;
}

size_t AttachmentTimeline::getFrameCount() {
	return _frames.size();
}
