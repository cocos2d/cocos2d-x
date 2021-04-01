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

#include <spine/RotateTimeline.h>

#include <spine/Skeleton.h>
#include <spine/Event.h>

#include <spine/Bone.h>
#include <spine/BoneData.h>
#include <spine/Animation.h>
#include <spine/TimelineType.h>

using namespace spine;

RTTI_IMPL(RotateTimeline, CurveTimeline)

RotateTimeline::RotateTimeline(int frameCount) : CurveTimeline(frameCount), _boneIndex(0) {
	_frames.setSize(frameCount << 1, 0);
}

void RotateTimeline::apply(Skeleton &skeleton, float lastTime, float time, Vector<Event *> *pEvents, float alpha,
	MixBlend blend, MixDirection direction
) {
	SP_UNUSED(lastTime);
	SP_UNUSED(pEvents);
	SP_UNUSED(direction);

	Bone *bone = skeleton.getBones()[_boneIndex];
	if (!bone->_active) return;

	if (time < _frames[0]) {
		switch (blend) {
		case MixBlend_Setup: {
			bone->_rotation = bone->_data._rotation;
			break;
		}
		case MixBlend_First: {
			float r = bone->_data._rotation - bone->_rotation;
			bone->_rotation += (r - (16384 - (int) (16384.499999999996 - r / 360)) * 360) * alpha;
			break;
		}
		default: {
			// TODO?
			break;
		}
		}
		return;
	}

	if (time >= _frames[_frames.size() - ENTRIES]) {
		float r = _frames[_frames.size() + PREV_ROTATION];
		switch (blend) {
			case MixBlend_Setup:
				bone->_rotation = bone->_data._rotation + r * alpha;
				break;
			case MixBlend_First:
			case MixBlend_Replace:
				r += bone->_data._rotation - bone->_rotation;
				r -= (16384 - (int)(16384.499999999996 - r / 360)) * 360;
				// Fall through.
			case MixBlend_Add:
				bone->_rotation += r * alpha;
		}
		return;
	}

	// Interpolate between the previous frame and the current frame.
	int frame = Animation::binarySearch(_frames, time, ENTRIES);
	float prevRotation = _frames[frame + PREV_ROTATION];
	float frameTime = _frames[frame];
	float percent = getCurvePercent((frame >> 1) - 1,
		1 - (time - frameTime) / (_frames[frame + PREV_TIME] - frameTime));
	float r = _frames[frame + ROTATION] - prevRotation;
	r = prevRotation + (r - (16384 - (int)(16384.499999999996 - r / 360)) * 360) * percent;
	switch (blend) {
		case MixBlend_Setup:
			bone->_rotation = bone->_data._rotation + (r - (16384 - (int)(16384.499999999996 - r / 360)) * 360) * alpha;
			break;
		case MixBlend_First:
		case MixBlend_Replace:
			r += bone->_data._rotation - bone->_rotation;
			// Fall through.
		case MixBlend_Add:
			bone->_rotation += (r - (16384 - (int)(16384.499999999996 - r / 360)) * 360) * alpha;
	}
}

int RotateTimeline::getPropertyId() {
	return ((int) TimelineType_Rotate << 24) + _boneIndex;
}

void RotateTimeline::setFrame(int frameIndex, float time, float degrees) {
	frameIndex <<= 1;
	_frames[frameIndex] = time;
	_frames[frameIndex + ROTATION] = degrees;
}

int RotateTimeline::getBoneIndex() {
	return _boneIndex;
}

void RotateTimeline::setBoneIndex(int inValue) {
	_boneIndex = inValue;
}

Vector<float> &RotateTimeline::getFrames() {
	return _frames;
}
