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
 
#include "renderer/backend/ProgramState.h"
#include "renderer/backend/ProgramCache.h"
#include "renderer/backend/Program.h"
#include "renderer/backend/Texture.h"
#include "renderer/backend/Types.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventType.h"
#include "base/CCDirector.h"

#include <algorithm>

#ifdef CC_USE_METAL
#include "glsl_optimizer.h"
#endif

CC_BACKEND_BEGIN

namespace {
#define MAT3_SIZE 36
#define MAT4X3_SIZE 48
#define VEC3_SIZE 12
#define VEC4_SIZE 16
#define BVEC3_SIZE 3
#define BVEC4_SIZE 4
#define IVEC3_SIZE 12
#define IVEC4_SIZE 16
    
    void convertbVec3TobVec4(const bool* src, bool* dst)
    {
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst[3] = false;
    }
    
    void convertiVec3ToiVec4(const int* src, int* dst)
    {
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst[3] = 0;
    }
    
    void convertVec3ToVec4(const float* src, float* dst)
    {
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst[3] = 0.0f;
    }
    
    void convertMat3ToMat4x3(const float* src, float* dst)
    {
        dst[3] = dst[7] = dst[11] = 0.0f;
        dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2];
        dst[4] = src[3]; dst[5] = src[4]; dst[6] = src[5];
        dst[8] = src[6]; dst[9] = src[7]; dst[10] = src[8];
    }
}

//static field
std::vector<ProgramState::AutoBindingResolver*> ProgramState::_customAutoBindingResolvers;

UniformBuffer::UniformBuffer(const backend::UniformInfo &_uniformInfo)
: uniformInfo(_uniformInfo)
{
    if(uniformInfo.bufferSize > 0)
    {
        data.resize(uniformInfo.bufferSize);
        std::fill(data.begin(), data.end(), 0);
    }
}

UniformBuffer::~UniformBuffer()
{
}

UniformBuffer::UniformBuffer(const UniformBuffer &other):
    uniformInfo(other.uniformInfo), data(other.data)
{
}

UniformBuffer& UniformBuffer::operator=(const UniformBuffer& rhs)
{
    if (this != &rhs)
    {
        uniformInfo = rhs.uniformInfo;
        data = rhs.data;
    }

    return *this;
}

UniformBuffer& UniformBuffer::operator=(UniformBuffer&& rhs)
{
    if (this != &rhs)
    {
        uniformInfo = rhs.uniformInfo;
        data = std::move(rhs.data);
    }

    return *this;
}

TextureInfo::TextureInfo(const std::vector<uint32_t>& _slots, const std::vector<backend::TextureBackend*> _textures)
: slot(_slots)
, textures(_textures)
{
    retainTextures();
}

TextureInfo::TextureInfo(const TextureInfo &other)
    : slot(other.slot)
    , textures(other.textures)
#if CC_ENABLE_CACHE_TEXTURE_DATA
    , location(other.location)
#endif
{
    retainTextures();
}

TextureInfo::~TextureInfo()
{
    releaseTextures();
}

void TextureInfo::retainTextures()
{
    for (auto& texture : textures)
        CC_SAFE_RETAIN(texture);
}

void TextureInfo::releaseTextures()
{
    for (auto& texture : textures)
        CC_SAFE_RELEASE(texture);
}

TextureInfo& TextureInfo::operator=(TextureInfo&& rhs)
{
    if (this != &rhs)
    {
        slot = rhs.slot;
        
        rhs.retainTextures();
        releaseTextures();
        textures = rhs.textures;
        
        //release the textures before cleaning the vertor
        rhs.releaseTextures();
        rhs.textures.clear();

#if CC_ENABLE_CACHE_TEXTURE_DATA
        location = rhs.location;
#endif
    }
    return *this;
}

TextureInfo& TextureInfo::operator=(const TextureInfo& rhs)
{
    if (this != &rhs)
    {
        slot = rhs.slot;
        textures = rhs.textures;
        retainTextures();

#if CC_ENABLE_CACHE_TEXTURE_DATA
        location = rhs.location;
#endif
    }
    return *this;
}

ProgramState::ProgramState(const std::string& vertexShader, const std::string& fragmentShader)
{
    _program = backend::ProgramCache::getInstance()->newProgram(vertexShader, fragmentShader);
    CC_SAFE_RETAIN(_program);
    
    auto maxVertexLocaiton = _program->getMaxVertexLocation();
    auto maxFragmentLocaiton = _program->getMaxFragmentLocation();
    
    if(maxVertexLocaiton > 0)
    {
        assert(maxVertexLocaiton);
        _vertexUniformInfos.resize(maxVertexLocaiton);
        createVertexUniformBuffer();
    }
    
    if(maxFragmentLocaiton > 0)
    {
        _fragmentUniformInfos.resize(maxFragmentLocaiton);
        createFragmentUniformBuffer();
    }

#if CC_ENABLE_CACHE_TEXTURE_DATA
    _backToForegroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom*){
        this->resetUniforms();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, -1);
#endif
}

void ProgramState::resetUniforms()
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    if(_program == nullptr)
        return;

    const auto& uniforms = _program->getAllUniformsLocation();
    const auto& uniformInfos = _program->getVertexUniformInfos();
    for(const auto& uniform : uniforms)
    {
        auto location = uniform.second.location;
        auto mappedLocation = _program->getMappedLocation(location);
        bool isTextureLocation = uniformInfos.at(uniform.first).bufferSize == 0;

        if(isTextureLocation)
        {
            //check if current location had been set before
            if(_vertexTextureInfos.find(location) != _vertexTextureInfos.end())
            {
                _vertexTextureInfos[location].location = mappedLocation;
            }
        }
        else
        {
            _vertexUniformInfos[location].uniformInfo.location = mappedLocation;
        }
    }
#endif
}

ProgramState::ProgramState()
{
}

ProgramState::~ProgramState()
{
    CC_SAFE_RELEASE_NULL(_program);
    
    _vertexUniformInfos.clear();
    _fragmentUniformInfos.clear();
    _vertexTextureInfos.clear();
    _fragmentTextureInfos.clear();

#if CC_ENABLE_CACHE_TEXTURE_DATA
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundListener);
#endif
}

ProgramState *ProgramState::clone() const
{
    ProgramState *cp = new ProgramState();
    cp->_program = _program;
    cp->_vertexUniformInfos = _vertexUniformInfos;
    cp->_fragmentUniformInfos = _fragmentUniformInfos;
    cp->_vertexTextureInfos = _vertexTextureInfos;
    cp->_fragmentTextureInfos = _fragmentTextureInfos;
    cp->_vertexUniformBuffer = _vertexUniformBuffer;
    cp->_fragmentUniformBuffer = _fragmentUniformBuffer;
    CC_SAFE_RETAIN(cp->_program);

    return cp;
}


void ProgramState::createVertexUniformBuffer()
{
    uint32_t totalUniformsSize = 0;
    const auto& vertexUniformInfos = _program->getVertexUniformInfos();
    for(const auto& uniformInfo : vertexUniformInfos)
    {
        if(uniformInfo.second.bufferSize)
        {
            _vertexUniformInfos[uniformInfo.second.location] = uniformInfo.second; 
            totalUniformsSize += uniformInfo.second.bufferSize;
        }
    }
#ifdef CC_USE_METAL
    if (totalUniformsSize > 0)
    {
        _vertexUniformBuffer.resize(totalUniformsSize, 0);
    }
#endif
}

void ProgramState::createFragmentUniformBuffer()
{
    uint32_t totalUniformsSize = 0;
    const auto& fragmentUniformInfos = _program->getFragmentUniformInfos();
    for(const auto& uniformInfo : fragmentUniformInfos)
    {
        if(uniformInfo.second.bufferSize)
        {
            _fragmentUniformInfos[uniformInfo.second.location] = uniformInfo.second;
            totalUniformsSize += uniformInfo.second.bufferSize;
        }
    }
#ifdef CC_USE_METAL
    if (totalUniformsSize > 0)
    {
        _fragmentUniformBuffer.resize(totalUniformsSize, 0);
    }
#endif
}

backend::UniformLocation ProgramState::getUniformLocation(const std::string& uniform) const
{
    return _program->getUniformLocation(uniform);
}

void ProgramState::setCallbackUniform(const backend::UniformLocation& uniformLocation,const UniformCallback& callback)
{
    _callbackUniforms[uniformLocation] = callback;
}

void ProgramState::setUniform(const backend::UniformLocation& uniformLocation, const void* data, uint32_t size)
{
    switch (uniformLocation.shaderStage)
    {
        case backend::ShaderStage::VERTEX:
            setVertexUniform(uniformLocation.location, data, size);
            break;
        case backend::ShaderStage::FRAGMENT:
            setFragmentUniform(uniformLocation.location, data, size);
            break;
        case backend::ShaderStage::VERTEX_AND_FRAGMENT:
            setVertexUniform(uniformLocation.location, data, size);
            setFragmentUniform(uniformLocation.location, data, size);
            break;
        default:
            break;
    }
}

#ifdef CC_USE_METAL
void ProgramState::convertAndCopyUniformData(const backend::UniformInfo& uniformInfo, const void* srcData, uint32_t srcSize, std::vector<char>& uniformBuffer)
{
    auto basicType = static_cast<glslopt_basic_type>(uniformInfo.type);
    char* convertedData = new char[uniformInfo.bufferSize];
    memset(convertedData, 0, uniformInfo.bufferSize);
    int offset = 0;
    switch (basicType)
    {
        case kGlslTypeFloat:
        {
            if(uniformInfo.isMatrix)
            {
                for (int i=0; i<uniformInfo.count; i++)
                {
                    if(offset >= srcSize)
                        break;
                    
                    convertMat3ToMat4x3((float*)srcData + offset, (float*)convertedData + i * MAT4X3_SIZE);
                    offset += MAT3_SIZE;
                }
            }
            else
            {
                for (int i=0; i<uniformInfo.count; i++)
                {
                    if(offset >= srcSize)
                        break;
                    
                    convertVec3ToVec4((float*)srcData +offset, (float*)convertedData + i * VEC4_SIZE);
                    offset += VEC3_SIZE;
                }
            }
            break;
        }
        case kGlslTypeBool:
        {
            for (int i=0; i<uniformInfo.count; i++)
            {
                if(offset >= srcSize)
                    break;
                
                convertbVec3TobVec4((bool*)srcData + offset, (bool*)convertedData + i * BVEC4_SIZE);
                offset += BVEC3_SIZE;
            }
            break;
        }
        case kGlslTypeInt:
        {
            for (int i=0; i<uniformInfo.count; i++)
            {
                if(offset >= srcSize)
                    break;
                
                convertiVec3ToiVec4((int*)srcData + offset, (int*)convertedData + i * IVEC4_SIZE);
                offset += IVEC3_SIZE;
            }
            break;
        }
        default:
            CC_ASSERT(false);
            break;
    }
    
    memcpy(uniformBuffer.data() + uniformInfo.location, convertedData, uniformInfo.bufferSize);
    CC_SAFE_DELETE_ARRAY(convertedData);
}
#endif

void ProgramState::setVertexUniform(int location, const void* data, uint32_t size)
{
    if(location < 0)
        return;
    
//float3 etc in Metal has both sizeof and alignment same as float4, need convert to correct laytout
#ifdef CC_USE_METAL
    auto& uniformInfo = _vertexUniformInfos[location].uniformInfo;
    if(uniformInfo.needConvert)
    {
        convertAndCopyUniformData(uniformInfo, data, size, _vertexUniformBuffer);
    }
    else
    {
        memcpy(_vertexUniformBuffer.data() + location, data, size);
    }
#else
    _vertexUniformInfos[location].data.assign((char*)data, (char*)data + size);
#endif
}

void ProgramState::setFragmentUniform(int location, const void* data, uint32_t size)
{
    if(location < 0)
        return;
   
//float3 etc in Metal has both sizeof and alignment same as float4, need convert to correct laytout
#ifdef CC_USE_METAL
    auto& uniformInfo = _fragmentUniformInfos[location].uniformInfo;
    if(uniformInfo.needConvert)
    {
        convertAndCopyUniformData(uniformInfo, data, size, _fragmentUniformBuffer);
    }
    else
    {
        memcpy(_fragmentUniformBuffer.data() + location, data, size);
    }
#else
    _fragmentUniformInfos[location].data.assign((char *)data, (char *)data + size);
#endif
}

void ProgramState::setTexture(const backend::UniformLocation& uniformLocation, uint32_t slot, backend::TextureBackend* texture)
{
    switch (uniformLocation.shaderStage)
    {
        case backend::ShaderStage::VERTEX:
            setTexture(uniformLocation.location, slot, texture, _vertexTextureInfos);
            break;
        case backend::ShaderStage::FRAGMENT:
            setTexture(uniformLocation.location, slot, texture, _fragmentTextureInfos);
            break;
        case backend::ShaderStage::VERTEX_AND_FRAGMENT:
            setTexture(uniformLocation.location, slot, texture, _vertexTextureInfos);
            setTexture(uniformLocation.location, slot, texture, _fragmentTextureInfos);
            break;
        default:
            break;
    }
}

void ProgramState::setTextureArray(const backend::UniformLocation& uniformLocation, const std::vector<uint32_t>& slots, const std::vector<backend::TextureBackend*> textures)
{
    switch (uniformLocation.shaderStage)
    {
        case backend::ShaderStage::VERTEX:
            setTextureArray(uniformLocation.location, slots, textures, _vertexTextureInfos);
            break;
        case backend::ShaderStage::FRAGMENT:
            setTextureArray(uniformLocation.location, slots, textures, _fragmentTextureInfos);
            break;
        case backend::ShaderStage::VERTEX_AND_FRAGMENT:
            setTextureArray(uniformLocation.location, slots, textures, _vertexTextureInfos);
            setTextureArray(uniformLocation.location, slots, textures, _fragmentTextureInfos);
            break;
        default:
            break;
    }
}

void ProgramState::setTexture(int location, uint32_t slot, backend::TextureBackend* texture, std::unordered_map<int, TextureInfo>& textureInfo)
{
    if(location < 0)
        return;
    TextureInfo info;
    info.slot = {slot};
    info.textures = {texture};
    info.retainTextures();
#if CC_ENABLE_CACHE_TEXTURE_DATA
    info.location = location;
#endif
    textureInfo[location] = std::move(info);
}

void ProgramState::setTextureArray(int location, const std::vector<uint32_t>& slots, const std::vector<backend::TextureBackend*> textures, std::unordered_map<int, TextureInfo>& textureInfo)
{
    assert(slots.size() == textures.size());
    TextureInfo info;
    info.slot = slots;
    info.textures = textures;
    info.retainTextures();
#if CC_ENABLE_CACHE_TEXTURE_DATA
    info.location = location;
#endif
    textureInfo[location] = std::move(info);

}

void ProgramState::setParameterAutoBinding(const std::string &uniform, const std::string &autoBinding)
{
    _autoBindings.emplace(uniform, autoBinding);
    applyAutoBinding(uniform, autoBinding);
}

void ProgramState::applyAutoBinding(const std::string &uniformName, const std::string &autoBinding)
{
    bool resolved = false;
    for (const auto resolver : _customAutoBindingResolvers)
    {
        resolved = resolver->resolveAutoBinding(this, uniformName, autoBinding);
        if (resolved) break;
    }
}

ProgramState::AutoBindingResolver::AutoBindingResolver()
{
    _customAutoBindingResolvers.emplace_back(this);
}

ProgramState::AutoBindingResolver::~AutoBindingResolver()
{
    auto &list = _customAutoBindingResolvers;
    list.erase(std::remove(list.begin(), list.end(), this), list.end());
}

CC_BACKEND_END

