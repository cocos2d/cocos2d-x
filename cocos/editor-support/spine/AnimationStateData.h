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

#ifndef Spine_AnimationStateData_h
#define Spine_AnimationStateData_h

#include <spine/HashMap.h>
#include <spine/SpineObject.h>
#include <spine/SpineString.h>

#include <assert.h>

namespace spine {
    class SkeletonData;
    class Animation;
    
    /// Stores mix (crossfade) durations to be applied when AnimationState animations are changed.
    class SP_API AnimationStateData : public SpineObject {
        friend class AnimationState;
        
    public:
		explicit AnimationStateData(SkeletonData* skeletonData);
		
        /// The SkeletonData to look up animations when they are specified by name.
        SkeletonData* getSkeletonData();
        
        /// The mix duration to use when no mix duration has been specifically defined between two animations.
        float getDefaultMix();
        void setDefaultMix(float inValue);
        
        /// Sets a mix duration by animation names.
        void setMix(const String& fromName, const String& toName, float duration);
        
        /// Sets a mix duration when changing from the specified animation to the other.
        /// See TrackEntry.MixDuration.
        void setMix(Animation* from, Animation* to, float duration);
        
        ///
        /// The mix duration to use when changing from the specified animation to the other,
        /// or the DefaultMix if no mix duration has been set.
        ///
        float getMix(Animation* from, Animation* to);

    private:
        class AnimationPair : public SpineObject {
        public:
            Animation* _a1;
            Animation* _a2;

            explicit AnimationPair(Animation* a1 = NULL, Animation* a2 = NULL);
            
            bool operator==(const AnimationPair &other) const;
        };
        
        SkeletonData* _skeletonData;
        float _defaultMix;
        HashMap<AnimationPair, float> _animationToMixTime;
    };
}

#endif /* Spine_AnimationStateData_h */
