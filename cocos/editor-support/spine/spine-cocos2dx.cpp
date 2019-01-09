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

#include <spine/spine-cocos2dx.h>
#include <spine/Extension.h>
#include <spine/AttachmentVertices.h>

USING_NS_CC;
using namespace spine;

static void deleteAttachmentVertices (void* vertices) {
	delete (AttachmentVertices *) vertices;
}

static unsigned short quadTriangles[6] = {0, 1, 2, 2, 3, 0};

static void setAttachmentVertices(RegionAttachment* attachment) {
	AtlasRegion* region = (AtlasRegion*)attachment->getRendererObject();
	AttachmentVertices* attachmentVertices = new AttachmentVertices((Texture2D*)region->page->getRendererObject(), 4, quadTriangles, 6);
	V3F_C4B_T2F* vertices = attachmentVertices->_triangles->verts;
	for (int i = 0, ii = 0; i < 4; ++i, ii += 2) {
		vertices[i].texCoords.u = attachment->getUVs()[ii];
		vertices[i].texCoords.v = attachment->getUVs()[ii + 1];
	}
	attachment->setRendererObject(attachmentVertices, deleteAttachmentVertices);	
}

static void setAttachmentVertices(MeshAttachment* attachment) {
	AtlasRegion* region = (AtlasRegion*)attachment->getRendererObject();
	AttachmentVertices* attachmentVertices = new AttachmentVertices((Texture2D*)region->page->getRendererObject(),
																	attachment->getWorldVerticesLength() >> 1, attachment->getTriangles().buffer(), attachment->getTriangles().size());
	V3F_C4B_T2F* vertices = attachmentVertices->_triangles->verts;
	for (int i = 0, ii = 0, nn = attachment->getWorldVerticesLength(); ii < nn; ++i, ii += 2) {
		vertices[i].texCoords.u = attachment->getUVs()[ii];
		vertices[i].texCoords.v = attachment->getUVs()[ii + 1];
	}
	attachment->setRendererObject(attachmentVertices, deleteAttachmentVertices);
}

Cocos2dAtlasAttachmentLoader::Cocos2dAtlasAttachmentLoader(Atlas* atlas): AtlasAttachmentLoader(atlas) {	
}

Cocos2dAtlasAttachmentLoader::~Cocos2dAtlasAttachmentLoader() { }

void Cocos2dAtlasAttachmentLoader::configureAttachment(Attachment* attachment) {
	if (attachment->getRTTI().isExactly(RegionAttachment::rtti)) {
		setAttachmentVertices((RegionAttachment*)attachment);
	} else if (attachment->getRTTI().isExactly(MeshAttachment::rtti)) {
		setAttachmentVertices((MeshAttachment*)attachment);
	}
}

GLuint wrap (TextureWrap wrap) {
	return wrap ==  TextureWrap_ClampToEdge ? GL_CLAMP_TO_EDGE : GL_REPEAT;
}

GLuint filter (TextureFilter filter) {
	switch (filter) {
	case TextureFilter_Unknown:
		break;
	case TextureFilter_Nearest:
		return GL_NEAREST;
	case TextureFilter_Linear:
		return GL_LINEAR;
	case TextureFilter_MipMap:
		return GL_LINEAR_MIPMAP_LINEAR;
	case TextureFilter_MipMapNearestNearest:
		return GL_NEAREST_MIPMAP_NEAREST;
	case TextureFilter_MipMapLinearNearest:
		return GL_LINEAR_MIPMAP_NEAREST;
	case TextureFilter_MipMapNearestLinear:
		return GL_NEAREST_MIPMAP_LINEAR;
	case TextureFilter_MipMapLinearLinear:
		return GL_LINEAR_MIPMAP_LINEAR;
	}
	return GL_LINEAR;
}

Cocos2dTextureLoader::Cocos2dTextureLoader() : TextureLoader() { }
Cocos2dTextureLoader::~Cocos2dTextureLoader() { }

void Cocos2dTextureLoader::load(AtlasPage& page, const spine::String& path) {
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(path.buffer());
	CCASSERT(texture != nullptr, "Invalid image");
	texture->retain();
	
	Texture2D::TexParams textureParams = {filter(page.minFilter), filter(page.magFilter), wrap(page.uWrap), wrap(page.vWrap)};
	texture->setTexParameters(textureParams);
	
	page.setRendererObject(texture);
	page.width = texture->getPixelsWide();
	page.height = texture->getPixelsHigh();
}
	
void Cocos2dTextureLoader::unload(void* texture) {
	((Texture2D*)texture)->release();
}


Cocos2dExtension::Cocos2dExtension() : DefaultSpineExtension() { }
	
Cocos2dExtension::~Cocos2dExtension() { }

char *Cocos2dExtension::_readFile(const spine::String &path, int *length) {
	Data data = FileUtils::getInstance()->getDataFromFile(FileUtils::getInstance()->fullPathForFilename(path.buffer()));
	if (data.isNull()) return 0;
	
	// avoid buffer overflow (int is shorter than ssize_t in certain platforms)
#if COCOS2D_VERSION >= 0x00031200
	ssize_t tmpLen;
	char *ret = (char*)data.takeBuffer(&tmpLen);
	*length = static_cast<int>(tmpLen);
	return ret;
#else
	*length = static_cast<int>(data.getSize());
	char* bytes = MALLOC(char, *length);
	memcpy(bytes, data.getBytes(), *length);
	return bytes;
#endif
}

SpineExtension *spine::getDefaultExtension () {
	return new Cocos2dExtension();
}

