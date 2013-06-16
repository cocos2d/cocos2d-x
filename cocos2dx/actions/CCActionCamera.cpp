/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.
 
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
#include "base_nodes/CCNode.h"
#include "CCCamera.h"
#include "CCStdC.h"
#include "cocoa/CCZone.h"

NS_CC_BEGIN
//
// CameraAction
//
void CCActionCamera::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    
    CCCamera *camera = pTarget->getCamera();
    camera->getCenterXYZ(&_centerXOrig, &_centerYOrig, &_centerZOrig);
    camera->getEyeXYZ(&_eyeXOrig, &_eyeYOrig, &_eyeZOrig);
    camera->getUpXYZ(&_upXOrig, &_upYOrig, &_upZOrig);
}

CCActionCamera* CCActionCamera::clone() const
{
	auto a = new CCActionCamera(*this);
	a->autorelease();
	return a;
}

CCActionInterval * CCActionCamera::reverse()
{
    return CCReverseTime::create(this);
}
//
// CCOrbitCamera
//

CCOrbitCamera * CCOrbitCamera::create(float t, float radius, float deltaRadius, float angleZ, float deltaAngleZ, float angleX, float deltaAngleX)
{
    CCOrbitCamera * pRet = new CCOrbitCamera();
    if(pRet->initWithDuration(t, radius, deltaRadius, angleZ, deltaAngleZ, angleX, deltaAngleX))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCOrbitCamera* CCOrbitCamera::clone() const
{
	auto a = new CCOrbitCamera(*this);
	a->initWithDuration(_duration, _radius, _deltaRadius, _angleZ, _deltaAngleZ, _angleX, _deltaAngleX);
	a->autorelease();
	return a;
}

CCObject * CCOrbitCamera::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCOrbitCamera* pRet = NULL;
    if(pZone && pZone->_copyObject) //in case of being called at sub class
        pRet = (CCOrbitCamera*)(pZone->_copyObject);
    else
    {
        pRet = new CCOrbitCamera();
        pZone = pNewZone = new CCZone(pRet);
    }

    CCActionInterval::copyWithZone(pZone);

    pRet->initWithDuration(_duration, _radius, _deltaRadius, _angleZ, _deltaAngleZ, _angleX, _deltaAngleX);

    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

bool CCOrbitCamera::initWithDuration(float t, float radius, float deltaRadius, float angleZ, float deltaAngleZ, float angleX, float deltaAngleX)
{
    if ( CCActionInterval::initWithDuration(t) )
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

void CCOrbitCamera::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
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

void CCOrbitCamera::update(float dt)
{
    float r = (_radius + _deltaRadius * dt) * CCCamera::getZEye();
    float za = _radZ + _radDeltaZ * dt;
    float xa = _radX + _radDeltaX * dt;

    float i = sinf(za) * cosf(xa) * r + _centerXOrig;
    float j = sinf(za) * sinf(xa) * r + _centerYOrig;
    float k = cosf(za) * r + _centerZOrig;

    _target->getCamera()->setEyeXYZ(i,j,k);
}

void CCOrbitCamera::sphericalRadius(float *newRadius, float *zenith, float *azimuth)
{
    float ex, ey, ez, cx, cy, cz, x, y, z;
    float r; // radius
    float s;

    CCCamera* pCamera = _target->getCamera();
    pCamera->getEyeXYZ(&ex, &ey, &ez);
    pCamera->getCenterXYZ(&cx, &cy, &cz);

    x = ex-cx;
    y = ey-cy;
    z = ez-cz;

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

    *newRadius = r / CCCamera::getZEye();                
}

NS_CC_END
