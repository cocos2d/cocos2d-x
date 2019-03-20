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
	_attachmentVertices.clear();
}

float Slot::getAttachmentTime() {
	return _skeleton.getTime() - _attachmentTime;
}

void Slot::setAttachmentTime(float inValue) {
	_attachmentTime = _skeleton.getTime() - inValue;
}

Vector<float> &Slot::getAttachmentVertices() {
	return _attachmentVertices;
}
