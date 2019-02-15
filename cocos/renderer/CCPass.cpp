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

 Ideas taken from:
 - GamePlay3D: http://gameplay3d.org/
 - OGRE3D: http://www.ogre3d.org/
 - Qt3D: http://qt-project.org/
 ****************************************************************************/
#include "renderer/CCPass.h"
#include <xxhash.h>
#include "renderer/CCTexture2D.h"
#include "renderer/CCTechnique.h"
#include "renderer/CCMaterial.h"
#include "renderer/backend/ProgramState.h"
#include "3d/CCMeshVertexIndexData.h"
#include "3d/CCVertexAttribBinding.h"
#include "base/CCDirector.h"
#include "renderer/CCRenderer.h"

#include "base/ccTypes.h"
#include "base/ccUtils.h"
#include "2d/CCNode.h"

NS_CC_BEGIN

//uniform names

static const char          *s_dirLightUniformColorName = "u_DirLightSourceColor";
static const char          *s_dirLightUniformDirName = "u_DirLightSourceDirection";

static const char          *s_pointLightUniformColorName = "u_PointLightSourceColor";
static const char          *s_pointLightUniformPositionName = "u_PointLightSourcePosition";
static const char          *s_pointLightUniformRangeInverseName = "u_PointLightSourceRangeInverse";

static const char          *s_spotLightUniformColorName = "u_SpotLightSourceColor";
static const char          *s_spotLightUniformPositionName = "u_SpotLightSourcePosition";
static const char          *s_spotLightUniformDirName = "u_SpotLightSourceDirection";
static const char          *s_spotLightUniformInnerAngleCosName = "u_SpotLightSourceInnerAngleCos";
static const char          *s_spotLightUniformOuterAngleCosName = "u_SpotLightSourceOuterAngleCos";
static const char          *s_spotLightUniformRangeInverseName = "u_SpotLightSourceRangeInverse";

static const char          *s_ambientLightUniformColorName = "u_AmbientLightSourceColor";

Pass* Pass::create(Technique* technique)
{
    auto pass = new (std::nothrow) Pass();
    if (pass && pass->init(technique))
    {
        pass->autorelease();
        return pass;
    }
    CC_SAFE_DELETE(pass);
    return nullptr;
}

Pass* Pass::createWithProgramState(Technique* technique, backend::ProgramState* programState)
{
    auto pass = new (std::nothrow) Pass();
    if (pass && pass->initWithProgramState(technique, programState))
    {
        pass->autorelease();
        return pass;
    }
    CC_SAFE_DELETE(pass);
    return nullptr;
}

bool Pass::init(Technique* technique)
{
    _technique = technique;
    return true;
}

bool Pass::initWithProgramState(Technique* technique, backend::ProgramState *programState)
{
    _technique = technique;
    setProgramState(programState);
    return true;
}

Pass::Pass()
{
    //_customCommand.set3D(true);
    
    //TODO: set _customCommand's vertex layout.
    //auto& vertexLayout = _customCommand.getPipelineDescriptor().vertexLayout;
    //vertexLayout.setAtrribute("a_position", 0, backend::VertexFormat::FLOAT_R32G32B32, 0, false);
    //vertexLayout.setAtrribute("a_texCoord", 1, backend::VertexFormat::FLOAT_R32G32, 6 * sizeof(float), false);
    //vertexLayout.setLayout(8 * sizeof(float), backend::VertexStepMode::VERTEX);

    _beforeVisitCmd.func = CC_CALLBACK_0(Pass::onBeforeVisitCmd, this);
    _afterVisitCmd.func = CC_CALLBACK_0(Pass::onAfterVisitCmd, this);

}

Pass::~Pass()
{
    CC_SAFE_RELEASE(_vertexAttribBinding);
    CC_SAFE_RELEASE(_programState);
}

Pass* Pass::clone() const
{
    auto pass = new (std::nothrow) Pass();
    if (pass)
    {
        //RenderState::cloneInto(pass);
        pass->_renderState = _renderState;

        pass->setProgramState(_programState->clone());
        
        pass->_vertexAttribBinding = _vertexAttribBinding;
        CC_SAFE_RETAIN(pass->_vertexAttribBinding);

        pass->setTechnique(_technique);

        pass->autorelease();
    }
    return pass;
}

backend::ProgramState* Pass::getProgramState() const
{
   return _programState;
}

void Pass::setProgramState(backend::ProgramState* programState)
{
    if (_programState != programState)
    {
        CC_SAFE_RELEASE(_programState);
        _programState = programState;
        CC_SAFE_RETAIN(_programState);
        _customCommand.getPipelineDescriptor().programState = _programState;
        initUniformLocations();
        _hashDirty = true;
    }
}

void Pass::initUniformLocations()
{
    auto *ps = _programState;

    _locMVPMatrix = ps->getUniformLocation("u_MVPMatrix");
    _locMVMatrix = ps->getUniformLocation("u_MVMatrix");
    _locPMatrix = ps->getUniformLocation("u_PMatrix");
    _locNormalMatrix = ps->getUniformLocation("u_NormalMatrix");

    _locTexture = ps->getUniformLocation("u_texture");
    
    _locColor = ps->getUniformLocation("u_color");
    _locMatrixPalette = ps->getUniformLocation("u_matrixPalette");

    _locDirLightColor = ps->getUniformLocation(s_dirLightUniformColorName);
    _locDirLightDir = ps->getUniformLocation(s_dirLightUniformDirName);

    _locPointLightColor = ps->getUniformLocation(s_pointLightUniformColorName);
    _locPointLightPosition = ps->getUniformLocation(s_pointLightUniformPositionName);
    _locPointLightRangeInverse = ps->getUniformLocation(s_pointLightUniformRangeInverseName);

    _locSpotLightColor = ps->getUniformLocation(s_spotLightUniformColorName);
    _locSpotLightPosition = ps->getUniformLocation(s_spotLightUniformPositionName);
    _locSpotLightDir = ps->getUniformLocation(s_spotLightUniformDirName);
    _locSpotLightInnerAngleCos = ps->getUniformLocation(s_spotLightUniformInnerAngleCosName);
    _locSpotLightOuterAngleCos = ps->getUniformLocation(s_spotLightUniformOuterAngleCosName);
    _locSpotLightRangeInverse = ps->getUniformLocation(s_spotLightUniformRangeInverseName);

    _locAmbientLigthColor = ps->getUniformLocation(s_ambientLightUniformColorName);
}

//uint32_t Pass::getHash() const
//{
//    if (_hashDirty || _state->isDirty())
//    {
//        //FIXME: loose information?
//        uint32_t program = (uint32_t)(intptr_t)(_programState->getProgram());
//        uint32_t textureid = _texture ? _texture->getName() : -1;
//        uint32_t stateblockid = _state->getHash();
//
//        _hash = program ^ textureid ^ stateblockid;
//
//        _hashDirty = false;
//    }
//
//    return _hash;
//}

//void Pass::bind(const Mat4& modelView)
//{
//    bind(modelView, true);
//}

//void Pass::bind(const Mat4& modelView, bool bindAttributes)
//{
//    // vertex attribs
//    if (bindAttributes && _vertexAttribBinding)
//        _vertexAttribBinding->bind();
//
//    auto glprogramstate = _glProgramState ? _glProgramState : getTarget()->getGLProgramState();
//
//    glprogramstate->applyGLProgram(modelView);
//    glprogramstate->applyUniforms();
//
//    //set render state
//    RenderState::bind(this);
//}

void Pass::draw(float globalZOrder, backend::Buffer* vertexBuffer, backend::Buffer* indexBuffer,
                CustomCommand::PrimitiveType primitive, CustomCommand::IndexFormat indexFormat,
                unsigned int indexCount, const Mat4& modelView)
{
    _customCommand.init(globalZOrder, BlendFunc::ALPHA_PREMULTIPLIED);
    _customCommand.setPrimitiveType(primitive);
    _customCommand.setIndexBuffer(indexBuffer, indexFormat);
    _customCommand.setVertexBuffer(vertexBuffer);
    _customCommand.setIndexDrawInfo(0, indexCount);

    auto &matrixP = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    auto mvp = matrixP * modelView;
    _programState->setUniform(_locMVPMatrix, mvp.m);
    if (_locMVMatrix) 
    {
        _programState->setUniform(_locMVMatrix, modelView.m);
    }
    
    if (_locPMatrix)
    {
        _programState->setUniform(_locPMatrix, matrixP.m);
    }

    if (_locNormalMatrix)
    {
        auto normalMatrix = utils::getNormalMat3OfMat4(modelView);
        _programState->setUniform(_locNormalMatrix, normalMatrix.data(), sizeof(normalMatrix[0]) * normalMatrix.size());
    }

    auto *renderer = Director::getInstance()->getRenderer();

    _beforeVisitCmd.init(globalZOrder);
    _afterVisitCmd.init(globalZOrder);

    renderer->addCommand(&_beforeVisitCmd);
    renderer->addCommand(&_customCommand);
    renderer->addCommand(&_afterVisitCmd);
}

void Pass::onBeforeVisitCmd()
{
    auto *renderer = Director::getInstance()->getRenderer();
    //_oldDepthEnabledState = renderer->getDepthTest();

    auto &pipelineDescriptor = _customCommand.getPipelineDescriptor();

    _rendererDepthTestEnabled = renderer->getDepthTest();
    _rendererDepthCmpFunc = renderer->getDepthCompareFunction();
    _rendererCullMode = renderer->getCullMode();
    
    _renderState.bindPass(this);
    renderer->setDepthTest(true);
}

void Pass::onAfterVisitCmd()
{
    auto *renderer = Director::getInstance()->getRenderer();
    _renderState.unbindPass(this);
    renderer->setDepthTest(_rendererDepthTestEnabled);
    renderer->setDepthCompareFunction(_rendererDepthCmpFunc);
    renderer->setCullMode(_rendererCullMode);
}


Node* Pass::getTarget() const
{
    CCASSERT(_technique && _technique->_material, "Pass must have a Technique and Material");

    Material *material = _technique->_material;
    return material->_target;
}

void Pass::setTechnique(Technique *technique)
{
    _technique = technique; //weak reference
}


//void Pass::unbind()
//{
//    RenderState::StateBlock::restore(0);
//
////    _vertexAttribBinding->unbind();
//}

void Pass::setVertexAttribBinding(VertexAttribBinding* binding)
{
    if (_vertexAttribBinding != binding)
    {
        CC_SAFE_RELEASE(_vertexAttribBinding);
        _vertexAttribBinding = binding;
        CC_SAFE_RETAIN(_vertexAttribBinding);
    }
}

VertexAttribBinding* Pass::getVertexAttributeBinding() const
{
    return _vertexAttribBinding;
}

void Pass::setUniformTexture(uint32_t slot, backend::Texture *tex)
{
    _programState->setTexture(_locTexture, slot, tex);
}

#define TRY_SET_UNIFORM(loc) \
    if(loc) { \
        _programState->setUniform(loc, data, (uint32_t)dataLen) ; \
    } \
    else \
    { \
     CCLOG("warning: failed to set uniform in %s", __FUNCTION__); \
    }


void Pass::setUniformColor(const void *data, size_t dataLen)
{
    TRY_SET_UNIFORM(_locColor);
}

void Pass::setUniformMatrixPalette(const void *data, size_t dataLen)
{
    TRY_SET_UNIFORM(_locMatrixPalette);
}


void Pass::setUniformDirLightColor(const void *data, size_t dataLen)
{
    TRY_SET_UNIFORM(_locDirLightColor);
}

void Pass::setUniformDirLightDir(const void *data, size_t dataLen)
{
    TRY_SET_UNIFORM(_locDirLightDir);
}

void Pass::setUniformPointLightColor(const void *data, size_t dataLen)
{
    TRY_SET_UNIFORM(_locPointLightColor);
}

void Pass::setUniformPointLightPosition(const void *data, size_t dataLen)
{
    TRY_SET_UNIFORM(_locPointLightPosition);
}

void Pass::setUniformPointLightRangeInverse(const void *data, size_t dataLen)
{
    TRY_SET_UNIFORM(_locPointLightRangeInverse);
}

void Pass::setUniformSpotLightColor(const void *data, size_t dataLen)
{
    TRY_SET_UNIFORM(_locSpotLightColor);
}

void Pass::setUniformSpotLightPosition(const void *data, size_t dataLen)
{
    TRY_SET_UNIFORM(_locSpotLightPosition);
}

void Pass::setUniformSpotLightDir(const void *data, size_t dataLen)
{
    TRY_SET_UNIFORM(_locSpotLightDir);
}

void Pass::setUniformSpotLightInnerAngleCos(const void *data, size_t dataLen)
{
    TRY_SET_UNIFORM(_locSpotLightInnerAngleCos);
}

void Pass::setUniformSpotLightOuterAngleCos(const void *data, size_t dataLen)
{
    TRY_SET_UNIFORM(_locSpotLightOuterAngleCos);
}

void Pass::setUniformSpotLightRangeInverse(const void *data, size_t dataLen)
{
    TRY_SET_UNIFORM(_locSpotLightRangeInverse);
}

void Pass::setUniformAmbientLigthColor(const void *data, size_t dataLen)
{
    TRY_SET_UNIFORM(_locAmbientLigthColor);
}



NS_CC_END
