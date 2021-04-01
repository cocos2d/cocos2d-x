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

#include "Macros.h"
#include "base/CCRef.h"
#include "platform/CCPlatformMacros.h"
#include "renderer/backend/ShaderModule.h"

#include <string>
#include <unordered_map>

CC_BACKEND_BEGIN
/**
 * @addtogroup _backend
 * @{
 */

/**
 * Create and reuse shader module.
 */
class ShaderCache : public Ref
{
public:
    /** returns the shared instance */
    static ShaderCache* getInstance();
    
    /** purges the cache. It releases the retained instance. */
    static void destroyInstance();
    
    /** 
     * Create a vertex shader module and add it to cache.
     * If it is created before, then just return the cached shader module.
     * @param shaderSource The source code of the shader.
     */
    static backend::ShaderModule* newVertexShaderModule(const std::string& shaderSource);
    
    /** 
     * Create a fragment shader module.
     * If it is created before, then just return the cached shader module.
     * @param shaderSource The source code of the shader.
     */
    static backend::ShaderModule* newFragmentShaderModule(const std::string& shaderSource);
    
    /**
     * Remove all unused shaders.
     */
    void removeUnusedShader();
    
protected:
    virtual ~ShaderCache();
    
    /**
     * Initial shader cache.
     * @return true if initial successful, otherwise false.
     */
    bool init();

    /**
     * New a shaderModule. 
     * If it was created before, then just return the cached shader module.
     * Otherwise add it to cache and return the object.
     * @param stage Specifies whether is vertex shader or fragment shader.
     * @param source Specifies shader source.
     * @return A ShaderModule object.
     */
    static backend::ShaderModule* newShaderModule(backend::ShaderStage stage, const std::string& shaderSource);
    
    static std::unordered_map<std::size_t, backend::ShaderModule*> _cachedShaders;
    static ShaderCache* _sharedShaderCache;
};

//end of _backend group
/// @}
CC_BACKEND_END
