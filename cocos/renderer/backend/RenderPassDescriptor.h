#pragma once

#include <array>
#include <vector>

#include "Macros.h"
#include "Types.h"

CC_BACKEND_BEGIN

class Texture;

struct RenderPassDescriptor
{
    RenderPassDescriptor& operator=(const RenderPassDescriptor& descriptor);
    bool operator==(const RenderPassDescriptor& descriptor);

    float clearDepthValue = 0.f;
    float clearStencilValue = 0.f;
    std::array<float, 4> clearColorValue {{0.f, 0.f, 0.f, 0.f}}; // double-braces required in C++11
    bool needColorAttachment = true;
    bool depthTestEnabled = false;
    bool stencilTestEnabled = false;
    bool needClearColor = false;
    bool needClearDepth = false;
    bool needClearStencil = false;
    Texture* depthAttachmentTexture = nullptr;
    Texture* stencilAttachmentTexture = nullptr;
    Texture* colorAttachmentsTexture[MAX_COLOR_ATTCHMENT] = { nullptr };
};

CC_BACKEND_END
