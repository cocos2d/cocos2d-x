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
#include "Contract.h"
#include "Intersection.h"

NS_CCR_BEGIN

Contract::Contract(Collider* collider1, Collider* collider2)
: _collider1(collider1)
, _collider2(collider2)
, _isPolygonCircle(false)
, _isCircleCircle(false)
, _isPolygonPolygon(false)
{
    bool isCollider1Polygon = Contract::isBoxCollider(_collider1) || Contract::isPolygonCollider(_collider1);
    bool isCollider2Polygon = Contract::isBoxCollider(_collider2) || Contract::isPolygonCollider(_collider2);
    bool isCollder1Circle = Contract::isCircleCollider(_collider1);
    bool isCollider2Circle = Contract::isCircleCollider(_collider2);
    
    if (isCollider1Polygon && isCollider2Polygon)
        _isPolygonPolygon = true;
    else if (isCollder1Circle && isCollider2Circle)
        _isCircleCircle = true;
    else if (isCollider1Polygon && isCollider2Circle)
        _isPolygonCircle = true;
    else if (isCollder1Circle && isCollider2Polygon)
    {
        _isPolygonCircle = true;
        _collider1 = collider2;
        _collider2 = collider1;
    }
    else
        assert(false);
    
    CC_SAFE_RETAIN(_collider1);
    CC_SAFE_RETAIN(_collider2);
}

Contract::~Contract()
{
    CC_SAFE_RELEASE_NULL(_collider1);
    CC_SAFE_RELEASE_NULL(_collider2);
}

Contract::CollisionType Contract::updateState()
{
    auto result = test();
    
    auto type = CollisionType::NONE;
    if (result && !_touching)
    {
        _touching = true;
        type = CollisionType::ENTER;
    }
    else if (result && _touching)
    {
        type = CollisionType::STAY;
    }
    else if (!result && _touching)
    {
        _touching = false;
        type = CollisionType::EXIT;
    }
    
    return type;
}

bool Contract::test() const
{
    if (!_collider1->getAABB().intersectsRect(_collider2->getAABB()))
        return false;
    
    if (_isPolygonPolygon)
        return Intersection::polygonPolygon(_collider1->getWorldPoints(), _collider2->getWorldPoints());
    
    if (_isCircleCircle)
    {
        const auto& p1= dynamic_cast<CircleCollider*>(_collider1);
        const auto& p2 = dynamic_cast<CircleCollider*>(_collider2);
        return Intersection::circleCircle(p1->getWorldPosition(), p1->getRadius(), p2->getWorldPosition(), p2->getRadius());
    }
    
    if (_isPolygonCircle)
    {
        const auto& p2 = dynamic_cast<CircleCollider*>(_collider2);
        return Intersection::polygonCircle(_collider1->getWorldPoints(), p2->getWorldPosition(), p2->getRadius());
    }
    
    return false;
}

bool Contract::isBoxCollider(Collider* collider)
{
    return dynamic_cast<BoxCollider*>(collider) != nullptr;
}

bool Contract::isPolygonCollider(Collider* collider)
{
    return dynamic_cast<PolygonCollider*>(collider) != nullptr;
}

bool Contract::isCircleCollider(Collider* collider)
{
    return dynamic_cast<CircleCollider*>(collider) != nullptr;
}

Collider* Contract::getCollider1() const
{
    return _collider1;
}

Collider* Contract::getCollider2() const
{
    return _collider2;
}

NS_CCR_END
