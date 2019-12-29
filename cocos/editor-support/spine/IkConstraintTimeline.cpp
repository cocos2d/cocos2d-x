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

#include <spine/IkConstraintTimeline.h>

#include <spine/Skeleton.h>
#include <spine/Event.h>

#include <spine/Animation.h>
#include <spine/TimelineType.h>
#include <spine/Slot.h>
#include <spine/SlotData.h>
#include <spine/IkConstraint.h>
#include <spine/IkConstraintData.h>

using namespace spine;

RTTI_IMPL(IkConstraintTimeline, CurveTimeline)

const int IkConstraintTimeline::ENTRIES = 6;
const int IkConstraintTimeline::PREV_TIME = -6;
const int IkConstraintTimeline::PREV_MIX = -5;
const int IkConstraintTimeline::PREV_SOFTNESS = -4;
const int IkConstraintTimeline::PREV_BEND_DIRECTION = -3;
const int IkConstraintTimeline::PREV_COMPRESS = -2;
const int IkConstraintTimeline::PREV_STRETCH = -1;
const int IkConstraintTimeline::MIX = 1;
const int IkConstraintTimeline::SOFTNESS = 2;
const int IkConstraintTimeline::BEND_DIRECTION = 3;
const int IkConstraintTimeline::COMPRESS = 4;
const int IkConstraintTimeline::STRETCH = 5;

IkConstraintTimeline::IkConstraintTimeline(int frameCount) : CurveTimeline(frameCount), _ikConstraintIndex(0) {
	_frames.setSize(frameCount * ENTRIES, 0);
}

void IkConstraintTimeline::apply(Skeleton &skeleton, float lastTime, float time, Vector<Event *> *pEvents, float alpha,
								 MixBlend blend, MixDirection direction) {
	SP_UNUSED(lastTime);
	SP_UNUSED(pEvents);

	IkConstraint *constraintP = skeleton._ikConstraints[_ikConstraintIndex];
	IkConstraint &constraint = *constraintP;
	if (!constraint.isActive()) return;

	if (time < _frames[0]) {
		switch (blend) {
			case MixBlend_Setup:
				constraint._mix = constraint._data._mix;
				constraint._softness = constraint._data._softness;
				constraint._bendDirection = constraint._data._bendDirection;
				constraint._compress = constraint._data._compress;
				constraint._stretch = constraint._data._stretch;
				return;
			case MixBlend_First:
				constraint._mix += (constraint._data._mix - constraint._mix) * alpha;
				constraint._softness += (constraint._data._softness - constraint._softness) * alpha;
				constraint._bendDirection = constraint._data._bendDirection;
				constraint._compress = constraint._data._compress;
				constraint._stretch = constraint._data._stretch;
				return;
			default:
				return;
		}
	}

	if (time >= _frames[_frames.size() - ENTRIES]) {
		// Time is after last frame.
		if (blend == MixBlend_Setup) {
			constraint._mix =
					constraint._data._mix + (_frames[_frames.size() + PREV_MIX] - constraint._data._mix) * alpha;
			constraint._softness = constraint._data._softness
				+ (_frames[_frames.size() + PREV_SOFTNESS] - constraint._data._softness) * alpha;
			if (direction == MixDirection_Out) {
				constraint._bendDirection = constraint._data._bendDirection;
				constraint._compress = constraint._data._compress;
				constraint._stretch = constraint._data._stretch;
			} else {
				constraint._bendDirection = (int) _frames[_frames.size() + PREV_BEND_DIRECTION];
				constraint._compress = _frames[_frames.size() + PREV_COMPRESS] != 0;
				constraint._stretch = _frames[_frames.size() + PREV_STRETCH] != 0;
			}
		} else {
			constraint._mix += (_frames[_frames.size() + PREV_MIX] - constraint._mix) * alpha;
			constraint._softness += (_frames[_frames.size() + PREV_SOFTNESS] - constraint._softness) * alpha;
			if (direction == MixDirection_In) {
				constraint._bendDirection = (int) _frames[_frames.size() + PREV_BEND_DIRECTION];
				constraint._compress = _frames[_frames.size() + PREV_COMPRESS] != 0;
				constraint._stretch = _frames[_frames.size() + PREV_STRETCH] != 0;
			}
		}
		return;
	}

	// Interpolate between the previous frame and the current frame.
	int frame = Animation::binarySearch(_frames, time, ENTRIES);
	float mix = _frames[frame + PREV_MIX];
	float softness = _frames[frame + PREV_SOFTNESS];
	float frameTime = _frames[frame];
	float percent = getCurvePercent(frame / ENTRIES - 1,
									1 - (time - frameTime) / (_frames[frame + PREV_TIME] - frameTime));

	if (blend == MixBlend_Setup) {
		constraint._mix =
				constraint._data._mix + (mix + (_frames[frame + MIX] - mix) * percent - constraint._data._mix) * alpha;
		constraint._softness = constraint._data._softness
			+ (softness + (_frames[frame + SOFTNESS] - softness) * percent - constraint._data._softness) * alpha;
		if (direction == MixDirection_Out) {
			constraint._bendDirection = constraint._data._bendDirection;
			constraint._compress = constraint._data._compress;
			constraint._stretch = constraint._data._stretch;
		} else {
			constraint._bendDirection = (int) _frames[_frames.size() + PREV_BEND_DIRECTION];
			constraint._compress = _frames[frame + PREV_COMPRESS] != 0;
			constraint._stretch = _frames[frame + PREV_STRETCH] != 0;
		}
	} else {
		constraint._mix += (mix + (_frames[frame + MIX] - mix) * percent - constraint._mix) * alpha;
		constraint._softness += (softness + (_frames[frame + SOFTNESS] - softness) * percent - constraint._softness) * alpha;
		if (direction == MixDirection_In) {
			constraint._bendDirection = (int) _frames[frame + PREV_BEND_DIRECTION];
			constraint._compress = _frames[frame + PREV_COMPRESS] != 0;
			constraint._stretch = _frames[frame + PREV_STRETCH] != 0;
		}
	}
}

int IkConstraintTimeline::getPropertyId() {
	return ((int) TimelineType_IkConstraint << 24) + _ikConstraintIndex;
}

void IkConstraintTimeline::setFrame(int frameIndex, float time, float mix, float softness, int bendDirection, bool compress, bool stretch) {
	frameIndex *= ENTRIES;
	_frames[frameIndex] = time;
	_frames[frameIndex + MIX] = mix;
	_frames[frameIndex + SOFTNESS] = softness;
	_frames[frameIndex + BEND_DIRECTION] = (float)bendDirection;
	_frames[frameIndex + COMPRESS] = compress ? 1 : 0;
	_frames[frameIndex + STRETCH] = stretch ? 1 : 0;
}
