/******************************************************************************
 * Spine Runtimes Software License
 * Version 2.1
 * 
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 * 
 * You are granted a perpetual, non-exclusive, non-sublicensable and
 * non-transferable license to install, execute and perform the Spine Runtimes
 * Software (the "Software") solely for internal use. Without the written
 * permission of Esoteric Software (typically granted by licensing Spine), you
 * may not (a) modify, translate, adapt or otherwise create derivative works,
 * improvements of the Software or develop new applications using the Software
 * or (b) remove, delete, alter or obscure any trademarks or any copyright,
 * trademark, patent or other intellectual property or proprietary rights
 * notices on or in the Software, including any copy thereof. Redistributions
 * in binary or source form must include this license and terms.
 * 
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef SPINE_SKELETONANIMATION_H_
#define SPINE_SKELETONANIMATION_H_

#include <spine/spine.h>
#include <spine/SkeletonRenderer.h>
#include "cocos2d.h"

namespace spine {

typedef std::function<void(int trackIndex)> StartListener;
typedef std::function<void(int trackIndex)> EndListener;
typedef std::function<void(int trackIndex, int loopCount)> CompleteListener;
typedef std::function<void(int trackIndex, spEvent* event)> EventListener;

/** Draws an animated skeleton, providing an AnimationState for applying one or more animations and queuing animations to be
  * played later. */
class SkeletonAnimation: public SkeletonRenderer {
public:
	static SkeletonAnimation* createWithData (spSkeletonData* skeletonData);
	static SkeletonAnimation* createWithFile (const std::string& skeletonDataFile, spAtlas* atlas, float scale = 1);
	static SkeletonAnimation* createWithFile (const std::string& skeletonDataFile, const std::string& atlasFile, float scale = 1);

	virtual void update (float deltaTime);

	void setAnimationStateData (spAnimationStateData* stateData);
	void setMix (const std::string& fromAnimation, const std::string& toAnimation, float duration);

	spTrackEntry* setAnimation (int trackIndex, const std::string& name, bool loop);
	spTrackEntry* addAnimation (int trackIndex, const std::string& name, bool loop, float delay = 0);
	spTrackEntry* getCurrent (int trackIndex = 0);
	void clearTracks ();
	void clearTrack (int trackIndex = 0);

	void setStartListener (const StartListener& listener);
	void setEndListener (const EndListener& listener);
	void setCompleteListener (const CompleteListener& listener);
	void setEventListener (const EventListener& listener);

	void setTrackStartListener (spTrackEntry* entry, const StartListener& listener);
	void setTrackEndListener (spTrackEntry* entry, const EndListener& listener);
	void setTrackCompleteListener (spTrackEntry* entry, const CompleteListener& listener);
	void setTrackEventListener (spTrackEntry* entry, const EventListener& listener);

	virtual void onAnimationStateEvent (int trackIndex, spEventType type, spEvent* event, int loopCount);
	virtual void onTrackEntryEvent (int trackIndex, spEventType type, spEvent* event, int loopCount);

	spAnimationState* getState() const;

CC_CONSTRUCTOR_ACCESS:
	SkeletonAnimation ();
	SkeletonAnimation (spSkeletonData* skeletonData);
	SkeletonAnimation (const std::string&skeletonDataFile, spAtlas* atlas, float scale = 1);
	SkeletonAnimation (const std::string& skeletonDataFile, const std::string& atlasFile, float scale = 1);
	virtual ~SkeletonAnimation ();
	void initialize ();

protected:
	spAnimationState* _state;

	bool _ownsAnimationStateData;

	StartListener _startListener;
	EndListener _endListener;
	CompleteListener _completeListener;
	EventListener _eventListener;

private:
	typedef SkeletonRenderer super;
};

}

#endif /* SPINE_SKELETONANIMATION_H_ */
