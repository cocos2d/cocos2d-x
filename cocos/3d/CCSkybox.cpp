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
#include "3d/CCSkybox.h"
#include "base/ccMacros.h"
#include "base/CCConfiguration.h"
#include "base/CCDirector.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCRenderState.h"
#include "renderer/CCTextureCube.h"
#include "renderer/ccShaders.h"
#include "2d/CCCamera.h"

NS_CC_BEGIN

Skybox::Skybox():
    _texture(nullptr)
{
}

Skybox::~Skybox()
{
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
    _customCommand.setTransparent(false);
    _customCommand.set3D(true);

    _customCommand.setBeforeCallback(CC_CALLBACK_0(Skybox::onBeforeDraw, this));
    _customCommand.setAfterCallback(CC_CALLBACK_0(Skybox::onAfterDraw, this));

    // create and set our custom shader
    auto* program = backend::Program::getBuiltinProgram(backend::ProgramType::SKYBOX_3D);
    _programState = new backend::ProgramState(program);

    auto &pipelineDescriptor = _customCommand.getPipelineDescriptor();
    auto layout = _programState->getVertexLayout();

    pipelineDescriptor.programState = _programState;
    // disable blend
    pipelineDescriptor.blendDescriptor.blendEnabled = false; 
    const auto& attributeInfo = _programState->getProgram()->getActiveAttributes();
    const auto& iter = attributeInfo.find(shaderinfos::attribute::ATTRIBUTE_NAME_POSITION);
    if(iter != attributeInfo.end())
    {
        layout->setAttribute(shaderinfos::attribute::ATTRIBUTE_NAME_POSITION, iter->second.location, backend::VertexFormat::FLOAT3, 0, false);
    }
    layout->setLayout(sizeof(Vec3));

    _uniformColorLoc = _programState->getUniformLocation("u_color");
    _uniformCameraRotLoc = _programState->getUniformLocation("u_cameraRot");
    _uniformEnvLoc = _programState->getUniformLocation("u_Env");

    initBuffers();
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
    texture->release();
    return true;
}

void Skybox::initBuffers()
{

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

    uint16_t idxBuf[] = { 0, 1, 2, 0, 2, 3 };

    _customCommand.createVertexBuffer(sizeof(Vec3), sizeof(vexBuf), CustomCommand::BufferUsage::STATIC);
    _customCommand.createIndexBuffer(CustomCommand::IndexFormat::U_SHORT, 6, CustomCommand::BufferUsage::STATIC);

    _customCommand.updateVertexBuffer(&vexBuf[0], sizeof(vexBuf));
    _customCommand.updateIndexBuffer(&idxBuf[0], sizeof(idxBuf));
}

void Skybox::draw(Renderer* renderer, const Mat4& transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder);

    renderer->addCommand(&_customCommand);

    auto camera = Camera::getVisitingCamera();

    Mat4 cameraModelMat = camera->getNodeToWorldTransform();
    Mat4 projectionMat = camera->getProjectionMatrix();
    // Ignore the translation
    cameraModelMat.m[12] = cameraModelMat.m[13] = cameraModelMat.m[14] = 0;
    // prescale the matrix to account for the camera fov
    cameraModelMat.scale(1 / projectionMat.m[0], 1 / projectionMat.m[5], 1.0);

    Vec4 color(_displayedColor.r / 255.f, _displayedColor.g / 255.f, _displayedColor.b / 255.f, 1.f);
    _programState->setUniform(_uniformColorLoc, &color, sizeof(color));
    _programState->setUniform(_uniformCameraRotLoc, cameraModelMat.m, sizeof(cameraModelMat.m));

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 4);
}

void Skybox::setTexture(TextureCube* texture)
{
    CCASSERT(texture != nullptr, __FUNCTION__);
    CC_SAFE_RELEASE_NULL(_texture);
    texture->retain();
    _texture = texture;
    _programState->setTexture(_uniformEnvLoc, 0, _texture->getBackendTexture());
}

void Skybox::reload()
{
    initBuffers();
}

void Skybox::onBeforeDraw()
{
    auto *renderer = Director::getInstance()->getRenderer();
    
    _rendererDepthTestEnabled = renderer->getDepthTest();
    _rendererDepthCmpFunc = renderer->getDepthCompareFunction();
    _rendererCullMode = renderer->getCullMode();

    renderer->setDepthTest(true);
    renderer->setDepthCompareFunction(backend::CompareFunction::LESS_EQUAL);
    renderer->setCullMode(CullMode::BACK);
}

void Skybox::onAfterDraw()
{
    auto *renderer = Director::getInstance()->getRenderer();
    renderer->setDepthTest(_rendererDepthTestEnabled);
    renderer->setDepthCompareFunction(_rendererDepthCmpFunc);
    renderer->setCullMode(_rendererCullMode);
}

NS_CC_END
