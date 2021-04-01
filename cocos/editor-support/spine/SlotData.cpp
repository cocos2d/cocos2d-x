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

#include <spine/SlotData.h>

#include <assert.h>

using namespace spine;

SlotData::SlotData(int index, const String &name, BoneData &boneData) :
		_index(index),
		_name(name),
		_boneData(boneData),
		_color(1, 1, 1, 1),
		_darkColor(0, 0, 0, 0),
		_hasDarkColor(false),
		_attachmentName(),
		_blendMode(BlendMode_Normal) {
	assert(_index >= 0);
	assert(_name.length() > 0);
}

int SlotData::getIndex() {
	return _index;
}

const String &SlotData::getName() {
	return _name;
}

BoneData &SlotData::getBoneData() {
	return _boneData;
}

Color &SlotData::getColor() {
	return _color;
}

Color &SlotData::getDarkColor() {
	return _darkColor;
}

bool SlotData::hasDarkColor() {
	return _hasDarkColor;
}

void SlotData::setHasDarkColor(bool inValue) {
	_hasDarkColor = inValue;
}

const String &SlotData::getAttachmentName() {
	return _attachmentName;
}

void SlotData::setAttachmentName(const String &inValue) {
	_attachmentName = inValue;
}

BlendMode SlotData::getBlendMode() {
	return _blendMode;
}

void SlotData::setBlendMode(BlendMode inValue) {
	_blendMode = inValue;
}
