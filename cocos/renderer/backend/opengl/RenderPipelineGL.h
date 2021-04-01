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

#include "../RenderPipeline.h"
#include "../RenderPipelineDescriptor.h"

#include "platform/CCGL.h"

#include <vector>

CC_BACKEND_BEGIN

class ProgramGL;
/**
 * @addtogroup _opengl
 * @{
 */

/**
 * Set program and blend state.
 */
class RenderPipelineGL : public RenderPipeline
{
public:
    /**
     * @param descriptor Specifies render pipeline descriptor.
     */
    RenderPipelineGL() = default;
    ~RenderPipelineGL();

    virtual void update(const PipelineDescriptor & pipelineDescirptor, const RenderPassDescriptor& renderpassDescriptor) override;
    /**
     * Get program instance.
     * @return Program instance.
     */
    inline ProgramGL* getProgram() const { return _programGL; }

private:
    void updateBlendState(const BlendDescriptor& descriptor);

    ProgramGL* _programGL = nullptr;
};
// end of _opengl group
/// @}
CC_BACKEND_END
