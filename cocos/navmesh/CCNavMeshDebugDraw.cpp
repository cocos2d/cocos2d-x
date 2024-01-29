/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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
#include "navmesh/CCNavMeshDebugDraw.h"
#if CC_USE_NAVMESH

#include "renderer/CCGLProgramCache.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCRenderState.h"
#include "base/CCDirector.h"
#include "base/ccMacros.h"

NS_CC_BEGIN

NavMeshDebugDraw::NavMeshDebugDraw()
: _currentPrimitive(nullptr)
, _primitiveType(GL_POINTS)
, _currentDepthMask(true)
, _dirtyBuffer(true)
{
    _stateBlock = RenderState::StateBlock::create();
    _stateBlock->setCullFace(true);
    _stateBlock->setCullFaceSide(RenderState::CullFaceSide::CULL_FACE_SIDE_BACK);
    _stateBlock->setDepthTest(true);
    _stateBlock->setBlend(true);
    _stateBlock->setBlendFunc(BlendFunc::ALPHA_NON_PREMULTIPLIED);
    CC_SAFE_RETAIN(_stateBlock);
    
    _customCmd.set3D(true);
    _customCmd.setTransparent(true);
    _program = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR);
    glGenBuffers(1, &_vbo);
}

void NavMeshDebugDraw::vertex(const float /*x*/, const float /*y*/, const float /*z*/, unsigned int /*color*/, const float /*u*/, const float /*v*/)
{

}

void NavMeshDebugDraw::vertex(const float* pos, unsigned int color, const float* uv)
{
    vertex(pos[0], pos[1], pos[2], color, uv[0], uv[1]);
}

void NavMeshDebugDraw::vertex(const float x, const float y, const float z, unsigned int color)
{
    if (!_currentPrimitive) return;
    V3F_C4F vertex = { Vec3(x, y, z), getColor(color) };
    _vertices.push_back(vertex);
    _dirtyBuffer = true;
}

void NavMeshDebugDraw::vertex(const float* pos, unsigned int color)
{
    vertex(pos[0], pos[1], pos[2], color);
}

NavMeshDebugDraw::~NavMeshDebugDraw()
{
    CC_SAFE_RELEASE(_stateBlock);
    for (auto iter : _primitiveList){
        delete iter;
    }
    glDeleteBuffers(1, &_vbo);
}

void NavMeshDebugDraw::depthMask(bool state)
{
    _currentDepthMask = state;
}

void NavMeshDebugDraw::begin(duDebugDrawPrimitives prim, float size /*= 1.0f*/)
{
    if (_currentPrimitive) return;
    _currentPrimitive = new (std::nothrow) Primitive;
    _currentPrimitive->type = getPrimitiveType(prim);
    _currentPrimitive->depthMask = _currentDepthMask;
    _currentPrimitive->start = _vertices.size();
    _currentPrimitive->size = size;
}

void NavMeshDebugDraw::end()
{
    if (!_currentPrimitive) return;
    _currentPrimitive->end = _vertices.size();
    _primitiveList.push_back(_currentPrimitive);
    _currentPrimitive = nullptr;
}

Vec4 NavMeshDebugDraw::getColor(unsigned int col)
{
    const unsigned int r = col & 0xff;
    const unsigned int g = (col >> 8) & 0xff;
    const unsigned int b = (col >> 16) & 0xff;
    const unsigned int a = (col >> 24) & 0xff;

    float factor = 1.0f / 255.0f;
    return Vec4(r, g, b, a) * factor;
}

GLenum NavMeshDebugDraw::getPrimitiveType(duDebugDrawPrimitives prim)
{
    switch (prim)
    {
    case DU_DRAW_POINTS:
        return GL_POINTS;
    case DU_DRAW_LINES:
        return GL_LINES;
    case DU_DRAW_TRIS:
        return GL_TRIANGLES;
    default:
        return GL_POINTS;
    }
}

void NavMeshDebugDraw::drawImplement(const cocos2d::Mat4& transform, uint32_t /*flags*/)
{
    _program->use();
    _program->setUniformsForBuiltins(transform);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C4F), (GLvoid *)offsetof(V3F_C4F, position));
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(V3F_C4F), (GLvoid *)offsetof(V3F_C4F, color));
    if (_dirtyBuffer){
        glBufferData(GL_ARRAY_BUFFER, sizeof(V3F_C4F)* _vertices.size(), &_vertices[0], GL_STATIC_DRAW);
        _dirtyBuffer = false;
    }
    for (auto &iter : _primitiveList){
        if (iter->type == GL_POINTS)
            continue;
        
        _stateBlock->setDepthWrite(iter->depthMask);
        if (iter->type == GL_LINES){
            glLineWidth(iter->size);
        }
        _stateBlock->bind();
        glDrawArrays(iter->type, iter->start, iter->end - iter->start);
        CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, iter->end - iter->start);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void NavMeshDebugDraw::draw(Renderer* renderer)
{
    _customCmd.init(0, Mat4::IDENTITY, Node::FLAGS_RENDER_AS_3D);
    _customCmd.func = CC_CALLBACK_0(NavMeshDebugDraw::drawImplement, this, Mat4::IDENTITY, 0);
    renderer->addCommand(&_customCmd);
}

void NavMeshDebugDraw::clear()
{
    _vertices.clear();
    for (auto iter : _primitiveList){
        delete iter;
    }
    _primitiveList.clear();
}

NS_CC_END

#endif //CC_USE_NAVMESH
