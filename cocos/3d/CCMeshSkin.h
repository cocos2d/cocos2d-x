/****************************************************************************
 Copyright (c) 2014-2017 Chukong Technologies Inc.

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
 * @brief MeshSkin, A class maintain a collection of bones that affect Mesh vertex.
 * And it is responsible for computing matrix palettes that used by skin mesh rendering.
 * @js NA
 * @lua NA
 */
class CC_DLL MeshSkin: public Ref
{
    friend class Mesh;
public:
    
    /**create a new meshskin if do not want to share meshskin*/
    static MeshSkin* create(Skeleton3D* skeleton, const std::string& filename, const std::string& name);
    
    static MeshSkin* create(Skeleton3D* skeleton, const std::vector<std::string>& boneNames, const std::vector<Mat4>& invBindPose);
    
    /**get total bone count, skin bone + node bone*/
    ssize_t getBoneCount() const;
    
    /**get bone*/
    Bone3D* getBoneByIndex(unsigned int index) const;
    Bone3D* getBoneByName(const std::string& id) const;
    
    /**get bone index*/
    int getBoneIndex(Bone3D* bone) const;
    
    /**compute matrix palette used by gpu skin*/
    Vec4* getMatrixPalette();
    
    /**getSkinBoneCount() * 3*/
    ssize_t getMatrixPaletteSize() const;
    
    /**get root bone of the skin*/
    Bone3D* getRootBone() const;
    
CC_CONSTRUCTOR_ACCESS:
    
    MeshSkin();
    
    ~MeshSkin();
    
    /**remove all bones*/
    void removeAllBones();
    
    /**add skin bone*/
    void addSkinBone(Bone3D* bone);
    
    /** get inverse bind pose */
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
