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

#include <spine/IkConstraintData.h>

#include <spine/BoneData.h>

using namespace spine;

IkConstraintData::IkConstraintData(const String &name) :
		ConstraintData(name),
		_target(NULL),
		_bendDirection(1),
		_compress(false),
		_stretch(false),
		_uniform(false),
		_mix(1),
		_softness(0) {
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

float IkConstraintData::getSoftness() {
	return _softness;
}

void IkConstraintData::setSoftness(float inValue) {
	_softness = inValue;
}

