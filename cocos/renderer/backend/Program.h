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
     * Get engine built-in program.
     * @param type Specifies the built-in program type.
     */
    static Program* getBuiltinProgram(ProgramType type);
    
    /**
     * Get uniform location by name.
     * @param uniform Specifies the uniform name.
     * @return The uniform location.
     */
    virtual UniformLocation getUniformLocation(const std::string& uniform) const = 0;

    /**
     * Get uniform location by engine built-in uniform enum name.
     * @param name Specifies the engine built-in uniform enum name.
     * @return The uniform location.
     */
    virtual UniformLocation getUniformLocation(backend::Uniform name) const = 0;

    /**
     * Get attribute location by attribute name.
     * @param name Specifies the attribute name.
     * @return The attribute location.
     */
    virtual int getAttributeLocation(const std::string& name) const =  0;

    /**
     * Get attribute location by engine built-in attribute enum name.
     * @param name Specifies the engine built-in attribute enum name.
     * @return The attribute location.
     */
    virtual int getAttributeLocation(backend::Attribute name) const =  0;
    
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
    
    /**
     * Get engine built-in program type.
     * @return The built-in program type.
     */
    ProgramType getProgramType() const { return _programType; }

    /**
     * Get uniform buffer size in bytes that can hold all the uniforms.
     * @param stage Specifies the shader stage. The symbolic constant can be either VERTEX or FRAGMENT.
     * @return The uniform buffer size in bytes.
     */
    virtual std::size_t getUniformBufferSize(ShaderStage stage) const =0;

    /**
     * Get a uniformInfo in given location from the specific shader stage.
     * @param stage Specifies the shader stage. The symbolic constant can be either VERTEX or FRAGMENT.
     * @param location Specifies the uniform locaion.
     * @return The uniformInfo.
     */
    virtual const UniformInfo& getActiveUniformInfo(ShaderStage stage, int location) const = 0;

    /**
     * Get all uniformInfos.
     * @return The uniformInfos.
     */
    virtual const std::unordered_map<std::string, UniformInfo>& getAllActiveUniformInfo(ShaderStage stage) const = 0;
    
protected:
    /**
     * Set engin built-in program type.
     * @param type Specifies the program type.
     */
    void setProgramType(ProgramType type);
    
    /**
     * @param vs Specifes the vertex shader source.
     * @param fs Specifes the fragment shader source.
     */
    Program(const std::string& vs, const std::string& fs);

#if CC_ENABLE_CACHE_TEXTURE_DATA
    /**
     * In case of EGL context lost, the engine will reload shaders. Thus location of uniform may changed.
     * The engine will maintain the relationship between the original uniform location and the current active uniform location.
     * @param location Specifies original location.
     * @return Current active uniform location.
     * @see `int getOriginalLocation(int location) const`
     */
    virtual int getMappedLocation(int location) const = 0;

    /**
     * In case of EGL context lost, the engine will reload shaders. Thus location of uniform may changed.
     * The engine will maintain the relationship between the original uniform location and the current active uniform location.
     * @param location Specifies the current active uniform location.
     * @return The original uniform location.
     * @see `int getMappedLocation(int location) const`
     */
    virtual int getOriginalLocation(int location) const = 0;

    /**
     * Get all uniform locations.
     * @return All uniform locations.
     */
    virtual const std::unordered_map<std::string, int> getAllUniformsLocation() const = 0;
    friend class ProgramState;
#endif
    friend class ProgramCache;
    
    std::string _vertexShader; ///< Vertex shader.
    std::string _fragmentShader; ///< Fragment shader.
    ProgramType _programType = ProgramType::CUSTOM_PROGRAM; ///< built-in program type, initial value is CUSTOM_PROGRAM.
};

//end of _backend group
/// @}
CC_BACKEND_END
