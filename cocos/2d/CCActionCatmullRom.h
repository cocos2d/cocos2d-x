/*
 * Copyright (c) 2008 Radu Gruian
 * Copyright (c) 2011 Vit Valentin
 * Copyright (c) 2012 cocos2d-x.org
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
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
#include "CCNode.h"
#include "CCGeometry.h"

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
    
    /** creates and initializes a Points array with capacity 
     * @js NA
     */
    static PointArray* create(ssize_t capacity);
    
    /**
     * @js NA
     * @lua NA
     */
    virtual ~PointArray();
    /**
     * @js NA
     * @lua NA
     */
    PointArray();
    
    /** initializes a Catmull Rom config with a capacity hint 
     * @js NA
     */
    bool initWithCapacity(ssize_t capacity);
    
    /** appends a control point 
     * @js NA
     */
    void addControlPoint(Point controlPoint);
    
    /** inserts a controlPoint at index 
     * @js NA
     */
    void insertControlPoint(Point &controlPoint, ssize_t index);
    
    /** replaces an existing controlPoint at index 
     * @js NA
     */
    void replaceControlPoint(Point &controlPoint, ssize_t index);
    
    /** get the value of a controlPoint at a given index 
     * @js NA
     */
    Point getControlPointAtIndex(ssize_t index);
    
    /** deletes a control point at a given index 
     * @js NA
     */
    void removeControlPointAtIndex(ssize_t index);
    
    /** returns the number of objects of the control point array 
     * @js NA
     */
    ssize_t count() const;
    
    /** returns a new copy of the array reversed. User is responsible for releasing this copy 
     * @js NA
     */
    PointArray* reverse() const;
    
    /** reverse the current control point array inline, without generating a new one 
     * @js NA
     */
    void reverseInline();
    /**
     * @js NA
     * @lua NA
     */
    virtual PointArray* clone() const;
    /**
     * @js NA
     */
    const std::vector<Point*>* getControlPoints() const;
    /**
     * @js NA
     */
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

    /** creates an action with a Cardinal Spline array of points and tension 
     * @code
     * when this function bound to js or lua,the input params are changed
     * in js: var create(var t,var table)
     * in lua: lcaol create(local t, local table)
     * @endcode
     */
    static CardinalSplineTo* create(float duration, PointArray* points, float tension);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~CardinalSplineTo();
    /**
     * @js NA
     * @lua NA
     */
    CardinalSplineTo();
    
    /** initializes the action with a duration and an array of points */
    bool initWithDuration(float duration, PointArray* points, float tension);

    virtual void updatePosition(Point &newPos);

    inline PointArray* getPoints() { return _points; }
    /**
     * @js NA
     * @lua NA
     */
    inline void setPoints(PointArray* points)
    {
        CC_SAFE_RETAIN(points);
        CC_SAFE_RELEASE(_points);
        _points = points;
    }

    // Overrides
	virtual CardinalSplineTo *clone() const override;
    virtual CardinalSplineTo* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;

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
    
    /** creates an action with a Cardinal Spline array of points and tension 
     * @code
     * when this function bound to js or lua,the input params are changed
     * in js: var create(var t,var table)
     * in lua: lcaol create(local t, local table)
     * @endcode
     */
    static CardinalSplineBy* create(float duration, PointArray* points, float tension);

    CardinalSplineBy();
    
    // Overrides
    virtual void startWithTarget(Node *target) override;
    virtual void updatePosition(Point &newPos) override;
	virtual CardinalSplineBy *clone() const override;
    virtual CardinalSplineBy* reverse() const override;

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
    
    /** creates an action with a Cardinal Spline array of points and tension 
     * @code
     * when this function bound to js or lua,the input params are changed
     * in js: var create(var dt,var table)
     * in lua: lcaol create(local dt, local table)
     * @endcode
     */
    static CatmullRomTo* create(float dt, PointArray* points);

    /** initializes the action with a duration and an array of points */
    bool initWithDuration(float dt, PointArray* points);

    // Override
	virtual CatmullRomTo *clone() const override;
	virtual CatmullRomTo *reverse() const override;
};

/** An action that moves the target with a CatmullRom curve by a certain distance.
 A Catmull Rom is a Cardinal Spline with a tension of 0.5.
 http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull.E2.80.93Rom_spline
 @ingroup Actions
 */
class CC_DLL CatmullRomBy : public CardinalSplineBy
{
public:
    /** creates an action with a Cardinal Spline array of points and tension 
     * @code
     * when this function bound to js or lua,the input params are changed
     * in js: var create(var dt,var table)
     * in lua: lcaol create(local dt, local table)
     * @endcode
     */
    static CatmullRomBy* create(float dt, PointArray* points);

    /** initializes the action with a duration and an array of points */
    bool initWithDuration(float dt, PointArray* points);

    // Override
	virtual CatmullRomBy *clone() const override;
	virtual CatmullRomBy *reverse() const override;

};

/** Returns the Cardinal Spline position for a given set of control points, tension and time */
extern CC_DLL Point ccCardinalSplineAt(Point &p0, Point &p1, Point &p2, Point &p3, float tension, float t);

// end of actions group
/// @}

NS_CC_END;

#endif // __CCACTION_CATMULLROM_H__
