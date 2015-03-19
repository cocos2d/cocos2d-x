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

#ifndef __CC_VERTEX_INDEX_DATA_H__
#define __CC_VERTEX_INDEX_DATA_H__

#include "base/CCRef.h"
#include <map>

NS_CC_BEGIN

class VertexBuffer;
/**
VertexStreamAttribute is used to specify the vertex attribute for drawing, which is correspondent to
glVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr).

 _semantic  ->  index
 _size      ->  size
 _type      ->  type
 _normalize ->  normalized
 _offset is used to compute the start offset in a interleaved array, take a V3F_C4B_T2F array,
 offset of vertex will be 0, offset of color would be 0 + sizeof(float) * 3 = 12, 
 offset of texture coord would be 12 + sizeof(char) * 4 = 16.
 @js NA
*/
struct CC_DLL VertexStreamAttribute
{
    /**
     Constructor.
     */
    VertexStreamAttribute()
    : _normalize(false),_offset(0),_semantic(0),_type(0),_size(0)
    {
    }
    /**
     Constructor
     @param offset The offset of the attribute.
     @param semantic The semantic (Position, Texcoord, Color etc) of attribute.
     @param type The type of attribute, could be GL_FLOAT, GL_UNSIGNED_BYTE etc.
     @param size Describe how many elements of type in the attribute.
     */
    VertexStreamAttribute(int offset, int semantic, int type, int size)
    : _normalize(false),_offset(offset),_semantic(semantic),_type(type),_size(size)
    {
    }
    /**
     Constructor
     @param offset The offset of the attribute.
     @param semantic The semantic (Position, Texcoord, Color etc) of attribute.
     @param type The type of attribute, could be GL_FLOAT, GL_UNSIGNED_BYTE etc.
     @param size Describe how many elements of type in the attribute.
     @param normalize If true, the data will be normalized by deviding 255.
     */
    VertexStreamAttribute(int offset, int semantic, int type, int size, bool normalize)
    : _normalize(normalize),_offset(offset),_semantic(semantic),_type(type),_size(size)
    {
    }
    /**
     Whether the attribute should be normalized or not.
     */
    bool _normalize;
    /**
     The offset of the attribute in the buffer.
     */
    int _offset;
    /**
     Describe that the attribute usage, could be Position, Color etc.
     */
    int _semantic;
    /**
     Describe the type of attribute, could be GL_FLOAT, GL_UNSIGNED_BYTE etc.
     */
    int _type;
    /**
     Describe how many elements of type in the attribute.
     */
    int _size;
};

/**
VertexData is a class used for specify input streams for GPU rendering pipeline,
a VertexData will be composed by several streams, every stream will contain a VertexStreamAttribute
and the binding VertexBuffer. Streams will be identified by semantic.
@js NA
*/

class CC_DLL VertexData : public Ref
{
public:
    /**
    Create function, used to create a instance of VertexData.
    */
    static VertexData* create();
    
    /**
    Get the number of streams in the VertexData.
    */
    size_t getVertexStreamCount() const;
    /**
    Set a stream to VertexData,given that stream is identified by semantic, so if the semantic is not
    specified before, it will add a stream, or it will override the old one.
    @param buffer The binding buffer of the stream.
    @param stream The binding vertex attribute, its member semantic will be used as the identifier.
    */
    bool setStream(VertexBuffer* buffer, const VertexStreamAttribute& stream);
    /**
    Remove the given streams.
    @param semantic The semantic of the stream.
    */
    void removeStream(int semantic);
    /**
    Get the attribute of stream, const version.
    @param semantic The semantic of the stream.
    */
    const VertexStreamAttribute* getStreamAttribute(int semantic) const;
    /**
    Get the attribute of stream.
    @param semantic The semantic of the stream.
    */
    VertexStreamAttribute* getStreamAttribute(int semantic);
    /**
    Get the binded buffer of the stream.
    @param semantic The semantic of the stream.
    */
    VertexBuffer* getStreamBuffer(int semantic) const;
    
    /**
    Called for rendering, it will bind the state of vertex data to current rendering pipeline.
    */
    void use();
protected:
    /**
    Constructor.
    */
    VertexData();
    /**
    Destructor.
    */
    virtual ~VertexData();
protected:
    /**
    Simple struct to bundle buffer and attribute.
    */
    struct BufferAttribute
    {
        VertexBuffer* _buffer;
        VertexStreamAttribute _stream;
    };
    
    /**
    Streams in the VertexData.
    */
    std::map<int, BufferAttribute> _vertexStreams;
};

NS_CC_END

#endif //__CC_VERTEX_INDEX_DATA_H__
