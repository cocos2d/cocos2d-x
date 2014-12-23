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

#ifndef __CCSKELETON3D_H__
#define __CCSKELETON3D_H__

#include "3d/CCBundle3DData.h"
#include "base/CCRef.h"
#include "base/CCVector.h"


NS_CC_BEGIN

/**
 * Defines a basic hierachial structure of transformation spaces.
 */
class CC_DLL Bone3D : public Ref
{
    friend class Skeleton3D;
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
    static Bone3D* create(const std::string& id);
    
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
    Bone3D* getParentBone();
    /**get child bone count*/
    ssize_t getChildBoneCount() const;
    /**get child bone by index*/
    Bone3D* getChildBoneByIndex(int index) const;
    /**add child bone*/
    void addChildBone(Bone3D* bone);
    /**remove child bone by index*/
    void removeChildBoneByIndex(int index);
    /**remove child bone*/
    void removeChildBone(Bone3D* bone);
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
    Bone3D(const std::string& id);
    
	/**
     * Destructor.
     */
    virtual ~Bone3D();
    
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
    
    Bone3D* _parent; //parent bone
    
    Vector<Bone3D*> _children;
    
    bool          _worldDirty;
    Mat4          _world;
    Mat4          _local;
    
    std::vector<BoneBlendState> _blendStates;
    
};

/**
 * Skeleton
 *
 */
class CC_DLL Skeleton3D: public Ref
{
public:
    
    static Skeleton3D* create(const std::vector<NodeData*>& skeletondata);
    
    /**get total bone count*/
    ssize_t getBoneCount() const;
    
    /**get bone*/
    Bone3D* getBoneByIndex(unsigned int index) const;
    Bone3D* getBoneByName(const std::string& id) const;
    
    /**get & set root bone*/
    ssize_t getRootCount() const;
    Bone3D* getRootBone(int index) const;
    
    /**get bone index*/
    int getBoneIndex(Bone3D* bone) const;
    
    /**refresh bone world matrix*/
    void updateBoneMatrix();
    
CC_CONSTRUCTOR_ACCESS:
    
    Skeleton3D();
    
    ~Skeleton3D();
    
    /**remove all bones*/
    void removeAllBones();
    
    /**add bone*/
    void addBone(Bone3D* bone);
    
    /** create Bone3D from NodeData */
    Bone3D* createBone3D(const NodeData& nodedata);
    
protected:
    
    Vector<Bone3D*> _bones; // bones

    Vector<Bone3D*> _rootBones;
};

NS_CC_END

#endif // __CCSKELETON3D_H__
