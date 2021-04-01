/****************************************************************************
 Copyright (c) 2014-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "renderer/backend/Types.h"

#include <vector>
#include <map>
#include <string>

#include "3d/CC3DProgramInfo.h"

NS_CC_BEGIN

/**mesh vertex attribute
* @js NA
* @lua NA
*/
struct MeshVertexAttrib
{
    backend::VertexFormat type;
    shaderinfos::VertexKey vertexAttrib;
    int getAttribSizeBytes() const;
};


/** model node data, since 3.3
* @js NA
* @lua NA
*/
struct ModelData
{
    std::string subMeshId;
    std::string materialId;
    std::vector<std::string> bones;
    std::vector<Mat4>        invBindPose;
    
    virtual ~ModelData() {}

    virtual void resetData()
    {
        bones.clear();
        invBindPose.clear();
    }
};

/** Node data, since 3.3 
* @js NA
* @lua NA
*/
struct NodeData
{
    std::string id;
    Mat4        transform;
    std::vector<ModelData*> modelNodeDatas;
    std::vector<NodeData*>  children;

    virtual ~NodeData()
    {
        resetData();
    }
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

/** node datas, since 3.3 
* @js NA
* @lua NA
*/
struct NodeDatas
{
    std::vector<NodeData*> skeleton; //skeleton
    std::vector<NodeData*> nodes; // nodes, CCNode, Sprite3D or part of Sprite3D
    
    virtual ~NodeDatas()
    {
        resetData();
    }
    
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

/**mesh data
* @js NA
* @lua NA
*/
struct MeshData
{
    typedef std::vector<unsigned short> IndexArray;
    std::vector<float> vertex;
    int vertexSizeInFloat;
    std::vector<IndexArray> subMeshIndices;
    std::vector<std::string> subMeshIds; //subMesh Names (since 3.3)
    std::vector<AABB> subMeshAABB;
    int numIndex;
    std::vector<MeshVertexAttrib> attribs;
    int attribCount;

public:
    /**
     * Get per vertex size
     * @return return the sum of each vertex's all attribute size.
     */
    int getPerVertexSize() const
    {
        int vertexsize = 0;
        for(const auto& attrib : attribs)
        {
            vertexsize += attrib.getAttribSizeBytes();
        }
        return vertexsize;
    }

    /**
     * Reset the data
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
    MeshData()
    : vertexSizeInFloat(0)
    , numIndex(0)
    , attribCount(0)
    {
    }
};

/** mesh datas 
* @js NA
* @lua NA
*/
struct MeshDatas
{
    std::vector<MeshData*> meshDatas;
    
    void resetData()
    {
        for(auto& it : meshDatas)
        {
            delete it;
        }
        meshDatas.clear();
    }
    ~MeshDatas()
    {
        resetData();
    }
};

/**skin data
* @js NA
* @lua NA
*/
struct SkinData
{
    std::vector<std::string> skinBoneNames; //skin bones affect skin
    std::vector<std::string> nodeBoneNames; //node bones don't affect skin, all bones [skinBone, nodeBone]
    std::vector<Mat4>        inverseBindPoseMatrices; //bind pose of skin bone, only for skin bone
    std::vector<Mat4>        skinBoneOriginMatrices; // original bone transform, for skin bone
    std::vector<Mat4>        nodeBoneOriginMatrices; // original bone transform, for node bone
    
    //bone child info, both skinbone and node bone
    std::map<int, std::vector<int> > boneChild;//key parent, value child
    int                              rootBoneIndex;
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

    void addSkinBoneNames(const std::string& name)
    {
        auto it = std::find(skinBoneNames.begin(), skinBoneNames.end(), name);
        if (it == skinBoneNames.end())
            skinBoneNames.push_back(name);
    }
    
    void addNodeBoneNames(const std::string& name)
    {
        auto it = std::find(nodeBoneNames.begin(), nodeBoneNames.end(), name);
        if (it == nodeBoneNames.end())
            nodeBoneNames.push_back(name);
    }
    
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

/**material data, 
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


/**new material, since 3.3 
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
     backend::SamplerAddressMode wrapS;
     backend::SamplerAddressMode wrapT;
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
    std::string id;
    unsigned int type;
    unsigned int offset;
};

NS_CC_END

#endif //__CC_BUNDLE_3D_DATA_H__
