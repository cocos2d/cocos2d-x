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

#include <spine/TransformConstraintTimeline.h>

#include <spine/Skeleton.h>
#include <spine/Event.h>

#include <spine/Animation.h>
#include <spine/TimelineType.h>
#include <spine/Slot.h>
#include <spine/SlotData.h>
#include <spine/TransformConstraint.h>
#include <spine/TransformConstraintData.h>

using namespace spine;

RTTI_IMPL(TransformConstraintTimeline, CurveTimeline)

const int TransformConstraintTimeline::ENTRIES = 5;
const int TransformConstraintTimeline::PREV_TIME = -5;
const int TransformConstraintTimeline::PREV_ROTATE = -4;
const int TransformConstraintTimeline::PREV_TRANSLATE = -3;
const int TransformConstraintTimeline::PREV_SCALE = -2;
const int TransformConstraintTimeline::PREV_SHEAR = -1;
const int TransformConstraintTimeline::ROTATE = 1;
const int TransformConstraintTimeline::TRANSLATE = 2;
const int TransformConstraintTimeline::SCALE = 3;
const int TransformConstraintTimeline::SHEAR = 4;

TransformConstraintTimeline::TransformConstraintTimeline(int frameCount) : CurveTimeline(frameCount),
	_transformConstraintIndex(0)
{
	_frames.setSize(frameCount * ENTRIES, 0);
}

void TransformConstraintTimeline::apply(Skeleton &skeleton, float lastTime, float time, Vector<Event *> *pEvents,
										float alpha, MixBlend blend, MixDirection direction) {
	SP_UNUSED(lastTime);
	SP_UNUSED(pEvents);
	SP_UNUSED(direction);

	TransformConstraint *constraintP = skeleton._transformConstraints[_transformConstraintIndex];
	TransformConstraint &constraint = *constraintP;
	if (!constraint.isActive()) return;

	if (time < _frames[0]) {
		switch (blend) {
		case MixBlend_Setup:
			constraint._rotateMix = constraint._data._rotateMix;
			constraint._translateMix = constraint._data._translateMix;
			constraint._scaleMix = constraint._data._scaleMix;
			constraint._shearMix = constraint._data._shearMix;
			return;
		case MixBlend_First:
			constraint._rotateMix += (constraint._data._rotateMix - constraint._rotateMix) * alpha;
			constraint._translateMix += (constraint._data._translateMix - constraint._translateMix) * alpha;
			constraint._scaleMix += (constraint._data._scaleMix - constraint._scaleMix) * alpha;
			constraint._shearMix += (constraint._data._shearMix - constraint._shearMix) * alpha;
			return;
		default:
			return;
		}
	}

	float rotate, translate, scale, shear;
	if (time >= _frames[_frames.size() - ENTRIES]) {
		// Time is after last frame.
		size_t i = _frames.size();
		rotate = _frames[i + PREV_ROTATE];
		translate = _frames[i + PREV_TRANSLATE];
		scale = _frames[i + PREV_SCALE];
		shear = _frames[i + PREV_SHEAR];
	} else {
		// Interpolate between the previous frame and the current frame.
		int frame = Animation::binarySearch(_frames, time, ENTRIES);
		rotate = _frames[frame + PREV_ROTATE];
		translate = _frames[frame + PREV_TRANSLATE];
		scale = _frames[frame + PREV_SCALE];
		shear = _frames[frame + PREV_SHEAR];
		float frameTime = _frames[frame];
		float percent = getCurvePercent(frame / ENTRIES - 1,
			1 - (time - frameTime) / (_frames[frame + PREV_TIME] - frameTime));

		rotate += (_frames[frame + ROTATE] - rotate) * percent;
		translate += (_frames[frame + TRANSLATE] - translate) * percent;
		scale += (_frames[frame + SCALE] - scale) * percent;
		shear += (_frames[frame + SHEAR] - shear) * percent;
	}

	if (blend == MixBlend_Setup) {
		TransformConstraintData &data = constraint._data;
		constraint._rotateMix = data._rotateMix + (rotate - data._rotateMix) * alpha;
		constraint._translateMix = data._translateMix + (translate - data._translateMix) * alpha;
		constraint._scaleMix = data._scaleMix + (scale - data._scaleMix) * alpha;
		constraint._shearMix = data._shearMix + (shear - data._shearMix) * alpha;
	} else {
		constraint._rotateMix += (rotate - constraint._rotateMix) * alpha;
		constraint._translateMix += (translate - constraint._translateMix) * alpha;
		constraint._scaleMix += (scale - constraint._scaleMix) * alpha;
		constraint._shearMix += (shear - constraint._shearMix) * alpha;
	}
}

int TransformConstraintTimeline::getPropertyId() {
	return ((int) TimelineType_TransformConstraint << 24) + _transformConstraintIndex;
}

void TransformConstraintTimeline::setFrame(size_t frameIndex, float time, float rotateMix, float translateMix, float scaleMix,
	float shearMix
) {
	frameIndex *= ENTRIES;
	_frames[frameIndex] = time;
	_frames[frameIndex + ROTATE] = rotateMix;
	_frames[frameIndex + TRANSLATE] = translateMix;
	_frames[frameIndex + SCALE] = scaleMix;
	_frames[frameIndex + SHEAR] = shearMix;
}
