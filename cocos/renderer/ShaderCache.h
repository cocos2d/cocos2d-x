/****************************************************************************
 Copyright (c) 2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "platform/CCPlatformMacros.h"
#include "renderer/backend/ShaderModule.h"

#include <string>
#include <unordered_map>

NS_CC_BEGIN

class CC_DLL ShaderCache
{
public:
    /** Create a vertex shader module.
        @param key A key to identify a shader module. If it is created before, then just return the cached shader module.
        @param shaderSource The source code of the shader.
     */
    static backend::ShaderModule* newVertexShaderModule(const std::string& key, const std::string& shaderSource);
    
    /** Create a fragment shader module.
     @param key A key to identify a shader module. If it is created before, then just return the cached shader module.
     @param shaderSource The source code of the shader.
     */
    static backend::ShaderModule* newFragmentShaderModule(const std::string& key, const std::string& shaderSource);
    
private:
    static std::unordered_map<std::string, backend::ShaderModule*> _cachedVertexShaders;
    static std::unordered_map<std::string, backend::ShaderModule*> _cachedFragmentShaders;
};

NS_CC_END
