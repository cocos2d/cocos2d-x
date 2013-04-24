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

#ifndef SPINE_ANIMATION_H_
#define SPINE_ANIMATION_H_

namespace cocos2d { namespace extension {

typedef struct Timeline Timeline;
struct Skeleton;

typedef struct {
	const char* const name;
	float duration;

	int timelineCount;
	Timeline** timelines;
} Animation;

Animation* Animation_create (const char* name, int timelineCount);
void Animation_dispose (Animation* self);

void Animation_apply (const Animation* self, struct Skeleton* skeleton, float time, int/*bool*/loop);
void Animation_mix (const Animation* self, struct Skeleton* skeleton, float time, int/*bool*/loop, float alpha);

/**/

struct Timeline {
	const void* const vtable;
};

void Timeline_dispose (Timeline* self);
void Timeline_apply (const Timeline* self, struct Skeleton* skeleton, float time, float alpha);

/**/

typedef struct {
	Timeline super;
	float* curves; /* dfx, dfy, ddfx, ddfy, dddfx, dddfy, ... */
} CurveTimeline;

void CurveTimeline_setLinear (CurveTimeline* self, int frameIndex);
void CurveTimeline_setStepped (CurveTimeline* self, int frameIndex);

/* Sets the control handle positions for an interpolation bezier curve used to transition from this keyframe to the next.
 * cx1 and cx2 are from 0 to 1, representing the percent of time between the two keyframes. cy1 and cy2 are the percent of
 * the difference between the keyframe's values. */
void CurveTimeline_setCurve (CurveTimeline* self, int frameIndex, float cx1, float cy1, float cx2, float cy2);
float CurveTimeline_getCurvePercent (const CurveTimeline* self, int frameIndex, float percent);

/**/

typedef struct BaseTimeline {
	CurveTimeline super;
	int const framesLength;
	float* const frames; /* time, angle, ... for rotate. time, x, y, ... for translate and scale. */
	int boneIndex;
} RotateTimeline;

RotateTimeline* RotateTimeline_create (int frameCount);

void RotateTimeline_setFrame (RotateTimeline* self, int frameIndex, float time, float angle);

/**/

typedef struct BaseTimeline TranslateTimeline;

TranslateTimeline* TranslateTimeline_create (int frameCount);

void TranslateTimeline_setFrame (TranslateTimeline* self, int frameIndex, float time, float x, float y);

/**/

typedef struct BaseTimeline ScaleTimeline;

ScaleTimeline* ScaleTimeline_create (int frameCount);

void ScaleTimeline_setFrame (ScaleTimeline* self, int frameIndex, float time, float x, float y);

/**/

typedef struct {
	CurveTimeline super;
	int const framesLength;
	float* const frames; /* time, r, g, b, a, ... */
	int slotIndex;
} ColorTimeline;

ColorTimeline* ColorTimeline_create (int frameCount);

void ColorTimeline_setFrame (ColorTimeline* self, int frameIndex, float time, float r, float g, float b, float a);

/**/

typedef struct {
	Timeline super;
	int const framesLength;
	float* const frames; /* time, ... */
	int slotIndex;
	const char** const attachmentNames;
} AttachmentTimeline;

AttachmentTimeline* AttachmentTimeline_create (int frameCount);

/* @param attachmentName May be 0. */
void AttachmentTimeline_setFrame (AttachmentTimeline* self, int frameIndex, float time, const char* attachmentName);

}} // namespace cocos2d { namespace extension {

#endif /* SPINE_ANIMATION_H_ */
