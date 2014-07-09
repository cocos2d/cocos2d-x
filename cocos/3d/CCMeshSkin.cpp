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
void Bone::setInverseBindPose(const Mat4& m)
{
    _invBindPose = m;
}

const Mat4& Bone::getInverseBindPose()
{
    return _invBindPose;
}

void Bone::setWorldMatDirty(bool dirty)
{
    _worldDirty = dirty;
    for (auto it : _children) {
        it->setWorldMatDirty(dirty);
    }
}

//update own world matrix and children's
void Bone::updateWorldMat()
{
    getWorldMat();
    for (auto itor : _children) {
        itor->updateWorldMat();
    }
}

const Mat4& Bone::getWorldMat()
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

void Bone::setAnimationValue(float* trans, float* rot, float* scale, float weight)
{
    BoneBlendState state;
    if (trans)
        state.localTranslate.set(trans);
    if (rot)
        state.localRot.set(rot);
    if (scale)
        state.localScale.set(scale);
    
    state.weight = weight;
    
    _blendStates.push_back(state);
    _localDirty = true;
}

void Bone::clearBoneBlendState()
{
    _blendStates.clear();
    for (auto it : _children) {
        it->clearBoneBlendState();
    }
}

/**
 * Creates C3DBone.
 */
Bone* Bone::create(const std::string& id)
{
    auto bone = new Bone(id);
    bone->autorelease();
    return bone;
}



/**
 * Updates the joint matrix.
 *
 * @param matrixPalette The matrix palette to update.
 */
void Bone::updateJointMatrix(Vec4* matrixPalette)
{
    {
        static Mat4 t;
        Mat4::multiply(_world, getInverseBindPose(), &t);

        matrixPalette[0].set(t.m[0], t.m[4], t.m[8], t.m[12]);
        matrixPalette[1].set(t.m[1], t.m[5], t.m[9], t.m[13]);
        matrixPalette[2].set(t.m[2], t.m[6], t.m[10], t.m[14]);
    }
}

//bone tree, we do not inherit from Node, Node has too many properties that we do not need. A clean Node is needed.
Bone* Bone::getParentBone()
{
    return _parent;
}
int Bone::getChildBoneCount() const
{
    return _children.size();
}
Bone* Bone::getChildBoneByIndex(int index)
{
    return _children.at(index);
}
void Bone::addChildBone(Bone* bone)
{
    if (_children.find(bone) == _children.end())
       _children.pushBack(bone);
}
void Bone::removeChildBoneByIndex(int index)
{
    _children.erase(index);
}
void Bone::removeChildBone(Bone* bone)
{
    _children.eraseObject(bone);
}
void Bone::removeAllChildBone()
{
    _children.clear();
}

Bone::Bone(const std::string& id)
: _name(id)
, _parent(nullptr)
, _localDirty(true)
, _worldDirty(true)
{
    
}

/**
 * Destructor.
 */
Bone::~Bone()
{
    removeAllChildBone();
}

void Bone::updateLocalMat()
{
    if (_blendStates.size())
    {
        Vec3 translate(Vec3::ZERO), scale(Vec3::ONE);
        Quaternion quat(Quaternion::identity());
        
        float total = 0.f;
        for (auto it: _blendStates) {
            total += it.weight;
        }
        if (total)
        {
            //if (_blendStates.size() == 1)
            if (true)
            {
                int cnt = _blendStates.size();
                translate = _blendStates[cnt - 1].localTranslate;
                scale = _blendStates[cnt - 1].localScale;
                quat = _blendStates[cnt - 1].localRot;
            }
            else
            {
                float invTotal = 1.f / total;
                for (auto it : _blendStates) {
                    float weight = (it.weight * invTotal);
                    translate += it.localTranslate * weight;
                    if (!it.localScale.isZero())
                    {
                        scale.x *= it.localScale.x * weight;
                        scale.y *= it.localScale.y * weight;
                        scale.z *= it.localScale.z * weight;
                    }
                    if (!it.localRot.isZero())
                    {
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
        }
        
        Mat4::createTranslation(translate, &_local);
        _local.rotate(quat);
        _local.scale(scale);
        
        _blendStates.clear();
        _localDirty = false;
    }
    else
    {
        CCLOG("use cached local");
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
    setBoneCount((int)skindata.boneNames.size());
    for (size_t i = 0; i < skindata.boneNames.size(); i++) {
        auto bone = Bone::create(skindata.boneNames[i]);
        bone->_invBindPose = skindata.inverseBindPoseMatrices[i];
        addBone(bone);
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
    return true;
}

unsigned int MeshSkin::getBoneCount() const
{
    return _bones.size();
}

//get bone
Bone* MeshSkin::getBoneByIndex(unsigned int index) const
{
    return _bones.at(index);
}
Bone* MeshSkin::getBoneByName(const std::string& id) const
{
    for (auto it : _bones) {
        if (it->getName() == id )
            return it;
    }
    return nullptr;
}

//get & set root bone
Bone* MeshSkin::getRootBone() const
{
    return _rootBone;
}
void MeshSkin::setRootBone(Bone* joint)
{
    CC_SAFE_RETAIN(joint);
    CC_SAFE_RELEASE(_rootBone);
    _rootBone = joint;
}

void MeshSkin::setBoneCount(int boneCount)
{
    removeAllBones();
    
    // Resize the joints vector and initialize to NULL
    _bones.reserve(boneCount);
//    for (auto i = 0; i < boneCount; i++)
//    {
//        _bones.pushBack(nullptr);
//    }
    
    // Rebuild the matrix palette. Each matrix is 3 rows of Vec4.
    CC_SAFE_DELETE_ARRAY(_matrixPalette);
    
    if (boneCount > 0)
    {
        _matrixPalette = new Vec4[boneCount * PALETTE_ROWS];
        for (unsigned int i = 0; i < boneCount * PALETTE_ROWS; i+=PALETTE_ROWS)
        {
            _matrixPalette[i+0].set(1.0f, 0.0f, 0.0f, 0.0f);
            _matrixPalette[i+1].set(0.0f, 1.0f, 0.0f, 0.0f);
            _matrixPalette[i+2].set(0.0f, 0.0f, 1.0f, 0.0f);
        }
    }
}

int MeshSkin::getBoneIndex(Bone* joint) const
{
    for (auto i = 0; i < _bones.size(); i++) {
        if (_bones.at(i) == joint)
            return i;
    }
    return -1;
}

//compute matrix palette used by gpu skin
Vec4* MeshSkin::getMatrixPalette()
{
    updateBoneMatrix();
    
    int i = 0;
	for (auto it : _bones )
	{
        it->updateJointMatrix(&_matrixPalette[i++ * PALETTE_ROWS]);
	}
    
    return _matrixPalette;
}

//getBoneCount() * 3
unsigned int MeshSkin::getMatrixPaletteSize() const
{
    return _bones.size() * PALETTE_ROWS;
}

//refresh bone world matrix
void MeshSkin::updateBoneMatrix()
{
    _rootBone->setWorldMatDirty(true);
    _rootBone->updateWorldMat();
}

void MeshSkin::removeAllBones()
{
    _bones.clear();
    CC_SAFE_DELETE_ARRAY(_matrixPalette);
    CC_SAFE_RELEASE(_rootBone);
}

void MeshSkin::addBone(Bone* bone)
{
    _bones.pushBack(bone);
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
