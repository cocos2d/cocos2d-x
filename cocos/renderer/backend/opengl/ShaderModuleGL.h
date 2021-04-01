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
 
#pragma once

#include "../ShaderModule.h"

#include "platform/CCGL.h"

CC_BACKEND_BEGIN
/**
 * @addtogroup _opengl
 * @{
 */

/**
 * Create and compile shader.
 */
class ShaderModuleGL : public ShaderModule
{
public:
    /**
     * @param stage Specifies whether is vertex shader or fragment shader.
     * @param source Specifies shader source.
     */
    ShaderModuleGL(ShaderStage stage, const std::string& source);
    ~ShaderModuleGL();

    /**
     * Get shader object.
     * @return Shader object.
     */
    inline GLuint getShader() const { return _shader; }
    
private:
    void compileShader(ShaderStage stage, const std::string& source);
    char* getErrorLog(GLuint shader) const;
    void deleteShader();
    
    GLuint _shader = 0;
    friend class ProgramGL;
};
//end of _opengl group
/// @}
CC_BACKEND_END
