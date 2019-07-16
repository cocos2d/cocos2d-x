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

#include "../Macros.h"
#include "../Types.h"
#include "../RenderPipelineDescriptor.h"
#include "base/CCRef.h"
#include "base/CCEventListenerCustom.h"
#include "platform/CCGL.h"
#include "../Program.h"

#include <string>
#include <vector>
#include <unordered_map>

CC_BACKEND_BEGIN

class ShaderModuleGL;

/**
 * Store attribute information.
 */
struct AttributeInfo
{
    unsigned int location = 0;
    unsigned int size = 0;
    GLenum type = GL_BYTE;
    GLsizei stride = 0;
    unsigned int offset = 0;
    GLboolean needToBeNormallized = GL_FALSE;
    std::string name;
};

/**
 * @addtogroup _opengl
 * @{
 */

/**
 * An OpenGL program.
 */
class ProgramGL : public Program
{
public:
    typedef std::vector<AttributeInfo> VertexAttributeArray;
    
    /**
     * @param vertexShader Specifes the vertex shader source.
     * @param fragmentShader Specifes the fragment shader source.
     */
    ProgramGL(const std::string& vertexShader, const std::string& fragmentShader);
    ~ProgramGL();
    
    /**
     * Get attribute informations.
     * @return Attribute informations.
     */
    inline const std::vector<VertexAttributeArray>& getAttributeInfos() const { return _attributeInfos; }

    /**
     * Get program object.
     * @return Program object.
     */
    inline GLuint getHandler() const { return _program; }

    /**
     * Calculate attribute information according to vertex layout.
     */
    void computeAttributeInfos(const RenderPipelineDescriptor& descriptor);

    /**
     * Get vertex uniform infomation.
     * @return Vertex uniform information. Key is uniform name, Value is corresponding uniform info.
     */
    virtual const std::unordered_map<std::string, UniformInfo>& getVertexUniformInfos() const override;

    /**
     * Get fragment uniform information.
     * @return Fragment uniform information. Key is uniform name, Value is corresponding uniform info.
     */
    virtual const std::unordered_map<std::string, UniformInfo>& getFragmentUniformInfos() const override;

    /**
     * Get uniform location by name.
     * @param uniform Specifies the uniform name.
     * @return The uniform location.
     */
    virtual UniformLocation getUniformLocation(const std::string& uniform) const override;

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
     * Get active vertex attributes.
     * @return Active vertex attributes. key is active attribute name, Value is corresponding attribute info.
     */
    virtual const std::unordered_map<std::string, AttributeBindInfo> getActiveAttributes() const override;

private:
    void compileProgram();
    bool getAttributeLocation(const std::string& attributeName, unsigned int& location) const;
    void computeUniformInfos();
#if CC_ENABLE_CACHE_TEXTURE_DATA
    virtual void reloadProgram();
    virtual int getMappedLocation(int location) const override;
    virtual const std::unordered_map<std::string, UniformLocation> getAllUniformsLocation() const override { return _originalUniformLocations; }
#endif
    
    GLuint _program = 0;
    ShaderModuleGL* _vertexShaderModule = nullptr;
    ShaderModuleGL* _fragmentShaderModule = nullptr;
    
    std::vector<VertexAttributeArray> _attributeInfos;
    std::unordered_map<std::string, UniformInfo> _uniformInfos;
#if CC_ENABLE_CACHE_TEXTURE_DATA
    std::unordered_map<std::string, UniformLocation> _originalUniformLocations;
    std::unordered_map<int, int> _uniformLocationMap;
    EventListenerCustom* _backToForegroundListener = nullptr;
#endif
    
    int _maxLocation = -1;
};
//end of _opengl group
/// @}
CC_BACKEND_END
