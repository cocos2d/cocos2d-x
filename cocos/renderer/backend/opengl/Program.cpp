#include "Program.h"
#include "ShaderModuleGL.h"

CC_BACKEND_BEGIN

namespace
{
    GLenum toGLAttributeType(VertexFormat vertexFormat)
    {
        GLenum ret = GL_INT;
        switch (vertexFormat)
        {
            case VertexFormat::FLOAT_R32G32B32A32:
            case VertexFormat::FLOAT_R32G32B32:
            case VertexFormat::FLOAT_R32G32:
            case VertexFormat::FLOAT_R32:
                ret = GL_FLOAT;
                break;
            case VertexFormat::INT_R32G32B32A32:
            case VertexFormat::INT_R32G32B32:
            case VertexFormat::INT_R32G32:
            case VertexFormat::INT_R32:
                ret = GL_INT;
                break;
            case VertexFormat::UBYTE_R8G8B8A8:
                ret = GL_UNSIGNED_BYTE;
                break;
            default:
                break;
        }
        return ret;
    }
    
    GLsizei getGLAttributeSize(VertexFormat vertexFormat)
    {
        GLsizei ret = 0;
        switch (vertexFormat)
        {
            case VertexFormat::FLOAT_R32G32B32A32:
            case VertexFormat::INT_R32G32B32A32:
            case VertexFormat::UBYTE_R8G8B8A8:
                ret = 4;
                break;
            case VertexFormat::FLOAT_R32G32B32:
            case VertexFormat::INT_R32G32B32:
                ret = 3;
                break;
            case VertexFormat::FLOAT_R32G32:
            case VertexFormat::INT_R32G32:
                ret = 2;
                break;
            case VertexFormat::FLOAT_R32:
            case VertexFormat::INT_R32:
                ret = 1;
                break;
            default:
                break;
        }
        return ret;
    }
}

Program::Program(const RenderPipelineDescriptor& descriptor)
: _vertexShaderModule(static_cast<ShaderModuleGL*>(descriptor.getVertexShaderModule()))
, _fragmentShaderModule(static_cast<ShaderModuleGL*>(descriptor.getFragmentShaderModule()))
{
    assert(_vertexShaderModule != nullptr && _fragmentShaderModule != nullptr);
    
    CC_SAFE_RETAIN(_vertexShaderModule);
    CC_SAFE_RETAIN(_fragmentShaderModule);
    
    compileProgram();
    computeAttributeInfos(descriptor);
    computeUniformInfos();
}

Program::~Program()
{
    CC_SAFE_RELEASE(_vertexShaderModule);
    CC_SAFE_RELEASE(_fragmentShaderModule);
    if (_program)
        glDeleteProgram(_program);
}

void Program::compileProgram()
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

void Program::computeAttributeInfos(const RenderPipelineDescriptor& descriptor)
{
    const auto& vertexLayouts = descriptor.getVertexLayouts();
    for (const auto& vertexLayout : vertexLayouts)
    {
        if (! vertexLayout.isValid())
            continue;
        
        VertexAttributeArray vertexAttributeArray;
        
        const auto& attributes = vertexLayout.getAttributes();
        for (const auto& attribute : attributes)
        {
            AttributeInfo attributeInfo;
            
            if (!getAttributeLocation(attribute.name, attributeInfo.location))
                continue;
            
            attributeInfo.stride = vertexLayout.getStride();
            attributeInfo.offset = attribute.offset;
            attributeInfo.type = toGLAttributeType(attribute.format);
            attributeInfo.size = getGLAttributeSize(attribute.format);
            attributeInfo.normalized = attribute.normalized;
            
            vertexAttributeArray.push_back(attributeInfo);
        }
        
        _attributeInfos.push_back(std::move(vertexAttributeArray));
    }
}

bool Program::getAttributeLocation(const std::string& attributeName, uint32_t& location)
{
    GLint loc = glGetAttribLocation(_program, attributeName.c_str());
    if (-1 == loc)
    {
        printf("Cocos2d: %s: can not find vertex attribute of %s", __FUNCTION__, attributeName.c_str());
        return false;
    }
    
    location = GLuint(loc);
    return true;
}

void Program::computeUniformInfos()
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
        glGetActiveUniform(_program, i, MAX_UNIFORM_NAME_LENGTH, &length, &uniform.size, &uniform.type, uniformName);
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
        
        uniform.name = uniformName;
        uniform.location = glGetUniformLocation(_program, uniformName);
        
        _uniformInfos.push_back(uniform);
    }
    free(uniformName);
}

CC_BACKEND_END
