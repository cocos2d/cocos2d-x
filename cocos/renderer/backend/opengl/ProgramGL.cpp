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
 
#include "ProgramGL.h"
#include "ShaderModuleGL.h"
#include "renderer/backend/Types.h"
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventType.h"
#include "renderer/backend/opengl/UtilsGL.h"

CC_BACKEND_BEGIN
namespace {
    std::string vsPreDefine("#version 100\n precision highp float;\n precision highp int;\n");
    std::string fsPreDefine("precision mediump float;\n precision mediump int;\n");
}

ProgramGL::ProgramGL(const std::string& vertexShader, const std::string& fragmentShader)
: Program(vertexShader, fragmentShader)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    //some device required manually specify the precision qualifiers for vertex shader.
    _vertexShaderModule = static_cast<ShaderModuleGL*>(ShaderCache::newVertexShaderModule(std::move(vsPreDefine + _vertexShader)));
    _fragmentShaderModule = static_cast<ShaderModuleGL*>(ShaderCache::newFragmentShaderModule(std::move(fsPreDefine +  _fragmentShader)));
#else
    _vertexShaderModule = static_cast<ShaderModuleGL*>(ShaderCache::newVertexShaderModule(_vertexShader));
    _fragmentShaderModule = static_cast<ShaderModuleGL*>(ShaderCache::newFragmentShaderModule(_fragmentShader));
#endif

    CC_SAFE_RETAIN(_vertexShaderModule);
    CC_SAFE_RETAIN(_fragmentShaderModule);
    compileProgram();
    computeUniformInfos();
    computeLocations();
#if CC_ENABLE_CACHE_TEXTURE_DATA
    for(const auto& uniform: _activeUniformInfos)
    {
        auto location = uniform.second.location;
        _originalUniformLocations[uniform.first] = location;
        _mapToCurrentActiveLocation[location] = location;
        _mapToOriginalLocation[location] = location;
    }

    _backToForegroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom*){
        this->reloadProgram();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, -1);
#endif
}

ProgramGL::~ProgramGL()
{
    CC_SAFE_RELEASE(_vertexShaderModule);
    CC_SAFE_RELEASE(_fragmentShaderModule);
    if (_program)
        glDeleteProgram(_program);

#if CC_ENABLE_CACHE_TEXTURE_DATA
    Director::getInstance()->getEventDispatcher()->removeEventListener(_backToForegroundListener);
#endif
}

#if CC_ENABLE_CACHE_TEXTURE_DATA
void ProgramGL::reloadProgram()
{
    _activeUniformInfos.clear();
    _mapToCurrentActiveLocation.clear();
    _mapToOriginalLocation.clear();
    static_cast<ShaderModuleGL*>(_vertexShaderModule)->compileShader(backend::ShaderStage::VERTEX, std::move(vsPreDefine + _vertexShader));
    static_cast<ShaderModuleGL*>(_fragmentShaderModule)->compileShader(backend::ShaderStage::FRAGMENT, std::move(fsPreDefine + _fragmentShader));
    compileProgram();
    computeUniformInfos();

    for(const auto& uniform : _activeUniformInfos)
    {
        auto location = _originalUniformLocations[uniform.first];
        _mapToCurrentActiveLocation[location] = uniform.second.location;
        _mapToOriginalLocation[uniform.second.location] = location;
    }
}
#endif

void ProgramGL::compileProgram()
{
    if (_vertexShaderModule == nullptr || _fragmentShaderModule == nullptr)
        return;
    
    auto vertShader = _vertexShaderModule->getShader();
    auto fragShader = _fragmentShaderModule->getShader();
    
    assert (vertShader != 0 && fragShader != 0);
    if (vertShader == 0 || fragShader == 0)
        return;
    
    _program = glCreateProgram();
    if (!_program)
        return;
    
    glAttachShader(_program, vertShader);
    glAttachShader(_program, fragShader);
    
    glLinkProgram(_program);
    
    GLint status = 0;
    glGetProgramiv(_program, GL_LINK_STATUS, &status);
    if (GL_FALSE == status)
    {
        printf("cocos2d: ERROR: %s: failed to link program ", __FUNCTION__);
        glDeleteProgram(_program);
        _program = 0;
    }
}

void ProgramGL::computeLocations()
{
    std::fill(_builtinAttributeLocation, _builtinAttributeLocation + ATTRIBUTE_MAX, -1);
//    std::fill(_builtinUniformLocation, _builtinUniformLocation + UNIFORM_MAX, -1);

    ///a_position
    auto location = glGetAttribLocation(_program, ATTRIBUTE_NAME_POSITION);
    _builtinAttributeLocation[Attribute::POSITION] = location;

    ///a_color
    location = glGetAttribLocation(_program, ATTRIBUTE_NAME_COLOR);
    _builtinAttributeLocation[Attribute::COLOR] = location;

    ///a_texCoord
    location = glGetAttribLocation(_program, ATTRIBUTE_NAME_TEXCOORD);
    _builtinAttributeLocation[Attribute::TEXCOORD] = location;

    ///u_MVPMatrix
    location = glGetUniformLocation(_program, UNIFORM_NAME_MVP_MATRIX);
    _builtinUniformLocation[Uniform::MVP_MATRIX].location[0] = location;
    _builtinUniformLocation[Uniform::MVP_MATRIX].location[1] = _activeUniformInfos[UNIFORM_NAME_MVP_MATRIX].bufferOffset;

    ///u_textColor
    location = glGetUniformLocation(_program, UNIFORM_NAME_TEXT_COLOR);
    _builtinUniformLocation[Uniform::TEXT_COLOR].location[0] = location;
    _builtinUniformLocation[Uniform::TEXT_COLOR].location[1] = _activeUniformInfos[UNIFORM_NAME_TEXT_COLOR].bufferOffset;

    ///u_effectColor
    location = glGetUniformLocation(_program, UNIFORM_NAME_EFFECT_COLOR);
    _builtinUniformLocation[Uniform::EFFECT_COLOR].location[0] = location;
    _builtinUniformLocation[Uniform::EFFECT_COLOR].location[1] = _activeUniformInfos[UNIFORM_NAME_EFFECT_COLOR].bufferOffset;

    ///u_effectType
    location = glGetUniformLocation(_program, UNIFORM_NAME_EFFECT_TYPE);
    _builtinUniformLocation[Uniform::EFFECT_TYPE].location[0] = location;
    _builtinUniformLocation[Uniform::EFFECT_TYPE].location[1] = _activeUniformInfos[UNIFORM_NAME_EFFECT_TYPE].bufferOffset;

    ///u_texture
    location = glGetUniformLocation(_program, UNIFORM_NAME_TEXTURE);
    _builtinUniformLocation[Uniform::TEXTURE].location[0] = location;

    ///u_texture1
    location = glGetUniformLocation(_program, UNIFORM_NAME_TEXTURE1);
    _builtinUniformLocation[Uniform::TEXTURE1].location[0] = location;
}

bool ProgramGL::getAttributeLocation(const std::string& attributeName, unsigned int& location) const
{
    GLint loc = glGetAttribLocation(_program, attributeName.c_str());
    if (-1 == loc)
    {
        CCLOG("Cocos2d: %s: can not find vertex attribute of %s", __FUNCTION__, attributeName.c_str());
        return false;
    }
    
    location = GLuint(loc);
    return true;
}

const std::unordered_map<std::string, AttributeBindInfo> ProgramGL::getActiveAttributes() const
{
    std::unordered_map<std::string, AttributeBindInfo> attributes;

    if (!_program) return attributes;

    GLint numOfActiveAttributes = 0;
    glGetProgramiv(_program, GL_ACTIVE_ATTRIBUTES, &numOfActiveAttributes);


    if (numOfActiveAttributes <= 0)
        return attributes;

    attributes.reserve(numOfActiveAttributes);

    int MAX_ATTRIBUTE_NAME_LENGTH = 256;
    std::vector<char> attrName(MAX_ATTRIBUTE_NAME_LENGTH + 1);

    GLint attrNameLen = 0;
    GLenum attrType;
    GLint attrSize;
    backend::AttributeBindInfo info;

    for (int i = 0; i < numOfActiveAttributes; i++)
    {
        glGetActiveAttrib(_program, i, MAX_ATTRIBUTE_NAME_LENGTH, &attrNameLen, &attrSize, &attrType, attrName.data());
        CHECK_GL_ERROR_DEBUG();
        info.attributeName = std::string(attrName.data(), attrName.data() + attrNameLen);
        info.location = glGetAttribLocation(_program, info.attributeName.c_str());
        info.type = attrType;
        info.size = UtilsGL::getGLDataTypeSize(attrType) * attrSize;
        CHECK_GL_ERROR_DEBUG();
        attributes[info.attributeName] = info;
    }

    return attributes;

}

void ProgramGL::computeUniformInfos()
{
    if (!_program)
    return;
    
    GLint numOfUniforms = 0;
    glGetProgramiv(_program, GL_ACTIVE_UNIFORMS, &numOfUniforms);
    if (!numOfUniforms)
    return;
    
#define MAX_UNIFORM_NAME_LENGTH 256
    UniformInfo uniform;
    GLint length = 0;
    _totalBufferSize = 0;
    _maxLocation = -1;
    _activeUniformInfos.clear();
    GLchar* uniformName = (GLchar*)malloc(MAX_UNIFORM_NAME_LENGTH + 1);
    for (int i = 0; i < numOfUniforms; ++i)
    {
        glGetActiveUniform(_program, i, MAX_UNIFORM_NAME_LENGTH, &length, &uniform.count, &uniform.type, uniformName);
        uniformName[length] = '\0';
        
        if (length > 3)
        {
            char* c = strrchr(uniformName, '[');
            if (c)
            {
                *c = '\0';
                uniform.isArray = true;
            }
        }
        uniform.location = glGetUniformLocation(_program, uniformName);
        uniform.size = UtilsGL::getGLDataTypeSize(uniform.type);
        uniform.bufferOffset = (uniform.size == 0) ? 0 : _totalBufferSize;
        _activeUniformInfos[uniformName] = uniform;
        _totalBufferSize += uniform.size * uniform.count;
        _maxLocation = _maxLocation <= uniform.location ? (uniform.location + 1) : _maxLocation;
    }
    free(uniformName);
}

int ProgramGL::getAttributeLocation(Attribute name) const
{
    return _builtinAttributeLocation[name];
}

int ProgramGL::getAttributeLocation(const std::string& name) const
{
    return glGetAttribLocation(_program, name.c_str());
}

UniformLocation ProgramGL::getUniformLocation(backend::Uniform name) const
{
   return _builtinUniformLocation[name];
}

UniformLocation ProgramGL::getUniformLocation(const std::string& uniform) const
{
    UniformLocation uniformLocation;
    if (_activeUniformInfos.find(uniform) != _activeUniformInfos.end())
    {
        const auto &uniformInfo = _activeUniformInfos.at(uniform);
#if CC_ENABLE_CACHE_TEXTURE_DATA
        uniformLocation.location[0] = _mapToOriginalLocation.at(uniformInfo.location);
#else
        uniformLocation.location[0] = uniformInfo.location;
#endif
        uniformLocation.location[1] = uniformInfo.bufferOffset;
    }
    return uniformLocation;
}

int ProgramGL::getMaxVertexLocation() const
{
    return _maxLocation;
}
int ProgramGL::getMaxFragmentLocation() const
{
    return _maxLocation;
}

#if CC_ENABLE_CACHE_TEXTURE_DATA
int ProgramGL::getMappedLocation(int location) const
{
    if(_mapToCurrentActiveLocation.find(location) != _mapToCurrentActiveLocation.end())
        return _mapToCurrentActiveLocation.at(location);
    else
        return -1;
}

int ProgramGL::getOriginalLocation(int location) const
{
    if (_mapToOriginalLocation.find(location) != _mapToOriginalLocation.end())
        return _mapToOriginalLocation.at(location);
    else
        return -1;
}
#endif

const UniformInfo& ProgramGL::getActiveUniformInfo(ShaderStage stage, int location) const
{
    return std::move(UniformInfo{});
}

const std::unordered_map<std::string, UniformInfo>& ProgramGL::getAllActiveUniformInfo(ShaderStage stage) const
{
    return _activeUniformInfos;
}

std::size_t ProgramGL::getUniformBufferSize(ShaderStage stage) const
{
    return _totalBufferSize;
}

CC_BACKEND_END
