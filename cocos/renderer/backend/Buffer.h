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

#include "Macros.h"
#include "Types.h"
#include "base/CCRef.h"

namespace cocos2d {
    class MeshVertexData;
    class MeshIndexData;
}

CC_BACKEND_BEGIN

/**
 * @addtogroup _backend
 * @{
 */

/**
 * @brief Used to store vertex and index data data.
 */
class Buffer : public cocos2d::Ref
{
public:
    /**
     * @brief Update buffer data
     * @param data Specifies a pointer to data that will be copied into the data store for initialization.
     * @param size Specifies the size in bytes of the data store region being replaced.
     * @see `updateSubData(void* data, unsigned int offset, unsigned int size)`
     */
    virtual void updateData(void* data, std::size_t size) = 0;
    
    /**
     * @brief Update buffer sub-region data
     * @param data Specifies a pointer to the new data that will be copied into the data store.
     * @param offset Specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes.
     * @param size Specifies the size in bytes of the data store region being replaced.
     * @see `updateData(void* data, unsigned int size)`
     */
    virtual void updateSubData(void* data, std::size_t offset, std::size_t size) = 0;

    /**
     * By default, static buffer data will automatically stored when it comes to foreground.
     * This function is used to indicate whether external data needs to be used to update the buffer instead of using the default stored data.
     * @param needDefaultStoredData Specifies whether to use the default stored data.
     */
    virtual void usingDefaultStoredData(bool needDefaultStoredData) = 0;

    /**
     * Get buffer size in bytes.
     * @return The buffer size in bytes.
     */
    std::size_t getSize() const { return _size; }

protected:
    /**
     * @param size Specifies the size in bytes of the buffer object's new data store.
     * @param type Specifies the target buffer object. The symbolic constant must be BufferType::VERTEX or BufferType::INDEX.
     * @param usage Specifies the expected usage pattern of the data store. The symbolic constant must be GL_STREAM_DRAW, GL_STATIC_DRAW, or GL_DYNAMIC_DRAW.
     */
    Buffer(std::size_t size, BufferType type, BufferUsage usage)
    : _usage(usage)
    , _type(type)
    , _size(size)
    {}
    
    virtual ~Buffer() = default;
    
    BufferUsage _usage = BufferUsage::DYNAMIC; ///< Buffer usage.
    BufferType _type = BufferType::VERTEX; ///< Buffer type.
    std::size_t _size = 0; ///< buffer size in bytes.
};

// end of _backend group
/// @}
CC_BACKEND_END
