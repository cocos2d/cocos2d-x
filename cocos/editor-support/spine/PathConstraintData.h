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

#ifndef Spine_PathConstraintData_h
#define Spine_PathConstraintData_h

#include <spine/PositionMode.h>
#include <spine/SpacingMode.h>
#include <spine/RotateMode.h>
#include <spine/Vector.h>
#include <spine/SpineObject.h>
#include <spine/SpineString.h>

namespace spine {
    class BoneData;
    class SlotData;
    
    class SP_API PathConstraintData : public SpineObject {
        friend class SkeletonBinary;
        friend class SkeletonJson;
        
        friend class PathConstraint;
        friend class Skeleton;
        friend class PathConstraintMixTimeline;
        friend class PathConstraintPositionTimeline;
        friend class PathConstraintSpacingTimeline;
        
    public:
        explicit PathConstraintData(const String& name);

        const String& getName();
        
        int getOrder();
        void setOrder(int inValue);
        
        Vector<BoneData*>& getBones();
        
        SlotData* getTarget();
        void setTarget(SlotData* inValue);
        
        PositionMode getPositionMode();
        void setPositionMode(PositionMode inValue);
        
        SpacingMode getSpacingMode();
        void setSpacingMode(SpacingMode inValue);
        
        RotateMode getRotateMode();
        void setRotateMode(RotateMode inValue);
        
        float getOffsetRotation();
        void setOffsetRotation(float inValue);
        
        float getPosition();
        void setPosition(float inValue);
        
        float getSpacing();
        void setSpacing(float inValue);
        
        float getRotateMix();
        void setRotateMix(float inValue);
        
        float getTranslateMix();
        void setTranslateMix(float inValue);

    private:
        const String _name;
        int _order;
        Vector<BoneData*> _bones;
        SlotData* _target;
        PositionMode _positionMode;
        SpacingMode _spacingMode;
        RotateMode _rotateMode;
        float _offsetRotation;
        float _position, _spacing, _rotateMix, _translateMix;
    };
}

#endif /* Spine_PathConstraintData_h */
