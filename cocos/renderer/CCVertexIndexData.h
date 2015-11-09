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

/**
 * @addtogroup renderer
 * @{
 */

NS_CC_BEGIN

class VertexBuffer;
/**
@class VertexStreamAttribute
@brief
@~english
VertexStreamAttribute is used to specify the vertex attribute for drawing, which is correspondent to
glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr).

 _semantic  ->  index
 _size      ->  size
 _type      ->  type
 _normalize ->  normalized
 _offset is used to compute the start offset in a interleaved array, take a V3F_C4B_T2F array,
 offset of vertex will be 0, offset of color would be 0 + sizeof(float) * 3 = 12, 
 offset of texture coord would be 12 + sizeof(char) * 4 = 16.
 * @~chinese 
 * VertexStreamAttribute用于指定渲染数据的顶点属性，和函数
 * glVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr)中的
 * 参数对应。
 * 
 * _semantic ->index，
 * _size ->size，
 * _type ->type，
 * _normalize ->normalized，
 * _offset用于计算交叉属性数组的偏移值,以V3F_C4B_T2F数组为例,
 * 顶点属性的偏移是0,颜色属性的偏移是0 + sizeof(float)*3 = 12
 * 纹理坐标属性的偏移是 12 + sizeof(char)*4=16
 @js NA
*/
struct CC_DLL VertexStreamAttribute
{
    /**@~english
     Constructor.
     * @~chinese 
     * 构造函数。
     */
    VertexStreamAttribute()
    : _normalize(false),_offset(0),_semantic(0),_type(0),_size(0)
    {
    }
    /**@~english
     Constructor
     * @~chinese 
     * 构造函数。
     * @param offset @~english The offset of the attribute.
     * @~chinese 属性的偏移
     @param semantic @~english The semantic (Position, Texcoord, Color etc) of attribute.
     * @~chinese 描述属性的语义,如位置、颜色等。
     @param type @~english The type of attribute, could be GL_FLOAT, GL_UNSIGNED_BYTE etc.
     * @~chinese 描述属性的类型,可能是GL_FLOAT,GL_UNSIGNED_BYTE等等。
     @param size @~english Describe how many elements of type in the attribute.
     * @~chinese 属性包含多少个type类型的元素。
     */
    VertexStreamAttribute(int offset, int semantic, int type, int size)
    : _normalize(false),_offset(offset),_semantic(semantic),_type(type),_size(size)
    {
    }
    /**@~english
     Constructor
     * @~chinese 
     * 构造函数。
     @param offset @~english The offset of the attribute.
     * @~chinese 属性的偏移
     @param semantic @~english The semantic (Position, Texcoord, Color etc) of attribute.
     * @~chinese 描述属性的语义,如位置、颜色等。
     @param type @~english The type of attribute, could be GL_FLOAT, GL_UNSIGNED_BYTE etc.
     * @~chinese 描述属性的类型,可能是GL_FLOAT,GL_UNSIGNED_BYTE等等。
     @param size @~english Describe how many elements of type in the attribute.
     * @~chinese 属性包含多少个type类型的元素。
     @param normalize @~english If true, the data will be normalized by deviding 255.
     * @~chinese 如果是真,数据将除以255来归一化。
     */
    VertexStreamAttribute(int offset, int semantic, int type, int size, bool normalize)
    : _normalize(normalize),_offset(offset),_semantic(semantic),_type(type),_size(size)
    {
    }
    /**@~english
     Whether the attribute should be normalized or not.
     * @~chinese 
     * 是否应该规范化属性。
     */
    bool _normalize;
    /**@~english
     The offset of the attribute in the buffer.
     * @~chinese 
     * 属性的偏移。
     */
    int _offset;
    /**@~english
     Describe that the attribute usage, could be Position, Color etc.
     * @~chinese 
     * 描述属性的语义,如位置、颜色等。
     */
    int _semantic;
    /**@~english
     Describe the type of attribute, could be GL_FLOAT, GL_UNSIGNED_BYTE etc.
     * @~chinese 
     * 描述属性的类型,可能是GL_FLOAT,GL_UNSIGNED_BYTE等等。
     */
    int _type;
    /**@~english
     Describe how many elements of type in the attribute.
     * @~chinese 
     * 描述属性包含多少个type类型的元素。
     */
    int _size;
};

/**
@class VertexData
@brief
@~english
VertexData is a class used for specify input streams for GPU rendering pipeline,
a VertexData will be composed by several streams, every stream will contain a VertexStreamAttribute
and the binding VertexBuffer. Streams will be identified by semantic.
 * @~chinese 
 * VertexData类用于指定输入流到GPU渲染管线,
 * VertexData将由几个流组成,每一个输入流包含的属性在VertexStreamAttribute中，数据在绑定的VertexBuffer。
 * 多个流之间用语义标示。
@js NA
*/

class CC_DLL VertexData : public Ref
{
public:
    /**@~english
    Create function, used to create a instance of VertexData.
     * @~chinese 
     * 创建函数,创建一个VertexData实例。
    */
    static VertexData* create();
    
    /**@~english
    Get the number of streams in the VertexData.
     * @~chinese 
     * 得到VertexData流的数量。
    */
    size_t getVertexStreamCount() const;
    /**@~english
    Set a stream to VertexData,given that stream is identified by semantic, so if the semantic is not
    specified before, it will add a stream, or it will override the old one.
     * @~chinese 
     * 设置一个新的流，如果包含的语义之前不存在，就会新建一个输入流，否则会覆盖之前的流
    @param buffer @~english The binding buffer of the stream.
     * @~chinese 流绑定的VertexBuffer
    @param stream @~english The binding vertex attribute, its member semantic will be used as the identifier.
     * @~chinese 流的属性。
    */
    bool setStream(VertexBuffer* buffer, const VertexStreamAttribute& stream);
    /**@~english
    Remove the given streams.
     * @~chinese 
     * 删除给定的输入流。
    @param semantic @~english The semantic of the stream.
     * @~chinese 要删除的流的语义。
    */
    void removeStream(int semantic);
    /**@~english
    Get the attribute of stream, const version.
     * @~chinese 
     * 得到流的属性,const版本。
    @param semantic @~english The semantic of the stream.
     * @~chinese 要得到的流的语义。
    */
    const VertexStreamAttribute* getStreamAttribute(int semantic) const;
    /**@~english
    Get the attribute of stream.
     * @~chinese 
     * 得到流的属性
    @param semantic @~english The semantic of the stream.
     * @~chinese 要得到的流的语义。
    */
    VertexStreamAttribute* getStreamAttribute(int semantic);
    /**@~english
    Get the binded buffer of the stream.
     * @~chinese 
     * 得到流绑定的VertexBuffer。
    @param semantic @~english The semantic of the stream.
     * @~chinese 要得到的流的语义。
    */
    VertexBuffer* getStreamBuffer(int semantic) const;
    
    /**@~english
    Called for rendering, it will bind the state of vertex data to current rendering pipeline.
     * @~chinese 
     * 在绘制时调用,它会将顶点数据的绑定到当前渲染管道。
    */
    void use();
protected:
    /**@~english
    Constructor.
     * @~chinese 
     * 构造函数。
    */
    VertexData();
    /**@~english
    Destructor.
     * @~chinese 
     * 析构函数。
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
/**
 end of support group
 @}
 */
#endif //__CC_VERTEX_INDEX_DATA_H__
