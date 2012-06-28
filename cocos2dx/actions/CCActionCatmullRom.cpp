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
 * Orignal code by Radu Gruian: http://www.codeproject.com/Articles/30838/Overhauser-Catmull-Rom-Splines-for-Camera-Animatio.So
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
CCPointArray* CCPointArray::arrayWithCapacity(unsigned int capacity)
{
    return CCPointArray::create(capacity);
}

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
    m_pControlPoints = new CCArray(capacity);
    
    return true;
}

CCObject* CCPointArray::copyWithZone(cocos2d::CCZone *zone)
{
    CCArray *newArray = (CCArray*)m_pControlPoints->copy();
    CCPointArray *points = CCPointArray::create(10);
    points->retain();
    points->setControlPoints(newArray);
    newArray->release();
    
    return points;
}

CCPointArray::~CCPointArray()
{
    CC_SAFE_RELEASE_NULL(m_pControlPoints);
}

CCPointArray::CCPointArray() :m_pControlPoints(NULL){}

void CCPointArray::addControlPoint(CCPoint controlPoint)
{
    // should create a new object of CCPoint
    // because developer always use this function like this
    // addControlPoint(ccp(x, y))
    // passing controlPoint is a temple object
    // and CCArray::addObject() will retain the passing object, so it 
    // should be an object created in heap
    CCPoint *temp = new CCPoint(controlPoint.x, controlPoint.y);
    m_pControlPoints->addObject(temp);
    temp->release();
}

void CCPointArray::insertControlPoint(CCPoint &controlPoint, unsigned int index)
{
    // should create a new object of CCPoint
    // because developer always use this function like this
    // insertControlPoint(ccp(x, y))
    // passing controlPoint is a temple object
    // and CCArray::insertObject() will retain the passing object, so it 
    // should be an object created in heap
    CCPoint *temp = new CCPoint(controlPoint.x, controlPoint.y);
    m_pControlPoints->insertObject(temp, index);
    temp->release();
}

CCPoint CCPointArray::getControlPointAtIndex(unsigned int index)
{
    index = MIN(m_pControlPoints->count()-1, MAX(index, 0));
    CCPoint point = *((CCPoint*)m_pControlPoints->objectAtIndex(index));
    
    return point;
}

void CCPointArray::replaceControlPoint(cocos2d::CCPoint &controlPoint, unsigned int index)
{
    // should create a new object of CCPoint
    // because developer always use this function like this
    // replaceControlPoint(ccp(x, y))
    // passing controlPoint is a temple object
    // and CCArray::insertObject() will retain the passing object, so it 
    // should be an object created in heap
    CCPoint *temp = new CCPoint(controlPoint.x, controlPoint.y);
    m_pControlPoints->replaceObjectAtIndex(index, temp);
    temp->release();
}

void CCPointArray::removeControlPointAtIndex(unsigned int index)
{
    m_pControlPoints->removeObjectAtIndex(index);
}

unsigned int CCPointArray::count()
{
    return m_pControlPoints->count();
}

CCPointArray* CCPointArray::reverse()
{
    CCArray *newArray = new CCArray(m_pControlPoints->count());
    for (int i = m_pControlPoints->count()-1; i >= 0; --i)
    {
        newArray->addObject(m_pControlPoints->objectAtIndex(i));
    }
    CCPointArray *config = CCPointArray::create(0);
    config->setControlPoints(newArray);
    
    newArray->release();
    
    return config;
}

void CCPointArray::reverseInline()
{
    unsigned int l = m_pControlPoints->count();
    for (unsigned int i = 0; i < l/2; ++i)
    {
        m_pControlPoints->exchangeObjectAtIndex(i, l-i-1);
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
CCCardinalSplineTo* CCCardinalSplineTo::actionWithDuration(float duration, cocos2d::CCPointArray *points, float tension)
{
    return CCCardinalSplineTo::create(duration, points, tension);
}

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
        this->m_fTension = tension;
        
        return true;
    }
    
    return false;
}

CCCardinalSplineTo::~CCCardinalSplineTo()
{
    CC_SAFE_RELEASE_NULL(m_pPoints);
}

CCCardinalSplineTo::CCCardinalSplineTo()
: m_pPoints(NULL)
, m_fTension(0.f)
, m_fDeltaT(0.f)
{
}

void CCCardinalSplineTo::startWithTarget(cocos2d::CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
	
    m_fDeltaT = (float) 1 / m_pPoints->count();
}

CCCardinalSplineTo* CCCardinalSplineTo::copyWithZone(cocos2d::CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCCardinalSplineTo* pRet = NULL;
    if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
    {
        pRet = (CCCardinalSplineTo*)(pZone->m_pCopyObject);
    }
    else
    {
        pRet = new CCCardinalSplineTo();
        pZone = pNewZone = new CCZone(pRet);
    }

    CCActionInterval::copyWithZone(pZone);

    pRet->initWithDuration(this->getDuration(), this->m_pPoints, this->m_fTension);

    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CCCardinalSplineTo::update(float time)
{
    unsigned int p;
    float lt;
	
	// border
    if (time == 1)
    {
        p = m_pPoints->count() - 1;
        lt = 1;
    }
    else 
    {
        p = time / m_fDeltaT;
        lt = (time - m_fDeltaT * (float)p) / m_fDeltaT;
    }
    
	// Interpolate    
    CCPoint pp0 = m_pPoints->getControlPointAtIndex(p-1);
    CCPoint pp1 = m_pPoints->getControlPointAtIndex(p+0);
    CCPoint pp2 = m_pPoints->getControlPointAtIndex(p+1);
    CCPoint pp3 = m_pPoints->getControlPointAtIndex(p+2);
	
    CCPoint newPos = ccCardinalSplineAt(pp0, pp1, pp2, pp3, m_fTension, lt);
	
    this->updatePosition(newPos);
}

void CCCardinalSplineTo::updatePosition(cocos2d::CCPoint &newPos)
{
    m_pTarget->setPosition(newPos);
}

CCActionInterval* CCCardinalSplineTo::reverse()
{
    CCPointArray *pReverse = m_pPoints->reverse();
    
    return CCCardinalSplineTo::create(m_fDuration, pReverse, m_fTension);
}

/* CCCardinalSplineBy
 */

CCCardinalSplineBy* CCCardinalSplineBy::actionWithDuration(float duration, cocos2d::CCPointArray *points, float tension)
{
    return CCCardinalSplineBy::create(duration, points, tension);
}

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

CCCardinalSplineBy::CCCardinalSplineBy() : m_startPosition(0,0)
{
}

void CCCardinalSplineBy::updatePosition(cocos2d::CCPoint &newPos)
{
    m_pTarget->setPosition(ccpAdd(newPos, m_startPosition));
}

CCActionInterval* CCCardinalSplineBy::reverse()
{
    CCPointArray *copyConfig = (CCPointArray*)m_pPoints->copy();
	
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
	
    return CCCardinalSplineBy::create(m_fDuration, pReverse, m_fTension);
}

void CCCardinalSplineBy::startWithTarget(cocos2d::CCNode *pTarget)
{    
    CCCardinalSplineTo::startWithTarget(pTarget);
    m_startPosition = pTarget->getPosition();
}

/* CCCatmullRomTo
 */
CCCatmullRomTo* CCCatmullRomTo::actionWithDuration(float dt, cocos2d::CCPointArray *points)
{
    return CCCatmullRomTo::create(dt, points);
}

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

/* CCCatmullRomBy
 */
CCCatmullRomBy* CCCatmullRomBy::actionWithDuration(float dt, cocos2d::CCPointArray *points)
{
    return CCCatmullRomBy::create(dt, points);
}

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

NS_CC_END;

