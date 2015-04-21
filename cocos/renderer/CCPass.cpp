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
    auto pass = new (std::nothrow) Pass(technique);
    pass->autorelease();
    return pass;
}

Pass* Pass::createWithGLProgramState(Technique* technique, GLProgramState* programState)
{
    auto pass = new (std::nothrow) Pass(technique, programState);
    pass->autorelease();
    return pass;
}

Pass::Pass(Technique* technique, GLProgramState *glProgramState)
: _glProgramState(glProgramState)
{
    CC_SAFE_RETAIN(_glProgramState);
}

Pass::Pass(Technique* technique)
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
    if (_hashDirty) {
        int glProgram = (int)_glProgramState->getGLProgram()->getProgram();
        int intArray[4] = { glProgram, (int)_textures.at(0)->getName(), (int)_blendFunc.src, (int)_blendFunc.dst};

        _hash = XXH32((const void*)intArray, sizeof(intArray), 0);
        _hashDirty = false;
    }

    return _hash;
}

void Pass::bind(const Mat4& modelView)
{
    if (_textures.size()>=0)
        GL::bindTexture2D(_textures.at(0)->getName());

    //set blend mode
    GL::blendFunc(_blendFunc.src, _blendFunc.dst);

    if (_glProgramState)
        _glProgramState->apply(modelView);
    else
        getTarget()->getGLProgramState()->apply(modelView);

}

Node* Pass::getTarget() const
{
    CCASSERT(_technique && _technique->_material, "Pass must have a Technique and Material");

    return _technique->_material->_target;
}

void Pass::unbind()
{

}

NS_CC_END
