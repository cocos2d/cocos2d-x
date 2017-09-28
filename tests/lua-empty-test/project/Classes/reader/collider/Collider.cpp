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
#include "Collider.h"

NS_CCR_BEGIN

//
// Implementation of Collider
//

Collider::Collider(cocos2d::Node* target, int targetGroupIndex, const cocos2d::Vec2& offset)
: _offset(offset)
, _AABB(0, 0, 0, 0)
, _targetGroupIndex(targetGroupIndex)
{
    assert(target != nullptr);
    _target = target;
    _target->retain();
}

Collider::~Collider()
{
    _target->release();
}

cocos2d::Mat4 Collider::getNodeToWorldTransformAR() const
{
    auto anchorPointSize = _target->getAnchorPointInPoints();
    auto mat4 = _target->getNodeToWorldTransform();
    mat4.translate(anchorPointSize.x, anchorPointSize.y, 0);
    return mat4;
}

cocos2d::Node* Collider::getTarget() const
{
    return _target;
}

const cocos2d::Rect& Collider::getAABB() const
{
    return _AABB;
}

const std::vector<cocos2d::Vec2>& Collider::getWorldPoints() const
{
    return _worldPoints;
}

int Collider::getTargetGroupIndex() const
{
    return _targetGroupIndex;
}

cocos2d::Vec2 Collider::getOffset() const
{
    return _offset;
}

void Collider::setOffset(const cocos2d::Vec2& offset)
{
    _offset = offset;
}

//
// Implementation of CircleCollider
//

CircleCollider::CircleCollider(cocos2d::Node* target, int targetGroupIndex, const cocos2d::Vec2& offset, float radius)
: creator::Collider(target, targetGroupIndex, offset)
, _radius(radius)
, _worldRadius(radius)
{}

CircleCollider::~CircleCollider()
{}

void CircleCollider::update()
{
    // world position
    auto transform = getNodeToWorldTransformAR();
    _worldPosition = cocos2d::PointApplyTransform(_offset, transform);
    
    // world radius
    transform.m[12] = transform.m[13] = transform.m[14] = 0;
    cocos2d::Vec2 tempVec2(_radius, 0);
    cocos2d::Vec2 tempP = cocos2d::PointApplyTransform(tempVec2, transform);
    _worldRadius = std::sqrt(tempP.x * tempP.x + tempP.y * tempP.y);
    
    // AABB
    _AABB.origin.x = _worldPosition.x - _worldRadius;
    _AABB.origin.y = _worldPosition.y - _worldRadius;
    _AABB.size.width = _worldRadius * 2;
    _AABB.size.height = _worldRadius * 2;
}

float CircleCollider::getRadius() const
{
    return _radius;
}

void CircleCollider::setRadius(float radius)
{
    _radius = radius;
}

const cocos2d::Vec2& CircleCollider::getWorldPosition() const
{
    return _worldPosition;
}

float CircleCollider::getWorldRadius() const
{
    return _worldRadius;
}

//
// Implementation of BoxCollider
//

BoxCollider::BoxCollider(cocos2d::Node* target, int targetGroupIndex, const cocos2d::Vec2& offset, const cocos2d::Size& size)
: creator::Collider(target, targetGroupIndex, offset)
, _size(size)
{
    _worldPoints = {
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0}
    };
}

BoxCollider::~BoxCollider()
{}

void BoxCollider::update()
{
    // world position
    cocos2d::Rect tempRect(_offset.x - _size.width/2,
                           _offset.y - _size.height/2,
                           _size.width,
                           _size.height);
    const auto& transform = getNodeToWorldTransformAR();
    tempRect = cocos2d::RectApplyTransform(tempRect, transform);
    _worldPoints[0] = tempRect.origin;                                                                      // bottom left
    _worldPoints[1] = {tempRect.origin.x, tempRect.origin.y + tempRect.size.height};                        // top left
    _worldPoints[2] = {tempRect.origin.x + tempRect.size.width, tempRect.origin.y + tempRect.size.height};  // top right
    _worldPoints[3] = {tempRect.origin.x + tempRect.size.width, tempRect.origin.y};                         // bottom right
    
    // AABB
    std::vector<float> xs = {_worldPoints[0].x, _worldPoints[1].x, _worldPoints[2].x, _worldPoints[3].x};
    std::vector<float> ys = {_worldPoints[0].y, _worldPoints[1].y, _worldPoints[2].y, _worldPoints[3].y};
    auto minmaxx = std::minmax_element(xs.begin(), xs.end());
    auto minmaxy = std::minmax_element(ys.begin(), ys.end());
    _AABB.origin.x = *minmaxx.first;
    _AABB.origin.y = *minmaxy.first;
    _AABB.size.width = *minmaxx.second - *minmaxx.first;
    _AABB.size.height = *minmaxy.second - *minmaxy.first;
}

cocos2d::Size BoxCollider::getSize() const
{
    return _size;
}

void BoxCollider::setSize(const cocos2d::Size& size)
{
    _size = size;
}

//
// Implementation of PolygonCollider
//

PolygonCollider::PolygonCollider(cocos2d::Node* target, int targetGroupIndex, const cocos2d::Vec2& offset, const std::vector<cocos2d::Vec2>& points)
: creator::Collider(target, targetGroupIndex, offset)
{
    _points = std::move(points);
}

PolygonCollider::~PolygonCollider()
{}

void PolygonCollider::update()
{
    float minx = std::numeric_limits<float>::max();
    float miny = minx;
    float maxx = std::numeric_limits<float>::min();
    float maxy = maxx;
    cocos2d::Vec2 tempVec2;
    const auto& transform = getNodeToWorldTransformAR();
    
    _worldPoints = _points;
    for (size_t i = 0, len = _worldPoints.size(); i < len; ++i)
    {
        tempVec2.x = _points[i].x + _offset.x;
        tempVec2.y = _points[i].y + _offset.y;
        
        auto p = _worldPoints[i] = cocos2d::PointApplyTransform(tempVec2, transform);
        
        if (p.x > maxx) maxx = p.x;
        if (p.x < minx) minx = p.x;
        if (p.y > maxy) maxy = p.y;
        if (p.y < miny) miny = p.y;
    }
    
    _AABB.origin.x = minx;
    _AABB.origin.y = miny;
    _AABB.size.width = maxx - minx;
    _AABB.size.height = maxy - miny;
}

std::vector<cocos2d::Vec2> PolygonCollider::getPoints() const
{
    return _points;
}

void PolygonCollider::setPoints(const std::vector<cocos2d::Vec2>& points)
{
    _points = points;
}

NS_CCR_END
