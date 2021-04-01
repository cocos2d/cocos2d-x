/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#if CC_USE_3D_PHYSICS

#if (CC_ENABLE_BULLET_INTEGRATION)

NS_CC_BEGIN

PhysicsSprite3D* PhysicsSprite3D::create(const std::string &modelPath, Physics3DRigidBodyDes* rigidDes, const cocos2d::Vec3& translateInPhysics, const cocos2d::Quaternion& rotInPhsyics)
{
    auto ret = new (std::nothrow) PhysicsSprite3D();
    if (ret && ret->initWithFile(modelPath))
    {
        auto obj = Physics3DRigidBody::create(rigidDes);
        ret->_physicsComponent = Physics3DComponent::create(obj, translateInPhysics, rotInPhsyics);
        ret->addComponent(ret->_physicsComponent);
        ret->_contentSize = ret->getBoundingBox().size;
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return ret;
}

PhysicsSprite3D* PhysicsSprite3D::createWithCollider(const std::string &modelPath, Physics3DColliderDes* colliderDes, const cocos2d::Vec3& translateInPhysics, const cocos2d::Quaternion& rotInPhsyics)
{
    auto ret = new (std::nothrow) PhysicsSprite3D();
    if (ret && ret->initWithFile(modelPath))
    {
        auto obj = Physics3DCollider::create(colliderDes);
        ret->_physicsComponent = Physics3DComponent::create(obj, translateInPhysics, rotInPhsyics);
        ret->addComponent(ret->_physicsComponent);
        ret->_contentSize = ret->getBoundingBox().size;
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return ret;
}

Physics3DObject* PhysicsSprite3D::getPhysicsObj() const
{
    return _physicsComponent->getPhysics3DObject();
}

void PhysicsSprite3D::setSyncFlag(Physics3DComponent::PhysicsSyncFlag syncFlag)
{
    if (_physicsComponent)
        _physicsComponent->setSyncFlag(syncFlag);
}

void PhysicsSprite3D::syncNodeToPhysics()
{
    if (_physicsComponent)
        _physicsComponent->syncNodeToPhysics();
}

void PhysicsSprite3D::syncPhysicsToNode()
{
    if (_physicsComponent)
        _physicsComponent->syncPhysicsToNode();
}

PhysicsSprite3D::PhysicsSprite3D()
: _physicsComponent(nullptr)
{
    
}
PhysicsSprite3D::~PhysicsSprite3D()
{
    
}

NS_CC_END

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif // CC_USE_3D_PHYSICS
