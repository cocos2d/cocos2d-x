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

#ifndef Spine_PointAttachment_h
#define Spine_PointAttachment_h

#include <spine/Attachment.h>

namespace spine {
	class Bone;

	/// An attachment which is a single point and a rotation. This can be used to spawn projectiles, particles, etc. A bone can be
	/// used in similar ways, but a PointAttachment is slightly less expensive to compute and can be hidden, shown, and placed in a
	/// skin.
	///
	/// See http://esotericsoftware.com/spine-point-attachments for Point Attachments in the Spine User Guide.
	///
	class SP_API PointAttachment : public Attachment {
		friend class SkeletonBinary;
		friend class SkeletonJson;

		RTTI_DECL

	public:
		explicit PointAttachment(const String& name);

		void computeWorldPosition(Bone& bone, float& ox, float& oy);

		float computeWorldRotation(Bone& bone);

		float getX();
		void setX(float inValue);

		float getY();
		void setY(float inValue);

		float getRotation();
		void setRotation(float inValue);

		virtual Attachment* copy();

	private:
		float _x, _y, _rotation;
	};
}

#endif /* Spine_PointAttachment_h */
