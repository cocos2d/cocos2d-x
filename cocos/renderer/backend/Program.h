#pragma once

#include "Macros.h"
#include "base/CCRef.h"
#include "platform/CCPlatformMacros.h"
#include "Types.h"
#include "ShaderCache.h"

#include <string>
#include <vector>
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
    virtual const std::unordered_map<std::string, AttributeBindInfo> getActiveAttributes() const = 0;

    const std::string& getVertexShader() const { return _vertexShader; }
    const std::string& getFragmentShader() const { return _fragmentShader; }
    
protected:
    Program(const std::string& vs, const std::string& fs);

#if CC_ENABLE_CACHE_TEXTURE_DATA
    virtual int getMappedLocation(int location) const = 0; //get the ture location after opengl program reload
    virtual const std::unordered_map<std::string, UniformLocation> getAllUniformsLocation() const = 0;
    friend class ProgramState;
    friend class ProgramCache;
#endif
    
    std::string _vertexShader;
    std::string _fragmentShader;
};

CC_BACKEND_END
