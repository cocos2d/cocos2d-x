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

#include "3d/CCMeshSkin.h"
#include "3d/CCSkeleton3D.h"
#include "3d/CCBundle3D.h"

#include "base/ccMacros.h"
#include "base/CCPlatformMacros.h"
#include "platform/CCFileUtils.h"

NS_CC_BEGIN

static int PALETTE_ROWS = 3;

MeshSkin::MeshSkin()
: _rootBone(nullptr)
, _matrixPalette(nullptr)
{
    
}

MeshSkin::~MeshSkin()
{
    removeAllBones();
    CC_SAFE_RELEASE(_skeleton);
}

MeshSkin* MeshSkin::create(Skeleton3D* skeleton, const std::string& filename, const std::string& name)
{
    //load skin here;
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filename);
    std::string key = fullPath + "#" + name;
    const auto skindata = MeshSkinDataCache::getInstance()->getMeshSkinData(key);
    if (skindata)
    {
        auto skin = new MeshSkin();
        skin->_skeleton = skeleton;
        skeleton->retain();
        skin->initFromSkinData(*skindata);
        skin->autorelease();
        return skin;
    }
    else
    {
        auto instance = Bundle3D::getInstance();
        bool ret = instance->load(fullPath);
        if (ret)
        {
            SkinData data;
            if (instance->loadSkinData(name, &data))
            {
                auto skin = new MeshSkin();
                skin->_skeleton = skeleton;
                skeleton->retain();
                skin->initFromSkinData(data);
                skin->autorelease();
                MeshSkinDataCache::getInstance()->addMeshSkinData(key, data);
                return skin;
            }
        }
    }
    
    return nullptr;
}

bool MeshSkin::initFromSkinData(const SkinData& skindata)
{
    ssize_t i = 0;
    for (; i < skindata.skinBoneNames.size(); i++) {
        auto bone = Bone3D::create(skindata.skinBoneNames[i]);
        bone->_invBindPose = skindata.inverseBindPoseMatrices[i];
        bone->setOriPose(skindata.skinBoneOriginMatrices[i]);
        _invBindPoses.push_back(skindata.inverseBindPoseMatrices[i]);
        addSkinBone(bone);
    }
    for (i = 0; i < skindata.nodeBoneNames.size(); i++) {
        auto bone = Bone3D::create(skindata.nodeBoneNames[i]);
        bone->setOriPose(skindata.nodeBoneOriginMatrices[i]);
        addNodeBone(bone);
    }
    for (auto it : skindata.boneChild) {
        auto parent = getBoneByIndex(it.first);
        for (auto childIt : it.second) {
            auto child = getBoneByIndex(childIt);
            child->_parent = parent;
            parent->_children.pushBack(child);
        }
    }
    
    setRootBone(getBoneByIndex(skindata.rootBoneIndex));
    _rootBone->resetPose();
    
    return true;
}

ssize_t MeshSkin::getBoneCount() const
{
    return _skinBones.size() + _nodeBones.size();
}

//get bone
Bone3D* MeshSkin::getBoneByIndex(unsigned int index) const
{
    if (index < _skinBones.size())
        return _skinBones.at(index);
    index -= _skinBones.size();
    if (index < _nodeBones.size())
        return _nodeBones.at(index);
    
    return nullptr;
}
Bone3D* MeshSkin::getBoneByName(const std::string& id) const
{
    //search from skin bones
    for (const auto& it : _skinBones) {
        if (it->getName() == id)
            return it;
    }
    //search from node bones
    for (const auto& it : _nodeBones) {
        if (it->getName() == id )
            return it;
    }
    return nullptr;
}

Bone3D* MeshSkin::getRootBone() const
{
    return _rootBone;
}
void MeshSkin::setRootBone(Bone3D* joint)
{
    CC_SAFE_RETAIN(joint);
    CC_SAFE_RELEASE(_rootBone);
    _rootBone = joint;
}

int MeshSkin::getBoneIndex(Bone3D* bone) const
{
    int i = 0;
    for (; i < _skinBones.size(); i++) {
        if (_skinBones.at(i) == bone)
            return i;
    }
    int index = 0;
    for (; index < _nodeBones.size(); index++, i++) {
        if (_nodeBones.at(index) == bone)
            return i;
    }
    return -1;
}

//compute matrix palette used by gpu skin
Vec4* MeshSkin::getMatrixPalette()
{
    updateBoneMatrix();
    
    if (_matrixPalette == nullptr)
    {
        _matrixPalette = new Vec4[_skinBones.size() * PALETTE_ROWS];
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

//refresh bone world matrix
void MeshSkin::updateBoneMatrix()
{
    _rootBone->setWorldMatDirty(true);
    _rootBone->updateWorldMat();
}

void MeshSkin::removeAllBones()
{
    _skinBones.clear();
    _nodeBones.clear();
    CC_SAFE_DELETE_ARRAY(_matrixPalette);
    CC_SAFE_RELEASE(_rootBone);
}

void MeshSkin::addSkinBone(Bone3D* bone)
{
    _skinBones.pushBack(bone);
}

void MeshSkin::addNodeBone(Bone3D* bone)
{
    _nodeBones.pushBack(bone);
}

////////////////////////////////////////////////////////////////////////
MeshSkinDataCache* MeshSkinDataCache::_cacheInstance = nullptr;

MeshSkinDataCache* MeshSkinDataCache::getInstance()
{
    if (_cacheInstance == nullptr)
        _cacheInstance = new MeshSkinDataCache();
    return _cacheInstance;
}
void MeshSkinDataCache::destroyInstance()
{
    if (_cacheInstance)
    {
        CC_SAFE_DELETE(_cacheInstance);
    }
}

const SkinData* MeshSkinDataCache::getMeshSkinData(const std::string& key) const
{
    auto it = _skinDatas.find(key);
    if (it != _skinDatas.end())
        return &it->second;
    
    return nullptr;
}

bool MeshSkinDataCache::addMeshSkinData(const std::string& key, const SkinData& skin)
{
    if (_skinDatas.find(key) != _skinDatas.end())
        return false; // already have this key
    
    _skinDatas[key] = skin;
    
    return true;
}

void MeshSkinDataCache::removeAllMeshSkinData()
{
    _skinDatas.clear();
}

MeshSkinDataCache::MeshSkinDataCache()
{
    
}
MeshSkinDataCache::~MeshSkinDataCache()
{
    
}

NS_CC_END
