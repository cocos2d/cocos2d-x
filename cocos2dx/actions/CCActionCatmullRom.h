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
 Used by CardinalSplineTo and (By) and CatmullRomTo (and By) actions.
@ingroup Actions
 */
class CC_DLL PointArray : public Object, public Clonable
{
public:
    
    /** creates and initializes a Points array with capacity */
    static PointArray* create(unsigned int capacity);

    virtual ~PointArray();
    PointArray();
    
    /** initializes a Catmull Rom config with a capacity hint */
    bool initWithCapacity(unsigned int capacity);
    
    /** appends a control point */
    void addControlPoint(Point controlPoint);
    
    /** inserts a controlPoint at index */
    void insertControlPoint(Point &controlPoint, unsigned int index);
    
    /** replaces an existing controlPoint at index */
    void replaceControlPoint(Point &controlPoint, unsigned int index);
    
    /** get the value of a controlPoint at a given index */
    Point getControlPointAtIndex(unsigned int index);
    
    /** deletes a control point at a given index */
    void removeControlPointAtIndex(unsigned int index);
    
    /** returns the number of objects of the control point array */
    unsigned int count() const;
    
    /** returns a new copy of the array reversed. User is responsible for releasing this copy */
    PointArray* reverse() const;
    
    /** reverse the current control point array inline, without generating a new one */
    void reverseInline();

    virtual PointArray* clone() const;

    const std::vector<Point*>* getControlPoints();

    void setControlPoints(std::vector<Point*> *controlPoints);
private:
    /** Array that contains the control points */
    std::vector<Point*> *_controlPoints;
};

/** Cardinal Spline path.
 http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline
@ingroup Actions
 */
class CC_DLL CardinalSplineTo : public ActionInterval
{
public:

    /** creates an action with a Cardinal Spline array of points and tension */
    static CardinalSplineTo* create(float duration, PointArray* points, float tension);

    virtual ~CardinalSplineTo();
    CardinalSplineTo();
    
    /** initializes the action with a duration and an array of points */
    bool initWithDuration(float duration, PointArray* points, float tension);
    
    // super virtual functions
	/** returns a new clone of the action */
	virtual CardinalSplineTo *clone() const;

	/** returns a new reversed action */
    virtual CardinalSplineTo* reverse() const;

    virtual CardinalSplineTo* copyWithZone(Zone* pZone);
    virtual void startWithTarget(Node *pTarget);
    virtual void update(float time);

    virtual void updatePosition(Point &newPos);
    
    inline PointArray* getPoints() { return _points; }
    inline void  setPoints(PointArray* points) 
    {
        CC_SAFE_RETAIN(points);
        CC_SAFE_RELEASE(_points);
        _points = points;
    }
    
protected:
    /** Array of control points */
    PointArray *_points;
    float _deltaT;
    float _tension;
    Point	_previousPosition;
    Point	_accumulatedDiff;
};

/** Cardinal Spline path.
 http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline
 @ingroup Actions
 */
class CC_DLL CardinalSplineBy : public CardinalSplineTo 
{
public:
    
    /** creates an action with a Cardinal Spline array of points and tension */
    static CardinalSplineBy* create(float duration, PointArray* points, float tension);

    CardinalSplineBy();
    
    virtual void startWithTarget(Node *pTarget);

    virtual void updatePosition(Point &newPos);

	/** returns a new clone of the action */
	virtual CardinalSplineBy *clone() const;

	/** returns a new reversed action */
    virtual CardinalSplineBy* reverse() const;

protected:
    Point _startPosition;
};

/** An action that moves the target with a CatmullRom curve to a destination point.
 A Catmull Rom is a Cardinal Spline with a tension of 0.5.
 http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull.E2.80.93Rom_spline
 @ingroup Actions
 */
class CC_DLL CatmullRomTo : public CardinalSplineTo
{
public:
    
    /** creates an action with a Cardinal Spline array of points and tension */
    static CatmullRomTo* create(float dt, PointArray* points);

    /** initializes the action with a duration and an array of points */
    bool initWithDuration(float dt, PointArray* points);

	/** returns a new clone of the action */
	virtual CatmullRomTo *clone() const;

	/** returns a reversed copy of the action */
	virtual CatmullRomTo *reverse() const;
};

/** An action that moves the target with a CatmullRom curve by a certain distance.
 A Catmull Rom is a Cardinal Spline with a tension of 0.5.
 http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull.E2.80.93Rom_spline
 @ingroup Actions
 */
class CC_DLL CatmullRomBy : public CardinalSplineBy
{
public:
    
    /** creates an action with a Cardinal Spline array of points and tension */
    static CatmullRomBy* create(float dt, PointArray* points);

    /** initializes the action with a duration and an array of points */
    bool initWithDuration(float dt, PointArray* points);

	/** returns a new clone of the action */
	virtual CatmullRomBy *clone() const;

	/** returns a reversed copy of the action */
	virtual CatmullRomBy *reverse() const;

};

/** Returns the Cardinal Spline position for a given set of control points, tension and time */
extern CC_DLL Point ccCardinalSplineAt(Point &p0, Point &p1, Point &p2, Point &p3, float tension, float t);

// end of actions group
/// @}

NS_CC_END;

#endif // __CCACTION_CATMULLROM_H__
