/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
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
#include "renderer/CCTrianglesCommand.h"
#include "xxhash.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCTexture2D.h"
#include "base//ccUtils.h"

NS_CC_BEGIN

TrianglesCommand::TrianglesCommand()
{
    _type = RenderCommand::Type::TRIANGLES_COMMAND;
}

void TrianglesCommand::init(float globalOrder, Texture2D* texture, const BlendFunc& blendType, const Triangles& triangles, const Mat4& mv, uint32_t flags)
{
    RenderCommand::init(globalOrder, mv, flags);
    
    _triangles = triangles;
    if(_triangles.indexCount % 3 != 0)
    {
        unsigned int count = _triangles.indexCount;
        _triangles.indexCount = count / 3 * 3;
        CCLOGERROR("Resize indexCount from %d to %d, size must be multiple times of 3", count, _triangles.indexCount);
    }
    _mv = mv;

    if (_programType != _pipelineDescriptor.programState->getProgram()->getProgramType() ||
        _texture != texture->getBackendTexture() ||
        _blendType != blendType)
    {
        _programType = _pipelineDescriptor.programState->getProgram()->getProgramType();
        _texture = texture->getBackendTexture();
        _blendType = blendType;
        
        //since it would be too expensive to check the uniforms, simplify enable batching for built-in program.
        if(_programType == backend::ProgramType::CUSTOM_PROGRAM)
            setSkipBatching(true);
        
        //TODO: minggo set it in Node?
        auto& blendDescriptor = _pipelineDescriptor.blendDescriptor;
        blendDescriptor.blendEnabled = true;
        blendDescriptor.sourceRGBBlendFactor = blendDescriptor.sourceAlphaBlendFactor = blendType.src;
        blendDescriptor.destinationRGBBlendFactor = blendDescriptor.destinationAlphaBlendFactor = blendType.dst;

        if(!isSkipBatching())
            generateMaterialID();
    }
}

void TrianglesCommand::updateMaterialID()
{
    setSkipBatching(false);
    generateMaterialID();
}

TrianglesCommand::~TrianglesCommand()
{
}

void TrianglesCommand::generateMaterialID()
{
    struct
    {
        void* texture;
        backend::ProgramType programType;
        backend::BlendFactor src;
        backend::BlendFactor dst;
    }hashMe;

    // NOTE: Initialize hashMe struct to make the value of padding bytes be filled with zero.
    // It's important since XXH32 below will also consider the padding bytes which probably
    // are set to random values by different compilers.
    memset(&hashMe, 0, sizeof(hashMe));

    hashMe.texture = _texture;
    hashMe.src = _blendType.src;
    hashMe.dst = _blendType.dst;
    hashMe.programType = _programType;
    _materialID = XXH32((const void*)&hashMe, sizeof(hashMe), 0);
}

NS_CC_END
