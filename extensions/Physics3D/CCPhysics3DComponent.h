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

#ifndef __PHYSICS_3D_COMPONENT_H__
#define __PHYSICS_3D_COMPONENT_H__

#include "math/CCMath.h"
#include "extensions/ExtensionMacros.h"
#include "extensions/ExtensionExport.h"
#include "2d/CCComponent.h"

#if (CC_ENABLE_BULLET_INTEGRATION)

NS_CC_EXT_BEGIN

class Physics3DObject;
class Physics3DWorld;

class CC_EX_DLL Physics3DComponent : public cocos2d::Component
{
public:
    enum class PhysicsSyncFlag
    {
        NONE = 0,
        NODE_TO_PHYSICS = 1,
        PHYSICS_TO_NODE = 2,
        NODE_AND_NODE = NODE_TO_PHYSICS | PHYSICS_TO_NODE,
    };
    
    CREATE_FUNC(Physics3DComponent);
    virtual ~Physics3DComponent();
    virtual bool init() override;

    /**
     * create
     */
    static Physics3DComponent* create(Physics3DObject* physicsObj, const cocos2d::Vec3& translateInPhysics = cocos2d::Vec3::ZERO, const cocos2d::Quaternion& rotInPhsyics = cocos2d::Quaternion::ZERO);
    
    void setPhysics3DObject(Physics3DObject* physicsObj);
    
    Physics3DObject* getPhysics3DObject() const { return _physics3DObj; }
    
    static std::string& getPhysics3DComponentName();
    
    virtual void setEnabled(bool b) override;
    
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    void preSimulate();
    
    void postSimulate();
    
    void addToPhysicsWorld(Physics3DWorld* world);
    
    /**
     * The node's transform in physics space
     */
    void setTransformInPhysics(const cocos2d::Vec3& translateInPhysics, const cocos2d::Quaternion& rotInPhsyics);
    
    /**
     * synchronization between node and physics is time consuming, you can skip some synchronization using this function
     */
    void setSyncFlag(PhysicsSyncFlag syncFlag);
    
CC_CONSTRUCTOR_ACCESS:
    Physics3DComponent();
    
protected:
    cocos2d::Mat4             _transformInPhysics; //transform in physics space
    cocos2d::Mat4             _invTransformInPhysics;
    
    Physics3DObject*          _physics3DObj;
    PhysicsSyncFlag           _syncFlag;
};

NS_CC_EXT_END

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif // __PHYSICS_3D_COMPONENT_H__
