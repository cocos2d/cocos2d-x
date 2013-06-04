/*******************************************************************************
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#include <spine/CCSkeletonAnimation.h>
#include <spine/extension.h>
#include <spine/spine-cocos2dx.h>

USING_NS_CC;
using std::min;
using std::max;
using std::vector;

namespace cocos2d { namespace extension {

CCSkeletonAnimation* CCSkeletonAnimation::createWithData (SkeletonData* skeletonData) {
	CCSkeletonAnimation* node = new CCSkeletonAnimation(skeletonData);
	node->autorelease();
	return node;
}

CCSkeletonAnimation* CCSkeletonAnimation::createWithFile (const char* skeletonDataFile, Atlas* atlas, float scale) {
	CCSkeletonAnimation* node = new CCSkeletonAnimation(skeletonDataFile, atlas, scale);
	node->autorelease();
	return node;
}

CCSkeletonAnimation* CCSkeletonAnimation::createWithFile (const char* skeletonDataFile, const char* atlasFile, float scale) {
	CCSkeletonAnimation* node = new CCSkeletonAnimation(skeletonDataFile, atlasFile, scale);
	node->autorelease();
	return node;
}

CCSkeletonAnimation::CCSkeletonAnimation (SkeletonData *skeletonData)
		: CCSkeleton(skeletonData) {
	addAnimationState();
}

CCSkeletonAnimation::CCSkeletonAnimation (const char* skeletonDataFile, Atlas* atlas, float scale)
		: CCSkeleton(skeletonDataFile, atlas, scale) {
	addAnimationState();
}

CCSkeletonAnimation::CCSkeletonAnimation (const char* skeletonDataFile, const char* atlasFile, float scale)
		: CCSkeleton(skeletonDataFile, atlasFile, scale) {
	addAnimationState();
}

CCSkeletonAnimation::~CCSkeletonAnimation () {
	for (std::vector<AnimationStateData*>::iterator iter = stateDatas.begin(); iter != stateDatas.end(); ++iter)
		AnimationStateData_dispose(*iter);

	for (std::vector<AnimationState*>::iterator iter = states.begin(); iter != states.end(); ++iter)
		AnimationState_dispose(*iter);
}

void CCSkeletonAnimation::update (float deltaTime) {
	super::update(deltaTime);

	deltaTime *= timeScale;
	for (std::vector<AnimationState*>::iterator iter = states.begin(); iter != states.end(); ++iter) {
		AnimationState_update(*iter, deltaTime);
		AnimationState_apply(*iter, skeleton);
	}
	Skeleton_updateWorldTransform(skeleton);
}

void CCSkeletonAnimation::addAnimationState (AnimationStateData* stateData) {
	if (!stateData) {
		stateData = AnimationStateData_create(skeleton->data);
		stateDatas.push_back(stateData);
	}
	AnimationState* state = AnimationState_create(stateData);
	states.push_back(state);
}

void CCSkeletonAnimation::setAnimationStateData (AnimationStateData* stateData, int stateIndex) {
	CCAssert(stateIndex >= 0 && stateIndex < (int)states.size(), "stateIndex out of range.");
	CCAssert(stateData, "stateData cannot be null.");

	AnimationState* state = states[stateIndex];
	for (std::vector<AnimationStateData*>::iterator iter = stateDatas.begin(); iter != stateDatas.end(); ++iter) {
		if (state->data == *iter) {
			AnimationStateData_dispose(state->data);
			stateDatas.erase(iter);
			break;
		}
	}
	for (std::vector<AnimationState*>::iterator iter = states.begin(); iter != states.end(); ++iter) {
		if (state == *iter) {
			states.erase(iter);
			break;
		}
	}
	AnimationState_dispose(state);

	state = AnimationState_create(stateData);
	states[stateIndex] = state;
}

void CCSkeletonAnimation::setMix (const char* fromAnimation, const char* toAnimation, float duration, int stateIndex) {
	CCAssert(stateIndex >= 0 && stateIndex < (int)states.size(), "stateIndex out of range.");
	AnimationStateData_setMixByName(states[stateIndex]->data, fromAnimation, toAnimation, duration);
}

void CCSkeletonAnimation::setAnimation (const char* name, bool loop, int stateIndex) {
	CCAssert(stateIndex >= 0 && stateIndex < (int)states.size(), "stateIndex out of range.");
	AnimationState_setAnimationByName(states[stateIndex], name, loop);
}

void CCSkeletonAnimation::addAnimation (const char* name, bool loop, float delay, int stateIndex) {
	CCAssert(stateIndex >= 0 && stateIndex < (int)states.size(), "stateIndex out of range.");
	AnimationState_addAnimationByName(states[stateIndex], name, loop, delay);
}

void CCSkeletonAnimation::clearAnimation (int stateIndex) {
	CCAssert(stateIndex >= 0 && stateIndex < (int)states.size(), "stateIndex out of range.");
	AnimationState_clearAnimation(states[stateIndex]);
}

}} // namespace cocos2d { namespace extension {