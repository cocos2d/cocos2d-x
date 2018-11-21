#pragma once

#include "../ShaderModule.h"

#include "platform/CCGL.h"

CC_BACKEND_BEGIN

class ShaderModuleGL : public ShaderModule
{
public:
    ShaderModuleGL(ShaderStage stage, const std::string& source);
    ~ShaderModuleGL();
    
    inline GLuint getShader() const { return _shader; }
    
private:
    void compileShader(ShaderStage stage, const std::string& source);
    char* getErrorLog(GLuint shader) const;
    void deleteShader();
    
    GLuint _shader = 0;
};

CC_BACKEND_END
