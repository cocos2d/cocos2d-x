/****************************************************************************
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

#ifndef __CC_VERTEX_INDEX_BUFFER_H__
#define __CC_VERTEX_INDEX_BUFFER_H__

#include <vector>
#include "base/CCRef.h"
#include "platform/CCGL.h"

NS_CC_BEGIN

class EventListenerCustom;

class CC_DLL VertexBuffer : public Ref
{
public:
    static VertexBuffer* create(int sizePerVertex, int vertexNumber);
    
    int getSizePerVertex() const;
    int getVertexNumber() const;
    bool updateVertices(const void* verts, int count, int begin);

    int getSize() const;
    
    GLuint getVBO() const;
    
protected:
    VertexBuffer();
    virtual ~VertexBuffer();
    
    bool init(int sizePerVertex, int vertexNumber);
protected:
    //event listener for foreground
    void recreateVBO() const;
    EventListenerCustom* _recreateVBOEventListener;
protected:
    mutable GLuint _vbo;
    int _sizePerVertex;
    int _vertexNumber;
    //buffer used for shadow copy
    std::vector<unsigned char> _shadowCopy;
protected:
    static bool _enableShadowCopy;
public:
    static bool isShadowCopyEnabled() { return _enableShadowCopy; }
    static void enableShadowCopy(bool enabled) { _enableShadowCopy = enabled; }
};

class CC_DLL IndexBuffer : public Ref
{
public:
    enum class IndexType
    {
        INDEX_TYPE_SHORT_16,
        INDEX_TYPE_UINT_32
    };
    
public:
    static IndexBuffer* create(IndexType type, int number);
    
    IndexType getType() const;
    int getSizePerIndex() const;
    int getIndexNumber() const;
    bool updateIndices(const void* indices, int count, int begin);

    int getSize() const;
    
    GLuint getVBO() const;

protected:
    IndexBuffer();
    virtual ~IndexBuffer();
    
    bool init(IndexType type, int number);
    
protected:
    mutable GLuint _vbo;
    IndexType _type;
    int _indexNumber;
    
protected:
    //event listener for foreground
    void recreateVBO() const;
    EventListenerCustom* _recreateVBOEventListener;
    //buffer used for shadow copy
    std::vector<unsigned char> _shadowCopy;
protected:
    static bool _enableShadowCopy;
public:
    static bool isShadowCopyEnabled() { return _enableShadowCopy; }
    static void enableShadowCopy(bool enabled) { _enableShadowCopy = enabled; }
};


NS_CC_END

#endif /* __CC_VERTEX_INDEX_BUFFER_H__*/
