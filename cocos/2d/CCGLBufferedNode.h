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

#include "platform/CCGL.h"

/**
* @js NA
*/
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

    /**@~english
     * Load the given data into this Node's GL Buffer. Needed for WebGL, as it does not support client-side arrays.
     * @~chinese
     * 加载给定数据到该节点的GL缓冲区。WebGL需要调用该接口,因为它不支持客户端数组。
     *
     * @param buf @~english The buffer data object pointer. @~chinese 缓冲区数据对象指针。
     * @param bufSize @~english The buffer size. @~chinese 缓冲区对象的大小。
     * @param slot @~english The slot index. @~chinese 缓冲区对象插槽索引
     */
    void setGLBufferData(void *buf, GLuint bufSize, int slot);

    /**
     *@~english Load the given index data into this Node's GL buffer at the given slot.
     *@~chinese 在给定插槽处，设置给定大小的索引数据缓冲区对象。
     *
     * @param buf @~english The buffer data object pointer. @~chinese 缓冲区数据对象指针。
     * @param bufSize @~english The buffer size. @~chinese 缓冲区对象的大小。
     * @param slot @~english The slot index. @~chinese 缓冲区对象插槽索引。
     */
    void setGLIndexData(void *buf, GLuint bufSize, int slot);

    /** @~english Allocate 4 buffer objs per node, and index into them as slots. @~chinese 每个节点分配4个缓冲区对象,。*/
    #define BUFFER_SLOTS 4
    /**@~english Handle for vertex buffers. @~chinese 缓冲区对象句柄。*/
    GLuint _bufferObject[BUFFER_SLOTS];
    /**@~english Size in bytes for vertex buffers. @~chinese 顶点缓冲区字节大小。*/
    GLuint _bufferSize[BUFFER_SLOTS];
    /**@~english Handle for index buffers. @~chinese 索引缓冲区句柄。*/
    GLuint _indexBufferObject[BUFFER_SLOTS];
    /**@~english Size in bytes for index buffers. @~chinese 索引缓冲区字节大小。*/
    GLuint _indexBufferSize[BUFFER_SLOTS];
};
#endif // __CC_GL_BUFFERED_NODE__
