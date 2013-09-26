/*
 * Copyright (c) 2012 cocos2d-x.org
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


#ifndef __CCACTION_CATMULLROM_H__
#define __CCACTION_CATMULLROM_H__

#include <vector>

#include "CCActionInterval.h"
#include "base_nodes/CCNode.h"
#include "cocoa/CCGeometry.h"

NS_CC_BEGIN;

/**
 * @addtogroup actions
 * @{
 */

/** An Array that contain control points.
 * Used by CCCardinalSplineTo and (By) and CCCatmullRomTo (and By) actions.
 * @ingroup Actions
 * @js NA
 */
class CC_DLL CCPointArray : public CCObject
{
public:
    
    /** creates and initializes a Points array with capacity 
     * @lua NA
     */
    static CCPointArray* create(unsigned int capacity);
    /**
     * @lua NA
     */
    virtual ~CCPointArray();
    /**
     * @lua NA
     */
    CCPointArray();
    
    /** initializes a Catmull Rom config with a capacity hint */
    bool initWithCapacity(unsigned int capacity);
    
    /** appends a control point */
    void addControlPoint(CCPoint controlPoint);
    
    /** inserts a controlPoint at index */
    void insertControlPoint(CCPoint &controlPoint, unsigned int index);
    
    /** replaces an existing controlPoint at index */
    void replaceControlPoint(CCPoint &controlPoint, unsigned int index);
    
    /** get the value of a controlPoint at a given index */
    CCPoint getControlPointAtIndex(unsigned int index);
    
    /** deletes a control point at a given index */
    void removeControlPointAtIndex(unsigned int index);
    
    /** returns the number of objects of the control point array */
    unsigned int count();
    
    /** returns a new copy of the array reversed. User is responsible for releasing this copy */
    CCPointArray* reverse();
    
    /** reverse the current control point array inline, without generating a new one */
    void reverseInline();
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone *zone);
    
    const std::vector<CCPoint*>* getControlPoints();

    void setControlPoints(std::vector<CCPoint*> *controlPoints);
private:
    /** Array that contains the control points */
    std::vector<CCPoint*> *m_pControlPoints;
};

/** Cardinal Spline path.
 http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline
@ingroup Actions
 */
class CC_DLL CCCardinalSplineTo : public CCActionInterval
{
public:

    /** creates an action with a Cardinal Spline array of points and tension 
     *  @code
     *  when thie function bound to js,the input params are changed
     *  js:var create(var duration,var pointTable,var tension)
     *  @endcode
     */
    static CCCardinalSplineTo* create(float duration, CCPointArray* points, float tension);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~CCCardinalSplineTo();
    /**
     *  @js ctor
     *  @lua NA
     */
    CCCardinalSplineTo();
    
    /** initializes the action with a duration and an array of points 
     *  @lua NA
     */
    bool initWithDuration(float duration, CCPointArray* points, float tension);
    
    // super virtual functions
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCCardinalSplineTo* copyWithZone(CCZone* pZone);
    /**
     *  @lua NA
     */
    virtual void startWithTarget(CCNode *pTarget);
    /**
     *  @lua NA
     */
    virtual void update(float time);
    virtual CCActionInterval* reverse();
    /**
     *  @lua NA
     */
    virtual void updatePosition(CCPoint &newPos);
    
    inline CCPointArray* getPoints() { return m_pPoints; }
    /**
     *  @js NA
     */
    inline void  setPoints(CCPointArray* points)
    {
        CC_SAFE_RETAIN(points);
        CC_SAFE_RELEASE(m_pPoints);
        m_pPoints = points;
    }
    
protected:
    /** Array of control points */
    CCPointArray *m_pPoints;
    float m_fDeltaT;
    float m_fTension;
    CCPoint	m_previousPosition;
    CCPoint	m_accumulatedDiff;
};

/** Cardinal Spline path.
 http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline
 @ingroup Actions
 */
class CC_DLL CCCardinalSplineBy : public CCCardinalSplineTo 
{
public:
    
    /** creates an action with a Cardinal Spline array of points and tension 
     *  @code
     *  when thie function bound to js,the input params are changed
     *  js:var create(var duration,var pointTable,var tension)
     *  @endcode
     */
    static CCCardinalSplineBy* create(float duration, CCPointArray* points, float tension);
    /**
     *  @js NA
     *  @lua NA
     */
    CCCardinalSplineBy();
    /**
     *  @lua NA
     */
    virtual void startWithTarget(CCNode *pTarget);
    virtual CCActionInterval* reverse();
    /**
     *  @lua NA
     */
    virtual void updatePosition(CCPoint &newPos);
protected:
    CCPoint m_startPosition;
};

/** An action that moves the target with a CatmullRom curve to a destination point.
 A Catmull Rom is a Cardinal Spline with a tension of 0.5.
 http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull.E2.80.93Rom_spline
 @ingroup Actions
 */
class CC_DLL CCCatmullRomTo : public CCCardinalSplineTo
{
public:
    
    /** creates an action with a Cardinal Spline array of points and tension 
     *  @code
     *  when this function bound to js,the input params are changed
     *  js:var create(var dt,var pointTable)
     *  @endcode
     */
    static CCCatmullRomTo* create(float dt, CCPointArray* points);

    /** initializes the action with a duration and an array of points 
     *  @js NA
     *  @lua NA
     */
    bool initWithDuration(float dt, CCPointArray* points);
};

/** An action that moves the target with a CatmullRom curve by a certain distance.
 A Catmull Rom is a Cardinal Spline with a tension of 0.5.
 http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull.E2.80.93Rom_spline
 @ingroup Actions
 */
class CC_DLL CCCatmullRomBy : public CCCardinalSplineBy
{
public:
    
    /** creates an action with a Cardinal Spline array of points and tension 
     *  @code
     *  when this function bound to js,the input params are changed
     *  js:var create(var dt,var pointTable)
     *  @endcode
     */
    static CCCatmullRomBy* create(float dt, CCPointArray* points);

    /** initializes the action with a duration and an array of points 
     *  @js NA
     *  @lua NA
     */
    bool initWithDuration(float dt, CCPointArray* points);
};

/** Returns the Cardinal Spline position for a given set of control points, tension and time */
extern CC_DLL CCPoint ccCardinalSplineAt(CCPoint &p0, CCPoint &p1, CCPoint &p2, CCPoint &p3, float tension, float t);

// end of actions group
/// @}

NS_CC_END;

#endif // __CCACTION_CATMULLROM_H__
