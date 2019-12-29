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
	_pathConstraintIndex(0)
{
	_frames.setSize(frameCount * ENTRIES, 0);
}

PathConstraintPositionTimeline::~PathConstraintPositionTimeline() {
}

void PathConstraintPositionTimeline::apply(Skeleton &skeleton, float lastTime, float time, Vector<Event *> *pEvents,
	float alpha, MixBlend blend, MixDirection direction
) {
	SP_UNUSED(lastTime);
	SP_UNUSED(pEvents);
	SP_UNUSED(direction);

	PathConstraint *constraintP = skeleton._pathConstraints[_pathConstraintIndex];
	PathConstraint &constraint = *constraintP;
	if (!constraint.isActive()) return;

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
	if (blend == MixBlend_Setup)
		constraint._position = constraint._data._position + (position - constraint._data._position) * alpha;
	else
		constraint._position += (position - constraint._position) * alpha;
}

int PathConstraintPositionTimeline::getPropertyId() {
	return ((int) TimelineType_PathConstraintPosition << 24) + _pathConstraintIndex;
}

void PathConstraintPositionTimeline::setFrame(int frameIndex, float time, float value) {
	frameIndex *= ENTRIES;
	_frames[frameIndex] = time;
	_frames[frameIndex + VALUE] = value;
}
