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

#include <vector>
#include <map>
 
NS_CC_BEGIN

/**mesh vertex attribute*/
struct MeshVertexAttrib
{
    //attribute size
    GLint size;
    //GL_FLOAT
    GLenum type;
    //VERTEX_ATTRIB_POSITION,VERTEX_ATTRIB_COLOR,VERTEX_ATTRIB_TEX_COORD,VERTEX_ATTRIB_NORMAL, VERTEX_ATTRIB_BLEND_WEIGHT, VERTEX_ATTRIB_BLEND_INDEX, GLProgram for detail
    int  vertexAttrib;
    //size in bytes
    int attribSizeBytes;
};

/**mesh data*/
struct MeshData
{
    std::vector<float> vertex;
    int vertexSizeInFloat;
    std::vector<unsigned short> indices;
    int numIndex;
    std::vector<MeshVertexAttrib> attribs;
    int attribCount;

public:
    void resetData()
    {
        vertex.clear();
        indices.clear();
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
    ~MeshData()
    {
        resetData();
    }
};

/**skin data*/
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
        for (auto iter : skinBoneNames)
        {
            if ((iter) == name)
                return;
        }
        
        skinBoneNames.push_back(name);
    }
    
    void addNodeBoneNames(const std::string& name)
    {
        for (auto iter : nodeBoneNames)
        {
            if ((iter) == name)
                return;
        }
        
        nodeBoneNames.push_back(name);
    }
    
    int getSkinBoneNameIndex(const std::string& name)const
    {
        int i = 0;
        for (auto iter : skinBoneNames)
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
        for (auto iter : skinBoneNames)
        {
            if ((iter) == name)
                return i;
            i++;
        }
        for(auto iter : nodeBoneNames)
        {
            if (iter == name)
                return i;
            i++;
        }
        return -1;
    }

};

/**material data*/
struct MaterialData
{
    std::string texturePath;
};

/**animation data*/
struct Animation3DData
{
public:
    struct Vec3Key
    {
        Vec3Key()
        : _time(0)
        , _key(Vec3::ZERO)
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
    : _totalTime(other._totalTime)
    , _translationKeys(other._translationKeys)
    , _rotationKeys(other._rotationKeys)
    , _scaleKeys(other._scaleKeys)
    {
    }
    
    void clear()
    {
        _totalTime = 0;
        _translationKeys.clear();
        _rotationKeys.clear();
        _scaleKeys.clear();
    }
};

/**reference data*/
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
