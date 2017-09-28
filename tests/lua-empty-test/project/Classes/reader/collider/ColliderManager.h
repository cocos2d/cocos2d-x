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
#pragma once

#include <map>
#include <functional>

#include "2d/CCDrawNode.h"

#include "Macros.h"
#include "Contract.h"
#include "Collider.h"

NS_CCR_BEGIN

class ColliderManager : public cocos2d::Node
{
public:
    typedef std::function<void(Contract::CollisionType, Collider*, Collider*)> CollistionCallback;
    
    void update(float dt);
    void removeCollider(Collider* collider);
    
    void enableDebugDraw(bool enabled);
    bool isDebugDrawEnabled() const;
    
    void enableAABBDebugDraw(bool value);
    bool isAABBDebugDrawEnabled() const;
    

    /** Register/unregister a callback. `key` is used to unregister because can not compare std::function<>.
     */
    void registerCollitionCallback(CollistionCallback callback, const std::string& key);
    void unregisterCollisionCallback(const std::string& key);
    
private:
    friend class CreatorReader;
    
    ColliderManager();
    ~ColliderManager();
    
    // invoked by CreatorReader
    void start();
    void setCollistionMatrix(const std::vector<std::vector<bool>>& collistionMatrix);
    void addCollider(Collider* collider);
    
    bool shouldColider(Collider* collider1, Collider* collider2) const;
    void checkColliders();
    void drawColliders() const;
    
    cocos2d::Vector<Contract*> _contracts;
    cocos2d::Vector<Collider*> _colliders;
    std::vector<std::vector<bool>> _collisionMatrix;
    bool _debugDrawEnabled;
    bool _AABBDebugDrawEnabled;
    
    cocos2d::DrawNode* _debugDrawNode;
    
    std::unordered_map<std::string, CollistionCallback> _collisionCallbacks;
    
    CREATOR_DISALLOW_COPY_ASSIGN_AND_MOVE(ColliderManager);
};

NS_CCR_END
