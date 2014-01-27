/******************************************************************************
 * Spine Runtime Software License - Version 1.1
 * 
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms in whole or in part, with
 * or without modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. A Spine Essential, Professional, Enterprise, or Education License must
 *    be purchased from Esoteric Software and the license must remain valid:
 *    http://esotericsoftware.com/
 * 2. Redistributions of source code must retain this license, which is the
 *    above copyright notice, this declaration of conditions and the following
 *    disclaimer.
 * 3. Redistributions in binary form must reproduce this license, which is the
 *    above copyright notice, this declaration of conditions and the following
 *    disclaimer, in the documentation and/or other materials provided with the
 *    distribution.
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
 *****************************************************************************/

#include <spine/spine-cocos2dx.h>
#include <spine/extension.h>

USING_NS_CC;

void _spAtlasPage_createTexture (spAtlasPage* self, const char* path) {
    Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(path);
    TextureAtlas* textureAtlas = TextureAtlas::createWithTexture(texture, 4);
    textureAtlas->retain();
    self->rendererObject = textureAtlas;
    // Using getContentSize to make it supports the strategy of loading resources in cocos2d-x.
    // self->width = texture->getPixelsWide();
    // self->height = texture->getPixelsHigh();
    self->width = texture->getContentSize().width;
    self->height = texture->getContentSize().height;
}

void _spAtlasPage_disposeTexture (spAtlasPage* self) {
	((TextureAtlas*)self->rendererObject)->release();
}

char* _spUtil_readFile (const char* path, int* length)
{
    char* ret = nullptr;
    int size = 0;
    Data data = FileUtils::getInstance()->getDataFromFile(path);
    
    if (!data.isNull())
    {
        size = static_cast<int>(data.getSize());
        *length = size;
        // Allocates one more byte for string terminal, it will be safe when parsing JSON file in Spine runtime.
        ret = (char*)malloc(size + 1);
        ret[size] = '\0';
        memcpy(ret, data.getBytes(), size);
    }
    
    return ret;
}

/**/

void spRegionAttachment_updateQuad (spRegionAttachment* self, spSlot* slot, V3F_C4B_T2F_Quad* quad, bool premultipliedAlpha) {
	float vertices[8];
	spRegionAttachment_computeWorldVertices(self, slot->skeleton->x, slot->skeleton->y, slot->bone, vertices);

	GLubyte r = slot->skeleton->r * slot->r * 255;
	GLubyte g = slot->skeleton->g * slot->g * 255;
	GLubyte b = slot->skeleton->b * slot->b * 255;
	float normalizedAlpha = slot->skeleton->a * slot->a;
	if (premultipliedAlpha) {
		r *= normalizedAlpha;
		g *= normalizedAlpha;
		b *= normalizedAlpha;
	}
	GLubyte a = normalizedAlpha * 255;
	quad->bl.colors.r = r;
	quad->bl.colors.g = g;
	quad->bl.colors.b = b;
	quad->bl.colors.a = a;
	quad->tl.colors.r = r;
	quad->tl.colors.g = g;
	quad->tl.colors.b = b;
	quad->tl.colors.a = a;
	quad->tr.colors.r = r;
	quad->tr.colors.g = g;
	quad->tr.colors.b = b;
	quad->tr.colors.a = a;
	quad->br.colors.r = r;
	quad->br.colors.g = g;
	quad->br.colors.b = b;
	quad->br.colors.a = a;

	quad->bl.vertices.x = vertices[VERTEX_X1];
	quad->bl.vertices.y = vertices[VERTEX_Y1];
	quad->tl.vertices.x = vertices[VERTEX_X2];
	quad->tl.vertices.y = vertices[VERTEX_Y2];
	quad->tr.vertices.x = vertices[VERTEX_X3];
	quad->tr.vertices.y = vertices[VERTEX_Y3];
	quad->br.vertices.x = vertices[VERTEX_X4];
	quad->br.vertices.y = vertices[VERTEX_Y4];

	quad->bl.texCoords.u = self->uvs[VERTEX_X1];
	quad->bl.texCoords.v = self->uvs[VERTEX_Y1];
	quad->tl.texCoords.u = self->uvs[VERTEX_X2];
	quad->tl.texCoords.v = self->uvs[VERTEX_Y2];
	quad->tr.texCoords.u = self->uvs[VERTEX_X3];
	quad->tr.texCoords.v = self->uvs[VERTEX_Y3];
	quad->br.texCoords.u = self->uvs[VERTEX_X4];
	quad->br.texCoords.v = self->uvs[VERTEX_Y4];
}
