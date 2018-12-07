#pragma once

#include "Macros.h"
#include "Types.h"
#include "VertexLayout.h"

#include <vector>

CC_BACKEND_BEGIN

class ShaderModule;
class DepthStencilState;
class BlendState;

struct RenderPipelineDescriptor
{
    ShaderModule* vertexShaderModule = nullptr;
    ShaderModule* fragmentShaderModule = nullptr;
    DepthStencilState* depthStencilState = nullptr;
    BlendState* blendState = nullptr;
    std::vector<VertexLayout> vertexLayouts;
    TextureFormat colorAttachmentsFormat[MAX_COLOR_ATTCHMENT] = { TextureFormat::SYSTEM_DEFAULT, TextureFormat::NONE };
    TextureFormat depthAttachmentFormat = TextureFormat::NONE;
    TextureFormat stencilAttachmentFormat = TextureFormat::NONE;
};

CC_BACKEND_END
