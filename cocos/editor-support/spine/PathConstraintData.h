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

#ifndef Spine_PathConstraintData_h
#define Spine_PathConstraintData_h

#include <spine/PositionMode.h>
#include <spine/SpacingMode.h>
#include <spine/RotateMode.h>
#include <spine/Vector.h>
#include <spine/SpineObject.h>
#include <spine/SpineString.h>
#include <spine/ConstraintData.h>

namespace spine {
	class BoneData;
	class SlotData;

	class SP_API PathConstraintData : public ConstraintData {
		friend class SkeletonBinary;
		friend class SkeletonJson;

		friend class PathConstraint;
		friend class Skeleton;
		friend class PathConstraintMixTimeline;
		friend class PathConstraintPositionTimeline;
		friend class PathConstraintSpacingTimeline;

	public:
		explicit PathConstraintData(const String& name);

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
