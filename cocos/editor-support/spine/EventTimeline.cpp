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

#include <spine/EventTimeline.h>

#include <spine/Skeleton.h>
#include <spine/Event.h>

#include <spine/Animation.h>
#include <spine/TimelineType.h>
#include <spine/Slot.h>
#include <spine/SlotData.h>
#include <spine/EventData.h>
#include <spine/ContainerUtil.h>

#include <float.h>

using namespace spine;

RTTI_IMPL(EventTimeline, Timeline)

EventTimeline::EventTimeline(int frameCount) : Timeline() {
	_frames.setSize(frameCount, 0);
	_events.setSize(frameCount, NULL);
}

EventTimeline::~EventTimeline() {
	ContainerUtil::cleanUpVectorOfPointers(_events);
}

void EventTimeline::apply(Skeleton &skeleton, float lastTime, float time, Vector<Event *> *pEvents, float alpha,
	MixBlend blend, MixDirection direction
) {
	if (pEvents == NULL) return;

	Vector<Event *> &events = *pEvents;

	size_t frameCount = _frames.size();

	if (lastTime > time) {
		// Fire events after last time for looped animations.
		apply(skeleton, lastTime, FLT_MAX, pEvents, alpha, blend, direction);
		lastTime = -1.0f;
	} else if (lastTime >= _frames[frameCount - 1]) {
		// Last time is after last frame.
		return;
	}

	if (time < _frames[0]) return; // Time is before first frame.

	int frame;
	if (lastTime < _frames[0]) {
		frame = 0;
	} else {
		frame = Animation::binarySearch(_frames, lastTime);
		float frameTime = _frames[frame];
		while (frame > 0) {
			// Fire multiple events with the same frame.
			if (_frames[frame - 1] != frameTime) break;
			frame--;
		}
	}

	for (; (size_t)frame < frameCount && time >= _frames[frame]; ++frame)
		events.add(_events[frame]);
}

int EventTimeline::getPropertyId() {
	return ((int) TimelineType_Event << 24);
}

void EventTimeline::setFrame(size_t frameIndex, Event *event) {
	_frames[frameIndex] = event->getTime();
	_events[frameIndex] = event;
}

Vector<float> EventTimeline::getFrames() { return _frames; }

Vector<Event *> &EventTimeline::getEvents() { return _events; }

size_t EventTimeline::getFrameCount() { return _frames.size(); }
