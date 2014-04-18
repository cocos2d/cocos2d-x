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

//
//  MeshAttachment.c
//  spine-cocos2d-iphone-ios
//
//  Created by Wojciech Trzasko CodingFingers on 18.02.2014.
//

#include <stdio.h>

#include <spine/MeshAttachment.h>
#include <spine/extension.h>

void _spMeshAttachment_dispose (spAttachment* attachment) {
  spMeshAttachment* self = SUB_CAST(spMeshAttachment, attachment);
    
  _spAttachment_deinit(attachment);
    
    FREE(self -> vertices);
    FREE(self -> trianglesIndices);
    FREE(self -> worldVertices);
    
    FREE(self -> edges);
    
  FREE(self);
}

spMeshAttachment* spMeshAttachment_create(const char* name)
{
    spMeshAttachment* self = NEW(spMeshAttachment);
    
    self -> u = 0;
    self -> v = 0;
    self -> u2 = 1;
    self -> v2 = 1;
    
    _spAttachment_init(SUPER(self), name, ATTACHMENT_MESH, _spMeshAttachment_dispose);
    return self;
}

void spMeshAttachment_setUVs(spMeshAttachment* self, float u, float v, float u2, float v2, int /*bool*/ rotate)
{
    self -> u = u;
    self -> v = v;
    self -> u2 = u2;
    self -> v2 = v2;
};

void spMeshAttachment_setMesh(spMeshAttachment* self, float* vertices, int verticesLength, int* triangles, int trianglesLength, float* uvs)
{
    self -> vertices = vertices;
    self -> verticesLength = verticesLength;
    
    self -> trianglesIndices = triangles;
    self -> trianglesIndicesLength = trianglesLength;
    
    self -> worldVerticesLength = verticesLength / 2 * 4;
    if(self -> worldVertices == NULL || self -> worldVerticesLength != self -> worldVerticesLength) {
        
        /* Free previous world vertices array => check is not leaking */
        if(self -> worldVertices != NULL)
        {
            FREE(self -> worldVertices);
        }
        
        self -> worldVertices = MALLOC(float, self ->  worldVerticesLength);
    }
    
    float u, v, w, h;
    if (self -> rendererObject != NULL) {
        
        spAtlasRegion* region = ((spAtlasRegion*)self -> rendererObject);
        
        u = region -> u;
        v = region -> v;
        w = region -> u2 - u;
        h = region -> v2 - v;
    }
    else
    {
        u = v = 0;
        w = h = 1;
    }
    
    for (int i = 0, ii = 2, n = verticesLength;
         i < n;
         i += 2, ii += 4)
    {
        self -> worldVertices[ii] = self -> u + uvs[i] * w;
        self -> worldVertices[ii + 1] = self -> v + uvs[i + 1] * h;
    }
};

void spMeshAttachment_computeWorldVertices(spMeshAttachment* self, float x, float y, spBone* bone)
{
    float objectX = x + bone -> worldX;
    float objectY = y + bone -> worldY;
    
    float m00 = bone -> m00, m01 = bone -> m01, m10 = bone -> m10, m11 = bone -> m11;
    
    float* worldVertices = self -> worldVertices;
    int worldVerticesLength = self -> worldVerticesLength;
    
    float* vertices = self -> vertices;
    
//    float* vertices = worldVerticesLength > 0 ? _vertices : self -> worldVertices;
    
    for (int v = 0, w = 0, n = worldVerticesLength; w < n; v += 2, w += 4)
    {
        float vx = vertices[v];
        float vy = vertices[v + 1];
        
        worldVertices[w] = vx * m00 + vy * m01 + objectX;
        worldVertices[w + 1] = vx * m10 + vy * m11 + objectY;
    }
};