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
 * Orignal code by Radu Gruian: http://www.codeproject.com/Articles/30838/Overhauser-Catmull-Rom-Splines-for-Camera-Animatio.So
 *
 * Adapted to cocos2d-x by Vit Valentin
 *
 * Adapted from cocos2d-x to cocos2d-iphone by Ricardo Quesada
 */


#ifndef __CCACTION_CATMULLROM_H__
#define __CCACTION_CATMULLROM_H__

#include "CCActionInterval.h"
#include "base_nodes/CCNode.h"
#include "cocoa/CCGeometry.h"

NS_CC_BEGIN;

/**
 * @addtogroup actions
 * @{
 */

/** An Array that contain control points.
 Used by CCCardinalSplineTo and (By) and CCCatmullRomTo (and By) actions.
@ingroup Actions
 */
class CC_DLL CCPointArray : public CCNode
{
public:
    /** creates and initializes a Points array with capacity 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCPointArray* arrayWithCapacity(unsigned int capacity);
    
    /** creates and initializes a Points array with capacity */
    static CCPointArray* create(unsigned int capacity);

    virtual ~CCPointArray();
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
    
    virtual CCObject* copyWithZone(CCZone *zone);
    
    inline CCArray* getControlPoints(){ return m_pControlPoints; }
    inline void setControlPoints(CCArray *controlPoints)
    {
        CC_SAFE_RETAIN(controlPoints);
        CC_SAFE_RELEASE(m_pControlPoints);
        m_pControlPoints = controlPoints;
    }
private:
    /** Array that contains the control points */
    CCArray *m_pControlPoints;
};

/** Cardinal Spline path.
 http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline
@ingroup Actions
 */
class CC_DLL CCCardinalSplineTo : public CCActionInterval
{
public:
    /** creates an action with a Cardinal Spline array of points and tension 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCCardinalSplineTo* actionWithDuration(float duration, CCPointArray* points, float tension);

    /** creates an action with a Cardinal Spline array of points and tension */
    static CCCardinalSplineTo* create(float duration, CCPointArray* points, float tension);

    virtual ~CCCardinalSplineTo();
    CCCardinalSplineTo();
    
    /** initializes the action with a duration and an array of points */
    bool initWithDuration(float duration, CCPointArray* points, float tension);
    
    // super virtual functions
    virtual CCCardinalSplineTo* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
    virtual CCActionInterval* reverse();
    
    virtual void updatePosition(CCPoint &newPos);
    
    inline CCPointArray* getPoints() { return m_pPoints; }
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
};

/** Cardinal Spline path.
 http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline
 @ingroup Actions
 */
class CC_DLL CCCardinalSplineBy : public CCCardinalSplineTo 
{
public:
    /** creates an action with a Cardinal Spline array of points and tension 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCCardinalSplineBy* actionWithDuration(float duration, CCPointArray* points, float tension);
    
    /** creates an action with a Cardinal Spline array of points and tension */
    static CCCardinalSplineBy* create(float duration, CCPointArray* points, float tension);

    CCCardinalSplineBy();
    
    virtual void startWithTarget(CCNode *pTarget);
    virtual CCActionInterval* reverse();
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
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCCatmullRomTo* actionWithDuration(float dt, CCPointArray* points);
    
    /** creates an action with a Cardinal Spline array of points and tension */
    static CCCatmullRomTo* create(float dt, CCPointArray* points);

    /** initializes the action with a duration and an array of points */
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
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static CCCatmullRomBy* actionWithDuration(float dt, CCPointArray* points);
    
    /** creates an action with a Cardinal Spline array of points and tension */
    static CCCatmullRomBy* create(float dt, CCPointArray* points);

    /** initializes the action with a duration and an array of points */
    bool initWithDuration(float dt, CCPointArray* points);
};

/** Returns the Cardinal Spline position for a given set of control points, tension and time */
extern CC_DLL CCPoint ccCardinalSplineAt(CCPoint &p0, CCPoint &p1, CCPoint &p2, CCPoint &p3, float tension, float t);

// end of actions group
/// @}

NS_CC_END;

#endif // __CCACTION_CATMULLROM_H__
