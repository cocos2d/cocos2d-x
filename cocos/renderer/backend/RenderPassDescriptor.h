/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
 
#pragma once

#include <array>
#include <vector>

#include "Macros.h"
#include "Types.h"

CC_BACKEND_BEGIN

class TextureBackend;
/**
 * @addtogroup _backend
 * @{
 */

/**
 * Store values about color, depth and stencil attachment.
 */
struct RenderPassDescriptor
{
    RenderPassDescriptor& operator=(const RenderPassDescriptor& descriptor);
    bool operator==(const RenderPassDescriptor& descriptor) const;
    bool needDepthStencilAttachment() const { return depthTestEnabled || stencilTestEnabled; }

    float clearDepthValue = 0.f;
    float clearStencilValue = 0.f;
    std::array<float, 4> clearColorValue {{0.f, 0.f, 0.f, 0.f}}; // double-braces required in C++11
    bool needColorAttachment = true;
    bool depthTestEnabled = false;
    bool stencilTestEnabled = false;
    bool needClearColor = false;
    bool needClearDepth = false;
    bool needClearStencil = false;
    TextureBackend* depthAttachmentTexture = nullptr;
    TextureBackend* stencilAttachmentTexture = nullptr;
    TextureBackend* colorAttachmentsTexture[MAX_COLOR_ATTCHMENT] = { nullptr };
};

//end of _backend group
/// @}
CC_BACKEND_END
