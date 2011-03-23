#include "CCApplication.h"
#include "CCEGLView.h"
#include "CCDirector.h"
#include "CCAccelerometer.h"
#include "CCTouchDispatcher.h"


#include <s3e.h>
#include <IwMemBucketHelpers.h>


NS_CC_BEGIN;

// sharedApplication pointer
CCApplication * CCApplication::sm_pSharedApplication = 0;

CCApplication::CCApplication()
{
	IW_CALLSTACK("CCApplication::CCApplication");
	
	m_nAnimationInterval = 0;
	CC_ASSERT(! sm_pSharedApplication);
	sm_pSharedApplication = this;
}

CCApplication::~CCApplication()
{
	IW_CALLSTACK("CCApplication::~CCApplication");
	
	CC_ASSERT(this == sm_pSharedApplication);		
	sm_pSharedApplication = NULL;
}


int CCApplication::Run()
{
	IW_CALLSTACK("CCApplication::Run");
	
	if ( ! initInstance() || !applicationDidFinishLaunching() )
	{
		return 0;
	}
	
	int64 updateTime = s3eTimerGetMs();
	
	while (!s3eDeviceCheckQuitRequest()) 
	{ 
		int64 currentTime = s3eTimerGetMs();
		if (currentTime - updateTime > m_nAnimationInterval)
		{
			updateTime = currentTime;
			
			s3eDeviceYield(0);
			s3eKeyboardUpdate();
			s3ePointerUpdate();
			
			ccAccelerationUpdate();
			CCDirector::sharedDirector()->mainLoop();
		}
		else 
		{
			s3eDeviceYield(0);
		}
		
	}
	return -1;
}

void CCApplication::setAnimationInterval(double interval)
{
	IW_CALLSTACK("CCXApplication::setAnimationInterval");
	m_nAnimationInterval = 1000 * interval;
	
}

CCApplication::Orientation CCApplication::setOrientation(Orientation orientation)
{
	IW_CALLSTACK("CCApplication::setOrientation");
	return orientation;
}

void CCApplication::statusBarFrame(CCRect * rect)
{
	if (rect)
	{
		*rect = CCRectMake(0, 0, 0, 0);
	}
}
void CCApplication::ccAccelerationUpdate()
{
	CCAcceleration AccValue;
	AccValue.x = (double)s3eAccelerometerGetX()/200;
	AccValue.y = (double)s3eAccelerometerGetY()/200;
	AccValue.z = (double)s3eAccelerometerGetZ()/200;
	AccValue.timestamp = (double) 50/ 100;
	
	// call delegates' didAccelerate function
	CCAccelerometer::sharedAccelerometer()->didAccelerate(&AccValue);
}
	
//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
CCApplication& CCApplication::sharedApplication()
{
	CC_ASSERT(sm_pSharedApplication);
	return *sm_pSharedApplication;
}

NS_CC_END;
