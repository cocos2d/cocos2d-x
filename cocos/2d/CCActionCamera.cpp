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

#include "CCActionCamera.h"
#include "CCNode.h"
#include "CCStdC.h"

NS_CC_BEGIN
//
// CameraAction
//
void ActionCamera::startWithTarget(Node *target)
{
    ActionInterval::startWithTarget(target);
}

ActionCamera* ActionCamera::clone() const
{
	// no copy constructor
	auto a = new ActionCamera();
	a->autorelease();
	return a;
}

ActionCamera * ActionCamera::reverse() const
{
    // FIXME: This conversion isn't safe.
    return (ActionCamera*)ReverseTime::create(const_cast<ActionCamera*>(this));
}

void ActionCamera::restore()
{
    _eyeX = _eyeY = 0.0f;
    _eyeZ = FLT_EPSILON;

    _centerX = _centerY = _centerZ = 0.0f;

    _upX = 0.0f;
    _upY = 1.0f;
    _upZ = 0.0f;
}

void ActionCamera::setEye(float x, float y, float z)
{
    _eyeX = x;
    _eyeY = y;
    _eyeZ = z;

    updateTransform();
}

void ActionCamera::setCenter(float centerX, float centerY, float centerZ)
{
    _centerX = centerX;
    _centerY = centerY;
    _centerZ = centerZ;

    updateTransform();
}

void ActionCamera::setUp(float upX, float upY, float upZ)
{
    _upX = upX;
    _upY = upY;
    _upZ = upZ;

    updateTransform();
}

void ActionCamera::updateTransform()
{
    kmVec3 eye, center, up;

    kmVec3Fill(&eye, _eyeX, _eyeY , _eyeZ);
    kmVec3Fill(&center, _centerX, _centerY, _centerZ);
    kmVec3Fill(&up, _upX, _upY, _upZ);

    kmMat4 lookupMatrix;
    kmMat4LookAt(&lookupMatrix, &eye, &center, &up);

    Point anchorPoint = _target->getAnchorPointInPoints();

    bool needsTranslation = !anchorPoint.equals(Point::ZERO);

    kmMat4 mv;
    kmMat4Identity(&mv);

    if(needsTranslation) {
        kmMat4 t;
        kmMat4Translation(&t, anchorPoint.x, anchorPoint.y, 0);
        kmMat4Multiply(&mv, &mv, &t);
    }

    kmMat4Multiply(&mv, &mv, &lookupMatrix);

    if(needsTranslation) {
        kmMat4 t;
        kmMat4Translation(&t, -anchorPoint.x, -anchorPoint.y, 0);
        kmMat4Multiply(&mv, &mv, &t);
    }

    // XXX FIXME TODO
    // Using the AdditionalTransform is a complete hack.
    // This should be done by multipliying the lookup-Matrix with the Node's MV matrix
    // And then setting the result as the new MV matrix
    // But that operation needs to be done after all the 'updates'.
    // So the Director should emit an 'director_after_update' event.
    // And this object should listen to it
    _target->setAdditionalTransform(mv);
}

//
// OrbitCamera
//

OrbitCamera * OrbitCamera::create(float t, float radius, float deltaRadius, float angleZ, float deltaAngleZ, float angleX, float deltaAngleX)
{
    OrbitCamera * obitCamera = new OrbitCamera();
    if(obitCamera->initWithDuration(t, radius, deltaRadius, angleZ, deltaAngleZ, angleX, deltaAngleX))
    {
        obitCamera->autorelease();
        return obitCamera;
    }
    CC_SAFE_DELETE(obitCamera);
    return nullptr;
}

OrbitCamera* OrbitCamera::clone() const
{
	// no copy constructor	
	auto a = new OrbitCamera();
	a->initWithDuration(_duration, _radius, _deltaRadius, _angleZ, _deltaAngleZ, _angleX, _deltaAngleX);
	a->autorelease();
	return a;
}

bool OrbitCamera::initWithDuration(float t, float radius, float deltaRadius, float angleZ, float deltaAngleZ, float angleX, float deltaAngleX)
{
    if ( ActionInterval::initWithDuration(t) )
    {
        _radius = radius;
        _deltaRadius = deltaRadius;
        _angleZ = angleZ;
        _deltaAngleZ = deltaAngleZ;
        _angleX = angleX;
        _deltaAngleX = deltaAngleX;

        _radDeltaZ = (float)CC_DEGREES_TO_RADIANS(deltaAngleZ);
        _radDeltaX = (float)CC_DEGREES_TO_RADIANS(deltaAngleX);
        return true;
    }
    return false;
}

void OrbitCamera::startWithTarget(Node *target)
{
    ActionCamera::startWithTarget(target);

    float r, zenith, azimuth;
    this->sphericalRadius(&r, &zenith, &azimuth);
    if( isnan(_radius) )
        _radius = r;
    if( isnan(_angleZ) )
        _angleZ = (float)CC_RADIANS_TO_DEGREES(zenith);
    if( isnan(_angleX) )
        _angleX = (float)CC_RADIANS_TO_DEGREES(azimuth);

    _radZ = (float)CC_DEGREES_TO_RADIANS(_angleZ);
    _radX = (float)CC_DEGREES_TO_RADIANS(_angleX);
}

void OrbitCamera::update(float dt)
{
    float r = (_radius + _deltaRadius * dt) * FLT_EPSILON;
    float za = _radZ + _radDeltaZ * dt;
    float xa = _radX + _radDeltaX * dt;

    float i = sinf(za) * cosf(xa) * r + _centerX;
    float j = sinf(za) * sinf(xa) * r + _centerY;
    float k = cosf(za) * r + _centerZ;

    setEye(i,j,k);
}

void OrbitCamera::sphericalRadius(float *newRadius, float *zenith, float *azimuth)
{
    float r; // radius
    float s;

    float x = _eyeX - _centerX;
    float y = _eyeY - _centerY;
    float z = _eyeZ - _centerZ;

    r = sqrtf( powf(x,2) + powf(y,2) + powf(z,2));
    s = sqrtf( powf(x,2) + powf(y,2));
    if( s == 0.0f )
        s = FLT_EPSILON;
    if(r==0.0f)
        r = FLT_EPSILON;

    *zenith = acosf( z/r);
    if( x < 0 )
        *azimuth= (float)M_PI - asinf(y/s);
    else
        *azimuth = asinf(y/s);

    *newRadius = r / FLT_EPSILON;
}

NS_CC_END
