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

#include <spine/PathConstraintData.h>

#include <spine/BoneData.h>
#include <spine/SlotData.h>

#include <assert.h>

using namespace spine;

PathConstraintData::PathConstraintData(const String &name) :
		ConstraintData(name),
		_target(NULL),
		_positionMode(PositionMode_Fixed),
		_spacingMode(SpacingMode_Length),
		_rotateMode(RotateMode_Tangent),
		_offsetRotation(0),
		_position(0),
		_spacing(0),
		_rotateMix(0),
		_translateMix(0) {
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
