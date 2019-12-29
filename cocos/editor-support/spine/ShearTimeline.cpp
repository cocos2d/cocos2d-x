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

#include <spine/ShearTimeline.h>

#include <spine/Skeleton.h>
#include <spine/Event.h>

#include <spine/Slot.h>
#include <spine/SlotData.h>
#include <spine/Bone.h>
#include <spine/BoneData.h>

using namespace spine;

RTTI_IMPL(ShearTimeline, TranslateTimeline)

ShearTimeline::ShearTimeline(int frameCount) : TranslateTimeline(frameCount) {
}

void ShearTimeline::apply(Skeleton &skeleton, float lastTime, float time, Vector<Event *> *pEvents, float alpha,
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
			bone._shearX = bone._data._shearX;
			bone._shearY = bone._data._shearY;
			return;
		case MixBlend_First:
			bone._shearX += (bone._data._shearX - bone._shearX) * alpha;
			bone._shearY += (bone._data._shearY - bone._shearY) * alpha;
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

		x = x + (_frames[frame + X] - x) * percent;
		y = y + (_frames[frame + Y] - y) * percent;
	}

	switch (blend) {
		case MixBlend_Setup:
			bone._shearX = bone._data._shearX + x * alpha;
			bone._shearY = bone._data._shearY + y * alpha;
			break;
		case MixBlend_First:
		case MixBlend_Replace:
			bone._shearX += (bone._data._shearX + x - bone._shearX) * alpha;
			bone._shearY += (bone._data._shearY + y - bone._shearY) * alpha;
			break;
		case MixBlend_Add:
			bone._shearX += x * alpha;
			bone._shearY += y * alpha;
	}
}

int ShearTimeline::getPropertyId() {
	return ((int) TimelineType_Shear << 24) + _boneIndex;
}
