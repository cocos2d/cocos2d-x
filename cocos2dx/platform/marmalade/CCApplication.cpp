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
Application * Application::sm_pSharedApplication = 0;

Application::Application()
{
	IW_CALLSTACK("CCApplication::Application");
	
	_animationInterval = 0;
	CC_ASSERT(! sm_pSharedApplication);
	sm_pSharedApplication = this;
}

Application::~Application()
{
	IW_CALLSTACK("CCApplication::~Application");
	
	CC_ASSERT(this == sm_pSharedApplication);		
	sm_pSharedApplication = NULL;
}
 
int Application::Run()
{
	IW_CALLSTACK("CCApplication::Run");
	
	s3eBool quitRequested = 0;
    bool bNeedQuit = false;

	if (!applicationDidFinishLaunching() )
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

		quitRequested = s3eDeviceCheckQuitRequest();
		if( quitRequested) {
            Director* pDirector = Director::sharedDirector();
            // if opengl view has been released, delete the director.
            if (pDirector->getOpenGLView() == NULL)
            {
                CC_SAFE_DELETE(pDirector);
                bNeedQuit = true;
            }
            else
            {
                pDirector->end();
            }
		}

		if( bNeedQuit ) {
			break;
		}

        Director::sharedDirector()->mainLoop();

		while ((s3eTimerGetMs() - updateTime) < _animationInterval) {
			int32 yield = (int32) (_animationInterval - (s3eTimerGetMs() - updateTime));
			if (yield<0)
				break;
			s3eDeviceYield(yield);
		}
		
	}
	return -1;
}

void Application::setAnimationInterval(double interval)
{
	IW_CALLSTACK("CCXApplication::setAnimationInterval");
	_animationInterval = (uint64)(1000 * interval);		// MH: Added cast to uint64
	
}

void Application::ccAccelerationUpdate()
{
// Accelerometer doesn't work on Marmalade X86 MacOS-X simulator
#if !(defined(__APPLE__) && defined(I3D_ARCH_X86))
	Director* pDirector = Director::sharedDirector();
	pDirector->getAccelerometer()->update((float)s3eAccelerometerGetX(), (float)s3eAccelerometerGetY(), (float)s3eAccelerometerGetZ(), s3eTimerGetMs());	// MH: Added casting to float
#endif
}

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
Application* Application::sharedApplication()	// MH Cocos2dx Director class expects this to return a pointer and not a reference
{
	CC_ASSERT(sm_pSharedApplication);
	return sm_pSharedApplication;					// MH Cocos2dx Director class expects this to return a pointer and not a reference
}

ccLanguageType Application::getCurrentLanguage()
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
			currentLanguage = kLanguageRussian;
			break;
			
		case S3E_DEVICE_LANGUAGE_KOREAN:
			currentLanguage = kLanguageKorean;
			break;
			
		case S3E_DEVICE_LANGUAGE_JAPANESE:
			currentLanguage = kLanguageJapanese;
			break;

		case S3E_DEVICE_LANGUAGE_HUNGARIAN:
			currentLanguage = kLanguageHungarian;
			break;
            
        case S3E_DEVICE_LANGUAGE_PORTUGUESE:
			currentLanguage = kLanguagePortuguese;
			break;
            
        case S3E_DEVICE_LANGUAGE_ARABIC:
			currentLanguage = kLanguageArabic;
			break;
            
		case S3E_DEVICE_LANGUAGE_NORWEGIAN:
			currentLanguage = kLanguageNorwegian;
			break;
			
		case S3E_DEVICE_LANGUAGE_POLISH:
			currentLanguage = kLanguagePolish;
			break;
			
		default:
			currentLanguage = kLanguageEnglish;
			break;
	}
	return currentLanguage;
}

TargetPlatform Application::getTargetPlatform()	// MH: Cocos2dx 2.0.3 added this new method to the protocol
{
	int os = s3eDeviceGetInt(S3E_DEVICE_OS);

	switch (os)
	{
	case S3E_OS_ID_QNX:
		return kTargetBlackBerry;
	case S3E_OS_ID_ANDROID:
		return kTargetAndroid;
	case S3E_OS_ID_IPHONE:
		return kTargetIphone;			// TODO: Need to add distinction between iPad and iPhone
	case S3E_OS_ID_WINDOWS:
		return kTargetWindows;
	case S3E_OS_ID_LINUX:
		return kTargetLinux;
	case S3E_OS_ID_OSX:
		return kTargetMacOS;
	}

	return kTargetWindows;				// TODO: TargetPlatform contains no definition for unsupported platform
}



NS_CC_END;
