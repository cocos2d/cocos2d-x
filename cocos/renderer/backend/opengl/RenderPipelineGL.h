#pragma once

#include "../RenderPipeline.h"
#include "../RenderPipelineDescriptor.h"

#include "platform/CCGL.h"

#include <vector>

CC_BACKEND_BEGIN

class ProgramGL;
class BlendStateGL;

class RenderPipelineGL : public RenderPipeline
{
public:
    RenderPipelineGL(const RenderPipelineDescriptor& descriptor);
    ~RenderPipelineGL();
    
    inline ProgramGL* getProgram() const { return _programGL; }
    inline BlendStateGL* getBlendState() const { return _blendState; }
    inline const std::vector<VertexLayout> & getVertexLayouts() const{ return _vertexLayouts; }
private:
    ProgramGL* _programGL = nullptr;
    BlendStateGL* _blendState = nullptr;
    std::vector<VertexLayout> _vertexLayouts;
};

CC_BACKEND_END
