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

#ifndef Spine_TransformConstraintData_h
#define Spine_TransformConstraintData_h

#include <spine/Vector.h>
#include <spine/SpineObject.h>
#include <spine/SpineString.h>

namespace spine {
    class BoneData;
    
    class SP_API TransformConstraintData : public SpineObject {
        friend class SkeletonBinary;
        friend class SkeletonJson;
        
        friend class TransformConstraint;
        friend class Skeleton;
        friend class TransformConstraintTimeline;
        
    public:
        explicit TransformConstraintData(const String& name);

        const String& getName();
        int getOrder();
        Vector<BoneData*>& getBones();
        BoneData* getTarget();
        float getRotateMix();
        float getTranslateMix();
        float getScaleMix();
        float getShearMix();
        
        float getOffsetRotation();
        float getOffsetX();
        float getOffsetY();
        float getOffsetScaleX();
        float getOffsetScaleY();
        float getOffsetShearY();
        
        bool isRelative();
        bool isLocal();
        
    private:
        const String _name;
        int _order;
        Vector<BoneData*> _bones;
        BoneData* _target;
        float _rotateMix, _translateMix, _scaleMix, _shearMix;
        float _offsetRotation, _offsetX, _offsetY, _offsetScaleX, _offsetScaleY, _offsetShearY;
        bool _relative, _local;
    };
}

#endif /* Spine_TransformConstraintData_h */
