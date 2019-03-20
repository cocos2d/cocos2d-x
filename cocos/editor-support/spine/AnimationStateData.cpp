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
