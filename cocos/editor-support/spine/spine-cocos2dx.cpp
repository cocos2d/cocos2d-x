/******************************************************************************
 * Spine Runtimes Software License
 * Version 2
 * 
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 * 
 * You are granted a perpetual, non-exclusive, non-sublicensable and
 * non-transferable license to install, execute and perform the Spine Runtimes
 * Software (the "Software") solely for internal use. Without the written
 * permission of Esoteric Software, you may not (a) modify, translate, adapt or
 * otherwise create derivative works, improvements of the Software or develop
 * new applications using the Software or (b) remove, delete, alter or obscure
 * any trademarks or any copyright, trademark, patent or other intellectual
 * property or proprietary rights notices on or in the Software, including
 * any copy thereof. Redistributions in binary or source form must include
 * this license and terms. THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL ESOTERIC SOFTARE BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#include <spine/spine-cocos2dx.h>
#include <spine/extension.h>

#include "CCTriangleTextureAtlas.h"

USING_NS_CC;

void _spAtlasPage_createTexture (spAtlasPage* self, const char* path) {
    Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(path);
    TriangleTextureAtlas* textureAtlas = TriangleTextureAtlas::createWithTexture(texture, 256);
    textureAtlas->retain();
    self->rendererObject = textureAtlas;
    // Using getContentSize to make it supports the strategy of loading resources in cocos2d-x.
    // self->width = texture->getContentSize().width;
    // self->height = texture->getContentSize().height;
    // getPixel series are much better choice.
    self->width = texture->getPixelsWide();
    self->height = texture->getPixelsHigh();
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

void spRegionAttachment_updateVertices (spRegionAttachment* self, spSlot* slot, V3F_C4B_T2F* vertices, bool premultipliedAlpha, float* calculatedVertices)
{
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
    
    vertices[0].colors.r = r;
    vertices[0].colors.g = g;
    vertices[0].colors.b = b;
    vertices[0].colors.a = a;
    vertices[0].vertices.x = calculatedVertices[VERTEX_X1];
    vertices[0].vertices.y = calculatedVertices[VERTEX_Y1];
    vertices[0].vertices.z = 0.0f;
    vertices[0].texCoords.u = self->uvs[VERTEX_X1];
    vertices[0].texCoords.v = self->uvs[VERTEX_Y1];
    
    vertices[1].colors.r = r;
    vertices[1].colors.g = g;
    vertices[1].colors.b = b;
    vertices[1].colors.a = a;
    vertices[1].vertices.x = calculatedVertices[VERTEX_X2];
    vertices[1].vertices.y = calculatedVertices[VERTEX_Y2];
    vertices[1].vertices.z = 0.0f;
    vertices[1].texCoords.u = self->uvs[VERTEX_X2];
    vertices[1].texCoords.v = self->uvs[VERTEX_Y2];
    
    vertices[2].colors.r = r;
    vertices[2].colors.g = g;
    vertices[2].colors.b = b;
    vertices[2].colors.a = a;
    vertices[2].vertices.x = calculatedVertices[VERTEX_X3];
    vertices[2].vertices.y = calculatedVertices[VERTEX_Y3];
    vertices[2].vertices.z = 0.0f;
    vertices[2].texCoords.u = self->uvs[VERTEX_X3];
    vertices[2].texCoords.v = self->uvs[VERTEX_Y3];
    
    vertices[3].colors.r = r;
    vertices[3].colors.g = g;
    vertices[3].colors.b = b;
    vertices[3].colors.a = a;
    vertices[3].vertices.x = calculatedVertices[VERTEX_X4];
    vertices[3].vertices.y = calculatedVertices[VERTEX_Y4];
    vertices[3].vertices.z = 0.0f;
    vertices[3].texCoords.u = self->uvs[VERTEX_X4];
    vertices[3].texCoords.v = self->uvs[VERTEX_Y4];
}

void spMeshAttachment_updateVertices (spMeshAttachment* self, spSlot* slot, V3F_C4B_T2F* vertices, bool premultipliedAlpha)
{
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
    
    for (int i = 0; i < self->verticesLength / 2; i++)
    {
        int vertexDataId = i * 4;
        
        vertices[i].vertices.x = self->worldVertices[vertexDataId];
        vertices[i].vertices.y = self->worldVertices[vertexDataId + 1];
        vertices[i].vertices.z = 0.0f;
        
        vertices[i].texCoords.u = self->worldVertices[vertexDataId + 2];
        vertices[i].texCoords.v = self->worldVertices[vertexDataId + 3];
        
        vertices[i].colors.r = r;
        vertices[i].colors.g = g;
        vertices[i].colors.b = b;
        vertices[i].colors.a = a;
    }
}