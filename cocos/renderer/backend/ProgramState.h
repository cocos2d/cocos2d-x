#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <cstdint>
#include "platform/CCPlatformMacros.h"
#include "base/CCRef.h"
#include "renderer/backend/Types.h"

CC_BACKEND_BEGIN

class Program;
class Texture;

struct UniformBuffer
{
    UniformBuffer(const backend::UniformInfo& _uniformInfo);
    UniformBuffer() = default;
    UniformBuffer(const UniformBuffer& _uniformBuffer);
    UniformBuffer& operator =(const UniformBuffer& rhs);
    ~UniformBuffer();
    UniformBuffer& operator =(UniformBuffer&& rhs);
    
    backend::UniformInfo uniformInfo;
    std::vector<char> data;

};

struct TextureInfo
{
    TextureInfo(const std::vector<uint32_t>& _slots, const std::vector<backend::Texture*> _textures);
    TextureInfo() = default;
    TextureInfo(const TextureInfo &);
    ~TextureInfo();
    TextureInfo& operator=(TextureInfo&& rhs);
    
    void retainTextures();
    void releaseTextures();
    
    std::vector<uint32_t> slot;
    std::vector<backend::Texture*> textures;
};

class ProgramState : public Ref
{
public:
    ProgramState(const std::string& vertexShader, const std::string& fragmentShader);
    virtual ~ProgramState();
    
    /***
    *  deep clone ProgramState
    */
    ProgramState *clone() const;
    
    //get program
    backend::Program* getProgram() const { return _program; }
    
    //get or set uniforms
    void setUniform(const backend::UniformLocation& uniformLocation, const void* data, ssize_t size);
    backend::UniformLocation getUniformLocation(const std::string& uniform) const;
    inline const std::vector<UniformBuffer>& getVertexUniformInfos() const { return _vertexUniformInfos; }
    inline std::vector<UniformBuffer>& getVertexUniformInfos() { return _vertexUniformInfos; }
    inline const std::vector<UniformBuffer>& getFragmentUniformInfos() const { return _fragmentUniformInfos; }
    

    void setUniform(const std::string &uniformName, const void *data, ssize_t size);

    template<typename T>
    void setUniform(const backend::UniformLocation& uniformLocation, const T& data)
    {
        setUniform(uniformLocation,(const void *) &data, sizeof(T));
    }
    template<typename T>
    void setUniform(const std::string &uniformName, const T& data)
    {
        setUniform(uniformName, (const void *)&data, sizeof(T));
    }

    //set textures
    void setTexture(const backend::UniformLocation& uniformLocation, uint32_t slot, backend::Texture* texture);
    void setTextureArray(const backend::UniformLocation& uniformLocation, const std::vector<uint32_t>& slots, const std::vector<backend::Texture*> textures);
    void addTexture(const backend::UniformLocation& uniformLocation, backend::Texture* texture);


    void setBuiltinUniforms(const Mat4 &matrixMV);

    inline const std::unordered_map<int, TextureInfo>& getVertexTextureInfos() const { return _vertexTextureInfos; }
    inline const std::unordered_map<int, TextureInfo>& getFragmentTextureInfos() const { return _fragmentTextureInfos; }
    
protected:

    ProgramState();

    void setVertexUniform(int location, const void* data, uint32_t size);
    void setFragmentUniform(int location, const void* data, uint32_t size);
    void createVertexUniformBuffer();
    void createFragmentUniformBuffer();
    void setTexture(int location, uint32_t slot, backend::Texture* texture, std::unordered_map<int, TextureInfo>& textureInfo);
    void setTextureArray(int location, const std::vector<uint32_t>& slots, const std::vector<backend::Texture*> textures, std::unordered_map<int, TextureInfo>& textureInfo);
    
    backend::Program* _program = nullptr;
    std::vector<UniformBuffer> _vertexUniformInfos;
    std::vector<UniformBuffer> _fragmentUniformInfos;
    
    std::unordered_map<int, TextureInfo> _vertexTextureInfos;
    std::unordered_map<int, TextureInfo> _fragmentTextureInfos;
    
    uint32_t _textureSlotId = 0;
};

CC_BACKEND_END
