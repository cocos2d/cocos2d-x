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
    
public:
    
    /**
     * Returns the inverse bind pose matrix for this joint.
     *
     * @return Inverse bind pose matrix.
     */
    const Mat4& getInverseBindPose();
    
    bool needUpdateWorldMat() const;
    
    //update own world matrix and children's
    void updateWorldMat();
    
    const Mat4& getWorldMat();
    
    const std::string& getName() const { return _name; }
    
	/**
     * Set AnimationValue. set to its transform
     */
	void setAnimationValueTranslation(float* value);
    void setAnimationValueRotation(float* value);
    void setAnimationValueScale(float* value);
    
    /**
     * Creates C3DBone.
     */
    static Bone* create(const std::string& id);
    
    /**
     * Sets the inverse bind pose matrix.
     *
     * @param m C3DMatrix representing the inverse bind pose for this Bone.
     */
    void setInverseBindPose(const Mat4& m);
    
    /**
     * Updates the joint matrix.
     *
     * @param bindShape The bind shape matrix.
     * @param matrixPalette The matrix palette to update.
     */
    void updateJointMatrix(const Mat4& bindShape, Vec4* matrixPalette);
    
    //bone tree, we do not inherit from Node, Node has too many properties that we do not need. A clean Node is needed.
    Bone* getParentBone();
    int getChildBoneCount() const;
    Bone* getChildBoneByIndex(int index);
    void addChildBone(Bone* bone);
    void removeChildBoneByIndex(int index);
    void removeChildBone(Bone* bone);
    void removeAllChildBone();
    
    
    
protected:
    enum DirtyFlag
    {
        Dirty_Translate = 1,
        Dirty_Rotation = 2,
        Dirty_Scale = 4,
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
    
    std::string _name;
    /**
     * The Mat4 representation of the Joint's bind pose.
     */
    Mat4 _bindPose;
    
    //    /**
    //     * Flag used to mark if the Joint's matrix is dirty.
    //     */
    //    bool _jointMatrixDirty;
    //
    //    /**
    //     * The number of MeshSkin's influencing the Joint.
    //     */
    //    unsigned int _skinCount;
    
    Bone* _parent;
    
    Vector<Bone*> _children;
    
    int           _dirtyFlag;
    bool          _worldDirty;
    Mat4          _world;
    Mat4          _local;
    Vec3          _localTranslate;
    Quaternion    _localRot;
    Vec3          _localScale;
};

/////////////////////////////////////////////////////////////////////////////
class MeshSkin: public Ref
{
public:
    MeshSkin* getOrCreate(const std::string& filename, const std::string& name);
    
    //create a new meshskin if do not want to share meshskin
    MeshSkin* create(const std::string& filename, const std::string& name);
    
    //get & set bind shape matrix
    const Mat4& getBindShape() const;
    void setBindShape(const float* matrix);
    
    unsigned int getBoneCount() const;
    
    void setBoneCount(int boneCount);
    
    //get bone
    Bone* getBoneByIndex(unsigned int index) const;
    Bone* getBoneByName(const std::string& id) const;
    
    //get & set root bone
    Bone* getRootBone() const;
    void setRootBone(Bone* joint);
    
    int getBoneIndex(Bone* joint) const;
    
    //compute matrix palette used by gpu skin
    Vec4* getMatrixPalette() const;
    
    //getBoneCount() * 3
    unsigned int getMatrixPaletteSize() const;
    
    //refresh bone world matrix
    void updateBoneMatrix();
    
protected:
    MeshSkin();
    
    ~MeshSkin();
    
    void removeAllBones();
    
    void addBone(Bone* bone);
    
    Mat4 _bindShape;
    Vector<Bone*> _bones;
    Bone* _rootBone;
    
    // Pointer to the array of palette matrices.
    // This array is passed to the vertex shader as a uniform.
    // Each 4x3 row-wise matrix is represented as 3 Vec4's.
    // The number of Vec4's is (_joints.size() * 3).
    Vec4* _matrixPalette;
};

class MeshSkinCache
{
public:
    static MeshSkinCache* getInstance();
    static void purgeMeshSkinCache();
    
    MeshSkin* getMeshSkin(const std::string& key);
    
    bool addMeshSkin(const std::string& key, MeshSkin* skin);
    
    void removeAllMeshSkin();
    void removeUnusedMeshSkin();
    
protected:
    MeshSkinCache();
    ~MeshSkinCache();
    
    static MeshSkinCache* _cacheInstance;
    
    std::unordered_map<std::string, MeshSkin*> _skins;
};

NS_CC_END

#endif // __CCSKIN_H__
