/****************************************************************************
 Copyright (c) 2015-2017 Chukong Technologies Inc.
 
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

#include "physics3d/CCPhysics3D.h"
#include "base/CCConfiguration.h"
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCRenderState.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCGLProgramCache.h"

#if CC_USE_3D_PHYSICS

#if (CC_ENABLE_BULLET_INTEGRATION)

NS_CC_BEGIN

void Physics3DDebugDrawer::drawLine( const btVector3& from,const btVector3& to,const btVector3& color )
{
    int count = 2;
    ensureCapacity(count);

    Vec3 col = convertbtVector3ToVec3(color);

    V3F_V4F *lines = (V3F_V4F *)(_buffer + _bufferCount);
    lines[0].vertex = convertbtVector3ToVec3(from);
    lines[0].color = Vec4(col.x, col.y, col.z, 1.0f);
    lines[1].vertex = convertbtVector3ToVec3(to);
    lines[1].color = Vec4(col.x, col.y, col.z, 1.0f);

    _bufferCount += count;
    _dirty = true;
}

void Physics3DDebugDrawer::drawContactPoint( const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int /*lifeTime*/,const btVector3& color )
{
    drawLine(PointOnB, PointOnB + normalOnB * distance, color);
}

void Physics3DDebugDrawer::reportErrorWarning( const char* warningString )
{
    CCLOG("%s", warningString);
}

void Physics3DDebugDrawer::draw3dText( const btVector3& /*location*/,const char* /*textString*/ )
{

}

void Physics3DDebugDrawer::setDebugMode( int debugMode )
{
    _debugMode = debugMode;
}

int Physics3DDebugDrawer::getDebugMode() const 
{
    return _debugMode;
}

void Physics3DDebugDrawer::draw( Renderer *renderer)
{
    _customCommand.init(0, Mat4::IDENTITY, 0);
    _customCommand.func = CC_CALLBACK_0(Physics3DDebugDrawer::drawImplementation, this, Mat4::IDENTITY, 0);
    renderer->addCommand(&_customCommand);
}

Physics3DDebugDrawer::Physics3DDebugDrawer()
    : _vao(0)
    , _vbo(0)
    , _bufferCapacity(0)
    , _bufferCount(0)
    , _buffer(nullptr)
    , _blendFunc(BlendFunc::DISABLE)
    , _dirty(true)
    , _debugMode(DBG_DrawWireframe | DBG_DrawConstraints | DBG_DrawConstraintLimits)
{
    init();
}

Physics3DDebugDrawer::~Physics3DDebugDrawer()
{
    free(_buffer);
    
    if (_vao)
    {
        glDeleteVertexArrays(1, &_vao);
        _vao = 0;
    }
    if (_vbo)
    {
        glDeleteBuffers(1, &_vbo);
        _vbo = 0;
    }
}

void Physics3DDebugDrawer::ensureCapacity( int count )
{
    CCASSERT(count>=0, "capacity must be >= 0");

    if(_bufferCount + count > _bufferCapacity)
    {
        _bufferCapacity += MAX(_bufferCapacity, count);
        _buffer = (V3F_V4F*)realloc(_buffer, _bufferCapacity*sizeof(V3F_V4F));
    }
}

void Physics3DDebugDrawer::drawImplementation( const Mat4 &transform, uint32_t /*flags*/ )
{
    _program->use();
    _program->setUniformsForBuiltins(transform);
    glEnable(GL_DEPTH_TEST);

    GL::blendFunc(_blendFunc.src, _blendFunc.dst);

    if (_dirty)
    {
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(V3F_V4F) * _bufferCapacity, _buffer, GL_STREAM_DRAW);
        _dirty = false;
    }
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        GL::bindVAO(_vao);
    }
    else
    {
        GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);

        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        // vertex
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_V4F), (GLvoid *)offsetof(V3F_V4F, vertex));
        // color
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(V3F_V4F), (GLvoid *)offsetof(V3F_V4F, color));
    }

    glDrawArrays(GL_LINES, 0, _bufferCount);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,_bufferCount);

    glDisable(GL_DEPTH_TEST);
    RenderState::StateBlock::_defaultState->setDepthTest(false);
}

void Physics3DDebugDrawer::init()
{
    _program = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR);

    ensureCapacity(512);

    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glGenVertexArrays(1, &_vao);
        GL::bindVAO(_vao);
    }

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(V3F_V4F)* _bufferCapacity, _buffer, GL_STREAM_DRAW);

    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_V4F), (GLvoid *)offsetof(V3F_V4F, vertex));

    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(V3F_V4F), (GLvoid *)offsetof(V3F_V4F, color));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (Configuration::getInstance()->supportsShareableVAO())
    {
        GL::bindVAO(0);
    }
}

void Physics3DDebugDrawer::clear()
{
    _bufferCount = 0;
}

NS_CC_END

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif //CC_USE_3D_PHYSICS
