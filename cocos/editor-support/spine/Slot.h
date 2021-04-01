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

#ifndef Spine_Slot_h
#define Spine_Slot_h

#include <spine/Vector.h>
#include <spine/SpineObject.h>
#include <spine/Color.h>

namespace spine {
class SlotData;

class Bone;

class Skeleton;

class Attachment;

class SP_API Slot : public SpineObject {
	friend class VertexAttachment;

	friend class Skeleton;

	friend class SkeletonBounds;

	friend class SkeletonClipping;

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
	Slot(SlotData &data, Bone &bone);

	void setToSetupPose();

	SlotData &getData();

	Bone &getBone();

	Skeleton &getSkeleton();

	Color &getColor();

	Color &getDarkColor();

	bool hasDarkColor();

	/// May be NULL.
	Attachment *getAttachment();

	void setAttachment(Attachment *inValue);

	float getAttachmentTime();

	void setAttachmentTime(float inValue);

	Vector<float> &getDeform();

private:
	SlotData &_data;
	Bone &_bone;
	Skeleton &_skeleton;
	Color _color;
	Color _darkColor;
	bool _hasDarkColor;
	Attachment *_attachment;
	float _attachmentTime;
	Vector<float> _deform;
};
}

#endif /* Spine_Slot_h */
