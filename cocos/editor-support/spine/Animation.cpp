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
#include <limits.h>
#include <spine/extension.h>

spAnimation* spAnimation_create (const char* name, int timelineCount) {
	spAnimation* self = NEW(spAnimation);
	MALLOC_STR(self->name, name);
	self->timelineCount = timelineCount;
	self->timelines = MALLOC(spTimeline*, timelineCount);
	return self;
}

void spAnimation_dispose (spAnimation* self) {
	int i;
	for (i = 0; i < self->timelineCount; ++i)
		spTimeline_dispose(self->timelines[i]);
	FREE(self->timelines);
	FREE(self->name);
	FREE(self);
}

void spAnimation_apply (const spAnimation* self, spSkeleton* skeleton, float lastTime, float time, int loop, spEvent** events,
		int* eventCount) {
	int i, n = self->timelineCount;

	if (loop && self->duration) {
		time = FMOD(time, self->duration);
		lastTime = FMOD(lastTime, self->duration);
	}

	for (i = 0; i < n; ++i)
		spTimeline_apply(self->timelines[i], skeleton, lastTime, time, events, eventCount, 1);
}

void spAnimation_mix (const spAnimation* self, spSkeleton* skeleton, float lastTime, float time, int loop, spEvent** events,
		int* eventCount, float alpha) {
	int i, n = self->timelineCount;

	if (loop && self->duration) {
		time = FMOD(time, self->duration);
		lastTime = FMOD(lastTime, self->duration);
	}

	for (i = 0; i < n; ++i)
		spTimeline_apply(self->timelines[i], skeleton, lastTime, time, events, eventCount, alpha);
}

/**/

typedef struct _spTimelineVtable {
	void (*apply) (const spTimeline* self, spSkeleton* skeleton, float lastTime, float time, spEvent** firedEvents,
			int* eventCount, float alpha);
	void (*dispose) (spTimeline* self);
} _spTimelineVtable;

void _spTimeline_init (spTimeline* self, spTimelineType type, /**/
void (*dispose) (spTimeline* self), /**/
		void (*apply) (const spTimeline* self, spSkeleton* skeleton, float lastTime, float time, spEvent** firedEvents,
				int* eventCount, float alpha)) {
	CONST_CAST(spTimelineType, self->type) = type;
	CONST_CAST(_spTimelineVtable*, self->vtable) = NEW(_spTimelineVtable);
	VTABLE(spTimeline, self)->dispose = dispose;
	VTABLE(spTimeline, self)->apply = apply;
}

void _spTimeline_deinit (spTimeline* self) {
	FREE(self->vtable);
}

void spTimeline_dispose (spTimeline* self) {
	VTABLE(spTimeline, self)->dispose(self);
}

void spTimeline_apply (const spTimeline* self, spSkeleton* skeleton, float lastTime, float time, spEvent** firedEvents,
		int* eventCount, float alpha) {
	VTABLE(spTimeline, self)->apply(self, skeleton, lastTime, time, firedEvents, eventCount, alpha);
}

/**/

static const float CURVE_LINEAR = 0;
static const float CURVE_STEPPED = -1;
static const int CURVE_SEGMENTS = 10;

void _spCurveTimeline_init (spCurveTimeline* self, spTimelineType type, int frameCount, /**/
void (*dispose) (spTimeline* self), /**/
		void (*apply) (const spTimeline* self, spSkeleton* skeleton, float lastTime, float time, spEvent** firedEvents,
				int* eventCount, float alpha)) {
	_spTimeline_init(SUPER(self), type, dispose, apply);
	self->curves = CALLOC(float, (frameCount - 1) * 6);
}

void _spCurveTimeline_deinit (spCurveTimeline* self) {
	_spTimeline_deinit(SUPER(self));
	FREE(self->curves);
}

void spCurveTimeline_setLinear (spCurveTimeline* self, int frameIndex) {
	self->curves[frameIndex * 6] = CURVE_LINEAR;
}

void spCurveTimeline_setStepped (spCurveTimeline* self, int frameIndex) {
	self->curves[frameIndex * 6] = CURVE_STEPPED;
}

void spCurveTimeline_setCurve (spCurveTimeline* self, int frameIndex, float cx1, float cy1, float cx2, float cy2) {
	float subdiv_step = 1.0f / CURVE_SEGMENTS;
	float subdiv_step2 = subdiv_step * subdiv_step;
	float subdiv_step3 = subdiv_step2 * subdiv_step;
	float pre1 = 3 * subdiv_step;
	float pre2 = 3 * subdiv_step2;
	float pre4 = 6 * subdiv_step2;
	float pre5 = 6 * subdiv_step3;
	float tmp1x = -cx1 * 2 + cx2;
	float tmp1y = -cy1 * 2 + cy2;
	float tmp2x = (cx1 - cx2) * 3 + 1;
	float tmp2y = (cy1 - cy2) * 3 + 1;
	int i = frameIndex * 6;
	self->curves[i] = cx1 * pre1 + tmp1x * pre2 + tmp2x * subdiv_step3;
	self->curves[i + 1] = cy1 * pre1 + tmp1y * pre2 + tmp2y * subdiv_step3;
	self->curves[i + 2] = tmp1x * pre4 + tmp2x * pre5;
	self->curves[i + 3] = tmp1y * pre4 + tmp2y * pre5;
	self->curves[i + 4] = tmp2x * pre5;
	self->curves[i + 5] = tmp2y * pre5;
}

float spCurveTimeline_getCurvePercent (const spCurveTimeline* self, int frameIndex, float percent) {
	float dfy;
	float ddfx;
	float ddfy;
	float dddfx;
	float dddfy;
	float x, y;
	int i;
	int curveIndex = frameIndex * 6;
	float dfx = self->curves[curveIndex];
	if (dfx == CURVE_LINEAR) return percent;
	if (dfx == CURVE_STEPPED) return 0;
	dfy = self->curves[curveIndex + 1];
	ddfx = self->curves[curveIndex + 2];
	ddfy = self->curves[curveIndex + 3];
	dddfx = self->curves[curveIndex + 4];
	dddfy = self->curves[curveIndex + 5];
	x = dfx, y = dfy;
	i = CURVE_SEGMENTS - 2;
	while (1) {
		if (x >= percent) {
			float lastX = x - dfx;
			float lastY = y - dfy;
			return lastY + (y - lastY) * (percent - lastX) / (x - lastX);
		}
		if (i == 0) break;
		i--;
		dfx += ddfx;
		dfy += ddfy;
		ddfx += dddfx;
		ddfy += dddfy;
		x += dfx;
		y += dfy;
	}
	return y + (1 - y) * (percent - x) / (1 - x); /* Last point is 1,1. */
}

/* @param target After the first and before the last entry. */
static int binarySearch (float *values, int valuesLength, float target, int step) {
	int low = 0, current;
	int high = valuesLength / step - 2;
	if (high == 0) return step;
	current = high >> 1;
	while (1) {
		if (values[(current + 1) * step] <= target)
			low = current + 1;
		else
			high = current;
		if (low == high) return (low + 1) * step;
		current = (low + high) >> 1;
	}
	return 0;
}

/*static int linearSearch (float *values, int valuesLength, float target, int step) {
 int i, last = valuesLength - step;
 for (i = 0; i <= last; i += step) {
 if (values[i] <= target) continue;
 return i;
 }
 return -1;
 }*/

/**/

void _spBaseTimeline_dispose (spTimeline* timeline) {
	struct spBaseTimeline* self = SUB_CAST(struct spBaseTimeline, timeline);
	_spCurveTimeline_deinit(SUPER(self));
	FREE(self->frames);
	FREE(self);
}

/* Many timelines have structure identical to struct spBaseTimeline and extend spCurveTimeline. **/
struct spBaseTimeline* _spBaseTimeline_create (int frameCount, spTimelineType type, int frameSize, /**/
		void (*apply) (const spTimeline* self, spSkeleton* skeleton, float lastTime, float time, spEvent** firedEvents,
				int* eventCount, float alpha)) {
	struct spBaseTimeline* self = NEW(struct spBaseTimeline);
	_spCurveTimeline_init(SUPER(self), type, frameCount, _spBaseTimeline_dispose, apply);

	CONST_CAST(int, self->framesLength) = frameCount * frameSize;
	CONST_CAST(float*, self->frames) = CALLOC(float, self->framesLength);

	return self;
}

/**/

static const int ROTATE_LAST_FRAME_TIME = -2;
static const int ROTATE_FRAME_VALUE = 1;

void _spRotateTimeline_apply (const spTimeline* timeline, spSkeleton* skeleton, float lastTime, float time, spEvent** firedEvents,
		int* eventCount, float alpha) {
	spBone *bone;
	int frameIndex;
	float lastFrameValue, frameTime, percent, amount;

	spRotateTimeline* self = SUB_CAST(spRotateTimeline, timeline);

	if (time < self->frames[0]) return; /* Time is before first frame. */

	bone = skeleton->bones[self->boneIndex];

	if (time >= self->frames[self->framesLength - 2]) { /* Time is after last frame. */
		float amount = bone->data->rotation + self->frames[self->framesLength - 1] - bone->rotation;
		while (amount > 180)
			amount -= 360;
		while (amount < -180)
			amount += 360;
		bone->rotation += amount * alpha;
		return;
	}

	/* Interpolate between the last frame and the current frame. */
	frameIndex = binarySearch(self->frames, self->framesLength, time, 2);
	lastFrameValue = self->frames[frameIndex - 1];
	frameTime = self->frames[frameIndex];
	percent = 1 - (time - frameTime) / (self->frames[frameIndex + ROTATE_LAST_FRAME_TIME] - frameTime);
	percent = spCurveTimeline_getCurvePercent(SUPER(self), frameIndex / 2 - 1, percent < 0 ? 0 : (percent > 1 ? 1 : percent));

	amount = self->frames[frameIndex + ROTATE_FRAME_VALUE] - lastFrameValue;
	while (amount > 180)
		amount -= 360;
	while (amount < -180)
		amount += 360;
	amount = bone->data->rotation + (lastFrameValue + amount * percent) - bone->rotation;
	while (amount > 180)
		amount -= 360;
	while (amount < -180)
		amount += 360;
	bone->rotation += amount * alpha;
}

spRotateTimeline* spRotateTimeline_create (int frameCount) {
	return _spBaseTimeline_create(frameCount, TIMELINE_ROTATE, 2, _spRotateTimeline_apply);
}

void spRotateTimeline_setFrame (spRotateTimeline* self, int frameIndex, float time, float angle) {
	frameIndex *= 2;
	self->frames[frameIndex] = time;
	self->frames[frameIndex + 1] = angle;
}

/**/

static const int TRANSLATE_LAST_FRAME_TIME = -3;
static const int TRANSLATE_FRAME_X = 1;
static const int TRANSLATE_FRAME_Y = 2;

void _spTranslateTimeline_apply (const spTimeline* timeline, spSkeleton* skeleton, float lastTime, float time,
		spEvent** firedEvents, int* eventCount, float alpha) {
	spBone *bone;
	int frameIndex;
	float lastFrameX, lastFrameY, frameTime, percent;

	spTranslateTimeline* self = SUB_CAST(spTranslateTimeline, timeline);

	if (time < self->frames[0]) return; /* Time is before first frame. */

	bone = skeleton->bones[self->boneIndex];

	if (time >= self->frames[self->framesLength - 3]) { /* Time is after last frame. */
		bone->x += (bone->data->x + self->frames[self->framesLength - 2] - bone->x) * alpha;
		bone->y += (bone->data->y + self->frames[self->framesLength - 1] - bone->y) * alpha;
		return;
	}

	/* Interpolate between the last frame and the current frame. */
	frameIndex = binarySearch(self->frames, self->framesLength, time, 3);
	lastFrameX = self->frames[frameIndex - 2];
	lastFrameY = self->frames[frameIndex - 1];
	frameTime = self->frames[frameIndex];
	percent = 1 - (time - frameTime) / (self->frames[frameIndex + TRANSLATE_LAST_FRAME_TIME] - frameTime);
	percent = spCurveTimeline_getCurvePercent(SUPER(self), frameIndex / 3 - 1, percent < 0 ? 0 : (percent > 1 ? 1 : percent));

	bone->x += (bone->data->x + lastFrameX + (self->frames[frameIndex + TRANSLATE_FRAME_X] - lastFrameX) * percent - bone->x)
			* alpha;
	bone->y += (bone->data->y + lastFrameY + (self->frames[frameIndex + TRANSLATE_FRAME_Y] - lastFrameY) * percent - bone->y)
			* alpha;
}

spTranslateTimeline* spTranslateTimeline_create (int frameCount) {
	return _spBaseTimeline_create(frameCount, TIMELINE_TRANLATE, 3, _spTranslateTimeline_apply);
}

void spTranslateTimeline_setFrame (spTranslateTimeline* self, int frameIndex, float time, float x, float y) {
	frameIndex *= 3;
	self->frames[frameIndex] = time;
	self->frames[frameIndex + 1] = x;
	self->frames[frameIndex + 2] = y;
}

/**/

void _spScaleTimeline_apply (const spTimeline* timeline, spSkeleton* skeleton, float lastTime, float time, spEvent** firedEvents,
		int* eventCount, float alpha) {
	spBone *bone;
	int frameIndex;
	float lastFrameX, lastFrameY, frameTime, percent;

	spScaleTimeline* self = SUB_CAST(spScaleTimeline, timeline);

	if (time < self->frames[0]) return; /* Time is before first frame. */

	bone = skeleton->bones[self->boneIndex];
	if (time >= self->frames[self->framesLength - 3]) { /* Time is after last frame. */
		bone->scaleX += (bone->data->scaleX - 1 + self->frames[self->framesLength - 2] - bone->scaleX) * alpha;
		bone->scaleY += (bone->data->scaleY - 1 + self->frames[self->framesLength - 1] - bone->scaleY) * alpha;
		return;
	}

	/* Interpolate between the last frame and the current frame. */
	frameIndex = binarySearch(self->frames, self->framesLength, time, 3);
	lastFrameX = self->frames[frameIndex - 2];
	lastFrameY = self->frames[frameIndex - 1];
	frameTime = self->frames[frameIndex];
	percent = 1 - (time - frameTime) / (self->frames[frameIndex + TRANSLATE_LAST_FRAME_TIME] - frameTime);
	percent = spCurveTimeline_getCurvePercent(SUPER(self), frameIndex / 3 - 1, percent < 0 ? 0 : (percent > 1 ? 1 : percent));

	bone->scaleX += (bone->data->scaleX - 1 + lastFrameX + (self->frames[frameIndex + TRANSLATE_FRAME_X] - lastFrameX) * percent
			- bone->scaleX) * alpha;
	bone->scaleY += (bone->data->scaleY - 1 + lastFrameY + (self->frames[frameIndex + TRANSLATE_FRAME_Y] - lastFrameY) * percent
			- bone->scaleY) * alpha;
}

spScaleTimeline* spScaleTimeline_create (int frameCount) {
	return _spBaseTimeline_create(frameCount, TIMELINE_SCALE, 3, _spScaleTimeline_apply);
}

void spScaleTimeline_setFrame (spScaleTimeline* self, int frameIndex, float time, float x, float y) {
	spTranslateTimeline_setFrame(self, frameIndex, time, x, y);
}

/**/

static const int COLOR_LAST_FRAME_TIME = -5;
static const int COLOR_FRAME_R = 1;
static const int COLOR_FRAME_G = 2;
static const int COLOR_FRAME_B = 3;
static const int COLOR_FRAME_A = 4;

void _spColorTimeline_apply (const spTimeline* timeline, spSkeleton* skeleton, float lastTime, float time, spEvent** firedEvents,
		int* eventCount, float alpha) {
	spSlot *slot;
	int frameIndex;
	float lastFrameR, lastFrameG, lastFrameB, lastFrameA, percent, frameTime;
	float r, g, b, a;
	spColorTimeline* self = (spColorTimeline*)timeline;

	if (time < self->frames[0]) return; /* Time is before first frame. */

	slot = skeleton->slots[self->slotIndex];

	if (time >= self->frames[self->framesLength - 5]) { /* Time is after last frame. */
		int i = self->framesLength - 1;
		slot->r = self->frames[i - 3];
		slot->g = self->frames[i - 2];
		slot->b = self->frames[i - 1];
		slot->a = self->frames[i];
		return;
	}

	/* Interpolate between the last frame and the current frame. */
	frameIndex = binarySearch(self->frames, self->framesLength, time, 5);
	lastFrameR = self->frames[frameIndex - 4];
	lastFrameG = self->frames[frameIndex - 3];
	lastFrameB = self->frames[frameIndex - 2];
	lastFrameA = self->frames[frameIndex - 1];
	frameTime = self->frames[frameIndex];
	percent = 1 - (time - frameTime) / (self->frames[frameIndex + COLOR_LAST_FRAME_TIME] - frameTime);
	percent = spCurveTimeline_getCurvePercent(SUPER(self), frameIndex / 5 - 1, percent < 0 ? 0 : (percent > 1 ? 1 : percent));

	r = lastFrameR + (self->frames[frameIndex + COLOR_FRAME_R] - lastFrameR) * percent;
	g = lastFrameG + (self->frames[frameIndex + COLOR_FRAME_G] - lastFrameG) * percent;
	b = lastFrameB + (self->frames[frameIndex + COLOR_FRAME_B] - lastFrameB) * percent;
	a = lastFrameA + (self->frames[frameIndex + COLOR_FRAME_A] - lastFrameA) * percent;
	if (alpha < 1) {
		slot->r += (r - slot->r) * alpha;
		slot->g += (g - slot->g) * alpha;
		slot->b += (b - slot->b) * alpha;
		slot->a += (a - slot->a) * alpha;
	} else {
		slot->r = r;
		slot->g = g;
		slot->b = b;
		slot->a = a;
	}
}

spColorTimeline* spColorTimeline_create (int frameCount) {
	return (spColorTimeline*)_spBaseTimeline_create(frameCount, TIMELINE_COLOR, 5, _spColorTimeline_apply);
}

void spColorTimeline_setFrame (spColorTimeline* self, int frameIndex, float time, float r, float g, float b, float a) {
	frameIndex *= 5;
	self->frames[frameIndex] = time;
	self->frames[frameIndex + 1] = r;
	self->frames[frameIndex + 2] = g;
	self->frames[frameIndex + 3] = b;
	self->frames[frameIndex + 4] = a;
}

/**/

void _spAttachmentTimeline_apply (const spTimeline* timeline, spSkeleton* skeleton, float lastTime, float time,
		spEvent** firedEvents, int* eventCount, float alpha) {
	int frameIndex;
	const char* attachmentName;
	spAttachmentTimeline* self = (spAttachmentTimeline*)timeline;

	if (time < self->frames[0]) return; /* Time is before first frame. */

	if (time >= self->frames[self->framesLength - 1]) /* Time is after last frame. */
		frameIndex = self->framesLength - 1;
	else
		frameIndex = binarySearch(self->frames, self->framesLength, time, 1) - 1;

	attachmentName = self->attachmentNames[frameIndex];
	spSlot_setAttachment(skeleton->slots[self->slotIndex],
			attachmentName ? spSkeleton_getAttachmentForSlotIndex(skeleton, self->slotIndex, attachmentName) : 0);
}

void _spAttachmentTimeline_dispose (spTimeline* timeline) {
	spAttachmentTimeline* self = SUB_CAST(spAttachmentTimeline, timeline);
	int i;

	_spTimeline_deinit(timeline);

	for (i = 0; i < self->framesLength; ++i)
		FREE(self->attachmentNames[i]);
	FREE(self->attachmentNames);
	FREE(self->frames);
	FREE(self);
}

spAttachmentTimeline* spAttachmentTimeline_create (int frameCount) {
	spAttachmentTimeline* self = NEW(spAttachmentTimeline);
	_spTimeline_init(SUPER(self), TIMELINE_ATTACHMENT, _spAttachmentTimeline_dispose, _spAttachmentTimeline_apply);

	CONST_CAST(int, self->framesLength) = frameCount;
	CONST_CAST(float*, self->frames) = CALLOC(float, frameCount);
	CONST_CAST(char**, self->attachmentNames) = CALLOC(char*, frameCount);

	return self;
}

void spAttachmentTimeline_setFrame (spAttachmentTimeline* self, int frameIndex, float time, const char* attachmentName) {
	self->frames[frameIndex] = time;

	FREE(self->attachmentNames[frameIndex]);
	if (attachmentName)
		MALLOC_STR(self->attachmentNames[frameIndex], attachmentName);
	else
		self->attachmentNames[frameIndex] = 0;
}

/**/

/** Fires events for frames > lastTime and <= time. */
void _spEventTimeline_apply (const spTimeline* timeline, spSkeleton* skeleton, float lastTime, float time, spEvent** firedEvents,
		int* eventCount, float alpha) {
	spEventTimeline* self = (spEventTimeline*)timeline;
	int frameIndex;
	if (!firedEvents) return;

	if (lastTime > time) { /* Fire events after last time for looped animations. */
		_spEventTimeline_apply(timeline, skeleton, lastTime, (float)INT_MAX, firedEvents, eventCount, alpha);
		lastTime = -1;
	} else if (lastTime >= self->frames[self->framesLength - 1]) /* Last time is after last frame. */
		return;
	if (time < self->frames[0]) return; /* Time is before first frame. */

	if (lastTime < self->frames[0])
		frameIndex = 0;
	else {
		float frame;
		frameIndex = binarySearch(self->frames, self->framesLength, lastTime, 1);
		frame = self->frames[frameIndex];
		while (frameIndex > 0) { /* Fire multiple events with the same frame. */
			if (self->frames[frameIndex - 1] != frame) break;
			frameIndex--;
		}
	}
	for (; frameIndex < self->framesLength && time >= self->frames[frameIndex]; frameIndex++) {
		firedEvents[*eventCount] = self->events[frameIndex];
		(*eventCount)++;
	}
}

void _spEventTimeline_dispose (spTimeline* timeline) {
	spEventTimeline* self = SUB_CAST(spEventTimeline, timeline);
	int i;

	_spTimeline_deinit(timeline);

	for (i = 0; i < self->framesLength; ++i)
		spEvent_dispose(self->events[i]);
	FREE(self->events);
	FREE(self->frames);
	FREE(self);
}

spEventTimeline* spEventTimeline_create (int frameCount) {
	spEventTimeline* self = NEW(spEventTimeline);
	_spTimeline_init(SUPER(self), TIMELINE_EVENT, _spEventTimeline_dispose, _spEventTimeline_apply);

	CONST_CAST(int, self->framesLength) = frameCount;
	CONST_CAST(float*, self->frames) = CALLOC(float, frameCount);
	CONST_CAST(spEvent**, self->events) = CALLOC(spEvent*, frameCount);

	return self;
}

void spEventTimeline_setFrame (spEventTimeline* self, int frameIndex, float time, spEvent* event) {
	self->frames[frameIndex] = time;

	FREE(self->events[frameIndex]);
	self->events[frameIndex] = event;
}

/**/

void _spDrawOrderTimeline_apply (const spTimeline* timeline, spSkeleton* skeleton, float lastTime, float time,
		spEvent** firedEvents, int* eventCount, float alpha) {
	int i;
	int frameIndex;
	const int* drawOrderToSetupIndex;
	spDrawOrderTimeline* self = (spDrawOrderTimeline*)timeline;

	if (time < self->frames[0]) return; /* Time is before first frame. */

	if (time >= self->frames[self->framesLength - 1]) /* Time is after last frame. */
		frameIndex = self->framesLength - 1;
	else
		frameIndex = binarySearch(self->frames, self->framesLength, time, 1) - 1;

	drawOrderToSetupIndex = self->drawOrders[frameIndex];
	if (!drawOrderToSetupIndex)
		memcpy(skeleton->drawOrder, skeleton->slots, self->slotCount * sizeof(int));
	else {
		for (i = 0; i < self->slotCount; i++)
			skeleton->drawOrder[i] = skeleton->slots[drawOrderToSetupIndex[i]];
	}
}

void _spDrawOrderTimeline_dispose (spTimeline* timeline) {
	spDrawOrderTimeline* self = SUB_CAST(spDrawOrderTimeline, timeline);
	int i;

	_spTimeline_deinit(timeline);

	for (i = 0; i < self->framesLength; ++i)
		FREE(self->drawOrders[i]);
	FREE(self->drawOrders);
	FREE(self->frames);
	FREE(self);
}

spDrawOrderTimeline* spDrawOrderTimeline_create (int frameCount, int slotCount) {
	spDrawOrderTimeline* self = NEW(spDrawOrderTimeline);
	_spTimeline_init(SUPER(self), TIMELINE_DRAWORDER, _spDrawOrderTimeline_dispose, _spDrawOrderTimeline_apply);

	CONST_CAST(int, self->framesLength) = frameCount;
	CONST_CAST(float*, self->frames) = CALLOC(float, frameCount);
	CONST_CAST(int**, self->drawOrders) = CALLOC(int*, frameCount);
	CONST_CAST(int, self->slotCount) = slotCount;

	return self;
}

void spDrawOrderTimeline_setFrame (spDrawOrderTimeline* self, int frameIndex, float time, const int* drawOrder) {
	self->frames[frameIndex] = time;

	FREE(self->drawOrders[frameIndex]);
	if (!drawOrder)
		self->drawOrders[frameIndex] = 0;
	else {
		self->drawOrders[frameIndex] = MALLOC(int, self->slotCount);
		memcpy(CONST_CAST(int*, self->drawOrders[frameIndex]), drawOrder, self->slotCount * sizeof(int));
	}
}
