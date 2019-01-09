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

#ifndef Spine_AnimationState_h
#define Spine_AnimationState_h

#include <spine/Vector.h>
#include <spine/Pool.h>
#include <spine/MixBlend.h>
#include <spine/SpineObject.h>
#include <spine/SpineString.h>
#include <spine/HasRendererObject.h>

namespace spine {
    enum EventType {
        EventType_Start,
        EventType_Interrupt,
        EventType_End,
        EventType_Complete,
        EventType_Dispose,
        EventType_Event
    };
    
    class AnimationState;
    class TrackEntry;

    class Animation;
    class Event;
    class AnimationStateData;
    class Skeleton;
    class RotateTimeline;
    
    typedef void (*AnimationStateListener) (AnimationState* state, EventType type, TrackEntry* entry, Event* event);
    
    /// State for the playback of an animation
    class SP_API TrackEntry : public SpineObject, public HasRendererObject {
        friend class EventQueue;
        friend class AnimationState;
        
    public:
        TrackEntry();

        virtual ~TrackEntry();
        
        /// The index of the track where this entry is either current or queued.
        int getTrackIndex();
        
        /// The animation to apply for this track entry.
        Animation* getAnimation();
        
        ///
        /// If true, the animation will repeat. If false, it will not, instead its last frame is applied if played beyond its duration.
        bool getLoop();
        void setLoop(bool inValue);

        ///
        /// If true, when mixing from the previous animation to this animation, the previous animation is applied as normal instead
        /// of being mixed out.
        ///
        /// When mixing between animations that key the same property, if a lower track also keys that property then the value will
        /// briefly dip toward the lower track value during the mix. This happens because the first animation mixes from 100% to 0%
        /// while the second animation mixes from 0% to 100%. Setting holdPrevious to true applies the first animation
        /// at 100% during the mix so the lower track value is overwritten. Such dipping does not occur on the lowest track which
        /// keys the property, only when a higher track also keys the property.
        ///
        /// Snapping will occur if holdPrevious is true and this animation does not key all the same properties as the
        /// previous animation.
        bool getHoldPrevious();
        void setHoldPrevious(bool inValue);
        
        ///
        /// Seconds to postpone playing the animation. When a track entry is the current track entry, delay postpones incrementing
        /// the track time. When a track entry is queued, delay is the time from the start of the previous animation to when the
        /// track entry will become the current track entry.
        float getDelay();
        void setDelay(float inValue);
        
        ///
        /// Current time in seconds this track entry has been the current track entry. The track time determines
        /// TrackEntry.AnimationTime. The track time can be set to start the animation at a time other than 0, without affecting looping.
        float getTrackTime();
        void setTrackTime(float inValue);
        
        ///
        /// The track time in seconds when this animation will be removed from the track. Defaults to the animation duration for
        /// non-looping animations and to int.MaxValue for looping animations. If the track end time is reached and no
        /// other animations are queued for playback, and mixing from any previous animations is complete, properties keyed by the animation,
        /// are set to the setup pose and the track is cleared.
        ///
        /// It may be desired to use AnimationState.addEmptyAnimation(int, float, float) to mix the properties back to the
        /// setup pose over time, rather than have it happen instantly.
        ///
        float getTrackEnd();
        void setTrackEnd(float inValue);
        
        ///
        /// Seconds when this animation starts, both initially and after looping. Defaults to 0.
        ///
        /// When changing the animation start time, it often makes sense to set TrackEntry.AnimationLast to the same value to
        /// prevent timeline keys before the start time from triggering.
        ///
        float getAnimationStart();
        void setAnimationStart(float inValue);
        
        ///
        /// Seconds for the last frame of this animation. Non-looping animations won't play past this time. Looping animations will
        /// loop back to TrackEntry.AnimationStart at this time. Defaults to the animation duration.
        float getAnimationEnd();
        void setAnimationEnd(float inValue);
        
        ///
        /// The time in seconds this animation was last applied. Some timelines use this for one-time triggers. Eg, when this
        /// animation is applied, event timelines will fire all events between the animation last time (exclusive) and animation time
        /// (inclusive). Defaults to -1 to ensure triggers on frame 0 happen the first time this animation is applied.
        float getAnimationLast();
        void setAnimationLast(float inValue);
        
        ///
        /// Uses TrackEntry.TrackTime to compute the animation time between TrackEntry.AnimationStart. and
        /// TrackEntry.AnimationEnd. When the track time is 0, the animation time is equal to the animation start time.
        ///
        float getAnimationTime();
        
        ///
        /// Multiplier for the delta time when the animation state is updated, causing time for this animation to play slower or
        /// faster. Defaults to 1.
        ///
        float getTimeScale();
        void setTimeScale(float inValue);
        
        ///
        /// Values less than 1 mix this animation with the last skeleton pose. Defaults to 1, which overwrites the last skeleton pose with
        /// this animation.
        ///
        /// Typically track 0 is used to completely pose the skeleton, then alpha can be used on higher tracks. It doesn't make sense
        /// to use alpha on track 0 if the skeleton pose is from the last frame render.
        ///
        float getAlpha();
        void setAlpha(float inValue);
        
        ///
        /// When the mix percentage (mix time / mix duration) is less than the event threshold, event timelines for the animation
        /// being mixed out will be applied. Defaults to 0, so event timelines are not applied for an animation being mixed out.
        float getEventThreshold();
        void setEventThreshold(float inValue);
        
        ///
        /// When the mix percentage (mix time / mix duration) is less than the attachment threshold, attachment timelines for the
        /// animation being mixed out will be applied. Defaults to 0, so attachment timelines are not applied for an animation being
        /// mixed out.
        float getAttachmentThreshold();
        void setAttachmentThreshold(float inValue);
        
        ///
        /// When the mix percentage (mix time / mix duration) is less than the draw order threshold, draw order timelines for the
        /// animation being mixed out will be applied. Defaults to 0, so draw order timelines are not applied for an animation being
        /// mixed out.
        ///
        float getDrawOrderThreshold();
        void setDrawOrderThreshold(float inValue);
        
        ///
        /// The animation queued to start after this animation, or NULL.
        TrackEntry* getNext();
        
        ///
        /// Returns true if at least one loop has been completed.
        bool isComplete();
        
        ///
        /// Seconds from 0 to the mix duration when mixing from the previous animation to this animation. May be slightly more than
        /// TrackEntry.MixDuration when the mix is complete.
        float getMixTime();
        void setMixTime(float inValue);
        
        ///
        /// Seconds for mixing from the previous animation to this animation. Defaults to the value provided by
        /// AnimationStateData based on the animation before this animation (if any).
        ///
        /// The mix duration can be set manually rather than use the value from AnimationStateData.GetMix.
        /// In that case, the mixDuration must be set before AnimationState.update(float) is next called.
        ///
        /// When using AnimationState::addAnimation(int, Animation, bool, float) with a delay
        /// less than or equal to 0, note the Delay is set using the mix duration from the AnimationStateData
        ///
        ///
        ///
        float getMixDuration();
        void setMixDuration(float inValue);


        MixBlend getMixBlend();
        void setMixBlend(MixBlend blend);
        
        ///
        /// The track entry for the previous animation when mixing from the previous animation to this animation, or NULL if no
        /// mixing is currently occuring. When mixing from multiple animations, MixingFrom makes up a double linked list with MixingTo.
        TrackEntry* getMixingFrom();

        ///
        /// The track entry for the next animation when mixing from this animation, or NULL if no mixing is currently occuring.
        /// When mixing from multiple animations, MixingTo makes up a double linked list with MixingFrom.
        TrackEntry* getMixingTo();
        
        ///
        /// Resets the rotation directions for mixing this entry's rotate timelines. This can be useful to avoid bones rotating the
        /// long way around when using alpha and starting animations on other tracks.
        ///
        /// Mixing involves finding a rotation between two others, which has two possible solutions: the short way or the long way around.
        /// The two rotations likely change over time, so which direction is the short or long way also changes.
        /// If the short way was always chosen, bones would flip to the other side when that direction became the long way.
        /// TrackEntry chooses the short way the first time it is applied and remembers that direction.
        void resetRotationDirections();
        
        void setListener(AnimationStateListener listener);

    private:
        Animation* _animation;
        
        TrackEntry* _next;
        TrackEntry* _mixingFrom;
        TrackEntry* _mixingTo;
        int _trackIndex;

        bool _loop, _holdPrevious;
        float _eventThreshold, _attachmentThreshold, _drawOrderThreshold;
        float _animationStart, _animationEnd, _animationLast, _nextAnimationLast;
        float _delay, _trackTime, _trackLast, _nextTrackLast, _trackEnd, _timeScale;
        float _alpha, _mixTime, _mixDuration, _interruptAlpha, _totalAlpha;
        MixBlend _mixBlend;
        Vector<int> _timelineMode;
        Vector<TrackEntry*> _timelineHoldMix;
        Vector<float> _timelinesRotation;
        AnimationStateListener _listener;
        
        void reset();
    };
    
    class SP_API EventQueueEntry : public SpineObject {
        friend class EventQueue;
        
    public:
        EventType _type;
        TrackEntry* _entry;
        Event* _event;
        
        EventQueueEntry(EventType eventType, TrackEntry* trackEntry, Event* event = NULL);
    };
    
    class SP_API EventQueue : public SpineObject {
        friend class AnimationState;
        
    private:
        Vector<EventQueueEntry> _eventQueueEntries;
        AnimationState& _state;
        Pool<TrackEntry>& _trackEntryPool;
        bool _drainDisabled;
        
        static EventQueue* newEventQueue(AnimationState& state, Pool<TrackEntry>& trackEntryPool);

        static EventQueueEntry newEventQueueEntry(EventType eventType, TrackEntry* entry, Event* event = NULL);
        
        EventQueue(AnimationState& state, Pool<TrackEntry>& trackEntryPool);
        
        ~EventQueue();
        
        void start(TrackEntry* entry);

        void interrupt(TrackEntry* entry);

        void end(TrackEntry* entry);

        void dispose(TrackEntry* entry);

        void complete(TrackEntry* entry);

        void event(TrackEntry* entry, Event* event);

        /// Raises all events in the queue and drains the queue.
        void drain();
    };
    
    class SP_API AnimationState : public SpineObject, public HasRendererObject {
        friend class TrackEntry;
        friend class EventQueue;
        
    public:
        explicit AnimationState(AnimationStateData* data);
        
        ~AnimationState();
        
        ///
        /// Increments the track entry times, setting queued animations as current if needed
        /// @param delta delta time
        void update(float delta);
        
        ///
        /// Poses the skeleton using the track entry animations. There are no side effects other than invoking listeners, so the
        /// animation state can be applied to multiple skeletons to pose them identically.
        bool apply(Skeleton& skeleton);
        
        ///
        /// Removes all animations from all tracks, leaving skeletons in their previous pose.
        /// It may be desired to use AnimationState.setEmptyAnimations(float) to mix the skeletons back to the setup pose,
        /// rather than leaving them in their previous pose.
        void clearTracks();
        
        ///
        /// Removes all animations from the tracks, leaving skeletons in their previous pose.
        /// It may be desired to use AnimationState.setEmptyAnimations(float) to mix the skeletons back to the setup pose,
        /// rather than leaving them in their previous pose.
        void clearTrack(size_t trackIndex);
        
        /// Sets an animation by name. setAnimation(int, Animation, bool)
        TrackEntry* setAnimation(size_t trackIndex, const String& animationName, bool loop);
        
        /// Sets the current animation for a track, discarding any queued animations.
        /// @param loop If true, the animation will repeat.
        /// If false, it will not, instead its last frame is applied if played beyond its duration.
        /// In either case TrackEntry.TrackEnd determines when the track is cleared.
        /// @return
        /// A track entry to allow further customization of animation playback. References to the track entry must not be kept
        /// after AnimationState.Dispose.
        TrackEntry* setAnimation(size_t trackIndex, Animation* animation, bool loop);
        
        /// Queues an animation by name.
        /// addAnimation(int, Animation, bool, float)
        TrackEntry* addAnimation(size_t trackIndex, const String& animationName, bool loop, float delay);
        
        /// Adds an animation to be played delay seconds after the current or last queued animation
        /// for a track. If the track is empty, it is equivalent to calling setAnimation.
        /// @param delay
        /// Seconds to begin this animation after the start of the previous animation. May be &lt;= 0 to use the animation
        /// duration of the previous track minus any mix duration plus the negative delay.
        ///
        /// @return A track entry to allow further customization of animation playback. References to the track entry must not be kept
        /// after AnimationState.Dispose
        TrackEntry* addAnimation(size_t trackIndex, Animation* animation, bool loop, float delay);
        
        ///
        /// Sets an empty animation for a track, discarding any queued animations, and mixes to it over the specified mix duration.
        TrackEntry* setEmptyAnimation(size_t trackIndex, float mixDuration);
        
        ///
        /// Adds an empty animation to be played after the current or last queued animation for a track, and mixes to it over the
        /// specified mix duration.
        /// @return
        /// A track entry to allow further customization of animation playback. References to the track entry must not be kept after AnimationState.Dispose.
        ///
        /// @param trackIndex Track number.
        /// @param mixDuration Mix duration.
        /// @param delay Seconds to begin this animation after the start of the previous animation. May be &lt;= 0 to use the animation
        /// duration of the previous track minus any mix duration plus the negative delay.
        TrackEntry* addEmptyAnimation(size_t trackIndex, float mixDuration, float delay);
        
        ///
        /// Sets an empty animation for every track, discarding any queued animations, and mixes to it over the specified mix duration.
        void setEmptyAnimations(float mixDuration);
        
        /// @return The track entry for the animation currently playing on the track, or NULL if no animation is currently playing.
        TrackEntry* getCurrent(size_t trackIndex);
        
        AnimationStateData* getData();
        
        /// A list of tracks that have animations, which may contain NULLs.
        Vector<TrackEntry*> &getTracks();

        float getTimeScale();
        void setTimeScale(float inValue);

        void setListener(AnimationStateListener listener);

		void disableQueue();
		void enableQueue();
        
    private:
        
        AnimationStateData* _data;

        Pool<TrackEntry> _trackEntryPool;
        Vector<TrackEntry*> _tracks;
        Vector<Event*> _events;
        EventQueue* _queue;

        Vector<int> _propertyIDs;
        bool _animationsChanged;

        AnimationStateListener _listener;
        
        float _timeScale;

        static Animation* getEmptyAnimation();
        
        static void applyRotateTimeline(RotateTimeline* rotateTimeline, Skeleton& skeleton, float time, float alpha, MixBlend pose, Vector<float>& timelinesRotation, size_t i, bool firstFrame);
        
        /// Returns true when all mixing from entries are complete.
        bool updateMixingFrom(TrackEntry* to, float delta);
        
        float applyMixingFrom(TrackEntry* to, Skeleton& skeleton, MixBlend currentPose);
        
        void queueEvents(TrackEntry* entry, float animationTime);
        
        /// Sets the active TrackEntry for a given track number.
        void setCurrent(size_t index, TrackEntry* current, bool interrupt);

        TrackEntry* expandToIndex(size_t index);

        /// Object-pooling version of new TrackEntry. Obtain an unused TrackEntry from the pool and clear/initialize its values.
        /// @param last May be NULL.
        TrackEntry* newTrackEntry(size_t trackIndex, Animation* animation, bool loop, TrackEntry* last);

        /// Dispose all track entries queued after the given TrackEntry.
        void disposeNext(TrackEntry* entry);

        void animationsChanged();

        void setTimelineModes(TrackEntry* entry);

        bool hasTimeline(TrackEntry* entry, int inId);
    };
}

#endif /* Spine_AnimationState_h */
