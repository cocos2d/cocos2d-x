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

#ifndef Spine_CurveTimeline_h
#define Spine_CurveTimeline_h

#include <spine/Timeline.h>
#include <spine/Vector.h>

namespace spine {
	/// Base class for frames that use an interpolation bezier curve.
	class SP_API CurveTimeline : public Timeline {
		RTTI_DECL

	public:
		explicit CurveTimeline(int frameCount);

		virtual ~CurveTimeline();

		virtual void apply(Skeleton& skeleton, float lastTime, float time, Vector<Event*>* pEvents, float alpha, MixBlend blend, MixDirection direction) = 0;

		virtual int getPropertyId() = 0;

		size_t getFrameCount();

		void setLinear(size_t frameIndex);

		void setStepped(size_t frameIndex);

		/// Sets the control handle positions for an interpolation bezier curve used to transition from this keyframe to the next.
		/// cx1 and cx2 are from 0 to 1, representing the percent of time between the two keyframes. cy1 and cy2 are the percent of
		/// the difference between the keyframe's values.
		void setCurve(size_t frameIndex, float cx1, float cy1, float cx2, float cy2);

		float getCurvePercent(size_t frameIndex, float percent);

		float getCurveType(size_t frameIndex);

	protected:
		static const float LINEAR;
		static const float STEPPED;
		static const float BEZIER;
		static const int BEZIER_SIZE;

	private:
		Vector<float> _curves; // type, x, y, ...
	};
}

#endif /* Spine_CurveTimeline_h */
