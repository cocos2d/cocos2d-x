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

#ifndef Spine_SlotData_h
#define Spine_SlotData_h

#include <spine/BlendMode.h>
#include <spine/SpineObject.h>
#include <spine/SpineString.h>
#include <spine/Color.h>

namespace spine {
class BoneData;

class SP_API SlotData : public SpineObject {
	friend class SkeletonBinary;

	friend class SkeletonJson;

	friend class AttachmentTimeline;

	friend class ColorTimeline;

	friend class DeformTimeline;

	friend class DrawOrderTimeline;

	friend class EventTimeline;

	friend class IkConstraintTimeline;

	friend class PathConstraintMixTimeline;

	friend class PathConstraintPositionTimeline;

	friend class PathConstraintSpacingTimeline;

	friend class ScaleTimeline;

	friend class ShearTimeline;

	friend class TransformConstraintTimeline;

	friend class TranslateTimeline;

	friend class TwoColorTimeline;

public:
	SlotData(int index, const String &name, BoneData &boneData);

	int getIndex();

	const String &getName();

	BoneData &getBoneData();

	Color &getColor();

	Color &getDarkColor();

	bool hasDarkColor();

	void setHasDarkColor(bool inValue);

	/// May be empty.
	const String &getAttachmentName();

	void setAttachmentName(const String &inValue);

	BlendMode getBlendMode();

	void setBlendMode(BlendMode inValue);

private:
	const int _index;
	String _name;
	BoneData &_boneData;
	Color _color;
	Color _darkColor;

	bool _hasDarkColor;
	String _attachmentName;
	BlendMode _blendMode;
};
}

#endif /* Spine_SlotData_h */
