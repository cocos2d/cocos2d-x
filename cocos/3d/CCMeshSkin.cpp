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
#include "3d/CCBundle3D.h"

#include "base/ccMacros.h"
#include "base/CCPlatformMacros.h"
#include "platform/CCFileUtils.h"

NS_CC_BEGIN

/**
 * Sets the inverse bind pose matrix.
 *
 * @param m C3DMatrix representing the inverse bind pose for this Bone.
 */
void Bone3D::setInverseBindPose(const Mat4& m)
{
    _invBindPose = m;
}

const Mat4& Bone3D::getInverseBindPose()
{
    return _invBindPose;
}

void Bone3D::setOriPose(const Mat4& m)
{
    _oriPose = m;
}

void Bone3D::resetPose()
{
    _local =_oriPose;
    
    for (auto it : _children) {
        it->resetPose();
    }
}

void Bone3D::setWorldMatDirty(bool dirty)
{
    _worldDirty = dirty;
    for (auto it : _children) {
        it->setWorldMatDirty(dirty);
    }
}

//update own world matrix and children's
void Bone3D::updateWorldMat()
{
    getWorldMat();
    for (auto itor : _children) {
        itor->updateWorldMat();
    }
}

const Mat4& Bone3D::getWorldMat()
{
    if (_worldDirty)
    {
        updateLocalMat();
        if (_parent)
        {
            _world = _parent->getWorldMat() * _local;
        }
        else
            _world = _local;
        
        _worldDirty = false;
    }
    
    return _world;
}

void Bone3D::setAnimationValue(float* trans, float* rot, float* scale, void* tag, float weight)
{
    for (auto& it : _blendStates) {
        if (it.tag == tag)
        {
            if (trans)
                it.localTranslate.set(trans);
            if (rot)
                it.localRot.set(rot);
            if (scale)
                it.localScale.set(scale);
            it.weight = weight;
            return;
        }
    }
    BoneBlendState state;
    if (trans)
        state.localTranslate.set(trans);
    if (rot)
        state.localRot.set(rot);
    if (scale)
        state.localScale.set(scale);
    
    state.weight = weight;
    state.tag = tag;
    
    _blendStates.push_back(state);
}

void Bone3D::clearBoneBlendState()
{
    _blendStates.clear();
    for (auto it : _children) {
        it->clearBoneBlendState();
    }
}

/**
 * Creates C3DBone.
 */
Bone3D* Bone3D::create(const std::string& id)
{
    auto bone = new Bone3D(id);
    bone->autorelease();
    return bone;
}

void Bone3D::updateJointMatrix(Vec4* matrixPalette)
{
    {
        static Mat4 t;
        Mat4::multiply(_world, getInverseBindPose(), &t);

        matrixPalette[0].set(t.m[0], t.m[4], t.m[8], t.m[12]);
        matrixPalette[1].set(t.m[1], t.m[5], t.m[9], t.m[13]);
        matrixPalette[2].set(t.m[2], t.m[6], t.m[10], t.m[14]);
    }
}

Bone3D* Bone3D::getParentBone()
{
    return _parent;
}
ssize_t Bone3D::getChildBoneCount() const
{
    return _children.size();
}
Bone3D* Bone3D::getChildBoneByIndex(int index)
{
    return _children.at(index);
}
void Bone3D::addChildBone(Bone3D* bone)
{
    if (_children.find(bone) == _children.end())
       _children.pushBack(bone);
}
void Bone3D::removeChildBoneByIndex(int index)
{
    _children.erase(index);
}
void Bone3D::removeChildBone(Bone3D* bone)
{
    _children.eraseObject(bone);
}
void Bone3D::removeAllChildBone()
{
    _children.clear();
}

Bone3D::Bone3D(const std::string& id)
: _name(id)
, _parent(nullptr)
, _worldDirty(true)
{
    
}

Bone3D::~Bone3D()
{
    removeAllChildBone();
}

void Bone3D::updateLocalMat()
{
    if (_blendStates.size())
    {
        Vec3 translate(Vec3::ZERO), scale(Vec3::ZERO);
        Quaternion quat(Quaternion::zero());
        
        float total = 0.f;
        for (auto it: _blendStates) {
            total += it.weight;
        }
        if (total)
        {
            if (_blendStates.size() == 1)
            {
                auto& state = _blendStates[0];
                translate = state.localTranslate;
                scale = state.localScale;
                quat = state.localRot;
            }
            else
            {
                float invTotal = 1.f / total;
                for (auto it : _blendStates) {
                    float weight = (it.weight * invTotal);
                    translate += it.localTranslate * weight;
                    scale.x += it.localScale.x * weight;
                    scale.y += it.localScale.y * weight;
                    scale.z += it.localScale.z * weight;
                    if (!quat.isZero())
                    {
                        Quaternion& q = _blendStates[0].localRot;
                        if (q.x * quat.x + q.y * quat.y + q.z * quat.z + q.w * quat.w < 0)
                            weight = -weight;
                    }
                    quat = Quaternion(it.localRot.x * weight + quat.x, it.localRot.y * weight + quat.y, it.localRot.z * weight + quat.z, it.localRot.w * weight + quat.w);
                }
            }
        }
        
        Mat4::createTranslation(translate, &_local);
        _local.rotate(quat);
        _local.scale(scale);
        
        _blendStates.clear();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int PALETTE_ROWS = 3;

MeshSkin::MeshSkin()
: _rootBone(nullptr)
, _matrixPalette(nullptr)
{
    
}

MeshSkin::~MeshSkin()
{
    removeAllBones();
}

//create a new meshskin if do not want to share meshskin
MeshSkin* MeshSkin::create(const std::string& filename, const std::string& name)
{
    //load skin here;
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filename);
    std::string key = fullPath + "#" + name;
    const auto skindata = MeshSkinDataCache::getInstance()->getMeshSkinData(key);
    if (skindata)
    {
        auto skin = new MeshSkin();
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
    for (auto it : _skinBones) {
        if (it->getName() == id)
            return it;
    }
    //search from node bones
    for (auto it : _nodeBones) {
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
    int i = 0;
	for (auto it : _skinBones )
	{
        it->updateJointMatrix(&_matrixPalette[i++ * PALETTE_ROWS]);
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
