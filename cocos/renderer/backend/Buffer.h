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

class Buffer : public cocos2d::Ref
{
public:
    virtual void updateData(void* data, unsigned int size) = 0;
    virtual void updateSubData(void* data, unsigned int offset, unsigned int size) = 0;

    /*
     * By default, static buffer data will automatically stored when it comes to foreground.
     * This function is used to indicate whether external data needs to be used to update the buffer instead of using the default stored data.
     */
    virtual void usingDefaultStoredData(bool needDefaultStoredData) = 0;

    unsigned int getSize() const { return _size; }

protected:
    Buffer(unsigned int size, BufferType type, BufferUsage usage)
    : _usage(usage)
    , _type(type)
    , _size(size)
    {}
    
    virtual ~Buffer() = default;
    
    BufferUsage _usage = BufferUsage::DYNAMIC;
    BufferType _type = BufferType::VERTEX;
    unsigned int _size = 0;
};

CC_BACKEND_END
