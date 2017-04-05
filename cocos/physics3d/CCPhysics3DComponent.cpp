 /****************************************************************************
 Copyright (c) 2015-2017 Chukong Technologies Inc.
 
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

#include "physics3d/CCPhysics3D.h"
#include "2d/CCNode.h"
#include "2d/CCScene.h"

#if CC_USE_3D_PHYSICS

#if (CC_ENABLE_BULLET_INTEGRATION)

NS_CC_BEGIN

Physics3DComponent::~Physics3DComponent()
{
    CC_SAFE_RELEASE(_physics3DObj);
}

std::string& Physics3DComponent::getPhysics3DComponentName()
{
    static std::string comName = "___Physics3DComponent___";
    return comName;
}

bool Physics3DComponent::init()
{
    setName(getPhysics3DComponentName());
    return Component::init();
}

Physics3DComponent* Physics3DComponent::create(Physics3DObject* physicsObj, const cocos2d::Vec3& translateInPhysics, const cocos2d::Quaternion& rotInPhsyics)
{
    auto ret = new (std::nothrow) Physics3DComponent();
    if (ret && ret->init())
    {
        ret->setPhysics3DObject(physicsObj);
        ret->setTransformInPhysics(translateInPhysics, rotInPhsyics);
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void Physics3DComponent::setPhysics3DObject(Physics3DObject* physicsObj)
{
    CC_SAFE_RETAIN(physicsObj);
    CC_SAFE_RELEASE(_physics3DObj);
    _physics3DObj = physicsObj;
}

Physics3DComponent::Physics3DComponent()
: _physics3DObj(nullptr)
, _syncFlag(Physics3DComponent::PhysicsSyncFlag::NODE_AND_NODE)
{
    
}

void Physics3DComponent::setEnabled(bool b)
{
    bool oldBool = _enabled;
    Component::setEnabled(b);
    if (_physics3DObj && oldBool != _enabled)
    {
        _enabled ? _physics3DObj->getPhysicsWorld()->addPhysics3DObject(_physics3DObj) : _physics3DObj->getPhysicsWorld()->removePhysics3DObject(_physics3DObj);
    }
}

void Physics3DComponent::addToPhysicsWorld(Physics3DWorld* world)
{
    //add component to physics world
    if (_physics3DObj)
    {
        _physics3DObj->setPhysicsWorld(world);
        world->addPhysics3DObject(_physics3DObj);
        auto& components = world->_physicsComponents;
        auto it = std::find(components.begin(), components.end(), this);
        if (it == components.end())
        {
            auto parent = _owner->getParent();
            while (parent) {
                for (size_t i = 0; i < components.size(); i++) {
                    if (parent == components[i]->getOwner())
                    {
                        //insert it here
                        components.insert(components.begin() + i, this);
                        return;
                    }
                }
                parent = parent->getParent();
            }
            
            components.insert(components.begin(), this);
        }
    }
}

void Physics3DComponent::onEnter()
{
    Component::onEnter();
    
    if (_physics3DObj->getPhysicsWorld() == nullptr && _owner)
    {
        auto scene = _owner->getScene();
        if (scene)
            addToPhysicsWorld(scene->getPhysics3DWorld());
    }
}

void Physics3DComponent::onExit()
{
    Component::onExit();
    setEnabled(false);
    
    //remove component from physics world
    if (_physics3DObj)
    {
        auto& components = _physics3DObj->getPhysicsWorld()->_physicsComponents;
        auto it = std::find(components.begin(), components.end(), this);
        if (it != components.end())
            components.erase(it);
    }
}

void Physics3DComponent::preSimulate()
{
    if (((int)_syncFlag & (int)Physics3DComponent::PhysicsSyncFlag::NODE_TO_PHYSICS) && _physics3DObj && _owner)
    {
        syncNodeToPhysics();
    }
}

void Physics3DComponent::postSimulate()
{
    if (((int)_syncFlag & (int)Physics3DComponent::PhysicsSyncFlag::PHYSICS_TO_NODE) && _physics3DObj && _owner)
    {
        syncPhysicsToNode();
    }
}

void Physics3DComponent::setTransformInPhysics(const cocos2d::Vec3& translateInPhysics, const cocos2d::Quaternion& rotInPhsyics)
{
    Mat4::createRotation(rotInPhsyics, &_transformInPhysics);
    _transformInPhysics.m[12] = translateInPhysics.x;
    _transformInPhysics.m[13] = translateInPhysics.y;
    _transformInPhysics.m[14] = translateInPhysics.z;
    
    _invTransformInPhysics = _transformInPhysics.getInversed();
}

void Physics3DComponent::setSyncFlag(PhysicsSyncFlag syncFlag)
{
    _syncFlag = syncFlag;
}

void Physics3DComponent::syncPhysicsToNode()
{
    if (_physics3DObj->getObjType() == Physics3DObject::PhysicsObjType::RIGID_BODY
     || _physics3DObj->getObjType() == Physics3DObject::PhysicsObjType::COLLIDER)
    {
        Mat4 parentMat;
        if (_owner->getParent())
            parentMat = _owner->getParent()->getNodeToWorldTransform();
        
        auto mat = parentMat.getInversed() * _physics3DObj->getWorldTransform();
        //remove scale, no scale support for physics
        float oneOverLen = 1.f / sqrtf(mat.m[0] * mat.m[0] + mat.m[1] * mat.m[1] + mat.m[2] * mat.m[2]);
        mat.m[0] *= oneOverLen;
        mat.m[1] *= oneOverLen;
        mat.m[2] *= oneOverLen;
        oneOverLen = 1.f / sqrtf(mat.m[4] * mat.m[4] + mat.m[5] * mat.m[5] + mat.m[6] * mat.m[6]);
        mat.m[4] *= oneOverLen;
        mat.m[5] *= oneOverLen;
        mat.m[6] *= oneOverLen;
        oneOverLen = 1.f / sqrtf(mat.m[8] * mat.m[8] + mat.m[9] * mat.m[9] + mat.m[10] * mat.m[10]);
        mat.m[8] *= oneOverLen;
        mat.m[9] *= oneOverLen;
        mat.m[10] *= oneOverLen;
        
        mat *= _transformInPhysics;
        static Vec3 scale, translation;
        static Quaternion quat;
        mat.decompose(&scale, &quat, &translation);
        _owner->setPosition3D(translation);
        quat.normalize();
        _owner->setRotationQuat(quat);
    }
}

void Physics3DComponent::syncNodeToPhysics()
{
    if (_physics3DObj->getObjType() == Physics3DObject::PhysicsObjType::RIGID_BODY
     || _physics3DObj->getObjType() == Physics3DObject::PhysicsObjType::COLLIDER)
    {
        auto mat = _owner->getNodeToWorldTransform();
        //remove scale, no scale support for physics
        float oneOverLen = 1.f / sqrtf(mat.m[0] * mat.m[0] + mat.m[1] * mat.m[1] + mat.m[2] * mat.m[2]);
        mat.m[0] *= oneOverLen;
        mat.m[1] *= oneOverLen;
        mat.m[2] *= oneOverLen;
        oneOverLen = 1.f / sqrtf(mat.m[4] * mat.m[4] + mat.m[5] * mat.m[5] + mat.m[6] * mat.m[6]);
        mat.m[4] *= oneOverLen;
        mat.m[5] *= oneOverLen;
        mat.m[6] *= oneOverLen;
        oneOverLen = 1.f / sqrtf(mat.m[8] * mat.m[8] + mat.m[9] * mat.m[9] + mat.m[10] * mat.m[10]);
        mat.m[8] *= oneOverLen;
        mat.m[9] *= oneOverLen;
        mat.m[10] *= oneOverLen;
        
        mat *=  _invTransformInPhysics;
        if (_physics3DObj->getObjType() == Physics3DObject::PhysicsObjType::RIGID_BODY)
        {
            auto body = static_cast<Physics3DRigidBody*>(_physics3DObj)->getRigidBody();
            auto motionState = body->getMotionState();
            motionState->setWorldTransform(convertMat4TobtTransform(mat));
            body->setMotionState(motionState);
        }
        else if (_physics3DObj->getObjType() == Physics3DObject::PhysicsObjType::COLLIDER)
        {
            auto object = static_cast<Physics3DCollider*>(_physics3DObj)->getGhostObject();
            object->setWorldTransform(convertMat4TobtTransform(mat));
        }
    }
}

NS_CC_END

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif //CC_USE_3D_PHYSICS
