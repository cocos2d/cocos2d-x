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
#include "renderer/CCVertexAttribBinding.h"
#include "renderer/backend/ProgramState.h"
#include "3d/CCMeshVertexIndexData.h"
#include "base/CCDirector.h"
#include "renderer/CCRenderer.h"

#include "base/ccTypes.h"
#include "2d/CCNode.h"

NS_CC_BEGIN


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
    _parent = technique;
    return true;
}

bool Pass::initWithProgramState(Technique* technique, backend::ProgramState *programState)
{
    _parent = technique;
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
        RenderState::cloneInto(pass);

        pass->setProgramState(_programState->clone());
        
        //
        pass->_vertexAttribBinding = _vertexAttribBinding;
        CC_SAFE_RETAIN(pass->_vertexAttribBinding);

        pass->setParent(_parent);

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

        _hashDirty = true;
    }
}

uint32_t Pass::getHash() const
{
    if (_hashDirty || _state->isDirty())
    {
        //FIXME: loose information?
        uint32_t program = (uint32_t)(intptr_t)(_programState->getProgram());
        uint32_t textureid = _texture ? _texture->getName() : -1;
        uint32_t stateblockid = _state->getHash();

        _hash = program ^ textureid ^ stateblockid;

        _hashDirty = false;
    }

    return _hash;
}

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

    const auto& projectionMat = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    Mat4 finalMat = projectionMat * modelView;
    auto location = _programState->getUniformLocation("u_MVPMatrix");
    _programState->setUniform(location, finalMat.m, sizeof(finalMat.m));

    _customCommand.getPipelineDescriptor().programState = _programState;

    Director::getInstance()->getRenderer()->addCommand(&_customCommand);

    RenderState::bind(this);
}

Node* Pass::getTarget() const
{
    CCASSERT(_parent && _parent->_parent, "Pass must have a Technique and Material");

    Material *material = static_cast<Material*>(_parent->_parent);
    return material->_target;
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


NS_CC_END
