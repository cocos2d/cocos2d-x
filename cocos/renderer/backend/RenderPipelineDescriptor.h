#pragma once

#include "Macros.h"
#include "Types.h"
#include "VertexLayout.h"
#include "renderer/backend/ProgramState.h"

#include <vector>
#include <memory>

CC_BACKEND_BEGIN

class DepthStencilState;
class BlendState;

struct RenderPipelineDescriptor
{
    ProgramState* programState = nullptr;
    BlendState* blendState = nullptr;
    std::shared_ptr<std::vector<VertexLayout>> vertexLayouts = std::make_shared<std::vector<VertexLayout>>();
    PixelFormat colorAttachmentsFormat[MAX_COLOR_ATTCHMENT] = { PixelFormat::DEFAULT };
    PixelFormat depthAttachmentFormat = PixelFormat::NONE;
    PixelFormat stencilAttachmentFormat = PixelFormat::NONE;
};

CC_BACKEND_END
