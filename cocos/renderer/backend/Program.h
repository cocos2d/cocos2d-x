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
/**
 * @addtogroup _backend
 * @{
 */

/**
 * A program.
 */
class Program : public Ref
{
public:
    /**
     * Get vertex uniform infomation.
     * @return Vertex uniform information. Key is uniform name, Value is corresponding uniform info.
     */
    virtual const std::unordered_map<std::string, UniformInfo>& getVertexUniformInfos() const = 0;

    /**
     * Get fragment uniform information.
     * @return Fragment uniform information. Key is uniform name, Value is corresponding uniform info.
     */
    virtual const std::unordered_map<std::string, UniformInfo>& getFragmentUniformInfos() const = 0;
    
    /**
     * Get uniform location by name.
     * @param uniform Specifies the uniform name.
     * @return The uniform location.
     */
    virtual UniformLocation getUniformLocation(const std::string& uniform) const = 0;
    
    /**
     * Get maximum vertex location.
     * @return Maximum vertex locaiton.
     */
    virtual int getMaxVertexLocation() const = 0;

    /**
     * Get maximum fragment location.
     * @return Maximum fragment location.
     */
    virtual int getMaxFragmentLocation() const = 0;

    /**
     * Get active vertex attributes.
     * @return Active vertex attributes. key is active attribute name, Value is corresponding attribute info.
     */
    virtual const std::unordered_map<std::string, AttributeBindInfo> getActiveAttributes() const = 0;

    /**
     * Get vertex shader.
     * @return Vertex shader.
     */
    const std::string& getVertexShader() const { return _vertexShader; }

    /**
     * Get fragment shader.
     * @ Fragment shader.
     */
    const std::string& getFragmentShader() const { return _fragmentShader; }
    
protected:
    /**
     * @param vs Specifes the vertex shader source.
     * @param fs Specifes the fragment shader source.
     */
    Program(const std::string& vs, const std::string& fs);

#if CC_ENABLE_CACHE_TEXTURE_DATA
    /**
     * Get the ture location after opengl program reload.
     * @param location Specifies original location before EGL context lost.
     */
    virtual int getMappedLocation(int location) const = 0;

    /**
     * Get all uniform locations.
     * @return All uniform locations.
     */
    virtual const std::unordered_map<std::string, UniformLocation> getAllUniformsLocation() const = 0;
    friend class ProgramState;
    friend class ProgramCache;
#endif
    
    std::string _vertexShader; ///< Vertex shader.
    std::string _fragmentShader; ///< Fragment shader.
};

//end of _backend group
/// @}
CC_BACKEND_END
