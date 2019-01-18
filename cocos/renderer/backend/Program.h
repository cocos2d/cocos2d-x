#pragma once

#include "Macros.h"
#include "base/CCRef.h"
#include "platform/CCPlatformMacros.h"
#include "Types.h"
#include "ShaderCache.h"

#include <string>
#include <unordered_map>

CC_BACKEND_BEGIN

class ShaderModule;

class Program : public Ref
{
public:
    virtual const std::unordered_map<std::string, UniformInfo>& getVertexUniformInfos() const = 0;
    virtual const std::unordered_map<std::string, UniformInfo>& getFragmentUniformInfos() const = 0;
    
    virtual UniformLocation getUniformLocation(const std::string& uniform) const = 0;
    
    virtual int getMaxVertexLocation() const = 0;
    virtual int getMaxFragmentLocation() const = 0;
    
    const std::string& getVertexShader() const { return _vertexShader; }
    const std::string& getFragmentShader() const { return _fragmentShader; }
    
protected:
    Program(const std::string& vs, const std::string& fs);
    
    std::string _vertexShader;
    std::string _fragmentShader;
};

CC_BACKEND_END
