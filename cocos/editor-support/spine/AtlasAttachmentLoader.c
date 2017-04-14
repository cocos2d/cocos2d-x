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

#include <spine/AtlasAttachmentLoader.h>
#include <spine/extension.h>

spAttachment* _spAtlasAttachmentLoader_createAttachment (spAttachmentLoader* loader, spSkin* skin, spAttachmentType type,
		const char* name, const char* path) {
	spAtlasAttachmentLoader* self = SUB_CAST(spAtlasAttachmentLoader, loader);
	switch (type) {
	case SP_ATTACHMENT_REGION: {
		spRegionAttachment* attachment;
		spAtlasRegion* region = spAtlas_findRegion(self->atlas, path);
		if (!region) {
			_spAttachmentLoader_setError(loader, "Region not found: ", path);
			return 0;
		}
		attachment = spRegionAttachment_create(name);
		attachment->rendererObject = region;
		spRegionAttachment_setUVs(attachment, region->u, region->v, region->u2, region->v2, region->rotate);
		attachment->regionOffsetX = region->offsetX;
		attachment->regionOffsetY = region->offsetY;
		attachment->regionWidth = region->width;
		attachment->regionHeight = region->height;
		attachment->regionOriginalWidth = region->originalWidth;
		attachment->regionOriginalHeight = region->originalHeight;
		return SUPER(attachment);
	}
	case SP_ATTACHMENT_MESH:
	case SP_ATTACHMENT_LINKED_MESH: {
		spMeshAttachment* attachment;
		spAtlasRegion* region = spAtlas_findRegion(self->atlas, path);
		if (!region) {
			_spAttachmentLoader_setError(loader, "Region not found: ", path);
			return 0;
		}
		attachment = spMeshAttachment_create(name);
		attachment->rendererObject = region;
		attachment->regionU = region->u;
		attachment->regionV = region->v;
		attachment->regionU2 = region->u2;
		attachment->regionV2 = region->v2;
		attachment->regionRotate = region->rotate;
		attachment->regionOffsetX = region->offsetX;
		attachment->regionOffsetY = region->offsetY;
		attachment->regionWidth = region->width;
		attachment->regionHeight = region->height;
		attachment->regionOriginalWidth = region->originalWidth;
		attachment->regionOriginalHeight = region->originalHeight;
		return SUPER(SUPER(attachment));
	}
	case SP_ATTACHMENT_BOUNDING_BOX:
		return SUPER(SUPER(spBoundingBoxAttachment_create(name)));
	case SP_ATTACHMENT_PATH:
		return SUPER(SUPER(spPathAttachment_create(name)));
	default:
		_spAttachmentLoader_setUnknownTypeError(loader, type);
		return 0;
	}

	UNUSED(skin);
}

spAtlasAttachmentLoader* spAtlasAttachmentLoader_create (spAtlas* atlas) {
	spAtlasAttachmentLoader* self = NEW(spAtlasAttachmentLoader);
	_spAttachmentLoader_init(SUPER(self), _spAttachmentLoader_deinit, _spAtlasAttachmentLoader_createAttachment, 0, 0);
	self->atlas = atlas;
	return self;
}
