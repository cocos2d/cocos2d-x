/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/


#include "renderer/CCQuadCommand.h"
#include "ccGLStateCache.h"

NS_CC_BEGIN

QuadCommand::QuadCommand()
:RenderCommand()
,_viewport(0)
,_depth(0)
,_textureID(0)
,_blendType(BlendFunc::DISABLE)
,_quadCount(0)
,_capacity(0)
{
    _type = RenderCommand::Type::QUAD_COMMAND;
    _shader = nullptr;
    _quad = nullptr;
}

void QuadCommand::init(int viewport, int32_t depth, GLuint textureID, GLProgram* shader, BlendFunc blendType, V3F_C4B_T2F_Quad* quad, ssize_t quadCount, const kmMat4 &mv)
{
    _viewport = viewport;
    _depth = depth;
    _textureID = textureID;
    _blendType = blendType;
    _quadCount = quadCount;
    _shader = shader;

    if(quadCount > _capacity ) {
        //TODO find a better way to manage quads, current way will result in memory be wasted
//        _quad = (V3F_C4B_T2F_Quad*)malloc(sizeof(V3F_C4B_T2F_Quad) * quadCount);
        _quad = (V3F_C4B_T2F_Quad*) realloc(_quad, sizeof(*quad) * quadCount );
        _capacity = quadCount;
    }

    kmMat4 p, mvp;
    kmGLGetMatrix(KM_GL_PROJECTION, &p);

    kmMat4Multiply(&mvp, &p, &mv);


    _quadCount = quadCount;
    memcpy(_quad, quad, sizeof(V3F_C4B_T2F_Quad) * quadCount);

    for(int i=0; i<quadCount; ++i) {
        V3F_C4B_T2F_Quad *q = &_quad[i];

        kmVec3 vec1, out1;
        vec1.x = q->bl.vertices.x;
        vec1.y = q->bl.vertices.y;
        vec1.z = q->bl.vertices.z;
        kmVec3TransformCoord(&out1, &vec1, &mvp);
        q->bl.vertices.x = out1.x;
        q->bl.vertices.y = out1.y;
        q->bl.vertices.z = out1.z;

        kmVec3 vec2, out2;
        vec2.x = q->br.vertices.x;
        vec2.y = q->br.vertices.y;
        vec2.z = q->br.vertices.z;
        kmVec3TransformCoord(&out2, &vec2, &mvp);
        q->br.vertices.x = out2.x;
        q->br.vertices.y = out2.y;
        q->br.vertices.z = out2.z;

        kmVec3 vec3, out3;
        vec3.x = q->tr.vertices.x;
        vec3.y = q->tr.vertices.y;
        vec3.z = q->tr.vertices.z;
        kmVec3TransformCoord(&out3, &vec3, &mvp);
        q->tr.vertices.x = out3.x;
        q->tr.vertices.y = out3.y;
        q->tr.vertices.z = out3.z;

        kmVec3 vec4, out4;
        vec4.x = q->tl.vertices.x;
        vec4.y = q->tl.vertices.y;
        vec4.z = q->tl.vertices.z;
        kmVec3TransformCoord(&out4, &vec4, &mvp);
        q->tl.vertices.x = out4.x;
        q->tl.vertices.y = out4.y;
        q->tl.vertices.z = out4.z;
    }
}

QuadCommand::~QuadCommand()
{
    free(_quad);
}

int64_t QuadCommand::generateID()
{
    _id = 0;

    //Generate Material ID
    //TODO fix shader ID generation
    CCASSERT(_shader->getProgram() < pow(2,10), "ShaderID is greater than 2^10");
    //TODO fix texture ID generation
    CCASSERT(_textureID < pow(2,18), "TextureID is greater than 2^18");

    //TODO fix blend id generation
    int blendID = 0;
    if(_blendType == BlendFunc::DISABLE)
    {
        blendID = 0;
    }
    else if(_blendType == BlendFunc::ALPHA_PREMULTIPLIED)
    {
        blendID = 1;
    }
    else if(_blendType == BlendFunc::ALPHA_NON_PREMULTIPLIED)
    {
        blendID = 2;
    }
    else if(_blendType == BlendFunc::ADDITIVE)
    {
        blendID = 3;
    }
    else
    {
        blendID = 4;
    }

    //TODO Material ID should be part of the ID
    //
    // Temporal hack (later, these 32-bits should be packed in 24-bits
    //
    // +---------------------+-------------------+----------------------+
    // | Shader ID (10 bits) | Blend ID (4 bits) | Texture ID (18 bits) |
    // +---------------------+-------------------+----------------------+

    _materialID = (int32_t)_shader->getProgram() << 22
            | (int32_t)blendID << 18
            | (int32_t)_textureID << 0;

    //Generate RenderCommandID
    _id = (int64_t)_viewport << 61
            | (int64_t)1 << 60 //translucent
            | (int64_t)_depth << 36;

    return _id;
}

void QuadCommand::useMaterial()
{
    _shader->use();

    _shader->setUniformsForBuiltins();

    //Set texture
    GL::bindTexture2D(_textureID);

    //set blend mode
    GL::blendFunc(_blendType.src, _blendType.dst);
}

NS_CC_END