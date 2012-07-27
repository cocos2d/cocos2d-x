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

#import "CCApplication.h"

#import <Cocoa/Cocoa.h>

#import "CCGeometry.h"
#include "CCDirector.h"
#import "CCDirectorCaller.h"

NS_CC_BEGIN;

CCApplication* CCApplication::sm_pSharedApplication = 0;

CCApplication::CCApplication()
{
    CC_ASSERT(! sm_pSharedApplication);
    sm_pSharedApplication = this;
}

CCApplication::~CCApplication()
{
    CC_ASSERT(this == sm_pSharedApplication);
    sm_pSharedApplication = 0;
}

int CCApplication::run()
{
    if (/*initInstance() &&*/ applicationDidFinishLaunching()) 
    {
        [[CCDirectorCaller sharedDirectorCaller] startMainLoop];
    }
    return 0;
}

void CCApplication::setAnimationInterval(double interval)
{
    [[CCDirectorCaller sharedDirectorCaller] setAnimationInterval: interval ];
}

/*
void CCApplication::statusBarFrame(cocos2d::CCRect * rect)
{
#if 0
    rect->origin.x = [[NSApplication sharedApplication] statusBarFrame].origin.x;
    rect->origin.y = [[NSApplication sharedApplication] statusBarFrame].origin.y;
    rect->size.width = [[NSApplication sharedApplication] statusBarFrame].size.width;
    rect->size.height = [[NSApplication sharedApplication] statusBarFrame].size.height;
#endif
}
*/

bool CCApplication::isIpad()
{
	// save whether to load iPad resources so if the window is resized, we are consistent
	static bool isSet = false;
	static bool isIPad = false;
	if( !isSet )
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		isIPad = (winSize.width >= 1024 && winSize.height >= 768);
		isSet = true;
	}
	return isIPad;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////////////////////////////

CCApplication& CCApplication::sharedApplication()
{
    CC_ASSERT(sm_pSharedApplication);
    return *sm_pSharedApplication;
}

ccLanguageType CCApplication::getCurrentLanguage()
{
    // get the current language and country config
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSArray *languages = [defaults objectForKey:@"AppleLanguages"];
    NSString *currentLanguage = [languages objectAtIndex:0];

    // get the current language code.(such as English is "en", Chinese is "zh" and so on)
    NSDictionary* temp = [NSLocale componentsFromLocaleIdentifier:currentLanguage];
    NSString * languageCode = [temp objectForKey:NSLocaleLanguageCode];

    ccLanguageType ret = kLanguageEnglish;
    if ([languageCode isEqualToString:@"zh"])
    {
        ret = kLanguageChinese;
    }
    else if ([languageCode isEqualToString:@"en"])
    {
        ret = kLanguageEnglish;
    }

    return ret;
}

NS_CC_END;
