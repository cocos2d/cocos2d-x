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

class ProgramGL : public Program
{
public:
    typedef std::vector<AttributeInfo> VertexAttributeArray;
    
    ProgramGL(const std::string& vertexShader, const std::string& fragmentShader);
    ~ProgramGL();
    
    inline const std::vector<VertexAttributeArray>& getAttributeInfos() const { return _attributeInfos; }
    inline GLuint getHandler() const { return _program; }
    void computeAttributeInfos(const RenderPipelineDescriptor& descriptor);

    virtual const std::unordered_map<std::string, UniformInfo>& getVertexUniformInfos() const override;
    virtual const std::unordered_map<std::string, UniformInfo>& getFragmentUniformInfos() const override;

    virtual UniformLocation getUniformLocation(const std::string& uniform) const override;

    virtual int getMaxVertexLocation() const override;
    virtual int getMaxFragmentLocation() const override;

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

CC_BACKEND_END
