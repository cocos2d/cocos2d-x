/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.

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
 
#include "ProgramMTL.h"
#include "ShaderModuleMTL.h"

CC_BACKEND_BEGIN

ProgramMTL::ProgramMTL(const std::string& vertexShader, const std::string& fragmentShader)
: Program(vertexShader, fragmentShader)
{
    _vertexShader = static_cast<ShaderModuleMTL*>(ShaderCache::newVertexShaderModule(vertexShader));
    _fragmentShader = static_cast<ShaderModuleMTL*>(ShaderCache::newFragmentShaderModule(fragmentShader));
    
    CC_SAFE_RETAIN(_vertexShader);
    CC_SAFE_RETAIN(_fragmentShader);
}

ProgramMTL::~ProgramMTL()
{
    CC_SAFE_RELEASE(_vertexShader);
    CC_SAFE_RELEASE(_fragmentShader);
}

UniformLocation ProgramMTL::getUniformLocation(const std::string& uniform) const
{
    UniformLocation uniformLocation;
    const auto& vsUniforms = _vertexShader->getUniforms();
    const auto& vsIter = vsUniforms.find(uniform);
    bool definedInVertex = false;
    if(vsIter != vsUniforms.end())
    {
        definedInVertex = true;
        uniformLocation.shaderStage = ShaderStage::VERTEX;
        uniformLocation.location = vsIter->second.location;
    }
    
    const auto& fsUniforms = _fragmentShader->getUniforms();
    const auto& fsIter = fsUniforms.find(uniform);
    if(fsIter != fsUniforms.end())
    {
        uniformLocation.shaderStage = (definedInVertex) ? ShaderStage::VERTEX_AND_FRAGMENT : ShaderStage::FRAGMENT;
        uniformLocation.location = fsIter->second.location;
    }
    
    return uniformLocation;
}

const std::unordered_map<std::string, UniformInfo>& ProgramMTL::getVertexUniformInfos() const
{
    return _vertexShader->getUniforms();
}

const std::unordered_map<std::string, UniformInfo>& ProgramMTL::getFragmentUniformInfos() const
{
    return _fragmentShader->getUniforms();
}

int ProgramMTL::getMaxVertexLocation() const
{
    return _vertexShader->getMaxLocation();
}

int ProgramMTL::getMaxFragmentLocation() const
{
    return _fragmentShader->getMaxLocation();
}

const std::unordered_map<std::string, AttributeBindInfo> ProgramMTL::getActiveAttributes() const
{
    return _vertexShader->getAttributeInfo();
}

CC_BACKEND_END
