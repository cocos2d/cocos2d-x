/*
 * Copyright (c) 2008 Radu Gruian
 * Copyright (c) 2011 Vit Valentin
 * Copyright (c) 2012 cocos2d-x.org
 * Copyright (c) 2013-2016 Chukong Technologies Inc.
 * Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *
 * Original code by Radu Gruian: http://www.codeproject.com/Articles/30838/Overhauser-Catmull-Rom-Splines-for-Camera-Animatio.So
 *
 * Adapted to cocos2d-x by Vit Valentin
 *
 * Adapted from cocos2d-x to cocos2d-iphone by Ricardo Quesada
 */
#include "base/ccMacros.h"
#include "2d/CCActionCatmullRom.h"
#include "2d/CCNode.h"

#include <iterator>

using namespace std;

NS_CC_BEGIN

/*
 *  Implementation of PointArray
 */

PointArray* PointArray::create(ssize_t capacity)
{
    PointArray* pointArray = new (std::nothrow) PointArray();
    if (pointArray && pointArray->initWithCapacity(capacity))
    {
        pointArray->autorelease();
        return pointArray;
    }

    delete pointArray;
    return nullptr;
}

bool PointArray::initWithCapacity(ssize_t capacity)
{
    _controlPoints.reserve(capacity);
    
    return true;
}

PointArray* PointArray::clone() const
{
    vector<Vec2> newArray = _controlPoints;
    
    PointArray *points = new (std::nothrow) PointArray();
    points->initWithCapacity(10);
    points->setControlPoints(std::move(newArray));

    points->autorelease();
    return points;
}

PointArray::~PointArray()
{
    CCLOGINFO("deallocing PointArray: %p", this);
}

PointArray::PointArray() {}

const std::vector<Vec2>& PointArray::getControlPoints() const
{
    return _controlPoints;
}

void PointArray::setControlPoints(vector<Vec2> controlPoints)
{
    _controlPoints = std::move(controlPoints);
}

void PointArray::addControlPoint(const Vec2& controlPoint)
{    
    _controlPoints.push_back(controlPoint);
}

void PointArray::insertControlPoint(const Vec2& controlPoint, ssize_t index)
{
    _controlPoints.insert(std::next(_controlPoints.begin(), index), controlPoint);
}

const Vec2& PointArray::getControlPointAtIndex(ssize_t index) const
{
    index = MIN(static_cast<ssize_t>(_controlPoints.size())-1, MAX(index, 0));
    return _controlPoints.at(index);
}

void PointArray::replaceControlPoint(const Vec2& controlPoint, ssize_t index)
{
    _controlPoints.at(index) = controlPoint;
}

void PointArray::removeControlPointAtIndex(ssize_t index)
{
    vector<Vec2>::iterator iter = std::next(_controlPoints.begin(), index);
    _controlPoints.erase(iter);
}

ssize_t PointArray::count() const
{
    return _controlPoints.size();
}

PointArray* PointArray::reverse() const
{
    vector<Vec2> newArray;
    newArray.reserve(_controlPoints.size());
    for (auto iter = _controlPoints.rbegin(), iterRend = _controlPoints.rend(); iter != iterRend; ++iter)
    {
        newArray.push_back(*iter);
    }
    PointArray *config = PointArray::create(0);
    config->setControlPoints(std::move(newArray));
    
    return config;
}

void PointArray::reverseInline()
{
    const size_t l = _controlPoints.size();
    Vec2 *p1 = nullptr;
    Vec2 *p2 = nullptr;
    float x, y;
    for (size_t i = 0; i < l/2; ++i)
    {
        p1 = &_controlPoints.at(i);
        p2 = &_controlPoints.at(l-i-1);
        
        x = p1->x;
        y = p1->y;
        
        p1->x = p2->x;
        p1->y = p2->y;
        
        p2->x = x;
        p2->y = y;
    }
}

// CatmullRom Spline formula:
Vec2 ccCardinalSplineAt(const Vec2 &p0, const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, float tension, float t)
{
    float t2 = t * t;
    float t3 = t2 * t;
    
    /*
     * Formula: s(-ttt + 2tt - t)P1 + s(-ttt + tt)P2 + (2ttt - 3tt + 1)P2 + s(ttt - 2tt + t)P3 + (-2ttt + 3tt)P3 + s(ttt - tt)P4
     */
    float s = (1 - tension) / 2;

    float b1 = s * ((-t3 + (2 * t2)) - t);                      // s(-t3 + 2 t2 - t)P1
    float b2 = s * (-t3 + t2) + (2 * t3 - 3 * t2 + 1);          // s(-t3 + t2)P2 + (2 t3 - 3 t2 + 1)P2
    float b3 = s * (t3 - 2 * t2 + t) + (-2 * t3 + 3 * t2);      // s(t3 - 2 t2 + t)P3 + (-2 t3 + 3 t2)P3
    float b4 = s * (t3 - t2);                                   // s(t3 - t2)P4
    
    float x = (p0.x*b1 + p1.x*b2 + p2.x*b3 + p3.x*b4);
    float y = (p0.y*b1 + p1.y*b2 + p2.y*b3 + p3.y*b4);

    return Vec2(x,y);
}

/* Implementation of CardinalSplineTo
 */

CardinalSplineTo* CardinalSplineTo::create(float duration, PointArray *points, float tension)
{
    CardinalSplineTo *ret = new (std::nothrow) CardinalSplineTo();
    if (ret)
    {
        if (ret->initWithDuration(duration, points, tension))
        {
            ret->autorelease();
        }
        else 
        {
            CC_SAFE_RELEASE_NULL(ret);
        }
    }

    return ret;
}

bool CardinalSplineTo::initWithDuration(float duration, PointArray *points, float tension)
{
    CCASSERT(points->count() > 0, "Invalid configuration. It must at least have one control point");

    if (ActionInterval::initWithDuration(duration))
    {
        this->setPoints(points);
        this->_tension = tension;
        
        return true;
    }
    
    return false;
}

CardinalSplineTo::~CardinalSplineTo()
{
    CC_SAFE_RELEASE_NULL(_points);
}

CardinalSplineTo::CardinalSplineTo()
: _points(nullptr)
, _deltaT(0.f)
, _tension(0.f)
{
}

void CardinalSplineTo::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);

//    _deltaT = (float) 1 / _points->count();
    
    // Issue #1441
    _deltaT = (float) 1 / (_points->count() - 1);

    _previousPosition = target->getPosition();
    _accumulatedDiff.setZero();
}

CardinalSplineTo* CardinalSplineTo::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) CardinalSplineTo();
    a->initWithDuration(this->_duration, this->_points->clone(), this->_tension);
    a->autorelease();
    return a;
}

void CardinalSplineTo::update(float time)
{
    ssize_t p;
    float lt;

    // eg.
    // p..p..p..p..p..p..p
    // 1..2..3..4..5..6..7
    // want p to be 1, 2, 3, 4, 5, 6
    if (time == 1)
    {
        p = _points->count() - 1;
        lt = 1;
    }
    else 
    {
        p = time / _deltaT;
        lt = (time - _deltaT * (float)p) / _deltaT;
    }
    
    // Interpolate
    Vec2 pp0 = _points->getControlPointAtIndex(p-1);
    Vec2 pp1 = _points->getControlPointAtIndex(p+0);
    Vec2 pp2 = _points->getControlPointAtIndex(p+1);
    Vec2 pp3 = _points->getControlPointAtIndex(p+2);

    Vec2 newPos = ccCardinalSplineAt(pp0, pp1, pp2, pp3, _tension, lt);

#if CC_ENABLE_STACKABLE_ACTIONS
    // Support for stacked actions
    Node *node = _target;
    Vec2 diff = node->getPosition() - _previousPosition;
    if( diff.x !=0 || diff.y != 0 )
    {
        _accumulatedDiff = _accumulatedDiff + diff;
        newPos = newPos + _accumulatedDiff;
    }
#endif
    
    this->updatePosition(newPos);
}

void CardinalSplineTo::updatePosition(const Vec2 &newPos)
{
    _target->setPosition(newPos);
    _previousPosition = newPos;
}

CardinalSplineTo* CardinalSplineTo::reverse() const
{
    PointArray *pReverse = _points->reverse();
    
    return CardinalSplineTo::create(_duration, pReverse, _tension);
}

/* CardinalSplineBy
 */

CardinalSplineBy* CardinalSplineBy::create(float duration, PointArray *points, float tension)
{
    CardinalSplineBy *ret = new (std::nothrow) CardinalSplineBy();
    if (ret)
    {
        if (ret->initWithDuration(duration, points, tension))
        {
            ret->autorelease();
        }
        else 
        {
            CC_SAFE_RELEASE_NULL(ret);
        }
    }

    return ret;
}

CardinalSplineBy::CardinalSplineBy() : _startPosition(0,0)
{
}

void CardinalSplineBy::updatePosition(const Vec2 &newPos)
{
    Vec2 p = newPos + _startPosition;
    _target->setPosition(p);
    _previousPosition = p;
}

CardinalSplineBy* CardinalSplineBy::reverse() const
{
    PointArray *copyConfig = _points->clone();

    //
    // convert "absolutes" to "diffs"
    //
    Vec2 p = copyConfig->getControlPointAtIndex(0);
    for (ssize_t i = 1; i < copyConfig->count(); ++i)
    {
        Vec2 current = copyConfig->getControlPointAtIndex(i);
        Vec2 diff = current - p;
        copyConfig->replaceControlPoint(diff, i);
        
        p = current;
    }

    // convert to "diffs" to "reverse absolute"

    PointArray *pReverse = copyConfig->reverse();

    // 1st element (which should be 0,0) should be here too
    
    p = pReverse->getControlPointAtIndex(pReverse->count()-1);
    pReverse->removeControlPointAtIndex(pReverse->count()-1);
    
    p = -p;
    pReverse->insertControlPoint(p, 0);
    
    for (ssize_t i = 1; i < pReverse->count(); ++i)
    {
        Vec2 current = pReverse->getControlPointAtIndex(i);
        current = -current;
        Vec2 abs = current + p;
        pReverse->replaceControlPoint(abs, i);
        
        p = abs;
    }

    return CardinalSplineBy::create(_duration, pReverse, _tension);
}

void CardinalSplineBy::startWithTarget(Node *target)
{    
    CardinalSplineTo::startWithTarget(target);
    _startPosition = target->getPosition();
}

CardinalSplineBy* CardinalSplineBy::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) CardinalSplineBy();
    a->initWithDuration(this->_duration, this->_points->clone(), this->_tension);
    a->autorelease();
    return a;
}

/* CatmullRomTo
 */

CatmullRomTo* CatmullRomTo::create(float dt, PointArray *points)
{
    CatmullRomTo *ret = new (std::nothrow) CatmullRomTo();
    if (ret)
    {
        if (ret->initWithDuration(dt, points))
        {
            ret->autorelease();
        }
        else 
        {
            CC_SAFE_RELEASE_NULL(ret);
        }
    }

    return ret;
}

bool CatmullRomTo::initWithDuration(float dt, PointArray *points)
{
    if (CardinalSplineTo::initWithDuration(dt, points, 0.5f))
    {
        return true;
    }
    
    return false;
}

CatmullRomTo* CatmullRomTo::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) CatmullRomTo();
    a->initWithDuration(this->_duration, this->_points->clone());
    a->autorelease();
    return a;
}

CatmullRomTo* CatmullRomTo::reverse() const
{
    PointArray *reverse = _points->reverse();
    return CatmullRomTo::create(_duration, reverse);
}


/* CatmullRomBy
 */

CatmullRomBy* CatmullRomBy::create(float dt, PointArray *points)
{
    CatmullRomBy *ret = new (std::nothrow) CatmullRomBy();
    if (ret)
    {
        if (ret->initWithDuration(dt, points))
        {
            ret->autorelease();
        }
        else 
        {
            CC_SAFE_RELEASE_NULL(ret);
        }
    }

    return ret;
}

bool CatmullRomBy::initWithDuration(float dt, PointArray *points)
{
    if (CardinalSplineTo::initWithDuration(dt, points, 0.5f))
    {
        return true;
    }
    
    return false;
}

CatmullRomBy* CatmullRomBy::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) CatmullRomBy();
    a->initWithDuration(this->_duration, this->_points->clone());
    a->autorelease();
    return a;
}

CatmullRomBy* CatmullRomBy::reverse() const
{
    PointArray *copyConfig = _points->clone();

    //
    // convert "absolutes" to "diffs"
    //
    Vec2 p = copyConfig->getControlPointAtIndex(0);
    for (ssize_t i = 1; i < copyConfig->count(); ++i)
    {
        Vec2 current = copyConfig->getControlPointAtIndex(i);
        Vec2 diff = current - p;
        copyConfig->replaceControlPoint(diff, i);

        p = current;
    }

    // convert to "diffs" to "reverse absolute"

    PointArray *reverse = copyConfig->reverse();

    // 1st element (which should be 0,0) should be here too

    p = reverse->getControlPointAtIndex(reverse->count()-1);
    reverse->removeControlPointAtIndex(reverse->count()-1);

    p = -p;
    reverse->insertControlPoint(p, 0);

    for (ssize_t i = 1; i < reverse->count(); ++i)
    {
        Vec2 current = reverse->getControlPointAtIndex(i);
        current = -current;
        Vec2 abs = current + p;
        reverse->replaceControlPoint(abs, i);

        p = abs;
    }

    return CatmullRomBy::create(_duration, reverse);
}

NS_CC_END
