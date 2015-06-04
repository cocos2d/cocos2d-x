/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#ifndef __CCMESHVERTEXINDEXDATA_H__
#define __CCMESHVERTEXINDEXDATA_H__

#include <string>
#include <vector>

#include "3d/CCBundle3DData.h"
#include "3d/CCAABB.h"

#include "base/CCRef.h"
#include "base/CCVector.h"
#include "math/CCMath.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCVertexIndexData.h"
#include "renderer/CCVertexIndexBuffer.h"


NS_CC_BEGIN

/**
 * @addtogroup _3d
 * @{
 */

class MeshVertexData;

/**
 * @~english The MeshIndexData class.
 * @class MeshIndexData
 * @brief @~english the MeshIndexData contain all of the indices data which mesh need.
 * @~chinese MeshIndexData包含了所有Mesh对象所需的索引信息
 * @js NA
 * @lua NA
 */
class MeshIndexData : public Ref
{
public:
    /**
     * @~english Create MeshIndexData object form the specified name, vertices, indices and AABB.
     * @~chinese 通过指定的名称，顶点数组，索引数组和AABB来创建的MeshIndexData对象
     * @param id @~english The MeshIndexData object name.
     * @~chinese 给定的名称
     * @param vertexData @~english The MeshIndexData object's vertices.
     * @~chinese 顶点数组
     * @param indexbuffer @~english The MeshIndexData object's indices.
     * @~chinese 索引数组
     * @param aabb @~english The MeshIndexData object's aabb.
     * @~chinese AABB对象
     * @return @~english The MeshIndexData object.
     * @~chinese 被创建的AABB对象
     */
    static MeshIndexData* create(const std::string& id, MeshVertexData* vertexData, IndexBuffer* indexbuffer, const AABB& aabb);
    
    /**
     * @~english Get index buffer.
     * @~chinese 获取索引缓冲
     * @return @~english The IndexBuffer object.
     * @~chinese IndexBuffer对象
     */
    const IndexBuffer* getIndexBuffer() const { return _indexBuffer; }

    /**
     * @~english Get vertex buffer.
     * @~chinese 获取顶点缓冲
     * @return @~english The VertexBuffer object.
     * @~chinese VertexBuffer对象
     */
    const VertexBuffer* getVertexBuffer() const;
    
    /**
     * @~english Get vertex data.
     * @~chinese 获取顶点数据
     * @return @~english The MeshVertexData object.
     * @~chinese MehsVertexData对象
     */
    const MeshVertexData* getMeshVertexData() const { return _vertexData; }
    
    /**
     * @~english Set MeshIndexData's AABB
     * @~chinese 设置AABB包围盒
     * @param aabb @~english New AABB object.
     * @~chinese 新AABB包围盒对象
     */
    void setAABB(const AABB& aabb) { _aabb = aabb; }

    /**
     * @~english Get MeshIndexData's AABB
     * @~chinese 获取AABB包围盒
     * @return aabb @~english The AABB object.
     * @~chinese AABB包围盒对象
     */
    const AABB& getAABB() const { return _aabb; }
    
    /** 
     * @~english Set the MeshIndexData object's ID.
     * @~chinese 设置该MeshIndexData的ID字符串
     * @param id @~english The new ID.
     * @~chinese 新ID字符串
     */
    void setId(const std::string& id) { _id = id; }

    /**
     * @~english Get the MeshIndexData object's ID.
     * @~chinese 获取该MeshIndexData对象的ID字符串
     * @return @~english The MeshIndexData object's ID.
     * @~chinese ID字符串
     */
    const std::string& getId() const { return _id; }
    
    /**
     * @~english Get the MeshIndexData object's primitive type.
     * @~chinese 获取该MeshIndexData对象的基本几何体类型
     * @return @~english The primitive type.
     * @~chinese 基本几何体类型
     */
    GLenum getPrimitiveType() const { return _primitiveType; }

    /**
     * @~english Set the MeshIndexData object's primitive type.
     * @~chinese 设置MeshIndexData对象的基本几何体类型
     * @param primitive @~english The new primitive type.
     * @~chinese 新类型
     */
    void   setPrimitiveType(GLenum primitive) { _primitiveType = primitive; }
    
CC_CONSTRUCTOR_ACCESS:
    MeshIndexData();
    virtual ~MeshIndexData();
    
protected:
    IndexBuffer*    _indexBuffer; //index buffer
    MeshVertexData* _vertexData; //vertex buffer, weak ref
    AABB           _aabb; // original aabb of the submesh
    std::string    _id; //id
    GLenum         _primitiveType;
    
    friend class MeshVertexData;
    friend class Sprite3D;
};

/**
 * @~english The MeshVertexData class.
 * @~chinese MeshVertexData 类
 * @brief @~english The MeshIndexData contain all of the vertices data which mesh need.
 * @~chinese MeshVertexData包括了所有网格所需的顶点数据
 */
class MeshVertexData : public Ref
{
    friend class Sprite3D;
    friend class Mesh;
public:
    /**
     * @~english Create MeshVertexData by specified MeshData object.
     * @~chinese 通过指定的MeshData对象创建
     * @param meshdata @~english The MeshData object.
     * @~chinese 指定的MeshData对象
     * @return @~english The MeshVertexData object.
     * @~chinese 被创建的MeshVertexData对象
     */
    static MeshVertexData* create(const MeshData& meshdata);
    
    /** 
     * @~english Get vertex buffer.
     * @~chinese 获取顶点缓冲对象
     * @return @~english The VertexBuffer object.
     * @~chinese VertexBuffer对象
     */
    const VertexBuffer* getVertexBuffer() const { return _vertexBuffer; }
    
    /**
     * @~english Get attributes count.
     * @~chinese 获取顶点属性总数
     * @return @~english The attributes count.
     * @~chinese 顶点属性数
     */
    ssize_t getMeshVertexAttribCount() const { return _attribs.size(); }
    
    /**
     * @~english Get attribute by index.
     * @~chinese 通过指定的索引获取定点索引
     * @param index @~english The specified index.
     * @~chinese 指定的索引
     * @return @~english The MeshVertexAttrib object.
     * @~chinese The MeshVertexAttrib 对象.
     */
    const MeshVertexAttrib& getMeshVertexAttrib(ssize_t index) const { return _attribs[index]; }
    
    /** 
     * @~english Get index data count.
     * @~chinese 获取索引数据数组的大小.
     * @return @~english The Indices array's size.
     * @~chinese 索引数据数组的大小
     */
    ssize_t getMeshIndexDataCount() const { return _indexs.size(); }
    /** 
     * @~english Get index data by index.
     * @~chinese 获取通过给定的索引获取索引数据
     * @param index @~english The specfied index.
     * @~chinese 指定的索引
     * @return @~english TheMeshIndexData object.
     * @~chinese MeshIndexData对象.
     */
    MeshIndexData* getMeshIndexDataByIndex(int index) const { return _indexs.at(index); }
    /**
     * @~english Get index data by ID string.
     * @~chinese 通过ID字符串获取指定的 索引数据.
     * @param id @~english The string ID.
     * @~chinese 字符串ID
     * @return @~english The MeshIndexData object.
     * @~chinese MeshIndexData对象
     */
    MeshIndexData* getMeshIndexDataById(const std::string& id) const;
    
    /**
     * @~english Check MeshVertexData whether has the specified vertex attribute.
     * @~chinese 检查该对象是否含有指定的顶点属性
     * @param attrib @~english The specified attribute index.
     * @~chinese 指定的顶点属性的索引
     * @return @~english Return true if the MeshVertexData object have this attribute, otherwise return false.
     * @~chinese 若包含返回true，反之返回false
     */
    bool hasVertexAttrib(int attrib) const;
    
CC_CONSTRUCTOR_ACCESS:
    MeshVertexData();
    virtual ~MeshVertexData();

protected:
    VertexData*          _vertexData; //mesh vertex data
    VertexBuffer*        _vertexBuffer; // vertex buffer
    Vector<MeshIndexData*> _indexs; //index data
    std::vector<MeshVertexAttrib> _attribs; //vertex attributes
    
    int                  _vertexCount; //vertex count
};

// end of 3d group
/// @}

NS_CC_END

#endif // __CCMESHVERTEXINDEXDATA_H__
