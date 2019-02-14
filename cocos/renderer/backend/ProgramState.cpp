#include "renderer/backend/ProgramState.h"
#include "renderer/backend/ProgramCache.h"
#include "renderer/backend/Program.h"
#include "renderer/backend/Texture.h"
#include "renderer/backend/Types.h"
#include "base/ccMacros.h"
#include "base/CCDirector.h"

#include <algorithm>

CC_BACKEND_BEGIN

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

TextureInfo::TextureInfo(const std::vector<uint32_t>& _slots, const std::vector<backend::Texture*> _textures)
: slot(_slots)
, textures(_textures)
{
    retainTextures();
}

TextureInfo::TextureInfo(const TextureInfo &other)
    : slot(other.slot)
    , textures(other.textures)
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
}

ProgramState::ProgramState()
{
}

ProgramState::~ProgramState()
{
    CC_SAFE_RELEASE(_program);
    
    _vertexUniformInfos.clear();
    _fragmentUniformInfos.clear();
    _vertexTextureInfos.clear();
    _fragmentTextureInfos.clear();
}

ProgramState *ProgramState::clone() const
{
    ProgramState *cp = new ProgramState();
    cp->_program = _program;
    cp->_vertexUniformInfos = _vertexUniformInfos;
    cp->_fragmentUniformInfos = _fragmentUniformInfos;
    cp->_vertexTextureInfos = _vertexTextureInfos;
    cp->_fragmentTextureInfos = _fragmentTextureInfos;
    cp->_textureSlotId = _textureSlotId;
    CC_SAFE_RETAIN(cp->_program);

    return cp;
}


void ProgramState::createVertexUniformBuffer()
{
    const auto& vertexUniformInfos = _program->getVertexUniformInfos();
    for(const auto& uniformInfo : vertexUniformInfos)
    {
        if(uniformInfo.second.bufferSize)
            _vertexUniformInfos[uniformInfo.second.location] = uniformInfo.second; 
    }
}

void ProgramState::createFragmentUniformBuffer()
{
    const auto& fragmentUniformInfos = _program->getFragmentUniformInfos();
    for(const auto& uniformInfo : fragmentUniformInfos)
    {
        if(uniformInfo.second.bufferSize)
            _fragmentUniformInfos[uniformInfo.second.location] = uniformInfo.second;
    }
}

backend::UniformLocation ProgramState::getUniformLocation(const std::string& uniform) const
{
    return _program->getUniformLocation(uniform);
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

void ProgramState::setVertexUniform(int location, const void* data, uint32_t size)
{
    if(location < 0)
        return;
    
    _vertexUniformInfos[location].data.assign((char*)data, (char*)data + size);
}

void ProgramState::setFragmentUniform(int location, const void* data, uint32_t size)
{
    if(location < 0)
        return;
    _fragmentUniformInfos[location].data.assign((char *)data, (char *)data + size);
}

void ProgramState::setTexture(const backend::UniformLocation& uniformLocation, uint32_t slot, backend::Texture* texture)
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

void ProgramState::addTexture(const backend::UniformLocation& uniformLocation, backend::Texture* texture)
{
    setTexture(uniformLocation, ++_textureSlotId, texture);
}

void ProgramState::setTextureArray(const backend::UniformLocation& uniformLocation, const std::vector<uint32_t>& slots, const std::vector<backend::Texture*> textures)
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

void ProgramState::setTexture(int location, uint32_t slot, backend::Texture* texture, std::unordered_map<int, TextureInfo>& textureInfo)
{
    if(location < 0)
        return;
    
    TextureInfo info;
    info.slot = {slot};
    info.textures = {texture};
    info.retainTextures();
    textureInfo[location] = std::move(info);
    _textureSlotId = std::max(_textureSlotId, slot);
}

void ProgramState::setTextureArray(int location, const std::vector<uint32_t>& slots, const std::vector<backend::Texture*> textures, std::unordered_map<int, TextureInfo>& textureInfo)
{
    assert(slots.size() == textures.size());
    TextureInfo info;
    info.slot = slots;
    info.textures = textures;
    info.retainTextures();
    textureInfo[location] = std::move(info);
}

CC_BACKEND_END

