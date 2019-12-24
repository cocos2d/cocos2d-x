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

#include <spine/SkeletonData.h>

#include <spine/BoneData.h>
#include <spine/SlotData.h>
#include <spine/Skin.h>
#include <spine/EventData.h>
#include <spine/Animation.h>
#include <spine/IkConstraintData.h>
#include <spine/TransformConstraintData.h>
#include <spine/PathConstraintData.h>

#include <spine/ContainerUtil.h>

using namespace spine;

SkeletonData::SkeletonData() :
		_name(),
		_defaultSkin(NULL),
		_x(0),
		_y(0),
		_width(0),
		_height(0),
		_version(),
		_hash(),
		_fps(0),
		_imagesPath() {
}

SkeletonData::~SkeletonData() {
	ContainerUtil::cleanUpVectorOfPointers(_bones);
	ContainerUtil::cleanUpVectorOfPointers(_slots);
	ContainerUtil::cleanUpVectorOfPointers(_skins);

	_defaultSkin = NULL;

	ContainerUtil::cleanUpVectorOfPointers(_events);
	ContainerUtil::cleanUpVectorOfPointers(_animations);
	ContainerUtil::cleanUpVectorOfPointers(_ikConstraints);
	ContainerUtil::cleanUpVectorOfPointers(_transformConstraints);
	ContainerUtil::cleanUpVectorOfPointers(_pathConstraints);
	for (size_t i = 0; i < _strings.size(); i++) {
		SpineExtension::free(_strings[i], __FILE__, __LINE__);
	}
}

BoneData *SkeletonData::findBone(const String &boneName) {
	return ContainerUtil::findWithName(_bones, boneName);
}

int SkeletonData::findBoneIndex(const String &boneName) {
	return ContainerUtil::findIndexWithName(_bones, boneName);
}

SlotData *SkeletonData::findSlot(const String &slotName) {
	return ContainerUtil::findWithName(_slots, slotName);
}

int SkeletonData::findSlotIndex(const String &slotName) {
	return ContainerUtil::findIndexWithName(_slots, slotName);
}

Skin *SkeletonData::findSkin(const String &skinName) {
	return ContainerUtil::findWithName(_skins, skinName);
}

spine::EventData *SkeletonData::findEvent(const String &eventDataName) {
	return ContainerUtil::findWithName(_events, eventDataName);
}

Animation *SkeletonData::findAnimation(const String &animationName) {
	return ContainerUtil::findWithName(_animations, animationName);
}

IkConstraintData *SkeletonData::findIkConstraint(const String &constraintName) {
	return ContainerUtil::findWithName(_ikConstraints, constraintName);
}

TransformConstraintData *SkeletonData::findTransformConstraint(const String &constraintName) {
	return ContainerUtil::findWithName(_transformConstraints, constraintName);
}

PathConstraintData *SkeletonData::findPathConstraint(const String &constraintName) {
	return ContainerUtil::findWithName(_pathConstraints, constraintName);
}

int SkeletonData::findPathConstraintIndex(const String &pathConstraintName) {
	return ContainerUtil::findIndexWithName(_pathConstraints, pathConstraintName);
}

const String &SkeletonData::getName() {
	return _name;
}

void SkeletonData::setName(const String &inValue) {
	_name = inValue;
}

Vector<BoneData *> &SkeletonData::getBones() {
	return _bones;
}

Vector<SlotData *> &SkeletonData::getSlots() {
	return _slots;
}

Vector<Skin *> &SkeletonData::getSkins() {
	return _skins;
}

Skin *SkeletonData::getDefaultSkin() {
	return _defaultSkin;
}

void SkeletonData::setDefaultSkin(Skin *inValue) {
	_defaultSkin = inValue;
}

Vector<spine::EventData *> &SkeletonData::getEvents() {
	return _events;
}

Vector<Animation *> &SkeletonData::getAnimations() {
	return _animations;
}

Vector<IkConstraintData *> &SkeletonData::getIkConstraints() {
	return _ikConstraints;
}

Vector<TransformConstraintData *> &SkeletonData::getTransformConstraints() {
	return _transformConstraints;
}

Vector<PathConstraintData *> &SkeletonData::getPathConstraints() {
	return _pathConstraints;
}

float SkeletonData::getX() {
	return _x;
}

void SkeletonData::setX(float inValue) {
	_x = inValue;
}

float SkeletonData::getY() {
	return _y;
}

void SkeletonData::setY(float inValue) {
	_y = inValue;
}

float SkeletonData::getWidth() {
	return _width;
}

void SkeletonData::setWidth(float inValue) {
	_width = inValue;
}

float SkeletonData::getHeight() {
	return _height;
}

void SkeletonData::setHeight(float inValue) {
	_height = inValue;
}

const String &SkeletonData::getVersion() {
	return _version;
}

void SkeletonData::setVersion(const String &inValue) {
	_version = inValue;
}

const String &SkeletonData::getHash() {
	return _hash;
}

void SkeletonData::setHash(const String &inValue) {
	_hash = inValue;
}

const String &SkeletonData::getImagesPath() {
	return _imagesPath;
}

void SkeletonData::setImagesPath(const String &inValue) {
	_imagesPath = inValue;
}


const String &SkeletonData::getAudioPath() {
	return _audioPath;
}

void SkeletonData::setAudioPath(const String &inValue) {
	_audioPath = inValue;
}

float SkeletonData::getFps() {
	return _fps;
}

void SkeletonData::setFps(float inValue) {
	_fps = inValue;
}
