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

#include <spine/AnimationState.h>
#include <spine/Animation.h>
#include <spine/Event.h>
#include <spine/AnimationStateData.h>
#include <spine/Skeleton.h>
#include <spine/RotateTimeline.h>
#include <spine/SkeletonData.h>
#include <spine/Bone.h>
#include <spine/BoneData.h>
#include <spine/AttachmentTimeline.h>
#include <spine/DrawOrderTimeline.h>
#include <spine/EventTimeline.h>

#include <float.h>

using namespace spine;

void dummyOnAnimationEventFunc(AnimationState *state, spine::EventType type, TrackEntry *entry, Event *event = NULL) {
	SP_UNUSED(state);
	SP_UNUSED(type);
	SP_UNUSED(entry);
	SP_UNUSED(event);
}

TrackEntry::TrackEntry() : _animation(NULL), _next(NULL), _mixingFrom(NULL), _mixingTo(0), _trackIndex(0), _loop(false), _holdPrevious(false),
	_eventThreshold(0), _attachmentThreshold(0), _drawOrderThreshold(0), _animationStart(0),
	_animationEnd(0), _animationLast(0), _nextAnimationLast(0), _delay(0), _trackTime(0),
	_trackLast(0), _nextTrackLast(0), _trackEnd(0), _timeScale(1.0f), _alpha(0), _mixTime(0),
	_mixDuration(0), _interruptAlpha(0), _totalAlpha(0), _mixBlend(MixBlend_Replace),
	_listener(dummyOnAnimationEventFunc), _listenerObject(NULL) {
}

TrackEntry::~TrackEntry() { }

int TrackEntry::getTrackIndex() { return _trackIndex; }

Animation *TrackEntry::getAnimation() { return _animation; }

bool TrackEntry::getLoop() { return _loop; }

void TrackEntry::setLoop(bool inValue) { _loop = inValue; }

bool TrackEntry::getHoldPrevious() { return _holdPrevious; }

void TrackEntry::setHoldPrevious(bool inValue) { _holdPrevious = inValue; }

float TrackEntry::getDelay() { return _delay; }

void TrackEntry::setDelay(float inValue) { _delay = inValue; }

float TrackEntry::getTrackTime() { return _trackTime; }

void TrackEntry::setTrackTime(float inValue) { _trackTime = inValue; }

float TrackEntry::getTrackEnd() { return _trackEnd; }

void TrackEntry::setTrackEnd(float inValue) { _trackEnd = inValue; }

float TrackEntry::getAnimationStart() { return _animationStart; }

void TrackEntry::setAnimationStart(float inValue) { _animationStart = inValue; }

float TrackEntry::getAnimationEnd() { return _animationEnd; }

void TrackEntry::setAnimationEnd(float inValue) { _animationEnd = inValue; }

float TrackEntry::getAnimationLast() { return _animationLast; }

void TrackEntry::setAnimationLast(float inValue) {
	_animationLast = inValue;
	_nextAnimationLast = inValue;
}

float TrackEntry::getAnimationTime() {
	if (_loop) {
		float duration = _animationEnd - _animationStart;
		if (duration == 0) return _animationStart;
		return MathUtil::fmod(_trackTime, duration) + _animationStart;
	}

	return MathUtil::min(_trackTime + _animationStart, _animationEnd);
}

float TrackEntry::getTimeScale() { return _timeScale; }

void TrackEntry::setTimeScale(float inValue) { _timeScale = inValue; }

float TrackEntry::getAlpha() { return _alpha; }

void TrackEntry::setAlpha(float inValue) { _alpha = inValue; }

float TrackEntry::getEventThreshold() { return _eventThreshold; }

void TrackEntry::setEventThreshold(float inValue) { _eventThreshold = inValue; }

float TrackEntry::getAttachmentThreshold() { return _attachmentThreshold; }

void TrackEntry::setAttachmentThreshold(float inValue) { _attachmentThreshold = inValue; }

float TrackEntry::getDrawOrderThreshold() { return _drawOrderThreshold; }

void TrackEntry::setDrawOrderThreshold(float inValue) { _drawOrderThreshold = inValue; }

TrackEntry *TrackEntry::getNext() { return _next; }

bool TrackEntry::isComplete() {
	return _trackTime >= _animationEnd - _animationStart;
}

float TrackEntry::getMixTime() { return _mixTime; }

void TrackEntry::setMixTime(float inValue) { _mixTime = inValue; }

float TrackEntry::getMixDuration() { return _mixDuration; }

void TrackEntry::setMixDuration(float inValue) { _mixDuration = inValue; }

TrackEntry *TrackEntry::getMixingFrom() { return _mixingFrom; }

TrackEntry *TrackEntry::getMixingTo() { return _mixingTo; }

void TrackEntry::setMixBlend(MixBlend blend) { _mixBlend = blend; }

MixBlend TrackEntry::getMixBlend() { return _mixBlend; }

void TrackEntry::resetRotationDirections() {
	_timelinesRotation.clear();
}

void TrackEntry::setListener(AnimationStateListener inValue) {
	_listener = inValue;
	_listenerObject = NULL;
}

void TrackEntry::setListener(AnimationStateListenerObject* inValue) {
	_listener = dummyOnAnimationEventFunc;
	_listenerObject = inValue;
}

void TrackEntry::reset() {
	_animation = NULL;
	_next = NULL;
	_mixingFrom = NULL;
	_mixingTo = NULL;

	setRendererObject(NULL);

	_timelineMode.clear();
	_timelineHoldMix.clear();
	_timelinesRotation.clear();

	_listener = dummyOnAnimationEventFunc;
	_listenerObject = NULL;
}

EventQueueEntry::EventQueueEntry(EventType eventType, TrackEntry *trackEntry, Event *event) :
		_type(eventType),
		_entry(trackEntry),
		_event(event) {
}

EventQueue *EventQueue::newEventQueue(AnimationState &state, Pool<TrackEntry> &trackEntryPool) {
	return new(__FILE__, __LINE__) EventQueue(state, trackEntryPool);
}

EventQueueEntry EventQueue::newEventQueueEntry(EventType eventType, TrackEntry *entry, Event *event) {
	return EventQueueEntry(eventType, entry, event);
}

EventQueue::EventQueue(AnimationState &state, Pool<TrackEntry> &trackEntryPool) : _state(state),
	_trackEntryPool(trackEntryPool),
	_drainDisabled(false) {
}

EventQueue::~EventQueue() {
}

void EventQueue::start(TrackEntry *entry) {
	_eventQueueEntries.add(newEventQueueEntry(EventType_Start, entry));
	_state._animationsChanged = true;
}

void EventQueue::interrupt(TrackEntry *entry) {
	_eventQueueEntries.add(newEventQueueEntry(EventType_Interrupt, entry));
}

void EventQueue::end(TrackEntry *entry) {
	_eventQueueEntries.add(newEventQueueEntry(EventType_End, entry));
	_state._animationsChanged = true;
}

void EventQueue::dispose(TrackEntry *entry) {
	_eventQueueEntries.add(newEventQueueEntry(EventType_Dispose, entry));
}

void EventQueue::complete(TrackEntry *entry) {
	_eventQueueEntries.add(newEventQueueEntry(EventType_Complete, entry));
}

void EventQueue::event(TrackEntry *entry, Event *event) {
	_eventQueueEntries.add(newEventQueueEntry(EventType_Event, entry, event));
}

/// Raises all events in the queue and drains the queue.
void EventQueue::drain() {
	if (_drainDisabled) {
		return;
	}

	_drainDisabled = true;

	AnimationState &state = _state;

	// Don't cache _eventQueueEntries.size() so callbacks can queue their own events (eg, call setAnimation in AnimationState_Complete).
	for (size_t i = 0; i < _eventQueueEntries.size(); ++i) {
		EventQueueEntry *queueEntry = &_eventQueueEntries[i];
		TrackEntry *trackEntry = queueEntry->_entry;

		switch (queueEntry->_type) {
		case EventType_Start:
		case EventType_Interrupt:
		case EventType_Complete:
			if (!trackEntry->_listenerObject) trackEntry->_listener(&state, queueEntry->_type, trackEntry, NULL);
			else trackEntry->_listenerObject->callback(&state, queueEntry->_type, trackEntry, NULL);
			if(!state._listenerObject) state._listener(&state, queueEntry->_type, trackEntry, NULL);
			else state._listenerObject->callback(&state, queueEntry->_type, trackEntry, NULL);
			break;
		case EventType_End:
			if (!trackEntry->_listenerObject) trackEntry->_listener(&state, queueEntry->_type, trackEntry, NULL);
			else trackEntry->_listenerObject->callback(&state, queueEntry->_type, trackEntry, NULL);
			if (!state._listenerObject) state._listener(&state, queueEntry->_type, trackEntry, NULL);
			else state._listenerObject->callback(&state, queueEntry->_type, trackEntry, NULL);
			/* Fall through. */
		case EventType_Dispose:
			if (!trackEntry->_listenerObject) trackEntry->_listener(&state, EventType_Dispose, trackEntry, NULL);
			else trackEntry->_listenerObject->callback(&state, EventType_Dispose, trackEntry, NULL);
			if (!state._listenerObject) state._listener(&state, EventType_Dispose, trackEntry, NULL);
			else state._listenerObject->callback(&state, EventType_Dispose, trackEntry, NULL);

			trackEntry->reset();
			_trackEntryPool.free(trackEntry);
			break;
		case EventType_Event:
			if (!trackEntry->_listenerObject) trackEntry->_listener(&state, queueEntry->_type, trackEntry, queueEntry->_event);
			else trackEntry->_listenerObject->callback(&state, queueEntry->_type, trackEntry, queueEntry->_event);
			if (!state._listenerObject) state._listener(&state, queueEntry->_type, trackEntry, queueEntry->_event);
			else state._listenerObject->callback(&state, queueEntry->_type, trackEntry, queueEntry->_event);
			break;
		}
	}
	_eventQueueEntries.clear();

	_drainDisabled = false;
}

const int Subsequent = 0;
const int First = 1;
const int Hold = 2;
const int HoldMix = 3;
const int NotLast = 4;

AnimationState::AnimationState(AnimationStateData *data) :
		_data(data),
		_queue(EventQueue::newEventQueue(*this, _trackEntryPool)),
		_animationsChanged(false),
		_listener(dummyOnAnimationEventFunc),
		_listenerObject(NULL),
		_timeScale(1) {
}

AnimationState::~AnimationState() {
	for (size_t i = 0; i < _tracks.size(); i++) {
		TrackEntry* entry = _tracks[i];
		if (entry) {
			TrackEntry* from = entry->_mixingFrom;
			while (from) {
				TrackEntry* curr = from;
				from = curr->_mixingFrom;
				delete curr;
			}
			TrackEntry* next = entry->_next;
			while (next) {
				TrackEntry* curr = next;
				next = curr->_next;
				delete curr;
			}
			delete entry;
		}
	}
	delete _queue;
}

void AnimationState::update(float delta) {
	delta *= _timeScale;
	for (size_t i = 0, n = _tracks.size(); i < n; ++i) {
		TrackEntry *currentP = _tracks[i];
		if (currentP == NULL) {
			continue;
		}

		TrackEntry &current = *currentP;

		current._animationLast = current._nextAnimationLast;
		current._trackLast = current._nextTrackLast;

		float currentDelta = delta * current._timeScale;

		if (current._delay > 0) {
			current._delay -= currentDelta;
			if (current._delay > 0) {
				continue;
			}
			currentDelta = -current._delay;
			current._delay = 0;
		}

		TrackEntry *next = current._next;
		if (next != NULL) {
			// When the next entry's delay is passed, change to the next entry, preserving leftover time.
			float nextTime = current._trackLast - next->_delay;
			if (nextTime >= 0) {
				next->_delay = 0;
				next->_trackTime += current._timeScale == 0 ? 0 : (nextTime / current._timeScale + delta) * next->_timeScale;
				current._trackTime += currentDelta;
				setCurrent(i, next, true);
				while (next->_mixingFrom != NULL) {
					next->_mixTime += delta;
					next = next->_mixingFrom;
				}
				continue;
			}
		} else if (current._trackLast >= current._trackEnd && current._mixingFrom == NULL) {
			// clear the track when there is no next entry, the track end time is reached, and there is no mixingFrom.
			_tracks[i] = NULL;

			_queue->end(currentP);
			disposeNext(currentP);
			continue;
		}

		if (current._mixingFrom != NULL && updateMixingFrom(currentP, delta)) {
			// End mixing from entries once all have completed.
			TrackEntry *from = current._mixingFrom;
			current._mixingFrom = NULL;
			if (from != NULL) from->_mixingTo = NULL;
			while (from != NULL) {
				_queue->end(from);
				from = from->_mixingFrom;
			}
		}

		current._trackTime += currentDelta;
	}

	_queue->drain();
}

bool AnimationState::apply(Skeleton &skeleton) {
	if (_animationsChanged) {
		animationsChanged();
	}

	bool applied = false;
	for (size_t i = 0, n = _tracks.size(); i < n; ++i) {
		TrackEntry *currentP = _tracks[i];
		if (currentP == NULL || currentP->_delay > 0) {
			continue;
		}

		TrackEntry &current = *currentP;

		applied = true;
		MixBlend blend = i == 0 ? MixBlend_First : current._mixBlend;

		// apply mixing from entries first.
		float mix = current._alpha;
		if (current._mixingFrom != NULL) {
			mix *= applyMixingFrom(currentP, skeleton, blend);
		} else if (current._trackTime >= current._trackEnd && current._next == NULL) {
			mix = 0; // Set to setup pose the last time the entry will be applied.
		}

		// apply current entry.
		float animationLast = current._animationLast, animationTime = current.getAnimationTime();
		size_t timelineCount = current._animation->_timelines.size();
		Vector<Timeline *> &timelines = current._animation->_timelines;
		if ((i == 0 && mix == 1) || blend == MixBlend_Add) {
			for (size_t ii = 0; ii < timelineCount; ++ii)
				timelines[ii]->apply(skeleton, animationLast, animationTime, &_events, mix, blend, MixDirection_In);
		} else {
			Vector<int> &timelineMode = current._timelineMode;

			bool firstFrame = current._timelinesRotation.size() == 0;
			if (firstFrame) current._timelinesRotation.setSize(timelines.size() << 1, 0);
			Vector<float> &timelinesRotation = current._timelinesRotation;

			for (size_t ii = 0; ii < timelineCount; ++ii) {
				Timeline *timeline = timelines[ii];
				assert(timeline);

				MixBlend timelineBlend = (timelineMode[ii] & (NotLast - 1)) == Subsequent ? blend : MixBlend_Setup;

				RotateTimeline *rotateTimeline = NULL;
				if (timeline->getRTTI().isExactly(RotateTimeline::rtti)) rotateTimeline = static_cast<RotateTimeline *>(timeline);

				if (rotateTimeline != NULL)
					applyRotateTimeline(rotateTimeline, skeleton, animationTime, mix, timelineBlend, timelinesRotation, ii << 1, firstFrame);
				else
					timeline->apply(skeleton, animationLast, animationTime, &_events, mix, timelineBlend, MixDirection_In);
			}
		}

		queueEvents(currentP, animationTime);
		_events.clear();
		current._nextAnimationLast = animationTime;
		current._nextTrackLast = current._trackTime;
	}

	_queue->drain();
	return applied;
}

void AnimationState::clearTracks() {
	bool oldDrainDisabled = _queue->_drainDisabled;
	_queue->_drainDisabled = true;
	for (size_t i = 0, n = _tracks.size(); i < n; ++i)
		clearTrack(i);
	_tracks.clear();
	_queue->_drainDisabled = oldDrainDisabled;
	_queue->drain();
}

void AnimationState::clearTrack(size_t trackIndex) {
	if (trackIndex >= _tracks.size()) return;

	TrackEntry *current = _tracks[trackIndex];
	if (current == NULL) return;

	_queue->end(current);

	disposeNext(current);

	TrackEntry *entry = current;
	while (true) {
		TrackEntry *from = entry->_mixingFrom;
		if (from == NULL) break;

		_queue->end(from);
		entry->_mixingFrom = NULL;
		entry->_mixingTo = NULL;
		entry = from;
	}

	_tracks[current->_trackIndex] = NULL;

	_queue->drain();
}

TrackEntry *AnimationState::setAnimation(size_t trackIndex, const String &animationName, bool loop) {
	Animation *animation = _data->_skeletonData->findAnimation(animationName);
	assert(animation != NULL);
	return setAnimation(trackIndex, animation, loop);
}

TrackEntry *AnimationState::setAnimation(size_t trackIndex, Animation *animation, bool loop) {
	assert(animation != NULL);

	bool interrupt = true;
	TrackEntry *current = expandToIndex(trackIndex);
	if (current != NULL) {
		if (current->_nextTrackLast == -1) {
			// Don't mix from an entry that was never applied.
			_tracks[trackIndex] = current->_mixingFrom;
			_queue->interrupt(current);
			_queue->end(current);
			disposeNext(current);
			current = current->_mixingFrom;
			interrupt = false;
		} else {
			disposeNext(current);
		}
	}

	TrackEntry *entry = newTrackEntry(trackIndex, animation, loop, current);
	setCurrent(trackIndex, entry, interrupt);
	_queue->drain();

	return entry;
}

TrackEntry *AnimationState::addAnimation(size_t trackIndex, const String &animationName, bool loop, float delay) {
	Animation *animation = _data->_skeletonData->findAnimation(animationName);
	assert(animation != NULL);
	return addAnimation(trackIndex, animation, loop, delay);
}

TrackEntry *AnimationState::addAnimation(size_t trackIndex, Animation *animation, bool loop, float delay) {
	assert(animation != NULL);

	TrackEntry *last = expandToIndex(trackIndex);
	if (last != NULL) {
		while (last->_next != NULL)
			last = last->_next;
	}

	TrackEntry *entry = newTrackEntry(trackIndex, animation, loop, last);

	if (last == NULL) {
		setCurrent(trackIndex, entry, true);
		_queue->drain();
	} else {
		last->_next = entry;
		if (delay <= 0) {
			float duration = last->_animationEnd - last->_animationStart;
			if (duration != 0) {
				if (last->_loop) {
					delay += duration * (1 + (int) (last->_trackTime / duration));
				} else {
					delay += MathUtil::max(duration, last->_trackTime);
				}
				delay -= _data->getMix(last->_animation, animation);
			} else {
				delay = last->_trackTime;
			}
		}
	}

	entry->_delay = delay;
	return entry;
}

TrackEntry *AnimationState::setEmptyAnimation(size_t trackIndex, float mixDuration) {
	TrackEntry *entry = setAnimation(trackIndex, AnimationState::getEmptyAnimation(), false);
	entry->_mixDuration = mixDuration;
	entry->_trackEnd = mixDuration;
	return entry;
}

TrackEntry *AnimationState::addEmptyAnimation(size_t trackIndex, float mixDuration, float delay) {
	if (delay <= 0) {
		delay -= mixDuration;
	}

	TrackEntry *entry = addAnimation(trackIndex, AnimationState::getEmptyAnimation(), false, delay);
	entry->_mixDuration = mixDuration;
	entry->_trackEnd = mixDuration;
	return entry;
}

void AnimationState::setEmptyAnimations(float mixDuration) {
	bool oldDrainDisabled = _queue->_drainDisabled;
	_queue->_drainDisabled = true;
	for (size_t i = 0, n = _tracks.size(); i < n; ++i) {
		TrackEntry *current = _tracks[i];
		if (current != NULL) {
			setEmptyAnimation(i, mixDuration);
		}
	}
	_queue->_drainDisabled = oldDrainDisabled;
	_queue->drain();
}

TrackEntry *AnimationState::getCurrent(size_t trackIndex) {
	return trackIndex >= _tracks.size() ? NULL : _tracks[trackIndex];
}

AnimationStateData *AnimationState::getData() {
	return _data;
}

Vector<TrackEntry *> &AnimationState::getTracks() {
	return _tracks;
}

float AnimationState::getTimeScale() {
	return _timeScale;
}

void AnimationState::setTimeScale(float inValue) {
	_timeScale = inValue;
}

void AnimationState::setListener(AnimationStateListener inValue) {
	_listener = inValue;
	_listenerObject = NULL;
}

void AnimationState::setListener(AnimationStateListenerObject* inValue) {
	_listener = dummyOnAnimationEventFunc;
	_listenerObject = inValue;
}

void AnimationState::disableQueue() {
	_queue->_drainDisabled = true;
}
void AnimationState::enableQueue() {
	_queue->_drainDisabled = false;
}

Animation *AnimationState::getEmptyAnimation() {
	static Vector<Timeline *> timelines;
	static Animation ret(String("<empty>"), timelines, 0);
	return &ret;
}

void AnimationState::applyRotateTimeline(RotateTimeline *rotateTimeline, Skeleton &skeleton, float time, float alpha,
	MixBlend blend, Vector<float> &timelinesRotation, size_t i, bool firstFrame
) {
	if (firstFrame) timelinesRotation[i] = 0;

	if (alpha == 1) {
		rotateTimeline->apply(skeleton, 0, time, NULL, 1, blend, MixDirection_In);
		return;
	}

	Bone *bone = skeleton._bones[rotateTimeline->_boneIndex];
	if (!bone->isActive()) return;
	Vector<float>& frames = rotateTimeline->_frames;
	float r1, r2;
	if (time < frames[0]) {
		switch (blend) {
		case MixBlend_Setup:
			bone->_rotation = bone->_data._rotation;
		default:
			return;
		case MixBlend_First:
			r1 = bone->_rotation;
			r2 = bone->_data._rotation;
		}
	} else {
		r1 = blend == MixBlend_Setup ? bone->_data._rotation : bone->_rotation;
		if (time >= frames[frames.size() - RotateTimeline::ENTRIES]) {
			// Time is after last frame.
			r2 = bone->_data._rotation + frames[frames.size() + RotateTimeline::PREV_ROTATION];
		} else {
			// Interpolate between the previous frame and the current frame.
			int frame = Animation::binarySearch(frames, time, RotateTimeline::ENTRIES);
			float prevRotation = frames[frame + RotateTimeline::PREV_ROTATION];
			float frameTime = frames[frame];
			float percent = rotateTimeline->getCurvePercent((frame >> 1) - 1, 1 - (time - frameTime) / (frames[frame +
				RotateTimeline::PREV_TIME] - frameTime));
			r2 = frames[frame + RotateTimeline::ROTATION] - prevRotation;
			r2 -= (16384 - (int) (16384.499999999996 - r2 / 360)) * 360;
			r2 = prevRotation + r2 * percent + bone->_data._rotation;
			r2 -= (16384 - (int) (16384.499999999996 - r2 / 360)) * 360;
		}
	}

	// Mix between rotations using the direction of the shortest route on the first frame while detecting crosses.
	float total, diff = r2 - r1;
	diff -= (16384 - (int) (16384.499999999996 - diff / 360)) * 360;
	if (diff == 0) {
		total = timelinesRotation[i];
	} else {
		float lastTotal, lastDiff;
		if (firstFrame) {
			lastTotal = 0;
			lastDiff = diff;
		} else {
			lastTotal = timelinesRotation[i]; // Angle and direction of mix, including loops.
			lastDiff = timelinesRotation[i + 1]; // Difference between bones.
		}

		bool current = diff > 0, dir = lastTotal >= 0;
		// Detect cross at 0 (not 180).
		if (MathUtil::sign(lastDiff) != MathUtil::sign(diff) && MathUtil::abs(lastDiff) <= 90) {
			// A cross after a 360 rotation is a loop.
			if (MathUtil::abs(lastTotal) > 180) lastTotal += 360 * MathUtil::sign(lastTotal);
			dir = current;
		}

		total = diff + lastTotal - MathUtil::fmod(lastTotal, 360); // Store loops as part of lastTotal.
		if (dir != current) {
			total += 360 * MathUtil::sign(lastTotal);
		}
		timelinesRotation[i] = total;
	}
	timelinesRotation[i + 1] = diff;
	r1 += total * alpha;
	bone->_rotation = r1 - (16384 - (int) (16384.499999999996 - r1 / 360)) * 360;
}

bool AnimationState::updateMixingFrom(TrackEntry *to, float delta) {
	TrackEntry *from = to->_mixingFrom;
	if (from == NULL) {
		return true;
	}

	bool finished = updateMixingFrom(from, delta);

	from->_animationLast = from->_nextAnimationLast;
	from->_trackLast = from->_nextTrackLast;

	// Require mixTime > 0 to ensure the mixing from entry was applied at least once.
	if (to->_mixTime > 0 && to->_mixTime >= to->_mixDuration) {
		// Require totalAlpha == 0 to ensure mixing is complete, unless mixDuration == 0 (the transition is a single frame).
		if (from->_totalAlpha == 0 || to->_mixDuration == 0) {
			to->_mixingFrom = from->_mixingFrom;
			if (from->_mixingFrom != NULL) from->_mixingFrom->_mixingTo = to;
			to->_interruptAlpha = from->_interruptAlpha;
			_queue->end(from);
		}
		return finished;
	}

	from->_trackTime += delta * from->_timeScale;
	to->_mixTime += delta;

	return false;
}

float AnimationState::applyMixingFrom(TrackEntry *to, Skeleton &skeleton, MixBlend blend) {
	TrackEntry *from = to->_mixingFrom;
	if (from->_mixingFrom != NULL) applyMixingFrom(from, skeleton, blend);

	float mix;
	if (to->_mixDuration == 0) {
		// Single frame mix to undo mixingFrom changes.
		mix = 1;
		if (blend == MixBlend_First) blend = MixBlend_Setup;
	} else {
		mix = to->_mixTime / to->_mixDuration;
		if (mix > 1) {
			mix = 1;
		}
		if (blend != MixBlend_First) blend = from->_mixBlend;
	}

	Vector<Event *> *eventBuffer = mix < from->_eventThreshold ? &_events : NULL;
	bool attachments = mix < from->_attachmentThreshold, drawOrder = mix < from->_drawOrderThreshold;
	float animationLast = from->_animationLast, animationTime = from->getAnimationTime();
	Vector<Timeline *> &timelines = from->_animation->_timelines;
	size_t timelineCount = timelines.size();
	float alphaHold = from->_alpha * to->_interruptAlpha, alphaMix = alphaHold * (1 - mix);

	if (blend == MixBlend_Add) {
		for (size_t i = 0; i < timelineCount; i++)
			timelines[i]->apply(skeleton, animationLast, animationTime, eventBuffer, alphaMix, blend, MixDirection_Out);
	} else {
		Vector<int> &timelineMode = from->_timelineMode;
		Vector<TrackEntry *> &timelineHoldMix = from->_timelineHoldMix;

		bool firstFrame = from->_timelinesRotation.size() == 0;
		if (firstFrame) from->_timelinesRotation.setSize(timelines.size() << 1, 0);

		Vector<float> &timelinesRotation = from->_timelinesRotation;

		from->_totalAlpha = 0;
		for (size_t i = 0; i < timelineCount; i++) {
			Timeline *timeline = timelines[i];
			MixDirection direction = MixDirection_Out;
			MixBlend timelineBlend;
			float alpha;
			switch (timelineMode[i] & (NotLast - 1)) {
				case Subsequent:
					timelineBlend = blend;
					if (!attachments && (timeline->getRTTI().isExactly(AttachmentTimeline::rtti))) {
						if ((timelineMode[i] & NotLast) == NotLast) continue;
						timelineBlend = MixBlend_Setup;
					}
					if (!drawOrder && (timeline->getRTTI().isExactly(DrawOrderTimeline::rtti))) continue;
					alpha = alphaMix;
					break;
				case First:
					timelineBlend = MixBlend_Setup;
					alpha = alphaMix;
					break;
				case Hold:
					timelineBlend = MixBlend_Setup;
					alpha = alphaHold;
					break;
				default:
					timelineBlend = MixBlend_Setup;
					TrackEntry *holdMix = timelineHoldMix[i];
					alpha = alphaHold * MathUtil::max(0.0f, 1.0f - holdMix->_mixTime / holdMix->_mixDuration);
					break;
			}
			from->_totalAlpha += alpha;
			if ((timeline->getRTTI().isExactly(RotateTimeline::rtti))) {
				applyRotateTimeline((RotateTimeline*)timeline, skeleton, animationTime, alpha, timelineBlend, timelinesRotation, i << 1, firstFrame);
			} else {
				if (timelineBlend == MixBlend_Setup) {
					if (timeline->getRTTI().isExactly(AttachmentTimeline::rtti)) {
						if (attachments || (timelineMode[i] & NotLast) == NotLast) direction = MixDirection_In;
					} else if (timeline->getRTTI().isExactly(DrawOrderTimeline::rtti)) {
						if (drawOrder) direction = MixDirection_In;
					}
				}
				timeline->apply(skeleton, animationLast, animationTime, eventBuffer, alpha, timelineBlend, direction);
			}
		}
	}

	if (to->_mixDuration > 0) {
		queueEvents(from, animationTime);
	}

	_events.clear();
	from->_nextAnimationLast = animationTime;
	from->_nextTrackLast = from->_trackTime;

	return mix;
}

void AnimationState::queueEvents(TrackEntry *entry, float animationTime) {
	float animationStart = entry->_animationStart, animationEnd = entry->_animationEnd;
	float duration = animationEnd - animationStart;
	float trackLastWrapped = MathUtil::fmod(entry->_trackLast, duration);

	// Queue events before complete.
	size_t i = 0, n = _events.size();
	for (; i < n; ++i) {
		Event *e = _events[i];
		if (e->_time < trackLastWrapped) break;
		if (e->_time > animationEnd) continue; // Discard events outside animation start/end.
		_queue->event(entry, e);
	}

	// Queue complete if completed a loop iteration or the animation.
	bool complete = false;
	if (entry->_loop)
		complete = duration == 0 || (trackLastWrapped > MathUtil::fmod(entry->_trackTime, duration));
	else
		complete = animationTime >= animationEnd && entry->_animationLast < animationEnd;
	if (complete) _queue->complete(entry);

	// Queue events after complete.
	for (; i < n; ++i) {
		Event *e = _events[i];
		if (e->_time < animationStart) continue; // Discard events outside animation start/end.
		_queue->event(entry, _events[i]);
	}
}

void AnimationState::setCurrent(size_t index, TrackEntry *current, bool interrupt) {
	TrackEntry *from = expandToIndex(index);
	_tracks[index] = current;

	if (from != NULL) {
		if (interrupt) _queue->interrupt(from);

		current->_mixingFrom = from;
		from->_mixingTo = current;
		current->_mixTime = 0;

		// Store interrupted mix percentage.
		if (from->_mixingFrom != NULL && from->_mixDuration > 0) {
			current->_interruptAlpha *= MathUtil::min(1.0f, from->_mixTime / from->_mixDuration);
		}

		from->_timelinesRotation.clear(); // Reset rotation for mixing out, in case entry was mixed in.
	}

	_queue->start(current); // triggers animationsChanged
}

TrackEntry *AnimationState::expandToIndex(size_t index) {
	if (index < _tracks.size()) return _tracks[index];
	while (index >= _tracks.size())
		_tracks.add(NULL);
	return NULL;
}

TrackEntry *AnimationState::newTrackEntry(size_t trackIndex, Animation *animation, bool loop, TrackEntry *last) {
	TrackEntry *entryP = _trackEntryPool.obtain(); // Pooling
	TrackEntry &entry = *entryP;

	entry._trackIndex = trackIndex;
	entry._animation = animation;
	entry._loop = loop;
	entry._holdPrevious = 0;

	entry._eventThreshold = 0;
	entry._attachmentThreshold = 0;
	entry._drawOrderThreshold = 0;

	entry._animationStart = 0;
	entry._animationEnd = animation->getDuration();
	entry._animationLast = -1;
	entry._nextAnimationLast = -1;

	entry._delay = 0;
	entry._trackTime = 0;
	entry._trackLast = -1;
	entry._nextTrackLast = -1; // nextTrackLast == -1 signifies a TrackEntry that wasn't applied yet.
	entry._trackEnd = FLT_MAX; // loop ? float.MaxValue : animation.Duration;
	entry._timeScale = 1;

	entry._alpha = 1;
	entry._interruptAlpha = 1;
	entry._mixTime = 0;
	entry._mixDuration = (last == NULL) ? 0 : _data->getMix(last->_animation, animation);

	return entryP;
}

void AnimationState::disposeNext(TrackEntry *entry) {
	TrackEntry *next = entry->_next;
	while (next != NULL) {
		_queue->dispose(next);
		next = next->_next;
	}
	entry->_next = NULL;
}

void AnimationState::animationsChanged() {
	_animationsChanged = false;

	_propertyIDs.clear();

	for (size_t i = 0, n = _tracks.size(); i < n; ++i) {
		TrackEntry *entry = _tracks[i];
		if (!entry) continue;

		while (entry->_mixingFrom != NULL)
			entry = entry->_mixingFrom;

		do {
			if (entry->_mixingTo == NULL || entry->_mixBlend != MixBlend_Add) computeHold(entry);
			entry = entry->_mixingTo;
		} while (entry != NULL);
	}

	_propertyIDs.clear();
	for (int i = (int)_tracks.size() - 1; i >= 0; i--) {
		TrackEntry *entry = _tracks[i];
		while (entry) {
			computeNotLast(entry);
			entry = entry->_mixingFrom;
		}
	}
}

void AnimationState::computeHold(TrackEntry *entry) {
	TrackEntry* to = entry->_mixingTo;
	Vector<Timeline *> &timelines = entry->_animation->_timelines;
	size_t timelinesCount = timelines.size();
	Vector<int> &timelineMode = entry->_timelineMode;
	timelineMode.setSize(timelinesCount, 0);
	Vector<TrackEntry *> &timelineHoldMix = entry->_timelineHoldMix;
	timelineHoldMix.setSize(timelinesCount, 0);

	if (to != NULL && to->_holdPrevious) {
		for (size_t i = 0; i < timelinesCount; i++) {
			int id = timelines[i]->getPropertyId();
			if (!_propertyIDs.containsKey(id)) _propertyIDs.put(id, true);
			timelineMode[i] = Hold;
		}
		return;
	}

	// outer:
	size_t i = 0;
	continue_outer:
	for (; i < timelinesCount; ++i) {
		Timeline *timeline = timelines[i];
		int id = timeline->getPropertyId();
		if (_propertyIDs.containsKey(id)) {
			timelineMode[i] = Subsequent;
		} else {
			_propertyIDs.put(id, true);

			if (to == NULL || timeline->getRTTI().isExactly(AttachmentTimeline::rtti) ||
					timeline->getRTTI().isExactly(DrawOrderTimeline::rtti) ||
					timeline->getRTTI().isExactly(EventTimeline::rtti) || !to->_animation->hasTimeline(id)) {
				timelineMode[i] = First;
			} else {
				for (TrackEntry *next = to->_mixingTo; next != NULL; next = next->_mixingTo) {
					if (next->_animation->hasTimeline(id)) continue;
					if (entry->_mixDuration > 0) {
						timelineMode[i] = HoldMix;
						timelineHoldMix[i] = entry;
						i++;
						goto continue_outer; // continue outer;
					}
					break;
				}
				timelineMode[i] = Hold;
			}
		}
	}
}

void AnimationState::computeNotLast(TrackEntry *entry) {
	Vector<Timeline *> &timelines = entry->_animation->_timelines;
	size_t timelinesCount = timelines.size();
	Vector<int> &timelineMode = entry->_timelineMode;

	for (size_t i = 0; i < timelinesCount; i++) {
		if (timelines[i]->getRTTI().isExactly(AttachmentTimeline::rtti)) {
			AttachmentTimeline *timeline = static_cast<AttachmentTimeline *>(timelines[i]);
			if (!_propertyIDs.containsKey(timeline->getSlotIndex()))
				_propertyIDs.put(timeline->getSlotIndex(), true);
			else
				timelineMode[i] |= NotLast;
		}
	}
}
