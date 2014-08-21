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

#ifndef __CCMESHSKIN_H__
#define __CCMESHSKIN_H__

#include <unordered_map>

#include "3d/CCBundle3DData.h"
#include "3d/CCSkeleton3D.h"

#include "base/ccMacros.h"
#include "base/CCRef.h"
#include "base/CCVector.h"
#include "base/ccTypes.h"
#include "math/CCMath.h"
#include "3d/3dExport.h"

NS_CC_BEGIN

class Bone3D;
class Skeleton3D;

/**
 * MeshSkin, A class maintain a collection of bones that affect Mesh vertex.
 * And it is responsible for computing matrix palletes that used by skin mesh rendering.
 */
class CC_3D_DLL MeshSkin: public Ref
{
public:
    
    /**create a new meshskin if do not want to share meshskin*/
    static MeshSkin* create(Skeleton3D* skeleton, const std::string& filename, const std::string& name);
    
    /**get total bone count, skin bone + node bone*/
    ssize_t getBoneCount() const;
    
    /**get bone*/
    Bone3D* getBoneByIndex(unsigned int index) const;
    Bone3D* getBoneByName(const std::string& id) const;
    
    /**get & set root bone*/
    Bone3D* getRootBone() const;
    void setRootBone(Bone3D* bone);
    
    /**get bone index*/
    int getBoneIndex(Bone3D* bone) const;
    
    /**compute matrix palette used by gpu skin*/
    Vec4* getMatrixPalette();
    
    /**getSkinBoneCount() * 3*/
    ssize_t getMatrixPaletteSize() const;
    
    /**refresh bone world matrix*/
    void updateBoneMatrix();
    
CC_CONSTRUCTOR_ACCESS:
    
    MeshSkin();
    
    ~MeshSkin();
    
    /**init from skin data*/
    bool initFromSkinData(const SkinData& skindata);
    
    /**remove all bones*/
    void removeAllBones();
    
    /**add skin bone*/
    void addSkinBone(Bone3D* bone);
    
    /**add Node bone*/
    void addNodeBone(Bone3D* bone);
    
protected:
    
    Vector<Bone3D*>    _skinBones; // bones with skin
    std::vector<Mat4>  _invBindPoses; //inverse bind pose of bone
    Vector<Bone3D*> _nodeBones; //bones without skin, only used to compute transform of children

    Bone3D* _rootBone;
    Skeleton3D*     _skeleton; //skeleton the skin refered
    
    // Pointer to the array of palette matrices.
    // This array is passed to the vertex shader as a uniform.
    // Each 4x3 row-wise matrix is represented as 3 Vec4's.
    // The number of Vec4's is (_skinBones.size() * 3).
    Vec4* _matrixPalette;
};

/**
 * MeshSkinData Cache
 */
class MeshSkinDataCache
{
public:
    /**get & destroy*/
    static MeshSkinDataCache* getInstance();
    static void destroyInstance();
    
    /**get mesh skin data from cache*/
    const SkinData* getMeshSkinData(const std::string& key) const;
    
    /**add mesh skin data to cache*/
    bool addMeshSkinData(const std::string& key, const SkinData& skinData);
    
    /**remove all mesh skin data*/
    void removeAllMeshSkinData();
    
protected:
    MeshSkinDataCache();
    ~MeshSkinDataCache();
    
    static MeshSkinDataCache* _cacheInstance; // instance
    
    std::unordered_map<std::string, SkinData> _skinDatas; //cached skindatas
};

NS_CC_END

#endif // __CCSKIN_H__
