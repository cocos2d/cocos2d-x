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

#ifndef Spine_BoneData_h
#define Spine_BoneData_h

#include <spine/TransformMode.h>
#include <spine/SpineObject.h>
#include <spine/SpineString.h>

namespace spine {
class SP_API BoneData : public SpineObject {
	friend class SkeletonBinary;

	friend class SkeletonJson;

	friend class AnimationState;

	friend class RotateTimeline;

	friend class ScaleTimeline;

	friend class ShearTimeline;

	friend class TranslateTimeline;

public:
	BoneData(int index, const String &name, BoneData *parent = NULL);

	/// The index of the bone in Skeleton.Bones
	int getIndex();

	/// The name of the bone, which is unique within the skeleton.
	const String &getName();

	/// May be NULL.
	BoneData *getParent();

	float getLength();

	void setLength(float inValue);

	/// Local X translation.
	float getX();

	void setX(float inValue);

	/// Local Y translation.
	float getY();

	void setY(float inValue);

	/// Local rotation.
	float getRotation();

	void setRotation(float inValue);

	/// Local scaleX.
	float getScaleX();

	void setScaleX(float inValue);

	/// Local scaleY.
	float getScaleY();

	void setScaleY(float inValue);

	/// Local shearX.
	float getShearX();

	void setShearX(float inValue);

	/// Local shearY.
	float getShearY();

	void setShearY(float inValue);

	/// The transform mode for how parent world transforms affect this bone.
	TransformMode getTransformMode();

	void setTransformMode(TransformMode inValue);

	bool isSkinRequired();
	void setSkinRequired(bool inValue);

private:
	const int _index;
	const String _name;
	BoneData *_parent;
	float _length;
	float _x, _y, _rotation, _scaleX, _scaleY, _shearX, _shearY;
	TransformMode _transformMode;
	bool _skinRequired;
};
}

#endif /* Spine_BoneData_h */
