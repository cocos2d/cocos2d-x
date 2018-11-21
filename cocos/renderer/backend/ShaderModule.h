#pragma once

#include "Macros.h"
#include "Types.h"
#include "base/CCRef.h"

#include <string>

CC_BACKEND_BEGIN

class ShaderModule : public cocos2d::Ref
{
public:
    ShaderStage getShaderStage() const;
    
protected:
    ShaderModule(ShaderStage stage);
    virtual ~ShaderModule();
    
    ShaderStage _stage = ShaderStage::VERTEX;
};

CC_BACKEND_END
