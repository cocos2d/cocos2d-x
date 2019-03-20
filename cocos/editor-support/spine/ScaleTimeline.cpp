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

#include <spine/ScaleTimeline.h>

#include <spine/Skeleton.h>
#include <spine/Event.h>

#include <spine/Slot.h>
#include <spine/SlotData.h>
#include <spine/Bone.h>
#include <spine/BoneData.h>

using namespace spine;

RTTI_IMPL(ScaleTimeline, TranslateTimeline)

ScaleTimeline::ScaleTimeline(int frameCount) : TranslateTimeline(frameCount) {
}

void ScaleTimeline::apply(Skeleton &skeleton, float lastTime, float time, Vector<Event *> *pEvents, float alpha,
						  MixBlend blend, MixDirection direction) {
	SP_UNUSED(lastTime);
	SP_UNUSED(pEvents);

	Bone *boneP = skeleton._bones[_boneIndex];
	Bone &bone = *boneP;

	if (time < _frames[0]) {
		switch (blend) {
			case MixBlend_Setup:
				bone._scaleX = bone._data._scaleX;
				bone._scaleY = bone._data._scaleY;
				return;
			case MixBlend_First:
				bone._scaleX += (bone._data._scaleX - bone._scaleX) * alpha;
				bone._scaleY += (bone._data._scaleY - bone._scaleY) * alpha;
			default: {}
		}
		return;
	}

	float x, y;
	if (time >= _frames[_frames.size() - ENTRIES]) {
		// Time is after last frame.
		x = _frames[_frames.size() + PREV_X] * bone._data._scaleX;
		y = _frames[_frames.size() + PREV_Y] * bone._data._scaleY;
	} else {
		// Interpolate between the previous frame and the current frame.
		int frame = Animation::binarySearch(_frames, time, ENTRIES);
		x = _frames[frame + PREV_X];
		y = _frames[frame + PREV_Y];
		float frameTime = _frames[frame];
		float percent = getCurvePercent(frame / ENTRIES - 1,
										1 - (time - frameTime) / (_frames[frame + PREV_TIME] - frameTime));

		x = (x + (_frames[frame + X] - x) * percent) * bone._data._scaleX;
		y = (y + (_frames[frame + Y] - y) * percent) * bone._data._scaleY;
	}

	if (alpha == 1) {
		if (blend == MixBlend_Add) {
			bone._scaleX += x - bone._data._scaleX;
			bone._scaleY += y - bone._data._scaleY;
		} else {
			bone._scaleX = x;
			bone._scaleY = y;
		}
	} else {
		// Mixing out uses sign of setup or current pose, else use sign of key.
		float bx, by;
		if (direction == MixDirection_Out) {
			switch (blend) {
				case MixBlend_Setup:
					bx = bone._data._scaleX;
					by = bone._data._scaleY;
					bone._scaleX = bx + (MathUtil::abs(x) * MathUtil::sign(bx) - bx) * alpha;
					bone._scaleY = by + (MathUtil::abs(y) * MathUtil::sign(by) - by) * alpha;
					break;
				case MixBlend_First:
				case MixBlend_Replace:
					bx = bone._scaleX;
					by = bone._scaleY;
					bone._scaleX = bx + (MathUtil::abs(x) * MathUtil::sign(bx) - bx) * alpha;
					bone._scaleY = by + (MathUtil::abs(y) * MathUtil::sign(by) - by) * alpha;
					break;
				case MixBlend_Add:
					bx = bone._scaleX;
					by = bone._scaleY;
					bone._scaleX = bx + (MathUtil::abs(x) * MathUtil::sign(bx) - bone._data._scaleX) * alpha;
					bone._scaleY = by + (MathUtil::abs(y) * MathUtil::sign(by) - bone._data._scaleY) * alpha;
			}
		} else {
			switch (blend) {
				case MixBlend_Setup:
					bx = MathUtil::abs(bone._data._scaleX) * MathUtil::sign(x);
					by = MathUtil::abs(bone._data._scaleY) * MathUtil::sign(y);
					bone._scaleX = bx + (x - bx) * alpha;
					bone._scaleY = by + (y - by) * alpha;
					break;
				case MixBlend_First:
				case MixBlend_Replace:
					bx = MathUtil::abs(bone._scaleX) * MathUtil::sign(x);
					by = MathUtil::abs(bone._scaleY) * MathUtil::sign(y);
					bone._scaleX = bx + (x - bx) * alpha;
					bone._scaleY = by + (y - by) * alpha;
					break;
				case MixBlend_Add:
					bx = MathUtil::sign(x);
					by = MathUtil::sign(y);
					bone._scaleX = MathUtil::abs(bone._scaleX) * bx + (x - MathUtil::abs(bone._data._scaleX) * bx) * alpha;
					bone._scaleY = MathUtil::abs(bone._scaleY) * by + (y - MathUtil::abs(bone._data._scaleY) * by) * alpha;
			}
		}
	}
}

int ScaleTimeline::getPropertyId() {
	return ((int) TimelineType_Scale << 24) + _boneIndex;
}
