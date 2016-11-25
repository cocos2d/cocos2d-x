/******************************************************************************
 * Spine Runtimes Software License
 * Version 2.3
 * 
 * Copyright (c) 2013-2015, Esoteric Software
 * All rights reserved.
 * 
 * You are granted a perpetual, non-exclusive, non-sublicensable and
 * non-transferable license to use, install, execute and perform the Spine
 * Runtimes Software (the "Software") and derivative works solely for personal
 * or internal use. Without the written permission of Esoteric Software (see
 * Section 2 of the Spine Software License Agreement), you may not (a) modify,
 * translate, adapt or otherwise create derivative works, improvements of the
 * Software or develop new applications using the Software or (b) remove,
 * delete, alter or obscure any trademarks or any copyright, trademark, patent
 * or other intellectual property or proprietary rights notices on or in the
 * Software, including any copy thereof. Redistributions in binary or source
 * form must include this license and terms.
 * 
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#include <spine/Cocos2dAttachmentLoader.h>
#include <spine/extension.h>
#include <spine/AttachmentVertices.h>

USING_NS_CC;
using namespace spine;

static unsigned short quadTriangles[6] = {0, 1, 2, 2, 3, 0};

spAttachment* _Cocos2dAttachmentLoader_createAttachment (spAttachmentLoader* loader, spSkin* skin, spAttachmentType type,
		const char* name, const char* path) {
	Cocos2dAttachmentLoader* self = SUB_CAST(Cocos2dAttachmentLoader, loader);
	return spAttachmentLoader_createAttachment(SUPER(self->atlasAttachmentLoader), skin, type, name, path);
}

void _Cocos2dAttachmentLoader_configureAttachment (spAttachmentLoader* loader, spAttachment* attachment) {
	attachment->attachmentLoader = loader;

	switch (attachment->type) {
	case SP_ATTACHMENT_REGION: {
		spRegionAttachment* regionAttachment = SUB_CAST(spRegionAttachment, attachment);
		spAtlasRegion* region = (spAtlasRegion*)regionAttachment->rendererObject;
		AttachmentVertices* attachmentVertices = new AttachmentVertices((Texture2D*)region->page->rendererObject, 4, quadTriangles, 6);
		V3F_C4B_T2F* vertices = attachmentVertices->_triangles->verts;
		for (int i = 0, ii = 0; i < 4; ++i, ii += 2) {
			vertices[i].texCoords.u = regionAttachment->uvs[ii];
			vertices[i].texCoords.v = regionAttachment->uvs[ii + 1];
		}
		regionAttachment->rendererObject = attachmentVertices;
		break;
	}
	case SP_ATTACHMENT_MESH: {
		spMeshAttachment* meshAttachment = SUB_CAST(spMeshAttachment, attachment);
		spAtlasRegion* region = (spAtlasRegion*)meshAttachment->rendererObject;
		AttachmentVertices* attachmentVertices = new AttachmentVertices((Texture2D*)region->page->rendererObject,
			meshAttachment->super.worldVerticesLength >> 1, meshAttachment->triangles, meshAttachment->trianglesCount);
		V3F_C4B_T2F* vertices = attachmentVertices->_triangles->verts;
		for (int i = 0, ii = 0, nn = meshAttachment->super.worldVerticesLength; ii < nn; ++i, ii += 2) {
			vertices[i].texCoords.u = meshAttachment->uvs[ii];
			vertices[i].texCoords.v = meshAttachment->uvs[ii + 1];
		}
		meshAttachment->rendererObject = attachmentVertices;
		break;
	}
	default: ;
	}
}

void _Cocos2dAttachmentLoader_disposeAttachment (spAttachmentLoader* /*loader*/, spAttachment* attachment) {
	switch (attachment->type) {
	case SP_ATTACHMENT_REGION: {
		spRegionAttachment* regionAttachment = SUB_CAST(spRegionAttachment, attachment);
		delete (AttachmentVertices*)regionAttachment->rendererObject;
		break;
	}
	case SP_ATTACHMENT_MESH: {
		spMeshAttachment* meshAttachment = SUB_CAST(spMeshAttachment, attachment);
		delete (AttachmentVertices*)meshAttachment->rendererObject;
		break;
	}
	default: ;
	}
}

void _Cocos2dAttachmentLoader_dispose (spAttachmentLoader* loader) {
	Cocos2dAttachmentLoader* self = SUB_CAST(Cocos2dAttachmentLoader, loader);
	spAttachmentLoader_dispose(SUPER_CAST(spAttachmentLoader, self->atlasAttachmentLoader));
	_spAttachmentLoader_deinit(loader);
}

Cocos2dAttachmentLoader* Cocos2dAttachmentLoader_create (spAtlas* atlas) {
	Cocos2dAttachmentLoader* self = NEW(Cocos2dAttachmentLoader);
	_spAttachmentLoader_init(SUPER(self), _Cocos2dAttachmentLoader_dispose, _Cocos2dAttachmentLoader_createAttachment,
		_Cocos2dAttachmentLoader_configureAttachment, _Cocos2dAttachmentLoader_disposeAttachment);
	self->atlasAttachmentLoader = spAtlasAttachmentLoader_create(atlas);
	return self;
}
