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

#include <spine/Animation.h>
#include <spine/Timeline.h>
#include <spine/Skeleton.h>
#include <spine/Event.h>

#include <spine/ContainerUtil.h>

using namespace spine;

Animation::Animation(const String &name, Vector<Timeline *> &timelines, float duration) :
		_timelines(timelines),
		_duration(duration),
		_name(name) {
	assert(_name.length() > 0);
}

Animation::~Animation() {
	ContainerUtil::cleanUpVectorOfPointers(_timelines);
}

void Animation::apply(Skeleton &skeleton, float lastTime, float time, bool loop, Vector<Event *> *pEvents, float alpha,
					  MixBlend blend, MixDirection direction) {
	if (loop && _duration != 0) {
		time = MathUtil::fmod(time, _duration);
		if (lastTime > 0) {
			lastTime = MathUtil::fmod(lastTime, _duration);
		}
	}

	for (size_t i = 0, n = _timelines.size(); i < n; ++i) {
		_timelines[i]->apply(skeleton, lastTime, time, pEvents, alpha, blend, direction);
	}
}

const String &Animation::getName() {
	return _name;
}

Vector<Timeline *> &Animation::getTimelines() {
	return _timelines;
}

float Animation::getDuration() {
	return _duration;
}

void Animation::setDuration(float inValue) {
	_duration = inValue;
}

int Animation::binarySearch(Vector<float> &values, float target, int step) {
	int low = 0;
	int size = (int)values.size();
	int high = size / step - 2;
	if (high == 0) {
		return step;
	}

	int current = (int) (static_cast<uint32_t>(high) >> 1);
	while (true) {
		if (values[(current + 1) * step] <= target) {
			low = current + 1;
		} else {
			high = current;
		}

		if (low == high) {
			return (low + 1) * step;
		}

		current = (int) (static_cast<uint32_t>(low + high) >> 1);
	}
}

int Animation::binarySearch(Vector<float> &values, float target) {
	int low = 0;
	int size = (int)values.size();
	int high = size - 2;
	if (high == 0) {
		return 1;
	}

	int current = (int) (static_cast<uint32_t>(high) >> 1);
	while (true) {
		if (values[(current + 1)] <= target) {
			low = current + 1;
		} else {
			high = current;
		}

		if (low == high) {
			return (low + 1);
		}

		current = (int) (static_cast<uint32_t>(low + high) >> 1);
	}
}

int Animation::linearSearch(Vector<float> &values, float target, int step) {
	for (int i = 0, last = (int)values.size() - step; i <= last; i += step) {
		if (values[i] > target) {
			return i;
		}
	}

	return -1;
}
