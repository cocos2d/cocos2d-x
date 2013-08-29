/*******************************************************************************
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#include <spine/AtlasAttachmentLoader.h>
#include <spine/extension.h>

namespace cocos2d { namespace extension {

Attachment* _AtlasAttachmentLoader_newAttachment (AttachmentLoader* loader, Skin* skin, AttachmentType type, const char* name) {
	AtlasAttachmentLoader* self = SUB_CAST(AtlasAttachmentLoader, loader);
	switch (type) {
	case ATTACHMENT_REGION: {
		RegionAttachment* attachment;
		AtlasRegion* region = Atlas_findRegion(self->atlas, name);
		if (!region) {
			_AttachmentLoader_setError(loader, "Region not found: ", name);
			return 0;
		}
		attachment = RegionAttachment_create(name);
		attachment->rendererObject = region;
		RegionAttachment_setUVs(attachment, region->u, region->v, region->u2, region->v2, region->rotate);
		attachment->regionOffsetX = region->offsetX;
		attachment->regionOffsetY = region->offsetY;
		attachment->regionWidth = region->width;
		attachment->regionHeight = region->height;
		attachment->regionOriginalWidth = region->originalWidth;
		attachment->regionOriginalHeight = region->originalHeight;
		return SUPER(attachment);
	}
	default:
		_AttachmentLoader_setUnknownTypeError(loader, type);
		return 0;
	}
}

AtlasAttachmentLoader* AtlasAttachmentLoader_create (Atlas* atlas) {
	AtlasAttachmentLoader* self = NEW(AtlasAttachmentLoader);
	_AttachmentLoader_init(SUPER(self), _AttachmentLoader_deinit, _AtlasAttachmentLoader_newAttachment);
	self->atlas = atlas;
	return self;
}

}} // namespace cocos2d { namespace extension {