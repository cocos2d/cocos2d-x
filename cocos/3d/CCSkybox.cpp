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

#include "base/ccMacros.h"
#include "base/CCConfiguration.h"
#include "base/CCDirector.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCRenderState.h"
#include "renderer/CCTextureCube.h"
#include "3d/CCSkybox.h"
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
	// The skybox is rendered using a purpose-built shader which makes use of
	// the shader language's inherent support for cubemaps. Hence there is no
	// need to build a cube mesh. All that is needed is a single quad that
	// covers the entire screen. The vertex shader will draw the appropriate
	// view of the cubemap onto that quad.
	//
	// The vertex shader does not apply either the model/view matrix or the
	// projection matrix, so the appropriate quad is one with unit coordinates
	// in the x and y dimensions. Such a quad will exactly cover the screen.
	// To ensure that the skybox is rendered behind all other objects, z needs
	// to be 1.0, but the vertex shader overwrites z to 1.0, so - for the sake
	// of z-buffering - it is unimportant what we set it to for the vertices
	// of the quad.
	//
	// The quad vertex positions are also used in deriving a direction
	// vector for the cubemap lookup. We choose z = -1 which matches the
	// negative-z pointing direction of the camera and gives a field of
	// view of 90deg in both x and y, if not otherwise adjusted. That fov
	// is then adjusted to exactly match the camera by applying a prescaling
	// to the camera's world transformation before sending it to the shader.

    // init vertex buffer object
    Vec3 vexBuf[] =
    {
        Vec3(1, -1, -1), Vec3(1, 1, -1), Vec3(-1, 1, -1), Vec3(-1, -1, -1)
    };

    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vexBuf), vexBuf, GL_STATIC_DRAW);

    // init index buffer object
    const unsigned char idxBuf[] = {0, 1, 2, 0, 2, 3};

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
    _customCommand.setTransparent(false);
    _customCommand.set3D(true);
    renderer->addCommand(&_customCommand);
}

void Skybox::onDraw(const Mat4& transform, uint32_t /*flags*/)
{
    auto camera = Camera::getVisitingCamera();
    
    Mat4 cameraModelMat = camera->getNodeToWorldTransform();
    Mat4 projectionMat = camera->getProjectionMatrix();
    // Ignore the translation
    cameraModelMat.m[12] = cameraModelMat.m[13] = cameraModelMat.m[14] = 0;
    // prescale the matrix to account for the camera fov
    cameraModelMat.scale(1 / projectionMat.m[0], 1 / projectionMat.m[5], 1.0);
    
    auto state = getGLProgramState();
    state->apply(transform);

    Vec4 color(_displayedColor.r / 255.f, _displayedColor.g / 255.f, _displayedColor.b / 255.f, 1.f);
    state->setUniformVec4("u_color", color);
    state->setUniformMat4("u_cameraRot", cameraModelMat);

    glEnable(GL_DEPTH_TEST);
    RenderState::StateBlock::_defaultState->setDepthTest(true);

    glDepthFunc(GL_LEQUAL);
    RenderState::StateBlock::_defaultState->setDepthFunction(RenderState::DEPTH_LEQUAL);

    glEnable(GL_CULL_FACE);
    RenderState::StateBlock::_defaultState->setCullFace(true);

    glCullFace(GL_BACK);
    RenderState::StateBlock::_defaultState->setCullFaceSide(RenderState::CULL_FACE_SIDE_BACK);
    
    glDisable(GL_BLEND);
    RenderState::StateBlock::_defaultState->setBlend(false);

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

    glDrawElements(GL_TRIANGLES, (GLsizei)6, GL_UNSIGNED_BYTE, nullptr);

    if (Configuration::getInstance()->supportsShareableVAO())
    {
        GL::bindVAO(0);
    }
    else
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 4);

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
