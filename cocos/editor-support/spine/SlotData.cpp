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
