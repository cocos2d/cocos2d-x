/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
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

#include "base/ccMacros.h"
#include "base/CCConfiguration.h"
#include "base/CCDirector.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCRenderer.h"
#include "3d/CCSkybox.h"
#include "3d/CCTextureCube.h"

#include "2d/CCCamera.h"

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

Skybox* Skybox::create(const std::string& positive_x, const std::string& negative_x,
               const std::string& positive_y, const std::string& negative_y,
               const std::string& positive_z, const std::string& negative_z)
{
    auto ret = new (std::nothrow) Skybox();
    ret->init(positive_x, negative_x, positive_y, negative_y, positive_z, negative_z);
    
    ret->autorelease();
    return ret;
}

bool Skybox::init()
{
    // create and set our custom shader
    auto shader = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_3D_SKYBOX);
    auto state = GLProgramState::create(shader);
    state->setVertexAttribPointer(GLProgram::ATTRIBUTE_NAME_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), nullptr);
    setGLProgramState(state);

    initBuffers();

    CHECK_GL_ERROR_DEBUG();

    return true;
}

bool Skybox::init(const std::string& positive_x, const std::string& negative_x,
          const std::string& positive_y, const std::string& negative_y,
          const std::string& positive_z, const std::string& negative_z)
{
    auto texture = TextureCube::create(positive_x, negative_x, positive_y, negative_y, positive_z, negative_z);
    if (texture == nullptr)
        return false;
    
    init();
    setTexture(texture);
    return true;
}

void Skybox::initBuffers()
{
    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glGenVertexArrays(1, &_vao);
        GL::bindVAO(_vao);
    }

    // init vertex buffer object
    Vec3 vexBuf[] =
    {
        Vec3(1, -1, 1),  Vec3(1, 1, 1),  Vec3(-1, 1, 1),  Vec3(-1, -1, 1),
        Vec3(1, -1, -1), Vec3(1, 1, -1), Vec3(-1, 1, -1), Vec3(-1, -1, -1)
    };

    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vexBuf), vexBuf, GL_STATIC_DRAW);

    // init index buffer object
    const unsigned char idxBuf[] = {  2, 1, 0, 3, 2, 0, // font
        1, 5, 4, 1, 4, 0, // right
        4, 5, 6, 4, 6, 7, // back
        7, 6, 2, 7, 2, 3, // left
        2, 6, 5, 2, 5, 1, // up
        3, 0, 4, 3, 4, 7  // down
    };

    glGenBuffers(1, &_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idxBuf), idxBuf, GL_STATIC_DRAW);

    if (Configuration::getInstance()->supportsShareableVAO())
    {
        glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
        getGLProgramState()->applyAttributes(false);

        GL::bindVAO(0);
    }
}

void Skybox::draw(Renderer* renderer, const Mat4& transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(Skybox::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void Skybox::onDraw(const Mat4& transform, uint32_t flags)
{
    auto camera = Camera::getVisitingCamera();
    
    /*
     At beginning, we have a regular skybox at origin point.
     To render the skybox, we should keep camera at the center of skybox.
     So we need a translate matrix, which can transform origin point to camera pos.
     Camera's node to word transform matrix don't match our requement,
        because it maybe contain the scale, rotate, reflact... effects, which isn't need.
     First, we transform origin point to camera position by camera's node to world matrix.
     Second, we create a translate matrix with the origin point's world position.
     */
    Vec3 cameraPosInNode(0, 0, 0);
    Vec3 cameraPosInWorld;
    Mat4 cameraModelMat = camera->getNodeToWorldTransform();
    Mat4 trans = Mat4::IDENTITY;
    cameraModelMat.transformPoint(cameraPosInNode, &cameraPosInWorld);
    trans.translate(cameraPosInWorld);
    
    auto state = getGLProgramState();
    state->apply(trans);

    Vec4 color(_displayedColor.r / 255.f, _displayedColor.g / 255.f, _displayedColor.b / 255.f, 1.f);
    state->setUniformVec4("u_color", color);
    float scalf = (camera->getFarPlane() + camera->getNearPlane()) / 2;
    state->setUniformFloat("u_scalef", scalf);
    
    GLboolean depthFlag = glIsEnabled(GL_DEPTH_TEST);
    GLint depthFunc;
    glGetIntegerv(GL_DEPTH_FUNC, &depthFunc);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    GLboolean cullFlag = glIsEnabled(GL_CULL_FACE);
    GLint cullMode;
    glGetIntegerv(GL_CULL_FACE_MODE, &cullMode);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

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

    glCullFace(cullMode);
    if (!cullFlag)
        glDisable(GL_CULL_FACE);

    glDepthFunc(depthFunc);
    if (!depthFlag)
        glDisable(GL_DEPTH_TEST);

    CHECK_GL_ERROR_DEBUG();
}

void Skybox::setTexture(TextureCube* texture)
{
    CCASSERT(texture != nullptr, __FUNCTION__);

    texture->retain();

    if (_texture)
        _texture->release();

    _texture = texture;

    getGLProgramState()->setUniformTexture("u_Env", _texture);
}

void Skybox::reload()
{
    initBuffers();
}

NS_CC_END
