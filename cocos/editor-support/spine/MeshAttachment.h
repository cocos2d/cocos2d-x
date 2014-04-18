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
//  MeshAttachment.h
//  spine-cocos2d-iphone-ios
//
//  Created by Wojciech Trzasko CodingFingers on 18.02.2014.
//

#ifndef spine_cocos2d_iphone_ios_MeshAttachment_h
#define spine_cocos2d_iphone_ios_MeshAttachment_h


#include <spine/Attachment.h>
#include <spine/Atlas.h>
#include <spine/Slot.h>

#ifdef __cplusplus
extern "C" {
#endif
    
typedef struct spMeshAttachment spMeshAttachment;
struct spMeshAttachment {
    
    spAttachment super;
    
    float x, y, scaleX, scaleY, rotation, width, height;
    
    void* rendererObject;
    
    float* vertices;
    int verticesLength;
    
    int* trianglesIndices;
    int trianglesIndicesLength;
    
    float* worldVertices;
    int worldVerticesLength;
    
    float u;
    float v;
    float u2;
    float v2;
    int hullLength;
    float* edges;
};

spMeshAttachment* spMeshAttachment_create(const char* name);
void spMeshAttachment_setUVs(spMeshAttachment* self, float u, float v, float u2, float v2, int /*bool*/ rotate);
void spMeshAttachment_setMesh(spMeshAttachment* self, float* vertices, int verticesLength, int* triangles, int trianglesLength, float* uvs);
void spMeshAttachment_computeWorldVertices(spMeshAttachment* self, float x, float y, spBone* bone);
    
#ifdef SPINE_SHORT_NAMES
    typedef spMeshAttachment MeshAttachment;
#define MeshAttachment_create(...)                  spMeshAttachment_create(__VA_ARGS__)
#define MeshAttachment_setUVs(...)                  spMeshAttachment_setUVs(__VA_ARGS__)
#define MeshAttachment_updateOffset(...)            spMeshAttachment_updateOffset(__VA_ARGS__)
#define MeshAttachment_computeWorldVertices(...)    spMeshAttachment_computeWorldVertices(__VA_ARGS__)
#endif
    
#ifdef __cplusplus
}
#endif

#endif