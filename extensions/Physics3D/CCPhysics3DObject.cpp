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

Physics3DRigidBody::Physics3DRigidBody()
: _btRigidBody(nullptr)
{
    
}

Physics3DRigidBody::~Physics3DRigidBody()
{
    CC_SAFE_DELETE(_btRigidBody);
}

Physics3DRigidBody* Physics3DRigidBody::create(Physics3DRigidBodyDes* info)
{
    auto ret = new (std::nothrow) Physics3DRigidBody();
    if (ret->init(info))
    {
        ret->autorelease();
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return ret;
}

bool Physics3DRigidBody::init(Physics3DRigidBodyDes* info)
{
    if (info->shape == nullptr)
        return false;
    
    btScalar mass = info->mass;
    auto shape = info->shape->getbtShape();
    auto localInertia = convertVec3TobtVector3(info->localInertia);
    if (mass != 0.f)
    {
        shape->calculateLocalInertia(mass,localInertia);
    }
    
    auto transform = convertMat4TobtTransform(info->originalTransform);
    btDefaultMotionState* myMotionState = new btDefaultMotionState(transform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,shape,localInertia);
    _btRigidBody = new btRigidBody(rbInfo);
    _type = Physics3DObject::PhysicsObjType::RIGID_BODY;
    
    return true;
}

NS_CC_EXT_END

#endif // CC_ENABLE_BULLET_INTEGRATION
