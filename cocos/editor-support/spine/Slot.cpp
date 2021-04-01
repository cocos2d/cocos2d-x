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

#include <spine/Slot.h>

#include <spine/SlotData.h>
#include <spine/Bone.h>
#include <spine/Skeleton.h>
#include <spine/Attachment.h>

using namespace spine;

Slot::Slot(SlotData &data, Bone &bone) :
		_data(data),
		_bone(bone),
		_skeleton(bone.getSkeleton()),
		_color(1, 1, 1, 1),
		_darkColor(0, 0, 0, 0),
		_hasDarkColor(data.hasDarkColor()),
		_attachment(NULL),
		_attachmentTime(0) {
	setToSetupPose();
}

void Slot::setToSetupPose() {
	_color.set(_data.getColor());

	const String &attachmentName = _data.getAttachmentName();
	if (attachmentName.length() > 0) {
		_attachment = NULL;
		setAttachment(_skeleton.getAttachment(_data.getIndex(), attachmentName));
	} else {
		setAttachment(NULL);
	}
}

SlotData &Slot::getData() {
	return _data;
}

Bone &Slot::getBone() {
	return _bone;
}

Skeleton &Slot::getSkeleton() {
	return _skeleton;
}

Color &Slot::getColor() {
	return _color;
}

Color &Slot::getDarkColor() {
	return _darkColor;
}

bool Slot::hasDarkColor() {
	return _hasDarkColor;
}

Attachment *Slot::getAttachment() {
	return _attachment;
}

void Slot::setAttachment(Attachment *inValue) {
	if (_attachment == inValue) {
		return;
	}

	_attachment = inValue;
	_attachmentTime = _skeleton.getTime();
	_deform.clear();
}

float Slot::getAttachmentTime() {
	return _skeleton.getTime() - _attachmentTime;
}

void Slot::setAttachmentTime(float inValue) {
	_attachmentTime = _skeleton.getTime() - inValue;
}

Vector<float> &Slot::getDeform() {
	return _deform;
}
