/******************************************************************************
 * Spine Runtime Software License - Version 1.1
 * 
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms in whole or in part, with
 * or without modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. A Spine Essential, Professional, Enterprise, or Education License must
 *    be purchased from Esoteric Software and the license must remain valid:
 *    http://esotericsoftware.com/
 * 2. Redistributions of source code must retain this license, which is the
 *    above copyright notice, this declaration of conditions and the following
 *    disclaimer.
 * 3. Redistributions in binary form must reproduce this license, which is the
 *    above copyright notice, this declaration of conditions and the following
 *    disclaimer, in the documentation and/or other materials provided with the
 *    distribution.
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
 *****************************************************************************/

#include <spine/Animation.h>
#include <spine/AnimationState.h>
#include <spine/AnimationStateData.h>
#include <spine/Event.h>
#include <spine/extension.h>
#include <spine/Skeleton.h>
#include <spine/SkeletonData.h>
#include <string.h>

spTrackEntry* _spTrackEntry_create () {
	spTrackEntry* entry = NEW(spTrackEntry);
	entry->timeScale = 1;
	entry->lastTime = -1;
	return entry;
}

void _spTrackEntry_dispose (spTrackEntry* entry) {
	FREE(entry);
}

void _spTrackEntry_disposeAll (spTrackEntry* entry) {
	while (entry) {
		spTrackEntry* next = entry->next;
		_spTrackEntry_dispose(entry);
		entry = next;
	}
}

/**/

typedef struct {
	spAnimationState super;
	spEvent** events;
} _spAnimationState;

void _spAnimationState_setCurrent (spAnimationState* self, int index, spTrackEntry* entry);

spAnimationState* spAnimationState_create (spAnimationStateData* data) {
	_spAnimationState* internal = NEW(_spAnimationState);
	spAnimationState* self = SUPER(internal);
	internal->events = MALLOC(spEvent*, 64);
	self->timeScale = 1;
	CONST_CAST(spAnimationStateData*, self->data) = data;
	return self;
}

void spAnimationState_dispose (spAnimationState* self) {
	int i;
	_spAnimationState* internal = SUB_CAST(_spAnimationState, self);
	FREE(internal->events);
	for (i = 0; i < self->trackCount; i++)
		_spTrackEntry_disposeAll(self->tracks[i]);
	FREE(self->tracks);
	FREE(self);
}

void spAnimationState_update (spAnimationState* self, float delta) {
	int i;
	float trackDelta;
	delta *= self->timeScale;
	for (i = 0; i < self->trackCount; i++) {
		spTrackEntry* current = self->tracks[i];
		if (!current) continue;

		trackDelta = delta * current->timeScale;
		current->time += trackDelta;
		if (current->previous) {
			current->previous->time += trackDelta;
			current->mixTime += trackDelta;
		}

		if (current->next) {
			if (current->lastTime >= current->next->delay) _spAnimationState_setCurrent(self, i, current->next);
		} else {
			/* End non-looping animation when it reaches its end time and there is no next entry. */
			if (!current->loop && current->lastTime >= current->endTime) spAnimationState_clearTrack(self, i);
		}
	}
}

void spAnimationState_apply (spAnimationState* self, spSkeleton* skeleton) {
	_spAnimationState* internal = SUB_CAST(_spAnimationState, self);

	int i, ii;
	int eventCount;
	float time;
	spTrackEntry* previous;
	for (i = 0; i < self->trackCount; i++) {
		spTrackEntry* current = self->tracks[i];
		if (!current) continue;

		eventCount = 0;

		time = current->time;
		if (!current->loop && time > current->endTime) time = current->endTime;

		previous = current->previous;
		if (!previous) {
			spAnimation_apply(current->animation, skeleton, current->lastTime, time, current->loop, internal->events, &eventCount);
		} else {
			float alpha = current->mixTime / current->mixDuration;

			float previousTime = previous->time;
			if (!previous->loop && previousTime > previous->endTime) previousTime = previous->endTime;
			spAnimation_apply(previous->animation, skeleton, previousTime, previousTime, previous->loop, 0, 0);

			if (alpha >= 1) {
				alpha = 1;
				_spTrackEntry_dispose(current->previous);
				current->previous = 0;
			}
			spAnimation_mix(current->animation, skeleton, current->lastTime, time, current->loop, internal->events, &eventCount,
					alpha);
		}

		for (ii = 0; ii < eventCount; ii++) {
			spEvent* event = internal->events[ii];
			if (current->listener) current->listener(self, i, ANIMATION_EVENT, event, 0);
			if (self->listener) self->listener(self, i, ANIMATION_EVENT, event, 0);
		}

		/* Check if completed the animation or a loop iteration. */
		if (current->loop ? (FMOD(current->lastTime, current->endTime) > FMOD(time, current->endTime)) //
				: (current->lastTime < current->endTime && time >= current->endTime)) {
			int count = (int)(time / current->endTime);
			if (current->listener) current->listener(self, i, ANIMATION_COMPLETE, 0, count);
			if (self->listener) self->listener(self, i, ANIMATION_COMPLETE, 0, count);
			if (i >= self->trackCount || self->tracks[i] != current) continue;
		}

		if (i >= self->trackCount || self->tracks[i] != current) continue;
		current->lastTime = current->time;
	}
}

void spAnimationState_clearTracks (spAnimationState* self) {
	int i;
	for (i = 0; i < self->trackCount; i++)
		spAnimationState_clearTrack(self, i);
	self->trackCount = 0;
}

void spAnimationState_clearTrack (spAnimationState* self, int trackIndex) {
	spTrackEntry* current;
	if (trackIndex >= self->trackCount) return;
	current = self->tracks[trackIndex];
	if (!current) return;

	if (current->listener) current->listener(self, trackIndex, ANIMATION_END, 0, 0);
	if (self->listener) self->listener(self, trackIndex, ANIMATION_END, 0, 0);

	self->tracks[trackIndex] = 0;
	if (current->previous) _spTrackEntry_dispose(current->previous);
	_spTrackEntry_disposeAll(current);
}

spTrackEntry* _spAnimationState_expandToIndex (spAnimationState* self, int index) {
	spTrackEntry** newTracks;
	if (index < self->trackCount) return self->tracks[index];
	newTracks = CALLOC(spTrackEntry*, index + 1);
	memcpy(newTracks, self->tracks, self->trackCount * sizeof(spTrackEntry*));
	FREE(self->tracks);
	self->tracks = newTracks;
	self->trackCount = index + 1;
	return 0;
}

void _spAnimationState_setCurrent (spAnimationState* self, int index, spTrackEntry* entry) {
	spTrackEntry* current = _spAnimationState_expandToIndex(self, index);
	if (current) {
		if (current->previous) {
			_spTrackEntry_dispose(current->previous);
			current->previous = 0;
		}

		if (current->listener) current->listener(self, index, ANIMATION_END, 0, 0);
		if (self->listener) self->listener(self, index, ANIMATION_END, 0, 0);

		entry->mixDuration = spAnimationStateData_getMix(self->data, current->animation, entry->animation);
		if (entry->mixDuration > 0) {
			entry->mixTime = 0;
			entry->previous = current;
		} else
			_spTrackEntry_dispose(current);
	}

	self->tracks[index] = entry;

	if (entry->listener) current->listener(self, index, ANIMATION_START, 0, 0);
	if (self->listener) self->listener(self, index, ANIMATION_START, 0, 0);
}

spTrackEntry* spAnimationState_setAnimationByName (spAnimationState* self, int trackIndex, const char* animationName,
		int/*bool*/loop) {
	spAnimation* animation = spSkeletonData_findAnimation(self->data->skeletonData, animationName);
	return spAnimationState_setAnimation(self, trackIndex, animation, loop);
}

spTrackEntry* spAnimationState_setAnimation (spAnimationState* self, int trackIndex, spAnimation* animation, int/*bool*/loop) {
	spTrackEntry* entry;
	spTrackEntry* current = _spAnimationState_expandToIndex(self, trackIndex);
	if (current) _spTrackEntry_disposeAll(current->next);

	entry = _spTrackEntry_create();
	entry->animation = animation;
	entry->loop = loop;
	entry->endTime = animation->duration;
	_spAnimationState_setCurrent(self, trackIndex, entry);
	return entry;
}

spTrackEntry* spAnimationState_addAnimationByName (spAnimationState* self, int trackIndex, const char* animationName,
		int/*bool*/loop, float delay) {
	spAnimation* animation = spSkeletonData_findAnimation(self->data->skeletonData, animationName);
	return spAnimationState_addAnimation(self, trackIndex, animation, loop, delay);
}

spTrackEntry* spAnimationState_addAnimation (spAnimationState* self, int trackIndex, spAnimation* animation, int/*bool*/loop,
		float delay) {
	spTrackEntry* last;

	spTrackEntry* entry = _spTrackEntry_create();
	entry->animation = animation;
	entry->loop = loop;
	entry->endTime = animation->duration;

	last = _spAnimationState_expandToIndex(self, trackIndex);
	if (last) {
		while (last->next)
			last = last->next;
		last->next = entry;
	} else
		self->tracks[trackIndex] = entry;

	if (delay <= 0) {
		if (last)
			delay += last->endTime - spAnimationStateData_getMix(self->data, last->animation, animation);
		else
			delay = 0;
	}
	entry->delay = delay;

	return entry;
}

spTrackEntry* spAnimationState_getCurrent (spAnimationState* self, int trackIndex) {
	if (trackIndex >= self->trackCount) return 0;
	return self->tracks[trackIndex];
}
