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
    Collider(cocos2d::Node* target, int targetGroupIndex, const cocos2d::Vec2& offset);
    ~Collider();
    
    virtual void update() = 0;
    
    const std::vector<cocos2d::Vec2>& getWorldPoints() const;
    const cocos2d::Rect& getAABB() const;
    cocos2d::Node* getTarget() const;
    int getTargetGroupIndex() const;
    cocos2d::Vec2 getOffset() const;
    void setOffset(const cocos2d::Vec2& offset);
    
protected:
    cocos2d::Mat4 getNodeToWorldTransformAR() const;
    
    cocos2d::Node* _target;
    int _targetGroupIndex;
    cocos2d::Vec2 _offset;
    cocos2d::Rect _AABB;
    std::vector<cocos2d::Vec2> _worldPoints;
};

class CircleCollider : public Collider
{
public:
    CircleCollider(cocos2d::Node* target, int targetGroupIndex, const cocos2d::Vec2& offset, float radius);
    
    virtual void update() override;
    
    float getRadius() const;
    void setRadius(float radius);
    float getWorldRadius() const;
    const cocos2d::Vec2& getWorldPosition() const;
private:
    float _radius;
    float _worldRadius;
    cocos2d::Vec2 _worldPosition;
};

class BoxCollider : public Collider
{
public:
    BoxCollider(cocos2d::Node* target, int targetGroupIndex, const cocos2d::Vec2& offset, const cocos2d::Size& size);
    
    virtual void update() override;
    
    cocos2d::Size getSize() const;
    void setSize(const cocos2d::Size& size);
private:
    cocos2d::Size _size;
};

class PolygonCollider : public Collider
{
public:
    PolygonCollider(cocos2d::Node* target, int targetGroupIndex, const cocos2d::Vec2& offset, const std::vector<cocos2d::Vec2>& points);
    
    virtual void update() override;
    
    std::vector<cocos2d::Vec2> getPoints() const;
    void setPoints(const std::vector<cocos2d::Vec2>& points);
private:
    std::vector<cocos2d::Vec2> _points;
};

NS_CCR_END
