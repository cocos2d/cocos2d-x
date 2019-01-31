#include "ProgramMTL.h"
#include "ShaderModuleMTL.h"

CC_BACKEND_BEGIN

ProgramMTL::ProgramMTL(id<MTLDevice> mtlDevice, const std::string& vertexShader, const std::string& fragmentShader)
: Program(vertexShader, fragmentShader)
{
    _vertexShader = static_cast<ShaderModuleMTL*>(ShaderCache::newVertexShaderModule(vertexShader));
    _fragmentShader = static_cast<ShaderModuleMTL*>(ShaderCache::newFragmentShaderModule(fragmentShader));
    
    CC_SAFE_RETAIN(_vertexShader);
    CC_SAFE_RETAIN(_fragmentShader);
}

ProgramMTL::~ProgramMTL()
{
    CC_SAFE_RELEASE(_vertexShader);
    CC_SAFE_RELEASE(_fragmentShader);
}

UniformLocation ProgramMTL::getUniformLocation(const std::string& uniform) const
{
    UniformLocation uniformLocation;
    const auto& vsUniforms = _vertexShader->getUniforms();
    const auto& vsIter = vsUniforms.find(uniform);
    bool definedInVertex = false;
    if(vsIter != vsUniforms.end())
    {
        definedInVertex = true;
        uniformLocation.shaderStage = ShaderStage::VERTEX;
        uniformLocation.location = vsIter->second.location;
    }
    
    const auto& fsUniforms = _fragmentShader->getUniforms();
    const auto& fsIter = fsUniforms.find(uniform);
    if(fsIter != fsUniforms.end())
    {
        uniformLocation.shaderStage = (definedInVertex) ? ShaderStage::VERTEX_AND_FRAGMENT : ShaderStage::FRAGMENT;
        uniformLocation.location = fsIter->second.location;
    }
    
    return uniformLocation;
}

const std::unordered_map<std::string, UniformInfo>& ProgramMTL::getVertexUniformInfos() const
{
    return _vertexShader->getUniforms();
}

const std::unordered_map<std::string, UniformInfo>& ProgramMTL::getFragmentUniformInfos() const
{
    return _fragmentShader->getUniforms();
}

int ProgramMTL::getMaxVertexLocation() const
{
    return _vertexShader->getMaxLocation();
}

int ProgramMTL::getMaxFragmentLocation() const
{
    return _fragmentShader->getMaxLocation();
}

std::vector<AttributeBindInfo> ProgramMTL::getActiveAttributes() const
{
    //TODO arnold
    return _vertexShader->getAttributeInfo();
}

CC_BACKEND_END
