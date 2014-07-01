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

#include "base/ccMacros.h"
#include "base/CCRef.h"
#include "base/CCVector.h"
#include "base/ccTypes.h"
#include "math/CCMath.h"

NS_CC_BEGIN

/**
 * Defines a basic hierachial structure of transformation spaces.
 */
class Bone : public Ref
{
    friend class MeshSkin;
public:
    
    /**
     * Returns the inverse bind pose matrix for this joint.
     *
     * @return Inverse bind pose matrix.
     */
    const Mat4& getInverseBindPose();
    
    /**update own world matrix and children's*/
    void updateWorldMat();
    
    /**get wrod matrix*/
    const Mat4& getWorldMat();
    
    /**get bone name*/
    const std::string& getName() const { return _name; }
    
    /**
     * set animation value
     * @param trans translate vec3
     * @param rot   rotation quaternion
     * @param scale scale vec3
     * @param tag, unique tag, only blend animation between different tags
     * @param weight, blend weight
     */
    void setAnimationValue(float* trans, float* rot, float* scale, void* tag = nullptr, float weight = 1.0f);
    
    /**clear bone blend states*/
    void clearBoneBlendState();
    /**
     * Creates C3DBone.
     */
    static Bone* create(const std::string& id);
    
    /**
     * Sets the inverse bind pose matrix.
     *
     * @param m Mat4 representing the inverse bind pose for this Bone.
     */
    void setInverseBindPose(const Mat4& m);
    
    /**
     * Sets the bone's original pose.
     *
     * @param m Mat4 representing the original pose for this Bone.
     */
    void setOriPose(const Mat4& m);
    
    /**
     * reset pose to origin
     */
    void resetPose();
    
    /**
     * Updates the joint matrix.
     *
     * @param matrixPalette The matrix palette to update.
     */
    void updateJointMatrix(Vec4* matrixPalette);
    
    /**bone tree, we do not inherit from Node, Node has too many properties that we do not need. A clean Node is needed.*/
    Bone* getParentBone();
    /**get child bone count*/
    ssize_t getChildBoneCount() const;
    /**get child bone by index*/
    Bone* getChildBoneByIndex(int index);
    /**add child bone*/
    void addChildBone(Bone* bone);
    /**remove child bone by index*/
    void removeChildBoneByIndex(int index);
    /**remove child bone*/
    void removeChildBone(Bone* bone);
    /**remove all child bone*/
    void removeAllChildBone();
    
    
    
protected:
    
    struct BoneBlendState
    {
        Vec3          localTranslate;
        Quaternion    localRot;
        Vec3          localScale;
        float         weight;
        void*         tag; //
        BoneBlendState()
        : localTranslate(Vec3::ZERO)
        , localRot(Quaternion::identity())
        , localScale(Vec3::ONE)
        , weight(1.f)
        , tag(nullptr)
        {
            
        }
    };
	/**
     * Constructor.
     */
    Bone(const std::string& id);
    
	/**
     * Destructor.
     */
    virtual ~Bone();
    
    /**
     * Update local matrix
     */
    void updateLocalMat();
    
    /**set world matrix dirty flag*/
    void setWorldMatDirty(bool dirty = true);
    
    std::string _name; // bone name
    /**
     * The Mat4 representation of the Joint's bind pose.
     */
    Mat4 _invBindPose;
    
    Mat4 _oriPose; //original bone pose
    
    Bone* _parent; //parent bone
    
    Vector<Bone*> _children;
    
    bool          _worldDirty;
    Mat4          _world;
    Mat4          _local;
    
    std::vector<BoneBlendState> _blendStates;
    
};

/**
 * MeshSkin, A class maintain a collection of bones that affect Mesh vertex.
 * And it is responsible for computing matrix palletes that used by skin mesh rendering.
 */
class MeshSkin: public Ref
{
public:
    
    /**create a new meshskin if do not want to share meshskin*/
    static MeshSkin* create(const std::string& filename, const std::string& name);
    
    /**get total bone count, skin bone + node bone*/
    ssize_t getBoneCount() const;
    
    /**get bone*/
    Bone* getBoneByIndex(unsigned int index) const;
    Bone* getBoneByName(const std::string& id) const;
    
    /**get & set root bone*/
    Bone* getRootBone() const;
    void setRootBone(Bone* bone);
    
    /**get bone index*/
    int getBoneIndex(Bone* bone) const;
    
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
    void addSkinBone(Bone* bone);
    
    /**add Node bone*/
    void addNodeBone(Bone* bone);
    
protected:
    
    Vector<Bone*> _skinBones; // bones with skin
    Vector<Bone*> _nodeBones; //bones without skin, only used to compute transform of children

    Bone* _rootBone;
    
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
