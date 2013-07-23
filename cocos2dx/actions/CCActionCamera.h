/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada

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

#include "CCActionInterval.h"

NS_CC_BEGIN

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
    ActionCamera()
		:_centerXOrig(0)
        ,_centerYOrig(0)
        ,_centerZOrig(0)
        ,_eyeXOrig(0)
        ,_eyeYOrig(0)
        ,_eyeZOrig(0)
        ,_upXOrig(0)
        ,_upYOrig(0)
        ,_upZOrig(0)
    {}
    virtual ~ActionCamera(){}

    // Overrides
    virtual void startWithTarget(Node *target) override;
    virtual ActionCamera * reverse() const override;
	virtual ActionCamera *clone() const override;

protected:
    float _centerXOrig;
    float _centerYOrig;
    float _centerZOrig;

    float _eyeXOrig;
    float _eyeYOrig;
    float _eyeZOrig;

    float _upXOrig;
    float _upYOrig;
    float _upZOrig;
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

    OrbitCamera()
		: _radius(0.0)
        , _deltaRadius(0.0)
        , _angleZ(0.0)
        , _deltaAngleZ(0.0)
        , _angleX(0.0)            
        , _deltaAngleX(0.0)
        , _radZ(0.0)
        , _radDeltaZ(0.0)
        , _radX(0.0)                        
        , _radDeltaX(0.0)        
    {}
    ~OrbitCamera(){}
    
    /** initializes a OrbitCamera action with radius, delta-radius,  z, deltaZ, x, deltaX */
    bool initWithDuration(float t, float radius, float deltaRadius, float angleZ, float deltaAngleZ, float angleX, float deltaAngleX);
    /** positions the camera according to spherical coordinates */
    void sphericalRadius(float *r, float *zenith, float *azimuth);

    // Overrides
	OrbitCamera *clone() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;

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