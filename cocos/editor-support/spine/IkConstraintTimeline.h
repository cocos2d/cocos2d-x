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
        void setFrame (int frameIndex, float time, float mix, int bendDirection, bool compress, bool stretch);
        
    private:
		static const int PREV_TIME;
		static const int PREV_MIX;
		static const int PREV_BEND_DIRECTION;
		static const int PREV_COMPRESS;
		static const int PREV_STRETCH;
		static const int MIX;
		static const int BEND_DIRECTION;
		static const int COMPRESS;
		static const int STRETCH;

        Vector<float> _frames;
        int _ikConstraintIndex;
    };
}

#endif /* Spine_IkConstraintTimeline_h */
