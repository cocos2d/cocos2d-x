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

#ifndef __CC_BUNDLE_3D_DATA_H__
#define __CC_BUNDLE_3D_DATA_H__

#include "base/CCRef.h"
#include "base/ccTypes.h"
#include "math/CCMath.h"
#include "3d/CCAABB.h"

#include <vector>
#include <map>
 
NS_CC_BEGIN

/**
 * @~english mesh vertex attribute
 * @~chinese 网格的顶点属性
 * @struct MeshVertexAttrib
 * @js NA
 * @lua NA
 */

struct MeshVertexAttrib
{
    /**
    * @~english The attribute size.
    * @~chinese 属性数
    */
    GLint size;
    /**
    * @~english Attribute's data type, currently must be GL_FLOAT.
    * @~chinese 属性的数据类型，当前必须为GL_FLOAT型
    */
    GLenum type;
    /**
     * @~english The attribute type, the attribute type must be one of the following:
     * VERTEX_ATTRIB_POSITION,VERTEX_ATTRIB_COLOR,VERTEX_ATTRIB_TEX_COORD,VERTEX_ATTRIB_NORMAL, VERTEX_ATTRIB_BLEND_WEIGHT, VERTEX_ATTRIB_BLEND_INDEX
     * @~chinese 属性类型，属性类型必须为下列中的类型之一：
     * VERTEX_ATTRIB_POSITION,VERTEX_ATTRIB_COLOR,VERTEX_ATTRIB_TEX_COORD,VERTEX_ATTRIB_NORMAL, VERTEX_ATTRIB_BLEND_WEIGHT, VERTEX_ATTRIB_BLEND_INDEX
     * @note @~english see GLProgram for detail
     * @~chinese 详细内容请参看GLProgram类
     **/
    int  vertexAttrib;
    /**
     * @~english The attribute size in bytes.
     * @~chinese 属性尺寸，以字节计
     */
    int attribSizeBytes;
};


/** Model node data, since 3.3.
* @struct ModelData
* @js NA
* @lua NA
*/
struct ModelData
{
    /** The sub mesh ID*/
    std::string subMeshId;
    /**The material ID.*/
    std::string matrialId;
    /**The bone list.*/
    std::vector<std::string> bones;
    /**The inverse bind pose matrix list.*/
    std::vector<Mat4>        invBindPose;
    
    /**
     * Destructor.
     **/
    virtual ~ModelData()
    {
        resetData();
    }

    /**
     * Reset the data of the ModelData object.
     **/
    virtual void resetData()
    {
        bones.clear();
        invBindPose.clear();
    }
};

/** Node data, since 3.3 
* @struct NodeData
* @js NA
* @lua NA
*/
struct NodeData
{
    /**The NodeData ID.*/
    std::string id;
    /**The NodeData transform.*/
    Mat4        transform;
    /**The Model data list.*/
    std::vector<ModelData*> modelNodeDatas;
    /**The children list.*/
    std::vector<NodeData*>  children;

    /**
     *Destructor.
     */
    virtual ~NodeData()
    {
        resetData();
    }

    /**
     * @~english Reset Data, will reset itself and children's data.
     */
    virtual void resetData()
    {
        id.clear();
        transform.setIdentity();
        for (auto& it : children)
        {
            delete it;
        }
        children.clear();
        
        for(auto& modeldata : modelNodeDatas)
        {
            delete modeldata;
        }
        modelNodeDatas.clear();
    }

};

/** 
 * @~english node datas, since 3.3 
 * @struct NodeDatas
 * @js NA
 * @lua NA
 */
struct NodeDatas
{
    /**
     * @~english The skeleton list.
     * @~chinese 骨骼列表
     **/
    std::vector<NodeData*> skeleton; //skeleton
    /**
     * @~english The NodeData list.
     * @~chinese NodeData(节点数据)列表
     */
    std::vector<NodeData*> nodes; // nodes, CCNode, Sprite3D or part of Sprite3D

    /**
    *Destructor.
    */
    virtual ~NodeDatas()
    {
        resetData();
    }
    
    /**
     * @~english Reset data.
     * @~chinese 重置数据
     */
    void resetData()
    {
        for(auto& it : skeleton)
        {
            delete it;
        }
        skeleton.clear();
        for(auto& it : nodes)
        {
            delete it;
        }
        nodes.clear();
    }
};

/**
 * @~english Mesh data
 * @~chinese 网格数据
 * @struct MeshData
 * @js NA
 * @lua NA
 */
struct MeshData
{
    typedef std::vector<unsigned short> IndexArray;
    /**
     * @~english The vertices list.
     * @~chinese 顶点数组
     */
    std::vector<float> vertex;
    /**
     * @~english The vertex size in float data type.
     * 顶点大小，以float数据类型计
     */
    int vertexSizeInFloat;
    /**
     * @~english Sub meshes' indices list.
     * @~chinese 子网格索引数组
     */
    std::vector<IndexArray> subMeshIndices;
    /**
     * @~english Sub meshes' ID list.
     * @~chinese 子网格ID数组
     */
    std::vector<std::string> subMeshIds; //subMesh Names (since 3.3)
    /**
     * @~english Sub meshes' AABB list.
     * @~chinese 子网格的AABB数组
     */
    std::vector<AABB> subMeshAABB;
    /**
     * @~english The Size of indices List.
     * 索引数组的大小
     */
    int numIndex;
    /**
     * @~english The vertex attribute lists.
     * @~chinese 顶点属性数组
     */
    std::vector<MeshVertexAttrib> attribs;
    /**
     * @~english The amount of the attributes.
     * @~chinese 顶点属性的个数
     */
    int attribCount;

public:
    /**
     * @~english Get per vertex size
     * @~chinese 获取每一个顶点的大小
     * @return return the sum of each vertex's all attribute size.
     * @~chinese 返回每个顶点所有属性大小之和
     */
    int getPerVertexSize() const
    {
        int vertexsize = 0;
        for(const auto& attrib : attribs)
        {
            vertexsize += attrib.attribSizeBytes;
        }
        return vertexsize;
    }

    /**
     * @~english Reset the data
     * @~chinese 重设数据
     */
    void resetData()
    {
        vertex.clear();
        subMeshIndices.clear();
        subMeshAABB.clear();
        attribs.clear();
        vertexSizeInFloat = 0;
        numIndex = 0;
        attribCount = 0;
    }
    /**
    * Constructor.
    */
    MeshData()
    : vertexSizeInFloat(0)
    , numIndex(0)
    , attribCount(0)
    {
    }
    /**
    * Destructor.
    */
    ~MeshData()
    {
        resetData();
    }
};

/** 
 * @~english mesh datas 
 * @~chinese 网格数据集合
 * @struct MeshDatas
 * @js NA
 * @lua NA
 */
struct MeshDatas
{
    /**
     * @~english The MeshData list
     * @~chinese 网格数据数组
     */
    std::vector<MeshData*> meshDatas;
    /**
     * @~english Reset data.
     * @~chinese 重设数据
     **/
    void resetData()
    {
        for(auto& it : meshDatas)
        {
            delete it;
        }
        meshDatas.clear();
    }
    /**
     * Destructor
     **/
    ~MeshDatas()
    {
        resetData();
    }
};

/**
 * @~english skin data
 * @~chinese 蒙皮数据
 * @struct SkinData
 * @js NA
 * @lua NA
 */
struct SkinData
{
    /**
     * @~english The skin bones list which affect skin.
     * @~chinese 影响蒙皮的骨骼数组
     */
    std::vector<std::string> skinBoneNames; 
    /**
     * @~english Node bones don't affect skin, all bones [skinBone, nodeBone].
     * @~chinese 不影响蒙皮的骨骼与影响蒙皮的骨骼（所有骨骼）数组
     */
    std::vector<std::string> nodeBoneNames; 
    /**
     * @~english Bind pose of skin bone, only for skin bone.
     * @~chinese 骨骼的蒙皮绑定姿态的逆变换矩阵数组，只有影响蒙皮的骨骼才与之对应
     */
    std::vector<Mat4>        inverseBindPoseMatrices; 
    /**
     * @~english Original bone transform, for skin bone.
     * @~chinese 骨骼的初始变换矩阵数组，只有影响蒙皮的骨骼才与之对应
     */
    std::vector<Mat4>        skinBoneOriginMatrices;
    /**
     * @~english Original bone transform, for node bone.
     * @~chinese 节点骨骼的初始变换矩阵数组
     */
    std::vector<Mat4>        nodeBoneOriginMatrices; 
    
    /**
     * @~english Bone child info[key parent, value child], both skinbone and node bone.
     * @~chinese 骨骼的子节点信息集合，存储数据为一个pair，主键为其父节点，值为子节点；蒙皮骨骼与节点骨骼都与之对应
     */
    std::map<int, std::vector<int> > boneChild;
    /**
     * @~english The root bone index.
     * @~chinese 根节点骨骼的索引
     */
    int                              rootBoneIndex;
    /**
     * @~english Reset data.
     * @~chinese 重设数据 
     */
    void resetData()
    {
        skinBoneNames.clear();
        nodeBoneNames.clear();
        inverseBindPoseMatrices.clear();
        skinBoneOriginMatrices.clear();
        nodeBoneOriginMatrices.clear();
        boneChild.clear();
        rootBoneIndex = -1;
    }

    /**
     * @~english Add name for SkinBone.
     * @~chinese 为蒙皮骨骼添加名称
     * @param name @~english The SkinBone name.
     * @~chinese 蒙皮骨骼的名称
     */
    void addSkinBoneNames(const std::string& name)
    {
        auto it = std::find(skinBoneNames.begin(), skinBoneNames.end(), name);
        if (it == skinBoneNames.end())
            skinBoneNames.push_back(name);
    }
    
    /**
     * @~english Add name for NodeBone.
     * @~chinese 为节点骨骼添加名称
     * @param name @~english the NodeBone name.
     * @~chinese 节点骨骼的名称
     */
    void addNodeBoneNames(const std::string& name)
    {
        auto it = std::find(nodeBoneNames.begin(), nodeBoneNames.end(), name);
        if (it == nodeBoneNames.end())
            nodeBoneNames.push_back(name);
    }
    
    /**
     * @~english Get the index of the specified SkinBone name.
     * @~chinese 通过给定的蒙皮骨骼的名称获取其索引
     * @param name @~english The specified name.
     * @~chinese 给定的蒙皮骨骼的名称
     * @return @~english The index.
     * @~chinese 蒙皮骨骼的索引
     */
    int getSkinBoneNameIndex(const std::string& name)const
    {
        int i = 0;
        for (const auto& iter : skinBoneNames)
        {
            if ((iter) == name)
                return i;
            i++;
        }
        return -1;
    }
    
    /**
     * @~english Get the index of the specified Bone name(skinBone & nodeBone both).
     * @~chinese 通过给定的名称返回骨骼的索引，（蒙皮骨骼与节点骨骼皆可）
     * @param name @~english The specified name.
     * @~chinese 指定的名称
     * @return @~english The index.
     * @~chinese 骨骼的索引
     */
    int getBoneNameIndex(const std::string& name)const
    {
        int i = 0;
        for (const auto& iter : skinBoneNames)
        {
            if ((iter) == name)
                return i;
            i++;
        }
        for(const auto& iter : nodeBoneNames)
        {
            if (iter == name)
                return i;
            i++;
        }
        return -1;
    }

};

/**
 * @~english material data
 * @~chinese 材质数据
 * @struct MaterialData
 * @js NA
 * @lua NA
 */
struct MaterialData
{
    std::map<int, std::string> texturePaths; //submesh id, texture path
    void resetData()
    {
        texturePaths.clear();
    }
};


/**
 * new material, since 3.3 
 * @js NA
 * @lua NA
 */
struct NTextureData
{
    enum class Usage {
        Unknown = 0,
        None = 1,
        Diffuse = 2, 
        Emissive = 3,
        Ambient = 4,
        Specular = 5,
        Shininess = 6,
        Normal = 7,
        Bump = 8,
        Transparency = 9,
        Reflection = 10
    };
     std::string id;
     std::string filename;
     Usage type;
     GLenum wrapS;
     GLenum wrapT;
} ;
struct NMaterialData
{
    std::vector<NTextureData> textures;
    std::string id;
    const NTextureData* getTextureData(const NTextureData::Usage& type) const
    {
        for(const auto& it : textures)
        {
            if (it.type == type)
                return &it;
        }
        return nullptr;
    }
};
/** material datas, since 3.3 
* @js NA
* @lua NA
*/
struct MaterialDatas
{
    std::vector<NMaterialData> materials;
    void resetData()
    {
        materials.clear();
    }
    const NMaterialData* getMaterialData(const std::string& materialid) const
    {
        for(const auto& it : materials)
        {
            if (it.id == materialid)
                return &it;
        }
        return nullptr;
    }
};
/**animation data
* @js NA
* @lua NA
*/
struct Animation3DData
{
public:
    struct Vec3Key
    {
        Vec3Key()
        : _time(0)
        {
        }
        
        Vec3Key(float time, const Vec3& v)
        : _time(time)
        , _key(v)
        {
        }
        
        float _time;
        Vec3 _key;
    };
    
    struct QuatKey
    {
        QuatKey()
        : _time(0)
        , _key(Quaternion::identity())
        {
        }
        
        QuatKey(float time, const Quaternion& quat)
        : _time(time)
        , _key(quat)
        {
        }
        
        float _time;
        Quaternion _key;
    };

public:
    std::map<std::string, std::vector<Vec3Key>> _translationKeys;
    std::map<std::string, std::vector<QuatKey>> _rotationKeys;
    std::map<std::string, std::vector<Vec3Key>> _scaleKeys;
    
    float _totalTime;

public:
    Animation3DData()
    :_totalTime(0)
    {
    }
    
    Animation3DData(const Animation3DData& other)
    : _translationKeys(other._translationKeys)
    , _rotationKeys(other._rotationKeys)
    , _scaleKeys(other._scaleKeys)
    , _totalTime(other._totalTime)
    {
    }
    
    void resetData()
    {
        _totalTime = 0;
        _translationKeys.clear();
        _rotationKeys.clear();
        _scaleKeys.clear();
    }
};

/**reference data
* @js NA
* @lua NA
*/
struct Reference
{
public:
    std::string id;
    unsigned int type;
    unsigned int offset;

    Reference(){}

    ~Reference(){}
};

NS_CC_END

#endif //__CC_BUNDLE_3D_DATA_H__
