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

#include <spine/BoneData.h>

#include <assert.h>

using namespace spine;

BoneData::BoneData(int index, const String &name, BoneData *parent) :
		_index(index),
		_name(name),
		_parent(parent),
		_length(0),
		_x(0),
		_y(0),
		_rotation(0),
		_scaleX(1),
		_scaleY(1),
		_shearX(0),
		_shearY(0),
		_transformMode(TransformMode_Normal) {
	assert(index >= 0);
	assert(_name.length() > 0);
}

int BoneData::getIndex() {
	return _index;
}

const String &BoneData::getName() {
	return _name;
}

BoneData *BoneData::getParent() {
	return _parent;
}

float BoneData::getLength() {
	return _length;
}

void BoneData::setLength(float inValue) {
	_length = inValue;
}

float BoneData::getX() {
	return _x;
}

void BoneData::setX(float inValue) {
	_x = inValue;
}

float BoneData::getY() {
	return _y;
}

void BoneData::setY(float inValue) {
	_y = inValue;
}

float BoneData::getRotation() {
	return _rotation;
}

void BoneData::setRotation(float inValue) {
	_rotation = inValue;
}

float BoneData::getScaleX() {
	return _scaleX;
}

void BoneData::setScaleX(float inValue) {
	_scaleX = inValue;
}

float BoneData::getScaleY() {
	return _scaleY;
}

void BoneData::setScaleY(float inValue) {
	_scaleY = inValue;
}

float BoneData::getShearX() {
	return _shearX;
}

void BoneData::setShearX(float inValue) {
	_shearX = inValue;
}

float BoneData::getShearY() {
	return _shearY;
}

void BoneData::setShearY(float inValue) {
	_shearY = inValue;
}

TransformMode BoneData::getTransformMode() {
	return _transformMode;
}

void BoneData::setTransformMode(TransformMode inValue) {
	_transformMode = inValue;
}
