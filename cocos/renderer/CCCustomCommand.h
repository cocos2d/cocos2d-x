/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include "renderer/CCRenderCommand.h"

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN

namespace backend
{
    class Buffer;
}

/**
Custom command is used for call custom openGL command which can not be done by other commands,
such as stencil function, depth functions etc. The render command is executed by calling a call back function.
*/
class CC_DLL CustomCommand : public RenderCommand
{
public:
    
    enum class DrawType
    {
        ARRAY,
        ELEMENT
    };
    
    using PrimitiveType = backend::PrimitiveType;
        
	/**Constructor.*/
    CustomCommand();
    /**Destructor.*/
    virtual ~CustomCommand();
    
    CustomCommand& operator=(const CustomCommand& rhs);
    
public:
	/**
	Init function.
	@param globalZOrder GlobalZOrder of the render command.
	@param modelViewTransform When in 3D mode, depth sorting needs modelViewTransform.
	@param flags Use to identify that the render command is 3D mode or not.
	*/
    void init(float globalZOrder, const Mat4& modelViewTransform, uint32_t flags);
    /**
    Init function. The render command will be in 2D mode.
    @param globalZOrder GlobalZOrder of the render command.
    */
    void init(float globalZOrder);
    
    void createVertexBuffer(size_t sizePerVertex, size_t count);
    void createIndexBuffer(size_t sizePerIndex, size_t count);

    void updateVertexBuffer(void* data, size_t length);
    void updateIndexBuffer(void* data, size_t length);
    void updateVertexBuffer(void* data, size_t offset, size_t length);
    void updateIndexBuffer(void* data, size_t offset, size_t length);
    void updateVertexBuffer(void* data, size_t offset, size_t count, size_t sizePerCount);
    void updateIndexBuffer(void* data, size_t offset, size_t count, size_t sizePerCount);
    
    inline void setDrawType(DrawType drawType) { _drawType = drawType; }
    inline DrawType getDrawType() const { return _drawType; }
    inline void setPrimitiveType(PrimitiveType primitiveType) { _primitiveType = primitiveType; }
    inline PrimitiveType getPrimitiveType() const { return _primitiveType; }
    
    inline backend::Buffer* getVertexBuffer() const { assert(_vertexBuffer); return _vertexBuffer; }
    inline backend::Buffer* getIndexBuffer() const { assert(_indexBuffer); return _indexBuffer; }
    inline size_t getIndexCount() const { return _indexCount; }
    inline size_t getVertexCount() const { return _vertexCount; }
    
    inline void setVertexDrawInfo(size_t vertexStart, size_t count) { _vertexStart = vertexStart; _vertexDrawCount = count; }
    inline size_t getVertexDrawStart() const { return _vertexStart; }
    inline size_t getVertexDrawCount() const { return _vertexDrawCount == 0 ? _vertexCount : _vertexDrawCount; }
    
    inline void setIndexDrawInfo(size_t indexBufferOffset, size_t count) { _indexBufferOffset = indexBufferOffset; _indexDrawCount = count; }
    inline size_t getIndexDrawBufferOffset() const { return _indexBufferOffset; }
    inline size_t getIndexDrawCount() const { return _indexDrawCount == 0 ? _indexCount : _indexDrawCount; }
    
    inline void setLineWidth(float lineWidth) { _lineWidth = lineWidth; }
    inline float getLineWidth() const { return _lineWidth; }

    /**Callback function.*/
    //TODO:minggo: should remove it.
    std::function<void()> func;

protected:
    backend::Buffer* _vertexBuffer = nullptr;
    backend::Buffer* _indexBuffer = nullptr;
    size_t _indexCount = 0;
    size_t _vertexCount = 0;
    
    size_t _vertexStart = 0;
    size_t _vertexDrawCount = 0;
    
    size_t _indexBufferOffset = 0;
    size_t _indexDrawCount = 0;

    size_t _perVertexSize = 0;
    size_t _perIndexSize = 0;
    
    DrawType _drawType = DrawType::ELEMENT;
    PrimitiveType _primitiveType = PrimitiveType::TRIANGLE;
    
    float _lineWidth = 0.0;
};

NS_CC_END
/**
 end of support group
 @}
 */
