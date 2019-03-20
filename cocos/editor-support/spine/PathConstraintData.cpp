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

#include <spine/PathConstraintData.h>

#include <spine/BoneData.h>
#include <spine/SlotData.h>

#include <assert.h>

using namespace spine;

PathConstraintData::PathConstraintData(const String &name) :
		_name(name),
		_order(0),
		_target(NULL),
		_positionMode(PositionMode_Fixed),
		_spacingMode(SpacingMode_Length),
		_rotateMode(RotateMode_Tangent),
		_offsetRotation(0),
		_position(0),
		_spacing(0),
		_rotateMix(0),
		_translateMix(0) {
	assert(_name.length() > 0);
}

const String &PathConstraintData::getName() {
	return _name;
}

int PathConstraintData::getOrder() {
	return _order;
}

void PathConstraintData::setOrder(int inValue) {
	_order = inValue;
}

Vector<BoneData *> &PathConstraintData::getBones() {
	return _bones;
}

SlotData *PathConstraintData::getTarget() {
	return _target;
}

void PathConstraintData::setTarget(SlotData *inValue) {
	_target = inValue;
}

PositionMode PathConstraintData::getPositionMode() {
	return _positionMode;
}

void PathConstraintData::setPositionMode(PositionMode inValue) {
	_positionMode = inValue;
}

SpacingMode PathConstraintData::getSpacingMode() {
	return _spacingMode;
}

void PathConstraintData::setSpacingMode(SpacingMode inValue) {
	_spacingMode = inValue;
}

RotateMode PathConstraintData::getRotateMode() {
	return _rotateMode;
}

void PathConstraintData::setRotateMode(RotateMode inValue) {
	_rotateMode = inValue;
}

float PathConstraintData::getOffsetRotation() {
	return _offsetRotation;
}

void PathConstraintData::setOffsetRotation(float inValue) {
	_offsetRotation = inValue;
}

float PathConstraintData::getPosition() {
	return _position;
}

void PathConstraintData::setPosition(float inValue) {
	_position = inValue;
}

float PathConstraintData::getSpacing() {
	return _spacing;
}

void PathConstraintData::setSpacing(float inValue) {
	_spacing = inValue;
}

float PathConstraintData::getRotateMix() {
	return _rotateMix;
}

void PathConstraintData::setRotateMix(float inValue) {
	_rotateMix = inValue;
}

float PathConstraintData::getTranslateMix() {
	return _translateMix;
}

void PathConstraintData::setTranslateMix(float inValue) {
	_translateMix = inValue;
}
