/****************************************************************************
Copyright (c) 2013      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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
#ifndef __CC_GL_BUFFERED_NODE__
#define __CC_GL_BUFFERED_NODE__

#include "CCGL.h"

class GLBufferedNode
{
public:
    /**
     * @js ctor
     */
    GLBufferedNode();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~GLBufferedNode();

    /**
     * 将传入数据载入当前Node的GL缓存。WebGL因为不支持客户端数组，需要用到此方法。
     */
    void setGLBufferData(void *buf, GLuint bufSize, int slot);
    void setGLIndexData(void *buf, GLuint bufSize, int slot);

    // 给每个Node分配4个缓存对象，并以槽的形式索引管理。
#define BUFFER_SLOTS 4
    GLuint _bufferObject[BUFFER_SLOTS];
    GLuint _bufferSize[BUFFER_SLOTS];

    GLuint _indexBufferObject[BUFFER_SLOTS];
    GLuint _indexBufferSize[BUFFER_SLOTS];
};
#endif // __CC_GL_BUFFERED_NODE__
