#pragma once

#include "../RenderPipeline.h"
#include "../RenderPipelineDescriptor.h"

#include "platform/CCGL.h"

#include <vector>

CC_BACKEND_BEGIN

class DepthStencilStateGL;
class ProgramGL;
class BlendStateGL;

class RenderPipelineGL : public RenderPipeline
{
public:
    RenderPipelineGL(const RenderPipelineDescriptor& descriptor);
    ~RenderPipelineGL();
    
    inline ProgramGL* getProgram() const { return _programGL; }
    inline DepthStencilStateGL* getDepthStencilState() const { return _depthStencilState; }
    inline BlendStateGL* getBlendState() const { return _blendState; }
    
private:
    ProgramGL* _programGL = nullptr;
    DepthStencilStateGL* _depthStencilState = nullptr;
    BlendStateGL* _blendState = nullptr;
};

CC_BACKEND_END
