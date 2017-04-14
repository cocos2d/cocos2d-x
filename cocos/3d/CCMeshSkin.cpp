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

#include "3d/CCMeshSkin.h"
#include "3d/CCBundle3D.h"
#include "3d/CCSkeleton3D.h"

NS_CC_BEGIN

static int PALETTE_ROWS = 3;

MeshSkin::MeshSkin()
: _rootBone(nullptr)
, _skeleton(nullptr)
, _matrixPalette(nullptr)
{
    
}

MeshSkin::~MeshSkin()
{
    removeAllBones();
    CC_SAFE_RELEASE(_skeleton);
}

MeshSkin* MeshSkin::create(Skeleton3D* skeleton, const std::vector<std::string>& boneNames, const std::vector<Mat4>& invBindPose)
{
    auto skin = new (std::nothrow) MeshSkin();
    skin->_skeleton = skeleton;
    skeleton->retain();
    
    CCASSERT(boneNames.size() == invBindPose.size(), "bone names' num should equals to invBindPose's num");
    for (const auto& it : boneNames) {
        auto bone = skeleton->getBoneByName(it);
        if (bone)
        {
            skin->addSkinBone(bone);
        }
    }
    skin->_invBindPoses = invBindPose;
    skin->autorelease();
    
    return skin;
}

ssize_t MeshSkin::getBoneCount() const
{
    return _skinBones.size();
}

//get bone
Bone3D* MeshSkin::getBoneByIndex(unsigned int index) const
{
    if (static_cast<int>(index) < _skinBones.size())
        return _skinBones.at(index);
    
    return nullptr;
}
Bone3D* MeshSkin::getBoneByName(const std::string& id) const
{
    //search from skin bones
    for (const auto& it : _skinBones) {
        if (it->getName() == id)
            return it;
    }
    return nullptr;
}

int MeshSkin::getBoneIndex(Bone3D* bone) const
{
    for (ssize_t i = 0, size = _skinBones.size(); i < size; ++i) {
        if (_skinBones.at(i) == bone)
            return static_cast<int>(i);
    }

    return -1;
}

//compute matrix palette used by gpu skin
Vec4* MeshSkin::getMatrixPalette()
{
    if (_matrixPalette == nullptr)
    {
        _matrixPalette = new (std::nothrow) Vec4[_skinBones.size() * PALETTE_ROWS];
    }
    int i = 0, paletteIndex = 0;
    static Mat4 t;
    for (auto it : _skinBones )
    {
        Mat4::multiply(it->getWorldMat(), _invBindPoses[i++], &t);
        _matrixPalette[paletteIndex++].set(t.m[0], t.m[4], t.m[8], t.m[12]);
        _matrixPalette[paletteIndex++].set(t.m[1], t.m[5], t.m[9], t.m[13]);
        _matrixPalette[paletteIndex++].set(t.m[2], t.m[6], t.m[10], t.m[14]);
    }
    
    return _matrixPalette;
}

ssize_t MeshSkin::getMatrixPaletteSize() const
{
    return _skinBones.size() * PALETTE_ROWS;
}

void MeshSkin::removeAllBones()
{
    _skinBones.clear();
    CC_SAFE_DELETE_ARRAY(_matrixPalette);
    CC_SAFE_RELEASE(_rootBone);
}

void MeshSkin::addSkinBone(Bone3D* bone)
{
    _skinBones.pushBack(bone);
}

Bone3D* MeshSkin::getRootBone() const
{
    Bone3D* root = nullptr;
    if (_skinBones.size())
    {
        root = _skinBones.at(0);
        while (root->getParentBone()) {
            root = root->getParentBone();
        }
    }
    return root;
}

const Mat4& MeshSkin::getInvBindPose(const Bone3D* bone)
{
    for (ssize_t i = 0, size = _skinBones.size(); i < size; ++i) {
        if (_skinBones.at(i) == bone)
        {
            return _invBindPoses.at(i);
        }
    }
    return Mat4::IDENTITY;
}

NS_CC_END
