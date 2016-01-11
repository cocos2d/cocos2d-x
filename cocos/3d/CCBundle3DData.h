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


/** @~english Model node data, since 3.3.
 * @~chinese 模型数据
* @struct ModelData
* @js NA
* @lua NA
*/
struct ModelData
{
    /** @~english The sub mesh ID @~chinese 子mesh id*/
    std::string subMeshId;
    /** @~english The material ID. @~chinese 材质ID*/
    std::string matrialId;
    /** @~english The bone list. @~chinese 骨骼列表*/
    std::vector<std::string> bones;
    /** @~english The inverse bind pose matrix list. @~chinese 绑定姿态逆矩阵列表*/
    std::vector<Mat4>        invBindPose;
    
    /**
     * @~english Destructor. @~chinese 析构函数
     **/
    virtual ~ModelData()
    {
        resetData();
    }

    /**
     * @~english Reset the data of the ModelData object. @~chinese 重置模型数据
     **/
    virtual void resetData()
    {
        bones.clear();
        invBindPose.clear();
    }
};

/** @~english Node data, since 3.3 @~chinese节点数据
* @struct NodeData
* @js NA
* @lua NA
*/
struct NodeData
{
    /**@~english The NodeData ID. @~chinese 节点数据ID*/
    std::string id;
    /** @~english The NodeData transform. @~chinese节点变换矩阵*/
    Mat4        transform;
    /**@~english The Model data list. @~chinese模型数据列表*/
    std::vector<ModelData*> modelNodeDatas;
    /** @~english The children list. @~chinese 孩子列表*/
    std::vector<NodeData*>  children;

    /**
     *@~english Destructor. @~chinese析构函数
     */
    virtual ~NodeData()
    {
        resetData();
    }

    /**
     * @~english Reset Data, will reset itself and children's data. @~chinese 重置节点数据，孩子节点数据也将被重置
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
 * @~english node datas, since 3.3 @~chinese 节点数据集
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
    *@~english Destructor. @~chinese析构函数
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
    * @~english Constructor. @~chinese 析构函数
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
 * @~english new Texture data, since 3.3 @~chinese 新的纹理数据
 * @js NA
 * @lua NA
 */
struct NTextureData
{
    /**
     * @~english Usage of texture @~chinese 纹理的用途
     */
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
    /** @~english texture id @~chinese 纹理ID */
     std::string id;
    /** @~english texture file name. @~chinese 纹理文件名 */
     std::string filename;
    /**@~english usage of texture @~chinese 纹理用途 */
     Usage type;
    /** @~english texture wrap mode @~chinese 纹理Wrap的方式*/
     GLenum wrapS;
    /** @~english texture wrap mode @~chinese 纹理Wrap的方式 */
     GLenum wrapT;
} ;

/**
 * @~english new material data @~chinese 新的材质数据
 */
struct NMaterialData
{
    /** @~english textures list. @~chinese 纹理列表 */
    std::vector<NTextureData> textures;
    /** @~english Material ID. @~chinese 材质ID */
    std::string id;
    /** @~english Get texture data by given usage @~chinese 获取给定用途的纹理数据 
     * @param type @~english Uage type. @~chinese 用途
     * @return @~english Texture data of given usage. @~chinese 给定用途的纹理数据
     */
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
/** @~english material datas, since 3.3 @~chinese 材质数据集合
* @js NA
* @lua NA
*/
struct MaterialDatas
{
    /** @~english material list @~chinese 材质列表 */
    std::vector<NMaterialData> materials;
    /** @~english reset data. @~chinese 重置材质数据 */
    void resetData()
    {
        materials.clear();
    }
    /** @~english Get material data by id. @~chinese 通过ID获取材质数据
     * @param materialid @~english Material ID. @~chinese材质ID
     * @return @~english Material data with given material ID. @~chinese给定材质ID的材质数据
     */
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
/** @~english animation data @~chinese 动画数据
* @js NA
* @lua NA
*/
struct Animation3DData
{
public:
    /** @~english key frame for vec3. Used internally. @~chinese vec3的关键帧数据，内部使用*/
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
    /** @~english key frame for Quaternion. Used internally. @~chinese 四元数的关键帧数据，内部使用*/
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
    /** @~english translation key frame. @~chinese 平移关键帧数据*/
    std::map<std::string, std::vector<Vec3Key>> _translationKeys;
    /** @~english rotation key frame. @~chinese 旋转关键帧数据*/
    std::map<std::string, std::vector<QuatKey>> _rotationKeys;
    /** @~english scale key frame. @~chinese 缩放关键帧数据*/
    std::map<std::string, std::vector<Vec3Key>> _scaleKeys;
    
    /** @~english total time of animation data. @~chinese 动画数据的时间长度*/
    float _totalTime;

public:
    /** @~english Constructor. @~chinese 构造函数*/
    Animation3DData()
    :_totalTime(0)
    {
    }
    /** @~english Copy constructor. @~chinese 拷贝构造函数*/
    Animation3DData(const Animation3DData& other)
    : _translationKeys(other._translationKeys)
    , _rotationKeys(other._rotationKeys)
    , _scaleKeys(other._scaleKeys)
    , _totalTime(other._totalTime)
    {
    }
    /** @~english reset data. @~chinese 重置动画数据*/
    void resetData()
    {
        _totalTime = 0;
        _translationKeys.clear();
        _rotationKeys.clear();
        _scaleKeys.clear();
    }
};

/** @~english reference data used for bundle header. @~chinese Bundle的表头信息
* @js NA
* @lua NA
*/
struct Reference
{
public:
    /** @~english reference data id @~chinese 数据ID */
    std::string id;
    /** @~english reference data type @~chinese 数据类型 */
    unsigned int type;
    /** @~english reference data offset @~chinese 数据偏移 */
    unsigned int offset;

    /** @~english Constructor @~chinese 构造函数 */
    Reference(){}

    /** @~english Destructor @~chinese 析构函数 */
    ~Reference(){}
};

NS_CC_END

#endif //__CC_BUNDLE_3D_DATA_H__
