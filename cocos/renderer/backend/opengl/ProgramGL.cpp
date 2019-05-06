#include "ProgramGL.h"
#include "ShaderModuleGL.h"
#include "renderer/backend/Types.h"
#include "base/ccMacros.h"
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventType.h"
#include "renderer/backend/opengl/UtilsGL.h"

CC_BACKEND_BEGIN


ProgramGL::ProgramGL(const std::string& vertexShader, const std::string& fragmentShader)
: Program(vertexShader, fragmentShader)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    string headersDef("#version 100\n precision highp float;\n precision highp int;\n");
    _vertexShader.insert(0, headersDef);
    _fragmentShader.insert(0, headersDef);
#endif
    

    _vertexShaderModule = static_cast<ShaderModuleGL*>(ShaderCache::newVertexShaderModule(_vertexShader));
    _fragmentShaderModule = static_cast<ShaderModuleGL*>(ShaderCache::newFragmentShaderModule(_fragmentShader));

    CC_SAFE_RETAIN(_vertexShaderModule);
    CC_SAFE_RETAIN(_fragmentShaderModule);
    compileProgram();
    computeUniformInfos();

#if CC_ENABLE_CACHE_TEXTURE_DATA
    for(const auto& uniform: _uniformInfos)
    {
        UniformLocation uniformLocation;
        uniformLocation.location = glGetUniformLocation(_program, uniform.first.c_str());
        _originalUniformLocations[uniform.first] = uniformLocation;
        _uniformLocationMap[uniform.second.location] = uniform.second.location;
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
    _uniformInfos.clear();
    static_cast<ShaderModuleGL*>(_vertexShaderModule)->compileShader(backend::ShaderStage::VERTEX, _vertexShader);
    static_cast<ShaderModuleGL*>(_fragmentShaderModule)->compileShader(backend::ShaderStage::FRAGMENT, _fragmentShader);
    compileProgram();
    computeUniformInfos();

    for(const auto& uniform : _uniformInfos)
    {
        auto location = _originalUniformLocations[uniform.first].location;
        _uniformLocationMap[location] = uniform.second.location;
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

void ProgramGL::computeAttributeInfos(const RenderPipelineDescriptor& descriptor)
{
    _attributeInfos.clear();
    const auto& vertexLayouts = descriptor.vertexLayouts;
    for (const auto& vertexLayout : *vertexLayouts)
    {
        if (! vertexLayout.isValid())
            continue;
        
        VertexAttributeArray vertexAttributeArray;
        
        const auto& attributes = vertexLayout.getAttributes();
        for (const auto& it : attributes)
        {
            auto &attribute = it.second;
            AttributeInfo attributeInfo;
            
            if (!getAttributeLocation(attribute.name, attributeInfo.location))
                continue;
            
            attributeInfo.stride = vertexLayout.getStride();
            attributeInfo.offset = attribute.offset;
            attributeInfo.type = UtilsGL::toGLAttributeType(attribute.format);
            attributeInfo.size = UtilsGL::getGLAttributeSize(attribute.format);
            attributeInfo.needToBeNormallized = attribute.needToBeNormallized;
            attributeInfo.name = attribute.name;

            vertexAttributeArray.push_back(attributeInfo);
        }
        
        _attributeInfos.push_back(std::move(vertexAttributeArray));
    }
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
        uniform.bufferSize = UtilsGL::getGLDataTypeSize(uniform.type);
        _uniformInfos[uniformName] = uniform;

        _maxLocation = _maxLocation <= uniform.location ? (uniform.location + 1) : _maxLocation;
    }
    free(uniformName);
}

UniformLocation ProgramGL::getUniformLocation(const std::string& uniform) const
{
    UniformLocation uniformLocation;
#if CC_ENABLE_CACHE_TEXTURE_DATA
    if(_originalUniformLocations.find(uniform) != _originalUniformLocations.end())
        return _originalUniformLocations.at(uniform);
    else
        return uniformLocation;
#else
    uniformLocation.location = glGetUniformLocation(_program, uniform.c_str());
    return uniformLocation;
#endif
}

const std::unordered_map<std::string, UniformInfo>& ProgramGL::getVertexUniformInfos() const
{
    return _uniformInfos;
}

const std::unordered_map<std::string, UniformInfo>& ProgramGL::getFragmentUniformInfos() const
{
    return _uniformInfos;
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
    if(_uniformLocationMap.find(location) != _uniformLocationMap.end())
        return _uniformLocationMap.at(location);
    else
        return -1;
}
#endif

CC_BACKEND_END
