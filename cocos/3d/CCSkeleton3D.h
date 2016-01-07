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
 * @addtogroup _3d
 * @{
 */

/**
 * @class Bone3D
 * @brief @~english Defines a basic hierachial structure of transformation spaces.
 * @~chinese Bone3D(3D骨骼)类定义了骨骼基本的变换的层次结构：即一个骨骼包含若干子骨骼，他们的变换按照层次结构计算，该类备用于骨骼动画中
 * @lua NA
 */
class CC_DLL Bone3D : public Ref
{
    friend class Skeleton3D;
    friend class MeshSkin;
public:
    
    /**
     * @~english Returns the inverse bind pose matrix for this joint.
     * @~chinese 获取当前骨骼绑定自带的逆变换矩阵
     * @return @~english Inverse bind pose matrix.
     * @~chinese 绑定姿态的逆矩阵
     */
    const Mat4& getInverseBindPose();
    
    /**
     * @~english Update own world matrix and children's
     * @~chinese 更新该骨骼以及该骨骼的所有子骨骼到世界坐标变换矩阵
     */
    void updateWorldMat();
    
    /**
     * @~english Get world matrix.
     * @~chinese 获得到世界坐标系的变换矩阵
     * @return @~english The world matrix.
     * @~chinese 世界坐标系变换矩阵
     **/
    const Mat4& getWorldMat();
    
    /**
     * @~english Get bone name.
     * @~chinese 获取骨骼名称
     * @return @~english  The bone's name string.
     * @~chinese 包含骨骼名称的字符串
     */
    const std::string& getName() const { return _name; }
    
    /**
     * @~english Set animation value
     * @~chinese 设置骨骼的动画参数
     * @param trans @~english Translate vector
     * @~chinese  平移向量
     * @param rot   @~english Rotation quaternion
     * @~chinese 旋转四元数
     * @param scale @~english Scale vector
     * @~chinese 缩放向量
     * @param tag @~english unique tag, only blend animation between different tags
     * @~chinese tag(标签)，在计算混合动画时只对有不同标签的骨骼有效
     * @param weight @~english blend weight
     */
    void setAnimationValue(float* trans, float* rot, float* scale, void* tag = nullptr, float weight = 1.0f);
    
    /**
     * @~english Clear bone blend states.
     * @~chinese 清除当前骨骼的混合状态.
     * */
    void clearBoneBlendState();
    /**
     * @~english Creates Bone3D object from the specified ID string.
     * @~chinese 通过给定的字符串ID来创建Bone3D对象.
     * @param id @~english The specified ID.
     * @~chinese 给定的ID.
     * @return @~english The Bone3D object.
     * @~chinese 被创建的Bone3D对象
     */
    static Bone3D* create(const std::string& id);
    
    /**
     * @~english Sets the inverse bind pose matrix.
     * @~chinese 设置骨骼的绑定姿态的逆变换矩阵.
     * @param m @~english Mat4 representing the inverse bind pose for this Bone.
     * @~chinese 绑定姿态的逆变换矩阵.
     */
    void setInverseBindPose(const Mat4& m);
    
    /**
     * @~english Sets the bone's original pose.
     * @~chinese 设置骨骼的初始姿态
     * @param m @~english Mat4 representing the original pose for this Bone.
     * @~chinese 骨骼的初始姿态变换矩阵
     */
    void setOriPose(const Mat4& m);
    
    /**
     * @~english Reset pose to origin
     * @~chinese 将骨骼当前的绑定姿态重设为初始姿态.
     */
    void resetPose();
    
    /**
     * @~english Updates the joint matrix.
     * @~chinese 更新骨骼的Joint矩阵，Joint矩阵用于将当前关节变换到其父节点
     * @param matrixPalette @~english The matrix palette to update.
     * @~chinese 被设置的骨骼变换矩阵数组
     */
    void updateJointMatrix(Vec4* matrixPalette);
    
    /**
     * @~english Get the parent Bone.
     * @~chinese 获取该骨骼的父骨骼
     * @return @~english The parent Bone3D object.
     * @~chinese 父骨骼
     * @note @~english bone tree, we do not inherit from Node, Node has too many properties that we do not need. A clean Node is needed.
     * @~chinese 因为Node类过于膨胀，Bone3D类并非继承自Node
     */
    Bone3D* getParentBone();

    /**
     * @~english Get child bone count.
     * @~chinese 获取该骨骼的子骨骼数
     * @return @~english The child bone count.
     * @~chinese 子骨骼数
     */
    ssize_t getChildBoneCount() const;

    /**
     * @~english Get the specified child bone by index
     * @~chinese 通过给定的索引获取获取子骨骼
     * @param index @~english The child bone index.
     * @~chinese 子骨骼索引
     * @return @~english The Bone3D object.
     * @~chinese Bone3D对象
     */
    Bone3D* getChildBoneByIndex(int index) const;

    /**
     * @~english Add the specified bone as skeleton's child.
     * @~chinese 添加给定的骨骼作为当前骨骼的子骨骼
     * @param bone @~english The specified bone.
     * @~chinese 指定的Bone3D的对象
     */
    void addChildBone(Bone3D* bone);
    /**
     * @~english Remove child bone by index.
     * @~chinese 通过给定的索引删除子骨骼
     * @param index @~english The specified index
     * @~chinese 给定的骨骼索引
     */
    void removeChildBoneByIndex(int index);
    /**
     * @~english Remove the specified child bone.
     * @~chinese 删除指定的子骨骼
     * @param bone @~english The specified child bone.
     * @~chinese 指定的子骨骼
     */
    void removeChildBone(Bone3D* bone);

    /**
     * @~english Remove all child bone.
     * @~chinese 删除所有子骨骼
     */
    void removeAllChildBone();
    
    
    
protected:
    /**
     * @~english The BoneBlendState struct
     * @brief @~english Store the transformation and weight for bone blending
     */
    struct BoneBlendState
    {
        Vec3          localTranslate;
        Quaternion    localRot;
        Vec3          localScale;
        float         weight;
        void*         tag; //
        BoneBlendState()
        : localRot(Quaternion::identity())
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
 * @~english Skeleton, a set contain all bones.
 * @~chinese 骨架类，包含了所有骨骼的集合
 * @class Skeleton3D
 */
class CC_DLL Skeleton3D: public Ref
{
public:
    /**
     * @~english Create Skeleton3D object by skeleton data array.
     * @~chinese 通过骨架数据数组创建一个Skeleton3D对象
     * @param skeletondata @~english The skeleton data array.
     * @~chinese 骨架数据数组
     * @return The created Skeleton3D object.
     * @lua NA
     */
    static Skeleton3D* create(const std::vector<NodeData*>& skeletondata);
    
    /**
     * @~english Get total bone count.
     * @~chinese 获取骨架内所有骨骼的总数
     * @return @~english The bone count.
     * @~chinese 骨骼总数
     */
    ssize_t getBoneCount() const;
    
    /**
     * @~english Get bone by the specified index.
     * @~chinese 通过指定的索引获取骨骼
     * @param index @~english The specified index.
     * @~chinese 指定的索引
     * @return @~english The Bone3D object.
     * @~chinese Bone3D 对象
     */
    Bone3D* getBoneByIndex(unsigned int index) const;

    /**
    * @~english Get bone by the specified id(name).
    * @~chinese 通过指定的id(名称)，获取骨骼
    * @param id @~english The specified id(name).
    * @~chinese 指定的id（名称）
    * @return @~english The Bone3D object.
    * @~chinese Bone3D 对象
    */
    Bone3D* getBoneByName(const std::string& id) const;
    
    /**
    * @~english Get root bones count.
    * @~chinese 获取骨架内作为根节点的骨骼数量
    * @return @~english The root bones count.
    * @~chinese 根节点骨骼数量
    */
    ssize_t getRootCount() const;

    /**
    * @~english Get the specified root bone by index.
    * @~chinese 通过指定的索引，获取根节点骨骼
    * @param index The index.
    * @~chinese 索引
    * @return The specified root bone.
    * @~chinese 根节点骨骼
    */
    Bone3D* getRootBone(int index) const;
    
    /**
     * @~english Get bone index.
     * @~chinese 通过指定的Bone3D对象，获取其在骨架内的索引
     * @param bone @~english The specified Bone3D object.
     * @~chinese 指定的Bone3D对象
     * @return @~english The bone index.
     * @~chinese 索引
     */
    int getBoneIndex(Bone3D* bone) const;
    
    /**
     * @~english Refresh all bones world matrix.
     * @~chinese 重新更新所有骨骼的世界坐标变换矩阵
     */
    void updateBoneMatrix();
    
CC_CONSTRUCTOR_ACCESS:
    
    Skeleton3D();
    
    ~Skeleton3D();
    
    /**
     * @~english Remove all bones
     * @~chinese 删除所有骨架下的所有骨骼.
     */
    void removeAllBones();
    
    /**
     * @~english Add the specified bone into the skeleton.
     * @~chinese 向骨架内添加指定的.
     */
    void addBone(Bone3D* bone);
    
    /** 
     * @~english Create a Bone3D object from the specified NodeData object, then add it into the skeleton.
     * @~chinese 通过给定的NodeData 对象创建Bone3D对象，然后将其加入到骨架内.
     * @param nodedata @~english The NodeData object.
     * @~chinese  指定的NodeData对象.
     * @return @~english The Bone3D object.
     * @~chinese  被创建的Bone3D对象.
     */
    Bone3D* createBone3D(const NodeData& nodedata);
    
protected:
    
    Vector<Bone3D*> _bones; // bones

    Vector<Bone3D*> _rootBones;
};

// end of 3d group
/// @}

NS_CC_END

#endif // __CCSKELETON3D_H__
