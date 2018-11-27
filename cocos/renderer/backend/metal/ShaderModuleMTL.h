#pragma once

#include "../ShaderModule.h"
#include <string>
#include <vector>
#include <memory>
#import <Metal/Metal.h>

struct glslopt_shader;

CC_BACKEND_BEGIN

class ShaderModuleMTL : public ShaderModule
{
public:
    ShaderModuleMTL(id<MTLDevice> mtlDevice, ShaderStage stage, const std::string& source);
    ~ShaderModuleMTL();
    
    inline id<MTLFunction> getMTLFunction() const { return _mtlFunction; }
    inline const std::shared_ptr<uint8_t>& getUniformBuffer() const { return _uniformBuffer; }
    inline const std::vector<std::string>& getUniforms() const { return _uniforms; }
    inline const std::vector<std::string>& getTextures() const { return _textures; }
    
private:
    void parseUniform(id<MTLDevice> mtlDevice, glslopt_shader* shader);
    void parseTexture(id<MTLDevice> mtlDevice, glslopt_shader* shader);
    
    id<MTLFunction> _mtlFunction = nil;
    
    std::shared_ptr<uint8_t> _uniformBuffer = nullptr;
    std::vector<std::string> _uniforms;
    
    // Texture index is the same as vector index.
    std::vector<std::string> _textures;
};

CC_BACKEND_END
