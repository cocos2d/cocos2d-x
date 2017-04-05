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
#include <spine/extension.h>

USING_NS_CC;

GLuint wrap (spAtlasWrap wrap) {
	return wrap == SP_ATLAS_CLAMPTOEDGE ? GL_CLAMP_TO_EDGE : GL_REPEAT;
}

GLuint filter (spAtlasFilter filter) {
	switch (filter) {
	case SP_ATLAS_UNKNOWN_FILTER:
		break;
	case SP_ATLAS_NEAREST:
		return GL_NEAREST;
	case SP_ATLAS_LINEAR:
		return GL_LINEAR;
	case SP_ATLAS_MIPMAP:
		return GL_LINEAR_MIPMAP_LINEAR;
	case SP_ATLAS_MIPMAP_NEAREST_NEAREST:
		return GL_NEAREST_MIPMAP_NEAREST;
	case SP_ATLAS_MIPMAP_LINEAR_NEAREST:
		return GL_LINEAR_MIPMAP_NEAREST;
	case SP_ATLAS_MIPMAP_NEAREST_LINEAR:
		return GL_NEAREST_MIPMAP_LINEAR;
	case SP_ATLAS_MIPMAP_LINEAR_LINEAR:
		return GL_LINEAR_MIPMAP_LINEAR;
	}
	return GL_LINEAR;
}

void _spAtlasPage_createTexture (spAtlasPage* self, const char* path) {
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(path);
	CCASSERT(texture != nullptr, "Invalid image");
	texture->retain();

	Texture2D::TexParams textureParams = {filter(self->minFilter), filter(self->magFilter), wrap(self->uWrap), wrap(self->vWrap)};
	texture->setTexParameters(textureParams);

	self->rendererObject = texture;
	self->width = texture->getPixelsWide();
	self->height = texture->getPixelsHigh();
}

void _spAtlasPage_disposeTexture (spAtlasPage* self) {
	((Texture2D*)self->rendererObject)->release();
}

char* _spUtil_readFile (const char* path, int* length) {
	Data data = FileUtils::getInstance()->getDataFromFile(FileUtils::getInstance()->fullPathForFilename(path));
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
