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

#include "base/ccConfig.h" // to include defination of CC_USE_PHYSICS
#if CC_USE_PHYSICS

#include "physics/CCPhysicsManager.h"
#include "physics/CCComponentPhysics2d.h"
#include "physics/CCPhysicsWorld.h"
#include "2d/CCScene.h"

NS_CC_BEGIN

PhysicsManager::PhysicsManager(Scene *scene)
: _scene(scene)
{
    _physicsWorld = PhysicsWorld::construct();
}

PhysicsManager::~PhysicsManager()
{
    delete _physicsWorld;
}

void PhysicsManager::update(float dt)
{
    // Update physics position, should loop as the same sequence as node tree.
    // ComponentPhysics2d::beforeSimulation() will depend on the sequence.
    beforeSimulation(_scene);
    
    // do simulation
    _physicsWorld->update(dt, false);
    
    // Update physics position, should loop as the same sequence as node tree.
    // ComponentPhysics2d::afterSimulation() will depend on the sequence.
    afterSimulation(_scene);
}

void PhysicsManager::beforeSimulation(Node *node)
{
    auto iter = _owners.find(node);
    if (iter != _owners.end())
    {
        auto component = iter->second;
        component->beforeSimulation();
    }
    
    for (auto child : node->getChildren())
        beforeSimulation(child);
}

void PhysicsManager::afterSimulation(Node *node)
{
    auto iter = _owners.find(node);
    if (iter != _owners.end())
    {
        auto component = iter->second;
        component->afterSimulation();
    }
    
    for (auto child : node->getChildren())
        afterSimulation(child);
}

void PhysicsManager::addPhysicsComponent(ComponentPhysics2d* componentPhsics2d)
{
    // don't add component again
    if (std::find(_components.begin(), _components.end(), componentPhsics2d) != _components.end())
        return;
    
    _components.push_back(componentPhsics2d);
    // Node::getComponent<>() is a time comsuming operation, so record data to avoid invoking it.
    std::pair<Node*, ComponentPhysics2d*> element(componentPhsics2d->getOwner(), componentPhsics2d);
    _owners.insert(element);
    
    if (nullptr != componentPhsics2d->getPhysicsBody())
        _physicsWorld->addBody(componentPhsics2d->getPhysicsBody());
}

void PhysicsManager::removePhysicsComponent(ComponentPhysics2d* componentPhsics2d)
{
    auto iter = std::find(_components.begin(), _components.end(), componentPhsics2d);
    if (iter != _components.end())
    {
        removeElementFromMap(*iter);
        
        _components.erase(iter);
        if (componentPhsics2d->getPhysicsBody())
            _physicsWorld->removeBody(componentPhsics2d->getPhysicsBody());
    }
}

void PhysicsManager::removeElementFromMap(ComponentPhysics2d* component)
{
    for (auto element : _owners)
    {
        if (element.second == component)
        {
            _owners.erase(element.first);
            break;
        }
    }
}

PhysicsWorld* PhysicsManager::getPhysicsWorld() const
{
    return _physicsWorld;
}

NS_CC_END

#endif // CC_USE_PHYSICS
