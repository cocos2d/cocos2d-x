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

#include <spine/AnimationState.h>
#include <spine/extension.h>

namespace cocos2d { namespace extension {

typedef struct {
	AnimationState super;
	Animation *previous;
	float previousTime;
	int/*bool*/previousLoop;
	float mixTime;
	float mixDuration;
} _Internal;

AnimationState* AnimationState_create (AnimationStateData* data) {
	AnimationState* self = SUPER(NEW(_Internal));
	CONST_CAST(AnimationStateData*, self->data) = data;
	return self;
}

void AnimationState_dispose (AnimationState* self) {
	FREE(self);
}

void AnimationState_update (AnimationState* self, float delta) {
	self->time += delta;
	SUB_CAST(_Internal, self) ->previousTime += delta;
	SUB_CAST(_Internal, self) ->mixTime += delta;
}

void AnimationState_apply (AnimationState* self, Skeleton* skeleton) {
	if (!self->animation) return;
	_Internal* internal = SUB_CAST(_Internal, self);
	if (internal->previous) {
		Animation_apply(internal->previous, skeleton, internal->previousTime, internal->previousLoop);
		float alpha = internal->mixTime / internal->mixDuration;
		if (alpha >= 1) {
			alpha = 1;
			internal->previous = 0;
		}
		Animation_mix(self->animation, skeleton, self->time, self->loop, alpha);
	} else
		Animation_apply(self->animation, skeleton, self->time, self->loop);
}

void AnimationState_setAnimationByName (AnimationState* self, const char* animationName, int/**/loop) {
	Animation* animation = SkeletonData_findAnimation(self->data->skeletonData, animationName);
	AnimationState_setAnimation(self, animation, loop);
}

void AnimationState_setAnimation (AnimationState* self, Animation* newAnimation, int/**/loop) {
	_Internal* internal = SUB_CAST(_Internal, self);
	internal->previous = 0;
	if (newAnimation && self->animation && self->data) {
		internal->mixDuration = AnimationStateData_getMix(self->data, self->animation, newAnimation);
		if (internal->mixDuration > 0) {
			internal->mixTime = 0;
			internal->previous = self->animation;
			internal->previousTime = self->time;
			internal->previousLoop = self->loop;
		}
	}
	CONST_CAST(Animation*, self->animation) = newAnimation;
	self->loop = loop;
	self->time = 0;
}

void AnimationState_clearAnimation (AnimationState* self) {
	SUB_CAST(_Internal, self) ->previous = 0;
	CONST_CAST(Animation*, self->animation) = 0;
}

int/*bool*/AnimationState_isComplete (AnimationState* self) {
	return !self->animation || self->time >= self->animation->duration;
}

}} // namespace cocos2d { namespace extension {
