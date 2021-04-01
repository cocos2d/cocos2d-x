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

#ifdef SPINE_UE4
#include "SpinePluginPrivatePCH.h"
#endif

#include <spine/AtlasAttachmentLoader.h>
#include <spine/Skin.h>
#include <spine/RegionAttachment.h>
#include <spine/MeshAttachment.h>
#include <spine/BoundingBoxAttachment.h>
#include <spine/PathAttachment.h>
#include <spine/PointAttachment.h>
#include <spine/ClippingAttachment.h>

#include <spine/Atlas.h>

namespace spine {
RTTI_IMPL(AtlasAttachmentLoader, AttachmentLoader)

AtlasAttachmentLoader::AtlasAttachmentLoader(Atlas *atlas) : AttachmentLoader(), _atlas(atlas) {
}

RegionAttachment *AtlasAttachmentLoader::newRegionAttachment(Skin &skin, const String &name, const String &path) {
	SP_UNUSED(skin);

	AtlasRegion *regionP = findRegion(path);
	if (!regionP) return NULL;

	AtlasRegion &region = *regionP;

	RegionAttachment *attachmentP = new(__FILE__, __LINE__) RegionAttachment(name);

	RegionAttachment &attachment = *attachmentP;
	attachment.setRendererObject(regionP);
	attachment.setUVs(region.u, region.v, region.u2, region.v2, region.rotate);
	attachment._regionOffsetX = region.offsetX;
	attachment._regionOffsetY = region.offsetY;
	attachment._regionWidth = (float)region.width;
	attachment._regionHeight = (float)region.height;
	attachment._regionOriginalWidth = (float)region.originalWidth;
	attachment._regionOriginalHeight = (float)region.originalHeight;
	return attachmentP;
}

MeshAttachment *AtlasAttachmentLoader::newMeshAttachment(Skin &skin, const String &name, const String &path) {
	SP_UNUSED(skin);

	AtlasRegion *regionP = findRegion(path);
	if (!regionP) return NULL;

	AtlasRegion &region = *regionP;

	MeshAttachment *attachmentP = new(__FILE__, __LINE__) MeshAttachment(name);

	MeshAttachment &attachment = *attachmentP;
	attachment.setRendererObject(regionP);
	attachment._regionU = region.u;
	attachment._regionV = region.v;
	attachment._regionU2 = region.u2;
	attachment._regionV2 = region.v2;
	attachment._regionRotate = region.rotate;
	attachment._regionDegrees = region.degrees;
	attachment._regionOffsetX = region.offsetX;
	attachment._regionOffsetY = region.offsetY;
	attachment._regionWidth = (float)region.width;
	attachment._regionHeight = (float)region.height;
	attachment._regionOriginalWidth = (float)region.originalWidth;
	attachment._regionOriginalHeight = (float)region.originalHeight;

	return attachmentP;
}

BoundingBoxAttachment *AtlasAttachmentLoader::newBoundingBoxAttachment(Skin &skin, const String &name) {
	SP_UNUSED(skin);
	return new(__FILE__, __LINE__) BoundingBoxAttachment(name);
}

PathAttachment *AtlasAttachmentLoader::newPathAttachment(Skin &skin, const String &name) {
	SP_UNUSED(skin);
	return new(__FILE__, __LINE__) PathAttachment(name);
}

PointAttachment *AtlasAttachmentLoader::newPointAttachment(Skin &skin, const String &name) {
	SP_UNUSED(skin);
	return new(__FILE__, __LINE__) PointAttachment(name);
}

ClippingAttachment *AtlasAttachmentLoader::newClippingAttachment(Skin &skin, const String &name) {
	SP_UNUSED(skin);
	return new(__FILE__, __LINE__) ClippingAttachment(name);
}

void AtlasAttachmentLoader::configureAttachment(Attachment* attachment) {
	SP_UNUSED(attachment);
}

AtlasRegion *AtlasAttachmentLoader::findRegion(const String &name) {
	return _atlas->findRegion(name);
}

}
