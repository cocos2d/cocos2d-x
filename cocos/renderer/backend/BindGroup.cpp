#include "BindGroup.h"
#include "Texture.h"

CC_BACKEND_BEGIN

BindGroup::UniformInfo::UniformInfo(const std::string& _name, const void* _data, uint32_t _size)
: name(_name)
, size(_size)
{
    data = malloc(size);
    if (data)
        memcpy(data, _data, size);
}

BindGroup::UniformInfo::UniformInfo(const UniformInfo& rhs)
: name(rhs.name)
, size(rhs.size)
{
    if (rhs.data)
    {
        data = malloc(size);
        if (data)
            memcpy(data, rhs.data, size);
    }
}

BindGroup::UniformInfo::~UniformInfo()
{
    if (data)
        free(data);
}

BindGroup::UniformInfo& BindGroup::UniformInfo::operator=(UniformInfo&& rhs)
{
    if (this != &rhs)
    {
        name = rhs.name;
        size = rhs.size;

        if (data) free(data);
        data = rhs.data;
        rhs.data = nullptr;
    }
    
    return *this;
}

BindGroup::UniformInfo& BindGroup::UniformInfo::operator=(const UniformInfo& rhs)
{
    if (this != &rhs)
    {
        name = rhs.name;
        size = rhs.size;

        if (data) free(data);
        data = malloc(size);
        if (data)
            memcpy(data, rhs.data, size);
    }

    return *this;
}

BindGroup::TextureInfo::TextureInfo(const std::string& _name, const std::vector<uint32_t>& _indices, const std::vector<Texture*> _textures)
: name(_name)
, indices(_indices)
, textures(_textures)
{
    retainTextures();
}

BindGroup::TextureInfo::TextureInfo(const TextureInfo& rhs)
: name(rhs.name)
, indices(rhs.indices)
, textures(rhs.textures)
{
    retainTextures();
}

BindGroup::TextureInfo::~TextureInfo()
{
    releaseTextures();
}

BindGroup::TextureInfo& BindGroup::TextureInfo::operator=(TextureInfo&& rhs)
{
    if (this != &rhs)
    {
        name = rhs.name;
        indices = std::move(rhs.indices);
        
        releaseTextures();
        textures = std::move(rhs.textures);
    }
    return *this;
}

BindGroup::TextureInfo& BindGroup::TextureInfo::operator=(const TextureInfo& rhs)
{
    if (this != &rhs)
    {
        name = rhs.name;
        indices = rhs.indices;

        releaseTextures();
        textures = rhs.textures;
        retainTextures();
    }

    return *this;
}

void BindGroup::TextureInfo::retainTextures()
{
    for (auto& texture : textures)
        CC_SAFE_RETAIN(texture);
}

void BindGroup::TextureInfo::releaseTextures()
{
    for (auto& texture : textures)
        CC_SAFE_RELEASE(texture);
}

void BindGroup::setTexture(const std::string &name, uint32_t index, Texture *texture)
{
    TextureInfo textureInfo(name, {index}, {texture});
    _textureInfos[name] = std::move(textureInfo);
}

void BindGroup::setTextureArray(const std::string& name, const std::vector<uint32_t>& indices, const std::vector<Texture*> textures)
{
    assert(indices.size() == textures.size());
    
    TextureInfo textureInfo(name, indices, textures);
    _textureInfos[name] = std::move(textureInfo);
}

void BindGroup::setUniform(const std::string& name, const void* data, uint32_t size)
{
    UniformInfo uniform(name, data, size);
    _uniformInfos[name] = std::move(uniform);
}

CC_BACKEND_END
