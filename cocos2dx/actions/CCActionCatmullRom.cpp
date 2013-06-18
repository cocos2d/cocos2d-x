/*
 * Copyright (c) 2010-2012 cocos2d-x.org
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2008 Radu Gruian
 *
 * Copyright (c) 2011 Vit Valentin
 *
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
#include "ccMacros.h"
#include "support/CCPointExtension.h"
#include "CCActionCatmullRom.h"
#include "cocoa/CCZone.h"

using namespace std;

NS_CC_BEGIN;

/*
 *  Implementation of CCPointArray
 */

CCPointArray* CCPointArray::create(unsigned int capacity)
{
    CCPointArray* ret = new CCPointArray();
    if (ret)
    {
        if (ret->initWithCapacity(capacity))
        {
            ret->autorelease();
        }
        else 
        {
            delete ret;
            ret = NULL;
        }
    }

    return ret;
}


bool CCPointArray::initWithCapacity(unsigned int capacity)
{
    _controlPoints = new vector<CCPoint*>();
    
    return true;
}

CCObject* CCPointArray::copyWithZone(cocos2d::CCZone *zone)
{
    vector<CCPoint*> *newArray = new vector<CCPoint*>();
    vector<CCPoint*>::iterator iter;
    for (iter = _controlPoints->begin(); iter != _controlPoints->end(); ++iter)
    {
        newArray->push_back(new CCPoint((*iter)->x, (*iter)->y));
    }
    
    CCPointArray *points = new CCPointArray();
    points->initWithCapacity(10);
    points->setControlPoints(newArray);
    
    return points;
}

CCPointArray::~CCPointArray()
{
    vector<CCPoint*>::iterator iter;
    for (iter = _controlPoints->begin(); iter != _controlPoints->end(); ++iter)
    {
        delete *iter;
    }
    delete _controlPoints;
}

CCPointArray::CCPointArray() :_controlPoints(NULL){}

const std::vector<CCPoint*>* CCPointArray::getControlPoints()
{
    return _controlPoints;
}

void CCPointArray::setControlPoints(vector<CCPoint*> *controlPoints)
{
    CCAssert(controlPoints != NULL, "control points should not be NULL");
    
    // delete old points
    vector<CCPoint*>::iterator iter;
    for (iter = _controlPoints->begin(); iter != _controlPoints->end(); ++iter)
    {
        delete *iter;
    }
    delete _controlPoints;
    
    _controlPoints = controlPoints;
}

void CCPointArray::addControlPoint(CCPoint controlPoint)
{    
    _controlPoints->push_back(new CCPoint(controlPoint.x, controlPoint.y));
}

void CCPointArray::insertControlPoint(CCPoint &controlPoint, unsigned int index)
{
    CCPoint *temp = new CCPoint(controlPoint.x, controlPoint.y);
    _controlPoints->insert(_controlPoints->begin() + index, temp);
}

CCPoint CCPointArray::getControlPointAtIndex(unsigned int index)
{
    index = MIN(_controlPoints->size()-1, MAX(index, 0));
    return *(_controlPoints->at(index));
}

void CCPointArray::replaceControlPoint(cocos2d::CCPoint &controlPoint, unsigned int index)
{

    CCPoint *temp = _controlPoints->at(index);
    temp->x = controlPoint.x;
    temp->y = controlPoint.y;
}

void CCPointArray::removeControlPointAtIndex(unsigned int index)
{
    vector<CCPoint*>::iterator iter = _controlPoints->begin() + index;
    CCPoint* pRemovedPoint = *iter;
    _controlPoints->erase(iter);
    delete pRemovedPoint;
}

unsigned int CCPointArray::count()
{
    return _controlPoints->size();
}

CCPointArray* CCPointArray::reverse()
{
    vector<CCPoint*> *newArray = new vector<CCPoint*>();
    vector<CCPoint*>::reverse_iterator iter;
    CCPoint *point = NULL;
    for (iter = _controlPoints->rbegin(); iter != _controlPoints->rend(); ++iter)
    {
        point = *iter;
        newArray->push_back(new CCPoint(point->x, point->y));
    }
    CCPointArray *config = CCPointArray::create(0);
    config->setControlPoints(newArray);
    
    return config;
}

void CCPointArray::reverseInline()
{
    unsigned int l = _controlPoints->size();
    CCPoint *p1 = NULL;
    CCPoint *p2 = NULL;
    int x, y;
    for (unsigned int i = 0; i < l/2; ++i)
    {
        p1 = _controlPoints->at(i);
        p2 = _controlPoints->at(l-i-1);
        
        x = p1->x;
        y = p1->y;
        
        p1->x = p2->x;
        p1->y = p2->y;
        
        p2->x = x;
        p2->y = y;
    }
}

// CatmullRom Spline formula:
CCPoint ccCardinalSplineAt(CCPoint &p0, CCPoint &p1, CCPoint &p2, CCPoint &p3, float tension, float t)
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
	
	return ccp(x,y);
}

/* Implementation of CCCardinalSplineTo
 */

CCCardinalSplineTo* CCCardinalSplineTo::create(float duration, cocos2d::CCPointArray *points, float tension)
{
    CCCardinalSplineTo *ret = new CCCardinalSplineTo();
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

bool CCCardinalSplineTo::initWithDuration(float duration, cocos2d::CCPointArray *points, float tension)
{
    CCAssert(points->count() > 0, "Invalid configuration. It must at least have one control point");

    if (CCActionInterval::initWithDuration(duration))
    {
        this->setPoints(points);
        this->_tension = tension;
        
        return true;
    }
    
    return false;
}

CCCardinalSplineTo::~CCCardinalSplineTo()
{
    CC_SAFE_RELEASE_NULL(_points);
}

CCCardinalSplineTo::CCCardinalSplineTo()
: _points(NULL)
, _deltaT(0.f)
, _tension(0.f)
{
}

void CCCardinalSplineTo::startWithTarget(cocos2d::CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
	
//    _deltaT = (float) 1 / _points->count();
    
    // Issue #1441
    _deltaT = (float) 1 / (_points->count() - 1);

    _previousPosition = pTarget->getPosition();
    _accumulatedDiff = CCPointZero;
}

CCCardinalSplineTo* CCCardinalSplineTo::clone() const
{
	auto a = new CCCardinalSplineTo(*this);
	a->initWithDuration(this->_duration, this->_points, this->_tension);
	a->autorelease();
	return a;
}

CCCardinalSplineTo* CCCardinalSplineTo::copyWithZone(cocos2d::CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCCardinalSplineTo* pRet = NULL;
    if(pZone && pZone->_copyObject) //in case of being called at sub class
    {
        pRet = (CCCardinalSplineTo*)(pZone->_copyObject);
    }
    else
    {
        pRet = new CCCardinalSplineTo();
        pZone = pNewZone = new CCZone(pRet);
    }

    CCActionInterval::copyWithZone(pZone);

    pRet->initWithDuration(this->getDuration(), this->_points, this->_tension);

    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CCCardinalSplineTo::update(float time)
{
    unsigned int p;
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
    CCPoint pp0 = _points->getControlPointAtIndex(p-1);
    CCPoint pp1 = _points->getControlPointAtIndex(p+0);
    CCPoint pp2 = _points->getControlPointAtIndex(p+1);
    CCPoint pp3 = _points->getControlPointAtIndex(p+2);
	
    CCPoint newPos = ccCardinalSplineAt(pp0, pp1, pp2, pp3, _tension, lt);
	
#if CC_ENABLE_STACKABLE_ACTIONS
    // Support for stacked actions
    CCNode *node = _target;
    CCPoint diff = ccpSub( node->getPosition(), _previousPosition);
    if( diff.x !=0 || diff.y != 0 ) {
        _accumulatedDiff = ccpAdd( _accumulatedDiff, diff);
        newPos = ccpAdd( newPos, _accumulatedDiff);
    }
#endif
    
    this->updatePosition(newPos);
}

void CCCardinalSplineTo::updatePosition(cocos2d::CCPoint &newPos)
{
    _target->setPosition(newPos);
    _previousPosition = newPos;
}

CCCardinalSplineTo* CCCardinalSplineTo::reverse() const
{
    CCPointArray *pReverse = _points->reverse();
    
    return CCCardinalSplineTo::create(_duration, pReverse, _tension);
}

/* CCCardinalSplineBy
 */

CCCardinalSplineBy* CCCardinalSplineBy::create(float duration, cocos2d::CCPointArray *points, float tension)
{
    CCCardinalSplineBy *ret = new CCCardinalSplineBy();
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

CCCardinalSplineBy::CCCardinalSplineBy() : _startPosition(0,0)
{
}

void CCCardinalSplineBy::updatePosition(cocos2d::CCPoint &newPos)
{
    CCPoint p = ccpAdd(newPos, _startPosition);
    _target->setPosition(p);
    _previousPosition = p;
}

CCCardinalSplineBy* CCCardinalSplineBy::reverse() const
{
    CCPointArray *copyConfig = (CCPointArray*)_points->copy();
	
	//
	// convert "absolutes" to "diffs"
	//
    CCPoint p = copyConfig->getControlPointAtIndex(0);
    for (unsigned int i = 1; i < copyConfig->count(); ++i)
    {
        CCPoint current = copyConfig->getControlPointAtIndex(i);
        CCPoint diff = ccpSub(current, p);
        copyConfig->replaceControlPoint(diff, i);
        
        p = current;
    }
	
	
	// convert to "diffs" to "reverse absolute"
	
    CCPointArray *pReverse = copyConfig->reverse();
    copyConfig->release();
	
	// 1st element (which should be 0,0) should be here too
    
    p = pReverse->getControlPointAtIndex(pReverse->count()-1);
    pReverse->removeControlPointAtIndex(pReverse->count()-1);
    
    p = ccpNeg(p);
    pReverse->insertControlPoint(p, 0);
    
    for (unsigned int i = 1; i < pReverse->count(); ++i)
    {
        CCPoint current = pReverse->getControlPointAtIndex(i);
        current = ccpNeg(current);
        CCPoint abs = ccpAdd(current, p);
        pReverse->replaceControlPoint(abs, i);
        
        p = abs;
    }
	
    return CCCardinalSplineBy::create(_duration, pReverse, _tension);
}

void CCCardinalSplineBy::startWithTarget(cocos2d::CCNode *pTarget)
{    
    CCCardinalSplineTo::startWithTarget(pTarget);
    _startPosition = pTarget->getPosition();
}

CCCardinalSplineBy* CCCardinalSplineBy::clone() const
{
	auto a = new CCCardinalSplineBy(*this);
	a->initWithDuration(this->_duration, (CCPointArray*)this->_points->copy()->autorelease(), this->_tension);
	a->autorelease();
	return a;
}

/* CCCatmullRomTo
 */

CCCatmullRomTo* CCCatmullRomTo::create(float dt, cocos2d::CCPointArray *points)
{
    CCCatmullRomTo *ret = new CCCatmullRomTo();
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

bool CCCatmullRomTo::initWithDuration(float dt, cocos2d::CCPointArray *points)
{
    if (CCCardinalSplineTo::initWithDuration(dt, points, 0.5f))
    {
        return true;
    }
    
    return false;
}

CCCatmullRomTo* CCCatmullRomTo::clone() const
{
	auto a = new CCCatmullRomTo(*this);
	a->initWithDuration(this->_duration, (CCPointArray*)this->_points->copy()->autorelease());
	a->autorelease();
	return a;
}


/* CCCatmullRomBy
 */

CCCatmullRomBy* CCCatmullRomBy::create(float dt, cocos2d::CCPointArray *points)
{
    CCCatmullRomBy *ret = new CCCatmullRomBy();
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

bool CCCatmullRomBy::initWithDuration(float dt, cocos2d::CCPointArray *points)
{
    if (CCCardinalSplineTo::initWithDuration(dt, points, 0.5f))
    {
        return true;
    }
    
    return false;
}

CCCatmullRomBy* CCCatmullRomBy::clone() const
{
	auto a = new CCCatmullRomBy(*this);
	a->initWithDuration(this->_duration, (CCPointArray*)this->_points->copy()->autorelease());
	a->autorelease();
	return a;
}

NS_CC_END;

