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

#include <vector>
#include "../Macros.h"

CC_BACKEND_BEGIN

class BufferMTL;

/**
 * @addtogroup _metal
 * @{
 */

/**
 * @brief A static class to manage BufferMTL
 * Schedule next available buffer at the beginning of frame for the render pass
 */
class BufferManager
{
public:
    /**
     * Add a buffer object into container.
     * @param buffer Specifies the buffer to be added.
     */
    static void addBuffer(BufferMTL* buffer);
    
    /**
     * Remove a buffer object from container.
     * @param buffer Specifies the buffer to be removed.
     */
    static void removeBuffer(BufferMTL* buffer);
    
    /**
     * Schedule next available buffer at the beginning of frame for the following render passes.
     */
    static void beginFrame();

private:
    static std::vector<BufferMTL*> _buffers;
};

// end of _metal group
/// @}
CC_BACKEND_END
