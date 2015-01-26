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

#include "3d/CCSkeleton3D.h"


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
    auto bone = new (std::nothrow) Bone3D(id);
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
Bone3D* Bone3D::getChildBoneByIndex(int index) const
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
        Quaternion quat(Quaternion::ZERO);
        
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
                for (const auto& it : _blendStates)
                {
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
                quat.normalize();
            }
        }
        
        Mat4::createTranslation(translate, &_local);
        _local.rotate(quat);
        _local.scale(scale);
        
        _blendStates.clear();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Skeleton3D::Skeleton3D()
{
    
}

Skeleton3D::~Skeleton3D()
{
    removeAllBones();
}

Skeleton3D* Skeleton3D::create(const std::vector<NodeData*>& skeletondata)
{
    auto skeleton = new (std::nothrow) Skeleton3D();
    for (const auto& it : skeletondata) {
        auto bone = skeleton->createBone3D(*it);
        bone->resetPose();
        skeleton->_rootBones.pushBack(bone);
    }
    skeleton->autorelease();
    return skeleton;
}

ssize_t Skeleton3D::getBoneCount() const
{
    return _bones.size();
}

//get bone
Bone3D* Skeleton3D::getBoneByIndex(unsigned int index) const
{
    if (index < static_cast<unsigned int>(_bones.size()))
        return _bones.at(index);
    
    return nullptr;
}
Bone3D* Skeleton3D::getBoneByName(const std::string& id) const
{
    //search from bones
    for (auto it : _bones) {
        if (it->getName() == id)
            return it;
    }
    
    return nullptr;
}

ssize_t Skeleton3D::getRootCount() const
{
    return _rootBones.size();
}

Bone3D* Skeleton3D::getRootBone(int index) const
{
    return _rootBones.at(index);
}

int Skeleton3D::getBoneIndex(Bone3D* bone) const
{
    int i = 0;
    for (; i < _bones.size(); i++) {
        if (_bones.at(i) == bone)
            return i;
    }
    
    return -1;
}

//refresh bone world matrix
void Skeleton3D::updateBoneMatrix()
{
    for (const auto& it : _rootBones) {
        it->setWorldMatDirty(true);
        it->updateWorldMat();
    }
}

void Skeleton3D::removeAllBones()
{
    _bones.clear();
    _rootBones.clear();
}

void Skeleton3D::addBone(Bone3D* bone)
{
    _bones.pushBack(bone);
}

Bone3D* Skeleton3D::createBone3D(const NodeData& nodedata)
{
    auto bone = Bone3D::create(nodedata.id);
    for (const auto& it : nodedata.children) {
        auto child = createBone3D(*it);
        bone->addChildBone(child);
        child->_parent = bone;
    }
    _bones.pushBack(bone);
    bone->_oriPose = nodedata.transform;
    return bone;
}

NS_CC_END
