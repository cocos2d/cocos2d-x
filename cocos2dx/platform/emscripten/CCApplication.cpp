#include "CCApplication.h"
#include "platform/CCFileUtils.h"
#include "CCDirector.h"
#include "CCEGLView.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include <emscripten/emscripten.h>

#define  LOGD(...)  fprintf(stderr, __VA_ARGS__)

NS_CC_BEGIN;

// sharedApplication pointer
CCApplication * CCApplication::sm_pSharedApplication = 0;
long CCApplication::_animationInterval = 1000;

// convert the timespec into milliseconds
static long time2millis(struct timespec *times)
{
    return times->tv_sec*1000 + times->tv_nsec/1000000;
}

CCApplication::CCApplication()
{
    CC_ASSERT(! sm_pSharedApplication);
    sm_pSharedApplication = this;
}

CCApplication::~CCApplication()
{
    CC_ASSERT(this == sm_pSharedApplication);
    sm_pSharedApplication = NULL;
}


extern "C" void mainLoopIter(void)
{
    CCEGLView::sharedOpenGLView()->handleEvents();
    CCDirector::sharedDirector()->mainLoop();
}

int CCApplication::run()
{
	struct timespec time_struct;
	long update_time;

	// Initialize instance and cocos2d.
	if (!applicationDidFinishLaunching())
	{
		return 0;
	}

	clock_gettime(CLOCK_REALTIME, &time_struct);
	update_time = time2millis(&time_struct);

    // XXX: Set to 1FPS while debugging
    emscripten_set_main_loop(&mainLoopIter, 0, 1);
	
	return -1;
}

void CCApplication::setAnimationInterval(double interval)
{
	// interval in milliseconds
	_animationInterval = (long)(interval * 1000);
}

void CCApplication::setResourceRootPath(const std::string& rootResDir)
{
    _resourceRootPath = rootResDir;
    if (_resourceRootPath[_resourceRootPath.length() - 1] != '/')
    {
        _resourceRootPath += '/';
    }
    CCFileUtils* pFileUtils = CCFileUtils::sharedFileUtils();
    std::vector<std::string> searchPaths = pFileUtils->getSearchPaths();
    searchPaths.insert(searchPaths.begin(), _resourceRootPath);
    pFileUtils->setSearchPaths(searchPaths);
}

const std::string& CCApplication::getResourceRootPath(void)
{
    return _resourceRootPath;
}

TargetPlatform CCApplication::getTargetPlatform()
{
    return kTargetEmscripten;
}

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
CCApplication* CCApplication::sharedApplication()
{
    CC_ASSERT(sm_pSharedApplication);
    return sm_pSharedApplication;
}

ccLanguageType CCApplication::getCurrentLanguage()
{
    return kLanguageEnglish;
}

NS_CC_END;
