/****************************************************************************
 Copyright (c) 2014-2017 Chukong Technologies Inc.

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
 * the MeshIndexData class.
 * @brief the MeshIndexData contain all of the indices data which mesh need.
 * @js NA
 * @lua NA
 */
class CC_DLL MeshIndexData : public Ref
{
public:
    /** create  */
    static MeshIndexData* create(const std::string& id, MeshVertexData* vertexData, IndexBuffer* indexbuffer, const AABB& aabb);
    
    /**get index buffer*/
    const IndexBuffer* getIndexBuffer() const { return _indexBuffer; }
    /**get vertex buffer*/
    const VertexBuffer* getVertexBuffer() const;
    
    /**get vertex data*/
    const MeshVertexData* getMeshVertexData() const { return _vertexData; }
    
    /** aabb getter and setter */
    void setAABB(const AABB& aabb) { _aabb = aabb; }
    const AABB& getAABB() const { return _aabb; }
    
    /** id setter and getter */
    void setId(const std::string& id) { _id = id; }
    const std::string& getId() const { return _id; }
    
    /**primitive type setter & getter*/
    GLenum getPrimitiveType() const { return _primitiveType; }
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
 * the MeshVertexData class.
 * @brief the MeshIndexData contain all of the vertices data which mesh need.
 */
class CC_DLL MeshVertexData : public Ref
{
    friend class Sprite3D;
    friend class Mesh;
public:
    /**create*/
    static MeshVertexData* create(const MeshData& meshdata);
    
    /** get vertexbuffer */
    const VertexBuffer* getVertexBuffer() const { return _vertexBuffer; }
    
    /** get attributes count */
    ssize_t getMeshVertexAttribCount() const { return _attribs.size(); }
    
    /** get attribute by index */
    const MeshVertexAttrib& getMeshVertexAttrib(ssize_t index) const { return _attribs[index]; }
    
    /** get index data count */
    ssize_t getMeshIndexDataCount() const { return _indexs.size(); }
    /** get index data by index */
    MeshIndexData* getMeshIndexDataByIndex(int index) const { return _indexs.at(index); }
    /** get index data by id */
    MeshIndexData* getMeshIndexDataById(const std::string& id) const;
    
    /**has vertex attribute?*/
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
