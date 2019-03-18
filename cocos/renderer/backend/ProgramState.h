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
    
    /**
    * An abstract base class that can be extended to support custom material auto bindings.
    *
    * Implementing a custom auto binding resolver allows the set of built-in parameter auto
    * bindings to be extended or overridden. Any parameter auto binding that is set on a
    * material will be forwarded to any custom auto binding resolvers, in the order in which
    * they are registered. If a registered resolver returns true (specifying that it handles
    * the specified autoBinding), no further code will be executed for that autoBinding.
    * This allows auto binding resolvers to not only implement new/custom binding strings,
    * but it also lets them override existing/built-in ones. For this reason, you should
    * ensure that you ONLY return true if you explicitly handle a custom auto binding; return
    * false otherwise.
    *
    * Note that the custom resolver is called only once for a GLProgramState object when its
    * node binding is initially set. This occurs when a material is initially bound to a
    * Node. The resolver is NOT called each frame or each time the GLProgramState is bound.
    *
    * If no registered resolvers explicitly handle an auto binding, the binding will attempt
    * to be resolved using the internal/built-in resolver, which is able to handle any
    * auto bindings found in the GLProgramState::AutoBinding enumeration.
    *
    * When an instance of a class that extends AutoBindingResolver is created, it is automatically
    * registered as a custom auto binding handler. Likewise, it is automatically unregistered
    * on destruction.
    *
    * @script{ignore}
    */
    class CC_DLL AutoBindingResolver {
    public:
        AutoBindingResolver();
        virtual ~AutoBindingResolver();
        /**
        * Called when an unrecognized uniform variable is encountered
        * during material loading.
        *
        * Implementations of this method should do a string comparison on the passed
        * in name parameter and decide whether or not they should handle the
        * parameter. If the parameter is not handled, false should be returned so
        * that other auto binding resolvers get a chance to handle the parameter.
        * Otherwise, the parameter should be set or bound and true should be returned.
        *
        * @param glProgramState The glProgramState
        * @param node The node that the material is attached to.
        * @param uniformName Name of the uniform
        * @param autoBinding Name of the auto binding to be resolved.
        *
        * @return True if the auto binding is handled and the associated parameter is
        *      bound, false otherwise.
        */
        virtual bool resolveAutoBinding(ProgramState *, const std::string &uniformName, const std::string &autoBinding) = 0;
    };
    /**
    * Sets a uniform auto-binding.
    *
    * This method parses the passed in autoBinding string and attempts to convert it
    * to an enumeration value. If it matches to one of the predefined strings, it will create a
    * callback to get the correct value at runtime.
    *
    * @param uniformName The name of the material parameter to store an auto-binding for.
    * @param autoBinding A string matching one of the built-in AutoBinding enum constants.
    */
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
    /**
    * Applies the specified custom auto-binding.
    *
    * @param uniformName Name of the shader uniform.
    * @param autoBinding Name of the auto binding.
    */
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
