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

#ifndef Spine_IkConstraintTimeline_h
#define Spine_IkConstraintTimeline_h

#include <spine/CurveTimeline.h>

namespace spine {

	class SP_API IkConstraintTimeline : public CurveTimeline {
		friend class SkeletonBinary;
		friend class SkeletonJson;

		RTTI_DECL

	public:
		static const int ENTRIES;

		explicit IkConstraintTimeline(int frameCount);

		virtual void apply(Skeleton& skeleton, float lastTime, float time, Vector<Event*>* pEvents, float alpha, MixBlend blend, MixDirection direction);

		virtual int getPropertyId();

		/// Sets the time, mix and bend direction of the specified keyframe.
		void setFrame (int frameIndex, float time, float mix, float softness, int bendDirection, bool compress, bool stretch);

	private:
		static const int PREV_TIME;
		static const int PREV_MIX;
		static const int PREV_SOFTNESS;
		static const int PREV_BEND_DIRECTION;
		static const int PREV_COMPRESS;
		static const int PREV_STRETCH;
		static const int MIX;
		static const int SOFTNESS;
		static const int BEND_DIRECTION;
		static const int COMPRESS;
		static const int STRETCH;

		Vector<float> _frames;
		int _ikConstraintIndex;
	};
}

#endif /* Spine_IkConstraintTimeline_h */
