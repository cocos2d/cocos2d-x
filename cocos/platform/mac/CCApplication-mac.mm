/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#import <Cocoa/Cocoa.h>
#import <Metal/Metal.h>
#include <algorithm>

#include "platform/CCApplication.h"
#include "platform/CCFileUtils.h"
#include "math/CCGeometry.h"
#include "base/CCDirector.h"
#include "base/ccUtils.h"
#include "renderer/backend/metal/DeviceMTL.h"

NS_CC_BEGIN

static long getCurrentMillSecond()
{
    long lLastTime = 0;
    struct timeval stCurrentTime;
    
    gettimeofday(&stCurrentTime,NULL);
    lLastTime = stCurrentTime.tv_sec*1000+stCurrentTime.tv_usec*0.001; // milliseconds
    return lLastTime;
}

Application* Application::sm_pSharedApplication = nullptr;

Application::Application()
: _animationInterval(1.0f/60.0f*1000.0f)
{
    CCASSERT(! sm_pSharedApplication, "sm_pSharedApplication already exist");
    sm_pSharedApplication = this;
}

Application::~Application()
{
    CCASSERT(this == sm_pSharedApplication, "sm_pSharedApplication != this");
    sm_pSharedApplication = 0;
}

int Application::run()
{
    initGLContextAttrs();
    if(!applicationDidFinishLaunching())
    {
        return 1;
    }
    
    long lastTime = 0L;
    long curTime = 0L;
    
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    
    // Retain glview to avoid glview being released in the while loop
    glview->retain();

    while (!glview->windowShouldClose())
    {
        lastTime = getCurrentMillSecond();
        
        director->mainLoop();
        glview->pollEvents();

        curTime = getCurrentMillSecond();
        if (curTime - lastTime < _animationInterval)
        {
            usleep(static_cast<useconds_t>((_animationInterval - curTime + lastTime)*1000));
        }
    }

    /* Only work on Desktop
    *  Director::mainLoop is really one frame logic
    *  when we want to close the window, we should call Director::end();
    *  then call Director::mainLoop to do release of internal resources
    */
    if (glview->isOpenGLReady())
    {
        director->end();
        director->mainLoop();
    }
    
    glview->release();
    
    return 0;
}

void Application::setAnimationInterval(float interval)
{
    _animationInterval = interval*1000.0f;
}

Application::Platform Application::getTargetPlatform()
{
    return Platform::OS_MAC;
}

std::string Application::getVersion() {
    NSString* version = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
    if (version) {
        return [version UTF8String];
    }
    return "";
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////////////////////////////

Application* Application::getInstance()
{
    CCASSERT(sm_pSharedApplication, "sm_pSharedApplication not set");
    return sm_pSharedApplication;
}

const char * Application::getCurrentLanguageCode()
{
    static char code[3]={0};
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSArray *languages = [defaults objectForKey:@"AppleLanguages"];
    NSString *currentLanguage = [languages objectAtIndex:0];
    
    // get the current language code.(such as English is "en", Chinese is "zh" and so on)
    NSDictionary* temp = [NSLocale componentsFromLocaleIdentifier:currentLanguage];
    NSString * languageCode = [temp objectForKey:NSLocaleLanguageCode];
    [languageCode getCString:code maxLength:3 encoding:NSASCIIStringEncoding];
    code[2]='\0';
    return code;
}

LanguageType Application::getCurrentLanguage()
{
    // get the current language and country config
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSArray *languages = [defaults objectForKey:@"AppleLanguages"];
    NSString *currentLanguage = [languages objectAtIndex:0];
    
    // get the current language code.(such as English is "en", Chinese is "zh" and so on)
    NSDictionary* temp = [NSLocale componentsFromLocaleIdentifier:currentLanguage];
    NSString * languageCode = [temp objectForKey:NSLocaleLanguageCode];
    
    return utils::getLanguageTypeByISO2([languageCode UTF8String]);
}

bool Application::openURL(const std::string &url)
{
    NSString* msg = [NSString stringWithCString:url.c_str() encoding:NSUTF8StringEncoding];
    NSURL* nsUrl = [NSURL URLWithString:msg];
    return [[NSWorkspace sharedWorkspace] openURL:nsUrl];
}

void Application::setStartupScriptFilename(const std::string& startupScriptFile)
{
    _startupScriptFilename = startupScriptFile;
    std::replace(_startupScriptFilename.begin(), _startupScriptFilename.end(), '\\', '/');
}

const std::string& Application::getStartupScriptFilename()
{
    return _startupScriptFilename;
}

NS_CC_END
