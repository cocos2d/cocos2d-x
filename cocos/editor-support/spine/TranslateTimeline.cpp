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

#include <spine/TranslateTimeline.h>

#include <spine/Skeleton.h>
#include <spine/Event.h>

#include <spine/Slot.h>
#include <spine/SlotData.h>
#include <spine/Bone.h>
#include <spine/BoneData.h>

using namespace spine;

RTTI_IMPL(TranslateTimeline, CurveTimeline)

const int TranslateTimeline::ENTRIES = 3;
const int TranslateTimeline::PREV_TIME = -3;
const int TranslateTimeline::PREV_X = -2;
const int TranslateTimeline::PREV_Y = -1;
const int TranslateTimeline::X = 1;
const int TranslateTimeline::Y = 2;

TranslateTimeline::TranslateTimeline(int frameCount) : CurveTimeline(frameCount), _boneIndex(0) {
	_frames.ensureCapacity(frameCount * ENTRIES);
	_frames.setSize(frameCount * ENTRIES, 0);
}

TranslateTimeline::~TranslateTimeline() {
}

void TranslateTimeline::apply(Skeleton &skeleton, float lastTime, float time, Vector<Event *> *pEvents, float alpha,
	MixBlend blend, MixDirection direction
) {
	SP_UNUSED(lastTime);
	SP_UNUSED(pEvents);
	SP_UNUSED(direction);

	Bone *boneP = skeleton._bones[_boneIndex];
	Bone &bone = *boneP;
	if (!bone._active) return;

	if (time < _frames[0]) {
		switch (blend) {
		case MixBlend_Setup:
			bone._x = bone._data._x;
			bone._y = bone._data._y;
			return;
		case MixBlend_First:
			bone._x += (bone._data._x - bone._x) * alpha;
			bone._y += (bone._data._y - bone._y) * alpha;
		default: {}
		}
		return;
	}

	float x, y;
	if (time >= _frames[_frames.size() - ENTRIES]) {
		// Time is after last frame.
		x = _frames[_frames.size() + PREV_X];
		y = _frames[_frames.size() + PREV_Y];
	} else {
		// Interpolate between the previous frame and the current frame.
		int frame = Animation::binarySearch(_frames, time, ENTRIES);
		x = _frames[frame + PREV_X];
		y = _frames[frame + PREV_Y];
		float frameTime = _frames[frame];
		float percent = getCurvePercent(frame / ENTRIES - 1,
			1 - (time - frameTime) / (_frames[frame + PREV_TIME] - frameTime));

		x += (_frames[frame + X] - x) * percent;
		y += (_frames[frame + Y] - y) * percent;
	}

	switch (blend) {
	case MixBlend_Setup:
		bone._x = bone._data._x + x * alpha;
		bone._y = bone._data._y + y * alpha;
		break;
	case MixBlend_First:
	case MixBlend_Replace:
		bone._x += (bone._data._x + x - bone._x) * alpha;
		bone._y += (bone._data._y + y - bone._y) * alpha;
		break;
	case MixBlend_Add:
		bone._x += x * alpha;
		bone._y += y * alpha;
	}
}

int TranslateTimeline::getPropertyId() {
	return ((int) TimelineType_Translate << 24) + _boneIndex;
}

void TranslateTimeline::setFrame(int frameIndex, float time, float x, float y) {
	frameIndex *= ENTRIES;
	_frames[frameIndex] = time;
	_frames[frameIndex + X] = x;
	_frames[frameIndex + Y] = y;
}
