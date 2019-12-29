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

#include <spine/AnimationStateData.h>
#include <spine/SkeletonData.h>
#include <spine/Animation.h>

using namespace spine;

AnimationStateData::AnimationStateData(SkeletonData *skeletonData) : _skeletonData(skeletonData), _defaultMix(0) {
}

void AnimationStateData::setMix(const String &fromName, const String &toName, float duration) {
	Animation *from = _skeletonData->findAnimation(fromName);
	Animation *to = _skeletonData->findAnimation(toName);

	setMix(from, to, duration);
}

void AnimationStateData::setMix(Animation *from, Animation *to, float duration) {
	assert(from != NULL);
	assert(to != NULL);

	AnimationPair key(from, to);
	_animationToMixTime.put(key, duration);
}

float AnimationStateData::getMix(Animation *from, Animation *to) {
	assert(from != NULL);
	assert(to != NULL);

	AnimationPair key(from, to);

	if (_animationToMixTime.containsKey(key)) return _animationToMixTime[key];
	return _defaultMix;
}

SkeletonData *AnimationStateData::getSkeletonData() {
	return _skeletonData;
}

float AnimationStateData::getDefaultMix() {
	return _defaultMix;
}

void AnimationStateData::setDefaultMix(float inValue) {
	_defaultMix = inValue;
}

AnimationStateData::AnimationPair::AnimationPair(Animation *a1, Animation *a2) : _a1(a1), _a2(a2) {
}

bool AnimationStateData::AnimationPair::operator==(const AnimationPair &other) const {
	return _a1->_name == other._a1->_name && _a2->_name == other._a2->_name;
}
