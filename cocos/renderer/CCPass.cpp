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

 Ideas taken from:
 - GamePlay3D: http://gameplay3d.org/
 - OGRE3D: http://www.ogre3d.org/
 - Qt3D: http://qt-project.org/
 ****************************************************************************/

#include "CCPass.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCTexture2D.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCTechnique.h"
#include "renderer/CCMaterial.h"

#include "base/ccTypes.h"
#include "2d/CCNode.h"

#include <xxhash.h>

NS_CC_BEGIN


Pass* Pass::create(Technique* technique)
{
    auto pass = new (std::nothrow) Pass();
    if (pass && pass->init(technique))
    {
        pass->autorelease();
        return pass;
    }
    return nullptr;
}

Pass* Pass::createWithGLProgramState(Technique* technique, GLProgramState* programState)
{
    auto pass = new (std::nothrow) Pass();
    if (pass && pass->initWithGLProgramState(technique, programState))
    {
        pass->autorelease();
        return pass;
    }
    return nullptr;
}

bool Pass::init(Technique* technique)
{
    _parent = technique;
    return true;
}

bool Pass::initWithGLProgramState(Technique* technique, GLProgramState *glProgramState)
{
    _parent = technique;
    _glProgramState = glProgramState;
    CC_SAFE_RETAIN(_glProgramState);
    return true;
}

Pass::Pass()
: _glProgramState(nullptr)
{
}

Pass::~Pass()
{
    CC_SAFE_RELEASE(_glProgramState);
}

GLProgramState* Pass::getGLProgramState() const
{
    return _glProgramState;
}

void Pass::setGLProgramState(GLProgramState* glProgramState)
{
    if ( _glProgramState != glProgramState) {
        CC_SAFE_RELEASE(_glProgramState);
        _glProgramState = glProgramState;
        CC_SAFE_RETAIN(_glProgramState);

        _hashDirty = true;
    }
}

uint32_t Pass::getHash() const
{
    if (_hashDirty || _state->isDirty()) {
        uint32_t glProgram = (uint32_t)_glProgramState->getGLProgram()->getProgram();
        uint32_t textureid = (uint32_t)_textures.at(0)->getName();
        uint32_t stateblockid = _state->getHash();

        _hash = glProgram ^ textureid ^ stateblockid;

//        _hash = XXH32((const void*)intArray, sizeof(intArray), 0);
        _hashDirty = false;
    }

    return _hash;
}

void Pass::bind(const Mat4& modelView)
{
    bind(modelView, true);
}

void Pass::bind(const Mat4& modelView, bool bindAttributes)
{
    auto glprogramstate = _glProgramState ? _glProgramState : getTarget()->getGLProgramState();

    glprogramstate->applyGLProgram(modelView);
    if (bindAttributes)
        glprogramstate->applyAttributes();
    glprogramstate->applyUniforms();

    //set render state
    RenderState::bind(this);
}

Node* Pass::getTarget() const
{
    CCASSERT(_parent && _parent->_parent, "Pass must have a Technique and Material");

    Material *material = static_cast<Material*>(_parent->_parent);
    return material->_target;
}

void Pass::unbind()
{
    RenderState::StateBlock::restore(0);
}

NS_CC_END
