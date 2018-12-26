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
    void init(float globalZOrder, const Mat4& modelViewTransform, unsigned int flags);
    
    /**
    Init function. The render command will be in 2D mode.
    @param globalZOrder GlobalZOrder of the render command.
    */
    void init(float globalZOrder);
    void init(float globalZOrder, const BlendFunc& blendFunc);
    
    void createVertexBuffer(unsigned int sizePerVertex, unsigned int count);
    void createIndexBuffer(unsigned int sizePerIndex, unsigned int count);

    void updateVertexBuffer(void* data, unsigned int length);
    void updateIndexBuffer(void* data, unsigned int length);
    void updateVertexBuffer(void* data, unsigned int offset, unsigned int length);
    void updateIndexBuffer(void* data, unsigned int offset, unsigned int length);
    
    inline void setDrawType(DrawType drawType) { _drawType = drawType; }
    inline DrawType getDrawType() const { return _drawType; }
    inline void setPrimitiveType(PrimitiveType primitiveType) { _primitiveType = primitiveType; }
    inline PrimitiveType getPrimitiveType() const { return _primitiveType; }
    
    inline backend::Buffer* getVertexBuffer() const { assert(_vertexBuffer); return _vertexBuffer; }
    inline backend::Buffer* getIndexBuffer() const { assert(_indexBuffer); return _indexBuffer; }
    inline unsigned int getIndexCount() const { return _indexCount; }
    inline unsigned int getVertexCount() const { return _vertexCount; }
    
    inline void setVertexDrawInfo(unsigned int vertexStart, unsigned int count) { _vertexStart = vertexStart; _vertexDrawCount = count; }
    inline unsigned int getVertexDrawStart() const { return _vertexStart; }
    inline unsigned int getVertexDrawCount() const { return _vertexDrawCount == 0 ? _vertexCount : _vertexDrawCount; }
    
    inline void setIndexDrawInfo(unsigned int indexBufferOffset, unsigned int count) { _indexBufferOffset = indexBufferOffset; _indexDrawCount = count; }
    inline unsigned int getIndexDrawBufferOffset() const { return _indexBufferOffset; }
    inline unsigned int getIndexDrawCount() const { return _indexDrawCount == 0 ? _indexCount : _indexDrawCount; }
    
    inline void setLineWidth(float lineWidth) { _lineWidth = lineWidth; }
    inline float getLineWidth() const { return _lineWidth; }

    /**Callback function.*/
    //TODO:minggo: should remove it.
    std::function<void()> func;

protected:
    backend::Buffer* _vertexBuffer = nullptr;
    backend::Buffer* _indexBuffer = nullptr;
    unsigned int _indexCount = 0;
    unsigned int _vertexCount = 0;
    
    unsigned int _vertexStart = 0;
    unsigned int _vertexDrawCount = 0;
    
    unsigned int _indexBufferOffset = 0;
    unsigned int _indexDrawCount = 0;
    
    DrawType _drawType = DrawType::ELEMENT;
    PrimitiveType _primitiveType = PrimitiveType::TRIANGLE;
    
    float _lineWidth = 0.0;
    
    unsigned int _sizePerVertex = 0;
    unsigned int _sizePerIndex = 0;
};

NS_CC_END
/**
 end of support group
 @}
 */
