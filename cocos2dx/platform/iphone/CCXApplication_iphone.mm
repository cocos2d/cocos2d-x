#import "CCDirectorCaller.h"

#include "CCXApplication_iphone.h"
#include "CCXUIImage_iphone.h"
#include "CCXEGLView_iphone.h"
#include "CCDirector.h"

#ifdef IPHONE
    #include <OpenGLES/ES1/gl.h>
#else
    #include <GLES/gl.h>
#endif


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
	
    void CCXApplication::run()
    {
        initCocos2d();
        [[CCDirectorCaller sharedDirectorCaller] startMainLoop];
    }

	//////////////////////////////////////////////////////////////////////////
	/// Implement static class member
	//////////////////////////////////////////////////////////////////////////
	CCXApplication * CCXApplication::getSharedApplication()
	{
		return s_pApplication;
	}
}

