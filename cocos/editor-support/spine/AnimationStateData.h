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

		/// The mix duration to use when changing from the specified animation to the other,
		/// or the DefaultMix if no mix duration has been set.
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
