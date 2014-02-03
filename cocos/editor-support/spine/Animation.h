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

#ifndef SPINE_ANIMATION_H_
#define SPINE_ANIMATION_H_

#include <spine/Event.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct spTimeline spTimeline;
struct spSkeleton;

typedef struct {
	const char* const name;
	float duration;

	int timelineCount;
	spTimeline** timelines;
} spAnimation;

spAnimation* spAnimation_create (const char* name, int timelineCount);
void spAnimation_dispose (spAnimation* self);

/** Poses the skeleton at the specified time for this animation.
 * @param lastTime The last time the animation was applied.
 * @param events Any triggered events are added. */
void spAnimation_apply (const spAnimation* self, struct spSkeleton* skeleton, float lastTime, float time, int loop,
		spEvent** events, int* eventCount);

/** Poses the skeleton at the specified time for this animation mixed with the current pose.
 * @param lastTime The last time the animation was applied.
 * @param events Any triggered events are added.
 * @param alpha The amount of this animation that affects the current pose. */
void spAnimation_mix (const spAnimation* self, struct spSkeleton* skeleton, float lastTime, float time, int loop,
		spEvent** events, int* eventCount, float alpha);

#ifdef SPINE_SHORT_NAMES
typedef spAnimation Animation;
#define Animation_create(...) spAnimation_create(__VA_ARGS__)
#define Animation_dispose(...) spAnimation_dispose(__VA_ARGS__)
#define Animation_apply(...) spAnimation_apply(__VA_ARGS__)
#define Animation_mix(...) spAnimation_mix(__VA_ARGS__)
#endif

/**/

typedef enum {
	TIMELINE_SCALE, TIMELINE_ROTATE, TIMELINE_TRANLATE, TIMELINE_COLOR, TIMELINE_ATTACHMENT, TIMELINE_EVENT, TIMELINE_DRAWORDER
} spTimelineType;

struct spTimeline {
	const spTimelineType type;

	const void* const vtable;
};

void spTimeline_dispose (spTimeline* self);
void spTimeline_apply (const spTimeline* self, struct spSkeleton* skeleton, float lastTime, float time, spEvent** firedEvents,
		int* eventCount, float alpha);

#ifdef SPINE_SHORT_NAMES
typedef spTimeline Timeline;
#define Timeline_dispose(...) spTimeline_dispose(__VA_ARGS__)
#define Timeline_apply(...) spTimeline_apply(__VA_ARGS__)
#endif

/**/

typedef struct {
	spTimeline super;
	float* curves; /* dfx, dfy, ddfx, ddfy, dddfx, dddfy, ... */
} spCurveTimeline;

void spCurveTimeline_setLinear (spCurveTimeline* self, int frameIndex);
void spCurveTimeline_setStepped (spCurveTimeline* self, int frameIndex);

/* Sets the control handle positions for an interpolation bezier curve used to transition from this keyframe to the next.
 * cx1 and cx2 are from 0 to 1, representing the percent of time between the two keyframes. cy1 and cy2 are the percent of
 * the difference between the keyframe's values. */
void spCurveTimeline_setCurve (spCurveTimeline* self, int frameIndex, float cx1, float cy1, float cx2, float cy2);
float spCurveTimeline_getCurvePercent (const spCurveTimeline* self, int frameIndex, float percent);

#ifdef SPINE_SHORT_NAMES
typedef spCurveTimeline CurveTimeline;
#define CurveTimeline_setLinear(...) spCurveTimeline_setLinear(__VA_ARGS__)
#define CurveTimeline_setStepped(...) spCurveTimeline_setStepped(__VA_ARGS__)
#define CurveTimeline_setCurve(...) spCurveTimeline_setCurve(__VA_ARGS__)
#define CurveTimeline_getCurvePercent(...) spCurveTimeline_getCurvePercent(__VA_ARGS__)
#endif

/**/

typedef struct spBaseTimeline {
	spCurveTimeline super;
	int const framesLength;
	float* const frames; /* time, angle, ... for rotate. time, x, y, ... for translate and scale. */
	int boneIndex;
} spRotateTimeline;

spRotateTimeline* spRotateTimeline_create (int frameCount);

void spRotateTimeline_setFrame (spRotateTimeline* self, int frameIndex, float time, float angle);

#ifdef SPINE_SHORT_NAMES
typedef spRotateTimeline RotateTimeline;
#define RotateTimeline_create(...) spRotateTimeline_create(__VA_ARGS__)
#define RotateTimeline_setFrame(...) spRotateTimeline_setFrame(__VA_ARGS__)
#endif

/**/

typedef struct spBaseTimeline spTranslateTimeline;

spTranslateTimeline* spTranslateTimeline_create (int frameCount);

void spTranslateTimeline_setFrame (spTranslateTimeline* self, int frameIndex, float time, float x, float y);

#ifdef SPINE_SHORT_NAMES
typedef spTranslateTimeline TranslateTimeline;
#define TranslateTimeline_create(...) spTranslateTimeline_create(__VA_ARGS__)
#define TranslateTimeline_setFrame(...) spTranslateTimeline_setFrame(__VA_ARGS__)
#endif

/**/

typedef struct spBaseTimeline spScaleTimeline;

spScaleTimeline* spScaleTimeline_create (int frameCount);

void spScaleTimeline_setFrame (spScaleTimeline* self, int frameIndex, float time, float x, float y);

#ifdef SPINE_SHORT_NAMES
typedef spScaleTimeline ScaleTimeline;
#define ScaleTimeline_create(...) spScaleTimeline_create(__VA_ARGS__)
#define ScaleTimeline_setFrame(...) spScaleTimeline_setFrame(__VA_ARGS__)
#endif

/**/

typedef struct {
	spCurveTimeline super;
	int const framesLength;
	float* const frames; /* time, r, g, b, a, ... */
	int slotIndex;
} spColorTimeline;

spColorTimeline* spColorTimeline_create (int frameCount);

void spColorTimeline_setFrame (spColorTimeline* self, int frameIndex, float time, float r, float g, float b, float a);

#ifdef SPINE_SHORT_NAMES
typedef spColorTimeline ColorTimeline;
#define ColorTimeline_create(...) spColorTimeline_create(__VA_ARGS__)
#define ColorTimeline_setFrame(...) spColorTimeline_setFrame(__VA_ARGS__)
#endif

/**/

typedef struct {
	spTimeline super;
	int const framesLength;
	float* const frames; /* time, ... */
	int slotIndex;
	const char** const attachmentNames;
} spAttachmentTimeline;

spAttachmentTimeline* spAttachmentTimeline_create (int frameCount);

/* @param attachmentName May be 0. */
void spAttachmentTimeline_setFrame (spAttachmentTimeline* self, int frameIndex, float time, const char* attachmentName);

#ifdef SPINE_SHORT_NAMES
typedef spAttachmentTimeline AttachmentTimeline;
#define AttachmentTimeline_create(...) spAttachmentTimeline_create(__VA_ARGS__)
#define AttachmentTimeline_setFrame(...) spAttachmentTimeline_setFrame(__VA_ARGS__)
#endif

/**/

typedef struct {
	spTimeline super;
	int const framesLength;
	float* const frames; /* time, ... */
	spEvent** const events;
} spEventTimeline;

spEventTimeline* spEventTimeline_create (int frameCount);

void spEventTimeline_setFrame (spEventTimeline* self, int frameIndex, float time, spEvent* event);

#ifdef SPINE_SHORT_NAMES
typedef spEventTimeline EventTimeline;
#define EventTimeline_create(...) spEventTimeline_create(__VA_ARGS__)
#define EventTimeline_setFrame(...) spEventTimeline_setFrame(__VA_ARGS__)
#endif

/**/

typedef struct {
	spTimeline super;
	int const framesLength;
	float* const frames; /* time, ... */
	const int** const drawOrders;
	int const slotCount;
} spDrawOrderTimeline;

spDrawOrderTimeline* spDrawOrderTimeline_create (int frameCount, int slotCount);

void spDrawOrderTimeline_setFrame (spDrawOrderTimeline* self, int frameIndex, float time, const int* drawOrder);

#ifdef SPINE_SHORT_NAMES
typedef spDrawOrderTimeline DrawOrderTimeline;
#define DrawOrderTimeline_create(...) spDrawOrderTimeline_create(__VA_ARGS__)
#define DrawOrderTimeline_setFrame(...) spDrawOrderTimeline_setFrame(__VA_ARGS__)
#endif

#ifdef __cplusplus
}
#endif

#endif /* SPINE_ANIMATION_H_ */
