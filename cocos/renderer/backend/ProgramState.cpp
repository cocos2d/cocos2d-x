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

ProgramState::ProgramState(Program* program)
{
    init(program);
}

bool ProgramState::init(Program* program)
{
    CC_SAFE_RETAIN(program);
    _program = program;
    _vertexUniformBufferSize = _program->getUniformBufferSize(ShaderStage::VERTEX);
    _vertexUniformBuffer = new char[_vertexUniformBufferSize];
    memset(_vertexUniformBuffer, 0, _vertexUniformBufferSize);
#ifdef CC_USE_METAL
    _fragmentUniformBufferSize = _program->getUniformBufferSize(ShaderStage::FRAGMENT);
    _fragmentUniformBuffer = new char[_fragmentUniformBufferSize];
    memset(_fragmentUniformBuffer, 0, _fragmentUniformBufferSize);
#endif

#if CC_ENABLE_CACHE_TEXTURE_DATA
    _backToForegroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom*){
        this->resetUniforms();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, -1);
#endif
    return true;
}

void ProgramState::resetUniforms()
{
#if CC_ENABLE_CACHE_TEXTURE_DATA
    if(_program == nullptr)
        return;

    const auto& uniformLocation = _program->getAllUniformsLocation();
    for(const auto& uniform : uniformLocation)
    {
        auto location = uniform.second;
        auto mappedLocation = _program->getMappedLocation(location);

        //check if current location had been set before
        if(_vertexTextureInfos.find(location) != _vertexTextureInfos.end())
        {
            _vertexTextureInfos[location].location = mappedLocation;
        }
    }
#endif
}

ProgramState::ProgramState()
{
}

ProgramState::~ProgramState()
{
    CC_SAFE_RELEASE(_program);
    CC_SAFE_DELETE_ARRAY(_vertexUniformBuffer);
    CC_SAFE_DELETE_ARRAY(_fragmentUniformBuffer);
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundListener);
#endif
}

ProgramState *ProgramState::clone() const
{
    ProgramState *cp = new ProgramState();
    cp->_program = _program;
    cp->_vertexUniformBufferSize = _vertexUniformBufferSize;
    cp->_fragmentUniformBufferSize = _fragmentUniformBufferSize;
    cp->_vertexTextureInfos = _vertexTextureInfos;
    cp->_fragmentTextureInfos = _fragmentTextureInfos;
    cp->_vertexUniformBuffer = new char[_vertexUniformBufferSize];
    memcpy(cp->_vertexUniformBuffer, _vertexUniformBuffer, _vertexUniformBufferSize);
    cp->_vertexLayout = _vertexLayout;
#ifdef CC_USE_METAL
    cp->_fragmentUniformBuffer = new char[_fragmentUniformBufferSize];
    memcpy(cp->_fragmentUniformBuffer, _fragmentUniformBuffer, _fragmentUniformBufferSize);
#endif
    CC_SAFE_RETAIN(cp->_program);

    return cp;
}

backend::UniformLocation ProgramState::getUniformLocation(backend::Uniform name) const
{
    return _program->getUniformLocation(name);
}

backend::UniformLocation ProgramState::getUniformLocation(const std::string& uniform) const
{
    return _program->getUniformLocation(uniform);
}

void ProgramState::setCallbackUniform(const backend::UniformLocation& uniformLocation,const UniformCallback& callback)
{
    _callbackUniforms[uniformLocation] = callback;
}

void ProgramState::setUniform(const backend::UniformLocation& uniformLocation, const void* data, std::size_t size)
{
    switch (uniformLocation.shaderStage)
    {
        case backend::ShaderStage::VERTEX:
            setVertexUniform(uniformLocation.location[0], data, size, uniformLocation.location[1]);
            break;
        case backend::ShaderStage::FRAGMENT:
            setFragmentUniform(uniformLocation.location[1], data, size);
            break;
        case backend::ShaderStage::VERTEX_AND_FRAGMENT:
            setVertexUniform(uniformLocation.location[0], data, size, uniformLocation.location[1]);
            setFragmentUniform(uniformLocation.location[1], data, size);
            break;
        default:
            break;
    }
}

#ifdef CC_USE_METAL
void ProgramState::convertAndCopyUniformData(const backend::UniformInfo& uniformInfo, const void* srcData, std::size_t srcSize, void* buffer)
{
    auto basicType = static_cast<glslopt_basic_type>(uniformInfo.type);
    char* convertedData = new char[uniformInfo.size];
    memset(convertedData, 0, uniformInfo.size);
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
    
    memcpy((char*)buffer + uniformInfo.location, convertedData, uniformInfo.size);
    CC_SAFE_DELETE_ARRAY(convertedData);
}
#endif

void ProgramState::setVertexUniform(int location, const void* data, std::size_t size, std::size_t offset)
{
    if(location < 0)
        return;
    
//float3 etc in Metal has both sizeof and alignment same as float4, need convert to correct laytout
#ifdef CC_USE_METAL
    const auto& uniformInfo = _program->getActiveUniformInfo(ShaderStage::VERTEX, location);
    if(uniformInfo.needConvert)
    {
        convertAndCopyUniformData(uniformInfo, data, size, _vertexUniformBuffer);
    }
    else
    {
        memcpy(_vertexUniformBuffer + location, data, size);
    }
#else
    memcpy(_vertexUniformBuffer + offset, data, size);
#endif
}

void ProgramState::setFragmentUniform(int location, const void* data, std::size_t size)
{
    if(location < 0)
        return;
   
//float3 etc in Metal has both sizeof and alignment same as float4, need convert to correct laytout
#ifdef CC_USE_METAL
    const auto& uniformInfo = _program->getActiveUniformInfo(ShaderStage::FRAGMENT, location);
    if(uniformInfo.needConvert)
    {
        convertAndCopyUniformData(uniformInfo, data, size, _fragmentUniformBuffer);
    }
    else
    {
        memcpy(_fragmentUniformBuffer + location, data, size);
    }
#endif
}

void ProgramState::setTexture(const backend::UniformLocation& uniformLocation, uint32_t slot, backend::TextureBackend* texture)
{
    switch (uniformLocation.shaderStage)
    {
        case backend::ShaderStage::VERTEX:
            setTexture(uniformLocation.location[0], slot, texture, _vertexTextureInfos);
            break;
        case backend::ShaderStage::FRAGMENT:
            setTexture(uniformLocation.location[1], slot, texture, _fragmentTextureInfos);
            break;
        case backend::ShaderStage::VERTEX_AND_FRAGMENT:
            setTexture(uniformLocation.location[0], slot, texture, _vertexTextureInfos);
            setTexture(uniformLocation.location[1], slot, texture, _fragmentTextureInfos);
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
            setTextureArray(uniformLocation.location[0], slots, textures, _vertexTextureInfos);
            break;
        case backend::ShaderStage::FRAGMENT:
            setTextureArray(uniformLocation.location[1], slots, textures, _fragmentTextureInfos);
            break;
        case backend::ShaderStage::VERTEX_AND_FRAGMENT:
            setTextureArray(uniformLocation.location[0], slots, textures, _vertexTextureInfos);
            setTextureArray(uniformLocation.location[1], slots, textures, _fragmentTextureInfos);
            break;
        default:
            break;
    }
}

void ProgramState::setTexture(int location, uint32_t slot, backend::TextureBackend* texture, std::unordered_map<int, TextureInfo>& textureInfo)
{
    if(location < 0)
        return;
    TextureInfo& info = textureInfo[location];
    info.releaseTextures();
    info.slot = {slot};
    info.textures = {texture};
    info.retainTextures();
#if CC_ENABLE_CACHE_TEXTURE_DATA
    info.location = location;
#endif
}

void ProgramState::setTextureArray(int location, const std::vector<uint32_t>& slots, const std::vector<backend::TextureBackend*> textures, std::unordered_map<int, TextureInfo>& textureInfo)
{
    assert(slots.size() == textures.size());
    TextureInfo& info = textureInfo[location];
    info.releaseTextures();
    info.slot = slots;
    info.textures = textures;
    info.retainTextures();
#if CC_ENABLE_CACHE_TEXTURE_DATA
    info.location = location;
#endif
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

void ProgramState::getVertexUniformBuffer(char** buffer, std::size_t& size) const
{
    *buffer = _vertexUniformBuffer;
    size = _vertexUniformBufferSize;
}

void ProgramState::getFragmentUniformBuffer(char** buffer, std::size_t& size) const
{
    *buffer = _fragmentUniformBuffer;
    size = _fragmentUniformBufferSize;
}

CC_BACKEND_END

