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

#include <spine/IkConstraintData.h>

#include <spine/BoneData.h>

using namespace spine;

IkConstraintData::IkConstraintData(const String &name) :
		_name(name),
		_order(0),
		_target(NULL),
		_bendDirection(1),
		_compress(false),
		_stretch(false),
		_uniform(false),
		_mix(1) {
}

const String &IkConstraintData::getName() {
	return _name;
}

size_t IkConstraintData::getOrder() {
	return _order;
}

void IkConstraintData::setOrder(size_t inValue) {
	_order = inValue;
}

Vector<BoneData *> &IkConstraintData::getBones() {
	return _bones;
}

BoneData *IkConstraintData::getTarget() {
	return _target;
}

void IkConstraintData::setTarget(BoneData *inValue) {
	_target = inValue;
}

int IkConstraintData::getBendDirection() {
	return _bendDirection;
}

void IkConstraintData::setBendDirection(int inValue) {
	_bendDirection = inValue;
}

float IkConstraintData::getMix() {
	return _mix;
}

void IkConstraintData::setMix(float inValue) {
	_mix = inValue;
}

bool IkConstraintData::getStretch() {
	return _stretch;
}

void IkConstraintData::setStretch(bool inValue) {
	_stretch = inValue;
}

bool IkConstraintData::getCompress() {
	return _compress;
}

void IkConstraintData::setCompress(bool inValue) {
	_compress = inValue;
}


bool IkConstraintData::getUniform() {
	return _uniform;
}

void IkConstraintData::setUniform(bool inValue) {
	_uniform = inValue;
}
