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

#include "spine/SkeletonAnimation.h"
#include "spine/spine-cocos2dx.h"
#include "spine/extension.h"
#include <algorithm>

USING_NS_CC;
using std::min;
using std::max;
using std::vector;

namespace spine {

typedef struct _TrackEntryListeners {
    StartListener startListener;
    InterruptListener interruptListener;
    EndListener endListener;
    DisposeListener disposeListener;
    CompleteListener completeListener;
    EventListener eventListener;
} _TrackEntryListeners;
    
void animationCallback (spAnimationState* state, spEventType type, spTrackEntry* entry, spEvent* event) {
	((SkeletonAnimation*)state->rendererObject)->onAnimationStateEvent(entry, type, event);
}

void trackEntryCallback (spAnimationState* state, spEventType type, spTrackEntry* entry, spEvent* event) {
	((SkeletonAnimation*)state->rendererObject)->onTrackEntryEvent(entry, type, event);
    if (type == SP_ANIMATION_DISPOSE)
        if (entry->rendererObject) delete (spine::_TrackEntryListeners*)entry->rendererObject;
}

static _TrackEntryListeners* getListeners (spTrackEntry* entry) {
	if (!entry->rendererObject) {
		entry->rendererObject = new spine::_TrackEntryListeners();
		entry->listener = trackEntryCallback;
	}
	return (_TrackEntryListeners*)entry->rendererObject;
}
    
//

SkeletonAnimation* SkeletonAnimation::createWithData (spSkeletonData* skeletonData, bool ownsSkeletonData) {
	SkeletonAnimation* node = new SkeletonAnimation();
	node->initWithData(skeletonData, ownsSkeletonData);
	node->autorelease();
	return node;
}

SkeletonAnimation* SkeletonAnimation::createWithJsonFile (const std::string& skeletonJsonFile, spAtlas* atlas, float scale) {
	SkeletonAnimation* node = new SkeletonAnimation();
	node->initWithJsonFile(skeletonJsonFile, atlas, scale);
	node->autorelease();
	return node;
}

SkeletonAnimation* SkeletonAnimation::createWithJsonFile (const std::string& skeletonJsonFile, const std::string& atlasFile, float scale) {
	SkeletonAnimation* node = new SkeletonAnimation();
	spAtlas* atlas = spAtlas_createFromFile(atlasFile.c_str(), 0);
	node->initWithJsonFile(skeletonJsonFile, atlas, scale);
	node->autorelease();
	return node;
}

SkeletonAnimation* SkeletonAnimation::createWithBinaryFile (const std::string& skeletonBinaryFile, spAtlas* atlas, float scale) {
	SkeletonAnimation* node = new SkeletonAnimation();
	node->initWithBinaryFile(skeletonBinaryFile, atlas, scale);
	node->autorelease();
	return node;
}

SkeletonAnimation* SkeletonAnimation::createWithBinaryFile (const std::string& skeletonBinaryFile, const std::string& atlasFile, float scale) {
	SkeletonAnimation* node = new SkeletonAnimation();
	spAtlas* atlas = spAtlas_createFromFile(atlasFile.c_str(), 0);
	node->initWithBinaryFile(skeletonBinaryFile, atlas, scale);
	node->autorelease();
	return node;
}


void SkeletonAnimation::initialize () {
	super::initialize();

	_ownsAnimationStateData = true;
	_state = spAnimationState_create(spAnimationStateData_create(_skeleton->data));
	_state->rendererObject = this;
	_state->listener = animationCallback;
}

SkeletonAnimation::SkeletonAnimation ()
		: SkeletonRenderer() {
}

SkeletonAnimation::~SkeletonAnimation () {
	if (_ownsAnimationStateData) spAnimationStateData_dispose(_state->data);
	spAnimationState_dispose(_state);
}

void SkeletonAnimation::update (float deltaTime) {
	super::update(deltaTime);

	deltaTime *= _timeScale;
	spAnimationState_update(_state, deltaTime);
	spAnimationState_apply(_state, _skeleton);
	spSkeleton_updateWorldTransform(_skeleton);
}

void SkeletonAnimation::setAnimationStateData (spAnimationStateData* stateData) {
	CCASSERT(stateData, "stateData cannot be null.");

    if (_ownsAnimationStateData) spAnimationStateData_dispose(_state->data);
    spAnimationState_dispose(_state);

	_ownsAnimationStateData = false;
	_state = spAnimationState_create(stateData);
	_state->rendererObject = this;
	_state->listener = animationCallback;
}

void SkeletonAnimation::setMix (const std::string& fromAnimation, const std::string& toAnimation, float duration) {
	spAnimationStateData_setMixByName(_state->data, fromAnimation.c_str(), toAnimation.c_str(), duration);
}

spTrackEntry* SkeletonAnimation::setAnimation (int trackIndex, const std::string& name, bool loop) {
	spAnimation* animation = spSkeletonData_findAnimation(_skeleton->data, name.c_str());
	if (!animation) {
		log("Spine: Animation not found: %s", name.c_str());
		return 0;
	}
	return spAnimationState_setAnimation(_state, trackIndex, animation, loop);
}

spTrackEntry* SkeletonAnimation::addAnimation (int trackIndex, const std::string& name, bool loop, float delay) {
	spAnimation* animation = spSkeletonData_findAnimation(_skeleton->data, name.c_str());
	if (!animation) {
		log("Spine: Animation not found: %s", name.c_str());
		return 0;
	}
	return spAnimationState_addAnimation(_state, trackIndex, animation, loop, delay);
}
	
spTrackEntry* SkeletonAnimation::setEmptyAnimation (int trackIndex, float mixDuration) {
	return spAnimationState_setEmptyAnimation(_state, trackIndex, mixDuration);
}

void SkeletonAnimation::setEmptyAnimations (float mixDuration) {
	spAnimationState_setEmptyAnimations(_state, mixDuration);
}

spTrackEntry* SkeletonAnimation::addEmptyAnimation (int trackIndex, float mixDuration, float delay) {
	return spAnimationState_addEmptyAnimation(_state, trackIndex, mixDuration, delay);
}

spAnimation* SkeletonAnimation::findAnimation(const std::string& name) const {
	return spSkeletonData_findAnimation(_skeleton->data, name.c_str());
}

spTrackEntry* SkeletonAnimation::getCurrent (int trackIndex) { 
	return spAnimationState_getCurrent(_state, trackIndex);
}

void SkeletonAnimation::clearTracks () {
	spAnimationState_clearTracks(_state);
}

void SkeletonAnimation::clearTrack (int trackIndex) {
	spAnimationState_clearTrack(_state, trackIndex);
}

void SkeletonAnimation::onAnimationStateEvent (spTrackEntry* entry, spEventType type, spEvent* event) {
	switch (type) {
	case SP_ANIMATION_START:
		if (_startListener) _startListener(entry);
		break;
    case SP_ANIMATION_INTERRUPT:
        if (_interruptListener) _interruptListener(entry);
        break;
	case SP_ANIMATION_END:
		if (_endListener) _endListener(entry);
		break;
    case SP_ANIMATION_DISPOSE:
        if (_disposeListener) _disposeListener(entry);
        break;
	case SP_ANIMATION_COMPLETE:
		if (_completeListener) _completeListener(entry);
		break;
	case SP_ANIMATION_EVENT:
		if (_eventListener) _eventListener(entry, event);
		break;
	}
}

void SkeletonAnimation::onTrackEntryEvent (spTrackEntry* entry, spEventType type, spEvent* event) {
	if (!entry->rendererObject) return;
	_TrackEntryListeners* listeners = (_TrackEntryListeners*)entry->rendererObject;
	switch (type) {
	case SP_ANIMATION_START:
		if (listeners->startListener) listeners->startListener(entry);
		break;
    case SP_ANIMATION_INTERRUPT:
        if (listeners->interruptListener) listeners->interruptListener(entry);
        break;
	case SP_ANIMATION_END:
		if (listeners->endListener) listeners->endListener(entry);
		break;
    case SP_ANIMATION_DISPOSE:
        if (listeners->disposeListener) listeners->disposeListener(entry);
        break;
	case SP_ANIMATION_COMPLETE:
		if (listeners->completeListener) listeners->completeListener(entry);
		break;
	case SP_ANIMATION_EVENT:
		if (listeners->eventListener) listeners->eventListener(entry, event);
		break;
	}
}

void SkeletonAnimation::setStartListener (const StartListener& listener) {
	_startListener = listener;
}
    
void SkeletonAnimation::setInterruptListener (const InterruptListener& listener) {
    _interruptListener = listener;
}
    
void SkeletonAnimation::setEndListener (const EndListener& listener) {
	_endListener = listener;
}
    
void SkeletonAnimation::setDisposeListener (const DisposeListener& listener) {
    _disposeListener = listener;
}

void SkeletonAnimation::setCompleteListener (const CompleteListener& listener) {
	_completeListener = listener;
}

void SkeletonAnimation::setEventListener (const EventListener& listener) {
	_eventListener = listener;
}

void SkeletonAnimation::setTrackStartListener (spTrackEntry* entry, const StartListener& listener) {
	getListeners(entry)->startListener = listener;
}
    
void SkeletonAnimation::setTrackInterruptListener (spTrackEntry* entry, const InterruptListener& listener) {
    getListeners(entry)->interruptListener = listener;
}

void SkeletonAnimation::setTrackEndListener (spTrackEntry* entry, const EndListener& listener) {
	getListeners(entry)->endListener = listener;
}
    
void SkeletonAnimation::setTrackDisposeListener (spTrackEntry* entry, const DisposeListener& listener) {
    getListeners(entry)->disposeListener = listener;
}

void SkeletonAnimation::setTrackCompleteListener (spTrackEntry* entry, const CompleteListener& listener) {
	getListeners(entry)->completeListener = listener;
}

void SkeletonAnimation::setTrackEventListener (spTrackEntry* entry, const EventListener& listener) {
	getListeners(entry)->eventListener = listener;
}

spAnimationState* SkeletonAnimation::getState() const {
	return _state;
}

}
