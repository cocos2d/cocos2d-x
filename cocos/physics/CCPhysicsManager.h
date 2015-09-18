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

#include <vector>
#include <unordered_map>

#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

class ComponentPhysics2d;
class PhysicsWorld;
class Scene;
class Node;

/**
 * @addtogroup physics
 * @{
 * @addtogroup physics_2d
 * @{
 */

/**
 * Now `PhysicsManager` belongs to a `Scene`. `Scene` will create `PhysicsManager` automatically.
 * The reason to design like this are:
 * - PhysicsManager keeps physics world, it is reasonale that a scene has its own physics world.
 *   It is useful that when a scene is active again, you don't have to create physics world and 
 *   do all related things again.
 * - Keep compatibility
 */
class CC_DLL PhysicsManager
{
public:
    
    /// @cond DO_NOT_SHOW
    
    /**
     * Create a PhysicsManager with `Scene`. `Scene` will create it automatically,
     * so don't create it yourself.
     *
     * @scene The scene this `PhysicsManager` belongs to.
     */
    PhysicsManager(Scene *scene);
    /**
     * Destructor.
     */
    ~PhysicsManager();
    
    /**
     * Do physics simulation. It will do the following things:
     * - synchronize Node's status(position, rotation, scale) to corresponding physics body
     * - do physics simulation
     * - synchronize physics body's status(position, rotation) to correspondind Node
     *
     * It is invoked by `Scene`, don't invoke it yourself.
     */
    void update(float dt);
    
    /// @endcond DO_NOT_SHOW
    
    /**
     * Get the physics world.
     *
     * @return Physics world managed by this `PhysicsManager`.
     */
    PhysicsWorld* getPhysicsWorld() const;
    
    /**
     * Add a physics component to be managed by the `PhysicsManager`. Will register physics 
     * component's physics body to physics world managed by this `PhysicsManager`.
     *
     * @param componentPhsics2d The physics component to be managed by this `PhysicsManager`.
     */
    void addPhysicsComponent(ComponentPhysics2d* componentPhsics2d);
    /**
     * Remove a physics component from `PhysiscsManager`. Will remove physics component's physics
     * body from the physics world managed by this `PhysicsManager`.
     */
    void removePhysicsComponent(ComponentPhysics2d* componentPhsics2d);
    
private:
    void beforeSimulation(Node *node);
    void afterSimulation(Node* node);
    void removeElementFromMap(ComponentPhysics2d* component);
private:
    std::vector<ComponentPhysics2d*> _components;
    // record the owners of components for performance
    std::unordered_map<Node*, ComponentPhysics2d*> _owners;
    PhysicsWorld *_physicsWorld;
    Scene *_scene;
};

/** @} */
/** @} */

NS_CC_END

#endif // CC_USE_PHYSICS
