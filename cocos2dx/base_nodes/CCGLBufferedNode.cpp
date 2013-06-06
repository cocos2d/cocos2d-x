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

#include "CCGLBufferedNode.h"

CCGLBufferedNode::CCGLBufferedNode(void)
{
    for(int i = 0; i < BUFFER_SLOTS; i++)
    {
        m_bufferObject[i] = 0;
        m_bufferSize[i] = 0;
        m_indexBufferObject[i] = 0;
        m_indexBufferSize[i] = 0;
    }
}

void CCGLBufferedNode::setGLBufferData(void *buf, GLuint bufSize, int slot)
{
    // WebGL doesn't support client-side arrays, so generate a buffer and load the data first.
    if(m_bufferSize[slot] < bufSize)
    {
        if(m_bufferObject[slot])
        {
            glDeleteBuffers(1, &(m_bufferObject[slot]));
        }
        glGenBuffers(1, &(m_bufferObject[slot]));
        m_bufferSize[slot] = bufSize;

        glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[slot]);
        glBufferData(GL_ARRAY_BUFFER, bufSize, buf, GL_DYNAMIC_DRAW);
    }
    else
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferObject[slot]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, bufSize, buf);
    }
}

void CCGLBufferedNode::setGLIndexData(void *buf, GLuint bufSize, int slot)
{
    // WebGL doesn't support client-side arrays, so generate a buffer and load the data first.
    if(m_indexBufferSize[slot] < bufSize)
    {
        if(m_indexBufferObject[slot])
        {
            glDeleteBuffers(1, &(m_indexBufferObject[slot]));
        }
        glGenBuffers(1, &(m_indexBufferObject[slot]));
        m_indexBufferSize[slot] = bufSize;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject[slot]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufSize, buf, GL_DYNAMIC_DRAW);
    }
    else
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject[slot]);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, bufSize, buf);
    }
}

