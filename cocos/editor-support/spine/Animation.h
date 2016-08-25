/******************************************************************************
 * Spine Runtimes Software License
 * Version 2.3
 * 
 * Copyright (c) 2013-2015, Esoteric Software
 * All rights reserved.
 * 
 * You are granted a perpetual, non-exclusive, non-sublicensable and
 * non-transferable license to use, install, execute and perform the Spine
 * Runtimes Software (the "Software") and derivative works solely for personal
 * or internal use. Without the written permission of Esoteric Software (see
 * Section 2 of the Spine Software License Agreement), you may not (a) modify,
 * translate, adapt or otherwise create derivative works, improvements of the
 * Software or develop new applications using the Software or (b) remove,
 * delete, alter or obscure any trademarks or any copyright, trademark, patent
 * or other intellectual property or proprietary rights notices on or in the
 * Software, including any copy thereof. Redistributions in binary or source
 * form must include this license and terms.
 * 
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef SPINE_ANIMATION_H_
#define SPINE_ANIMATION_H_

#include <spine/Event.h>
#include <spine/Attachment.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct spTimeline spTimeline;
struct spSkeleton;

typedef struct spAnimation {
	const char* const name;
	float duration;

	int timelinesCount;
	spTimeline** timelines;

#ifdef __cplusplus
	spAnimation() :
		name(0),
		duration(0),
		timelinesCount(0),
		timelines(0) {
	}
#endif
} spAnimation;

spAnimation* spAnimation_create (const char* name, int timelinesCount);
void spAnimation_dispose (spAnimation* self);

/** Poses the skeleton at the specified time for this animation.
 * @param lastTime The last time the animation was applied.
 * @param events Any triggered events are added. May be null.*/
void spAnimation_apply (const spAnimation* self, struct spSkeleton* skeleton, float lastTime, float time, int loop,
		spEvent** events, int* eventsCount);

/** Poses the skeleton at the specified time for this animation mixed with the current pose.
 * @param lastTime The last time the animation was applied.
 * @param events Any triggered events are added. May be null.
 * @param alpha The amount of this animation that affects the current pose. */
void spAnimation_mix (const spAnimation* self, struct spSkeleton* skeleton, float lastTime, float time, int loop,
		spEvent** events, int* eventsCount, float alpha);

#ifdef SPINE_SHORT_NAMES
typedef spAnimation Animation;
#define Animation_create(...) spAnimation_create(__VA_ARGS__)
#define Animation_dispose(...) spAnimation_dispose(__VA_ARGS__)
#define Animation_apply(...) spAnimation_apply(__VA_ARGS__)
#define Animation_mix(...) spAnimation_mix(__VA_ARGS__)
#endif

/**/

typedef enum {
	SP_TIMELINE_SCALE,
	SP_TIMELINE_ROTATE,
	SP_TIMELINE_TRANSLATE,
	SP_TIMELINE_SHEAR,
	SP_TIMELINE_COLOR,
	SP_TIMELINE_ATTACHMENT,
	SP_TIMELINE_EVENT,
	SP_TIMELINE_DRAWORDER,
	SP_TIMELINE_DEFORM,
	SP_TIMELINE_IKCONSTRAINT,
	SP_TIMELINE_TRANSFORMCONSTRAINT,
	SP_TIMELINE_PATHCONSTRAINTPOSITION,
	SP_TIMELINE_PATHCONSTRAINTSPACING,
	SP_TIMELINE_PATHCONSTRAINTMIX
} spTimelineType;

struct spTimeline {
	const spTimelineType type;
	const void* const vtable;

#ifdef __cplusplus
	spTimeline() :
		type(SP_TIMELINE_SCALE),
		vtable(0) {
	}
#endif
};

void spTimeline_dispose (spTimeline* self);
void spTimeline_apply (const spTimeline* self, struct spSkeleton* skeleton, float lastTime, float time, spEvent** firedEvents,
		int* eventsCount, float alpha);

#ifdef SPINE_SHORT_NAMES
typedef spTimeline Timeline;
#define TIMELINE_SCALE SP_TIMELINE_SCALE
#define TIMELINE_ROTATE SP_TIMELINE_ROTATE
#define TIMELINE_TRANSLATE SP_TIMELINE_TRANSLATE
#define TIMELINE_COLOR SP_TIMELINE_COLOR
#define TIMELINE_ATTACHMENT SP_TIMELINE_ATTACHMENT
#define TIMELINE_EVENT SP_TIMELINE_EVENT
#define TIMELINE_DRAWORDER SP_TIMELINE_DRAWORDER
#define Timeline_dispose(...) spTimeline_dispose(__VA_ARGS__)
#define Timeline_apply(...) spTimeline_apply(__VA_ARGS__)
#endif

/**/

typedef struct spCurveTimeline {
	spTimeline super;
	float* curves; /* type, x, y, ... */

#ifdef __cplusplus
	spCurveTimeline() :
		super(),
		curves(0) {
	}
#endif
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
	int const framesCount;
	float* const frames; /* time, angle, ... for rotate. time, x, y, ... for translate and scale. */
	int boneIndex;

#ifdef __cplusplus
	spBaseTimeline() :
		super(),
		framesCount(0),
		frames(0),
		boneIndex(0) {
	}
#endif
} spBaseTimeline;

/**/

static const int ROTATE_ENTRIES = 2;

typedef struct spBaseTimeline spRotateTimeline;

spRotateTimeline* spRotateTimeline_create (int framesCount);

void spRotateTimeline_setFrame (spRotateTimeline* self, int frameIndex, float time, float angle);

#ifdef SPINE_SHORT_NAMES
typedef spRotateTimeline RotateTimeline;
#define RotateTimeline_create(...) spRotateTimeline_create(__VA_ARGS__)
#define RotateTimeline_setFrame(...) spRotateTimeline_setFrame(__VA_ARGS__)
#endif

/**/

static const int TRANSLATE_ENTRIES = 3;

typedef struct spBaseTimeline spTranslateTimeline;

spTranslateTimeline* spTranslateTimeline_create (int framesCount);

void spTranslateTimeline_setFrame (spTranslateTimeline* self, int frameIndex, float time, float x, float y);

#ifdef SPINE_SHORT_NAMES
typedef spTranslateTimeline TranslateTimeline;
#define TranslateTimeline_create(...) spTranslateTimeline_create(__VA_ARGS__)
#define TranslateTimeline_setFrame(...) spTranslateTimeline_setFrame(__VA_ARGS__)
#endif

/**/

typedef struct spBaseTimeline spScaleTimeline;

spScaleTimeline* spScaleTimeline_create (int framesCount);

void spScaleTimeline_setFrame (spScaleTimeline* self, int frameIndex, float time, float x, float y);

#ifdef SPINE_SHORT_NAMES
typedef spScaleTimeline ScaleTimeline;
#define ScaleTimeline_create(...) spScaleTimeline_create(__VA_ARGS__)
#define ScaleTimeline_setFrame(...) spScaleTimeline_setFrame(__VA_ARGS__)
#endif

/**/

typedef struct spBaseTimeline spShearTimeline;

spShearTimeline* spShearTimeline_create (int framesCount);

void spShearTimeline_setFrame (spShearTimeline* self, int frameIndex, float time, float x, float y);

#ifdef SPINE_SHORT_NAMES
typedef spShearTimeline ShearTimeline;
#define ShearTimeline_create(...) spShearTimeline_create(__VA_ARGS__)
#define ShearTimeline_setFrame(...) spShearTimeline_setFrame(__VA_ARGS__)
#endif

/**/

static const int COLOR_ENTRIES = 5;

typedef struct spColorTimeline {
	spCurveTimeline super;
	int const framesCount;
	float* const frames; /* time, r, g, b, a, ... */
	int slotIndex;

#ifdef __cplusplus
	spColorTimeline() :
		super(),
		framesCount(0),
		frames(0),
		slotIndex(0) {
	}
#endif
} spColorTimeline;

spColorTimeline* spColorTimeline_create (int framesCount);

void spColorTimeline_setFrame (spColorTimeline* self, int frameIndex, float time, float r, float g, float b, float a);

#ifdef SPINE_SHORT_NAMES
typedef spColorTimeline ColorTimeline;
#define ColorTimeline_create(...) spColorTimeline_create(__VA_ARGS__)
#define ColorTimeline_setFrame(...) spColorTimeline_setFrame(__VA_ARGS__)
#endif

/**/

typedef struct spAttachmentTimeline {
	spTimeline super;
	int const framesCount;
	float* const frames; /* time, ... */
	int slotIndex;
	const char** const attachmentNames;

#ifdef __cplusplus
	spAttachmentTimeline() :
		super(),
		framesCount(0),
		frames(0),
		slotIndex(0),
		attachmentNames(0) {
	}
#endif
} spAttachmentTimeline;

spAttachmentTimeline* spAttachmentTimeline_create (int framesCount);

/* @param attachmentName May be 0. */
void spAttachmentTimeline_setFrame (spAttachmentTimeline* self, int frameIndex, float time, const char* attachmentName);

#ifdef SPINE_SHORT_NAMES
typedef spAttachmentTimeline AttachmentTimeline;
#define AttachmentTimeline_create(...) spAttachmentTimeline_create(__VA_ARGS__)
#define AttachmentTimeline_setFrame(...) spAttachmentTimeline_setFrame(__VA_ARGS__)
#endif

/**/

typedef struct spEventTimeline {
	spTimeline super;
	int const framesCount;
	float* const frames; /* time, ... */
	spEvent** const events;

#ifdef __cplusplus
	spEventTimeline() :
		super(),
		framesCount(0),
		frames(0),
		events(0) {
	}
#endif
} spEventTimeline;

spEventTimeline* spEventTimeline_create (int framesCount);

void spEventTimeline_setFrame (spEventTimeline* self, int frameIndex, spEvent* event);

#ifdef SPINE_SHORT_NAMES
typedef spEventTimeline EventTimeline;
#define EventTimeline_create(...) spEventTimeline_create(__VA_ARGS__)
#define EventTimeline_setFrame(...) spEventTimeline_setFrame(__VA_ARGS__)
#endif

/**/

typedef struct spDrawOrderTimeline {
	spTimeline super;
	int const framesCount;
	float* const frames; /* time, ... */
	const int** const drawOrders;
	int const slotsCount;

#ifdef __cplusplus
	spDrawOrderTimeline() :
		super(),
		framesCount(0),
		frames(0),
		drawOrders(0),
		slotsCount(0) {
	}
#endif
} spDrawOrderTimeline;

spDrawOrderTimeline* spDrawOrderTimeline_create (int framesCount, int slotsCount);

void spDrawOrderTimeline_setFrame (spDrawOrderTimeline* self, int frameIndex, float time, const int* drawOrder);

#ifdef SPINE_SHORT_NAMES
typedef spDrawOrderTimeline DrawOrderTimeline;
#define DrawOrderTimeline_create(...) spDrawOrderTimeline_create(__VA_ARGS__)
#define DrawOrderTimeline_setFrame(...) spDrawOrderTimeline_setFrame(__VA_ARGS__)
#endif

/**/

typedef struct spDeformTimeline {
	spCurveTimeline super;
	int const framesCount;
	float* const frames; /* time, ... */
	int const frameVerticesCount;
	const float** const frameVertices;
	int slotIndex;
	spAttachment* attachment;

#ifdef __cplusplus
	spDeformTimeline() :
		super(),
		framesCount(0),
		frames(0),
		frameVerticesCount(0),
		frameVertices(0),
		slotIndex(0) {
	}
#endif
} spDeformTimeline;

spDeformTimeline* spDeformTimeline_create (int framesCount, int frameVerticesCount);

void spDeformTimeline_setFrame (spDeformTimeline* self, int frameIndex, float time, float* vertices);

#ifdef SPINE_SHORT_NAMES
typedef spDeformTimeline DeformTimeline;
#define DeformTimeline_create(...) spDeformTimeline_create(__VA_ARGS__)
#define DeformTimeline_setFrame(...) spDeformTimeline_setFrame(__VA_ARGS__)
#endif

/**/

static const int IKCONSTRAINT_ENTRIES = 3;

typedef struct spIkConstraintTimeline {
	spCurveTimeline super;
	int const framesCount;
	float* const frames; /* time, mix, bendDirection, ... */
	int ikConstraintIndex;

#ifdef __cplusplus
	spIkConstraintTimeline() :
		super(),
		framesCount(0),
		frames(0),
		ikConstraintIndex(0) {
	}
#endif
} spIkConstraintTimeline;

spIkConstraintTimeline* spIkConstraintTimeline_create (int framesCount);

void spIkConstraintTimeline_setFrame (spIkConstraintTimeline* self, int frameIndex, float time, float mix, int bendDirection);

#ifdef SPINE_SHORT_NAMES
typedef spIkConstraintTimeline IkConstraintTimeline;
#define IkConstraintTimeline_create(...) spIkConstraintTimeline_create(__VA_ARGS__)
#define IkConstraintTimeline_setFrame(...) spIkConstraintTimeline_setFrame(__VA_ARGS__)
#endif

/**/

static const int TRANSFORMCONSTRAINT_ENTRIES = 5;

typedef struct spTransformConstraintTimeline {
	spCurveTimeline super;
	int const framesCount;
	float* const frames; /* time, rotate mix, translate mix, scale mix, shear mix, ... */
	int transformConstraintIndex;

#ifdef __cplusplus
	spTransformConstraintTimeline() :
		super(),
		framesCount(0),
		frames(0),
		transformConstraintIndex(0) {
	}
#endif
} spTransformConstraintTimeline;

spTransformConstraintTimeline* spTransformConstraintTimeline_create (int framesCount);

void spTransformConstraintTimeline_setFrame (spTransformConstraintTimeline* self, int frameIndex, float time, float rotateMix, float translateMix, float scaleMix, float shearMix);

#ifdef SPINE_SHORT_NAMES
typedef spTransformConstraintTimeline TransformConstraintTimeline;
#define TransformConstraintTimeline_create(...) spTransformConstraintTimeline_create(__VA_ARGS__)
#define TransformConstraintTimeline_setFrame(...) spTransformConstraintTimeline_setFrame(__VA_ARGS__)
#endif

/**/

static const int PATHCONSTRAINTPOSITION_ENTRIES = 2;

typedef struct spPathConstraintPositionTimeline {
	spCurveTimeline super;
	int const framesCount;
	float* const frames; /* time, rotate mix, translate mix, scale mix, shear mix, ... */
	int pathConstraintIndex;

#ifdef __cplusplus
	spPathConstraintPositionTimeline() :
		super(),
		framesCount(0),
		frames(0),
		pathConstraintIndex(0) {
	}
#endif
} spPathConstraintPositionTimeline;

spPathConstraintPositionTimeline* spPathConstraintPositionTimeline_create (int framesCount);

void spPathConstraintPositionTimeline_setFrame (spPathConstraintPositionTimeline* self, int frameIndex, float time, float value);

#ifdef SPINE_SHORT_NAMES
typedef spPathConstraintPositionTimeline PathConstraintPositionTimeline;
#define PathConstraintPositionTimeline_create(...) spPathConstraintPositionTimeline_create(__VA_ARGS__)
#define PathConstraintPositionTimeline_setFrame(...) spPathConstraintPositionTimeline_setFrame(__VA_ARGS__)
#endif

/**/

static const int PATHCONSTRAINTSPACING_ENTRIES = 2;

typedef struct spPathConstraintSpacingTimeline {
	spCurveTimeline super;
	int const framesCount;
	float* const frames; /* time, rotate mix, translate mix, scale mix, shear mix, ... */
	int pathConstraintIndex;

#ifdef __cplusplus
	spPathConstraintSpacingTimeline() :
		super(),
		framesCount(0),
		frames(0),
		pathConstraintIndex(0) {
	}
#endif
} spPathConstraintSpacingTimeline;

spPathConstraintSpacingTimeline* spPathConstraintSpacingTimeline_create (int framesCount);

void spPathConstraintSpacingTimeline_setFrame (spPathConstraintSpacingTimeline* self, int frameIndex, float time, float value);

#ifdef SPINE_SHORT_NAMES
typedef spPathConstraintSpacingTimeline PathConstraintSpacingTimeline;
#define PathConstraintSpacingTimeline_create(...) spPathConstraintSpacingTimeline_create(__VA_ARGS__)
#define PathConstraintSpacingTimeline_setFrame(...) spPathConstraintSpacingTimeline_setFrame(__VA_ARGS__)
#endif

/**/

static const int PATHCONSTRAINTMIX_ENTRIES = 3;

typedef struct spPathConstraintMixTimeline {
	spCurveTimeline super;
	int const framesCount;
	float* const frames; /* time, rotate mix, translate mix, scale mix, shear mix, ... */
	int pathConstraintIndex;

#ifdef __cplusplus
	spPathConstraintMixTimeline() :
		super(),
		framesCount(0),
		frames(0),
		pathConstraintIndex(0) {
	}
#endif
} spPathConstraintMixTimeline;

spPathConstraintMixTimeline* spPathConstraintMixTimeline_create (int framesCount);

void spPathConstraintMixTimeline_setFrame (spPathConstraintMixTimeline* self, int frameIndex, float time, float rotateMix, float translateMix);

#ifdef SPINE_SHORT_NAMES
typedef spPathConstraintMixTimeline PathConstraintMixTimeline;
#define PathConstraintMixTimeline_create(...) spPathConstraintMixTimeline_create(__VA_ARGS__)
#define PathConstraintMixTimeline_setFrame(...) spPathConstraintMixTimeline_setFrame(__VA_ARGS__)
#endif

/**/

#ifdef __cplusplus
}
#endif

#endif /* SPINE_ANIMATION_H_ */
