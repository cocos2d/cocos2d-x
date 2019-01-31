#pragma once

#include "../ShaderModule.h"
#include "../Types.h"

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
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
    inline const std::unordered_map<std::string, UniformInfo>& getUniforms() const { return _uniformInfos; }
    inline const int getMaxLocation() const { return _maxLocation; }
    
private:
    void parseAttibute(id<MTLDevice> mtlDevice, glslopt_shader* shader);
    void parseUniform(id<MTLDevice> mtlDevice, glslopt_shader* shader);
    void parseTexture(id<MTLDevice> mtlDevice, glslopt_shader* shader);
    
    id<MTLFunction> _mtlFunction = nil;
    
    std::shared_ptr<uint8_t> _uniformBuffer = nullptr;
    std::unordered_map<std::string, UniformInfo> _uniformInfos;
    std::vector<AttributeBindInfo> _attributeInfo;
    
    int _maxLocation = -1;
};

CC_BACKEND_END
