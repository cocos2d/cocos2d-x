/****************************************************************************
Copyright (c) 2013      Zynga Inc.

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

#include <GLES2/gl2.h>

class CCGLBufferedNode
{
public:
    CCGLBufferedNode(void);

    /**
     * Load the given data into this CCNode's GL Buffer. Needed for WebGL, as it does not support client-side arrays.
     */
    void setGLBufferData(void *buf, GLuint bufSize, int slot);
    void setGLIndexData(void *buf, GLuint bufSize, int slot);

    // We allocate 4 buffer objs per node, and index into them as slots.
#define BUFFER_SLOTS 4
    GLuint m_bufferObject[BUFFER_SLOTS];
    GLuint m_bufferSize[BUFFER_SLOTS];

    GLuint m_indexBufferObject[BUFFER_SLOTS];
    GLuint m_indexBufferSize[BUFFER_SLOTS];
};
#endif // __CC_GL_BUFFERED_NODE__
