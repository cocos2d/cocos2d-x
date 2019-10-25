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
Custom command is used to draw all things except triangle commands. You can use
this command to draw things, just provide vertex/index data and set corret flags.
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
    /**
    Buffer usage of vertex/index buffer. If the contents is not updated every frame,
    then use STATIC, other use DYNAMIC.
    */
    using BufferUsage = backend::BufferUsage;
    /**
    The index format determine the size for index data. U_SHORT is enough for most
    cases.
    */
    using IndexFormat = backend::IndexFormat;


    typedef std::function<void()> CallBackFunc;

	/**Constructor.*/
    CustomCommand();
    /**Destructor.*/
    ~CustomCommand();
    

public:
	/**
    TODO: should remove it.
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
    /**
    Init function. The render command will be in 2D mode.
    @param globalZOrder GlobalZOrder of the render command.
    @param blendFunc blend function of the render command.
    */
    void init(float globalZOrder, const BlendFunc& blendFunc);

    /**
    Create a vertex buffer of the custom command. The buffer size is (vertexSize * capacity).
    If the buffer already exists, then it will delete the old buffer and create a new one.
    @param vertexSize the size of every vertex data.
    @param capacity how many vertices of the buffer
    @param usage the usage of the vertex buffer. Use Static of the vertex data are not updated
                 every frame, otherwise use DYNAMIC.
    */
    void createVertexBuffer(std::size_t vertexSize, std::size_t capacity, BufferUsage usage);
    /**
    Create an index buffer of the custom command. The buffer size is (indexSize * capacity).
    Index size is determined by format. If the buffer already exists, then it will delete the
    old buffer and create a new one.
    @param format index fomrat, if format is U_SHORT, then the index data type should be
                  unsigned short, otherwise should be unsigned int.
    @param capacity how many indices of the buffer
    @param usage the usage of the vertex buffer. Use Static of the index data are not updated
                 every frame, otherwise use DYNAMIC.
    */
    void createIndexBuffer(IndexFormat format, std::size_t capacity, BufferUsage usage);

    /**
    Update vertex buffer contents.
    @param data Specifies a pointer to the new data that will be copied into the data store.
    @param length Specifies the length in bytes of the data store region being replaced.
    */
    void updateVertexBuffer(void* data, std::size_t length);
    /**
    Update index buffer contents.
    @param data Specifies a pointer to the new data that will be copied into the data store.
    @param length Specifies the size in bytes of the data store region being replaced.
    */
    void updateIndexBuffer(void* data, std::size_t length);
    /**
    Update some or all contents of vertex buffer.
    @param data Specifies a pointer to the new data that will be copied into the data store.
    @param offset Specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes.
    @param length Specifies the size in bytes of the data store region being replaced.
    */
    void updateVertexBuffer(void* data, std::size_t offset, std::size_t length);
    /**
    Update some or call contents of index buffer
    @param data Specifies a pointer to the new data that will be copied into the data store.
    @param offset specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes.
    @param length Specifies the size in bytes of the data store region being replaced.
    */
    void updateIndexBuffer(void* data, std::size_t offset, std::size_t length);

    /**
    Get vertex buffer capacity.
    */
    inline std::size_t getVertexCapacity() const { return _vertexCapacity; }
    /**
    Get index buffer capacity.
    */
    inline std::size_t getIndexCapacity() const { return _indexCapacity; }

    inline void setDrawType(DrawType drawType) { _drawType = drawType; }
    inline DrawType getDrawType() const { return _drawType; }

    inline void setPrimitiveType(PrimitiveType primitiveType) { _primitiveType = primitiveType; }
    inline PrimitiveType getPrimitiveType() const { return _primitiveType; }

    /**
    Set the vertex buffer. The existing vertex buffer will be replaced if exist.
    */
    void setVertexBuffer(backend::Buffer* vertexBuffer);
    inline backend::Buffer* getVertexBuffer() const { return _vertexBuffer; }

    /**
    Set the index buffer. The existing index buffer will be replaced if exist.
    */
    void setIndexBuffer(backend::Buffer* indexBuffer, IndexFormat indexFormat);
    inline backend::Buffer* getIndexBuffer() const { return _indexBuffer; }

    /**
    Set the drawing information if the drawing type is ARRAY.
    @start specifices the starting index of vertex buffer
    @count specifices the number of vertices to be rendered
    */
    inline void setVertexDrawInfo(std::size_t start, std::size_t count) { _vertexDrawStart = start; _vertexDrawCount = count; }
    inline std::size_t getVertexDrawStart() const { return _vertexDrawStart; }
    inline std::size_t getVertexDrawCount() const { return _vertexDrawCount;}

    /**
    Set the drawing information if the drawing type is ELEMENT.
    @start specifices the starting index of index buffer
    @count specifices the number of indices to be rendered
    */
    inline void setIndexDrawInfo(std::size_t start, std::size_t count) { _indexDrawOffset = start * _indexSize; _indexDrawCount = count; }
    inline std::size_t getIndexDrawOffset() const { return _indexDrawOffset; }
    inline std::size_t getIndexDrawCount() const { return _indexDrawCount; }
    
    inline void setLineWidth(float lineWidth) { _lineWidth = lineWidth; }
    inline float getLineWidth() const { return _lineWidth; }

    inline IndexFormat getIndexFormat() const { return _indexFormat; }

    /**Callback function.*/
    //TODO:minggo: should remove it.
    std::function<void()> func;

    /**
    * set a callback which will be invoke before rendering
    */
    void setBeforeCallback(const CallBackFunc &before) { _beforeCallback = before; }

    /**
    * set a callback which will be invoke after rendering
    */
    void setAfterCallback(const CallBackFunc &after) { _afterCallback = after; }

    const CallBackFunc &getBeforeCallback() { return _beforeCallback; }

    const CallBackFunc &getAfterCallback() { return _afterCallback; }

protected:
    std::size_t computeIndexSize() const;

    backend::Buffer* _vertexBuffer = nullptr;
    backend::Buffer* _indexBuffer = nullptr;
    
    std::size_t _vertexDrawStart = 0;
    std::size_t _vertexDrawCount = 0;
    
    std::size_t _indexDrawOffset = 0;
    std::size_t _indexDrawCount = 0;
    
    DrawType _drawType = DrawType::ELEMENT;
    PrimitiveType _primitiveType = PrimitiveType::TRIANGLE;
    IndexFormat _indexFormat = IndexFormat::U_SHORT;
    
    float _lineWidth = 0.0;
    
    std::size_t _indexSize = 0;

    std::size_t _vertexCapacity = 0;
    std::size_t _indexCapacity = 0;


    CallBackFunc _beforeCallback = nullptr;
    CallBackFunc _afterCallback = nullptr;
};

NS_CC_END
/**
 end of support group
 @}
 */
