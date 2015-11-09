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

#include "3d/CCBundle3DData.h"
#include "base/CCRef.h"
#include "base/CCVector.h"
#include "math/CCMath.h"


NS_CC_BEGIN

/**
 * @addtogroup _3d
 * @{
 */

class Bone3D;
class Skeleton3D;

/**
 * @class MeshSkin
 * @brief @~english MeshSkin, A class maintain a collection of bones that affect Mesh vertex.
 * And it is responsible for computing matrix palletes that used by skin mesh rendering.
 * @~chinese MeshSkin：包含了一系列蒙皮骨骼的集合，负责为骨骼蒙皮渲染创建骨骼矩阵组
 * @js NA
 * @lua NA
 */
class CC_DLL MeshSkin: public Ref
{
    friend class Mesh;
public:
    
    /**
     * @~english Create a new meshskin if do not want to share meshskin
     * @param skeleton @~english The specified skeleton.
     */
    static MeshSkin* create(Skeleton3D* skeleton, const std::string& filename, const std::string& name);
    
    /**
     * @~english Create a new meshskin if do not want to share meshskin
     * @~chinese 通过非共享方式创建一个MeshSkin对象
     * @param skeleton @~english The specified skeleton.
     * @~chinese 指定的Skeleton3D对象
     * @param boneNames @~english The bones names list.
     * @~chinese 骨骼名称数组
     * @param invBindPose @~english The bones' inverse binding pose.
     * @~chinese 骨骼的绑定姿态逆矩阵
     * @return @~english The meshSkin object.
     * @~chinese 被创建的MeshSkin对象
     */
    static MeshSkin* create(Skeleton3D* skeleton, const std::vector<std::string>& boneNames, const std::vector<Mat4>& invBindPose);
    
    /**
     * @~english Get total bone count. (skin bone + node bone)
     * @~chinese 获取所有骨骼数，包含蒙皮骨骼与节点骨骼
     * @return @~english The bone count.
     * @~chinese 骨骼数
     */
    ssize_t getBoneCount() const;
    
    /**
     * @~english Get the specified bone by index.
     * @~chinese 通过索引获取骨骼
     * @param index @~english The index.
     * @~chinese 骨骼索引
     * @return @~english The Bone3D object.
     * @~chinese Bone3D 对象
     */
    Bone3D* getBoneByIndex(unsigned int index) const;

    /**
    * @~english Get the specified bone by name.
    * @~chinese 通过骨骼名称获取骨骼
    * @param id @~english The name.
    * @~chinese 骨骼名称
    * @return @~english The Bone3D object.
    * @~chinese Bone3D对象
    */
    Bone3D* getBoneByName(const std::string& id) const;
    
    /**
     * @~english Get the specified bone index.
     * @~chinese 获取指定的骨骼索引
     * @param bone @~english The specified Bone3D object.
     * @~chinese 指定的Bone3D对象
     * @return @~english The index.
     * @~chinese 指定的Bone3D对象的索引
     */
    int getBoneIndex(Bone3D* bone) const;
    
    /**
     * @~english Compute matrix palette used by gpu skin. The matrix palette is array of matrix which contatin
     * @~chinese 创建一个矩阵组(matrix palette)用以进行GPU蒙皮
     * @return @~english The matrix palette.
     * @~chinese 骨骼变换矩阵组
     */
    Vec4* getMatrixPalette();
    
    /**
     * @~english Get the MatrixPalette size.
     * @~chinese 获取骨骼变换矩阵组的大小
     * @return @~english The size.
     * @~chinese 大小
     * @note @~english Equal to the getSkinBoneCount() * 3
     * @~chinese 与getSkinBoneCount() * 3结果相等
     */
    ssize_t getMatrixPaletteSize() const;
    
    /**
     * @~english Get the root bone of the skin.
     * @~chinese 获取根骨骼
     * @return @~english The Bone3D object. 
     * @~chinese Bone3D对象
     */
    Bone3D* getRootBone() const;
    
CC_CONSTRUCTOR_ACCESS:
    
    MeshSkin();
    
    ~MeshSkin();
    
    /**
     * @~english Remove all bones.
     * @~chinese 删除所有骨骼
     */
    void removeAllBones();
    
    /**
     * @~english Add the specified skin bone
     * @~chinese 添加一个给定的蒙皮骨骼
     * @param bone @~english The Bone3D object.
     * @~chinese Bone3D对象
     */
    void addSkinBone(Bone3D* bone);
    
    /** 
     * @~english Get inverse bind pose by the specified Bone3D object.
     * @~chinese 获取指定骨骼的绑定姿态的逆矩阵
     * @param bone @~english The Bone3d object.
     * @~chinese Bone3D 对象
     * @return @~english The inverse bind pose matrix.
     * @~chinese 绑定姿态逆矩阵
     */
    const Mat4& getInvBindPose(const Bone3D* bone);
    
protected:
    
    Vector<Bone3D*>    _skinBones; // bones with skin
    std::vector<Mat4>  _invBindPoses; //inverse bind pose of bone

    Bone3D* _rootBone;
    Skeleton3D*     _skeleton; //skeleton the skin referred
    
    // Pointer to the array of palette matrices.
    // This array is passed to the vertex shader as a uniform.
    // Each 4x3 row-wise matrix is represented as 3 Vec4's.
    // The number of Vec4's is (_skinBones.size() * 3).
    Vec4* _matrixPalette;
};

// end of 3d group
/// @}

NS_CC_END

#endif // __CCSKIN_H__
