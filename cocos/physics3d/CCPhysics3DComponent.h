﻿/****************************************************************************
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
    @addtogroup _3d
    @{
*/

class Physics3DObject;
class Physics3DWorld;

/**
    @class Physics3DComponent
    @brief @~english A component with 3D physics, you can add a rigid body to it, and then add this component to a node, the node will move and rotate with this rigid body
    @~chinese 您可以添加一个刚体给3D物理组件，然后将这个组件添加到一个节点，该节点将与此刚体移动以及转动
*/
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

    /** destructor*/
    virtual ~Physics3DComponent();

    /** initialize
    */
    virtual bool init() override;

    /** @~english create Physics3DComponent
        @~chinese 创建physics3dcomponent
        @param physicsObj @~english  pointer to a Physics object contain in the component @~chinese 在组件包含一个物理对象的指针
        @param translateInPhysics @~english  offset that the owner node in the physics object's space @~chinese 所有者节点与物理对象的偏移（在物理空间）
        @param rotInPhsyics @~english  offset rotation that the owner node in the physics object's space @~chinese 所有者节点与物理对象的旋转（在物理空间）
        @return @~english created Physics3DComponent @~chinese 创建physics3dcomponent
    */
    static Physics3DComponent* create(Physics3DObject* physicsObj, const cocos2d::Vec3& translateInPhysics = cocos2d::Vec3::ZERO, const cocos2d::Quaternion& rotInPhsyics = cocos2d::Quaternion::ZERO);

    /** @~english set Physics object to the component
        @~chinese 将物理对象添加到组件
        @param physicsObj @~english  the physics object that will be seted @~chinese 将添加的物理对象
    */
    void setPhysics3DObject(Physics3DObject* physicsObj);

    /** @~english get physics object
        @~chinese 获取当前组件的物理对象
        @return @~english the physics object @~chinese 当前组件的物理对象
    */
    Physics3DObject* getPhysics3DObject() const { return _physics3DObj; }

    /** @~english get the component name, it is used to find whether it is Physics3DComponent
        @~chinese 得到的组件的名称
        @return @~english the name of component name @~chinese 组件的名称
    */
    static std::string& getPhysics3DComponentName();

    /** @~english set it enable or not
        @~chinese 设置是否启用组件
        @param b @~english  set ture to enable this component reverse otherwise @~chinese 是否启用组件
    */
    virtual void setEnabled(bool b) override;


    virtual void onEnter() override;
    virtual void onExit() override;

    /** @~english add this component to physics world, called by scene
        @~chinese 将该组件添加到物理世界，被场景对象调用
        @param world @~english  the physics world which this component will be added @~chinese 这个组件将被添加到的物理世界
    */
    void addToPhysicsWorld(Physics3DWorld* world);

    /** @~english The node's transform in physics object space
        @~chinese 节点在物理对象空间的变换
        @param translateInPhysics @~english  the transfrom in physics object space @~chinese 在物理空间的变换
        @param rotInPhsyics @~english  the quaternion in physics object space @~chinese 在物理空间的四元数
    */
    void setTransformInPhysics(const cocos2d::Vec3& translateInPhysics, const cocos2d::Quaternion& rotInPhsyics);

    /** @~english synchronization between node and physics is time consuming, you can skip some synchronization using this function
        @~chinese 节点和物理之间的同步是耗费时间，你可以使用此功能跳过一些同步
        @param syncFlag @~english  the synchroniztion of component @~chinese 同步标识
    */
    void setSyncFlag(PhysicsSyncFlag syncFlag);

    /** @~english align node and physics according to physics object
        @~chinese 根据物理对象对齐节点和物理
    */
    void syncToPhysics();

    /** @~english align node and physics according to node
        @~chinese 根据节点对象对齐节点和物理
    */
    void syncToNode();

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
