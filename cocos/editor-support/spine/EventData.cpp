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

#include <spine/EventData.h>

#include <assert.h>

spine::EventData::EventData(const spine::String &name) :
		_name(name),
		_intValue(0),
		_floatValue(0),
		_stringValue(),
		_audioPath(),
		_volume(1),
		_balance(0) {
	assert(_name.length() > 0);
}

/// The name of the event, which is unique within the skeleton.
const spine::String &spine::EventData::getName() const {
	return _name;
}

int spine::EventData::getIntValue() {
	return _intValue;
}

void spine::EventData::setIntValue(int inValue) {
	_intValue = inValue;
}

float spine::EventData::getFloatValue() {
	return _floatValue;
}

void spine::EventData::setFloatValue(float inValue) {
	_floatValue = inValue;
}

const spine::String &spine::EventData::getStringValue() {
	return _stringValue;
}

void spine::EventData::setStringValue(const spine::String &inValue) {
	this->_stringValue = inValue;
}

const spine::String &spine::EventData::getAudioPath() {
	return _audioPath;
}

void spine::EventData::setAudioPath(const spine::String &inValue) {
	_audioPath = inValue;
}


float spine::EventData::getVolume() {
	return _volume;
}

void spine::EventData::setVolume(float inValue) {
	_volume = inValue;
}

float spine::EventData::getBalance() {
	return _balance;
}

void spine::EventData::setBalance(float inValue) {
	_balance = inValue;
}
