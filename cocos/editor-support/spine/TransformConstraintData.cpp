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

#include <spine/TransformConstraintData.h>

#include <spine/BoneData.h>

#include <assert.h>

using namespace spine;
TransformConstraintData::TransformConstraintData(const String &name) :
		_name(name),
		_order(0),
		_target(NULL),
		_rotateMix(0),
		_translateMix(0),
		_scaleMix(0),
		_shearMix(0),
		_offsetRotation(0),
		_offsetX(0),
		_offsetY(0),
		_offsetScaleX(0),
		_offsetScaleY(0),
		_offsetShearY(0),
		_relative(false),
		_local(false) {
	assert(_name.length() > 0);
}

const String &TransformConstraintData::getName() {
	return _name;
}

int TransformConstraintData::getOrder() {
	return _order;
}

Vector<BoneData *> &TransformConstraintData::getBones() {
	return _bones;
}

BoneData *TransformConstraintData::getTarget() {
	return _target;
}

float TransformConstraintData::getRotateMix() {
	return _rotateMix;
}

float TransformConstraintData::getTranslateMix() {
	return _translateMix;
}

float TransformConstraintData::getScaleMix() {
	return _scaleMix;
}

float TransformConstraintData::getShearMix() {
	return _shearMix;
}

float TransformConstraintData::getOffsetRotation() {
	return _offsetRotation;
}

float TransformConstraintData::getOffsetX() {
	return _offsetX;
}

float TransformConstraintData::getOffsetY() {
	return _offsetY;
}

float TransformConstraintData::getOffsetScaleX() {
	return _offsetScaleX;
}

float TransformConstraintData::getOffsetScaleY() {
	return _offsetScaleY;
}

float TransformConstraintData::getOffsetShearY() {
	return _offsetShearY;
}

bool TransformConstraintData::isRelative() {
	return _relative;
}

bool TransformConstraintData::isLocal() {
	return _local;
}
