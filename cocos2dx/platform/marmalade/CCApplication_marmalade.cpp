/****************************************************************************
 Copyright (c) 2011      cocos2d-x.org   http://cocos2d-x.org
 Copyright (c) 2011      Максим Аксенов
 Copyright (c) 2011      Giovanni Zito, Francis Styck

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
	
	s3eBool quitRequested = 0;

	if ( ! initInstance() || !applicationDidFinishLaunching() )
	{
		return 0;
	}
	
	uint64 updateTime = 0 ;
	
	while (true) 
	{ 
		updateTime = s3eTimerGetMs();
			
		s3eDeviceYield(0);
		s3eKeyboardUpdate();
		s3ePointerUpdate();
			
		ccAccelerationUpdate();

		quitRequested = s3eDeviceCheckQuitRequest() ;
		if( quitRequested && CCDirector::sharedDirector()->getOpenGLView() != NULL ) {
			CCDirector::sharedDirector()->end() ;
			// end status will be processed in CCDirector::sharedDirector()->mainLoop();
		}

		CCDirector::sharedDirector()->mainLoop();

		if( quitRequested ) {
			break ;
		}

		while ((s3eTimerGetMs() - updateTime) < m_nAnimationInterval) {
			int32 yield = (int32) (m_nAnimationInterval - (s3eTimerGetMs() - updateTime));
			if (yield<0)
				break;
			s3eDeviceYield(yield);
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
// Accelerometer doesn't work on Marmalade X86 MacOS-X simulator
#if !(defined(__APPLE__) && defined(I3D_ARCH_X86))
	CCAccelerometer::sharedAccelerometer()->update(s3eAccelerometerGetX(),s3eAccelerometerGetY(),s3eAccelerometerGetZ(),s3eTimerGetMs());
#endif
}

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
CCApplication& CCApplication::sharedApplication()
{
	CC_ASSERT(sm_pSharedApplication);
	return *sm_pSharedApplication;
}

ccLanguageType CCApplication::getCurrentLanguage()
{
	int nLanguageIdx;
	ccLanguageType currentLanguage;

	nLanguageIdx = s3eDeviceGetInt(S3E_DEVICE_LANGUAGE);
	
	switch (nLanguageIdx)
	{
		case S3E_DEVICE_LANGUAGE_ENGLISH:
			currentLanguage = kLanguageEnglish;
			break;

		case S3E_DEVICE_LANGUAGE_SIMPL_CHINESE:
		case  S3E_DEVICE_LANGUAGE_TRAD_CHINESE:
			currentLanguage = kLanguageChinese;
			break;

		case S3E_DEVICE_LANGUAGE_FRENCH:
			currentLanguage = kLanguageFrench;
			break;

		case S3E_DEVICE_LANGUAGE_ITALIAN:
			currentLanguage = kLanguageItalian;
			break;

		case S3E_DEVICE_LANGUAGE_GERMAN:
			currentLanguage = kLanguageGerman;
			break;

		case S3E_DEVICE_LANGUAGE_SPANISH:
			currentLanguage = kLanguageSpanish;
			break;

		case S3E_DEVICE_LANGUAGE_RUSSIAN:
			currentLanguage = kLanguageItalian;
			break;

		default:
			currentLanguage = kLanguageRussian;
			break;
	}
	return currentLanguage;
}


NS_CC_END;
