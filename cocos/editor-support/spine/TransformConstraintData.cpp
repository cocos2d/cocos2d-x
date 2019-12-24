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

#include <spine/TransformConstraintData.h>

#include <spine/BoneData.h>

#include <assert.h>

using namespace spine;
TransformConstraintData::TransformConstraintData(const String &name) :
		ConstraintData(name),
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
