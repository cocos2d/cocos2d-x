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

#ifndef Spine_Slot_h
#define Spine_Slot_h

#include <spine/Vector.h>
#include <spine/SpineObject.h>
#include <spine/Color.h>

#include <string>

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

	Vector<float> &getAttachmentVertices();

private:
	SlotData &_data;
	Bone &_bone;
	Skeleton &_skeleton;
	Color _color;
	Color _darkColor;
	bool _hasDarkColor;
	Attachment *_attachment;
	float _attachmentTime;
	Vector<float> _attachmentVertices;
};
}

#endif /* Spine_Slot_h */
