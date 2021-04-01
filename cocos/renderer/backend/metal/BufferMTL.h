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

#include "../Buffer.h"
#import <Metal/Metal.h>

CC_BACKEND_BEGIN

/**
 * @addtogroup _metal
 * @{
 */

/**
 * @brief Used to store vertex and index data data.
 * Dynamic buffer data refers to frequently updated data stored in a buffer.
 * To avoid creating new buffers per frame and to minimize processor idle time between frames, implement a triple buffering model to update dynamic buffer.
 */
class BufferMTL : public Buffer
{
public:
    /// @name Constructor, Destructor and Initializers
    /**
     * @brief BufferMTL constructor
     * @param mtlDevice The device for which MTLBuffer object was created.
     * @param size Specifies the size in bytes of the buffer object's new data store.
     * @param type Specifies the target buffer object. The symbolic constant must be BufferType::VERTEX or BufferType::INDEX.
     * @param usage Specifies the expected usage pattern of the data store. The symbolic constant must be BufferUsage::STATIC, BufferUsage::DYNAMIC.
     */
    BufferMTL(id<MTLDevice> mtlDevice, std::size_t size, BufferType type, BufferUsage usage);
    ~BufferMTL();
    
    /// @name Update Buffer
    /**
     * @brief Update buffer data
     * @param data Specifies a pointer to data that will be copied into the data store for initialization.
     * @param size Specifies the size in bytes of the data store region being replaced.
     * @see `updateSubData(void* data, unsigned int offset, unsigned int size)`
     */
    virtual void updateData(void* data, std::size_t size) override;
    
    /**
     * @brief Update buffer sub-region data
     * @param data Specifies a pointer to the new data that will be copied into the data store.
     * @param offset Specifies the offset into the buffer object's data store where data replacement will begin, measured in bytes.
     * @param size Specifies the size in bytes of the data store region being replaced.
     * @see `updateData(void* data, unsigned int size)`
     */
    virtual void updateSubData(void* data, std::size_t offset, std::size_t size) override;
    
    /**
     * Emply implementation. Mainly used in EGL context lost.
     */
    virtual void usingDefaultStoredData(bool needDefaultStoredData) override {};
    
    /// @name Setters & Getters
    id<MTLBuffer> getMTLBuffer() const;
    
    /**
     * @brief a triple buffering
     * Will switch to next buffer and use the buffer in the following render pass in current frame.
     */
    void beginFrame();
    
private:
    void updateIndex();

    id<MTLBuffer> _mtlBuffer = nil;
    NSMutableArray* _dynamicDataBuffers = nil;
    int _currentFrameIndex = 0;
    bool _indexUpdated = false;
};

// end of _metal group
/// @}
CC_BACKEND_END
