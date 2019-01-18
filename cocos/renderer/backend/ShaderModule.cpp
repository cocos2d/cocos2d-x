#include "ShaderModule.h"

CC_BACKEND_BEGIN

ShaderStage ShaderModule::getShaderStage() const
{
    return _stage;
}

ShaderModule::ShaderModule(ShaderStage stage):
_stage(stage)
{
}

ShaderModule::~ShaderModule()
{}

CC_BACKEND_END
