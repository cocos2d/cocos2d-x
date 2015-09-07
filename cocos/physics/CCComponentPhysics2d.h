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

#pragma once

#include "base/ccConfig.h" // to include defination of CC_USE_PHYSICS
#if CC_USE_PHYSICS

#include "platform/CCPlatformMacros.h"
#include "2d/CCComponent.h"

NS_CC_BEGIN

/**
 * @addtogroup physics
 * @{
 * @addtogroup physics_2d
 * @{
 */

class PhysicsBody;

class CC_DLL ComponentPhysics2d : public Component
{
public:
    /**
     * Create a physics component without physics body. Can set phyiscs body later with setPhysicsBody().
     * I am not sure if we need this function, because i think physics body is needed when creating a
     * physics component. But i think it is needed by editor, so i keep this function.
     *
     * @return A pointer of `ComponentPhysics2d` that is autoreleased.
     */
    static ComponentPhysics2d* create();
    /**
     * Create a physics component with physics body.
     *
     * @param physicsBody The physics body that belongs to this component.
     * @return A pointer of `ComponentPhysics2d` that is autoreleased.
     */
    static ComponentPhysics2d* create(PhysicsBody *physicsBody);
    
    virtual ~ComponentPhysics2d();
    
    /// @cond DO_NOT_SHOW

    /**
     * Synchronize Node's status(position, rotation, scale) to phyiscs body.
     * It is invoked before physics simulation.
     *
     * @warning Don't invoke this funciton by yourself.
     */
    void beforeSimulation();
    /**
     * Synchronize physics body's status(position, rotation) to phyiscs body.
     * It is invoked after physics simulation.
     *
     * @warning Don't invoke this funciton by yourself.
     */
    void afterSimulation();
    
    /// @endcond DO_NOT_SHOW
    
    /**
     * Set physics body of this physics component. If the physics body is set to
     * another physics component before, will set another physics component's physics
     * body to null.
     *
     * @param physicsBody The physics body belongs to this component.
     */
    void setPhysicsBody(PhysicsBody *physicsBody);
    /**
     * Get the physics body of this component.
     *
     * @return The physics body of this component.
     */
    PhysicsBody* getPhysicsBody() const;
    
    virtual void setEnabled(bool value) override;
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void onAdd() override;
    virtual void onRemove() override;
    
public:
    const static std::string COMPONENT_NAME;
    
CC_CONSTRUCTOR_ACCESS:
    ComponentPhysics2d();
    ComponentPhysics2d(PhysicsBody *phsicsBody);
    
private:
    void removePhysicsBody();
    void addToPhysicsManager();
    void removeFromPhysicsManager();
    Mat4 getParentToWorldTransform() const;
    float getPhysicsRotation(Node *node) const;
    bool isVec3Equal(const Vec3 &v1, const Vec3 &v2) const;
    
private:
    // this physic body of this component
    PhysicsBody *_physicsBody;
    // offset between owner's center point and down left point
    Vec3 _ownerCenterOffset;
    Mat4 _nodeToWorldTransform;
    // offset of owner's center point and anchor point in parent coordinate
    Vec2 _offset;
    float _physicsRotation;
    // the rotation of owner when the component is added to, the value will not change
    float _ownerOriginRotation;
    Vec3 _recordScale;
    Vec3 _scale;
};

/** @} */
/** @} */

NS_CC_END

#endif // CC_USE_PHYSICS
