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

#include "2d/CCNode.h"

#include "Macros.h"

NS_CCR_BEGIN

class Collider : public cocos2d::Ref
{
public:
    virtual void update() = 0;

    const cocos2d::Rect& getAABB() const;
    cocos2d::Node* getTarget() const;
    
protected:
    Collider(cocos2d::Node* target, int targetGroupIndex, const cocos2d::Vec2& offset);
    virtual ~Collider();
    cocos2d::Mat4 getNodeToWorldTransformAR() const;
    
    cocos2d::Node* _target;
    int _targetGroupIndex;
    cocos2d::Vec2 _offset;
    cocos2d::Rect _AABB;
    std::vector<cocos2d::Vec2> _worldPoints;
    
private:
    friend class Contract;
    friend class ColliderManager;
    
    cocos2d::Vec2 getOffset() const;
    void setOffset(const cocos2d::Vec2& offset);
    int getTargetGroupIndex() const;
    const std::vector<cocos2d::Vec2>& getWorldPoints() const;
    
    CREATOR_DISALLOW_COPY_ASSIGN_AND_MOVE(Collider);
};

class CircleCollider : public Collider
{
public:
    virtual void update() override;
    float getRadius() const;
    
private:
    friend class Contract;
    friend class ColliderManager;
    friend class CreatorReader;
    
    CircleCollider(cocos2d::Node* target, int targetGroupIndex, const cocos2d::Vec2& offset, float radius);
    ~CircleCollider();
    
    float getWorldRadius() const;
    const cocos2d::Vec2& getWorldPosition() const;
    void setRadius(float radius);
    
    float _radius;
    float _worldRadius;
    cocos2d::Vec2 _worldPosition;
    
    CREATOR_DISALLOW_COPY_ASSIGN_AND_MOVE(CircleCollider);
};

class BoxCollider : public Collider
{
public:
    virtual void update() override;
    cocos2d::Size getSize() const;
    
private:
    friend class Contract;
    friend class ColliderManager;
    friend class CreatorReader;
    
    BoxCollider(cocos2d::Node* target, int targetGroupIndex, const cocos2d::Vec2& offset, const cocos2d::Size& size);
    ~BoxCollider();
    void setSize(const cocos2d::Size& size);
    
    cocos2d::Size _size;
    
    CREATOR_DISALLOW_COPY_ASSIGN_AND_MOVE(BoxCollider);
};

class PolygonCollider : public Collider
{
public:
    virtual void update() override;
    std::vector<cocos2d::Vec2> getPoints() const;
    
private:
    friend class Contract;
    friend class ColliderManager;
    friend class CreatorReader;
    
    PolygonCollider(cocos2d::Node* target, int targetGroupIndex, const cocos2d::Vec2& offset, const std::vector<cocos2d::Vec2>& points);
    ~PolygonCollider();
    void setPoints(const std::vector<cocos2d::Vec2>& points);
    std::vector<cocos2d::Vec2> _points;
    
    CREATOR_DISALLOW_COPY_ASSIGN_AND_MOVE(PolygonCollider);
};

NS_CCR_END
