#pragma once

#include "../RenderPipeline.h"
#include "../RenderPipelineDescriptor.h"

#include "platform/CCGL.h"

#include <vector>

CC_BACKEND_BEGIN

class DepthStencilStateGL;
class Program;
class BlendStateGL;

class RenderPipelineGL : public RenderPipeline
{
public:
    RenderPipelineGL(const RenderPipelineDescriptor& descriptor);
    ~RenderPipelineGL();
    
    inline Program* getProgram() const { return _program; }
    inline DepthStencilStateGL* getDepthStencilState() const { return _depthStencilState; }
    inline BlendStateGL* getBlendState() const { return _blendState; }
    
private:
    Program* _program = nullptr;
    DepthStencilStateGL* _depthStencilState = nullptr;
    BlendStateGL* _blendState = nullptr;
};

CC_BACKEND_END
