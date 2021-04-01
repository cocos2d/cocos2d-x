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
		_transformMode(TransformMode_Normal),
		_skinRequired(false) {
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

bool BoneData::isSkinRequired() {
	return _skinRequired;
}

void BoneData::setSkinRequired(bool inValue) {
	_skinRequired = inValue;
}
