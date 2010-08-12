/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#include <cfloat>
#include "CCCameraAction.h"
#include "CCNode.h"
#include "CCCamera.h"
namespace cocos2d{
	//
	// CameraAction
	//
	void CCCameraAction::startWithTarget(NSObject *pTarget)
	{
		__super::startWithTarget(pTarget);
		
		CCCamera *camera = dynamic_cast<CCNode*>(pTarget)->getCamera();
		camera->getCenterXYZ(&m_fCenterXOrig, &m_fCenterYOrig, &m_fCenterZOrig);
		camera->getEyeXYZ(&m_fEyeXOrig, &m_fEyeYOrig, &m_fEyeZOrig);
		camera->getUpXYZ(&m_fUpXOrig, &m_fUpYOrig, &m_fUpZOrig);
	}
	
	CCIntervalAction * CCCameraAction::reverse()
	{
		return CCReverseTime::actionWithAction(this);
	}
	//
	// CCOrbitCamera
	//
	CCOrbitCamera * CCOrbitCamera::actionWithDuration(float t, float radius, float deltaRadius, float angleZ, float deltaAngleZ, float angleX, float deltaAngleX)
	{
		CCOrbitCamera * pRet = new CCOrbitCamera();
		pRet->initWithDuration(t, radius, deltaRadius, angleZ, deltaAngleZ, angleX, deltaAngleX);
		pRet->autorelease();
		return pRet;
	}

	NSObject * CCOrbitCamera::copyWithZone(NSZone *pZone)
	{
		NSZone* pNewZone = NULL;
		CCOrbitCamera* pRet = NULL;
		if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
			pRet = dynamic_cast<CCOrbitCamera*>(pZone->m_pCopyObject);
		else
		{
			pRet = new CCOrbitCamera();
			pZone = pNewZone = new NSZone(pRet);
		}

		__super::copyWithZone(pZone);

		pRet->initWithDuration(m_fDuration, m_fRadius, m_fDeltaRadius, m_fAngleZ, m_fDeltaAngleZ, m_fAngleX, m_fDeltaAngleX);

		CCX_SAFE_DELETE(pNewZone);
		return pRet;
	}

	CCOrbitCamera * CCOrbitCamera::initWithDuration(float t, float radius, float deltaRadius, float angleZ, float deltaAngleZ, float angleX, float deltaAngleX)
	{
		if ( __super::initWithDuration(t) )
		{
			m_fRadius = radius;
			m_fDeltaRadius = deltaRadius;
			m_fAngleZ = angleZ;
			m_fDeltaAngleZ = deltaAngleZ;
			m_fAngleX = angleX;
			m_fDeltaAngleX = deltaAngleX;

			m_fRadDeltaZ = (CGFloat)CC_DEGREES_TO_RADIANS(deltaAngleZ);
			m_fRadDeltaX = (CGFloat)CC_DEGREES_TO_RADIANS(deltaAngleX);
			return this;
		}
		return NULL;
	}

	void CCOrbitCamera::startWithTarget(NSObject *pTarget)
	{
		__super::startWithTarget(pTarget);
		float r, zenith, azimuth;
		this->sphericalRadius(&r, &zenith, &azimuth);
		if( _isnan(m_fRadius) )
			m_fRadius = r;
		if( _isnan(m_fAngleZ) )
			m_fAngleZ = (CGFloat)CC_RADIANS_TO_DEGREES(zenith);
		if( _isnan(m_fAngleX) )
			m_fAngleX = (CGFloat)CC_RADIANS_TO_DEGREES(azimuth);

		m_fRadZ = (CGFloat)CC_DEGREES_TO_RADIANS(m_fAngleZ);
		m_fRadX = (CGFloat)CC_DEGREES_TO_RADIANS(m_fAngleX);
	}

	void CCOrbitCamera::update(ccTime dt)
	{
		float r = (m_fRadius + m_fDeltaRadius * dt) * CCCamera::getZEye();
		float za = m_fRadZ + m_fRadDeltaZ * dt;
		float xa = m_fRadX + m_fRadDeltaX * dt;

		float i = sinf(za) * cosf(xa) * r + m_fCenterXOrig;
		float j = sinf(za) * sinf(xa) * r + m_fCenterYOrig;
		float k = cosf(za) * r + m_fCenterZOrig;

		dynamic_cast<CCNode*>(m_pTarget)->getCamera()->setEyeXYZ(i,j,k);
	}

	void CCOrbitCamera::sphericalRadius(float *newRadius, float *zenith, float *azimuth)
	{
		float ex, ey, ez, cx, cy, cz, x, y, z;
		float r; // radius
		float s;

		CCCamera* pCamera = dynamic_cast<CCNode*>(m_pTarget)->getCamera();
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
			*azimuth= (CGFloat)M_PI - asinf(y/s);
		else
			*azimuth = asinf(y/s);

		*newRadius = r / CCCamera::getZEye();				
	}
} // namespace cocos2d