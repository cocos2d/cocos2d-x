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

#include <cstdint>

#include "base/CCRef.h"

#include "Macros.h"
#include "Types.h"
#include "RenderPassDescriptor.h"
#include "CCStdC.h"
#include "ProgramState.h"
#include "VertexLayout.h"

#include <memory>
#include <vector>

CC_BACKEND_BEGIN

class RenderPass;
class RenderPipeline;
class Buffer;
class DepthStencilState;


class CommandBuffer : public cocos2d::Ref
{
public:
    virtual void beginFrame() = 0;
    virtual void beginRenderPass(const RenderPassDescriptor& descriptor) = 0;
    virtual void setRenderPipeline(RenderPipeline* renderPipeline) = 0;
    virtual void setViewport(int x, int y, unsigned int w, unsigned int h) = 0;
    virtual void setCullMode(CullMode mode) = 0;
    virtual void setWinding(Winding winding) = 0;
    virtual void setVertexBuffer(unsigned int index, Buffer* buffer) = 0;
    virtual void setProgramState(ProgramState* programState) = 0;
    virtual void setIndexBuffer(Buffer* buffer) = 0;
    virtual void drawArrays(PrimitiveType primitiveType, unsigned int start,  unsigned int count) = 0;
    virtual void drawElements(PrimitiveType primitiveType, IndexFormat indexType, unsigned int count, unsigned int offset) = 0;
    virtual void endRenderPass() = 0;
    virtual void endFrame() = 0;
    
    virtual void setLineWidth(float lineWidth) = 0;
    virtual void setScissorRect(bool isEnabled, float x, float y, float width, float height) = 0;
    virtual void setDepthStencilState(DepthStencilState* depthStencilState) = 0;
    virtual void captureScreen(std::function<void(const unsigned char*, int, int)> callback) = 0;
    
    void setStencilReferenceValue(unsigned int value);
    void setStencilReferenceValue(unsigned int frontRef, unsigned int backRef);

    inline const std::shared_ptr<std::vector<VertexLayout>>& getVertexLayouts() const { return _vertexLayouts; }
    void updateVertexLayouts(const std::shared_ptr<std::vector<VertexLayout>> &layout) { _vertexLayouts = layout; }

protected:
    virtual ~CommandBuffer() = default;
    
    unsigned int _stencilReferenceValueFront = 0;
    unsigned int _stencilReferenceValueBack = 0;
    std::shared_ptr<std::vector<VertexLayout>> _vertexLayouts;
};

CC_BACKEND_END
