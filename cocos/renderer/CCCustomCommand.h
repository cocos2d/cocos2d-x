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
    using BufferUsage = backend::BufferUsage;
    using IndexFormat = backend::IndexFormat;
        
	/**Constructor.*/
    CustomCommand();
    /**Destructor.*/
    virtual ~CustomCommand();
    
public:
	/**
	Init function.
	@param globalZOrder GlobalZOrder of the render command.
	@param modelViewTransform When in 3D mode, depth sorting needs modelViewTransform.
	@param flags Use to identify that the render command is 3D mode or not.
	*/
    void init(float globalZOrder, const Mat4& modelViewTransform, unsigned int flags);
    
    /**
    Init function. The render command will be in 2D mode.
    @param globalZOrder GlobalZOrder of the render command.
    */
    void init(float globalZOrder);
    void init(float globalZOrder, const BlendFunc& blendFunc);
    
    void createVertexBuffer(unsigned int vertexSize, unsigned int capacity, BufferUsage usage);
    void createIndexBuffer(IndexFormat format, unsigned int capacity, BufferUsage usage);

    void updateVertexBuffer(void* data, unsigned int length);
    void updateIndexBuffer(void* data, unsigned int length);
    void updateVertexBuffer(void* data, unsigned int offset, unsigned int length);
    void updateIndexBuffer(void* data, unsigned int offset, unsigned int length);

    inline unsigned int getVertexCapacity() const { return _vertexCapacity; }
    inline unsigned int getIndexCapacity() const { return _indexCapacity; }
    
    inline void setDrawType(DrawType drawType) { _drawType = drawType; }
    inline DrawType getDrawType() const { return _drawType; }

    inline void setPrimitiveType(PrimitiveType primitiveType) { _primitiveType = primitiveType; }
    inline PrimitiveType getPrimitiveType() const { return _primitiveType; }

    void setVertexBuffer(backend::Buffer* vertexBuffer);
    inline backend::Buffer* getVertexBuffer() const { assert(_vertexBuffer); return _vertexBuffer; }

    void setIndexBuffer(backend::Buffer* indexBuffer, IndexFormat indexFormat);
    inline backend::Buffer* getIndexBuffer() const { assert(_indexBuffer); return _indexBuffer; }

    inline void setVertexDrawInfo(unsigned int start, unsigned int count) { _vertexDrawStart = start; _vertexDrawCount = count; }
    inline unsigned int getVertexDrawStart() const { return _vertexDrawStart; }
    inline unsigned int getVertexDrawCount() const { return _vertexDrawCount;}
    
    inline void setIndexDrawInfo(unsigned int start, unsigned int count) { _indexDrawOffset = start * _indexSize; _indexDrawCount = count; }
    inline unsigned int getIndexDrawOffset() const { return _indexDrawOffset; }
    inline unsigned int getIndexDrawCount() const { return _indexDrawCount; }
    
    inline void setLineWidth(float lineWidth) { _lineWidth = lineWidth; }
    inline float getLineWidth() const { return _lineWidth; }

    inline IndexFormat getIndexFormat() const { return _indexFormat; }
    
    void clear();

    /**Callback function.*/
    //TODO:minggo: should remove it.
    std::function<void()> func;

protected:
    unsigned int computeIndexSize() const;

    backend::Buffer* _vertexBuffer = nullptr;
    backend::Buffer* _indexBuffer = nullptr;
    
    unsigned int _vertexDrawStart = 0;
    unsigned int _vertexDrawCount = 0;
    
    unsigned int _indexDrawOffset = 0;
    unsigned int _indexDrawCount = 0;
    
    DrawType _drawType = DrawType::ELEMENT;
    PrimitiveType _primitiveType = PrimitiveType::TRIANGLE;
    IndexFormat _indexFormat = IndexFormat::U_SHORT;
    
    float _lineWidth = 0.0;
    
    unsigned int _indexSize = 0;

    unsigned int _vertexCapacity = 0;
    unsigned int _indexCapacity = 0;
};

NS_CC_END
/**
 end of support group
 @}
 */
