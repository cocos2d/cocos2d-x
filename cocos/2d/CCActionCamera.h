/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#ifndef __CCCAMERA_ACTION_H__
#define __CCCAMERA_ACTION_H__

#include "2d/CCActionInterval.h"
#include "math/CCMath.h"

NS_CC_BEGIN

USING_NS_CC_MATH;

class Camera;

/**
 * @addtogroup actions
 * @{
 */

/** 
@brief Base class for Camera actions
@ingroup Actions
*/
class CC_DLL ActionCamera : public ActionInterval //<NSCopying> 
{
public:
    /**
     * @js ctor
     */
    ActionCamera();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ActionCamera(){};

    // Overrides
    virtual void startWithTarget(Node *target) override;
    virtual ActionCamera * reverse() const override;
	virtual ActionCamera *clone() const override;

    /* sets the Eye value of the Camera */
    void setEye(const Vector3 &eye);
    void setEye(float x, float y, float z);
    /* returns the Eye value of the Camera */
    const Vector3& getEye() const { return _eye; }
    /* sets the Center value of the Camera */
    void setCenter(const Vector3 &center);
    /* returns the Center value of the Camera */
    const Vector3& getCenter() const { return _center; }
    /* sets the Up value of the Camera */
    void setUp(const Vector3 &up);
    /* Returns the Up value of the Camera */
    const Vector3& getUp() const { return _up; }

protected:

    void restore();
    void updateTransform();

    Vector3 _center;
    Vector3 _eye;
    Vector3 _up;
};

/** 
@brief OrbitCamera action
Orbits the camera around the center of the screen using spherical coordinates
@ingroup Actions
*/
class CC_DLL OrbitCamera : public ActionCamera //<NSCopying> 
{
public:
    /** creates a OrbitCamera action with radius, delta-radius,  z, deltaZ, x, deltaX */
    static OrbitCamera* create(float t, float radius, float deltaRadius, float angleZ, float deltaAngleZ, float angleX, float deltaAngleX);
    
    /** positions the camera according to spherical coordinates */
    void sphericalRadius(float *r, float *zenith, float *azimuth);

    // Overrides
	OrbitCamera *clone() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    /**
     * @js ctor
     */
    OrbitCamera();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~OrbitCamera();
    
    /** initializes a OrbitCamera action with radius, delta-radius,  z, deltaZ, x, deltaX */
    bool initWithDuration(float t, float radius, float deltaRadius, float angleZ, float deltaAngleZ, float angleX, float deltaAngleX);

protected:
    float _radius;
    float _deltaRadius;
    float _angleZ;
    float _deltaAngleZ;
    float _angleX;
    float _deltaAngleX;

    float _radZ;
    float _radDeltaZ;
    float _radX;
    float _radDeltaX;
};

// end of actions group
/// @}

NS_CC_END

#endif //__CCCAMERA_ACTION_H__