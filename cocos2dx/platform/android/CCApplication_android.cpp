#include "CCApplication.h"
#include "jni/JniHelper.h"
#include "CCDirector.h"
#include "CCEGLView.h"
#include "android/jni/SystemInfoJni.h"
#include <android/log.h>
#include <jni.h>

#include <cstring>

#define  LOG_TAG    "CCApplication_android Debug"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

NS_CC_BEGIN;

// sharedApplication pointer
CCApplication * CCApplication::sm_pSharedApplication = 0;

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

int CCApplication::run()
{
        // Initialize instance and cocos2d.
        if (! initInstance() || ! applicationDidFinishLaunching())
        {
                return 0;
        }
	
	return -1;
}

void CCApplication::setAnimationInterval(double interval)
{
	JniMethodInfo methodInfo;
	if (! JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/lib/Cocos2dxRenderer", "setAnimationInterval", 
		"(D)V"))
	{
		CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
	}
	else
	{
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, interval);
	}
}

CCApplication::Orientation CCApplication::setOrientation(Orientation orientation)
{
    return orientation;
}

void CCApplication::statusBarFrame(CCRect * rect)
{
    if (rect)
    {
        // android doesn't have status bar.
        *rect = CCRectMake(0, 0, 0, 0);
    }
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
    std::string localInfo = getCurrentLanguageJNI();
    ccLanguageType ret = kLanguageEnglish;

    int pos = localInfo.find("@");
    if (pos == std::string::npos)
    {
        return kLanguageEnglish;
    }

    std::string languageName = localInfo.substr(0, pos);
    std::string countryName  = localInfo.substr(pos + 1);

    if (0 == languageName.compare("zh"))
    {
        if (0 == countryName.compare("CN"))
        {
            ret = kLanguageChinese_Simplified;
        }
        else
        {
            ret = kLanguageChinese_Traditional;
        }
    }
    else if (0 == languageName.compare("ja"))
    {
        ret = kLanguageJapanese;
    }
    else if (0 == languageName.compare("en"))
    {
        ret = kLanguageEnglish;
    }

    return ret;
}

NS_CC_END;
