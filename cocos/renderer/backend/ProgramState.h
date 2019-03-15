#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <cstdint>
#include "platform/CCPlatformMacros.h"
#include "base/CCRef.h"
#include "renderer/backend/Types.h"
#include "renderer/backend/Program.h"

CC_BACKEND_BEGIN

class Texture;

struct UniformBuffer
{
    UniformBuffer(const backend::UniformInfo& _uniformInfo);
    UniformBuffer() = default;
    UniformBuffer(const UniformBuffer& _uniformBuffer);
    UniformBuffer& operator =(const UniformBuffer& rhs);
    ~UniformBuffer();
    UniformBuffer& operator =(UniformBuffer&& rhs);
    
    inline const bool isValid() const { return uniformInfo.location != -1; }
    
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
    TextureInfo& operator=(const TextureInfo& rhs);
    
    void retainTextures();
    void releaseTextures();
    
    std::vector<uint32_t> slot;
    std::vector<backend::Texture*> textures;
};

class ProgramState : public Ref
{
public:

    using UniformCallback = std::function<void(ProgramState*, const UniformLocation &)>;

    ProgramState(const std::string& vertexShader, const std::string& fragmentShader);
    virtual ~ProgramState();
    
    /***
    *  deep clone ProgramState
    */
    ProgramState *clone() const;
    
    //get program
    backend::Program* getProgram() const { return _program; }
    
    //get or set uniforms
    void setUniform(const backend::UniformLocation& uniformLocation, const void* data, uint32_t size);
    backend::UniformLocation getUniformLocation(const std::string& uniform) const;
    inline const std::vector<UniformBuffer>& getVertexUniformInfos() const { return _vertexUniformInfos; }
    inline std::vector<UniformBuffer>& getVertexUniformInfos() { return _vertexUniformInfos; }
    inline const std::vector<UniformBuffer>& getFragmentUniformInfos() const { return _fragmentUniformInfos; }

    void setCallbackUniform(const backend::UniformLocation&, const UniformCallback &);

    //set textures
    void setTexture(const backend::UniformLocation& uniformLocation, uint32_t slot, backend::Texture* texture);
    void setTextureArray(const backend::UniformLocation& uniformLocation, const std::vector<uint32_t>& slots, const std::vector<backend::Texture*> textures);

    inline const std::unordered_map<int, TextureInfo>& getVertexTextureInfos() const { return _vertexTextureInfos; }
    inline const std::unordered_map<int, TextureInfo>& getFragmentTextureInfos() const { return _fragmentTextureInfos; }
    inline const std::unordered_map<UniformLocation, UniformCallback, UniformLocation>& getCallbackUniforms() const { return _callbackUniforms; }

    class CC_DLL AutoBindingResolver {
    public:
        virtual ~AutoBindingResolver();
        //TODO doc
        virtual bool resolveAutoBinding(ProgramState *, const std::string &uniformName, const std::string &autoBinding) = 0;
    protected:
        AutoBindingResolver();
    };

    void setParameterAutoBinding(const std::string &, const std::string &);

protected:

    ProgramState();

    void setVertexUniform(int location, const void* data, uint32_t size);
    void setFragmentUniform(int location, const void* data, uint32_t size);
    void createVertexUniformBuffer();
    void createFragmentUniformBuffer();
    void setTexture(int location, uint32_t slot, backend::Texture* texture, std::unordered_map<int, TextureInfo>& textureInfo);
    void setTextureArray(int location, const std::vector<uint32_t>& slots, const std::vector<backend::Texture*> textures, std::unordered_map<int, TextureInfo>& textureInfo);
    
#ifdef CC_USE_METAL
    //float3 etc in Metal has both sizeof and alignment same as float4, convert it before fill into uniform buffer
    void convertUniformData(const backend::UniformInfo& uniformInfo, const void* srcData, uint32_t srcSize, std::vector<char>& uniformData);
#endif
    
    void applyAutoBinding(const std::string &, const std::string &);

    backend::Program*                                       _program = nullptr;
    std::vector<UniformBuffer>                              _vertexUniformInfos;
    std::vector<UniformBuffer>                              _fragmentUniformInfos;
    std::unordered_map<UniformLocation, UniformCallback, UniformLocation>   _callbackUniforms;
    
    std::unordered_map<int, TextureInfo>                    _vertexTextureInfos;
    std::unordered_map<int, TextureInfo>                    _fragmentTextureInfos;

    std::unordered_map<std::string, std::string>            _autoBindings;

    static std::vector<AutoBindingResolver*>                _customAutoBindingResolvers;
};

CC_BACKEND_END
