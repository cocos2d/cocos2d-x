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

#ifndef Spine_IkConstraint_h
#define Spine_IkConstraint_h

#include <spine/ConstraintData.h>

#include <spine/Vector.h>

namespace spine {
class IkConstraintData;

class Skeleton;

class Bone;

class SP_API IkConstraint : public Updatable {
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
	static void apply(Bone &parent, Bone &child, float targetX, float targetY, int bendDir, bool stretch, float softness, float alpha);

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

	float getSoftness();

	void setSoftness(float inValue);

	bool isActive();

	void setActive(bool inValue);

private:
	IkConstraintData &_data;
	Vector<Bone *> _bones;
	int _bendDirection;
	bool _compress;
	bool _stretch;
	float _mix;
	float _softness;
	Bone *_target;
	bool _active;
};
}

#endif /* Spine_IkConstraint_h */
