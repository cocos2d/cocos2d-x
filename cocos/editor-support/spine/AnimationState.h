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

#ifndef SPINE_ANIMATIONSTATE_H_
#define SPINE_ANIMATIONSTATE_H_

#include <spine/Animation.h>
#include <spine/AnimationStateData.h>
#include <spine/Event.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	SP_ANIMATION_START, SP_ANIMATION_INTERRUPT, SP_ANIMATION_END, SP_ANIMATION_COMPLETE, SP_ANIMATION_DISPOSE, SP_ANIMATION_EVENT
} spEventType;

typedef struct spAnimationState spAnimationState;
typedef struct spTrackEntry spTrackEntry;

typedef void (*spAnimationStateListener) (spAnimationState* state, spEventType type, spTrackEntry* entry, spEvent* event);

struct spTrackEntry {
	spAnimation* animation;
	spTrackEntry* next;
	spTrackEntry* mixingFrom;
	spAnimationStateListener listener;
	int trackIndex;
	int /*boolean*/ loop;
	float eventThreshold, attachmentThreshold, drawOrderThreshold;
	float animationStart, animationEnd, animationLast, nextAnimationLast;
	float delay, trackTime, trackLast, nextTrackLast, trackEnd, timeScale;
	float alpha, mixTime, mixDuration, mixAlpha;
	int* /*boolean*/ timelinesFirst;
	int timelinesFirstCount;
	float* timelinesRotation;
	int timelinesRotationCount;
	void* rendererObject;

#ifdef __cplusplus
	spTrackEntry() :
		animation(0),
		next(0), mixingFrom(0),
		listener(0),
		trackIndex(0),
		loop(0),
		eventThreshold(0), attachmentThreshold(0), drawOrderThreshold(0),
		animationStart(0), animationEnd(0), animationLast(0), nextAnimationLast(0),
		delay(0), trackTime(0), trackLast(0), nextTrackLast(0), trackEnd(0), timeScale(0),
		alpha(0), mixTime(0), mixDuration(0), mixAlpha(0),
		timelinesFirst(0),
		timelinesFirstCount(0),
		timelinesRotation(0),
		timelinesRotationCount(0) {
	}
#endif
};

struct spAnimationState {
	spAnimationStateData* const data;

	int tracksCount;
	spTrackEntry** tracks;

	spAnimationStateListener listener;

	float timeScale;

	void* rendererObject;

#ifdef __cplusplus
	spAnimationState() :
		data(0),
		tracksCount(0),
		tracks(0),
		listener(0),
		timeScale(0) {
	}
#endif
};

/* @param data May be 0 for no mixing. */
spAnimationState* spAnimationState_create (spAnimationStateData* data);
void spAnimationState_dispose (spAnimationState* self);

void spAnimationState_update (spAnimationState* self, float delta);
void spAnimationState_apply (spAnimationState* self, struct spSkeleton* skeleton);

void spAnimationState_clearTracks (spAnimationState* self);
void spAnimationState_clearTrack (spAnimationState* self, int trackIndex);

/** Set the current animation. Any queued animations are cleared. */
spTrackEntry* spAnimationState_setAnimationByName (spAnimationState* self, int trackIndex, const char* animationName,
		int/*bool*/loop);
spTrackEntry* spAnimationState_setAnimation (spAnimationState* self, int trackIndex, spAnimation* animation, int/*bool*/loop);

/** Adds an animation to be played delay seconds after the current or last queued animation, taking into account any mix
 * duration. */
spTrackEntry* spAnimationState_addAnimationByName (spAnimationState* self, int trackIndex, const char* animationName,
		int/*bool*/loop, float delay);
spTrackEntry* spAnimationState_addAnimation (spAnimationState* self, int trackIndex, spAnimation* animation, int/*bool*/loop,
		float delay);
spTrackEntry* spAnimationState_setEmptyAnimation(spAnimationState* self, int trackIndex, float mixDuration);
spTrackEntry* spAnimationState_addEmptyAnimation(spAnimationState* self, int trackIndex, float mixDuration, float delay);
void spAnimationState_setEmptyAnimations(spAnimationState* self, float mixDuration);

spTrackEntry* spAnimationState_getCurrent (spAnimationState* self, int trackIndex);

void spAnimationState_clearListenerNotifications(spAnimationState* self);

float spTrackEntry_getAnimationTime (spTrackEntry* entry);

/** Use this to dispose static memory before your app exits to appease your memory leak detector*/
void spAnimationState_disposeStatics ();

#ifdef SPINE_SHORT_NAMES
typedef spEventType EventType;
#define ANIMATION_START SP_ANIMATION_START
#define ANIMATION_INTERRUPT SP_ANIMATION_INTERRUPT
#define ANIMATION_END SP_ANIMATION_END
#define ANIMATION_COMPLETE SP_ANIMATION_COMPLETE
#define ANIMATION_DISPOSE SP_ANIMATION_DISPOSE
#define ANIMATION_EVENT SP_ANIMATION_EVENT
typedef spAnimationStateListener AnimationStateListener;
typedef spTrackEntry TrackEntry;
typedef spAnimationState AnimationState;
#define AnimationState_create(...) spAnimationState_create(__VA_ARGS__)
#define AnimationState_dispose(...) spAnimationState_dispose(__VA_ARGS__)
#define AnimationState_update(...) spAnimationState_update(__VA_ARGS__)
#define AnimationState_apply(...) spAnimationState_apply(__VA_ARGS__)
#define AnimationState_clearTracks(...) spAnimationState_clearTracks(__VA_ARGS__)
#define AnimationState_clearTrack(...) spAnimationState_clearTrack(__VA_ARGS__)
#define AnimationState_setAnimationByName(...) spAnimationState_setAnimationByName(__VA_ARGS__)
#define AnimationState_setAnimation(...) spAnimationState_setAnimation(__VA_ARGS__)
#define AnimationState_addAnimationByName(...) spAnimationState_addAnimationByName(__VA_ARGS__)
#define AnimationState_addAnimation(...) spAnimationState_addAnimation(__VA_ARGS__)
#define AnimationState_setEmptyAnimation(...) spAnimatinState_setEmptyAnimation(__VA_ARGS__)
#define AnimationState_addEmptyAnimation(...) spAnimatinState_addEmptyAnimation(__VA_ARGS__)
#define AnimationState_setEmptyAnimations(...) spAnimatinState_setEmptyAnimations(__VA_ARGS__)
#define AnimationState_getCurrent(...) spAnimationState_getCurrent(__VA_ARGS__)
#define AnimationState_clearListenerNotifications(...) spAnimatinState_clearListenerNotifications(__VA_ARGS__)
#endif

#ifdef __cplusplus
}
#endif

#endif /* SPINE_ANIMATIONSTATE_H_ */
