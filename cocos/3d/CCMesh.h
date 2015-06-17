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

#ifndef __CCMESH_H__
#define __CCMESH_H__

#include <string>

#include "3d/CCBundle3DData.h"
#include "3d/CCAABB.h"

#include "base/CCRef.h"
#include "math/CCMath.h"
#include "renderer/CCMeshCommand.h"

NS_CC_BEGIN

/**
 * @addtogroup _3d
 * @{
 */

class Texture2D;
class MeshSkin;
class MeshIndexData;
class GLProgramState;
class GLProgram;
class Material;
class Renderer;
class Scene;
class Pass;

/** 
 * @class Mesh
 * @brief @~english Mesh: contains ref to index buffer, GLProgramState, texture, skin, blend function, aabb and so on
 * @~chinese Mesh：用于存储网格中的索引缓存，Gl渲染状态，纹理，蒙皮，片段混合方程以及AABB等数据.
 */
class CC_DLL Mesh : public Ref
{
    friend class Sprite3D;
public:
    /**
     * @~english The indices array
     * @~chinese 顶点索引数组
     */
    typedef std::vector<unsigned short> IndexArray;
    /**
     * @~english Create mesh from positions, normals, and so on, single SubMesh
     * @~chinese 通过位置，法线及其他参数来创建一个单独的子网格
     * @param positions @~english The positions list.
     * @~chinese 位置数组
     * @param normals @~english The normals list.
     * @~chinese 法线数组
     * @param texs @~english The texture UV corodinates list.
     * @~chinese 纹理的UV坐标数组
     * @param indices @~english The indices list
     * @~chinese 顶点索引数组
     * @return @~english The Mesh object.
     * @~chinese 被创建的Mesh对象
     */
    static Mesh* create(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texs, const IndexArray& indices);
    /**create mesh with vertex attributes*/
    CC_DEPRECATED_ATTRIBUTE static Mesh* create(const std::vector<float>& vertices, int perVertexSizeInFloat, const IndexArray& indices, int numIndex, const std::vector<MeshVertexAttrib>& attribs, int attribCount){ return create(vertices, perVertexSizeInFloat, indices, attribs); }
    
    /**
     * @~english Create mesh from vertices, indices and attribs
     * @~chinese 通过顶点数组，索引数组以及顶点属性来创建网格
     * @param vertices @~english the vertices list.
     * @~chinese 顶点数组
     * @param perVertexSizeInFloat @~english Each vertex element's size.
     * @~chinese 每个顶点元素的大小
     * @param indices @~english The indices list.
     * @~chinese 索引数组
     * @param attribs @~english The mesh vertices attributes list.
     * @~chinese 顶点属性数组
     * @return @~english The Mesh object.
     * @~chinese 被创建的网格
     * @lua NA
     */
    static Mesh* create(const std::vector<float>& vertices, int perVertexSizeInFloat, const IndexArray& indices, const std::vector<MeshVertexAttrib>& attribs);
    
    /** 
     *@~english  Create mesh from name, mesh index data and skin
     * @~chinese 通过名称，MeshIndexData对象以及蒙皮来创建Mesh对象
     * @param name @~english The name.
     * @~chinese 名称
     * @param indexData @~english The indexData list.
     * @~chinese 索引数据列表
     * @param skin @~english The MeshSkin object.
     * @~chinese 网格蒙皮信息
     * @return @~english The Mesh object.
     * @~chinese 被创建的网格
     * @lua NA
     */
    static Mesh* create(const std::string& name, MeshIndexData* indexData, MeshSkin* skin = nullptr);
    
    /**
     * @~english Get the vertex buffer.
     * @~chinese 获取顶点缓冲
     * @return @~english The VBO ID.
     * @~chinese 顶点缓冲的句柄ID
     * @lua NA
     */
    GLuint getVertexBuffer() const;
    /**
     * @~english Check if the mesh have specified vertex attribute or not
     * @~chinese 检查网格是否拥有指定的顶点属性
     * @param attrib @~english The attribute type ID.
     * @~chinese 顶点属性ID
     * @return @~english Return true if the mesh have specified attribute, otherwise return false.
     * @~chinese 当该网格包含指定顶点属性时返回true，反之返回false
     * @lua NA
     */
    bool hasVertexAttrib(int attrib) const;
    /**
     * @~english Get the mesh vertex attribute count.
     * @~chinese 返回该网格包含的顶点属性的数量
     * @return @~english The vertex attribute count.
     * @~chinese 顶点属性的数量
     */
    ssize_t getMeshVertexAttribCount() const;
    /**
     * @~english Get MeshVertexAttribute by index
     * @~chinese 通过所索引获取网格的顶点属性
     * @param idx @~english The index.
     * @~chinese 顶点属性索引
     * @return @~english The MeshVertexAttribute object.
     * @~chinese MeshVertexAttribute 对象
     **/
    const MeshVertexAttrib& getMeshVertexAttribute(int idx);
    /**
     * @~english Get per vertex size in bytes.
     * @~chinese 获取每一个顶点的数据大小，以字节计
     * @return @~english The per vertex size in bytes.
     * @~chinese 每个顶点的数据大小
     */
    int getVertexSizeInBytes() const;

    /** 
     * @~english Texture setter.
     * @~chinese 设置网格纹理
     * @param texPath @~english The texture file path.
     * @~chinese 纹理文件的路径
     */
    void setTexture(const std::string& texPath);

    /**
     * @~english Texture setter.
     * @~chinese 设置网格纹理
     * @param tex @~english The Texture2D object.
     * @~chinese Texture2D 对象
     */
    void setTexture(Texture2D* tex);

    /**
     * @~english Texture getter.
     * @~chinese 获取纹理
     * @return @~english The Texture2D object.
     * @~chinese Texture2D 对象
     */
    Texture2D* getTexture() const;
    
    /**
     * @~english Visible setter
     * @~chinese 设置可见性
     * @param visible @~english The visiblity
     * @~chinese 可见性
     */
    void setVisible(bool visible);

    /**
     * Visible getter.
     * @~chinese 获取可见性
     * @return the visiblity of the mesh.
     * @~chinese 可见性
     */
    bool isVisible() const;
    
    /**
     * @~english The skin getter.
     * @~chinese 获取蒙皮信息
     * @return @~english The MeshSkin Object.
     * @~chinese MeshSkin 对象
     * @lua NA
     */
    MeshSkin* getSkin() const { return _skin; }
    
    /**
     * @~english Mesh index data getter.
     * @~chinese 获取网格索引数据
     * @return @~english The MeshIndexData object.
     * @~chinese MeshIndexData 对象
     * @lua NA
     */
    MeshIndexData* getMeshIndexData() const { return _meshIndexData; }
    
    /**
     * @~english Get GLProgramState.
     * @~chinese 获得GL shader状态
     * @return @~english The GLProgramState object.
     * @~chinese GLProgramState 对象
     * @lua NA
     */
    GLProgramState* getGLProgramState() const;
    
    /**
     * @~english Get the mesh's name.
     * @~chinese 获取网格名称
     * @return @~english The mesh's name.
     * @~chinese 网格名称
     */
    const std::string& getName() const { return _name; }
    
    /**
     * @~english Set the blending function.
     * @~chinese 设置片段混合函数
     * @param blendFunc @~english The specified blending function.
     * @~chinese 给定的混合函数
     */
    void setBlendFunc(const BlendFunc &blendFunc);

    /**
     * @~english Get the mesh's blending function.
     * @~chinese 获取片段混合函数
     * @return The blending function.
     * @~chinese 混合函数
     */
    const BlendFunc &getBlendFunc() const;
    
    /** 
     * @~english Get primitive type.
     * @~chinese 获取基本几何体类型，所谓基本几何体类型，即网格以何种方式按照其索引组织绘制
     * @return @~english The primitive type.
     * @~chinese 基本几何体类型
     * @lua NA
     */
    GLenum getPrimitiveType() const;
    /**
     * @~english Get index count
     * @~chinese 获取索引数量
     * @return @~english The index count of the mesh.
     * @~chinese网格的索引数量
     * @lua NA
     */
    ssize_t getIndexCount() const;
    /**
     * @~english Get the mesh's index data format.
     * @~chinese 获取网格的索引数据类型
     * @return @~english The index data format, should be GL_UNSIGNED_SHORT.
     * @~chinese 网格的索引数据类型，通常为 GL_UNSIGNED_SHORT类型
     * @lua NA
     */
    GLenum getIndexFormat() const;
    /**
     * @~english Get the mesh's index buffer object(IBO) handle.
     * @~chinese 获取网格的顶点缓冲对象(IBO)的GL句柄
     * @return @~english The IBO handle.
     * @~chinese 顶点缓冲对象(IBO)的GL句柄
     * @lua NA
     */
    GLuint getIndexBuffer() const;
    
    /**
     * @~english Get the mesh's AABB in local space.
     * @~chinese 获取网格的局部坐标系下的AABB
     * @return @~english The AABB object.
     * @~chinese AABB对象
     */
    const AABB& getAABB() const { return _aabb; }

    /**  
     * @~english Sets a new GLProgramState for the Mesh
     * @~chinese 为网格设置新的GLProgrameState对象
     * @param glProgramState @~english The new GLProgramState object.
     * @~chinese 新GLProgrameState对象
     * @note @~english A new Material will be created for it
     * @~chinese 新的材质将会被创建
     */
    void setGLProgramState(GLProgramState* glProgramState);

    /**
     * @~english Sets a new Material to the Mesh 
     * @~chinese 给网格设置新材质
     * @param material @~english The new Material object.
     * @~chinese 新材质
     */
    void setMaterial(Material* material);

    /**
     * @~english Get the Material which being used by the Mesh 
     * @~chinese 获取当前Mesh所使用的材质
     * @return @~english The material object. @~chinese 材质对象
     */
    Material* getMaterial() const;

    void draw(Renderer* renderer, float globalZ, const Mat4& transform, uint32_t flags, unsigned int lightMask, const Vec4& color, bool forceDepthWrite);

    /** 
     * @~english Get the MeshCommand.
     * @~chinese 获取MeshCommand
     * @return @~english The MeshCommand object
     * @~chinese MeshCommand 对象
     */
    MeshCommand& getMeshCommand() { return _meshCommand; }

    /**
     * @~english Set a specified skin to mesh.
     * @~chinese 给网格设置指定的蒙皮信息
     * @param skin @~english The specified skin object.
     * @~chinese 指定的MeshSkin对象
     */
    void setSkin(MeshSkin* skin);
    /**
     * @~english Set the mesh index data.
     * @~chinese 设置网格的索引数据
     * @param indexdata @~english The specified MeshIndexData.
     * @~chinese 指定的MeshIndexData对象
     */
    void setMeshIndexData(MeshIndexData* indexdata);

    /**
     * @~english Set the mesh's name.
     * @~chinese 设置网格的名称
     * @param name @~english The mesh's new name.
     * @~chinese 网格的新名称
     */
    void setName(const std::string& name) { _name = name; }
 
    /** 
     * @~english Calculate the AABB of the mesh.
     * @~chinese 计算网格的AABB
     * @note @~english The AABB is in the local space, not the world space
     * @~chinese 该AABB是在网格的局部坐标系下，而非世界坐标系下
     */
    void calculateAABB();
    

CC_CONSTRUCTOR_ACCESS:

    Mesh();
    virtual ~Mesh();

protected:
    void setLightUniforms(Pass* pass, Scene* scene, const Vec4& color, unsigned int lightmask);
    void bindMeshCommand();

    Texture2D*          _texture;  //texture that submesh is using
    MeshSkin*           _skin;     //skin
    bool                _visible; // is the submesh visible
    bool                _isTransparent; // is this mesh transparent, it is a property of material in fact
    
    std::string         _name;
    MeshCommand         _meshCommand;
    MeshIndexData*      _meshIndexData;
    GLProgramState*     _glProgramState;
    BlendFunc           _blend;
    bool                _blendDirty;
    Material*           _material;
    AABB                _aabb;
    std::function<void()> _visibleChanged;
};

// end of 3d group
/// @}


NS_CC_END

#endif // __CCMESH_H__
