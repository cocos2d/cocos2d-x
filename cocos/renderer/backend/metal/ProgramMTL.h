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

#include "../Program.h"
#import <Metal/Metal.h>

CC_BACKEND_BEGIN

class ShaderModuleMTL;

/**
 * @addtogroup _metal
 * @{
 */

/**
 * A metal Program
 */
class ProgramMTL : public Program
{
public:
    /// @name Constructor, Destructor and Initializers
    /**
     * @param vertexShader Specifes the vertex shader source.
     * @param fragmentShader Specifes the fragment shader source.
     */
    ProgramMTL(const std::string& vertexShader, const std::string& fragmentShader);
    virtual ~ProgramMTL();
    
    /**
     * Get uniform location by name.
     * @param uniform Specifies the uniform name.
     * @return The uniform location.
     */
    virtual UniformLocation getUniformLocation(const std::string& uniform) const override;

    /**
     * Get uniform location by engine built-in uniform enum name.
     * @param name Specifies the engine built-in uniform enum name.
     * @return The uniform location.
     */
    virtual UniformLocation getUniformLocation(backend::Uniform name) const override;
    
    /**
     * Get attribute location by attribute name.
     * @param name Specifies the attribute name.
     * @return The attribute location.
     */
    virtual int getAttributeLocation(const std::string& name) const override;

    /**
     * Get attribute location by engine built-in attribute enum name.
     * @param name Specifies the engine built-in attribute enum name.
     * @return The attribute location.
     */
    virtual int getAttributeLocation(Attribute name) const override;
    
    /**
     * Get vertex shader module.
     * @return Vertex shader module.
     */
    virtual ShaderModuleMTL* getVertexShader() const { return _vertexShader; }
    
    /**
     * Get fragment shader module.
     * @ Fragment shader module.
     */
    virtual ShaderModuleMTL* getFragmentShader() const { return _fragmentShader; }
    
    /**
     * Get active vertex attributes.
     * @return Active vertex attributes. key is active attribute name, Value is corresponding attribute info.
     */
    const std::unordered_map<std::string, AttributeBindInfo> getActiveAttributes() const override;
    
    /**
     * Get maximum vertex location.
     * @return Maximum vertex locaiton.
     */
    virtual int getMaxVertexLocation() const override;
    
    /**
     * Get maximum fragment location.
     * @return Maximum fragment location.
     */
    virtual int getMaxFragmentLocation() const override;
    
    /**
     * Get uniform buffer size in bytes that can hold all the uniforms.
     * @param stage Specifies the shader stage. The symbolic constant can be either VERTEX or FRAGMENT.
     * @return The uniform buffer size in bytes.
     */
    virtual std::size_t getUniformBufferSize(ShaderStage stage) const override;

    /**
     * Get a uniformInfo in given location from the specific shader stage.
     * @param stage Specifies the shader stage. The symbolic constant can be either VERTEX or FRAGMENT.
     * @param location Specifies the uniform locaion.
     * @return The uniformInfo.
     */
    virtual const UniformInfo& getActiveUniformInfo(ShaderStage stage, int location) const override;

    /**
     * Get all uniformInfos.
     * @return The uniformInfos.
     */
    virtual const std::unordered_map<std::string, UniformInfo>& getAllActiveUniformInfo(ShaderStage stage) const override;

private:
    ShaderModuleMTL* _vertexShader = nullptr;
    ShaderModuleMTL* _fragmentShader = nullptr;
};

// end of _metal group
/// @}
CC_BACKEND_END
