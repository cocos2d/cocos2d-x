/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
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

namespace cocos2d {
	class CCCamera;

	/** 
	@brief Base class for CCCamera actions
	*/
	class CC_DLL CCActionCamera : public CCActionInterval //<NSCopying> 
	{
	public:
		CCActionCamera()
			:m_fCenterXOrig(0)
			,m_fCenterYOrig(0)
			,m_fCenterZOrig(0)
			,m_fEyeXOrig(0)
			,m_fEyeYOrig(0)
			,m_fEyeZOrig(0)
			,m_fUpXOrig(0)
			,m_fUpYOrig(0)
			,m_fUpZOrig(0)
		{}
		virtual ~CCActionCamera(){}
		// super methods
		virtual void startWithTarget(CCNode *pTarget);
		virtual CCActionInterval * reverse();
	protected:
		float m_fCenterXOrig;
		float m_fCenterYOrig;
		float m_fCenterZOrig;

		float m_fEyeXOrig;
		float m_fEyeYOrig;
		float m_fEyeZOrig;

		float m_fUpXOrig;
		float m_fUpYOrig;
		float m_fUpZOrig;
	};

	/** 
	@brief CCOrbitCamera action
	Orbits the camera around the center of the screen using spherical coordinates
	*/
	class CC_DLL CCOrbitCamera : public CCActionCamera //<NSCopying> 
	{
	public:
		CCOrbitCamera()
			: m_fRadius(0.0)
            , m_fDeltaRadius(0.0)
            , m_fAngleZ(0.0)
            , m_fDeltaAngleZ(0.0)
            , m_fAngleX(0.0)			
			, m_fDeltaAngleX(0.0)
            , m_fRadZ(0.0)
            , m_fRadDeltaZ(0.0)
            , m_fRadX(0.0)						
			, m_fRadDeltaX(0.0)		
		{}
		~CCOrbitCamera(){}
		/** creates a CCOrbitCamera action with radius, delta-radius,  z, deltaZ, x, deltaX */
		static CCOrbitCamera * actionWithDuration(float t, float radius, float deltaRadius, float angleZ, float deltaAngleZ, float angleX, float deltaAngleX);
		/** initializes a CCOrbitCamera action with radius, delta-radius,  z, deltaZ, x, deltaX */
		bool initWithDuration(float t, float radius, float deltaRadius, float angleZ, float deltaAngleZ, float angleX, float deltaAngleX);
		/** positions the camera according to spherical coordinates */
		void sphericalRadius(float *r, float *zenith, float *azimuth);
		// super methods
		virtual CCObject* copyWithZone(CCZone* pZone);
		virtual void startWithTarget(CCNode *pTarget);
		virtual void update(ccTime time);

	protected:
		float m_fRadius;
		float m_fDeltaRadius;
		float m_fAngleZ;
		float m_fDeltaAngleZ;
		float m_fAngleX;
		float m_fDeltaAngleX;

		float m_fRadZ;
		float m_fRadDeltaZ;
		float m_fRadX;
		float m_fRadDeltaX;
	};

} // namespace cocos2d

#endif //__CCCAMERA_ACTION_H__