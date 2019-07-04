/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
 
#include "ShaderModuleGL.h"

#include "platform/CCPlatformMacros.h"
#include "base/ccMacros.h"

CC_BACKEND_BEGIN

ShaderModuleGL::ShaderModuleGL(ShaderStage stage, const std::string& source)
: ShaderModule(stage)
{
    compileShader(stage, source);
}

ShaderModuleGL::~ShaderModuleGL()
{
    deleteShader();
}

void ShaderModuleGL::compileShader(ShaderStage stage, const std::string &source)
{
    GLenum shaderType = stage == ShaderStage::VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;
    const GLchar* sourcePtr = reinterpret_cast<const GLchar*>(source.c_str());
    _shader = glCreateShader(shaderType);
    if (!_shader)
        return;
    
    glShaderSource(_shader, 1, &sourcePtr, nullptr);
    glCompileShader(_shader);
    
    GLint status = 0;
    glGetShaderiv(_shader, GL_COMPILE_STATUS, &status);
    if (! status)
    {
        CCLOG("cocos2d: ERROR: Failed to compile shader:\n%s", source.c_str());
        CCLOG("cocos2d: %s", getErrorLog(_shader));
        deleteShader();
        CCASSERT(false, "Shader compile failed!");
    }
}

char* ShaderModuleGL::getErrorLog(GLuint shader) const
{
    GLint logLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    char* log = (char*)malloc(sizeof(char) * logLength);
    glGetShaderInfoLog(shader, logLength, nullptr, log);
    return log;
}

void ShaderModuleGL::deleteShader()
{
    if (_shader)
    {
        glDeleteShader(_shader);
        _shader = 0;
    }
}

CC_BACKEND_END
