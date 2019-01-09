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

#ifndef Spine_IkConstraint_h
#define Spine_IkConstraint_h

#include <spine/Constraint.h>

#include <spine/Vector.h>

namespace spine {
class IkConstraintData;

class Skeleton;

class Bone;

class SP_API IkConstraint : public Constraint {
	friend class Skeleton;

	friend class IkConstraintTimeline;

RTTI_DECL

public:
	/// Adjusts the bone rotation so the tip is as close to the target position as possible. The target is specified
	/// in the world coordinate system.
	static void apply(Bone &bone, float targetX, float targetY, bool compress, bool stretch, bool uniform, float alpha);

	/// Adjusts the parent and child bone rotations so the tip of the child is as close to the target position as
	/// possible. The target is specified in the world coordinate system.
	/// @param child A direct descendant of the parent bone.
	static void apply(Bone &parent, Bone &child, float targetX, float targetY, int bendDir, bool stretch, float alpha);

	IkConstraint(IkConstraintData &data, Skeleton &skeleton);

	/// Applies the constraint to the constrained bones.
	void apply();

	virtual void update();

	virtual int getOrder();

	IkConstraintData &getData();

	Vector<Bone *> &getBones();

	Bone *getTarget();

	void setTarget(Bone *inValue);

	int getBendDirection();

	void setBendDirection(int inValue);

	bool getCompress();

	void setCompress(bool inValue);

	bool getStretch();

	void setStretch(bool inValue);

	float getMix();

	void setMix(float inValue);

private:
	IkConstraintData &_data;
	Vector<Bone *> _bones;
	int _bendDirection;
	bool _compress;
	bool _stretch;
	float _mix;
	Bone *_target;
};
}

#endif /* Spine_IkConstraint_h */
