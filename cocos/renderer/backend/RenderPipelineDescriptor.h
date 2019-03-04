#pragma once

#include "Macros.h"
#include "Types.h"
#include "VertexLayout.h"
#include "renderer/backend/ProgramState.h"

#include <vector>

CC_BACKEND_BEGIN

class DepthStencilState;
class BlendState;

struct RenderPipelineDescriptor
{
    ProgramState* programState = nullptr;
    BlendState* blendState = nullptr;
    std::vector<VertexLayout> vertexLayouts;
    TextureFormat colorAttachmentsFormat[MAX_COLOR_ATTCHMENT] = { TextureFormat::SYSTEM_DEFAULT };
    TextureFormat depthAttachmentFormat = TextureFormat::D24S8;
    TextureFormat stencilAttachmentFormat = TextureFormat::D24S8;
};

CC_BACKEND_END
