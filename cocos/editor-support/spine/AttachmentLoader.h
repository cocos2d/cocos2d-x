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

#ifndef Spine_AttachmentLoader_h
#define Spine_AttachmentLoader_h

#include <spine/RTTI.h>
#include <spine/SpineObject.h>
#include <spine/SpineString.h>

namespace spine {
	class Skin;
	class Attachment;
	class RegionAttachment;
	class MeshAttachment;
	class BoundingBoxAttachment;
	class PathAttachment;
	class PointAttachment;
	class ClippingAttachment;

	class SP_API AttachmentLoader : public SpineObject {
	public:
		RTTI_DECL

		AttachmentLoader();

		virtual ~AttachmentLoader();

		/// @return May be NULL to not load any attachment.
		virtual RegionAttachment* newRegionAttachment(Skin& skin, const String& name, const String& path) = 0;

		/// @return May be NULL to not load any attachment.
		virtual MeshAttachment* newMeshAttachment(Skin& skin, const String& name, const String& path) = 0;

		/// @return May be NULL to not load any attachment.
		virtual BoundingBoxAttachment* newBoundingBoxAttachment(Skin& skin, const String& name) = 0;

		/// @return May be NULL to not load any attachment
		virtual PathAttachment* newPathAttachment(Skin& skin, const String& name) = 0;

		virtual PointAttachment* newPointAttachment(Skin& skin, const String& name) = 0;

		virtual ClippingAttachment* newClippingAttachment(Skin& skin, const String& name) = 0;

		virtual void configureAttachment(Attachment* attachment) = 0;
	};
}

#endif /* Spine_AttachmentLoader_h */
