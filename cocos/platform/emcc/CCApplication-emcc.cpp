/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
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

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_EMSCRIPTEN

#include "CCApplication.h"
//#include "platform/CCFileUtils.h"
#include "base/CCDirector.h"
#include "CCGLViewImpl-emcc.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#ifndef __EMSCRIPTEN__
#define __EMSCRIPTEN__ 1
#endif

#include <locale>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#define  LOGD(...)  emscripten_log(EM_LOG_CONSOLE, ##__VA_ARGS__)

NS_CC_BEGIN

// sharedApplication pointer
Application * Application::sm_pSharedApplication = 0;
std::string Application::_appVersion;
std::string Application::_appBuildVersion;

static bool useBackgroundLoop = false;
static bool useMainLoopTiming = true;

// convert the timespec into milliseconds
static long time2millis(struct timespec *times)
{
	return times->tv_sec * 1000 + times->tv_nsec / 1000000;
}

Application::Application()
{
    CCAssert(! sm_pSharedApplication, "");
    sm_pSharedApplication = this;
    
    const std::string &localeName = emscripten_run_script_string("navigator.languages ? navigator.languages[0] : (navigator.language || navigator.userLanguage)");
    _currentLocale = !localeName.empty() ? localeName.substr(0, 2).c_str() : "en";
}

Application::~Application()
{
    CCAssert(this == sm_pSharedApplication, "");
    sm_pSharedApplication = NULL;
}

extern "C" void mainLoopIter()
{
    if (useMainLoopTiming)
    {
        float animationInterval = Director::getInstance()->getAnimationInterval();
        emscripten_set_main_loop_timing(EM_TIMING_RAF, animationInterval * 60);
        useMainLoopTiming = false;
    }
    
    if (useBackgroundLoop)
        return ;
    
	//CCEGLView::sharedOpenGLView()->handleEvents();
	//TIME_START(mainloop);
	Director::getInstance()->mainLoop();
	//TIME_TOTAL_LOG(mainloop, "one loop");
	//Director::getInstance()->getOpenGLView()->pollEvents();
}

extern "C"
{
    void EMSCRIPTEN_KEEPALIVE backgroundMainLoop()
    {
        if (!useBackgroundLoop)
            return;
        Director::getInstance()->mainLoop();
    }
};

const char *beforeunload_callback(int eventType, const void *reserved, void *userData)
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    
    CCLOG("beforeunload callback");
    if (glview->isOpenGLReady())
    {
        director->end();
        director->mainLoop();
        director = nullptr;
    }
    glview->release();
    
    Application* application = (Application*)userData;
    delete application;
    return nullptr;
}

int Application::run()
{

	struct timespec time_struct;
	double update_time;

	initGLContextAttrs();


	// Initialize instance and cocos2d.
	if (!applicationDidFinishLaunching())
	{
		return 1;
	}

	//clock_gettime(CLOCK_REALTIME, &time_struct);
	update_time = emscripten_get_now(); //time2millis(&time_struct);

	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();

	glview->retain();

	CCLOG("Mainloop begin %f", director->getAnimationInterval());
	// XXX: Set to 1FPS while debugging
    
    EM_ASM(setInterval(function(){ Module.ccall('backgroundMainLoop'); }, 500););
    
    emscripten_set_beforeunload_callback(this, beforeunload_callback);
    
    emscripten_set_main_loop(&mainLoopIter, 0, 1);

	CCLOG("Mainloop end");
	if (glview->isOpenGLReady())
	{
		director->end();
		director->mainLoop();
		director = nullptr;
	}
	glview->release();

	return 0;          
}

void Application::setAnimationInterval(float interval)
{
	CCLOG("Animation interval %f", interval);
	_animationInterval = (long)(interval * 1000);
    
    if (!useMainLoopTiming)
    {
        emscripten_set_main_loop_timing(EM_TIMING_RAF, _animationInterval * 60 / 1000);
    }
}

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
Application* Application::getInstance()
{
    CCAssert(sm_pSharedApplication, "");
    return sm_pSharedApplication;
}

// @deprecated Use getInstance() instead
Application* Application::sharedApplication()
{
    return Application::getInstance();
}

const char * Application::getCurrentLanguageCode()
{
    return _currentLocale.c_str();
}

void Application::setCurrentLocale(const std::string &locale)
{
    _currentLocale = locale;
}

LanguageType Application::getCurrentLanguage()
{
    const char *languageCode = getCurrentLanguageCode();
    if (strcmp(languageCode, "zh") == 0) return LanguageType::CHINESE;
    if (strcmp(languageCode, "en") == 0) return LanguageType::ENGLISH;
    if (strcmp(languageCode, "fr") == 0) return LanguageType::FRENCH;
    if (strcmp(languageCode, "it") == 0) return LanguageType::ITALIAN;
    if (strcmp(languageCode, "de") == 0) return LanguageType::GERMAN;
    if (strcmp(languageCode, "es") == 0) return LanguageType::SPANISH;
    if (strcmp(languageCode, "nl") == 0) return LanguageType::DUTCH;
    if (strcmp(languageCode, "ru") == 0) return LanguageType::RUSSIAN;
    if (strcmp(languageCode, "ko") == 0) return LanguageType::KOREAN;
    if (strcmp(languageCode, "ja") == 0) return LanguageType::JAPANESE;
    if (strcmp(languageCode, "hu") == 0) return LanguageType::HUNGARIAN;
    if (strcmp(languageCode, "pt") == 0) return LanguageType::PORTUGUESE;
    if (strcmp(languageCode, "ar") == 0) return LanguageType::ARABIC;
    if (strcmp(languageCode, "nb") == 0) return LanguageType::NORWEGIAN;
    if (strcmp(languageCode, "pl") == 0) return LanguageType::POLISH;
    if (strcmp(languageCode, "tr") == 0) return LanguageType::TURKISH;
    if (strcmp(languageCode, "uk") == 0) return LanguageType::UKRAINIAN;
    if (strcmp(languageCode, "ro") == 0) return LanguageType::ROMANIAN;
    if (strcmp(languageCode, "bg") == 0) return LanguageType::BULGARIAN;
    return LanguageType::ENGLISH;
}

Application::Platform Application::getTargetPlatform()
{
    return Platform::OS_EMSCRIPTEN;
}

std::string Application::getVersion()
{
    return _appVersion;
}

std::string Application::getBuildVersion()
{
    return _appBuildVersion;
}

void Application::setAppVersion(const std::string &version)
{
    _appVersion = version;
}

void Application::setAppBuildVersion(const std::string &version)
{
    _appBuildVersion = version;
}

void Application::setResourceRootPath(const std::string& rootResDir)
{

}

const std::string& Application::getResourceRootPath(void)
{
    static std::string ret = "/";
    return ret;
}

bool Application::openURL(const std::string &url)
{
    std::string script = "window.open(\"";
    script += url;
    script += "\", \"_blank\")";
    emscripten_run_script(script.c_str());
    return false;
}

void Application::toggleToFullscreen()
{
    auto director = Director::getInstance();
    GLViewImpl *glview = static_cast<GLViewImpl*>(director->getOpenGLView());
    glview->toggleToFullscreen();
}

bool Application::isFullscreen()
{
    auto director = Director::getInstance();
    GLViewImpl *glview = static_cast<GLViewImpl*>(director->getOpenGLView());
    return glview->isFullscreen();
}

void Application::setForegroundMainLoop()
{
    applicationWillEnterForeground();
    
    useBackgroundLoop = false;
}

void Application::setBackgroundMainLoop()
{
    applicationDidEnterBackground();
    useBackgroundLoop = true;
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

