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

#include <spine/DrawOrderTimeline.h>

#include <spine/Skeleton.h>
#include <spine/Event.h>

#include <spine/Animation.h>
#include <spine/TimelineType.h>
#include <spine/Slot.h>
#include <spine/SlotData.h>

using namespace spine;

RTTI_IMPL(DrawOrderTimeline, Timeline)

DrawOrderTimeline::DrawOrderTimeline(int frameCount) : Timeline() {
	_frames.ensureCapacity(frameCount);
	_drawOrders.ensureCapacity(frameCount);

	_frames.setSize(frameCount, 0);

	for (int i = 0; i < frameCount; ++i) {
		Vector<int> vec;
		_drawOrders.add(vec);
	}
}

void DrawOrderTimeline::apply(Skeleton &skeleton, float lastTime, float time, Vector<Event *> *pEvents, float alpha,
	MixBlend blend, MixDirection direction
) {
	SP_UNUSED(lastTime);
	SP_UNUSED(pEvents);
	SP_UNUSED(alpha);

	Vector<Slot *> &drawOrder = skeleton._drawOrder;
	Vector<Slot *> &slots = skeleton._slots;
	if (direction == MixDirection_Out && blend == MixBlend_Setup) {
		drawOrder.clear();
		drawOrder.ensureCapacity(slots.size());
		for (size_t i = 0, n = slots.size(); i < n; ++i)
			drawOrder.add(slots[i]);
		return;
	}

	if (time < _frames[0]) {
		if (blend == MixBlend_Setup || blend == MixBlend_First) {
			drawOrder.clear();
			drawOrder.ensureCapacity(slots.size());
			for (size_t i = 0, n = slots.size(); i < n; ++i)
				drawOrder.add(slots[i]);
		}
		return;
	}

	size_t frame;
	if (time >= _frames[_frames.size() - 1]) {
		// Time is after last frame.
		frame = _frames.size() - 1;
	} else
		frame = (size_t)Animation::binarySearch(_frames, time) - 1;

	Vector<int> &drawOrderToSetupIndex = _drawOrders[frame];
	if (drawOrderToSetupIndex.size() == 0) {
		drawOrder.clear();
		for (size_t i = 0, n = slots.size(); i < n; ++i)
			drawOrder.add(slots[i]);
	} else {
		for (size_t i = 0, n = drawOrderToSetupIndex.size(); i < n; ++i)
			drawOrder[i] = slots[drawOrderToSetupIndex[i]];
	}
}

int DrawOrderTimeline::getPropertyId() {
	return ((int) TimelineType_DrawOrder << 24);
}

void DrawOrderTimeline::setFrame(size_t frameIndex, float time, Vector<int> &drawOrder) {
	_frames[frameIndex] = time;
	_drawOrders[frameIndex].clear();
	_drawOrders[frameIndex].addAll(drawOrder);
}

Vector<float> &DrawOrderTimeline::getFrames() {
	return _frames;
}

Vector<Vector<int> > &DrawOrderTimeline::getDrawOrders() {
	return _drawOrders;
}

size_t DrawOrderTimeline::getFrameCount() {
	return _frames.size();
}
