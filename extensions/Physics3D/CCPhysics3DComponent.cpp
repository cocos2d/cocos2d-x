/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
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

#include "CCPhysics3D.h"

#if (CC_ENABLE_BULLET_INTEGRATION)



NS_CC_EXT_BEGIN

Physics3DComponent::~Physics3DComponent()
{
    
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

Physics3DComponent* Physics3DComponent::create(Physics3DObject* physicsObj)
{
    auto ret = new (std::nothrow) Physics3DComponent();
    if (ret && ret->init())
    {
        ret->setPhysics3DObject(physicsObj);
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

//virtual void update(float delta);
bool Physics3DComponent::serialize(void* r)
{
    //TODO: FIXME
    return Component::serialize(r);
}

void Physics3DComponent::setPhysics3DObject(Physics3DObject* physicsObj)
{
    CC_SAFE_RETAIN(physicsObj);
    CC_SAFE_RELEASE(_physics3DObj);
    _physics3DObj = physicsObj;
}

Physics3DComponent::Physics3DComponent()
: _physics3DObj(nullptr)
{
    
}

void Physics3DComponent::setEnabled(bool b)
{
    bool oldBool = b;
    Component::setEnabled(b);
    if (_physics3DObj && oldBool != _enabled)
    {
        _enabled ? _physics3DObj->getPhysicsWorld()->addPhysics3DObject(_physics3DObj) : _physics3DObj->getPhysicsWorld()->removePhysics3DObject(_physics3DObj);
    }
}

void Physics3DComponent::onEnter()
{
    Component::onEnter();
    setEnabled(true);
}

void Physics3DComponent::onExit()
{
    Component::onExit();
    setEnabled(false);
}

void Physics3DComponent::syncToPhysics()
{
    if (_physics3DObj && _owner)
    {
        if (_physics3DObj->getObjType() == Physics3DObject::PhysicsObjType::RIGID_BODY)
        {
            auto parentMat = _owner->getParent()->getNodeToWorldTransform();
            auto mat = parentMat.getInversed() * _physics3DObj->getWorldTransform();
            static Vec3 scale, translation;
            static Quaternion quat;
            mat.decompose(&scale, &quat, &translation);
            _owner->setPosition3D(translation);
            _owner->setRotationQuat(quat);
            _owner->setScaleX(scale.x);
            _owner->setScaleY(scale.y);
            _owner->setScaleZ(scale.z);
        }
    }
}

NS_CC_EXT_END

#endif // CC_ENABLE_BULLET_INTEGRATION
