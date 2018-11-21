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

#include "ShaderCache.h"
#include "renderer/backend/Device.h"

NS_CC_BEGIN

std::unordered_map<std::string, backend::ShaderModule*> ShaderCache::_cachedVertexShaders;
std::unordered_map<std::string, backend::ShaderModule*> ShaderCache::_cachedFragmentShaders;

backend::ShaderModule* ShaderCache::newVertexShaderModule(const std::string& key, const std::string& shaderSource)
{
    auto iter = ShaderCache::_cachedVertexShaders.find(key);
    if (ShaderCache::_cachedVertexShaders.end() != iter)
        return iter->second;
    
    auto shader = backend::Device::getInstance()->createShaderModule(backend::ShaderStage::VERTEX, shaderSource);
    CC_SAFE_RETAIN(shader);
    ShaderCache::_cachedVertexShaders.emplace(key, shader);
    
    return shader;
}

backend::ShaderModule* ShaderCache::newFragmentShaderModule(const std::string& key, const std::string& shaderSource)
{
    auto iter = ShaderCache::_cachedFragmentShaders.find(key);
    if (ShaderCache::_cachedFragmentShaders.end() != iter)
        return iter->second;
    
    auto shader = backend::Device::getInstance()->createShaderModule(backend::ShaderStage::FRAGMENT, shaderSource);
    CC_SAFE_RETAIN(shader);
    ShaderCache::_cachedFragmentShaders.emplace(key, shader);
    
    return shader;
}

NS_CC_END
