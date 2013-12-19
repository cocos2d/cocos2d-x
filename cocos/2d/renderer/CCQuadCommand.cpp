/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org

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


#include "CCQuadCommand.h"
#include "ccGLStateCache.h"
#include "CCMaterialManager.h"
#include "kazmath/vec4.h"

NS_CC_BEGIN
RenderCommandPool<QuadCommand> QuadCommand::_commandPool;

QuadCommand::QuadCommand()
:RenderCommand()
,_textureID(0)
,_blendType(BlendFunc::DISABLE)
,_quadCount(0)
,_capacity(0)
{
    _type = RenderCommand::Type::QUAD_COMMAND;
    _shader = nullptr;
    _quad = nullptr;
}

void QuadCommand::init(int viewport, float depth, GLuint textureID, GLProgram* shader, BlendFunc blendType, V3F_C4B_T2F_Quad* quad, ssize_t quadCount, const kmMat4 &mv)
{
    RenderCommand::init(viewport, depth);
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
        
        applyTransformToPoint(&q->bl.vertices, &mvp);
        applyTransformToPoint(&q->br.vertices, &mvp);
        applyTransformToPoint(&q->tr.vertices, &mvp);
        applyTransformToPoint(&q->tl.vertices, &mvp);
    }
}

inline void QuadCommand::applyTransformToPoint(Vertex3F* point, const kmMat4* pMatrix)
{
    kmVec4 v;
    kmVec4 inV;
    kmVec4Fill(&inV, point->x, point->y, point->z, 1.0);
    kmVec4Transform(&v, &inV, pMatrix);
    
    point->x = v.x / v.w;
    point->y = v.y / v.w;
    point->z = v.z / v.w;
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
    CCASSERT(_shader->getProgram() < 64, "ShaderID is greater than 64");
    //TODO fix texture ID generation
    CCASSERT(_textureID < 1024, "TextureID is greater than 1024");

    int blendID = 0;
    blendID = MaterialManager::getInstance()->getBlendFuncID(_blendType);

    _materialID = (int32_t)_shader->getProgram() << 28
            | (int32_t)blendID << 24
            | (int32_t)_textureID << 14;

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

void QuadCommand::releaseToCommandPool()
{
    getCommandPool().pushBackCommand(this);
}

NS_CC_END
