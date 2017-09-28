/****************************************************************************
 Copyright (c) 2017 Chukong Technologies Inc.
 
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
#include "ColliderManager.h"

#include "base/CCDirector.h"
#include "base/CCScheduler.h"

NS_CCR_BEGIN

ColliderManager::ColliderManager()
: _debugDrawEnabled(false)
, _AABBDebugDrawEnabled(false)
, _debugDrawNode(nullptr)
{
    _debugDrawNode = cocos2d::DrawNode::create();
    _debugDrawNode->retain();
}

ColliderManager::~ColliderManager()
{
    CC_SAFE_RELEASE_NULL(_debugDrawNode);
}

void ColliderManager::start()
{
    cocos2d::Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(ColliderManager::update, this), this, 0, false, "update");
}

void ColliderManager::update(float dt)
{
    // if collider's target is not a decent of current running scene, then remove it from collider manager
    checkColliders();
    
    if (_colliders.empty())
    {
        cocos2d::Director::getInstance()->getScheduler()->unschedule("update", this);
        return;
    }
    
    for (auto& collider : _colliders)
        collider->update();
    
    for (auto& contract : _contracts)
    {
        auto type = contract->updateState();
        if (Contract::CollisionType::NONE == type)
            continue;
        
        // emit collision event
        for (const auto& e : _collisionCallbacks)
            e.second(type, contract->getCollider1(), contract->getCollider2());
    }
    
    drawColliders();
}

void ColliderManager::enableDebugDraw(bool enabled)
{
    _debugDrawEnabled = enabled;
}

bool ColliderManager::isDebugDrawEnabled() const
{
    return _debugDrawEnabled;
}

void ColliderManager::addCollider(Collider* collider)
{
    const auto& result = std::find(_colliders.begin(), _colliders.end(), collider);
    if (result == _colliders.end())
    {
        for (auto& other : _colliders)
            if (shouldColider(collider, other))
                _contracts.pushBack(new Contract(collider, other));
        
        _colliders.pushBack(collider);
    }
}

void ColliderManager::enableAABBDebugDraw(bool value)
{
    _AABBDebugDrawEnabled = value;
}

bool ColliderManager::isAABBDebugDrawEnabled() const
{
    return _AABBDebugDrawEnabled;
}

void ColliderManager::setCollistionMatrix(const std::vector<std::vector<bool>>& collistionMatrix)
{
    _collisionMatrix = std::move(collistionMatrix);
}

bool ColliderManager::shouldColider(Collider* collider1, Collider* collider2) const
{
    auto target1 = collider1->getTarget();
    auto target2 = collider2->getTarget();
    auto target1GroupIndex = collider1->getTargetGroupIndex();
    auto target2GroupIndex = collider2->getTargetGroupIndex();
    
    return (target1 != target2) &&
           _collisionMatrix[target1GroupIndex][target2GroupIndex];
}

void ColliderManager::checkColliders()
{
    std::vector<Collider*> collidersToRemove;
    
    for (auto& collider : _colliders)
    {
        auto target = collider->getTarget();
        while (target->getParent() != nullptr)
            target = target->getParent();
        
        if (target != cocos2d::Director::getInstance()->getRunningScene())
            collidersToRemove.push_back(collider);
    }
    
    for (auto& collider : collidersToRemove)
        removeCollider(collider);
}

void ColliderManager::removeCollider(creator::Collider *collider)
{
    auto found = std::find(_colliders.begin(), _colliders.end(), collider);
    if (found != _colliders.end())
    {
        _colliders.erase(found);
        
        // don't emit exit event as creator since the collider is not running scene
        for (auto iter = _contracts.begin(), end = _contracts.end(); iter != end;)
        {
            if ((*iter)->getCollider1() == collider || (*iter)->getCollider2() == collider)
                iter = _contracts.erase(iter);
            else
                ++iter;
        }
    }
    else
        assert(false);
}

void ColliderManager::registerCollitionCallback(CollistionCallback callback, const std::string& key)
{
    if (_collisionCallbacks.find(key) != _collisionCallbacks.end())
    {
        cocos2d::log("callback with key:%s already exist", key.c_str());
        return;
    }
    
    _collisionCallbacks[key] = callback;
}
void ColliderManager::unregisterCollisionCallback(const std::string& key)
{
    if (_collisionCallbacks.find(key) != _collisionCallbacks.end())
        _collisionCallbacks.erase(key);
}

void ColliderManager::drawColliders() const
{
    if (!_debugDrawEnabled && !_AABBDebugDrawEnabled)
        return;
    
    _debugDrawNode->clear();
    
    if (_debugDrawNode->getParent() == nullptr)
        cocos2d::Director::getInstance()->getRunningScene()->addChild(_debugDrawNode);
    
    CircleCollider *circleCollider = nullptr;
    for (const auto& collider : _colliders)
    {
        if (_debugDrawEnabled)
        {
            // BoxCollider and PolygonCollider
            const auto& worldPoints = collider->getWorldPoints();
            if (!worldPoints.empty())
            {
                _debugDrawNode->drawPoly(&worldPoints[0], static_cast<unsigned int>(worldPoints.size()), true, cocos2d::Color4F::WHITE);
            }
            else
            {
                // Circle Collider
                circleCollider = dynamic_cast<CircleCollider*>(collider);
                _debugDrawNode->drawCircle(circleCollider->getWorldPosition(),
                                           circleCollider->getWorldRadius(),
                                           M_PI * 2, 200, false, cocos2d::Color4F::WHITE);
            }
        }
        
        if (_AABBDebugDrawEnabled)
        {
            const auto& AABB = collider->getAABB();
            const auto& origin = AABB.origin;
            const auto& size = AABB.size;
            _debugDrawNode->drawLine(origin, cocos2d::Vec2(origin.x + size.width, origin.y), cocos2d::Color4F::BLUE);
            _debugDrawNode->drawLine(cocos2d::Vec2(origin.x + size.width, origin.y), cocos2d::Vec2(origin.x + size.width, origin.y + size.height), cocos2d::Color4F::BLUE);
            _debugDrawNode->drawLine(cocos2d::Vec2(origin.x + size.width, origin.y + size.height), cocos2d::Vec2(origin.x, origin.y + size.height), cocos2d::Color4F::BLUE);
            _debugDrawNode->drawLine(cocos2d::Vec2(origin.x, origin.y + size.height), origin, cocos2d::Color4F::BLUE);
        }
    }
}

NS_CCR_END
