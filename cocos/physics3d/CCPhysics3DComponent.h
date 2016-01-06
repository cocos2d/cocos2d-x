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

#include "base/ccConfig.h"
#include "math/CCMath.h"

#include "2d/CCComponent.h"

#if CC_USE_3D_PHYSICS

#if (CC_ENABLE_BULLET_INTEGRATION)

NS_CC_BEGIN

/**
 * @addtogroup _3d
 * @{
 */

class Physics3DObject;
class Physics3DWorld;

/** @brief Physics3DComponent: A component with 3D physics, you can add a rigid body to it, and then add this component to a node, the node will move and rotate with this rigid body */
class CC_DLL Physics3DComponent : public cocos2d::Component
{
    friend class Physics3DWorld;
public:
    enum class PhysicsSyncFlag
    {
        NONE = 0,
        NODE_TO_PHYSICS = 1, //align node transform to the physics
        PHYSICS_TO_NODE = 2, // align physics transform to the node
        NODE_AND_NODE = NODE_TO_PHYSICS | PHYSICS_TO_NODE, //pre simulation, align the physics object to the node and align the node transform according to physics object after simulation
    };
    
    CREATE_FUNC(Physics3DComponent);
    virtual ~Physics3DComponent();
    virtual bool init() override;

    /**
     * create Physics3DComponent
     * @param physicsObj pointer to a Physics object contain in the component
     * @param translateInPhysics offset that the owner node in the physics object's space
     * @param rotInPhsyics offset rotation that the owner node in the physics object's space
     * @return created Physics3DComponent
     */
    static Physics3DComponent* create(Physics3DObject* physicsObj, const cocos2d::Vec3& translateInPhysics = cocos2d::Vec3::ZERO, const cocos2d::Quaternion& rotInPhsyics = cocos2d::Quaternion::ZERO);
    
    /**
     * set Physics object to the component
     */
    void setPhysics3DObject(Physics3DObject* physicsObj);
    
    /**
     * get physics object
     */
    Physics3DObject* getPhysics3DObject() const { return _physics3DObj; }
    
    /**
     * get the component name, it is used to find whether it is Physics3DComponent
     */
    static std::string& getPhysics3DComponentName();
    
    /**
     * set it enable or not
     */
    virtual void setEnabled(bool b) override;
    
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    /**
     * add this component to physics world, called by scene
     */
    void addToPhysicsWorld(Physics3DWorld* world);
    
    /**
     * The node's transform in physics object space
     */
    void setTransformInPhysics(const cocos2d::Vec3& translateInPhysics, const cocos2d::Quaternion& rotInPhsyics);
    
    /**
     * synchronization between node and physics is time consuming, you can skip some synchronization using this function
     */
    void setSyncFlag(PhysicsSyncFlag syncFlag);
    
    /**
     * synchronize node transformation to physics
     */
    void syncNodeToPhysics();
    
    /**
     * synchronize physics transformation to node
     */
    void syncPhysicsToNode();
    
CC_CONSTRUCTOR_ACCESS:
    Physics3DComponent();
    
protected:
    void preSimulate();
    
    void postSimulate();
    
    cocos2d::Mat4             _transformInPhysics; //transform in physics space
    cocos2d::Mat4             _invTransformInPhysics;
    
    Physics3DObject*          _physics3DObj;
    PhysicsSyncFlag           _syncFlag;
};

// end of 3d group
/// @}
NS_CC_END

#endif // CC_ENABLE_BULLET_INTEGRATION

#endif //CC_USE_3D_PHYSICS

#endif // __PHYSICS_3D_COMPONENT_H__
