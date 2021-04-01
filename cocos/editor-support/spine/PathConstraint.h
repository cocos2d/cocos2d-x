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

#ifndef Spine_PathConstraint_h
#define Spine_PathConstraint_h

#include <spine/ConstraintData.h>

#include <spine/Vector.h>

namespace spine {
	class PathConstraintData;
	class Skeleton;
	class PathAttachment;
	class Bone;
	class Slot;

	class SP_API PathConstraint : public Updatable {
		friend class Skeleton;
		friend class PathConstraintMixTimeline;
		friend class PathConstraintPositionTimeline;
		friend class PathConstraintSpacingTimeline;

		RTTI_DECL

	public:
		PathConstraint(PathConstraintData& data, Skeleton& skeleton);

		/// Applies the constraint to the constrained bones.
		void apply();

		virtual void update();

		virtual int getOrder();

		float getPosition();
		void setPosition(float inValue);

		float getSpacing();
		void setSpacing(float inValue);

		float getRotateMix();
		void setRotateMix(float inValue);

		float getTranslateMix();
		void setTranslateMix(float inValue);

		Vector<Bone*>& getBones();

		Slot* getTarget();
		void setTarget(Slot* inValue);

		PathConstraintData& getData();

		bool isActive();

		void setActive(bool inValue);

	private:
		static const float EPSILON;
		static const int NONE;
		static const int BEFORE;
		static const int AFTER;

		PathConstraintData& _data;
		Vector<Bone*> _bones;
		Slot* _target;
		float _position, _spacing, _rotateMix, _translateMix;

		Vector<float> _spaces;
		Vector<float> _positions;
		Vector<float> _world;
		Vector<float> _curves;
		Vector<float> _lengths;
		Vector<float> _segments;

		bool _active;

		Vector<float>& computeWorldPositions(PathAttachment& path, int spacesCount, bool tangents, bool percentPosition, bool percentSpacing);

		static void addBeforePosition(float p, Vector<float>& temp, int i, Vector<float>& output, int o);

		static void addAfterPosition(float p, Vector<float>& temp, int i, Vector<float>& output, int o);

		static void addCurvePosition(float p, float x1, float y1, float cx1, float cy1, float cx2, float cy2, float x2, float y2, Vector<float>& output, int o, bool tangents);
	};
}

#endif /* Spine_PathConstraint_h */
