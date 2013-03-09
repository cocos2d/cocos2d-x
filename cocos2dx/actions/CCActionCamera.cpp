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
    camera->getCenterXYZ(&m_fCenterXOrig, &m_fCenterYOrig, &m_fCenterZOrig);
    camera->getEyeXYZ(&m_fEyeXOrig, &m_fEyeYOrig, &m_fEyeZOrig);
    camera->getUpXYZ(&m_fUpXOrig, &m_fUpYOrig, &m_fUpZOrig);
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

CCObject * CCOrbitCamera::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCOrbitCamera* pRet = NULL;
    if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
        pRet = (CCOrbitCamera*)(pZone->m_pCopyObject);
    else
    {
        pRet = new CCOrbitCamera();
        pZone = pNewZone = new CCZone(pRet);
    }

    CCActionInterval::copyWithZone(pZone);

    pRet->initWithDuration(m_fDuration, m_fRadius, m_fDeltaRadius, m_fAngleZ, m_fDeltaAngleZ, m_fAngleX, m_fDeltaAngleX);

    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

bool CCOrbitCamera::initWithDuration(float t, float radius, float deltaRadius, float angleZ, float deltaAngleZ, float angleX, float deltaAngleX)
{
    if ( CCActionInterval::initWithDuration(t) )
    {
        m_fRadius = radius;
        m_fDeltaRadius = deltaRadius;
        m_fAngleZ = angleZ;
        m_fDeltaAngleZ = deltaAngleZ;
        m_fAngleX = angleX;
        m_fDeltaAngleX = deltaAngleX;

        m_fRadDeltaZ = (float)CC_DEGREES_TO_RADIANS(deltaAngleZ);
        m_fRadDeltaX = (float)CC_DEGREES_TO_RADIANS(deltaAngleX);
        return true;
    }
    return false;
}

void CCOrbitCamera::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    float r, zenith, azimuth;
    this->sphericalRadius(&r, &zenith, &azimuth);
    if( isnan(m_fRadius) )
        m_fRadius = r;
    if( isnan(m_fAngleZ) )
        m_fAngleZ = (float)CC_RADIANS_TO_DEGREES(zenith);
    if( isnan(m_fAngleX) )
        m_fAngleX = (float)CC_RADIANS_TO_DEGREES(azimuth);

    m_fRadZ = (float)CC_DEGREES_TO_RADIANS(m_fAngleZ);
    m_fRadX = (float)CC_DEGREES_TO_RADIANS(m_fAngleX);
}

void CCOrbitCamera::update(float dt)
{
    float r = (m_fRadius + m_fDeltaRadius * dt) * CCCamera::getZEye();
    float za = m_fRadZ + m_fRadDeltaZ * dt;
    float xa = m_fRadX + m_fRadDeltaX * dt;

    float i = sinf(za) * cosf(xa) * r + m_fCenterXOrig;
    float j = sinf(za) * sinf(xa) * r + m_fCenterYOrig;
    float k = cosf(za) * r + m_fCenterZOrig;

    m_pTarget->getCamera()->setEyeXYZ(i,j,k);
}

void CCOrbitCamera::sphericalRadius(float *newRadius, float *zenith, float *azimuth)
{
    float ex, ey, ez, cx, cy, cz, x, y, z;
    float r; // radius
    float s;

    CCCamera* pCamera = m_pTarget->getCamera();
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
