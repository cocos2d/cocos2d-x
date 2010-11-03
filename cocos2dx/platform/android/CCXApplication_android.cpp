#include "CCXApplication_android.h"
#include "CCXUIImage_android.h"
#include "CCXEGLView_android.h"
#include "CCDirector.h"

// #include "CCXGLExtFunc.h"
#include <GLES/glext.h>
#include <android/log.h>

namespace   cocos2d {
	static CCXApplication *s_pApplication;

    CCXApplication::CCXApplication()
    {
    	s_pApplication = this;
    }

    CCXApplication::~CCXApplication()
    {
        
    }

	ccDeviceOrientation CCXApplication::setDeviceOrientation(ccDeviceOrientation eOritation)
    {
		return eOritation;
    }

    CGRect CCXApplication::statusBarFrame()
    {
        CGRect rc;
        return rc;
    }

	//////////////////////////////////////////////////////////////////////////
	/// Implement static class member
	//////////////////////////////////////////////////////////////////////////
	CCXApplication * CCXApplication::getSharedApplication()
	{
		return s_pApplication;
	}
}

extern "C"
{
JavaVM *gJavaVM = NULL;

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
	gJavaVM = vm;
	return JNI_VERSION_1_4;
}

void Java_org_cocos2dx_DemoRenderer_nativeRender(JNIEnv* env)
{
	cocos2d::CCDirector::getSharedDirector()->preMainLoop();
}

}
