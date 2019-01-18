#pragma once

#include "Macros.h"
#include "Types.h"

#include "base/CCRef.h"

CC_BACKEND_BEGIN

class RenderPipeline : public cocos2d::Ref
{
protected:
    virtual ~RenderPipeline() = default;
};

CC_BACKEND_END
