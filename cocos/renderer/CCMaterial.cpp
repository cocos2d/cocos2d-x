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

#include "renderer/CCMaterial.h"
#include "renderer/CCTechnique.h"
#include "renderer/CCGLProgramState.h"

NS_CC_BEGIN

Material* Material::createWithFilename(const std::string& path)
{
    return nullptr;
}

Material* Material::createWithGLStateProgram(GLProgramState* programState)
{
    return new (std::nothrow) Material(programState);
}

Material::Material(cocos2d::GLProgramState *state)
{
    auto technique = Technique::createWithGLProgramState(state);
    _techniques.pushBack(technique);

    // weak pointer
    _currentTechnique = technique;
}

std::string Material::getName() const
{
    return _name;
}

Material::Material()
{
}

Material::~Material()
{
}

Technique* Material::getTechnique() const
{
    return _currentTechnique;
}
Technique* Material::getTechniqueByName(const std::string& name)
{
    for(const auto& technique : _techniques) {
        if( technique->getName() == name)
            return technique;
    }
    return nullptr;
}

Technique* Material::getTechniqueByIndex(ssize_t index)
{
    CC_ASSERT(index>=0 && index<_techniques.size() && "Invalid size");

    return _techniques.at(index);
}

void Material::addTechnique(Technique* technique)
{
    _techniques.pushBack(technique);
}

void Material::setTechnique(const std::string& techniqueName)
{
    auto technique = getTechniqueByName(techniqueName);
    if (technique)
        _currentTechnique = technique;
}

ssize_t Material::getTechniqueCount() const
{
    return _techniques.size();
}

NS_CC_END
