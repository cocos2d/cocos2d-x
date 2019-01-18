#include "renderer/backend/ProgramState.h"
#include "renderer/backend/ProgramCache.h"
#include "renderer/backend/Program.h"
#include "renderer/backend/Texture.h"

CC_BACKEND_BEGIN

UniformBuffer::UniformBuffer(backend::UniformInfo _uniformInfo)
: uniformInfo(_uniformInfo)
, dirty(false)
{
    if(uniformInfo.bufferSize)
    {
        data = malloc(uniformInfo.bufferSize);
        if (data)
            memset(data, 0, uniformInfo.bufferSize);
    }
}

UniformBuffer::~UniformBuffer()
{
    if (data)
        free(data);
}

UniformBuffer& UniformBuffer::operator=(UniformBuffer&& rhs)
{
    if (this != &rhs)
    {
        uniformInfo = rhs.uniformInfo;
        data = rhs.data;
        rhs.data = nullptr;
    }

    return *this;
}

TextureInfo::TextureInfo(const std::vector<uint32_t>& _slots, const std::vector<backend::Texture*> _textures)
: slot(_slots)
, textures(_textures)
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

ProgramState::~ProgramState()
{
    CC_SAFE_RELEASE(_program);
    
    _vertexUniformInfos.clear();
    _fragmentUniformInfos.clear();
    _vertexTextureInfos.clear();
    _fragmentTextureInfos.clear();
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
    
    assert(size <= _vertexUniformInfos[location].uniformInfo.bufferSize);
    memcpy(_vertexUniformInfos[location].data, data, size);
    _vertexUniformInfos[location].dirty = true;
}

void ProgramState::setFragmentUniform(int location, const void* data, uint32_t size)
{
    if(location < 0)
        return;
    
    assert(size <= _fragmentUniformInfos[location].uniformInfo.bufferSize);
    memcpy(_fragmentUniformInfos[location].data, data, size);
    _fragmentUniformInfos[location].dirty = true;
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

