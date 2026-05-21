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

#include "../Macros.h"
#include "../CommandBuffer.h"
#include "base/CCEventListenerCustom.h"
#include "platform/CCGL.h"

#include "CCStdC.h"

#include <vector>

CC_BACKEND_BEGIN

class BufferGL;
class RenderPipelineGL;
class ProgramGL;
class DepthStencilStateGL;

/**
 * @addtogroup _opengl
 * @{
 */

/**
 * @brief Store encoded commands for the GPU to execute.
 * A command buffer stores encoded commands until the buffer is committed for execution by the GPU
 */
class CommandBufferGL final : public CommandBuffer
{
public:
    CommandBufferGL();
    ~CommandBufferGL();
    
    /// @name Setters & Getters
    /**
     * @brief Indicate the begining of a frame
     */
    virtual void beginFrame() override;

    /**
     * Begin a render pass, initial color, depth and stencil attachment.
     * @param descriptor Specifies a group of render targets that hold the results of a render pass.
     */
    virtual void beginRenderPass(const RenderPassDescriptor& descriptor) override;

    /**
     * Sets the current render pipeline state object.
     * @param renderPipeline An object that contains the graphics functions and configuration state used in a render pass.
     */
    virtual void setRenderPipeline(RenderPipeline* renderPipeline) override;
    
    /**
     * Fixed-function state
     * @param x The x coordinate of the upper-left corner of the viewport.
     * @param y The y coordinate of the upper-left corner of the viewport.
     * @param w The width of the viewport, in pixels.
     * @param h The height of the viewport, in pixels.
     */
    virtual void setViewport(int x, int y, unsigned int w, unsigned int h) override;

    /**
     * Fixed-function state
     * @param mode Controls if primitives are culled when front facing, back facing, or not culled at all.
     */
    virtual void setCullMode(CullMode mode) override;

    /**
     * Fixed-function state
     * @param winding The winding order of front-facing primitives.
     */
    virtual void setWinding(Winding winding) override;

    /**
     * Set a global buffer for all vertex shaders at the given bind point index 0.
     * @param buffer The vertex buffer to be setted in the buffer argument table.
     */
    virtual void setVertexBuffer(Buffer* buffer) override;

    /**
     * Set unifroms and textures
     * @param programState A programState object that hold the uniform and texture data.
     */
    virtual void setProgramState(ProgramState* programState) override;

    /**
     * Set indexes when drawing primitives with index list
     * @ buffer A buffer object that the device will read indexes from.
     * @ see `drawElements(PrimitiveType primitiveType, IndexFormat indexType, unsigned int count, unsigned int offset)`
     */
    virtual void setIndexBuffer(Buffer* buffer) override;

    /**
     * Draw primitives without an index list.
     * @param primitiveType The type of primitives that elements are assembled into.
     * @param start For each instance, the first index to draw
     * @param count For each instance, the number of indexes to draw
     * @see `drawElements(PrimitiveType primitiveType, IndexFormat indexType, unsigned int count, unsigned int offset)`
     */
    virtual void drawArrays(PrimitiveType primitiveType, std::size_t start,  std::size_t count) override;

    /**
     * Draw primitives with an index list.
     * @param primitiveType The type of primitives that elements are assembled into.
     * @param indexType The type if indexes, either 16 bit integer or 32 bit integer.
     * @param count The number of indexes to read from the index buffer for each instance.
     * @param offset Byte offset within indexBuffer to start reading indexes from.
     * @see `setIndexBuffer(Buffer* buffer)`
     * @see `drawArrays(PrimitiveType primitiveType, unsigned int start,  unsigned int count)`
    */
    virtual void drawElements(PrimitiveType primitiveType, IndexFormat indexType, std::size_t count, std::size_t offset) override;
    
    /**
     * Do some resources release.
     */
    virtual void endRenderPass() override;

    /**
     * Present a drawable and commit a command buffer so it can be executed as soon as possible.
     */
    virtual void endFrame() override;
    
    /**
     * Fixed-function state
     * @param lineWidth Specifies the width of rasterized lines.
     */
    virtual void setLineWidth(float lineWidth) override;
    
    /**
     * Fixed-function state
     * @param x, y Specifies the lower left corner of the scissor box
     * @param wdith Specifies the width of the scissor box
     * @param height Specifies the height of the scissor box
     */
    virtual void setScissorRect(bool isEnabled, float x, float y, float width, float height) override;

    /**
     * Set depthStencil status
     * @param depthStencilState Specifies the depth and stencil status
     */
    virtual void setDepthStencilState(DepthStencilState* depthStencilState) override;

    /**
     * Get a screen snapshot
     * @param callback A callback to deal with screen snapshot image.
     */
    virtual void captureScreen(std::function<void(const unsigned char*, int, int)> callback) override ;

private:
    struct Viewport
    {
        int x = 0;
        int y = 0;
        unsigned int w = 0;
        unsigned int h = 0;
    };
    
    void prepareDrawing() const;
    void bindVertexBuffer(ProgramGL* program) const;
    void setUniforms(ProgramGL* program) const;
    void setUniform(bool isArray, GLuint location, unsigned int size, GLenum uniformType, void* data) const;
    void cleanResources();
    void applyRenderPassDescriptor(const RenderPassDescriptor& descirptor);

    // The frame buffer generated by engine. All frame buffer other than default frame buffer share it.
    GLuint _generatedFBO = 0;
    bool _generatedFBOBindColor = false;
    bool _generatedFBOBindDepth = false;
    bool _generatedFBOBindStencil = false;
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
    bool _framebufferReadWriteDisabled = false;
#endif

    GLint _defaultFBO = 0;  // The value gets from glGetIntegerv, so need to use GLint
    GLuint _currentFBO = 0;
    BufferGL* _vertexBuffer = nullptr;
    ProgramState* _programState = nullptr;
    BufferGL* _indexBuffer = nullptr;
    RenderPipelineGL* _renderPipeline = nullptr;
    CullMode _cullMode = CullMode::NONE;
    DepthStencilStateGL* _depthStencilStateGL = nullptr;
    Viewport _viewPort;
    GLboolean _alphaTestEnabled = false;

#if CC_ENABLE_CACHE_TEXTURE_DATA
    EventListenerCustom* _backToForegroundListener = nullptr;
#endif
};

// end of _opengl group
/// @}
CC_BACKEND_END
