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

#ifndef __PHYSICS_3D_OBJECT_H__
#define __PHYSICS_3D_OBJECT_H__

#include "math/CCMath.h"
#include "base/CCRef.h"
#include "extensions/ExtensionMacros.h"
#include "extensions/ExtensionExport.h"

#if (CC_ENABLE_BULLET_INTEGRATION)

class btCollisionShape;
class btRigidBody;

NS_CC_EXT_BEGIN

class Physics3DShape;

CC_EX_DLL class Physics3DObject : public Ref
{
public:
    enum class PhysicsObjType
    {
        UNKNOWN = 0,
        RIGID_BODY,
    };
    
    virtual PhysicsObjType getObjType() const { return _type; }
    
    void setUserData(void* userData)  { _userData = userData; }
    
    void* getUserData() const { return _userData; }
    
CC_CONSTRUCTOR_ACCESS:
    Physics3DObject()
    : _type(PhysicsObjType::UNKNOWN)
    {
        
    }
    virtual ~Physics3DObject(){}
    
protected:
    PhysicsObjType _type;
    void* _userData;
};

CC_EX_DLL struct Physics3DRigidBodyDes
{
    float mass; //Note: mass equals zero means static, default 0
    cocos2d::Vec3 localInertia; //default (0, 0, 0)
    Physics3DShape* shape;
    cocos2d::Mat4 originalTransform;
    
    Physics3DRigidBodyDes()
    : mass(0.f)
    , localInertia(0.f, 0.f, 0.f)
    , shape(nullptr)
    {
        
    }
};
CC_EX_DLL class Physics3DRigidBody : public Physics3DObject
{
public:
    
    static Physics3DRigidBody* create(Physics3DRigidBodyDes* info);
    
    btRigidBody* getRigidBody() const { return _btRigidBody; }
    
CC_CONSTRUCTOR_ACCESS:
    Physics3DRigidBody();
    virtual ~Physics3DRigidBody();
    
    bool init(Physics3DRigidBodyDes* info);
    
protected:
    btRigidBody* _btRigidBody;
};

NS_CC_EXT_END

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif // __PHYSICS_3D_OBJECT_H__
