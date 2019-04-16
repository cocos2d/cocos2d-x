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

#if CC_ENABLE_CACHE_TEXTURE_DATA
    virtual void deleteShader() = 0;
#endif

    ShaderStage _stage = ShaderStage::VERTEX;
};

CC_BACKEND_END
