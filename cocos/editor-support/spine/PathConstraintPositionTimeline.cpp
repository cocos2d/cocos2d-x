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

#ifdef SPINE_UE4
#include "SpinePluginPrivatePCH.h"
#endif

#include <spine/PathConstraintPositionTimeline.h>

#include <spine/Skeleton.h>
#include <spine/Event.h>

#include <spine/Animation.h>
#include <spine/TimelineType.h>
#include <spine/Slot.h>
#include <spine/SlotData.h>
#include <spine/PathConstraint.h>
#include <spine/PathConstraintData.h>

using namespace spine;

RTTI_IMPL(PathConstraintPositionTimeline, CurveTimeline)

const int PathConstraintPositionTimeline::ENTRIES = 2;
const int PathConstraintPositionTimeline::PREV_TIME = -2;
const int PathConstraintPositionTimeline::PREV_VALUE = -1;
const int PathConstraintPositionTimeline::VALUE = 1;

PathConstraintPositionTimeline::PathConstraintPositionTimeline(int frameCount) : CurveTimeline(frameCount),
																				 _pathConstraintIndex(0) {
	_frames.setSize(frameCount * ENTRIES, 0);
}

PathConstraintPositionTimeline::~PathConstraintPositionTimeline() {
}

void PathConstraintPositionTimeline::apply(Skeleton &skeleton, float lastTime, float time, Vector<Event *> *pEvents,
										   float alpha, MixBlend blend, MixDirection direction) {
	SP_UNUSED(lastTime);
	SP_UNUSED(pEvents);
	SP_UNUSED(direction);

	PathConstraint *constraintP = skeleton._pathConstraints[_pathConstraintIndex];
	PathConstraint &constraint = *constraintP;
	if (time < _frames[0]) {
		switch (blend) {
			case MixBlend_Setup:
				constraint._position = constraint._data._position;
				return;
			case MixBlend_First:
				constraint._position += (constraint._data._position - constraint._position) * alpha;
				return;
			default:
				return;
		}
	}

	float position;
	if (time >= _frames[_frames.size() - ENTRIES]) {
		// Time is after last frame.
		position = _frames[_frames.size() + PREV_VALUE];
	} else {
		// Interpolate between the previous frame and the current frame.
		int frame = Animation::binarySearch(_frames, time, ENTRIES);
		position = _frames[frame + PREV_VALUE];
		float frameTime = _frames[frame];
		float percent = getCurvePercent(frame / ENTRIES - 1,
										1 - (time - frameTime) / (_frames[frame + PREV_TIME] - frameTime));

		position += (_frames[frame + VALUE] - position) * percent;
	}
	if (blend == MixBlend_Setup) {
		constraint._position = constraint._data._position + (position - constraint._data._position) * alpha;
	} else {
		constraint._position += (position - constraint._position) * alpha;
	}
}

int PathConstraintPositionTimeline::getPropertyId() {
	return ((int) TimelineType_PathConstraintPosition << 24) + _pathConstraintIndex;
}

void PathConstraintPositionTimeline::setFrame(int frameIndex, float time, float value) {
	frameIndex *= ENTRIES;
	_frames[frameIndex] = time;
	_frames[frameIndex + VALUE] = value;
}
