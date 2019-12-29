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

#ifndef Spine_IkConstraintData_h
#define Spine_IkConstraintData_h

#include <spine/Vector.h>
#include <spine/SpineObject.h>
#include <spine/SpineString.h>
#include <spine/ConstraintData.h>

namespace spine {
	class BoneData;

	class SP_API IkConstraintData : public ConstraintData {
		friend class SkeletonBinary;
		friend class SkeletonJson;
		friend class IkConstraint;
		friend class Skeleton;
		friend class IkConstraintTimeline;

	public:
		explicit IkConstraintData(const String& name);

		/// The bones that are constrained by this IK Constraint.
		Vector<BoneData*>& getBones();

		/// The bone that is the IK target.
		BoneData* getTarget();
		void setTarget(BoneData* inValue);

		/// Controls the bend direction of the IK bones, either 1 or -1.
		int getBendDirection();
		void setBendDirection(int inValue);

		bool getCompress();
		void setCompress(bool inValue);

		bool getStretch();
		void setStretch(bool inValue);

		bool getUniform();
		void setUniform(bool inValue);

		float getMix();
		void setMix(float inValue);

		float getSoftness();
		void setSoftness(float inValue);

	private:
		Vector<BoneData*> _bones;
		BoneData* _target;
		int _bendDirection;
		bool _compress;
		bool _stretch;
		bool _uniform;
		float _mix;
		float _softness;
	};
}

#endif /* Spine_IkConstraintData_h */
