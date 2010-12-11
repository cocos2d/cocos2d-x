#include "CCXApplication_android.h"
#include "CCXUIImage_android.h"
#include "CCXEGLView_android.h"
#include "CCDirector.h"

#include <GLES/glext.h>

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
    
    void CCXApplication::Run()
    {
    	applicationDidFinishLaunching();
    }

	//////////////////////////////////////////////////////////////////////////
	/// Implement static class member
	//////////////////////////////////////////////////////////////////////////
	CCXApplication * CCXApplication::sharedApplication()
	{
		return s_pApplication;
	}
}
