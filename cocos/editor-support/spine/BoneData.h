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

private:
	const int _index;
	const String _name;
	BoneData *_parent;
	float _length;
	float _x, _y, _rotation, _scaleX, _scaleY, _shearX, _shearY;
	TransformMode _transformMode;
};
}

#endif /* Spine_BoneData_h */
