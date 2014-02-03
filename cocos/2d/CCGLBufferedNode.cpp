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

#include "CCGLBufferedNode.h"

GLBufferedNode::GLBufferedNode()
{
    for(int i = 0; i < BUFFER_SLOTS; i++)
    {
        _bufferObject[i] = 0;
        _bufferSize[i] = 0;
        _indexBufferObject[i] = 0;
        _indexBufferSize[i] = 0;
    }
}

GLBufferedNode::~GLBufferedNode()
{
    for(int i = 0; i < BUFFER_SLOTS; i++)
    {
        if(_bufferSize[i])
        {
            glDeleteBuffers(1, &(_bufferObject[i]));
        }
        if(_indexBufferSize[i])
        {
            glDeleteBuffers(1, &(_indexBufferObject[i]));
        }
    }
}

void GLBufferedNode::setGLBufferData(void *buf, GLuint bufSize, int slot)
{
    // WebGL doesn't support client-side arrays, so generate a buffer and load the data first.
    if(_bufferSize[slot] < bufSize)
    {
        if(_bufferObject[slot])
        {
            glDeleteBuffers(1, &(_bufferObject[slot]));
        }
        glGenBuffers(1, &(_bufferObject[slot]));
        _bufferSize[slot] = bufSize;

        glBindBuffer(GL_ARRAY_BUFFER, _bufferObject[slot]);
        glBufferData(GL_ARRAY_BUFFER, bufSize, buf, GL_DYNAMIC_DRAW);
    }
    else
    {
        glBindBuffer(GL_ARRAY_BUFFER, _bufferObject[slot]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, bufSize, buf);
    }
}

void GLBufferedNode::setGLIndexData(void *buf, GLuint bufSize, int slot)
{
    // WebGL doesn't support client-side arrays, so generate a buffer and load the data first.
    if(_indexBufferSize[slot] < bufSize)
    {
        if(_indexBufferObject[slot])
        {
            glDeleteBuffers(1, &(_indexBufferObject[slot]));
        }
        glGenBuffers(1, &(_indexBufferObject[slot]));
        _indexBufferSize[slot] = bufSize;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferObject[slot]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufSize, buf, GL_DYNAMIC_DRAW);
    }
    else
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferObject[slot]);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, bufSize, buf);
    }
}

