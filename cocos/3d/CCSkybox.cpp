/****************************************************************************
    Copyright (c) 2014 Chukong Technologies Inc.

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

#include "CCSkybox.h"
#include "CCTextureCube.h"

NS_CC_BEGIN

Skybox::Skybox()
    : _vao(0)
    , _vertexBuffer(0)
    , _indexBuffer(0)
    ,_texture(nullptr)
{
}

Skybox::~Skybox()
{
    glDeleteBuffers(1, &_vertexBuffer);
    glDeleteBuffers(1, &_indexBuffer);

    _vertexBuffer = 0;
    _indexBuffer = 0;

    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glDeleteVertexArrays(1, &_vao);
        GL::bindVAO(0);
        _vao = 0;
    }

    _texture->release();
}

bool Skybox::init()
{
    // create and set our custom shader
    auto shader = GLProgram::createWithFilenames("Sprite3DTest/skybox.vert", "Sprite3DTest/skybox.frag");
    auto state = GLProgramState::create(shader);
    setGLProgramState(state);

    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glGenVertexArrays(1, &_vao);
        GL::bindVAO(_vao);
    }

    initBuffers();

    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), nullptr);

        GL::bindVAO(0);
    }

    CHECK_GL_ERROR_DEBUG();

    return true;
}

void Skybox::initBuffers()
{
    // init vertex buffer object
    Vec3 vexBuf[] =
    {
        Vec3(1, -1, 1),  Vec3(1, 1, 1),  Vec3(-1, 1, 1),  Vec3(-1, -1, 1),
        Vec3(1, -1, -1), Vec3(1, 1, -1), Vec3(-1, 1, -1), Vec3(-1, -1, -1)
    };

    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vexBuf), vexBuf, GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // init index buffer object
    unsigned char idxBuf[] = { 2, 1, 0, 3, 2, 0, 1, 5, 4, 1, 4, 0, 4, 5, 6, 4, 6, 7, 7, 6, 2, 7, 2, 3 };

    glGenBuffers(1, &_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idxBuf), idxBuf, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Skybox::draw(Renderer* renderer, const Mat4& transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(Skybox::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void Skybox::onDraw(const Mat4& transform, uint32_t flags)
{
    auto state = getGLProgramState();
    state->applyGLProgram(transform);
    state->applyUniforms();

    GLboolean   depthFlag = glIsEnabled(GL_DEPTH_TEST);
    GLint		depthFunc;
    glGetIntegerv(GL_DEPTH_FUNC, &depthFunc);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    if (Configuration::getInstance()->supportsShareableVAO())
    {
        GL::bindVAO(_vao);
    }
    else
    {
        GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION);

        glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), nullptr);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    }

    glDrawElements(GL_TRIANGLES, (GLsizei)36, GL_UNSIGNED_BYTE, nullptr);

    if (Configuration::getInstance()->supportsShareableVAO())
    {
        GL::bindVAO(0);
    }
    else
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 8);

    glDepthFunc(depthFunc);
    if (!depthFlag)
        glDisable(GL_DEPTH_TEST);

    CHECK_GL_ERROR_DEBUG();
}

void Skybox::setTexture(TextureCube* texture)
{
    CCASSERT(texture != nullptr, __FUNCTION__);

    _texture = texture;
    _texture->retain();

    auto state = getGLProgramState();
    state->setUniformTexture("u_Env", _texture);
}

NS_CC_END
